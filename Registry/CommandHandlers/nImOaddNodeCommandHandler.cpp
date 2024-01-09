//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Registry/CommandHandlers/nImOaddNodeCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'add node' command handler.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
//
//              All rights reserved. Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following conditions are met:
//                * Redistributions of source code must retain the above copyright notice, this list
//                  of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright notice, this
//                  list of conditions and the following disclaimer in the documentation and / or
//                  other materials provided with the distribution.
//                * Neither the name of the copyright holders nor the names of its contributors may
//                  be used to endorse or promote products derived from this software without
//                  specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//              DAMAGE.
//
//  Created:    2023-04-04
//
//--------------------------------------------------------------------------------------------------

#include "nImOaddNodeCommandHandler.h"

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <nImOregistryCommands.h>
#include <nImOregistryTypes.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO 'add node' command handler. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::AddNodeCommandHandler::AddNodeCommandHandler
    (SpContextWithNetworking    owner,
     SpRegistry                 theRegistry,
     const Connection &         statusConnection) :
        inherited{owner, theRegistry}, _statusConnection{statusConnection}
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::AddNodeCommandHandler::AddNodeCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::AddNodeCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments)
    const
{
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    bool    okSoFar{false};

    _owner->report("add node request received"s);
    if (6 < arguments.size())
    {
        auto        machineNameString{arguments[1]->asString()};
        auto        nodeNameString{arguments[2]->asString()};
        auto        execPathString{arguments[3]->asString()};
        auto        launchDirectoryString{arguments[4]->asString()};
        auto        commandLineString{arguments[5]->asString()};
        auto        connArray{arguments[6]->asArray()};
        Connection  theConnection;
        ServiceType theType;

        if (3 < connArray->size())
        {
            auto    addressValue{(*connArray)[0]->asInteger()};
            auto    portValue{(*connArray)[1]->asInteger()};
            auto    transportValue{(*connArray)[2]->asInteger()};
            auto    typeValue{(*connArray)[3]->asInteger()};

            if (nullptr != addressValue)
            {
                theConnection._address = addressValue->getIntegerValue();
            }
            if (nullptr != portValue)
            {
                theConnection._port = portValue->getIntegerValue();
            }
            if (nullptr != transportValue)
            {
                theConnection._transport = StaticCast(TransportType, transportValue->getIntegerValue());
            }
            if (nullptr != typeValue)
            {
                theType = StaticCast(ServiceType, typeValue->getIntegerValue());
            }
        }
        if ((nullptr != machineNameString) && (nullptr != nodeNameString) && (nullptr != execPathString) && (nullptr != launchDirectoryString) &&
            (nullptr != commandLineString) && (nullptr != connArray))
        {
            auto    address{theConnection._address};
            auto    status{_registry->addMachine(machineNameString->getValue(), address)};

            if (status.first)
            {
                auto    nodeName{nodeNameString->getValue()};
                auto    execPath{execPathString->getValue()};
                auto    launchDirectory{launchDirectoryString->getValue()};
                auto    commandLine{commandLineString->getValue()};

                status = _registry->addNode(nodeName, execPath, launchDirectory, commandLine, theType, theConnection);
                if (status.first)
                {
                    okSoFar = sendSimpleResponse(socket, kAddNodeResponse, "add node"s, true);
                    if (okSoFar)
                    {
                        sendStatusReport(_owner, _statusConnection, kNodeAddedStatus + kStatusSeparator + nodeName);
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != machineNameString) && (nullptr != nodeNameString) && (nullptr != execPathString) && " //####
                    "(nullptr != launchDirectoryString) && (nullptr != commandLineString) && (nullptr != connArray))"); //####
        }
    }
    else
    {
        ODL_LOG("! (6 < arguments.size())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::AddNodeCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Registry/CommandHandlers/nImOaddConnectionCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'add connection' command handler.
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
//  Created:    2023-07-23
//
//--------------------------------------------------------------------------------------------------

#include "nImOaddConnectionCommandHandler.h"

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <ContainerTypes/nImOarray.h>
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
 @brief The class definition for the %nImO 'add connection' command handler. */
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

nImO::AddConnectionCommandHandler::AddConnectionCommandHandler
    (SpContextWithNetworking    owner,
     SpRegistry                 theRegistry,
     const Connection &         statusConnection) :
        inherited{owner, theRegistry}, _statusConnection{statusConnection}
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::AddConnectionCommandHandler::AddConnectionCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::AddConnectionCommandHandler::doIt
    (asio::ip::tcp::socket &    socket,
     const Array &              arguments)
    const
{
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    bool    okSoFar{false};

    _owner->report("add connection request received");
    if (6 < arguments.size())
    {
        SpValue         element1{arguments[1]};
        SpValue         element2{arguments[2]};
        SpValue         element3{arguments[3]};
        SpValue         element4{arguments[4]};
        SpValue         element5{arguments[5]};
        SpValue         element6{arguments[6]};
        CPtr(String)    fromNodeNameString{element1->asString()};
        CPtr(String)    fromPathString{element2->asString()};
        CPtr(String)    toNodeNameString{element3->asString()};
        CPtr(String)    toPathString{element4->asString()};
        CPtr(String)    dataTypeString{element5->asString()};
        CPtr(Integer)   modeString{element6->asInteger()};

        if ((nullptr != fromNodeNameString) && (nullptr != fromPathString) && (nullptr != toNodeNameString) && (nullptr != toPathString) &&
            (nullptr != dataTypeString) && (nullptr != modeString))
        {
            std::string     fromNodeName{fromNodeNameString->getValue()};
            std::string     fromPath{fromPathString->getValue()};
            std::string     toNodeName{toNodeNameString->getValue()};
            std::string     toPath{toPathString->getValue()};
            std::string     dataType{dataTypeString->getValue()};
            TransportType   mode{StaticCast(TransportType, modeString->getIntegerValue())};
            auto            status{_registry->addConnection(fromNodeName, fromPath, toNodeName, toPath, dataType, mode)};

            if (status.first)
            {
                okSoFar = sendSimpleResponse(socket, kAddConnectionResponse, "add connection", true);
                if (okSoFar)
                {
                    sendStatusReport(_owner, _statusConnection, kConnectionAddedStatus + kStatusSeparator + fromNodeName + kStatusSeparator +
                                     fromPath + kStatusSeparator + toNodeName + kStatusSeparator + toPath + kStatusSeparator +
                                     std::to_string(modeString->getIntegerValue()));
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != fromNodeNameString) && (nullptr != fromPathString) && (nullptr != toNodeNameString) && " //####
                    "(nullptr != toPathString) && (nullptr != dataTypeString) && (nullptr != modeString))"); //####
        }
    }
    else
    {
        ODL_LOG("! (6 < arguments.size())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::AddConnectionCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Launcher/CommandHandlers/nImOreloadAppListCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO reload app list command handler.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-01-16
//
//--------------------------------------------------------------------------------------------------

#include <Launcher/CommandHandlers/nImOreloadAppListCommandHandler.h>

//#include <BasicTypes/nImOaddress.h>
//#include <BasicTypes/nImOinteger.h>
//#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
//#include <nImOinChannel.h>
#include <nImOlauncherCommands.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO reload app list command handler. */
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

nImO::ReloadAppListCommandHandler::ReloadAppListCommandHandler
    (SpLauncherContext  owner) :
        inherited{owner}
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::ReloadAppListCommandHandler::ReloadAppListCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::ReloadAppListCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments)
    const
{
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    bool    okSoFar{false};

    _ownerForLauncher->report("get run params for app request received"s);
#if 0
    if (3 < arguments.size())
    {
        auto    pathString{arguments[1]->asString()};
        auto    dataTypeString{arguments[2]->asString()};
        auto    modeValue{arguments[3]->asInteger()};

        if ((nullptr != pathString) && (nullptr != dataTypeString) && (nullptr != modeValue))
        {
            auto    theChannel{_ownerForLauncher->getInputChannel(pathString->getValue())};

            if (nullptr == theChannel)
            {
                ODL_LOG("(nullptr == theChannel)"); //####
            }
            else
            {
                if (theChannel->setUp(StaticCast(TransportType, modeValue->getIntegerValue())))
                {
                    auto    theConnection{theChannel->getConnection()};
                    auto    infoArray{std::make_shared<Array>()};

                    infoArray->addValue(std::make_shared<Address>(theConnection._address));
                    infoArray->addValue(std::make_shared<Integer>(theConnection._port));
                    okSoFar = sendComplexResponse(socket, kReloadAppListResponse, "set up receiver"s, infoArray);
                }
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != pathString) && (nullptr != dataTypeString) && (nullptr != modeValue))"); //####
        }
    }
    else
    {
        ODL_LOG("! (3 < arguments.size())"); //####
    }
#endif//0
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ReloadAppListCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

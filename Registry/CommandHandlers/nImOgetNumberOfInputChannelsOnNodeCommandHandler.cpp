//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Registry/CommandHandlers/nImOgetNumberOfInputChannelsOnNodeCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'get number of input channels on node' command handler.
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
//  Created:    2024-02-24
//
//--------------------------------------------------------------------------------------------------

#include "nImOgetNumberOfInputChannelsOnNodeCommandHandler.h"

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
 @brief The class definition for the %nImO 'get number of input channels on node' command handler. */
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

nImO::GetNumberOfInputChannelsOnNodeCommandHandler::GetNumberOfInputChannelsOnNodeCommandHandler
    (SpServiceContext   owner,
     SpRegistry         theRegistry) :
        inherited{owner, theRegistry}
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "theRegistry = ", theRegistry.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::GetNumberOfInputChannelsOnNodeCommandHandler::GetNumberOfInputChannelsOnNodeCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::GetNumberOfInputChannelsOnNodeCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments,
     std::string &  reason)
    const
{
    NIMO_UNUSED_VAR_(arguments);
    ODL_OBJENTER(); //####
    ODL_P3("socket = ", &socket, "arguments = ", &arguments, "reason = ", &reason); //####
    bool    okSoFar{false};

    _owner->report("get number of input channels on node request received."s);
    if (1 < arguments.size())
    {
        auto    asString{arguments[1]->asString()};

        if (nullptr == asString)
        {
            ODL_LOG("(nullptr == asString)"); //####
            reason = "Invalid argument(s)"s;
        }
        else
        {
            auto    statusWithInt{_registry->getNumberOfInputChannelsOnNode(asString->getValue())};

            if (statusWithInt.first.first)
            {
                auto    count{std::make_shared<Integer>(statusWithInt.second)};

                okSoFar = sendComplexResponse(socket, kGetNumberOfInputChannelsOnNodeResponse, "get number of input channels on node"s, count, reason);
                ODL_B1("okSoFar = ", okSoFar); //####
            }
            else
            {
                ODL_LOG("! (statusWithInt.first.first)"); //####
                reason = "getNumberOfInputChannelsOnNode() returned '"s + statusWithInt.first.second + "'"s;
            }
        }
    }
    else
    {
        ODL_LOG("! (1 < arguments.size())"); //####
        reason = "Missing argument(s)"s;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetNumberOfInputChannelsOnNodeCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

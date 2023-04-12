//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOremoveNodeCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'remove node' command handler.
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

#include "nImOremoveNodeCommandHandler.h"

#include <nImOarray.h>
#include <nImOregistryCommands.h>
#include <nImOregistryTypes.h>
#include <nImOstring.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO 'remove node' command handler. */
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

nImO::RemoveNodeCommandHandler::RemoveNodeCommandHandler
    (SpContextWithNetworking    owner,
     SpRegistry                 theRegistry,
     const Connection &         statusConnection) :
        inherited(owner), _registry(theRegistry), _statusConnection(statusConnection)
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::RemoveNodeCommandHandler::RemoveNodeCommandHandler

nImO::RemoveNodeCommandHandler::~RemoveNodeCommandHandler
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::RemoveNodeCommandHandler::~RemoveNodeCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::RemoveNodeCommandHandler::doIt
    (asio::ip::tcp::socket &    socket,
     const Array &              arguments)
    const
{
    bool    okSoFar = false;

    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    _owner->report("remove node request received");
    if (1 < arguments.size())
    {
        SpValue         element{arguments[1]};
        CPtr(String)    asString{element->asString()};

        if (nullptr != asString)
        {
            std::string         nodeName{asString->getValue()};
            RegSuccessOrFailure status{_registry->removeNode(nodeName)};

            if (status.first)
            {
                okSoFar = sendSimpleResponse(socket, kRemoveNodeResponse, "remove node", true);
                if (okSoFar)
                {
                    sendStatusReport(_owner, _statusConnection, kNodeRemovedStatus + kStatusSeparator + nodeName);
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != asString)"); //####
        }
    }
    else
    {
        ODL_LOG("! (1 < arguments.size())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::RemoveNodeCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

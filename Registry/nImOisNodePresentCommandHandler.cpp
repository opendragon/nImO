//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOisNodePresentCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'node present' command handler.
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
//  Created:    2023-04-03
//
//--------------------------------------------------------------------------------------------------

#include "nImOisNodePresentCommandHandler.h"

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
 @brief The class definition for the %nImO 'node present' command handler. */
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

nImO::NodePresentCommandHandler::NodePresentCommandHandler
    (SpContextWithNetworking    owner,
     SpRegistry                 theRegistry) :
        inherited(owner), _registry(theRegistry)
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::NodePresentCommandHandler::NodePresentCommandHandler

nImO::NodePresentCommandHandler::~NodePresentCommandHandler
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::NodePresentCommandHandler::~NodePresentCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::NodePresentCommandHandler::doIt
    (asio::ip::tcp::socket &    socket,
     const Array &              arguments)
    const
{
    bool    okSoFar = false;

    NIMO_UNUSED_ARG_(arguments);
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    _owner->report("node present request received");
    if (1 < arguments.size())
    {
        SpValue         element{arguments[1]};
        CPtr(String)    asString{element->asString()};

        if (nullptr != asString)
        {
            RegBoolOrFailure    statusWithBool{_registry->isNodePresent(asString->getValue())};

            if (statusWithBool.first.first)
            {
                okSoFar = sendSimpleResponse(socket, kIsNodePresentResponse, "node present", statusWithBool.second);
            }
            else
            {
                ODL_LOG("! (statusWithBool.first.first)"); //####
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
} // nImO::NodePresentCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOgetNamesOfNodesCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'names of nodes' command handler.
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
//  Created:    2023-04-09
//
//--------------------------------------------------------------------------------------------------

#include "nImOgetNamesOfNodesCommandHandler.h"

#include <nImOarray.h>
#include <nImOinteger.h>
#include <nImOregistryCommands.h>
#include <nImOregistryTypes.h>
#include <nImOset.h>
#include <nImOstring.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO 'names of nodes' command handler. */
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

nImO::NamesOfNodesCommandHandler::NamesOfNodesCommandHandler
    (SpContextWithNetworking    owner,
     SpRegistry                 theRegistry) :
        inherited(owner), _registry(theRegistry)
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::NamesOfNodesCommandHandler::NamesOfNodesCommandHandler

nImO::NamesOfNodesCommandHandler::~NamesOfNodesCommandHandler
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::NamesOfNodesCommandHandler::~NamesOfNodesCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::NamesOfNodesCommandHandler::doIt
    (asio::ip::tcp::socket &    socket,
     const Array &              arguments)
    const
{
    bool    okSoFar = false;

    NIMO_UNUSED_ARG_(arguments);
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    _owner->report("names of nodes request received");
    if (0 < arguments.size())
    {
        RegStringSetOrFailure   statusWithSet{_registry->getNamesOfNodes()};

        if (statusWithSet.first.first)
        {
            StringSet & theStrings{statusWithSet.second};
            SpSet       stringSet{new Set};

            for (auto walker = theStrings.begin(); walker != theStrings.end(); ++walker)
            {
                stringSet->addValue(std::make_shared<String>(*walker));
            }
            okSoFar = sendComplexResponse(socket, kGetNamesOfNodesResponse, "names of nodes", stringSet);
        }
        else
        {
            ODL_LOG("! (statusWithSet.first.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (0 < arguments.size())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::NamesOfNodesCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
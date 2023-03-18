//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryProxy.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for access to nImO registries.
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
//  Created:    2023-01-26
//
//--------------------------------------------------------------------------------------------------

#include <nImOregistryProxy.h>

#include <nImOcommandTypes.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for access to %nImO registries. */
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

nImO::RegistryProxy::RegistryProxy
    (ContextWithNetworking &    context,
     const std::string &        address,
     const uint16_t             port) :
        _context(context), _address(address), _port(port)
{
    ODL_ENTER(); //####
    _context.report("RegistryProxy found at " + _address + ":" + std::to_string(_port) + ".");
    ODL_EXIT_P(this); //####
} // nImO::RegistryProxy::RegistryProxy

nImO::RegistryProxy::~RegistryProxy
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::RegistryProxy::~~RegistryProxy

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::RegSuccessOrFailure
nImO::RegistryProxy::addNode
    (const std::string &    nodeName,
     const Connection &     nodeConnection)
{
    NIMO_UNUSED_ARG_(nodeName);
    NIMO_UNUSED_ARG_(nodeConnection);
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{false, "not implemented"};

    //TBD
    ODL_OBJEXIT(); //####
    return status;
} // nImO::RegistryProxy::addNode

nImO::RegNodeInfoOrFailure
nImO::RegistryProxy::getNodeInformation
    (const std::string &    nodeName)
    const
{
    NIMO_UNUSED_ARG_(nodeName);
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{false, "not implemented"};
    NodeInfo            info;

    //TBD
    ODL_OBJEXIT(); //####
    return RegNodeInfoOrFailure{status, info};
} // nImO::RegistryProxy::getNodeInformation

nImO::RegStringSetOrFailure
nImO::RegistryProxy::getNodes
    (void)
    const
{
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{false, "not implemented"};
    StringSet           strings;

    //TBD
    ODL_OBJEXIT(); //####
    return RegStringSetOrFailure{status, strings};
} // nImO::RegistryProxy::getNodes

nImO::RegBoolOrFailure
nImO::RegistryProxy::nodePresent
    (const std::string &    nodeName)
{
    NIMO_UNUSED_ARG_(nodeName);
    bool    found = false;

    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{false, "not implemented"};

    //TBD
    ODL_OBJEXIT(); //####
    return RegBoolOrFailure{status, found};
} // nImO::RegistryProxy::nodePresent

nImO::RegIntOrFailure
nImO::RegistryProxy::numNodes
    (void)
    const
{
    int count = -1;

    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{false, "not implemented"};

    //TBD
    ODL_OBJEXIT(); //####
    return RegIntOrFailure{status, count};
} // nImO::RegistryProxy::numNodes

nImO::RegSuccessOrFailure
nImO::RegistryProxy::removeNode
    (const std::string &    nodeName)
{
    NIMO_UNUSED_ARG_(nodeName);
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{false, "not implemented"};

    //TBD
    ODL_OBJEXIT(); //####
    return status;
} // nImO::RegistryProxy::removeNode

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithZeroConfig.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO execution contexts that use mDNS.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2022 by OpenDragon.
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
//  Created:    2022-07-18
//
//--------------------------------------------------------------------------------------------------

#include "nImOcontextWithZeroConfig.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO execution contexts that use mDNS. */
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

nImO::ContextWithZeroConfig::ContextWithZeroConfig
    (const std::string &    executableName,
     const bool             logging,
     const std::string &    nodeName) :
        inherited(executableName, nodeName), _logger(nullptr)
{
    ODL_ENTER(); //####
    //ODL_S2s("progName = ", executableName, "nodeName = ", nodeName); //####
    //ODL_B1("logging = ", logging); //####
    try
    {
        if (logging)
        {
            _logger = new Logger;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::ContextWithZeroConfig::ContextWithZeroConfig

nImO::ContextWithZeroConfig::~ContextWithZeroConfig
    (void)
{
    ODL_OBJENTER(); //####
    removeAllListeners();
    if (nullptr != _logger)
    {
        delete _logger;
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithZeroConfig::~ContextWithZeroConfig

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::ContextWithZeroConfig::addListener
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::ContextWithZeroConfig::addListener

/*! @brief Remove all listeners. */
void
nImO::ContextWithZeroConfig::removeAllListeners
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::ContextWithZeroConfig::removeAllListeners

void
nImO::ContextWithZeroConfig::removeListener
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::ContextWithZeroConfig::removeListener

void
nImO::ContextWithZeroConfig::report
    (const std::string &    message)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("message = ", message); //####
    if (nullptr != _logger)
    {
        _logger->report(message);
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithZeroConfig::report

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

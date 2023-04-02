//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontext.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO execution context.
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
//  Created:    2022-07-05
//
//--------------------------------------------------------------------------------------------------

#include <nImOcontext.h>

#include <nImOvalue.h>

#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO execution context. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief Flag to prevent more than one context per application. */
static bool lContextCreated = false;

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

nImO::Context::Context
    (const std::string &    executableName,
     const std::string &    nodeName) :
        _executableName(executableName), _nodeName(nodeName), _service(new asio::io_service)
{
    ODL_ENTER(); //####
    ODL_S2s("executableName = ", executableName, "nodeName = ", nodeName); //####
    ODL_P1("_service <- ", _service.get()); //!!!
    if (lContextCreated)
    {
        throw "Too many contexts.";

    }
    try
    {
        lContextCreated = true;
        Value::initialize();
#if 0
#if (defined(ODL_ENABLE_LOGGING_) && defined(MpM_LogIncludesYarpTrace))
        yarp::os::Network::setVerbosity(1);
#else // ! (defined(ODL_ENABLE_LOGGING_) && defined(MpM_LogIncludesYarpTrace))
        yarp::os::Network::setVerbosity(-1);
#endif // ! (defined(ODL_ENABLE_LOGGING_) && defined(MpM_LogIncludesYarpTrace))
        double  intPart;
        double  now = yarp::os::Time::now();
        double  fraction = modf(now, &intPart);
        int     seed = StaticCast(int, ceil(fraction * kMaxRandom));

#if defined(MpM_ChattyStart)
# if MAC_OR_LINUX_
        if (lLogger)
        {
            std::string message{"Program "};

            message += progName;
#  if USE_YARP_FATAL_NOT_FAIL_
            lLogger->info("%s", message.c_str());
#  else // ! USE_YARP_FATAL_NOT_FAIL_
            lLogger->info(message.c_str());
#  endif // ! USE_YARP_FATAL_NOT_FAIL_
            lLogger->info("Movement And Meaning Version: " MpM_VERSION_ ", YARP Version: "
                          YARP_VERSION_STRING ", ACE Version: " ACE_VERSION);
        }
# endif // MAC_OR_LINUX_
#endif // defined(MpM_ChattyStart)
        ODL_D2("time = ", now, "fraction = ", fraction); //####
        ODL_I1("seed = ", seed); //####
        yarp::os::Random::seed(seed);
#endif//0
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::Context::Context

nImO::Context::~Context
    (void)
{
    ODL_OBJENTER(); //####
    lContextCreated = false;
    ODL_OBJEXIT(); //####
} // nImO::Context::~Context

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

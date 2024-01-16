//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOlauncherContext.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO Launcher execution context.
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
//  Created:    2024-01-15
//
//--------------------------------------------------------------------------------------------------

#include <Contexts/nImOlauncherContext.h>

//#include <CommandHandlers/nImOsetUpReceiverCommandHandler.h>
//#include <CommandHandlers/nImOsetUpSenderCommandHandler.h>
//#include <CommandHandlers/nImOstartReceiverCommandHandler.h>
//#include <CommandHandlers/nImOstartSenderCommandHandler.h>
//#include <CommandHandlers/nImOstopReceiverCommandHandler.h>
//#include <CommandHandlers/nImOstopSenderCommandHandler.h>
#include <nImOlauncherCommands.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO Launcher execution context. */
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

nImO::LauncherContext::LauncherContext
    (const int              argc,
     Ptr(Ptr(char))         argv,
     const std::string &    executableName,
     const std::string &    tagForLogging,
     const bool             logging,
     const std::string &    nodeName) :
        inherited{argc, argv, executableName, tagForLogging, logging, true, nodeName}
{
    ODL_ENTER(); //####
    ODL_S3s("executableName = ", executableName, "tagForLogging = ", tagForLogging, "nodeName = ", nodeName); //####
    ODL_B1("logging = ", logging); //####
    try
    {
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::LauncherContext::LauncherContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::AddLauncherHandlers
    (SpLauncherContext      context,
     Ptr(CallbackFunction)  shutdownCallback)
{
    ODL_ENTER(); //####
    ODL_P2("context = ", context.get(), "shutdownCallback = ", shutdownCallback); //####
    // Note that we have to add our handlers first, since adding the standard handlers initiates an acceptor.
    auto    actualContext{context.get()};

    if (nullptr != actualContext)
    {
#if 0
        bool    goAhead{true};
        auto    newHandler1{std::make_shared<StartReceiverCommandHandler>(context)};

        ODL_P1("newHandler1 <- ", newHandler1.get()); //####
        if (! actualContext->addHandler(kStartReceiverRequest, newHandler1))
        {
            goAhead = false;
        }
        if (goAhead)
        {
            auto    newHandler2{std::make_shared<StartSenderCommandHandler>(context)};

            ODL_P1("newHandler2 <- ", newHandler2.get()); //####
            if (! actualContext->addHandler(kStartSenderRequest, newHandler2))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler3{std::make_shared<StopReceiverCommandHandler>(context)};

            ODL_P1("newHandler3 <- ", newHandler3.get()); //####
            if (! actualContext->addHandler(kStopReceiverRequest, newHandler3))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler4{std::make_shared<StopSenderCommandHandler>(context)};

            ODL_P1("newHandler4 <- ", newHandler4.get()); //####
            if (! actualContext->addHandler(kStopSenderRequest, newHandler4))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler5{std::make_shared<SetUpReceiverCommandHandler>(context)};

            ODL_P1("newHandler5 <- ", newHandler5.get()); //####
            if (! actualContext->addHandler(kSetUpReceiverRequest, newHandler5))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler6{std::make_shared<SetUpSenderCommandHandler>(context)};

            ODL_P1("newHandler6 <- ", newHandler6.get()); //####
            if (! actualContext->addHandler(kSetUpSenderRequest, newHandler6))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            ServiceContext::addStandardHandlers(context, shutdownCallback);
        }
#endif//0
    }
    ODL_EXIT(); //####
} // nImO::AddInputOutputHandlers

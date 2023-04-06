//--------------------------------------------------------------------------------------------------
//
//  File:       nImOregistryMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to provide a central registry for nImO.
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
//  Created:    2022-07-24
//
//--------------------------------------------------------------------------------------------------

#include "nImOaddNodeCommandHandler.h"
#include "nImOisNodePresentCommandHandler.h"
#include "nImOgetNumberOfNodesCommandHandler.h"
#include "nImOregistry.h"
#include "nImOregistryContext.h"
#include "nImOremoveNodeCommandHandler.h"

#include <nImOmainSupport.h>
#include <nImOregistryCommands.h>
#include <nImOserviceContext.h>
#include <nImOserviceOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A service application to register #nImO entities. */

/*! @dir Registry
 @brief The set of files that implement the Register application. */
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
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for the #nImO Registry.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    nImO::DescriptorVector  argumentList;
    nImO::ServiceOptions    optionValues;
    int                     exitCode = 0;

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::ReportVersions();
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Registry", "", 2022, NIMO_COPYRIGHT_NAME_, optionValues,
                                    nImO::kSkipArgsOption | nImO::kSkipChannelOption | nImO::kSkipEndpointOption | nImO::kSkipFlavoursOption |
                                    nImO::kSkipGoOption | nImO::kSkipInfoOption | nImO::kSkipModOption | nImO::kSkipNodeOption |
                                    nImO::kSkipPortOption | nImO::kSkipTagOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::DisableWaitForRegistry(true);
            nImO::SpContextWithNetworking   ourContext{new nImO::RegistryContext{argc, argv, progName, optionValues._logging, true}};
            nImO::Connection                statusConnection{ourContext->getStatusInfo()};

            ODL_P1("ourContext <- ", ourContext.get()); //!!!
            nImO::ServiceContext::addStandardHandlers(ourContext);
            if (ourContext->asServiceContext()->findRegistry(true))
            {
                ourContext->report("Registry already running.");
            }
            else
            {
                nImO::SpRegistry    theRegistry{new nImO::Registry{ourContext, optionValues._logging}};

                ODL_P1("theRegistry <- ", theRegistry.get()); //!!!
                if (nullptr == theRegistry)
                {
                    ourContext->report("Could not create Registry.");
                }
                else
                {
                    Ptr(nImO::RegistryContext)  asRegistryContext{ReinterpretCast(Ptr(nImO::RegistryContext), ourContext.get())};

                    asRegistryContext->addHandler(nImO::kAddNodeRequest, new nImO::AddNodeCommandHandler(ourContext, theRegistry, statusConnection));
                    asRegistryContext->addHandler(nImO::kIsNodePresentRequest, new nImO::NodePresentCommandHandler(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNumberOfNodesRequest, new nImO::NumNodesCommandHandler(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kRemoveNodeRequest, new nImO::RemoveNodeCommandHandler(ourContext, theRegistry,
                                                                                                               statusConnection));
                    if (asRegistryContext->makePortAnnouncement(asRegistryContext->getCommandPort(), NIMO_REGISTRY_SERVICE_NAME,
                                                                nImO::GetShortComputerName(), NIMO_REGISTRY_ADDRESS_KEY))
                    {
                        for ( ; nImO::gKeepRunning; )
                        {
                            this_thread::yield();
    //TBD
                        }
                        asRegistryContext->removeAnnouncement();
                    }
                }
            }
            nImO::EnableWaitForRegistry();
            ourContext->report("exiting.");
        }
        catch (...)
        {
            ODL_LOG("Exception caught"); //####
            exitCode = -1;
        }
    }
    ODL_EXIT_I(exitCode); //####
    return exitCode;
} // main

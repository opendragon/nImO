//--------------------------------------------------------------------------------------------------
//
//  File:       nImOlauncherMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to provide remote launch capabilities for nImO.
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
//  Created:    2023-02-10
//
//--------------------------------------------------------------------------------------------------

#include <nImOcommonCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOserviceContext.h>
#include <nImOserviceOptions.h>
#include <nImOstringArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A service application to provide remote launch capabilities for #nImO. */

/*! @dir Launcher
 @brief The set of files that implement the Launcher application. */
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

/*! @brief The entry point for remote launching for #nImO.
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
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Launcher", "", 2023, NIMO_COPYRIGHT_NAME_, optionValues,
                                    nImO::kSkipArgsOption | nImO::kSkipChannelOption | nImO::kSkipEndpointOption | nImO::kSkipFlavoursOption |
                                    nImO::kSkipGoOption | nImO::kSkipInfoOption | nImO::kSkipPortOption | nImO::kSkipReportOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            std::string                     nodeName;
            nImO::SpContextWithNetworking   ourContext{new nImO::ServiceContext{argc, argv, progName, "launcher", optionValues._logging, true}};
            nImO::Connection                registryConnection;
            Ptr(nImO::ServiceContext)       asServiceContext{ourContext->asServiceContext()};

            if (0 < optionValues._node.length())
            {
                nodeName = optionValues._node;
            }
            else
            {
                nodeName = nImO::GetShortComputerName() + "-launcher";
            }
            nImO::ServiceContext::addStandardHandlers(ourContext);
            if (asServiceContext->findRegistry(registryConnection))
            {
                nImO::RegistryProxy     proxy{ourContext, registryConnection};
                nImO::RegBoolOrFailure  statusWithBool = proxy.isNodePresent(nodeName);

                if (statusWithBool.first.first)
                {
                    if (statusWithBool.second)
                    {
                        ourContext->report(nodeName + " already running.");
                        std::cerr << nodeName << " already running." << std::endl;
                        exitCode = 1;
                    }
                    else
                    {
                        nImO::RegSuccessOrFailure   status = proxy.addNode(nodeName, nImO::ServiceType::LauncherService,
                                                                           asServiceContext->getCommandConnection());

                        if (status.first)
                        {
                            ourContext->report("waiting for requests.");
                            for ( ; nImO::gKeepRunning; )
                            {
                                this_thread::yield();
        //TBD
                            }
                            nImO::gKeepRunning = true; // So that the call to 'removeNode' won't fail...
                            status = proxy.removeNode(nodeName);
                            if (! status.first)
                            {
                                std::cerr << "Problem with 'removeNode': " << status.second << std::endl;
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'addNode': " << status.second << std::endl;
                            exitCode = 1;
                        }
                    }
                }
                else
                {
                    std::cerr << "Problem with 'isNodePresent': " << statusWithBool.first.second << std::endl;
                    exitCode = 1;
                }
            }
            else
            {
                ourContext->report("Registry not found.");
                exitCode = 2;
            }
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

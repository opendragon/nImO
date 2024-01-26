//--------------------------------------------------------------------------------------------------
//
//  File:       nImOlauchMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to start a service via a nImO launcher.
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
//  Created:    2024-01-26
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <Contexts/nImOutilityContext.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOstandardOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to start a service via a #nImO launcher. */

/*! @dir Bridge
 @brief The set of files that implement the Bridge application. */
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

/*! @brief The entry point for starting a service via a #nImO launcher.

 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string                     progName{*argv};
    nImO::StringArgumentDescriptor  firstArg{"launcher"s, "Launcher to use"s, nImO::ArgumentMode::Optional, ""s};
    nImO::StringArgumentDescriptor  secondArg{"service"s, "Service to launch"s, nImO::ArgumentMode::Optional, ""s};
    nImO::DescriptorVector          argumentList{};
    nImO::StandardOptions           optionValues{};
    int                             exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(&firstArg);
    argumentList.push_back(&secondArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Launch a service"s, "nImOlaunch launcher-node passthrough"s, 2024,
                                     nImO::kCopyrightName, optionValues, nullptr, nImO::kSkipExpandedOption |
                                     nImO::kSkipFlavoursOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>(progName, "launch"s, optionValues._logging)};
            nImO::Connection    registryConnection{};

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                nImO::RegistryProxy proxy{ourContext, registryConnection};
                auto                launcherName{firstArg.getCurrentValue()};
                auto                serviceName{secondArg.getCurrentValue()};

std::cerr << "** Unimplemented **\n";
                if (launcherName.empty())
                {
                    auto    statusWithAllNodes{proxy.getInformationForAllNodes()};

                    if (statusWithAllNodes.first.first)
                    {
                        nImO::StdStringSet  launchers{};
                        auto                nodes{statusWithAllNodes.second};

                        for (auto & walker : nodes)
                        {
                            if (walker._found && (nImO::ServiceType::LauncherService == walker._serviceType))
                            {
                                launchers.insert(walker._name);
                            }
                        }
                        if (launchers.empty())
                        {
                            ourContext->report("No launchers found."s);
                            exitCode = 1;
                        }
                        else
                        {
                            //TBD     obtain list of launchers and ask for which launcher to use or none
// set launcherName
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getInformationForAllNodes': " << statusWithAllNodes.first.second << "\n";
                        exitCode = 1;
                    }
                }
                else
                {
                    auto    statusWithNodeInfo{proxy.getNodeInformation(launcherName)};

                    if (statusWithNodeInfo.first.first)
                    {
                        if (statusWithNodeInfo.second._found)
                        {
                            if (nImO::ServiceType::LauncherService != statusWithNodeInfo.second._serviceType)
                            {
                                ourContext->report("'" + launcherName + "' is not a launcher."s);
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            ourContext->report("Unknown node: '"s + launcherName + "'"s);
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    //TBD     connect to launcher
                    if (serviceName.empty())
                    {
                        //TBD     obtain list of services and ask for which to launch, or none
// set serviceName
                    }
                    else
                    {
                        //TBD     if service is unknown, error message and exit
                    }
                }
                if (0 == exitCode)
                {
                    //TBD     get service options and service parameters
                    //TBD     ask which options are to be applied
                    //TBD     ask for values for parameters
                    //TBD     launch service via launcher with provided options and parameters
                }
            }
            else
            {
                ourContext->report("Registry not found."s);
                exitCode = 2;
            }
            ourContext->report("exiting."s, false);
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

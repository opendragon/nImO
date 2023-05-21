//--------------------------------------------------------------------------------------------------
//
//  File:       nImOshutdownMain.cpp
//
//  Project:    nImO
//
//  Contains:   A tool to shutdown all active nImO applications except copies of nImOmonitor.
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
//  Created:    2023-03-14
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <Contexts/nImOutilityContext.h>
#include <nImOcommonCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOrequestResponse.h>
#include <nImOstandardOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A tool to shutdown all active #nImO applications except copies of nImOmonitor.. */

/*! @dir Shutdown
 @brief The set of files that implement the Shutdown tool. */
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

/*! @brief The entry point for the tool.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string                     progName{*argv};
    nImO::StringArgumentDescriptor  firstArg{"node", T_("Node to be shutdown (if machine is not specified)"), nImO::ArgumentMode::Optional, ""};
    nImO::DescriptorVector          argumentList;
    nImO::StandardOptions           optionValues;
    int                             exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::ReportVersions();
    argumentList.push_back(&firstArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Shutdown one node or machine or all nodes", "nImOshutdown [node]", 2023,
                                     NIMO_COPYRIGHT_NAME_, optionValues, nullptr, nImO::kSkipFlavoursOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::SpContextWithNetworking   ourContext{new nImO::UtilityContext{progName, "shutdown", optionValues._logging}};
            std::string                     nodeName{firstArg.getCurrentValue()};
            nImO::Connection                registryConnection;

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                nImO::RegistryProxy proxy{ourContext, registryConnection};

                if (0 < optionValues._machine.length())
                {
                    nImO::RegNodeInfoVectorOrFailure    statusWithAllNodes{proxy.getInformationForAllNodesOnMachine(optionValues._machine)};

                    if (statusWithAllNodes.first.first)
                    {
                        nImO::NodeInfoVector &  nodes{statusWithAllNodes.second};

                        // Send Shutdown command to all launchers on the machine.
                        for (auto walker = nodes.begin(); walker != nodes.end(); ++walker)
                        {
                            auto    theInfo{*walker};

                            if (theInfo._found && (nImO::ServiceType::LauncherService == theInfo._serviceType))
                            {
                                ourContext->report("sending shutdown request to " + theInfo._name);
                                nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, theInfo._connection, nImO::kShutDownRequest,
                                                                                 nImO::kShutDownResponse);
                                // Give the service time to inform the Registry.
                                nImO::ConsumeSomeTime(ourContext.get(), 20);
                            }
                            else
                            {
                                ODL_LOG("! (theInfo._found && (nImO::ServiceType::LauncherService == theInfo._serviceType))"); //####
                            }
                        }


                        // TBD: Close all connections for nodes on the machine.
                        if (optionValues._expanded)
                        {
                            ourContext->report("closing all connections");
                        }
                        // Send Shutdown command to all other nodes on the machine.
                        for (auto walker = nodes.begin(); walker != nodes.end(); ++walker)
                        {
                            auto    theInfo{*walker};

                            if (theInfo._found && (nImO::ServiceType::LauncherService != theInfo._serviceType))
                            {
                                ourContext->report("sending shutdown request to " + nodeName);
                                nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, theInfo._connection, nImO::kShutDownRequest,
                                                                                 nImO::kShutDownResponse);
                                // Give the service time to inform the Registry.
                                nImO::ConsumeSomeTime(ourContext.get(), 20);
                            }
                            else
                            {
                                ODL_LOG("! (theInfo._found && (nImO::ServiceType::LauncherService != theInfo._serviceType))"); //####
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getInformationForAllNodes': " << statusWithAllNodes.first.second << std::endl;
                        exitCode = 1;
                    }
                }
                else if (0 < nodeName.length())
                {
                    nImO::RegNodeInfoOrFailure  statusWithInfo{proxy.getNodeInformation(nodeName)};

                    if (statusWithInfo.first.first)
                    {
                        if (statusWithInfo.second._found)
                        {
                            // Close all connections for services on the node.
                            if (optionValues._expanded)
                            {
                                ourContext->report("closing all connections to " + nodeName);
                            }
                            // TBD
                            // Send Shutdown command to the node.
                            if (optionValues._expanded)
                            {
                                ourContext->report("sending shutdown request to " + nodeName);
                            }
                            nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, statusWithInfo.second._connection, nImO::kShutDownRequest,
                                                                             nImO::kShutDownResponse);
                        }
                        else
                        {
                            ourContext->report("Unknown node: '" + nodeName + "'");
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getNodeInformation': " << statusWithInfo.first.second << std::endl;
                        exitCode = 1;
                    }
                }
                else
                {
                    nImO::RegNodeInfoVectorOrFailure    statusWithAllNodes{proxy.getInformationForAllNodes()};

                    if (statusWithAllNodes.first.first)
                    {
                        nImO::NodeInfoVector &  nodes{statusWithAllNodes.second};

                        // Send Shutdown command to all launchers.
                        for (auto walker = nodes.begin(); walker != nodes.end(); ++walker)
                        {
                            auto    theInfo{*walker};

                            if (theInfo._found && (nImO::ServiceType::LauncherService == theInfo._serviceType))
                            {
                                ourContext->report("sending shutdown request to " + nodeName);
                                nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, theInfo._connection, nImO::kShutDownRequest,
                                                                                 nImO::kShutDownResponse);
                                // Give the service time to inform the Registry.
                                nImO::ConsumeSomeTime(ourContext.get(), 20);
                            }
                            else
                            {
                                ODL_LOG("! (theInfo._found && (nImO::ServiceType::LauncherService == theInfo._serviceType))"); //####
                            }
                        }


                        // TBD: Close all connections.
                        if (optionValues._expanded)
                        {
                            ourContext->report("closing all connections");
                        }
                        // Send Shutdown command to all other nodes.
                        for (auto walker = nodes.begin(); walker != nodes.end(); ++walker)
                        {
                            auto    theInfo{*walker};

                            if (theInfo._found && (nImO::ServiceType::LauncherService != theInfo._serviceType))
                            {
                                ourContext->report("sending shutdown request to " + nodeName);
                                nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, theInfo._connection, nImO::kShutDownRequest,
                                                                                 nImO::kShutDownResponse);
                                // Give the service time to inform the Registry.
                                nImO::ConsumeSomeTime(ourContext.get(), 20);
                            }
                            else
                            {
                                ODL_LOG("! (theInfo._found && (nImO::ServiceType::LauncherService != theInfo._serviceType))"); //####
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getInformationForAllNodes': " << statusWithAllNodes.first.second << std::endl;
                        exitCode = 1;
                    }
                    // Give the Registry time to handle pending requests.
                    nImO::ConsumeSomeTime(ourContext.get(), 20);
                    ourContext->report("sending shutdown request to Registry");
                    // Send Shutdown command to Registry.
                    nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, registryConnection, nImO::kShutDownRequest, nImO::kShutDownResponse);
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

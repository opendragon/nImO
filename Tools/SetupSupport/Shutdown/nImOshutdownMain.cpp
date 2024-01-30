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

#include <string>

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
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::StringArgumentDescriptor>("node"s,
                                                                                      "Node to be shutdown (if machine is not specified)"s,
                                                                                      nImO::ArgumentMode::Optional, ""s)};
    nImO::DescriptorVector  argumentList{};
    nImO::StandardOptions   optionValues{};
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(firstArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Shutdown one node or machine or all nodes"s, "nImOshutdown node"s, 2023,
                                     nImO::kCopyrightName, optionValues, nullptr, nImO::kSkipFlavoursOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>(progName, "shutdown"s, optionValues._logging)};
            auto                nodeName{firstArg->getCurrentValue()};
            nImO::Connection    registryConnection{};

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                nImO::RegistryProxy proxy{ourContext, registryConnection};

                if (optionValues._machine.empty())
                {
                    if (nodeName.empty())
                    {
                        auto    statusWithAllNodes{proxy.getInformationForAllNodes()};

                        if (statusWithAllNodes.first.first)
                        {
                            auto    nodes{statusWithAllNodes.second};

                            // Send Shutdown command to all launchers.
                            for (auto & walker : nodes)
                            {
                                if (walker._found && (nImO::ServiceType::LauncherService == walker._serviceType))
                                {
                                    ourContext->report("sending shutdown request to '"s + walker._name + "'."s);
                                    nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, walker._connection, nImO::kShutDownRequest,
                                                                                     nImO::kShutDownResponse);
                                    // Give the service time to inform the Registry.
                                    nImO::ConsumeSomeTime(ourContext.get(), 20);
                                    auto    statusWithBool{proxy.removeNode(walker._name)};

                                    if (! statusWithBool.first.first)
                                    {
                                        std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << "\n";
                                    }
                                }
                            }
                            if (optionValues._expanded)
                            {
                                ourContext->report("closing all connections"s);
                            }
                            auto    statusWithAllConnections{proxy.getInformationForAllConnections()};

                            if (statusWithAllConnections.first.first)
                            {
                                for (auto & walker : statusWithAllConnections.second)
                                {
                                    bool    okSoFar{true};

                                    if (walker._found)
                                    {
                                        auto                fromNode{walker._fromNode};
                                        auto                fromPath{walker._fromPath};
                                        auto                toNode{walker._toNode};
                                        auto                toPath{walker._toPath};
                                        nImO::Connection    fromConnection;
                                        auto                statusWithNodeInfo{proxy.getNodeInformation(fromNode)};

                                        if (statusWithNodeInfo.first.first)
                                        {
                                            if (statusWithNodeInfo.second._found)
                                            {
                                                fromConnection = statusWithNodeInfo.second._connection;
                                            }
                                            else
                                            {
                                                ourContext->report("Unknown node: '"s + fromNode + "'."s);
                                                okSoFar = false;
                                            }
                                        }
                                        else
                                        {
                                            std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                                            okSoFar = false;
                                        }
                                        if (okSoFar)
                                        {
                                            statusWithNodeInfo = proxy.getNodeInformation(toNode);
                                            if (statusWithNodeInfo.first.first)
                                            {
                                                if (statusWithNodeInfo.second._found)
                                                {
                                                    bool    reported{false};

                                                    nImO::CloseConnection(ourContext, fromNode, proxy, fromPath, true, reported);
                                                }
                                                else
                                                {
                                                    ourContext->report("Unknown node: '"s + toNode + "'."s);
                                                }
                                            }
                                            else
                                            {
                                                std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                std::cerr << "Problem with 'getInformationForAllConnections': " << statusWithAllConnections.first.second << "\n";
                                exitCode = 1;
                            }
                            // Send Shutdown command to all other nodes.
                            for (auto & walker : nodes)
                            {
                                if (walker._found && (nImO::ServiceType::LauncherService != walker._serviceType))
                                {
                                    ourContext->report("sending shutdown request to '"s + walker._name + "'."s);
                                    nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, walker._connection, nImO::kShutDownRequest,
                                                                                     nImO::kShutDownResponse);
                                    // Give the service time to inform the Registry.
                                    nImO::ConsumeSomeTime(ourContext.get(), 20);
                                    auto    statusWithBool{proxy.removeNode(walker._name)};

                                    if (! statusWithBool.first.first)
                                    {
                                        std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << "\n";
                                    }
                                }
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'getInformationForAllNodes': " << statusWithAllNodes.first.second << "\n";
                            exitCode = 1;
                        }
                        // Give the Registry time to handle pending requests.
                        nImO::ConsumeSomeTime(ourContext.get(), 20);
                        ourContext->report("sending shutdown request to Registry."s);
                        // Send Shutdown command to Registry.
                        nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, registryConnection, nImO::kShutDownRequest,
                                                                         nImO::kShutDownResponse);
                    }
                    else
                    {
                        auto    statusWithInfo{proxy.getNodeInformation(nodeName)};

                        if (statusWithInfo.first.first)
                        {
                            if (statusWithInfo.second._found)
                            {
                                // Close all connections for services on the node.
                                if (optionValues._expanded)
                                {
                                    ourContext->report("closing all connections to node '"s + nodeName + "'."s);
                                }
                                auto    statusWithAllConnections{proxy.getInformationForAllConnectionsOnNode(nodeName)};

                                if (statusWithAllConnections.first.first)
                                {
                                    for (auto & walker : statusWithAllConnections.second)
                                    {
                                        bool    okSoFar{true};

                                        if (walker._found)
                                        {
                                            auto                fromNode{walker._fromNode};
                                            auto                fromPath{walker._fromPath};
                                            auto                toNode{walker._toNode};
                                            auto                toPath{walker._toPath};
                                            nImO::Connection    fromConnection;
                                            auto                statusWithNodeInfo{proxy.getNodeInformation(fromNode)};

                                            if (statusWithNodeInfo.first.first)
                                            {
                                                if (statusWithNodeInfo.second._found)
                                                {
                                                    fromConnection = statusWithNodeInfo.second._connection;
                                                }
                                                else
                                                {
                                                    ourContext->report("Unknown node: '"s + fromNode + "'."s);
                                                    okSoFar = false;
                                                }
                                            }
                                            else
                                            {
                                                std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                                                okSoFar = false;
                                            }
                                            if (okSoFar)
                                            {
                                                statusWithNodeInfo = proxy.getNodeInformation(toNode);
                                                if (statusWithNodeInfo.first.first)
                                                {
                                                    if (statusWithNodeInfo.second._found)
                                                    {
                                                        bool    reported{false};

                                                        nImO::CloseConnection(ourContext, fromNode, proxy, fromPath, true, reported);
                                                        auto    statusWithBool{proxy.clearChannelInUse(fromNode, fromPath)};

                                                        if (! statusWithBool.first.first)
                                                        {
                                                            std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                                                            okSoFar = false;
                                                        }
                                                        if (okSoFar)
                                                        {
                                                            statusWithBool = proxy.clearChannelInUse(toNode, toPath);
                                                            if (! statusWithBool.first.first)
                                                            {
                                                                std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        ourContext->report("Unknown node: '"s + toNode + "'."s);
                                                    }
                                                }
                                                else
                                                {
                                                    std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                                                    exitCode = 1;
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    std::cerr << "Problem with 'getInformationForAllConnectionsOnNode': " << statusWithAllConnections.first.second <<
                                                "\n";
                                    exitCode = 1;
                                }
                                // Send Shutdown command to the node.
                                if (optionValues._expanded)
                                {
                                    ourContext->report("sending shutdown request to '"s + nodeName + "'."s);
                                }
                                nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, statusWithInfo.second._connection, nImO::kShutDownRequest,
                                                                                 nImO::kShutDownResponse);
                                auto    statusWithBool{proxy.removeNode(nodeName)};

                                if (! statusWithBool.first.first)
                                {
                                    std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << "\n";
                                }
                            }
                            else
                            {
                                ourContext->report("Unknown node: '"s + nodeName + "'."s);
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'getNodeInformation': " << statusWithInfo.first.second << "\n";
                            exitCode = 1;
                        }
                    }
                }
                else
                {
                    auto    statusWithAllNodes{proxy.getInformationForAllNodesOnMachine(optionValues._machine)};

                    if (statusWithAllNodes.first.first)
                    {
                        auto    nodes{statusWithAllNodes.second};

                        // Send Shutdown command to all the launchers on the machine.
                        for (auto & walker : nodes)
                        {
                            if (walker._found && (nImO::ServiceType::LauncherService == walker._serviceType))
                            {
                                ourContext->report("sending shutdown request to '"s + walker._name + "'."s);
                                nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, walker._connection, nImO::kShutDownRequest,
                                                                                 nImO::kShutDownResponse);
                                // Give the service time to inform the Registry.
                                nImO::ConsumeSomeTime(ourContext.get(), 20);
                                auto    statusWithBool{proxy.removeNode(walker._name)};

                                if (! statusWithBool.first.first)
                                {
                                    std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << "\n";
                                }
                            }
                            else
                            {
                                ODL_LOG("! (walker._found && (nImO::ServiceType::LauncherService == walker._serviceType))"); //####
                            }
                        }
                        if (optionValues._expanded)
                        {
                            ourContext->report("closing all connections on machine '"s + optionValues._machine + "'."s);
                        }
                        auto    statusWithAllConnections{proxy.getInformationForAllConnectionsOnMachine(optionValues._machine)};

                        if (statusWithAllConnections.first.first)
                        {
                            for (auto & walker : statusWithAllConnections.second)
                            {
                                bool    okSoFar{true};

                                if (walker._found)
                                {
                                    auto                fromNode{walker._fromNode};
                                    auto                fromPath{walker._fromPath};
                                    auto                toNode{walker._toNode};
                                    auto                toPath{walker._toPath};
                                    nImO::Connection    fromConnection;
                                    auto                statusWithNodeInfo{proxy.getNodeInformation(fromNode)};

                                    if (statusWithNodeInfo.first.first)
                                    {
                                        if (statusWithNodeInfo.second._found)
                                        {
                                            fromConnection = statusWithNodeInfo.second._connection;
                                        }
                                        else
                                        {
                                            ourContext->report("Unknown node: '"s + fromNode + "'."s);
                                            okSoFar = false;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                                        okSoFar = false;
                                    }
                                    if (okSoFar)
                                    {
                                        statusWithNodeInfo = proxy.getNodeInformation(toNode);
                                        if (statusWithNodeInfo.first.first)
                                        {
                                            if (statusWithNodeInfo.second._found)
                                            {
                                                bool    reported{false};

                                                nImO::CloseConnection(ourContext, fromNode, proxy, fromPath, true, reported);
                                                auto    statusWithBool{proxy.clearChannelInUse(fromNode, fromPath)};

                                                if (! statusWithBool.first.first)
                                                {
                                                    std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                                                    okSoFar = false;
                                                }
                                                if (okSoFar)
                                                {
                                                    statusWithBool = proxy.clearChannelInUse(toNode, toPath);
                                                    if (! statusWithBool.first.first)
                                                    {
                                                        std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                ourContext->report("Unknown node: '"s + toNode + "'."s);
                                            }
                                        }
                                        else
                                        {
                                            std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                                            exitCode = 1;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'getInformationForAllConnectionsOnMachine': " << statusWithAllConnections.first.second <<
                                        "\n";
                            exitCode = 1;
                        }
                        // Send Shutdown command to all other nodes on the machine.
                        for (auto & walker : nodes)
                        {
                            if (walker._found && (nImO::ServiceType::LauncherService != walker._serviceType))
                            {
                                ourContext->report("sending shutdown request to '"s + walker._name + "'."s);
                                nImO::SendRequestWithNoArgumentsAndEmptyResponse(ourContext, walker._connection, nImO::kShutDownRequest,
                                                                                 nImO::kShutDownResponse);
                                // Give the service time to inform the Registry.
                                nImO::ConsumeSomeTime(ourContext.get(), 20);
                                auto    statusWithBool{proxy.removeNode(walker._name)};

                                if (! statusWithBool.first.first)
                                {
                                    std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << "\n";
                                }
                            }
                            else
                            {
                                ODL_LOG("! (walker._found && (nImO::ServiceType::LauncherService != walker._serviceType))"); //####
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getInformationForAllNodes': " << statusWithAllNodes.first.second << "\n";
                        exitCode = 1;
                    }
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

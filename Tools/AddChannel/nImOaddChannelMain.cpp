//--------------------------------------------------------------------------------------------------
//
//  File:       nImOaddChannelMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to add nImO channels to a node.
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
//  Created:    2024-02-25
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOlogicalArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <Contexts/nImOutilityContext.h>
#include <nImOchannelName.h>
#include <nImOinputOutputCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOrequestResponse.h>
#include <nImOstandardOptions.h>
#include <ResponseHandlers/nImOaddInputChannelResponseHandler.h>
#include <ResponseHandlers/nImOaddOutputChannelResponseHandler.h>
#include <ResponseHandlers/nImOgetChannelLimitsResponseHandler.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to add #nImO channels to a node. */

/*! @dir Connect
 @brief The set of files that implement the AddChannel application. */
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

/*! @brief The entry point for connecting two #nImO channels together.

 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::StringArgumentDescriptor>("node"s, "Node to get new channel"s,
                                                                                      nImO::ArgumentMode::Required, ""s)};
    auto                    secondArg{std::make_shared<nImO::LogicalArgumentDescriptor>("isOutput"s,
                                                                                        "True if the new channel is an output"s,
                                                                                        nImO::ArgumentMode::Optional, false)};
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
    argumentList.push_back(secondArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Add a channel"s, "nImOaddChannel node1 true"s, 2024,
                                     nImO::kCopyrightName, optionValues, nullptr,
                                     nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>(progName, "addChannel"s, optionValues._logging)};
            nImO::Connection    registryConnection{};

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                auto    proxy{nImO::RegistryProxy::create(ourContext, registryConnection)};
                auto    nodeName{firstArg->getCurrentValue()};
                bool    forOutput{secondArg->getCurrentValue()};
                auto    statusWithInfo{proxy->getNodeInformation(nodeName)};

                if (statusWithInfo.first.first)
                {
                    if (statusWithInfo.second._found)
                    {
                        int64_t existingChannelCount{0};

                        if (forOutput)
                        {
                            auto    statusWithInt{proxy->getNumberOfOutputChannelsOnNode(nodeName)};

                            if (statusWithInt.first.first)
                            {
                                existingChannelCount = statusWithInt.second;
                            }
                            else
                            {
                                std::cerr << "Problem with 'getNumberOfOutputChannelsOnNode': " << statusWithInt.first.second << ".\n";
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            auto    statusWithInt{proxy->getNumberOfInputChannelsOnNode(nodeName)};

                            if (statusWithInt.first.first)
                            {
                                existingChannelCount = statusWithInt.second;
                            }
                            else
                            {
                                std::cerr << "Problem with 'getNumberOfOutputChannelsOnNode': " << statusWithInt.first.second << ".\n";
                                exitCode = 1;
                            }
                        }
                        if (0 == exitCode)
                        {
                            nImO::Connection    nodeConnection{statusWithInfo.second._connection};
                            int64_t             maxInputChannels;
                            int64_t             maxOutputChannels;
                            auto                handler1{std::make_unique<nImO::GetChannelLimitsResponseHandler>()};
                            auto                statusWithLimits{nImO::SendRequestWithNoArgumentsAndNonEmptyResponse(ourContext, nodeConnection,
                                                                                                                     handler1.get(),
                                                                                                                     nImO::kGetChannelLimitsRequest,
                                                                                                                     nImO::kGetChannelLimitsResponse)};

                            if (statusWithLimits.first)
                            {
                                handler1->result(maxInputChannels, maxOutputChannels);
                                if (forOutput)
                                {
                                    if ((nImO::kUnlimitedChannels != maxOutputChannels) && (existingChannelCount >= maxOutputChannels))
                                    {
                                        std::cerr << "No more available output channels on node " << nodeName << ".\n";
                                        exitCode = 1;
                                    }
                                    else
                                    {
                                        auto    handler2{std::make_unique<nImO::AddOutputChannelResponseHandler>()};
                                        auto    status{nImO::SendRequestWithNoArgumentsAndNonEmptyResponse(ourContext, nodeConnection, handler2.get(),
                                                                                                           nImO::kAddOutputChannelRequest,
                                                                                                           nImO::kAddOutputChannelResponse)};

                                        if (! status.first)
                                        {
                                            std::cerr << "Problem with 'addOutputChannel': " << status.second << ".\n";
                                            exitCode = 1;
                                        }
                                    }
                                }
                                else
                                {
                                    if ((nImO::kUnlimitedChannels != maxInputChannels) && (existingChannelCount >= maxInputChannels))
                                    {
                                        std::cerr << "No more available input channels on node " << nodeName << ".\n";
                                        exitCode = 1;
                                    }
                                    else
                                    {
                                        auto    handler3{std::make_unique<nImO::AddInputChannelResponseHandler>()};
                                        auto    status{nImO::SendRequestWithNoArgumentsAndNonEmptyResponse(ourContext, nodeConnection, handler3.get(),
                                                                                                           nImO::kAddInputChannelRequest,
                                                                                                           nImO::kAddInputChannelResponse)};

                                        if (! status.first)
                                        {
                                            std::cerr << "Problem with 'addInputChannel': " << status.second << ".\n";
                                            exitCode = 1;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                std::cerr << "Problem with 'getChannelLimits': " << statusWithLimits.second << ".\n";
                                exitCode = 1;
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "Unknown node " << nodeName << ".\n";
                        exitCode = 1;
                    }
                }
                else
                {
                    std::cerr << "Problem with 'getNodeInformation': " << statusWithInfo.first.second << ".\n";
                    exitCode = 1;
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

//--------------------------------------------------------------------------------------------------
//
//  File:       nImOchartMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to display information about nImO.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2025 by OpenDragon.
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
//  Created:    2025-05-23
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <Contexts/nImOsinkContext.h>
#include <nImOaddInputChannelCallbackHandler.h>
#include <nImOchannelName.h>
#include <nImOinputOutputCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOserviceOptions.h>
#include <nImOsinkBreakHandler.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility service to chart SIGNAL messages. */

/*! @dir Chart
 @brief The set of files that implement the Chart application. */
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

/*! @brief The entry point for charting SIGNAL messages.

 Standard output will receive a list of the connections to the channel.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             thisService{"Chart"s};
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::IntegerArgumentDescriptor>("numIn"s, "Number of input channels"s,
                                                                                       nImO::ArgumentMode::Optional, 1, true, 1, false, 0)};
    nImO::DescriptorVector  argumentList{};
    nImO::ServiceOptions    optionValues{};
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(firstArg);
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Chart values from the input SIGNAL channels"s, "nImOchart 2"s, 2025, nImO::kCopyrightName,
                                    optionValues, nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipInTypeOption |
                                    nImO::kSkipPortOption | nImO::kSkipRemoteOption, true))
    {
        try
        {
            nImO::CheckArgumentDescriptions(argumentList);
            nImO::LoadConfiguration(optionValues._configFilePath);
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, optionValues._randomNodeName, thisService, optionValues._tag)};
            auto                basePath{optionValues._base};
            auto                ourContext{std::make_shared<nImO::SinkContext>(argc, argv, thisService, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new nImO::SinkBreakHandler{ourContext.get()}};
            auto                addInputChannelCallback{new nImO::AddInputChannelCallbackHandler{ourContext.get(), basePath}};

            if (! basePath.empty())
            {
                if ('/' != basePath[0])
                {
                    basePath = "/"s + basePath;
                }
            }
            nImO::SetSpecialBreakObject(cleanup);
            ourContext->setChannelLimits(nImO::kUnlimitedChannels, 0);
            if (optionValues._autolaunch)
            {
                ourContext->findAndLaunchTheRegistry();
            }
            nImO::AddInputOutputHandlers(ourContext, argumentList, cleanup, addInputChannelCallback);
            if (ourContext->findTheRegistry(registryConnection))
            {
                auto    proxy{nImO::RegistryProxy::create(ourContext, registryConnection)};
                auto    statusWithBool{proxy->isNodePresent(nodeName)};

                if (statusWithBool.first.first)
                {
                    if (statusWithBool.second)
                    {
                        ourContext->report(nodeName + " already running."s);
                        std::cerr << nodeName << " already running.\n";
                        exitCode = 1;
                    }
                    else
                    {
                        statusWithBool = proxy->addNode(nodeName, argc, argv, nImO::ServiceType::FilterService,
                                                        ourContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                for (int ii{1}, mm{firstArg->getCurrentValue()}; (ii <= mm) && (0 == exitCode); ++ii)
                                {
                                    std::string scratch;

                                    // Using one greater than the requested number of channels will ensure that all the
                                    // channel paths will have a number at the end.
                                    if (nImO::ChannelName::generatePath(basePath, nImO::ChannelName::ChannelType::Input, mm + 1, ii, scratch))
                                    {
                                        statusWithBool = proxy->addChannel(nodeName, scratch, false, nImO::kSignalType,
                                                                           nImO::TransportType::kAny);
                                        if (statusWithBool.first.first)
                                        {
                                            if (statusWithBool.second)
                                            {
                                                ourContext->addInputChannel(scratch);
                                            }
                                            else
                                            {
                                                ourContext->report(scratch + " already registered."s);
                                                std::cerr << scratch << " already registered.\n";
                                                exitCode = 1;
                                            }
                                        }
                                        else
                                        {
                                            std::cerr << "Problem with 'addChannel': " << statusWithBool.first.second << ".\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Invalid channel path '" << basePath << "'.\n";
                                        exitCode = 1;
                                    }
                                }
                                if (0 == exitCode)
                                {
                                    addInputChannelCallback->enable(nodeName, proxy, optionValues._inType);
                                    if (optionValues._waitForConnections)
                                    {
                                        bool    connected{false};

                                        std::cout << "waiting for connection(s).\n";
                                        ourContext->report("waiting for connection(s)."s);
                                        for ( ; nImO::gKeepRunning && (! connected); )
                                        {
                                            boost::this_thread::yield();
                                            connected = ourContext->anInputChannelIsConnected();
                                        }
                                    }
                                    if (nImO::gKeepRunning)
                                    {
                                        ourContext->report("waiting for messages."s);
                                        std::cout << progName << " ready.\n";
                                        std::cout.flush();
                                    }
                                    for ( ; nImO::gKeepRunning && (0 == exitCode); )
                                    {
                                        boost::this_thread::yield();
                                        auto    nextData{ourContext->getNextMessage()};

                                        if (nImO::gKeepRunning)
                                        {
                                            if (nextData)
                                            {
                                                auto    contents{nextData->_receivedMessage};

                                                if (contents)
                                                {
//                                                    if (! outChannel->send(contents))
//                                                    {
//                                                        ourContext->report("problem sending to '"s + outChannelPath + "'."s);
//                                                        std::cerr << "problem sending to " << outChannelPath << "\n";
//                                                        exitCode = 1;
//                                                        break;
//
//                                                    }
                                                }
                                            }
                                        }
                                    }
                                    addInputChannelCallback->disable();
                                    // Wait for the callbacks to finish
                                    for ( ; addInputChannelCallback->isActive() && nImO::gKeepRunning; )
                                    {
                                        boost::this_thread::yield();
                                    }
                                    if (! nImO::gPendingStop)
                                    {
                                        bool                    alreadyReported{false};
                                        nImO::StdStringVector   inChannelPaths;

                                        nImO::gKeepRunning = true; // So that the calls to 'CloseConnection' and 'getInputChannelNames' won't fail...
                                        ourContext->getInputChannelNames(inChannelPaths);
                                        for (auto & walker : inChannelPaths)
                                        {
                                            nImO::CloseConnection(ourContext, nodeName, proxy, walker, false, alreadyReported);
                                        }
                                    }
                                    std::cout << progName << " done.\n";
                                    std::cout.flush();
                                }
                                nImO::StdStringVector   inChannelPaths;

                                ourContext->getInputChannelNames(inChannelPaths);
                                for (auto & walker : inChannelPaths)
                                {
                                    statusWithBool = proxy->removeChannel(nodeName, walker);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(walker + " already unregistered."s);
                                            std::cerr << walker << " already unregistered.\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Problem with 'removeChannel': " << statusWithBool.first.second << ".\n";
                                        exitCode = 1;
                                    }
                                }
                                if (! nImO::gPendingStop)
                                {
                                    nImO::gKeepRunning = true; // So that the call to 'removeNode' won't fail...
                                    statusWithBool = proxy->removeNode(nodeName);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(nodeName + " already unregistered."s);
                                            std::cerr << nodeName << " already unregistered.\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << ".\n";
                                        exitCode = 1;
                                    }
                                }
                            }
                            else
                            {
                                ourContext->report(nodeName + " already registered."s);
                                std::cerr << nodeName << " already registered.\n";
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'addNode': " << statusWithBool.first.second << ".\n";
                            exitCode = 1;
                        }
                    }
                }
                else
                {
                    std::cerr << "Problem with 'isNodePresent': " << statusWithBool.first.second << ".\n";
                    exitCode = 1;
                }
            }
            else
            {
                ourContext->report("Registry not found."s);
                exitCode = 2;
            }
            ourContext->report("exiting."s);
        }
        catch (const std::string &  fault)
        {
            std::cerr << "Exception: " << fault << "\n";
            exitCode = -1;
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

//--------------------------------------------------------------------------------------------------
//
//  File:       nImOwriteMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to write to a nImO channel.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-02-19
//
//--------------------------------------------------------------------------------------------------

#include <Containers/nImOstringBuffer.h>
#include <Contexts/nImOsourceContext.h>
#include <nImOcallbackFunction.h>
#include <nImOchannelName.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOserviceOptions.h>
#include <nImOsourceBreakHandler.h>

#include <chrono>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to write to a #nImO channel. */

/*! @dir Write
 @brief The set of files that implement the Write application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace std::chrono_literals;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief Used to protect the received text. */
std::mutex  lReceivedLock{};

/*! @brief Used to indicate that there is some received text. */
std::condition_variable lReceivedCondition{};

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Handle console input.
 @param[out] outLine where to place the received text. */
static void
gatherLines
    (std::string &  outLine)
{
    std::string inLine{};

    for ( ; nImO::gKeepRunning; )
    {
        boost::this_thread::yield();
        if (getline(std::cin, inLine))
        {
            {
                std::lock_guard<std::mutex>  lock{lReceivedLock};

                outLine = inLine;
            }
            lReceivedCondition.notify_one();
        }
    }
    lReceivedCondition.notify_one();
} // gatherLines

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for writing to a #nImO channel.

 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             thisService{"Write"s};
    std::string             progName{*argv};
    nImO::DescriptorVector  argumentList{};
    nImO::ServiceOptions    optionValues{};
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Write to a channel"s, "nImOwrite"s, 2016, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipInTypeOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, thisService, optionValues._tag)};
            auto                ourContext{std::make_shared<nImO::SourceContext>(argc, argv, thisService, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new nImO::SourceBreakHandler{}};

            nImO::SetSpecialBreakObject(cleanup);
            ourContext->setChannelLimits(0, 1);
            nImO::AddInputOutputHandlers(ourContext, cleanup);
            if (ourContext->findRegistry(registryConnection))
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
                        statusWithBool = proxy->addNode(nodeName, argc, argv, nImO::ServiceType::InputService,
                                                        ourContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                bool        outValid{false};
                                std::string outChannelPath;
                                auto        basePath{optionValues._base};

                                if (! basePath.empty())
                                {
                                    if ('/' != basePath[0])
                                    {
                                        basePath = "/"s + basePath;
                                    }
                                }
                                if (nImO::ChannelName::generatePath(basePath, true, 1, 1, outChannelPath))
                                {
                                    statusWithBool = proxy->addChannel(nodeName, outChannelPath, true, optionValues._outType,
                                                                       nImO::TransportType::kAny);
                                    if (statusWithBool.first.first)
                                    {
                                        if (statusWithBool.second)
                                        {
                                            ourContext->addOutputChannel(outChannelPath);
                                            outValid = true;
                                        }
                                        else
                                        {
                                            ourContext->report(outChannelPath + " already registered."s);
                                            std::cerr << outChannelPath << " already registered.\n";
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
                                if (0 == exitCode)
                                {
                                    auto    outChannel{ourContext->getOutputChannel(outChannelPath)};

                                    if (outChannel)
                                    {
                                        if (optionValues._waitForConnections)
                                        {
                                            bool    connected{false};

                                            std::cout << "waiting for connection(s).\n";
                                            ourContext->report("waiting for connection(s)."s);
                                            for ( ; nImO::gKeepRunning && (! connected); )
                                            {
                                                boost::this_thread::yield();
                                                connected = outChannel->isConnected();
                                            }
                                        }
                                        ourContext->report("waiting for input."s);
                                        nImO::StringBuffer  inBuffer;
                                        std::string         inLine;
                                        auto                aThread{new boost::thread([&inLine]
                                                                                        (void)
                                                                                        {
                                                                                            gatherLines(inLine);
                                                                                        })};

                                        ODL_P1(aThread); //####
                                        aThread->detach();
                                        std::cout << "ready.\n";
                                        std::cout.flush();
                                        for ( ; nImO::gKeepRunning; )
                                        {
                                            {
                                                // Check for text.
                                                std::unique_lock<std::mutex>    lock{lReceivedLock};

                                                for ( ; nImO::gKeepRunning && inLine.empty(); )
                                                {
                                                    boost::this_thread::yield();
                                                    lReceivedCondition.wait_for(lock, 10ms,
                                                                                  []
                                                                                  (void)
                                                                                  {
                                                                                    return (! nImO::gKeepRunning);
                                                                                  });
                                                }
                                            }
                                            if (nImO::gKeepRunning)
                                            {
                                                inBuffer.addString("\n" + inLine);
                                                inLine.clear();
                                                auto    readValue{inBuffer.convertToValue()};

                                                if (readValue)
                                                {
                                                    inBuffer.reset();
                                                    if (nImO::gKeepRunning)
                                                    {
                                                        if (! outChannel->send(readValue))
                                                        {
                                                            ourContext->report("problem sending to '"s + outChannelPath + "'."s);
                                                            std::cerr << "problem sending to " << outChannelPath << "\n";
                                                            exitCode = 1;
                                                            break;

                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if (! nImO::gPendingStop)
                                        {
                                            bool    alreadyReported{false};

                                            nImO::gKeepRunning = true; // So that the call to 'removeConnection' won't fail...
                                            nImO::CloseConnection(ourContext, nodeName, proxy, outChannelPath, true, alreadyReported);
                                        }
                                        std::cout << "done.\n";
                                        std::cout.flush();
                                    }
                                }
                                if (outValid)
                                {
                                    nImO::gKeepRunning = true; // So that the call to 'removeChannel' won't fail...
                                    statusWithBool = proxy->removeChannel(nodeName, outChannelPath);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(outChannelPath + " already unregistered."s);
                                            std::cerr << outChannelPath << " already unregistered.\n";
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
        catch (...)
        {
            ODL_LOG("Exception caught"); //####
            exitCode = -1;
        }
    }
    ODL_EXIT_I(exitCode); //####
    return exitCode;
} // main

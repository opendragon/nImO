//--------------------------------------------------------------------------------------------------
//
//  File:       nImOrepeatMain.cpp
//
//  Project:    nImO
//
//  Contains:   A wiring application to demonstrate using the nImO library in a program.
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
//  Created:    2024-11-04
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOdoubleArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <Contexts/nImOfilterContext.h>
#include <nImOchannelName.h>
#include <nImOfilterBreakHandler.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOserviceOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A wiring application to demonstrate using the nImO library in a program. */

/*! @dir Repeat
 @brief The set of files that implement the Repeat application. */
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

/*! @brief The entry point for the wiring application.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::IntegerArgumentDescriptor>("repeats"s, "Number of copies of the input message"s,
                                                                                       nImO::ArgumentMode::Optional | nImO::ArgumentMode::Mutable, 1, true, 1, false, 0)};
    auto                    secondArg{std::make_shared<nImO::DoubleArgumentDescriptor>("delay"s, "Number of seconds between duplicated messages"s,
                                                                                      nImO::ArgumentMode::Optional | nImO::ArgumentMode::Mutable, 1.0, true, 0.0, false, 0.0)};
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
    argumentList.push_back(secondArg);
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Send copies of a message to a channel after a delay"s, "nImOrepeat 2 3.5"s, 2024, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption))
    {
        try
        {
            nImO::CheckArgumentDescriptions(argumentList);
            nImO::LoadConfiguration(optionValues._configFilePath);
            nImO::SetSignalHandlers(nImO::CatchSignal);
            std::string         thisService{"Repeat"s};
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, optionValues._randomNodeName, thisService, optionValues._tag,
                                                                 ! optionValues._suppressStandardSuffix)};
            auto                ourContext{std::make_shared<nImO::FilterContext>(argc, argv, thisService, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new nImO::FilterBreakHandler{ourContext.get()}};
            auto                longName{progName + " ["s + nodeName + "]"s};

            nImO::SetSpecialBreakObject(cleanup);
            ourContext->setChannelLimits(1, 1);
            if (optionValues._autolaunch)
            {
                ourContext->findAndLaunchTheRegistry();
            }
            nImO::AddInputOutputHandlers(ourContext, argumentList, cleanup);
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
                                bool        inValid{false};
                                bool        outValid{false};
                                std::string inChannelPath;
                                std::string outChannelPath;
                                auto        basePath{optionValues._base};

                                if (! basePath.empty())
                                {
                                    if ('/' != basePath[0])
                                    {
                                        basePath = "/"s + basePath;
                                    }
                                }
                                if (nImO::ChannelName::generatePath(basePath, nImO::ChannelName::ChannelType::Output, 1, 1, outChannelPath))
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
                                    if (nImO::ChannelName::generatePath(basePath, nImO::ChannelName::ChannelType::Input, 1, 1, inChannelPath))
                                    {
                                        statusWithBool = proxy->addChannel(nodeName, inChannelPath, false, optionValues._inType,
                                                                           nImO::TransportType::kAny);
                                        if (statusWithBool.first.first)
                                        {
                                            if (statusWithBool.second)
                                            {
                                                ourContext->addInputChannel(inChannelPath);
                                                inValid = true;
                                            }
                                            else
                                            {
                                                ourContext->report(inChannelPath + " already registered."s);
                                                std::cerr << inChannelPath << " already registered.\n";
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
                                    auto    outChannel{ourContext->getOutputChannel(outChannelPath)};

                                    if (outChannel)
                                    {
                                        if (optionValues._waitForConnections)
                                        {
                                            auto    inChannel{ourContext->getInputChannel(inChannelPath)};
                                            bool    connected{false};

                                            std::cout << "Waiting for connection(s).\n";
                                            ourContext->report("Waiting for connection(s)."s);
                                            for ( ; nImO::gKeepRunning && (! connected); )
                                            {
                                                boost::this_thread::yield();
                                                connected = (inChannel->isConnected() && outChannel->isConnected());
                                            }
                                        }
                                        if (nImO::gKeepRunning)
                                        {
                                            ourContext->report("Waiting for messages."s);
                                            std::cout << longName << " ready.\n";
                                            std::cout.flush();
                                        }
                                        std::set<nImO::SpDeadlineTimer> timers{};

                                        for ( ; nImO::gKeepRunning; )
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
                                                        int64_t numCopies{firstArg->getCurrentValue()};
                                                        auto    numMilliseconds{StaticCast(int, 1000.0 * secondArg->getCurrentValue())};
                                                        auto    delayTime{boost::posix_time::milliseconds(numMilliseconds)};

                                                        for (int64_t ii{0}; ii < numCopies; ++ii)
                                                        {
                                                            auto    aTimer{std::make_shared<BAD_t>(*ourContext->getService())};

                                                            timers.insert(aTimer);
                                                            aTimer->expires_from_now(delayTime * (ii + 1));
                                                            aTimer->async_wait([&outChannel, &ourContext, contents, outChannelPath, aTimer]
                                                                               (const BSErr & error)
                                                                               {
                                                                                    if ((! error) && nImO::gKeepRunning)
                                                                                    {
                                                                                        if (! outChannel->send(contents))
                                                                                        {
                                                                                            ourContext->report("Problem sending to '"s + outChannelPath +
                                                                                                               "'."s);
                                                                                        }
                                                                                    }
                                                                                });
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        for (auto & walker : timers)
                                        {
                                            walker->cancel();
                                        }
                                        if (! nImO::gPendingStop)
                                        {
                                            bool    alreadyReported{false};

                                            nImO::gKeepRunning = true; // So that the calls to 'removeConnection' won't fail...
                                            nImO::CloseConnection(ourContext, nodeName, proxy, outChannelPath, true, alreadyReported);
                                            nImO::CloseConnection(ourContext, nodeName, proxy, inChannelPath, false, alreadyReported);
                                        }
                                        std::cout << longName << " done.\n";
                                        std::cout.flush();
                                    }
                                }
                                if (inValid)
                                {
                                    nImO::gKeepRunning = true; // So that the call to 'removeChannel' won't fail...
                                    statusWithBool = proxy->removeChannel(nodeName, inChannelPath);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(inChannelPath + " already unregistered."s);
                                            std::cerr << inChannelPath << " already unregistered.\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Problem with 'removeChannel': " << statusWithBool.first.second << ".\n";
                                        exitCode = 1;
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
            ourContext->report("Exiting."s);
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

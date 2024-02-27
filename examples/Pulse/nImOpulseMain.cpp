//--------------------------------------------------------------------------------------------------
//
//  File:       nImOpulseMain.cpp
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
//  Created:    2024-02-20
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOdoubleArgumentDescriptor.h>
#include <Contexts/nImOsourceContext.h>
#include <nImOchannelName.h>
#include <nImOfilterBreakHandler.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOserviceOptions.h>
#include <nImOsourceBreakHandler.h>
#include <nImOstandardChannels.h>

//#include <boost/date_time/posix_time/posix_time.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A wiring application to demonstrate using the nImO library in a program. */

/*! @dir Passthrough
 @brief The set of files that implement the Delay application. */
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
    constexpr double        tinyValue{1e-6};
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::DoubleArgumentDescriptor>("duration"s, "Number of seconds for full cycle"s,
                                                                                      nImO::ArgumentMode::Optional, 1.0, true, tinyValue, false, 0.0)};
    auto                    secondArg{std::make_shared<nImO::DoubleArgumentDescriptor>("dutyCycle"s, "Fraction of 'on' time"s,
                                                                                       nImO::ArgumentMode::Optional, 0.5, true, tinyValue, true,
                                                                                       1.0 - tinyValue)};
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
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Pulse"s, 2023, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipInTypeOption |
                                    nImO::kSkipOutTypeOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, "pulse"s, optionValues._tag)};
            auto                ourContext{std::make_shared<nImO::SourceContext>(argc, argv, progName, "Pulse"s, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new nImO::SourceBreakHandler{}};

            nImO::SetSpecialBreakObject(cleanup);
            ourContext->setChannelLimits(0, 1);
            nImO::AddInputOutputHandlers(ourContext, cleanup);
            if (ourContext->findRegistry(registryConnection))
            {
                nImO::RegistryProxy proxy{ourContext, registryConnection};
                auto                statusWithBool{proxy.isNodePresent(nodeName)};

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
                        statusWithBool = proxy.addNode(nodeName, argc, argv, nImO::ServiceType::FilterService,
                                                       ourContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                bool        outValid{false};
                                std::string outChannelPath;
                                auto        basePath{optionValues._base};

                                if (nImO::ChannelName::generatePath(basePath, true, 1, 1, outChannelPath))
                                {
                                    // Note the fixed data type and the restriction to TCP.
                                    statusWithBool = proxy.addChannel(nodeName, outChannelPath, true, nImO::kLogicDataType,
                                                                      nImO::TransportType::kTCP);
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

                                            ourContext->report("waiting for connection(s)."s);
                                            for ( ; nImO::gKeepRunning && (! connected); )
                                            {
                                                boost::this_thread::yield();
                                                connected = outChannel->isConnected();
                                            }
                                        }
#if 0
                                        //TBD!!
                                        auto    delayTime{boost::posix_time::milliseconds(StaticCast(int, 1000.0 * firstArg->getCurrentValue()))};

                                        std::set<nImO::SpDeadlineTimer> timers{};

                                        for ( ; nImO::gKeepRunning; )
                                        {
                                            boost::this_thread::yield();
                                            if (nImO::gKeepRunning)
                                            {
//                                                auto    contents{nextData->_receivedMessage};

//                                                if (contents)
                                                {
                                                    //TBD!!!
                                                    auto    aTimer{std::make_shared<BAD_t>(*ourContext->getService())};

                                                    timers.insert(aTimer);
                                                    aTimer->expires_from_now(delayTime);
//                                                    aTimer->async_wait([&outChannel, &ourContext, contents, outChannelPath, aTimer]
//                                                                       (const BSErr & error)
//                                                                       {
//                                                                            if ((! error) && nImO::gKeepRunning)
//                                                                            {
//                                                                                if (! outChannel->send(contents))
//                                                                                {
//                                                                                    ourContext->report("problem sending to '"s + outChannelPath +
//                                                                                                       "'."s);
//                                                                                }
//                                                                            }
//                                                                        });
                                                }
                                            }
                                        }
                                        for (auto & walker : timers)
                                        {
                                            walker->cancel();
                                        }
#endif//0
                                        if (! nImO::gPendingStop)
                                        {
                                            bool    alreadyReported{false};

                                            nImO::gKeepRunning = true; // So that the calls to 'removeConnection' won't fail...
                                            nImO::CloseConnection(ourContext, nodeName, proxy, outChannelPath, true, alreadyReported);
                                        }
                                        std::cerr << "done.\n";
                                    }
                                }
                                if (outValid)
                                {
                                    nImO::gKeepRunning = true; // So that the call to 'removeChannel' won't fail...
                                    statusWithBool = proxy.removeChannel(nodeName, outChannelPath);
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
                                    statusWithBool = proxy.removeNode(nodeName);
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

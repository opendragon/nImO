//--------------------------------------------------------------------------------------------------
//
//  File:       nImOfanInMain.cpp
//
//  Project:    nImO
//
//  Contains:   An example application to demonstrate using the nImO library in a program.
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
//  Created:    2023-01-28
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <Contexts/nImOfilterContext.h>
#include <nImOchannelName.h>
#include <nImOcommonCommands.h>
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
 @brief An example application to demonstrate using the nImO library in a program. */

/*! @dir FanIn
 @brief The set of files that implement the FanIn application. */
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

/*! @brief The entry point for the example application.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string                     progName{*argv};
    nImO::IntegerArgumentDescriptor firstArg{"numIn"s, "Number of input channels"s, nImO::ArgumentMode::Optional, 1, true, 1, false, 0};
    nImO::DescriptorVector          argumentList;
    nImO::ServiceOptions            optionValues;
    int                             exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(&firstArg);
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "FanIn example"s, ""s, 2023, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption, true))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, "fanin"s, optionValues._tag)};
            auto                ourContext{std::make_shared<nImO::FilterContext>(argc, argv, progName, "FanIn"s,
                                                                                 optionValues._logging, nodeName)};
            nImO::Connection    registryConnection;
            auto                asServiceContext{ourContext->asServiceContext()};

            nImO::InputOutputContext::addInputOutputHandlers(ourContext);
            if (asServiceContext->findRegistry(registryConnection))
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
                                                       asServiceContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                auto        basePath{optionValues._base};
                                std::string outChannelPath;
                                bool        outValid{false};

                                if (nImO::ChannelName::generatePath(basePath, true, 1, 1, outChannelPath))
                                {
                                    statusWithBool = proxy.addChannel(nodeName, outChannelPath, true, optionValues._outType,
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
                                        std::cerr << "Problem with 'addChannel': " << statusWithBool.first.second << "\n";
                                        exitCode = 1;
                                    }
                                }
                                else
                                {
                                    std::cerr << "Invalid channel path " << "'" << basePath << "'\n";
                                    exitCode = 1;
                                }
                                for (int ii = 1, mm = firstArg.getCurrentValue(); (ii <= mm) && (0 == exitCode); ++ii)
                                {
                                    std::string scratch;

                                    // Using one greater than the requested number of channels will ensure that all the
                                    // channel paths will have a number at the end.
                                    if (nImO::ChannelName::generatePath(basePath, false, mm + 1, ii, scratch))
                                    {
                                        statusWithBool = proxy.addChannel(nodeName, scratch, false, optionValues._inType,
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
                                            std::cerr << "Problem with 'addChannel': " << statusWithBool.first.second << "\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Invalid channel path " << "'" << basePath << "'\n";
                                        exitCode = 1;
                                    }
                                }
                                if (0 == exitCode)
                                {
std::cerr << "** Unimplemented **\n";
                                    ourContext->report("waiting for requests."s);
                                    for ( ; nImO::gKeepRunning; )
                                    {
                                        boost::this_thread::yield();
                                        auto    nextData{ourContext->getNextMessage()};

                                        if (nImO::gKeepRunning)
                                        {
                                            if (nextData)
                                            {
                                                auto                contents{nextData->_receivedMessage};
//                                                nImO::StringBuffer  buff;
//
//                                                contents->printToStringBuffer(buff);
//                                                auto    valString{buff.getString()};
//
//                                                std::cout << valString << "\n";
//TBD!!
                                            }
                                        }
                                    }
                                }
                                if (! nImO::gPendingStop)
                                {
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
                                            std::cerr << "Problem with 'removeChannel': " << statusWithBool.first.second << "\n";
                                            exitCode = 1;
                                        }
                                    }
                                    nImO::StringVector  inChannelPaths;

                                    ourContext->getInputChannelNames(inChannelPaths);
                                    for (auto walker{inChannelPaths.begin()}; walker != inChannelPaths.end(); ++walker)
                                    {
                                        std::string chanName{*walker};

                                        nImO::gKeepRunning = true; // So that the call to 'removeChannel' won't fail...
                                        statusWithBool = proxy.removeChannel(nodeName, chanName);
                                        if (statusWithBool.first.first)
                                        {
                                            if (! statusWithBool.second)
                                            {
                                                ourContext->report(chanName + " already unregistered."s);
                                                std::cerr << chanName << " already unregistered.\n";
                                                exitCode = 1;
                                            }
                                        }
                                        else
                                        {
                                            std::cerr << "Problem with 'removeChannel': " << statusWithBool.first.second << "\n";
                                            exitCode = 1;
                                        }
                                    }
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
                                        std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << "\n";
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
                            std::cerr << "Problem with 'addNode': " << statusWithBool.first.second << "\n";
                            exitCode = 1;
                        }
                    }
                }
                else
                {
                    std::cerr << "Problem with 'isNodePresent': " << statusWithBool.first.second << "\n";
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
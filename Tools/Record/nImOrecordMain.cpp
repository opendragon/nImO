//--------------------------------------------------------------------------------------------------
//
//  File:       nImOrecordMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to record from a nImO channel to a file.
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
//  Created:    2024-10-17
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <Containers/nImOstringBuffer.h>
#include <Contexts/nImOsinkContext.h>
#include <nImOchannelName.h>
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
 @brief A utility application to record from a #nImO channel to a file. */

/*! @dir Record
 @brief The set of files that implement the Record application. */
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

/*! @brief The entry point for recording from a #nImO channel to a file.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             thisService{"Record"s};
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::FilePathArgumentDescriptor>("output"s, "File to write to"s,
                                                                                        nImO::ArgumentMode::Required, ""s, ""s, true)};
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
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Record to a file from a channel"s, "nImOrecord recording.txt"s, 2024, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipOutTypeOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, thisService, optionValues._tag)};
            auto                ourContext{std::make_shared<nImO::SinkContext>(argc, argv, thisService, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new nImO::SinkBreakHandler{ourContext.get()}};

            nImO::SetSpecialBreakObject(cleanup);
            ourContext->setChannelLimits(1, 0);
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
                        statusWithBool = proxy->addNode(nodeName, argc, argv, nImO::ServiceType::OutputService,
                                                        ourContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                bool        inValid{false};
                                std::string inChannelPath;
                                auto        basePath{optionValues._base};

                                if (! basePath.empty())
                                {
                                    if ('/' != basePath[0])
                                    {
                                        basePath = "/"s + basePath;
                                    }
                                }
                                if (nImO::ChannelName::generatePath(basePath, false, 1, 1, inChannelPath))
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
                                if (0 == exitCode)
                                {
                                    std::string     workingPath{firstArg->getCurrentValue()};
                                    std::ofstream   outStream{workingPath};

                                    if (outStream)
                                    {
                                        if (optionValues._waitForConnections)
                                        {
                                            auto    inChannel{ourContext->getInputChannel(inChannelPath)};
                                            bool    connected{false};

                                            std::cout << "waiting for connection(s).\n";
                                            ourContext->report("waiting for connection(s)."s);
                                            for ( ; nImO::gKeepRunning && (! connected); )
                                            {
                                                boost::this_thread::yield();
                                                connected = inChannel->isConnected();
                                            }
                                        }
                                        if (nImO::gKeepRunning)
                                        {
                                            ourContext->report("waiting for messages."s);
                                            std::cout << "ready.\n";
                                            std::cout.flush();
                                        }
                                        for ( ; nImO::gKeepRunning; )
                                        {
                                            boost::this_thread::yield();
                                            auto    nextData{ourContext->getNextMessage()};

                                            if (nImO::gKeepRunning)
                                            {
                                                if (nextData)
                                                {
                                                    auto                contents{nextData->_receivedMessage};
                                                    nImO::StringBuffer  buff;

                                                    contents->printToStringBuffer(buff);
                                                    auto    valString{buff.getString()};

                                                    outStream << nImO::kCommentChar << "\n" << valString << "\n";
                                                    outStream.flush();
                                                }
                                            }
                                        }
                                        if (! nImO::gPendingStop)
                                        {
                                            bool    alreadyReported{false};

                                            nImO::gKeepRunning = true; // So that the call to 'removeConnection' won't fail...
                                            nImO::CloseConnection(ourContext, nodeName, proxy, inChannelPath, false, alreadyReported);
                                        }
                                        std::cout << "done.\n";
                                        std::cout.flush();
                                    }
                                    else
                                    {
                                        std::cerr << "Warning: output file could not be written.\n";
                                        exitCode = 1;
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

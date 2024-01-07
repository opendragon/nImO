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

#include <ArgumentDescriptors/nImOchannelArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <Containers/nImOstringBuffer.h>
#include <Contexts/nImOsourceContext.h>
#include <nImOchannelName.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOserviceOptions.h>

#include <ncurses.h>

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

/*! @brief The entry point for writing to a #nImO channel.

 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    nImO::DescriptorVector  argumentList;
    nImO::ServiceOptions    optionValues;
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Write to a channel"s, ""s, 2016, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipInTypeOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            std::string         nodeName{nImO::ConstructNodeName(optionValues._node, "write"s, optionValues._tag)};
            auto                ourContext{std::make_shared<nImO::SourceContext>(argc, argv, progName, "write"s, optionValues._logging, nodeName)};
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
                        statusWithBool = proxy.addNode(nodeName, argc, argv, nImO::ServiceType::InputService,
                                                       asServiceContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                bool        outValid = false;
                                std::string outChannelPath;
                                std::string basePath{optionValues._base};

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
                                if (0 == exitCode)
                                {
                                    auto    outChannel{ourContext->getOutputChannel(outChannelPath)};

                                    if (outChannel)
                                    {
                                        ourContext->report("waiting for input."s);
                                        for ( ; nImO::gKeepRunning; )
                                        {
                                            boost::this_thread::yield();
                                            nImO::StringBuffer  inBuffer;
                                            std::string         inLine;
                                            nImO::SpValue       readValue;

                                            for ( ; getline(std::cin, inLine); )
                                            {
                                                inBuffer.addString("\n" + inLine);
                                                readValue = inBuffer.convertToValue();
                                                if (readValue)
                                                {
                                                    break;

                                                }
                                            }
                                            if (nImO::gKeepRunning)
                                            {
                                                if (! outChannel->send(readValue))
                                                {
                                                    ourContext->report("problem sending to "s + outChannelPath);
                                                    std::cerr << "problem sending to " << outChannelPath << "\n";
                                                    exitCode = 1;
                                                    break;

                                                }
                                            }
                                        }
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

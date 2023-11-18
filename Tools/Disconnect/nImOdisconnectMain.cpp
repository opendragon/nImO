//--------------------------------------------------------------------------------------------------
//
//  File:       nImOdisconnectMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to disconnect two nImO channels.
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
#include <Contexts/nImOutilityContext.h>
#include <nImOchannelName.h>
#include <nImOinputOutputCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
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
 @brief A utility application to disconnect two #nImO channels. */

/*! @dir Disconnect
 @brief The set of files that implement the Disconnect application. */
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

/*! @brief The entry point for disconnecting two #nImO channels.

 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string                     progName{*argv};
    nImO::ChannelArgumentDescriptor firstArg{"from/to", "'Sending'or 'Receiving' channel", nImO::ArgumentMode::Required, "/out"};
    nImO::DescriptorVector          argumentList;
    nImO::StandardOptions           optionValues;
    int                             exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(&firstArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Disconnect two channels"s, ""s, 2016, nImO::kCopyrightName, optionValues, nullptr,
                                     nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>(progName, "disconnect"s, optionValues._logging)};
            nImO::Connection    registryConnection;

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                nImO::RegistryProxy proxy{ourContext, registryConnection};
                auto                channel{firstArg.getCurrentValue()};
                std::string         nodeName{channel->getNode()};
                std::string         path{channel->getPath()};
                std::string         fromNode;
                std::string         fromPath;
                std::string         toNode;
                std::string         toPath;
                auto                statusWithInfo{proxy.getConnectionInformation(nodeName, path, false)};

                if (statusWithInfo.first.first)
                {
                    nImO::ConnectionInfo &  connection1{statusWithInfo.second};

                    if (connection1._found)
                    {
                        fromNode = connection1._fromNode;
                        fromPath = connection1._fromPath;
                        toNode = connection1._toNode;
                        toPath = connection1._toPath;
                        auto    statusWithBool{proxy.removeConnection(nodeName, path, false)};

                        if (statusWithBool.first.first)
                        {
                            if (! statusWithBool.second)
                            {
                                ourContext->report("channel '"s + nodeName + " "s + path + "' could not be disconnected."s);
                                std::cerr << "channel '" << nodeName << " " << path << "' could not be disconnected.\n";
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'removeConnection': " << statusWithBool.first.second << "\n";
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        statusWithInfo = proxy.getConnectionInformation(nodeName, path, true);
                        if (statusWithInfo.first.first)
                        {
                            nImO::ConnectionInfo &  connection2{statusWithInfo.second};

                            if (connection2._found)
                            {
                                fromNode = connection2._fromNode;
                                fromPath = connection2._fromPath;
                                toNode = connection2._toNode;
                                toPath = connection2._toPath;
                                auto    statusWithBool{proxy.removeConnection(nodeName, path, true)};

                                if (statusWithBool.first.first)
                                {
                                    if (! statusWithBool.second)
                                    {
                                        ourContext->report("channel '"s + nodeName + " "s + path + "' could not be disconnected."s);
                                        std::cerr << "channel '" << nodeName << " " << path << "' could not be disconnected.\n";
                                        exitCode = 1;
                                    }
                                }
                                else
                                {
                                    std::cerr << "Problem with 'removeConnection': " << statusWithBool.first.second << "\n";
                                    exitCode = 1;
                                }
                            }
                            else
                            {
                                ourContext->report("channel '"s + nodeName + " "s + path + "' could not be found."s);
                                std::cerr << "channel '" << nodeName << " " << path << "' could not be found.\n";
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'getConnectionInformation': " << statusWithInfo.first.second << "\n";
                            exitCode = 1;
                        }
                    }
                }
                else
                {
                    std::cerr << "Problem with 'getConnectionInformation': " << statusWithInfo.first.second << "\n";
                    exitCode = 1;
                }
                if (0 == exitCode)
                {
                    auto    statusWithBool{proxy.clearChannelInUse(fromNode, fromPath)};

                    if (! statusWithBool.first.first)
                    {
                        std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                        exitCode = 1;
                    }
                    statusWithBool = proxy.clearChannelInUse(toNode, toPath);
                    if (! statusWithBool.first.first)
                    {
                        std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    // TBD: Send 'stopSource' command to 'from' node.
                    // TBD: Send 'stopDestination' command to 'to' node.
std::cerr << "** Unimplemented **\n";
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

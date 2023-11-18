//--------------------------------------------------------------------------------------------------
//
//  File:       nImOconnectMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to connect two nImO channels together.
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
#include <ArgumentDescriptors/nImOstringsArgumentDescriptor.h>
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
 @brief A utility application to connect two #nImO channels together. */

/*! @dir Connect
 @brief The set of files that implement the Connect application. */
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

/*! @brief Writes out a description of the 'mode' argument.
 @param[in,out] outStream The stream to write to. */
static void
helpForConnect
    (std::ostream & outStream)
{
    nImO::StringSet modes(nImO::ChannelName::transportNames());

    outStream << "Available modes:\n";
    for (auto & walker : modes)
    {
        outStream << "  " << walker << "\n";
    }
} // helpForConnect

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
    std::string                     progName{*argv};
    nImO::ChannelArgumentDescriptor firstArg{"from", "'Sending' channel", nImO::ArgumentMode::Required, "/out"};
    nImO::ChannelArgumentDescriptor secondArg{"to", "'Receiving' channel", nImO::ArgumentMode::Required, "/in"};
    nImO::StringsArgumentDescriptor thirdArg{"mode", "Transport mode", nImO::ArgumentMode::Optional, "tcp", nImO::ChannelName::transportNames()};
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
    argumentList.push_back(&secondArg);
    argumentList.push_back(&thirdArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Connect two channels"s, ""s, 2016, nImO::kCopyrightName, optionValues, helpForConnect,
                                     nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>(progName, "connect"s, optionValues._logging)};
            nImO::Connection    registryConnection;

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                nImO::RegistryProxy proxy{ourContext, registryConnection};
                auto                fromChannel{firstArg.getCurrentValue()};
                auto                toChannel{secondArg.getCurrentValue()};
                auto                modeRequested{thirdArg.getCurrentValue()};
                std::string         fromNode{fromChannel->getNode()};
                std::string         fromPath{fromChannel->getPath()};
                std::string         toNode{toChannel->getNode()};
                std::string         toPath{toChannel->getPath()};
                std::string         dataType{};
                auto                statusWithBool{proxy.isChannelPresent(fromNode, fromPath)};
                bool                previousStateForFrom{false};
                bool                previousStateForTo{false};
                bool                needToRestoreFromState{false};
                bool                needToRestoreToState{false};

                if (statusWithBool.first.first)
                {
                    if (! statusWithBool.second)
                    {
                        ourContext->report("channel '"s + fromNode + " "s + fromPath + "' not registered."s);
                        std::cerr << "channel '" << fromNode << " " << fromPath << "' not registered.\n";
                        exitCode = 1;
                    }
                }
                else
                {
                    std::cerr << "Problem with 'isChannelPresent': " << statusWithBool.first.second << "\n";
                    exitCode = 1;
                }
                if (0 == exitCode)
                {
                    statusWithBool = proxy.isChannelPresent(toNode, toPath);
                    if (statusWithBool.first.first)
                    {
                        if (! statusWithBool.second)
                        {
                            ourContext->report("channel '"s + toNode + " "s + toPath + "' not registered."s);
                            std::cerr << "channel '" << toNode << " " << toPath << "' not registered.\n";
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'isChannelPresent': " << statusWithBool.first.second << "\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    if (fromNode == toNode)
                    {
                        ourContext->report("node '"s + toNode + "' cannot be connected directly to itself."s);
                        std::cerr << "node '" << toNode << "' cannot be connected directly to itself.\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    // Grab the 'from' channel.
                    statusWithBool = proxy.getChannelInUseAndSet(fromNode, fromPath);
                    if (statusWithBool.first.first)
                    {
                        previousStateForFrom = statusWithBool.second;
                        needToRestoreFromState = true;
                    }
                    else
                    {
                        std::cerr << "Problem with 'getChannelInUseAndSet': " << statusWithBool.first.second << "\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    // Grab the 'to' channel.
                    statusWithBool = proxy.getChannelInUseAndSet(toNode, toPath);
                    if (statusWithBool.first.first)
                    {
                        previousStateForTo = statusWithBool.second;
                        needToRestoreToState = true;
                    }
                    else
                    {
                        std::cerr << "Problem with 'getChannelInUseAndSet': " << statusWithBool.first.second << "\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    // Check if we now have exclusive access to the two channels.
                    if (previousStateForFrom)
                    {
                        ourContext->report("channel '"s + fromNode + " "s + fromPath + "' is already connected."s);
                        std::cerr << "channel '" << fromNode << " " << fromPath << "' is already connected.\n";
                        exitCode = 1;
                    }
                    else if (previousStateForTo)
                    {
                        ourContext->report("channel '"s + toNode + " "s + toPath + "' is already connected."s);
                        std::cerr << "channel '" << toNode << " " << toPath << "' is already connected.\n";
                        exitCode = 1;
                    }
                }
                // We now 'own' the two channels, so we need to resolve if they can be connected.
                bool                fromIsOutput{false};
                bool                toIsOutput{false};
                std::string         fromDataType{};
                std::string         toDataType{};
                nImO::TransportType fromModes{nImO::TransportType::kUnknown};
                nImO::TransportType toModes{nImO::TransportType::kUnknown};
                nImO::TransportType resolvedMode{nImO::ChannelName::transportFromName(modeRequested)};

                if (0 == exitCode)
                {
                    auto    statusWithInfo{proxy.getChannelInformation(fromNode, fromPath)};

                    if (statusWithInfo.first.first)
                    {
                        if (statusWithInfo.second._found)
                        {
                            fromIsOutput = statusWithInfo.second._isOutput;
                            fromDataType = statusWithInfo.second._dataType;
                            fromModes = statusWithInfo.second._modes;
                        }
                        else
                        {
                            ourContext->report("channel '"s + fromNode + " "s + fromPath + "' was not found."s);
                            std::cerr << "channel '" << fromNode << " " << fromPath << "' was not found.\n";
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getChannelInformation': " << statusWithInfo.first.second << "\n";
                        exitCode = 1;
                    }
                    if (0 == exitCode)
                    {
                        statusWithInfo = proxy.getChannelInformation(toNode, toPath);
                        if (statusWithInfo.first.first)
                        {
                            if (statusWithInfo.second._found)
                            {
                                toIsOutput = statusWithInfo.second._isOutput;
                                toDataType = statusWithInfo.second._dataType;
                                toModes = statusWithInfo.second._modes;
                            }
                            else
                            {
                                ourContext->report("channel '"s + toNode + " "s + toPath + "' was not found."s);
                                std::cerr << "channel '" << toNode << " " << toPath << "' was not found.\n";
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'getChannelInformation': " << statusWithInfo.first.second << "\n";
                            exitCode = 1;
                        }
                    }
                    if (0 == exitCode)
                    {
                        if (toIsOutput)
                        {
                            ourContext->report("channel '"s + toNode + " "s + toPath + "' is an output!"s);
                            std::cerr << "channel '" << toNode << " " << toPath << "' is an output!\n";
                            exitCode = 1;
                        }
                        else if (! fromIsOutput)
                        {
                            ourContext->report("channel '"s + fromNode + " "s + fromPath + "' is an input!"s);
                            std::cerr << "channel '" << fromNode << " " << fromPath << "' is an input!\n";
                            exitCode = 1;
                        }
                        else
                        {
                            // Do the data types match up? Set 'dataType'.
                            if (fromDataType.empty())
                            {
                                dataType = toDataType;
                            }
                            else
                            {
                                if (toDataType.empty())
                                {
                                    dataType = fromDataType;
                                }
                                else if (fromDataType != toDataType)
                                {
                                    ourContext->report("channel '"s + fromNode + " "s + fromPath + "("s + fromDataType + ")' does not match '"s  +
                                                       toNode + " "s + toPath + "("s + toDataType + ")'."s);
                                    std::cerr << "channel '" << fromNode << " " << fromPath << "(" << fromDataType << ")' does not match '" <<
                                                toNode << " " << toPath << "(" << toDataType << ")'.\n";
                                    exitCode = 1;
                                }
                            }
                            if (0 == exitCode)
                            {
                                // Do the modes match up? Set 'resolvedMode'.
                                resolvedMode = nImO::ResolveTransport(fromModes, toModes);
                                if (nImO::TransportType::kUnknown == resolvedMode)
                                {
                                    ourContext->report("channel '"s + fromNode + " "s + fromPath + "' has incompatible transport mode with '"s  +
                                                       toNode + " "s + toPath + "'."s);
                                    std::cerr << "channel '" << fromNode << " " << fromPath << "' has incompatible transport mode with '" << toNode <<
                                                " " << toPath << "'.\n";
                                    exitCode = 1;
                                }
                            }
                        }
                    }
                }
                if (0 == exitCode)
                {
                    // Everything is fine, record the connection!
                    statusWithBool = proxy.addConnection(fromNode, fromPath, toNode, toPath, dataType, resolvedMode);
                    if (statusWithBool.first.first)
                    {
                        if (! statusWithBool.second)
                        {
                            ourContext->report("channel '"s + fromNode + " "s + fromPath + "' could not be connected to '"s  + toNode + " "s +
                                               toPath + "'."s);
                            std::cerr << "channel '" << fromNode << " " << fromPath << "' could not be connected to '" << toNode << " " << toPath <<
                                        "'.\n";
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'addConnection': " << statusWithBool.first.second << "\n";
                        exitCode = 1;
                    }
                    if (0 == exitCode)
                    {
                        // Send 'startDestination' command to 'to' node.
                        // Send 'startSource' command to 'from' node.
std::cerr << "** Unimplemented **\n";
                    }
                }
                if (0 != exitCode)
                {
                    if (needToRestoreFromState)
                    {
                        if (! previousStateForFrom)
                        {
                            statusWithBool = proxy.clearChannelInUse(fromNode, fromPath);
                            if (! statusWithBool.first.first)
                            {
                                std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                            }
                        }
                    }
                    if (needToRestoreToState)
                    {
                        if (! previousStateForTo)
                        {
                            statusWithBool = proxy.clearChannelInUse(toNode, toPath);
                            if (! statusWithBool.first.first)
                            {
                                std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                            }
                        }
                    }
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

//--------------------------------------------------------------------------------------------------
//
//  File:       nImOgetParametersMain.cpp
//
//  Project:    nImO
//
//  Contains:   A tool to get the parameters of an active nImO service.
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
//  Created:    2025-11-10
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Contexts/nImOutilityContext.h>
#include <nImOinputOutputCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOrequestResponse.h>
#include <nImOstandardOptions.h>
#include <ResponseHandlers/nImOgetParametersResponseHandler.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A tool to get the parameters of an active #nImO service. */

/*! @dir GetParameters
 @brief The set of files that implement the GetParameters tool. */
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

/*! @brief The entry point for the tool.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::StringArgumentDescriptor>("node"s,
                                                                                      "Node to be interrogated"s,
                                                                                      nImO::ArgumentMode::Required)};
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
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Get parameters of a node"s, "nImOgetParameters node"s, 2025,
                                     nImO::kCopyrightName, optionValues, nullptr, nImO::kSkipAutolaunchOption | nImO::kSkipMachineOption | nImO::kSkipNodeOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>("getParameter"s, optionValues._logging)};
            auto                nodeName{firstArg->getCurrentValue()};
            nImO::Connection    registryConnection{};

            if (ourContext->asUtilityContext()->findTheRegistry(registryConnection))
            {
                auto    proxy{nImO::RegistryProxy::create(ourContext, registryConnection)};
                auto    statusWithInfo{proxy->getNodeInformation(nodeName)};

                if (statusWithInfo.first.first)
                {
                    if (statusWithInfo.second._found)
                    {
                        // Send Get Parameters command to the node.
                        if (optionValues._expanded)
                        {
                            ourContext->report("sending get parameters request to '"s + nodeName + "'."s);
                        }
                        auto    handler{std::make_unique<nImO::GetParametersResponseHandler>()};
                        auto    status{nImO::SendRequestWithNoArgumentsAndNonEmptyResponse(ourContext, statusWithInfo.second._connection, handler.get(),
                                                                                           nImO::kGetParametersRequest, nImO::kGetParametersResponse)};

                        if (status.first)
                        {
                            nImO::SpArray   result{handler->result()};

                            std::cout << *result << "\n";
std::cerr << "*** unimplemented ***\n";
//                            nImO::AddressInfo   result{handler->result()};
//
//                            receiverAddress = result._address;
//                            receiverPort = result._port;
                        }
                        else
                        {
                            ourContext->report("Problem getting the parameters of node "s + nodeName + ": "s + status.second + "."s);
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        ourContext->report("Unknown node: '"s + nodeName + "'."s);
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

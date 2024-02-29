//--------------------------------------------------------------------------------------------------
//
//  File:       nImOlauchMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to start a service via a nImO launcher.
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
//  Created:    2024-01-26
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Contexts/nImOutilityContext.h>
#include <ResponseHandlers/nImOgetRunOptionsForAppResponseHandler.h>
#include <ResponseHandlers/nImOgetRunParamsForAppResponseHandler.h>
#include <ResponseHandlers/nImOlaunchAppResponseHandler.h>
#include <nImOlauncherCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOrequestResponse.h>
#include <nImOstandardOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to start a service via a #nImO launcher. */

/*! @dir Bridge
 @brief The set of files that implement the Bridge application. */
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

std::string
constructNodeNameFromOptions
    (const std::string &            launcherName,
     const std::string &            serviceName,
     const nImO::StdStringVector &  theOptions)
{
    ODL_ENTER(); //####
    ODL_S2s("launcherName = ", launcherName, "serviceName = ", serviceName); //####
    std::string nodeName{launcherName};
    std::string tag{};

    for (auto & walker : theOptions)
    {
        if (0 < walker.length())
        {
            auto    optionChar{walker.substr(0, 1)[0]};
            auto    optionValue{walker.substr(1, walker.length())};

            if ('n' == optionChar)
            {
                nodeName = optionValue;
            }
            else if ('t' == optionChar)
            {
                tag = optionValue;
            }
        }
    }
    std::string result{nImO::ConstructNodeName(nodeName, serviceName, tag)};

    ODL_EXIT_s(result); //####
    return result;
} // constructNodeNameFromOptions

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for starting a service via a #nImO launcher.

 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::StringArgumentDescriptor>("launcher"s, "Launcher to use"s,
                                                                                      nImO::ArgumentMode::Optional, ""s)};
    auto                    secondArg{std::make_shared<nImO::StringArgumentDescriptor>("service"s, "Service to launch"s,
                                                                                       nImO::ArgumentMode::Optional, ""s)};
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
    argumentList.push_back(secondArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Launch a service"s, "nImOlaunch launcher-node passthrough"s, 2024,
                                     nImO::kCopyrightName, optionValues, nullptr, nImO::kSkipExpandedOption |
                                     nImO::kSkipFlavoursOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>(progName, "launch"s, optionValues._logging)};
            nImO::Connection    registryConnection{};

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                auto                proxy{nImO::RegistryProxy::create(ourContext, registryConnection)};
                nImO::Connection    launcherConnection{};
                auto                launcherName{firstArg->getCurrentValue()};
                auto                serviceName{secondArg->getCurrentValue()};

                if (launcherName.empty())
                {
                    auto    statusWithAllNodes{proxy->getInformationForAllNodes()};

                    if (statusWithAllNodes.first.first)
                    {
                        nImO::StdStringSet  launchers{};
                        auto                nodes{statusWithAllNodes.second};

                        for (auto & walker : nodes)
                        {
                            if (walker._found && (nImO::ServiceType::LauncherService == walker._serviceType))
                            {
                                launchers.insert(walker._name);
                            }
                        }
                        if (launchers.empty())
                        {
                            ourContext->report("No launchers found."s);
                            exitCode = 1;
                        }
                        else
                        {
                            std::cout << "The following launchers are available:\n";
                            int count{0};
                            int selection{0};

                            std::cout << "\t0 : <select none and leave>\n";
                            for (auto & walker : launchers)
                            {
                                ++count;
                                std::cout << "\t" << count << " : " << walker << "\n";
                            }
                            do
                             {
                                 std::cout << "Selection? ";
                                 std::cout.flush();
                                 std::cin >> selection;
                             }
                            while ((0 > selection) || (selection > count));
                            if (0 == selection)
                            {
                                exitCode = 2;
                            }
                            else
                            {
                                count = 0;
                                for (auto & walker : launchers)
                                {
                                    ++count;
                                    if (selection == count)
                                    {
                                        launcherName = walker;
                                        for (auto & subWalker : nodes)
                                        {
                                            if (subWalker._name == launcherName)
                                            {
                                                launcherConnection = subWalker._connection;
                                                break;

                                            }
                                        }
                                        break;

                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getInformationForAllNodes': " << statusWithAllNodes.first.second << ".\n";
                        exitCode = 1;
                    }
                }
                else
                {
                    auto    statusWithNodeInfo{proxy->getNodeInformation(launcherName)};

                    if (statusWithNodeInfo.first.first)
                    {
                        if (statusWithNodeInfo.second._found)
                        {
                            if (nImO::ServiceType::LauncherService == statusWithNodeInfo.second._serviceType)
                            {
                                launcherConnection = statusWithNodeInfo.second._connection;
                            }
                            else
                            {
                                ourContext->report("'" + launcherName + "' is not a launcher."s);
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            ourContext->report("Unknown node: '"s + launcherName + "'."s);
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << ".\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    auto    statusWithInfo{proxy->getInformationForAllApplicationsOnNode(launcherName)};

                    if (statusWithInfo.first.first)
                    {
                        auto    applicationsInfo{statusWithInfo.second};

                        if (serviceName.empty())
                        {
                            std::cout << "The following services are available from launcher '" << launcherName << "':\n";
                            int count{0};
                            int selection{0};

                            std::cout << "\t0 : <select none and leave>\n";
                            for (auto & walker : applicationsInfo)
                            {
                                if (walker._found)
                                {
                                    ++count;
                                    std::cout << "\t" << count << " : " << walker._appName << " -> " << walker._appDescription << "\n";
                                }
                            }
                            do
                             {
                                 std::cout << "Selection? ";
                                 std::cout.flush();
                                 std::cin >> selection;
                             }
                            while ((0 > selection) || (selection > count));
                            if (0 == selection)
                            {
                                exitCode = 2;
                            }
                            else
                            {
                                count = 0;
                                for (auto & walker : applicationsInfo)
                                {
                                    ++count;
                                    if (selection == count)
                                    {
                                        serviceName = walker._appName;
                                        break;

                                    }
                                }
                            }
                        }
                        else
                        {
                            bool    found{false};

                            for (auto & walker : applicationsInfo)
                            {
                                if (walker._found && (walker._appName == serviceName))
                                {
                                    found = true;
                                    break;

                                }
                            }
                            if (! found)
                            {
                                ourContext->report("Unknown service: '"s + serviceName + "' on launcher '" + launcherName + "'."s);
                                exitCode = 1;
                            }
                        }
                    }
                    else
                    {
                        std::cerr << "Problem with 'getInformationForAllApplicationsOnNode': " << statusWithInfo.first.second << ".\n";
                        exitCode = 1;
                    }
                }
                if (0 == exitCode)
                {
                    nImO::DescriptorVector  appDescriptors{};
                    auto                    argArray1{std::make_shared<nImO::Array>()};
                    auto                    handler1{std::make_unique<nImO::GetRunOptionsForAppResponseHandler>()};

                    argArray1->addValue(std::make_shared<nImO::String>(serviceName));
                    auto            statusWithBool{nImO::SendRequestWithArgumentsAndNonEmptyResponse(ourContext, launcherConnection, handler1.get(),
                                                                                                     argArray1.get(),
                                                                                                     nImO::kGetRunOptionsForAppRequest,
                                                                                                     nImO::kGetRunOptionsForAppResponse)};
                    std::set<char>  availableOptions{};
                    std::set<char>  optionNeedsString{};

                    if (statusWithBool.first)
                    {
                        for (auto & walker : handler1->result())
                        {
                            auto    aChar{tolower(walker)};

                            if ('a' != aChar)
                            {
                                // A service will report options that we aren't going to use.
                                availableOptions.insert(aChar);
                            }
                        }
                        auto    argArray2{std::make_shared<nImO::Array>()};
                        auto    handler2{std::make_unique<nImO::GetRunParamsForAppResponseHandler>()};

                        argArray2->addValue(std::make_shared<nImO::String>(serviceName));
                        statusWithBool = nImO::SendRequestWithArgumentsAndNonEmptyResponse(ourContext, launcherConnection, handler2.get(),
                                                                                           argArray2.get(), nImO::kGetRunParamsForAppRequest,
                                                                                           nImO::kGetRunParamsForAppResponse);

                        if (statusWithBool.first)
                        {
                            for (auto & walker : handler2->result())
                            {
                                auto    descriptor{nImO::ConvertStringToDescriptor(walker)};

                                if (descriptor)
                                {
                                    appDescriptors.push_back(descriptor);
                                }
                                else
                                {
                                    ourContext->report("Bad argument descriptor: '" + walker + "'.");
                                    exitCode = 1;
                                }
                            }
                        }
                        else
                        {
                            std::cerr << "Problem getting the run parameters for '" << serviceName << "' from '" << launcherName + "'.\n";
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        std::cerr << "Problem getting the run options for '" << serviceName << "' from '" << launcherName + "'.\n";
                        exitCode = 1;
                    }
                    if (0 == exitCode)
                    {
                        std::cout << "Options for " << serviceName << " on " << launcherName << ":\n";
                        for (auto charWalker : availableOptions)
                        {
                            std::cout << "\t" << charWalker << "\t";
                            switch (charWalker)
                            {
                                case 'a' :
                                    // Ignore this option if it appears!
                                    break;

                                case 'b' :
                                    std::cout << "Specify the base name for channels"; // string arg required
                                    optionNeedsString.insert(charWalker);
                                    break;

                                case 'c' :
                                    std::cout << "Specify the path to the configuration file"; // file path arg required
                                    optionNeedsString.insert(charWalker);
                                    break;

                                case 'e' :
                                    std::cout << "Display more details";
                                    break;

                                case 'i' :
                                    std::cout << "Specify the data type for the input channel(s)"; // string arg required
                                    optionNeedsString.insert(charWalker);
                                    break;

                                case 'l' :
                                    std::cout << "Log the application";
                                    break;

                                case 'n' :
                                    std::cout << "Specify a non-default node name to be used"; // string arg required
                                    optionNeedsString.insert(charWalker);
                                    break;

                                case 'o' :
                                    std::cout << "Specify the data type for the output channel(s)"; // string arg required
                                    optionNeedsString.insert(charWalker);
                                    break;

                                case 't' :
                                    std::cout << "Specify the tag to be used as part of the service name"; // string arg required
                                    optionNeedsString.insert(charWalker);
                                    break;

                                case 'w' :
                                    std::cout << "Wait for connection(s)";
                                    break;

                                default :
                                    std::cout << "<unexpected option '" << charWalker << "'";
                                    break;

                            }
                            std::cout << "\n";
                        }
                        std::string             optionsSoFar{};
                        nImO::StdStringVector   optionsToApply{};

                        // Build up the option list:
                        for ( ; ; )
                        {
                            if (! optionsSoFar.empty())
                            {
                                std::cout << "Options already selected: " << optionsSoFar << "\n";
                            }
                            std::cout << "Option to apply (empty line when finished): ";
                            std::cout.flush();
                            std::string inLine;

                            if (getline(std::cin, inLine))
                            {
                                // Trim down the input
                                inLine = nImO::LeftTrim(inLine);
                                if (inLine.empty())
                                {
                                    break;

                                }
                                auto    aChar{StaticCast(char, tolower(inLine[0]))};

                                if (availableOptions.end() == availableOptions.find(aChar))
                                {
                                    std::cout << "No such option." << "\n";
                                }
                                else
                                {
                                    optionsSoFar += " "s + aChar;
                                    std::string newOption{aChar};

                                    if (optionNeedsString.end() == optionNeedsString.find(aChar))
                                    {
                                        optionsToApply.push_back(newOption);
                                    }
                                    else
                                    {
                                        std::cout << "Argument for the option: ";
                                        std::cout.flush();
                                        if (getline(std::cin, inLine))
                                        {
                                            // Trim down the input
                                            inLine = nImO::LeftTrim(inLine);
                                            if (inLine.empty())
                                            {
                                                break;

                                            }
                                            inLine = nImO::RightTrim(inLine);
                                            newOption += inLine;
                                            optionsToApply.push_back(newOption);
                                        }
                                        else
                                        {
                                            break;

                                        }
                                    }
                                }
                            }
                            else
                            {
                                break;

                            }
                        }
                        // Check if the application already has been registered!
                        auto    newNodeName{constructNodeNameFromOptions(launcherName, serviceName, optionsToApply)};
                        auto    statusWithInfo{proxy->getNodeInformation(newNodeName)};

                        if (statusWithInfo.first.first)
                        {
                            if (statusWithInfo.second._found)
                            {
                                ourContext->report("Node '"s + newNodeName + "'already present."s);
                                exitCode = 1;
                            }
                            else
                            {
                                if (! appDescriptors.empty())
                                {
                                    std::cout << "Parameters for " << serviceName << " on " << launcherName << ":\n";
                                    for (auto & walker : appDescriptors)
                                    {
                                        std::cout << "\t" << walker->describe() << "\n";
                                    }
                                    do
                                    {
                                        std::cout << "Values for parameters:\n";
                                        if (PromptForValues(appDescriptors))
                                        {
                                            break;

                                        }
                                        std::cout << "A parameter failed to be set.\n";
                                    }
                                    while (true);
                                }
                                auto    argArray2{std::make_shared<nImO::Array>()};
                                auto    handler2{std::make_unique<nImO::LaunchAppResponseHandler>()};
                                auto    optionsArray{std::make_shared<nImO::Array>()};
                                auto    parametersArray{std::make_shared<nImO::Array>()};

                                for (auto & option : optionsToApply)
                                {
                                    optionsArray->addValue(std::make_shared<nImO::String>(option));
                                }
                                for (auto & walker : appDescriptors)
                                {
                                    parametersArray->addValue(std::make_shared<nImO::String>(walker->getProcessedValue()));
                                }
                                argArray2->addValue(std::make_shared<nImO::String>(serviceName));
                                argArray2->addValue(optionsArray);
                                argArray2->addValue(parametersArray);
                                statusWithBool = nImO::SendRequestWithArgumentsAndNonEmptyResponse(ourContext, launcherConnection, handler2.get(),
                                                                                                   argArray2.get(), nImO::kLaunchAppRequest,
                                                                                                   nImO::kLaunchAppResponse);
                                if (! statusWithBool.first)
                                {
                                    std::cerr << "Problem launching the application '" << serviceName << "' on '" << launcherName + "'.\n";
                                    exitCode = 1;
                                }
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'getNodeInformation': " << statusWithInfo.first.second << ".\n";
                            exitCode = 1;
                        }
                    }
                }
            }
            else
            {
                ourContext->report("Registry not found."s);
                exitCode = 2;
            }
            ourContext->report("exiting."s, false);
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

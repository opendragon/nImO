//--------------------------------------------------------------------------------------------------
//
//  File:       nImOlauncherMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to provide remote launch capabilities for nImO.
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
//  Created:    2023-02-10
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <BasicTypes/nImOstring.h>
#include <BasicTypes/nImOvalue.h>
#include <Containers/nImOmap.h>
#include <Containers/nImOstringBuffer.h>
#include <Launcher/nImOlauncherContext.h>
#include <nImOlauncherCommands.h>
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
 @brief A service application to provide remote launch capabilities for #nImO. */

/*! @dir Launcher
 @brief The set of files that implement the Launcher application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The default path to the application file list file. */
static const std::string    kDefaultAppListFilePath{nImO_RUN_CONFIG_DIR_ "nimo-services.txt"};

/*! @brief The loaded application file list values. */
static nImO::SpValue    lAppListValues{};

/*! @brief A class to provide values that are used for handling callbacks for the application. */
class LauncherBreakHandler final : public nImO::CallbackFunction
{
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        using inherited = CallbackFunction;

    public :
        // Public methods.

        /*! @brief The constructor. */
        inline LauncherBreakHandler
            (void) :
                inherited()
        {
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Process a break signal. */
        void
        operator()
            (void)
            const
            override
        {
            ODL_OBJENTER(); //####
            ODL_OBJEXIT(); //####
        }

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

}; // LauncherBreakHandler

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

static bool
loadApplicationInformation
    (const std::string &    appListFilePath)
{
    ODL_ENTER(); //####
    ODL_S1s("appListFilePath = ", appListFilePath); //####
    std::string workingPath;
    bool        result{false};

    if (appListFilePath.empty())
    {
        workingPath = kDefaultAppListFilePath;
    }
    else
    {
        workingPath = appListFilePath;
    }
#if MAC_OR_LINUX_
    if (0 == access(workingPath.c_str(), R_OK))
#else // not MAC_OR_LINUX_
    if (0 == _access(workingPath.c_str(), 4))
#endif // not MAC_OR_LINUX_
    {
        std::ifstream   inStream{workingPath.c_str()};

        if (inStream)
        {
            nImO::StringBuffer  readString{};

            inStream >> readString;
            auto    readValue{readString.convertToValue()};

            if (nullptr == readValue)
            {
                std::cerr << "Could not parse contents of application file list file.\n";
            }
            else
            {
                auto    asMap{readValue->asMap()};

                if (nullptr == asMap)
                {
                    std::cerr << "Application file list file did not have the correct structure.\n";
                }
                else
                {
                    // Check the structure of the value read.
                    if (nImO::Enumerable::String == asMap->getKeyKind())
                    {
                        auto    writeMap{std::make_shared<nImO::Map>()};
                        auto    descriptionKey{std::make_shared<nImO::String>(nImO::kDescriptionKey)};
                        auto    pathKey{std::make_shared<nImO::String>(nImO::kPathKey)};

                        for (auto & walker : *asMap)
                        {
                            auto    readSubMap{walker.second->asMap()};

                            if (nullptr == readSubMap)
                            {
                                // Ignore entries that aren't Maps, rather than rejecting the whole file.
                                std::cerr << "warning: value with key " << walker.first << " is not a map.\n";
                            }
                            else if (nImO::Enumerable::String == readSubMap->getKeyKind())
                            {
                                auto    descriptionEntry{readSubMap->find(descriptionKey)};
                                auto    pathEntry{readSubMap->find(pathKey)};

                                if (readSubMap->end() == descriptionEntry)
                                {
                                    std::cerr << "warning: value with key " << walker.first << " is missing a description.\n";
                                }
                                else if (readSubMap->end() == pathEntry)
                                {
                                    std::cerr << "warning: value with key " << walker.first << " is missing a path.\n";
                                }
                                else
                                {
                                    auto    descriptionAsString{descriptionEntry->second->asString()};
                                    auto    pathAsString{pathEntry->second->asString()};

                                    if (nullptr == descriptionAsString)
                                    {
                                        std::cerr << "warning: description for value with key " << walker.first << " is invalid.\n";
                                    }
                                    else if (nullptr == pathAsString)
                                    {
                                        std::cerr << "warning: path for value with key " << walker.first << " is invalid.\n";
                                    }
                                    else
                                    {
                                        auto    writeSubMap{std::make_shared<nImO::Map>()};
                                        bool    useOriginal{true};
                                        auto    pathValue{pathAsString->getValue()};

                                        if (3 < pathValue.length())
                                        {
                                            if (pathValue.substr(0, 3) == "$$/")
                                            {
                                                pathValue = nImO_BIN_DIR_ + pathValue.substr(3);
                                                useOriginal = false;
                                            }
                                        }
                                        // Check if the path exists!
#if MAC_OR_LINUX_
                                        if (0 == access(pathValue.c_str(), R_OK))
#else // not MAC_OR_LINUX_
                                        if (0 == _access(pathValue.c_str(), 4))
#endif // not MAC_OR_LINUX_
                                        {
                                            writeSubMap->addValue(descriptionKey, descriptionEntry->second);
                                            if (useOriginal)
                                            {
                                                writeSubMap->addValue(pathKey, pathEntry->second);
                                            }
                                            else
                                            {
                                                writeSubMap->addValue(pathKey, std::make_shared<nImO::String>(pathValue));
                                            }
                                            writeMap->addValue(walker.first, writeSubMap);
                                        }
                                        else
                                        {
                                            std::cerr << "warning: file at path for value with key " << walker.first <<
                                                        " could not be found.\n";
                                        }
                                    }
                                }
                            }
                            else
                            {
                                // Ignore entries that are Maps with the wrong key type, rather than rejecting the whole file.
                                std::cerr << "warning: value with key " << walker.first << " does not have the correct structure.\n";
                            }
                        }
                        if (! writeMap->empty())
                        {
                            lAppListValues = writeMap;
                            result = true;
                        }
                    }
                    else
                    {
                        std::cerr << "Application file list file did not have the correct structure.\n";
                    }
                }
            }
        }
        else
        {
            std::cerr << "Application file list file could not be read.\n";
        }
    }
    else
    {
        std::cerr << "Application file list file could not be found.\n";
    }
    ODL_EXIT_B(result); //####
    return result;
} // loadApplicationInformation

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for remote launching for #nImO.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string                         progName{*argv};
    nImO::FilePathArgumentDescriptor    firstArg{"appList"s, "File containing a list of applications"s, nImO::ArgumentMode::Optional, ""s,
                                                kDefaultAppListFilePath};
    nImO::DescriptorVector              argumentList{};
    nImO::ServiceOptions                optionValues{};
    int                                 exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(&firstArg);
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Launcher"s, ""s, 2023, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipArgsOption | nImO::kSkipBaseOption | nImO::kSkipDescribeOption | nImO::kSkipExpandedOption |
                                    nImO::kSkipFlavoursOption | nImO::kSkipInTypeOption | nImO::kSkipNodeOption | nImO::kSkipOutTypeOption |
                                    nImO::kSkipTagOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, "launcher"s, optionValues._tag)};
            auto                ourContext{std::make_shared<nImO::LauncherContext>(argc, argv, progName, "Launcher"s, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new LauncherBreakHandler};

            nImO::SetSpecialBreakObject(cleanup);
            nImO::AddLauncherHandlers(ourContext, cleanup);
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
                        statusWithBool = proxy.addNode(nodeName, argc, argv, nImO::ServiceType::LauncherService,
                                                       ourContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
std::cerr << "** Unimplemented **\n";
                                // Load the app list file and exit if not properly structured.
                                if (loadApplicationInformation(firstArg.getCurrentValue()))
                                {
std::cerr << *lAppListValues << std::endl;//!!
                                    //TBD: Send the app list map to the Registry
                                    ourContext->report("waiting for requests."s);
                                    std::cerr << "ready.\n";
                                    for ( ; nImO::gKeepRunning; )
                                    {
                                        boost::this_thread::yield();
                                    }
                                    std::cerr << "done.\n";
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
                                            std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << "\n";
                                            exitCode = 1;
                                        }
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

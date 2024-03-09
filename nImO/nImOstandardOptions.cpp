//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstandardOptions.cpp
//
//  Project:    nImO
//
//  Contains:   The function and class definitions for standard command-line options used with nImO.
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
//  Created:    2023-03-11
//
//--------------------------------------------------------------------------------------------------

#include <nImOstandardOptions.h>

#include <ArgumentDescriptors/nImObaseArgumentDescriptor.h>
#include <BasicTypes/nImOstring.h>
#include <BasicTypes/nImOvalue.h>
#include <Containers/nImOmap.h>
#include <Containers/nImOstringBuffer.h>
#include <nImOmainSupport.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The function and variable definitions for standard command-line options used with nImO. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace nImO;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The default path to the configuration file. */
static const std::string    kDefaultConfigFilePath{nImO_RUN_CONFIG_DIR_ "nimo-config.txt"};

/*! @brief The loaded configuration values. */
static nImO::SpValue    lConfigurationValues{};

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

boost::optional<nImO::SpValue>
nImO::GetConfiguredValue
    (const std::string &    key)
{
    ODL_ENTER(); //####
    ODL_S1s("key = ", key); //####
    boost::optional<SpValue>    retVal;

    if ((! key.empty()) && (nullptr != lConfigurationValues))
    {
        auto    asMapValue{lConfigurationValues->asMap()};

        if (nullptr != asMapValue)
        {
            auto    iter{asMapValue->find(std::make_shared<String>(key))};

            if (asMapValue->end() != iter)
            {
                retVal = iter->second;
            }
        }
    }
    ODL_EXIT(); //####
    return retVal;
} // nImO::GetConfiguredValue

void
nImO::LoadConfiguration
    (const std::string &    configFilePath)
{
    ODL_ENTER(); //####
    ODL_S1s("configFilePath = ", configFilePath); //####
    std::string workingPath;

    if (configFilePath.empty())
    {
        workingPath = kDefaultConfigFilePath;
    }
    else
    {
        workingPath = configFilePath;
    }
#if MAC_OR_LINUX_OR_BSD_
    if (0 == access(workingPath.c_str(), R_OK))
#else // not MAC_OR_LINUX_OR_BSD_
    if (0 == _access(workingPath.c_str(), 4))
#endif // not MAC_OR_LINUX_OR_BSD_
    {
        std::ifstream   inStream{workingPath};

        if (inStream)
        {
            nImO::StringBuffer  readString{};

            inStream >> readString;
            auto    readValue{readString.convertToValue()};

            if (readValue && (nullptr != readValue->asMap()))
            {
                // Check the structure of the value read.
                lConfigurationValues = readValue;
            }
            else
            {
                if (readValue)
                {
                    std::cerr << "warning: configuration file did not have the correct structure.\n";
                }
                else
                {
                    std::cerr << "warning: could not parse contents of configuration file.\n";
                }
            }
        }
        else
        {
            std::cerr << "warning: configuration file could not be read.\n";
        }
    }
    else
    {
        std::cerr << "warning: configuration file could not be found.\n";
    }
    ODL_EXIT(); //####
} // LoadConfiguration

bool
nImO::ProcessStandardOptions
    (const int              argc,
     Ptr(Ptr(char))         argv,
     DescriptorVector &     argumentDescriptions,
     const std::string &    utilityDescription,
     const std::string &    utilityExample,
     const int              year,
     const std::string &    copyrightHolder,
     StandardOptions &      optionValues,
     HelpFunction           helper,
     const OptionsMask      optionsToIgnore,
     Ptr(StdStringVector)   arguments)
{
    ODL_ENTER(); //####
    ODL_I2("argc = ", argc, "year = ", year); //####
    ODL_P3("argv = ", argv, "argumentDescriptions = ", &argumentDescriptions, "optionValues = ", &optionValues); //####
    ODL_X1("optionsToIgnore = ", StaticCast(int64_t, optionsToIgnore)); //####
    ODL_P1("arguments = ", arguments); //####
    ODL_S3s("utilityDescription = ", utilityDescription, "utilityExample = ", utilityExample, //####
            "copyrightHolder = ", copyrightHolder); //####
    enum class OptionIndex
    {
        kOptionUNKNOWN,
        kOptionCONFIG,
        kOptionDESCRIBE,
        kOptionEXPANDED,
        kOptionHELP,
        kOptionJSON,
        kOptionLOG,
        kOptionMACHINE,
        kOptionTABS,
        kOptionVERSION
    }; // OptionIndex

    bool                        keepGoing{true};
    Option_::Descriptor         firstDescriptor{StaticCast(unsigned int, OptionIndex::kOptionUNKNOWN), 0, "", "",
                                                Option_::Arg::None, nullptr};
    auto                        configHelpString{"  "s + MakeOption("c"s, "config"s) + " <path> \tSpecify the path to the configuration file"s};
    Option_::Descriptor         configDescriptor{StaticCast(unsigned int, OptionIndex::kOptionCONFIG), 0, "c", "config",
                                                Option_::Arg::Required, configHelpString.c_str()};
    auto                        expandedHelpString{"  "s + MakeOption("e"s, "expanded"s) + " \tDisplay more details"s};
    Option_::Descriptor         expandedDescriptor{StaticCast(unsigned int, OptionIndex::kOptionEXPANDED), 0, "e",
                                                    "expanded", Option_::Arg::None, expandedHelpString.c_str()};
    auto                        helpHelpString{"  "s + MakeOption("h"s, "help"s) + "  \tPrint usage and exit"s};
    Option_::Descriptor         helpDescriptor{StaticCast(unsigned int, OptionIndex::kOptionHELP), 0, "h", "help",
                                                Option_::Arg::None, helpHelpString.c_str()};
    auto                        jsonHelpString{"  "s + MakeOption("j"s, "json"s) + " \tGenerate output in JSON format"s};
    Option_::Descriptor         jsonDescriptor{StaticCast(unsigned int, OptionIndex::kOptionJSON), 0, "j", "json",
                                                Option_::Arg::None, jsonHelpString.c_str()};
    auto                        logHelpString{"  "s + MakeOption("l"s, "log"s) + " \tLog the application"s};
    Option_::Descriptor         logDescriptor{StaticCast(unsigned int, OptionIndex::kOptionLOG), 0, "l",
                                                "log", Option_::Arg::None, logHelpString.c_str()};
    auto                        machineHelpString{"  "s + MakeOption("m"s, "machine"s) + " <name> \tSpecify machine to be referenced"s};
    Option_::Descriptor         machineDescriptor{StaticCast(unsigned int, OptionIndex::kOptionMACHINE), 0, "m", "machine",
                                                    Option_::Arg::Required, machineHelpString.c_str()};
    auto                        tabsHelpString{"  "s + MakeOption("t"s, "tabs"s) + " \tGenerate output in tab-format"s};
    Option_::Descriptor         tabsDescriptor{StaticCast(unsigned int, OptionIndex::kOptionTABS), 0, "t", "tabs",
                                                Option_::Arg::None, tabsHelpString.c_str()};
    auto                        versionHelpString{"  "s + MakeOption("v"s, "version"s) + " \tPrint version information and exit"s};
    Option_::Descriptor         versionDescriptor{StaticCast(unsigned int, OptionIndex::kOptionVERSION), 0, "v",
                                                    "version", Option_::Arg::None, versionHelpString.c_str()};
    Option_::Descriptor         lastDescriptor{0, 0, nullptr, nullptr, nullptr, nullptr};
    Option_::Descriptor         usage[11]; // first, config, describe, expanded, help, json, log, machine, tabs, version, last
    Ptr(Option_::Descriptor)    usageWalker{usage};
    int                         argcWork = argc;
    Ptr(Ptr(char))              argvWork{argv};
    auto                        usageString{"USAGE: "s};
    auto                        argList{ArgumentsToArgString(argumentDescriptions)};

    usageString += *argv;
    usageString += " [options]"s;
    if (! argList.empty())
    {
        usageString += " "s + argList;
    }
    if (! utilityDescription.empty())
    {
        usageString += "\n"s + utilityDescription;
    }
    if (! utilityExample.empty())
    {
        usageString += "\n\nExample: "s + utilityExample;
    }
    if (! argList.empty())
    {
        StdStringVector descriptions;

        ArgumentsToDescriptionArray(argumentDescriptions, descriptions);
        usageString += "\n\n"s;
        for (size_t ii = 0, mm = descriptions.size(); mm > ii; ++ii)
        {
            if (0 < ii)
            {
                usageString += "\n"s;
            }
            usageString += "  "s + descriptions[ii];
        }
    }
    usageString += "\n\nOptions:"s;
#if MAC_OR_LINUX_OR_BSD_
    firstDescriptor.help = strdup(usageString.c_str());
#else // not MAC_OR_LINUX_OR_BSD_
    firstDescriptor.help = _strdup(usageString.c_str());
#endif // not MAC_OR_LINUX_OR_BSD_
    memcpy(usageWalker++, &firstDescriptor, sizeof(firstDescriptor));
    if (0 == (kSkipConfigFileOption & optionsToIgnore))
    {
        memcpy(usageWalker++, &configDescriptor, sizeof(configDescriptor));
    }
    if (0 == (kSkipExpandedOption & optionsToIgnore))
    {
        memcpy(usageWalker++, &expandedDescriptor, sizeof(expandedDescriptor));
    }
    memcpy(usageWalker++, &helpDescriptor, sizeof(helpDescriptor));
    if (0 == (kSkipFlavoursOption & optionsToIgnore))
    {
        memcpy(usageWalker++, &jsonDescriptor, sizeof(jsonDescriptor));
    }
    if (0 == (kSkipLoggingOption & optionsToIgnore))
    {
        memcpy(usageWalker++, &logDescriptor, sizeof(logDescriptor));
    }
    if (0 == (kSkipMachineOption & optionsToIgnore))
    {
        memcpy(usageWalker++, &machineDescriptor, sizeof(machineDescriptor));
    }
    if (0 == (kSkipFlavoursOption & optionsToIgnore))
    {
        memcpy(usageWalker++, &tabsDescriptor, sizeof(tabsDescriptor));
    }
    memcpy(usageWalker++, &versionDescriptor, sizeof(versionDescriptor));
    memcpy(usageWalker++, &lastDescriptor, sizeof(lastDescriptor));
    argcWork -= (argc > 0);
    argvWork += (argc > 0); // skip program name argv[0] if present
    Option_::Stats  stats{usage, argcWork, argvWork};
    auto            options{std::make_unique<Option_::Option[]>(stats.options_max)};
    auto            buffer{std::make_unique<Option_::Option[]>(stats.buffer_max)};
    Option_::Parser parse{usage, argcWork, argvWork, options.get(), buffer.get(), 1};
    std::string     badArgs;

    if (parse.error())
    {
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else
    {
        if ((nullptr != options[StaticCast(size_t, OptionIndex::kOptionHELP)]) ||
            (nullptr != options[StaticCast(size_t, OptionIndex::kOptionUNKNOWN)]))
        {
            Option_::printUsage(std::cout, usage, kHelpLineLength);
            if (nullptr != helper)
            {
                helper(std::cout);
            }
            keepGoing = false;
            ODL_B1("keepGoing <- ", keepGoing); //####
        }
        else
        {
            if (nullptr == options[StaticCast(size_t, OptionIndex::kOptionVERSION)])
            {
                if (ProcessArguments(argumentDescriptions, parse, badArgs))
                {
                    if (0 == (kSkipFlavoursOption & optionsToIgnore))
                    {
                        if (nullptr == options[StaticCast(size_t, OptionIndex::kOptionJSON)])
                        {
                            if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionTABS)])
                            {
                                optionValues._flavour = OutputFlavour::kFlavourTabs;
                            }
                        }
                        else
                        {
                            optionValues._flavour = OutputFlavour::kFlavourJSON;
                        }
                    }
                    if ((0 == (kSkipExpandedOption & optionsToIgnore)) && (nullptr != options[StaticCast(size_t, OptionIndex::kOptionEXPANDED)]))
                    {
                        optionValues._expanded = true;
                    }
                    if ((0 == (kSkipLoggingOption & optionsToIgnore)) &&(nullptr != options[StaticCast(size_t, OptionIndex::kOptionLOG)]))
                    {
                        optionValues._logging = true;
                    }
                    optionValues._configFilePath = kDefaultConfigFilePath;
                    if (0 == (kSkipConfigFileOption & optionsToIgnore))
                    {
                        // Use the last 'machine' value.
                        for (Ptr(Option_::Option) opt = options[StaticCast(size_t, OptionIndex::kOptionCONFIG)]; nullptr != opt; opt = opt->next())
                        {
                            if (nullptr != opt->arg)
                            {
                                optionValues._configFilePath = opt->arg;
                            }
                        }
                    }
                    if (0 == (kSkipMachineOption & optionsToIgnore))
                    {
                        // Use the last 'machine' value.
                        for (Ptr(Option_::Option) opt = options[StaticCast(size_t, OptionIndex::kOptionMACHINE)]; nullptr != opt; opt = opt->next())
                        {
                            if (nullptr != opt->arg)
                            {
                                optionValues._machine = opt->arg;
                            }
                        }
                    }
                    if (nullptr != arguments)
                    {
                        arguments->clear();
                        for (int ii = 0; ii < parse.nonOptionsCount(); ++ii)
                        {
                            arguments->emplace_back(parse.nonOption(ii));
                        }
                    }
                }
                else
                {
                    std::cout << "One or more invalid or missing arguments (" << badArgs << ").\n";
                    keepGoing = false;
                    ODL_B1("keepGoing <- ", keepGoing); //####
                }
            }
            else
            {
                auto    nImOversionString{SanitizeString(nImO_VERSION_, true)};

                std::cout << "Version " << nImOversionString << ": Copyright (c) " << year << " by " <<
                            copyrightHolder << ".\n";
                keepGoing = false;
                ODL_B1("keepGoing <- ", keepGoing); //####
            }
        }
    }
    ODL_EXIT_B(keepGoing); //####
    return keepGoing;
} // nImO::ProcessStandardOptions

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

#include <fstream>
#include <initFile.h>
#include <initFileObject.h>
#include <nImObaseArgumentDescriptor.h>

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

#if MAC_OR_LINUX_
# define CONFIG_FILE_ROOT_PATH  "/etc/nImO/"
#else // ! MAC_OR_LINUX_
# define CONFIG_FILE_ROOT_PATH  "C:/nImO/"
#endif // ! MAC_OR_LINUX_

/*! @brief The default path to the configuration file. */
static const std::string    kDefaultConfigFilePath{CONFIG_FILE_ROOT_PATH "nimo-config.txt"};

/*! @brief The loaded configuration values. */
static InitFile::SpBaseValue    lConfigurationValues;

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

boost::optional<InitFile::SpBaseValue>
nImO::GetConfiguredValue
    (const std::string &    key)
{
    ODL_ENTER(); //####
    ODL_S1s("key = ", key); //####
    boost::optional<InitFile::SpBaseValue>  retVal;

    if ((0 < key.length()) && (nullptr != lConfigurationValues))
    {
        Ptr(InitFile::ObjectValue)  asObjectValue{lConfigurationValues->AsObject()};

        if (nullptr != asObjectValue)
        {
            InitFile::SpBaseValue   value{asObjectValue->GetValue(key)};

            if (nullptr != value)
            {
                retVal = value;
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

    if (0 < configFilePath.length())
    {
        workingPath = configFilePath;
    }
    else
    {
        workingPath = kDefaultConfigFilePath;
    }
#if MAC_OR_LINUX_
    if (0 == access(workingPath.c_str(), R_OK))
#else // ! MAC_OR_LINUX_
    if (0 == _access(workingPath.c_str(), 4))
#endif // ! MAC_OR_LINUX_
    {
        std::ifstream   inStream{workingPath.c_str()};

        if (inStream)
        {
            InitFile::SpBaseValue readValue{InitFile::GetValue(inStream)};

            if ((nullptr != readValue) && (nullptr != readValue->AsObject()))
            {
                lConfigurationValues = readValue;
            }
        }
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
     CPtr(char)             copyrightHolder,
     StandardOptions &      optionValues,
     HelpFunction           helper,
     const OptionsMask      optionsToIgnore,
     Ptr(StringVector)      arguments)
{
    ODL_ENTER(); //####
    ODL_I3("argc = ", argc, "year = ", year, "optionsToIgnore = ", StaticCast(int64_t, optionsToIgnore)); //####
    ODL_P3("argv = ", argv, "argumentDescriptions = ", &argumentDescriptions, "optionValues = ", &optionValues); //####
    ODL_P1("arguments = ", arguments); //####
    ODL_S2s("utilityDescription = ", utilityDescription, "utilityExample = ", utilityExample); //####
    ODL_S1("copyrightHolder = ", copyrightHolder); //####
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
    Option_::Descriptor         configDescriptor{StaticCast(unsigned int, OptionIndex::kOptionCONFIG), 0, "c", "config",
                                                    Option_::Arg::Required,
                                                    T_("  --config, -c <path> \tSpecify path to configuration file")};
    Option_::Descriptor         describeDescriptor{StaticCast(unsigned int, OptionIndex::kOptionDESCRIBE), 0, "d", "describe", Option_::Arg::None,
                                                    T_("  --describe, -d \tPrint type and description and exit")};
    Option_::Descriptor         expandedDescriptor{StaticCast(unsigned int, OptionIndex::kOptionEXPANDED), 0, "e",
                                                    "expanded", Option_::Arg::None, T_("  --expanded, -e \tDisplay more details")};
    Option_::Descriptor         helpDescriptor{StaticCast(unsigned int, OptionIndex::kOptionHELP), 0, "h", "help",
                                                Option_::Arg::None, T_("  --help, -h  \tPrint usage and exit")};
    Option_::Descriptor         jsonDescriptor{StaticCast(unsigned int, OptionIndex::kOptionJSON), 0, "j", "json",
                                                Option_::Arg::None,
                                                T_("  --json, -j \tGenerate output in JSON format")};
    Option_::Descriptor         logDescriptor{StaticCast(unsigned int, OptionIndex::kOptionLOG), 0, "l",
                                                "log", Option_::Arg::None, T_("  --log, -l \tLog application")};
    Option_::Descriptor         machineDescriptor{StaticCast(unsigned int, OptionIndex::kOptionMACHINE), 0, "m", "machine",
                                                    Option_::Arg::Required,
                                                    T_("  --machine, -m <name> \tSpecify machine to be referenced")};
    Option_::Descriptor         tabsDescriptor{StaticCast(unsigned int, OptionIndex::kOptionTABS), 0, "t", "tabs",
                                                Option_::Arg::None,
                                                T_("  --tabs, -t \tGenerate output in tab-format")};
    Option_::Descriptor         versionDescriptor{StaticCast(unsigned int, OptionIndex::kOptionVERSION), 0, "v",
                                                    "version", Option_::Arg::None,
                                                    T_("  --version, -v \tPrint version information and exit")};
    Option_::Descriptor         lastDescriptor{0, 0, nullptr, nullptr, nullptr, nullptr};
    Option_::Descriptor         usage[11]; // first, config, describe, expanded, help, json, log, machine, tabs, version, last
    Ptr(Option_::Descriptor)    usageWalker{usage};
    int                         argcWork = argc;
    Ptr(Ptr(char))              argvWork{argv};
    std::string                 usageString{"USAGE: "};
    std::string                 argList{ArgumentsToArgString(argumentDescriptions)};

    usageString += *argv;
    usageString += " [options]";
    if (0 < argList.length())
    {
        usageString += " " + argList;
    }
    if (0 < utilityDescription.length())
    {
        usageString += "\n" + utilityDescription;
    }
    if (0 < utilityExample.length())
    {
        usageString += "\n\nExample: " + utilityExample;
    }
    if (0 < argList.length())
    {
        StringVector    descriptions;

        ArgumentsToDescriptionArray(argumentDescriptions, descriptions);
        usageString += "\n\n";
        for (size_t ii = 0, mm = descriptions.size(); mm > ii; ++ii)
        {
            if (0 < ii)
            {
                usageString += "\n";
            }
            usageString += "  " + descriptions[ii];
        }
    }
    usageString += "\n\nOptions:";
#if MAC_OR_LINUX_
    firstDescriptor.help = strdup(usageString.c_str());
#else // ! MAC_OR_LINUX_
    firstDescriptor.help = _strdup(usageString.c_str());
#endif // ! MAC_OR_LINUX_
    memcpy(usageWalker++, &firstDescriptor, sizeof(firstDescriptor));
    if (0 == (kSkipConfigFileOption & optionsToIgnore))
    {
        memcpy(usageWalker++, &configDescriptor, sizeof(configDescriptor));
    }
    memcpy(usageWalker++, &describeDescriptor, sizeof(describeDescriptor));
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
    Option_::Stats                      stats{usage, argcWork, argvWork};
    std::unique_ptr<Option_::Option[]>  options{new Option_::Option[stats.options_max]};
    std::unique_ptr<Option_::Option[]>  buffer{new Option_::Option[stats.buffer_max]};
    Option_::Parser                     parse{usage, argcWork, argvWork, options.get(), buffer.get(), 1};
    std::string                         badArgs;

    if (parse.error())
    {
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if ((nullptr != options[StaticCast(size_t, OptionIndex::kOptionHELP)]) ||
             (nullptr != options[StaticCast(size_t, OptionIndex::kOptionUNKNOWN)]))
    {
        Option_::printUsage(std::cout, usage, HELP_LINE_LENGTH_);
        if (nullptr != helper)
        {
            helper(std::cout);
        }
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionVERSION)])
    {
        std::string nImOversionString{SanitizeString(nImO_VERSION_, true)};

        std::cout << "Version " << nImOversionString << ": Copyright (c) " << year << " by " <<
                    copyrightHolder << "." << std::endl;
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionDESCRIBE)])
    {
        std::cout << "Utility\t" << utilityDescription << std::endl;
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (ProcessArguments(argumentDescriptions, parse, badArgs))
    {
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionJSON)])
        {
            optionValues._flavour = OutputFlavour::kFlavourJSON;
        }
        else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionTABS)])
        {
            optionValues._flavour = OutputFlavour::kFlavourTabs;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionEXPANDED)])
        {
            optionValues._expanded = true;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionLOG)])
        {
            optionValues._logging = true;
        }
        Ptr(Option_::Option)    configOption{options[StaticCast(size_t, OptionIndex::kOptionCONFIG)]};

        if ((0 == (kSkipConfigFileOption & optionsToIgnore)) && (nullptr != configOption) && (nullptr != configOption->arg))
        {
            optionValues._configFilePath = configOption->arg;
        }
        Ptr(Option_::Option)    machineOption{options[StaticCast(size_t, OptionIndex::kOptionMACHINE)]};

        if ((0 == (kSkipMachineOption & optionsToIgnore)) && (nullptr != machineOption) && (nullptr != machineOption->arg))
        {
            optionValues._machine = machineOption->arg;
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
        std::cout << "One or more invalid or missing arguments (" << badArgs << ")." << std::endl;
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    ODL_EXIT_B(keepGoing); //####
    return keepGoing;
} // nImO::ProcessStandardOptions

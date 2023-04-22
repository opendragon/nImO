//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOserviceOptions.cpp
//
//  Project:    nImO
//
//  Contains:   The function and class definitions for service command-line options used with nImO.
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

#include <nImOserviceOptions.h>

//#include <fstream>
//#include <initFile.h>
//#include <initFileObject.h>
#include <nImObaseArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The function and variable definitions for service command-line options used with nImO. */
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

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

bool
nImO::ProcessServiceOptions
    (const int              argc,
     Ptr(Ptr(char))         argv,
     DescriptorVector &     argumentDescriptions,
     const std::string &    serviceDescription,
     const std::string &    matchingCriteria,
     const int              year,
     CPtr(char)             copyrightHolder,
     ServiceOptions &       optionValues,
     const OptionsMask      skipOptions,
     Ptr(StringVector)      arguments)
{
    ODL_ENTER(); //####
    ODL_I3("argc = ", argc, "year = ", year, "skipOptions = ", StaticCast(int64_t, skipOptions)); //####
    ODL_P4("argv = ", argv, "argumentDescriptions = ", &argumentDescriptions, "optionValues = ", &optionValues, "arguments = ", arguments); //####
    ODL_S2s("serviceDescription = ", serviceDescription, "matchingCriteria = ", matchingCriteria); //####
    ODL_S1("copyrightHolder = ", copyrightHolder); //####
    enum class OptionIndex
    {
        kOptionUNKNOWN,
        kOptionARGS,
        kOptionCHANNEL,
        kOptionCONFIG,
        kOptionDETAIL,
        kOptionENDPOINT,
        kOptionGO,
        kOptionHELP,
        kOptionINFO,
        kOptionLOG,
        kOptionMOD,
        kOptionNODE,
        kOptionPORT,
        kOptionREPORT,
        kOptionTAG,
        kOptionVERSION
    }; // OptionIndex

    bool        isAdapter = (0 < matchingCriteria.length());
    bool        keepGoing = true;
    std::string serviceKindName(isAdapter ? "adapter" : "service");
    std::string goPartText("  --go, -g \tStart the ");
    std::string infoPartText("  --info, -i \tPrint executable type, supported ");
    std::string reportPartText("  --report, -r \tReport the ");
    std::string tagPartText("  --tag, -t \tSpecify the tag to be used as part of the ");

    goPartText += serviceKindName + " immediately";
    infoPartText += serviceKindName + " options";
    if (isAdapter)
    {
        infoPartText += ", matching criteria";
    }
    infoPartText += " and description and exit";
    reportPartText += serviceKindName + " metrics when the application exits";
    tagPartText += serviceKindName + " name";
    Option_::Descriptor firstDescriptor{StaticCast(unsigned int, OptionIndex::kOptionUNKNOWN), 0, "", "", Option_::Arg::None, NULL};
    Option_::Descriptor argsDescriptor{StaticCast(unsigned int, OptionIndex::kOptionARGS), 0, "a", "args", Option_::Arg::None,
                                        T_("  --args, -a \tReport the argument formats")};
    Option_::Descriptor channelDescriptor{StaticCast(unsigned int, OptionIndex::kOptionCHANNEL), 0, "d", "channel", Option_::Arg::None,
                                            T_("  --channel, -d \tReport the actual endpoint name")};
    Option_::Descriptor configDescriptor{StaticCast(unsigned int, OptionIndex::kOptionCONFIG), 0, "c", "config", Option_::Arg::Optional,
                                            T_("  --config, -c <path> \tSpecify path to configuration file")};
    Option_::Descriptor         detailDescriptor{StaticCast(unsigned int, OptionIndex::kOptionDETAIL), 0, "x",
                                                "detail", Option_::Arg::None, T_("  --detail, -x \tDisplay more details")};
    Option_::Descriptor endpointDescriptor{StaticCast(unsigned int, OptionIndex::kOptionENDPOINT), 0, "e", "endpoint", Option_::Arg::Required,
                                            T_("  --endpoint, -e \tSpecify an alternative endpoint name to be used")};
    Option_::Descriptor goDescriptor{StaticCast(unsigned int, OptionIndex::kOptionGO), 0, "g", "go", Option_::Arg::None, goPartText.c_str()};
    Option_::Descriptor helpDescriptor{StaticCast(unsigned int, OptionIndex::kOptionHELP), 0, "h", "help", Option_::Arg::None,
                                        T_("  --help, -h \tPrint usage and exit")};
    Option_::Descriptor infoDescriptor{StaticCast(unsigned int, OptionIndex::kOptionINFO), 0, "i", "info", Option_::Arg::None, infoPartText.c_str()};
    Option_::Descriptor logDescriptor{StaticCast(unsigned int, OptionIndex::kOptionLOG), 0, "l", "log", Option_::Arg::None,
                                        T_("  --log, -l \tLog application")};
    Option_::Descriptor modDescriptor{StaticCast(unsigned int, OptionIndex::kOptionMOD), 0, "m", "mod", Option_::Arg::Required,
                                        T_("  --mod, -m \tUse the IP address as a modifier for the tag")};
    Option_::Descriptor nodeDescriptor{StaticCast(unsigned int, OptionIndex::kOptionNODE), 0, "n", "node", Option_::Arg::Required,
                                        T_("  --node, -n \tSpecify a non-default node name to be used")};
    Option_::Descriptor portDescriptor{StaticCast(unsigned int, OptionIndex::kOptionPORT), 0, "p", "port", Option_::Arg::Required,
                                        T_("  --port, -p \tSpecify a non-default port to be used")};
    Option_::Descriptor reportDescriptor{StaticCast(unsigned int, OptionIndex::kOptionREPORT), 0, "r", "report", Option_::Arg::None,
                                            reportPartText.c_str()};
    Option_::Descriptor tagDescriptor{StaticCast(unsigned int, OptionIndex::kOptionTAG), 0, "t", "tag",Option_::Arg::Required, tagPartText.c_str()};
    Option_::Descriptor versionDescriptor{StaticCast(unsigned int, OptionIndex::kOptionVERSION), 0, "v", "vers", Option_::Arg::None,
                                            T_("  --vers, -v \tPrint version information and exit")};
    Option_::Descriptor lastDescriptor{0, 0, nullptr, nullptr, nullptr, nullptr};
    int                 argcWork = argc;
    Ptr(Ptr(char))      argvWork = argv;
    std::string         usageString("USAGE: ");
    std::string         argList{ArgumentsToArgString(argumentDescriptions)};

    if (nullptr != arguments)
    {
        arguments->clear();
    }
    usageString += *argv;
    usageString += " [options]";
    if (0 < argList.length())
    {
        StringVector    descriptions;

        ArgumentsToDescriptionArray(argumentDescriptions, descriptions, 2);
        usageString += " ";
        usageString += argList + "\n\n";
        for (size_t ii = 0, mm = descriptions.size(); mm > ii; ++ii)
        {
            if (0 < ii)
            {
                usageString += "\n";
            }
            usageString += "  ";
            usageString += descriptions[ii];
        }
    }
    usageString += "\n\nOptions:";
    // firstDescriptor, helpDescriptor, versionDescriptor, lastDescriptor
    size_t descriptorCount = 4;

    if (0 == (skipOptions & kSkipArgsOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipChannelOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipConfigFileOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipDetailOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipEndpointOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipGoOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipInfoOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipLoggingOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipModOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipNodeOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipPortOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipReportOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipTagOption))
    {
        ++descriptorCount;
    }
    Ptr(Option_::Descriptor)    usage = new Option_::Descriptor[descriptorCount];
    Ptr(Option_::Descriptor)    usageWalker = usage;

#if MAC_OR_LINUX_
    firstDescriptor.help = strdup(usageString.c_str());
#else // ! MAC_OR_LINUX_
    firstDescriptor.help = _strdup(usageString.c_str());
#endif // ! MAC_OR_LINUX_
    memcpy(usageWalker++, &firstDescriptor, sizeof(firstDescriptor));
    if (0 == (skipOptions & kSkipArgsOption))
    {
        memcpy(usageWalker++, &argsDescriptor, sizeof(argsDescriptor));
    }
    if (0 == (skipOptions & kSkipChannelOption))
    {
        memcpy(usageWalker++, &channelDescriptor, sizeof(channelDescriptor));
    }
    if (0 == (skipOptions & kSkipConfigFileOption))
    {
        memcpy(usageWalker++, &configDescriptor, sizeof(configDescriptor));
    }
    if (0 == (skipOptions & kSkipDetailOption))
    {
        memcpy(usageWalker++, &detailDescriptor, sizeof(detailDescriptor));
    }
    if (0 == (skipOptions & kSkipEndpointOption))
    {
        memcpy(usageWalker++, &endpointDescriptor, sizeof(endpointDescriptor));
    }
    if (0 == (skipOptions & kSkipGoOption))
    {
        memcpy(usageWalker++, &goDescriptor, sizeof(goDescriptor));
    }
    memcpy(usageWalker++, &helpDescriptor, sizeof(helpDescriptor));
    if (0 == (skipOptions & kSkipInfoOption))
    {
        memcpy(usageWalker++, &infoDescriptor, sizeof(infoDescriptor));
    }
    if (0 == (skipOptions & kSkipLoggingOption))
    {
        memcpy(usageWalker++, &logDescriptor, sizeof(logDescriptor));
    }
    if (0 == (skipOptions & kSkipModOption))
    {
        memcpy(usageWalker++, &modDescriptor, sizeof(modDescriptor));
    }
    if (0 == (skipOptions & kSkipNodeOption))
    {
        memcpy(usageWalker++, &nodeDescriptor, sizeof(nodeDescriptor));
    }
    if (0 == (skipOptions & kSkipPortOption))
    {
        memcpy(usageWalker++, &portDescriptor, sizeof(portDescriptor));
    }
    if (0 == (skipOptions & kSkipReportOption))
    {
        memcpy(usageWalker++, &reportDescriptor, sizeof(reportDescriptor));
    }
    if (0 == (skipOptions & kSkipTagOption))
    {
        memcpy(usageWalker++, &tagDescriptor, sizeof(tagDescriptor));
    }
    memcpy(usageWalker++, &versionDescriptor, sizeof(versionDescriptor));
    memcpy(usageWalker++, &lastDescriptor, sizeof(lastDescriptor));
    argcWork -= (argc > 0);
    argvWork += (argc > 0); // skip program name argv[0] if present
    Option_::Stats          stats(usage, argcWork, argvWork);
    Ptr(Option_::Option)    options = new Option_::Option[stats.options_max];
    Ptr(Option_::Option)    buffer = new Option_::Option[stats.buffer_max];
    Option_::Parser         parse(usage, argcWork, argvWork, options, buffer, 1);
    std::string             badArgs;

    if (parse.error())
    {
        ODL_LOG("(parse.error())"); //####
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if ((nullptr != options[StaticCast(size_t, OptionIndex::kOptionHELP)]) ||
             (nullptr != options[StaticCast(size_t, OptionIndex::kOptionUNKNOWN)]))
    {
        Option_::printUsage(std::cout, usage, HELP_LINE_LENGTH_);
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionVERSION)])
    {
        std::cout << "Version " << SanitizeString(nImO_VERSION_, true) << ": Copyright (c) " << year << " by " << copyrightHolder << "." << std::endl;
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionARGS)])
    {
        for (size_t ii = 0, mm = argumentDescriptions.size(); mm > ii; ++ii)
        {
            Ptr(nImO::BaseArgumentDescriptor)   anArg = argumentDescriptions[ii];

            if (0 < ii)
            {
                std::cout << ARGUMENT_SEPARATOR_;
            }
            if (anArg)
            {
                std::cout << anArg->toString().c_str();
            }
        }
        std::cout << std::endl;
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionINFO)])
    {
        bool    needTab = true;

        // Note that we don't report the 'h' and 'v' options, as they are not involved in
        // determining what choices to offer when launching a service.
        std::cout << (isAdapter ? "Adapter" : "Service");
        if (0 == (skipOptions & kSkipArgsOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "a";
        }
        if (0 == (skipOptions & kSkipConfigFileOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "c";
        }
        if (0 == (skipOptions & kSkipChannelOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "d";
        }
        if (0 == (skipOptions & kSkipDetailOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "x";
        }
        if (0 == (skipOptions & kSkipEndpointOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "e";
        }
        if (0 == (skipOptions & kSkipGoOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "g";
        }
        if (0 == (skipOptions & kSkipInfoOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "i";
        }
        if (0 == (skipOptions & kSkipLoggingOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "l";
        }
        if (0 == (skipOptions & kSkipModOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "m";
        }
        if (0 == (skipOptions & kSkipNodeOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "n";
        }
        if (0 == (skipOptions & kSkipPortOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "p";
        }
        if (0 == (skipOptions & kSkipReportOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "r";
        }
        if (0 == (skipOptions & kSkipTagOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "t";
        }
        if (needTab)
        {
            std::cout << "\t";
        }
        std::cout << "\t" << matchingCriteria << "\t" << serviceDescription << std::endl;
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (ProcessArguments(argumentDescriptions, parse, badArgs))
    {
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionGO)])
        {
            optionValues._goWasSet = true;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionCHANNEL)])
        {
            optionValues._reportEndpoint = true;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionMOD)])
        {
            std::string modArg = options[StaticCast(size_t, OptionIndex::kOptionMOD)].arg;

            if (0 < modArg.length())
            {
                CPtr(char)  startPtr = modArg.c_str();
                Ptr(char)   endPtr;
                int         numBytes = static_cast<int>(strtol(startPtr, &endPtr, 10));

                if ((startPtr != endPtr) && ('\0' == *endPtr))
                {
                    switch (numBytes)
                    {
                        case 0 :
                            optionValues._modFlag = kModificationNone;
                            break;

                        case 1 :
                            optionValues._modFlag = kModificationBottomByte;
                            break;

                        case 2 :
                            optionValues._modFlag = kModificationBottomTwoBytes;
                            break;

                        case 3 :
                            optionValues._modFlag = kModificationBottomThreeBytes;
                            break;

                        case 4 :
                            optionValues._modFlag = kModificationAllBytes;
                            break;

                        default :
                            break;

                    }
                }
            }
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionLOG)])
        {
            optionValues._logging = true;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionDETAIL)])
        {
            optionValues._detailed = true;
        }
        Ptr(Option_::Option)    configOption{options[StaticCast(size_t, OptionIndex::kOptionCONFIG)]};

        if ((0 == (kSkipConfigFileOption & kSkipConfigFileOption)) && (nullptr != configOption) && (nullptr != configOption->arg))
        {
            optionValues._configFilePath = configOption->arg;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionNODE)])
        {
            optionValues._node = options[StaticCast(size_t, OptionIndex::kOptionNODE)].arg;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionENDPOINT)])
        {
            optionValues._serviceEndpointName = options[StaticCast(size_t, OptionIndex::kOptionENDPOINT)].arg;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionPORT)])
        {
            optionValues._servicePortNumber = options[StaticCast(size_t, OptionIndex::kOptionPORT)].arg;
            if (0 < optionValues._servicePortNumber.length())
            {
                CPtr(char)  startPtr = optionValues._servicePortNumber.c_str();
                Ptr(char)   endPtr;
                int         aPort = StaticCast(int, strtol(startPtr, &endPtr, 10));

                if ((startPtr == endPtr) || ('\0' != *endPtr) || (! ValidPortNumber(aPort)))
                {
                    std::cout << "Bad port number." << std::endl;
                    keepGoing = false;
                    ODL_B1("keepGoing <- ", keepGoing); //####
                }
            }
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionTAG)])
        {
            optionValues._tag = options[StaticCast(size_t, OptionIndex::kOptionTAG)].arg;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionREPORT)])
        {
            optionValues._reportOnExit = true;
        }
        if (nullptr != arguments)
        {
            for (int ii = 0; ii < parse.nonOptionsCount(); ++ii)
            {
                arguments->push_back(parse.nonOption(ii));
            }
        }
    }
    else
    {
        std::cout << "One or more invalid or missing arguments (" << badArgs << ")." << std::endl;
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    delete[] options;
    delete[] buffer;
    free(ConstCast(Ptr(char), firstDescriptor.help));
    delete[] usage;
    ODL_EXIT_B(keepGoing); //####
    return keepGoing;
} // nImO::ProcessServiceOptions

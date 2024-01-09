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

#include <ArgumentDescriptors/nImObaseArgumentDescriptor.h>

#include <string>

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
     const std::string &    copyrightHolder,
     ServiceOptions &       optionValues,
     const OptionsMask      skipOptions,
     const bool             multipleInputs,
     const bool             multipleOutputs,
     Ptr(StringVector)      arguments)
{
    ODL_ENTER(); //####
    ODL_I2("argc = ", argc, "year = ", year); //####
    ODL_P4("argv = ", argv, "argumentDescriptions = ", &argumentDescriptions, "optionValues = ", &optionValues, "arguments = ", arguments); //####
    ODL_S3s("serviceDescription = ", serviceDescription, "matchingCriteria = ", matchingCriteria, "copyrightHolder = ", copyrightHolder); //####
    ODL_X1("skipOptions = ", StaticCast(int64_t, skipOptions)); //####
    ODL_B2("multipleInputs = ", multipleInputs, "multipleOutputs = ", multipleOutputs); //####
    enum class OptionIndex
    {
        kOptionUNKNOWN,
        kOptionARGS,
        kOptionBASE,
        kOptionCONFIG,
        kOptionDESCRIBE,
        kOptionEXPANDED,
        kOptionHELP,
        kOptionINTYPE,
        kOptionLOG,
        kOptionNODE,
        kOptionOUTTYPE,
        kOptionTAG,
        kOptionVERSION
    }; // OptionIndex

    bool    isAdapter{! matchingCriteria.empty()};
    bool    keepGoing{true};
    auto    serviceKindName{isAdapter ? "adapter"s : "service"s};
    auto    describePartText{"  --describe, -d \tPrint executable type, supported "s};
    auto    tagPartText{"  --tag, -t <tag> \tSpecify the tag to be used as part of the "s};

    describePartText += serviceKindName + " options"s;
    if (isAdapter)
    {
        describePartText += ", matching criteria"s;
    }
    describePartText += " and description and exit"s;
    tagPartText += serviceKindName + " name"s;
    Option_::Descriptor firstDescriptor{StaticCast(unsigned int, OptionIndex::kOptionUNKNOWN), 0, "", "", Option_::Arg::None, NULL};
    Option_::Descriptor argsDescriptor{StaticCast(unsigned int, OptionIndex::kOptionARGS), 0, "a", "args", Option_::Arg::None,
                                        "  --args, -a \tReport the argument formats"};
    Option_::Descriptor baseDescriptor{StaticCast(unsigned int, OptionIndex::kOptionBASE), 0, "b", "base", Option_::Arg::Required,
                                            "  --base, -b <name> \tSpecifies the base name for channels"};
    Option_::Descriptor configDescriptor{StaticCast(unsigned int, OptionIndex::kOptionCONFIG), 0, "c", "config", Option_::Arg::Optional,
                                            "  --config, -c <path> \tSpecify path to configuration file"};
    Option_::Descriptor describeDescriptor{StaticCast(unsigned int, OptionIndex::kOptionDESCRIBE), 0, "d", "describe", Option_::Arg::None,
                                            describePartText.c_str()};
    Option_::Descriptor expandedDescriptor{StaticCast(unsigned int, OptionIndex::kOptionEXPANDED), 0, "e",
                                            "expanded", Option_::Arg::None, "  --expanded, -e \tDisplay more details"};
    Option_::Descriptor helpDescriptor{StaticCast(unsigned int, OptionIndex::kOptionHELP), 0, "h", "help", Option_::Arg::None,
                                        "  --help, -h \tPrint usage and exit"};
    Option_::Descriptor inTypeDescriptor1{StaticCast(unsigned int, OptionIndex::kOptionINTYPE), 0, "i", "intype", Option_::Arg::Required,
                                            "  --intype, -i <type> \tSpecifies the data type for the input channel"};
    Option_::Descriptor inTypeDescriptor2{StaticCast(unsigned int, OptionIndex::kOptionINTYPE), 0, "i", "intype", Option_::Arg::Required,
                                            "  --intype, -i <type> \tSpecifies the data type for input channels"};
    Option_::Descriptor logDescriptor{StaticCast(unsigned int, OptionIndex::kOptionLOG), 0, "l", "log", Option_::Arg::None,
                                        "  --log, -l \tLog application"};
    Option_::Descriptor nodeDescriptor{StaticCast(unsigned int, OptionIndex::kOptionNODE), 0, "n", "node", Option_::Arg::Required,
                                        "  --node, -n <name> \tSpecify a non-default node name to be used"};
    Option_::Descriptor outTypeDescriptor1{StaticCast(unsigned int, OptionIndex::kOptionOUTTYPE), 0, "o", "outtype", Option_::Arg::Required,
                                            "  --outtype, -o <type> \tSpecifies the data type for the output channel"};
    Option_::Descriptor outTypeDescriptor2{StaticCast(unsigned int, OptionIndex::kOptionOUTTYPE), 0, "o", "outtype", Option_::Arg::Required,
                                            "  --outtype, -o <type> \tSpecifies the data type for output channels"};
    Option_::Descriptor tagDescriptor{StaticCast(unsigned int, OptionIndex::kOptionTAG), 0, "t", "tag",Option_::Arg::Required, tagPartText.c_str()};
    Option_::Descriptor versionDescriptor{StaticCast(unsigned int, OptionIndex::kOptionVERSION), 0, "v", "version", Option_::Arg::None,
                                            "  --version, -v \tPrint version information and exit"};
    Option_::Descriptor lastDescriptor{0, 0, nullptr, nullptr, nullptr, nullptr};
    int                 argcWork{argc};
    Ptr(Ptr(char))      argvWork{argv};
    auto                usageString{"USAGE: "s};
    auto                argList{ArgumentsToArgString(argumentDescriptions)};

    if (nullptr != arguments)
    {
        arguments->clear();
    }
    usageString += *argv;
    usageString += " [options]"s;
    if (! argList.empty())
    {
        StringVector    descriptions;

        ArgumentsToDescriptionArray(argumentDescriptions, descriptions, 2);
        usageString += " "s + argList + "\n\n"s;
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
    // firstDescriptor, helpDescriptor, versionDescriptor, lastDescriptor
    size_t descriptorCount{4};

    if (0 == (skipOptions & kSkipArgsOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipBaseOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipConfigFileOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipDescribeOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipExpandedOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipInTypeOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipLoggingOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipNodeOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipOutTypeOption))
    {
        ++descriptorCount;
    }
    if (0 == (skipOptions & kSkipTagOption))
    {
        ++descriptorCount;
    }
    Ptr(Option_::Descriptor)    usage{new Option_::Descriptor[descriptorCount]};
    Ptr(Option_::Descriptor)    usageWalker{usage};

#if MAC_OR_LINUX_
    firstDescriptor.help = strdup(usageString.c_str());
#else // not MAC_OR_LINUX_
    firstDescriptor.help = _strdup(usageString.c_str());
#endif // not MAC_OR_LINUX_
    memcpy(usageWalker++, &firstDescriptor, sizeof(firstDescriptor));
    if (0 == (skipOptions & kSkipArgsOption))
    {
        memcpy(usageWalker++, &argsDescriptor, sizeof(argsDescriptor));
    }
    if (0 == (skipOptions & kSkipBaseOption))
    {
        memcpy(usageWalker++, &baseDescriptor, sizeof(baseDescriptor));
    }
    if (0 == (skipOptions & kSkipConfigFileOption))
    {
        memcpy(usageWalker++, &configDescriptor, sizeof(configDescriptor));
    }
    if (0 == (skipOptions & kSkipDescribeOption))
    {
        memcpy(usageWalker++, &describeDescriptor, sizeof(describeDescriptor));
    }
    if (0 == (skipOptions & kSkipExpandedOption))
    {
        memcpy(usageWalker++, &expandedDescriptor, sizeof(expandedDescriptor));
    }
    memcpy(usageWalker++, &helpDescriptor, sizeof(helpDescriptor));
    if (0 == (skipOptions & kSkipInTypeOption))
    {
        if (multipleInputs)
        {
            memcpy(usageWalker++, &inTypeDescriptor2, sizeof(inTypeDescriptor2));
        }
        else
        {
            memcpy(usageWalker++, &inTypeDescriptor1, sizeof(inTypeDescriptor1));
        }
    }
    if (0 == (skipOptions & kSkipLoggingOption))
    {
        memcpy(usageWalker++, &logDescriptor, sizeof(logDescriptor));
    }
    if (0 == (skipOptions & kSkipNodeOption))
    {
        memcpy(usageWalker++, &nodeDescriptor, sizeof(nodeDescriptor));
    }
    if (0 == (skipOptions & kSkipOutTypeOption))
    {
        if (multipleOutputs)
        {
            memcpy(usageWalker++, &outTypeDescriptor2, sizeof(outTypeDescriptor2));
        }
        else
        {
            memcpy(usageWalker++, &outTypeDescriptor1, sizeof(outTypeDescriptor1));
        }
    }
    if (0 == (skipOptions & kSkipTagOption))
    {
        memcpy(usageWalker++, &tagDescriptor, sizeof(tagDescriptor));
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
        ODL_LOG("(parse.error())"); //####
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if ((nullptr != options[StaticCast(size_t, OptionIndex::kOptionHELP)]) ||
             (nullptr != options[StaticCast(size_t, OptionIndex::kOptionUNKNOWN)]))
    {
        Option_::printUsage(std::cout, usage, kHelpLineLength);
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionARGS)])
    {
        for (size_t ii = 0, mm = argumentDescriptions.size(); mm > ii; ++ii)
        {
            Ptr(nImO::BaseArgumentDescriptor)   anArg{argumentDescriptions[ii]};

            if (0 < ii)
            {
                std::cout << kArgumentSeparator;
            }
            if (anArg)
            {
                std::cout << anArg->toString().c_str();
            }
        }
        std::cout << "\n";
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionVERSION)])
    {
        std::cout << "Version " << SanitizeString(nImO_VERSION_, true) << ": Copyright (c) " << year << " by " <<
                    copyrightHolder << ".\n";
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionDESCRIBE)])
    {
        bool    needTab{true};

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
        if (0 == (skipOptions & kSkipBaseOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "b";
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
        if (0 == (skipOptions & kSkipDescribeOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "d";
        }
        if (0 == (skipOptions & kSkipExpandedOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "e";
        }
        if (0 == (skipOptions & kSkipInTypeOption))
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
        if (0 == (skipOptions & kSkipNodeOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "n";
        }
        if (0 == (skipOptions & kSkipOutTypeOption))
        {
            if (needTab)
            {
                std::cout << "\t";
                needTab = false;
            }
            std::cout << "o";
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
        std::cout << "\t" << matchingCriteria << "\t" << serviceDescription << "\n";
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    else if (ProcessArguments(argumentDescriptions, parse, badArgs))
    {
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionEXPANDED)])
        {
            optionValues._expanded = true;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionLOG)])
        {
            optionValues._logging = true;
        }
        if ((0 == (skipOptions & kSkipBaseOption)) && (nullptr != options[StaticCast(size_t, OptionIndex::kOptionBASE)]))
        {
            optionValues._base = options[StaticCast(size_t, OptionIndex::kOptionBASE)].arg;
        }
        Ptr(Option_::Option)    configOption{options[StaticCast(size_t, OptionIndex::kOptionCONFIG)]};

        if ((0 == (skipOptions & kSkipConfigFileOption)) && (nullptr != configOption) && (nullptr != configOption->arg))
        {
            optionValues._configFilePath = configOption->arg;
        }
        if ((0 == (skipOptions & kSkipInTypeOption)) && (nullptr != options[StaticCast(size_t, OptionIndex::kOptionINTYPE)]))
        {
            optionValues._inType = options[StaticCast(size_t, OptionIndex::kOptionINTYPE)].arg;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionNODE)])
        {
            optionValues._node = options[StaticCast(size_t, OptionIndex::kOptionNODE)].arg;
        }
        if ((0 == (skipOptions & kSkipOutTypeOption)) && (nullptr != options[StaticCast(size_t, OptionIndex::kOptionOUTTYPE)]))
        {
            optionValues._outType = options[StaticCast(size_t, OptionIndex::kOptionOUTTYPE)].arg;
        }
        if (nullptr != options[StaticCast(size_t, OptionIndex::kOptionTAG)])
        {
            optionValues._tag = options[StaticCast(size_t, OptionIndex::kOptionTAG)].arg;
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
        std::cout << "One or more invalid or missing arguments (" << badArgs << ").\n";
        keepGoing = false;
        ODL_B1("keepGoing <- ", keepGoing); //####
    }
    free(ConstCast(Ptr(char), firstDescriptor.help));
    delete[] usage;
    ODL_EXIT_B(keepGoing); //####
    return keepGoing;
} // nImO::ProcessServiceOptions

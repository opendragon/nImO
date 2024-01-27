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
     const int              year,
     const std::string &    copyrightHolder,
     ServiceOptions &       optionValues,
     const OptionsMask      skipOptions,
     const bool             multipleInputs,
     const bool             multipleOutputs,
     Ptr(StdStringVector)   arguments)
{
    ODL_ENTER(); //####
    ODL_I2("argc = ", argc, "year = ", year); //####
    ODL_P4("argv = ", argv, "argumentDescriptions = ", &argumentDescriptions, "optionValues = ", &optionValues, "arguments = ", arguments); //####
    ODL_S2s("serviceDescription = ", serviceDescription, "copyrightHolder = ", copyrightHolder); //####
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
        kOptionVERSION,
        kOptionWAIT
    }; // OptionIndex

    bool                keepGoing{true};
    Option_::Descriptor firstDescriptor{StaticCast(unsigned int, OptionIndex::kOptionUNKNOWN), 0, "", "", Option_::Arg::None, NULL};
    auto                argsHelpString{"  "s + MakeOption("a"s, "args"s) + " \tReport the argument formats"s};
    Option_::Descriptor argsDescriptor{StaticCast(unsigned int, OptionIndex::kOptionARGS), 0, "a", "args", Option_::Arg::None,
                                        argsHelpString.c_str()};
    auto                baseHelpString{"  "s + MakeOption("b"s, "base"s) + " <name> \tSpecifies the base name for channels"s};
    Option_::Descriptor baseDescriptor{StaticCast(unsigned int, OptionIndex::kOptionBASE), 0, "b", "base", Option_::Arg::Required,
                                        baseHelpString.c_str()};
    auto                configHelpString{"  "s + MakeOption("c"s, "config"s) + " <path> \tSpecify path to configuration file"s};
    Option_::Descriptor configDescriptor{StaticCast(unsigned int, OptionIndex::kOptionCONFIG), 0, "c", "config", Option_::Arg::Optional,
                                            configHelpString.c_str()};
    auto                describeHelpString{"  "s + MakeOption("d"s, "describe"s) +
                                            " \tPrint executable type, supported service options and description and exit"s};
    Option_::Descriptor describeDescriptor{StaticCast(unsigned int, OptionIndex::kOptionDESCRIBE), 0, "d", "describe", Option_::Arg::None,
                                            describeHelpString.c_str()};
    auto                expandedHelpString{"  "s + MakeOption("e"s, "expanded"s) + " \tDisplay more details"s};
    Option_::Descriptor expandedDescriptor{StaticCast(unsigned int, OptionIndex::kOptionEXPANDED), 0, "e",
                                            "expanded", Option_::Arg::None, expandedHelpString.c_str()};
    auto                helpHelpString{"  "s + MakeOption("h"s, "help"s) + " \tPrint usage and exit"s};
    Option_::Descriptor helpDescriptor{StaticCast(unsigned int, OptionIndex::kOptionHELP), 0, "h", "help", Option_::Arg::None,
                                        helpHelpString.c_str()};
    auto                inTypeHelpString1{"  "s + MakeOption("i"s, "intype"s) + " <type> \tSpecifies the data type for the input channel"s};
    Option_::Descriptor inTypeDescriptor1{StaticCast(unsigned int, OptionIndex::kOptionINTYPE), 0, "i", "intype", Option_::Arg::Required,
                                            inTypeHelpString1.c_str()};
    auto                inTypeHelpString2{"  "s + MakeOption("i"s, "intype"s) + " <type> \tSpecifies the data type for input channels"s};
    Option_::Descriptor inTypeDescriptor2{StaticCast(unsigned int, OptionIndex::kOptionINTYPE), 0, "i", "intype", Option_::Arg::Required,
                                            inTypeHelpString2.c_str()};
    auto                logHelpString{"  "s + MakeOption("l"s, "log"s) + " \tLog application"s};
    Option_::Descriptor logDescriptor{StaticCast(unsigned int, OptionIndex::kOptionLOG), 0, "l", "log", Option_::Arg::None,
                                        logHelpString.c_str()};
    auto                nodeHelpString{"  "s + MakeOption("n"s, "node"s) + " <name> \tSpecify a non-default node name to be used"s};
    Option_::Descriptor nodeDescriptor{StaticCast(unsigned int, OptionIndex::kOptionNODE), 0, "n", "node", Option_::Arg::Required,
                                        nodeHelpString.c_str()};
    auto                outTypeHelpString1{"  "s + MakeOption("o"s, "outtype"s) + " <type> \tSpecifies the data type for the output channel"s};
    Option_::Descriptor outTypeDescriptor1{StaticCast(unsigned int, OptionIndex::kOptionOUTTYPE), 0, "o", "outtype", Option_::Arg::Required,
                                            outTypeHelpString1.c_str()};
    auto                outTypeHelpString2{"  "s + MakeOption("o"s, "outtype"s) + " <type> \tSpecifies the data type for output channels"s};
    Option_::Descriptor outTypeDescriptor2{StaticCast(unsigned int, OptionIndex::kOptionOUTTYPE), 0, "o", "outtype", Option_::Arg::Required,
                                            outTypeHelpString2.c_str()};
    auto                tagHelpString{"  "s + MakeOption("t"s, "tag"s) + " <tag> \tSpecify the tag to be used as part of the service name"s};
    Option_::Descriptor tagDescriptor{StaticCast(unsigned int, OptionIndex::kOptionTAG), 0, "t", "tag",Option_::Arg::Required, tagHelpString.c_str()};
    auto                versionHelpString{"  "s + MakeOption("v"s, "version"s) + " \tPrint version information and exit"s};
    Option_::Descriptor versionDescriptor{StaticCast(unsigned int, OptionIndex::kOptionVERSION), 0, "v", "version", Option_::Arg::None,
                                            versionHelpString.c_str()};
    auto                waitHelpString{"  "s + MakeOption("w"s, "wait"s) + " \tWait for connection(s)"s};
    Option_::Descriptor waitDescriptor{StaticCast(unsigned int, OptionIndex::kOptionWAIT), 0, "w", "wait", Option_::Arg::None,
                                        waitHelpString.c_str()};
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
        StdStringVector descriptions;

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
    if (0 == (skipOptions & kSkipWaitOption))
    {
        ++descriptorCount;
    }
    Ptr(Option_::Descriptor)    usage{new Option_::Descriptor[descriptorCount]};
    Ptr(Option_::Descriptor)    usageWalker{usage};

#if MAC_OR_LINUX_OR_BSD_
    firstDescriptor.help = strdup(usageString.c_str());
#else // not MAC_OR_LINUX_OR_BSD_
    firstDescriptor.help = _strdup(usageString.c_str());
#endif // not MAC_OR_LINUX_OR_BSD_
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
    if (0 == (skipOptions & kSkipWaitOption))
    {
        memcpy(usageWalker++, &waitDescriptor, sizeof(waitDescriptor));
    }
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

            if (anArg)
            {
                std::cout << anArg->toString().c_str() << "\n";
            }
        }
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
        // Note that we don't report the 'd', 'h' and 'v' options, as they are not involved in
        // determining what choices to offer when launching a service.
        if (0 == (skipOptions & kSkipArgsOption))
        {
            std::cout << "a";
        }
        if (0 == (skipOptions & kSkipBaseOption))
        {
            std::cout << "b";
        }
        if (0 == (skipOptions & kSkipConfigFileOption))
        {
            std::cout << "c";
        }
        if (0 == (skipOptions & kSkipExpandedOption))
        {
            std::cout << "e";
        }
        if (0 == (skipOptions & kSkipInTypeOption))
        {
            std::cout << "i";
        }
        if (0 == (skipOptions & kSkipLoggingOption))
        {
            std::cout << "l";
        }
        if (0 == (skipOptions & kSkipNodeOption))
        {
            std::cout << "n";
        }
        if (0 == (skipOptions & kSkipOutTypeOption))
        {
            std::cout << "o";
        }
        if (0 == (skipOptions & kSkipTagOption))
        {
            std::cout << "t";
        }
        if (0 == (skipOptions & kSkipWaitOption))
        {
            std::cout << "w";
        }
        std::cout << "\t" << serviceDescription << "\n";
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
        if ((0 == (skipOptions & kSkipWaitOption)) && (nullptr != options[StaticCast(size_t, OptionIndex::kOptionWAIT)]))
        {
            optionValues._waitForConnections = true;
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

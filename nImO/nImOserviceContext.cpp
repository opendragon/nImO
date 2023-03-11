//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOserviceContext.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO execution contexts that use a command port.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2022 by OpenDragon.
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
//  Created:    2022-07-05
//
//--------------------------------------------------------------------------------------------------

#include "nImOserviceContext.h"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO execution contexts that use a command port. */
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
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::ServiceContext::ServiceContext
    (const std::string &    executableName,
     const std::string &    tag,
     const bool             logging,
     const ThreadMode       whichThreads,
     const std::string &    nodeName) :
        inherited(executableName, tag, logging, whichThreads, nodeName), _acceptor(*getService()), _keepGoing(true)
{
    ODL_ENTER(); //####
    //ODL_S3s("progName = ", executableName, "tag = ", tag, "nodeName = ", nodeName); //####
    //ODL_B1("logging = ", logging); //####
    try
    {
        createCommandPort();
        setCommandPort(_commandPort);
        if (waitForRegistry())
        {
            // TBD
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::ServiceContext::ServiceContext

nImO::ServiceContext::~ServiceContext
    (void)
{
    ODL_OBJENTER(); //####
    destroyCommandPort();
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::~ServiceContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::ServiceContext::createCommandPort
    (void)
{
    ODL_OBJENTER(); //####
    _acceptor.open(asio::ip::tcp::v4());
    _acceptor.listen();
    _commandPort = _acceptor.local_endpoint().port();
    Ptr(CommandSession) newSession = new CommandSession(*this);

    _acceptor.async_accept(newSession->getSocket(),
                           [this, newSession]
                           (const boost::system::error_code  ec)
                           {
                               handleAccept(newSession, ec);
                           });
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::createCommandPort

void
nImO::ServiceContext::destroyCommandPort
(void)
{
    ODL_OBJENTER(); //####
    _keepGoing = false;
    _acceptor.cancel();
    _acceptor.close();
    for (auto walker = _sessions.begin(); walker != _sessions.end(); ++walker)
    {
        Ptr(CommandSession) aSession = *walker;

        aSession->getSocket().cancel();
    }
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::destroyCommandPort

void
nImO::ServiceContext::handleAccept
    (Ptr(CommandSession)        newSession,
     const system::error_code & error)
{
    bool    releaseSession;

    ODL_OBJENTER(); //####
    if (0 == error.value())
    {
        if (_keepGoing)
        {
            releaseSession = false;
            newSession->start();
            newSession = new CommandSession(*this);
            _sessions.insert(newSession);
            _acceptor.async_accept(newSession->getSocket(),
                                   [this, newSession]
                                   (const system::error_code  ec)
                                   {
                                       handleAccept(newSession, ec);
                                   });
        }
        else
        {
            releaseSession = true;
        }
    }
    else
    {
        releaseSession = true;
    }
    if (releaseSession)
    {
        auto    found(_sessions.find(newSession));

        if (_sessions.end() != found)
        {
            _sessions.erase(found);
            delete newSession;
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::handleAccept

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

#if 0
bool
nImO::ProcessStandardUtilitiesOptions
    (const int              argc,
     Ptr(Ptr(char))         argv,
     DescriptorVector &     argumentDescriptions,
     const std::string &    utilityDescription,
     const std::string &    utilityExample,
     const int              year,
     CPtr(char)             copyrightHolder,
     StandardOptions &      optionValues,
     HelpFunction           helper,
     const OptionsMask      skipOptions,
     Ptr(StringVector)      arguments)
#endif//0
#if 0
bool
nImO::ProcessStandardServiceOptions
    (const int                      argc,
     Ptr(Ptr(char))                 argv,
     DescriptorVector &             argumentDescriptions,
     const std::string &            serviceDescription,
     //const YarpString &            matchingCriteria,//?
     const int                      year,
     CPtr(char)                     copyrightHolder,
     bool &                         goWasSet,
     bool &                         reportEndpoint,
     bool &                         reportOnExit,
StandardOptions &      optionValues,
     //YarpString &                  tag,
     //YarpString &                  serviceEndpointName,
     //YarpString &                  servicePortNumber,
     //AddressTagModifier &          modFlag,
     const OptionsMask              skipOptions,
     Ptr(StringVector)              arguments)
{
    ODL_ENTER(); //####
    ODL_I2("argc = ", argc, "year = ", year); //####
    ODL_P4("argv = ", argv, "argumentDescriptions = ", &argumentDescriptions, //####
           "reportEndpoint = ", &reportEndpoint, "reportOnExit = ", &reportOnExit); //####
    ODL_P2("modFlag = ", &modFlag, "arguments = ", arguments); //####
    ODL_S2s("serviceDescription = ", serviceDescription, "matchingCriteria = ", //####
            matchingCriteria); //####
    ODL_S1("copyrightHolder = ", copyrightHolder); //####
    enum optionIndex
    {
        kOptionUNKNOWN,
        kOptionARGS,
        kOptionCHANNEL,
        kOptionENDPOINT,
        kOptionGO,
        kOptionHELP,
        kOptionINFO,
        kOptionMOD,
        kOptionPORT,
        kOptionREPORT,
        kOptionTAG,
        kOptionVERSION
    }; // optionIndex

    bool       isAdapter = (0 < matchingCriteria.length());
    bool       keepGoing = true;
    YarpString serviceKindName(isAdapter ? "adapter" : "service");
    YarpString goPartText("  --go, -g          Start the ");
    YarpString infoPartText("  --info, -i        Print executable type, supported ");
    YarpString reportPartText("  --report, -r      Report the ");
    YarpString tagPartText("  --tag, -t         Specify the tag to be used as part of the ");

    goPartText += serviceKindName + " immediately";
    infoPartText += serviceKindName + " options";
    if (isAdapter)
    {
        infoPartText += ", matching criteria";
    }
    infoPartText += " and description and exit";
    reportPartText += serviceKindName + " metrics when the application exits";
    tagPartText += serviceKindName + " name";
    Option_::Descriptor firstDescriptor(kOptionUNKNOWN, 0, "", "", Option_::Arg::None, NULL);
    Option_::Descriptor argsDescriptor(kOptionARGS, 0, ARGS_OPTION_STRING_, "args",
                                       Option_::Arg::None,
                                       T_("  --args, -" ARGS_OPTION_STRING_
                                          "        Report the argument formats"));
    Option_::Descriptor channelDescriptor(kOptionCHANNEL, 0, CHANNEL_OPTION_STRING_, "channel",
                                          Option_::Arg::None,
                                          T_("  --channel, -" CHANNEL_OPTION_STRING_
                                             "     Report the actual endpoint name"));
    Option_::Descriptor endpointDescriptor(kOptionENDPOINT, 0, ENDPOINT_OPTION_STRING_,
                                           "endpoint", Option_::Arg::Required,
                                           T_("  --endpoint, -" ENDPOINT_OPTION_STRING_
                                              "    Specify an alternative endpoint name to be "
                                              "used"));
    Option_::Descriptor goDescriptor(kOptionGO, 0, GO_OPTION_STRING_, "go", Option_::Arg::None,
                                     goPartText.c_str());
    Option_::Descriptor helpDescriptor(kOptionHELP, 0, HELP_OPTION_STRING_, "help",
                                       Option_::Arg::None,
                                       T_("  --help, -" HELP_OPTION_STRING_
                                          "        Print usage and exit"));
    Option_::Descriptor infoDescriptor(kOptionINFO, 0, INFO_OPTION_STRING_, "info",
                                       Option_::Arg::None, infoPartText.c_str());
    Option_::Descriptor modDescriptor(kOptionMOD, 0, MOD_OPTION_STRING_, "mod",
                                      Option_::Arg::Required,
                                      T_("  --mod, -" MOD_OPTION_STRING_
                                         "         Use the IP address as a modifier for the tag"));
    Option_::Descriptor portDescriptor(kOptionPORT, 0, PORT_OPTION_STRING_, "port",
                                       Option_::Arg::Required,
                                       T_("  --port, -" PORT_OPTION_STRING_
                                          "        Specify a non-default port to be used"));
    Option_::Descriptor reportDescriptor(kOptionREPORT, 0, REPORT_OPTION_STRING_, "report",
                                         Option_::Arg::None, reportPartText.c_str());
    Option_::Descriptor tagDescriptor(kOptionTAG, 0, TAG_OPTION_STRING_, "tag",
                                      Option_::Arg::Required, tagPartText.c_str());
    Option_::Descriptor versionDescriptor(kOptionVERSION, 0, VERSION_OPTION_STRING_, "vers",
                                          Option_::Arg::None,
                                          T_("  --vers, -" VERSION_OPTION_STRING_
                                             "        Print version information and exit"));
    Option_::Descriptor lastDescriptor(0, 0, NULL, NULL, NULL, NULL);
    int                 argcWork = argc;
    char * *            argvWork = argv;
    YarpString          usageString("USAGE: ");
    YarpString          argList(ArgumentsToArgString(argumentDescriptions));

    reportEndpoint = reportOnExit = goWasSet = false;
    tag = serviceEndpointName = serviceEndpointName = "";
    modFlag = kModificationNone;
    if (arguments)
    {
        arguments->clear();
    }
    usageString += *argv;
    usageString += " [options]";
    if (0 < argList.length())
    {
        YarpStringVector descriptions;

        Utilities::ArgumentsToDescriptionArray(argumentDescriptions, descriptions, 2);
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

    if (! (skipOptions & kSkipArgsOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipChannelOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipEndpointOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipGoOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipInfoOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipModOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipPortOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipReportOption))
    {
        ++descriptorCount;
    }
    if (! (skipOptions & kSkipTagOption))
    {
        ++descriptorCount;
    }
    Option_::Descriptor * usage = new Option_::Descriptor[descriptorCount];
    Option_::Descriptor * usageWalker = usage;

#if MAC_OR_LINUX_
    firstDescriptor.help = strdup(usageString.c_str());
#else // ! MAC_OR_LINUX_
    firstDescriptor.help = _strdup(usageString.c_str());
#endif // ! MAC_OR_LINUX_
    memcpy(usageWalker++, &firstDescriptor, sizeof(firstDescriptor));
    if (! (skipOptions & kSkipArgsOption))
    {
        memcpy(usageWalker++, &argsDescriptor, sizeof(argsDescriptor));
    }
    if (! (skipOptions & kSkipChannelOption))
    {
        memcpy(usageWalker++, &channelDescriptor, sizeof(channelDescriptor));
    }
    if (! (skipOptions & kSkipEndpointOption))
    {
        memcpy(usageWalker++, &endpointDescriptor, sizeof(endpointDescriptor));
    }
    if (! (skipOptions & kSkipGoOption))
    {
        memcpy(usageWalker++, &goDescriptor, sizeof(goDescriptor));
    }
    memcpy(usageWalker++, &helpDescriptor, sizeof(helpDescriptor));
    if (! (skipOptions & kSkipInfoOption))
    {
        memcpy(usageWalker++, &infoDescriptor, sizeof(infoDescriptor));
    }
    if (! (skipOptions & kSkipModOption))
    {
        memcpy(usageWalker++, &modDescriptor, sizeof(modDescriptor));
    }
    if (! (skipOptions & kSkipPortOption))
    {
        memcpy(usageWalker++, &portDescriptor, sizeof(portDescriptor));
    }
    if (! (skipOptions & kSkipReportOption))
    {
        memcpy(usageWalker++, &reportDescriptor, sizeof(reportDescriptor));
    }
    if (! (skipOptions & kSkipTagOption))
    {
        memcpy(usageWalker++, &tagDescriptor, sizeof(tagDescriptor));
    }
    memcpy(usageWalker++, &versionDescriptor, sizeof(versionDescriptor));
    memcpy(usageWalker++, &lastDescriptor, sizeof(lastDescriptor));
    argcWork -= (argc > 0);
    argvWork += (argc > 0); // skip program name argv[0] if present
    Option_::Stats    stats(usage, argcWork, argvWork);
    Option_::Option * options = new Option_::Option[stats.options_max];
    Option_::Option * buffer = new Option_::Option[stats.buffer_max];
    Option_::Parser   parse(usage, argcWork, argvWork, options, buffer, 1);
    YarpString        badArgs;

    if (parse.error())
    {
        ODL_LOG("(parse.error())"); //####
        keepGoing = false;
    }
    else if (options[kOptionHELP] || options[kOptionUNKNOWN])
    {
        ODL_LOG("(options[kOptionHELP] || options[kOptionUNKNOWN])"); //####
        Option_::printUsage(cout, usage, HELP_LINE_LENGTH_);
        keepGoing = false;
    }
    else if (options[kOptionVERSION])
    {
        ODL_LOG("(options[kOptionVERSION])"); //####
        YarpString mpmVersionString(SanitizeString(MpM_VERSION_, true));

        cout << "Version " << mpmVersionString.c_str() << ": Copyright (c) " << year << " by " <<
                copyrightHolder << "." << endl;
        keepGoing = false;
    }
    else if (options[kOptionARGS])
    {
        ODL_LOG("(options[kOptionARGS])"); //####
        for (size_t ii = 0, mm = argumentDescriptions.size(); mm > ii; ++ii)
        {
            Utilities::BaseArgumentDescriptor * anArg = argumentDescriptions[ii];

            if (0 < ii)
            {
                cout << ARGUMENT_SEPARATOR_;
            }
            if (anArg)
            {
                cout << anArg->toString().c_str();
            }
        }
        cout << endl;
        keepGoing = false;
    }
    else if (options[kOptionINFO])
    {
        ODL_LOG("(options[kOptionINFO])"); //####
        bool needTab = true;

        // Note that we don't report the 'h' and 'v' options, as they are not involved in
        // determining what choices to offer when launching a service.
        cout << (isAdapter ? "Adapter" : "Service");
        if (! (skipOptions & kSkipArgsOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << ARGS_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipChannelOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << CHANNEL_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipEndpointOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << ENDPOINT_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipGoOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << GO_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipInfoOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << INFO_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipModOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << MOD_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipPortOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << PORT_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipReportOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << REPORT_OPTION_STRING_;
        }
        if (! (skipOptions & kSkipTagOption))
        {
            if (needTab)
            {
                cout << "\t";
                needTab = false;
            }
            cout << TAG_OPTION_STRING_;
        }
        if (needTab)
        {
            cout << "\t";
        }
        cout << "\t" << matchingCriteria.c_str() << "\t" << serviceDescription.c_str() << endl;
        keepGoing = false;
    }
    else if (ProcessArguments(argumentDescriptions, parse, badArgs))
    {
        ODL_LOG("(ProcessArguments(argumentDescriptions, parse, badArgs))"); //####
        if (options[kOptionGO])
        {
            goWasSet = true;
        }
        if (options[kOptionCHANNEL])
        {
            reportEndpoint = true;
        }
        if (options[kOptionMOD])
        {
            YarpString modArg = options[kOptionMOD].arg;

            if (0 < modArg.length())
            {
                const char * startPtr = modArg.c_str();
                char *       endPtr;
                int          numBytes = static_cast<int>(strtol(startPtr, &endPtr, 10));

                if ((startPtr != endPtr) && (!*endPtr))
                {
                    switch (numBytes)
                    {
                        case 0 :
                            modFlag = kModificationNone;
                            break;

                        case 1 :
                            modFlag = kModificationBottomByte;
                            break;

                        case 2 :
                            modFlag = kModificationBottomTwoBytes;
                            break;

                        case 3 :
                            modFlag = kModificationBottomThreeBytes;
                            break;

                        case 4 :
                            modFlag = kModificationAllBytes;
                            break;

                        default :
                            break;

                    }
                }
            }
        }
        if (options[kOptionREPORT])
        {
            reportOnExit = true;
        }
        if (options[kOptionENDPOINT])
        {
            serviceEndpointName = options[kOptionENDPOINT].arg;
            ODL_S1s("serviceEndpointName <- ", serviceEndpointName); //####
        }
        if (options[kOptionPORT])
        {
            servicePortNumber = options[kOptionPORT].arg;
            ODL_S1s("servicePortNumber <- ", servicePortNumber); //####
            if (0 < servicePortNumber.length())
            {
                const char * startPtr = servicePortNumber.c_str();
                char *       endPtr;
                int          aPort = static_cast<int>(strtol(startPtr, &endPtr, 10));

                if ((startPtr == endPtr) || *endPtr || (! Utilities::ValidPortNumber(aPort)))
                {
                    cout << "Bad port number." << endl;
                    keepGoing = false;
                }
            }
        }
        if (options[kOptionTAG])
        {
            tag = options[kOptionTAG].arg;
            ODL_S1s("tag <- ", tag); //####
        }
        if (arguments)
        {
            for (int ii = 0; ii < parse.nonOptionsCount(); ++ii)
            {
                arguments->push_back(parse.nonOption(ii));
            }
        }
    }
    else
    {
        ODL_LOG("! (ProcessArguments(argumentDescriptions, parse, badArgs))"); //####
        cout << "One or more invalid or missing arguments (" << badArgs.c_str() << ")." << endl;
        keepGoing = false;
    }
    delete[] options;
    delete[] buffer;
    free(const_cast<char *>(firstDescriptor.help));
    delete[] usage;
    ODL_EXIT_B(keepGoing); //####
    return keepGoing;
} // nImO::ProcessStandardServiceOptions
#endif//0

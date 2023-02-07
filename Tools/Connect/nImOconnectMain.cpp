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

#include <nImOchannelArgumentDescriptor.h>
#include <nImOchannelName.h>
#include "nImOregistryProxy.h"
#include <nImOstringsArgumentDescriptor.h>
#include <nImOutilityContext.h>

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

/*! @brief Set to @c false when a SIGINT occurs. */
static std::atomic<bool>    lKeepRunning(true);

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief The signal handler to catch requests to stop the application.
 @param[in] signal The signal being handled. */
static void
catchSignal
    (int signal)
{
    ODL_ENTER(); //####
    ODL_I1("signal = ", signal); //####
#if defined(SIGINT)
    if (SIGINT == signal)
    {
        lKeepRunning = false;
    }
    else
#endif // defined(SIGINT)
    {
        std::string message{"Exiting due to signal "};

        message += std::to_string(signal);
        message += " = ";
        message += nImO::NameOfSignal(signal);
        ODL_EXIT_EXIT(1); //####
        exit(1);
    }
} // catchSignal

/*! @brief Writes out a description of the 'mode' argument.
 @param[in,out] outStream The stream to write to. */
static void
helpForConnect
    (std::ostream & outStream)
{
    nImO::StringSet modes(nImO::ChannelName::transportNames());

    outStream << "Available modes:" << std::endl;
    for (auto & walker : modes)
    {
        outStream << "  " << walker << std::endl;
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
    nImO::ChannelArgumentDescriptor firstArg{"from", T_("'Sending' channel"),
                                                nImO::ArgumentMode::RequiredModifiable, "/out"};
    nImO::ChannelArgumentDescriptor secondArg{"to", T_("'Receiving' channel"),
                                                nImO::ArgumentMode::RequiredModifiable, "/in"};
    nImO::StringsArgumentDescriptor thirdArg{"mode", T_("Transport mode"),
                                                nImO::ArgumentMode::OptionalModifiable, "tcp",
                                                nImO::ChannelName::transportNames()};
    nImO::DescriptorVector          argumentList;
    nImO::OutputFlavour             flavour;
    bool                            logging = false;
    std::string                     configFilePath;
    int                             exitCode = 0;

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    argumentList.push_back(&firstArg);
    argumentList.push_back(&secondArg);
    argumentList.push_back(&thirdArg);
    if (nImO::ProcessStandardUtilitiesOptions(argc, argv, argumentList, "Connect two channels", "",
                                              2016, NIMO_COPYRIGHT_NAME_, flavour, logging, configFilePath,
                                              helpForConnect, false, true))
    {
        nImO::LoadConfiguration(configFilePath);
        try
        {
            nImO::UtilityContext    ourContext{progName, "connect", logging};
            std::string             registryAddress;
            uint16_t                registryPort;

            nImO::SetSignalHandlers(catchSignal);
            if (ourContext.findRegistry(registryAddress, registryPort))
            {
                nImO::RegistryProxy proxy{ourContext, registryAddress, registryPort};

                // TBD
            }
            else
            {
                ourContext.report("Registry not found.");
                exitCode = 2;
            }
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

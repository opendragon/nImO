//--------------------------------------------------------------------------------------------------
//
//  File:       nImOmonitorMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to continuously report information on nImO.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2017 by OpenDragon.
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
//  Created:    2017-01-26
//
//--------------------------------------------------------------------------------------------------

#include <nImOcontextWithMDNS.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#include <signal.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wc++11-extensions"
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
# pragma clang diagnostic ignored "-Wdocumentation"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# pragma clang diagnostic ignored "-Wextern-c-compat"
# pragma clang diagnostic ignored "-Wpadded"
# pragma clang diagnostic ignored "-Wshadow"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wweak-vtables"
#endif // defined(__APPLE__)
#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4996)
#endif // ! MAC_OR_LINUX_
//#include <ace/Version.h>
//#include <yarp/conf/version.h>
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to continuously report information on #nImO. */

/*! @dir Info
 @brief The set of files that implement the Monitor application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief Set to @0 when a SIGINT occurs. */
static volatile sig_atomic_t    lKeepRunning = 1;

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
        lKeepRunning = 0;
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

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for reporting information on #nImO.

 Standard output will receive a list of the connections to the channel.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string progName{*argv};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::DescriptorVector  argumentList;
    nImO::OutputFlavour     flavour;
    bool                    logging = false; // We will create the logging port used by other applications
    std::string             configFilePath;

    if (nImO::ProcessStandardUtilitiesOptions(argc, argv, argumentList, "Report on nImO", "", 2017,
                                              NIMO_COPYRIGHT_NAME_, flavour, logging, configFilePath, nullptr, false,
                                              true, true))
    {
        nImO::LoadConfiguration(configFilePath);
        try
        {
            nImO::ContextWithMDNS   ourContext(progName, logging);

            nImO::SetSignalHandlers(catchSignal);
            // Open a UDP port to collect messages.


            // Announce the UDP port so that other applications can report.


            // Wait for messages until exit requested via Ctrl-C.
            for ( ; 1 == lKeepRunning; )
            {

            }
            std::cout << "saw Ctrl-C" << std::endl;
            // Retract the announcement.

            // Close the UDP port.
            
        }
        catch (...)
        {
            ODL_LOG("Exception caught"); //####
        }
    }
    ODL_EXIT_I(0); //####
    return 0;
} // main

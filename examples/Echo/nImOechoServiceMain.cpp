//--------------------------------------------------------------------------------------------------
//
//  File:       nImOechoServiceMain.cpp
//
//  Project:    nImO
//
//  Contains:   An example application to demonstrate using the nImO library in a program.
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
//  Created:    2023-01-24
//
//--------------------------------------------------------------------------------------------------

#include "nImOregistryProxy.h"
#include <nImOserviceContext.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief An example application to demonstrate using the nImO library in a program. */

/*! @dir Version
 @brief The set of files that implement the EchoService application. */
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

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for the example application.
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
    bool                    logging = false;
    std::string             configFilePath;
    int                     exitCode = 0;

    if (nImO::ProcessStandardUtilitiesOptions(argc, argv, argumentList, "Echo service example", "", 2023,
                                              NIMO_COPYRIGHT_NAME_, flavour, logging, configFilePath, nullptr, false,
                                              true, true))
    {
        nImO::LoadConfiguration(configFilePath);
        try
        {
            nImO::ServiceContext    ourContext{progName, "EchoService", logging};
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
#if 0
            //start the ricochet program on each cluster machine, with a specified port number
            //get the list of cluster machines from 'hosts.list'
            //running = true
            // while running
            // {
            //     read a character from the terminal
            //     if it's an 's':
            //     {
            //         if random mode
            //         {
            //             create a random vector of 'next' machines, with a random length from #machines/4 to #machines*4;
            //             duplicates allowed
            //         }
            //         else
            //         {
            //             create a vector of 'next' machines with a random hop count of #machines/4 to #machines*4,
            //             reusing the 'hosts.list' entries to fill the vector
            //             select a cluster machine at random
            //             send a 'fire' message with the vector of 'next' machines on the specified port number
            //         }
            //     }
            //     else if it's a 'q':
            //     {
            //         send a 'quit' message to all the cluster machines on the specified port number
            //         running = false
            //     }
            // }
            // exit
#endif //0
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

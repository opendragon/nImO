//--------------------------------------------------------------------------------------------------
//
//  File:       nImOricochetMain.cpp
//
//  Project:    nImO
//
//  Contains:   An example application to demonstrate using the nImO library in a program.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2020 by OpenDragon.
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
//  Created:    2020-02-24
//
//--------------------------------------------------------------------------------------------------

#include <nImObooleanArgumentDescriptor.hpp>
#include <nImOmiscellaneousContext.hpp>
#include <nImOportArgumentDescriptor.hpp>
#include <nImOstringArgumentDescriptor.hpp>

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
 @brief The set of files that implement the Ricochet application. */
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
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for the example application.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int        argc,
     char * *   argv)
{
    std::string progName{*argv};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::PortArgumentDescriptor firstArg{"port", T_("Port for communication"),
                                          nImO::ArgumentMode::Optional, 2020};
    nImO::DescriptorVector       argumentList;
    nImO::OutputFlavour          flavour;
    bool                         logging = false;

    argumentList.push_back(&firstArg);
    if (nImO::ProcessStandardUtilitiesOptions(argc, argv, argumentList, "Ricochet example", "", 2020,
                                              NIMO_COPYRIGHT_NAME_, flavour, logging, nullptr, true, true))
    {
        try
        {
            nImO::MiscellaneousContext  ourContext(progName);

#if 0
            running = true
            while running
            {
                read a message from the specified port number
                if it's a 'fire' message
                {
                    [turn on the blue LED]
                    if the vector is non-empty
                    {
                        [delay a short interval]
                        fetch the first machine from the vector
                        send a 'fire' message to the selected machine - the new message has the first vector element
                        dropped
                        [delay another short interval]
                    }
                    [turn off the blue LED]
                }
                else if it's a 'quit' message
                {
                    running = false
                    [set the blue LED to 'heartbeat' mode]
                }
            }
            exit
#endif//0
        }
        catch (...)
        {
            ODL_LOG("Exception caught"); //####
        }
    }
    ODL_EXIT_I(0); //####
    return 0;
} // main

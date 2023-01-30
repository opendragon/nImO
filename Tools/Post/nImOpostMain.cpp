//--------------------------------------------------------------------------------------------------
//
//  File:       nImOpostMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to write to the log applications.
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
//  Created:    2022-12-10
//
//--------------------------------------------------------------------------------------------------

#include <nImOarray.h>
#include <nImObooleanArgumentDescriptor.h>
#include <nImOcontextWithMDNS.h>
#include <nImOstringArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to write to the log applications. */

/*! @dir List
 @brief The set of files that implement the Post application. */
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

/*! @brief The entry point for writing to the log applications.

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
    nImO::BooleanArgumentDescriptor firstArg{"stream", T_("Read standard input for text"),
                                                nImO::ArgumentMode::OptionalModifiable, false};
    nImO::StringArgumentDescriptor  secondArg{"message", T_("Text to send to logging applications"),
                                                nImO::ArgumentMode::OptionalModifiable, ""};
    nImO::DescriptorVector          argumentList;
    nImO::OutputFlavour             flavour;
    bool                            logging = true; // We need to have the logging ports set up!
    nImO::StringVector              arguments;
    std::string                     configFilePath;
    int                             exitCode = 0;

    argumentList.push_back(&firstArg);
    argumentList.push_back(&secondArg);
    if (nImO::ProcessStandardUtilitiesOptions(argc, argv, argumentList, "Write to the log applications", "",
                                              2022, NIMO_COPYRIGHT_NAME_, flavour, logging, configFilePath, nullptr,
                                              false, true, true, &arguments))
    {
        nImO::LoadConfiguration(configFilePath);
        try
        {
            nImO::ContextWithNetworking ourContext{progName, "post", logging};
            std::string                 header{secondArg.getCurrentValue()};
            bool                        readFromStdin{firstArg.getCurrentValue()};

            if (readFromStdin)
            {
                nImO::StringVector  stuffToSend;

                if (0 < header.length())
                {
                    stuffToSend.push_back(header);
                }
                std::string inLine;

                while (getline(std::cin, inLine))
                {
                    stuffToSend.push_back(inLine);
                }
                if (1 < stuffToSend.size())
                {
                    if (! ourContext.report(stuffToSend))
                    {
                        exitCode = 1;
                    }
                }
                else if (0 < stuffToSend.size())
                {
                    if (! ourContext.report(stuffToSend[0]))
                    {
                        exitCode = 1;
                    }
                }
            }
            else if (0 < header.length())
            {
                if (! ourContext.report(header))
                {
                    exitCode = 1;
                }
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

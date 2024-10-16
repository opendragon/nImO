//--------------------------------------------------------------------------------------------------
//
//  File:       nImOversionMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to report the version numbers of nImO and its dependencies.
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

#include <nImOstandardOptions.h>

#include <boost/version.hpp>
#include <regex>
#include "sqlite3.h"

//#include <odlEnable.h>
#include <odlInclude.h>

#if MAC_OR_LINUX_OR_BSD_
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif // MAC_OR_LINUX_OR_BSD_
#include <mdns.hpp>
#if MAC_OR_LINUX_OR_BSD_
# pragma GCC diagnostic pop
#endif // MAC_OR_LINUX_OR_BSD_

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to report the version numbers of #nImO and its dependencies. */

/*! @dir Version
 @brief The set of files that implement the Version application. */
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

/*! @brief Return the version coming from the Boost macros as a
 more 'normal' representation.
 @return The Boost version string with underscores replaced with
 periods. */
static std::string
getBoostVersion
    (void)
{
    std::string source{BOOST_LIB_VERSION};
    std::regex  exp{"_"};

    return std::regex_replace(source, exp, ".");
} // getBoostVersion

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for reporting the version numbers.

 Standard output will receive a list of the version numbers.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    nImO::DescriptorVector  argumentList{};
    nImO::StandardOptions   optionValues{};
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Reports the version number of the libraries used"s, "nImOversion -t"s, 2016,
                                     nImO::kCopyrightName, optionValues, nullptr, nImO::kSkipConfigFileOption | nImO::kSkipExpandedOption |
                                     nImO::kSkipLoggingOption | nImO::kSkipMachineOption))
    {
        std::string mdnsVersionString;
        std::string nImOversionString;
        std::string odlVersionString;
        std::string sqlVersionString{SQLITE_VERSION};

        try
        {
            switch (optionValues._flavour)
            {
                case nImO::OutputFlavour::kFlavourTabs :
                    mdnsVersionString = nImO::SanitizeString(mdns_plusplus_VERSION_, true);
                    nImOversionString = nImO::SanitizeString(nImO_VERSION_, true);
                    odlVersionString = nImO::SanitizeString(ODL_VERSION_, true);
                    std::cout << nImOversionString << "\t" << odlVersionString << "\t" << mdnsVersionString << "\t" <<
                                getBoostVersion() << "\t" << sqlVersionString << "\n";
                    break;

                case nImO::OutputFlavour::kFlavourJSON :
                    mdnsVersionString = nImO::SanitizeString(mdns_plusplus_VERSION_);
                    nImOversionString = nImO::SanitizeString(nImO_VERSION_);
                    odlVersionString = nImO::SanitizeString(ODL_VERSION_);
                    std::cout << "{ " CHAR_DOUBLEQUOTE_ "nImO" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << nImOversionString <<
                                CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "ODL" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                odlVersionString << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "mdns_plusplus"
                                                       CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                mdnsVersionString << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "Boost"
                                                        CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                getBoostVersion() << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "SQLite"
                                                        CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                sqlVersionString << CHAR_DOUBLEQUOTE_ << " }\n";
                    break;

                case nImO::OutputFlavour::kFlavourNiMo :
                    mdnsVersionString = nImO::SanitizeString(mdns_plusplus_VERSION_);
                    nImOversionString = nImO::SanitizeString(nImO_VERSION_);
                    odlVersionString = nImO::SanitizeString(ODL_VERSION_);
                    std::cout << nImO::kStartMapChar << " " CHAR_DOUBLEQUOTE_ "nImO" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator <<
                                                    " " CHAR_DOUBLEQUOTE_ << nImOversionString <<
                                CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "ODL" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator <<
                                                    " " CHAR_DOUBLEQUOTE_ <<
                                odlVersionString << CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "mdns_plusplus"
                                                       CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ <<
                                mdnsVersionString << CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "Boost"
                                                        CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ <<
                                getBoostVersion() << CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "SQLite"
                                                        CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ <<
                                sqlVersionString << CHAR_DOUBLEQUOTE_ << " " << nImO::kEndMapChar << "\n";
                    break;

                case nImO::OutputFlavour::kFlavourNormal :
                    mdnsVersionString = nImO::SanitizeString(mdns_plusplus_VERSION_, true);
                    nImOversionString = nImO::SanitizeString(nImO_VERSION_, true);
                    odlVersionString = nImO::SanitizeString(ODL_VERSION_, true);
                    std::cout << "nImO version: " << nImOversionString << ", ODL version: " <<
                                odlVersionString << ", mdns_plusplus version: " << mdnsVersionString <<
                                ", Boost version: " << getBoostVersion() << ", SQLite version: " << sqlVersionString << "\n";
                    break;

                default :
                    break;

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

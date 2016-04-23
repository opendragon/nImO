//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommon.hpp
//
//  Project:    nImO
//
//  Contains:   The function and class declarations for common entities for nImO.
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
//  Created:    2016-03-21
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOcommon_HPP_))
# define nImOcommon_HPP_ /* Header guard */

# include <nImO/nImOconfig.hpp>

# if (! defined(LINUX_))
/*! @brief @c TRUE if Linux, @c FALSE otherwise. */
#  define LINUX_ defined(__linux__)
# endif // ! defined(LINUX_)
# if (! defined(MAC_OR_LINUX_))
/*! @brief @c TRUE if non-Windows, @c FALSE if Windows. */
#  define MAC_OR_LINUX_ (defined(__APPLE__) || defined(__linux__))
# endif // ! defined(MAC_OR_LINUX_)

//# include <algorithm>
//# include <cctype>
# include <cmath>
# include <csignal>
# include <cstdlib>
//# include <cstring>
# include <iostream>
# include <list>
# include <map>
# include <set>
//# include <stdint.h>
# include <sstream>
//# include <time.h>
# include <vector>

# if MAC_OR_LINUX_
#  include <arpa/inet.h>
#  include <sys/socket.h>
#  define SOCKET         int /* Standard socket type in *nix. */
#  define INVALID_SOCKET -1
# else // ! MAC_OR_LINUX_
#  pragma warning(push)
#  pragma warning(disable: 4996)
#  include <WinSock2.h>
#  include <Ws2tcpip.h>
#  pragma warning(pop)
# endif // ! MAC_OR_LINUX_

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The function and class declarations for common entities for %nImO. */

/*! @dir /nImO
 @brief The set of files that implement the %nImO framework. */

/*! @dir /CommonTests
 @brief The set of files that provide test cases for the %nImO framework. */

/*! @namespace nImO
 @brief The classes that implement the %nImO framework. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief A TAB character. */
# define CHAR_TAB_                  "\t"

/*! @brief A NEWLINE character. */
# define CHAR_NEWLINE_              "\n"

/*! @brief A DOUBLEQUOTE character. */
# define CHAR_DOUBLEQUOTE_          "\""

/*! @brief The default name for the root part of a channel name. */
# define DEFAULT_CHANNEL_ROOT_      "channel_"

# if (! defined(FALSE))
#  define FALSE 0
# endif // ! defined(FALSE)

/*! @brief The line length for command-line help output. */
# define HELP_LINE_LENGTH_          250

/*! @brief The largest IP port that is acceptable. */
# define MAXIMUM_PORT_ALLOWED_      65535

/*! @brief The smallest IP port that is acceptable. */
# define MINIMUM_PORT_ALLOWED_      1024

/*! @brief The standard copyright holder name to use for m+m-created executables. */
# define NIMO_COPYRIGHT_NAME_       "OpenDragon"

/*! @brief The IP address for the loopback address for the machine that is running the
 executable. */
# define SELF_ADDRESS_IPADDR_       "127.0.0.1"

/*! @brief The IP name for the loopback address for the machine that is running the
 executable. */
# define SELF_ADDRESS_NAME_         "localhost"

/*! @brief The signal to use for internally-detected timeouts. */
# if MAC_OR_LINUX_
#  define STANDARD_SIGNAL_TO_USE_   SIGUSR2
# else // ! MAC_OR_LINUX_
#  define STANDARD_SIGNAL_TO_USE_   42
# endif // ! MAC_OR_LINUX_

/*! @brief A simple macro to hold the pieces of a string together. */
# define T_(xx_)                    xx_

# if (! defined(TRUE))
#  define TRUE 1
# endif // ! defined(TRUE)

namespace nImO
{
    // Type definitions.

    enum Enumerable
    {
        kEnumerableUnknown,
        kEnumerableBoolean,
        kEnumerableInteger,
        kEnumerableString,
        kEnumerableNotEnumerable
    }; // Enumerable

    /*! @brief The format for the output from command-line tools. */
    enum OutputFlavour
    {
        /*! @brief Normal output with no special processing. */
        kOutputFlavourNormal,

        /*! @brief Output in JSON format. Tabs and newlines are replaced with spaces. */
        kOutputFlavourJSON,

        /*! @brief Output in tab-delimited format. Tabs and newlines are replaced with
         spaces. */
        kOutputFlavourTabs,

        /*! @brief Force the size to be 4 bytes. */
        kOutputFlavourUnknown = 0x7FFFFFFF

    }; // OutputFlavour

    // Forward reference.
    class BaseArgumentDescriptor;

    /*! @brief A sequence of argument descriptors. */
    typedef std::vector<BaseArgumentDescriptor *> DescriptorVector;

    /*! @brief A pointer to a handler for system signals.
     @param theSignal The signal of interest. */
    typedef void (* SignalHandler)
       (int theSignal);

    /*! @brief A sequence of strings. */
    typedef std::vector<std::string> StringVector;

    // Methods.

    /*! @brief Generate a random channel name.
     @returns A randomly-generated channel name. */
    std::string
    GetRandomChannelName(const char * channelRoot = DEFAULT_CHANNEL_ROOT_);

    /*! @brief Generate a random channel name.
     @returns A randomly-generated channel name. */
    std::string
    GetRandomChannelName(const std::string & channelRoot);

    /*! @brief Return a random string of hexadecimal digits.
     @returns A random string of hexadecimal digits. */
    std::string
    GetRandomHexString(void);

    /*! @brief Perform initialization of internal resources.
     @param progName The name of the executing program.

     Should be called in the main() function of each application or service. */
    void
    Initialize(const std::string & progName);

    /*! @brief Return the name of a signal.
     @param theSignal The signal of interest.
     @returns A string description of the signal. */
    const char *
    NameOfSignal(const int theSignal);

    /*! @brief Process the standard options for utility executables.
     The option '-h' / '--help' displays the list of optional parameters and arguments and
     returns @c false.
     The option '-i' / '--info' displays the type of the executable and the description of the
     executable and returns @c false.
     The option '-j' / '--json' specifies that output is to be in JSON format.
     The option '-t' / '--tabs' specifies that output is to be in tab-delimited format.
     The option '-v' / '--vers'displays the version and copyright information and returns
     @c false.
     @param argc The number of arguments in 'argv'.
     @param argv The arguments to be used with the utility.
     @param argumentDescriptions Descriptions of the arguments to the adapter.
     @param utilityDescription A description of the utility.
     @param year The copyright year for the calling application.
     @param copyrightHolder The name of the entity holding the copyright to the utility.
     @param flavour Set if the -j or -t options are seen.
     @param ignoreFlavours @c true if the flavour options are ignored and @c false otherwise.
     @param arguments If non-@c NULL, returns the arguments for the utility.
     @returns @c true if the program should continue and @c false if it should leave. */
    bool
    ProcessStandardUtilitiesOptions(const int           argc,
                                    char * *            argv,
                                    DescriptorVector &  argumentDescriptions,
                                    const std::string & utilityDescription,
                                    const int           year,
                                    const char *        copyrightHolder,
                                    OutputFlavour &     flavour,
                                    const bool          ignoreFlavours = false,
                                    StringVector *      arguments = NULL);

    /*! @brief Return a string with special characters escaped.
     @param inString The string to be processed.
     @param allowDoubleQuotes @c true if double quotes aren't escaped and @c false otherwise.
     @returns A string with special characters escaped. */
    std::string
    SanitizeString(const std::string & inString,
                   const bool          allowDoubleQuotes = false);

    /*! @brief Connect the standard signals to a handler.
     @param theHandler The new handler for the signals. */
    void
    SetSignalHandlers(SignalHandler theHandler);

    /*! @brief Set up the signal-handling behaviour so that this thread will catch our signal. */
    void
    SetUpCatcher(void);

    /*! @brief Restore the normal signal-handling behaviour. */
    void
    ShutDownCatcher(void);

    /*! @brief Checks a network port number for validity.
     @param aPort The port number to be checked.
     @param systemAllowed @c true if system port numbers are valid and @c false otherwise.
     @returns @c true if the port number is valid and @c false otherwise. */
    inline bool
    ValidPortNumber(const int  aPort,
                    const bool systemAllowed = false)
    {
        return (((systemAllowed ? 0 : MINIMUM_PORT_ALLOWED_) <= aPort) &&
                (MAXIMUM_PORT_ALLOWED_ >= aPort));
    } // ValidPortNumber

    /*! @brief The character that is used with 'blob' data formatting. */
    extern const char kBlobSeparator;

    /*! @brief A character that brackets a string value. */
    extern const char kDoubleQuote;
    
    /*! @brief The character that ends an Array value. */
    extern const char kEndArrayChar;

    /*! @brief The character that ends a Map value. */
    extern const char kEndMapChar;

    /*! @brief The character that ends a Set value. */
    extern const char kEndSetChar;

    /*! @brief The escape character. */
    extern const char kEscapeChar;

    /*! @brief The character that separates a key from a value in a key/value pair. */
    extern const char kKeyValueSeparator;

    /*! @brief A character that brackets a string value. */
    extern const char kSingleQuote;

    /*! @brief The character that starts an Array value. */
    extern const char kStartArrayChar;

    /*! @brief The character that starts a Map value. */
    extern const char kStartMapChar;

    /*! @brief The character that starts a Set value. */
    extern const char kStartSetChar;

    /*! @brief The directory separator string; */
    extern const std::string kDirectorySeparator;

} // nImO

#endif // ! defined(nImOcommon_HPP_)

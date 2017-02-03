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
# include <cstring>
# include <iostream>
# include <list>
# include <map>
# include <memory>
# include <queue>
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

/*! @dir /Tests
 @brief The set of files that provide test cases for the %nImO framework. */

/*! @namespace nImO
 @brief The classes that implement the %nImO framework. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

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

    /*! @brief The tag values for Message contents. */
    enum DataKind
    {
        /*! @brief The mask for the kind of data that follows. */
        kKindMask = 0x00C0,

        /*! @brief The data that follows is a signed integer value. */
        kKindInteger = 0x0000,

            /*! @brief The mask for the size of the signed integer value. */
            kKindIntegerSizeMask = 0x0020,

            /*! @brief The signed integer value is in the range -16..15 and is contained
             within this byte. */
            kKindIntegerShortValue = 0x0000,

                /*! @brief The mask for the value of the signed integer. */
                kKindIntegerShortValueValueMask = 0x001F,

                /*! @brief The minimum value representable in a short signed integer. */
                kKindIntegerShortValueMinValue = -16,

                /*! @brief The maximum value representable in a short signed integer. */
                kKindIntegerShortValueMaxValue = 15,

                /*! @brief The position of the sign bit in the short signed integer. */
                kKindIntegerShortValueSignBit = 0x0010,

            /*! @brief The signed integer value follows this byte. */
            kKindIntegerLongValue = 0x0020,

                /*! @brief The mask for the count of the number of bytes (1..8) that contain
                 the signed integer value.
                 Note that the count contained in the byte is one less than the actual count. */
                kKindIntegerLongValueCountMask = 0x0007,

        /*! @brief The data that follows is one or more floating-point values. */
        kKindDouble = 0x0040,

            /*! @brief The mask for the size of the count of floating-point values. */
            kKindDoubleCountMask = 0x0020,

            /*! @brief The count of the number of floating-point values is in the range 1..16
             and is contained within this byte.
             Note that the count contained in the byte is one less than the actual count. */
            kKindDoubleShortCount = 0x0000,

                /*! @brief The mask for the count of the number of floating-point values. */
                kKindDoubleShortCountMask = 0x001F,

                /*! @brief The minimum count representable in a short floating point. */
                kKindDoubleShortCountMinValue = 1,

                /*! @brief The maximum count representable in a short floating point. */
                kKindDoubleShortCountMaxValue = 32,

            /*! @brief The count of the number of floating-point values is contained in the
             next byte(s) and the size of the count (1..8) is contained in this byte.
             Note that the size of the count contained in the byte is one less than the actual
             size of the count; the count itself is the actual count. */
            kKindDoubleLongCount = 0x0020,

                /*! @brief The mask for the size of the count of floating-point values. */
                kKindDoubleLongCountMask = 0x0007,

        /*! @brief The data that follows is a String or Blob. */
        kKindStringOrBlob = 0x0080,

            /*! @brief The mask for the type of data - String or Blob. */
            kKindStringOrBlobTypeMask = 0x0020,

            /*! @brief The data that follows is a non-@c NULL-terminated String. */
            kKindStringOrBlobStringValue = 0x0000,

            /*! @brief The data that follows is a Blob. */
            kKindStringOrBlobBlobValue = 0x0020,

            /*! @brief The mask for the length of the data that follows. */
            kKindStringOrBlobLengthMask = 0x0010,

            /*! @brief The length of the data is in the range 0..15 and is contained within
             this byte. */
            kKindStringOrBlobShortLengthValue = 0x0000,

                /*! @brief The mask for the length of the data. */
                kKindStringOrBlobShortLengthMask = 0x000F,

                /*! @brief The minimum count representable in a short floating point. */
                kKindStringOrBlobShortLengthMinValue = 0,

                /*! @brief The maximum count representable in a short floating point. */
                kKindStringOrBlobShortLengthMaxValue = 15,

            /*! @brief The length of the data is contained in the next byte(s). */
            kKindStringOrBlobLongLengthValue = 0x0010,

                /*! @brief The mask for the count of the number of bytes (1..8) that contain
                 the length of the data.
                 Note that the count contained in the byte is one less than the actual count;
                 the length is the actual length. */
                kKindStringOrBlobLongLengthMask = 0x0007,

        /*! @brief The data that follows is a Boolean or a Container. */
        kKindOther = 0x00C0,

            /*! @brief The mask for the type of value that follows. */
            kKindOtherTypeMask = 0x0030,

            /*! @brief The value is a Boolean. */
            kKindOtherBoolean = 0x0000,

                /*! @brief The mask for the value of the Boolean. */
                kKindOtherBooleanValueMask = 0x0001,

                /*! @brief The value is @c false. */
                kKindOtherBooleanFalseValue = 0x0000,

                /*! @brief The value is @c true. */
                kKindOtherBooleanTrueValue = 0x00001,

            /*! @brief The value that follows is a Container. */
            kKindOtherContainerStart = 0x0010,

            /*! @brief The value that preceeded this was a Container. */
            kKindOtherContainerEnd = 0x0020,

            /*! @brief The mask for the type of Container. */
            kKindOtherContainerTypeMask = 0x000C,

            /*! @brief The container is an Array. */
            kKindOtherContainerTypeArray = 0x0000,

            /*! @brief The container is a Map. */
            kKindOtherContainerTypeMap = 0x0004,

            /*! @brief The container is a Set. */
            kKindOtherContainerTypeSet = 0x0008,

            /*! @brief The mask for the empty / non-empty state of the Container. */
            kKindOtherContainerEmptyMask = 0x0001,

            /*! @brief The Container is empty; no count of the number of elements follows. */
            kKindOtherContainerEmptyValue = 0x0000,

            /*! @brief The Container is non-empty and the count of the number of elements
             follows, as a signed integer value, if this is the 'start' tag.
             Note that the number of elements is offset by -17, as a negative count of
             elements is not possible, and a count of zero is already handled. */
            kKindOtherContainerNonEmptyValue = 0x0001,

            /*! @brief The value that follows is a Message. */
            kKindOtherMessage = 0x0030,

                /*! @brief The mask for the start / end state of the Message. */
                kKindOtherMessageStartEndMask = 0x0008,

                /*! @brief The data that follows form a Message. */
                kKindOtherMessageStartValue = 0x0000,

                /*! @brief The data that preceeded this was a Message. */
                kKindOtherMessageEndValue = 0x0008,

                /*! @brief The mask for the empty / non-empty state of the Message. */
                kKindOtherMessageEmptyMask = 0x0004,

                /*! @brief The Message is empty. */
                kKindOtherMessageEmptyValue = 0x0000,

                /*! @brief The Message is non-empty; the type flag (top two-bits) of the first
                 Value in the Message, if the start of the Message or of the last Value in the
                 Message, if the end of the Message, is contained in the byte. */
                kKindOtherMessageNonEmptyValue = 0x0004,

                /*! @brief The mask for the type of the immediately enclosed Value in the
                 Message - the first Value, if the start of the Message, and the last Value if
                 the end of the Message. */
                kKindOtherMessageExpectedTypeMask = 0x0003,

                /*! @brief The number of positions to right-shift the type of a tag to align with
                 the Message type value. */
                kKindOtherMessageExpectedTypeShift = 6,

                /*! @brief The enclosed value in the Message is a signed integer. */
                kKindOtherMessageExpectedIntegerValue = 0x0000,

                /*! @brief The enclosed value in the Message is a float-point number. */
                kKindOtherMessageExpectedDoubleValue = 0x0001,

                /*! @brief The enclosed value in the Message is a String or Blob. */
                kKindOtherMessageExpectedStringOrBlobValue = 0x0002,

                /*! @brief The enclosed value in the Message is a Boolean or Container. */
                kKindOtherMessageExpectedOtherValue = 0x0003

    }; // DataKind

    /*! @brief Whether a Value is enumerable. */
    enum Enumerable
    {
        /*! @brief It is not known if the Value is enumerable. */
        kEnumerableUnknown,

        /*! @brief The Value is a Boolean and therefore enumerable. */
        kEnumerableBoolean,

        /*! @brief The Value is a signed integer and therefore enumerable. */
        kEnumerableInteger,

        /*! @brief The Value is a String and therefore enumerable. */
        kEnumerableString,

        /*! @brief The Value is not enumerable. */
        kEnumerableNotEnumerable

    }; // Enumerable

    /*! @brief The state of a Message. */
    enum MessageState
    {
        /*! @brief The Message is neither open nor closed. */
        kMessageStateUnknown,

        /*! @brief The Message has been opened for reading. */
        kMessageStateOpenForReading,

        /*! @brief The Message has been opened for writing. */
        kMessageStateOpenForWriting,

        /*! @brief The Message has been closed. */
        kMessageStateClosed

    }; // MessageState

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

    /*! @brief The status of a read operation on a Message. */
    enum ReadStatus
    {
        /*! @brief Reading from the Message was successful; a @c NULL result indicates and empty
        Message. */
        kReadSuccessful,

        /*! @brief Reading from the Message was successful and all data was processed. */
        kReadSuccessfulAtEnd,

        /*! @brief The Message was incomplete and more data is needed. */
        kReadIncomplete,

        /*! @brief Invalid data was found in the Message and reading is not possible. */
        kReadInvalid

    }; // ReadStatus

    // Forward reference.
    class BaseArgumentDescriptor;

    /*! @brief A byte array that is the same size as an integer. */
    typedef uint8_t NumberAsBytes[sizeof(int64_t)];

    /*! @brief A sequence of argument descriptors. */
    typedef std::vector<BaseArgumentDescriptor *> DescriptorVector;

    /*! @brief A pointer to a handler for system signals.
     @param[in] theSignal The signal of interest. */
    typedef void (* SignalHandler)
       (int theSignal);

    /*! @brief A sequence of strings. */
    typedef std::vector<std::string> StringVector;

    // Methods.

    /*! @brief Convert a set of bytes into a floating-point value.
     @param[in] inString The byte string to be processed.
     @returns The floating-point value stored in the bytes. */
    double
    B2D(const NumberAsBytes &inString);

    /*! @brief Convert a set of bytes into an integer value.
     @param[in] inString The byte string to be processed.
     @param[in] numBytes The number of bytes to be processed.
     @returns The integer value stored in the bytes. */
    int64_t
    B2I(const NumberAsBytes &inString,
        const size_t        numBytes);

    /*! @brief Compare two byte strings.
     @param[in] first The first byte string.
     @param[in] second The second byte string.
     @param[in] numBytes The number of bytes to be compared.
     @returns @c 0 if the two byte strings are identical or the positive index (1-origin) where the
     two byte strings differ. */
    size_t
    CompareBytes(const void   *first,
                 const void   *second,
                 const size_t numBytes);

    /*! @brief Convert a floating-point value into a set of bytes.
     @param[in] inValue The number to be converted.
     @param[out] outString The byte string to be filled. */
    void
    D2B(const double  inValue,
        NumberAsBytes &outString);

    /*! @brief Generate a random channel name.
     @returns A randomly-generated channel name. */
    std::string
    GetRandomChannelName(const char *channelRoot = DEFAULT_CHANNEL_ROOT_);

    /*! @brief Generate a random channel name.
     @returns A randomly-generated channel name. */
    std::string
    GetRandomChannelName(const std::string &channelRoot);

    /*! @brief Return a random string of hexadecimal digits.
     @returns A random string of hexadecimal digits. */
    std::string
    GetRandomHexString(void);

    /*! @brief Convert an integer value into a set of bytes and return the minimum number of bytes
     needed to represent the value.
     @param[in] inValue The number to be converted.
     @param[out] outString The byte string to be filled.
     @returns The minimum number of bytes needed to represent the value. */
    size_t
    I2B(const int64_t inValue,
        NumberAsBytes &outString);

    /*! @brief Perform initialization of internal resources.
     @param[in] progName The name of the executing program.

     Should be called in the main() function of each application or service. */
    void
    Initialize(const std::string &progName);

    /*! @brief Return the name of a signal.
     @param[in] theSignal The signal of interest.
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
     @param[in] argc The number of arguments in 'argv'.
     @param[in] argv The arguments to be used with the utility.
     @param[in,out] argumentDescriptions Descriptions of the arguments to the adapter.
     @param[in] utilityDescription A description of the utility.
     @param[in] year The copyright year for the calling application.
     @param[in] copyrightHolder The name of the entity holding the copyright to the utility.
     @param[in,out] flavour Set if the -j or -t options are seen.
     @param[in] ignoreFlavours @c true if the flavour options are ignored and @c false otherwise.
     @param[in] arguments If non-@c NULL, returns the arguments for the utility.
     @returns @c true if the program should continue and @c false if it should leave. */
    bool
    ProcessStandardUtilitiesOptions(const int         argc,
                                    char              **argv,
                                    DescriptorVector  &argumentDescriptions,
                                    const std::string &utilityDescription,
                                    const int         year,
                                    const char        *copyrightHolder,
                                    OutputFlavour     &flavour,
                                    const bool        ignoreFlavours = false,
                                    StringVector      *arguments = NULL);

    /*! @brief Return a string with special characters escaped.
     @param[in] inString The string to be processed.
     @param[in] allowDoubleQuotes @c true if double quotes aren't escaped and @c false otherwise.
     @returns A string with special characters escaped. */
    std::string
    SanitizeString(const std::string &inString,
                   const bool        allowDoubleQuotes = false);

    /*! @brief Connect the standard signals to a handler.
     @param[in] theHandler The new handler for the signals. */
    void
    SetSignalHandlers(SignalHandler theHandler);

    /*! @brief Set up the signal-handling behaviour so that this thread will catch our signal. */
    void
    SetUpCatcher(void);

    /*! @brief Restore the normal signal-handling behaviour. */
    void
    ShutDownCatcher(void);

    /*! @brief Checks a network port number for validity.
     @param[in] aPort The port number to be checked.
     @param[in] systemAllowed @c true if system port numbers are valid and @c false otherwise.
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

    /*! @brief The character that ends an Array value. */
    extern const char kEndArrayChar;

    /*! @brief The character that ends a Map value. */
    extern const char kEndMapChar;

    /*! @brief The character that ends a Set value. */
    extern const char kEndSetChar;

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

    /*! @brief A character that brackets a string value. */
    extern const uint8_t kDoubleQuote;

    /*! @brief The escape character. */
    extern const uint8_t kEscapeChar;

    /*! @brief The directory separator string; */
    extern const std::string kDirectorySeparator;

} // nImO

#endif // ! defined(nImOcommon_HPP_)

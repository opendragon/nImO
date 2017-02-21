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
    // Forward declarations.

    class Array;
    class BaseArgumentDescriptor;
    class BufferChunk;
    class Map;
    class Message;
    class Set;
    class String;
    class StringBuffer;
    class Value;
    
    // Type definitions.

    /*! @brief The tag values for Message contents. */
    enum class DataKind : uint8_t
    {
        /*! @brief The mask for the kind of data that follows. */
        Mask = 0x00C0,

        /*! @brief The data that follows is a signed integer value. */
        Integer = 0x0000,

            /*! @brief The mask for the size of the signed integer value. */
            IntegerSizeMask = 0x0020,

            /*! @brief The signed integer value is in the range -16..15 and is contained
             within this byte. */
            IntegerShortValue = 0x0000,

                /*! @brief The mask for the value of the signed integer. */
                IntegerShortValueValueMask = 0x001F,

                /*! @brief The position of the sign bit in the short signed integer. */
                IntegerShortValueSignBit = 0x0010,

            /*! @brief The signed integer value follows this byte. */
            IntegerLongValue = 0x0020,

                /*! @brief The mask for the count of the number of bytes (1..8) that contain
                 the signed integer value.
                 Note that the count contained in the byte is one less than the actual count. */
                IntegerLongValueCountMask = 0x0007,

        /*! @brief The data that follows is one or more floating-point values. */
        Double = 0x0040,

            /*! @brief The mask for the size of the count of floating-point values. */
            DoubleCountMask = 0x0020,

            /*! @brief The count of the number of floating-point values is in the range 1..16
             and is contained within this byte.
             Note that the count contained in the byte is one less than the actual count. */
            DoubleShortCount = 0x0000,

                /*! @brief The mask for the count of the number of floating-point values. */
                DoubleShortCountMask = 0x001F,

            /*! @brief The count of the number of floating-point values is contained in the
             next byte(s) and the size of the count (1..8) is contained in this byte.
             Note that the size of the count contained in the byte is one less than the actual
             size of the count; the count itself is the actual count. */
            DoubleLongCount = 0x0020,

                /*! @brief The mask for the size of the count of floating-point values. */
                DoubleLongCountMask = 0x0007,

        /*! @brief The data that follows is a String or Blob. */
        StringOrBlob = 0x0080,

            /*! @brief The mask for the type of data - String or Blob. */
            StringOrBlobTypeMask = 0x0020,

            /*! @brief The data that follows is a non-@c nullptr-terminated String. */
            StringOrBlobStringValue = 0x0000,

            /*! @brief The data that follows is a Blob. */
            StringOrBlobBlobValue = 0x0020,

            /*! @brief The mask for the length of the data that follows. */
            StringOrBlobLengthMask = 0x0010,

            /*! @brief The length of the data is in the range 0..15 and is contained within
             this byte. */
            StringOrBlobShortLengthValue = 0x0000,

                /*! @brief The mask for the length of the data. */
                StringOrBlobShortLengthMask = 0x000F,

            /*! @brief The length of the data is contained in the next byte(s). */
            StringOrBlobLongLengthValue = 0x0010,

                /*! @brief The mask for the count of the number of bytes (1..8) that contain
                 the length of the data.
                 Note that the count contained in the byte is one less than the actual count;
                 the length is the actual length. */
                StringOrBlobLongLengthMask = 0x0007,

        /*! @brief The data that follows is a Logical or a Container. */
        Other = 0x00C0,

            /*! @brief The mask for the type of value that follows. */
            OtherTypeMask = 0x0030,

            /*! @brief The value is a Logical. */
            OtherLogical = 0x0000,

                /*! @brief The mask for the value of the Logical. */
                OtherLogicalValueMask = 0x0001,

                /*! @brief The value is @c false. */
                OtherLogicalFalseValue = 0x0000,

                /*! @brief The value is @c true. */
                OtherLogicalTrueValue = 0x00001,

            /*! @brief The value that follows is a Container. */
            OtherContainerStart = 0x0010,

            /*! @brief The value that preceeded this was a Container. */
            OtherContainerEnd = 0x0020,

            /*! @brief The mask for the type of Container. */
            OtherContainerTypeMask = 0x000C,

            /*! @brief The container is an Array. */
            OtherContainerTypeArray = 0x0000,

            /*! @brief The container is a Map. */
            OtherContainerTypeMap = 0x0004,

            /*! @brief The container is a Set. */
            OtherContainerTypeSet = 0x0008,

            /*! @brief The mask for the empty / non-empty state of the Container. */
            OtherContainerEmptyMask = 0x0001,

            /*! @brief The Container is empty; no count of the number of elements follows. */
            OtherContainerEmptyValue = 0x0000,

            /*! @brief The Container is non-empty and the count of the number of elements
             follows, as a signed integer value, if this is the 'start' tag.
             Note that the number of elements is offset by -17, as a negative count of
             elements is not possible, and a count of zero is already handled. */
            OtherContainerNonEmptyValue = 0x0001,

            /*! @brief The value that follows is a Message. */
            OtherMessage = 0x0030,

                /*! @brief The mask for the start / end state of the Message. */
                OtherMessageStartEndMask = 0x0008,

                /*! @brief The data that follows form a Message. */
                OtherMessageStartValue = 0x0000,

                /*! @brief The data that preceeded this was a Message. */
                OtherMessageEndValue = 0x0008,

                /*! @brief The mask for the empty / non-empty state of the Message. */
                OtherMessageEmptyMask = 0x0004,

                /*! @brief The Message is empty. */
                OtherMessageEmptyValue = 0x0000,

                /*! @brief The Message is non-empty; the type flag (top two-bits) of the first
                 Value in the Message, if the start of the Message or of the last Value in the
                 Message, if the end of the Message, is contained in the byte. */
                OtherMessageNonEmptyValue = 0x0004,

                /*! @brief The mask for the type of the immediately enclosed Value in the
                 Message - the first Value, if the start of the Message, and the last Value if
                 the end of the Message. */
                OtherMessageExpectedTypeMask = 0x0003,

                /*! @brief The number of positions to right-shift the type of a tag to align with
                 the Message type value. */
                OtherMessageExpectedTypeShift = 6,

                /*! @brief The enclosed value in the Message is a signed integer. */
                OtherMessageExpectedIntegerValue = 0x0000,

                /*! @brief The enclosed value in the Message is a float-point number. */
                OtherMessageExpectedDoubleValue = 0x0001,

                /*! @brief The enclosed value in the Message is a String or Blob. */
                OtherMessageExpectedStringOrBlobValue = 0x0002,

                /*! @brief The enclosed value in the Message is a Logical or Container. */
                OtherMessageExpectedOtherValue = 0x0003

    }; // DataKind

    /*! @brief The minimum count representable in a short floating point. */
    const int DataKindDoubleShortCountMinValue = 1;

    /*! @brief The maximum count representable in a short floating point. */
    const int DataKindDoubleShortCountMaxValue = 32;

    /*! @brief The minimum value representable in a short signed integer. */
    const int DataKindIntegerShortValueMinValue = -16;

    /*! @brief The maximum value representable in a short signed integer. */
    const int DataKindIntegerShortValueMaxValue = 15;

    /*! @brief The minimum count representable in a short floating point. */
    const int DataKindStringOrBlobShortLengthMinValue = 0;

    /*! @brief The maximum count representable in a short floating point. */
    const int StringOrBlobShortLengthMaxValue = 15;

    /*! @brief Whether a Value is enumerable. */
    enum class Enumerable
    {
        /*! @brief It is not known if the Value is enumerable. */
        Unknown,

        /*! @brief The Value is a Logical and therefore enumerable. */
        Logical,

        /*! @brief The Value is a signed integer and therefore enumerable. */
        Integer,

        /*! @brief The Value is a String and therefore enumerable. */
        String,

        /*! @brief The Value is not enumerable. */
        NotEnumerable

    }; // Enumerable

    /*! @brief The state of a Message. */
    enum class MessageState
    {
        /*! @brief The Message is neither open nor closed. */
        Unknown,

        /*! @brief The Message has been opened for reading. */
        OpenForReading,

        /*! @brief The Message has been opened for writing. */
        OpenForWriting,

        /*! @brief The Message has been closed. */
        Closed

    }; // MessageState

    /*! @brief The format for the output from command-line tools. */
    enum class OutputFlavour : uint32_t
    {
        /*! @brief Normal output with no special processing. */
        Normal,

        /*! @brief Output in JSON format. Tabs and newlines are replaced with spaces. */
        JSON,

        /*! @brief Output in tab-delimited format. Tabs and newlines are replaced with
         spaces. */
        Tabs,

        /*! @brief The output format is unknown. */
        Unknown

    }; // OutputFlavour

    /*! @brief The status of a read operation on a Message. */
    enum class ReadStatus
    {
        /*! @brief Reading from the Message was successful; a @c nullptr result indicates and empty
        Message. */
        Successful,

        /*! @brief Reading from the Message was successful and all data was processed. */
        SuccessfulAtEnd,

        /*! @brief The Message was incomplete and more data is needed. */
        Incomplete,

        /*! @brief Invalid data was found in the Message and reading is not possible. */
        Invalid

    }; // ReadStatus

    /*! @brief A byte array that is the same size as an integer. */
    using NumberAsBytes = uint8_t[sizeof(int64_t)];

    /*! @brief A sequence of argument descriptors. */
    using DescriptorVector = std::vector<BaseArgumentDescriptor *>;

    /*! @brief A holder for a shared pointer to an Array. */
    using SpArray = std::shared_ptr<Array>;

    /*! @brief A holder for a shared pointer to a BufferChunk. */
    using SpBufferChunk = std::shared_ptr<BufferChunk>;

    /*! @brief A holder for a shared pointer to a Map. */
    using SpMap = std::shared_ptr<Map>;

    /*! @brief A holder for a shared pointer to a Message. */
    using SpMessage = std::shared_ptr<Message>;

    /*! @brief A holder for a shared pointer to a Set. */
    using SpSet = std::shared_ptr<Set>;

    /*! @brief A holder for a shared pointer to a String. */
    using SpString = std::shared_ptr<String>;

    /*! @brief A holder for a shared pointer to a StringBuffer. */
    using SpStringBuffer = std::shared_ptr<StringBuffer>;

    /*! @brief A holder for a shared pointer to a Value. */
    using SpValue = std::shared_ptr<Value>;

    /*! @brief A holder for a non-shared pointer to an Array. */
    using UpArray = std::unique_ptr<Array>;

    /*! @brief A holder for a non-shared pointer to a BufferChunk. */
    using UpBufferChunk = std::unique_ptr<BufferChunk>;

    /*! @brief A holder for a non-shared pointer to a Map. */
    using UpMap = std::unique_ptr<Map>;

    /*! @brief A holder for a non-shared pointer to a Message. */
    using UpMessage = std::unique_ptr<Message>;

    /*! @brief A holder for a non-shared pointer to a Set. */
    using UpSet = std::unique_ptr<Set>;

    /*! @brief A holder for a non-shared pointer to a String. */
    using UpString = std::unique_ptr<String>;

    /*! @brief A holder for a non-shared pointer to a StringBuffer. */
    using UpStringBuffer = std::unique_ptr<StringBuffer>;

    /*! @brief A holder for a non-shared pointer to an array of uint8_t values. */
    using UpAuint8_t = std::unique_ptr<uint8_t[]>;

    /*! @brief A holder for a non-shared pointer to a Value. */
    using UpValue = std::unique_ptr<Value>;

    /*! @brief A holder for a weak pointer to an Array. */
    using WpArray = std::weak_ptr<Array>;

    /*! @brief A holder for a weak pointer to a BufferChunk. */
    using WpBufferChunk = std::weak_ptr<BufferChunk>;

    /*! @brief A holder for a weak pointer to a Map. */
    using WpMap = std::weak_ptr<Map>;

    /*! @brief A holder for a weak pointer to a Message. */
    using WpMessage = std::weak_ptr<Message>;

    /*! @brief A holder for a weak pointer to a Set. */
    using WpSet = std::weak_ptr<Set>;

    /*! @brief A holder for a weak pointer to a String. */
    using WpString = std::weak_ptr<String>;

    /*! @brief A holder for a weak pointer to a StringBuffer. */
    using WpStringBuffer = std::weak_ptr<StringBuffer>;

    /*! @brief A holder for a weak pointer to a Value. */
    using WpValue = std::weak_ptr<Value>;

    /*! @brief A pointer to a handler for system signals.
     @param[in] theSignal The signal of interest. */
    using SignalHandler = void (*)
       (int theSignal);

    /*! @brief A sequence of strings. */
    using StringVector = std::vector<std::string>;

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

    /*! @brief Convert a string to a double value.
     @param[in] startPtr The string to be converted.
     @param[out] result The value represented by the string.
     @returns @c true if the string contained a representation of a double and @c false
     otherwise. */
    bool
    ConvertToDouble(const char *startPtr,
                    double      &result);
    
    /*! @brief Convert a string to an integer value.
     @param[in] startPtr The string to be converted.
     @param[out] result The value represented by the string.
     @returns @c true if the string contained a representation of an integer and @c false
     otherwise. */
    bool
    ConvertToLong(const char *startPtr,
                  int64_t    &result);

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
     @param[in] arguments If non-@c nullptr, returns the arguments for the utility.
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
                                    StringVector      *arguments = nullptr);

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

    /*! @brief Merge two DataKind values together.
     @param[in] leftValue The first value to be merged.
     @param[in] rightValue The second value to be merged.
     @returns The result of the bit-wise merge of the two values. */
    inline DataKind
    operator |(const DataKind leftValue,
               const DataKind rightValue)
    {
        return static_cast<DataKind>(static_cast<uint8_t>(leftValue) |
                                     static_cast<uint8_t>(rightValue));
    } // operator |

    /*! @brief Merge a DataKind value and an unsigned byte together.
     @param[in] leftValue The first value to be merged.
     @param[in] rightValue The second value to be merged.
     @returns The result of the bit-wise merge of the two values. */
    inline DataKind
    operator |(const DataKind leftValue,
               const uint8_t  rightValue)
    {
        return static_cast<DataKind>(static_cast<uint8_t>(leftValue) | rightValue);
    } // operator |

    /*! @brief Merge a DataKind value and an unsigned byte together.
     @param[in] leftValue The first value to be merged.
     @param[in] rightValue The second value to be merged.
     @returns The result of the bit-wise merge of the two values. */
    inline DataKind
    operator |(const uint8_t  leftValue,
               const DataKind rightValue)
    {
        return static_cast<DataKind>(leftValue | static_cast<uint8_t>(rightValue));
    } // operator |

    /*! @brief Mask an unsigned byte with a DataKind mask.
     @param[in] leftValue The first value to be combined.
     @param[in] rightValue The second value to be combined.
     @returns The result of the bit-wise masking of the two values. */
    inline DataKind
    operator &(const DataKind leftValue,
               const uint8_t  rightValue)
    {
        return static_cast<DataKind>(static_cast<uint8_t>(leftValue) & rightValue);
    } // operator &

    /*! @brief Mask an unsigned byte with a DataKind mask.
     @param[in] leftValue The first value to be combined.
     @param[in] rightValue The second value to be combined.
     @returns The result of the bit-wise masking of the two values. */
    inline DataKind
    operator &(const uint8_t  leftValue,
               const DataKind rightValue)
    {
        return static_cast<DataKind>(leftValue & static_cast<uint8_t>(rightValue));
    } // operator &

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

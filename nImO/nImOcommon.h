//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommon.h
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

#if (! defined(nImOcommon_H_))
# define nImOcommon_H_ /* Header guard */

# include <nImOconfig.h>
# include <initFileBase.h>

// Make sure that a couple of critical macros are defined!
# if (! defined(TRUE_))
#  define TRUE_  1
# endif // not defined(TRUE_)
# if (! defined(FALSE_))
#  define FALSE_ 0
# endif // not defined(FALSE_)

# undef BSD_
# if defined(__FreeBSD__)
#  define BSD_    TRUE_
# elif defined(__NetBSD__)
#  define BSD_    TRUE_
# elif defined(__OpenBSD__)
#  define BSD_    TRUE_
# elif defined(__bsdi__)
#  define BSD_    TRUE_
# elif defined(__Dragonfly__)
#  define BSD_    TRUE_
# else // ! defined(__Dragonfly__)
#  define BSD_    FALSE_
# endif // ! defined(__Dragonfly__)

# if (! defined(LINUX_))
/*! @brief @c TRUE_ if Linux, FALSE_ otherwise. */
#  if defined(__linux__)
#   define LINUX_ TRUE_
#  else // not defined(__linux__)
#   define LINUX_ FALSE_
#  endif // not defined(__linux__)
# endif // not defined(LINUX_)

# if (! defined(MAC_OR_LINUX_))
/* TRUE_ if non-Windows, FALSE_ if Windows. */
#  if defined(__APPLE__)
#   define MAC_OR_LINUX_ TRUE_
#  elif LINUX_
#   define MAC_OR_LINUX_ TRUE_
#  else // not LINUX_
#   define MAC_OR_LINUX_ BSD_
#  endif // not LINUX_
# endif // not defined(MAC_OR_LINUX_)

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
# endif // defined(__APPLE__)
# include <boost/asio.hpp>
# include <boost/optional.hpp>
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)
# include <cmath>
# include <csignal>
# include <cstdlib>
# include <cstring>
# include <iomanip>
# include <iostream>
# include <list>
# include <map>
# include <memory>
# include <mutex>
# include <queue>
# include <set>
# include <sstream>
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
#  include <iphlpapi.h>
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
# define CHAR_DOUBLEQUOTE_              "\""

/*! @brief The default name for the root part of a channel name. */
# define DEFAULT_CHANNEL_ROOT_          "channel_"

/*! @brief The line length for command-line help output. */
constexpr size_t    HELP_LINE_LENGTH_ = 250;

/*! @brief The largest IP port that is acceptable. */
constexpr int   MAXIMUM_PORT_ALLOWED_ = 65535;

/*! @brief The smallest IP port that is acceptable. */
constexpr int   MINIMUM_PORT_ALLOWED_ = 1024;

/*! @brief The character separating argument descriptors. */
# define ARGUMENT_SEPARATOR_            "\v"

/*! @brief The standard copyright holder name to use for m+m-created executables. */
# define NIMO_COPYRIGHT_NAME_           "OpenDragon"

/*! @brief The IP address for the loopback address for the machine that is running the
 executable. */
# define SELF_ADDRESS_IPADDR_           "127.0.0.1"

/*! @brief The IP name for the loopback address for the machine that is running the
 executable. */
# define SELF_ADDRESS_NAME_             "localhost"

/*! @brief The signal to use for internally-detected timeouts. */
# if MAC_OR_LINUX_
#  define STANDARD_SIGNAL_TO_USE_       SIGUSR2
# else // ! MAC_OR_LINUX_
#  define STANDARD_SIGNAL_TO_USE_       42
# endif // ! MAC_OR_LINUX_

/*! @brief A simple macro to calculate the number of elements in an array. */
# define A_SIZE(arr_)                   (sizeof(arr_) / sizeof(*arr_))

/*! @brief A simple macro to make the pointer declarations a bit more readable. */
# define Ptr(type_)                     type_ *

/*! @brief A simple macro to make the pointer declarations a bit more readable. */
# define CPtr(type_)                    const type_ *

/*! @brief A macro to make 'casts' more legible. */
# define StaticCast(type_,value_)       static_cast<type_>(value_)
/*! @brief A macro to make 'casts' more legible. */
# define ConstCast(type_,value_)        const_cast<type_>(value_)
/*! @brief A macro to make 'casts' more legible. */
# define DynamicCast(type_,value_)      dynamic_cast<type_>(value_)
/*! @brief A macro to make 'casts' more legible. */
# define ReinterpretCast(type_,value_)  reinterpret_cast<type_>(value_)

/*! @brief Return an enumerated value as its underlying type.
 { From Effective Modern C++. }
 @tparam Type The type of value being converted.
 @param[in] enumerator The value to be converted.
 @return The input value as its underlying type. */
template
    <typename   Type>
constexpr typename std::underlying_type<Type>::type
toUType
    (Type  enumerator)
    noexcept
{
    return StaticCast(typename std::underlying_type<Type>::type, enumerator);
}

using namespace boost;

# define UnaryAndBinaryOperators(Type_) \
inline constexpr Type_ \
operator~\
    (const Type_ rightValue)\
{\
    return StaticCast(Type_, ~ toUType(rightValue));\
}\
\
inline constexpr Type_ \
operator|\
    (const Type_ leftValue,\
     const Type_ rightValue)\
{\
    return StaticCast(Type_, toUType(leftValue) | toUType(rightValue));\
}\
\
inline constexpr Type_ \
operator|\
    (const Type_ leftValue,\
     const uint8_t  rightValue)\
{\
    return StaticCast(Type_, toUType(leftValue) | rightValue);\
}\
\
inline constexpr Type_ \
operator|\
    (const uint8_t  leftValue,\
     const Type_ rightValue)\
{\
    return StaticCast(Type_, leftValue | toUType(rightValue));\
}\
\
inline constexpr Type_ \
operator&\
    (const Type_ leftValue,\
     const Type_ rightValue)\
{\
    return StaticCast(Type_, toUType(leftValue) & toUType(rightValue));\
}\
\
inline constexpr Type_ \
operator&\
    (const Type_ leftValue,\
     const uint8_t  rightValue)\
{\
    return StaticCast(Type_, toUType(leftValue) & rightValue);\
}\
\
inline constexpr Type_ \
operator&\
    (const uint8_t  leftValue,\
     const Type_ rightValue)\
{\
    return StaticCast(Type_, leftValue & toUType(rightValue));\
}

namespace nImO
{
    // Forward declarations.

    class Array;
    class BaseArgumentDescriptor;
    class BufferChunk;
    class ChannelName;
    class Context;
    class Flaw;
    class Integer;
    class Logical;
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

                /*! @brief The mask for the count of the number of bytes (1..8) that contain the signed integer value.
                 Note that the count contained in the byte is one less than the actual count. */
                IntegerLongValueCountMask = 0x0007,

        /*! @brief The data that follows is one or more floating-point values. */
        Double = 0x0040,

            /*! @brief The mask for the size of the count of floating-point values. */
            DoubleCountMask = 0x0020,

            /*! @brief The count of the number of floating-point values is in the range 1..16 and is contained within this byte.
             Note that the count contained in the byte is one less than the actual count. */
            DoubleShortCount = 0x0000,

                /*! @brief The mask for the count of the number of floating-point values. */
                DoubleShortCountMask = 0x001F,

            /*! @brief The count of the number of floating-point values is contained in the next byte(s) and the size of the count (1..8) is contained in this byte.
             Note that the size of the count contained in the byte is one less than the actual size of the count; the count itself is the actual count. */
            DoubleLongCount = 0x0020,

                /*! @brief The mask for the size of the count of floating-point values. */
                DoubleLongCountMask = 0x0007,

        /*! @brief The data that follows is a String or Blob. */
        StringOrBlob = 0x0080,

            /*! @brief The mask for the type of data - String or Blob. */
            StringOrBlobTypeMask = 0x0020,

            /*! @brief The data that follows is a non-@c NULL-terminated String. */
            StringOrBlobStringValue = 0x0000,

            /*! @brief The data that follows is a Blob. */
            StringOrBlobBlobValue = 0x0020,

            /*! @brief The mask for the length of the data that follows. */
            StringOrBlobLengthMask = 0x0010,

            /*! @brief The length of the data is in the range 0..15 and is contained within this byte. */
            StringOrBlobShortLengthValue = 0x0000,

                /*! @brief The mask for the length of the data. */
                StringOrBlobShortLengthMask = 0x000F,

            /*! @brief The length of the data is contained in the next byte(s). */
            StringOrBlobLongLengthValue = 0x0010,

                /*! @brief The mask for the count of the number of bytes (1..8) that contain the length of the data.
                 Note that the count contained in the byte is one less than the actual count; the length is the actual length. */
                StringOrBlobLongLengthMask = 0x0007,

        /*! @brief The data that follows is a Logical or a Container. */
        Other = 0x00C0,

            /*! @brief The mask for the type of value that follows. */
            OtherTypeMask = 0x0030,

            /*! @brief The value is Miscellaneous. */
            OtherMiscellaneous = 0x0000,

                /*! @brief The mask for the type of Miscellaneous. */
                OtherMiscellaneousTypeMask = 0x000C,

                /*! @brief The value is a Logical. */
                OtherMiscellaneousTypeLogical = 0x0000,

                    /*! @brief The mask for the value of the Logical. */
                    OtherMiscellaneousLogicalValueMask = 0x0001,

                    /*! @brief The value is @c false. */
                    OtherMiscellaneousLogicalFalseValue = 0x0000,

                    /*! @brief The value is @c true. */
                    OtherMiscellaneousLogicalTrueValue = 0x0001,

                /*! @brief The value is an IPv4 address. */ //TBD!!!
                OtherMiscellaneousTypeIPv4Address = 0x0004,

                /*! @brief An unimplemented miscellaneous value. */
                OtherMiscellaneousTypeReserved1 = 0x0008,

                /*! @brief An unimplemented miscellaneous value. */
                OtherMiscellanouesTypeReserved2 = 0x000C,

            /*! @brief The value that follows is a Container. */
            OtherContainerStart = 0x0010,

            /*! @brief The value that preceeded this was a Container. */
            OtherContainerEnd = 0x0020,

            /*! @brief The mask for the type of Container. */
            OtherContainerTypeMask = 0x000C,

            /*! @brief The Container is an Array. */
            OtherContainerTypeArray = 0x0000,

            /*! @brief The Container is a Map. */
            OtherContainerTypeMap = 0x0004,

            /*! @brief The Container is a Set. */
            OtherContainerTypeSet = 0x0008,

            /*! @brief An unimplemented value for the Container type. */
            OtherContainerTypeReserved = 0x000C,

            /*! @brief The mask for the empty / non-empty state of the Container. */
            OtherContainerEmptyMask = 0x0001,

            /*! @brief The Container is empty; no count of the number of elements follows. */
            OtherContainerEmptyValue = 0x0000,

            /*! @brief The Container is non-empty and the count of the number of elements follows, as a signed integer value, if this is the 'start' tag.
             Note that the number of elements is offset by -17, as a negative count of elements is not possible, and a count of zero is already handled. */
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

                /*! @brief The Message is non-empty; the type flag (top two-bits) of the first Value in the Message, if the start of the Message or of the last Value in the Message,
                 if the end of the Message, is contained in the byte. */
                OtherMessageNonEmptyValue = 0x0004,

                /*! @brief The mask for the type of the immediately enclosed Value in the Message - the first Value, if the start of the Message, and the last Value if the end of the Message. */
                OtherMessageExpectedTypeMask = 0x0003,

                /*! @brief The number of positions to right-shift the type of a tag to align with the Message type value. */
                OtherMessageExpectedTypeShift = 6,

                /*! @brief The enclosed value in the Message is a signed integer. */
                OtherMessageExpectedIntegerValue = 0x0000,

                /*! @brief The enclosed value in the Message is a float-point number. */
                OtherMessageExpectedDoubleValue = 0x0001,

                /*! @brief The enclosed value in the Message is a String or Blob. */
                OtherMessageExpectedStringOrBlobValue = 0x0002,

                /*! @brief The enclosed value in the Message is a Logical or Container. */
                OtherMessageExpectedOtherValue = 0x0003,

        /*! @brief The mask for detecting the start or end of a Message. */
        StartOfMessageMask = (Other | OtherMessage | OtherMessageStartEndMask),

        /*! @brief The value for the start of a Message. */
        StartOfMessageValue = (Other | OtherMessage | OtherMessageStartValue),

        /*! @brief The value for the start of a Message. */
        EndOfMessageValue = (Other | OtherMessage | OtherMessageEndValue),

        /*! @brief A value that will not normally appear in a Message. */
        EscapeValue = (Other | OtherContainerStart | OtherContainerTypeReserved)

    }; // DataKind

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

    /*! @brief The transport mechanism to use. */
    enum class TransportType : uint8_t
    {
        /*! @brief The transport mechanism is unknown. */
        kUnknown =  0x00,

        /*! @brief Use TCP for the transport mechanism. */
        kTCP =      0x01,

        /*! @brief Use UDP for the transport mechanism. */
        kUDP =      0x02,

        /*! @brief Any transport mechanism is allowed. */
        kAny =      0x7F

    }; // TransportType

    /*! @brief A network connection description. */
    struct Connection
    {
        /*! @brief The IP address of the connection.*/
        uint32_t    _address{0};

        /*! @brief The port of the connection. */
        uint16_t    _port{0};

        /*! @brief The transport mechanism of the connection. */
        TransportType   _transport{TransportType::kTCP};

        /*! @brief The constructor.
         @param[in] address The IP address for the connection.
         @param[in] port The port for the connection.
         @param[in] transport The transport mechanism for the connection. */
        inline Connection
            (const uint32_t         address = 0,
             const uint16_t         port = 0,
             const TransportType    transport = TransportType::kTCP) :
                _address(address), _port(port), _transport(transport)
        {
        }

        /*! @brief Return @c true if the two Connections are equal.
         @param[in] other The Connnection to be compared with.
         @return @c true if the two Connections are comparable and equal. */
        inline bool
        operator==
            (const Connection & other)
            const
        {
            return ((_address == other._address) && (_port == other._port) && (_transport == other._transport));
        }

        /*! @brief Return @c false if the two Connections are equal.
         @param[in] other The Connnection to be compared with.
         @return @c false if the two Connections are comparable and equal. */
        inline bool
        operator!=
            (const Connection & other)
            const
        {
            return ((_address != other._address) || (_port != other._port) || (_transport != other._transport));
        }

    }; // Connection

    /*! @brief A pointer to a function that can be invoked when help is requested, to
     provide more detailed information on the arguments to an application.
     @param[in,out] outStream The stream to write to. */
    typedef void
        (* HelpFunction)
            (std::ostream & outStream);

    namespace internal_
    {
        /*! @brief A function used to suppress 'unused variable' warnings.
         @tparam Type_ The type of value being ignored. */
        template
            <typename Type_>
        void
        ignore_unused_variable_
            (const Type_ &)
        {
        }

    }; // internal_

/*! @brief Suppress warnings about unused variables. */
# define NIMO_UNUSED_VAR_(var_)  nImO::internal_::ignore_unused_variable_(var_)

    /*! @brief The minimum count representable in a short floating point. */
    const int   DataKindDoubleShortCountMinValue = 1;

    /*! @brief The maximum count representable in a short floating point. */
    const int   DataKindDoubleShortCountMaxValue = 32;

    /*! @brief The minimum value representable in a short signed integer. */
    const int   DataKindIntegerShortValueMinValue = -16;

    /*! @brief The maximum value representable in a short signed integer. */
    const int   DataKindIntegerShortValueMaxValue = 15;

    /*! @brief The minimum count representable in a short floating point. */
    const int   DataKindStringOrBlobShortLengthMinValue = 0;

    /*! @brief The maximum count representable in a short floating point. */
    const int   DataKindStringOrBlobShortLengthMaxValue = 15;

    /*! @brief A byte array that is the same size as an integer. */
    using NumberAsBytes = uint8_t[sizeof(int64_t)];

    /*! @brief A sequence of bytes. */
    using ByteVector = std::vector<uint8_t>;

    /*! @brief A sequence of argument descriptors. */
    using DescriptorVector = std::vector<BaseArgumentDescriptor *>;

    /*! @brief The table type used for lookups. */
    using StringSet = std::set<std::string>;

    /*! @brief A holder for a shared pointer to an Array. */
    using SpArray = std::shared_ptr<Array>;

    /*! @brief A holder for a shared pointer to a BaseArgumentDescriptor. */
    using SpBaseArgumentDescriptor = std::shared_ptr<BaseArgumentDescriptor>;

    /*! @brief A holder for a shared pointer to a BufferChunk. */
    using SpBufferChunk = std::shared_ptr<BufferChunk>;

    /*! @brief A holder for a shared pointer to a ChannelName. */
    using SpChannelName = std::shared_ptr<ChannelName>;

    /*! @brief A holder for a shared pointer to a Flaw. */
    using SpFlaw = std::shared_ptr<Flaw>;

    /*! @brief A holder for a shared pointer to a Flaw. */
    using SpInteger = std::shared_ptr<Integer>;

    /*! @brief A holder for a shared pointer to a Flaw. */
    using SpLogical = std::shared_ptr<Logical>;

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

    /*! @brief A holder for a non-shared pointer to a Flaw. */
    using UpFlaw = std::unique_ptr<Flaw>;

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

    /*! @brief A holder for a weak pointer to a Flaw. */
    using WpFlaw = std::weak_ptr<Flaw>;

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

    /*! @brief A pointer to a handler for interrupt signals. */
    using SignalFunction = void (*)
       (void);

    /*! @brief A pointer to a handler for system signals.
     @param[in] theSignal The signal of interest. */
    using SignalHandler = void (*)
       (const int theSignal);

    /*! @brief A sequence of strings. */
    using StringVector = std::vector<std::string>;

    /*! @brief Contains @c true if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<bool, std::string>    SuccessOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, bool> BoolOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, int64_t> IntOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<SuccessOrFailure, StringSet>   StringSetOrFailure;

    // Methods.

    /*! @brief Convert a set of bytes into a floating-point value.
     @param[in] inString The byte string to be processed.
     @return The floating-point value stored in the bytes. */
    double
    B2D
        (const NumberAsBytes &  inString);

    /*! @brief Convert a set of bytes into an integer value.
     @param[in] inString The byte string to be processed.
     @param[in] numBytes The number of bytes to be processed.
     @return The integer value stored in the bytes. */
    int64_t
    B2I
        (const NumberAsBytes &  inString,
         const size_t           numBytes);

    /*! @brief Return @c true if standard input can be used and @c false otherwise.
     @return @c true if standard input can be used and @c false otherwise. */
    bool
    CanReadFromStandardInput
        (void);

    /*! @brief Compare two byte strings.
     @param[in] first The first byte string.
     @param[in] second The second byte string.
     @param[in] numBytes The number of bytes to be compared.
     @return @c 0 if the two byte strings are identical or the positive index (1-origin) where the
     two byte strings differ. */
    size_t
    CompareBytes
        (CPtr(void)     first,
         CPtr(void)     second,
         const size_t   numBytes);

    /*! @brief Construct a node name.
     @param[in] nameFromOptions The name to be used if provided via a command-line option.
     @param[in] suffixIfNotFromOptions If nameFromOptions is blank, construct a name with this as the suffix.
     @param[in] tag The tag to be applied to the name.
     @return The constructed node name. */
    std::string
    ConstructNodeName
        (const std::string  nameFromOptions,
         const std::string  suffixIfNotFromOptions,
         const std::string  tag);

    /*! @brief Introduce some delay in processing.
     @param[in] context The active runtime environment.
     @param[in] amount The fraction of a second to delay. */
    void
    ConsumeSomeTime
        (Ptr(Context)   context,
         const double   factor = 200.0);

    /*! @brief Convert a double value to a string.
     @param[in] value The value to be represented in the string.
     @return The string representation of the value. */
    std::string
    ConvertDoubleToString
        (const double   value);

    /*! @brief Convert a string to a double value.
     @param[in] startPtr The string to be converted.
     @param[out] result The value represented by the string.
     @return @c true if the string contained a representation of a double and @c false
     otherwise. */
    bool
    ConvertToDouble
        (CPtr(char) startPtr,
         double &   result);

    /*! @brief Convert a string to a double value.
     @param[in] aString The string to be converted.
     @param[out] result The value represented by the string.
     @return @c true if the string contained a representation of a double and @c false
     otherwise. */
    bool
    ConvertToDouble
        (const std::string &    aString,
         double &               result);

    /*! @brief Convert a string to an integer value.
     @param[in] startPtr The string to be converted.
     @param[out] result The value represented by the string.
     @return @c true if the string contained a representation of an integer and @c false
     otherwise. */
    bool
    ConvertToInt64
        (CPtr(char) startPtr,
         int64_t &  result);

    /*! @brief Convert a string to an integer value.
     @param[in] aString The string to be converted.
     @param[out] result The value represented by the string.
     @return @c true if the string contained a representation of an integer and @c false
     otherwise. */
    bool
    ConvertToInt64
        (const std::string &    aString,
         int64_t &              result);

    /*! @brief Convert a floating-point value into a set of bytes.
     @param[in] inValue The number to be converted.
     @param[out] outString The byte string to be filled. */
    void
    D2B
        (const double       inValue,
         NumberAsBytes &    outString);

    /*! @brief Write out a block of memory as a formatted dump to standard error.
     @param[in] address Starting address of memory to dump.
     @param[in] numBytes The number of bytes to dump. */
    void
    DumpMemoryToStandardError
        (CPtr(void)     address,
         const size_t   numBytes);

    /*! @brief Return a random string of hexadecimal digits.
     @return A random string of hexadecimal digits. */
    std::string
    GetRandomHexString
        (void);

    /*! @brief Return the short form of the computer name.
     @return The short form of the computer name. */
    std::string
    GetShortComputerName
        (void);

    /*! @brief Convert an integer value into a set of bytes and return the minimum number of bytes
     needed to represent the value.
     @param[in] inValue The number to be converted.
     @param[out] outString The byte string to be filled.
     @return The minimum number of bytes needed to represent the value. */
    size_t
    I2B
        (const int64_t      inValue,
         NumberAsBytes &    outString);

    /*! @brief Construct a tab-delimited string from the command-line.
     @param[in] numArgs The number of arguments.
     @param[in] args The arguments.
     @return A tab-delimited string containing the arguments. */
    std::string
    MakeStringFromComandLine
        (const int      numArgs,
         Ptr(Ptr(char)) args);

    /*! @brief Return the name of a signal.
     @param[in] theSignal The signal of interest.
     @return A string description of the signal. */
    CPtr(char)
    NameOfSignal
        (const int  theSignal);

    UnaryAndBinaryOperators(DataKind)

    UnaryAndBinaryOperators(TransportType)

    /*! @brief Write out a (possibly multi-line) description.
     @param[in,out] outStream The stream to write to.
     @param[in] heading The text to appear on the first line before the beginning of the
     description.
     @param[in] description The description, which may contain multiple newlines. */
    void
    OutputDescription
        (std::ostream &         outStream,
         CPtr(char)             heading,
         const std::string &    description);

    /*! @brief Return a random number in the interval 0..RANDMAX.
     @return A value in the range 0..RANDMAX. */
    uint32_t
    RandomUnsigned
        (void);

    /*! @brief Write out the versions of libraries used, if enabled via the build flag. */
    void
    ReportVersions
        (void);

    /*! @brief Standardize the handling of multiple TransportType value specifications.
     @param[in] firstTransport A TransportType value.
     @param[in] secondTransport Another TransportType value.
     @param[in] defaultTransport The TransportType value to use if nothing else is resolveable.
     @return The TransportType value to be used. */
    TransportType
    ResolveTransport
        (const TransportType    firstTransport,
         const TransportType    secondTransport,
         const TransportType    defaultTransport = TransportType::kUnknown);

    /*! @brief Return a string with special characters escaped.
     @param[in] inString The string to be processed.
     @param[in] allowDoubleQuotes @c true if double quotes aren't escaped and @c false otherwise.
     @return A string with special characters escaped. */
    std::string
    SanitizeString
        (const std::string &    inString,
         const bool             allowDoubleQuotes = false);

    /*! @brief Connect the standard signals to a handler.
     @param[in] theHandler The new handler for the signals. */
    void
    SetSignalHandlers
        (SignalHandler  theHandler);

    /*! @brief Checks a network port number for validity.
     @param[in] aPort The port number to be checked.
     @param[in] systemAllowed @c true if system port numbers are valid and @c false otherwise.
     @return @c true if the port number is valid and @c false otherwise. */
    inline bool
    ValidPortNumber
        (const int  aPort,
         const bool systemAllowed = false)
    {
        return (((systemAllowed ? 0 : MINIMUM_PORT_ALLOWED_) <= aPort) && (MAXIMUM_PORT_ALLOWED_ >= aPort));
    }

    /*! @brief The character that is used with 'blob' data formatting. */
    extern const char   kBlobSeparator;

    /*! @brief The character that ends an Array value. */
    extern const char   kEndArrayChar;

    /*! @brief The character that ends a Map value. */
    extern const char   kEndMapChar;

    /*! @brief The character that ends a string. */
    extern const char   kEndOfString;

    /*! @brief The character that ends a Set value. */
    extern const char   kEndSetChar;

    /*! @brief The character that separates a key from a value in a key/value pair. */
    extern const char   kKeyValueSeparator;

    /*! @brief A character that brackets a string value. */
    extern const char   kSingleQuote;

    /*! @brief The character that starts an Array value. */
    extern const char   kStartArrayChar;

    /*! @brief The character that starts a Map value. */
    extern const char   kStartMapChar;

    /*! @brief The character that starts a Set value. */
    extern const char   kStartSetChar;

    /*! @brief A character that brackets a string value. */
    extern const uint8_t    kDoubleQuote;

    /*! @brief The escape character. */
    extern const uint8_t    kEscapeChar;

    /*! @brief The directory separator string. */
    extern const std::string    kDirectorySeparator;

    /*! @brief The status separator string. */
    extern const std::string    kStatusSeparator;

} // nImO

#endif // not defined(nImOcommon_H_)

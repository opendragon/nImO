//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOmessageInsertTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
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
//  Created:    2016-04-24
//
//--------------------------------------------------------------------------------------------------

#include <nImOarray.hpp>
#include <nImOblob.hpp>
#include <nImObufferChunk.hpp>
#include <nImOdouble.hpp>
#include <nImOinteger.hpp>
#include <nImOlogical.hpp>
#include <nImOmap.hpp>
#include <nImOmessage.hpp>
#include <nImOset.hpp>
#include <nImOstring.hpp>
#include <nImOstringBuffer.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The test driver for the unit tests of the %nImO common library. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace nImO;
using std::cerr;
using std::cout;
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief The signal handler to catch requests to stop the service.
 @param[in] signal The signal being handled. */
static void
catchSignal(int signal)
{
    ODL_ENTER(); //####
    ODL_LL1("signal = ", signal); //####
    std::string message("Exiting due to signal ");
    
    message += std::to_string(signal);
    message += " = ";
    message += NameOfSignal(signal);
#if 0
    nImO_ERROR_(message.c_str());
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

/*! @brief Put a Value into a Message and verify what was stored.
 @param[in,out] stuff The Message to be modified.
 @param[in] aValue The Value to be added to the Message.
 @param[in] expectedContents1 The expected contents of the Message.
 @param[in] expectedSize1 The expected size of the Message.
 @param[in] expectedContents2 The expected contents of the Message when prepared for transmission.
 @param[in] expectedSize2 The expected size of the contents of the Message when prepared for
 transmission.
 @returns Zero on success and non-zero on failure. */
static int
setValueAndCheck(Message        &stuff,
                 const Value    &aValue,
                 const DataKind *expectedContents1,
                 const size_t   expectedSize1,
                 const uint8_t  *expectedContents2,
                 const size_t   expectedSize2)
{
    ODL_ENTER(); //####
    ODL_P4("stuff = ", &stuff, "aValue = ", &aValue, "expectedContents1 = ", //####
           expectedContents1, "expectedContents2 = ", expectedContents2); //####
    ODL_LL2("expectedSize1 = ", expectedSize1, "expectedSize2 = ", expectedSize2); //####
    stuff.open(true);
    stuff.setValue(aValue);
    stuff.close();
    auto   contents1(stuff.getBytes());
    size_t length1 = contents1.size();
    int    result;

    ODL_PACKET("expectedContents1", expectedContents1, expectedSize1); //####
    ODL_PACKET("contents1", contents1.data(), length1); //####
    if (expectedSize1 == length1)
    {
        result = static_cast<int>(CompareBytes(expectedContents1, contents1.data(),
                                               expectedSize1));
        if (0 == result)
        {
            if (expectedContents2 && expectedSize2)
            {
                std::string contents2(stuff.getBytesForTransmission());
                size_t      length2 = contents2.size();

                ODL_PACKET("expectedContents2", expectedContents2, expectedSize2); //####
                ODL_PACKET("contents2", contents2.data(), length2); //####
                if (expectedSize2 == length2)
                {
                    result = static_cast<int>(CompareBytes(expectedContents2, contents2.data(),
                                                           expectedSize2));
                }
                else
                {
                    ODL_LOG("! (expectedSize2 == length2)"); //####
                    result = 1;
                }
            }
        }
    }
    else
    {
        ODL_LOG("! (expectedSize1 == length1)"); //####
        result = 1;
    }
    ODL_EXIT_LL(result); //####
    return result;
} // setValueAndCheck

#if defined(__APPLE__)
# pragma mark *** Test Case 001 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyMessage(const char *launchPath,
                         const int  argc,
                         char       **argv) // empty message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedEmptyBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            const size_t  expectedEmptyByteCount = (sizeof(expectedEmptyBytes) /
                                                    sizeof(*expectedEmptyBytes));
            ODL_PACKET("expectedBytes", expectedEmptyBytes, expectedEmptyByteCount); //####
            auto   contents1(stuff->getBytes());
            size_t length1 = contents1.size();

            stuff->open(true);
            if (0 != length1)
            {
                ODL_LOG("(0 != length1)"); //####
            }
            else
            {
                stuff->close();
                contents1 = stuff->getBytes();
                length1 = contents1.size();
                ODL_PACKET("contents", contents1.data(), length1); //####
                if (expectedEmptyByteCount == length1)
                {
                    result = static_cast<int>(CompareBytes(expectedEmptyBytes, contents1.data(),
                                                           expectedEmptyByteCount));
                    if (0 == result)
                    {
                        static const uint8_t transmitEmptyBytes[] =
                        {
                            0xF0, // Start of message
                            0xF8, // End of message
                            0x17 // Checksum
                        };
                        const size_t transmitEmptyByteCount = (sizeof(transmitEmptyBytes) /
                                                               sizeof(*transmitEmptyBytes));
                        std::string  contents2(stuff->getBytesForTransmission());
                        size_t       length2 = contents2.size();

                        ODL_PACKET("transmitEmptyBytes", transmitEmptyBytes, //####
                                   transmitEmptyByteCount); //####
                        ODL_PACKET("contents2", contents2.data(), length2); //####
                        if (transmitEmptyByteCount == length2)
                        {
                            result = static_cast<int>(CompareBytes(transmitEmptyBytes,
                                                                   contents2.data(),
                                                                   transmitEmptyByteCount));
                        }
                        else
                        {
                            ODL_LOG("! (transmitEmptyByteCount == length2)"); //####
                            result = 1;
                        }
                    }
                }
                else
                {
                    ODL_LOG("! (expectedEmptyByteCount == length1)"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertEmptyMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertLogicalMessage(const char *launchPath,
                           const int  argc,
                           char       **argv) // boolean message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedTrueBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalTrueValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedTrueByteCount = (sizeof(expectedTrueBytes) /
                                                  sizeof(*expectedTrueBytes));
            static const DataKind expectedFalseBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedFalseByteCount = (sizeof(expectedFalseBytes) /
                                                   sizeof(*expectedFalseBytes));
            static const uint8_t transmitFalseBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xC0, // Logical False
                0xFF, // End of message, last is Other
                0x49 // Checksum
            };
            const size_t transmitFalseByteCount = (sizeof(transmitFalseBytes) /
                                                   sizeof(*transmitFalseBytes));
            static const uint8_t transmitTrueBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xC1, // Logical true
                0xFF, // End of message, last is Other
                0x48 // Checksum
            };
            const size_t transmitTrueByteCount = (sizeof(transmitTrueBytes) /
                                                  sizeof(*transmitTrueBytes));
            Logical falseValue(false);
            Logical trueValue(true);

            result = setValueAndCheck(*stuff, trueValue, expectedTrueBytes, expectedTrueByteCount,
                                      transmitTrueBytes, transmitTrueByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, falseValue, expectedFalseBytes,
                                          expectedFalseByteCount, transmitFalseBytes,
                                          transmitFalseByteCount);
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertLogicalMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertTinyIntegerMessage(const char *launchPath,
                               const int  argc,
                               char       **argv) // tiny integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedMinus12Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  (-12 & DataKind::IntegerShortValueValueMask),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus12ByteCount = (sizeof(expectedMinus12Bytes) /
                                                     sizeof(*expectedMinus12Bytes));
            static const DataKind expectedZeroBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  0,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedZeroByteCount = (sizeof(expectedZeroBytes) /
                                                  sizeof(*expectedZeroBytes));
            static const DataKind expectedPlus12Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  (12 & DataKind::IntegerShortValueValueMask),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus12ByteCount = (sizeof(expectedPlus12Bytes) /
                                                    sizeof(*expectedPlus12Bytes));
            static const uint8_t transmitMinus12Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x14, // Integer -12
                0xFC, // End of message, last is Integer
                0xFB // Checksum
            };
            const size_t transmitMinus12ByteCount = (sizeof(transmitMinus12Bytes) /
                                                   sizeof(*transmitMinus12Bytes));
            static const uint8_t transmitZeroBytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x00, // Integer 0
                0xFC, // End of message, last is Integer
                0x0F // Checksum
            };
            const size_t transmitZeroByteCount = (sizeof(transmitZeroBytes) /
                                                  sizeof(*transmitZeroBytes));
            static const uint8_t transmitPlus12Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x0C, // Integer 12
                0xFC, // End of message, last is Integer
                0x03 // Checksum
            };
            const size_t transmitPlus12ByteCount = (sizeof(transmitPlus12Bytes) /
                                                     sizeof(*transmitPlus12Bytes));
            Integer minus12Value(-12);
            Integer zeroValue(0);
            Integer plus12Value(12);

            result = setValueAndCheck(*stuff, minus12Value, expectedMinus12Bytes,
                                      expectedMinus12ByteCount, transmitMinus12Bytes,
                                      transmitMinus12ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, zeroValue, expectedZeroBytes,
                                          expectedZeroByteCount, transmitZeroBytes,
                                          transmitZeroByteCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus12Value, expectedPlus12Bytes,
                                          expectedPlus12ByteCount, transmitPlus12Bytes,
                                          transmitPlus12ByteCount);
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertTinyIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertShortIntegerMessage(const char *launchPath,
                                const int  argc,
                                char       **argv) // short integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedMinus144Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((2 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0xFF), static_cast<DataKind>(0x70),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus144ByteCount = (sizeof(expectedMinus144Bytes) /
                                                      sizeof(*expectedMinus144Bytes));
            static const DataKind expectedPlus144Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((2 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x90),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus144ByteCount = (sizeof(expectedPlus144Bytes) /
                                                     sizeof(*expectedPlus144Bytes));
            static const uint8_t transmitMinus144Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x21, 0xFF, 0x70, // Integer -144
                0xFC, // End of message, last is Integer
                0x7F // Checksum
            };
            const size_t transmitMinus144ByteCount = (sizeof(transmitMinus144Bytes) /
                                                      sizeof(*transmitMinus144Bytes));
            static const uint8_t transmitPlus144Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x21, 0x00, 0x90, // Integer 144
                0xFC, // End of message, last is Integer
                0x5E // Checksum
            };
            const size_t transmitPlus144ByteCount = (sizeof(transmitPlus144Bytes) /
                                                     sizeof(*transmitPlus144Bytes));
            Integer minus144Value(-144);
            Integer plus144Value(144);

            result = setValueAndCheck(*stuff, minus144Value, expectedMinus144Bytes,
                                      expectedMinus144ByteCount, transmitMinus144Bytes,
                                      transmitMinus144ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus144Value, expectedPlus144Bytes,
                                          expectedPlus144ByteCount, transmitPlus144Bytes,
                                          transmitPlus144ByteCount);
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertShortIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertMediumIntegerMessage(const char *launchPath,
                                 const int  argc,
                                 char       **argv) // medium integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedMinus1234567Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((3 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0xED), static_cast<DataKind>(0x29),
                static_cast<DataKind>(0x79),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus1234567ByteCount = (sizeof(expectedMinus1234567Bytes) /
                                                          sizeof(*expectedMinus1234567Bytes));
            static const DataKind expectedPlus1234567Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((3 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0xD6),
                static_cast<DataKind>(0x87),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus1234567ByteCount = (sizeof(expectedPlus1234567Bytes) /
                                                         sizeof(*expectedPlus1234567Bytes));
            static const uint8_t transmitMinus1234567Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x22, 0xED, 0x29, 0x79, // Integer -1234567
                0xFC, // End of message, last is Integer
                0x5E // Checksum
            };
            const size_t transmitMinus1234567ByteCount = (sizeof(transmitMinus1234567Bytes) /
                                                          sizeof(*transmitMinus1234567Bytes));
            static const uint8_t transmitPlus1234567Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x22, 0x12, 0xD6, 0x87, // Integer 1234567
                0xFC, // End of message, last is Integer
                0x7E // Checksum
            };
            const size_t transmitPlus1234567ByteCount = (sizeof(transmitPlus1234567Bytes) /
                                                         sizeof(*transmitPlus1234567Bytes));
            Integer minus1234567Value(-1234567);
            Integer plus1234567Value(1234567);

            result = setValueAndCheck(*stuff, minus1234567Value, expectedMinus1234567Bytes,
                                      expectedMinus1234567ByteCount, transmitMinus1234567Bytes,
                                      transmitMinus1234567ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus1234567Value, expectedPlus1234567Bytes,
                                          expectedPlus1234567ByteCount, transmitPlus1234567Bytes,
                                          transmitPlus1234567ByteCount);
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertMediumIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertBigIntegerMessage(const char *launchPath,
                              const int  argc,
                              char       **argv) // big integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedMinusBigNumberBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((6 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0xED), static_cast<DataKind>(0xCB),
                static_cast<DataKind>(0xA9), static_cast<DataKind>(0x87),
                static_cast<DataKind>(0x65), static_cast<DataKind>(0x44),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinusBigNumberByteCount = (sizeof(expectedMinusBigNumberBytes) /
                                                            sizeof(*expectedMinusBigNumberBytes));
            static const DataKind expectedPlusBigNumberBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((6 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x34),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x78),
                static_cast<DataKind>(0x9A), static_cast<DataKind>(0xBC),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlusBigNumberByteCount = (sizeof(expectedPlusBigNumberBytes) /
                                                           sizeof(*expectedPlusBigNumberBytes));
            static const uint8_t transmitMinusBigNumberBytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x25, 0xED, 0xCB, 0xA9, 0x87, 0x65, 0x44, // Integer -20015998343868
                0xFC, // End of message, last is Integer
                0x59 // Checksum
            };
            const size_t transmitMinusBigNumberByteCount = (sizeof(transmitMinusBigNumberBytes) /
                                                            sizeof(*transmitMinusBigNumberBytes));
            static const uint8_t transmitPlusBigNumberBytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x25, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, // Integer 20015998343868
                0xFC, // End of message, last is Integer
                0x80 // Checksum
            };
            const size_t transmitPlusBigNumberByteCount = (sizeof(transmitPlusBigNumberBytes) /
                                                           sizeof(*transmitPlusBigNumberBytes));
            Integer minusBigNumberValue(-20015998343868);
            Integer plusBigNumberValue(20015998343868);

            result = setValueAndCheck(*stuff, minusBigNumberValue, expectedMinusBigNumberBytes,
                                      expectedMinusBigNumberByteCount, transmitMinusBigNumberBytes,
                                      transmitMinusBigNumberByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plusBigNumberValue, expectedPlusBigNumberBytes,
                                          expectedPlusBigNumberByteCount,
                                          transmitPlusBigNumberBytes,
                                          transmitPlusBigNumberByteCount);
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertBigIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 007 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyStringMessage(const char *launchPath,
                               const int  argc,
                               char       **argv) // empty string message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedEmptyStringBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyStringByteCount = (sizeof(expectedEmptyStringBytes) /
                                                         sizeof(*expectedEmptyStringBytes));
            static const uint8_t transmitEmptyStringBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0x80, // String - empty
                0xFE, // End of message, last is String or Blob
                0x8B // Checksum
            };
            const size_t transmitEmptyStringByteCount = (sizeof(transmitEmptyStringBytes) /
                                                         sizeof(*transmitEmptyStringBytes));
            String emptyStringValue("");

            result = setValueAndCheck(*stuff, emptyStringValue, expectedEmptyStringBytes,
                                      expectedEmptyStringByteCount, transmitEmptyStringBytes,
                                      transmitEmptyStringByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertEmptyStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 008 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertShortStringMessage(const char *launchPath,
                               const int  argc,
                               char       **argv) // short string message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedShortStringBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (6 & DataKind::StringOrBlobShortLengthMask),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortStringByteCount = (sizeof(expectedShortStringBytes) /
                                                         sizeof(*expectedShortStringBytes));
            static const uint8_t transmitShortStringBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0x86, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, // String - 'abcdef'
                0xFE, // End of message, last is String or Blob
                0x30 // Checksum
            };
            const size_t transmitShortStringByteCount = (sizeof(transmitShortStringBytes) /
                                                         sizeof(*transmitShortStringBytes));
            String shortStringValue("abcdef");

            result = setValueAndCheck(*stuff, shortStringValue, expectedShortStringBytes,
                                      expectedShortStringByteCount, transmitShortStringBytes,
                                      transmitShortStringByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertShortStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 009 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertMediumStringMessage(const char *launchPath,
                                const int  argc,
                                char       **argv) // medium string message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedMediumStringBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobLongLengthValue |
                  ((1 - 1) & DataKind::StringOrBlobLongLengthMask),
                static_cast<DataKind>(42),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                static_cast<DataKind>('a'), static_cast<DataKind>('b'),
                static_cast<DataKind>('c'), static_cast<DataKind>('d'),
                static_cast<DataKind>('e'), static_cast<DataKind>('f'),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedMediumStringByteCount = (sizeof(expectedMediumStringBytes) /
                                                          sizeof(*expectedMediumStringBytes));
            static const uint8_t transmitMediumStringBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0x90, 0x2A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, // String - 'abcdef'*7, length = 42
                0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                0xFE, // End of message, last is String or Blob
                0xFE // Checksum
            };
            const size_t transmitMediumStringByteCount = (sizeof(transmitMediumStringBytes) /
                                                          sizeof(*transmitMediumStringBytes));
            String mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

            result = setValueAndCheck(*stuff, mediumStringValue, expectedMediumStringBytes,
                                      expectedMediumStringByteCount, transmitMediumStringBytes,
                                      transmitMediumStringByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertMediumStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 010 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyBlobMessage(const char *launchPath,
                             const int  argc,
                             char       **argv) // empty blob message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedEmptyBlobBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyBlobByteCount = (sizeof(expectedEmptyBlobBytes) /
                                                       sizeof(*expectedEmptyBlobBytes));
            static const uint8_t transmitEmptyBlobBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xA0, // Empty Blob
                0xFE, // End of message, last is String or Blob
                0x6B // Checksum
            };
            const size_t transmitEmptyBlobByteCount = (sizeof(transmitEmptyBlobBytes) /
                                                       sizeof(*transmitEmptyBlobBytes));
            Blob emptyBlobValue;

            result = setValueAndCheck(*stuff, emptyBlobValue, expectedEmptyBlobBytes,
                                      expectedEmptyBlobByteCount, transmitEmptyBlobBytes,
                                      transmitEmptyBlobByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertEmptyBlobMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 011 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertShortBlobMessage(const char *launchPath,
                             const int  argc,
                             char       **argv) // short blob message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedShortBlobBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (6 & DataKind::StringOrBlobShortLengthMask),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortBlobByteCount = (sizeof(expectedShortBlobBytes) /
                                                       sizeof(*expectedShortBlobBytes));
            static const uint8_t actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t actualDataCount = (sizeof(actualData) / sizeof(*actualData));
            static const uint8_t transmitShortBlobBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xA6, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, // Short Blob
                0xFE, // End of message, last is String or Blob
                0xFA // Checksum
            };
            const size_t transmitShortBlobByteCount = (sizeof(transmitShortBlobBytes) /
                                                       sizeof(*transmitShortBlobBytes));
            Blob shortBlobValue(actualData, actualDataCount);

            result = setValueAndCheck(*stuff, shortBlobValue, expectedShortBlobBytes,
                                      expectedShortBlobByteCount, transmitShortBlobBytes,
                                      transmitShortBlobByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertShortBlobMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 012 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertMediumBlobMessage(const char *launchPath,
                              const int  argc,
                              char       **argv) // medium blob message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedMediumBlobBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobLongLengthValue |
                  ((1 - 1) & DataKind::StringOrBlobLongLengthMask),
                static_cast<DataKind>(42),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x23),
                static_cast<DataKind>(0x34), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x67),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedMediumBlobByteCount = (sizeof(expectedMediumBlobBytes) /
                                                        sizeof(*expectedMediumBlobBytes));
            static const uint8_t actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t actualDataCount = (sizeof(actualData) / sizeof(*actualData));
            static const uint8_t transmitMediumBlobBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xB0, 0x2A, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, // Medium Blob, length = 42
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0xFE, // End of message, last is String or Blob
                0x44 // Checksum
            };
            const size_t transmitMediumBlobByteCount = (sizeof(transmitMediumBlobBytes) /
                                                        sizeof(*transmitMediumBlobBytes));
            Blob mediumBlobValue(actualData, actualDataCount);

            result = setValueAndCheck(*stuff, mediumBlobValue, expectedMediumBlobBytes,
                                      expectedMediumBlobByteCount, transmitMediumBlobBytes,
                                      transmitMediumBlobByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertMediumBlobMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 013 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertSingleFloatMessage(const char *launchPath,
                               const int  argc,
                               char       **argv) // single float message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedPlus42Point5Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - DataKindDoubleShortCountMinValue) &
                    DataKind::DoubleShortCountMask),
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            const size_t expectedPlus42Point5ByteCount = (sizeof(expectedPlus42Point5Bytes) /
                                                          sizeof(*expectedPlus42Point5Bytes));
            static const DataKind expectedMinus42Point5Bytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - DataKindDoubleShortCountMinValue) &
                    DataKind::DoubleShortCountMask),
                static_cast<DataKind>(0xC0), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            const size_t expectedMinus42Point5ByteCount = (sizeof(expectedMinus42Point5Bytes) /
                                                           sizeof(*expectedMinus42Point5Bytes));
            static const uint8_t transmitMinus42Point5Bytes[] =
            {
                0xF5, // Start of message, next is Floating-point
                0x40, 0xC0, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // one Double value, -42.5
                0xFD, // End of message, last is Floating-point
                0x88 // Checksum
            };
            const size_t transmitMinus42Point5ByteCount = (sizeof(transmitMinus42Point5Bytes) /
                                                           sizeof(*transmitMinus42Point5Bytes));
            static const uint8_t transmitPlus42Point5Bytes[] =
            {
                0xF5, // Start of message, next is Floating-point
                0x40, 0x40, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // one Double value, 42.5
                0xFD, // End of message, last is Floating-point
                0x08 // Checksum
            };
            const size_t transmitPlus42Point5ByteCount = (sizeof(transmitPlus42Point5Bytes) /
                                                          sizeof(*transmitPlus42Point5Bytes));
            Double plus42Point5(42.5);
            Double minus42Point5(-42.5);

            result = setValueAndCheck(*stuff, plus42Point5, expectedPlus42Point5Bytes,
                                      expectedPlus42Point5ByteCount, transmitPlus42Point5Bytes,
                                      transmitPlus42Point5ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, minus42Point5, expectedMinus42Point5Bytes,
                                          expectedMinus42Point5ByteCount,
                                          transmitMinus42Point5Bytes,
                                          transmitMinus42Point5ByteCount);
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertSingleFloatMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 014 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertMultipleEscapesMessage(const char *launchPath,
                                   const int  argc,
                                   char       **argv) // message with multiple escapes
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;
    
    try
    {
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind expectedMultipleEscapesBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                DataKind::OtherMessageNonEmptyValue |
                DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                DataKind::StringOrBlobShortLengthValue |
                (10 & DataKind::StringOrBlobShortLengthMask),
                static_cast<DataKind>(0xDC), static_cast<DataKind>(0xF0),
                static_cast<DataKind>(0xF1), static_cast<DataKind>(0xF2),
                static_cast<DataKind>(0x0D), static_cast<DataKind>(0xF3),
                static_cast<DataKind>(0xF4), static_cast<DataKind>(0xF5),
                static_cast<DataKind>(0xF6), static_cast<DataKind>(0xF7),
                // End of Message
                DataKind::EndOfMessageValue |
                DataKind::OtherMessageNonEmptyValue |
                DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedMultipleEscapesByteCount = (sizeof(expectedMultipleEscapesBytes) /
                                                             sizeof(*expectedMultipleEscapesBytes));
            static const uint8_t actualData[] =
            {
                0xDC, 0xF0, 0xF1, 0xF2, 0x0D, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7
            };
            const size_t actualDataCount = (sizeof(actualData) / sizeof(*actualData));
            static const uint8_t transmitMultipleEscapesBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xAA, 0xDC, 0x5C, 0xDC, 0x70, 0xDC, 0x71, 0xDC, 0x72, 0x0D, 0xDC, 0x73, 0xDC, 0x74,
                0xDC, 0x75, 0xDC, 0x76, 0xDC, 0x77, // many escapes
                0xFE, // End of message, last is String or Blob
                0xDC, 0x5C // Checksum
            };
            const size_t transmitMultipleEscapesByteCount = (sizeof(transmitMultipleEscapesBytes) /
                                                             sizeof(*transmitMultipleEscapesBytes));
            Blob multipleEscapesValue(actualData, actualDataCount);
            
            result = setValueAndCheck(*stuff, multipleEscapesValue, expectedMultipleEscapesBytes,
                                      expectedMultipleEscapesByteCount,
                                      transmitMultipleEscapesBytes,
                                      transmitMultipleEscapesByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertMultipleEscapesMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyArrayMessage(const char *launchPath,
                              const int  argc,
                              char       **argv) // empty array message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedEmptyArrayBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedEmptyArrayByteCount = (sizeof(expectedEmptyArrayBytes) /
                                                        sizeof(*expectedEmptyArrayBytes));
            static const uint8_t transmitEmptyArrayBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xFF, // End of message, last is Other
                0x59 // Checksum
            };
            const size_t transmitEmptyArrayByteCount = (sizeof(transmitEmptyArrayBytes) /
                                                        sizeof(*transmitEmptyArrayBytes));
            Array emptyArray;

            result = setValueAndCheck(*stuff, emptyArray, expectedEmptyArrayBytes,
                                      expectedEmptyArrayByteCount, transmitEmptyArrayBytes,
                                      transmitEmptyArrayByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertEmptyArrayMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyMapMessage(const char *launchPath,
                            const int  argc,
                            char       **argv) // empty map message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedEmptyMapBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedEmptyMapByteCount = (sizeof(expectedEmptyMapBytes) /
                                                      sizeof(*expectedEmptyMapBytes));
            static const uint8_t transmitEmptyMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xFF, // End of message, last is Other
                0x51 // Checksum
            };
            const size_t transmitEmptyMapByteCount = (sizeof(transmitEmptyMapBytes) /
                                                      sizeof(*transmitEmptyMapBytes));
            Map emptyMap;

            result = setValueAndCheck(*stuff, emptyMap, expectedEmptyMapBytes,
                                      expectedEmptyMapByteCount, transmitEmptyMapBytes,
                                      transmitEmptyMapByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertEmptyMapMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptySetMessage(const char *launchPath,
                            const int  argc,
                            char       **argv) // empty set message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedEmptySetBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedEmptySetByteCount = (sizeof(expectedEmptySetBytes) /
                                                      sizeof(*expectedEmptySetBytes));
            static const uint8_t transmitEmptySetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD8, // Start of empty Set
                0xE8, // End of empty Set
                0xFF, // End of message, last is Other
                0x49 // Checksum
            };
            const size_t transmitEmptySetByteCount = (sizeof(transmitEmptySetBytes) /
                                                      sizeof(*transmitEmptySetBytes));
            Set emptySet;

            result = setValueAndCheck(*stuff, emptySet, expectedEmptySetBytes,
                                      expectedEmptySetByteCount, transmitEmptySetBytes,
                                      transmitEmptySetByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertEmptySetMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneLogicalMessage(const char *launchPath,
                                   const int  argc,
                                   char       **argv) // array with one boolean message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneLogicalBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneLogicalByteCount = (sizeof(expectedArrayOneLogicalBytes) /
                                                             sizeof(*expectedArrayOneLogicalBytes));
            static const uint8_t transmitArrayOneLogicalBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xC0, // Logical false
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x87 // Checksum
            };
            const size_t transmitArrayOneLogicalByteCount = (sizeof(transmitArrayOneLogicalBytes) /
                                                             sizeof(*transmitArrayOneLogicalBytes));
            Array arrayOneLogical;

            arrayOneLogical.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayOneLogical, expectedArrayOneLogicalBytes,
                                      expectedArrayOneLogicalByteCount,
                                      transmitArrayOneLogicalBytes,
                                      transmitArrayOneLogicalByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneLogicalMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneIntegerMessage(const char *launchPath,
                                   const int  argc,
                                   char       **argv) // array with one integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneIntegerBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  0,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneIntegerByteCount = (sizeof(expectedArrayOneIntegerBytes) /
                                                             sizeof(*expectedArrayOneIntegerBytes));
            static const uint8_t transmitArrayOneIntegerBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0x00, // Integer zero
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x47 // Checksum
            };
            const size_t transmitArrayOneIntegerByteCount = (sizeof(transmitArrayOneIntegerBytes) /
                                                             sizeof(*transmitArrayOneIntegerBytes));
            Array arrayOneInteger;

            arrayOneInteger.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayOneInteger, expectedArrayOneIntegerBytes,
                                      expectedArrayOneIntegerByteCount,
                                      transmitArrayOneIntegerBytes,
                                      transmitArrayOneIntegerByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneDoubleMessage(const char *launchPath,
                                   const int  argc,
                                   char       **argv) // array with one double message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneDoubleBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - DataKindDoubleShortCountMinValue) &
                    DataKind::DoubleShortCountMask),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneDoubleByteCount = (sizeof(expectedArrayOneDoubleBytes) /
                                                            sizeof(*expectedArrayOneDoubleBytes));
            static const uint8_t transmitArrayOneDoubleBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Double zero
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x07 // Checksum
            };
            const size_t transmitArrayOneDoubleByteCount = (sizeof(transmitArrayOneDoubleBytes) /
                                                            sizeof(*transmitArrayOneDoubleBytes));
            Array arrayOneDouble;

            arrayOneDouble.addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayOneDouble, expectedArrayOneDoubleBytes,
                                      expectedArrayOneDoubleByteCount, transmitArrayOneDoubleBytes,
                                      transmitArrayOneDoubleByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneDoubleMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneStringMessage(const char *launchPath,
                                  const int  argc,
                                  char       **argv) // array with one string message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneStringBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneStringByteCount = (sizeof(expectedArrayOneStringBytes) /
                                                            sizeof(*expectedArrayOneStringBytes));
            static const uint8_t transmitArrayOneStringBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0x80, // Empty String
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xC7 // Checksum
            };
            const size_t transmitArrayOneStringByteCount = (sizeof(transmitArrayOneStringBytes) /
                                                            sizeof(*transmitArrayOneStringBytes));
            Array arrayOneString;

            arrayOneString.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayOneString, expectedArrayOneStringBytes,
                                      expectedArrayOneStringByteCount, transmitArrayOneStringBytes,
                                      transmitArrayOneStringByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 114 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneBlobMessage(const char *launchPath,
                                const int  argc,
                                char       **argv) // array with one blob message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneBlobBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneBlobByteCount = (sizeof(expectedArrayOneBlobBytes) /
                                                          sizeof(*expectedArrayOneBlobBytes));
            static const uint8_t transmitArrayOneBlobBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xA0, // Empty Blob
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xA7 // Checksum
            };
            const size_t transmitArrayOneBlobByteCount = (sizeof(transmitArrayOneBlobBytes) /
                                                          sizeof(*transmitArrayOneBlobBytes));
            Array arrayOneBlob;

            arrayOneBlob.addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayOneBlob, expectedArrayOneBlobBytes,
                                      expectedArrayOneBlobByteCount, transmitArrayOneBlobBytes,
                                      transmitArrayOneBlobByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneBlobMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 115 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneArrayMessage(const char *launchPath,
                                 const int  argc,
                                 char       **argv) // array with one array message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneArrayBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneArrayByteCount = (sizeof(expectedArrayOneArrayBytes) /
                                                           sizeof(*expectedArrayOneArrayBytes));
            static const uint8_t transmitArrayOneArrayBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x97 // Checksum
            };
            const size_t transmitArrayOneArrayByteCount = (sizeof(transmitArrayOneArrayBytes) /
                                                           sizeof(*transmitArrayOneArrayBytes));
            Array arrayOneArray;

            arrayOneArray.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneArray, expectedArrayOneArrayBytes,
                                      expectedArrayOneArrayByteCount, transmitArrayOneArrayBytes,
                                      transmitArrayOneArrayByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneArrayMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 116 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneMapMessage(const char *launchPath,
                               const int  argc,
                               char       **argv) // array with one map message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneMapBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneMapByteCount = (sizeof(expectedArrayOneMapBytes) /
                                                         sizeof(*expectedArrayOneMapBytes));
            static const uint8_t transmitArrayOneMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x8F // Checksum
            };
            const size_t transmitArrayOneMapByteCount = (sizeof(transmitArrayOneMapBytes) /
                                                         sizeof(*transmitArrayOneMapBytes));
            Array arrayOneMap;

            arrayOneMap.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneMap, expectedArrayOneMapBytes,
                                      expectedArrayOneMapByteCount, transmitArrayOneMapBytes,
                                      transmitArrayOneMapByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneMapMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 117 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneSetMessage(const char *launchPath,
                               const int  argc,
                               char       **argv) // array with one set message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneSetBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneSetByteCount = (sizeof(expectedArrayOneSetBytes) /
                                                         sizeof(*expectedArrayOneSetBytes));
            static const uint8_t transmitArrayOneSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xD8, // Start of empty Map
                0xE8, // End of empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x87 // Checksum
            };
            const size_t transmitArrayOneSetByteCount = (sizeof(transmitArrayOneSetBytes) /
                                                         sizeof(*transmitArrayOneSetBytes));
            Array arrayOneSet;

            arrayOneSet.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneSet, expectedArrayOneSetBytes,
                                      expectedArrayOneSetByteCount, transmitArrayOneSetBytes,
                                      transmitArrayOneSetByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneSetMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 130 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoLogicalsMessage(const char *launchPath,
                                    const int  argc,
                                    char       **argv) // array with two booleans message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoLogicalsBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoLogicalsByteCount =
                                                     (sizeof(expectedArrayTwoLogicalsBytes) /
                                                      sizeof(*expectedArrayTwoLogicalsBytes));
            static const uint8_t transmitArrayTwoLogicalsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xC0, 0xC0, // Two Logical falses
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xC6 // Checksum
            };
            const size_t transmitArrayTwoLogicalsByteCount =
                                                        (sizeof(transmitArrayTwoLogicalsBytes) /
                                                         sizeof(*transmitArrayTwoLogicalsBytes));
            Array arrayTwoLogicals;

            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayTwoLogicals, expectedArrayTwoLogicalsBytes,
                                      expectedArrayTwoLogicalsByteCount,
                                      transmitArrayTwoLogicalsBytes,
                                      transmitArrayTwoLogicalsByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoLogicalsMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 131 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoIntegersMessage(const char *launchPath,
                                    const int  argc,
                                    char       **argv) // array with two integers message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoIntegersBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  0,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  0,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoIntegersByteCount =
                                                        (sizeof(expectedArrayTwoIntegersBytes) /
                                                         sizeof(*expectedArrayTwoIntegersBytes));
            static const uint8_t transmitArrayTwoIntegersBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0x00, 0x00, // Two Integer zeroes
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x46 // Checksum
            };
            const size_t transmitArrayTwoIntegersByteCount =
                                                        (sizeof(transmitArrayTwoIntegersBytes) /
                                                         sizeof(*transmitArrayTwoIntegersBytes));
            Array arrayTwoIntegers;

            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayTwoIntegers, expectedArrayTwoIntegersBytes,
                                      expectedArrayTwoIntegersByteCount,
                                      transmitArrayTwoIntegersBytes,
                                      transmitArrayTwoIntegersByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoIntegersMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 132 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoDoublesMessage(const char *launchPath,
                                   const int  argc,
                                   char       **argv) // array with two doubles message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoDoublesBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((2 - DataKindDoubleShortCountMinValue) &
                    DataKind::DoubleShortCountMask),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoDoublesByteCount = (sizeof(expectedArrayTwoDoublesBytes) /
                                                             sizeof(*expectedArrayTwoDoublesBytes));
            static const uint8_t transmitArrayTwoDoublesBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Two Double zeroes
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x05 // Checksum
            };
            const size_t transmitArrayTwoDoublesByteCount =
                                                            (sizeof(transmitArrayTwoDoublesBytes) /
                                                             sizeof(*transmitArrayTwoDoublesBytes));
            Array arrayTwoDoubles;

            arrayTwoDoubles.addValue(std::make_shared<Double>());
            arrayTwoDoubles.addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayTwoDoubles, expectedArrayTwoDoublesBytes,
                                      expectedArrayTwoDoublesByteCount,
                                      transmitArrayTwoDoublesBytes,
                                      transmitArrayTwoDoublesByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoDoublesMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 133 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoStringsMessage(const char *launchPath,
                                   const int  argc,
                                   char       **argv) // array with two strings message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoStringsBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoStringsByteCount = (sizeof(expectedArrayTwoStringsBytes) /
                                                             sizeof(*expectedArrayTwoStringsBytes));
            static const uint8_t transmitArrayTwoStringsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0x80, 0x80, // Two empty Strings
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x46 // Checksum
            };
            const size_t transmitArrayTwoStringsByteCount = (sizeof(transmitArrayTwoStringsBytes) /
                                                             sizeof(*transmitArrayTwoStringsBytes));
            Array arrayTwoStrings;

            arrayTwoStrings.addValue(std::make_shared<String>());
            arrayTwoStrings.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayTwoStrings, expectedArrayTwoStringsBytes,
                                      expectedArrayTwoStringsByteCount,
                                      transmitArrayTwoStringsBytes,
                                      transmitArrayTwoStringsByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoStringsMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 134 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoBlobsMessage(const char *launchPath,
                                 const int  argc,
                                 char       **argv) // array with two blobs message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoBlobsBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoBlobsByteCount = (sizeof(expectedArrayTwoBlobsBytes) /
                                                           sizeof(*expectedArrayTwoBlobsBytes));
            static const uint8_t transmitArrayTwoBlobsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xA0, 0xA0, // Two empty Blobs
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x06 // Checksum
            };
            const size_t transmitArrayTwoBlobsByteCount = (sizeof(transmitArrayTwoBlobsBytes) /
                                                           sizeof(*transmitArrayTwoBlobsBytes));
            Array arrayTwoBlobs;

            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayTwoBlobs, expectedArrayTwoBlobsBytes,
                                      expectedArrayTwoBlobsByteCount, transmitArrayTwoBlobsBytes,
                                      transmitArrayTwoBlobsByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoBlobsMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 135 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoArraysMessage(const char *launchPath,
                                  const int  argc,
                                  char       **argv) // array with two arrays message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoArraysBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoArraysByteCount = (sizeof(expectedArrayTwoArraysBytes) /
                                                            sizeof(*expectedArrayTwoArraysBytes));
            static const uint8_t transmitArrayTwoArraysBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD0, // Start of first empty Array
                0xE0, // End of first empty Array
                0xD0, // Start of second empty Array
                0xE0, // End of second empty Array
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xE6 // Checksum
            };
            const size_t transmitArrayTwoArraysByteCount = (sizeof(transmitArrayTwoArraysBytes) /
                                                            sizeof(*transmitArrayTwoArraysBytes));
            Array arrayTwoArrays;

            arrayTwoArrays.addValue(std::make_shared<Array>());
            arrayTwoArrays.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayTwoArrays, expectedArrayTwoArraysBytes,
                                      expectedArrayTwoArraysByteCount, transmitArrayTwoArraysBytes,
                                      transmitArrayTwoArraysByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoArraysMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 136 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoMapsMessage(const char *launchPath,
                                const int  argc,
                                char       **argv) // array with two maps message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoMapsBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoMapsByteCount = (sizeof(expectedArrayTwoMapsBytes) /
                                                          sizeof(*expectedArrayTwoMapsBytes));
            static const uint8_t transmitArrayTwoMapsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD4, // Start of first empty Map
                0xE4, // End of first empty Map
                0xD4, // Start of first empty Map
                0xE4, // End of first empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xD6 // Checksum
            };
            const size_t transmitArrayTwoMapsByteCount = (sizeof(transmitArrayTwoMapsBytes) /
                                                          sizeof(*transmitArrayTwoMapsBytes));
            Array arrayTwoMaps;

            arrayTwoMaps.addValue(std::make_shared<Map>());
            arrayTwoMaps.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayTwoMaps, expectedArrayTwoMapsBytes,
                                      expectedArrayTwoMapsByteCount, transmitArrayTwoMapsBytes,
                                      transmitArrayTwoMapsByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoMapsMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 137 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoSetsMessage(const char *launchPath,
                                const int  argc,
                                char       **argv) // array with two sets message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayTwoSetsBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoSetsByteCount = (sizeof(expectedArrayTwoSetsBytes) /
                                                          sizeof(*expectedArrayTwoSetsBytes));
            static const uint8_t transmitArrayTwoSetsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD8, // Start of first empty Set
                0xE8, // End of first empty Set
                0xD8, // Start of first empty Set
                0xE8, // End of first empty Set
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xC6 // Checksum
            };
            const size_t transmitArrayTwoSetsByteCount = (sizeof(transmitArrayTwoSetsBytes) /
                                                          sizeof(*transmitArrayTwoSetsBytes));
            Array arrayTwoSets;

            arrayTwoSets.addValue(std::make_shared<Set>());
            arrayTwoSets.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayTwoSets, expectedArrayTwoSetsBytes,
                                      expectedArrayTwoSetsByteCount, transmitArrayTwoSetsBytes,
                                      transmitArrayTwoSetsByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayTwoSetsMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 138 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneArrayOneMapMessage(const char *launchPath,
                                       const int  argc,
                                       char       **argv) // array with array and map message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneArrayOneMapBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneArrayOneMapByteCount =
                                                    (sizeof(expectedArrayOneArrayOneMapBytes) /
                                                     sizeof(*expectedArrayOneArrayOneMapBytes));
            static const uint8_t transmitArrayOneArrayOneMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xDE // Checksum
            };
            const size_t transmitArrayOneArrayOneMapByteCount =
                                                        (sizeof(transmitArrayOneArrayOneMapBytes) /
                                                         sizeof(*transmitArrayOneArrayOneMapBytes));
            Array arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(std::make_shared<Array>());
            arrayOneArrayOneMap.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneArrayOneMap,
                                      expectedArrayOneArrayOneMapBytes,
                                      expectedArrayOneArrayOneMapByteCount,
                                      transmitArrayOneArrayOneMapBytes,
                                      transmitArrayOneArrayOneMapByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneArrayOneMapMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 139 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneMapOneSetMessage(const char *launchPath,
                                     const int  argc,
                                     char       **argv) // array with map and set message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneMapOneSetBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneMapOneSetByteCount =
                                                        (sizeof(expectedArrayOneMapOneSetBytes) /
                                                         sizeof(*expectedArrayOneMapOneSetBytes));
            static const uint8_t transmitArrayOneMapOneSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xD8, // Start of empty Set
                0xE8, // End of empty Set
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xCE // Checksum
            };
            const size_t transmitArrayOneMapOneSetByteCount =
                                                        (sizeof(transmitArrayOneMapOneSetBytes) /
                                                         sizeof(*transmitArrayOneMapOneSetBytes));
            Array arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(std::make_shared<Map>());
            arrayOneMapOneSet.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneMapOneSet, expectedArrayOneMapOneSetBytes,
                                      expectedArrayOneMapOneSetByteCount,
                                      transmitArrayOneMapOneSetBytes,
                                      transmitArrayOneMapOneSetByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneMapOneSetMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 140 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneSetOneArrayMessage(const char *launchPath,
                                       const int  argc,
                                       char       **argv) // array with set and array message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedArrayOneSetOneArrayBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneSetOneArrayByteCount =
                                                        (sizeof(expectedArrayOneSetOneArrayBytes) /
                                                         sizeof(*expectedArrayOneSetOneArrayBytes));
            static const uint8_t transmitArrayOneSetOneArrayBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD8, // Start of empty Set
                0xE8, // End of empty Set
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xD6 // Checksum
            };
            const size_t transmitArrayOneSetOneArrayByteCount =
                                                        (sizeof(transmitArrayOneSetOneArrayBytes) /
                                                         sizeof(*transmitArrayOneSetOneArrayBytes));
            Array arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(std::make_shared<Set>());
            arrayOneSetOneArray.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneSetOneArray,
                                      expectedArrayOneSetOneArrayBytes,
                                      expectedArrayOneSetOneArrayByteCount,
                                      transmitArrayOneSetOneArrayBytes,
                                      transmitArrayOneSetOneArrayByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayOneSetOneArrayMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 141 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithManyDoublesMessage(const char *launchPath,
                                        const int  argc,
                                        char       **argv) // array with many doubles message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            const size_t          numValues = 43;
            static const DataKind expectedArrayManyDoublesBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((1 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(static_cast<int>(numValues) +
                                      DataKindIntegerShortValueMinValue - 1),
                // Double
                DataKind::Double | DataKind::DoubleLongCount |
                  ((1 - 1) & DataKind::DoubleLongCountMask),
                static_cast<DataKind>(numValues),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 0
                static_cast<DataKind>(0x3F), static_cast<DataKind>(0xF0),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 1
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 2
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x08),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 3
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x10),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 4
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x14),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 5
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x18),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 6
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x1C),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 7
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x20),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 8
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x22),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 9
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x24),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 10
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x26),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 11
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x28),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 12
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x2A),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 13
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x2C),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 14
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x2E),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 15
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x30),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 16
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x31),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 17
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x32),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 18
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x33),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 19
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x34),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 20
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x35),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 21
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x36),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 22
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x37),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 23
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x38),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 24
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x39),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 25
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x3A),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 26
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x3B),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 27
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x3C),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 28
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x3D),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 29
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x3E),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 30
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x3F),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 31
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x40),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 32
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x40),
                static_cast<DataKind>(0x80), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 33
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x41),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 34
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x41),
                static_cast<DataKind>(0x80), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 35
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x42),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 36
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x42),
                static_cast<DataKind>(0x80), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 37
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x43),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 38
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x43),
                static_cast<DataKind>(0x80), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 39
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x44),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 40
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x44),
                static_cast<DataKind>(0x80), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 41
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x45),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 42
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayManyDoublesByteCount =
                                                        (sizeof(expectedArrayManyDoublesBytes) /
                                                         sizeof(*expectedArrayManyDoublesBytes));
            static const uint8_t transmitArrayManyDoublesBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x20, 0x1A, // Start of non-empty Array, 42 elements
                0x60, 0x2B, // Count of doubles that follow
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0
                0x3F, 0xDC, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 1 [note the escape]
                0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 2
                0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 3
                0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 4
                0x40, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 5
                0x40, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 6
                0x40, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 7
                0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 8
                0x40, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 9
                0x40, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 10
                0x40, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 11
                0x40, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 12
                0x40, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 13
                0x40, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 14
                0x40, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 15
                0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 16
                0x40, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 17
                0x40, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 18
                0x40, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 19
                0x40, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 20
                0x40, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 21
                0x40, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 22
                0x40, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 23
                0x40, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 24
                0x40, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 25
                0x40, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 26
                0x40, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 27
                0x40, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 28
                0x40, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 29
                0x40, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 30
                0x40, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 31
                0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 32
                0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 33
                0x40, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
                0x40, 0x41, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
                0x40, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
                0x40, 0x42, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
                0x40, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
                0x40, 0x43, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 39
                0x40, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 40
                0x40, 0x44, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, // 41
                0x40, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xBA // Checksum
            };
            const size_t transmitArrayManyDoublesByteCount =
                                                        (sizeof(transmitArrayManyDoublesBytes) /
                                                         sizeof(*transmitArrayManyDoublesBytes));
            Array arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(std::make_shared<Double>(static_cast<double>(ii)));
            }
            result = setValueAndCheck(*stuff, arrayManyDoubles, expectedArrayManyDoublesBytes,
                                      expectedArrayManyDoublesByteCount,
                                      transmitArrayManyDoublesBytes,
                                      transmitArrayManyDoublesByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertArrayWithManyDoublesMessage

#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_


#if defined(__APPLE__)
# pragma mark *** Test Case 160 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertLogicalMapMessage(const char *launchPath,
                              const int  argc,
                              char       **argv) // boolean map message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedLogicalMapBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  (13 & DataKind::IntegerShortValueValueMask),
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedLogicalMapByteCount = (sizeof(expectedLogicalMapBytes) /
                                                        sizeof(*expectedLogicalMapBytes));
            static const uint8_t transmitLogicalMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD5, 0x10, // Start of non-empty Map, one element
                0xC0, // Logical key = false
                0x0D, // Integer value = 13
                0xE5, // End of non-empty Map
                0xFF, // End of message, last is Other
                0x72 // Checksum
            };
            const size_t transmitLogicalMapByteCount = (sizeof(transmitLogicalMapBytes) /
                                                        sizeof(*transmitLogicalMapBytes));
            Map logicalMap;

            logicalMap.addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, logicalMap, expectedLogicalMapBytes,
                                      expectedLogicalMapByteCount, transmitLogicalMapBytes,
                                      transmitLogicalMapByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertLogicalMapMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 161 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertIntegerMapMessage(const char *launchPath,
                              const int  argc,
                              char       **argv) // integer map message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedIntegerMapBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  0,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  (13 & DataKind::IntegerShortValueValueMask),
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedIntegerMapByteCount = (sizeof(expectedIntegerMapBytes) /
                                                        sizeof(*expectedIntegerMapBytes));
            static const uint8_t transmitIntegerMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD5, 0x10, // Start of non-empty Map, one element
                0x00, // Integer key = 0
                0x0D, // Integer value = 13
                0xE5, // End of non-empty Map
                0xFF, // End of message, last is Other
                0x32 // Checksum
            };
            const size_t transmitIntegerMapByteCount = (sizeof(transmitIntegerMapBytes) /
                                                        sizeof(*transmitIntegerMapBytes));
            Map integerMap;

            integerMap.addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, integerMap, expectedIntegerMapBytes,
                                      expectedIntegerMapByteCount, transmitIntegerMapBytes,
                                      transmitIntegerMapByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertIntegerMapMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 162 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertStringMapMessage(const char *launchPath,
                             const int  argc,
                             char       **argv) // integer map message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedStringMapBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  (13 & DataKind::IntegerShortValueValueMask),
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedStringMapByteCount = (sizeof(expectedStringMapBytes) /
                                                       sizeof(*expectedStringMapBytes));
            static const uint8_t transmitStringMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD5, 0x10, // Start of non-empty Map, one element
                0x80, // String key = empty
                0x0D, // Integer value = 13
                0xE5, // End of non-empty Map
                0xFF, // End of message, last is Other
                0xB2 // Checksum
            };
            const size_t transmitStringMapByteCount = (sizeof(transmitStringMapBytes) /
                                                       sizeof(*transmitStringMapBytes));
            Map stringMap;

            stringMap.addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, stringMap, expectedStringMapBytes,
                                      expectedStringMapByteCount, transmitStringMapBytes,
                                      transmitStringMapByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertStringMapMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 163 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertLogicalSetMessage(const char *launchPath,
                              const int  argc,
                              char       **argv) // boolean set message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedLogicalSetBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedLogicalSetByteCount = (sizeof(expectedLogicalSetBytes) /
                                                        sizeof(*expectedLogicalSetBytes));
            static const uint8_t transmitLogicalSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD9, 0x10, // Start of non-empty Set, one element
                0xC0, // Logical key = false
                0xE9, // End of non-empty Set
                0xFF, // End of message, last is Other
                0x77 // Checksum
            };
            const size_t transmitLogicalSetByteCount = (sizeof(transmitLogicalSetBytes) /
                                                        sizeof(*transmitLogicalSetBytes));
            Set logicalSet;

            logicalSet.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, logicalSet, expectedLogicalSetBytes,
                                      expectedLogicalSetByteCount, transmitLogicalSetBytes,
                                      transmitLogicalSetByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertLogicalSetMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 164 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertIntegerSetMessage(const char *launchPath,
                              const int  argc,
                              char       **argv) // integer set message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedIntegerSetBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  0,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedIntegerSetByteCount = (sizeof(expectedIntegerSetBytes) /
                                                        sizeof(*expectedIntegerSetBytes));
            static const uint8_t transmitIntegerSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD9, 0x10, // Start of non-empty Set, one element
                0x00, // Integer key = 0
                0xE9, // End of non-empty Set
                0xFF, // End of message, last is Other
                0x37 // Checksum
            };
            const size_t transmitIntegerSetByteCount = (sizeof(transmitIntegerSetBytes) /
                                                        sizeof(*transmitIntegerSetBytes));
            Set integerSet;

            integerSet.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, integerSet, expectedIntegerSetBytes,
                                      expectedIntegerSetByteCount, transmitIntegerSetBytes,
                                      transmitIntegerSetByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertIntegerSetMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 165 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInsertStringSetMessage(const char *launchPath,
                             const int  argc,
                             char       **argv) // integer set message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind expectedStringSetBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedStringSetByteCount = (sizeof(expectedStringSetBytes) /
                                                       sizeof(*expectedStringSetBytes));
            static const uint8_t transmitStringSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD9, 0x10, // Start of non-empty Set, one element
                0x80, // String key = empty
                0xE9, // End of non-empty Set
                0xFF, // End of message, last is Other
                0xB7 // Checksum
            };
            const size_t transmitStringSetByteCount = (sizeof(transmitStringSetBytes) /
                                                       sizeof(*transmitStringSetBytes));
            Set stringSet;

            stringSet.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, stringSet, expectedStringSetBytes,
                                      expectedStringSetByteCount, transmitStringSetBytes,
                                      transmitStringSetByteCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestInsertStringSetMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for unit tests of the %nImO common classes.

 The first argument is the test number, the second argument is the name of the channel to be used
 with the test, the optional third argument is the machine to connect to and the optional fourth
 argument is the port number to be used. Output depends on the test being run.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the unit tests.
 @returns @c 0 on a successful test and @c 1 on failure. */
int
main(int  argc,
     char **argv)
{
    std::string progName(*argv);

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
#if 0
#if MAC_OR_LINUX_
    SetUpLogger(progName);
#endif // MAC_OR_LINUX_
#endif//0
    int result = 1;

    try
    {
        Initialize(progName);
        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToLong(argv[1], selector) && (0 < selector))
            {
                SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestInsertEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestInsertLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestInsertTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestInsertShortIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestInsertMediumIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 6 :
                        result = doTestInsertBigIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 7 :
                        result = doTestInsertEmptyStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 8 :
                        result = doTestInsertShortStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 9 :
                        result = doTestInsertMediumStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestInsertEmptyBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 11 :
                        result = doTestInsertShortBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestInsertMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestInsertSingleFloatMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 14 :
                        result = doTestInsertMultipleEscapesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 100 :
                        result = doTestInsertEmptyArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestInsertEmptyMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestInsertEmptySetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 110 :
                        result = doTestInsertArrayOneLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 111 :
                        result = doTestInsertArrayOneIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 112 :
                        result = doTestInsertArrayOneDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 113 :
                        result = doTestInsertArrayOneStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 114 :
                        result = doTestInsertArrayOneBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 115 :
                        result = doTestInsertArrayOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 116 :
                        result = doTestInsertArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 117 :
                        result = doTestInsertArrayOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 130 :
                        result = doTestInsertArrayTwoLogicalsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 131 :
                        result = doTestInsertArrayTwoIntegersMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 132 :
                        result = doTestInsertArrayTwoDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 133 :
                        result = doTestInsertArrayTwoStringsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 134 :
                        result = doTestInsertArrayTwoBlobsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 135 :
                        result = doTestInsertArrayTwoArraysMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 136 :
                        result = doTestInsertArrayTwoMapsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 137 :
                        result = doTestInsertArrayTwoSetsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 138 :
                        result = doTestInsertArrayOneArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 139 :
                        result = doTestInsertArrayOneMapOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 140 :
                        result = doTestInsertArrayOneSetOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 141 :
                        result = doTestInsertArrayWithManyDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 160 :
                        result = doTestInsertLogicalMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 161 :
                        result = doTestInsertIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 162 :
                        result = doTestInsertStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 163 :
                        result = doTestInsertLogicalSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 164 :
                        result = doTestInsertIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 165 :
                        result = doTestInsertStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    default :
                        break;

                }
                if (result)
                {
                    ODL_LL1("%%%%%%% unit test failure = ", result); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (0 < --argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // main

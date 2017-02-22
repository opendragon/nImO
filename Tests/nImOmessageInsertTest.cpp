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

#include <nImO/nImOarray.hpp>
#include <nImO/nImOblob.hpp>
#include <nImO/nImObufferChunk.hpp>
#include <nImO/nImOdouble.hpp>
#include <nImO/nImOinteger.hpp>
#include <nImO/nImOlogical.hpp>
#include <nImO/nImOmap.hpp>
#include <nImO/nImOmessage.hpp>
#include <nImO/nImOset.hpp>
#include <nImO/nImOstring.hpp>
#include <nImO/nImOstringBuffer.hpp>

#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

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
    std::stringstream buff;
    std::string       message("Exiting due to signal ");

    buff << signal;
    message += buff.str();
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
 @param[in] expectedContents The expected contents of the Message.
 @param[in] expectedSize The expected size of the Message.
 @returns Zero on success and non-zero on failure. */
static int
setValueAndCheck(Message        &stuff,
                 const Value    &aValue,
                 const DataKind *expectedContents,
                 const size_t   expectedSize)
{
    ODL_ENTER(); //####
    ODL_P3("stuff = ", &stuff, "aValue = ", &aValue, "expectedContents = ", //####
           expectedContents); //####
    ODL_LL1("expectedSize = ", expectedSize); //####
    stuff.open(true);
    stuff.setValue(aValue);
    stuff.close();
    size_t        length = 0;
    const uint8_t *contents = stuff.getBytes(length);
    int           result;

    ODL_PACKET("expectedContents", expectedContents, expectedSize); //####
    ODL_PACKET("contents", contents, length); //####
    if ((nullptr != contents) && (expectedSize == length))
    {
        result = CompareBytes(expectedContents, contents, expectedSize);
    }
    else
    {
        ODL_LOG("! ((nullptr != contents) && (expectedSize == length))"); //####
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
            static const DataKind expectedBytes[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageEmptyValue
            };
            const size_t  expectedCount = (sizeof(expectedBytes) / sizeof(*expectedBytes));
            ODL_PACKET("expectedBytes", expectedBytes, expectedCount); //####
            size_t        length = 0;
            const uint8_t *contents = stuff->getBytes(length);

            stuff->open(true);
            if ((nullptr != contents) || (0 != length))
            {
                ODL_LOG("((nullptr != contents) || (0 != length))"); //####
            }
            else
            {
                stuff->close();
                contents = stuff->getBytes(length);
                ODL_PACKET("contents", contents, length); //####
                if ((nullptr != contents) && (expectedCount == length))
                {
                    result = CompareBytes(expectedBytes, contents, expectedCount);
                }
                else
                {
                    ODL_LOG("! ((nullptr != contents) && (expectedCount == length))"); //####
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
            static const DataKind expectedBytesForTrue[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalTrueValue,
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedTrueCount = (sizeof(expectedBytesForTrue) /
                                              sizeof(*expectedBytesForTrue));
            static const DataKind expectedBytesForFalse[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedFalseCount = (sizeof(expectedBytesForFalse) /
                                               sizeof(*expectedBytesForFalse));
            Logical falseValue(false);
            Logical trueValue(true);

            result = setValueAndCheck(*stuff, trueValue, expectedBytesForTrue, expectedTrueCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, falseValue, expectedBytesForFalse,
                                          expectedFalseCount);
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
            static const DataKind expectedBytesForMinus12[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  (-12 & DataKind::IntegerShortValueValueMask),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus12Count = (sizeof(expectedBytesForMinus12) /
                                                 sizeof(*expectedBytesForMinus12));
            static const DataKind expectedBytesForZero[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  0,
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedZeroCount = (sizeof(expectedBytesForZero) /
                                              sizeof(*expectedBytesForZero));
            static const DataKind expectedBytesForPlus12[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerShortValue |
                  (12 & DataKind::IntegerShortValueValueMask),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus12Count = (sizeof(expectedBytesForPlus12) /
                                                sizeof(*expectedBytesForPlus12));
            Integer minus12Value(-12);
            Integer zeroValue(0);
            Integer plus12Value(12);

            result = setValueAndCheck(*stuff, minus12Value, expectedBytesForMinus12,
                                      expectedMinus12Count);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, zeroValue, expectedBytesForZero,
                                          expectedZeroCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus12Value, expectedBytesForPlus12,
                                          expectedPlus12Count);
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
            static const DataKind expectedBytesForMinus144[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((2 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0xFF), static_cast<DataKind>(0x70),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus144Count = (sizeof(expectedBytesForMinus144) /
                                                  sizeof(*expectedBytesForMinus144));
            static const DataKind expectedBytesForPlus144[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((2 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x90),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus144Count = (sizeof(expectedBytesForPlus144) /
                                                 sizeof(*expectedBytesForPlus144));
            Integer minus144Value(-144);
            Integer plus144Value(144);

            result = setValueAndCheck(*stuff, minus144Value, expectedBytesForMinus144,
                                      expectedMinus144Count);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus144Value, expectedBytesForPlus144,
                                          expectedPlus144Count);
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
            static const DataKind expectedBytesForMinus1234567[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((3 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0xED), static_cast<DataKind>(0x29),
                static_cast<DataKind>(0x79),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus1234567Count = (sizeof(expectedBytesForMinus1234567) /
                                                      sizeof(*expectedBytesForMinus1234567));
            static const DataKind expectedBytesForPlus1234567[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((3 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0xD6),
                static_cast<DataKind>(0x87),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus1234567Count = (sizeof(expectedBytesForPlus1234567) /
                                                     sizeof(*expectedBytesForPlus1234567));
            Integer minus1234567Value(-1234567);
            Integer plus1234567Value(1234567);

            result = setValueAndCheck(*stuff, minus1234567Value, expectedBytesForMinus1234567,
                                      expectedMinus1234567Count);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus1234567Value, expectedBytesForPlus1234567,
                                          expectedPlus1234567Count);
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
            static const DataKind expectedBytesForMinusBigNumber[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((6 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0xED), static_cast<DataKind>(0xCB),
                static_cast<DataKind>(0xA9), static_cast<DataKind>(0x87),
                static_cast<DataKind>(0x65), static_cast<DataKind>(0x44),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedMinusBigNumberCount = (sizeof(expectedBytesForMinusBigNumber) /
                                                        sizeof(*expectedBytesForMinusBigNumber));
            static const DataKind expectedBytesForPlusBigNumber[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((6 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0x12), static_cast<DataKind>(0x34),
                static_cast<DataKind>(0x56), static_cast<DataKind>(0x78),
                static_cast<DataKind>(0x9A), static_cast<DataKind>(0xBC),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t expectedPlusBigNumberCount = (sizeof(expectedBytesForPlusBigNumber) /
                                                       sizeof(*expectedBytesForPlusBigNumber));
            Integer minusBigNumberValue(-20015998343868);
            Integer plusBigNumberValue(20015998343868);

            result = setValueAndCheck(*stuff, minusBigNumberValue, expectedBytesForMinusBigNumber,
                                      expectedMinusBigNumberCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plusBigNumberValue,
                                          expectedBytesForPlusBigNumber,
                                          expectedPlusBigNumberCount);
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
            static const DataKind expectedBytesForEmptyString[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyStringCount = (sizeof(expectedBytesForEmptyString) /
                                                     sizeof(*expectedBytesForEmptyString));
            String emptyStringValue("");

            result = setValueAndCheck(*stuff, emptyStringValue, expectedBytesForEmptyString,
                                      expectedEmptyStringCount);
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
            static const DataKind expectedBytesForShortString[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortStringCount = (sizeof(expectedBytesForShortString) /
                                                     sizeof(*expectedBytesForShortString));
            String shortStringValue("abcdef");

            result = setValueAndCheck(*stuff, shortStringValue, expectedBytesForShortString,
                                      expectedShortStringCount);
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
            static const DataKind expectedBytesForMediumString[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedMediumStringCount = (sizeof(expectedBytesForMediumString) /
                                                     sizeof(*expectedBytesForMediumString));
            String mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

            result = setValueAndCheck(*stuff, mediumStringValue, expectedBytesForMediumString,
                                      expectedMediumStringCount);
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
            static const DataKind expectedBytesForEmptyBlob[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (0 & DataKind::StringOrBlobShortLengthMask),
                // End of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyBlobCount = (sizeof(expectedBytesForEmptyBlob) /
                                                   sizeof(*expectedBytesForEmptyBlob));
            Blob   emptyBlobValue;

            result = setValueAndCheck(*stuff, emptyBlobValue, expectedBytesForEmptyBlob,
                                      expectedEmptyBlobCount);
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
            static const DataKind expectedBytesForShortBlob[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortBlobCount = (sizeof(expectedBytesForShortBlob) /
                                                   sizeof(*expectedBytesForShortBlob));
            static const uint8_t actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t actualDataCount = (sizeof(actualData) / sizeof(*actualData));
            Blob   shortBlobValue(actualData, actualDataCount);

            result = setValueAndCheck(*stuff, shortBlobValue, expectedBytesForShortBlob,
                                      expectedShortBlobCount);
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
            static const DataKind expectedBytesForMediumBlob[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedMediumBlobCount = (sizeof(expectedBytesForMediumBlob) /
                                                    sizeof(*expectedBytesForMediumBlob));
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
            Blob   mediumBlobValue(actualData, actualDataCount);

            result = setValueAndCheck(*stuff, mediumBlobValue, expectedBytesForMediumBlob,
                                      expectedMediumBlobCount);
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
            static const DataKind expectedBytesForPlus42Point5[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            const size_t expectedPlus42Point5Count = (sizeof(expectedBytesForPlus42Point5) /
                                                      sizeof(*expectedBytesForPlus42Point5));
            static const DataKind expectedBytesForMinus42Point5[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            const size_t expectedMinus42Point5Count = (sizeof(expectedBytesForMinus42Point5) /
                                                      sizeof(*expectedBytesForMinus42Point5));
            Double plus42Point5(42.5);
            Double minus42Point5(-42.5);

            result = setValueAndCheck(*stuff, plus42Point5, expectedBytesForPlus42Point5,
                                      expectedPlus42Point5Count);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, minus42Point5, expectedBytesForMinus42Point5,
                                          expectedMinus42Point5Count);
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
            static const DataKind expectedBytesForEmptyArray[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedEmptyArrayCount = (sizeof(expectedBytesForEmptyArray) /
                                                    sizeof(*expectedBytesForEmptyArray));
            Array  emptyArray;

            result = setValueAndCheck(*stuff, emptyArray, expectedBytesForEmptyArray,
                                      expectedEmptyArrayCount);
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
            static const DataKind expectedBytesForEmptyMap[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedEmptyMapCount = (sizeof(expectedBytesForEmptyMap) /
                                                  sizeof(*expectedBytesForEmptyMap));
            Map    emptyMap;

            result = setValueAndCheck(*stuff, emptyMap, expectedBytesForEmptyMap,
                                      expectedEmptyMapCount);
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
            static const DataKind expectedBytesForEmptySet[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedEmptySetCount = (sizeof(expectedBytesForEmptySet) /
                                                  sizeof(*expectedBytesForEmptySet));
            Set    emptySet;

            result = setValueAndCheck(*stuff, emptySet, expectedBytesForEmptySet,
                                      expectedEmptySetCount);
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
            static const DataKind expectedBytesForArrayOneLogical[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneLogicalCount = (sizeof(expectedBytesForArrayOneLogical) /
                                                         sizeof(*expectedBytesForArrayOneLogical));
            Array  arrayOneLogical;

            arrayOneLogical.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayOneLogical, expectedBytesForArrayOneLogical,
                                      expectedArrayOneLogicalCount);
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
            static const DataKind expectedBytesForArrayOneInteger[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneIntegerCount = (sizeof(expectedBytesForArrayOneInteger) /
                                                         sizeof(*expectedBytesForArrayOneInteger));
            Array  arrayOneInteger;

            arrayOneInteger.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayOneInteger, expectedBytesForArrayOneInteger,
                                      expectedArrayOneIntegerCount);
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
            static const DataKind expectedBytesForArrayOneDouble[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneDoubleCount = (sizeof(expectedBytesForArrayOneDouble) /
                                                        sizeof(*expectedBytesForArrayOneDouble));
            Array arrayOneDouble;

            arrayOneDouble.addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayOneDouble, expectedBytesForArrayOneDouble,
                                      expectedArrayOneDoubleCount);
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
            static const DataKind expectedBytesForArrayOneString[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneStringCount = (sizeof(expectedBytesForArrayOneString) /
                                                        sizeof(*expectedBytesForArrayOneString));
            Array  arrayOneString;

            arrayOneString.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayOneString, expectedBytesForArrayOneString,
                                      expectedArrayOneStringCount);
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
            static const DataKind expectedBytesForArrayOneBlob[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneBlobCount = (sizeof(expectedBytesForArrayOneBlob) /
                                                      sizeof(*expectedBytesForArrayOneBlob));
            Array  arrayOneBlob;

            arrayOneBlob.addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayOneBlob, expectedBytesForArrayOneBlob,
                                      expectedArrayOneBlobCount);
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
            static const DataKind expectedBytesForArrayOneArray[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneArrayCount = (sizeof(expectedBytesForArrayOneArray) /
                                                       sizeof(*expectedBytesForArrayOneArray));
            Array  arrayOneArray;

            arrayOneArray.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneArray, expectedBytesForArrayOneArray,
                                      expectedArrayOneArrayCount);
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
            static const DataKind expectedBytesForArrayOneMap[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneMapCount = (sizeof(expectedBytesForArrayOneMap) /
                                                     sizeof(*expectedBytesForArrayOneMap));
            Array  arrayOneMap;

            arrayOneMap.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneMap, expectedBytesForArrayOneMap,
                                      expectedArrayOneMapCount);
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
            static const DataKind expectedBytesForArrayOneSet[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneSetCount = (sizeof(expectedBytesForArrayOneSet) /
                                                     sizeof(*expectedBytesForArrayOneSet));
            Array  arrayOneSet;

            arrayOneSet.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneSet, expectedBytesForArrayOneSet,
                                      expectedArrayOneSetCount);
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
            static const DataKind expectedBytesForArrayTwoLogicals[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoLogicalsCount =
                                                     (sizeof(expectedBytesForArrayTwoLogicals) /
                                                      sizeof(*expectedBytesForArrayTwoLogicals));
            Array  arrayTwoLogicals;

            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayTwoLogicals, expectedBytesForArrayTwoLogicals,
                                      expectedArrayTwoLogicalsCount);
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
            static const DataKind expectedBytesForArrayTwoIntegers[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoIntegersCount =
                                                     (sizeof(expectedBytesForArrayTwoIntegers) /
                                                      sizeof(*expectedBytesForArrayTwoIntegers));
            Array  arrayTwoIntegers;

            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayTwoIntegers, expectedBytesForArrayTwoIntegers,
                                      expectedArrayTwoIntegersCount);
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
            static const DataKind expectedBytesForArrayTwoDoubles[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoDoublesCount = (sizeof(expectedBytesForArrayTwoDoubles) /
                                                         sizeof(*expectedBytesForArrayTwoDoubles));
            Array  arrayTwoDoubles;

            arrayTwoDoubles.addValue(std::make_shared<Double>());
            arrayTwoDoubles.addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayTwoDoubles, expectedBytesForArrayTwoDoubles,
                                      expectedArrayTwoDoublesCount);
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
            static const DataKind expectedBytesForArrayTwoStrings[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoStringsCount = (sizeof(expectedBytesForArrayTwoStrings) /
                                                         sizeof(*expectedBytesForArrayTwoStrings));
            Array  arrayTwoStrings;

            arrayTwoStrings.addValue(std::make_shared<String>());
            arrayTwoStrings.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayTwoStrings, expectedBytesForArrayTwoStrings,
                                      expectedArrayTwoStringsCount);
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
            static const DataKind expectedBytesForArrayTwoBlobs[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoBlobsCount = (sizeof(expectedBytesForArrayTwoBlobs) /
                                                       sizeof(*expectedBytesForArrayTwoBlobs));
            Array  arrayTwoBlobs;

            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayTwoBlobs, expectedBytesForArrayTwoBlobs,
                                      expectedArrayTwoBlobsCount);
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
            static const DataKind expectedBytesForArrayTwoArrays[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoArraysCount = (sizeof(expectedBytesForArrayTwoArrays) /
                                                        sizeof(*expectedBytesForArrayTwoArrays));
            Array  arrayTwoArrays;

            arrayTwoArrays.addValue(std::make_shared<Array>());
            arrayTwoArrays.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayTwoArrays, expectedBytesForArrayTwoArrays,
                                      expectedArrayTwoArraysCount);
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
            static const DataKind expectedBytesForArrayTwoMaps[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoMapsCount = (sizeof(expectedBytesForArrayTwoMaps) /
                                                      sizeof(*expectedBytesForArrayTwoMaps));
            Array  arrayTwoMaps;

            arrayTwoMaps.addValue(std::make_shared<Map>());
            arrayTwoMaps.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayTwoMaps, expectedBytesForArrayTwoMaps,
                                      expectedArrayTwoMapsCount);
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
            static const DataKind expectedBytesForArrayTwoSets[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoSetsCount = (sizeof(expectedBytesForArrayTwoSets) /
                                                      sizeof(*expectedBytesForArrayTwoSets));
            Array  arrayTwoSets;

            arrayTwoSets.addValue(std::make_shared<Set>());
            arrayTwoSets.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayTwoSets, expectedBytesForArrayTwoSets,
                                      expectedArrayTwoSetsCount);
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
            static const DataKind expectedBytesForArrayOneArrayOneMap[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneArrayOneMapCount =
                                                    (sizeof(expectedBytesForArrayOneArrayOneMap) /
                                                     sizeof(*expectedBytesForArrayOneArrayOneMap));
            Array  arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(std::make_shared<Array>());
            arrayOneArrayOneMap.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneArrayOneMap,
                                      expectedBytesForArrayOneArrayOneMap,
                                      expectedArrayOneArrayOneMapCount);
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
            static const DataKind expectedBytesForArrayOneMapOneSet[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneMapOneSetCount =
                                                        (sizeof(expectedBytesForArrayOneMapOneSet) /
                                                        sizeof(*expectedBytesForArrayOneMapOneSet));
            Array  arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(std::make_shared<Map>());
            arrayOneMapOneSet.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneMapOneSet, expectedBytesForArrayOneMapOneSet,
                                      expectedArrayOneMapOneSetCount);
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
            static const DataKind expectedBytesForArrayOneSetOneArray[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneSetOneArrayCount =
                                                    (sizeof(expectedBytesForArrayOneSetOneArray) /
                                                     sizeof(*expectedBytesForArrayOneSetOneArray));
            Array  arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(std::make_shared<Set>());
            arrayOneSetOneArray.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneSetOneArray,
                                      expectedBytesForArrayOneSetOneArray,
                                      expectedArrayOneSetOneArrayCount);
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
            const size_t         numValues = 43;
            static const DataKind expectedBytesForArrayManyDoubles[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((1 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(numValues + DataKindIntegerShortValueMinValue - 1),
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedArrayManyDoublesCount = (sizeof(expectedBytesForArrayManyDoubles) /
                                                        sizeof(*expectedBytesForArrayManyDoubles));
            Array  arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(std::make_shared<Double>(ii));
            }
            result = setValueAndCheck(*stuff, arrayManyDoubles, expectedBytesForArrayManyDoubles,
                                      expectedArrayManyDoublesCount);
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
            static const DataKind expectedBytesForLogicalMap[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedLogicalMapCount = (sizeof(expectedBytesForLogicalMap) /
                                                    sizeof(*expectedBytesForLogicalMap));
            Map    booleanMap;

            booleanMap.addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, booleanMap, expectedBytesForLogicalMap,
                                      expectedLogicalMapCount);
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
            static const DataKind expectedBytesForIntegerMap[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedIntegerMapCount = (sizeof(expectedBytesForIntegerMap) /
                                                    sizeof(*expectedBytesForIntegerMap));
            Map    integerMap;

            integerMap.addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, integerMap, expectedBytesForIntegerMap,
                                      expectedIntegerMapCount);
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
            static const DataKind expectedBytesForStringMap[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedStringMapCount = (sizeof(expectedBytesForStringMap) /
                                                   sizeof(*expectedBytesForStringMap));
            Map    stringMap;

            stringMap.addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, stringMap, expectedBytesForStringMap,
                                      expectedStringMapCount);
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
            static const DataKind expectedBytesForLogicalSet[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedLogicalSetCount = (sizeof(expectedBytesForLogicalSet) /
                                                    sizeof(*expectedBytesForLogicalSet));
            Set    booleanSet;

            booleanSet.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, booleanSet, expectedBytesForLogicalSet,
                                      expectedLogicalSetCount);
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
            static const DataKind expectedBytesForIntegerSet[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedIntegerSetCount = (sizeof(expectedBytesForIntegerSet) /
                                                     sizeof(*expectedBytesForIntegerSet));
            Set    integerSet;

            integerSet.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, integerSet, expectedBytesForIntegerSet,
                                      expectedIntegerSetCount);
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
            static const DataKind expectedBytesForStringSet[] =
            {
                // Start of Message
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageStartValue |
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
                DataKind::Other | DataKind::OtherMessage |
                  DataKind::OtherMessageEndValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t expectedStringSetCount = (sizeof(expectedBytesForStringSet) /
                                                   sizeof(*expectedBytesForStringSet));
            Set    stringSet;

            stringSet.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, stringSet, expectedBytesForStringSet,
                                      expectedStringSetCount);
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

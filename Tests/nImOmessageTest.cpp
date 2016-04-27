//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOmessageTest.cpp
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

#include <nImO/nImOblob.hpp>
#include <nImO/nImOboolean.hpp>
#include <nImO/nImObufferChunk.hpp>
#include <nImO/nImOdouble.hpp>
#include <nImO/nImOinteger.hpp>
#include <nImO/nImOmessage.hpp>
#include <nImO/nImOstring.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The test driver for the unit tests of the %nImO common library. */

/*! @namespace nImO::Test
 @brief The classes used for unit testing of the %nImO classes. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using std::cerr;
using std::cout;
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

/*! @brief The number of elements in a small test. */
static const size_t kSmallTestSize = 100;

/*! @brief The number of elements in a big test. */
static const size_t kBigTestSize = 100000;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief The signal handler to catch requests to stop the service.
 @param signal The signal being handled. */
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
    message += nImO::NameOfSignal(signal);
#if 0
    nImO_ERROR_(message.c_str());
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

#if 0
/*! @brief Compare a Value object with a string.
 @param aValue The object to be compared.
 @param aString The string to be compared to.
 @returns @c -1, @c 0 or @c 1 depending on where the string is greater than, equal to or less than
 the object representation as a string. */
static int
compareValueWithString(const nImO::Value & aValue,
                       const char *        aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    nImO::StringBuffer buff;
    int                result;
    size_t             length;
    
    aValue.printToStringBuffer(buff);
    result = strcmp(buff.getString(length), aString);
    ODL_S2("got: ", buff.getString(length), "expected: ", aString); //####
    ODL_EXIT_LL(result); //####
    return result;
} // compareValueWithString
#endif//0

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMessage(const char * launchPath,
                   const int    argc,
                   char * *     argv) // empty message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytes[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageEmptyValue,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageEmptyValue
            };
            const size_t    expectedCount = (sizeof(expectedBytes) / sizeof(*expectedBytes));
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            stuff->open();
            if ((NULL != contents) || (0 != length))
            {
                ODL_LOG("((NULL != contents) || (0 != length))"); //####
            }
            else
            {
                stuff->close();
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedCount == length))
                {
                    result = memcmp(expectedBytes, contents, expectedCount);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedCount == length))"); //####
                }
            }
            delete stuff;
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
} // doTestEmptyMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestBooleanMessage(const char * launchPath,
                     const int    argc,
                     char * *     argv) // boolean message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForTrue[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedOtherValue,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherBoolean +
                  nImO::DataKind::kKindOtherBooleanTrueValue,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedTrueCount = (sizeof(expectedBytesForTrue) /
                                              sizeof(*expectedBytesForTrue));
            static const uint8_t expectedBytesForFalse[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedOtherValue,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherBoolean +
                  nImO::DataKind::kKindOtherBooleanFalseValue,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedFalseCount = (sizeof(expectedBytesForFalse) /
                                               sizeof(*expectedBytesForFalse));
            nImO::Boolean falseValue(false);
            nImO::Boolean trueValue(true);

            stuff->open();
            stuff->setValue(trueValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedTrueCount == length))
            {
                result = memcmp(expectedBytesForTrue, contents, expectedTrueCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedTrueCount == length))"); //####
            }
            if (0 == result)
            {
                stuff->open();
                stuff->setValue(falseValue);
                stuff->close();
                length = 0;
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedFalseCount == length))
                {
                    result = memcmp(expectedBytesForFalse, contents, expectedFalseCount);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedFalseCount == length))"); //####
                }
            }
            delete stuff;
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
} // doTestEmptyMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestTinyIntegerMessage(const char * launchPath,
                         const int    argc,
                         char * *     argv) // tiny integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForMinus12[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerShortValue +
                  (-12 & nImO::DataKind::kKindSignedIntegerShortValueValueMask),
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedMinus12Count = (sizeof(expectedBytesForMinus12) /
                                                 sizeof(*expectedBytesForMinus12));
            static const uint8_t expectedBytesForZero[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerShortValue +
                  0,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedZeroCount = (sizeof(expectedBytesForZero) /
                                              sizeof(*expectedBytesForZero));
            static const uint8_t expectedBytesForPlus12[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerShortValue +
                  (12 & nImO::DataKind::kKindSignedIntegerShortValueValueMask),
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedPlus12Count = (sizeof(expectedBytesForPlus12) /
                                                sizeof(*expectedBytesForPlus12));
            nImO::Integer minus12Value(-12);
            nImO::Integer zeroValue(0);
            nImO::Integer plus12Value(12);

            stuff->open();
            stuff->setValue(minus12Value);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedMinus12Count == length))
            {
                result = memcmp(expectedBytesForMinus12, contents, expectedMinus12Count);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedMinus12Count == length))"); //####
            }
            if (0 == result)
            {
                stuff->open();
                stuff->setValue(zeroValue);
                stuff->close();
                length = 0;
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedZeroCount == length))
                {
                    result = memcmp(expectedBytesForZero, contents, expectedZeroCount);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedZeroCount == length))"); //####
                }
            }
            if (0 == result)
            {
                stuff->open();
                stuff->setValue(plus12Value);
                stuff->close();
                length = 0;
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedPlus12Count == length))
                {
                    result = memcmp(expectedBytesForPlus12, contents, expectedPlus12Count);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedPlus12Count == length))"); //####
                }
            }
            delete stuff;
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
} // doTestTinyIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestShortIntegerMessage(const char * launchPath,
                          const int    argc,
                          char * *     argv) // short integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForMinus144[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerLongValue +
                  ((2 - 1) & nImO::DataKind::kKindSignedIntegerLongValueCountMask),
                0xFF, 0x70,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedMinus144Count = (sizeof(expectedBytesForMinus144) /
                                                  sizeof(*expectedBytesForMinus144));
            static const uint8_t expectedBytesForPlus144[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerLongValue +
                  ((2 - 1) & nImO::DataKind::kKindSignedIntegerLongValueCountMask),
                0x00, 0x90,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedPlus144Count = (sizeof(expectedBytesForPlus144) /
                                                 sizeof(*expectedBytesForPlus144));
            nImO::Integer minus144Value(-144);
            nImO::Integer plus144Value(144);

            stuff->open();
            stuff->setValue(minus144Value);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedMinus144Count == length))
            {
                result = memcmp(expectedBytesForMinus144, contents, expectedMinus144Count);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedMinus144Count == length))"); //####
            }
            if (0 == result)
            {
                stuff->open();
                stuff->setValue(plus144Value);
                stuff->close();
                length = 0;
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedPlus144Count == length))
                {
                    result = memcmp(expectedBytesForPlus144, contents, expectedPlus144Count);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedPlus144Count == length))"); //####
                }
            }
            delete stuff;
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
} // doTestShortIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestMediumIntegerMessage(const char * launchPath,
                           const int    argc,
                           char * *     argv) // medium integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForMinus1234567[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerLongValue +
                  ((3 - 1) & nImO::DataKind::kKindSignedIntegerLongValueCountMask),
                0xED, 0x29, 0x79,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedMinus1234567Count = (sizeof(expectedBytesForMinus1234567) /
                                                      sizeof(*expectedBytesForMinus1234567));
            static const uint8_t expectedBytesForPlus1234567[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerLongValue +
                  ((3 - 1) & nImO::DataKind::kKindSignedIntegerLongValueCountMask),
                0x12, 0xD6, 0x87,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedPlus1234567Count = (sizeof(expectedBytesForPlus1234567) /
                                                     sizeof(*expectedBytesForPlus1234567));
            nImO::Integer minus1234567Value(-1234567);
            nImO::Integer plus1234567Value(1234567);

            stuff->open();
            stuff->setValue(minus1234567Value);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedMinus1234567Count == length))
            {
                result = memcmp(expectedBytesForMinus1234567, contents, expectedMinus1234567Count);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedMinus1234567Count == length))"); //####
            }
            if (0 == result)
            {
                stuff->open();
                stuff->setValue(plus1234567Value);
                stuff->close();
                length = 0;
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedPlus1234567Count == length))
                {
                    result = memcmp(expectedBytesForPlus1234567, contents,
                                    expectedPlus1234567Count);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedPlus1234567Count == length))"); //####
                }
            }
            delete stuff;
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
} // doTestMediumIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 06 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestBigIntegerMessage(const char * launchPath,
                        const int    argc,
                        char * *     argv) // big integer message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForMinusBigNumber[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerLongValue +
                  ((6 - 1) & nImO::DataKind::kKindSignedIntegerLongValueCountMask),
                0xED, 0xCB, 0xA9, 0x87, 0x65, 0x44,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedMinusBigNumberCount = (sizeof(expectedBytesForMinusBigNumber) /
                                                        sizeof(*expectedBytesForMinusBigNumber));
            static const uint8_t expectedBytesForPlusBigNumber[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue,
                nImO::DataKind::kKindSignedInteger + nImO::DataKind::kKindSignedIntegerLongValue +
                  ((6 - 1) & nImO::DataKind::kKindSignedIntegerLongValueCountMask),
                0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedSignedIntegerValue
            };
            const size_t expectedPlusBigNumberCount = (sizeof(expectedBytesForPlusBigNumber) /
                                                       sizeof(*expectedBytesForPlusBigNumber));
            nImO::Integer minusBigNumberValue(-20015998343868);
            nImO::Integer plusBigNumberValue(20015998343868);

            stuff->open();
            stuff->setValue(minusBigNumberValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedMinusBigNumberCount == length))
            {
                result = memcmp(expectedBytesForMinusBigNumber, contents,
                                expectedMinusBigNumberCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedMinusBigNumberCount == length))"); //####
            }
            if (0 == result)
            {
                stuff->open();
                stuff->setValue(plusBigNumberValue);
                stuff->close();
                length = 0;
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedPlusBigNumberCount == length))
                {
                    result = memcmp(expectedBytesForPlusBigNumber, contents,
                                    expectedPlusBigNumberCount);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedPlusBigNumberCount == length))"); //####
                }
            }
            delete stuff;
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
} // doTestBigIntegerMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 07 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestEmptyStringMessage(const char * launchPath,
                         const int    argc,
                         char * *     argv) // empty string message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForEmptyString[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue,
                nImO::DataKind::kKindStringOrBlob + nImO::DataKind::kKindStringOrBlobStringValue +
                  nImO::DataKind::kKindStringOrBlobShortLengthValue +
                  (0 & nImO::DataKind::kKindStringOrBlobShortLengthMask),
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyStringCount = (sizeof(expectedBytesForEmptyString) /
                                                     sizeof(*expectedBytesForEmptyString));
            nImO::String emptyStringValue("");

            stuff->open();
            stuff->setValue(emptyStringValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedEmptyStringCount == length))
            {
                result = memcmp(expectedBytesForEmptyString, contents, expectedEmptyStringCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedEmptyStringCount == length))"); //####
            }
            delete stuff;
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
} // doTestEmptyStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 08 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestShortStringMessage(const char * launchPath,
                         const int    argc,
                         char * *     argv) // short string message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForShortString[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue,
                nImO::DataKind::kKindStringOrBlob + nImO::DataKind::kKindStringOrBlobStringValue +
                  nImO::DataKind::kKindStringOrBlobShortLengthValue +
                  (6 & nImO::DataKind::kKindStringOrBlobShortLengthMask),
                'a', 'b', 'c', 'd', 'e', 'f',
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortStringCount = (sizeof(expectedBytesForShortString) /
                                                     sizeof(*expectedBytesForShortString));
            nImO::String shortStringValue("abcdef");

            stuff->open();
            stuff->setValue(shortStringValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedShortStringCount == length))
            {
                result = memcmp(expectedBytesForShortString, contents, expectedShortStringCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedShortStringCount == length))"); //####
            }
            delete stuff;
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
} // doTestShortStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 09 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestMediumStringMessage(const char * launchPath,
                          const int    argc,
                          char * *     argv) // medium string message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForMediumString[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue,
                nImO::DataKind::kKindStringOrBlob + nImO::DataKind::kKindStringOrBlobStringValue +
                  nImO::DataKind::kKindStringOrBlobLongLengthValue +
                  ((1 - 1) & nImO::DataKind::kKindStringOrBlobLongLengthMask),
                42,
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedMediumStringCount = (sizeof(expectedBytesForMediumString) /
                                                     sizeof(*expectedBytesForMediumString));
            nImO::String mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

            stuff->open();
            stuff->setValue(mediumStringValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedMediumStringCount == length))
            {
                result = memcmp(expectedBytesForMediumString, contents, expectedMediumStringCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedMediumStringCount == length))"); //####
            }
            delete stuff;
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
} // doTestMediumStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestEmptyBlobMessage(const char * launchPath,
                       const int    argc,
                       char * *     argv) // empty blob message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForEmptyBlob[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue,
                nImO::DataKind::kKindStringOrBlob + nImO::DataKind::kKindStringOrBlobBlobValue +
                  nImO::DataKind::kKindStringOrBlobShortLengthValue +
                  (0 & nImO::DataKind::kKindStringOrBlobShortLengthMask),
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyBlobCount = (sizeof(expectedBytesForEmptyBlob) /
                                                   sizeof(*expectedBytesForEmptyBlob));
            nImO::Blob emptyBlobValue;

            stuff->open();
            stuff->setValue(emptyBlobValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedEmptyBlobCount == length))
            {
                result = memcmp(expectedBytesForEmptyBlob, contents, expectedEmptyBlobCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedEmptyBlobCount == length))"); //####
            }
            delete stuff;
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
} // doTestEmptyBlobMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 11 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestShortBlobMessage(const char * launchPath,
                       const int    argc,
                       char * *     argv) // short blob message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForShortBlob[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue,
                nImO::DataKind::kKindStringOrBlob + nImO::DataKind::kKindStringOrBlobBlobValue +
                  nImO::DataKind::kKindStringOrBlobShortLengthValue +
                  (6 & nImO::DataKind::kKindStringOrBlobShortLengthMask),
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortBlobCount = (sizeof(expectedBytesForShortBlob) /
                                                   sizeof(*expectedBytesForShortBlob));
            static const uint8_t actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t actualDataCount = (sizeof(actualData) / sizeof(*actualData));
            nImO::Blob   shortBlobValue(actualData, actualDataCount);

            stuff->open();
            stuff->setValue(shortBlobValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedShortBlobCount == length))
            {
                result = memcmp(expectedBytesForShortBlob, contents, expectedShortBlobCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedShortBlobCount == length))"); //####
            }
            delete stuff;
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
} // doTestShortBlobMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 12 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestMediumBlobMessage(const char * launchPath,
                        const int    argc,
                        char * *     argv) // medium blob message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForMediumBlob[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue,
                nImO::DataKind::kKindStringOrBlob + nImO::DataKind::kKindStringOrBlobBlobValue +
                  nImO::DataKind::kKindStringOrBlobLongLengthValue +
                  ((1 - 1) & nImO::DataKind::kKindStringOrBlobLongLengthMask),
                42,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedStringOrBlobValue
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
            nImO::Blob mediumBlobValue(actualData, actualDataCount);

            stuff->open();
            stuff->setValue(mediumBlobValue);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedMediumBlobCount == length))
            {
                result = memcmp(expectedBytesForMediumBlob, contents, expectedMediumBlobCount);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedMediumBlobCount == length))"); //####
            }
            delete stuff;
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
} // doTestMediumBlobMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 13 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestSingleFloatMessage(const char * launchPath,
                         const int    argc,
                         char * *     argv) // single float message
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        nImO::Message * stuff = new nImO::Message;

        if (stuff)
        {
            static const uint8_t expectedBytesForPlus42Point5[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedFloatingPointValue,
                nImO::DataKind::kKindFloatingPoint + nImO::DataKind::kKindFloatingPointShortCount +
                  (0 & nImO::DataKind::kKindFloatingPointShortCountMask),
                0x40, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedFloatingPointValue
            };
            const size_t expectedPlus42Point5Count = (sizeof(expectedBytesForPlus42Point5) /
                                                      sizeof(*expectedBytesForPlus42Point5));
            static const uint8_t expectedBytesForMinus42Point5[] =
            {
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageStartValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedFloatingPointValue,
                nImO::DataKind::kKindFloatingPoint + nImO::DataKind::kKindFloatingPointShortCount +
                  (0 & nImO::DataKind::kKindFloatingPointShortCountMask),
                0xC0, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
                nImO::DataKind::kKindOther + nImO::DataKind::kKindOtherMessage +
                  nImO::DataKind::kKindOtherMessageEndValue +
                  nImO::DataKind::kKindOtherMessageNonEmptyValue +
                  nImO::DataKind::kKindOtherMessageExpectedFloatingPointValue
            };
            const size_t expectedMinus42Point5Count = (sizeof(expectedBytesForMinus42Point5) /
                                                      sizeof(*expectedBytesForMinus42Point5));
            nImO::Double plus42Point5(42.5);
            nImO::Double minus42Point5(-42.5);

            stuff->open();
            stuff->setValue(plus42Point5);
            stuff->close();
            size_t          length = 0;
            const uint8_t * contents = stuff->getBytes(length);

            if ((NULL != contents) && (expectedPlus42Point5Count == length))
            {
                result = memcmp(expectedBytesForPlus42Point5, contents, expectedPlus42Point5Count);
            }
            else
            {
                ODL_LOG("! ((NULL != contents) && (expectedPlus42Point5Count == length))"); //####
            }
            if (0 == result)
            {
                stuff->open();
                stuff->setValue(minus42Point5);
                stuff->close();
                length = 0;
                contents = stuff->getBytes(length);
                if ((NULL != contents) && (expectedMinus42Point5Count == length))
                {
                    result = memcmp(expectedBytesForMinus42Point5, contents,
                                    expectedMinus42Point5Count);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedMinus42Point5Count == length))"); //####
                }
            }
            delete stuff;
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
} // doTestSingleFloatMessage
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
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used with the unit tests.
 @returns @c 0 on a successful test and @c 1 on failure. */
int
main(int      argc,
     char * * argv)
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
        nImO::Initialize(progName);
        if (0 < --argc)
        {
            const char * startPtr = argv[1];
            char *       endPtr;
            int          selector = strtol(startPtr, &endPtr, 10);

            ODL_LL1("selector <- ", selector); //####
            if ((startPtr != endPtr) && (! *endPtr) && (0 < selector))
            {
                nImO::SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestBooleanMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestShortIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestMediumIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 6 :
                        result = doTestBigIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 7 :
                        result = doTestEmptyStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 8 :
                        result = doTestShortStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 9 :
                        result = doTestMediumStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestEmptyBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 11 :
                        result = doTestShortBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestSingleFloatMessage(*argv, argc - 1, argv + 2);
                        break;

                    default :
                        break;

#if 0
# Test message with empty array
add_test(NAME TestEmptyArrayMessage COMMAND ${THIS_TARGET} 100)
# Test message with empty map
add_test(NAME TestEmptyMapMessage COMMAND ${THIS_TARGET} 101)
# Test message with empty set
add_test(NAME TestEmptySetMessage COMMAND ${THIS_TARGET} 102)

# Test message with array with one boolean
add_test(NAME TestArrayWithOneBooleanMessage COMMAND ${THIS_TARGET} 112)
# Test message with array with one integer
add_test(NAME TestArrayWithOneIntegerMessage COMMAND ${THIS_TARGET} 113)
# Test message with array with one double
add_test(NAME TestArrayWithOneDoubleMessage COMMAND ${THIS_TARGET} 114)
# Test message with array with one string
add_test(NAME TestArrayWithOneStringMessage COMMAND ${THIS_TARGET} 115)
# Test message with array with one blob
add_test(NAME TestArrayWithOneBlobMessage COMMAND ${THIS_TARGET} 116)
# Test message with array with one empty array
add_test(NAME TestArrayWithOneEmptyArrayMessage COMMAND ${THIS_TARGET} 117)
# Test message with array with one empty map
add_test(NAME TestArrayWithOneEmptyMapMessage COMMAND ${THIS_TARGET} 118)
# Test message with array with one empty set
add_test(NAME TestArrayWithOneEmptySetMessage COMMAND ${THIS_TARGET} 119)

# Test message with array with two booleans
add_test(NAME TestArrayWithTwoBooleansMessage COMMAND ${THIS_TARGET} 130)
# Test message with array with two integers
add_test(NAME TestArrayWithTwoIntegersMessage COMMAND ${THIS_TARGET} 131)
# Test message with array with two doubles
add_test(NAME TestArrayWithTwoDoublesMessage COMMAND ${THIS_TARGET} 132)
# Test message with array with two strings
add_test(NAME TestArrayWithTwoStringsMessage COMMAND ${THIS_TARGET} 133)
# Test message with array with two blobs
add_test(NAME TestArrayWithTwoBlobsMessage COMMAND ${THIS_TARGET} 134)
# Test message with array with two empty arrays
add_test(NAME TestArrayWithTwoEmptyArraysMessage COMMAND ${THIS_TARGET} 135)
# Test message with array with two empty maps
add_test(NAME TestArrayWithTwoEmptyMapsMessage COMMAND ${THIS_TARGET} 136)
# Test message with array with two empty sets
add_test(NAME TestArrayWithTwoEmptySetsMessage COMMAND ${THIS_TARGET} 137)
# Test message with array with empty array and empty map
add_test(NAME TestArrayWithEmptyArrayAndEmptyMapMessage COMMAND ${THIS_TARGET} 138)
# Test message with array with empty map and empty set
add_test(NAME TestArrayWithEmptyMapAndEmptySetMessage COMMAND ${THIS_TARGET} 139)
# Test message with array with empty set and empty array
add_test(NAME TestArrayWithEmptySetAndEmptyArrayMessage COMMAND ${THIS_TARGET} 140)

# Test message with boolean map
add_test(NAME TestBooleanMapMessage COMMAND ${THIS_TARGET} 150)
# Test message with integer map
add_test(NAME TestIntegerMapMessage COMMAND ${THIS_TARGET} 151)
# Test message with string map
add_test(NAME TestStringMapMessage COMMAND ${THIS_TARGET} 152)
# Test message with boolean set
add_test(NAME TestBooleanSetMessage COMMAND ${THIS_TARGET} 153)
# Test message with integer set
add_test(NAME TestIntegerSetMessage COMMAND ${THIS_TARGET} 154)
# Test message with string set
add_test(NAME TestStringSetMessage COMMAND ${THIS_TARGET} 155)
#endif//0

                }
                if (result)
                {
                    ODL_LL1("%%%%%%% unit test failure = ", result); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (2 < --argc)"); //####
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

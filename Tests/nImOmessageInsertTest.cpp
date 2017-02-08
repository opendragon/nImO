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
#include <nImO/nImOboolean.hpp>
#include <nImO/nImObufferChunk.hpp>
#include <nImO/nImOdouble.hpp>
#include <nImO/nImOinteger.hpp>
#include <nImO/nImOmap.hpp>
#include <nImO/nImOmessage.hpp>
#include <nImO/nImOset.hpp>
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
    message += nImO::NameOfSignal(signal);
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
setValueAndCheck(nImO::Message     &stuff,
                 const nImO::Value &aValue,
                 const uint8_t     *expectedContents,
                 const size_t      expectedSize)
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
    if ((NULL != contents) && (expectedSize == length))
    {
        result = nImO::CompareBytes(expectedContents, contents, expectedSize);
    }
    else
    {
        ODL_LOG("! ((NULL != contents) && (expectedSize == length))"); //####
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytes[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageEmptyValue
            };
            const size_t  expectedCount = (sizeof(expectedBytes) / sizeof(*expectedBytes));
            ODL_PACKET("expectedBytes", expectedBytes, expectedCount); //####
            size_t        length = 0;
            const uint8_t *contents = stuff->getBytes(length);

            stuff->open(true);
            if ((NULL != contents) || (0 != length))
            {
                ODL_LOG("((NULL != contents) || (0 != length))"); //####
            }
            else
            {
                stuff->close();
		contents = stuff->getBytes(length);
                ODL_PACKET("contents", contents, length); //####
                if ((NULL != contents) && (expectedCount == length))
                {
                    result = nImO::CompareBytes(expectedBytes, contents, expectedCount);
                }
                else
                {
                    ODL_LOG("! ((NULL != contents) && (expectedCount == length))"); //####
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
doTestInsertBooleanMessage(const char *launchPath,
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForTrue[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Boolean
                nImO::kKindOther + nImO::kKindOtherBoolean +
                  nImO::kKindOtherBooleanTrueValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedTrueCount = (sizeof(expectedBytesForTrue) /
                                              sizeof(*expectedBytesForTrue));
            static const uint8_t expectedBytesForFalse[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Boolean
                nImO::kKindOther + nImO::kKindOtherBoolean +
                  nImO::kKindOtherBooleanFalseValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedFalseCount = (sizeof(expectedBytesForFalse) /
                                               sizeof(*expectedBytesForFalse));
            nImO::Boolean falseValue(false);
            nImO::Boolean trueValue(true);

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
} // doTestInsertBooleanMessage
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForMinus12[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  (-12 &nImO::kKindIntegerShortValueValueMask),
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus12Count = (sizeof(expectedBytesForMinus12) /
                                                 sizeof(*expectedBytesForMinus12));
            static const uint8_t expectedBytesForZero[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  0,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedZeroCount = (sizeof(expectedBytesForZero) /
                                              sizeof(*expectedBytesForZero));
            static const uint8_t expectedBytesForPlus12[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  (12 &nImO::kKindIntegerShortValueValueMask),
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus12Count = (sizeof(expectedBytesForPlus12) /
                                                sizeof(*expectedBytesForPlus12));
            nImO::Integer minus12Value(-12);
            nImO::Integer zeroValue(0);
            nImO::Integer plus12Value(12);

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForMinus144[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerLongValue +
                  ((2 - 1) &nImO::kKindIntegerLongValueCountMask),
                0xFF, 0x70,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus144Count = (sizeof(expectedBytesForMinus144) /
                                                  sizeof(*expectedBytesForMinus144));
            static const uint8_t expectedBytesForPlus144[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerLongValue +
                  ((2 - 1) &nImO::kKindIntegerLongValueCountMask),
                0x00, 0x90,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus144Count = (sizeof(expectedBytesForPlus144) /
                                                 sizeof(*expectedBytesForPlus144));
            nImO::Integer minus144Value(-144);
            nImO::Integer plus144Value(144);

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForMinus1234567[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerLongValue +
                  ((3 - 1) &nImO::kKindIntegerLongValueCountMask),
                0xED, 0x29, 0x79,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedMinus1234567Count = (sizeof(expectedBytesForMinus1234567) /
                                                      sizeof(*expectedBytesForMinus1234567));
            static const uint8_t expectedBytesForPlus1234567[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerLongValue +
                  ((3 - 1) &nImO::kKindIntegerLongValueCountMask),
                0x12, 0xD6, 0x87,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedPlus1234567Count = (sizeof(expectedBytesForPlus1234567) /
                                                     sizeof(*expectedBytesForPlus1234567));
            nImO::Integer minus1234567Value(-1234567);
            nImO::Integer plus1234567Value(1234567);

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForMinusBigNumber[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerLongValue +
                  ((6 - 1) &nImO::kKindIntegerLongValueCountMask),
                0xED, 0xCB, 0xA9, 0x87, 0x65, 0x44,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedMinusBigNumberCount = (sizeof(expectedBytesForMinusBigNumber) /
                                                        sizeof(*expectedBytesForMinusBigNumber));
            static const uint8_t expectedBytesForPlusBigNumber[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerLongValue +
                  ((6 - 1) &nImO::kKindIntegerLongValueCountMask),
                0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedIntegerValue
            };
            const size_t expectedPlusBigNumberCount = (sizeof(expectedBytesForPlusBigNumber) /
                                                       sizeof(*expectedBytesForPlusBigNumber));
            nImO::Integer minusBigNumberValue(-20015998343868);
            nImO::Integer plusBigNumberValue(20015998343868);

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForEmptyString[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue,
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyStringCount = (sizeof(expectedBytesForEmptyString) /
                                                     sizeof(*expectedBytesForEmptyString));
            nImO::String emptyStringValue("");

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForShortString[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue,
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (6 &nImO::kKindStringOrBlobShortLengthMask),
                'a', 'b', 'c', 'd', 'e', 'f',
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortStringCount = (sizeof(expectedBytesForShortString) /
                                                     sizeof(*expectedBytesForShortString));
            nImO::String shortStringValue("abcdef");

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForMediumString[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue,
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobLongLengthValue +
                  ((1 - 1) &nImO::kKindStringOrBlobLongLengthMask),
                42,
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                'a', 'b', 'c', 'd', 'e', 'f',
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedMediumStringCount = (sizeof(expectedBytesForMediumString) /
                                                     sizeof(*expectedBytesForMediumString));
            nImO::String mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForEmptyBlob[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue,
                // Blob
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobBlobValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedEmptyBlobCount = (sizeof(expectedBytesForEmptyBlob) /
                                                   sizeof(*expectedBytesForEmptyBlob));
            nImO::Blob   emptyBlobValue;

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForShortBlob[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue,
                // Blob
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobBlobValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (6 &nImO::kKindStringOrBlobShortLengthMask),
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue
            };
            const size_t expectedShortBlobCount = (sizeof(expectedBytesForShortBlob) /
                                                   sizeof(*expectedBytesForShortBlob));
            static const uint8_t actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t actualDataCount = (sizeof(actualData) / sizeof(*actualData));
            nImO::Blob   shortBlobValue(actualData, actualDataCount);

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForMediumBlob[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue,
                // Blob
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobBlobValue +
                  nImO::kKindStringOrBlobLongLengthValue +
                  ((1 - 1) &nImO::kKindStringOrBlobLongLengthMask),
                42,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedStringOrBlobValue
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
            nImO::Blob   mediumBlobValue(actualData, actualDataCount);

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForPlus42Point5[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedDoubleValue,
                // Double
                nImO::kKindDouble + nImO::kKindDoubleShortCount +
                  ((1 - nImO::kKindDoubleShortCountMinValue) &
                    nImO::kKindDoubleShortCountMask),
                0x40, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedDoubleValue
            };
            const size_t expectedPlus42Point5Count = (sizeof(expectedBytesForPlus42Point5) /
                                                      sizeof(*expectedBytesForPlus42Point5));
            static const uint8_t expectedBytesForMinus42Point5[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedDoubleValue,
                // Double
                nImO::kKindDouble + nImO::kKindDoubleShortCount +
                  ((1 - nImO::kKindDoubleShortCountMinValue) &
                    nImO::kKindDoubleShortCountMask),
                0xC0, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedDoubleValue
            };
            const size_t expectedMinus42Point5Count = (sizeof(expectedBytesForMinus42Point5) /
                                                      sizeof(*expectedBytesForMinus42Point5));
            nImO::Double plus42Point5(42.5);
            nImO::Double minus42Point5(-42.5);

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForEmptyArray[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedEmptyArrayCount = (sizeof(expectedBytesForEmptyArray) /
                                                    sizeof(*expectedBytesForEmptyArray));
            nImO::Array  emptyArray;

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForEmptyMap[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedEmptyMapCount = (sizeof(expectedBytesForEmptyMap) /
                                                  sizeof(*expectedBytesForEmptyMap));
            nImO::Map    emptyMap;

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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForEmptySet[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedEmptySetCount = (sizeof(expectedBytesForEmptySet) /
                                                  sizeof(*expectedBytesForEmptySet));
            nImO::Set    emptySet;

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
doTestInsertArrayOneBooleanMessage(const char *launchPath,
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneBoolean[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Boolean
                nImO::kKindOther + nImO::kKindOtherBoolean +
                  nImO::kKindOtherBooleanFalseValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneBooleanCount = (sizeof(expectedBytesForArrayOneBoolean) /
                                                         sizeof(*expectedBytesForArrayOneBoolean));
            nImO::Array  arrayOneBoolean;

            arrayOneBoolean.addValue(new nImO::Boolean);
            result = setValueAndCheck(*stuff, arrayOneBoolean, expectedBytesForArrayOneBoolean,
                                      expectedArrayOneBooleanCount);
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
} // doTestInsertArrayOneBooleanMessage
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneInteger[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  0,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneIntegerCount = (sizeof(expectedBytesForArrayOneInteger) /
                                                         sizeof(*expectedBytesForArrayOneInteger));
            nImO::Array  arrayOneInteger;

            arrayOneInteger.addValue(new nImO::Integer);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneDouble[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Double
                nImO::kKindDouble + nImO::kKindDoubleShortCount +
                  ((1 - nImO::kKindDoubleShortCountMinValue) &
                    nImO::kKindDoubleShortCountMask),
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneDoubleCount = (sizeof(expectedBytesForArrayOneDouble) /
                                                        sizeof(*expectedBytesForArrayOneDouble));
            nImO::Array arrayOneDouble;

            arrayOneDouble.addValue(new nImO::Double);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneString[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneStringCount = (sizeof(expectedBytesForArrayOneString) /
                                                        sizeof(*expectedBytesForArrayOneString));
            nImO::Array  arrayOneString;

            arrayOneString.addValue(new nImO::String);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneBlob[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Blob
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobBlobValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneBlobCount = (sizeof(expectedBytesForArrayOneBlob) /
                                                      sizeof(*expectedBytesForArrayOneBlob));
            nImO::Array  arrayOneBlob;

            arrayOneBlob.addValue(new nImO::Blob);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneArray[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneArrayCount = (sizeof(expectedBytesForArrayOneArray) /
                                                       sizeof(*expectedBytesForArrayOneArray));
            nImO::Array  arrayOneArray;

            arrayOneArray.addValue(new nImO::Array);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneMap[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneMapCount = (sizeof(expectedBytesForArrayOneMap) /
                                                     sizeof(*expectedBytesForArrayOneMap));
            nImO::Array  arrayOneMap;

            arrayOneMap.addValue(new nImO::Map);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneSet[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneSetCount = (sizeof(expectedBytesForArrayOneSet) /
                                                     sizeof(*expectedBytesForArrayOneSet));
            nImO::Array  arrayOneSet;

            arrayOneSet.addValue(new nImO::Set);
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
doTestInsertArrayTwoBooleansMessage(const char *launchPath,
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoBooleans[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Boolean
                nImO::kKindOther + nImO::kKindOtherBoolean +
                  nImO::kKindOtherBooleanFalseValue,
                // Boolean
                nImO::kKindOther + nImO::kKindOtherBoolean +
                  nImO::kKindOtherBooleanFalseValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoBooleansCount =
                                                     (sizeof(expectedBytesForArrayTwoBooleans) /
                                                      sizeof(*expectedBytesForArrayTwoBooleans));
            nImO::Array  arrayTwoBooleans;

            arrayTwoBooleans.addValue(new nImO::Boolean);
            arrayTwoBooleans.addValue(new nImO::Boolean);
            result = setValueAndCheck(*stuff, arrayTwoBooleans, expectedBytesForArrayTwoBooleans,
                                      expectedArrayTwoBooleansCount);
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
} // doTestInsertArrayTwoBooleansMessage
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoIntegers[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  0,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  0,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoIntegersCount =
                                                     (sizeof(expectedBytesForArrayTwoIntegers) /
                                                      sizeof(*expectedBytesForArrayTwoIntegers));
            nImO::Array  arrayTwoIntegers;

            arrayTwoIntegers.addValue(new nImO::Integer);
            arrayTwoIntegers.addValue(new nImO::Integer);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoDoubles[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Double
                nImO::kKindDouble + nImO::kKindDoubleShortCount +
                  ((2 - nImO::kKindDoubleShortCountMinValue) &
                    nImO::kKindDoubleShortCountMask),
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoDoublesCount = (sizeof(expectedBytesForArrayTwoDoubles) /
                                                         sizeof(*expectedBytesForArrayTwoDoubles));
            nImO::Array  arrayTwoDoubles;

            arrayTwoDoubles.addValue(new nImO::Double);
            arrayTwoDoubles.addValue(new nImO::Double);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoStrings[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoStringsCount = (sizeof(expectedBytesForArrayTwoStrings) /
                                                         sizeof(*expectedBytesForArrayTwoStrings));
            nImO::Array  arrayTwoStrings;

            arrayTwoStrings.addValue(new nImO::String);
            arrayTwoStrings.addValue(new nImO::String);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoBlobs[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Blob
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobBlobValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // Blob
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobBlobValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoBlobsCount = (sizeof(expectedBytesForArrayTwoBlobs) /
                                                       sizeof(*expectedBytesForArrayTwoBlobs));
            nImO::Array  arrayTwoBlobs;

            arrayTwoBlobs.addValue(new nImO::Blob);
            arrayTwoBlobs.addValue(new nImO::Blob);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoArrays[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoArraysCount = (sizeof(expectedBytesForArrayTwoArrays) /
                                                        sizeof(*expectedBytesForArrayTwoArrays));
            nImO::Array  arrayTwoArrays;

            arrayTwoArrays.addValue(new nImO::Array);
            arrayTwoArrays.addValue(new nImO::Array);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoMaps[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoMapsCount = (sizeof(expectedBytesForArrayTwoMaps) /
                                                      sizeof(*expectedBytesForArrayTwoMaps));
            nImO::Array  arrayTwoMaps;

            arrayTwoMaps.addValue(new nImO::Map);
            arrayTwoMaps.addValue(new nImO::Map);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayTwoSets[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayTwoSetsCount = (sizeof(expectedBytesForArrayTwoSets) /
                                                      sizeof(*expectedBytesForArrayTwoSets));
            nImO::Array  arrayTwoSets;

            arrayTwoSets.addValue(new nImO::Set);
            arrayTwoSets.addValue(new nImO::Set);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneArrayOneMap[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneArrayOneMapCount =
                                                    (sizeof(expectedBytesForArrayOneArrayOneMap) /
                                                     sizeof(*expectedBytesForArrayOneArrayOneMap));
            nImO::Array  arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(new nImO::Array);
            arrayOneArrayOneMap.addValue(new nImO::Map);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneMapOneSet[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerEmptyValue,
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneMapOneSetCount =
                                                        (sizeof(expectedBytesForArrayOneMapOneSet) /
                                                        sizeof(*expectedBytesForArrayOneMapOneSet));
            nImO::Array  arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(new nImO::Map);
            arrayOneMapOneSet.addValue(new nImO::Set);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForArrayOneSetOneArray[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((2 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerEmptyValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerEmptyValue,
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayOneSetOneArrayCount =
                                                    (sizeof(expectedBytesForArrayOneSetOneArray) /
                                                     sizeof(*expectedBytesForArrayOneSetOneArray));
            nImO::Array  arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(new nImO::Set);
            arrayOneSetOneArray.addValue(new nImO::Array);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            const size_t         numValues = 43;
            static const uint8_t expectedBytesForArrayManyDoubles[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Array
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerLongValue +
                  ((1 - 1) &nImO::kKindIntegerLongValueCountMask),
                numValues + nImO::kKindIntegerShortValueMinValue - 1,
                // Double
                nImO::kKindDouble + nImO::kKindDoubleLongCount +
                  ((1 - 1) &nImO::kKindDoubleLongCountMask),
                numValues,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0
                0x3F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 1
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
                // End of Array
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeArray +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedArrayManyDoublesCount = (sizeof(expectedBytesForArrayManyDoubles) /
                                                        sizeof(*expectedBytesForArrayManyDoubles));
            nImO::Array  arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(new nImO::Double(ii));
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
doTestInsertBooleanMapMessage(const char *launchPath,
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForBooleanMap[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Boolean
                nImO::kKindOther + nImO::kKindOtherBoolean +
                  nImO::kKindOtherBooleanFalseValue,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  (13 &nImO::kKindIntegerShortValueValueMask),
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedBooleanMapCount = (sizeof(expectedBytesForBooleanMap) /
                                                    sizeof(*expectedBytesForBooleanMap));
            nImO::Map    booleanMap;

            booleanMap.addValue(new nImO::Boolean, new nImO::Integer(13));
            result = setValueAndCheck(*stuff, booleanMap, expectedBytesForBooleanMap,
                                      expectedBooleanMapCount);
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
} // doTestInsertBooleanMapMessage
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForIntegerMap[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  0,
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  (13 &nImO::kKindIntegerShortValueValueMask),
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedIntegerMapCount = (sizeof(expectedBytesForIntegerMap) /
                                                    sizeof(*expectedBytesForIntegerMap));
            nImO::Map    integerMap;

            integerMap.addValue(new nImO::Integer, new nImO::Integer(13));
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForStringMap[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Map
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  (13 &nImO::kKindIntegerShortValueValueMask),
                // End of Map
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeMap +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedStringMapCount = (sizeof(expectedBytesForStringMap) /
                                                   sizeof(*expectedBytesForStringMap));
            nImO::Map    stringMap;

            stringMap.addValue(new nImO::String, new nImO::Integer(13));
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
doTestInsertBooleanSetMessage(const char *launchPath,
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForBooleanSet[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Boolean
                nImO::kKindOther + nImO::kKindOtherBoolean +
                  nImO::kKindOtherBooleanFalseValue,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedBooleanSetCount = (sizeof(expectedBytesForBooleanSet) /
                                                    sizeof(*expectedBytesForBooleanSet));
            nImO::Set    booleanSet;

            booleanSet.addValue(new nImO::Boolean);
            result = setValueAndCheck(*stuff, booleanSet, expectedBytesForBooleanSet,
                                      expectedBooleanSetCount);
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
} // doTestInsertBooleanSetMessage
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForIntegerSet[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // Signed Integer
                nImO::kKindInteger + nImO::kKindIntegerShortValue +
                  0,
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedIntegerSetCount = (sizeof(expectedBytesForIntegerSet) /
                                                    sizeof(*expectedBytesForIntegerSet));
            nImO::Set    integerSet;

            integerSet.addValue(new nImO::Integer);
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
        nImO::UpMessage stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t expectedBytesForStringSet[] =
            {
                // Start of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageStartValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue,
                // Start of Set
                nImO::kKindOther + nImO::kKindOtherContainerStart +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerNonEmptyValue,
                // Signed Integer
                nImO::kKindInteger +
                  nImO::kKindIntegerShortValue +
                  ((1 + nImO::kKindIntegerShortValueMinValue - 1) &
                    nImO::kKindIntegerShortValueValueMask),
                // String
                nImO::kKindStringOrBlob + nImO::kKindStringOrBlobStringValue +
                  nImO::kKindStringOrBlobShortLengthValue +
                  (0 &nImO::kKindStringOrBlobShortLengthMask),
                // End of Set
                nImO::kKindOther + nImO::kKindOtherContainerEnd +
                  nImO::kKindOtherContainerTypeSet +
                  nImO::kKindOtherContainerNonEmptyValue,
                // End of Message
                nImO::kKindOther + nImO::kKindOtherMessage +
                  nImO::kKindOtherMessageEndValue +
                  nImO::kKindOtherMessageNonEmptyValue +
                  nImO::kKindOtherMessageExpectedOtherValue
            };
            const size_t expectedStringSetCount = (sizeof(expectedBytesForStringSet) /
                                                   sizeof(*expectedBytesForStringSet));
            nImO::Set    stringSet;

            stringSet.addValue(new nImO::String);
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
        nImO::Initialize(progName);
        if (0 < --argc)
        {
            const char *startPtr = argv[1];
            char       *endPtr;
            int        selector = strtol(startPtr, &endPtr, 10);

            ODL_LL1("selector <- ", selector); //####
            if ((startPtr != endPtr) && (! *endPtr) && (0 < selector))
            {
                nImO::SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestInsertEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestInsertBooleanMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestInsertArrayOneBooleanMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestInsertArrayTwoBooleansMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestInsertBooleanMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 161 :
                        result = doTestInsertIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 162 :
                        result = doTestInsertStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 163 :
                        result = doTestInsertBooleanSetMessage(*argv, argc - 1, argv + 2);
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

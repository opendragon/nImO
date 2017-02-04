//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOmessageExtractTest.cpp
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
//  Created:    2016-04-28
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

#if 0
/*! @brief The number of elements in a small test. */
static const size_t kSmallTestSize = 100;
#endif//0

#if 0
/*! @brief The number of elements in a big test. */
static const size_t kBigTestSize = 100000;
#endif//0

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

/*! @brief Extract a Value from a Message and verify what was stored.
 @param[in,out] stuff The Message to be modified.
 @param[in] insertedContents The data to be added to the Message.
 @param[in] insertedSize The size of the data added to the Message.
 @param[in] expectedValue The expected Value from the Message.
 @returns Zero on success and non-zero on failure. */
static int
extractValueAndCheck(nImO::Message     &stuff,
                     const uint8_t     *insertedContents,
                     const size_t      insertedSize,
                     const nImO::Value &expectedValue)
{
    ODL_ENTER(); //####
    ODL_P3("stuff = ", &stuff, "insertedContents = ", insertedContents, "expectedValue = ", //####
           &expectedValue); //####
    ODL_LL1("insertedSize = ", insertedSize); //####
    ODL_PACKET("inserted", insertedContents, insertedSize); //####
    int result = 1;

    // First, the 'this-should-work' test:
    stuff.open(false);
    stuff.appendBytes(insertedContents, insertedSize);
    nImO::ReadStatus             status = nImO::kReadInvalid;
    std::unique_ptr<nImO::Value> extractedValue(stuff.getValue(status));

    ODL_P1("extractedValue <- ", extractedValue.get()); //####
    ODL_LL1("status <- ", status); //####
    stuff.close();
    if (NULL == extractedValue)
    {
        ODL_LOG("(NULL == extractedValue)"); //####
    }
    else
    {
        if (nImO::kReadSuccessfulAtEnd == status)
        {
            if (extractedValue->deeplyEqualTo(expectedValue))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (extractedValue->deeplyEqualTo(expectedValue))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nImO::kReadSuccessfulAtEnd == status)"); //####
        }
    }
    if (0 == result)
    {
        // And now, let's make sure that 'short' messages are handled correctly:
        for (size_t ii = 1, shortenedSize = insertedSize - 1;
             (0 == result) && (shortenedSize > ii); ++ii)
        {
            stuff.open(false);
            stuff.appendBytes(insertedContents, ii);
            status = nImO::kReadInvalid;
            extractedValue.reset(stuff.getValue(status));
            ODL_P1("extractedValue <- ", extractedValue.get()); //####
            ODL_LL1("status <- ", status); //####
            stuff.close();
            if (NULL == extractedValue)
            {
                if (nImO::kReadIncomplete != status)
                {
                    ODL_LOG("(nImO::kReadIncomplete != status)"); //####
                    ODL_LL1("ii = ", ii); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! (NULL == extractedValue)");
                ODL_LL1("ii = ", ii); //####
                result = 1;
            }
        }
    }
    ODL_EXIT_LL(result); //####
    return result;
} // extractValueAndCheck

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
doTestEmptyMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            ODL_LOG("(stuff)"); //####
            static const uint8_t bytesToInsert[] =
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
            const size_t                 insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            ODL_PACKET("bytesToInsert", bytesToInsert, insertionCount); //####
            nImO::ReadStatus             status;
            std::unique_ptr<nImO::Value> extractedValue(stuff->getValue(status));

            ODL_P1("extractedValue <- ", extractedValue.get()); //####
            if ((NULL == extractedValue) && (nImO::kReadInvalid == status))
            {
                ODL_LOG("((NULL == extractedValue) && (nImO::kReadInvalid == status))"); //####
                stuff->open(true);
                stuff->close();
                stuff->open(false);
                stuff->appendBytes(bytesToInsert, insertionCount);
                extractedValue.reset(stuff->getValue(status));
                ODL_P1("extractedValue <- ", extractedValue.get()); //####
                stuff->close();
                if ((NULL == extractedValue) && (nImO::kReadSuccessfulAtEnd == status))
                {
                    ODL_LOG("((NULL == extractedValue) && (nImO::kReadSuccessfulAtEnd == " //####
                            "status))"); //####
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((NULL == extractedValue) && (nImO::kReadSuccessfulAtEnd == " //####
                            "status))"); //####
                }
                stuff->reset();
            }
            else
            {
                ODL_LOG("! ((NULL == extractedValue) && (nImO::kReadInvalid == status))"); //####
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
} // doTestEmptyMessage
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
doTestBooleanMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForTrue[] =
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
            const size_t insertedTrueCount = (sizeof(insertedBytesForTrue) /
                                              sizeof(*insertedBytesForTrue));
            static const uint8_t insertedBytesForFalse[] =
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
            const size_t  insertedFalseCount = (sizeof(insertedBytesForFalse) /
                                                sizeof(*insertedBytesForFalse));
            nImO::Boolean falseValue(false);
            nImO::Boolean trueValue(true);

            result = extractValueAndCheck(*stuff, insertedBytesForTrue, insertedTrueCount,
                                          trueValue);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForFalse, insertedFalseCount,
                                              falseValue);
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
} // doTestBooleanMessage
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
doTestTinyIntegerMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForMinus12[] =
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
            const size_t insertedMinus12Count = (sizeof(insertedBytesForMinus12) /
                                                 sizeof(*insertedBytesForMinus12));
            static const uint8_t insertedBytesForZero[] =
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
            const size_t insertedZeroCount = (sizeof(insertedBytesForZero) /
                                              sizeof(*insertedBytesForZero));
            static const uint8_t insertedBytesForPlus12[] =
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
            const size_t  insertedPlus12Count = (sizeof(insertedBytesForPlus12) /
                                                 sizeof(*insertedBytesForPlus12));
            nImO::Integer minus12Value(-12);
            nImO::Integer zeroValue(0);
            nImO::Integer plus12Value(12);
            
            result = extractValueAndCheck(*stuff, insertedBytesForMinus12, insertedMinus12Count,
                                          minus12Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForZero, insertedZeroCount,
                                              zeroValue);
            }
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus12, insertedPlus12Count,
                                              plus12Value);
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
} // doTestTinyIntegerMessage
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
doTestShortIntegerMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForMinus144[] =
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
            const size_t insertedMinus144Count = (sizeof(insertedBytesForMinus144) /
                                                  sizeof(*insertedBytesForMinus144));
            static const uint8_t insertedBytesForPlus144[] =
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
            const size_t  insertedPlus144Count = (sizeof(insertedBytesForPlus144) /
                                                  sizeof(*insertedBytesForPlus144));
            nImO::Integer minus144Value(-144);
            nImO::Integer plus144Value(144);

            result = extractValueAndCheck(*stuff, insertedBytesForMinus144, insertedMinus144Count,
                                          minus144Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus144, insertedPlus144Count,
                                              plus144Value);
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
} // doTestShortIntegerMessage
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
doTestMediumIntegerMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForMinus1234567[] =
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
            const size_t insertedMinus1234567Count = (sizeof(insertedBytesForMinus1234567) /
                                                      sizeof(*insertedBytesForMinus1234567));
            static const uint8_t insertedBytesForPlus1234567[] =
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
            const size_t  insertedPlus1234567Count = (sizeof(insertedBytesForPlus1234567) /
                                                      sizeof(*insertedBytesForPlus1234567));
            nImO::Integer minus1234567Value(-1234567);
            nImO::Integer plus1234567Value(1234567);

            result = extractValueAndCheck(*stuff, insertedBytesForMinus1234567,
                                          insertedMinus1234567Count, minus1234567Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus1234567,
                                              insertedPlus1234567Count, plus1234567Value);
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
} // doTestMediumIntegerMessage
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
doTestBigIntegerMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForMinusBigNumber[] =
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
            const size_t insertedMinusBigNumberCount = (sizeof(insertedBytesForMinusBigNumber) /
                                                        sizeof(*insertedBytesForMinusBigNumber));
            static const uint8_t insertedBytesForPlusBigNumber[] =
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
            const size_t  insertedPlusBigNumberCount = (sizeof(insertedBytesForPlusBigNumber) /
                                                        sizeof(*insertedBytesForPlusBigNumber));
            nImO::Integer minusBigNumberValue(-20015998343868);
            nImO::Integer plusBigNumberValue(20015998343868);

            result = extractValueAndCheck(*stuff, insertedBytesForMinusBigNumber,
                                          insertedMinusBigNumberCount, minusBigNumberValue);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlusBigNumber,
                                              insertedPlusBigNumberCount, plusBigNumberValue);
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
} // doTestBigIntegerMessage
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
doTestEmptyStringMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForEmptyString[] =
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
            const size_t insertedEmptyStringCount = (sizeof(insertedBytesForEmptyString) /
                                                     sizeof(*insertedBytesForEmptyString));
            nImO::String emptyStringValue;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyString,
                                          insertedEmptyStringCount, emptyStringValue);
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
doTestShortStringMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForShortString[] =
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
            const size_t insertedShortStringCount = (sizeof(insertedBytesForShortString) /
                                                     sizeof(*insertedBytesForShortString));
            nImO::String shortStringValue("abcdef");

            result = extractValueAndCheck(*stuff, insertedBytesForShortString,
                                          insertedShortStringCount, shortStringValue);
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
doTestMediumStringMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForMediumString[] =
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
            const size_t insertedMediumStringCount = (sizeof(insertedBytesForMediumString) /
                                                      sizeof(*insertedBytesForMediumString));
            nImO::String mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

            result = extractValueAndCheck(*stuff, insertedBytesForMediumString,
                                          insertedMediumStringCount, mediumStringValue);
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
doTestEmptyBlobMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForEmptyBlob[] =
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
            const size_t insertedEmptyBlobCount = (sizeof(insertedBytesForEmptyBlob) /
                                                   sizeof(*insertedBytesForEmptyBlob));
            nImO::Blob   emptyBlobValue;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyBlob,
                                          insertedEmptyBlobCount, emptyBlobValue);
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
doTestShortBlobMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForShortBlob[] =
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
            const size_t insertedShortBlobCount = (sizeof(insertedBytesForShortBlob) /
                                                   sizeof(*insertedBytesForShortBlob));
            static const uint8_t actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t actualDataCount = (sizeof(actualData) / sizeof(*actualData));
            nImO::Blob   shortBlobValue(actualData, actualDataCount);

            result = extractValueAndCheck(*stuff, insertedBytesForShortBlob,
                                          insertedShortBlobCount, shortBlobValue);
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
doTestMediumBlobMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForMediumBlob[] =
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
            const size_t insertedMediumBlobCount = (sizeof(insertedBytesForMediumBlob) /
                                                    sizeof(*insertedBytesForMediumBlob));
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

            result = extractValueAndCheck(*stuff, insertedBytesForMediumBlob,
                                          insertedMediumBlobCount, mediumBlobValue);
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
doTestSingleFloatMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForPlus42Point5[] =
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
            const size_t insertedPlus42Point5Count = (sizeof(insertedBytesForPlus42Point5) /
                                                      sizeof(*insertedBytesForPlus42Point5));
            static const uint8_t insertedBytesForMinus42Point5[] =
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
            const size_t insertedMinus42Point5Count = (sizeof(insertedBytesForMinus42Point5) /
                                                       sizeof(*insertedBytesForMinus42Point5));
            nImO::Double plus42Point5(42.5);
            nImO::Double minus42Point5(-42.5);

            result = extractValueAndCheck(*stuff, insertedBytesForMinus42Point5,
                                          insertedMinus42Point5Count, minus42Point5);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus42Point5,
                                              insertedPlus42Point5Count, plus42Point5);
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
} // doTestSingleFloatMessage
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
doTestEmptyArrayMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForEmptyArray[] =
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
            const size_t insertedEmptyArrayCount = (sizeof(insertedBytesForEmptyArray) /
                                                    sizeof(*insertedBytesForEmptyArray));
            nImO::Array  emptyArray;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyArray,
                                          insertedEmptyArrayCount, emptyArray);
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
} // doTestEmptyArrayMessage
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
doTestEmptyMapMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForEmptyMap[] =
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
            const size_t insertedEmptyMapCount = (sizeof(insertedBytesForEmptyMap) /
                                                  sizeof(*insertedBytesForEmptyMap));
            nImO::Map    emptyMap;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyMap,
                                          insertedEmptyMapCount, emptyMap);
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
} // doTestEmptyMapMessage
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
doTestEmptySetMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForEmptySet[] =
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
            const size_t insertedEmptySetCount = (sizeof(insertedBytesForEmptySet) /
                                                  sizeof(*insertedBytesForEmptySet));
            nImO::Set    emptySet;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptySet,
                                          insertedEmptySetCount, emptySet);
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
} // doTestEmptySetMessage
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
doTestArrayOneBooleanMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneBoolean[] =
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
            const size_t insertedArrayOneBooleanCount = (sizeof(insertedBytesForArrayOneBoolean) /
                                                         sizeof(*insertedBytesForArrayOneBoolean));
            nImO::Array  arrayOneBoolean;

            arrayOneBoolean.addValue(new nImO::Boolean);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneBoolean,
                                          insertedArrayOneBooleanCount, arrayOneBoolean);
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
} // doTestArrayOneBooleanMessage
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
doTestArrayOneIntegerMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneInteger[] =
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
            const size_t insertedArrayOneIntegerCount = (sizeof(insertedBytesForArrayOneInteger) /
                                                         sizeof(*insertedBytesForArrayOneInteger));
            nImO::Array  arrayOneInteger;

            arrayOneInteger.addValue(new nImO::Integer);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneInteger,
                                          insertedArrayOneIntegerCount, arrayOneInteger);
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
} // doTestArrayOneIntegerMessage
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
doTestArrayOneDoubleMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneDouble[] =
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
            const size_t insertedArrayOneDoubleCount = (sizeof(insertedBytesForArrayOneDouble) /
                                                        sizeof(*insertedBytesForArrayOneDouble));
            nImO::Array  arrayOneDouble;

            arrayOneDouble.addValue(new nImO::Double);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneDouble,
                                          insertedArrayOneDoubleCount, arrayOneDouble);
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
} // doTestArrayOneDoubleMessage
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
doTestArrayOneStringMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneString[] =
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
            const size_t insertedArrayOneStringCount = (sizeof(insertedBytesForArrayOneString) /
                                                        sizeof(*insertedBytesForArrayOneString));
            nImO::Array  arrayOneString;

            arrayOneString.addValue(new nImO::String);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneString,
                                          insertedArrayOneStringCount, arrayOneString);
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
} // doTestArrayOneStringMessage
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
doTestArrayOneBlobMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneBlob[] =
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
            const size_t insertedArrayOneBlobCount = (sizeof(insertedBytesForArrayOneBlob) /
                                                      sizeof(*insertedBytesForArrayOneBlob));
            nImO::Array  arrayOneBlob;

            arrayOneBlob.addValue(new nImO::Blob);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneBlob,
                                          insertedArrayOneBlobCount, arrayOneBlob);
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
} // doTestArrayOneBlobMessage
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
doTestArrayOneArrayMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneArray[] =
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
            const size_t insertedArrayOneArrayCount = (sizeof(insertedBytesForArrayOneArray) /
                                                       sizeof(*insertedBytesForArrayOneArray));
            nImO::Array  arrayOneArray;

            arrayOneArray.addValue(new nImO::Array);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneArray,
                                          insertedArrayOneArrayCount, arrayOneArray);
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
} // doTestArrayOneArrayMessage
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
doTestArrayOneMapMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneMap[] =
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
            const size_t insertedArrayOneMapCount = (sizeof(insertedBytesForArrayOneMap) /
                                                     sizeof(*insertedBytesForArrayOneMap));
            nImO::Array  arrayOneMap;

            arrayOneMap.addValue(new nImO::Map);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneMap,
                                          insertedArrayOneMapCount, arrayOneMap);
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
} // doTestArrayOneMapMessage
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
doTestArrayOneSetMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneSet[] =
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
            const size_t insertedArrayOneSetCount = (sizeof(insertedBytesForArrayOneSet) /
                                                     sizeof(*insertedBytesForArrayOneSet));
            nImO::Array  arrayOneSet;

            arrayOneSet.addValue(new nImO::Set);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneSet,
                                          insertedArrayOneSetCount, arrayOneSet);
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
} // doTestArrayOneSetMessage
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
doTestArrayTwoBooleansMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoBooleans[] =
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
            const size_t insertedArrayTwoBooleansCount = (sizeof(insertedBytesForArrayTwoBooleans) /
                                                         sizeof(*insertedBytesForArrayTwoBooleans));
            nImO::Array  arrayTwoBooleans;

            arrayTwoBooleans.addValue(new nImO::Boolean);
            arrayTwoBooleans.addValue(new nImO::Boolean);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoBooleans,
                                          insertedArrayTwoBooleansCount, arrayTwoBooleans);
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
} // doTestArrayTwoBooleansMessage
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
doTestArrayTwoIntegersMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoIntegers[] =
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
            const size_t insertedArrayTwoIntegersCount =
                                                     (sizeof(insertedBytesForArrayTwoIntegers) /
                                                      sizeof(*insertedBytesForArrayTwoIntegers));
            nImO::Array  arrayTwoIntegers;

            arrayTwoIntegers.addValue(new nImO::Integer);
            arrayTwoIntegers.addValue(new nImO::Integer);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoIntegers,
                                          insertedArrayTwoIntegersCount, arrayTwoIntegers);
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
} // doTestArrayTwoIntegersMessage
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
doTestArrayTwoDoublesMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoDoubles[] =
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
            const size_t insertedArrayTwoDoublesCount = (sizeof(insertedBytesForArrayTwoDoubles) /
                                                         sizeof(*insertedBytesForArrayTwoDoubles));
            nImO::Array  arrayTwoDoubles;

            arrayTwoDoubles.addValue(new nImO::Double);
            arrayTwoDoubles.addValue(new nImO::Double);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoDoubles,
                                          insertedArrayTwoDoublesCount, arrayTwoDoubles);
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
} // doTestArrayTwoDoublesMessage
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
doTestArrayTwoStringsMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoStrings[] =
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
            const size_t insertedArrayTwoStringsCount = (sizeof(insertedBytesForArrayTwoStrings) /
                                                         sizeof(*insertedBytesForArrayTwoStrings));
            nImO::Array  arrayTwoStrings;

            arrayTwoStrings.addValue(new nImO::String);
            arrayTwoStrings.addValue(new nImO::String);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoStrings,
                                          insertedArrayTwoStringsCount, arrayTwoStrings);
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
} // doTestArrayTwoStringsMessage
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
doTestArrayTwoBlobsMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoBlobs[] =
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
            const size_t insertedArrayTwoBlobsCount = (sizeof(insertedBytesForArrayTwoBlobs) /
                                                       sizeof(*insertedBytesForArrayTwoBlobs));
            nImO::Array  arrayTwoBlobs;

            arrayTwoBlobs.addValue(new nImO::Blob);
            arrayTwoBlobs.addValue(new nImO::Blob);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoBlobs,
                                          insertedArrayTwoBlobsCount, arrayTwoBlobs);
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
} // doTestArrayTwoBlobsMessage
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
doTestArrayTwoArraysMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoArrays[] =
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
            const size_t insertedArrayTwoArraysCount = (sizeof(insertedBytesForArrayTwoArrays) /
                                                        sizeof(*insertedBytesForArrayTwoArrays));
            nImO::Array  arrayTwoArrays;

            arrayTwoArrays.addValue(new nImO::Array);
            arrayTwoArrays.addValue(new nImO::Array);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoArrays,
                                          insertedArrayTwoArraysCount, arrayTwoArrays);
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
} // doTestArrayTwoArraysMessage
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
doTestArrayTwoMapsMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoMaps[] =
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
            const size_t insertedArrayTwoMapsCount = (sizeof(insertedBytesForArrayTwoMaps) /
                                                      sizeof(*insertedBytesForArrayTwoMaps));
            nImO::Array  arrayTwoMaps;

            arrayTwoMaps.addValue(new nImO::Map);
            arrayTwoMaps.addValue(new nImO::Map);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoMaps,
                                          insertedArrayTwoMapsCount, arrayTwoMaps);
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
} // doTestArrayTwoMapsMessage
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
doTestArrayTwoSetsMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayTwoSets[] =
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
            const size_t insertedArrayTwoSetsCount = (sizeof(insertedBytesForArrayTwoSets) /
                                                      sizeof(*insertedBytesForArrayTwoSets));
            nImO::Array  arrayTwoSets;

            arrayTwoSets.addValue(new nImO::Set);
            arrayTwoSets.addValue(new nImO::Set);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoSets,
                                          insertedArrayTwoSetsCount, arrayTwoSets);
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
} // doTestArrayTwoSetsMessage
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
doTestArrayOneArrayOneMapMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneArrayOneMap[] =
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
            const size_t insertedArrayOneArrayOneMapCount =
                                                    (sizeof(insertedBytesForArrayOneArrayOneMap) /
                                                     sizeof(*insertedBytesForArrayOneArrayOneMap));
            nImO::Array  arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(new nImO::Array);
            arrayOneArrayOneMap.addValue(new nImO::Map);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneArrayOneMap,
                                          insertedArrayOneArrayOneMapCount, arrayOneArrayOneMap);
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
} // doTestArrayOneArrayOneMapMessage
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
doTestArrayOneMapOneSetMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneMapOneSet[] =
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
            const size_t insertedArrayOneMapOneSetCount =
                                                      (sizeof(insertedBytesForArrayOneMapOneSet) /
                                                       sizeof(*insertedBytesForArrayOneMapOneSet));
            nImO::Array  arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(new nImO::Map);
            arrayOneMapOneSet.addValue(new nImO::Set);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneMapOneSet,
                                          insertedArrayOneMapOneSetCount, arrayOneMapOneSet);
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
} // doTestArrayOneMapOneSetMessage
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
doTestArrayOneSetOneArrayMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForArrayOneSetOneArray[] =
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
            const size_t insertedArrayOneSetOneArrayCount =
                                                    (sizeof(insertedBytesForArrayOneSetOneArray) /
                                                     sizeof(*insertedBytesForArrayOneSetOneArray));
            nImO::Array  arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(new nImO::Set);
            arrayOneSetOneArray.addValue(new nImO::Array);
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneSetOneArray,
                                          insertedArrayOneSetOneArrayCount, arrayOneSetOneArray);
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
} // doTestArrayOneSetOneArrayMessage
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
doTestArrayWithManyDoublesMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            const size_t         numValues = 43;
            static const uint8_t insertedBytesForArrayManyDoubles[] =
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
            const size_t insertedArrayManyDoublesCount =
                                                     (sizeof(insertedBytesForArrayManyDoubles) /
                                                      sizeof(*insertedBytesForArrayManyDoubles));
            nImO::Array  arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(new nImO::Double(ii));
            }
            result = extractValueAndCheck(*stuff, insertedBytesForArrayManyDoubles,
                                          insertedArrayManyDoublesCount, arrayManyDoubles);
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
} // doTestArrayWithManyDoublesMessage

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
doTestBooleanMapMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForBooleanMap[] =
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
            const size_t insertedBooleanMapCount = (sizeof(insertedBytesForBooleanMap) /
                                                    sizeof(*insertedBytesForBooleanMap));
            nImO::Map    booleanMap;

            booleanMap.addValue(new nImO::Boolean, new nImO::Integer(13));
            result = extractValueAndCheck(*stuff, insertedBytesForBooleanMap,
                                          insertedBooleanMapCount, booleanMap);
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
} // doTestBooleanMapMessage
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
doTestIntegerMapMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForIntegerMap[] =
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
            const size_t insertedIntegerMapCount = (sizeof(insertedBytesForIntegerMap) /
                                                    sizeof(*insertedBytesForIntegerMap));
            nImO::Map    integerMap;

            integerMap.addValue(new nImO::Integer, new nImO::Integer(13));
            result = extractValueAndCheck(*stuff, insertedBytesForIntegerMap,
                                          insertedIntegerMapCount, integerMap);
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
} // doTestIntegerMapMessage
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
doTestStringMapMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForStringMap[] =
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
            const size_t insertedStringMapCount = (sizeof(insertedBytesForStringMap) /
                                                   sizeof(*insertedBytesForStringMap));
            nImO::Map    stringMap;

            stringMap.addValue(new nImO::String, new nImO::Integer(13));
            result = extractValueAndCheck(*stuff, insertedBytesForStringMap,
                                          insertedStringMapCount, stringMap);
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
} // doTestStringMapMessage
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
doTestBooleanSetMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForBooleanSet[] =
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
            const size_t insertedBooleanSetCount = (sizeof(insertedBytesForBooleanSet) /
                                                    sizeof(*insertedBytesForBooleanSet));
            nImO::Set    booleanSet;

            booleanSet.addValue(new nImO::Boolean);
            result = extractValueAndCheck(*stuff, insertedBytesForBooleanSet,
                                          insertedBooleanSetCount, booleanSet);
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
} // doTestBooleanSetMessage
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
doTestIntegerSetMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForIntegerSet[] =
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
            const size_t insertedIntegerSetCount = (sizeof(insertedBytesForIntegerSet) /
                                                    sizeof(*insertedBytesForIntegerSet));
            nImO::Set    integerSet;

            integerSet.addValue(new nImO::Integer);
            result = extractValueAndCheck(*stuff, insertedBytesForIntegerSet,
                                          insertedIntegerSetCount, integerSet);
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
} // doTestIntegerSetMessage
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
doTestStringSetMessage(const char *launchPath,
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
        std::unique_ptr<nImO::Message> stuff(new nImO::Message);

        if (stuff)
        {
            static const uint8_t insertedBytesForStringSet[] =
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
            const size_t insertedStringSetCount = (sizeof(insertedBytesForStringSet) /
                                                   sizeof(*insertedBytesForStringSet));
            nImO::Set    stringSet;

            stringSet.addValue(new nImO::String);
            result = extractValueAndCheck(*stuff, insertedBytesForStringSet,
                                          insertedStringSetCount, stringSet);
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
} // doTestStringSetMessage
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

                    case 100 :
                        result = doTestEmptyArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestEmptyMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestEmptySetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 110 :
                        result = doTestArrayOneBooleanMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 111 :
                        result = doTestArrayOneIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 112 :
                        result = doTestArrayOneDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 113 :
                        result = doTestArrayOneStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 114 :
                        result = doTestArrayOneBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 115 :
                        result = doTestArrayOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 116 :
                        result = doTestArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 117 :
                        result = doTestArrayOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 130 :
                        result = doTestArrayTwoBooleansMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 131 :
                        result = doTestArrayTwoIntegersMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 132 :
                        result = doTestArrayTwoDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 133 :
                        result = doTestArrayTwoStringsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 134 :
                        result = doTestArrayTwoBlobsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 135 :
                        result = doTestArrayTwoArraysMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 136 :
                        result = doTestArrayTwoMapsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 137 :
                        result = doTestArrayTwoSetsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 138 :
                        result = doTestArrayOneArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 139 :
                        result = doTestArrayOneMapOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 140 :
                        result = doTestArrayOneSetOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 141 :
                        result = doTestArrayWithManyDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 160 :
                        result = doTestBooleanMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 161 :
                        result = doTestIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 162 :
                        result = doTestStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 163 :
                        result = doTestBooleanSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 164 :
                        result = doTestIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 165 :
                        result = doTestStringSetMessage(*argv, argc - 1, argv + 2);
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

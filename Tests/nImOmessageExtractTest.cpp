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

#include <nImOarray.hpp>
#include <nImOblob.hpp>
#include <nImObufferChunk.hpp>
#include <nImOdouble.hpp>
#include <nImOflaw.hpp>
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
[[noreturn]]
static void
catchSignal
    (int signal)
{
    ODL_ENTER(); //####
    ODL_I1("signal = ", signal); //####
    std::string message{"Exiting due to signal "};

    message += std::to_string(signal);
    message += " = ";
    message += NameOfSignal(signal);
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
 @return Zero on success and non-zero on failure. */
static int
extractValueAndCheck
    (Message &          stuff,
     const DataKind *   insertedContents,
     const size_t       insertedSize,
     const Value &      expectedValue)
{
    ODL_ENTER(); //####
    ODL_P3("stuff = ", &stuff, "insertedContents = ", insertedContents, "expectedValue = ", //####
           &expectedValue); //####
    ODL_I1("insertedSize = ", insertedSize); //####
    ODL_PACKET("inserted", insertedContents, insertedSize); //####
    int result = 1;

    // First, the 'this-should-work' test:
    stuff.open(false);
    stuff.appendBytes(insertedContents, insertedSize);
    SpValue extractedValue{stuff.getValue()};

    ODL_P1("extractedValue <- ", extractedValue.get()); //####
    stuff.close();
    if (nullptr == extractedValue)
    {
        ODL_LOG("(nullptr == extractedValue)"); //####
    }
    else
    {
        const Flaw *    asFlaw = extractedValue->asFlaw();

        if (asFlaw)
        {
            ODL_LOG("(asFlaw)"); //####
            ODL_LOG(asFlaw->getDescription().c_str()); //####
        }
        else if (stuff.readAtEnd())
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
            ODL_LOG("! (stuff.readAtEnd())"); //####
        }
    }
    if (0 == result)
    {
        // And now, let's make sure that 'short' messages are handled correctly:
        for (size_t ii = 1, shortenedSize = insertedSize - 1; (0 == result) && (shortenedSize > ii); ++ii)
        {
            stuff.open(false);
            stuff.appendBytes(insertedContents, ii);
            extractedValue = stuff.getValue();
            ODL_P1("extractedValue <- ", extractedValue.get()); //####
            stuff.close();
            if (nullptr != extractedValue)
            {
                const Flaw *    asFlaw = extractedValue->asFlaw();

                if (asFlaw)
                {
                    ODL_LOG("(asFlaw)"); //####
                    ODL_LOG(asFlaw->getDescription().c_str()); //####
                }
                else
                {
                    ODL_LOG("! (nullptr == extractedValue)");
                    ODL_I1("ii = ", ii); //####
                    result = 1;
                }
            }
        }
    }
    ODL_EXIT_I(result); //####
    return result;
} // extractValueAndCheck

#if defined(__APPLE__)
# pragma mark *** Test Case 001 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // empty message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            ODL_LOG("(stuff)"); //####
            static const DataKind   bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            const size_t            insertionCount = A_SIZE(bytesToInsert);
            ODL_PACKET("bytesToInsert", bytesToInsert, insertionCount); //####
            SpValue                 extractedValue{stuff->getValue()};

            ODL_P1("extractedValue <- ", extractedValue.get()); //####
            if (stuff->readAtEnd())
            {
                if (nullptr == extractedValue)
                {
                    ODL_LOG("Null Value read"); //####
                }
                else
                {
                    const Flaw *    asFlaw = extractedValue->asFlaw();

                    if (asFlaw)
                    {
                        ODL_LOG("(asFlaw)"); //####
                        ODL_LOG(asFlaw->getDescription().c_str()); //####
                        stuff->open(true);
                        stuff->close();
                        stuff->open(false);
                        stuff->appendBytes(bytesToInsert, insertionCount);
                        extractedValue = stuff->getValue();
                        ODL_P1("extractedValue <- ", extractedValue.get()); //####
                        stuff->close();
                        if (stuff->readAtEnd())
                        {
                            if (nullptr == extractedValue)
                            {
                                ODL_LOG("(nullptr == extractedValue)"); //####
                                result = 0;
                            }
                            else
                            {
                                asFlaw = extractedValue->asFlaw();
                                if (asFlaw)
                                {
                                    ODL_LOG("(asFlaw)"); //####
                                    ODL_LOG(asFlaw->getDescription().c_str()); //####
                                }
                                else
                                {
                                    ODL_LOG("! (asFlaw)"); //####
                                }
                            }
                        }
                        stuff->reset();
                    }
                }
            }
            else
            {
                ODL_LOG("! (stuff->readAtEnd())"); //####
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // logical message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForTrue[] =
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
            const size_t            insertedTrueCount = A_SIZE(insertedBytesForTrue);
            static const DataKind   insertedBytesForFalse[] =
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
            const size_t            insertedFalseCount = A_SIZE(insertedBytesForFalse);
            Logical                 falseValue(false);
            Logical                 trueValue(true);

            result = extractValueAndCheck(*stuff, insertedBytesForTrue, insertedTrueCount, trueValue);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForFalse, insertedFalseCount, falseValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestTinyIntegerMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // tiny integer message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinus12[] =
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
            const size_t            insertedMinus12Count = A_SIZE(insertedBytesForMinus12);
            static const DataKind   insertedBytesForZero[] =
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
            const size_t            insertedZeroCount = A_SIZE(insertedBytesForZero);
            static const DataKind   insertedBytesForPlus12[] =
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
            const size_t            insertedPlus12Count = A_SIZE(insertedBytesForPlus12);
            Integer                 minus12Value(-12);
            Integer                 zeroValue(0);
            Integer                 plus12Value(12);

            result = extractValueAndCheck(*stuff, insertedBytesForMinus12, insertedMinus12Count, minus12Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForZero, insertedZeroCount, zeroValue);
            }
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus12, insertedPlus12Count, plus12Value);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestTinyIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallIntegerMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // small integer message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinus144[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((2 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0xFF), StaticCast(DataKind, 0x70),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t            insertedMinus144Count = A_SIZE(insertedBytesForMinus144);
            static const DataKind   insertedBytesForPlus144[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((2 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x90),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t            insertedPlus144Count = A_SIZE(insertedBytesForPlus144);
            Integer                 minus144Value(-144);
            Integer                 plus144Value(144);

            result = extractValueAndCheck(*stuff, insertedBytesForMinus144, insertedMinus144Count, minus144Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus144, insertedPlus144Count, plus144Value);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMediumIntegerMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // medium integer message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinus1234567[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((3 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0xED), StaticCast(DataKind, 0x29),
                StaticCast(DataKind, 0x79),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t            insertedMinus1234567Count = A_SIZE(insertedBytesForMinus1234567);
            static const DataKind   insertedBytesForPlus1234567[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((3 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0xD6),
                StaticCast(DataKind, 0x87),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t            insertedPlus1234567Count = A_SIZE(insertedBytesForPlus1234567);
            Integer                 minus1234567Value(-1234567);
            Integer                 plus1234567Value(1234567);

            result = extractValueAndCheck(*stuff, insertedBytesForMinus1234567, insertedMinus1234567Count, minus1234567Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus1234567, insertedPlus1234567Count, plus1234567Value);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestMediumIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBigIntegerMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // big integer message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinusBigNumber[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((6 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0xED), StaticCast(DataKind, 0xCB),
                StaticCast(DataKind, 0xA9), StaticCast(DataKind, 0x87),
                StaticCast(DataKind, 0x65), StaticCast(DataKind, 0x44),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t            insertedMinusBigNumberCount = A_SIZE(insertedBytesForMinusBigNumber);
            static const DataKind   insertedBytesForPlusBigNumber[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((6 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x34),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x78),
                StaticCast(DataKind, 0x9A), StaticCast(DataKind, 0xBC),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t            insertedPlusBigNumberCount = A_SIZE(insertedBytesForPlusBigNumber);
            Integer                 minusBigNumberValue(-20015998343868);
            Integer                 plusBigNumberValue(20015998343868);

            result = extractValueAndCheck(*stuff, insertedBytesForMinusBigNumber, insertedMinusBigNumberCount, minusBigNumberValue);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlusBigNumber, insertedPlusBigNumberCount, plusBigNumberValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestBigIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 007 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyStringMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // empty string message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyString[] =
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
            const size_t            insertedEmptyStringCount = A_SIZE(insertedBytesForEmptyString);
            String                  emptyStringValue;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyString, insertedEmptyStringCount, emptyStringValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 008 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestShortStringMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // short string message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForShortString[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (6 & DataKind::StringOrBlobShortLengthMask),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t            insertedShortStringCount = A_SIZE(insertedBytesForShortString);
            String                  shortStringValue("abcdef");

            result = extractValueAndCheck(*stuff, insertedBytesForShortString, insertedShortStringCount, shortStringValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestShortStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 009 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMediumStringMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // medium string message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMediumString[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobLongLengthValue |
                  ((1 - 1) & DataKind::StringOrBlobLongLengthMask),
                StaticCast(DataKind, 42),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                StaticCast(DataKind, 'a'), StaticCast(DataKind, 'b'),
                StaticCast(DataKind, 'c'), StaticCast(DataKind, 'd'),
                StaticCast(DataKind, 'e'), StaticCast(DataKind, 'f'),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t            insertedMediumStringCount = A_SIZE(insertedBytesForMediumString);
            String                  mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

            result = extractValueAndCheck(*stuff, insertedBytesForMediumString, insertedMediumStringCount, mediumStringValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestMediumStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 010 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyBlobMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // empty blob message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyBlob[] =
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
            const size_t            insertedEmptyBlobCount = A_SIZE(insertedBytesForEmptyBlob);
            Blob                    emptyBlobValue;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyBlob, insertedEmptyBlobCount, emptyBlobValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 011 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallBlobMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // small blob message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForSmallBlob[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (6 & DataKind::StringOrBlobShortLengthMask),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t            insertedSmallBlobCount = A_SIZE(insertedBytesForSmallBlob);
            static const uint8_t    actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t            actualDataCount = A_SIZE(actualData);
            Blob                    shortBlobValue(actualData, actualDataCount);

            result = extractValueAndCheck(*stuff, insertedBytesForSmallBlob, insertedSmallBlobCount, shortBlobValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 012 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMediumBlobMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // medium blob message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMediumBlob[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobLongLengthValue |
                  ((1 - 1) & DataKind::StringOrBlobLongLengthMask),
                StaticCast(DataKind, 42),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                StaticCast(DataKind, 0x12), StaticCast(DataKind, 0x23),
                StaticCast(DataKind, 0x34), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x56), StaticCast(DataKind, 0x67),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t            insertedMediumBlobCount = A_SIZE(insertedBytesForMediumBlob);
            static const uint8_t    actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t            actualDataCount = A_SIZE(actualData);
            Blob                    mediumBlobValue(actualData, actualDataCount);

            result = extractValueAndCheck(*stuff, insertedBytesForMediumBlob, insertedMediumBlobCount, mediumBlobValue);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestMediumBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 013 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingleDoubleMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // single double message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForPlus42Point5[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - DataKindDoubleShortCountMinValue) &
                    DataKind::DoubleShortCountMask),
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            const size_t            insertedPlus42Point5Count = A_SIZE(insertedBytesForPlus42Point5);
            static const DataKind   insertedBytesForMinus42Point5[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - DataKindDoubleShortCountMinValue) &
                    DataKind::DoubleShortCountMask),
                StaticCast(DataKind, 0xC0), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            const size_t            insertedMinus42Point5Count = A_SIZE(insertedBytesForMinus42Point5);
            Double                  plus42Point5(42.5);
            Double                  minus42Point5(-42.5);

            result = extractValueAndCheck(*stuff, insertedBytesForMinus42Point5, insertedMinus42Point5Count, minus42Point5);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus42Point5, insertedPlus42Point5Count, plus42Point5);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingleDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyArrayMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // empty array message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyArray[] =
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
            const size_t            insertedEmptyArrayCount = A_SIZE(insertedBytesForEmptyArray);
            Array                   emptyArray;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyArray, insertedEmptyArrayCount, emptyArray);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMapMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // empty map message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyMap[] =
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
            const size_t            insertedEmptyMapCount = A_SIZE(insertedBytesForEmptyMap);
            Map                     emptyMap;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptyMap, insertedEmptyMapCount, emptyMap);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptySetMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // empty set message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptySet[] =
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
            const size_t            insertedEmptySetCount = A_SIZE(insertedBytesForEmptySet);
            Set                     emptySet;

            result = extractValueAndCheck(*stuff, insertedBytesForEmptySet, insertedEmptySetCount, emptySet);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptySetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneLogicalMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one logical message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneLogical[] =
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
            const size_t            insertedArrayOneLogicalCount = A_SIZE(insertedBytesForArrayOneLogical);
            Array                   arrayOneLogical;

            arrayOneLogical.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneLogical, insertedArrayOneLogicalCount, arrayOneLogical);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneIntegerMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one integer message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneInteger[] =
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
            const size_t            insertedArrayOneIntegerCount = A_SIZE(insertedBytesForArrayOneInteger);
            Array                   arrayOneInteger;

            arrayOneInteger.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneInteger, insertedArrayOneIntegerCount, arrayOneInteger);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneDoubleMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one double message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneDouble[] =
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
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t            insertedArrayOneDoubleCount = A_SIZE(insertedBytesForArrayOneDouble);
            Array                   arrayOneDouble;

            arrayOneDouble.addValue(std::make_shared<Double>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneDouble, insertedArrayOneDoubleCount, arrayOneDouble);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneStringMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one string message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneString[] =
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
            const size_t            insertedArrayOneStringCount = A_SIZE(insertedBytesForArrayOneString);
            Array                   arrayOneString;

            arrayOneString.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneString, insertedArrayOneStringCount, arrayOneString);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 114 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneBlobMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one blob message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneBlob[] =
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
            const size_t            insertedArrayOneBlobCount = A_SIZE(insertedBytesForArrayOneBlob);
            Array                   arrayOneBlob;

            arrayOneBlob.addValue(std::make_shared<Blob>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneBlob, insertedArrayOneBlobCount, arrayOneBlob);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 115 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneArrayMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one array message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneArray[] =
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
            const size_t            insertedArrayOneArrayCount = A_SIZE(insertedBytesForArrayOneArray);
            Array                   arrayOneArray;

            arrayOneArray.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneArray, insertedArrayOneArrayCount, arrayOneArray);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 116 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneMapMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one map message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneMap[] =
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
            const size_t            insertedArrayOneMapCount = A_SIZE(insertedBytesForArrayOneMap);
            Array                   arrayOneMap;

            arrayOneMap.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneMap, insertedArrayOneMapCount, arrayOneMap);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 117 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneSetMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with one set message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneSet[] =
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
            const size_t            insertedArrayOneSetCount = A_SIZE(insertedBytesForArrayOneSet);
            Array                   arrayOneSet;

            arrayOneSet.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneSet, insertedArrayOneSetCount, arrayOneSet);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 130 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoLogicalsMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two logicals message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoLogicals[] =
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
            const size_t            insertedArrayTwoLogicalsCount = A_SIZE(insertedBytesForArrayTwoLogicals);
            Array                   arrayTwoLogicals;

            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoLogicals, insertedArrayTwoLogicalsCount, arrayTwoLogicals);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoLogicalsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 131 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoIntegersMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two integers message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoIntegers[] =
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
            const size_t            insertedArrayTwoIntegersCount = A_SIZE(insertedBytesForArrayTwoIntegers);
            Array                   arrayTwoIntegers;

            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoIntegers, insertedArrayTwoIntegersCount, arrayTwoIntegers);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoIntegersMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 132 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoDoublesMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two doubles message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoDoubles[] =
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
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t            insertedArrayTwoDoublesCount = A_SIZE(insertedBytesForArrayTwoDoubles);
            Array                   arrayTwoDoubles;

            arrayTwoDoubles.addValue(std::make_shared<Double>());
            arrayTwoDoubles.addValue(std::make_shared<Double>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoDoubles, insertedArrayTwoDoublesCount, arrayTwoDoubles);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 133 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoStringsMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two strings message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoStrings[] =
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
            const size_t            insertedArrayTwoStringsCount = A_SIZE(insertedBytesForArrayTwoStrings);
            Array                   arrayTwoStrings;

            arrayTwoStrings.addValue(std::make_shared<String>());
            arrayTwoStrings.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoStrings, insertedArrayTwoStringsCount, arrayTwoStrings);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoStringsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 134 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoBlobsMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two blobs message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoBlobs[] =
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
            const size_t            insertedArrayTwoBlobsCount = A_SIZE(insertedBytesForArrayTwoBlobs);
            Array                   arrayTwoBlobs;

            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoBlobs, insertedArrayTwoBlobsCount, arrayTwoBlobs);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoBlobsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 135 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoArraysMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two arrays message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoArrays[] =
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
            const size_t            insertedArrayTwoArraysCount = A_SIZE(insertedBytesForArrayTwoArrays);
            Array                   arrayTwoArrays;

            arrayTwoArrays.addValue(std::make_shared<Array>());
            arrayTwoArrays.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoArrays, insertedArrayTwoArraysCount, arrayTwoArrays);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoArraysMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 136 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoMapsMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two maps message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoMaps[] =
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
            const size_t            insertedArrayTwoMapsCount = A_SIZE(insertedBytesForArrayTwoMaps);
            Array                   arrayTwoMaps;

            arrayTwoMaps.addValue(std::make_shared<Map>());
            arrayTwoMaps.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoMaps, insertedArrayTwoMapsCount, arrayTwoMaps);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoMapsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 137 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayTwoSetsMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with two sets message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoSets[] =
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
            const size_t            insertedArrayTwoSetsCount = A_SIZE(insertedBytesForArrayTwoSets);
            Array                   arrayTwoSets;

            arrayTwoSets.addValue(std::make_shared<Set>());
            arrayTwoSets.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoSets, insertedArrayTwoSetsCount, arrayTwoSets);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayTwoSetsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 138 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneArrayOneMapMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with array and map message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneArrayOneMap[] =
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
            const size_t            insertedArrayOneArrayOneMapCount = A_SIZE(insertedBytesForArrayOneArrayOneMap);
            Array                   arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(std::make_shared<Array>());
            arrayOneArrayOneMap.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneArrayOneMap, insertedArrayOneArrayOneMapCount, arrayOneArrayOneMap);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 139 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneMapOneSetMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with map and set message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneMapOneSet[] =
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
            const size_t            insertedArrayOneMapOneSetCount = A_SIZE(insertedBytesForArrayOneMapOneSet);
            Array                   arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(std::make_shared<Map>());
            arrayOneMapOneSet.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneMapOneSet, insertedArrayOneMapOneSetCount, arrayOneMapOneSet);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneMapOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 140 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayOneSetOneArrayMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with set and array message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneSetOneArray[] =
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
            const size_t            insertedArrayOneSetOneArrayCount = A_SIZE(insertedBytesForArrayOneSetOneArray);
            Array                   arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(std::make_shared<Set>());
            arrayOneSetOneArray.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneSetOneArray, insertedArrayOneSetOneArrayCount, arrayOneSetOneArray);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayOneSetOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 141 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayWithManyDoublesMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with many doubles message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const size_t     numValues = 43;
            static const DataKind   insertedBytesForArrayManyDoubles[] =
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
                StaticCast(DataKind, StaticCast(int, numValues) +
                    DataKindIntegerShortValueMinValue - 1),
                // Double
                DataKind::Double | DataKind::DoubleLongCount |
                  ((1 - 1) & DataKind::DoubleLongCountMask),
                StaticCast(DataKind, numValues),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 0
                StaticCast(DataKind, 0x3F), StaticCast(DataKind, 0xF0),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 1
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 2
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x08),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 3
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x10),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 4
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x14),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 5
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x18),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 6
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x1C),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 7
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x20),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 8
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x22),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 9
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x24),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 10
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x26),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 11
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x28),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 12
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x2A),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 13
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x2C),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 14
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x2E),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 15
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x30),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 16
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x31),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 17
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x32),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 18
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x33),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 19
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x34),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 20
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x35),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 21
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x36),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 22
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x37),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 23
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x38),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 24
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x39),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 25
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x3A),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 26
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x3B),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 27
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x3C),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 28
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x3D),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 29
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x3E),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 30
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x3F),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 31
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x40),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 32
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x40),
                StaticCast(DataKind, 0x80), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 33
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x41),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 34
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x41),
                StaticCast(DataKind, 0x80), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 35
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x42),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 36
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x42),
                StaticCast(DataKind, 0x80), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 37
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x43),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 38
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x43),
                StaticCast(DataKind, 0x80), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 39
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x44),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 40
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x44),
                StaticCast(DataKind, 0x80), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 41
                StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x45),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00),
                StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 42
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t            insertedArrayManyDoublesCount = A_SIZE(insertedBytesForArrayManyDoubles);
            Array                   arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = extractValueAndCheck(*stuff, insertedBytesForArrayManyDoubles, insertedArrayManyDoublesCount, arrayManyDoubles);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayWithManyDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 160 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalMapMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // logical map message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForLogicalMap[] =
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
            const size_t            insertedLogicalMapCount = A_SIZE(insertedBytesForLogicalMap);
            Map                     logicalMap;

            logicalMap.addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedBytesForLogicalMap, insertedLogicalMapCount, logicalMap);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 161 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerMapMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // integer map message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForIntegerMap[] =
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
            const size_t            insertedIntegerMapCount = A_SIZE(insertedBytesForIntegerMap);
            Map                     integerMap;

            integerMap.addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedBytesForIntegerMap, insertedIntegerMapCount, integerMap);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestIntegerMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 162 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringMapMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // string map message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForStringMap[] =
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
            const size_t            insertedStringMapCount = A_SIZE(insertedBytesForStringMap);
            Map                     stringMap;

            stringMap.addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedBytesForStringMap, insertedStringMapCount, stringMap);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 163 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalSetMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // logical set message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForLogicalSet[] =
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
            const size_t            insertedLogicalSetCount = A_SIZE(insertedBytesForLogicalSet);
            Set                     logicalSet;

            logicalSet.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedBytesForLogicalSet, insertedLogicalSetCount, logicalSet);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 164 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerSetMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // integer set message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForIntegerSet[] =
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
            const size_t            insertedIntegerSetCount = A_SIZE(insertedBytesForIntegerSet);
            Set                     integerSet;

            integerSet.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedBytesForIntegerSet, insertedIntegerSetCount, integerSet);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestIntegerSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 165 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringSetMessage
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // string set message
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForStringSet[] =
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
            const size_t            insertedStringSetCount = A_SIZE(insertedBytesForStringSet);
            Set                     stringSet;

            stringSet.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedBytesForStringSet, insertedStringSetCount, stringSet);
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 180 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMessageWithArrayWithRangeOfIntegers
    (const char *   NOT_USED_(launchPath),
     const int      NOT_USED_(argc),
     char * *       NOT_USED_(argv)) // array with range of integers
{
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (stuff)
        {
            static const size_t kNumValues = 18;
            Array               arrayWithIntegers;
            int64_t             posValue = 1;

            for (size_t ii = 0; kNumValues > ii; ++ii)
            {
                arrayWithIntegers.addValue(std::make_shared<Integer>(posValue));
                posValue *= 10;
            }
            for ( ; 0 < posValue; )
            {
                arrayWithIntegers.addValue(std::make_shared<Integer>(- posValue));
                posValue /= 10;
            }
            if (arrayWithIntegers.size() == ((2 * kNumValues) + 1))
            {
                // Insert the array into the message.
                stuff->open(true);
                stuff->setValue(arrayWithIntegers);
                stuff->close();
                // Extract objects from the message and compare with the expected contents.
                SpValue extractedValue{stuff->getValue(true)};

                ODL_P1("extractedValue <- ", extractedValue.get()); //####
                if (nullptr == extractedValue)
                {
                    ODL_LOG("(nullptr == extractedValue)"); //####
                }
                else
                {
                    const Flaw *    asFlaw = extractedValue->asFlaw();

                    if (asFlaw)
                    {
                        ODL_LOG("(asFlaw)"); //####
                        ODL_LOG(asFlaw->getDescription().c_str()); //####
                    }
                    else if (stuff->readAtEnd())
                    {
                        if (extractedValue->deeplyEqualTo(arrayWithIntegers))
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (extractedValue->deeplyEqualTo(arrayWithIntegers))"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (stuff->readAtEnd())"); //####
                    }
                }
                if (0 == result)
                {
                    // Compare the bytes with the expected minimal bytes.
                    static const DataKind   expectedBytesForArrayWithIntegers[] =
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
                        StaticCast(DataKind, StaticCast(int, (2 * kNumValues) + 1) +
                                              DataKindIntegerShortValueMinValue - 1),
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerShortValue |
                          0x01, // 1
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerShortValue |
                          0x0A, // 10
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((1 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x64), // 100
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((2 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x03), StaticCast(DataKind, 0xE8), // 1000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((2 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x27), StaticCast(DataKind, 0x10), // 10000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((3 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x01), StaticCast(DataKind, 0x86),
                        StaticCast(DataKind, 0xA0), // 100000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((3 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x0F), StaticCast(DataKind, 0x42),
                        StaticCast(DataKind, 0x40), // 1000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((4 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x98),
                        StaticCast(DataKind, 0x96), StaticCast(DataKind, 0x80), // 10000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((4 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x05), StaticCast(DataKind, 0xF5),
                        StaticCast(DataKind, 0xE1), StaticCast(DataKind, 0x00), // 100000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((4 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x3B), StaticCast(DataKind, 0x9A),
                        StaticCast(DataKind, 0xCA), StaticCast(DataKind, 0x00), // 1000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((5 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x02), StaticCast(DataKind, 0x54),
                        StaticCast(DataKind, 0x0B), StaticCast(DataKind, 0xE4),
                        StaticCast(DataKind, 0x00), // 10000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((5 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x17), StaticCast(DataKind, 0x48),
                        StaticCast(DataKind, 0x76), StaticCast(DataKind, 0xE8),
                        StaticCast(DataKind, 0x00), // 10000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((6 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x00), StaticCast(DataKind, 0xE8),
                        StaticCast(DataKind, 0xD4), StaticCast(DataKind, 0xA5),
                        StaticCast(DataKind, 0x10), StaticCast(DataKind, 0x00), // 100000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((6 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x09), StaticCast(DataKind, 0x18),
                        StaticCast(DataKind, 0x4E), StaticCast(DataKind, 0x72),
                        StaticCast(DataKind, 0xA0), StaticCast(DataKind, 0x00), // 1000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((6 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x5A), StaticCast(DataKind, 0xF3),
                        StaticCast(DataKind, 0x10), StaticCast(DataKind, 0x7A),
                        StaticCast(DataKind, 0x40), StaticCast(DataKind, 0x00), // 10000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((7 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x03), StaticCast(DataKind, 0x8D),
                        StaticCast(DataKind, 0x7E), StaticCast(DataKind, 0xA4),
                        StaticCast(DataKind, 0xC6), StaticCast(DataKind, 0x80),
                        StaticCast(DataKind, 0x00), // 100000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((7 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x23), StaticCast(DataKind, 0x86),
                        StaticCast(DataKind, 0xF2), StaticCast(DataKind, 0x6F),
                        StaticCast(DataKind, 0xC1), StaticCast(DataKind, 0x00),
                        StaticCast(DataKind, 0x00), // 10000000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((8 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x01), StaticCast(DataKind, 0x63),
                        StaticCast(DataKind, 0x45), StaticCast(DataKind, 0x78),
                        StaticCast(DataKind, 0x5D), StaticCast(DataKind, 0x8A),
                        StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // 100000000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((8 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xF2), StaticCast(DataKind, 0x1F),
                        StaticCast(DataKind, 0x49), StaticCast(DataKind, 0x4C),
                        StaticCast(DataKind, 0x58), StaticCast(DataKind, 0x9C),
                        StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // -1000000000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((8 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFE), StaticCast(DataKind, 0x9C),
                        StaticCast(DataKind, 0xBA), StaticCast(DataKind, 0x87),
                        StaticCast(DataKind, 0xA2), StaticCast(DataKind, 0x76),
                        StaticCast(DataKind, 0x00), StaticCast(DataKind, 0x00), // -100000000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((7 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xDC), StaticCast(DataKind, 0x79),
                        StaticCast(DataKind, 0x0D), StaticCast(DataKind, 0x90),
                        StaticCast(DataKind, 0x3F), StaticCast(DataKind, 0x00),
                        StaticCast(DataKind, 0x00), // -10000000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((7 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFC), StaticCast(DataKind, 0x72),
                        StaticCast(DataKind, 0x81), StaticCast(DataKind, 0x5B),
                        StaticCast(DataKind, 0x39), StaticCast(DataKind, 0x80),
                        StaticCast(DataKind, 0x00), // -1000000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((6 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xA5), StaticCast(DataKind, 0x0C),
                        StaticCast(DataKind, 0xEF), StaticCast(DataKind, 0x85),
                        StaticCast(DataKind, 0xC0), StaticCast(DataKind, 0x00), // -100000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((6 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xF6), StaticCast(DataKind, 0xE7),
                        StaticCast(DataKind, 0xB1), StaticCast(DataKind, 0x8D),
                        StaticCast(DataKind, 0x60), StaticCast(DataKind, 0x00), // -10000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((6 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFF), StaticCast(DataKind, 0x17),
                        StaticCast(DataKind, 0x2B), StaticCast(DataKind, 0x5A),
                        StaticCast(DataKind, 0xF0), StaticCast(DataKind, 0x00), // -1000000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((5 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xE8), StaticCast(DataKind, 0xB7),
                        StaticCast(DataKind, 0x89), StaticCast(DataKind, 0x18),
                        StaticCast(DataKind, 0x00), // -100000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((5 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFD), StaticCast(DataKind, 0xAB),
                        StaticCast(DataKind, 0xF4), StaticCast(DataKind, 0x1C),
                        StaticCast(DataKind, 0x00), // -10000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((4 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xC4), StaticCast(DataKind, 0x65),
                        StaticCast(DataKind, 0x36), StaticCast(DataKind, 0x00), // -1000000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((4 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFA), StaticCast(DataKind, 0x0A),
                        StaticCast(DataKind, 0x1F), StaticCast(DataKind, 0x00), // -100000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((4 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFF), StaticCast(DataKind, 0x67),
                        StaticCast(DataKind, 0x69), StaticCast(DataKind, 0x80), // -10000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((3 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xF0), StaticCast(DataKind, 0xBD),
                        StaticCast(DataKind, 0xC0), // -1000000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((3 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFE), StaticCast(DataKind, 0x79),
                        StaticCast(DataKind, 0x60), // -100000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((2 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xD8), StaticCast(DataKind, 0xF0), // -10000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((2 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0xFC), StaticCast(DataKind, 0x18), // -1000
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerLongValue |
                          ((1 - 1) & DataKind::IntegerLongValueCountMask),
                        StaticCast(DataKind, 0x9C), // -100
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerShortValue |
                          (0xF6 & DataKind::IntegerShortValueValueMask), // -10
                        // Signed Integer
                        DataKind::Integer | DataKind::IntegerShortValue |
                          (0xFF & DataKind::IntegerShortValueValueMask), // -1
                        // End of Array
                        DataKind::Other | DataKind::OtherContainerEnd |
                          DataKind::OtherContainerTypeArray |
                          DataKind::OtherContainerNonEmptyValue,
                        // End of Message
                        DataKind::EndOfMessageValue |
                          DataKind::OtherMessageNonEmptyValue |
                          DataKind::OtherMessageExpectedOtherValue
                    };
                    const size_t            expectedBytesForArrayWithIntegersCount = A_SIZE(expectedBytesForArrayWithIntegers);
                    auto                    contents{stuff->getBytes()};
                    size_t                  length = contents.size();

                    ODL_PACKET("contents", contents.data(), length); //####
                    ODL_PACKET("expected", expectedBytesForArrayWithIntegers, //####
                               expectedBytesForArrayWithIntegersCount); //####
                    if (expectedBytesForArrayWithIntegersCount == length)
                    {
                        result = StaticCast(int, CompareBytes(expectedBytesForArrayWithIntegers, contents.data(),
                                                               expectedBytesForArrayWithIntegersCount));
                    }
                    else
                    {
                        ODL_LOG("! (expectedBytesForArrayWithIntegersCount == length)"); //####
                        result = 1;
                    }
                }
            }
            else
            {
                ODL_LOG("! (arrayWithIntegers.size() == ((2 * kNumValues) + 1))"); //####
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
    ODL_EXIT_I(result); //####
    return result;
} // doTestMessageWithArrayWithRangeOfIntegers

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for unit tests of the %nImO common classes.

 The first argument is the test number, the second argument is the name of the channel to be used
 with the test, the optional third argument is the machine to connect to and the optional fourth
 argument is the port number to be used. Output depends on the test being run.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the unit tests.
 @return @c 0 on a successful test and @c 1 on failure. */
int
main
    (int    argc,
     char * *   argv)
{
    std::string progName{*argv};

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
        Initialize(progName, nImO::ApplicationRole::Test);
        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestSmallIntegerMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestSmallBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestSingleDoubleMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestArrayOneLogicalMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestArrayTwoLogicalsMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestLogicalMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 161 :
                        result = doTestIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 162 :
                        result = doTestStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 163 :
                        result = doTestLogicalSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 164 :
                        result = doTestIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 165 :
                        result = doTestStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 180 :
                        result = doTestMessageWithArrayWithRangeOfIntegers(*argv, argc - 1, argv + 2);
                        break;

                    default :
                        break;

                }
                if (result)
                {
                    ODL_I1("%%%%%%% unit test failure = ", result); //####
                }
            }
            else
            {
                ODL_LOG("! (ConvertToInt64(argv[1], selector) && (0 < selector))"); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < --argc)"); //####
        }
        nImO::Terminate();
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // main

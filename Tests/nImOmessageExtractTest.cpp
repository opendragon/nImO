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

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOblob.h>
#include <BasicTypes/nImOdate.h>
#include <BasicTypes/nImOdouble.h>
#include <BasicTypes/nImOflaw.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <BasicTypes/nImOtime.h>
#include <Containers/nImOarray.h>
#include <Containers/nImObufferChunk.h>
#include <Containers/nImOmap.h>
#include <Containers/nImOmessage.h>
#include <Containers/nImOset.h>
#include <Containers/nImOstringBuffer.h>
#include <Contexts/nImOtestContext.h>

#include <string>

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
    ODL_I1(signal); //####
    auto    message{"exiting due to signal "s + std::to_string(signal) + " = "s + NameOfSignal(signal)};

    NIMO_UNUSED_VAR_(message);
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
    (Message &      stuff,
     CPtr(DataKind) insertedContents,
     const size_t   insertedSize,
     const Value &  expectedValue)
{
    ODL_ENTER(); //####
    ODL_P3(&stuff, insertedContents, &expectedValue); //####
    ODL_I1(insertedSize); //####
    ODL_PACKET("inserted", insertedContents, insertedSize); //####
    int result{1};

    // First, the 'this-should-work' test:
    stuff.open(false);
    stuff.appendBytes(insertedContents, insertedSize);
    auto    extractedValue{stuff.getValue()};

    ODL_P1(extractedValue.get()); //####
    stuff.close();
    if (extractedValue)
    {
        auto    asFlaw{extractedValue->asFlaw()};

        if (nullptr == asFlaw)
        {
            if (stuff.readAtEnd())
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
        else
        {
            ODL_LOG("! (nullptr == asFlaw)"); //####
            ODL_LOG(asFlaw->getDescription().c_str()); //####
        }
    }
    else
    {
        ODL_LOG("! (extractedValue)"); //####
    }
    if (0 == result)
    {
        // And now, let's make sure that 'short' messages are handled correctly:
        for (size_t ii = 1, shortenedSize = (insertedSize - 1); (0 == result) && (shortenedSize > ii); ++ii)
        {
            stuff.open(false);
            stuff.appendBytes(insertedContents, ii);
            extractedValue = stuff.getValue();
            ODL_P1(extractedValue.get()); //####
            stuff.close();
            if (extractedValue)
            {
                auto    asFlaw{extractedValue->asFlaw()};

                if (nullptr == asFlaw)
                {
                    ODL_LOG("(nullptr == asFlaw)");
                    ODL_I1(ii); //####
                    result = 1;
                }
                else
                {
                    ODL_LOG(asFlaw->getDescription().c_str()); //####
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
doTestExtractEmptyMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};
            ODL_PACKET("bytesToInsert", bytesToInsert, insertionCount); //####
            auto                extractedValue{stuff->getValue()};

            ODL_P1(extractedValue.get()); //####
            if (stuff->readAtEnd())
            {
                if (extractedValue)
                {
                    auto    asFlaw{extractedValue->asFlaw()};

                    if (nullptr != asFlaw)
                    {
                        ODL_LOG(asFlaw->getDescription().c_str()); //####
                        stuff->open(true);
                        stuff->close();
                        stuff->open(false);
                        stuff->appendBytes(bytesToInsert, insertionCount);
                        extractedValue = stuff->getValue();
                        ODL_P1(extractedValue.get()); //####
                        stuff->close();
                        if (stuff->readAtEnd())
                        {
                            if (extractedValue)
                            {
                                asFlaw = extractedValue->asFlaw();
                                if (nullptr == asFlaw)
                                {
                                    ODL_LOG("! (nullptr != asFlaw)"); //####
                                }
                                else
                                {
                                    ODL_LOG(asFlaw->getDescription().c_str()); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("(nullptr == extractedValue)"); //####
                                result = 0;
                            }
                        }
                        stuff->reset();
                    }
                }
                else
                {
                    ODL_LOG("Null Value read"); //####
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
} // doTestExtractEmptyMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractLogicalMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForTrue[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalTrueValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedTrueCount{numElementsInArray(insertedBytesForTrue)};
            static const DataKind   insertedBytesForFalse[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedFalseCount{numElementsInArray(insertedBytesForFalse)};
            Logical                 falseValue{false};
            Logical                 trueValue{true};

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
} // doTestExtractLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractTinyIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinus12[]
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
            constexpr size_t        insertedMinus12Count{numElementsInArray(insertedBytesForMinus12)};
            static const DataKind   insertedBytesForZero[]
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
            constexpr size_t        insertedZeroCount{numElementsInArray(insertedBytesForZero)};
            static const DataKind   insertedBytesForPlus12[]
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
            constexpr size_t        insertedPlus12Count{numElementsInArray(insertedBytesForPlus12)};
            Integer                 minus12Value{-12};
            Integer                 zeroValue{0};
            Integer                 plus12Value{12};

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
} // doTestExtractTinyIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractSmallIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinus144[]
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
            constexpr size_t        insertedMinus144Count{numElementsInArray(insertedBytesForMinus144)};
            static const DataKind   insertedBytesForPlus144[]
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
            constexpr size_t        insertedPlus144Count{numElementsInArray(insertedBytesForPlus144)};
            Integer                 minus144Value{-144};
            Integer                 plus144Value{144};

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
} // doTestExtractSmallIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractMediumIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinus1234567[]
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
            constexpr size_t        insertedMinus1234567Count{numElementsInArray(insertedBytesForMinus1234567)};
            static const DataKind   insertedBytesForPlus1234567[]
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
            constexpr size_t        insertedPlus1234567Count{numElementsInArray(insertedBytesForPlus1234567)};
            Integer                 minus1234567Value{-1234567};
            Integer                 plus1234567Value{1234567};

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
} // doTestExtractMediumIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractBigIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMinusBigNumber[]
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
            constexpr size_t        insertedMinusBigNumberCount{numElementsInArray(insertedBytesForMinusBigNumber)};
            static const DataKind   insertedBytesForPlusBigNumber[]
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
            constexpr size_t        insertedPlusBigNumberCount{numElementsInArray(insertedBytesForPlusBigNumber)};
            Integer                 minusBigNumberValue{-20015998343868};
            Integer                 plusBigNumberValue{20015998343868};

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
} // doTestExtractBigIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 007 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractEmptyStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyString[]
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
            constexpr size_t        insertedEmptyStringCount{numElementsInArray(insertedBytesForEmptyString)};
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
} // doTestExtractEmptyStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 008 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractShortStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForShortString[]
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
            constexpr size_t        insertedShortStringCount{numElementsInArray(insertedBytesForShortString)};
            String                  shortStringValue{"abcdef"};

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
} // doTestExtractShortStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 009 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractMediumStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMediumString[]
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
            constexpr size_t        insertedMediumStringCount{numElementsInArray(insertedBytesForMediumString)};
            String                  mediumStringValue{"abcdefabcdefabcdefabcdefabcdefabcdefabcdef"};

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
} // doTestExtractMediumStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 010 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractEmptyBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyBlob[]
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
            constexpr size_t        insertedEmptyBlobCount{numElementsInArray(insertedBytesForEmptyBlob)};
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
} // doTestExtractEmptyBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 011 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractSmallBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForSmallBlob[]
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
            constexpr size_t        insertedSmallBlobCount{numElementsInArray(insertedBytesForSmallBlob)};
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            constexpr size_t        actualDataCount{numElementsInArray(actualData)};
            Blob                    smallBlobValue{actualData, actualDataCount};

            result = extractValueAndCheck(*stuff, insertedBytesForSmallBlob, insertedSmallBlobCount, smallBlobValue);
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
} // doTestExtractSmallBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 012 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractMediumBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForMediumBlob[]
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
            constexpr size_t        insertedMediumBlobCount{numElementsInArray(insertedBytesForMediumBlob)};
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            constexpr size_t        actualDataCount{numElementsInArray(actualData)};
            Blob                    mediumBlobValue{actualData, actualDataCount};

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
} // doTestExtractMediumBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 013 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractSingleDoubleMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForPlus42Point5[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - kDataKindDoubleShortCountMinValue) &
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
            constexpr size_t        insertedPlus42Point5Count{numElementsInArray(insertedBytesForPlus42Point5)};
            static const DataKind   insertedBytesForMinus42Point5[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - kDataKindDoubleShortCountMinValue) &
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
            constexpr size_t        insertedMinus42Point5Count{numElementsInArray(insertedBytesForMinus42Point5)};
            Double                  plus42Point5Value{42.5};
            Double                  minus42Point5Value{-42.5};

            result = extractValueAndCheck(*stuff, insertedBytesForMinus42Point5, insertedMinus42Point5Count, minus42Point5Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedBytesForPlus42Point5, insertedPlus42Point5Count, plus42Point5Value);
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
} // doTestExtractSingleDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 014 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractAddressMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForAddress[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0x12),
                    StaticCast(DataKind, 0x34),
                    StaticCast(DataKind, 0x56),
                    StaticCast(DataKind, 0x78),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedAddressCount{numElementsInArray(insertedBytesForAddress)};
            Address                 addressValue{0x12345678};

            result = extractValueAndCheck(*stuff, insertedBytesForAddress, insertedAddressCount, addressValue);
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
} // doTestExtractAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 015 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractDateMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Date::DatePieces   aDate{12, 11, 10};
            static const DataKind           insertedBytesForDate[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(aDate)),
                    StaticCast(DataKind, SecondDateByte(aDate)),
                    StaticCast(DataKind, ThirdDateByte(aDate)),
                    StaticCast(DataKind, FourthDateByte(aDate)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                insertedDateCount{numElementsInArray(insertedBytesForDate)};
            Date                            dateValue{MakeDateValue(aDate)};

            result = extractValueAndCheck(*stuff, insertedBytesForDate, insertedDateCount, dateValue);
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
} // doTestExtractDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 016 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractTimeMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Time::TimePieces   aTime{12, 11, 10, 9};
            static const DataKind           insertedBytesForTime[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Time
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(aTime)),
                    StaticCast(DataKind, SecondTimeByte(aTime)),
                    StaticCast(DataKind, ThirdTimeByte(aTime)),
                    StaticCast(DataKind, FourthTimeByte(aTime)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                insertedTimeCount{numElementsInArray(insertedBytesForTime)};
            Time                            timeValue{MakeTimeValue(aTime)};

            result = extractValueAndCheck(*stuff, insertedBytesForTime, insertedTimeCount, timeValue);
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
} // doTestExtractTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractEmptyArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyArray[]
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
            constexpr size_t        insertedEmptyArrayCount{numElementsInArray(insertedBytesForEmptyArray)};
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
} // doTestExtractEmptyArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractEmptyMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptyMap[]
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
            constexpr size_t        insertedEmptyMapCount{numElementsInArray(insertedBytesForEmptyMap)};
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
} // doTestExtractEmptyMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractEmptySetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForEmptySet[]
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
            constexpr size_t        insertedEmptySetCount{numElementsInArray(insertedBytesForEmptySet)};
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
} // doTestExtractEmptySetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneLogicalMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneLogical[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedArrayOneLogicalCount{numElementsInArray(insertedBytesForArrayOneLogical)};
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
} // doTestExtractArrayOneLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneInteger[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneIntegerCount{numElementsInArray(insertedBytesForArrayOneInteger)};
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
} // doTestExtractArrayOneIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneDoubleMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneDouble[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((1 - kDataKindDoubleShortCountMinValue) &
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
            constexpr size_t        insertedArrayOneDoubleCount{numElementsInArray(insertedBytesForArrayOneDouble)};
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
} // doTestExtractArrayOneDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneString[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneStringCount{numElementsInArray(insertedBytesForArrayOneString)};
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
} // doTestExtractArrayOneStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 114 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneBlob[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneBlobCount{numElementsInArray(insertedBytesForArrayOneBlob)};
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
} // doTestExtractArrayOneBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 115 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneArray[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneArrayCount{numElementsInArray(insertedBytesForArrayOneArray)};
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
} // doTestExtractArrayOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 116 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneMap[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneMapCount{numElementsInArray(insertedBytesForArrayOneMap)};
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
} // doTestExtractArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 117 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneSet[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneSetCount{numElementsInArray(insertedBytesForArrayOneSet)};
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
} // doTestExtractArrayOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 118 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithOneAddressMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneAddress[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0x12),
                    StaticCast(DataKind, 0x34),
                    StaticCast(DataKind, 0x56),
                    StaticCast(DataKind, 0x78),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedArrayOneAddressCount{numElementsInArray(insertedBytesForArrayOneAddress)};
            Array                   arrayOneAddress;

            arrayOneAddress.addValue(std::make_shared<Address>(0x12345678));
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneAddress, insertedArrayOneAddressCount, arrayOneAddress);
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
} // doTestExtractArrayWithOneAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 119 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithOneDateMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Date::DatePieces   aDate{12, 11, 10};
            static const DataKind           insertedBytesForArrayOneDate[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(aDate)),
                    StaticCast(DataKind, SecondDateByte(aDate)),
                    StaticCast(DataKind, ThirdDateByte(aDate)),
                    StaticCast(DataKind, FourthDateByte(aDate)),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                insertedArrayOneDateCount{numElementsInArray(insertedBytesForArrayOneDate)};
            Array                           arrayOneDate;

            arrayOneDate.addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneDate, insertedArrayOneDateCount, arrayOneDate);
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
} // doTestExtractArrayWithOneDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 120 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithOneTimeMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Time::TimePieces   aTime{12, 11, 10, 9};
            static const DataKind           insertedBytesForArrayOneTime[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Time
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(aTime)),
                    StaticCast(DataKind, SecondTimeByte(aTime)),
                    StaticCast(DataKind, ThirdTimeByte(aTime)),
                    StaticCast(DataKind, FourthTimeByte(aTime)),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                insertedArrayOneTimeCount{numElementsInArray(insertedBytesForArrayOneTime)};
            Array                           arrayOneTime;

            arrayOneTime.addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneTime, insertedArrayOneTimeCount, arrayOneTime);
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
} // doTestExtractArrayWithOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 130 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoLogicalsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoLogicals[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedArrayTwoLogicalsCount{numElementsInArray(insertedBytesForArrayTwoLogicals)};
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
} // doTestExtractArrayTwoLogicalsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 131 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoIntegersMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoIntegers[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayTwoIntegersCount{numElementsInArray(insertedBytesForArrayTwoIntegers)};
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
} // doTestExtractArrayTwoIntegersMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 132 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoDoublesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoDoubles[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((2 - kDataKindDoubleShortCountMinValue) &
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
            constexpr size_t        insertedArrayTwoDoublesCount{numElementsInArray(insertedBytesForArrayTwoDoubles)};
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
} // doTestExtractArrayTwoDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 133 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoStringsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoStrings[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayTwoStringsCount{numElementsInArray(insertedBytesForArrayTwoStrings)};
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
} // doTestExtractArrayTwoStringsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 134 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoBlobsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoBlobs[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayTwoBlobsCount{numElementsInArray(insertedBytesForArrayTwoBlobs)};
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
} // doTestExtractArrayTwoBlobsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 135 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoArraysMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoArrays[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayTwoArraysCount{numElementsInArray(insertedBytesForArrayTwoArrays)};
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
} // doTestExtractArrayTwoArraysMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 136 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoMapsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoMaps[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayTwoMapsCount{numElementsInArray(insertedBytesForArrayTwoMaps)};
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
} // doTestExtractArrayTwoMapsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 137 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayTwoSetsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoSets[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayTwoSetsCount{numElementsInArray(insertedBytesForArrayTwoSets)};
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
} // doTestExtractArrayTwoSetsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 138 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneArrayOneMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneArrayOneMap[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneArrayOneMapCount{numElementsInArray(insertedBytesForArrayOneArrayOneMap)};
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
} // doTestExtractArrayOneArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 139 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneMapOneSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneMapOneSet[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneMapOneSetCount{numElementsInArray(insertedBytesForArrayOneMapOneSet)};
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
} // doTestExtractArrayOneMapOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 140 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayOneSetOneArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayOneSetOneArray[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedArrayOneSetOneArrayCount{numElementsInArray(insertedBytesForArrayOneSetOneArray)};
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
} // doTestExtractArrayOneSetOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 141 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithManyDoublesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            constexpr size_t        numValues{43};
            static const DataKind   insertedBytesForArrayManyDoubles[]
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
                    kDataKindIntegerShortValueMinValue - 1),
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
            constexpr size_t        insertedArrayManyDoublesCount{numElementsInArray(insertedBytesForArrayManyDoubles)};
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
} // doTestExtractArrayWithManyDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 142 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithTwoAddressesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForArrayTwoAddresses[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0x12),
                    StaticCast(DataKind, 0x34),
                    StaticCast(DataKind, 0x56),
                    StaticCast(DataKind, 0x78),
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0x34),
                    StaticCast(DataKind, 0x56),
                    StaticCast(DataKind, 0x78),
                    StaticCast(DataKind, 0xAB),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedArrayTwoAddressesCount{numElementsInArray(insertedBytesForArrayTwoAddresses)};
            Array                   arrayTwoAddresses;

            arrayTwoAddresses.addValue(std::make_shared<Address>(0x12345678));
            arrayTwoAddresses.addValue(std::make_shared<Address>(0x345678AB));
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoAddresses, insertedArrayTwoAddressesCount, arrayTwoAddresses);
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
} // doTestExtractArrayWithTwoAddressesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 143 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithTwoDatesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Date::DatePieces   aDate1{12, 11, 10};
            static const Date::DatePieces   aDate2{11, 10, 9};
            static const DataKind           insertedBytesForArrayTwoDates[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(aDate1)),
                    StaticCast(DataKind, SecondDateByte(aDate1)),
                    StaticCast(DataKind, ThirdDateByte(aDate1)),
                    StaticCast(DataKind, FourthDateByte(aDate1)),
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(aDate2)),
                    StaticCast(DataKind, SecondDateByte(aDate2)),
                    StaticCast(DataKind, ThirdDateByte(aDate2)),
                    StaticCast(DataKind, FourthDateByte(aDate2)),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedArrayTwoDatesCount{numElementsInArray(insertedBytesForArrayTwoDates)};
            Array                   arrayTwoDates;

            arrayTwoDates.addValue(std::make_shared<Date>(MakeDateValue(aDate1)));
            arrayTwoDates.addValue(std::make_shared<Date>(MakeDateValue(aDate2)));
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoDates, insertedArrayTwoDatesCount, arrayTwoDates);
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
} // doTestExtractArrayWithTwoDatesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 144 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithTwoTimesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Time::TimePieces   aTime1{12, 11, 10, 9};
            static const Time::TimePieces   aTime2{11, 10, 9, 8};
            static const DataKind           insertedBytesForArrayTwoTimes[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Time
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(aTime1)),
                    StaticCast(DataKind, SecondTimeByte(aTime1)),
                    StaticCast(DataKind, ThirdTimeByte(aTime1)),
                    StaticCast(DataKind, FourthTimeByte(aTime1)),
                // Time
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(aTime2)),
                    StaticCast(DataKind, SecondTimeByte(aTime2)),
                    StaticCast(DataKind, ThirdTimeByte(aTime2)),
                    StaticCast(DataKind, FourthTimeByte(aTime2)),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedArrayTwoTimesCount{numElementsInArray(insertedBytesForArrayTwoTimes)};
            Array                   arrayTwoTimes;

            arrayTwoTimes.addValue(std::make_shared<Time>(MakeTimeValue(aTime1)));
            arrayTwoTimes.addValue(std::make_shared<Time>(MakeTimeValue(aTime2)));
            result = extractValueAndCheck(*stuff, insertedBytesForArrayTwoTimes, insertedArrayTwoTimesCount, arrayTwoTimes);
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
} // doTestExtractArrayWithTwoTimesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 145 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractArrayWithOneDateOneTimeMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Date::DatePieces   aDate{12, 11, 10};
            static const Time::TimePieces   aTime{12, 11, 10, 9};
            static const DataKind           insertedBytesForArrayOneDateOneTime[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(aDate)),
                    StaticCast(DataKind, SecondDateByte(aDate)),
                    StaticCast(DataKind, ThirdDateByte(aDate)),
                    StaticCast(DataKind, FourthDateByte(aDate)),
                // Time
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(aTime)),
                    StaticCast(DataKind, SecondTimeByte(aTime)),
                    StaticCast(DataKind, ThirdTimeByte(aTime)),
                    StaticCast(DataKind, FourthTimeByte(aTime)),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                insertedArrayOneDateOneTimeCount{numElementsInArray(insertedBytesForArrayOneDateOneTime)};
            Array                           arrayOneDateOneTime;

            arrayOneDateOneTime.addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            arrayOneDateOneTime.addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = extractValueAndCheck(*stuff, insertedBytesForArrayOneDateOneTime, insertedArrayOneDateOneTimeCount, arrayOneDateOneTime);
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
} // doTestExtractArrayWithOneDateOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 160 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractLogicalMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForLogicalMap[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
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
            constexpr size_t        insertedLogicalMapCount{numElementsInArray(insertedBytesForLogicalMap)};
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
} // doTestExtractLogicalMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 161 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractIntegerMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForIntegerMap[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedIntegerMapCount{numElementsInArray(insertedBytesForIntegerMap)};
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
} // doTestExtractIntegerMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 162 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractStringMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForStringMap[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedStringMapCount{numElementsInArray(insertedBytesForStringMap)};
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
} // doTestExtractStringMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 163 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractLogicalSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForLogicalSet[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedLogicalSetCount{numElementsInArray(insertedBytesForLogicalSet)};
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
} // doTestExtractLogicalSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 164 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractIntegerSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForIntegerSet[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedIntegerSetCount{numElementsInArray(insertedBytesForIntegerSet)};
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
} // doTestExtractIntegerSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 165 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractStdStringSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForStdStringSet[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t        insertedStdStringSetCount{numElementsInArray(insertedBytesForStdStringSet)};
            Set                     stringSet;

            stringSet.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedBytesForStdStringSet, insertedStdStringSetCount, stringSet);
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
} // doTestExtractStdStringSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 166 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractAddressMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForAddressMap[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0),
                    StaticCast(DataKind, 0),
                    StaticCast(DataKind, 0),
                    StaticCast(DataKind, 0),
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
            constexpr size_t        insertedAddressMapCount{numElementsInArray(insertedBytesForAddressMap)};
            Map                     addressMap;

            addressMap.addValue(std::make_shared<Address>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedBytesForAddressMap, insertedAddressMapCount, addressMap);
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
} // doTestExtractAddressMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 167 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractAddressSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const DataKind   insertedBytesForAddressSet[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0),
                    StaticCast(DataKind, 0),
                    StaticCast(DataKind, 0),
                    StaticCast(DataKind, 0),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        insertedAddressSetCount{numElementsInArray(insertedBytesForAddressSet)};
            Set                     addressSet;

            addressSet.addValue(std::make_shared<Address>());
            result = extractValueAndCheck(*stuff, insertedBytesForAddressSet, insertedAddressSetCount, addressSet);
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
} // doTestExtractAddressSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 168 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractDateMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Date::DatePieces   aDate{12, 11, 10};
            static const DataKind           insertedBytesForDateMap[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(aDate)),
                    StaticCast(DataKind, SecondDateByte(aDate)),
                    StaticCast(DataKind, ThirdDateByte(aDate)),
                    StaticCast(DataKind, FourthDateByte(aDate)),
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
            constexpr size_t        insertedDateMapCount{numElementsInArray(insertedBytesForDateMap)};
            Map                     dateMap;

            dateMap.addValue(std::make_shared<Date>(MakeDateValue(aDate)), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedBytesForDateMap, insertedDateMapCount, dateMap);
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
} // doTestExtractDateMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 169 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractDateSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Date::DatePieces   aDate{12, 11, 10};
            static const DataKind           insertedBytesForDateSet[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(aDate)),
                    StaticCast(DataKind, SecondDateByte(aDate)),
                    StaticCast(DataKind, ThirdDateByte(aDate)),
                    StaticCast(DataKind, FourthDateByte(aDate)),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                insertedDateSetCount{numElementsInArray(insertedBytesForDateSet)};
            Set                             dateSet;

            dateSet.addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = extractValueAndCheck(*stuff, insertedBytesForDateSet, insertedDateSetCount, dateSet);
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
} // doTestExtractDateSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 170 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractTimeMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Time::TimePieces   aTime{12, 11, 10, 9};
            static const DataKind           insertedBytesForTimeMap[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Time
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(aTime)),
                    StaticCast(DataKind, SecondTimeByte(aTime)),
                    StaticCast(DataKind, ThirdTimeByte(aTime)),
                    StaticCast(DataKind, FourthTimeByte(aTime)),
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
            constexpr size_t                insertedTimeMapCount{numElementsInArray(insertedBytesForTimeMap)};
            Map                             timeMap;

            timeMap.addValue(std::make_shared<Time>(MakeTimeValue(aTime)), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedBytesForTimeMap, insertedTimeMapCount, timeMap);
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
} // doTestExtractTimeMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 171 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractTimeSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            static const Time::TimePieces   aTime{12, 11, 10, 9};
            static const DataKind           insertedBytesForTimeSet[]
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
                  ((1 + kDataKindIntegerShortValueMinValue - 1) &
                    DataKind::IntegerShortValueValueMask),
                // Time
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(aTime)),
                    StaticCast(DataKind, SecondTimeByte(aTime)),
                    StaticCast(DataKind, ThirdTimeByte(aTime)),
                    StaticCast(DataKind, FourthTimeByte(aTime)),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                insertedTimeSetCount{numElementsInArray(insertedBytesForTimeSet)};
            Set                             timeSet;

            timeSet.addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = extractValueAndCheck(*stuff, insertedBytesForTimeSet, insertedTimeSetCount, timeSet);
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
} // doTestExtractTimeSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 180 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestExtractMessageWithArrayWithRangeOfIntegers
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1(launchPath); //####
    //ODL_I1(argc); //####
    //ODL_P1(argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (stuff)
        {
            constexpr size_t    kNumValues{18};
            auto                arrayWithIntegers{std::make_shared<Array>()};
            int64_t             posValue{1};

            for (size_t ii = 0; kNumValues > ii; ++ii)
            {
                arrayWithIntegers->addValue(std::make_shared<Integer>(posValue));
                posValue *= 10;
            }
            for ( ; 0 < posValue; )
            {
                arrayWithIntegers->addValue(std::make_shared<Integer>(- posValue));
                posValue /= 10;
            }
            if (arrayWithIntegers->size() == ((2 * kNumValues) + 1))
            {
                // Insert the array into the message.
                stuff->open(true);
                stuff->setValue(arrayWithIntegers);
                stuff->close();
                // Extract objects from the message and compare with the expected contents.
                auto    extractedValue{stuff->getValue(true)};

                ODL_P1(extractedValue.get()); //####
                if (extractedValue)
                {
                    auto    asFlaw{extractedValue->asFlaw()};

                    if (nullptr == asFlaw)
                    {
                        if (stuff->readAtEnd())
                        {
                            if (extractedValue->deeplyEqualTo(*arrayWithIntegers))
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
                    else
                    {
                        ODL_LOG(asFlaw->getDescription().c_str()); //####
                    }
                }
                else
                {
                    ODL_LOG("! (extractedValue)"); //####
                }
                if (0 == result)
                {
                    // Compare the bytes with the expected minimal bytes.
                    static const DataKind   expectedBytesForArrayWithIntegers[]
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
                        StaticCast(DataKind, StaticCast(int, (2 * kNumValues) + 1) + kDataKindIntegerShortValueMinValue - 1),
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
                    constexpr size_t        expectedBytesForArrayWithIntegersCount{numElementsInArray(expectedBytesForArrayWithIntegers)};
                    auto                    contents{stuff->getString()};
                    size_t                  length{contents.size()};

                    ODL_PACKET("contents", contents.data(), length); //####
                    ODL_PACKET("expected", expectedBytesForArrayWithIntegers, expectedBytesForArrayWithIntegersCount); //####
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
} // doTestExtractMessageWithArrayWithRangeOfIntegers

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
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string progName{*argv};
    int         result{1};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    try
    {
        nImO::TestContext   ourContext{};

        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestExtractEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestExtractLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestExtractTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestExtractSmallIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestExtractMediumIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 6 :
                        result = doTestExtractBigIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 7 :
                        result = doTestExtractEmptyStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 8 :
                        result = doTestExtractShortStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 9 :
                        result = doTestExtractMediumStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestExtractEmptyBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 11 :
                        result = doTestExtractSmallBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestExtractMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestExtractSingleDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 14 :
                        result = doTestExtractAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 15 :
                        result = doTestExtractDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 16 :
                        result = doTestExtractTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 100 :
                        result = doTestExtractEmptyArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestExtractEmptyMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestExtractEmptySetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 110 :
                        result = doTestExtractArrayOneLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 111 :
                        result = doTestExtractArrayOneIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 112 :
                        result = doTestExtractArrayOneDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 113 :
                        result = doTestExtractArrayOneStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 114 :
                        result = doTestExtractArrayOneBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 115 :
                        result = doTestExtractArrayOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 116 :
                        result = doTestExtractArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 117 :
                        result = doTestExtractArrayOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 118 :
                        result = doTestExtractArrayWithOneAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 119 :
                        result = doTestExtractArrayWithOneDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 120 :
                        result = doTestExtractArrayWithOneTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 130 :
                        result = doTestExtractArrayTwoLogicalsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 131 :
                        result = doTestExtractArrayTwoIntegersMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 132 :
                        result = doTestExtractArrayTwoDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 133 :
                        result = doTestExtractArrayTwoStringsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 134 :
                        result = doTestExtractArrayTwoBlobsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 135 :
                        result = doTestExtractArrayTwoArraysMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 136 :
                        result = doTestExtractArrayTwoMapsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 137 :
                        result = doTestExtractArrayTwoSetsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 138 :
                        result = doTestExtractArrayOneArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 139 :
                        result = doTestExtractArrayOneMapOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 140 :
                        result = doTestExtractArrayOneSetOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 141 :
                        result = doTestExtractArrayWithManyDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 142 :
                        result = doTestExtractArrayWithTwoAddressesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 143 :
                        result = doTestExtractArrayWithTwoDatesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 144 :
                        result = doTestExtractArrayWithTwoTimesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 145 :
                        result = doTestExtractArrayWithOneDateOneTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 160 :
                        result = doTestExtractLogicalMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 161 :
                        result = doTestExtractIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 162 :
                        result = doTestExtractStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 163 :
                        result = doTestExtractLogicalSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 164 :
                        result = doTestExtractIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 165 :
                        result = doTestExtractStdStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 166 :
                        result = doTestExtractAddressMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 167 :
                        result = doTestExtractAddressSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 168 :
                        result = doTestExtractDateMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 169 :
                        result = doTestExtractDateSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 170 :
                        result = doTestExtractTimeMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 171 :
                        result = doTestExtractTimeSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 180 :
                        result = doTestExtractMessageWithArrayWithRangeOfIntegers(*argv, argc - 1, argv + 2);
                        break;

                    default :
                        break;

                }
                if (0 != result)
                {
                    ODL_I1(result); //####
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
        
    }
    ODL_EXIT_I(result); //####
    return result;
} // main

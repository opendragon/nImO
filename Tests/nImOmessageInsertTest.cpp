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

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOblob.h>
#include <BasicTypes/nImOdate.h>
#include <BasicTypes/nImOdouble.h>
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

/*! @brief Put a Value into a Message and verify what was stored.
 @param[in,out] stuff The Message to be modified.
 @param[in] aValue The Value to be added to the Message.
 @param[in] expectedContents1 The expected contents of the Message.
 @param[in] expectedSize1 The expected size of the Message.
 @param[in] expectedContents2 The expected contents of the Message when prepared for transmission.
 @param[in] expectedSize2 The expected size of the contents of the Message when prepared for
 transmission.
 @return Zero on success and non-zero on failure. */
static int
setValueAndCheck
    (Message &      stuff,
     SpValue        aValue,
     CPtr(DataKind) expectedContents,
     const size_t   expectedSize)
{
    ODL_ENTER(); //####
    ODL_P3(&stuff, aValue.get(), expectedContents); //####
    ODL_I1(expectedSize); //####
    stuff.open(true);
    stuff.setValue(aValue);
    stuff.close();
    auto    contents{stuff.getString()};
    size_t  length{contents.size()};
    int     result;

    ODL_PACKET("expectedContents1", expectedContents, expectedSize); //####
    ODL_PACKET("contents1", contents.data(), length); //####
    if (expectedSize == length)
    {
        result = StaticCast(int, CompareBytes(expectedContents, contents.data(), expectedSize));
    }
    else
    {
        ODL_LOG("! (expectedSize == length)"); //####
        result = 1;
    }
    ODL_EXIT_I(result); //####
    return result;
} // setValueAndCheck

#if defined(__APPLE__)
# pragma mark *** Test Case 001 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyMessage
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
            static const DataKind   expectedEmptyBytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            constexpr size_t        expectedEmptyByteCount{numElementsInArray(expectedEmptyBytes)};
            ODL_PACKET("expectedBytes", expectedEmptyBytes, expectedEmptyByteCount); //####
            auto                    contents{stuff->getString()};
            size_t                  length{contents.size()};

            stuff->open(true);
            if (0 == length)
            {
                stuff->close();
                contents = stuff->getString();
                length = contents.size();
                ODL_PACKET("contents", contents.data(), length); //####
                if (expectedEmptyByteCount == length)
                {
                    result = StaticCast(int, CompareBytes(expectedEmptyBytes, contents.data(), expectedEmptyByteCount));
                }
                else
                {
                    ODL_LOG("! (expectedEmptyByteCount == length)"); //####
                }
            }
            else
            {
                ODL_LOG("! (0 == length)"); //####
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
} // doTestInsertEmptyMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertLogicalMessage
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
            static const DataKind   expectedTrueBytes[]
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
            constexpr size_t        expectedTrueByteCount{numElementsInArray(expectedTrueBytes)};
            static const DataKind   expectedFalseBytes[]
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
            constexpr size_t        expectedFalseByteCount{numElementsInArray(expectedFalseBytes)};
            auto                    falseValue{std::make_shared<Logical>(false)};
            auto                    trueValue{std::make_shared<Logical>(true)};

            result = setValueAndCheck(*stuff, trueValue, expectedTrueBytes, expectedTrueByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, falseValue, expectedFalseBytes, expectedFalseByteCount);
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
} // doTestInsertLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertTinyIntegerMessage
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
            static const DataKind   expectedMinus12Bytes[]
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
            constexpr size_t        expectedMinus12ByteCount{numElementsInArray(expectedMinus12Bytes)};
            static const DataKind   expectedZeroBytes[]
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
            constexpr size_t        expectedZeroByteCount{numElementsInArray(expectedZeroBytes)};
            static const DataKind   expectedPlus12Bytes[]
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
            constexpr size_t        expectedPlus12ByteCount{numElementsInArray(expectedPlus12Bytes)};
            auto                    minus12Value{std::make_shared<Integer>(-12)};
            auto                    zeroValue{std::make_shared<Integer>(0)};
            auto                    plus12Value{std::make_shared<Integer>(12)};

            result = setValueAndCheck(*stuff, minus12Value, expectedMinus12Bytes, expectedMinus12ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, zeroValue, expectedZeroBytes, expectedZeroByteCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus12Value, expectedPlus12Bytes, expectedPlus12ByteCount);
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
} // doTestInsertTinyIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertSmallIntegerMessage
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
            static const DataKind   expectedMinus144Bytes[]
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
            constexpr size_t        expectedMinus144ByteCount{numElementsInArray(expectedMinus144Bytes)};
            static const DataKind   expectedPlus144Bytes[]
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
            constexpr size_t        expectedPlus144ByteCount{numElementsInArray(expectedPlus144Bytes)};
            auto                    minus144Value{std::make_shared<Integer>(-144)};
            auto                    plus144Value{std::make_shared<Integer>(144)};

            result = setValueAndCheck(*stuff, minus144Value, expectedMinus144Bytes, expectedMinus144ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus144Value, expectedPlus144Bytes, expectedPlus144ByteCount);
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
} // doTestInsertSmallIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertMediumIntegerMessage
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
            static const DataKind   expectedMinus1234567Bytes[]
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
            constexpr size_t        expectedMinus1234567ByteCount{numElementsInArray(expectedMinus1234567Bytes)};
            static const DataKind   expectedPlus1234567Bytes[]
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
            constexpr size_t        expectedPlus1234567ByteCount{numElementsInArray(expectedPlus1234567Bytes)};
            auto                    minus1234567Value{std::make_shared<Integer>(-1234567)};
            auto                    plus1234567Value{std::make_shared<Integer>(1234567)};

            result = setValueAndCheck(*stuff, minus1234567Value, expectedMinus1234567Bytes, expectedMinus1234567ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus1234567Value, expectedPlus1234567Bytes, expectedPlus1234567ByteCount);
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
} // doTestInsertMediumIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertBigIntegerMessage
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
            static const DataKind   expectedMinusBigNumberBytes[]
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
            constexpr size_t        expectedMinusBigNumberByteCount{numElementsInArray(expectedMinusBigNumberBytes)};
            static const DataKind   expectedPlusBigNumberBytes[]
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
            constexpr size_t        expectedPlusBigNumberByteCount{numElementsInArray(expectedPlusBigNumberBytes)};
            auto                    minusBigNumberValue{std::make_shared<Integer>(-20015998343868)};
            auto                    plusBigNumberValue{std::make_shared<Integer>(20015998343868)};

            result = setValueAndCheck(*stuff, minusBigNumberValue, expectedMinusBigNumberBytes, expectedMinusBigNumberByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plusBigNumberValue, expectedPlusBigNumberBytes, expectedPlusBigNumberByteCount);
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
} // doTestInsertBigIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 007 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyStringMessage
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
            static const DataKind   expectedEmptyStringBytes[]
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
            constexpr size_t        expectedEmptyStringByteCount{numElementsInArray(expectedEmptyStringBytes)};
            auto                    emptyStringValue{std::make_shared<String>()};

            result = setValueAndCheck(*stuff, emptyStringValue, expectedEmptyStringBytes, expectedEmptyStringByteCount);
        }
        else
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
} // doTestInsertEmptyStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 008 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertShortStringMessage
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
            static const DataKind   expectedShortStringBytes[]
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
            constexpr size_t        expectedShortStringByteCount{numElementsInArray(expectedShortStringBytes)};
            auto                    shortStringValue{std::make_shared<String>("abcdef")};

            result = setValueAndCheck(*stuff, shortStringValue, expectedShortStringBytes, expectedShortStringByteCount);
        }
        else
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
} // doTestInsertShortStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 009 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertMediumStringMessage
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
            static const DataKind   expectedMediumStringBytes[]
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
            constexpr size_t        expectedMediumStringByteCount{numElementsInArray(expectedMediumStringBytes)};
            auto                    mediumStringValue{std::make_shared<String>("abcdefabcdefabcdefabcdefabcdefabcdefabcdef")};

            result = setValueAndCheck(*stuff, mediumStringValue, expectedMediumStringBytes, expectedMediumStringByteCount);
        }
        else
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
} // doTestInsertMediumStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 010 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyBlobMessage
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
            static const DataKind   expectedEmptyBlobBytes[]
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
            constexpr size_t        expectedEmptyBlobByteCount{numElementsInArray(expectedEmptyBlobBytes)};
            auto                    emptyBlobValue{std::make_shared<Blob>()};

            result = setValueAndCheck(*stuff, emptyBlobValue, expectedEmptyBlobBytes, expectedEmptyBlobByteCount);
        }
        else
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
} // doTestInsertEmptyBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 011 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertSmallBlobMessage
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
            static const DataKind   expectedSmallBlobBytes[]
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
            constexpr size_t        expectedSmallBlobByteCount{numElementsInArray(expectedSmallBlobBytes)};
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            constexpr size_t        actualDataCount{numElementsInArray(actualData)};
            auto                    smallBlobValue{std::make_shared<Blob>(actualData, actualDataCount)};

            result = setValueAndCheck(*stuff, smallBlobValue, expectedSmallBlobBytes, expectedSmallBlobByteCount);
        }
        else
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
} // doTestInsertSmallBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 012 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertMediumBlobMessage
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
            static const DataKind   expectedMediumBlobBytes[]
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
            constexpr size_t        expectedMediumBlobByteCount{numElementsInArray(expectedMediumBlobBytes)};
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
            auto                    mediumBlobValue{std::make_shared<Blob>(actualData, actualDataCount)};

            result = setValueAndCheck(*stuff, mediumBlobValue, expectedMediumBlobBytes, expectedMediumBlobByteCount);
        }
        else
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
} // doTestInsertMediumBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 013 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertSingleDoubleMessage
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
            static const DataKind   expectedPlus42Point5Bytes[]
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
            constexpr size_t        expectedPlus42Point5ByteCount{numElementsInArray(expectedPlus42Point5Bytes)};
            static const DataKind   expectedMinus42Point5Bytes[]
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
            constexpr size_t        expectedMinus42Point5ByteCount{numElementsInArray(expectedMinus42Point5Bytes)};
            auto                    plus42Point5Value{std::make_shared<Double>(42.5)};
            auto                    minus42Point5Value{std::make_shared<Double>(-42.5)};

            result = setValueAndCheck(*stuff, plus42Point5Value, expectedPlus42Point5Bytes,
                                      expectedPlus42Point5ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, minus42Point5Value, expectedMinus42Point5Bytes, expectedMinus42Point5ByteCount);
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
} // doTestInsertSingleDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 014 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertAddressMessage
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
            static const DataKind   expectedAddress1Bytes[]
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
            constexpr size_t        expectedAddress1ByteCount{numElementsInArray(expectedAddress1Bytes)};
            static const DataKind   expectedAddress2Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0x34),
                    StaticCast(DataKind, 0x56),
                    StaticCast(DataKind, 0x78),
                    StaticCast(DataKind, 0xAB),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        expectedAddress2ByteCount{numElementsInArray(expectedAddress2Bytes)};
            static const DataKind   expectedAddress3Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Address
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address,
                    StaticCast(DataKind, 0x56),
                    StaticCast(DataKind, 0x78),
                    StaticCast(DataKind, 0xAB),
                    StaticCast(DataKind, 0xCD),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t        expectedAddress3ByteCount{numElementsInArray(expectedAddress3Bytes)};
            auto                    address1Value{std::make_shared<Address>(0x12345678)};
            auto                    address2Value{std::make_shared<Address>(0x345678AB)};
            auto                    address3Value{std::make_shared<Address>(0x5678ABCD)};

            result = setValueAndCheck(*stuff, address1Value, expectedAddress1Bytes, expectedAddress1ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, address2Value, expectedAddress2Bytes, expectedAddress2ByteCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, address3Value, expectedAddress3Bytes, expectedAddress3ByteCount);
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
} // doTestInsertAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 015 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertDateMessage
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
            static const Date::DatePieces   date1{12, 11, 10};
            static const Date::DatePieces   date2{11, 10, 9};
            static const Date::DatePieces   date3{10, 9, 8};
            static const DataKind           expectedDate1Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(date1)),
                    StaticCast(DataKind, SecondDateByte(date1)),
                    StaticCast(DataKind, ThirdDateByte(date1)),
                    StaticCast(DataKind, FourthDateByte(date1)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                expectedDate1ByteCount{numElementsInArray(expectedDate1Bytes)};
            static const DataKind           expectedDate2Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(date2)),
                    StaticCast(DataKind, SecondDateByte(date2)),
                    StaticCast(DataKind, ThirdDateByte(date2)),
                    StaticCast(DataKind, FourthDateByte(date2)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                expectedDate2ByteCount{numElementsInArray(expectedDate2Bytes)};
            static const DataKind           expectedDate3Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeDate,
                    StaticCast(DataKind, FirstDateByte(date3)),
                    StaticCast(DataKind, SecondDateByte(date3)),
                    StaticCast(DataKind, ThirdDateByte(date3)),
                    StaticCast(DataKind, FourthDateByte(date3)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                expectedDate3ByteCount{numElementsInArray(expectedDate3Bytes)};
            auto                            date1Value{std::make_shared<Date>(MakeDateValue(date1))};
            auto                            date2Value{std::make_shared<Date>(MakeDateValue(date2))};
            auto                            date3Value{std::make_shared<Date>(MakeDateValue(date3))};

            result = setValueAndCheck(*stuff, date1Value, expectedDate1Bytes, expectedDate1ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, date2Value, expectedDate2Bytes, expectedDate2ByteCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, date3Value, expectedDate3Bytes, expectedDate3ByteCount);
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
} // doTestInsertDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 016 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertTimeMessage
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
            static const Time::TimePieces   time1{12, 11, 10, 9};
            static const Time::TimePieces   time2{11, 10, 9, 8};
            static const Time::TimePieces   time3{10, 9, 8, 7};
            static const DataKind           expectedTime1Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(time1)),
                    StaticCast(DataKind, SecondTimeByte(time1)),
                    StaticCast(DataKind, ThirdTimeByte(time1)),
                    StaticCast(DataKind, FourthTimeByte(time1)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                expectedTime1ByteCount{numElementsInArray(expectedTime1Bytes)};
            static const DataKind           expectedTime2Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(time2)),
                    StaticCast(DataKind, SecondTimeByte(time2)),
                    StaticCast(DataKind, ThirdTimeByte(time2)),
                    StaticCast(DataKind, FourthTimeByte(time2)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                expectedTime2ByteCount{numElementsInArray(expectedTime2Bytes)};
            static const DataKind           expectedTime3Bytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Date
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeTime,
                    StaticCast(DataKind, FirstTimeByte(time3)),
                    StaticCast(DataKind, SecondTimeByte(time3)),
                    StaticCast(DataKind, ThirdTimeByte(time3)),
                    StaticCast(DataKind, FourthTimeByte(time3)),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t                expectedTime3ByteCount{numElementsInArray(expectedTime3Bytes)};
            auto                            time1Value{std::make_shared<Time>(MakeTimeValue(time1))};
            auto                            time2Value{std::make_shared<Time>(MakeTimeValue(time2))};
            auto                            time3Value{std::make_shared<Time>(MakeTimeValue(time3))};

            result = setValueAndCheck(*stuff, time1Value, expectedTime1Bytes, expectedTime1ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, time2Value, expectedTime2Bytes, expectedTime2ByteCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, time3Value, expectedTime3Bytes, expectedTime3ByteCount);
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
} // doTestInsertTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyArrayMessage
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
            static const DataKind   expectedEmptyArrayBytes[]
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
            constexpr size_t        expectedEmptyArrayByteCount{numElementsInArray(expectedEmptyArrayBytes)};
            auto                    emptyArray{std::make_shared<Array>()};

            result = setValueAndCheck(*stuff, emptyArray, expectedEmptyArrayBytes, expectedEmptyArrayByteCount);
        }
        else
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
} // doTestInsertEmptyArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptyMapMessage
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
            static const DataKind   expectedEmptyMapBytes[]
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
            constexpr size_t        expectedEmptyMapByteCount{numElementsInArray(expectedEmptyMapBytes)};
            auto                    emptyMap{std::make_shared<Map>()};

            result = setValueAndCheck(*stuff, emptyMap, expectedEmptyMapBytes, expectedEmptyMapByteCount);
        }
        else
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
} // doTestInsertEmptyMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertEmptySetMessage
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
            static const DataKind   expectedEmptySetBytes[]
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
            constexpr size_t        expectedEmptySetByteCount{numElementsInArray(expectedEmptySetBytes)};
            auto                    emptySet{std::make_shared<Set>()};

            result = setValueAndCheck(*stuff, emptySet, expectedEmptySetBytes, expectedEmptySetByteCount);
        }
        else
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
} // doTestInsertEmptySetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneLogicalMessage
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
            static const DataKind   expectedArrayOneLogicalBytes[]
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
            constexpr size_t        expectedArrayOneLogicalByteCount{numElementsInArray(expectedArrayOneLogicalBytes)};
            auto                    arrayOneLogical{std::make_shared<Array>()};

            arrayOneLogical->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayOneLogical, expectedArrayOneLogicalBytes, expectedArrayOneLogicalByteCount);
        }
        else
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
} // doTestInsertArrayOneLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneIntegerMessage
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
            static const DataKind   expectedArrayOneIntegerBytes[]
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
            constexpr size_t        expectedArrayOneIntegerByteCount{numElementsInArray(expectedArrayOneIntegerBytes)};
            auto                    arrayOneInteger{std::make_shared<Array>()};

            arrayOneInteger->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayOneInteger, expectedArrayOneIntegerBytes, expectedArrayOneIntegerByteCount);
        }
        else
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
} // doTestInsertArrayOneIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneDoubleMessage
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
            static const DataKind   expectedArrayOneDoubleBytes[]
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
            constexpr size_t        expectedArrayOneDoubleByteCount{numElementsInArray(expectedArrayOneDoubleBytes)};
            auto                    arrayOneDouble{std::make_shared<Array>()};

            arrayOneDouble->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayOneDouble, expectedArrayOneDoubleBytes, expectedArrayOneDoubleByteCount);
        }
        else
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
} // doTestInsertArrayOneDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneStringMessage
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
            static const DataKind   expectedArrayOneStringBytes[]
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
            constexpr size_t        expectedArrayOneStringByteCount{numElementsInArray(expectedArrayOneStringBytes)};
            auto                    arrayOneString{std::make_shared<Array>()};

            arrayOneString->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayOneString, expectedArrayOneStringBytes, expectedArrayOneStringByteCount);
        }
        else
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
} // doTestInsertArrayOneStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 114 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneBlobMessage
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
            static const DataKind   expectedArrayOneBlobBytes[]
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
            constexpr size_t        expectedArrayOneBlobByteCount{numElementsInArray(expectedArrayOneBlobBytes)};
            auto                    arrayOneBlob{std::make_shared<Array>()};

            arrayOneBlob->addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayOneBlob, expectedArrayOneBlobBytes, expectedArrayOneBlobByteCount);
        }
        else
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
} // doTestInsertArrayOneBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 115 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneArrayMessage
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
            static const DataKind   expectedArrayOneArrayBytes[]
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
            constexpr size_t        expectedArrayOneArrayByteCount{numElementsInArray(expectedArrayOneArrayBytes)};
            auto                    arrayOneArray{std::make_shared<Array>()};

            arrayOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneArray, expectedArrayOneArrayBytes, expectedArrayOneArrayByteCount);
        }
        else
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
} // doTestInsertArrayOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 116 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneMapMessage
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
            static const DataKind   expectedArrayOneMapBytes[]
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
            constexpr size_t        expectedArrayOneMapByteCount{numElementsInArray(expectedArrayOneMapBytes)};
            auto                    arrayOneMap{std::make_shared<Array>()};

            arrayOneMap->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneMap, expectedArrayOneMapBytes, expectedArrayOneMapByteCount);
        }
        else
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
} // doTestInsertArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 117 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneSetMessage
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
            static const DataKind   expectedArrayOneSetBytes[]
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
            constexpr size_t        expectedArrayOneSetByteCount{numElementsInArray(expectedArrayOneSetBytes)};
            auto                    arrayOneSet{std::make_shared<Array>()};

            arrayOneSet->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneSet, expectedArrayOneSetBytes, expectedArrayOneSetByteCount);
        }
        else
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
} // doTestInsertArrayOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 118 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithOneAddressMessage
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
            static const DataKind   expectedArrayOneAddressBytes[]
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
            constexpr size_t        expectedArrayOneAddressByteCount{numElementsInArray(expectedArrayOneAddressBytes)};
            auto                    arrayOneAddress{std::make_shared<Array>()};

            arrayOneAddress->addValue(std::make_shared<Address>(0x12345678));
            result = setValueAndCheck(*stuff, arrayOneAddress, expectedArrayOneAddressBytes, expectedArrayOneAddressByteCount);
        }
        else
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
} // doTestInsertArrayWithOneAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 119 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithOneDateMessage
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
            static const DataKind           expectedArrayOneDateBytes[]
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
            constexpr size_t                expectedArrayOneDateByteCount{numElementsInArray(expectedArrayOneDateBytes)};
            auto                            arrayOneDate{std::make_shared<Array>()};

            arrayOneDate->addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = setValueAndCheck(*stuff, arrayOneDate, expectedArrayOneDateBytes, expectedArrayOneDateByteCount);
        }
        else
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
} // doTestInsertArrayWithOneDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 120 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithOneTimeMessage
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
            static const DataKind           expectedArrayOneTimeBytes[]
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
            constexpr size_t                expectedArrayOneTimeByteCount{numElementsInArray(expectedArrayOneTimeBytes)};
            auto                            arrayOneTime{std::make_shared<Array>()};

            arrayOneTime->addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = setValueAndCheck(*stuff, arrayOneTime, expectedArrayOneTimeBytes, expectedArrayOneTimeByteCount);
        }
        else
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
} // doTestInsertArrayWithOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 130 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoLogicalsMessage
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
            static const DataKind   expectedArrayTwoLogicalsBytes[]
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
            constexpr size_t        expectedArrayTwoLogicalsByteCount{numElementsInArray(expectedArrayTwoLogicalsBytes)};
            auto                    arrayTwoLogicals{std::make_shared<Array>()};

            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayTwoLogicals, expectedArrayTwoLogicalsBytes, expectedArrayTwoLogicalsByteCount);
        }
        else
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
} // doTestInsertArrayTwoLogicalsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 131 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoIntegersMessage
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
            static const DataKind   expectedArrayTwoIntegersBytes[]
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
            constexpr size_t        expectedArrayTwoIntegersByteCount{numElementsInArray(expectedArrayTwoIntegersBytes)};
            auto                    arrayTwoIntegers{std::make_shared<Array>()};

            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayTwoIntegers, expectedArrayTwoIntegersBytes, expectedArrayTwoIntegersByteCount);
        }
        else
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
} // doTestInsertArrayTwoIntegersMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 132 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoDoublesMessage
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
            static const DataKind   expectedArrayTwoDoublesBytes[]
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
            constexpr size_t        expectedArrayTwoDoublesByteCount{numElementsInArray(expectedArrayTwoDoublesBytes)};
            auto                    arrayTwoDoubles{std::make_shared<Array>()};

            arrayTwoDoubles->addValue(std::make_shared<Double>());
            arrayTwoDoubles->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayTwoDoubles, expectedArrayTwoDoublesBytes, expectedArrayTwoDoublesByteCount);
        }
        else
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
} // doTestInsertArrayTwoDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 133 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoStringsMessage
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
            static const DataKind   expectedArrayTwoStringsBytes[]
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
            constexpr size_t        expectedArrayTwoStringsByteCount{numElementsInArray(expectedArrayTwoStringsBytes)};
            auto                    arrayTwoStrings{std::make_shared<Array>()};

            arrayTwoStrings->addValue(std::make_shared<String>());
            arrayTwoStrings->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayTwoStrings, expectedArrayTwoStringsBytes, expectedArrayTwoStringsByteCount);
        }
        else
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
} // doTestInsertArrayTwoStringsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 134 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoBlobsMessage
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
            static const DataKind   expectedArrayTwoBlobsBytes[]
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
            constexpr size_t        expectedArrayTwoBlobsByteCount{numElementsInArray(expectedArrayTwoBlobsBytes)};
            auto                    arrayTwoBlobs{std::make_shared<Array>()};

            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayTwoBlobs, expectedArrayTwoBlobsBytes, expectedArrayTwoBlobsByteCount);
        }
        else
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
} // doTestInsertArrayTwoBlobsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 135 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoArraysMessage
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
            static const DataKind   expectedArrayTwoArraysBytes[]
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
            constexpr size_t        expectedArrayTwoArraysByteCount{numElementsInArray(expectedArrayTwoArraysBytes)};
            auto                    arrayTwoArrays{std::make_shared<Array>()};

            arrayTwoArrays->addValue(std::make_shared<Array>());
            arrayTwoArrays->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayTwoArrays, expectedArrayTwoArraysBytes, expectedArrayTwoArraysByteCount);
        }
        else
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
} // doTestInsertArrayTwoArraysMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 136 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoMapsMessage
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
            static const DataKind   expectedArrayTwoMapsBytes[]
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
            constexpr size_t        expectedArrayTwoMapsByteCount{numElementsInArray(expectedArrayTwoMapsBytes)};
            auto                    arrayTwoMaps{std::make_shared<Array>()};

            arrayTwoMaps->addValue(std::make_shared<Map>());
            arrayTwoMaps->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayTwoMaps, expectedArrayTwoMapsBytes, expectedArrayTwoMapsByteCount);
        }
        else
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
} // doTestInsertArrayTwoMapsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 137 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayTwoSetsMessage
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
            static const DataKind   expectedArrayTwoSetsBytes[]
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
            constexpr size_t        expectedArrayTwoSetsByteCount{numElementsInArray(expectedArrayTwoSetsBytes)};
            auto                    arrayTwoSets{std::make_shared<Array>()};

            arrayTwoSets->addValue(std::make_shared<Set>());
            arrayTwoSets->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayTwoSets, expectedArrayTwoSetsBytes, expectedArrayTwoSetsByteCount);
        }
        else
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
} // doTestInsertArrayTwoSetsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 138 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneArrayOneMapMessage
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
            static const DataKind   expectedArrayOneArrayOneMapBytes[]
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
            constexpr size_t        expectedArrayOneArrayOneMapByteCount{numElementsInArray(expectedArrayOneArrayOneMapBytes)};
            auto                    arrayOneArrayOneMap{std::make_shared<Array>()};

            arrayOneArrayOneMap->addValue(std::make_shared<Array>());
            arrayOneArrayOneMap->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneArrayOneMap, expectedArrayOneArrayOneMapBytes, expectedArrayOneArrayOneMapByteCount);
        }
        else
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
} // doTestInsertArrayOneArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 139 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneMapOneSetMessage
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
            static const DataKind   expectedArrayOneMapOneSetBytes[]
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
            constexpr size_t        expectedArrayOneMapOneSetByteCount{numElementsInArray(expectedArrayOneMapOneSetBytes)};
            auto                    arrayOneMapOneSet{std::make_shared<Array>()};

            arrayOneMapOneSet->addValue(std::make_shared<Map>());
            arrayOneMapOneSet->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneMapOneSet, expectedArrayOneMapOneSetBytes, expectedArrayOneMapOneSetByteCount);
        }
        else
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
} // doTestInsertArrayOneMapOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 140 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayOneSetOneArrayMessage
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
            static const DataKind   expectedArrayOneSetOneArrayBytes[]
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
            constexpr size_t        expectedArrayOneSetOneArrayByteCount{numElementsInArray(expectedArrayOneSetOneArrayBytes)};
            auto                    arrayOneSetOneArray{std::make_shared<Array>()};

            arrayOneSetOneArray->addValue(std::make_shared<Set>());
            arrayOneSetOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneSetOneArray, expectedArrayOneSetOneArrayBytes, expectedArrayOneSetOneArrayByteCount);
        }
        else
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
} // doTestInsertArrayOneSetOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 141 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithManyDoublesMessage
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
            static const DataKind   expectedArrayManyDoublesBytes[]
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
            constexpr size_t        expectedArrayManyDoublesByteCount{numElementsInArray(expectedArrayManyDoublesBytes)};
            auto                    arrayManyDoubles{std::make_shared<Array>()};

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles->addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = setValueAndCheck(*stuff, arrayManyDoubles, expectedArrayManyDoublesBytes, expectedArrayManyDoublesByteCount);
        }
        else
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
} // doTestInsertArrayWithManyDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 142 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithTwoAddressesMessage
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
            static const DataKind   expectedArrayTwoAddressesBytes[]
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
            constexpr size_t        expectedArrayTwoAddressesByteCount{numElementsInArray(expectedArrayTwoAddressesBytes)};
            auto                    arrayTwoAddresses{std::make_shared<Array>()};

            arrayTwoAddresses->addValue(std::make_shared<Address>(0x12345678));
            arrayTwoAddresses->addValue(std::make_shared<Address>(0x345678AB));
            result = setValueAndCheck(*stuff, arrayTwoAddresses, expectedArrayTwoAddressesBytes, expectedArrayTwoAddressesByteCount);
        }
        else
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
} // doTestInsertArrayWithTwoAddressesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 143 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithTwoDatesMessage
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
            static const DataKind           expectedArrayTwoDatesBytes[]
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
            constexpr size_t                expectedArrayTwoDatesByteCount{numElementsInArray(expectedArrayTwoDatesBytes)};
            auto                            arrayTwoDates{std::make_shared<Array>()};

            arrayTwoDates->addValue(std::make_shared<Date>(MakeDateValue(aDate1)));
            arrayTwoDates->addValue(std::make_shared<Date>(MakeDateValue(aDate2)));
            result = setValueAndCheck(*stuff, arrayTwoDates, expectedArrayTwoDatesBytes, expectedArrayTwoDatesByteCount);
        }
        else
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
} // doTestInsertArrayWithTwoDatesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 144 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithTwoTimesMessage
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
            static const DataKind           expectedArrayTwoTimesBytes[]
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
            constexpr size_t        expectedArrayTwoTimesByteCount{numElementsInArray(expectedArrayTwoTimesBytes)};
            auto                    arrayTwoTimes{std::make_shared<Array>()};

            arrayTwoTimes->addValue(std::make_shared<Time>(MakeTimeValue(aTime1)));
            arrayTwoTimes->addValue(std::make_shared<Time>(MakeTimeValue(aTime2)));
            result = setValueAndCheck(*stuff, arrayTwoTimes, expectedArrayTwoTimesBytes, expectedArrayTwoTimesByteCount);
        }
        else
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
} // doTestInsertArrayWithTwoTimesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 145 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertArrayWithOneDateOneTimeMessage
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
            static const DataKind           expectedArrayOneDateOneTimeBytes[]
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
            constexpr size_t                expectedArrayOneDateOneTimeByteCount{numElementsInArray(expectedArrayOneDateOneTimeBytes)};
            auto                            arrayOneDateOneTime{std::make_shared<Array>()};

            arrayOneDateOneTime->addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            arrayOneDateOneTime->addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = setValueAndCheck(*stuff, arrayOneDateOneTime, expectedArrayOneDateOneTimeBytes, expectedArrayOneDateOneTimeByteCount);
        }
        else
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
} // doTestInsertArrayWithOneDateOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 160 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertLogicalMapMessage
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
            static const DataKind   expectedLogicalMapBytes[]
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
            constexpr size_t        expectedLogicalMapByteCount{numElementsInArray(expectedLogicalMapBytes)};
            auto                    logicalMap{std::make_shared<Map>()};

            logicalMap->addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, logicalMap, expectedLogicalMapBytes, expectedLogicalMapByteCount);
        }
        else
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
} // doTestInsertLogicalMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 161 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertIntegerMapMessage
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
            static const DataKind   expectedIntegerMapBytes[]
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
            constexpr size_t        expectedIntegerMapByteCount{numElementsInArray(expectedIntegerMapBytes)};
            auto                    integerMap{std::make_shared<Map>()};

            integerMap->addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, integerMap, expectedIntegerMapBytes, expectedIntegerMapByteCount);
        }
        else
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
} // doTestInsertIntegerMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 162 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertStringMapMessage
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
            static const DataKind   expectedStringMapBytes[]
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
            constexpr size_t        expectedStringMapByteCount{numElementsInArray(expectedStringMapBytes)};
            auto                    stringMap{std::make_shared<Map>()};

            stringMap->addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, stringMap, expectedStringMapBytes, expectedStringMapByteCount);
        }
        else
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
} // doTestInsertStringMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 163 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertLogicalSetMessage
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
            static const DataKind   expectedLogicalSetBytes[]
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
            constexpr size_t        expectedLogicalSetByteCount{numElementsInArray(expectedLogicalSetBytes)};
            auto                    logicalSet{std::make_shared<Set>()};

            logicalSet->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, logicalSet, expectedLogicalSetBytes, expectedLogicalSetByteCount);
        }
        else
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
} // doTestInsertLogicalSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 164 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertIntegerSetMessage
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
            static const DataKind   expectedIntegerSetBytes[]
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
            constexpr size_t        expectedIntegerSetByteCount{numElementsInArray(expectedIntegerSetBytes)};
            auto                    integerSet{std::make_shared<Set>()};

            integerSet->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, integerSet, expectedIntegerSetBytes, expectedIntegerSetByteCount);
        }
        else
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
} // doTestInsertIntegerSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 165 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertStdStringSetMessage
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
            static const DataKind   expectedStdStringSetBytes[]
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
            constexpr size_t        expectedStdStringSetByteCount{numElementsInArray(expectedStdStringSetBytes)};
            auto                    stringSet{std::make_shared<Set>()};

            stringSet->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, stringSet, expectedStdStringSetBytes, expectedStdStringSetByteCount);
        }
        else
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
} // doTestInsertStdStringSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 166 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertAddressMapMessage
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
            static const DataKind   expectedAddressMapBytes[]
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
            constexpr size_t        expectedAddressMapByteCount{numElementsInArray(expectedAddressMapBytes)};
            auto                    addressMap{std::make_shared<Map>()};

            addressMap->addValue(std::make_shared<Address>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, addressMap, expectedAddressMapBytes, expectedAddressMapByteCount);
        }
        else
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
} // doTestInsertAddressMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 167 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertAddressSetMessage
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
            static const DataKind   expectedAddressSetBytes[]
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
            constexpr size_t        expectedAddressSetByteCount{numElementsInArray(expectedAddressSetBytes)};
            auto                    addressSet{std::make_shared<Set>()};

            addressSet->addValue(std::make_shared<Address>());
            result = setValueAndCheck(*stuff, addressSet, expectedAddressSetBytes, expectedAddressSetByteCount);
        }
        else
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
} // doTestInsertAddressSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 168 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertDateMapMessage
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
            static const DataKind           expectedDateMapBytes[]
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
            constexpr size_t                expectedDateMapByteCount{numElementsInArray(expectedDateMapBytes)};
            auto                            dateMap{std::make_shared<Map>()};

            dateMap->addValue(std::make_shared<Date>(MakeDateValue(aDate)), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, dateMap, expectedDateMapBytes, expectedDateMapByteCount);
        }
        else
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
} // doTestInsertDateMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 169 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertDateSetMessage
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
            static const DataKind           expectedDateSetBytes[]
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
                // Date
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
            constexpr size_t                expectedDateSetByteCount{numElementsInArray(expectedDateSetBytes)};
            auto                            dateSet{std::make_shared<Set>()};

            dateSet->addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = setValueAndCheck(*stuff, dateSet, expectedDateSetBytes, expectedDateSetByteCount);
        }
        else
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
} // doTestInsertDateSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 170 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertTimeMapMessage
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
            static const DataKind           expectedTimeMapBytes[]
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
            constexpr size_t        expectedTimeMapByteCount{numElementsInArray(expectedTimeMapBytes)};
            auto                    timeMap{std::make_shared<Map>()};

            timeMap->addValue(std::make_shared<Time>(MakeTimeValue(aTime)), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, timeMap, expectedTimeMapBytes, expectedTimeMapByteCount);
        }
        else
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
} // doTestInsertTimeMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 171 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInsertTimeSetMessage
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
            static const DataKind           expectedTimeSetBytes[]
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
            constexpr size_t                expectedTimeSetByteCount{numElementsInArray(expectedTimeSetBytes)};
            auto                            timeSet{std::make_shared<Set>()};

            timeSet->addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = setValueAndCheck(*stuff, timeSet, expectedTimeSetBytes, expectedTimeSetByteCount);
        }
        else
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
} // doTestInsertTimeSetMessage

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
                        result = doTestInsertEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestInsertLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestInsertTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestInsertSmallIntegerMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestInsertSmallBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestInsertMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestInsertSingleDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 14 :
                        result = doTestInsertAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 15 :
                        result = doTestInsertDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 16 :
                        result = doTestInsertTimeMessage(*argv, argc - 1, argv + 2);
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

                    case 118 :
                        result = doTestInsertArrayWithOneAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 119 :
                        result = doTestInsertArrayWithOneDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 120 :
                        result = doTestInsertArrayWithOneTimeMessage(*argv, argc - 1, argv + 2);
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

                    case 142 :
                        result = doTestInsertArrayWithTwoAddressesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 143 :
                        result = doTestInsertArrayWithTwoDatesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 144 :
                        result = doTestInsertArrayWithTwoTimesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 145 :
                        result = doTestInsertArrayWithOneDateOneTimeMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestInsertStdStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 166 :
                        result = doTestInsertAddressMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 167 :
                        result = doTestInsertAddressSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 168 :
                        result = doTestInsertDateMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 169 :
                        result = doTestInsertDateSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 170 :
                        result = doTestInsertTimeMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 171 :
                        result = doTestInsertTimeSetMessage(*argv, argc - 1, argv + 2);
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

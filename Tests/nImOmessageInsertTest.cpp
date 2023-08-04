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

#include <BasicTypes/nImOblob.h>
#include <BasicTypes/nImOdouble.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <ContainerTypes/nImOarray.h>
#include <ContainerTypes/nImObufferChunk.h>
#include <ContainerTypes/nImOmap.h>
#include <ContainerTypes/nImOmessage.h>
#include <ContainerTypes/nImOset.h>
#include <ContainerTypes/nImOstringBuffer.h>
#include <Contexts/nImOtestContext.h>

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
    ODL_I1("signal = ", signal); //####
    std::string message{"exiting due to signal " + std::to_string(signal) + " = " + NameOfSignal(signal)};

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
    ODL_P3("stuff = ", &stuff, "aValue = ", aValue.get(), "expectedContents = ", expectedContents); //####
    ODL_I1("expectedSize = ", expectedSize); //####
    stuff.open(true);
    stuff.setValue(aValue);
    stuff.close();
    auto    contents{stuff.getBytes()};
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            static const DataKind   expectedEmptyBytes[]
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            const size_t            expectedEmptyByteCount{A_SIZE(expectedEmptyBytes)};
            ODL_PACKET("expectedBytes", expectedEmptyBytes, expectedEmptyByteCount); //####
            auto                    contents{stuff->getBytes()};
            size_t                  length{contents.size()};

            stuff->open(true);
            if (0 == length)
            {
                stuff->close();
                contents = stuff->getBytes();
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            static const DataKind   expectedTrueBytes[]
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
            const size_t            expectedTrueByteCount{A_SIZE(expectedTrueBytes)};
            static const DataKind   expectedFalseBytes[]
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
            const size_t            expectedFalseByteCount{A_SIZE(expectedFalseBytes)};
            auto                    falseValue{std::make_shared<Logical>(false)};
            auto                    trueValue{std::make_shared<Logical>(true)};

            result = setValueAndCheck(*stuff, trueValue, expectedTrueBytes, expectedTrueByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, falseValue, expectedFalseBytes, expectedFalseByteCount);
            }
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedMinus12ByteCount{A_SIZE(expectedMinus12Bytes)};
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
            const size_t            expectedZeroByteCount{A_SIZE(expectedZeroBytes)};
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
            const size_t            expectedPlus12ByteCount{A_SIZE(expectedPlus12Bytes)};
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedMinus144ByteCount{A_SIZE(expectedMinus144Bytes)};
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
            const size_t            expectedPlus144ByteCount{A_SIZE(expectedPlus144Bytes)};
            auto                    minus144Value{std::make_shared<Integer>(-144)};
            auto                    plus144Value{std::make_shared<Integer>(144)};

            result = setValueAndCheck(*stuff, minus144Value, expectedMinus144Bytes, expectedMinus144ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus144Value, expectedPlus144Bytes, expectedPlus144ByteCount);
            }
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedMinus1234567ByteCount{A_SIZE(expectedMinus1234567Bytes)};
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
            const size_t            expectedPlus1234567ByteCount{A_SIZE(expectedPlus1234567Bytes)};
            auto                    minus1234567Value{std::make_shared<Integer>(-1234567)};
            auto                    plus1234567Value{std::make_shared<Integer>(1234567)};

            result = setValueAndCheck(*stuff, minus1234567Value, expectedMinus1234567Bytes, expectedMinus1234567ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus1234567Value, expectedPlus1234567Bytes, expectedPlus1234567ByteCount);
            }
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedMinusBigNumberByteCount{A_SIZE(expectedMinusBigNumberBytes)};
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
            const size_t            expectedPlusBigNumberByteCount{A_SIZE(expectedPlusBigNumberBytes)};
            auto                    minusBigNumberValue{std::make_shared<Integer>(-20015998343868)};
            auto                    plusBigNumberValue{std::make_shared<Integer>(20015998343868)};

            result = setValueAndCheck(*stuff, minusBigNumberValue, expectedMinusBigNumberBytes, expectedMinusBigNumberByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plusBigNumberValue, expectedPlusBigNumberBytes, expectedPlusBigNumberByteCount);
            }
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedEmptyStringByteCount{A_SIZE(expectedEmptyStringBytes)};
            auto                    emptyStringValue{std::make_shared<String>()};

            result = setValueAndCheck(*stuff, emptyStringValue, expectedEmptyStringBytes, expectedEmptyStringByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedShortStringByteCount{A_SIZE(expectedShortStringBytes)};
            auto                    shortStringValue{std::make_shared<String>("abcdef")};

            result = setValueAndCheck(*stuff, shortStringValue, expectedShortStringBytes, expectedShortStringByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedMediumStringByteCount{A_SIZE(expectedMediumStringBytes)};
            auto                    mediumStringValue{std::make_shared<String>("abcdefabcdefabcdefabcdefabcdefabcdefabcdef")};

            result = setValueAndCheck(*stuff, mediumStringValue, expectedMediumStringBytes, expectedMediumStringByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedEmptyBlobByteCount{A_SIZE(expectedEmptyBlobBytes)};
            auto                    emptyBlobValue{std::make_shared<Blob>()};

            result = setValueAndCheck(*stuff, emptyBlobValue, expectedEmptyBlobBytes, expectedEmptyBlobByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedSmallBlobByteCount{A_SIZE(expectedSmallBlobBytes)};
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t            actualDataCount{A_SIZE(actualData)};
            auto                    smallBlobValue{std::make_shared<Blob>(actualData, actualDataCount)};

            result = setValueAndCheck(*stuff, smallBlobValue, expectedSmallBlobBytes, expectedSmallBlobByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedMediumBlobByteCount{A_SIZE(expectedMediumBlobBytes)};
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
            const size_t            actualDataCount{A_SIZE(actualData)};
            auto                    mediumBlobValue{std::make_shared<Blob>(actualData, actualDataCount)};

            result = setValueAndCheck(*stuff, mediumBlobValue, expectedMediumBlobBytes, expectedMediumBlobByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            static const DataKind   expectedPlus42Point5Bytes[]
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
            const size_t            expectedPlus42Point5ByteCount{A_SIZE(expectedPlus42Point5Bytes)};
            static const DataKind   expectedMinus42Point5Bytes[]
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
            const size_t            expectedMinus42Point5ByteCount{A_SIZE(expectedMinus42Point5Bytes)};
            auto                    plus42Point5Value{std::make_shared<Double>(42.5)};
            auto                    minus42Point5Value{std::make_shared<Double>(-42.5)};

            result = setValueAndCheck(*stuff, plus42Point5Value, expectedPlus42Point5Bytes,
                                      expectedPlus42Point5ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, minus42Point5Value, expectedMinus42Point5Bytes, expectedMinus42Point5ByteCount);
            }
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedEmptyArrayByteCount{A_SIZE(expectedEmptyArrayBytes)};
            auto                    emptyArray{std::make_shared<Array>()};

            result = setValueAndCheck(*stuff, emptyArray, expectedEmptyArrayBytes, expectedEmptyArrayByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedEmptyMapByteCount{A_SIZE(expectedEmptyMapBytes)};
            auto                    emptyMap{std::make_shared<Map>()};

            result = setValueAndCheck(*stuff, emptyMap, expectedEmptyMapBytes, expectedEmptyMapByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedEmptySetByteCount{A_SIZE(expectedEmptySetBytes)};
            auto                    emptySet{std::make_shared<Set>()};

            result = setValueAndCheck(*stuff, emptySet, expectedEmptySetBytes, expectedEmptySetByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneLogicalByteCount{A_SIZE(expectedArrayOneLogicalBytes)};
            auto                    arrayOneLogical{std::make_shared<Array>()};

            arrayOneLogical->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayOneLogical, expectedArrayOneLogicalBytes, expectedArrayOneLogicalByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneIntegerByteCount{A_SIZE(expectedArrayOneIntegerBytes)};
            auto                    arrayOneInteger{std::make_shared<Array>()};

            arrayOneInteger->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayOneInteger, expectedArrayOneIntegerBytes, expectedArrayOneIntegerByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneDoubleByteCount{A_SIZE(expectedArrayOneDoubleBytes)};
            auto                    arrayOneDouble{std::make_shared<Array>()};

            arrayOneDouble->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayOneDouble, expectedArrayOneDoubleBytes, expectedArrayOneDoubleByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneStringByteCount{A_SIZE(expectedArrayOneStringBytes)};
            auto                    arrayOneString{std::make_shared<Array>()};

            arrayOneString->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayOneString, expectedArrayOneStringBytes, expectedArrayOneStringByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneBlobByteCount{A_SIZE(expectedArrayOneBlobBytes)};
            auto                    arrayOneBlob{std::make_shared<Array>()};

            arrayOneBlob->addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayOneBlob, expectedArrayOneBlobBytes, expectedArrayOneBlobByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneArrayByteCount{A_SIZE(expectedArrayOneArrayBytes)};
            auto                    arrayOneArray{std::make_shared<Array>()};

            arrayOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneArray, expectedArrayOneArrayBytes, expectedArrayOneArrayByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneMapByteCount{A_SIZE(expectedArrayOneMapBytes)};
            auto                    arrayOneMap{std::make_shared<Array>()};

            arrayOneMap->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneMap, expectedArrayOneMapBytes, expectedArrayOneMapByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneSetByteCount{A_SIZE(expectedArrayOneSetBytes)};
            auto                    arrayOneSet{std::make_shared<Array>()};

            arrayOneSet->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneSet, expectedArrayOneSetBytes, expectedArrayOneSetByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoLogicalsByteCount{A_SIZE(expectedArrayTwoLogicalsBytes)};
            auto                    arrayTwoLogicals{std::make_shared<Array>()};

            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayTwoLogicals, expectedArrayTwoLogicalsBytes, expectedArrayTwoLogicalsByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoIntegersByteCount{A_SIZE(expectedArrayTwoIntegersBytes)};
            auto                    arrayTwoIntegers{std::make_shared<Array>()};

            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayTwoIntegers, expectedArrayTwoIntegersBytes, expectedArrayTwoIntegersByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoDoublesByteCount{A_SIZE(expectedArrayTwoDoublesBytes)};
            auto                    arrayTwoDoubles{std::make_shared<Array>()};

            arrayTwoDoubles->addValue(std::make_shared<Double>());
            arrayTwoDoubles->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayTwoDoubles, expectedArrayTwoDoublesBytes, expectedArrayTwoDoublesByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoStringsByteCount{A_SIZE(expectedArrayTwoStringsBytes)};
            auto                    arrayTwoStrings{std::make_shared<Array>()};

            arrayTwoStrings->addValue(std::make_shared<String>());
            arrayTwoStrings->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayTwoStrings, expectedArrayTwoStringsBytes, expectedArrayTwoStringsByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoBlobsByteCount{A_SIZE(expectedArrayTwoBlobsBytes)};
            auto                    arrayTwoBlobs{std::make_shared<Array>()};

            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayTwoBlobs, expectedArrayTwoBlobsBytes, expectedArrayTwoBlobsByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoArraysByteCount{A_SIZE(expectedArrayTwoArraysBytes)};
            auto                    arrayTwoArrays{std::make_shared<Array>()};

            arrayTwoArrays->addValue(std::make_shared<Array>());
            arrayTwoArrays->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayTwoArrays, expectedArrayTwoArraysBytes, expectedArrayTwoArraysByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoMapsByteCount{A_SIZE(expectedArrayTwoMapsBytes)};
            auto                    arrayTwoMaps{std::make_shared<Array>()};

            arrayTwoMaps->addValue(std::make_shared<Map>());
            arrayTwoMaps->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayTwoMaps, expectedArrayTwoMapsBytes, expectedArrayTwoMapsByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayTwoSetsByteCount{A_SIZE(expectedArrayTwoSetsBytes)};
            auto                    arrayTwoSets{std::make_shared<Array>()};

            arrayTwoSets->addValue(std::make_shared<Set>());
            arrayTwoSets->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayTwoSets, expectedArrayTwoSetsBytes, expectedArrayTwoSetsByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneArrayOneMapByteCount{A_SIZE(expectedArrayOneArrayOneMapBytes)};
            auto                    arrayOneArrayOneMap{std::make_shared<Array>()};

            arrayOneArrayOneMap->addValue(std::make_shared<Array>());
            arrayOneArrayOneMap->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneArrayOneMap, expectedArrayOneArrayOneMapBytes, expectedArrayOneArrayOneMapByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneMapOneSetByteCount{A_SIZE(expectedArrayOneMapOneSetBytes)};
            auto                    arrayOneMapOneSet{std::make_shared<Array>()};

            arrayOneMapOneSet->addValue(std::make_shared<Map>());
            arrayOneMapOneSet->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneMapOneSet, expectedArrayOneMapOneSetBytes, expectedArrayOneMapOneSetByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedArrayOneSetOneArrayByteCount{A_SIZE(expectedArrayOneSetOneArrayBytes)};
            auto                    arrayOneSetOneArray{std::make_shared<Array>()};

            arrayOneSetOneArray->addValue(std::make_shared<Set>());
            arrayOneSetOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneSetOneArray, expectedArrayOneSetOneArrayBytes, expectedArrayOneSetOneArrayByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            const size_t            numValues = 43;
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
            const size_t            expectedArrayManyDoublesByteCount{A_SIZE(expectedArrayManyDoublesBytes)};
            auto                    arrayManyDoubles{std::make_shared<Array>()};

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles->addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = setValueAndCheck(*stuff, arrayManyDoubles, expectedArrayManyDoublesBytes, expectedArrayManyDoublesByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedLogicalMapByteCount{A_SIZE(expectedLogicalMapBytes)};
            auto                    logicalMap{std::make_shared<Map>()};

            logicalMap->addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, logicalMap, expectedLogicalMapBytes, expectedLogicalMapByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedIntegerMapByteCount{A_SIZE(expectedIntegerMapBytes)};
            auto                    integerMap{std::make_shared<Map>()};

            integerMap->addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, integerMap, expectedIntegerMapBytes, expectedIntegerMapByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedStringMapByteCount{A_SIZE(expectedStringMapBytes)};
            auto                    stringMap{std::make_shared<Map>()};

            stringMap->addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, stringMap, expectedStringMapBytes, expectedStringMapByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedLogicalSetByteCount{A_SIZE(expectedLogicalSetBytes)};
            auto                    logicalSet{std::make_shared<Set>()};

            logicalSet->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, logicalSet, expectedLogicalSetBytes, expectedLogicalSetByteCount);
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
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
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
            const size_t            expectedIntegerSetByteCount{A_SIZE(expectedIntegerSetBytes)};
            auto                    integerSet{std::make_shared<Set>()};

            integerSet->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, integerSet, expectedIntegerSetBytes, expectedIntegerSetByteCount);
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
doTestInsertStringSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        auto    stuff{std::make_unique<Message>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            static const DataKind   expectedStringSetBytes[]
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
            const size_t            expectedStringSetByteCount{A_SIZE(expectedStringSetBytes)};
            auto                    stringSet{std::make_shared<Set>()};

            stringSet->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, stringSet, expectedStringSetBytes, expectedStringSetByteCount);
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestInsertStringSetMessage

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
    nImO::ReportVersions();
    try
    {
        nImO::TestContext   ourContext{progName};

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
                if (0 != result)
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // main

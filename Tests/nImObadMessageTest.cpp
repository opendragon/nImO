//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImObadMessageTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2017 by OpenDragon.
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
//  Created:    2017-03-06
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOblob.h>
#include <BasicTypes/nImOdouble.h>
#include <BasicTypes/nImOflaw.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
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
    ODL_I1("signal = ", signal); //####
    auto    message{"exiting due to signal "s + std::to_string(signal) + " = "s + NameOfSignal(signal)};

    NIMO_UNUSED_VAR_(message);
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

/*! @brief Extract a Value from a Message and verify what was stored.
 @param[in,out] stuff The Message to be modified.
 @param[in] insertedContents The data to be added to the Message.
 @param[in] insertedSize The size of the data added to the Message.
 @param[in] expectedFlawString The expected Flaw result from the Message.
 @return Zero on success and non-zero on failure. */
static int
attemptExtractValueAndCheck
    (Message &              stuff,
     CPtr(DataKind)         insertedContents,
     const size_t           insertedSize,
     const std::string &    expectedFlawString)
{
    ODL_ENTER(); //####
    ODL_P2("stuff = ", &stuff, "insertedContents = ", insertedContents); //####
    ODL_I1("insertedSize = ", insertedSize); //####
    ODL_S1s("expectedFlawString = ", expectedFlawString); //####
    ODL_PACKET("inserted", insertedContents, insertedSize); //####
    int result{1};

    stuff.open(false);
    stuff.appendBytes(insertedContents, insertedSize);
    auto    extractedValue{stuff.getValue()};

    ODL_P1("extractedValue <- ", extractedValue.get()); //####
    stuff.close();
    if (nullptr == extractedValue)
    {
        ODL_LOG("(nullptr == extractedValue)"); //####
    }
    else
    {
        auto    asFlaw{extractedValue->asFlaw()};

        if (nullptr != asFlaw)
        {
            ODL_LOG(asFlaw->getDescription().c_str()); //####
            if (asFlaw->getDescription() == expectedFlawString)
            {
                ODL_LOG("(asFlaw->getDescription() == expectedFlawString)"); //####
                result = 0;
            }
            stuff.reset();
        }
    }
    ODL_EXIT_I(result); //####
    return result;
} // attemptExtractValueAndCheck

#if defined(__APPLE__)
# pragma mark *** Test Case 001 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMessageInitialEndTag
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
            ODL_LOG("! (nullptr == stuff)"); //####
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with incorrect start tag @0d/0x0");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMessageInitialEndTag

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMessageTerminalStartTag
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Message with incorrect end tag @1d/0x1");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMessageTerminalStartTag

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMessageWithContent
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Message with incorrect end tag @1d/0x1");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMessageWithContent

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithoutContent
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with mismatched initial Value tag @1d/0x1");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithoutContent

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithMismatchedInitialStartTag
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with mismatched initial Value tag @1d/0x1");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithMismatchedInitialStartTag

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithMismatchedTerminalEndTag
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
            static const DataKind   bytesToInsert[]
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
                  DataKind::OtherMessageExpectedIntegerValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with mismatched end Value tag @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithMismatchedTerminalEndTag

#if defined(__APPLE__)
# pragma mark *** Test Case 007 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithInvalidContentTag
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Invalid
                DataKind::EscapeValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1d/0x1");
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
doTestNonEmptyMessageWithZeroDoubleCount
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((0 - kDataKindDoubleShortCountMinValue) &
                  DataKind::DoubleShortCountMask),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Bad count for Double @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithZeroDoubleCount

#if defined(__APPLE__)
# pragma mark *** Test Case 009 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithStringWithInvalidLength
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
            static const DataKind   bytesToInsert[]
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
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Null Value read @4d/0x4");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithStringWithInvalidLength

#if defined(__APPLE__)
# pragma mark *** Test Case 010 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithBlobWithInvalidLength
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobLongLengthValue |
                  ((1 - 1) & DataKind::StringOrBlobLongLengthMask),
                StaticCast(DataKind, 42),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Null Value read @4d/0x4");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithBlobWithInvalidLength

#if defined(__APPLE__)
# pragma mark *** Test Case 020 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithArrayWithInitialEndTag
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerEnd |
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1d/0x1");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTTestNonEmptyMessageWithArrayWithInitialEndTag

#if defined(__APPLE__)
# pragma mark *** Test Case 021 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithArrayWithTerminalStartTag
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
            static const DataKind   bytesToInsert[]
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
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Array with incorrect end tag @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithArrayWithTerminalStartTag

#if defined(__APPLE__)
# pragma mark *** Test Case 022 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithEmptyArrayWithContent
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Array with incorrect end tag @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithEmptyArrayWithContent

#if defined(__APPLE__)
# pragma mark *** Test Case 023 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyArrayWithoutContent
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
            static const DataKind   bytesToInsert[]
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
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @3d/0x3");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyArrayWithoutContent

#if defined(__APPLE__)
# pragma mark *** Test Case 024 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyArrayWithInvalidCount
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
            static const DataKind   bytesToInsert[]
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
                StaticCast(DataKind, 0 + kDataKindIntegerShortValueMinValue - 1),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Array with zero or negative count @4d/0x4");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyArrayWithInvalidCount

#if defined(__APPLE__)
# pragma mark *** Test Case 025 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyArrayWithTooFewValues
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
            static const DataKind   bytesToInsert[]
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
                  ((3 + kDataKindIntegerShortValueMinValue - 1) &
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @5d/0x5");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyArrayWithTooFewValues

#if defined(__APPLE__)
# pragma mark *** Test Case 026 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyArrayWithTooManyValues
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
            static const DataKind   bytesToInsert[]
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Non-empty Array with incorrect end tag @5d/0x5");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyArrayWithTooManyValues

#if defined(__APPLE__)
# pragma mark *** Test Case 027 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyArrayWithTooManyDoubles
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
            static const DataKind   bytesToInsert[]
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
                DataKind::Double | DataKind::DoubleLongCount |
                  ((1 - 1) & DataKind::DoubleLongCountMask),
                StaticCast(DataKind, 3),
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Non-empty Array with incorrect end tag @29d/0x1d");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyArrayWithTooManyDoubles

#if defined(__APPLE__)
# pragma mark *** Test Case 040 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithMapWithInitialEndTag
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerEnd |
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1d/0x1");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithMapWithInitialEndTag

#if defined(__APPLE__)
# pragma mark *** Test Case 041 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithMapWithTerminalStartTag
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
            static const DataKind   bytesToInsert[]
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
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Map with incorrect end tag @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithMapWithTerminalStartTag

#if defined(__APPLE__)
# pragma mark *** Test Case 042 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithEmptyMapWithContent
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Map with incorrect end tag @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithEmptyMapWithContent

#if defined(__APPLE__)
# pragma mark *** Test Case 043 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyMapWithoutContent
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
            static const DataKind   bytesToInsert[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @3d/0x3");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyMapWithoutContent

#if defined(__APPLE__)
# pragma mark *** Test Case 044 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyMapWithInvalidCount
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
            static const DataKind   bytesToInsert[]
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
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((1 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0 + kDataKindIntegerShortValueMinValue - 1),
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Map with zero or negative count @4d/0x4");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyMapWithInvalidCount

#if defined(__APPLE__)
# pragma mark *** Test Case 045 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyMapWithTooFewValues
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
            static const DataKind   bytesToInsert[]
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
                  ((3 + kDataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalTrueValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalTrueValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @7d/0x7");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyMapWithTooFewValues

#if defined(__APPLE__)
# pragma mark *** Test Case 046 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyMapWithTooManyValues
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
            static const DataKind   bytesToInsert[]
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
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalTrueValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalTrueValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Non-empty Map with incorrect end tag @5d/0x5");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyMapWithTooManyValues

#if defined(__APPLE__)
# pragma mark *** Test Case 047 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptyMapWithIncompletePair
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
            static const DataKind   bytesToInsert[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalTrueValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @6d/0x6");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptyMapWithIncompletePair

#if defined(__APPLE__)
# pragma mark *** Test Case 060 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithSetWithInitialEndTag
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerEnd |
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1d/0x1");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTTestNonEmptyMessageWithSetWithInitialEndTag

#if defined(__APPLE__)
# pragma mark *** Test Case 061 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithSetWithTerminalStartTag
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
            static const DataKind   bytesToInsert[]
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
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Set with incorrect end tag @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithSetWithTerminalStartTag

#if defined(__APPLE__)
# pragma mark *** Test Case 062 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithEmptySetWithContent
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
            static const DataKind   bytesToInsert[]
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Set with incorrect end tag @2d/0x2");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithEmptySetWithContent

#if defined(__APPLE__)
# pragma mark *** Test Case 063 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptySetWithoutContent
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
            static const DataKind   bytesToInsert[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @3d/0x3");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptySetWithoutContent

#if defined(__APPLE__)
# pragma mark *** Test Case 064 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptySetWithInvalidCount
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
            static const DataKind   bytesToInsert[]
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
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((1 - 1) & DataKind::IntegerLongValueCountMask),
                StaticCast(DataKind, 0 + kDataKindIntegerShortValueMinValue - 1),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Set with zero or negative count @4d/0x4");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptySetWithInvalidCount

#if defined(__APPLE__)
# pragma mark *** Test Case 065 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptySetWithTooFewValues
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
            static const DataKind   bytesToInsert[]
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
                  ((3 + kDataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @5d/0x5");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptySetWithTooFewValues

#if defined(__APPLE__)
# pragma mark *** Test Case 066 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMessageWithNonEmptySetWithTooManyValues
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
            static const DataKind   bytesToInsert[]
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
                  ((2 + kDataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeLogical |
                  DataKind::OtherMiscellaneousLogicalFalseValue,
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
            constexpr size_t    insertionCount{numElementsInArray(bytesToInsert)};

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @6d/0x6");
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMessageWithNonEmptySetWithTooManyValues

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
    int         result = 1;

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
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
                        result = doTestMessageInitialEndTag(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestMessageTerminalStartTag(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestEmptyMessageWithContent(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestNonEmptyMessageWithoutContent(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestNonEmptyMessageWithMismatchedInitialStartTag(*argv, argc - 1, argv + 2);
                        break;

                    case 6 :
                        result = doTestNonEmptyMessageWithMismatchedTerminalEndTag(*argv, argc - 1, argv + 2);
                        break;

                    case 7 :
                        result = doTestNonEmptyMessageWithInvalidContentTag(*argv, argc - 1, argv + 2);
                        break;

                    case 8 :
                        result = doTestNonEmptyMessageWithZeroDoubleCount(*argv, argc - 1, argv + 2);
                        break;

                    case 9 :
                        result = doTestNonEmptyMessageWithStringWithInvalidLength(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestNonEmptyMessageWithBlobWithInvalidLength(*argv, argc - 1, argv + 2);
                        break;

                    case 20 :
                        result = doTestNonEmptyMessageWithArrayWithInitialEndTag(*argv, argc - 1, argv + 2);
                        break;

                    case 21 :
                        result = doTestNonEmptyMessageWithArrayWithTerminalStartTag(*argv, argc - 1, argv + 2);
                        break;

                    case 22 :
                        result = doTestNonEmptyMessageWithEmptyArrayWithContent(*argv, argc - 1, argv + 2);
                        break;

                    case 23 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithoutContent(*argv, argc - 1, argv + 2);
                        break;

                    case 24 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithInvalidCount(*argv, argc - 1, argv + 2);
                        break;

                    case 25 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithTooFewValues(*argv, argc - 1, argv + 2);
                        break;

                    case 26 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithTooManyValues(*argv, argc - 1, argv + 2);
                        break;

                    case 27 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithTooManyDoubles(*argv, argc - 1, argv + 2);
                        break;

                    case 40 :
                        result = doTestNonEmptyMessageWithMapWithInitialEndTag(*argv, argc - 1, argv + 2);
                        break;

                    case 41 :
                        result = doTestNonEmptyMessageWithMapWithTerminalStartTag(*argv, argc - 1, argv + 2);
                        break;

                    case 42 :
                        result = doTestNonEmptyMessageWithEmptyMapWithContent(*argv, argc - 1, argv + 2);
                        break;

                    case 43 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithoutContent(*argv, argc - 1, argv + 2);
                        break;

                    case 44 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithInvalidCount(*argv, argc - 1, argv + 2);
                        break;

                    case 45 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithTooFewValues(*argv, argc - 1, argv + 2);
                        break;

                    case 46 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithTooManyValues(*argv, argc - 1, argv + 2);
                        break;

                    case 47 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithIncompletePair(*argv, argc - 1, argv + 2);
                        break;

                    case 60 :
                        result = doTestNonEmptyMessageWithSetWithInitialEndTag(*argv, argc - 1, argv + 2);
                        break;

                    case 61 :
                        result = doTestNonEmptyMessageWithSetWithTerminalStartTag(*argv, argc - 1, argv + 2);
                        break;

                    case 62 :
                        result = doTestNonEmptyMessageWithEmptySetWithContent(*argv, argc - 1, argv + 2);
                        break;

                    case 63 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithoutContent(*argv, argc - 1, argv + 2);
                        break;

                    case 64 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithInvalidCount(*argv, argc - 1, argv + 2);
                        break;

                    case 65 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithTooFewValues(*argv, argc - 1, argv + 2);
                        break;

                    case 66 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithTooManyValues(*argv, argc - 1, argv + 2);
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

//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOMIMEAndMessagesTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2022 by OpenDragon.
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
//  Created:    2022-12-05
//
//--------------------------------------------------------------------------------------------------

#include <nImOarray.h>
#include <nImOblob.h>
#include <nImObufferChunk.h>
#include <nImOdouble.h>
#include <nImOflaw.h>
#include <nImOinteger.h>
#include <nImOlogical.h>
#include <nImOmap.h>
#include <nImOmessage.h>
#include <nImOMIMESupport.h>
#include <nImOset.h>
#include <nImOstring.h>
#include <nImOstringBuffer.h>
#include <nImOtestContext.h>

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
    std::string message{"Exiting due to signal "};

    message += std::to_string(signal);
    message += " = ";
    message += NameOfSignal(signal);
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
    (Message &          stuff,
     SpValue            aValue,
     CPtr(std::string)  expectedContents,
     const size_t       expectedSize)
{
    ODL_ENTER(); //####
    ODL_P3("stuff = ", &stuff, "aValue = ", aValue, "expectedContents = ", expectedContents); //####
    ODL_I1("expectedSize = ", expectedSize); //####
    stuff.open(true);
    stuff.setValue(aValue);
    stuff.close();
    int     result = 1;

    if (0 < stuff.getLength())
    {
        auto    asString{stuff.getBytes()};

        if (0 < asString.length())
        {
            StringVector    outVec;

            EncodeBytesAsMIME(outVec, asString);
            if (expectedSize == outVec.size())
            {
                result = 0;
                for (size_t ii = 0; (0 == result) && (ii < expectedSize); ++ii)
                {
                    if (expectedContents[ii] != outVec[ii])
                    {
                        ODL_LOG("(expectedContents[ii] != outVec[ii])"); //####
                        result = 1;
                    }
                }
            }
            else
            {
                ODL_LOG("! (expectedSize == outVec.size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < asString.length())"); //####
        }
    }
    else
    {
        ODL_LOG("! (0 < stuff.getLength())"); //####
    }
    ODL_EXIT_I(result); //####
    return result;
} // setValueAndCheck

/*! @brief Extract a Value from a Message and verify what was stored.
 @param[in,out] stuff The Message to be modified.
 @param[in] insertedContents The data to be added to the Message.
 @param[in] insertedSize The size of the data added to the Message.
 @param[in] expectedValue The expected Value from the Message.
 @return Zero on success and non-zero on failure. */
static int
extractValueAndCheck
    (Message &          stuff,
     CPtr(std::string)  insertedContents,
     const size_t       insertedSize,
     const Value &      expectedValue)
{
    ODL_ENTER(); //####
    ODL_P3("stuff = ", &stuff, "insertedContents = ", insertedContents, "expectedValue = ", //####
           &expectedValue); //####
    ODL_I1("insertedSize = ", insertedSize); //####
    ODL_PACKET("inserted", insertedContents, insertedSize); //####
    int             result = 1;
    StringVector    inVec;
    ByteVector      outBytes;

    for (size_t ii = 0; ii < insertedSize; ++ii)
    {
        inVec.push_back(insertedContents[ii]);
    }
    if (DecodeMIMEToBytes(inVec, outBytes))
    {
        if (0 < outBytes.size())
        {
            stuff.open(false);
            stuff.appendBytes(outBytes.data(), outBytes.size());
            SpValue extractedValue{stuff.getValue()};

            ODL_P1("extractedValue <- ", extractedValue.get()); //####
            stuff.close();
            if (stuff.readAtEnd())
            {
                if (nullptr == extractedValue)
                {
                    ODL_LOG("(nullptr == extractedValue)"); //####
                }
                else
                {
                    CPtr(Flaw)    asFlaw = extractedValue->asFlaw();

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
            }
            else
            {
                ODL_LOG("! (stuff->readAtEnd())"); //####
            }
            stuff.reset();
        }
        else
        {
            ODL_LOG("! (0 < outBytes.size())"); //####
        }
    }
    else
    {
        ODL_LOG("! (DecodeMIMEToBytes(inVec, outBytes))"); //####
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
doTestMIMEInsertEmptyMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            stuff->open(true);
            stuff->close();
            if (0 < stuff->getLength())
            {
                auto    asString{stuff->getBytes()};

                if (0 < asString.length())
                {
                    std::string     expectedLines[]{ "8Pg=" };
                    const size_t    expectedLinesCount{A_SIZE(expectedLines)};
                    StringVector    outVec;

                    EncodeBytesAsMIME(outVec, asString);
                    if (expectedLinesCount == outVec.size())
                    {
                        result = 0;
                        for (size_t ii = 0; (0 == result) && (ii < expectedLinesCount); ++ii)
                        {
                            if (expectedLines[ii] != outVec[ii])
                            {
                                ODL_LOG("(expectedLines[ii] != outVec[ii])"); //####
                                result = 1;
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (expectedLinesCount == outVec.size())"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (0 < asString.length())"); //####
                }
            }
            else
            {
                ODL_LOG("! (0 < stuff->getLength())"); //####
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
} // doTestMIMEInsertEmptyMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractEmptyMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            ODL_LOG("(stuff)"); //####
            StringVector    inVec;
            ByteVector      outBytes;

            inVec.push_back("8Pg=");
            if (DecodeMIMEToBytes(inVec, outBytes))
            {
                if (0 < outBytes.size())
                {
                    stuff->open(false);
                    stuff->appendBytes(outBytes.data(), outBytes.size());
                    SpValue extractedValue{stuff->getValue()};

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
                            CPtr(Flaw)    asFlaw = extractedValue->asFlaw();

                            if (nullptr != asFlaw)
                            {
                                ODL_LOG("(nullptr != asFlaw)"); //####
                                ODL_LOG(asFlaw->getDescription().c_str()); //####
                            }
                            else
                            {
                                ODL_LOG("! (nullptr != asFlaw)"); //####
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (stuff->readAtEnd())"); //####
                    }
                    stuff->reset();
                }
                else
                {
                    ODL_LOG("! (0 < outBytes.size())"); //####
                }
            }
            else
            {
                ODL_LOG("! (DecodeMIMEToBytes(inVec, outBytes))"); //####
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
} // doTestMIMEExtractEmptyMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertLogicalMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         falseValue{new Logical(false)};
            SpValue         trueValue{new Logical(true)};
            std::string     expectedTrueLines[]{ "98H/" };
            const size_t    expectedTrueLinesCount{A_SIZE(expectedTrueLines)};
            std::string     expectedFalseLines[]{ "98D/" };
            const size_t    expectedFalseLinesCount{A_SIZE(expectedFalseLines)};

            result = setValueAndCheck(*stuff, trueValue, expectedTrueLines, expectedTrueLinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, falseValue, expectedFalseLines, expectedFalseLinesCount);
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
} // doTestMIMEInsertLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractLogicalMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedTrueLines[]{ "98H/" };
            const size_t    insertedTrueLinesCount{A_SIZE(insertedTrueLines)};
            std::string     insertedFalseLines[]{ "98D/" };
            const size_t    insertedFalseLinesCount{A_SIZE(insertedFalseLines)};
            Logical         falseValue(false);
            Logical         trueValue(true);

            result = extractValueAndCheck(*stuff, insertedTrueLines, insertedTrueLinesCount, trueValue);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedFalseLines, insertedFalseLinesCount, falseValue);
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
} // doTestMIMEExtractLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertTinyIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // tiny integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         minus12Value{new Integer(-12)};
            SpValue         zeroValue{new Integer};
            SpValue         plus12Value{new Integer(12)};
            std::string     expectedMinus12Lines[]{ "9BT8" };
            const size_t    expectedMinus12LinesCount{A_SIZE(expectedMinus12Lines)};
            std::string     expectedZeroLines[]{ "9AD8" };
            const size_t    expectedZeroLinesCount{A_SIZE(expectedZeroLines)};
            std::string     expectedPlus12Lines[]{ "9Az8" };
            const size_t    expectedPlus12LinesCount{A_SIZE(expectedPlus12Lines)};

            result = setValueAndCheck(*stuff, minus12Value, expectedMinus12Lines, expectedMinus12LinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, zeroValue, expectedZeroLines, expectedZeroLinesCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus12Value, expectedPlus12Lines, expectedPlus12LinesCount);
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
} // doTestMIMEInsertTinyIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractTinyIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // tiny integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedMinus12Lines[]{ "9BT8" };
            const size_t    insertedMinus12LinesCount{A_SIZE(insertedMinus12Lines)};
            std::string     insertedZeroLines[]{ "9AD8" };
            const size_t    insertedZeroLinesCount{A_SIZE(insertedZeroLines)};
            std::string     insertedPlus12Lines[]{ "9Az8" };
            const size_t    insertedPlus12LinesCount{A_SIZE(insertedPlus12Lines)};
            Integer         minus12Value(-12);
            Integer         zeroValue(0);
            Integer         plus12Value(12);

            result = extractValueAndCheck(*stuff, insertedMinus12Lines, insertedMinus12LinesCount, minus12Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedZeroLines, insertedZeroLinesCount, zeroValue);
            }
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedPlus12Lines, insertedPlus12LinesCount, plus12Value);
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
} // doTestMIMEExtractTinyIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 007 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertSmallIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         minus144Value{new Integer(-144)};
            SpValue         plus144Value{new Integer(144)};
            std::string     expectedMinus144Lines[]{ "9CH/cPw=" };
            const size_t    expectedMinus144LinesCount{A_SIZE(expectedMinus144Lines)};
            std::string     expectedPlus144Lines[]{ "9CEAkPw=" };
            const size_t    expectedPlus144LinesCount{A_SIZE(expectedPlus144Lines)};

            result = setValueAndCheck(*stuff, minus144Value, expectedMinus144Lines, expectedMinus144LinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus144Value, expectedPlus144Lines, expectedPlus144LinesCount);
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
} // doTestMIMEInsertSmallIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 008 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractSmallIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedMinus144Lines[]{ "9CH/cPw=" };
            const size_t    insertedMinus144LinesCount{A_SIZE(insertedMinus144Lines)};
            std::string     insertedPlus144Lines[]{ "9CEAkPw=" };
            const size_t    insertedPlus144LinesCount{A_SIZE(insertedPlus144Lines)};
            Integer         minus144Value(-144);
            Integer         plus144Value(144);

            result = extractValueAndCheck(*stuff, insertedMinus144Lines, insertedMinus144LinesCount, minus144Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedPlus144Lines, insertedPlus144LinesCount, plus144Value);
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
} // doTestMIMEExtractSmallIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 009 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertMediumIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // medium integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         minus1234567Value{new Integer(-1234567)};
            SpValue         plus1234567Value{new Integer(1234567)};
            std::string     expectedMinus1234567Lines[]{ "9CLtKXn8" };
            const size_t    expectedMinus1234567LinesCount{A_SIZE(expectedMinus1234567Lines)};
            std::string     expectedPlus1234567Lines[]{ "9CIS1of8" };
            const size_t    expectedPlus1234567LinesCount{A_SIZE(expectedPlus1234567Lines)};

            result = setValueAndCheck(*stuff, minus1234567Value, expectedMinus1234567Lines,
                                      expectedMinus1234567LinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus1234567Value, expectedPlus1234567Lines,
                                          expectedPlus1234567LinesCount);
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
} // doTestMIMEInsertMediumIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 010 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractMediumIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // medium integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedMinus1234567Lines[]{ "9CLtKXn8" };
            const size_t    insertedMinus1234567LinesCount{A_SIZE(insertedMinus1234567Lines)};
            std::string     insertedPlus1234567Lines[]{ "9CIS1of8" };
            const size_t    insertedPlus1234567LinesCount{A_SIZE(insertedPlus1234567Lines)};
            Integer         minus1234567Value(-1234567);
            Integer         plus1234567Value(1234567);

            result = extractValueAndCheck(*stuff, insertedMinus1234567Lines, insertedMinus1234567LinesCount,
                                          minus1234567Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedPlus1234567Lines, insertedPlus1234567LinesCount,
                                              plus1234567Value);
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
} // doTestMIMEExtractMediumIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 011 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertBigIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // big integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         minusBigNumberValue{new Integer(-20015998343868)};
            SpValue         plusBigNumberValue{new Integer(20015998343868)};
            std::string     expectedMinusBigNumberLines[]{ "9CXty6mHZUT8" };
            const size_t    expectedMinusBigNumberLinesCount{A_SIZE(expectedMinusBigNumberLines)};
            std::string     expectedPlusBigNumberLines[]{ "9CUSNFZ4mrz8" };
            const size_t    expectedPlusBigNumberLinesCount{A_SIZE(expectedPlusBigNumberLines)};

            result = setValueAndCheck(*stuff, minusBigNumberValue, expectedMinusBigNumberLines,
                                      expectedMinusBigNumberLinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plusBigNumberValue, expectedPlusBigNumberLines,
                                          expectedPlusBigNumberLinesCount);
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
} // doTestMIMEInsertBigIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 012 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractBigIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // big integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedMinusBigNumberLines[]{ "9CXty6mHZUT8" };
            const size_t    insertedMinusBigNumberLinesCount{A_SIZE(insertedMinusBigNumberLines)};
            std::string     insertedPlusBigNumberLines[]{ "9CUSNFZ4mrz8" };
            const size_t    insertedPlusBigNumberLinesCount{A_SIZE(insertedPlusBigNumberLines)};
            Integer         minusBigNumberValue(-20015998343868);
            Integer         plusBigNumberValue(20015998343868);

            result = extractValueAndCheck(*stuff, insertedMinusBigNumberLines, insertedMinusBigNumberLinesCount,
                                          minusBigNumberValue);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedPlusBigNumberLines, insertedPlusBigNumberLinesCount,
                                              plusBigNumberValue);
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
} // doTestMIMEExtractBigIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 013 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertEmptyStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         emptyStringValue{new String};
            std::string     expectedEmptyStringLines[]{ "9oD+" };
            const size_t    expectedEmptyStringLinesCount{A_SIZE(expectedEmptyStringLines)};

            result = setValueAndCheck(*stuff, emptyStringValue, expectedEmptyStringLines, expectedEmptyStringLinesCount);
        }
        else
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
} // doTestMIMEInsertEmptyStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 014 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractEmptyStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedEmptyStringLines[]{ "9oD+" };
            const size_t    insertedEmptyStringLinesCount{A_SIZE(insertedEmptyStringLines)};
            String          emptyStringValue;

            result = extractValueAndCheck(*stuff, insertedEmptyStringLines, insertedEmptyStringLinesCount,
                                          emptyStringValue);
        }
        else
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
} // doTestMIMEExtractEmptyStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 015 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertShortStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // short string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         shortStringValue{new String("abcdef")};
            std::string     expectedShortStringLines[]{ "9oZhYmNkZWb+" };
            const size_t    expectedShortStringLinesCount{A_SIZE(expectedShortStringLines)};

            result = setValueAndCheck(*stuff, shortStringValue, expectedShortStringLines,
                                      expectedShortStringLinesCount);
        }
        else
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
} // doTestMIMEInsertShortStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 016 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractShortStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // short string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedShortStringLines[]{ "9oZhYmNkZWb+" };
            const size_t    insertedShortStringLinesCount{A_SIZE(insertedShortStringLines)};
            String          shortStringValue("abcdef");

            result = extractValueAndCheck(*stuff, insertedShortStringLines, insertedShortStringLinesCount,
                                          shortStringValue);
        }
        else
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
} // doTestMIMEExtractShortStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 017 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertMediumStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // medium string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         mediumStringValue{new String("abcdefabcdefabcdefabcdefabcdefabcdefabcdef")};
            std::string     expectedMediumStringLines[]{
                                                "9pAqYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVm/g==" };
            const size_t    expectedMediumStringLinesCount{A_SIZE(expectedMediumStringLines)};

            result = setValueAndCheck(*stuff, mediumStringValue, expectedMediumStringLines,
                                      expectedMediumStringLinesCount);
        }
        else
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
} // doTestMIMEInsertMediumStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 018 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractMediumStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // medium string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedMediumStringLines[]{
                                                "9pAqYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVm/g==" };
            const size_t    insertedMediumStringLinesCount{A_SIZE(insertedMediumStringLines)};
            String          mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

            result = extractValueAndCheck(*stuff, insertedMediumStringLines, insertedMediumStringLinesCount,
                                          mediumStringValue);
        }
        else
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
} // doTestMIMEExtractMediumStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 019 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertEmptyBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         emptyBlobValue{new Blob};
            std::string     expectedEmptyBlobLines[]{ "9qD+" };
            const size_t    expectedEmptyBlobLinesCount{A_SIZE(expectedEmptyBlobLines)};

            result = setValueAndCheck(*stuff, emptyBlobValue, expectedEmptyBlobLines, expectedEmptyBlobLinesCount);
        }
        else
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
} // doTestMIMEInsertEmptyBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 020 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractEmptyBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedEmptyBlobLines[]{ "9qD+" };
            const size_t    insertedEmptyBlobLinesCount{A_SIZE(insertedEmptyBlobLines)};
            Blob            emptyBlobValue;

            result = extractValueAndCheck(*stuff, insertedEmptyBlobLines, insertedEmptyBlobLinesCount, emptyBlobValue);
        }
        else
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
} // doTestMIMEExtractEmptyBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 021 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertSmallBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t            actualDataCount{A_SIZE(actualData)};
            SpValue                 smallBlobValue{ new Blob(actualData, actualDataCount)};
            std::string             expectedSmallBlobLines[]{ "9qYSIzRFVmf+" };
            const size_t            expectedSmallBlobLinesCount{A_SIZE(expectedSmallBlobLines)};

            result = setValueAndCheck(*stuff, smallBlobValue, expectedSmallBlobLines, expectedSmallBlobLinesCount);
        }
        else
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
} // doTestMIMEInsertSmallBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 022 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractSmallBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string             insertedSmallBlobLines[]{ "9qYSIzRFVmf+" };
            const size_t            insertedSmallBlobLinesCount{A_SIZE(insertedSmallBlobLines)};
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t            actualDataCount{A_SIZE(actualData)};
            Blob                    smallBlobValue(actualData, actualDataCount);

            result = extractValueAndCheck(*stuff, insertedSmallBlobLines, insertedSmallBlobLinesCount, smallBlobValue);
        }
        else
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
} // doTestMIMEExtractSmallBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 023 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertMediumBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // medium blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
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
            SpValue                 mediumBlobValue{new Blob(actualData, actualDataCount)};
            std::string             expectedMediumBlobLines[]{
                                                "9rAqEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZn/g==" };
            const size_t            expectedMediumBlobLinesCount{A_SIZE(expectedMediumBlobLines)};

            result = setValueAndCheck(*stuff, mediumBlobValue, expectedMediumBlobLines, expectedMediumBlobLinesCount);
        }
        else
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
} // doTestMIMEInsertMediumBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 024 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractMediumBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // medium blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string             insertedMediumBlobLines[]{
                                                "9rAqEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZn/g==" };
            const size_t            insertedMediumBlobLinesCount{A_SIZE(insertedMediumBlobLines)};
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
            Blob                    mediumBlobValue(actualData, actualDataCount);

            result = extractValueAndCheck(*stuff, insertedMediumBlobLines, insertedMediumBlobLinesCount,
                                          mediumBlobValue);
        }
        else
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
} // doTestMIMEExtractMediumBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 025 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertSingleDoubleMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // single double message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         plus42Point5Value{new Double(42.5)};
            SpValue         minus42Point5Value{new Double(-42.5)};
            std::string     expectedPlus42Point5Lines[]{ "9UBARUAAAAAAAP0=" };
            const size_t    expectedPlus42Point5LinesCount{A_SIZE(expectedPlus42Point5Lines)};
            std::string     expectedMinus42Point5Lines[]{ "9UDARUAAAAAAAP0=" };
            const size_t    expectedMinus42Point5LinesCount{A_SIZE(expectedMinus42Point5Lines)};

            result = setValueAndCheck(*stuff, plus42Point5Value, expectedPlus42Point5Lines,
                                      expectedPlus42Point5LinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, minus42Point5Value, expectedMinus42Point5Lines,
                                          expectedMinus42Point5LinesCount);
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
} // doTestMIMEInsertSingleDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 026 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractSingleDoubleMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // single double message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedPlus42Point5Lines[]{ "9UBARUAAAAAAAP0=" };
            const size_t    insertedPlus42Point5LinesCount{A_SIZE(insertedPlus42Point5Lines)};
            std::string     insertedMinus42Point5Lines[]{ "9UDARUAAAAAAAP0=" };
            const size_t    insertedMinus42Point5LinesCount{A_SIZE(insertedMinus42Point5Lines)};
            Double          plus42Point5Value(42.5);
            Double          minus42Point5Value(-42.5);

            result = extractValueAndCheck(*stuff, insertedPlus42Point5Lines, insertedPlus42Point5LinesCount,
                                          plus42Point5Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedMinus42Point5Lines, insertedMinus42Point5LinesCount,
                                              minus42Point5Value);
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
} // doTestMIMEExtractSingleDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertEmptyArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         emptyArray{new Array};
            std::string     expectedEmptyArrayLines[]{ "99Dg/w==" };
            const size_t    expectedEmptyArrayLinesCount{A_SIZE(expectedEmptyArrayLines)};

            result = setValueAndCheck(*stuff, emptyArray, expectedEmptyArrayLines, expectedEmptyArrayLinesCount);
        }
        else
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
} // doTestMIMEInsertEmptyArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractEmptyArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedEmptyArrayLines[]{ "99Dg/w==" };
            const size_t    insertedEmptyArrayLinesCount{A_SIZE(insertedEmptyArrayLines)};
            Array           emptyArray;

            result = extractValueAndCheck(*stuff, insertedEmptyArrayLines, insertedEmptyArrayLinesCount, emptyArray);
        }
        else
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
} // doTestMIMEExtractEmptyArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertEmptyMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         emptyMap{new Map};
            std::string     expectedEmptyMapLines[]{ "99Tk/w==" };
            const size_t    expectedEmptyMapLinesCount{A_SIZE(expectedEmptyMapLines)};

            result = setValueAndCheck(*stuff, emptyMap, expectedEmptyMapLines, expectedEmptyMapLinesCount);
        }
        else
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
} // doTestMIMEInsertEmptyMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 103 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractEmptyMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedEmptyMapLines[]{ "99Tk/w==" };
            const size_t    insertedEmptyMapLinesCount{A_SIZE(insertedEmptyMapLines)};
            Map             emptyMap;

            result = extractValueAndCheck(*stuff, insertedEmptyMapLines, insertedEmptyMapLinesCount, emptyMap);
        }
        else
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
} // doTestMIMEExtractEmptyMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 104 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertEmptySetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpValue         emptySet{new Set};
            std::string     expectedEmptySetLines[]{ "99jo/w==" };
            const size_t    expectedEmptySetLinesCount{A_SIZE(expectedEmptySetLines)};

            result = setValueAndCheck(*stuff, emptySet, expectedEmptySetLines, expectedEmptySetLinesCount);
        }
        else
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
} // doTestMIMEInsertEmptySetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 105 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractEmptySetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedEmptySetLines[]{ "99jo/w==" };
            const size_t    insertedEmptySetLinesCount{A_SIZE(insertedEmptySetLines)};
            Set             emptySet;

            result = extractValueAndCheck(*stuff, insertedEmptySetLines, insertedEmptySetLinesCount, emptySet);
        }
        else
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
} // doTestMIMEExtractEmptySetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 200 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneLogicalMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one logical message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneLogical{new Array};
            std::string     expectedArrayOneLogicalLines[]{ "99EQwOH/" };
            const size_t    expectedArrayOneLogicalLinesCount{A_SIZE(expectedArrayOneLogicalLines)};

            arrayOneLogical->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayOneLogical, expectedArrayOneLogicalLines,
                                      expectedArrayOneLogicalLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 201 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneLogicalMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one logical message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneLogicalLines[]{ "99EQwOH/" };
            const size_t    insertedArrayOneLogicalLinesCount{A_SIZE(insertedArrayOneLogicalLines)};
            Array           arrayOneLogical;

            arrayOneLogical.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedArrayOneLogicalLines, insertedArrayOneLogicalLinesCount,
                                          arrayOneLogical);
        }
        else
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
} // doTestMIMEExtractArrayOneLogicalMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 202 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneInteger{new Array};
            std::string     expectedArrayOneIntegerLines[]{ "99EQAOH/" };
            const size_t    expectedArrayOneIntegerLinesCount{A_SIZE(expectedArrayOneIntegerLines)};

            arrayOneInteger->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayOneInteger, expectedArrayOneIntegerLines,
                                      expectedArrayOneIntegerLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 203 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneIntegerMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one integer message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneIntegerLines[]{ "99EQAOH/" };
            const size_t    insertedArrayOneIntegerLinesCount{A_SIZE(insertedArrayOneIntegerLines)};
            Array           arrayOneInteger;

            arrayOneInteger.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedArrayOneIntegerLines, insertedArrayOneIntegerLinesCount,
                                          arrayOneInteger);
        }
        else
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
} // doTestMIMEExtractArrayOneIntegerMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 204 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneDoubleMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one double message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneDouble{new Array};
            std::string     expectedArrayOneDoubleLines[]{ "99EQQAAAAAAAAAAA4f8=" };
            const size_t    expectedArrayOneDoubleLinesCount{A_SIZE(expectedArrayOneDoubleLines)};

            arrayOneDouble->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayOneDouble, expectedArrayOneDoubleLines,
                                      expectedArrayOneDoubleLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 205 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneDoubleMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one double message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneDoubleLines[]{ "99EQQAAAAAAAAAAA4f8=" };
            const size_t    insertedArrayOneDoubleLinesCount{A_SIZE(insertedArrayOneDoubleLines)};
            Array           arrayOneDouble;

            arrayOneDouble.addValue(std::make_shared<Double>());
            result = extractValueAndCheck(*stuff, insertedArrayOneDoubleLines, insertedArrayOneDoubleLinesCount,
                                          arrayOneDouble);
        }
        else
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
} // doTestMIMEExtractArrayOneDoubleMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 206 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneString{new Array};
            std::string     expectedArrayOneStringLines[]{ "99EQgOH/" };
            const size_t    expectedArrayOneStringLinesCount{A_SIZE(expectedArrayOneStringLines)};

            arrayOneString->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayOneString, expectedArrayOneStringLines,
                                      expectedArrayOneStringLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 207 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneStringMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one string message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneStringLines[]{ "99EQgOH/" };
            const size_t    insertedArrayOneStringLinesCount{A_SIZE(insertedArrayOneStringLines)};
            Array           arrayOneString;

            arrayOneString.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedArrayOneStringLines, insertedArrayOneStringLinesCount,
                                          arrayOneString);
        }
        else
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
} // doTestMIMEExtractArrayOneStringMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 208 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneBlob{new Array};
            std::string     expectedArrayOneBlobLines[]{ "99EQoOH/" };
            const size_t    expectedArrayOneBlobLinesCount{A_SIZE(expectedArrayOneBlobLines)};

            arrayOneBlob->addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayOneBlob, expectedArrayOneBlobLines, expectedArrayOneBlobLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 209 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneBlobMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one blob message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneBlobLines[]{ "99EQoOH/" };
            const size_t    insertedArrayOneBlobLinesCount{A_SIZE(insertedArrayOneBlobLines)};
            Array           arrayOneBlob;

            arrayOneBlob.addValue(std::make_shared<Blob>());
            result = extractValueAndCheck(*stuff, insertedArrayOneBlobLines, insertedArrayOneBlobLinesCount,
                                          arrayOneBlob);
        }
        else
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
} // doTestMIMEExtractArrayOneBlobMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 210 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one array message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneArray{new Array};
            std::string     expectedArrayOneArrayLines[]{ "99EQ0ODh/w==" };
            const size_t    expectedArrayOneArrayLinesCount{A_SIZE(expectedArrayOneArrayLines)};

            arrayOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneArray, expectedArrayOneArrayLines,
                                      expectedArrayOneArrayLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 211 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one array message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneArrayLines[]{ "99EQ0ODh/w==" };
            const size_t    insertedArrayOneArrayLinesCount{A_SIZE(insertedArrayOneArrayLines)};
            Array           arrayOneArray;

            arrayOneArray.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedArrayOneArrayLines, insertedArrayOneArrayLinesCount,
                                          arrayOneArray);
        }
        else
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
} // doTestMIMEExtractArrayOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 212 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneMap{new Array};
            std::string     expectedArrayOneMapLines[]{ "99EQ1OTh/w==" };
            const size_t    expectedArrayOneMapLinesCount{A_SIZE(expectedArrayOneMapLines)};

            arrayOneMap->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneMap, expectedArrayOneMapLines, expectedArrayOneMapLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 213 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneMapLines[]{ "99EQ1OTh/w==" };
            const size_t    insertedArrayOneMapLinesCount{A_SIZE(insertedArrayOneMapLines)};
            Array           arrayOneMap;

            arrayOneMap.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedArrayOneMapLines, insertedArrayOneMapLinesCount, arrayOneMap);
        }
        else
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
} // doTestMIMEExtractArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 214 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneSet{new Array};
            std::string     expectedArrayOneSetLines[]{ "99EQ2Ojh/w==" };
            const size_t    expectedArrayOneSetLinesCount{A_SIZE(expectedArrayOneSetLines)};

            arrayOneSet->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneSet, expectedArrayOneSetLines, expectedArrayOneSetLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 215 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with one set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneSetLines[]{ "99EQ2Ojh/w==" };
            const size_t    insertedArrayOneSetLinesCount{A_SIZE(insertedArrayOneSetLines)};
            Array           arrayOneSet;

            arrayOneSet.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedArrayOneSetLines, insertedArrayOneSetLinesCount, arrayOneSet);
        }
        else
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
} // doTestMIMEExtractArrayOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 300 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoLogicalsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two logicals message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoLogicals{new Array};
            std::string     expectedArrayTwoLogicalsLines[]{ "99ERwMDh/w==" };
            const size_t    expectedArrayTwoLogicalsLinesCount{A_SIZE(expectedArrayTwoLogicalsLines)};

            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayTwoLogicals, expectedArrayTwoLogicalsLines,
                                      expectedArrayTwoLogicalsLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoLogicalsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 301 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoLogicalsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two logicals message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoLogicalsLines[]{ "99ERwMDh/w==" };
            const size_t    insertedArrayTwoLogicalsLinesCount{A_SIZE(insertedArrayTwoLogicalsLines)};
            Array           arrayTwoLogicals;

            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoLogicalsLines, insertedArrayTwoLogicalsLinesCount,
                                          arrayTwoLogicals);
        }
        else
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
} // doTestMIMEExtractArrayTwoLogicalsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 302 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoIntegersMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two integers message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoIntegers{new Array};
            std::string     expectedArrayTwoIntegersLines[]{ "99ERAADh/w==" };
            const size_t    expectedArrayTwoIntegersLinesCount{A_SIZE(expectedArrayTwoIntegersLines)};

            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayTwoIntegers, expectedArrayTwoIntegersLines,
                                      expectedArrayTwoIntegersLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoIntegersMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 303 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoIntegersMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two integers message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoIntegersLines[]{ "99ERAADh/w==" };
            const size_t    insertedArrayTwoIntegersLinesCount{A_SIZE(insertedArrayTwoIntegersLines)};
            Array           arrayTwoIntegers;

            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoIntegersLines, insertedArrayTwoIntegersLinesCount,
                                          arrayTwoIntegers);
        }
        else
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
} // doTestMIMEExtractArrayTwoIntegersMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 304 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoDoublesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two doubles message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoDoubles{new Array};
            std::string     expectedArrayTwoDoublesLines[]{ "99ERQQAAAAAAAAAAAAAAAAAAAADh/w==" };
            const size_t    expectedArrayTwoDoublesLinesCount{A_SIZE(expectedArrayTwoDoublesLines)};

            arrayTwoDoubles->addValue(std::make_shared<Double>());
            arrayTwoDoubles->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayTwoDoubles, expectedArrayTwoDoublesLines,
                                      expectedArrayTwoDoublesLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 305 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoDoublesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two doubles message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoDoublesLines[]{ "99ERQQAAAAAAAAAAAAAAAAAAAADh/w==" };
            const size_t    insertedArrayTwoDoublesLinesCount{A_SIZE(insertedArrayTwoDoublesLines)};
            Array           arrayTwoDoubles;

            arrayTwoDoubles.addValue(std::make_shared<Double>());
            arrayTwoDoubles.addValue(std::make_shared<Double>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoDoublesLines, insertedArrayTwoDoublesLinesCount,
                                          arrayTwoDoubles);
        }
        else
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
} // doTestMIMEExtractArrayTwoDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 306 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoStringsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two strings message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoStrings{new Array};
            std::string     expectedArrayTwoStringsLines[]{ "99ERgIDh/w==" };
            const size_t    expectedArrayTwoStringsLinesCount{A_SIZE(expectedArrayTwoStringsLines)};

            arrayTwoStrings->addValue(std::make_shared<String>());
            arrayTwoStrings->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayTwoStrings, expectedArrayTwoStringsLines,
                                      expectedArrayTwoStringsLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoStringsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 307 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoStringsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two strings message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoStringsLines[]{ "99ERgIDh/w==" };
            const size_t    insertedArrayTwoStringsLinesCount{A_SIZE(insertedArrayTwoStringsLines)};
            Array           arrayTwoStrings;

            arrayTwoStrings.addValue(std::make_shared<String>());
            arrayTwoStrings.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoStringsLines, insertedArrayTwoStringsLinesCount,
                                          arrayTwoStrings);
        }
        else
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
} // doTestMIMEExtractArrayTwoStringsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 308 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoBlobsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two blobs message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoBlobs{new Array};
            std::string     expectedArrayTwoBlobsLines[]{ "99ERoKDh/w==" };
            const size_t    expectedArrayTwoBlobsLinesCount{A_SIZE(expectedArrayTwoBlobsLines)};

            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayTwoBlobs, expectedArrayTwoBlobsLines,
                                      expectedArrayTwoBlobsLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoBlobsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 309 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoBlobsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two blobs message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoBlobsLines[]{ "99ERoKDh/w==" };
            const size_t    insertedArrayTwoBlobsLinesCount{A_SIZE(insertedArrayTwoBlobsLines)};
            Array           arrayTwoBlobs;

            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoBlobsLines, insertedArrayTwoBlobsLinesCount,
                                          arrayTwoBlobs);
        }
        else
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
} // doTestMIMEExtractArrayTwoBlobsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 310 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoArraysMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two arrays message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoArrays{new Array};
            std::string     expectedArrayTwoArraysLines[]{ "99ER0ODQ4OH/" };
            const size_t    expectedArrayTwoArraysLinesCount{A_SIZE(expectedArrayTwoArraysLines)};

            arrayTwoArrays->addValue(std::make_shared<Array>());
            arrayTwoArrays->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayTwoArrays, expectedArrayTwoArraysLines,
                                      expectedArrayTwoArraysLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoArraysMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 311 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoArraysMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two arrays message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoArraysLines[]{ "99ER0ODQ4OH/" };
            const size_t    insertedArrayTwoArraysLinesCount{A_SIZE(insertedArrayTwoArraysLines)};
            Array           arrayTwoArrays;

            arrayTwoArrays.addValue(std::make_shared<Array>());
            arrayTwoArrays.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoArraysLines, insertedArrayTwoArraysLinesCount,
                                          arrayTwoArrays);
        }
        else
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
} // doTestMIMEExtractArrayTwoArraysMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 312 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoMapsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two maps message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoMaps{new Array};
            std::string     expectedArrayTwoMapsLines[]{ "99ER1OTU5OH/" };
            const size_t    expectedArrayTwoMapsLinesCount{A_SIZE(expectedArrayTwoMapsLines)};

            arrayTwoMaps->addValue(std::make_shared<Map>());
            arrayTwoMaps->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayTwoMaps, expectedArrayTwoMapsLines, expectedArrayTwoMapsLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoMapsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 313 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoMapsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two maps message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoMapsLines[]{ "99ER1OTU5OH/" };
            const size_t    insertedArrayTwoMapsLinesCount{A_SIZE(insertedArrayTwoMapsLines)};
            Array           arrayTwoMaps;

            arrayTwoMaps.addValue(std::make_shared<Map>());
            arrayTwoMaps.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoMapsLines, insertedArrayTwoMapsLinesCount,
                                          arrayTwoMaps);
        }
        else
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
} // doTestMIMEExtractArrayTwoMapsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 314 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayTwoSetsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two sets message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayTwoSets{new Array};
            std::string     expectedArrayTwoSetsLines[]{ "99ER2OjY6OH/" };
            const size_t    expectedArrayTwoSetsLinesCount{A_SIZE(expectedArrayTwoSetsLines)};

            arrayTwoSets->addValue(std::make_shared<Set>());
            arrayTwoSets->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayTwoSets, expectedArrayTwoSetsLines, expectedArrayTwoSetsLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayTwoSetsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 315 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayTwoSetsMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with two sets message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayTwoSetsLines[]{ "99ER2OjY6OH/" };
            const size_t    insertedArrayTwoSetsLinesCount{A_SIZE(insertedArrayTwoSetsLines)};
            Array           arrayTwoSets;

            arrayTwoSets.addValue(std::make_shared<Set>());
            arrayTwoSets.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoSetsLines, insertedArrayTwoSetsLinesCount,
                                          arrayTwoSets);
        }
        else
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
} // doTestMIMEExtractArrayTwoSetsMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 316 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneArrayOneMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with array and map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneArrayOneMap{new Array};
            std::string     expectedArrayOneArrayOneMapLines[]{ "99ER0ODU5OH/" };
            const size_t    expectedArrayOneArrayOneMapLinesCount{A_SIZE(expectedArrayOneArrayOneMapLines)};

            arrayOneArrayOneMap->addValue(std::make_shared<Array>());
            arrayOneArrayOneMap->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneArrayOneMap, expectedArrayOneArrayOneMapLines,
                                      expectedArrayOneArrayOneMapLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 317 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneArrayOneMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with array and map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneArrayOneMapLines[]{ "99ER0ODU5OH/" };
            const size_t    insertedArrayOneArrayOneMapLinesCount{A_SIZE(insertedArrayOneArrayOneMapLines)};
            Array           arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(std::make_shared<Array>());
            arrayOneArrayOneMap.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedArrayOneArrayOneMapLines,
                                          insertedArrayOneArrayOneMapLinesCount, arrayOneArrayOneMap);
        }
        else
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
} // doTestMIMEExtractArrayOneArrayOneMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 318 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneMapOneSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with map and set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneMapOneSet{new Array};
            std::string     expectedArrayOneMapOneSetLines[]{ "99ER1OTY6OH/" };
            const size_t    expectedArrayOneMapOneSetLinesCount{A_SIZE(expectedArrayOneMapOneSetLines)};

            arrayOneMapOneSet->addValue(std::make_shared<Map>());
            arrayOneMapOneSet->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneMapOneSet, expectedArrayOneMapOneSetLines,
                                      expectedArrayOneMapOneSetLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneMapOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 319 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneMapOneSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with map and set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneMapOneSetLines[]{ "99ER1OTY6OH/" };
            const size_t    insertedArrayOneMapOneSetLinesCount{A_SIZE(insertedArrayOneMapOneSetLines)};
            Array           arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(std::make_shared<Map>());
            arrayOneMapOneSet.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedArrayOneMapOneSetLines, insertedArrayOneMapOneSetLinesCount,
                                          arrayOneMapOneSet);
        }
        else
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
} // doTestMIMEExtractArrayOneMapOneSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 320 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayOneSetOneArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with set and array message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayOneSetOneArray{new Array};
            std::string     expectedArrayOneSetOneArrayLines[]{ "99ER2OjQ4OH/" };
            const size_t    expectedArrayOneSetOneArrayLinesCount{A_SIZE(expectedArrayOneSetOneArrayLines)};

            arrayOneSetOneArray->addValue(std::make_shared<Set>());
            arrayOneSetOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneSetOneArray, expectedArrayOneSetOneArrayLines,
                                      expectedArrayOneSetOneArrayLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayOneSetOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 321 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayOneSetOneArrayMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with set and array message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayOneSetOneArrayLines[]{ "99ER2OjQ4OH/" };
            const size_t    insertedArrayOneSetOneArrayLinesCount{A_SIZE(insertedArrayOneSetOneArrayLines)};
            Array           arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(std::make_shared<Set>());
            arrayOneSetOneArray.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedArrayOneSetOneArrayLines,
                                          insertedArrayOneSetOneArrayLinesCount, arrayOneSetOneArray);
        }
        else
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
} // doTestMIMEExtractArrayOneSetOneArrayMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 322 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithManyDoublesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with many doubles message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            const size_t    numValues = 43;
            SpArray         arrayManyDoubles{new Array};
            std::string     expectedArrayManyDoublesLines[]{
                                    "99EgGmArAAAAAAAAAAA/8AAAAAAAAEAAAAAAAAAAQAgAAAAAAABAEAAAAAAAAEAUAAAAAAAAQBgAAAAA",
                                    "AABAHAAAAAAAAEAgAAAAAAAAQCIAAAAAAABAJAAAAAAAAEAmAAAAAAAAQCgAAAAAAABAKgAAAAAAAEAs",
                                    "AAAAAAAAQC4AAAAAAABAMAAAAAAAAEAxAAAAAAAAQDIAAAAAAABAMwAAAAAAAEA0AAAAAAAAQDUAAAAA",
                                    "AABANgAAAAAAAEA3AAAAAAAAQDgAAAAAAABAOQAAAAAAAEA6AAAAAAAAQDsAAAAAAABAPAAAAAAAAEA9",
                                    "AAAAAAAAQD4AAAAAAABAPwAAAAAAAEBAAAAAAAAAQECAAAAAAABAQQAAAAAAAEBBgAAAAAAAQEIAAAAA",
                                    "AABAQoAAAAAAAEBDAAAAAAAAQEOAAAAAAABARAAAAAAAAEBEgAAAAAAAQEUAAAAAAADh/w==" };
            const size_t    expectedArrayManyDoublesLinesCount{A_SIZE(expectedArrayManyDoublesLines)};

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles->addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = setValueAndCheck(*stuff, arrayManyDoubles, expectedArrayManyDoublesLines,
                                      expectedArrayManyDoublesLinesCount);
        }
        else
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
} // doTestMIMEInsertArrayWithManyDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 323 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithManyDoublesMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with many doubles message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            const size_t    numValues = 43;
            std::string     insertedArrayManyDoublesLines[]{
                                    "99EgGmArAAAAAAAAAAA/8AAAAAAAAEAAAAAAAAAAQAgAAAAAAABAEAAAAAAAAEAUAAAAAAAAQBgAAAAA",
                                    "AABAHAAAAAAAAEAgAAAAAAAAQCIAAAAAAABAJAAAAAAAAEAmAAAAAAAAQCgAAAAAAABAKgAAAAAAAEAs",
                                    "AAAAAAAAQC4AAAAAAABAMAAAAAAAAEAxAAAAAAAAQDIAAAAAAABAMwAAAAAAAEA0AAAAAAAAQDUAAAAA",
                                    "AABANgAAAAAAAEA3AAAAAAAAQDgAAAAAAABAOQAAAAAAAEA6AAAAAAAAQDsAAAAAAABAPAAAAAAAAEA9",
                                    "AAAAAAAAQD4AAAAAAABAPwAAAAAAAEBAAAAAAAAAQECAAAAAAABAQQAAAAAAAEBBgAAAAAAAQEIAAAAA",
                                    "AABAQoAAAAAAAEBDAAAAAAAAQEOAAAAAAABARAAAAAAAAEBEgAAAAAAAQEUAAAAAAADh/w==" };
            const size_t    insertedArrayManyDoublesLinesCount{A_SIZE(insertedArrayManyDoublesLines)};
            Array           arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = extractValueAndCheck(*stuff, insertedArrayManyDoublesLines, insertedArrayManyDoublesLinesCount,
                                          arrayManyDoubles);
        }
        else
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
} // doTestMIMEExtractArrayWithManyDoublesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 400 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertLogicalMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpMap           logicalMap{new Map};
            std::string     expectedLogicalMapLines[]{ "99UQwA3l/w==" };
            const size_t    expectedLogicalMapLinesCount{A_SIZE(expectedLogicalMapLines)};

            logicalMap->addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, logicalMap, expectedLogicalMapLines, expectedLogicalMapLinesCount);
        }
        else
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
} // doTestMIMEInsertLogicalMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 401 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractLogicalMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedLogicalMapLines[]{ "99UQwA3l/w==" };
            const size_t    insertedLogicalMapLinesCount{A_SIZE(insertedLogicalMapLines)};
            Map             logicalMap;

            logicalMap.addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedLogicalMapLines, insertedLogicalMapLinesCount, logicalMap);
        }
        else
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
} // doTestMIMEExtractLogicalMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 402 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertIntegerMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpMap           integerMap{new Map};
            std::string     expectedIntegerMapLines[]{ "99UQAA3l/w==" };
            const size_t    expectedIntegerMapLinesCount{A_SIZE(expectedIntegerMapLines)};

            integerMap->addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, integerMap, expectedIntegerMapLines, expectedIntegerMapLinesCount);
        }
        else
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
} // doTestMIMEInsertIntegerMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 403 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractIntegerMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedIntegerMapLines[]{ "99UQAA3l/w==" };
            const size_t    insertedIntegerMapLinesCount{A_SIZE(insertedIntegerMapLines)};
            Map             integerMap;

            integerMap.addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedIntegerMapLines, insertedIntegerMapLinesCount, integerMap);
        }
        else
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
} // doTestMIMEExtractIntegerMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 404 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertStringMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpMap           stringMap{new Map};
            std::string     expectedStringMapLines[]{ "99UQgA3l/w==" };
            const size_t    expectedStringMapLinesCount{A_SIZE(expectedStringMapLines)};

            stringMap->addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, stringMap, expectedStringMapLines, expectedStringMapLinesCount);
        }
        else
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
} // doTestMIMEInsertStringMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 405 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractStringMapMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // string map message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedStringMapLines[]{ "99UQgA3l/w==" };
            const size_t    insertedStringMapLinesCount{A_SIZE(insertedStringMapLines)};
            Map             stringMap;

            stringMap.addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedStringMapLines, insertedStringMapLinesCount, stringMap);
        }
        else
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
} // doTestMIMEExtractStringMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 406 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertLogicalSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpSet           logicalSet{new Set};
            std::string     expectedLogicalSetLines[]{ "99kQwOn/" };
            const size_t    expectedLogicalSetLinesCount{A_SIZE(expectedLogicalSetLines)};

            logicalSet->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, logicalSet, expectedLogicalSetLines, expectedLogicalSetLinesCount);
        }
        else
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
} // doTestMIMEInsertLogicalSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 407 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractLogicalSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedLogicalSetLines[]{ "99kQwOn/" };
            const size_t    insertedLogicalSetLinesCount{A_SIZE(insertedLogicalSetLines)};
            Set             logicalSet;

            logicalSet.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedLogicalSetLines, insertedLogicalSetLinesCount, logicalSet);
        }
        else
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
} // doTestMIMEExtractLogicalSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 408 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertIntegerSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpSet           integerSet{new Set};
            std::string     expectedIntegerSetLines[]{ "99kQAOn/" };
            const size_t    expectedIntegerSetLinesCount{A_SIZE(expectedIntegerSetLines)};

            integerSet->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, integerSet, expectedIntegerSetLines, expectedIntegerSetLinesCount);
        }
        else
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
} // doTestMIMEInsertIntegerSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 409 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractIntegerSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedIntegerSetLines[]{ "99kQAOn/" };
            const size_t    insertedIntegerSetLinesCount{A_SIZE(insertedIntegerSetLines)};
            Set             integerSet;

            integerSet.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedIntegerSetLines, insertedIntegerSetLinesCount, integerSet);
        }
        else
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
} // doTestMIMEExtractIntegerSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 410 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertStringSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpSet           stringSet{new Set};
            std::string     expectedStringSetLines[]{ "99kQgOn/" };
            const size_t    expectedStringSetLinesCount{A_SIZE(expectedStringSetLines)};

            stringSet->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, stringSet, expectedStringSetLines, expectedStringSetLinesCount);
        }
        else
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
} // doTestMIMEInsertStringSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 411 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractStringSetMessage
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // string set message
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedStringSetLines[]{ "99kQgOn/" };
            const size_t    insertedStringSetLinesCount{A_SIZE(insertedStringSetLines)};
            Set             stringSet;

            stringSet.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedStringSetLines, insertedStringSetLinesCount, stringSet);
        }
        else
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
} // doTestMIMEExtractStringSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 500 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithRangeOfIntegers
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with range of integers
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            SpArray         arrayWithRangeOfIntegers{new Array};
            std::string     expectedArrayWithRangeOfIntegersLines[]{
                                    "99EgEwEKIGQhA+ghJxAiAYagIg9CQCMAmJaAIwX14QAjO5rKACQCVAvkACQXSHboACUA6NSlEAAlCRhO",
                                    "cqAAJVrzEHpAACYDjX6kxoAAJiOG8m/BAAAnAWNFeF2KAAAfFiCcIfwYIdjwIv55YCLwvcAj/2dpgCP6",
                                    "Ch8AI8RlNgAk/av0HAAk6LeJGAAl/xcrWvAAJfbnsY1gACWlDO+FwAAm/HKBWzmAACbceQ2QPwAAJ/6c",
                                    "uoeidgAA4f8=" };
            const size_t    expectedArrayWithRangeOfIntegersLinesCount{A_SIZE(expectedArrayWithRangeOfIntegersLines)};

            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(1));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(10));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(100));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(1000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(10000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(100000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(1000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(10000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(100000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(1000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(10000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(100000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(1000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(10000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(100000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(1000000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(10000000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(100000000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-1));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-10));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-100));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-1000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-10000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-100000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-1000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-10000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-100000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-1000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-10000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-100000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-1000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-10000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-100000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-1000000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-10000000000000000));
            arrayWithRangeOfIntegers->addValue(std::make_shared<Integer>(-100000000000000000));
            result = setValueAndCheck(*stuff, arrayWithRangeOfIntegers, expectedArrayWithRangeOfIntegersLines,
                                      expectedArrayWithRangeOfIntegersLinesCount);
        }
        else
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
} // doTestMIMEExtractArrayWithRangeOfIntegers

#if defined(__APPLE__)
# pragma mark *** Test Case 501 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithRangeOfIntegers
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with range of integers
{
    MDNS_UNUSED_ARG_(launchPath);
    MDNS_UNUSED_ARG_(argc);
    MDNS_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Message>()};

        if (nullptr != stuff)
        {
            std::string     insertedArrayWithRangeOfIntegersLines[]{
                                    "99EgEwEKIGQhA+ghJxAiAYagIg9CQCMAmJaAIwX14QAjO5rKACQCVAvkACQXSHboACUA6NSlEAAlCRhO",
                                    "cqAAJVrzEHpAACYDjX6kxoAAJiOG8m/BAAAnAWNFeF2KAAAfFiCcIfwYIdjwIv55YCLwvcAj/2dpgCP6",
                                    "Ch8AI8RlNgAk/av0HAAk6LeJGAAl/xcrWvAAJfbnsY1gACWlDO+FwAAm/HKBWzmAACbceQ2QPwAAJ/6c",
                                    "uoeidgAA4f8=" };
            const size_t    insertedArrayWithRangeOfIntegersLinesCount{A_SIZE(insertedArrayWithRangeOfIntegersLines)};
            Array           arrayWithRangeOfIntegers;

            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(1));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(10));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(100));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(1000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(10000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(100000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(1000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(10000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(100000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(1000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(10000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(100000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(1000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(10000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(100000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(1000000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(10000000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(100000000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-1));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-10));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-100));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-1000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-10000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-100000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-1000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-10000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-100000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-1000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-10000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-100000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-1000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-10000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-100000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-1000000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-10000000000000000));
            arrayWithRangeOfIntegers.addValue(std::make_shared<Integer>(-100000000000000000));
            result = extractValueAndCheck(*stuff, insertedArrayWithRangeOfIntegersLines,
                                          insertedArrayWithRangeOfIntegersLinesCount, arrayWithRangeOfIntegers);
        }
        else
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
} // doTestMIMEExtractArrayWithRangeOfIntegers

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

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    int result = 1;

    try
    {
        nImO::TestContext   ourContext(progName);

        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestMIMEInsertEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestMIMEExtractEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestMIMEInsertLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestMIMEExtractLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestMIMEInsertTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 6 :
                        result = doTestMIMEExtractTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 7 :
                        result = doTestMIMEInsertSmallIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 8 :
                        result = doTestMIMEExtractSmallIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 9 :
                        result = doTestMIMEInsertMediumIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestMIMEExtractMediumIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 11 :
                        result = doTestMIMEInsertBigIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestMIMEExtractBigIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestMIMEInsertEmptyStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 14 :
                        result = doTestMIMEExtractEmptyStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 15 :
                        result = doTestMIMEInsertShortStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 16 :
                        result = doTestMIMEExtractShortStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 17 :
                        result = doTestMIMEInsertMediumStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 18 :
                        result = doTestMIMEExtractMediumStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 19 :
                        result = doTestMIMEInsertEmptyBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 20 :
                        result = doTestMIMEExtractEmptyBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 21 :
                        result = doTestMIMEInsertSmallBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 22 :
                        result = doTestMIMEExtractSmallBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 23 :
                        result = doTestMIMEInsertMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 24 :
                        result = doTestMIMEExtractMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 25 :
                        result = doTestMIMEInsertSingleDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 26 :
                        result = doTestMIMEExtractSingleDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 100 :
                        result = doTestMIMEInsertEmptyArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestMIMEExtractEmptyArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestMIMEInsertEmptyMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 103 :
                        result = doTestMIMEExtractEmptyMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 104 :
                        result = doTestMIMEInsertEmptySetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 105 :
                        result = doTestMIMEExtractEmptySetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 200 :
                        result = doTestMIMEInsertArrayOneLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 201 :
                        result = doTestMIMEExtractArrayOneLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 202 :
                        result = doTestMIMEInsertArrayOneIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 203 :
                        result = doTestMIMEExtractArrayOneIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 204 :
                        result = doTestMIMEInsertArrayOneDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 205 :
                        result = doTestMIMEExtractArrayOneDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 206 :
                        result = doTestMIMEInsertArrayOneStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 207 :
                        result = doTestMIMEExtractArrayOneStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 208 :
                        result = doTestMIMEInsertArrayOneBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 209 :
                        result = doTestMIMEExtractArrayOneBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 210 :
                        result = doTestMIMEInsertArrayOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 211 :
                        result = doTestMIMEExtractArrayOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 212 :
                        result = doTestMIMEInsertArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 213 :
                        result = doTestMIMEExtractArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 214 :
                        result = doTestMIMEInsertArrayOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 215 :
                        result = doTestMIMEExtractArrayOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 300 :
                        result = doTestMIMEInsertArrayTwoLogicalsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 301 :
                        result = doTestMIMEExtractArrayTwoLogicalsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 302 :
                        result = doTestMIMEInsertArrayTwoIntegersMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 303 :
                        result = doTestMIMEExtractArrayTwoIntegersMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 304 :
                        result = doTestMIMEInsertArrayTwoDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 305 :
                        result = doTestMIMEExtractArrayTwoDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 306 :
                        result = doTestMIMEInsertArrayTwoStringsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 307 :
                        result = doTestMIMEExtractArrayTwoStringsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 308 :
                        result = doTestMIMEInsertArrayTwoBlobsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 309 :
                        result = doTestMIMEExtractArrayTwoBlobsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 310 :
                        result = doTestMIMEInsertArrayTwoArraysMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 311 :
                        result = doTestMIMEExtractArrayTwoArraysMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 312 :
                        result = doTestMIMEInsertArrayTwoMapsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 313 :
                        result = doTestMIMEExtractArrayTwoMapsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 314 :
                        result = doTestMIMEInsertArrayTwoSetsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 315 :
                        result = doTestMIMEExtractArrayTwoSetsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 316 :
                        result = doTestMIMEInsertArrayOneArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 317 :
                        result = doTestMIMEExtractArrayOneArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 318 :
                        result = doTestMIMEInsertArrayOneMapOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 319 :
                        result = doTestMIMEExtractArrayOneMapOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 320 :
                        result = doTestMIMEInsertArrayOneSetOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 321 :
                        result = doTestMIMEExtractArrayOneSetOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 322 :
                        result = doTestMIMEInsertArrayWithManyDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 323 :
                        result = doTestMIMEExtractArrayWithManyDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 400 :
                        result = doTestMIMEInsertLogicalMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 401 :
                        result = doTestMIMEExtractLogicalMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 402 :
                        result = doTestMIMEInsertIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 403 :
                        result = doTestMIMEExtractIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 404 :
                        result = doTestMIMEInsertStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 405 :
                        result = doTestMIMEExtractStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 406 :
                        result = doTestMIMEInsertLogicalSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 407 :
                        result = doTestMIMEExtractLogicalSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 408 :
                        result = doTestMIMEInsertIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 409 :
                        result = doTestMIMEExtractIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 410 :
                        result = doTestMIMEInsertStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 411 :
                        result = doTestMIMEExtractStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 500 :
                        result = doTestMIMEInsertArrayWithRangeOfIntegers(*argv, argc - 1, argv + 2);
                        break;

                    case 501 :
                        result = doTestMIMEExtractArrayWithRangeOfIntegers(*argv, argc - 1, argv + 2);
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
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

#include <nImOarray.hpp>
#include <nImOblob.hpp>
#include <nImObufferChunk.hpp>
#include <nImOdouble.hpp>
#include <nImOinteger.hpp>
#include <nImOlogical.hpp>
#include <nImOmap.hpp>
#include <nImOmessage.hpp>
#include <nImOMIMESupport.hpp>
#include <nImOset.hpp>
#include <nImOstring.hpp>
#include <nImOstringBuffer.hpp>
#include <nImOtestContext.hpp>

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
#if 0
    nImO_ERROR_(message.c_str());
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

#if 0
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
     const Value &      aValue,
     const DataKind *   expectedContents1,
     const size_t       expectedSize1,
     const uint8_t *    expectedContents2,
     const size_t       expectedSize2)
{
    ODL_ENTER(); //####
    ODL_P4("stuff = ", &stuff, "aValue = ", &aValue, "expectedContents1 = ", //####
           expectedContents1, "expectedContents2 = ", expectedContents2); //####
    ODL_I2("expectedSize1 = ", expectedSize1, "expectedSize2 = ", expectedSize2); //####
    stuff.open(true);
    stuff.setValue(aValue);
    stuff.close();
    auto    contents1{stuff.getBytes()};
    size_t  length1 = contents1.size();
    int     result;

    ODL_PACKET("expectedContents1", expectedContents1, expectedSize1); //####
    ODL_PACKET("contents1", contents1.data(), length1); //####
    if (expectedSize1 == length1)
    {
        result = StaticCast(int, CompareBytes(expectedContents1, contents1.data(), expectedSize1));
        if (0 == result)
        {
            if ((nullptr != expectedContents2) && (0 < expectedSize2))
            {
                std::string contents2{stuff.getBytesForTransmission()};
                size_t      length2 = contents2.size();

                ODL_PACKET("expectedContents2", expectedContents2, expectedSize2); //####
                ODL_PACKET("contents2", contents2.data(), length2); //####
                if (expectedSize2 == length2)
                {
                    result = StaticCast(int, CompareBytes(expectedContents2, contents2.data(), expectedSize2));
                }
                else
                {
                    ODL_LOG("! (expectedSize2 == length2)"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((nullptr != expectedContents2) && (0 < expectedSize2))"); //####
            }
        }
    }
    else
    {
        ODL_LOG("! (expectedSize1 == length1)"); //####
        result = 1;
    }
    ODL_EXIT_I(result); //####
    return result;
} // setValueAndCheck
#endif//0

#if 0
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

                if (nullptr == asFlaw)
                {
                    ODL_LOG("(nullptr == asFlaw)");
                    ODL_I1("ii = ", ii); //####
                    result = 1;
                }
                else
                {
                    ODL_LOG("! (nullptr == asFlaw)"); //####
                    ODL_LOG(asFlaw->getDescription().c_str()); //####
                }
            }
        }
    }
    ODL_EXIT_I(result); //####
    return result;
} // extractValueAndCheck
#endif//0

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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty message
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
            // static const DataKind   expectedEmptyBytes[] =
            // {
            //     // Start of Message
            //     DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
            //     // End of Message
            //     DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            // };
            StringVector    outVec;

            stuff->open(true);
            stuff->close();
//            stuff->getBytesAsMIME(outVec);
            if (0 < outVec.size())
            {
                std::string     expectedLines[] = { "a", "b" };
                const size_t    expectedLinesCount = A_SIZE(expectedLines);
#if 0
                        static const uint8_t    transmitEmptyBytes[] =
                        {
                            0xF0, // Start of message
                            0xF8, // End of message
                            0x17 // Checksum
                        };
#endif//0                
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
                ODL_LOG("! (0 < outVec.size())"); //####
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // logical message
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
            static const DataKind   expectedTrueBytes[] =
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
            const size_t            expectedTrueByteCount = A_SIZE(expectedTrueBytes);
            static const DataKind   expectedFalseBytes[] =
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
            const size_t            expectedFalseByteCount = A_SIZE(expectedFalseBytes);
#if 0
            static const uint8_t    transmitFalseBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xC0, // Logical False
                0xFF, // End of message, last is Other
                0x49 // Checksum
            };
            const size_t            transmitFalseByteCount = A_SIZE(transmitFalseBytes);
            static const uint8_t    transmitTrueBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xC1, // Logical true
                0xFF, // End of message, last is Other
                0x48 // Checksum
            };
            const size_t            transmitTrueByteCount = A_SIZE(transmitTrueBytes);
            Logical                 falseValue(false);
            Logical                 trueValue(true);

            result = setValueAndCheck(*stuff, trueValue, expectedTrueBytes, expectedTrueByteCount, transmitTrueBytes, transmitTrueByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, falseValue, expectedFalseBytes, expectedFalseByteCount, transmitFalseBytes,
                                          transmitFalseByteCount);
            }
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // logical message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // tiny integer message
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
            static const DataKind   expectedMinus12Bytes[] =
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
            const size_t            expectedMinus12ByteCount = A_SIZE(expectedMinus12Bytes);
            static const DataKind   expectedZeroBytes[] =
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
            const size_t            expectedZeroByteCount = A_SIZE(expectedZeroBytes);
            static const DataKind   expectedPlus12Bytes[] =
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
            const size_t            expectedPlus12ByteCount = A_SIZE(expectedPlus12Bytes);
#if 0
            static const uint8_t    transmitMinus12Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x14, // Integer -12
                0xFC, // End of message, last is Integer
                0xFB // Checksum
            };
            const size_t            transmitMinus12ByteCount = A_SIZE(transmitMinus12Bytes);
            static const uint8_t    transmitZeroBytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x00, // Integer 0
                0xFC, // End of message, last is Integer
                0x0F // Checksum
            };
            const size_t            transmitZeroByteCount = A_SIZE(transmitZeroBytes);
            static const uint8_t    transmitPlus12Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x0C, // Integer 12
                0xFC, // End of message, last is Integer
                0x03 // Checksum
            };
            const size_t            transmitPlus12ByteCount = A_SIZE(transmitPlus12Bytes);
            Integer                 minus12Value(-12);
            Integer                 zeroValue(0);
            Integer                 plus12Value(12);

            result = setValueAndCheck(*stuff, minus12Value, expectedMinus12Bytes, expectedMinus12ByteCount, transmitMinus12Bytes,
                                      transmitMinus12ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, zeroValue, expectedZeroBytes, expectedZeroByteCount, transmitZeroBytes,
                                          transmitZeroByteCount);
            }
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus12Value, expectedPlus12Bytes, expectedPlus12ByteCount, transmitPlus12Bytes,
                                          transmitPlus12ByteCount);
            }
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // tiny integer message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // small integer message
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
            static const DataKind   expectedMinus144Bytes[] =
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
            const size_t            expectedMinus144ByteCount = A_SIZE(expectedMinus144Bytes);
            static const DataKind   expectedPlus144Bytes[] =
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
            const size_t            expectedPlus144ByteCount = A_SIZE(expectedPlus144Bytes);
#if 0
            static const uint8_t    transmitMinus144Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x21, 0xFF, 0x70, // Integer -144
                0xFC, // End of message, last is Integer
                0x7F // Checksum
            };
            const size_t            transmitMinus144ByteCount = A_SIZE(transmitMinus144Bytes);
            static const uint8_t    transmitPlus144Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x21, 0x00, 0x90, // Integer 144
                0xFC, // End of message, last is Integer
                0x5E // Checksum
            };
            const size_t            transmitPlus144ByteCount = A_SIZE(transmitPlus144Bytes);
            Integer                 minus144Value(-144);
            Integer                 plus144Value(144);

            result = setValueAndCheck(*stuff, minus144Value, expectedMinus144Bytes, expectedMinus144ByteCount, transmitMinus144Bytes,
                                      transmitMinus144ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus144Value, expectedPlus144Bytes, expectedPlus144ByteCount, transmitPlus144Bytes,
                                          transmitPlus144ByteCount);
            }
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // small integer message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // medium integer message
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
            static const DataKind   expectedMinus1234567Bytes[] =
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
            const size_t            expectedMinus1234567ByteCount = A_SIZE(expectedMinus1234567Bytes);
            static const DataKind   expectedPlus1234567Bytes[] =
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
            const size_t            expectedPlus1234567ByteCount = A_SIZE(expectedPlus1234567Bytes);
#if 0
            static const uint8_t    transmitMinus1234567Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x22, 0xED, 0x29, 0x79, // Integer -1234567
                0xFC, // End of message, last is Integer
                0x5E // Checksum
            };
            const size_t            transmitMinus1234567ByteCount = A_SIZE(transmitMinus1234567Bytes);
            static const uint8_t    transmitPlus1234567Bytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x22, 0x12, 0xD6, 0x87, // Integer 1234567
                0xFC, // End of message, last is Integer
                0x7E // Checksum
            };
            const size_t            transmitPlus1234567ByteCount = A_SIZE(transmitPlus1234567Bytes);
            Integer                 minus1234567Value(-1234567);
            Integer                 plus1234567Value(1234567);

            result = setValueAndCheck(*stuff, minus1234567Value, expectedMinus1234567Bytes, expectedMinus1234567ByteCount, transmitMinus1234567Bytes,
                                      transmitMinus1234567ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus1234567Value, expectedPlus1234567Bytes, expectedPlus1234567ByteCount, transmitPlus1234567Bytes,
                                          transmitPlus1234567ByteCount);
            }
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // medium integer message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // big integer message
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
            static const DataKind   expectedMinusBigNumberBytes[] =
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
            const size_t            expectedMinusBigNumberByteCount = A_SIZE(expectedMinusBigNumberBytes);
            static const DataKind   expectedPlusBigNumberBytes[] =
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
            const size_t            expectedPlusBigNumberByteCount = A_SIZE(expectedPlusBigNumberBytes);
#if 0
            static const uint8_t    transmitMinusBigNumberBytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x25, 0xED, 0xCB, 0xA9, 0x87, 0x65, 0x44, // Integer -20015998343868
                0xFC, // End of message, last is Integer
                0x59 // Checksum
            };
            const size_t            transmitMinusBigNumberByteCount = A_SIZE(transmitMinusBigNumberBytes);
            static const uint8_t    transmitPlusBigNumberBytes[] =
            {
                0xF4, // Start of message, next is Integer
                0x25, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, // Integer 20015998343868
                0xFC, // End of message, last is Integer
                0x80 // Checksum
            };
            const size_t            transmitPlusBigNumberByteCount = A_SIZE(transmitPlusBigNumberBytes);
            Integer                 minusBigNumberValue(-20015998343868);
            Integer                 plusBigNumberValue(20015998343868);

            result = setValueAndCheck(*stuff, minusBigNumberValue, expectedMinusBigNumberBytes, expectedMinusBigNumberByteCount,
                                      transmitMinusBigNumberBytes, transmitMinusBigNumberByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plusBigNumberValue, expectedPlusBigNumberBytes, expectedPlusBigNumberByteCount,
                                          transmitPlusBigNumberBytes, transmitPlusBigNumberByteCount);
            }
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // big integer message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty string message
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
            static const DataKind   expectedEmptyStringBytes[] =
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
            const size_t            expectedEmptyStringByteCount = A_SIZE(expectedEmptyStringBytes);
#if 0
            static const uint8_t    transmitEmptyStringBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0x80, // String - empty
                0xFE, // End of message, last is String or Blob
                0x8B // Checksum
            };
            const size_t            transmitEmptyStringByteCount = A_SIZE(transmitEmptyStringBytes);
            String                  emptyStringValue("");

            result = setValueAndCheck(*stuff, emptyStringValue, expectedEmptyStringBytes, expectedEmptyStringByteCount, transmitEmptyStringBytes,
                                      transmitEmptyStringByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty string message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // short string message
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
            static const DataKind   expectedShortStringBytes[] =
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
            const size_t            expectedShortStringByteCount = A_SIZE(expectedShortStringBytes);
#if 0
            static const uint8_t    transmitShortStringBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0x86, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, // String - 'abcdef'
                0xFE, // End of message, last is String or Blob
                0x30 // Checksum
            };
            const size_t            transmitShortStringByteCount = A_SIZE(transmitShortStringBytes);
            String                  shortStringValue("abcdef");

            result = setValueAndCheck(*stuff, shortStringValue, expectedShortStringBytes, expectedShortStringByteCount, transmitShortStringBytes,
                                      transmitShortStringByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // short string message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // medium string message
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
            static const DataKind   expectedMediumStringBytes[] =
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
            const size_t            expectedMediumStringByteCount = A_SIZE(expectedMediumStringBytes);
#if 0
            static const uint8_t    transmitMediumStringBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0x90, 0x2A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, // String - 'abcdef'*7, length = 42
                0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                0xFE, // End of message, last is String or Blob
                0xFE // Checksum
            };
            const size_t            transmitMediumStringByteCount = A_SIZE(transmitMediumStringBytes);
            String                  mediumStringValue("abcdefabcdefabcdefabcdefabcdefabcdefabcdef");

            result = setValueAndCheck(*stuff, mediumStringValue, expectedMediumStringBytes, expectedMediumStringByteCount,
                                      transmitMediumStringBytes, transmitMediumStringByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // medium string message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty blob message
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
            static const DataKind   expectedEmptyBlobBytes[] =
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
            const size_t            expectedEmptyBlobByteCount = A_SIZE(expectedEmptyBlobBytes);
#if 0
            static const uint8_t    transmitEmptyBlobBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xA0, // Empty Blob
                0xFE, // End of message, last is String or Blob
                0x6B // Checksum
            };
            const size_t            transmitEmptyBlobByteCount = A_SIZE(transmitEmptyBlobBytes);
            Blob                    emptyBlobValue;

            result = setValueAndCheck(*stuff, emptyBlobValue, expectedEmptyBlobBytes, expectedEmptyBlobByteCount,
                                      transmitEmptyBlobBytes, transmitEmptyBlobByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty blob message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // small blob message
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
            static const DataKind   expectedSmallBlobBytes[] =
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
            const size_t            expectedSmallBlobByteCount = A_SIZE(expectedSmallBlobBytes);
            static const uint8_t    actualData[] =
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            const size_t            actualDataCount = A_SIZE(actualData);
#if 0
            static const uint8_t    transmitSmallBlobBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xA6, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, // Short Blob
                0xFE, // End of message, last is String or Blob
                0xFA // Checksum
            };
            const size_t            transmitSmallBlobByteCount = A_SIZE(transmitSmallBlobBytes);
            Blob                    shortBlobValue(actualData, actualDataCount);

            result = setValueAndCheck(*stuff, shortBlobValue, expectedSmallBlobBytes, expectedSmallBlobByteCount, transmitSmallBlobBytes,
                                      transmitSmallBlobByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // small blob message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // medium blob message
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
            static const DataKind   expectedMediumBlobBytes[] =
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
            const size_t            expectedMediumBlobByteCount = A_SIZE(expectedMediumBlobBytes);
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
#if 0
            static const uint8_t    transmitMediumBlobBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xB0, 0x2A, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, // Medium Blob, length = 42
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67,
                0xFE, // End of message, last is String or Blob
                0x44 // Checksum
            };
            const size_t            transmitMediumBlobByteCount = A_SIZE(transmitMediumBlobBytes);
            Blob                    mediumBlobValue(actualData, actualDataCount);

            result = setValueAndCheck(*stuff, mediumBlobValue, expectedMediumBlobBytes, expectedMediumBlobByteCount, transmitMediumBlobBytes,
                                      transmitMediumBlobByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // medium blob message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // single double message
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
            static const DataKind   expectedPlus42Point5Bytes[] =
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
            const size_t            expectedPlus42Point5ByteCount = A_SIZE(expectedPlus42Point5Bytes);
            static const DataKind   expectedMinus42Point5Bytes[] =
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
            const size_t            expectedMinus42Point5ByteCount = A_SIZE(expectedMinus42Point5Bytes);
#if 0
            static const uint8_t    transmitMinus42Point5Bytes[] =
            {
                0xF5, // Start of message, next is Doubleing-point
                0x40, 0xC0, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // one Double value, -42.5
                0xFD, // End of message, last is Doubleing-point
                0x88 // Checksum
            };
            const size_t            transmitMinus42Point5ByteCount = A_SIZE(transmitMinus42Point5Bytes);
            static const uint8_t    transmitPlus42Point5Bytes[] =
            {
                0xF5, // Start of message, next is Doubleing-point
                0x40, 0x40, 0x45, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // one Double value, 42.5
                0xFD, // End of message, last is Doubleing-point
                0x08 // Checksum
            };
            const size_t            transmitPlus42Point5ByteCount = A_SIZE(transmitPlus42Point5Bytes);
            Double                  plus42Point5(42.5);
            Double                  minus42Point5(-42.5);

            result = setValueAndCheck(*stuff, plus42Point5, expectedPlus42Point5Bytes,
                                      expectedPlus42Point5ByteCount, transmitPlus42Point5Bytes,
                                      transmitPlus42Point5ByteCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, minus42Point5, expectedMinus42Point5Bytes, expectedMinus42Point5ByteCount,
                                          transmitMinus42Point5Bytes, transmitMinus42Point5ByteCount);
            }
#endif//0
        }
        else
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
# pragma mark *** Test Case 013 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractSingleDoubleMessage
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // single double message
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
#if 0
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
#endif//0
        }
        else
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
# pragma mark *** Test Case 027 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertMultipleEscapesMessage
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // message with multiple escapes
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
            static const DataKind   expectedMultipleEscapesBytes[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // Blob
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobShortLengthValue |
                  (10 & DataKind::StringOrBlobShortLengthMask),
                StaticCast(DataKind, 0xDC), StaticCast(DataKind, 0xF0),
                StaticCast(DataKind, 0xF1), StaticCast(DataKind, 0xF2),
                StaticCast(DataKind, 0x0D), StaticCast(DataKind, 0xF3),
                StaticCast(DataKind, 0xF4), StaticCast(DataKind, 0xF5),
                StaticCast(DataKind, 0xF6), StaticCast(DataKind, 0xF7),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t            expectedMultipleEscapesByteCount = A_SIZE(expectedMultipleEscapesBytes);
            static const uint8_t    actualData[] =
            {
                0xDC, 0xF0, 0xF1, 0xF2, 0x0D, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7
            };
            const size_t            actualDataCount = A_SIZE(actualData);
#if 0
            static const uint8_t    transmitMultipleEscapesBytes[] =
            {
                0xF6, // Start of message, next is String or Blob
                0xAA, 0xDC, 0x5C, 0xDC, 0x70, 0xDC, 0x71, 0xDC, 0x72, 0x0D, 0xDC, 0x73, 0xDC, 0x74,
                0xDC, 0x75, 0xDC, 0x76, 0xDC, 0x77, // many escapes
                0xFE, // End of message, last is String or Blob
                0xDC, 0x5C // Checksum
            };
            const size_t            transmitMultipleEscapesByteCount = A_SIZE(transmitMultipleEscapesBytes);
            Blob                    multipleEscapesValue(actualData, actualDataCount);

            result = setValueAndCheck(*stuff, multipleEscapesValue, expectedMultipleEscapesBytes, expectedMultipleEscapesByteCount,
                                      transmitMultipleEscapesBytes, transmitMultipleEscapesByteCount);
#endif//0
        }
        else
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
} // doTestMIMEInsertMultipleEscapesMessage

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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty array message
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
            static const DataKind   expectedEmptyArrayBytes[] =
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
            const size_t            expectedEmptyArrayByteCount = A_SIZE(expectedEmptyArrayBytes);
#if 0
            static const uint8_t    transmitEmptyArrayBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xFF, // End of message, last is Other
                0x59 // Checksum
            };
            const size_t            transmitEmptyArrayByteCount = A_SIZE(transmitEmptyArrayBytes);
            Array                   emptyArray;

            result = setValueAndCheck(*stuff, emptyArray, expectedEmptyArrayBytes, expectedEmptyArrayByteCount, transmitEmptyArrayBytes,
                                      transmitEmptyArrayByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty array message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty map message
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
            static const DataKind   expectedEmptyMapBytes[] =
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
            const size_t            expectedEmptyMapByteCount = A_SIZE(expectedEmptyMapBytes);
#if 0
            static const uint8_t    transmitEmptyMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xFF, // End of message, last is Other
                0x51 // Checksum
            };
            const size_t            transmitEmptyMapByteCount = A_SIZE(transmitEmptyMapBytes);
            Map                     emptyMap;

            result = setValueAndCheck(*stuff, emptyMap, expectedEmptyMapBytes, expectedEmptyMapByteCount, transmitEmptyMapBytes,
                                      transmitEmptyMapByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty map message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty set message
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
            static const DataKind   expectedEmptySetBytes[] =
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
            const size_t            expectedEmptySetByteCount = A_SIZE(expectedEmptySetBytes);
#if 0
            static const uint8_t    transmitEmptySetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD8, // Start of empty Set
                0xE8, // End of empty Set
                0xFF, // End of message, last is Other
                0x49 // Checksum
            };
            const size_t            transmitEmptySetByteCount = A_SIZE(transmitEmptySetBytes);
            Set                     emptySet;

            result = setValueAndCheck(*stuff, emptySet, expectedEmptySetBytes, expectedEmptySetByteCount, transmitEmptySetBytes,
                                      transmitEmptySetByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // empty set message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one logical message
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
            static const DataKind   expectedArrayOneLogicalBytes[] =
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
            const size_t            expectedArrayOneLogicalByteCount = A_SIZE(expectedArrayOneLogicalBytes);
#if 0
            static const uint8_t    transmitArrayOneLogicalBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xC0, // Logical false
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x87 // Checksum
            };
            const size_t            transmitArrayOneLogicalByteCount = A_SIZE(transmitArrayOneLogicalBytes);
            Array                   arrayOneLogical;

            arrayOneLogical.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayOneLogical, expectedArrayOneLogicalBytes, expectedArrayOneLogicalByteCount,
                                      transmitArrayOneLogicalBytes, transmitArrayOneLogicalByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one logical message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one integer message
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
            static const DataKind   expectedArrayOneIntegerBytes[] =
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
            const size_t            expectedArrayOneIntegerByteCount = A_SIZE(expectedArrayOneIntegerBytes);
#if 0
            static const uint8_t    transmitArrayOneIntegerBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0x00, // Integer zero
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x47 // Checksum
            };
            const size_t            transmitArrayOneIntegerByteCount = A_SIZE(transmitArrayOneIntegerBytes);
            Array                   arrayOneInteger;

            arrayOneInteger.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayOneInteger, expectedArrayOneIntegerBytes, expectedArrayOneIntegerByteCount,
                                      transmitArrayOneIntegerBytes, transmitArrayOneIntegerByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one integer message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one double message
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
            static const DataKind   expectedArrayOneDoubleBytes[] =
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
            const size_t            expectedArrayOneDoubleByteCount = A_SIZE(expectedArrayOneDoubleBytes);
#if 0
            static const uint8_t    transmitArrayOneDoubleBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Double zero
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x07 // Checksum
            };
            const size_t            transmitArrayOneDoubleByteCount = A_SIZE(transmitArrayOneDoubleBytes);
            Array                   arrayOneDouble;

            arrayOneDouble.addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayOneDouble, expectedArrayOneDoubleBytes, expectedArrayOneDoubleByteCount,
                                      transmitArrayOneDoubleBytes, transmitArrayOneDoubleByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one double message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one string message
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
            static const DataKind   expectedArrayOneStringBytes[] =
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
            const size_t            expectedArrayOneStringByteCount = A_SIZE(expectedArrayOneStringBytes);
#if 0
            static const uint8_t    transmitArrayOneStringBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0x80, // Empty String
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xC7 // Checksum
            };
            const size_t            transmitArrayOneStringByteCount = A_SIZE(transmitArrayOneStringBytes);
            Array                   arrayOneString;

            arrayOneString.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayOneString, expectedArrayOneStringBytes, expectedArrayOneStringByteCount,
                                      transmitArrayOneStringBytes, transmitArrayOneStringByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one string message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one blob message
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
            static const DataKind   expectedArrayOneBlobBytes[] =
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
            const size_t            expectedArrayOneBlobByteCount = A_SIZE(expectedArrayOneBlobBytes);
#if 0
            static const uint8_t    transmitArrayOneBlobBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xA0, // Empty Blob
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xA7 // Checksum
            };
            const size_t            transmitArrayOneBlobByteCount = A_SIZE(transmitArrayOneBlobBytes);
            Array                   arrayOneBlob;

            arrayOneBlob.addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayOneBlob, expectedArrayOneBlobBytes, expectedArrayOneBlobByteCount,
                                      transmitArrayOneBlobBytes, transmitArrayOneBlobByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one blob message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one array message
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
            static const DataKind   expectedArrayOneArrayBytes[] =
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
            const size_t            expectedArrayOneArrayByteCount = A_SIZE(expectedArrayOneArrayBytes);
#if 0
            static const uint8_t    transmitArrayOneArrayBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x97 // Checksum
            };
            const size_t            transmitArrayOneArrayByteCount = A_SIZE(transmitArrayOneArrayBytes);
            Array                   arrayOneArray;

            arrayOneArray.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneArray, expectedArrayOneArrayBytes, expectedArrayOneArrayByteCount,
                                      transmitArrayOneArrayBytes, transmitArrayOneArrayByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one array message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one map message
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
            static const DataKind   expectedArrayOneMapBytes[] =
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
            const size_t            expectedArrayOneMapByteCount = A_SIZE(expectedArrayOneMapBytes);
#if 0
            static const uint8_t    transmitArrayOneMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x8F // Checksum
            };
            const size_t            transmitArrayOneMapByteCount = A_SIZE(transmitArrayOneMapBytes);
            Array                   arrayOneMap;

            arrayOneMap.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneMap, expectedArrayOneMapBytes, expectedArrayOneMapByteCount,
                                      transmitArrayOneMapBytes, transmitArrayOneMapByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one map message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one set message
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
            static const DataKind   expectedArrayOneSetBytes[] =
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
            const size_t            expectedArrayOneSetByteCount = A_SIZE(expectedArrayOneSetBytes);
#if 0
            static const uint8_t    transmitArrayOneSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x10, // Start of non-empty Array, one element
                0xD8, // Start of empty Map
                0xE8, // End of empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x87 // Checksum
            };
            const size_t            transmitArrayOneSetByteCount = A_SIZE(transmitArrayOneSetBytes);
            Array                   arrayOneSet;

            arrayOneSet.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneSet, expectedArrayOneSetBytes, expectedArrayOneSetByteCount,
                                      transmitArrayOneSetBytes, transmitArrayOneSetByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with one set message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two logicals message
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
            static const DataKind   expectedArrayTwoLogicalsBytes[] =
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
            const size_t            expectedArrayTwoLogicalsByteCount = A_SIZE(expectedArrayTwoLogicalsBytes);
#if 0
            static const uint8_t    transmitArrayTwoLogicalsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xC0, 0xC0, // Two Logical falses
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xC6 // Checksum
            };
            const size_t            transmitArrayTwoLogicalsByteCount = A_SIZE(transmitArrayTwoLogicalsBytes);
            Array                   arrayTwoLogicals;

            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayTwoLogicals, expectedArrayTwoLogicalsBytes, expectedArrayTwoLogicalsByteCount,
                                      transmitArrayTwoLogicalsBytes, transmitArrayTwoLogicalsByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two logicals message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two integers message
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
            static const DataKind   expectedArrayTwoIntegersBytes[] =
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
            const size_t            expectedArrayTwoIntegersByteCount = A_SIZE(expectedArrayTwoIntegersBytes);
#if 0
            static const uint8_t    transmitArrayTwoIntegersBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0x00, 0x00, // Two Integer zeroes
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x46 // Checksum
            };
            const size_t            transmitArrayTwoIntegersByteCount = A_SIZE(transmitArrayTwoIntegersBytes);
            Array                   arrayTwoIntegers;

            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayTwoIntegers, expectedArrayTwoIntegersBytes, expectedArrayTwoIntegersByteCount,
                                      transmitArrayTwoIntegersBytes, transmitArrayTwoIntegersByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two integers message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two doubles message
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
            static const DataKind   expectedArrayTwoDoublesBytes[] =
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
            const size_t            expectedArrayTwoDoublesByteCount = A_SIZE(expectedArrayTwoDoublesBytes);
#if 0
            static const uint8_t    transmitArrayTwoDoublesBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Two Double zeroes
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x05 // Checksum
            };
            const size_t            transmitArrayTwoDoublesByteCount = A_SIZE(transmitArrayTwoDoublesBytes);
            Array                   arrayTwoDoubles;

            arrayTwoDoubles.addValue(std::make_shared<Double>());
            arrayTwoDoubles.addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayTwoDoubles, expectedArrayTwoDoublesBytes, expectedArrayTwoDoublesByteCount,
                                      transmitArrayTwoDoublesBytes, transmitArrayTwoDoublesByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two doubles message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two strings message
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
            static const DataKind   expectedArrayTwoStringsBytes[] =
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
            const size_t            expectedArrayTwoStringsByteCount = A_SIZE(expectedArrayTwoStringsBytes);
#if 0
            static const uint8_t    transmitArrayTwoStringsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0x80, 0x80, // Two empty Strings
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x46 // Checksum
            };
            const size_t            transmitArrayTwoStringsByteCount = A_SIZE(transmitArrayTwoStringsBytes);
            Array                   arrayTwoStrings;

            arrayTwoStrings.addValue(std::make_shared<String>());
            arrayTwoStrings.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayTwoStrings, expectedArrayTwoStringsBytes, expectedArrayTwoStringsByteCount,
                                      transmitArrayTwoStringsBytes, transmitArrayTwoStringsByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two strings message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two blobs message
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
            static const DataKind   expectedArrayTwoBlobsBytes[] =
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
            const size_t            expectedArrayTwoBlobsByteCount = A_SIZE(expectedArrayTwoBlobsBytes);
#if 0
            static const uint8_t    transmitArrayTwoBlobsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xA0, 0xA0, // Two empty Blobs
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0x06 // Checksum
            };
            const size_t            transmitArrayTwoBlobsByteCount = A_SIZE(transmitArrayTwoBlobsBytes);
            Array                   arrayTwoBlobs;

            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayTwoBlobs, expectedArrayTwoBlobsBytes, expectedArrayTwoBlobsByteCount,
                                      transmitArrayTwoBlobsBytes, transmitArrayTwoBlobsByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two blobs message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two arrays message
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
            static const DataKind   expectedArrayTwoArraysBytes[] =
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
            const size_t            expectedArrayTwoArraysByteCount = A_SIZE(expectedArrayTwoArraysBytes);
#if 0
            static const uint8_t    transmitArrayTwoArraysBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD0, // Start of first empty Array
                0xE0, // End of first empty Array
                0xD0, // Start of second empty Array
                0xE0, // End of second empty Array
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xE6 // Checksum
            };
            const size_t            transmitArrayTwoArraysByteCount = A_SIZE(transmitArrayTwoArraysBytes);
            Array                   arrayTwoArrays;

            arrayTwoArrays.addValue(std::make_shared<Array>());
            arrayTwoArrays.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayTwoArrays, expectedArrayTwoArraysBytes, expectedArrayTwoArraysByteCount,
                                      transmitArrayTwoArraysBytes, transmitArrayTwoArraysByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two arrays message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two maps message
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
            static const DataKind   expectedArrayTwoMapsBytes[] =
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
            const size_t            expectedArrayTwoMapsByteCount = A_SIZE(expectedArrayTwoMapsBytes);
#if 0
            static const uint8_t    transmitArrayTwoMapsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD4, // Start of first empty Map
                0xE4, // End of first empty Map
                0xD4, // Start of first empty Map
                0xE4, // End of first empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xD6 // Checksum
            };
            const size_t            transmitArrayTwoMapsByteCount = A_SIZE(transmitArrayTwoMapsBytes);
            Array                   arrayTwoMaps;

            arrayTwoMaps.addValue(std::make_shared<Map>());
            arrayTwoMaps.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayTwoMaps, expectedArrayTwoMapsBytes, expectedArrayTwoMapsByteCount,
                                      transmitArrayTwoMapsBytes, transmitArrayTwoMapsByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two maps message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two sets message
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
            static const DataKind   expectedArrayTwoSetsBytes[] =
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
            const size_t            expectedArrayTwoSetsByteCount = A_SIZE(expectedArrayTwoSetsBytes);
#if 0
            static const uint8_t    transmitArrayTwoSetsBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD8, // Start of first empty Set
                0xE8, // End of first empty Set
                0xD8, // Start of first empty Set
                0xE8, // End of first empty Set
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xC6 // Checksum
            };
            const size_t            transmitArrayTwoSetsByteCount = A_SIZE(transmitArrayTwoSetsBytes);
            Array                   arrayTwoSets;

            arrayTwoSets.addValue(std::make_shared<Set>());
            arrayTwoSets.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayTwoSets, expectedArrayTwoSetsBytes, expectedArrayTwoSetsByteCount,
                                      transmitArrayTwoSetsBytes, transmitArrayTwoSetsByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with two sets message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with array and map message
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
            static const DataKind   expectedArrayOneArrayOneMapBytes[] =
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
            const size_t            expectedArrayOneArrayOneMapByteCount = A_SIZE(expectedArrayOneArrayOneMapBytes);
#if 0
            static const uint8_t    transmitArrayOneArrayOneMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xDE // Checksum
            };
            const size_t            transmitArrayOneArrayOneMapByteCount = A_SIZE(transmitArrayOneArrayOneMapBytes);
            Array                   arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(std::make_shared<Array>());
            arrayOneArrayOneMap.addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneArrayOneMap, expectedArrayOneArrayOneMapBytes, expectedArrayOneArrayOneMapByteCount,
                                      transmitArrayOneArrayOneMapBytes, transmitArrayOneArrayOneMapByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with array and map message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with map and set message
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
            static const DataKind   expectedArrayOneMapOneSetBytes[] =
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
            const size_t            expectedArrayOneMapOneSetByteCount = A_SIZE(expectedArrayOneMapOneSetBytes);
#if 0
            static const uint8_t    transmitArrayOneMapOneSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD4, // Start of empty Map
                0xE4, // End of empty Map
                0xD8, // Start of empty Set
                0xE8, // End of empty Set
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xCE // Checksum
            };
            const size_t            transmitArrayOneMapOneSetByteCount = A_SIZE(transmitArrayOneMapOneSetBytes);
            Array                   arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(std::make_shared<Map>());
            arrayOneMapOneSet.addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneMapOneSet, expectedArrayOneMapOneSetBytes, expectedArrayOneMapOneSetByteCount,
                                      transmitArrayOneMapOneSetBytes, transmitArrayOneMapOneSetByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with map and set message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with set and array message
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
            static const DataKind   expectedArrayOneSetOneArrayBytes[] =
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
            const size_t            expectedArrayOneSetOneArrayByteCount = A_SIZE(expectedArrayOneSetOneArrayBytes);
#if 0
            static const uint8_t    transmitArrayOneSetOneArrayBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x11, // Start of non-empty Array, two elements
                0xD8, // Start of empty Set
                0xE8, // End of empty Set
                0xD0, // Start of empty Array
                0xE0, // End of empty Array
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xD6 // Checksum
            };
            const size_t            transmitArrayOneSetOneArrayByteCount = A_SIZE(transmitArrayOneSetOneArrayBytes);
            Array                   arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(std::make_shared<Set>());
            arrayOneSetOneArray.addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneSetOneArray, expectedArrayOneSetOneArrayBytes, expectedArrayOneSetOneArrayByteCount,
                                      transmitArrayOneSetOneArrayBytes, transmitArrayOneSetOneArrayByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with set and array message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with many doubles message
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
            const size_t            numValues = 43;
            static const DataKind   expectedArrayManyDoublesBytes[] =
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
            const size_t            expectedArrayManyDoublesByteCount = A_SIZE(expectedArrayManyDoublesBytes);
#if 0
            static const uint8_t    transmitArrayManyDoublesBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD1, 0x20, 0x1A, // Start of non-empty Array, 42 elements
                0x60, 0x2B, // Count of doubles that follow
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0
                0x3F, 0xDC, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 1 [note the escape]
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
                0xE1, // End of non-empty Array
                0xFF, // End of message, last is Other
                0xBA // Checksum
            };
            const size_t            transmitArrayManyDoublesByteCount = A_SIZE(transmitArrayManyDoublesBytes);
            Array                   arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = setValueAndCheck(*stuff, arrayManyDoubles, expectedArrayManyDoublesBytes, expectedArrayManyDoublesByteCount,
                                      transmitArrayManyDoublesBytes, transmitArrayManyDoublesByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with many doubles message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // logical map message
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
            static const DataKind   expectedLogicalMapBytes[] =
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
            const size_t            expectedLogicalMapByteCount = A_SIZE(expectedLogicalMapBytes);
#if 0
            static const uint8_t    transmitLogicalMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD5, 0x10, // Start of non-empty Map, one element
                0xC0, // Logical key = false
                0x0D, // Integer value = 13
                0xE5, // End of non-empty Map
                0xFF, // End of message, last is Other
                0x72 // Checksum
            };
            const size_t            transmitLogicalMapByteCount = A_SIZE(transmitLogicalMapBytes);
            Map                     logicalMap;

            logicalMap.addValue(std::make_shared<Logical>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, logicalMap, expectedLogicalMapBytes, expectedLogicalMapByteCount, transmitLogicalMapBytes,
                                      transmitLogicalMapByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // logical map message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // integer map message
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
            static const DataKind   expectedIntegerMapBytes[] =
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
            const size_t            expectedIntegerMapByteCount = A_SIZE(expectedIntegerMapBytes);
#if 0
            static const uint8_t    transmitIntegerMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD5, 0x10, // Start of non-empty Map, one element
                0x00, // Integer key = 0
                0x0D, // Integer value = 13
                0xE5, // End of non-empty Map
                0xFF, // End of message, last is Other
                0x32 // Checksum
            };
            const size_t            transmitIntegerMapByteCount = A_SIZE(transmitIntegerMapBytes);
            Map                     integerMap;

            integerMap.addValue(std::make_shared<Integer>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, integerMap, expectedIntegerMapBytes, expectedIntegerMapByteCount, transmitIntegerMapBytes,
                                      transmitIntegerMapByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // integer map message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // integer map message
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
            static const DataKind   expectedStringMapBytes[] =
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
            const size_t            expectedStringMapByteCount = A_SIZE(expectedStringMapBytes);
#if 0
            static const uint8_t    transmitStringMapBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD5, 0x10, // Start of non-empty Map, one element
                0x80, // String key = empty
                0x0D, // Integer value = 13
                0xE5, // End of non-empty Map
                0xFF, // End of message, last is Other
                0xB2 // Checksum
            };
            const size_t            transmitStringMapByteCount = A_SIZE(transmitStringMapBytes);
            Map                     stringMap;

            stringMap.addValue(std::make_shared<String>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, stringMap, expectedStringMapBytes, expectedStringMapByteCount, transmitStringMapBytes,
                                      transmitStringMapByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // string map message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // logical set message
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
            static const DataKind   expectedLogicalSetBytes[] =
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
            const size_t            expectedLogicalSetByteCount = A_SIZE(expectedLogicalSetBytes);
#if 0
            static const uint8_t    transmitLogicalSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD9, 0x10, // Start of non-empty Set, one element
                0xC0, // Logical key = false
                0xE9, // End of non-empty Set
                0xFF, // End of message, last is Other
                0x77 // Checksum
            };
            const size_t            transmitLogicalSetByteCount = A_SIZE(transmitLogicalSetBytes);
            Set                     logicalSet;

            logicalSet.addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, logicalSet, expectedLogicalSetBytes, expectedLogicalSetByteCount, transmitLogicalSetBytes,
                                      transmitLogicalSetByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // logical set message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // integer set message
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
            static const DataKind   expectedIntegerSetBytes[] =
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
            const size_t            expectedIntegerSetByteCount = A_SIZE(expectedIntegerSetBytes);
#if 0
            static const uint8_t    transmitIntegerSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD9, 0x10, // Start of non-empty Set, one element
                0x00, // Integer key = 0
                0xE9, // End of non-empty Set
                0xFF, // End of message, last is Other
                0x37 // Checksum
            };
            const size_t            transmitIntegerSetByteCount = A_SIZE(transmitIntegerSetBytes);
            Set                     integerSet;

            integerSet.addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, integerSet, expectedIntegerSetBytes, expectedIntegerSetByteCount, transmitIntegerSetBytes,
                                      transmitIntegerSetByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // integer set message
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
#if 0
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
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // integer set message
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
            static const DataKind   expectedStringSetBytes[] =
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
            const size_t            expectedStringSetByteCount = A_SIZE(expectedStringSetBytes);
#if 0
            static const uint8_t    transmitStringSetBytes[] =
            {
                0xF7, // Start of message, next is Other
                0xD9, 0x10, // Start of non-empty Set, one element
                0x80, // String key = empty
                0xE9, // End of non-empty Set
                0xFF, // End of message, last is Other
                0xB7 // Checksum
            };
            const size_t            transmitStringSetByteCount = A_SIZE(transmitStringSetBytes);
            Set                     stringSet;

            stringSet.addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, stringSet, expectedStringSetBytes, expectedStringSetByteCount, transmitStringSetBytes,
                                      transmitStringSetByteCount);
#endif//0
        }
        else
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
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // string set message
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
#if 0
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
#endif//0
        }
        else
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
doTestMIMEExtractMessageWithArrayWithRangeOfIntegers
    (const char *   launchPath,
     const int      argc,
     char * *       argv) // array with range of integers
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
#if 0
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
#endif//0
        }
        else
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
} // doTestMIMEExtractMessageWithArrayWithRangeOfIntegers

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
    (int        argc,
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

                    case 27 :
                        result = doTestMIMEInsertMultipleEscapesMessage(*argv, argc - 1, argv + 2);
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
                        result = doTestMIMEExtractMessageWithArrayWithRangeOfIntegers(*argv, argc - 1, argv + 2);
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

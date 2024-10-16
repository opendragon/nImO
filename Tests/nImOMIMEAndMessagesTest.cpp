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
#include <nImOMIMESupport.h>

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

/*! @brief The number of tests of MIME sets. */
constexpr int   kMaxMIMETests{100};

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
    (Message &          stuff,
     SpValue            aValue,
     CPtr(std::string)  expectedContents,
     const size_t       expectedSize)
{
    ODL_ENTER(); //####
    ODL_P3(&stuff, aValue.get(), expectedContents); //####
    ODL_I1(expectedSize); //####
    stuff.open(true);
    stuff.setValue(aValue);
    stuff.close();
    int result{1};

    if (0 < stuff.getLength())
    {
        auto    asString{stuff.getString()};

        if (asString.empty())
        {
            ODL_LOG("(asString.empty())"); //####
        }
        else
        {
            StdStringVector outVec;

            EncodeBytesAsMIME(outVec, asString);
            if (expectedSize == outVec.size())
            {
                result = 0;
                for (size_t ii = 0; (0 == result) && (ii < expectedSize); ++ii)
                {
                    auto    expectedString{expectedContents[ii]};
                    auto    outString{outVec[ii]};

                    ODL_S2s(expectedString, outString); //####
                    if (expectedString != outString)
                    {
                        ODL_LOG("(expectedString != outString)"); //####
                        result = 1;
                    }
                }
            }
            else
            {
                ODL_LOG("! (expectedSize == outVec.size())"); //####
            }
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
    ODL_P3(&stuff, insertedContents, &expectedValue); //####
    ODL_I1(insertedSize); //####
    ODL_PACKET("inserted", insertedContents, insertedSize); //####
    int             result{1};
    StdStringVector inVec;
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
            auto    extractedValue{stuff.getValue()};

            ODL_P1(extractedValue.get()); //####
            stuff.close();
            if (stuff.readAtEnd())
            {
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
doTestMIMEBytesMod3Is0
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
        StdStringVector inOutValue;
        ByteVector      inValue;
        ByteVector      outValue;

        for (int ii = 0; ii < kMaxMIMETests; ++ii)
        {
            int mm{ii * 3};

            inValue.clear();
            inValue.reserve(mm);
            for (int jj = 0; jj < mm; ++jj)
            {
                inValue.push_back(nImO::RandomUnsigned() % 0x00FF);
            }
            inOutValue.clear();
            EncodeBytesAsMIME(inOutValue, inValue.data(), inValue.size());
            outValue.clear();
            DecodeMIMEToBytes(inOutValue, outValue);
            if (inValue.size() == outValue.size())
            {
                if (0 != memcmp(inValue.data(), outValue.data(), inValue.size()))
                {
                    ODL_LOG("(0 != memcmp(inValue.data(), outValue.data(), inValue.size()))"); //####
                    result = 1;
                    break;
                }
                result = 0;
            }
            else
            {
                ODL_LOG("! (inValue.size() == outValue.size())"); //####
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
} // doTestMIMEBytesMod3Is0

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEBytesMod3Is1
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
        StdStringVector inOutValue;
        ByteVector      inValue;
        ByteVector      outValue;

        for (int ii = 0; ii < kMaxMIMETests; ++ii)
        {
            int mm{(ii * 3) + 1};

            inValue.clear();
            inValue.reserve(mm);
            for (int jj = 0; jj < mm; ++jj)
            {
                inValue.push_back(nImO::RandomUnsigned() % 0x00FF);
            }
            inOutValue.clear();
            EncodeBytesAsMIME(inOutValue, inValue.data(), inValue.size());
            outValue.clear();
            DecodeMIMEToBytes(inOutValue, outValue);
            if (inValue.size() == outValue.size())
            {
                if (0 != memcmp(inValue.data(), outValue.data(), inValue.size()))
                {
                    ODL_LOG("(0 != memcmp(inValue.data(), outValue.data(), inValue.size()))"); //####
                    result = 1;
                    break;
                }
                result = 0;
            }
            else
            {
                ODL_LOG("! (inValue.size() == outValue.size())"); //####
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
} // doTestMIMEBytesMod3Is1

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEBytesMod3Is2
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
        StdStringVector inOutValue;
        ByteVector      inValue;
        ByteVector      outValue;

        for (int ii = 0; ii < kMaxMIMETests; ++ii)
        {
            int mm{(ii * 3) + 2};

            inValue.clear();
            inValue.reserve(mm);
            for (int jj = 0; jj < mm; ++jj)
            {
                inValue.push_back(nImO::RandomUnsigned() % 0x00FF);
            }
            inOutValue.clear();
            EncodeBytesAsMIME(inOutValue, inValue.data(), inValue.size());
            outValue.clear();
            DecodeMIMEToBytes(inOutValue, outValue);
            if (inValue.size() == outValue.size())
            {
                if (0 != memcmp(inValue.data(), outValue.data(), inValue.size()))
                {
                    ODL_LOG("(0 != memcmp(inValue.data(), outValue.data(), inValue.size()))"); //####
                    result = 1;
                    break;
                }
                result = 0;
            }
            else
            {
                ODL_LOG("! (inValue.size() == outValue.size())"); //####
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
} // doTestMIMEBytesMod3Is2

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEBytesMod3Is0Packaged
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
        StdStringVector inOutValue;
        ByteVector      inValue;
        ByteVector      outValue;

        for (int ii = 0; ii < kMaxMIMETests; ++ii)
        {
            int mm{ii * 3};

            inValue.clear();
            inValue.reserve(mm);
            for (int jj = 0; jj < mm; ++jj)
            {
                inValue.push_back(nImO::RandomUnsigned() % 0x00FF);
            }
            inOutValue.clear();
            EncodeBytesAsMIME(inOutValue, inValue.data(), inValue.size());
            auto    inOutString{PackageMessage(inOutValue)};
            auto    inOutTrimmed{nImO::UnpackageMessage(*inOutString)};

            outValue.clear();
            DecodeMIMEToBytes(inOutTrimmed, outValue);
            if (inValue.size() == outValue.size())
            {
                if (0 != memcmp(inValue.data(), outValue.data(), inValue.size()))
                {
                    ODL_LOG("(0 != memcmp(inValue.data(), outValue.data(), inValue.size()))"); //####
                    result = 1;
                    break;
                }
                result = 0;
            }
            else
            {
                ODL_LOG("! (inValue.size() == outValue.size())"); //####
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
} // doTestMIMEBytesMod3Is0Packaged

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEBytesMod3Is1Packaged
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
        StdStringVector inOutValue;
        ByteVector      inValue;
        ByteVector      outValue;

        for (int ii = 0; ii < kMaxMIMETests; ++ii)
        {
            int mm{(ii * 3) + 1};

            inValue.clear();
            inValue.reserve(mm);
            for (int jj = 0; jj < mm; ++jj)
            {
                inValue.push_back(nImO::RandomUnsigned() % 0x00FF);
            }
            inOutValue.clear();
            EncodeBytesAsMIME(inOutValue, inValue.data(), inValue.size());
            auto    inOutString{PackageMessage(inOutValue)};
            auto    inOutTrimmed{nImO::UnpackageMessage(*inOutString)};

            outValue.clear();
            DecodeMIMEToBytes(inOutTrimmed, outValue);
            if (inValue.size() == outValue.size())
            {
                if (0 != memcmp(inValue.data(), outValue.data(), inValue.size()))
                {
                    ODL_LOG("(0 != memcmp(inValue.data(), outValue.data(), inValue.size()))"); //####
                    result = 1;
                    break;
                }
                result = 0;
            }
            else
            {
                ODL_LOG("! (inValue.size() == outValue.size())"); //####
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
} // doTestMIMEBytesMod3Is1Packaged

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEBytesMod3Is2Packaged
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
        StdStringVector inOutValue;
        ByteVector      inValue;
        ByteVector      outValue;

        for (int ii = 0; ii < kMaxMIMETests; ++ii)
        {
            int mm{(ii * 3) + 2};

            inValue.clear();
            inValue.reserve(mm);
            for (int jj = 0; jj < mm; ++jj)
            {
                inValue.push_back(nImO::RandomUnsigned() % 0x00FF);
            }
            inOutValue.clear();
            EncodeBytesAsMIME(inOutValue, inValue.data(), inValue.size());
            auto    inOutString{PackageMessage(inOutValue)};
            auto    inOutTrimmed{nImO::UnpackageMessage(*inOutString)};

            outValue.clear();
            DecodeMIMEToBytes(inOutTrimmed, outValue);
            if (inValue.size() == outValue.size())
            {
                if (0 != memcmp(inValue.data(), outValue.data(), inValue.size()))
                {
                    ODL_LOG("(0 != memcmp(inValue.data(), outValue.data(), inValue.size()))"); //####
                    result = 1;
                    break;
                }
                result = 0;
            }
            else
            {
                ODL_LOG("! (inValue.size() == outValue.size())"); //####
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
} // doTestMIMEBytesMod3Is2Packaged

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
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
            stuff->open(true);
            stuff->close();
            if (0 < stuff->getLength())
            {
                auto    asString{stuff->getString()};

                if (asString.empty())
                {
                    ODL_LOG("(asString.empty())"); //####
                }
                else
                {
                    std::string         expectedLines[]{ "8Pg="s };
                    constexpr size_t    expectedLinesCount{numElementsInArray(expectedLines)};
                    StdStringVector     outVec;

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
# pragma mark *** Test Case 101 ***
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
            StdStringVector inVec;
            ByteVector      outBytes;

            inVec.push_back("8Pg=");
            if (DecodeMIMEToBytes(inVec, outBytes))
            {
                if (0 < outBytes.size())
                {
                    stuff->open(false);
                    stuff->appendBytes(outBytes.data(), outBytes.size());
                    auto    extractedValue{stuff->getValue()};

                    ODL_P1(extractedValue.get()); //####
                    stuff->close();
                    if (stuff->readAtEnd())
                    {
                        if (extractedValue)
                        {
                            auto    asFlaw{extractedValue->asFlaw()};

                            if (nullptr == asFlaw)
                            {
                                ODL_LOG("(nullptr == asFlaw)"); //####
                            }
                            else
                            {
                                ODL_LOG(asFlaw->getDescription().c_str()); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (extractedValue)"); //####
                            result = 0;
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
# pragma mark *** Test Case 102 ***
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
            auto                falseValue{std::make_shared<Logical>(false)};
            auto                trueValue{std::make_shared<Logical>(true)};
            std::string         expectedTrueLines[]{ "98H/"s };
            constexpr size_t    expectedTrueLinesCount{numElementsInArray(expectedTrueLines)};
            std::string         expectedFalseLines[]{ "98D/"s };
            constexpr size_t    expectedFalseLinesCount{numElementsInArray(expectedFalseLines)};

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
# pragma mark *** Test Case 103 ***
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
            std::string         insertedTrueLines[]{ "98H/"s };
            constexpr size_t    insertedTrueLinesCount{numElementsInArray(insertedTrueLines)};
            std::string         insertedFalseLines[]{ "98D/"s };
            constexpr size_t    insertedFalseLinesCount{numElementsInArray(insertedFalseLines)};
            Logical             falseValue{false};
            Logical             trueValue{true};

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
# pragma mark *** Test Case 104 ***
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
            auto                minus12Value{std::make_shared<Integer>(-12)};
            auto                zeroValue{std::make_shared<Integer>()};
            auto                plus12Value{std::make_shared<Integer>(12)};
            std::string         expectedMinus12Lines[]{ "9BT8"s };
            constexpr size_t    expectedMinus12LinesCount{numElementsInArray(expectedMinus12Lines)};
            std::string         expectedZeroLines[]{ "9AD8"s };
            constexpr size_t    expectedZeroLinesCount{numElementsInArray(expectedZeroLines)};
            std::string         expectedPlus12Lines[]{ "9Az8"s };
            constexpr size_t    expectedPlus12LinesCount{numElementsInArray(expectedPlus12Lines)};

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
# pragma mark *** Test Case 105 ***
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
            std::string         insertedMinus12Lines[]{ "9BT8"s };
            constexpr size_t    insertedMinus12LinesCount{numElementsInArray(insertedMinus12Lines)};
            std::string         insertedZeroLines[]{ "9AD8"s };
            constexpr size_t    insertedZeroLinesCount{numElementsInArray(insertedZeroLines)};
            std::string         insertedPlus12Lines[]{ "9Az8"s };
            constexpr size_t    insertedPlus12LinesCount{numElementsInArray(insertedPlus12Lines)};
            Integer             minus12Value{-12};
            Integer             zeroValue{0};
            Integer             plus12Value{12};

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
# pragma mark *** Test Case 106 ***
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
            auto                minus144Value{std::make_shared<Integer>(-144)};
            auto                plus144Value{std::make_shared<Integer>(144)};
            std::string         expectedMinus144Lines[]{ "9CH/cPw="s };
            constexpr size_t    expectedMinus144LinesCount{numElementsInArray(expectedMinus144Lines)};
            std::string         expectedPlus144Lines[]{ "9CEAkPw="s };
            constexpr size_t    expectedPlus144LinesCount{numElementsInArray(expectedPlus144Lines)};

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
# pragma mark *** Test Case 107 ***
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
            std::string         insertedMinus144Lines[]{ "9CH/cPw="s };
            constexpr size_t    insertedMinus144LinesCount{numElementsInArray(insertedMinus144Lines)};
            std::string         insertedPlus144Lines[]{ "9CEAkPw="s };
            constexpr size_t    insertedPlus144LinesCount{numElementsInArray(insertedPlus144Lines)};
            Integer             minus144Value{-144};
            Integer             plus144Value{144};

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
# pragma mark *** Test Case 108 ***
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
            auto                minus1234567Value{std::make_shared<Integer>(-1234567)};
            auto                plus1234567Value{std::make_shared<Integer>(1234567)};
            std::string         expectedMinus1234567Lines[]{ "9CLtKXn8"s };
            constexpr size_t    expectedMinus1234567LinesCount{numElementsInArray(expectedMinus1234567Lines)};
            std::string         expectedPlus1234567Lines[]{ "9CIS1of8"s };
            constexpr size_t    expectedPlus1234567LinesCount{numElementsInArray(expectedPlus1234567Lines)};

            result = setValueAndCheck(*stuff, minus1234567Value, expectedMinus1234567Lines, expectedMinus1234567LinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plus1234567Value, expectedPlus1234567Lines, expectedPlus1234567LinesCount);
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
# pragma mark *** Test Case 109 ***
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
            std::string         insertedMinus1234567Lines[]{ "9CLtKXn8"s };
            constexpr size_t    insertedMinus1234567LinesCount{numElementsInArray(insertedMinus1234567Lines)};
            std::string         insertedPlus1234567Lines[]{ "9CIS1of8"s };
            constexpr size_t    insertedPlus1234567LinesCount{numElementsInArray(insertedPlus1234567Lines)};
            Integer             minus1234567Value{-1234567};
            Integer             plus1234567Value{1234567};

            result = extractValueAndCheck(*stuff, insertedMinus1234567Lines, insertedMinus1234567LinesCount, minus1234567Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedPlus1234567Lines, insertedPlus1234567LinesCount, plus1234567Value);
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
# pragma mark *** Test Case 110 ***
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
            auto                minusBigNumberValue{std::make_shared<Integer>(-20015998343868)};
            auto                plusBigNumberValue{std::make_shared<Integer>(20015998343868)};
            std::string         expectedMinusBigNumberLines[]{ "9CXty6mHZUT8"s };
            constexpr size_t    expectedMinusBigNumberLinesCount{numElementsInArray(expectedMinusBigNumberLines)};
            std::string         expectedPlusBigNumberLines[]{ "9CUSNFZ4mrz8"s };
            constexpr size_t    expectedPlusBigNumberLinesCount{numElementsInArray(expectedPlusBigNumberLines)};

            result = setValueAndCheck(*stuff, minusBigNumberValue, expectedMinusBigNumberLines, expectedMinusBigNumberLinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, plusBigNumberValue, expectedPlusBigNumberLines, expectedPlusBigNumberLinesCount);
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
# pragma mark *** Test Case 111 ***
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
            std::string         insertedMinusBigNumberLines[]{ "9CXty6mHZUT8"s };
            constexpr size_t    insertedMinusBigNumberLinesCount{numElementsInArray(insertedMinusBigNumberLines)};
            std::string         insertedPlusBigNumberLines[]{ "9CUSNFZ4mrz8"s };
            constexpr size_t    insertedPlusBigNumberLinesCount{numElementsInArray(insertedPlusBigNumberLines)};
            Integer             minusBigNumberValue{-20015998343868};
            Integer             plusBigNumberValue{20015998343868};

            result = extractValueAndCheck(*stuff, insertedMinusBigNumberLines, insertedMinusBigNumberLinesCount, minusBigNumberValue);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedPlusBigNumberLines, insertedPlusBigNumberLinesCount, plusBigNumberValue);
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
# pragma mark *** Test Case 112 ***
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
            auto                emptyStringValue{std::make_shared<String>()};
            std::string         expectedEmptyStringLines[]{ "9oD+"s };
            constexpr size_t    expectedEmptyStringLinesCount{numElementsInArray(expectedEmptyStringLines)};

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
# pragma mark *** Test Case 113 ***
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
            std::string         insertedEmptyStringLines[]{ "9oD+"s };
            constexpr size_t    insertedEmptyStringLinesCount{numElementsInArray(insertedEmptyStringLines)};
            String              emptyStringValue;

            result = extractValueAndCheck(*stuff, insertedEmptyStringLines, insertedEmptyStringLinesCount, emptyStringValue);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 114 ***
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
            auto                shortStringValue{std::make_shared<String>("abcdef"s)};
            std::string         expectedShortStringLines[]{ "9oZhYmNkZWb+"s };
            constexpr size_t    expectedShortStringLinesCount{numElementsInArray(expectedShortStringLines)};

            result = setValueAndCheck(*stuff, shortStringValue, expectedShortStringLines, expectedShortStringLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 115 ***
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
            std::string         insertedShortStringLines[]{ "9oZhYmNkZWb+"s };
            constexpr size_t    insertedShortStringLinesCount{numElementsInArray(insertedShortStringLines)};
            String              shortStringValue{"abcdef"s};

            result = extractValueAndCheck(*stuff, insertedShortStringLines, insertedShortStringLinesCount, shortStringValue);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 116 ***
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
            auto                mediumStringValue{std::make_shared<String>("abcdefabcdefabcdefabcdefabcdefabcdefabcdef"s)};
            std::string         expectedMediumStringLines[]{ "9pAqYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVm/g=="s };
            constexpr size_t    expectedMediumStringLinesCount{numElementsInArray(expectedMediumStringLines)};

            result = setValueAndCheck(*stuff, mediumStringValue, expectedMediumStringLines, expectedMediumStringLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 117 ***
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
            std::string         insertedMediumStringLines[]{ "9pAqYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVmYWJjZGVm/g=="s };
            constexpr size_t    insertedMediumStringLinesCount{numElementsInArray(insertedMediumStringLines)};
            String              mediumStringValue{"abcdefabcdefabcdefabcdefabcdefabcdefabcdef"s};

            result = extractValueAndCheck(*stuff, insertedMediumStringLines, insertedMediumStringLinesCount, mediumStringValue);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 118 ***
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
            auto                emptyBlobValue{std::make_shared<Blob>()};
            std::string         expectedEmptyBlobLines[]{ "9qD+"s };
            constexpr size_t    expectedEmptyBlobLinesCount{numElementsInArray(expectedEmptyBlobLines)};

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
# pragma mark *** Test Case 119 ***
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
            std::string         insertedEmptyBlobLines[]{ "9qD+"s };
            constexpr size_t    insertedEmptyBlobLinesCount{numElementsInArray(insertedEmptyBlobLines)};
            Blob                emptyBlobValue;

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
# pragma mark *** Test Case 120 ***
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
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            constexpr size_t        actualDataCount{numElementsInArray(actualData)};
            auto                    smallBlobValue{std::make_shared<Blob>(actualData, actualDataCount)};
            std::string             expectedSmallBlobLines[]{ "9qYSIzRFVmf+"s };
            constexpr size_t        expectedSmallBlobLinesCount{numElementsInArray(expectedSmallBlobLines)};

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
# pragma mark *** Test Case 121 ***
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
            std::string             insertedSmallBlobLines[]{ "9qYSIzRFVmf+"s };
            constexpr size_t        insertedSmallBlobLinesCount{numElementsInArray(insertedSmallBlobLines)};
            static const uint8_t    actualData[]
            {
                0x12, 0x23, 0x34, 0x45, 0x56, 0x67
            };
            constexpr size_t        actualDataCount{numElementsInArray(actualData)};
            Blob                    smallBlobValue{actualData, actualDataCount};

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
# pragma mark *** Test Case 122 ***
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
            std::string             expectedMediumBlobLines[]{ "9rAqEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZn/g=="s };
            constexpr size_t        expectedMediumBlobLinesCount{numElementsInArray(expectedMediumBlobLines)};

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
# pragma mark *** Test Case 123 ***
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
            std::string             insertedMediumBlobLines[]{ "9rAqEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZnEiM0RVZn/g=="s };
            constexpr size_t        insertedMediumBlobLinesCount{numElementsInArray(insertedMediumBlobLines)};
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

            result = extractValueAndCheck(*stuff, insertedMediumBlobLines, insertedMediumBlobLinesCount, mediumBlobValue);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 124 ***
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
            auto                plus42Point5Value{std::make_shared<Double>(42.5)};
            auto                minus42Point5Value{std::make_shared<Double>(-42.5)};
            std::string         expectedPlus42Point5Lines[]{ "9UBARUAAAAAAAP0="s };
            constexpr size_t    expectedPlus42Point5LinesCount{numElementsInArray(expectedPlus42Point5Lines)};
            std::string         expectedMinus42Point5Lines[]{ "9UDARUAAAAAAAP0="s };
            constexpr size_t    expectedMinus42Point5LinesCount{numElementsInArray(expectedMinus42Point5Lines)};

            result = setValueAndCheck(*stuff, plus42Point5Value, expectedPlus42Point5Lines, expectedPlus42Point5LinesCount);
            if (0 == result)
            {
                result = setValueAndCheck(*stuff, minus42Point5Value, expectedMinus42Point5Lines, expectedMinus42Point5LinesCount);
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
# pragma mark *** Test Case 125 ***
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
            std::string         insertedPlus42Point5Lines[]{ "9UBARUAAAAAAAP0="s };
            constexpr size_t    insertedPlus42Point5LinesCount{numElementsInArray(insertedPlus42Point5Lines)};
            std::string         insertedMinus42Point5Lines[]{ "9UDARUAAAAAAAP0="s };
            constexpr size_t    insertedMinus42Point5LinesCount{numElementsInArray(insertedMinus42Point5Lines)};
            Double              plus42Point5Value{42.5};
            Double              minus42Point5Value{-42.5};

            result = extractValueAndCheck(*stuff, insertedPlus42Point5Lines, insertedPlus42Point5LinesCount, plus42Point5Value);
            if (0 == result)
            {
                result = extractValueAndCheck(*stuff, insertedMinus42Point5Lines, insertedMinus42Point5LinesCount, minus42Point5Value);
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
# pragma mark *** Test Case 126 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertAddressMessage
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
            auto                addressValue{std::make_shared<Address>(0x12345678)};
            std::string         expectedAddressLines[]{ "98QSNFZ4/w=="s };
            constexpr size_t    expectedAddressLinesCount{numElementsInArray(expectedAddressLines)};

            result = setValueAndCheck(*stuff, addressValue, expectedAddressLines, expectedAddressLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 127 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractAddressMessage
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
            std::string         insertedAddressLines[]{ "98QSNFZ4/w=="s };
            constexpr size_t    insertedAddressLinesCount{numElementsInArray(insertedAddressLines)};
            Address             addressValue{0x12345678};

            result = extractValueAndCheck(*stuff, insertedAddressLines, insertedAddressLinesCount, addressValue);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 128 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertDateMessage
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
            auto                            dateValue{std::make_shared<Date>(MakeDateValue(aDate))};
            std::string                     expectedDateLines[]{ "98UAABTq/w=="s };
            constexpr size_t                expectedDateLinesCount{numElementsInArray(expectedDateLines)};

            result = setValueAndCheck(*stuff, dateValue, expectedDateLines, expectedDateLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 129 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractDateMessage
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
            std::string                     insertedDateLines[]{ "98UAABTq/w=="s };
            constexpr size_t                insertedDateLinesCount{numElementsInArray(insertedDateLines)};
            Date                            dateValue{MakeDateValue(aDate)};

            result = extractValueAndCheck(*stuff, insertedDateLines, insertedDateLinesCount, dateValue);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 130 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertTimeMessage
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
            auto                            timeValue{std::make_shared<Time>(MakeTimeValue(aTime))};
            std::string                     expectedTimeLines[]{ "98YCnWc5/w=="s };
            constexpr size_t                expectedTimeLinesCount{numElementsInArray(expectedTimeLines)};

            result = setValueAndCheck(*stuff, timeValue, expectedTimeLines, expectedTimeLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 131 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractTimeMessage
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
            std::string                     insertedTimeLines[]{ "98YCnWc5/w=="s };
            constexpr size_t                insertedTimeLinesCount{numElementsInArray(insertedTimeLines)};
            Time                            timeValue{MakeTimeValue(aTime)};

            result = extractValueAndCheck(*stuff, insertedTimeLines, insertedTimeLinesCount, timeValue);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 200 ***
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
            auto                emptyArray{std::make_shared<Array>()};
            std::string         expectedEmptyArrayLines[]{ "99Dg/w=="s };
            constexpr size_t    expectedEmptyArrayLinesCount{numElementsInArray(expectedEmptyArrayLines)};

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
# pragma mark *** Test Case 201 ***
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
            std::string         insertedEmptyArrayLines[]{ "99Dg/w=="s };
            constexpr size_t    insertedEmptyArrayLinesCount{numElementsInArray(insertedEmptyArrayLines)};
            Array               emptyArray;

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
# pragma mark *** Test Case 202 ***
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
            auto                emptyMap{std::make_shared<Map>()};
            std::string         expectedEmptyMapLines[]{ "99Tk/w=="s };
            constexpr size_t    expectedEmptyMapLinesCount{numElementsInArray(expectedEmptyMapLines)};

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
# pragma mark *** Test Case 203 ***
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
            std::string         insertedEmptyMapLines[]{ "99Tk/w=="s };
            constexpr size_t    insertedEmptyMapLinesCount{numElementsInArray(insertedEmptyMapLines)};
            Map                 emptyMap;

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
# pragma mark *** Test Case 204 ***
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
            auto                emptySet{std::make_shared<Set>()};
            std::string         expectedEmptySetLines[]{ "99jo/w=="s };
            constexpr size_t    expectedEmptySetLinesCount{numElementsInArray(expectedEmptySetLines)};

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
# pragma mark *** Test Case 205 ***
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
            std::string         insertedEmptySetLines[]{ "99jo/w=="s };
            constexpr size_t    insertedEmptySetLinesCount{numElementsInArray(insertedEmptySetLines)};
            Set                 emptySet;

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
# pragma mark *** Test Case 300 ***
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
            auto                arrayOneLogical{std::make_shared<Array>()};
            std::string         expectedArrayOneLogicalLines[]{ "99EQwOH/"s };
            constexpr size_t    expectedArrayOneLogicalLinesCount{numElementsInArray(expectedArrayOneLogicalLines)};

            arrayOneLogical->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayOneLogical, expectedArrayOneLogicalLines, expectedArrayOneLogicalLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 301 ***
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
            std::string         insertedArrayOneLogicalLines[]{ "99EQwOH/"s };
            constexpr size_t    insertedArrayOneLogicalLinesCount{numElementsInArray(insertedArrayOneLogicalLines)};
            Array               arrayOneLogical;

            arrayOneLogical.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedArrayOneLogicalLines, insertedArrayOneLogicalLinesCount, arrayOneLogical);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 302 ***
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
            auto                arrayOneInteger{std::make_shared<Array>()};
            std::string         expectedArrayOneIntegerLines[]{ "99EQAOH/"s };
            constexpr size_t    expectedArrayOneIntegerLinesCount{numElementsInArray(expectedArrayOneIntegerLines)};

            arrayOneInteger->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayOneInteger, expectedArrayOneIntegerLines, expectedArrayOneIntegerLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 303 ***
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
            std::string         insertedArrayOneIntegerLines[]{ "99EQAOH/"s };
            constexpr size_t    insertedArrayOneIntegerLinesCount{numElementsInArray(insertedArrayOneIntegerLines)};
            Array               arrayOneInteger;

            arrayOneInteger.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedArrayOneIntegerLines, insertedArrayOneIntegerLinesCount, arrayOneInteger);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 304 ***
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
            auto                arrayOneDouble{std::make_shared<Array>()};
            std::string         expectedArrayOneDoubleLines[]{ "99EQQAAAAAAAAAAA4f8="s };
            constexpr size_t    expectedArrayOneDoubleLinesCount{numElementsInArray(expectedArrayOneDoubleLines)};

            arrayOneDouble->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayOneDouble, expectedArrayOneDoubleLines, expectedArrayOneDoubleLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 305 ***
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
            std::string         insertedArrayOneDoubleLines[]{ "99EQQAAAAAAAAAAA4f8="s };
            constexpr size_t    insertedArrayOneDoubleLinesCount{numElementsInArray(insertedArrayOneDoubleLines)};
            Array               arrayOneDouble;

            arrayOneDouble.addValue(std::make_shared<Double>());
            result = extractValueAndCheck(*stuff, insertedArrayOneDoubleLines, insertedArrayOneDoubleLinesCount, arrayOneDouble);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 306 ***
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
            auto                arrayOneString{std::make_shared<Array>()};
            std::string         expectedArrayOneStringLines[]{ "99EQgOH/"s };
            constexpr size_t    expectedArrayOneStringLinesCount{numElementsInArray(expectedArrayOneStringLines)};

            arrayOneString->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayOneString, expectedArrayOneStringLines, expectedArrayOneStringLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 307 ***
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
            std::string         insertedArrayOneStringLines[]{ "99EQgOH/"s };
            constexpr size_t    insertedArrayOneStringLinesCount{numElementsInArray(insertedArrayOneStringLines)};
            Array               arrayOneString;

            arrayOneString.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedArrayOneStringLines, insertedArrayOneStringLinesCount, arrayOneString);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 308 ***
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
            auto                arrayOneBlob{std::make_shared<Array>()};
            std::string         expectedArrayOneBlobLines[]{ "99EQoOH/"s };
            constexpr size_t    expectedArrayOneBlobLinesCount{numElementsInArray(expectedArrayOneBlobLines)};

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
# pragma mark *** Test Case 309 ***
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
            std::string         insertedArrayOneBlobLines[]{ "99EQoOH/"s };
            constexpr size_t    insertedArrayOneBlobLinesCount{numElementsInArray(insertedArrayOneBlobLines)};
            Array               arrayOneBlob;

            arrayOneBlob.addValue(std::make_shared<Blob>());
            result = extractValueAndCheck(*stuff, insertedArrayOneBlobLines, insertedArrayOneBlobLinesCount, arrayOneBlob);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 310 ***
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
            auto                arrayOneArray{std::make_shared<Array>()};
            std::string         expectedArrayOneArrayLines[]{ "99EQ0ODh/w=="s };
            constexpr size_t    expectedArrayOneArrayLinesCount{numElementsInArray(expectedArrayOneArrayLines)};

            arrayOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneArray, expectedArrayOneArrayLines, expectedArrayOneArrayLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 311 ***
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
            std::string         insertedArrayOneArrayLines[]{ "99EQ0ODh/w=="s };
            constexpr size_t    insertedArrayOneArrayLinesCount{numElementsInArray(insertedArrayOneArrayLines)};
            Array               arrayOneArray;

            arrayOneArray.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedArrayOneArrayLines, insertedArrayOneArrayLinesCount, arrayOneArray);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 312 ***
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
            auto                arrayOneMap{std::make_shared<Array>()};
            std::string         expectedArrayOneMapLines[]{ "99EQ1OTh/w=="s };
            constexpr size_t    expectedArrayOneMapLinesCount{numElementsInArray(expectedArrayOneMapLines)};

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
# pragma mark *** Test Case 313 ***
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
            std::string         insertedArrayOneMapLines[]{ "99EQ1OTh/w=="s };
            constexpr size_t    insertedArrayOneMapLinesCount{numElementsInArray(insertedArrayOneMapLines)};
            Array               arrayOneMap;

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
# pragma mark *** Test Case 314 ***
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
            auto                arrayOneSet{std::make_shared<Array>()};
            std::string         expectedArrayOneSetLines[]{ "99EQ2Ojh/w=="s };
            constexpr size_t    expectedArrayOneSetLinesCount{numElementsInArray(expectedArrayOneSetLines)};

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
# pragma mark *** Test Case 315 ***
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
            std::string         insertedArrayOneSetLines[]{ "99EQ2Ojh/w=="s };
            constexpr size_t    insertedArrayOneSetLinesCount{numElementsInArray(insertedArrayOneSetLines)};
            Array               arrayOneSet;

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
# pragma mark *** Test Case 316 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithOneAddressMessage
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
            auto                arrayOneAddress{std::make_shared<Array>()};
            std::string         expectedArrayOneAddressLines[]{ "99EQxDRWeKvh/w=="s };
            constexpr size_t    expectedArrayOneAddressLinesCount{numElementsInArray(expectedArrayOneAddressLines)};

            arrayOneAddress->addValue(std::make_shared<Address>(0x345678AB));
            result = setValueAndCheck(*stuff, arrayOneAddress, expectedArrayOneAddressLines, expectedArrayOneAddressLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertArrayWithOneAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 317 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithOneAddressMessage
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
            std::string         insertedArrayOneAddressLines[]{ "99EQxDRWeKvh/w=="s };
            constexpr size_t    insertedArrayOneAddressLinesCount{numElementsInArray(insertedArrayOneAddressLines)};
            Array               arrayOneAddress;

            arrayOneAddress.addValue(std::make_shared<Address>(0x345678AB));
            result = extractValueAndCheck(*stuff, insertedArrayOneAddressLines, insertedArrayOneAddressLinesCount, arrayOneAddress);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractArrayWithOneAddressMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 318 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithOneDateMessage
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
            auto                            arrayOneDate{std::make_shared<Array>()};
            std::string                     expectedArrayOneDateLines[]{ "99EQxQAAFOrh/w=="s };
            constexpr size_t                expectedArrayOneDateLinesCount{numElementsInArray(expectedArrayOneDateLines)};

            arrayOneDate->addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = setValueAndCheck(*stuff, arrayOneDate, expectedArrayOneDateLines, expectedArrayOneDateLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertArrayWithOneDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 319 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithOneDateMessage
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
            std::string                     insertedArrayOneDateLines[]{ "99EQxQAAFOrh/w=="s };
            constexpr size_t                insertedArrayOneDateLinesCount{numElementsInArray(insertedArrayOneDateLines)};
            Array                           arrayOneDate;

            arrayOneDate.addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = extractValueAndCheck(*stuff, insertedArrayOneDateLines, insertedArrayOneDateLinesCount, arrayOneDate);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractArrayWithOneDateMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 320 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithOneTimeMessage
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
            auto                            arrayOneTime{std::make_shared<Array>()};
            std::string                     expectedArrayOneTimeLines[]{ "99EQxgKdZznh/w=="s };
            constexpr size_t                expectedArrayOneTimeLinesCount{numElementsInArray(expectedArrayOneTimeLines)};

            arrayOneTime->addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = setValueAndCheck(*stuff, arrayOneTime, expectedArrayOneTimeLines, expectedArrayOneTimeLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertArrayWithOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 321 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithOneTimeMessage
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
            std::string                     insertedArrayOneTimeLines[]{ "99EQxgKdZznh/w=="s };
            constexpr size_t                insertedArrayOneTimeLinesCount{numElementsInArray(insertedArrayOneTimeLines)};
            Array                           arrayOneTime;

            arrayOneTime.addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = extractValueAndCheck(*stuff, insertedArrayOneTimeLines, insertedArrayOneTimeLinesCount, arrayOneTime);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractArrayWithOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 400 ***
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
            auto                arrayTwoLogicals{std::make_shared<Array>()};
            std::string         expectedArrayTwoLogicalsLines[]{ "99ERwMDh/w=="s };
            constexpr size_t    expectedArrayTwoLogicalsLinesCount{numElementsInArray(expectedArrayTwoLogicalsLines)};

            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            arrayTwoLogicals->addValue(std::make_shared<Logical>());
            result = setValueAndCheck(*stuff, arrayTwoLogicals, expectedArrayTwoLogicalsLines, expectedArrayTwoLogicalsLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 401 ***
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
            std::string         insertedArrayTwoLogicalsLines[]{ "99ERwMDh/w=="s };
            constexpr size_t    insertedArrayTwoLogicalsLinesCount{numElementsInArray(insertedArrayTwoLogicalsLines)};
            Array               arrayTwoLogicals;

            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            arrayTwoLogicals.addValue(std::make_shared<Logical>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoLogicalsLines, insertedArrayTwoLogicalsLinesCount, arrayTwoLogicals);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 402 ***
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
            auto                arrayTwoIntegers{std::make_shared<Array>()};
            std::string         expectedArrayTwoIntegersLines[]{ "99ERAADh/w=="s };
            constexpr size_t    expectedArrayTwoIntegersLinesCount{numElementsInArray(expectedArrayTwoIntegersLines)};

            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            arrayTwoIntegers->addValue(std::make_shared<Integer>());
            result = setValueAndCheck(*stuff, arrayTwoIntegers, expectedArrayTwoIntegersLines, expectedArrayTwoIntegersLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 403 ***
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
            std::string         insertedArrayTwoIntegersLines[]{ "99ERAADh/w=="s };
            constexpr size_t    insertedArrayTwoIntegersLinesCount{numElementsInArray(insertedArrayTwoIntegersLines)};
            Array               arrayTwoIntegers;

            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            arrayTwoIntegers.addValue(std::make_shared<Integer>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoIntegersLines, insertedArrayTwoIntegersLinesCount, arrayTwoIntegers);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 404 ***
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
            auto                arrayTwoDoubles{std::make_shared<Array>()};
            std::string         expectedArrayTwoDoublesLines[]{ "99ERQQAAAAAAAAAAAAAAAAAAAADh/w=="s };
            constexpr size_t    expectedArrayTwoDoublesLinesCount{numElementsInArray(expectedArrayTwoDoublesLines)};

            arrayTwoDoubles->addValue(std::make_shared<Double>());
            arrayTwoDoubles->addValue(std::make_shared<Double>());
            result = setValueAndCheck(*stuff, arrayTwoDoubles, expectedArrayTwoDoublesLines, expectedArrayTwoDoublesLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 405 ***
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
            std::string         insertedArrayTwoDoublesLines[]{ "99ERQQAAAAAAAAAAAAAAAAAAAADh/w=="s };
            constexpr size_t    insertedArrayTwoDoublesLinesCount{numElementsInArray(insertedArrayTwoDoublesLines)};
            Array               arrayTwoDoubles;

            arrayTwoDoubles.addValue(std::make_shared<Double>());
            arrayTwoDoubles.addValue(std::make_shared<Double>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoDoublesLines, insertedArrayTwoDoublesLinesCount, arrayTwoDoubles);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 406 ***
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
            auto                arrayTwoStrings{std::make_shared<Array>()};
            std::string         expectedArrayTwoStringsLines[]{ "99ERgIDh/w=="s };
            constexpr size_t    expectedArrayTwoStringsLinesCount{numElementsInArray(expectedArrayTwoStringsLines)};

            arrayTwoStrings->addValue(std::make_shared<String>());
            arrayTwoStrings->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, arrayTwoStrings, expectedArrayTwoStringsLines, expectedArrayTwoStringsLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 407 ***
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
            std::string         insertedArrayTwoStringsLines[]{ "99ERgIDh/w=="s };
            constexpr size_t    insertedArrayTwoStringsLinesCount{numElementsInArray(insertedArrayTwoStringsLines)};
            Array               arrayTwoStrings;

            arrayTwoStrings.addValue(std::make_shared<String>());
            arrayTwoStrings.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoStringsLines, insertedArrayTwoStringsLinesCount, arrayTwoStrings);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 408 ***
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
            auto                arrayTwoBlobs{std::make_shared<Array>()};
            std::string         expectedArrayTwoBlobsLines[]{ "99ERoKDh/w=="s };
            constexpr size_t    expectedArrayTwoBlobsLinesCount{numElementsInArray(expectedArrayTwoBlobsLines)};

            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            arrayTwoBlobs->addValue(std::make_shared<Blob>());
            result = setValueAndCheck(*stuff, arrayTwoBlobs, expectedArrayTwoBlobsLines, expectedArrayTwoBlobsLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 409 ***
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
            std::string         insertedArrayTwoBlobsLines[]{ "99ERoKDh/w=="s };
            constexpr size_t    insertedArrayTwoBlobsLinesCount{numElementsInArray(insertedArrayTwoBlobsLines)};
            Array               arrayTwoBlobs;

            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            arrayTwoBlobs.addValue(std::make_shared<Blob>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoBlobsLines, insertedArrayTwoBlobsLinesCount, arrayTwoBlobs);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 410 ***
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
            auto                arrayTwoArrays{std::make_shared<Array>()};
            std::string         expectedArrayTwoArraysLines[]{ "99ER0ODQ4OH/"s };
            constexpr size_t    expectedArrayTwoArraysLinesCount{numElementsInArray(expectedArrayTwoArraysLines)};

            arrayTwoArrays->addValue(std::make_shared<Array>());
            arrayTwoArrays->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayTwoArrays, expectedArrayTwoArraysLines, expectedArrayTwoArraysLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 411 ***
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
            std::string         insertedArrayTwoArraysLines[]{ "99ER0ODQ4OH/"s };
            constexpr size_t    insertedArrayTwoArraysLinesCount{numElementsInArray(insertedArrayTwoArraysLines)};
            Array               arrayTwoArrays;

            arrayTwoArrays.addValue(std::make_shared<Array>());
            arrayTwoArrays.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoArraysLines, insertedArrayTwoArraysLinesCount, arrayTwoArrays);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 412 ***
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
            auto                arrayTwoMaps{std::make_shared<Array>()};
            std::string         expectedArrayTwoMapsLines[]{ "99ER1OTU5OH/"s };
            constexpr size_t    expectedArrayTwoMapsLinesCount{numElementsInArray(expectedArrayTwoMapsLines)};

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
# pragma mark *** Test Case 413 ***
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
            std::string         insertedArrayTwoMapsLines[]{ "99ER1OTU5OH/"s };
            constexpr size_t    insertedArrayTwoMapsLinesCount{numElementsInArray(insertedArrayTwoMapsLines)};
            Array               arrayTwoMaps;

            arrayTwoMaps.addValue(std::make_shared<Map>());
            arrayTwoMaps.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoMapsLines, insertedArrayTwoMapsLinesCount, arrayTwoMaps);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 414 ***
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
            auto                arrayTwoSets{std::make_shared<Array>()};
            std::string         expectedArrayTwoSetsLines[]{ "99ER2OjY6OH/"s };
            constexpr size_t    expectedArrayTwoSetsLinesCount{numElementsInArray(expectedArrayTwoSetsLines)};

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
# pragma mark *** Test Case 415 ***
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
            std::string         insertedArrayTwoSetsLines[]{ "99ER2OjY6OH/"s };
            constexpr size_t    insertedArrayTwoSetsLinesCount{numElementsInArray(insertedArrayTwoSetsLines)};
            Array               arrayTwoSets;

            arrayTwoSets.addValue(std::make_shared<Set>());
            arrayTwoSets.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedArrayTwoSetsLines, insertedArrayTwoSetsLinesCount, arrayTwoSets);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 416 ***
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
            auto                arrayOneArrayOneMap{std::make_shared<Array>()};
            std::string         expectedArrayOneArrayOneMapLines[]{ "99ER0ODU5OH/"s };
            constexpr size_t    expectedArrayOneArrayOneMapLinesCount{numElementsInArray(expectedArrayOneArrayOneMapLines)};

            arrayOneArrayOneMap->addValue(std::make_shared<Array>());
            arrayOneArrayOneMap->addValue(std::make_shared<Map>());
            result = setValueAndCheck(*stuff, arrayOneArrayOneMap, expectedArrayOneArrayOneMapLines, expectedArrayOneArrayOneMapLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 417 ***
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
            std::string         insertedArrayOneArrayOneMapLines[]{ "99ER0ODU5OH/"s };
            constexpr size_t    insertedArrayOneArrayOneMapLinesCount{numElementsInArray(insertedArrayOneArrayOneMapLines)};
            Array               arrayOneArrayOneMap;

            arrayOneArrayOneMap.addValue(std::make_shared<Array>());
            arrayOneArrayOneMap.addValue(std::make_shared<Map>());
            result = extractValueAndCheck(*stuff, insertedArrayOneArrayOneMapLines, insertedArrayOneArrayOneMapLinesCount, arrayOneArrayOneMap);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 418 ***
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
            auto                arrayOneMapOneSet{std::make_shared<Array>()};
            std::string         expectedArrayOneMapOneSetLines[]{ "99ER1OTY6OH/"s };
            constexpr size_t    expectedArrayOneMapOneSetLinesCount{numElementsInArray(expectedArrayOneMapOneSetLines)};

            arrayOneMapOneSet->addValue(std::make_shared<Map>());
            arrayOneMapOneSet->addValue(std::make_shared<Set>());
            result = setValueAndCheck(*stuff, arrayOneMapOneSet, expectedArrayOneMapOneSetLines, expectedArrayOneMapOneSetLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 419 ***
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
            std::string         insertedArrayOneMapOneSetLines[]{ "99ER1OTY6OH/"s };
            constexpr size_t    insertedArrayOneMapOneSetLinesCount{numElementsInArray(insertedArrayOneMapOneSetLines)};
            Array               arrayOneMapOneSet;

            arrayOneMapOneSet.addValue(std::make_shared<Map>());
            arrayOneMapOneSet.addValue(std::make_shared<Set>());
            result = extractValueAndCheck(*stuff, insertedArrayOneMapOneSetLines, insertedArrayOneMapOneSetLinesCount, arrayOneMapOneSet);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 420 ***
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
            auto                arrayOneSetOneArray{std::make_shared<Array>()};
            std::string         expectedArrayOneSetOneArrayLines[]{ "99ER2OjQ4OH/"s };
            constexpr size_t    expectedArrayOneSetOneArrayLinesCount{numElementsInArray(expectedArrayOneSetOneArrayLines)};

            arrayOneSetOneArray->addValue(std::make_shared<Set>());
            arrayOneSetOneArray->addValue(std::make_shared<Array>());
            result = setValueAndCheck(*stuff, arrayOneSetOneArray, expectedArrayOneSetOneArrayLines, expectedArrayOneSetOneArrayLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 421 ***
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
            std::string         insertedArrayOneSetOneArrayLines[]{ "99ER2OjQ4OH/"s };
            constexpr size_t    insertedArrayOneSetOneArrayLinesCount{numElementsInArray(insertedArrayOneSetOneArrayLines)};
            Array               arrayOneSetOneArray;

            arrayOneSetOneArray.addValue(std::make_shared<Set>());
            arrayOneSetOneArray.addValue(std::make_shared<Array>());
            result = extractValueAndCheck(*stuff, insertedArrayOneSetOneArrayLines, insertedArrayOneSetOneArrayLinesCount, arrayOneSetOneArray);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 422 ***
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
            constexpr size_t    numValues{43};
            auto                arrayManyDoubles{std::make_shared<Array>()};
            std::string         expectedArrayManyDoublesLines[]{
                                    "99EgGmArAAAAAAAAAAA/8AAAAAAAAEAAAAAAAAAAQAgAAAAAAABAEAAAAAAAAEAUAAAAAAAA"s,
                                    "QBgAAAAAAABAHAAAAAAAAEAgAAAAAAAAQCIAAAAAAABAJAAAAAAAAEAmAAAAAAAAQCgAAAAA"s,
                                    "AABAKgAAAAAAAEAsAAAAAAAAQC4AAAAAAABAMAAAAAAAAEAxAAAAAAAAQDIAAAAAAABAMwAA"s,
                                    "AAAAAEA0AAAAAAAAQDUAAAAAAABANgAAAAAAAEA3AAAAAAAAQDgAAAAAAABAOQAAAAAAAEA6"s,
                                    "AAAAAAAAQDsAAAAAAABAPAAAAAAAAEA9AAAAAAAAQD4AAAAAAABAPwAAAAAAAEBAAAAAAAAA"s,
                                    "QECAAAAAAABAQQAAAAAAAEBBgAAAAAAAQEIAAAAAAABAQoAAAAAAAEBDAAAAAAAAQEOAAAAA"s,
                                    "AABARAAAAAAAAEBEgAAAAAAAQEUAAAAAAADh/w=="s };
            constexpr size_t    expectedArrayManyDoublesLinesCount{numElementsInArray(expectedArrayManyDoublesLines)};

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles->addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = setValueAndCheck(*stuff, arrayManyDoubles, expectedArrayManyDoublesLines, expectedArrayManyDoublesLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 423 ***
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
            constexpr size_t    numValues{43};
            std::string         insertedArrayManyDoublesLines[]{
                                    "99EgGmArAAAAAAAAAAA/8AAAAAAAAEAAAAAAAAAAQAgAAAAAAABAEAAAAAAAAEAUAAAAAAAA"s,
                                    "QBgAAAAAAABAHAAAAAAAAEAgAAAAAAAAQCIAAAAAAABAJAAAAAAAAEAmAAAAAAAAQCgAAAAA"s,
                                    "AABAKgAAAAAAAEAsAAAAAAAAQC4AAAAAAABAMAAAAAAAAEAxAAAAAAAAQDIAAAAAAABAMwAA"s,
                                    "AAAAAEA0AAAAAAAAQDUAAAAAAABANgAAAAAAAEA3AAAAAAAAQDgAAAAAAABAOQAAAAAAAEA6"s,
                                    "AAAAAAAAQDsAAAAAAABAPAAAAAAAAEA9AAAAAAAAQD4AAAAAAABAPwAAAAAAAEBAAAAAAAAA"s,
                                    "QECAAAAAAABAQQAAAAAAAEBBgAAAAAAAQEIAAAAAAABAQoAAAAAAAEBDAAAAAAAAQEOAAAAA"s,
                                    "AABARAAAAAAAAEBEgAAAAAAAQEUAAAAAAADh/w=="s };
            constexpr size_t    insertedArrayManyDoublesLinesCount{numElementsInArray(insertedArrayManyDoublesLines)};
            Array               arrayManyDoubles;

            for (size_t ii = 0; numValues > ii; ++ii)
            {
                arrayManyDoubles.addValue(std::make_shared<Double>(StaticCast(double, ii)));
            }
            result = extractValueAndCheck(*stuff, insertedArrayManyDoublesLines, insertedArrayManyDoublesLinesCount, arrayManyDoubles);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 424 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithTwoAddressesMessage
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
            auto                arrayTwoAddresses{std::make_shared<Array>()};
            std::string         expectedArrayTwoAddressesLines[]{ "99ERxBI0VnjENFZ4q+H/"s };
            constexpr size_t    expectedArrayTwoAddressesLinesCount{numElementsInArray(expectedArrayTwoAddressesLines)};

            arrayTwoAddresses->addValue(std::make_shared<Address>(0x12345678));
            arrayTwoAddresses->addValue(std::make_shared<Address>(0x345678AB));
            result = setValueAndCheck(*stuff, arrayTwoAddresses, expectedArrayTwoAddressesLines, expectedArrayTwoAddressesLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertArrayWithTwoAddressesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 425 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithTwoAddressesMessage
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
            std::string         insertedArrayTwoAddressesLines[]{ "99ERxBI0VnjENFZ4q+H/"s };
            constexpr size_t    insertedArrayTwoAddressesLinesCount{numElementsInArray(insertedArrayTwoAddressesLines)};
            Array               arrayTwoAddresses;

            arrayTwoAddresses.addValue(std::make_shared<Address>(0x12345678));
            arrayTwoAddresses.addValue(std::make_shared<Address>(0x345678AB));
            result = extractValueAndCheck(*stuff, insertedArrayTwoAddressesLines, insertedArrayTwoAddressesLinesCount, arrayTwoAddresses);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractArrayWithTwoAddressesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 426 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithTwoDatesMessage
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
            auto                            arrayTwoDates{std::make_shared<Array>()};
            std::string                     expectedArrayTwoDatesLines[]{ "99ERxQAAFOrFAAATKeH/"s };
            constexpr size_t                expectedArrayTwoDatesLinesCount{numElementsInArray(expectedArrayTwoDatesLines)};

            arrayTwoDates->addValue(std::make_shared<Date>(MakeDateValue(aDate1)));
            arrayTwoDates->addValue(std::make_shared<Date>(MakeDateValue(aDate2)));
            result = setValueAndCheck(*stuff, arrayTwoDates, expectedArrayTwoDatesLines, expectedArrayTwoDatesLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertArrayWithTwoDatesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 427 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithTwoDatesMessage
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
            std::string                     insertedArrayTwoDatesLines[]{ "99ERxQAAFOrFAAATKeH/"s };
            constexpr size_t                insertedArrayTwoDatesLinesCount{numElementsInArray(insertedArrayTwoDatesLines)};
            Array                           arrayTwoDates;

            arrayTwoDates.addValue(std::make_shared<Date>(MakeDateValue(aDate1)));
            arrayTwoDates.addValue(std::make_shared<Date>(MakeDateValue(aDate2)));
            result = extractValueAndCheck(*stuff, insertedArrayTwoDatesLines, insertedArrayTwoDatesLinesCount, arrayTwoDates);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractArrayWithTwoDatesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 428 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithTwoTimesMessage
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
            auto                            arrayTwoTimes{std::make_shared<Array>()};
            std::string                     expectedArrayTwoTimesLines[]{ "99ERxgKdZznGAmWKcOH/"s };
            constexpr size_t                expectedArrayTwoTimesLinesCount{numElementsInArray(expectedArrayTwoTimesLines)};

            arrayTwoTimes->addValue(std::make_shared<Time>(MakeTimeValue(aTime1)));
            arrayTwoTimes->addValue(std::make_shared<Time>(MakeTimeValue(aTime2)));
            result = setValueAndCheck(*stuff, arrayTwoTimes, expectedArrayTwoTimesLines, expectedArrayTwoTimesLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertArrayWithTwoTimesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 429 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithTwoTimesMessage
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
            std::string                     insertedArrayTwoTimesLines[]{ "99ERxgKdZznGAmWKcOH/"s };
            constexpr size_t                insertedArrayTwoTimesLinesCount{numElementsInArray(insertedArrayTwoTimesLines)};
            Array                           arrayTwoTimes;

            arrayTwoTimes.addValue(std::make_shared<Time>(MakeTimeValue(aTime1)));
            arrayTwoTimes.addValue(std::make_shared<Time>(MakeTimeValue(aTime2)));
            result = extractValueAndCheck(*stuff, insertedArrayTwoTimesLines, insertedArrayTwoTimesLinesCount, arrayTwoTimes);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractArrayWithTwoTimesMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 430 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertArrayWithOneDateOneTimeMessage
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
            auto                            arrayOneDateOneTime{std::make_shared<Array>()};
            std::string                     expectedArrayOneDateOneTimeLines[]{ "99ERxQAAFOrGAp1nOeH/"s };
            constexpr size_t                expectedArrayOneDateOneTimeLinesCount{numElementsInArray(expectedArrayOneDateOneTimeLines)};

            arrayOneDateOneTime->addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            arrayOneDateOneTime->addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = setValueAndCheck(*stuff, arrayOneDateOneTime, expectedArrayOneDateOneTimeLines, expectedArrayOneDateOneTimeLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertArrayWithOneDateOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 431 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractArrayWithOneDateOneTimeMessage
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
            std::string                     insertedArrayOneDateOneTimeLines[]{ "99ERxQAAFOrGAp1nOeH/"s };
            constexpr size_t                insertedArrayOneDateOneTimeLinesCount{numElementsInArray(insertedArrayOneDateOneTimeLines)};
            Array                           arrayOneDateOneTime;

            arrayOneDateOneTime.addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            arrayOneDateOneTime.addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = extractValueAndCheck(*stuff, insertedArrayOneDateOneTimeLines, insertedArrayOneDateOneTimeLinesCount, arrayOneDateOneTime);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractArrayWithOneDateOneTimeMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 500 ***
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
            auto                logicalMap{std::make_shared<Map>()};
            std::string         expectedLogicalMapLines[]{ "99UQwA3l/w=="s };
            constexpr size_t    expectedLogicalMapLinesCount{numElementsInArray(expectedLogicalMapLines)};

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
# pragma mark *** Test Case 501 ***
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
            std::string         insertedLogicalMapLines[]{ "99UQwA3l/w=="s };
            constexpr size_t    insertedLogicalMapLinesCount{numElementsInArray(insertedLogicalMapLines)};
            Map                 logicalMap;

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
# pragma mark *** Test Case 502 ***
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
            auto                integerMap{std::make_shared<Map>()};
            std::string         expectedIntegerMapLines[]{ "99UQAA3l/w=="s };
            constexpr size_t    expectedIntegerMapLinesCount{numElementsInArray(expectedIntegerMapLines)};

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
# pragma mark *** Test Case 503 ***
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
            std::string         insertedIntegerMapLines[]{ "99UQAA3l/w=="s };
            constexpr size_t    insertedIntegerMapLinesCount{numElementsInArray(insertedIntegerMapLines)};
            Map                 integerMap;

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
# pragma mark *** Test Case 504 ***
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
            auto                stringMap{std::make_shared<Map>()};
            std::string         expectedStringMapLines[]{ "99UQgA3l/w=="s };
            constexpr size_t    expectedStringMapLinesCount{numElementsInArray(expectedStringMapLines)};

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
# pragma mark *** Test Case 505 ***
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
            std::string         insertedStringMapLines[]{ "99UQgA3l/w=="s };
            constexpr size_t    insertedStringMapLinesCount{numElementsInArray(insertedStringMapLines)};
            Map                 stringMap;

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
# pragma mark *** Test Case 506 ***
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
            auto                logicalSet{std::make_shared<Set>()};
            std::string         expectedLogicalSetLines[]{ "99kQwOn/"s };
            constexpr size_t    expectedLogicalSetLinesCount{numElementsInArray(expectedLogicalSetLines)};

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
# pragma mark *** Test Case 507 ***
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
            std::string         insertedLogicalSetLines[]{ "99kQwOn/"s };
            constexpr size_t    insertedLogicalSetLinesCount{numElementsInArray(insertedLogicalSetLines)};
            Set                 logicalSet;

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
# pragma mark *** Test Case 508 ***
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
            auto                integerSet{std::make_shared<Set>()};
            std::string         expectedIntegerSetLines[]{ "99kQAOn/"s };
            constexpr size_t    expectedIntegerSetLinesCount{numElementsInArray(expectedIntegerSetLines)};

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
# pragma mark *** Test Case 509 ***
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
            std::string         insertedIntegerSetLines[]{ "99kQAOn/"s };
            constexpr size_t    insertedIntegerSetLinesCount{numElementsInArray(insertedIntegerSetLines)};
            Set                 integerSet;

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
# pragma mark *** Test Case 510 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertStdStringSetMessage
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
            auto                stringSet{std::make_shared<Set>()};
            std::string         expectedStdStringSetLines[]{ "99kQgOn/"s };
            constexpr size_t    expectedStdStringSetLinesCount{numElementsInArray(expectedStdStringSetLines)};

            stringSet->addValue(std::make_shared<String>());
            result = setValueAndCheck(*stuff, stringSet, expectedStdStringSetLines, expectedStdStringSetLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertStdStringSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 511 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractStdStringSetMessage
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
            std::string         insertedStdStringSetLines[]{ "99kQgOn/"s };
            constexpr size_t    insertedStdStringSetLinesCount{numElementsInArray(insertedStdStringSetLines)};
            Set                 stringSet;

            stringSet.addValue(std::make_shared<String>());
            result = extractValueAndCheck(*stuff, insertedStdStringSetLines, insertedStdStringSetLinesCount, stringSet);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractStdStringSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 512 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertAddressMapMessage
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
            auto                addressMap{std::make_shared<Map>()};
            std::string         expectedAddressMapLines[]{ "99UQxAAAAAAN5f8="s };
            constexpr size_t    expectedAddressMapLinesCount{numElementsInArray(expectedAddressMapLines)};

            addressMap->addValue(std::make_shared<Address>(), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, addressMap, expectedAddressMapLines, expectedAddressMapLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertAddressMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 513 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractAddressMapMessage
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
            std::string         insertedAddressMapLines[]{ "99UQxAAAAAAN5f8="s };
            constexpr size_t    insertedAddressMapLinesCount{numElementsInArray(insertedAddressMapLines)};
            Map                 addressMap;

            addressMap.addValue(std::make_shared<Address>(), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedAddressMapLines, insertedAddressMapLinesCount, addressMap);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractAddressMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 514 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertAddressSetMessage
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
            auto                addressSet{std::make_shared<Set>()};
            std::string         expectedAddressSetLines[]{ "99kQxAAAAADp/w=="s };
            constexpr size_t    expectedAddressSetLinesCount{numElementsInArray(expectedAddressSetLines)};

            addressSet->addValue(std::make_shared<Address>());
            result = setValueAndCheck(*stuff, addressSet, expectedAddressSetLines, expectedAddressSetLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertAddressSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 515 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractAddressSetMessage
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
            std::string         insertedAddressSetLines[]{ "99kQxAAAAADp/w=="s };
            constexpr size_t    insertedAddressSetLinesCount{numElementsInArray(insertedAddressSetLines)};
            Set                 addressSet;

            addressSet.addValue(std::make_shared<Address>());
            result = extractValueAndCheck(*stuff, insertedAddressSetLines, insertedAddressSetLinesCount, addressSet);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractAddressSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 516 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertDateMapMessage
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
            auto                            dateMap{std::make_shared<Map>()};
            std::string                     expectedDateMapLines[]{ "99UQxQAAFOoN5f8="s };
            constexpr size_t                expectedDateMapLinesCount{numElementsInArray(expectedDateMapLines)};

            dateMap->addValue(std::make_shared<Date>(MakeDateValue(aDate)), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, dateMap, expectedDateMapLines, expectedDateMapLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertDateMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 517 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractDateMapMessage
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
            std::string                     insertedDateMapLines[]{ "99UQxQAAFOoN5f8="s };
            constexpr size_t                insertedDateMapLinesCount{numElementsInArray(insertedDateMapLines)};
            Map                             dateMap;

            dateMap.addValue(std::make_shared<Date>(MakeDateValue(aDate)), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedDateMapLines, insertedDateMapLinesCount, dateMap);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractDateMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 518 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertDateSetMessage
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
            auto                            dateSet{std::make_shared<Set>()};
            std::string                     expectedDateSetLines[]{ "99kQxQAAFOrp/w=="s };
            constexpr size_t                expectedDateSetLinesCount{numElementsInArray(expectedDateSetLines)};

            dateSet->addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = setValueAndCheck(*stuff, dateSet, expectedDateSetLines, expectedDateSetLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertDateSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 519 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractDateSetMessage
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
            std::string                     insertedDateSetLines[]{ "99kQxQAAFOrp/w=="s };
            constexpr size_t                insertedDateSetLinesCount{numElementsInArray(insertedDateSetLines)};
            Set                             dateSet;

            dateSet.addValue(std::make_shared<Date>(MakeDateValue(aDate)));
            result = extractValueAndCheck(*stuff, insertedDateSetLines, insertedDateSetLinesCount, dateSet);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractDateSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 520 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertTimeMapMessage
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
            auto                            timeMap{std::make_shared<Map>()};
            std::string                     expectedTimeMapLines[]{ "99UQxgKdZzkN5f8="s };
            constexpr size_t                expectedTimeMapLinesCount{numElementsInArray(expectedTimeMapLines)};

            timeMap->addValue(std::make_shared<Time>(MakeTimeValue(aTime)), std::make_shared<Integer>(13));
            result = setValueAndCheck(*stuff, timeMap, expectedTimeMapLines, expectedTimeMapLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertTimeMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 521 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractTimeMapMessage
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
            std::string                     insertedTimeMapLines[]{ "99UQxgKdZzkN5f8="s };
            constexpr size_t                insertedTimeMapLinesCount{numElementsInArray(insertedTimeMapLines)};
            Map                             timeMap;

            timeMap.addValue(std::make_shared<Time>(MakeTimeValue(aTime)), std::make_shared<Integer>(13));
            result = extractValueAndCheck(*stuff, insertedTimeMapLines, insertedTimeMapLinesCount, timeMap);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractTimeMapMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 522 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEInsertTimeSetMessage
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
            auto                            timeSet{std::make_shared<Set>()};
            std::string                     expectedTimeSetLines[]{ "99kQxgKdZznp/w=="s };
            constexpr size_t                expectedTimeSetLinesCount{numElementsInArray(expectedTimeSetLines)};

            timeSet->addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = setValueAndCheck(*stuff, timeSet, expectedTimeSetLines, expectedTimeSetLinesCount);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEInsertTimeSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 523 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMEExtractTimeSetMessage
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
            std::string                     insertedTimeSetLines[]{ "99kQxgKdZznp/w=="s };
            constexpr size_t                insertedTimeSetLinesCount{numElementsInArray(insertedTimeSetLines)};
            Set                             timeSet;

            timeSet.addValue(std::make_shared<Time>(MakeTimeValue(aTime)));
            result = extractValueAndCheck(*stuff, insertedTimeSetLines, insertedTimeSetLinesCount, timeSet);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMEExtractTimeSetMessage

#if defined(__APPLE__)
# pragma mark *** Test Case 600 ***
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
            auto                arrayWithRangeOfIntegers{std::make_shared<Array>()};
            std::string         expectedArrayWithRangeOfIntegersLines[]{
                                    "99EgEwEKIGQhA+ghJxAiAYagIg9CQCMAmJaAIwX14QAjO5rKACQCVAvkACQXSHboACUA6NSl"s,
                                    "EAAlCRhOcqAAJVrzEHpAACYDjX6kxoAAJiOG8m/BAAAnAWNFeF2KAAAfFiCcIfwYIdjwIv55"s,
                                    "YCLwvcAj/2dpgCP6Ch8AI8RlNgAk/av0HAAk6LeJGAAl/xcrWvAAJfbnsY1gACWlDO+FwAAm"s,
                                    "/HKBWzmAACbceQ2QPwAAJ/6cuoeidgAA4f8="s };
            constexpr size_t    expectedArrayWithRangeOfIntegersLinesCount{numElementsInArray(expectedArrayWithRangeOfIntegersLines)};

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
# pragma mark *** Test Case 601 ***
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
            std::string         insertedArrayWithRangeOfIntegersLines[]{
                                    "99EgEwEKIGQhA+ghJxAiAYagIg9CQCMAmJaAIwX14QAjO5rKACQCVAvkACQXSHboACUA6NSl"s,
                                    "EAAlCRhOcqAAJVrzEHpAACYDjX6kxoAAJiOG8m/BAAAnAWNFeF2KAAAfFiCcIfwYIdjwIv55"s,
                                    "YCLwvcAj/2dpgCP6Ch8AI8RlNgAk/av0HAAk6LeJGAAl/xcrWvAAJfbnsY1gACWlDO+FwAAm"s,
                                    "/HKBWzmAACbceQ2QPwAAJ/6cuoeidgAA4f8="s };
            constexpr size_t    insertedArrayWithRangeOfIntegersLinesCount{numElementsInArray(insertedArrayWithRangeOfIntegersLines)};
            Array               arrayWithRangeOfIntegers;

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
            result = extractValueAndCheck(*stuff, insertedArrayWithRangeOfIntegersLines, insertedArrayWithRangeOfIntegersLinesCount,
                                          arrayWithRangeOfIntegers);
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
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
# pragma mark *** Test Case 700 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMExtractWithBadNumberOfCharacters
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
        StdStringVector inVec;
        ByteVector      outBytes;

        inVec.push_back("99UQAA3l/w=");
        if (DecodeMIMEToBytes(inVec, outBytes))
        {
            ODL_LOG("DecodeMIMEToBytes(inVec, outBytes)"); //####
        }
        else
        {
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMExtractWithBadNumberOfCharacters

#if defined(__APPLE__)
# pragma mark *** Test Case 701 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMIMExtractWithBadCharacters
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
        StdStringVector inVec;
        ByteVector      outBytes;

        inVec.push_back("99?QAA3l/w==");
        if (DecodeMIMEToBytes(inVec, outBytes))
        {
            ODL_LOG("DecodeMIMEToBytes(inVec, outBytes)"); //####
        }
        else
        {
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMIMExtractWithBadCharacters

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
                        result = doTestMIMEBytesMod3Is0(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestMIMEBytesMod3Is1(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestMIMEBytesMod3Is2(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestMIMEBytesMod3Is0Packaged(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestMIMEBytesMod3Is1Packaged(*argv, argc - 1, argv + 2);
                        break;

                    case 6 :
                        result = doTestMIMEBytesMod3Is2Packaged(*argv, argc - 1, argv + 2);
                        break;

                    case 100 :
                        result = doTestMIMEInsertEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestMIMEExtractEmptyMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestMIMEInsertLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 103 :
                        result = doTestMIMEExtractLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 104 :
                        result = doTestMIMEInsertTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 105 :
                        result = doTestMIMEExtractTinyIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 106 :
                        result = doTestMIMEInsertSmallIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 107 :
                        result = doTestMIMEExtractSmallIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 108 :
                        result = doTestMIMEInsertMediumIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 109 :
                        result = doTestMIMEExtractMediumIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 110 :
                        result = doTestMIMEInsertBigIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 111 :
                        result = doTestMIMEExtractBigIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 112 :
                        result = doTestMIMEInsertEmptyStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 113 :
                        result = doTestMIMEExtractEmptyStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 114 :
                        result = doTestMIMEInsertShortStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 115 :
                        result = doTestMIMEExtractShortStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 116 :
                        result = doTestMIMEInsertMediumStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 117 :
                        result = doTestMIMEExtractMediumStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 118 :
                        result = doTestMIMEInsertEmptyBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 119 :
                        result = doTestMIMEExtractEmptyBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 120 :
                        result = doTestMIMEInsertSmallBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 121 :
                        result = doTestMIMEExtractSmallBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 122 :
                        result = doTestMIMEInsertMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 123 :
                        result = doTestMIMEExtractMediumBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 124 :
                        result = doTestMIMEInsertSingleDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 125 :
                        result = doTestMIMEExtractSingleDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 126 :
                        result = doTestMIMEInsertAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 127 :
                        result = doTestMIMEExtractAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 128 :
                        result = doTestMIMEInsertDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 129 :
                        result = doTestMIMEExtractDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 130 :
                        result = doTestMIMEInsertTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 131 :
                        result = doTestMIMEExtractTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 200 :
                        result = doTestMIMEInsertEmptyArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 201 :
                        result = doTestMIMEExtractEmptyArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 202 :
                        result = doTestMIMEInsertEmptyMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 203 :
                        result = doTestMIMEExtractEmptyMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 204 :
                        result = doTestMIMEInsertEmptySetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 205 :
                        result = doTestMIMEExtractEmptySetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 300 :
                        result = doTestMIMEInsertArrayOneLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 301 :
                        result = doTestMIMEExtractArrayOneLogicalMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 302 :
                        result = doTestMIMEInsertArrayOneIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 303 :
                        result = doTestMIMEExtractArrayOneIntegerMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 304 :
                        result = doTestMIMEInsertArrayOneDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 305 :
                        result = doTestMIMEExtractArrayOneDoubleMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 306 :
                        result = doTestMIMEInsertArrayOneStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 307 :
                        result = doTestMIMEExtractArrayOneStringMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 308 :
                        result = doTestMIMEInsertArrayOneBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 309 :
                        result = doTestMIMEExtractArrayOneBlobMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 310 :
                        result = doTestMIMEInsertArrayOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 311 :
                        result = doTestMIMEExtractArrayOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 312 :
                        result = doTestMIMEInsertArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 313 :
                        result = doTestMIMEExtractArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 314 :
                        result = doTestMIMEInsertArrayOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 315 :
                        result = doTestMIMEExtractArrayOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 316 :
                        result = doTestMIMEInsertArrayWithOneAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 317 :
                        result = doTestMIMEExtractArrayWithOneAddressMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 318 :
                        result = doTestMIMEInsertArrayWithOneDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 319 :
                        result = doTestMIMEExtractArrayWithOneDateMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 320 :
                        result = doTestMIMEInsertArrayWithOneTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 321 :
                        result = doTestMIMEExtractArrayWithOneTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 400 :
                        result = doTestMIMEInsertArrayTwoLogicalsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 401 :
                        result = doTestMIMEExtractArrayTwoLogicalsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 402 :
                        result = doTestMIMEInsertArrayTwoIntegersMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 403 :
                        result = doTestMIMEExtractArrayTwoIntegersMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 404 :
                        result = doTestMIMEInsertArrayTwoDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 405 :
                        result = doTestMIMEExtractArrayTwoDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 406 :
                        result = doTestMIMEInsertArrayTwoStringsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 407 :
                        result = doTestMIMEExtractArrayTwoStringsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 408 :
                        result = doTestMIMEInsertArrayTwoBlobsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 409 :
                        result = doTestMIMEExtractArrayTwoBlobsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 410 :
                        result = doTestMIMEInsertArrayTwoArraysMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 411 :
                        result = doTestMIMEExtractArrayTwoArraysMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 412 :
                        result = doTestMIMEInsertArrayTwoMapsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 413 :
                        result = doTestMIMEExtractArrayTwoMapsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 414 :
                        result = doTestMIMEInsertArrayTwoSetsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 415 :
                        result = doTestMIMEExtractArrayTwoSetsMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 416 :
                        result = doTestMIMEInsertArrayOneArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 417 :
                        result = doTestMIMEExtractArrayOneArrayOneMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 418 :
                        result = doTestMIMEInsertArrayOneMapOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 419 :
                        result = doTestMIMEExtractArrayOneMapOneSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 420 :
                        result = doTestMIMEInsertArrayOneSetOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 421 :
                        result = doTestMIMEExtractArrayOneSetOneArrayMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 422 :
                        result = doTestMIMEInsertArrayWithManyDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 423 :
                        result = doTestMIMEExtractArrayWithManyDoublesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 424 :
                        result = doTestMIMEInsertArrayWithTwoAddressesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 425 :
                        result = doTestMIMEExtractArrayWithTwoAddressesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 426 :
                        result = doTestMIMEInsertArrayWithTwoDatesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 427 :
                        result = doTestMIMEExtractArrayWithTwoDatesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 428 :
                        result = doTestMIMEInsertArrayWithTwoTimesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 429 :
                        result = doTestMIMEExtractArrayWithTwoTimesMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 430 :
                        result = doTestMIMEInsertArrayWithOneDateOneTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 431 :
                        result = doTestMIMEExtractArrayWithOneDateOneTimeMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 500 :
                        result = doTestMIMEInsertLogicalMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 501 :
                        result = doTestMIMEExtractLogicalMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 502 :
                        result = doTestMIMEInsertIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 503 :
                        result = doTestMIMEExtractIntegerMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 504 :
                        result = doTestMIMEInsertStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 505 :
                        result = doTestMIMEExtractStringMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 506 :
                        result = doTestMIMEInsertLogicalSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 507 :
                        result = doTestMIMEExtractLogicalSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 508 :
                        result = doTestMIMEInsertIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 509 :
                        result = doTestMIMEExtractIntegerSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 510 :
                        result = doTestMIMEInsertStdStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 511 :
                        result = doTestMIMEExtractStdStringSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 512 :
                        result = doTestMIMEInsertAddressMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 513 :
                        result = doTestMIMEExtractAddressMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 514 :
                        result = doTestMIMEInsertAddressSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 515 :
                        result = doTestMIMEExtractAddressSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 516 :
                        result = doTestMIMEInsertDateMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 517 :
                        result = doTestMIMEExtractDateMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 518 :
                        result = doTestMIMEInsertDateSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 519 :
                        result = doTestMIMEExtractDateSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 520 :
                        result = doTestMIMEInsertTimeMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 521 :
                        result = doTestMIMEExtractTimeMapMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 522 :
                        result = doTestMIMEInsertTimeSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 523 :
                        result = doTestMIMEExtractTimeSetMessage(*argv, argc - 1, argv + 2);
                        break;

                    case 600 :
                        result = doTestMIMEInsertArrayWithRangeOfIntegers(*argv, argc - 1, argv + 2);
                        break;

                    case 601 :
                        result = doTestMIMEExtractArrayWithRangeOfIntegers(*argv, argc - 1, argv + 2);
                        break;

                    case 700 :
                        result = doTestMIMExtractWithBadNumberOfCharacters(*argv, argc - 1, argv + 2);
                        break;

                    case 701 :
                        result = doTestMIMExtractWithBadCharacters(*argv, argc - 1, argv + 2);
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

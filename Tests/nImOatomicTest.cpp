//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOatomicTest.cpp
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
//  Created:    2016-03-22
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOblob.h>
#include <BasicTypes/nImOdouble.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <ContainerTypes/nImObufferChunk.h>
#include <ContainerTypes/nImOstringBuffer.h>
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

/*! @namespace nImO::Test
 @brief The classes used for unit testing of the %nImO classes. */
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

/*! @brief The number of elements in a small test. */
constexpr size_t    kSmallTestSize{100};

/*! @brief The number of elements in a big test. */
constexpr size_t    kBigTestSize{100000};

static const char kHexDigits[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

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
    std::string message{"exiting due to signal "s + std::to_string(signal) + " = "s + NameOfSignal(signal)};

    NIMO_UNUSED_VAR_(message);
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

/*! @brief Compare a Value object with a string.
 @param[in] aValue The object to be compared.
 @param[in] aString The string to be compared to.
 @return @c -1, @c 0 or @c 1 depending on whether the string is greater than, equal to or less than
 the object representation as a string. */
static int
compareValueWithString
    (const Value &  aValue,
     CPtr(char)     aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    StringBuffer    buff;
    int             result;

    aValue.printToStringBuffer(buff);
    auto    valString{buff.getString()};

    result = valString.compare(aString);
    ODL_S2("got: ", valString.c_str(), "expected: ", aString); //####
    ODL_EXIT_I(result); //####
    return result;
} // compareValueWithString

/*! @brief Compare a Value object with a JSON string.
 @param[in] aValue The object to be compared.
 @param[in] aString The JSON string to be compared to.
 @return @c -1, @c 0 or @c 1 depending on whether the string is greater than, equal to or less than
 the object representation as JSON. */
static int
compareValueWithStringAsJSON
    (const Value &  aValue,
     CPtr(char)     aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    StringBuffer    buff;
    int             result;

    aValue.printToStringBufferAsJSON(buff);
    auto    valString{buff.getString()};

    result = valString.compare(aString);
    ODL_S2("got: ", valString.c_str(), "expected: ", aString); //####
    ODL_EXIT_I(result); //####
    return result;
} // compareValueWithStringAsJSON

/*! @brief Extract the bytes of an IPv4 address from a string.
 @param[out] asBytes The bytes for the address.
 @param[in] inString The character string to process.
 @return @c true on success and @c false on failure. */
static bool
getIPv4Bytes
    (Address::IPv4Bytes &   asBytes,
     CPtr(char)             inString)
{
    bool    okSoFar{true};

    for (size_t ii = 0, mm = numElementsInArray(asBytes); okSoFar && (ii < mm); ++ii)
    {
        Ptr(char)   endPtr;
        int64_t     value{strtoll(inString, &endPtr, 10)};

        if (inString == endPtr)
        {
            okSoFar = false;
        }
        else
        {
            if ((255 < value) || (0 > value))
            {
                okSoFar = false;
            }
            else if ((kEndOfString == *endPtr) && (ii == (mm - 1)))
            {
                asBytes[ii] = StaticCast(uint8_t, value);
            }
            else if ((kAddressSeparator == *endPtr) && (ii < (mm - 1)))
            {
                asBytes[ii] = StaticCast(uint8_t, value);
                inString = endPtr + 1;
            }
            else
            {
                okSoFar = false;
            }
        }
    }
    return okSoFar;
} // getIPv4Bytes

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyBufferChunk
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
        auto    stuff{std::make_unique<BufferChunk>(false)};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == stuff->getDataSize())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->getDataSize())"); //####
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
} // doTestEmptyBufferChunk

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBufferChunkWithSingleByte
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
        auto    stuff{std::make_unique<BufferChunk>(false)};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            uint8_t data{StaticCast(uint8_t, ReinterpretCast(intptr_t, stuff.get()) & 0x00FF)};

            stuff->appendData(&data, sizeof(data));
            if (1 == stuff->getDataSize())
            {
                CPtr(uint8_t) storedData{stuff->getData()};

                if ((nullptr != storedData) && (data == *storedData))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((nullptr != storedData) && (data == *storedData))"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 == stuff->getDataSize())"); //####
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
} // doTestBufferChunkWithSingleByte

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFilledBufferChunk
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
        auto    stuff{std::make_unique<BufferChunk>(false)};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            size_t  howMuch{stuff->getAvailableBytes()};

            if (1 < howMuch)
            {
                uint8_t data{StaticCast(uint8_t, ReinterpretCast(intptr_t, stuff.get()) & 0x00FF)};

                for (size_t ii = 0; howMuch > ii; ++ii)
                {
                    uint8_t newData{StaticCast(uint8_t, (data + ii) & 0x00FF)};

                    stuff->appendData(&newData, sizeof(newData));
                }
                if ((0 == stuff->getAvailableBytes()) && (howMuch == stuff->getDataSize()))
                {
                    CPtr(uint8_t) storedData{stuff->getData()};

                    if (nullptr != storedData)
                    {
                        result = 0;
                        for (size_t ii = 0; (0 == result) && (howMuch > ii); ++ii)
                        {
                            uint8_t aValue{storedData[ii]};
                            uint8_t expectedValue{StaticCast(uint8_t, (data + ii) & 0x00FF)};

                            if (aValue != expectedValue)
                            {
                                ODL_LOG("(aValue != expectedValue)"); //####
                                result = 1;
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (nullptr != storedData)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (((0 == stuff->getAvailableBytes()) && (howMuch == " //####
                            "stuff->getDataSize()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 < howMuch)"); //####
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
} // doTestFilledBufferChunk

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestOverfilledBufferChunk
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
        auto    stuff{std::make_unique<BufferChunk>(false)};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            size_t  howMuch{stuff->getAvailableBytes()};

            if (1 < howMuch)
            {
                uint8_t data{StaticCast(uint8_t, ReinterpretCast(intptr_t, stuff.get()) & 0x00FF)};

                for (size_t ii = 0; howMuch >= ii; ++ii)
                {
                    uint8_t newData{StaticCast(uint8_t, (data + ii) & 0x00FF)};

                    stuff->appendData(&newData, sizeof(newData));
                }
                if ((0 == stuff->getAvailableBytes()) && (howMuch == stuff->getDataSize()))
                {
                    CPtr(uint8_t) storedData{stuff->getData()};

                    if (nullptr != storedData)
                    {
                        result = 0;
                        for (size_t ii = 0; (0 == result) && (howMuch > ii); ++ii)
                        {
                            uint8_t aValue{storedData[ii]};
                            uint8_t expectedValue{StaticCast(uint8_t, (data + ii) & 0x00FF)};

                            if (aValue != expectedValue)
                            {
                                ODL_LOG("(aValue != expectedValue)"); //####
                                result = 1;
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (nullptr != storedData)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (((0 == stuff->getAvailableBytes()) && (howMuch == " //####
                            "stuff->getDataSize()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 < howMuch)"); //####
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
} // doTestOverfilledBufferChunk

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBufferChunkReset
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
        auto    stuff{std::make_unique<BufferChunk>(false)};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            uint8_t data{StaticCast(uint8_t, ReinterpretCast(intptr_t, stuff.get()) & 0x00FF)};

            stuff->appendData(&data, sizeof(data));
            if (1 == stuff->getDataSize())
            {
                stuff->reset();
                if (0 == stuff->getDataSize())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == stuff->getDataSize())"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 == stuff->getDataSize())"); //####
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
} // doTestBufferChunkReset

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyStringBuffer
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
        auto    stuff{std::make_unique<StringBuffer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == stuff->getLength())
            {
                auto    outString{stuff->getString()};
                size_t  length{outString.size()};

                if (0 == length)
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == length)"); //####
                }
            }
            else
            {
                ODL_LOG("! (0 == stuff->getLength())"); //####
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
} // doTestEmptyStringBuffer

#if defined(__APPLE__)
# pragma mark *** Test Case 11 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithCharacters
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  inString{*argv};
            CPtr(char)  outString{argv[1]};
            size_t      outLength{strlen(outString)};
            auto        stuff{std::make_unique<StringBuffer>()};

            if (nullptr == stuff)
            {
                ODL_LOG("(nullptr == stuff)"); //####
            }
            else
            {
                stuff->addString(inString);
                size_t  resultLength{stuff->getLength()};

                if (resultLength == outLength)
                {
                    auto    resultString{stuff->getString()};

                    if (0 == resultString.compare(outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_S2("outString = ", outString, "resultString = ", resultString.c_str()); //####
                        ODL_LOG("! (0 == resultString.compare(outString))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (resultLength == outLength)"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringBufferWithCharacters

#if defined(__APPLE__)
# pragma mark *** Test Case 12 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithLogical
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  outString{argv[1]};
            int64_t     value;

            if (ConvertToInt64(*argv, value) && (0 <= value))
            {
                auto    stuff{std::make_unique<StringBuffer>()};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    bool asBool{0 != value};

                    stuff->addBool(asBool);
                    auto    resultString{stuff->getString()};

                    if (0 == resultString.compare(outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == resultString.compare(outString))"); //####
                    }
                }
            }
            else
            {
                ODL_LOG("! (ConvertToInt64(*argv, value) && (0 <= value))"); //####
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringBufferWithLogical

#if defined(__APPLE__)
# pragma mark *** Test Case 13 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithInteger
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  outString{argv[1]};
            int64_t     value;

            if (ConvertToInt64(*argv, value))
            {
                auto    stuff{std::make_unique<StringBuffer>()};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    stuff->addLong(value);
                    auto    resultString{stuff->getString()};

                    if (0 == resultString.compare(outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == resultString.compare(outString))"); //####
                    }
                }
            }
            else
            {
                ODL_LOG("! ConvertToInt64(*argv, value)"); //####
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringBufferWithInteger

#if defined(__APPLE__)
# pragma mark *** Test Case 14 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithString
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  inString{*argv};
            CPtr(char)  outString{argv[1]};
            size_t      outLength{strlen(outString)};
            auto        stuff{std::make_unique<StringBuffer>()};

            if (nullptr == stuff)
            {
                ODL_LOG("(nullptr == stuff)"); //####
            }
            else
            {
                stuff->addString(inString, true);
                size_t  resultLength{stuff->getLength()};

                if (resultLength == outLength)
                {
                    auto    resultString{stuff->getString()};

                    if (0 == resultString.compare(outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == resultString.compare(outString))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (resultLength == outLength)"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringBufferWithString

#if defined(__APPLE__)
# pragma mark *** Test Case 15 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithSpecialCharacters
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
        CPtr(char)  inString{"abc\tdef\f\rghi\302"};
        CPtr(char)  outString{"\"abc\\tdef\\f\\rghi\\M-B\""};
        size_t      outLength{strlen(outString)};
        auto        stuff{std::make_unique<StringBuffer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            stuff->addString(inString, true);
            size_t  resultLength{stuff->getLength()};

            if (resultLength == outLength)
            {
                auto    resultString{stuff->getString()};

                if (0 == resultString.compare(outString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == resultString.compare(outString))"); //####
                }
            }
            else
            {
                ODL_LOG("! (resultLength == outLength)"); //####
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
} // doTestStringBufferWithSpecialCharacters

#if defined(__APPLE__)
# pragma mark *** Test Case 16 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithDouble
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  outString{argv[1]};
            double      value;

            if (ConvertToDouble(*argv, value))
            {
                auto    stuff{std::make_unique<StringBuffer>()};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    stuff->addDouble(value);
                    auto    resultString{stuff->getString()};
                    size_t  ii{0};

                    for (result = 0; (kEndOfString != *outString) && (kEndOfString != resultString[ii]); ++outString, ++ii)
                    {
                        char    outChar{StaticCast(char, tolower(*outString))};
                        char    resultChar{StaticCast(char, tolower(resultString[ii]))};

                        if (outChar != resultChar)
                        {
                            break;

                        }
                    }
                    if ((kEndOfString != *outString) || (kEndOfString != resultString[ii]))
                    {
                        ODL_LOG("(*outString || resultString[ii])"); //####
                        result = 1;
                    }
                }
            }
            else
            {
                ODL_LOG("! ConvertToDouble(*argv, value)"); //####
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringBufferWithDouble

#if defined(__APPLE__)
# pragma mark *** Test Case 17 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBigStringBuffer
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
        auto    stuff{std::make_unique<StringBuffer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            CPtr(char)  bigString{"abcdefghijklmnopqrstuvwxyz0123456789"};
            size_t      bigLength{strlen(bigString)};

            for (size_t ii = 0; kBigTestSize > ii; ++ii)
            {
                stuff->addString(bigString);
            }
            auto    resultString{stuff->getString()};
            size_t  length = resultString.size();

            if ((bigLength * kBigTestSize) == length)
            {
                auto bytes{resultString.data()};

                result = 0;
                for (size_t ii = 0; (0 == result) && (kBigTestSize > ii); ++ii, bytes += bigLength)
                {
                    if (0 != CompareBytes(bigString, bytes, bigLength))
                    {
                        ODL_LOG("(0 != CompareBytes(bigString, bytes, bigLength))"); //####
                        result = 1;
                    }
                }
            }
            else
            {
                ODL_LOG("! ((bigLength * kBigTestSize) == length)"); //####
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
} // doTestBigStringBuffer

#if defined(__APPLE__)
# pragma mark *** Test Case 18 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithEmptyBlob
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
        auto    stuff{std::make_unique<StringBuffer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            stuff->addBytes(nullptr, 0);
            auto        resultString{stuff->getString()};
            CPtr(char)  expectedString{"%0%%"};

            if (0 == resultString.compare(expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == resultString.compare(expectedString))"); //####
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
} // doTestStringBufferWithEmptyBlob

#if defined(__APPLE__)
# pragma mark *** Test Case 19 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithSmallBlob
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
        auto    stuff{std::make_unique<StringBuffer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            auto    smallBlob{std::make_unique<uint8_t[]>(kSmallTestSize)};

            if (nullptr != smallBlob)
            {
                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    Ptr(uint8_t)    addr{smallBlob.get()};
                    uint8_t         aByte{StaticCast(uint8_t, ReinterpretCast(intptr_t, addr) ^ ii)};

                    smallBlob[ii] = aByte;
                }
                stuff->addBytes(smallBlob.get(), kSmallTestSize);
                auto        resultString{stuff->getString()};
                std::string expectedString{"%"s + std::to_string(kSmallTestSize) + "%"s};

                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    uint8_t aByte{smallBlob[ii]};
                    char    highByte{kHexDigits[(aByte >> 4) & 0x0F]};
                    char    lowByte{kHexDigits[aByte & 0x0F]};

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%"s;
                if (0 == resultString.compare(expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == resultString.compare(expectedString))"); //####
                }
            }
            else
            {
                ODL_LOG("! (nullptr != smallBlob)"); //####
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
} // doTestStringBufferWithSmallBlob

#if defined(__APPLE__)
# pragma mark *** Test Case 20 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithBigBlob
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
        auto    stuff{std::make_unique<StringBuffer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            auto    bigBlob{std::make_unique<uint8_t[]>(kBigTestSize)};

            if (nullptr != bigBlob)
            {
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    Ptr(uint8_t)    addr{bigBlob.get()};
                    uint8_t         aByte{StaticCast(uint8_t, ReinterpretCast(intptr_t, addr) ^ ii)};

                    bigBlob[ii] = aByte;
                }
                stuff->addBytes(bigBlob.get(), kBigTestSize);
                auto        resultString{stuff->getString()};
                std::string expectedString{"%"s + std::to_string(kBigTestSize) + "%"s};

                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    uint8_t aByte{bigBlob[ii]};
                    char    highByte{kHexDigits[(aByte >> 4) & 0x0F]};
                    char    lowByte{kHexDigits[aByte & 0x0F]};

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%"s;
                if (0 == resultString.compare(expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == resultString.compare(expectedString))"); //####
                }
            }
            else
            {
                ODL_LOG("! (nullptr != bigBlob)"); //####
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
} // doTestStringBufferWithBigBlob

#if defined(__APPLE__)
# pragma mark *** Test Case 21 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferReset
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
        auto    stuff{std::make_unique<StringBuffer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            stuff->addString("abcdef");
            stuff->reset();
            size_t  resultLength{stuff->getLength()};

            if (0 == resultLength)
            {
                auto    resultString{stuff->getString()};

                if (0 == resultString.length())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == resultString.length())"); //####
                }
            }
            else
            {
                ODL_LOG("! (0 == stuff->getLength())"); //####
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
} // doTestStringBufferReset

#if defined(__APPLE__)
# pragma mark *** Test Case 50 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultLogicalValue
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
        auto    stuff{std::make_unique<Logical>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == compareValueWithString(*stuff, "false"))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, \"false\"))"); //####
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
} // doTestDefaultLogicalValue

#if defined(__APPLE__)
# pragma mark *** Test Case 51 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  outString{argv[1]};
            int64_t     value;

            if (ConvertToInt64(*argv, value) && (0 <= value))
            {
                auto    stuff{std::make_unique<Logical>(0 != value)};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    if (0 == compareValueWithString(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
                    }
                }
            }
            else
            {
                ODL_LOG("! (ConvertToInt64(*argv, value) && (0 <= value))"); //####
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalValue

#if defined(__APPLE__)
# pragma mark *** Test Case 52 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultIntegerValue
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
        auto    stuff{std::make_unique<Integer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if ((0 == compareValueWithString(*stuff, "0")) && (nullptr != stuff->asInteger()))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! ((0 == compareValueWithString(*stuff, \"0\")) && " //####
                        "(nullptr != stuff->asInteger()))"); //####
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
} // doTestDefaultIntegerValue

#if defined(__APPLE__)
# pragma mark *** Test Case 53 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNumberValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  outString{argv[1]};
            int64_t     intValue;

            if (ConvertToInt64(*argv, intValue))
            {
                auto    stuff{std::make_unique<Integer>(intValue)};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    if (0 == compareValueWithString(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
                    }
                }
            }
            else
            {
                double floatValue;

                if (ConvertToDouble(*argv, floatValue))
                {
                    auto    stuff{std::make_unique<Double>(floatValue)};

                    if (nullptr == stuff)
                    {
                        ODL_LOG("(nullptr == stuff)"); //####
                    }
                    else
                    {
                        if (0 == compareValueWithString(*stuff, outString))
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
                        }
                    }
                }
                else
                {
                    ODL_LOG("! ConvertToDouble(*argv, floatValue)"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNumberValue

#if defined(__APPLE__)
# pragma mark *** Test Case 54 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultStringValue
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
        auto    stuff{std::make_unique<String>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == compareValueWithString(*stuff, "\"\""))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("(0 == compareValueWithString(*stuff, \"\\\"\\\"\"))"); //####
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
} // doTestDefaultStringValue

#if defined(__APPLE__)
# pragma mark *** Test Case 55 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            auto    stuff{std::make_unique<String>(*argv)};

            if (nullptr == stuff)
            {
                ODL_LOG("(nullptr == stuff)"); //####
            }
            else
            {
                if (0 == compareValueWithString(*stuff, argv[1]))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, argv[1]))"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringValue

#if defined(__APPLE__)
# pragma mark *** Test Case 56 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringValueWithEscapes
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
        CPtr(char)  inString{"abc\tdef\f\rghi\302"};
        CPtr(char)  outString{"\"abc\\tdef\\f\\rghi\\M-B\""};
        auto        stuff{std::make_unique<String>(inString)};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == compareValueWithString(*stuff, outString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
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
} // doTestStringValueWithEscapes

#if defined(__APPLE__)
# pragma mark *** Test Case 57 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultBlobValue
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
        auto    stuff{std::make_unique<Blob>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == compareValueWithString(*stuff, "%0%%"))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, \"%0%%\"))"); //####
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
} // doTestDefaultBlobValue

#if defined(__APPLE__)
# pragma mark *** Test Case 58 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallBlobValue
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
        auto    smallBlob{std::make_unique<uint8_t[]>(kSmallTestSize)};

        if (smallBlob)
        {
            for (size_t ii = 0; kSmallTestSize > ii; ++ii)
            {
                uint8_t aByte{StaticCast(uint8_t, ReinterpretCast(intptr_t, smallBlob.get()) ^ ii)};

                smallBlob[ii] = aByte;
            }
            auto    stuff{std::make_unique<Blob>(smallBlob.get(), kSmallTestSize)};

            if (nullptr == stuff)
            {
                ODL_LOG("(nullptr == stuff)"); //####
            }
            else
            {
                std::string expectedString{"%"s + std::to_string(kSmallTestSize) + "%"s};

                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    uint8_t aByte{smallBlob[ii]};
                    char    highByte{kHexDigits[(aByte >> 4) & 0x0F]};
                    char    lowByte{kHexDigits[aByte & 0x0F]};

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%"s;
                if (0 == compareValueWithString(*stuff, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, " //####
                            "expectedString.c_str()))"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (smallBlob)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallBlobValue

#if defined(__APPLE__)
# pragma mark *** Test Case 59 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBigBlobValue
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
        auto    bigBlob{std::make_unique<uint8_t[]>(kBigTestSize)};

        if (nullptr != bigBlob)
        {
            for (size_t ii = 0; kBigTestSize > ii; ++ii)
            {
                uint8_t aByte{StaticCast(uint8_t, ReinterpretCast(intptr_t, bigBlob.get()) ^ ii)};

                bigBlob[ii] = aByte;
            }
            auto    stuff{std::make_unique<Blob>(bigBlob.get(), kBigTestSize)};

            if (nullptr == stuff)
            {
                ODL_LOG("(nullptr == stuff)"); //####
            }
            else
            {
                std::string expectedString{"%"s + std::to_string(kBigTestSize) + "%"s};

                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    uint8_t aByte{bigBlob[ii]};
                    char    highByte{kHexDigits[(aByte >> 4) & 0x0F]};
                    char    lowByte{kHexDigits[aByte & 0x0F]};

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%"s;
                if (0 == compareValueWithString(*stuff, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, " //####
                            "expectedString.c_str()))"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != bigBlob)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestBigBlobValue

#if defined(__APPLE__)
# pragma mark *** Test Case 60 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalCopyAndAssign
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
    int result;

    try
    {
        Logical falseStuff{false};
        Logical trueStuff{true};

        if ((! falseStuff.getValue()) && trueStuff.getValue())
        {
            Logical falseCopy{falseStuff};
            Logical trueCopy{trueStuff};

            if ((falseCopy.getValue() == falseStuff.getValue()) && (trueCopy.getValue() == trueStuff.getValue()))
            {
                falseCopy = trueStuff;
                trueCopy = falseStuff;
                if ((falseCopy.getValue() == trueStuff.getValue()) &&
                    (trueCopy.getValue() == falseStuff.getValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((falseCopy.getValue() == trueStuff.getValue()) && " //####
                            "(trueCopy.getValue() == falseStuff.getValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((falseCopy.getValue() == falseStuff.getValue()) && " //####
                        "(trueCopy.getValue() == trueStuff.getValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((! falseStuff.getValue()) && trueStuff.getValue())"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalCopyAndAssign

#if defined(__APPLE__)
# pragma mark *** Test Case 61 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerCopyAndAssign
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
        static const int64_t value1{-1234};
        static const int64_t value2{0};
        static const int64_t value3{2345};
        Integer              negativeStuff{value1};
        Integer              zeroStuff{value2};
        Integer              positiveStuff{value3};

        if ((value1 == negativeStuff.getIntegerValue()) &&
            (value2 == zeroStuff.getIntegerValue()) &&
            (value3 == positiveStuff.getIntegerValue()))
        {
            Integer negativeCopy{negativeStuff};
            Integer zeroCopy{zeroStuff};
            Integer positiveCopy{positiveStuff};

            if ((negativeCopy.getIntegerValue() == negativeStuff.getIntegerValue()) &&
                (zeroCopy.getIntegerValue() == zeroStuff.getIntegerValue()) &&
                (positiveCopy.getIntegerValue() == positiveStuff.getIntegerValue()))
            {
                negativeCopy = zeroStuff;
                zeroCopy = positiveStuff;
                positiveCopy = negativeStuff;
                if ((negativeCopy.getIntegerValue() == zeroStuff.getIntegerValue()) &&
                    (zeroCopy.getIntegerValue() == positiveStuff.getIntegerValue()) &&
                    (positiveCopy.getIntegerValue() == negativeStuff.getIntegerValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((negativeCopy.getIntegerValue() == " //####
                            "zeroStuff.getIntegerValue()) && " //####
                            "(zeroCopy.getIntegerValue() == " //####
                            "positiveStuff.getIntegerValue()) && " //####
                            "(positiveCopy.getIntegerValue() == " //####
                            "negativeStuff.getIntegerValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((negativeCopy.getIntegerValue() == " //####
                        "negativeStuff.getIntegerValue()) && " //####
                        "(zeroCopy.getIntegerValue() == " //####
                        "zeroStuff.getIntegerValue()) && " //####
                        "(positiveCopy.getIntegerValue() == " //####
                        "positiveStuff.getIntegerValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((value1 == negativeStuff.getIntegerValue()) && " //####
                    "(value2 == zeroStuff.getIntegerValue()) && " //####
                    "(value3 == positiveStuff.getIntegerValue()))"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestIntegerCopyAndAssign

#if defined(__APPLE__)
# pragma mark *** Test Case 62 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDoubleCopyAndAssign
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
        static const double value1{-1234.5};
        static const double value2{0.0};
        static const double value3{2345.6};
        Double              negativeStuff{value1};
        Double              zeroStuff{value2};
        Double              positiveStuff{value3};

        if ((value1 == negativeStuff.getDoubleValue()) &&
            (value2 == zeroStuff.getDoubleValue()) &&
            (value3 == positiveStuff.getDoubleValue()))
        {
            Double negativeCopy{negativeStuff};
            Double zeroCopy{zeroStuff};
            Double positiveCopy{positiveStuff};

            if ((negativeCopy.getDoubleValue() == negativeStuff.getDoubleValue()) &&
                (zeroCopy.getDoubleValue() == zeroStuff.getDoubleValue()) &&
                (positiveCopy.getDoubleValue() == positiveStuff.getDoubleValue()))
            {
                negativeCopy = zeroStuff;
                zeroCopy = positiveStuff;
                positiveCopy = negativeStuff;
                if ((negativeCopy.getDoubleValue() == zeroStuff.getDoubleValue()) &&
                    (zeroCopy.getDoubleValue() == positiveStuff.getDoubleValue()) &&
                    (positiveCopy.getDoubleValue() == negativeStuff.getDoubleValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((negativeCopy.getDoubleValue() == " //####
                            "zeroStuff.getDoubleValue()) && " //####
                            "(zeroCopy.getDoubleValue() == " //####
                            "positiveStuff.getDoubleValue()) && " //####
                            "(positiveCopy.getDoubleValue() == " //####
                            "negativeStuff.getDoubleValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((negativeCopy.getDoubleValue() == " //####
                        "negativeStuff.getDoubleValue()) && " //####
                        "(zeroCopy.getDoubleValue() == zeroStuff.getDoubleValue()) && " //####
                        "(positiveCopy.getDoubleValue() == " //####
                        "positiveStuff.getDoubleValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((value1 == negativeStuff.getDoubleValue()) && " //####
                    "(value2 == zeroStuff.getDoubleValue()) && " //####
                    "(value3 == positiveStuff.getDoubleValue()))"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestDoubleCopyAndAssign

#if defined(__APPLE__)
# pragma mark *** Test Case 63 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringCopyAndAssign
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
        String emptyString;
        String shortString{"alphabetagamma"};

        if ((0 == emptyString.getValue().length()) && (shortString.getValue() == "alphabetagamma"s))
        {
            String  emptyCopy{emptyString};
            String  shortCopy{shortString};

            if ((emptyCopy.getValue() == emptyString.getValue()) && (shortCopy.getValue() == shortString.getValue()))
            {
                emptyCopy = shortString;
                shortCopy = emptyString;
                if ((emptyCopy.getValue() == shortString.getValue()) && (shortCopy.getValue() == emptyString.getValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((emptyCopy.getValue() == shortString.getValue()) && " //####
                            "(shortCopy.getValue() == emptyString.getValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((emptyCopy.getValue() == emptyString.getValue()) && " //####
                        "(shortCopy.getValue() == shortString.getValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((0 == emptyString.getValue().length()) && " //####
                    "(shortString.getValue() == \"alphabetagamma\"))"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringCopyAndAssign

#if defined(__APPLE__)
# pragma mark *** Test Case 64 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBlobCopyAndAssign
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
        auto    bigBlob{std::make_unique<uint8_t[]>(kBigTestSize)};
        auto    smallBlob{std::make_unique<uint8_t[]>(kSmallTestSize)};

        if ((nullptr != bigBlob) && (nullptr != smallBlob))
        {
            for (size_t ii = 0; kBigTestSize > ii; ++ii)
            {
                uint8_t aByte{StaticCast(uint8_t, ReinterpretCast(intptr_t, bigBlob.get()) ^ ii)};

                bigBlob[ii] = aByte;
            }
            for (size_t ii = 0; kSmallTestSize > ii; ++ii)
            {
                uint8_t aByte{StaticCast(uint8_t, ReinterpretCast(intptr_t, smallBlob.get()) ^ ii)};

                smallBlob[ii] = aByte;
            }
            Blob            smallStuff{smallBlob.get(), kSmallTestSize};
            Blob            bigStuff{bigBlob.get(), kBigTestSize};
            size_t          smallLength{0};
            size_t          bigLength{0};
            CPtr(uint8_t)   smallValue{smallStuff.getValue(smallLength)};
            CPtr(uint8_t)   bigValue{bigStuff.getValue(bigLength)};

            result = ((kSmallTestSize == smallLength) ? 0 : 1);
            if (0 == result)
            {
                result = StaticCast(int, CompareBytes(smallValue, smallBlob.get(), kSmallTestSize));
            }
            if (0 == result)
            {
                result = ((kBigTestSize == bigLength) ? 0 : 1);
                if (0 == result)
                {
                    result = StaticCast(int, CompareBytes(bigValue, bigBlob.get(), kBigTestSize));
                }
            }
            if (0 == result)
            {
                Blob    smallCopy{smallStuff};
                Blob    bigCopy{bigStuff};

                smallLength = bigLength = 0;
                smallValue = smallCopy.getValue(smallLength);
                bigValue = bigCopy.getValue(bigLength);
                result = ((kSmallTestSize == smallLength) ? 0 : 1);
                if (0 == result)
                {
                    result = StaticCast(int, CompareBytes(smallValue, smallBlob.get(), kSmallTestSize));
                }
                if (0 == result)
                {
                    result = ((kBigTestSize == bigLength) ? 0 : 1);
                    if (0 == result)
                    {
                        result = StaticCast(int, CompareBytes(bigValue, bigBlob.get(), kBigTestSize));
                    }
                }
                if (0 == result)
                {
                    smallCopy = bigStuff;
                    bigCopy = smallStuff;
                    smallLength = bigLength = 0;
                    smallValue = smallCopy.getValue(smallLength);
                    bigValue = bigCopy.getValue(bigLength);
                    result = ((kBigTestSize == smallLength) ? 0 : 1);
                    if (0 == result)
                    {
                        result = StaticCast(int, CompareBytes(smallValue, bigBlob.get(), kBigTestSize));
                    }
                    if (0 == result)
                    {
                        result = ((kSmallTestSize == bigLength) ? 0 : 1);
                        if (0 == result)
                        {
                            result = StaticCast(int, CompareBytes(bigValue, smallBlob.get(), kSmallTestSize));
                        }
                    }
                }
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
} // doTestBlobCopyAndAssign

#if defined(__APPLE__)
# pragma mark *** Test Case 65 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultAddressValue
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
        auto    stuff{std::make_unique<Address>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if ((0 == compareValueWithString(*stuff, "@0.0.0.0")) && (nullptr != stuff->asAddress()))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! ((0 == compareValueWithString(*stuff, \"0.0.0.0\")) && " //####
                        "(nullptr != stuff->asAddress()))"); //####
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
} // doTestDefaultAddressValue

#if defined(__APPLE__)
# pragma mark *** Test Case 66 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddressValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
//    ODL_S1("launchPath = ", launchPath); //####
//    ODL_I1("argc = ", argc); //####
//    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            Address::IPv4Bytes  asBytes;
            CPtr(char)          outString{argv[1]};

            if (getIPv4Bytes(asBytes, argv[0]))
            {
                auto    stuff{std::make_unique<Address>(asBytes)};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    if (0 == compareValueWithString(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
                    }
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestAddressValue

#if defined(__APPLE__)
# pragma mark *** Test Case 67 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddressCopyAndAssign
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
        static const IPv4Address    value1{0x12345678};
        static const IPv4Address    value2{0x345678AB};
        static const IPv4Address    value3{0x5678ABCD};
        Address                     address1{value1};
        Address                     address2{value2};
        Address                     address3{value3};

        if ((value1 == address1.getAddressValue()) &&
            (value2 == address2.getAddressValue()) &&
            (value3 == address3.getAddressValue()))
        {
            Address copy1{address1};
            Address copy2{address2};
            Address copy3{address3};

            if ((copy1.getAddressValue() == address1.getAddressValue()) &&
                (copy2.getAddressValue() == address2.getAddressValue()) &&
                (copy3.getAddressValue() == address3.getAddressValue()))
            {
                copy1 = address2;
                copy2 = address3;
                copy3 = address1;
                if ((copy1.getAddressValue() == address2.getAddressValue()) &&
                    (copy2.getAddressValue() == address3.getAddressValue()) &&
                    (copy3.getAddressValue() == address1.getAddressValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((copy1.getAddressValue() == address2.getAddressValue()) && " //####
                            "(copy2.getAddressValue() == address3.getAddressValue()) && " //####
                            "(copy3.getAddressValue() == address1.getAddressValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((copy1.getAddressValue() == address1.getAddressValue()) && " //####
                        "(copy2.getAddressValue() == address2.getAddressValue()) && " //####
                        "(copy3.getAddressValue() == address3.getAddressValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((value1 == address1.getAddressValue()) && " //####
                    "(value2 == address2.getAddressValue()) && " //####
                    "(value3 == address3.getAddressValue()))"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestAddressCopyAndAssign

#if defined(__APPLE__)
# pragma mark *** Test Case 80 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidLogicalCompares
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
    int result{0};

    try
    {
        struct tests
        {
            bool                _leftValue;
            bool                _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // tests

        const tests testSet[]
        {
            { false, false,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { false, true,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { true,  false,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { true,  true,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} } // ==
        };
        constexpr size_t    numTests{numElementsInArray(testSet)};

        for (size_t ii = 0; (0 == result) && (numTests > ii); ++ii)
        {
            Logical leftValue{testSet[ii]._leftValue};
            Logical rightValue{testSet[ii]._rightValue};

            if (testSet[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
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
} // doTestValidLogicalCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 81 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidNumberCompares
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
    int result{0};

    try
    {
        struct testsI2I
        {
            int64_t             _leftValue;
            int64_t             _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testsI2I
        struct testsI2R
        {
            int64_t             _leftValue;
            double              _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testsI2R
        struct testsR2I
        {
            double              _leftValue;
            int64_t             _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testsR2I
        struct testsR2R
        {
            double              _leftValue;
            double              _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testsR2R

        const testsI2I      testSet1[]
        {
            // l   r
            { 0,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { 0,   1,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 0,  -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { -1,  0,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { -1, -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} } // ==
        };
        constexpr size_t    numTests1{numElementsInArray(testSet1)};
        const testsI2R      testSet2[]
        {
            // l   r
            { 0,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { 0,   1,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 0,  -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { -1,  0,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { -1, -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} } // ==
        };
        constexpr size_t    numTests2{numElementsInArray(testSet2)};
        const testsR2I      testSet3[]
        {
            // l   r
            { 0,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { 0,   1,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 0,  -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { -1,  0,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { -1, -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} } // ==
        };
        constexpr size_t    numTests3{numElementsInArray(testSet3)};
        const testsR2R      testSet4[]
        {
            // l   r
            { 0,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { 0,   1,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 0,  -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   0,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { -1,  0,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 1,   1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { -1, -1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} } // ==
        };
        constexpr size_t    numTests4{numElementsInArray(testSet4)};

        for (size_t ii = 0; (0 == result) && (numTests1 > ii); ++ii)
        {
            Integer leftValue{testSet1[ii]._leftValue};
            Integer rightValue{testSet1[ii]._rightValue};

            if (testSet1[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet1[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTests2 > ii); ++ii)
        {
            Integer leftValue{testSet2[ii]._leftValue};
            Double  rightValue{testSet2[ii]._rightValue};

            if (testSet2[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet2[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet2[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet2[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet2[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet2[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet2[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet2[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet2[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet2[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTests3 > ii); ++ii)
        {
            Double  leftValue{testSet3[ii]._leftValue};
            Integer rightValue{testSet3[ii]._rightValue};

            if (testSet3[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet3[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet3[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet3[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet3[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet3[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet3[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet3[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet3[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet3[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTests4 > ii); ++ii)
        {
            Double  leftValue{testSet4[ii]._leftValue};
            Double  rightValue{testSet4[ii]._rightValue};

            if (testSet4[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet4[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet4[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet4[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet4[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet4[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet4[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet4[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet4[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet4[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
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
} // doTestValidNumberCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 82 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidStringCompares
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
    int result{0};

    try
    {
        struct tests
        {
            CPtr(char)          _leftValue;
            CPtr(char)          _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // tests

        const tests testSet[]
        {
            // left  right
            { "",    "",
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { "",    "abc",
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { "abc",  "",
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { "abc",  "abc",
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { "abc",  "def",
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { "def",  "abc",
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { "abc",  "abcd",
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { "abcd", "abc",
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} } // ==
        };
        constexpr size_t    numTests{numElementsInArray(testSet)};

        for (size_t ii = 0; (0 == result) && (numTests > ii); ++ii)
        {
            String leftValue{testSet[ii]._leftValue};
            String rightValue{testSet[ii]._rightValue};

            if (testSet[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
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
} // doTestValidStringCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 83 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidBlobCompares
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
    int result{0};

    try
    {
        struct tests
        {
            CPtr(Blob)          _leftValue;
            CPtr(Blob)          _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // tests

        const uint8_t       blobData1[]{ 1, 2, 3, 4, 5, 6 };
        const uint8_t       blobData2[]{ 1, 2, 3, 4, 5, 6, 7 };
        const uint8_t       blobData3[]{ 1, 2, 3, 4, 5, 7 };
        constexpr size_t    blobSize1{numElementsInArray(blobData1)};
        constexpr size_t    blobSize2{numElementsInArray(blobData2)};
        constexpr size_t    blobSize3{numElementsInArray(blobData3)};
        Blob                blob0;
        Blob                blob1(blobData1, blobSize1);
        Blob                blob2(blobData2, blobSize2);
        Blob                blob3(blobData3, blobSize3);
        const tests         testSet[]
        {
            // left   right
            { &blob0, &blob0,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { &blob0, &blob1,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { &blob1, &blob0,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { &blob1, &blob1,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { &blob1, &blob3,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { &blob3, &blob1,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { &blob1, &blob2,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { &blob2, &blob1,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} } // ==
        };
        constexpr size_t    numTests{numElementsInArray(testSet)};

        for (size_t ii = 0; (0 == result) && (numTests > ii); ++ii)
        {
            const Blob &    leftValue{*testSet[ii]._leftValue};
            const Blob &    rightValue{*testSet[ii]._rightValue};

            if (testSet[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
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
} // doTestValidBlobCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 84 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidLogicalCompares
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
    int result{0};

    try
    {
        ComparisonStatus    status;
        Logical             leftValue;
        Number              rightValue1;
        String              rightValue2;
        Blob                rightValue3;
        Address             rightValue4;
        Ptr(Value)          rightValues[]{ &rightValue1, &rightValue2, &rightValue3, &rightValue4 };
        constexpr size_t    numRightValues{numElementsInArray(rightValues)};

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue{*rightValues[ii]};

            status = leftValue.lessThan(aRightValue);
            if (status.IsValid())
            {
                ODL_LOG("(status.IsValid())"); //####
                result = 1;
            }
            else
            {
                status = leftValue.greaterThan(aRightValue);
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.lessThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.greaterThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.equalTo(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
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
} // doTestInvalidLogicalCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 85 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidNumberCompares
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
    int result{0};

    try
    {
        ComparisonStatus    status;
        Number              leftValue;
        Logical             rightValue1;
        String              rightValue2;
        Blob                rightValue3;
        Address             rightValue4;
        Ptr(Value)          rightValues[]{ &rightValue1, &rightValue2, &rightValue3, &rightValue4 };
        constexpr size_t    numRightValues{numElementsInArray(rightValues)};

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue{*rightValues[ii]};

            status = leftValue.lessThan(aRightValue);
            if (status.IsValid())
            {
                ODL_LOG("(status.IsValid())"); //####
                result = 1;
            }
            else
            {
                status = leftValue.greaterThan(aRightValue);
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.lessThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.greaterThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.equalTo(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
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
} // doTestInvalidNumberCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 86 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidStringCompares
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
    int result{0};

    try
    {
        ComparisonStatus    status;
        String              leftValue;
        Logical             rightValue1;
        Number              rightValue2;
        Blob                rightValue3;
        Address             rightValue4;
        Ptr(Value)          rightValues[]{ &rightValue1, &rightValue2, &rightValue3, &rightValue4 };
        constexpr size_t    numRightValues{numElementsInArray(rightValues)};

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue{*rightValues[ii]};

            status = leftValue.lessThan(aRightValue);
            if (status.IsValid())
            {
                ODL_LOG("(status.IsValid())"); //####
                result = 1;
            }
            else
            {
                status = leftValue.greaterThan(aRightValue);
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.lessThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.greaterThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.equalTo(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
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
} // doTestInvalidStringCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 87 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidBlobCompares
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
    int result{0};

    try
    {
        ComparisonStatus    status;
        Blob                leftValue;
        Logical             rightValue1;
        Number              rightValue2;
        String              rightValue3;
        Address             rightValue4;
        Ptr(Value)          rightValues[]{ &rightValue1, &rightValue2, &rightValue3, &rightValue4 };
        constexpr size_t    numRightValues{numElementsInArray(rightValues)};

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue{*rightValues[ii]};

            status = leftValue.lessThan(aRightValue);
            if (status.IsValid())
            {
                ODL_LOG("(status.IsValid())"); //####
                result = 1;
            }
            else
            {
                status = leftValue.greaterThan(aRightValue);
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.lessThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.greaterThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.equalTo(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
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
} // doTestInvalidBlobCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 88 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidAddressCompares
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
    int result{0};

    try
    {
        struct testsA2A
        {
            IPv4Address         _leftValue;
            IPv4Address         _rightValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testsA2A

        const testsA2A  testSet1[]
        {
            // l   r
            { 0x00000000, 0x00000000,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { 0x00000000, 0x00000001,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 0x12345678, 0x10000000,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { 0x00000001, 0x00000000,
                ComparisonStatus{false}, // <
                ComparisonStatus{true}, // >
                ComparisonStatus{false}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{false} }, // ==
            { 0x10000000, 0x12345678,
                ComparisonStatus{true}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{false}, // >=
                ComparisonStatus{false} }, // ==
            { 0x00000001, 0x00000001,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} }, // ==
            { 0x10000000, 0x10000000,
                ComparisonStatus{false}, // <
                ComparisonStatus{false}, // >
                ComparisonStatus{true}, // <=
                ComparisonStatus{true}, // >=
                ComparisonStatus{true} } // ==
        };
        constexpr size_t    numTests1{numElementsInArray(testSet1)};

        for (size_t ii = 0; (0 == result) && (numTests1 > ii); ++ii)
        {
            Address leftValue{testSet1[ii]._leftValue};
            Address rightValue{testSet1[ii]._rightValue};

            if (testSet1[ii]._lessThan != leftValue.lessThan(rightValue))
            {
                ODL_LOG("(testSet1[ii]._lessThan != leftValue.lessThan(rightValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1[ii]._greaterThan != leftValue.greaterThan(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._greaterThan != leftValue.greaterThan(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._lessThanOrEqual != leftValue.lessThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._greaterThanOrEqual != leftValue.greaterThanOrEqual(rightValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1[ii]._equalTo != leftValue.equalTo(rightValue))
                {
                    ODL_LOG("(testSet1[ii]._equalTo != leftValue.equalTo(rightValue))"); //####
                    result = 1;
                }
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
} // doTestValidAddressCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 89 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidAddressCompares
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
    int result{0};

    try
    {
        ComparisonStatus    status;
        Address             leftValue;
        Logical             rightValue1;
        String              rightValue2;
        Blob                rightValue3;
        Integer             rightValue4;
        Ptr(Value)          rightValues[]{ &rightValue1, &rightValue2, &rightValue3, &rightValue4 };
        constexpr size_t    numRightValues{numElementsInArray(rightValues)};

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue{*rightValues[ii]};

            status = leftValue.lessThan(aRightValue);
            if (status.IsValid())
            {
                ODL_LOG("(status.IsValid())"); //####
                result = 1;
            }
            else
            {
                status = leftValue.greaterThan(aRightValue);
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.lessThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.greaterThanOrEqual(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
                else
                {
                    status = leftValue.equalTo(aRightValue);
                }
            }
            if (0 == result)
            {
                if (status.IsValid())
                {
                    ODL_LOG("(status.IsValid())"); //####
                    result = 1;
                }
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
} // doTestInvalidAddressCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultLogicalValueAsJSON
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
        auto    stuff{std::make_unique<Logical>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == compareValueWithStringAsJSON(*stuff, "false"))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, \"false\"))"); //####
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
} // doTestDefaultLogicalValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  outString{argv[1]};
            int64_t     value;

            if (ConvertToInt64(*argv, value) && (0 <= value))
            {
                auto    stuff{std::make_unique<Logical>(0 != value)};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    if (0 == compareValueWithStringAsJSON(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, outString))"); //####
                    }
                }
            }
            else
            {
                ODL_LOG("! (ConvertToInt64(*argv, value) && (0 <= value))"); //####
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultIntegerValueAsJSON
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
        auto    stuff{std::make_unique<Integer>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if ((0 == compareValueWithStringAsJSON(*stuff, "0")) && (nullptr != stuff->asInteger()))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! ((0 == compareValueWithStringAsJSON(*stuff, \"0\")) && " //####
                        "(nullptr != stuff->asInteger()))"); //####
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
} // doTestDefaultIntegerValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 103 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNumberValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            CPtr(char)  outString{argv[1]};
            int64_t     intValue;

            if (ConvertToInt64(*argv, intValue))
            {
                auto    stuff{std::make_unique<Integer>(intValue)};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    if (0 == compareValueWithStringAsJSON(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, outString))"); //####
                    }
                }
            }
            else
            {
                double floatValue;

                if (ConvertToDouble(*argv, floatValue))
                {
                    auto    stuff{std::make_unique<Double>(floatValue)};

                    if (nullptr == stuff)
                    {
                        ODL_LOG("(nullptr == stuff)"); //####
                    }
                    else
                    {
                        if (0 == compareValueWithStringAsJSON(*stuff, outString))
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, outString))"); //####
                        }
                    }
                }
                else
                {
                    ODL_LOG("! ConvertToDouble(*argv, floatValue)"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNumberValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 104 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultStringValueAsJSON
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
        auto    stuff{std::make_unique<String>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if (0 == compareValueWithStringAsJSON(*stuff, "\"\""))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("(0 == compareValueWithStringAsJSON(*stuff, \"\\\"\\\"\"))"); //####
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
} // doTestDefaultStringValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 105 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            auto    stuff{std::make_unique<String>(*argv)};

            if (nullptr == stuff)
            {
                ODL_LOG("(nullptr == stuff)"); //####
            }
            else
            {
                if (0 == compareValueWithStringAsJSON(*stuff, argv[1]))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, argv[1]))"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 106 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDefaultAddressValueJSON
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
        auto    stuff{std::make_unique<Address>()};

        if (nullptr == stuff)
        {
            ODL_LOG("(nullptr == stuff)"); //####
        }
        else
        {
            if ((0 == compareValueWithStringAsJSON(*stuff, "\"0.0.0.0\"")) && (nullptr != stuff->asAddress()))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! ((0 == compareValueWithStringAsJSON(*stuff, \"\\\"0\\\"\")) && " //####
                        "(nullptr != stuff->asAddress()))"); //####
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
} // doTestDefaultAddressValueJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 107 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddressValueJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            Address::IPv4Bytes  asBytes;
            CPtr(char)          outString{argv[1]};

            if (getIPv4Bytes(asBytes, argv[0]))
            {
                auto    stuff{std::make_unique<Address>(asBytes)};

                if (nullptr == stuff)
                {
                    ODL_LOG("(nullptr == stuff)"); //####
                }
                else
                {
                    if (0 == compareValueWithStringAsJSON(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, outString))"); //####
                    }
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doAddressValueJSON

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
                    case 0 :
                        // Just used to validate the random number seed.
                        result = 0;
                        break;

                    case 1 :
                        result = doTestEmptyBufferChunk(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestBufferChunkWithSingleByte(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestFilledBufferChunk(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestOverfilledBufferChunk(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestBufferChunkReset(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestEmptyStringBuffer(*argv, argc - 1, argv + 2);
                        break;

                    case 11 :
                        result = doTestStringBufferWithCharacters(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestStringBufferWithLogical(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestStringBufferWithInteger(*argv, argc - 1, argv + 2);
                        break;

                    case 14 :
                        result = doTestStringBufferWithString(*argv, argc - 1, argv + 2);
                        break;

                    case 15 :
                        result = doTestStringBufferWithSpecialCharacters(*argv, argc - 1, argv + 2);
                        break;

                    case 16 :
                        result = doTestStringBufferWithDouble(*argv, argc - 1, argv + 2);
                        break;

                    case 17 :
                        result = doTestBigStringBuffer(*argv, argc - 1, argv + 2);
                        break;

                    case 18 :
                        result = doTestStringBufferWithEmptyBlob(*argv, argc - 1, argv + 2);
                        break;

                    case 19 :
                        result = doTestStringBufferWithSmallBlob(*argv, argc - 1, argv + 2);
                        break;

                    case 20 :
                        result = doTestStringBufferWithBigBlob(*argv, argc - 1, argv + 2);
                        break;

                    case 21 :
                        result = doTestStringBufferReset(*argv, argc - 1, argv + 2);
                        break;

                    case 50 :
                        result = doTestDefaultLogicalValue(*argv, argc - 1, argv + 2);
                        break;

                    case 51 :
                        result = doTestLogicalValue(*argv, argc - 1, argv + 2);
                        break;

                    case 52 :
                        result = doTestDefaultIntegerValue(*argv, argc - 1, argv + 2);
                        break;

                    case 53 :
                        result = doTestNumberValue(*argv, argc - 1, argv + 2);
                        break;

                    case 54 :
                        result = doTestDefaultStringValue(*argv, argc - 1, argv + 2);
                        break;

                    case 55 :
                        result = doTestStringValue(*argv, argc - 1, argv + 2);
                        break;

                    case 56 :
                        result = doTestStringValueWithEscapes(*argv, argc - 1, argv + 2);
                        break;

                    case 57 :
                        result = doTestDefaultBlobValue(*argv, argc - 1, argv + 2);
                        break;

                    case 58 :
                        result = doTestSmallBlobValue(*argv, argc - 1, argv + 2);
                        break;

                    case 59 :
                        result = doTestBigBlobValue(*argv, argc - 1, argv + 2);
                        break;

                    case 60 :
                        result = doTestLogicalCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 61 :
                        result = doTestIntegerCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 62 :
                        result = doTestDoubleCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 63 :
                        result = doTestStringCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 64 :
                        result = doTestBlobCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 65 :
                        result = doTestDefaultAddressValue(*argv, argc - 1, argv + 2);
                        break;

                    case 66 :
                        result = doTestAddressValue(*argv, argc - 1, argv + 2);
                        break;

                    case 67 :
                        result = doTestAddressCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 80 :
                        result = doTestValidLogicalCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 81 :
                        result = doTestValidNumberCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 82 :
                        result = doTestValidStringCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 83 :
                        result = doTestValidBlobCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 84 :
                        result = doTestInvalidLogicalCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 85 :
                        result = doTestInvalidNumberCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 86 :
                        result = doTestInvalidStringCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 87 :
                        result = doTestInvalidBlobCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 88 :
                        result = doTestValidAddressCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 89 :
                        result = doTestInvalidAddressCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 100 :
                        result = doTestDefaultLogicalValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestLogicalValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestDefaultIntegerValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 103 :
                        result = doTestNumberValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 104 :
                        result = doTestDefaultStringValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 105 :
                        result = doTestStringValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 106 :
                        result = doTestDefaultAddressValueJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 107 :
                        result = doTestAddressValueJSON(*argv, argc - 1, argv + 2);
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

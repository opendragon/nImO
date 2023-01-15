//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOcontainerTest.cpp
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
//  Created:    2016-04-05
//
//--------------------------------------------------------------------------------------------------

#include <nImOarray.h>
#include <nImOblob.h>
#include <nImObufferChunk.h>
#include <nImOdouble.h>
#include <nImOinteger.h>
#include <nImOlogical.h>
#include <nImOmap.h>
#include <nImOset.h>
#include <nImOstring.h>
#include <nImOstringBuffer.h>
#include <nImOtestContext.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#include <stdio.h>

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

/*! @brief The number of elements in a big test. */
static const size_t kBigTestSize = 100000;

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

/*! @brief Compare a Value object with a string.
 @param[in] aValue The object to be compared.
 @param[in] aString The string to be compared to.
 @return @c -1, @c 0 or @c 1 depending on whether the string is greater than, equal to or less than
 the object representation as a string. */
static int
compareValueWithSquishedString
    (const Value &  aValue,
     CPtr(char)     aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    StringBuffer    buff;
    int             result;

    aValue.printToStringBuffer(buff, true);
    auto    resultString{buff.getString()};

    result = resultString.compare(aString);
    ODL_S2("got: ", resultString.c_str(), "expected: ", aString); //####
    ODL_EXIT_I(result); //####
    return result;
} // compareValueWithSquishedString

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
    auto    resultString{buff.getString()};

    result = resultString.compare(aString);
    ODL_S2("got: ", resultString.c_str(), "expected: ", aString); //####
    ODL_EXIT_I(result); //####
    return result;
} // compareValueWithString

/*! @brief Compare a Value object with a JSON string.
 @param[in] aValue The object to be compared.
 @param[in] aString The JSON string to be compared to.
 @return @c -1, @c 0 or @c 1 depending on whether the string is greater than, equal to or less than
 the object representation as JSON. */
static int
compareValueWithSquishedStringAsJSON
    (const Value &  aValue,
     CPtr(char)     aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    StringBuffer    buff;
    int             result;

    aValue.printToStringBufferAsJSON(buff, true);
    auto    resultString{buff.getString()};

    result = resultString.compare(aString);
    ODL_S2("got: ", resultString.c_str(), "expected: ", aString); //####
    ODL_EXIT_I(result); //####
    return result;
} // compareValueWithSquishedStringAsJSON

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
    auto    resultString{buff.getString()};

    result = resultString.compare(aString);
    ODL_S2("got: ", resultString.c_str(), "expected: ", aString); //####
    ODL_EXIT_I(result); //####
    return result;
} // compareValueWithStringAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 1 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyArrayValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar, kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ', kEndArrayChar, kEndOfString
            };

            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyArrayValue

#if defined(__APPLE__)
# pragma mark *** Test Case 2 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularArrayValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                    '1', '2', '3', '.', '4', '5',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                    '1', '2', '3', '.', '4', '5', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Double>(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularArrayValue

#if defined(__APPLE__)
# pragma mark *** Test Case 3 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallArrayValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                    '1', '2', '3', '.', '4', '5', ' ',
                    't', 'r', 'u', 'e', ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                    '4', '2',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                    '1', '2', '3', '.', '4', '5', ' ',
                    't', 'r', 'u', 'e', ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                    '4', '2', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<String>("charlie"));
            stuff->addValue(std::make_shared<Integer>(42));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallArrayValue

#if defined(__APPLE__)
# pragma mark *** Test Case 4 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBigArrayValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // big array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            UpAuint8_t  bigBlob{new uint8_t[kBigTestSize]};

            if (nullptr != bigBlob)
            {
                std::string expectedSquishedString;
                std::string expectedString;
                char        numBuff[10];

                expectedSquishedString += kStartArrayChar;
                expectedString += kStartArrayChar;
                expectedString += ' ';
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    Ptr(uint8_t)    addr = bigBlob.get();
                    uint8_t         aByte = StaticCast(uint8_t, ReinterpretCast(intptr_t, addr) ^ ii);

                    if (0 != ii)
                    {
                        expectedSquishedString += ' ';
                    }
                    bigBlob[ii] = aByte;
                    stuff->addValue(std::make_shared<Integer>(aByte));
                    snprintf(numBuff, sizeof(numBuff), "%d ", aByte);
                    expectedString += numBuff;
                    snprintf(numBuff, sizeof(numBuff), "%d", aByte);
                    expectedSquishedString += numBuff;
                }
                expectedSquishedString += kEndArrayChar;
                expectedString += kEndArrayChar;
                if (0 == compareValueWithString(*stuff, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
                }
                if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                            "expectedSquishedString))"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestBigArrayValue

#if defined(__APPLE__)
# pragma mark *** Test Case 5 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyArraySizeFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array size()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
     //ODL_S1("launchPath = ", launchPath); //####
     //ODL_I1("argc = ", argc); //####
     //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyArraySizeFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 6 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyArraySizeFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty array size()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
     //ODL_S1("launchPath = ", launchPath); //####
     //ODL_I1("argc = ", argc); //####
     //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Double>(123.45));
            if (1 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (1 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyArraySizeFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 7 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyArrayEmptyFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array empty()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
     //ODL_S1("launchPath = ", launchPath); //####
     //ODL_I1("argc = ", argc); //####
     //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            if (stuff->empty())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (stuff->empty())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyArrayEmptyFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 8 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyArrayEmptyFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty array empty()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
     //ODL_S1("launchPath = ", launchPath); //####
     //ODL_I1("argc = ", argc); //####
     //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Double>(123.45));
            if (stuff->empty())
            {
                ODL_LOG("(stuff->empty())"); //####
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyArrayEmptyFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 9 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyArrayClearFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array clear()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
     //ODL_S1("launchPath = ", launchPath); //####
     //ODL_I1("argc = ", argc); //####
     //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            stuff->clear();
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyArrayClearFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyArrayClearFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty array clear()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
     //ODL_S1("launchPath = ", launchPath); //####
     //ODL_I1("argc = ", argc); //####
     //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Double>(123.45));
            stuff->clear();
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyArrayClearFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 11 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyArrayRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            if (stuff->end() == stuff->random())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (stuff->end() == stuff->randomIterator())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyArrayRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 12 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyArrayRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty array random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            result = 0;
            stuff->addValue(std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<String>("charlie"));
            stuff->addValue(std::make_shared<Integer>(42));
            for (size_t ii = 0, count = (2 * stuff->size()); ii < count; ++ii)
            {
                if (stuff->end() == stuff->random())
                {
                    ODL_LOG("(stuff->end() == stuff->random())"); //####
                    result = 1;
                    break;

                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyArrayRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 13 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearingNonEmptyArrayUsingRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // clear non-empty array using random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            result = 0;
            stuff->addValue(std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<String>("charlie"));
            stuff->addValue(std::make_shared<Integer>(42));
            for (size_t ii = 0, count = stuff->size(); ii < count; ++ii)
            {
                Array::iterator walker(stuff->random());

                if (stuff->end() == walker)
                {
                    ODL_LOG("(stuff->end() == walker)"); //####
                    result = 1;
                    break;

                }
                stuff->erase(walker);
            }
            if (0 == result)
            {
                if (! stuff->empty())
                {
                    ODL_LOG("(! stuff->empty())"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestClearingNonEmptyArrayUsingRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 50 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar, kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ', kEndMapChar, kEndOfString
            };

            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 51 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularLogicalMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular logical map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    't', 'r', 'u', 'e', kKeyValueSeparator,
                        '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    't', 'r', 'u', 'e', ' ', kKeyValueSeparator, ' ',
                        '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularLogicalMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 52 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularIntegerMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular integer map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '4', '2', kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '4', '2', ' ', kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Double>(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularIntegerMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 53 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularStringMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular string map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                        kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                        kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("charlie"), std::make_shared<Double>(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularStringMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 54 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallLogicalMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small logical map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    'f', 'a', 'l', 's', 'e', kKeyValueSeparator, '4', '2', ' ',
                    't', 'r', 'u', 'e', kKeyValueSeparator,
                    '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    'f', 'a', 'l', 's', 'e', ' ', kKeyValueSeparator, ' ', '4', '2', ' ',
                    't', 'r', 'u', 'e', ' ', kKeyValueSeparator, ' ',
                    '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(false), std::make_shared<Integer>(42));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallLogicalMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 55 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallIntegerMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small integer map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '1', '2', kKeyValueSeparator, '1', '2', '3', '4', '.', '5', ' ',
                    '1', '7', kKeyValueSeparator, '1', '2', '.', '3', '4', '5', ' ',
                    '4', '2', kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '1', '2', ' ', kKeyValueSeparator, ' ', '1', '2', '3', '4', '.', '5', ' ',
                    '1', '7', ' ', kKeyValueSeparator, ' ', '1', '2', '.', '3', '4', '5', ' ',
                    '4', '2', ' ', kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Integer>(17), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<Integer>(12), std::make_shared<Double>(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallIntegerMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 56 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallStringMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small string map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', kKeyValueSeparator,
                        '1', '2', '3', '4', '.', '5', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', kKeyValueSeparator,
                        '1', '2', '3', '.', '4', '5', ' ',
                    '"', 'l', 'i', 'm', 'a', '"', kKeyValueSeparator,
                        '1', '2', '.', '3', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ', kKeyValueSeparator, ' ',
                        '1', '2', '3', '4', '.', '5', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', ' ', kKeyValueSeparator, ' ',
                        '1', '2', '3', '.', '4', '5', ' ',
                    '"', 'l', 'i', 'm', 'a', '"', ' ', kKeyValueSeparator, ' ',
                        '1', '2', '.', '3', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("delta"), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<String>("lima"), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<String>("charlie"), std::make_shared<Double>(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallStringMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 57 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMapSizeFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map size()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMapSizeFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 58 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMapSizeFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty map size()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            if (1 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (1 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMapSizeFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 59 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMapEmptyFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map empty()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            if (stuff->empty())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (stuff->empty())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMapEmptyFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 60 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMapEmptyFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty map empty()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            if (stuff->empty())
            {
                ODL_LOG("(stuff->empty())"); //####
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMapEmptyFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 61 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMapClearFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map clear()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            stuff->clear();
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMapClearFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 62 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMapClearFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty map clear()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            stuff->clear();
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMapClearFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 63 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMapRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            if (stuff->end() == stuff->random())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (stuff->end() == stuff->randomIterator())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMapRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 64 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptyMapRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty map random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<String>("delta"), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<String>("lima"), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<String>("charlie"), std::make_shared<Double>(1234.5));
            result = 0;
            for (size_t ii = 0, count = (2 * stuff->size()); ii < count; ++ii)
            {
                if (stuff->end() == stuff->random())
                {
                    ODL_LOG("(stuff->end() == stuff->random())"); //####
                    result = 1;
                    break;

                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptyMapRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 65 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearingNonEmptyMapUsingRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // clear non-empty map using random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
     //ODL_S1("launchPath = ", launchPath); //####
     //ODL_I1("argc = ", argc); //####
     //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            result = 0;
            stuff->addValue(std::make_shared<String>("delta"), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<String>("lima"), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<String>("charlie"), std::make_shared<Double>(1234.5));
            for (size_t ii = 0, count = stuff->size(); ii < count; ++ii)
            {
                Map::iterator walker(stuff->random());

                if (stuff->end() == walker)
                {
                    ODL_LOG("(stuff->end() == walker)"); //####
                    result = 1;
                    break;

                }
                stuff->erase(walker);
            }
            if (0 == result)
            {
                if (! stuff->empty())
                {
                    ODL_LOG("(! stuff->empty())"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestClearingNonEmptyMapUsingRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptySetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar, kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ', kEndSetChar, kEndOfString
            };

            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptySetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularLogicalSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular logical set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    't', 'r', 'u', 'e',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    't', 'r', 'u', 'e', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularLogicalSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularIntegerSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular integer set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    '4', '2',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    '4', '2', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularIntegerSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 103 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularStringSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular string set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("charlie"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularStringSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 104 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallLogicalSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small logical set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    'f', 'a', 'l', 's', 'e', ' ',
                    't', 'r', 'u', 'e',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    'f', 'a', 'l', 's', 'e', ' ',
                    't', 'r', 'u', 'e', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<Logical>(false));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<Logical>(false));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallLogicalSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 105 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallIntegerSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small integer set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    '1', '2', ' ',
                    '1', '7', ' ',
                    '4', '2', ' ',
                    '1', '2', '3',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    '1', '2', ' ',
                    '1', '7', ' ',
                    '4', '2', ' ',
                    '1', '2', '3', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(123));
            stuff->addValue(std::make_shared<Integer>(42));
            stuff->addValue(std::make_shared<Integer>(17));
            stuff->addValue(std::make_shared<Integer>(12));
            stuff->addValue(std::make_shared<Integer>(123));
            stuff->addValue(std::make_shared<Integer>(42));
            stuff->addValue(std::make_shared<Integer>(17));
            stuff->addValue(std::make_shared<Integer>(12));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallIntegerSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 106 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallStringSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small string set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    '"', 'a', 'l', 'p', 'h', 'a', '"', ' ',
                    '"', 'b', 'e', 't', 'a', '"', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', ' ',
                    '"', 'g', 'a', 'm', 'm', 'a', '"',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    '"', 'a', 'l', 'p', 'h', 'a', '"', ' ',
                    '"', 'b', 'e', 't', 'a', '"', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', ' ',
                    '"', 'g', 'a', 'm', 'm', 'a', '"', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("gamma"));
            stuff->addValue(std::make_shared<String>("alpha"));
            stuff->addValue(std::make_shared<String>("delta"));
            stuff->addValue(std::make_shared<String>("beta"));
            stuff->addValue(std::make_shared<String>("gamma"));
            stuff->addValue(std::make_shared<String>("alpha"));
            stuff->addValue(std::make_shared<String>("delta"));
            stuff->addValue(std::make_shared<String>("beta"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallStringSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 107 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptySetSizeFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set size()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptySetSizeFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 108 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptySetSizeFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty set size()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Logical>(true));
            if (1 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptySetSizeFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 109 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptySetEmptyFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set empty()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            if (stuff->empty())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (stuff->empty())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptySetEmptyFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptySetEmptyFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty set empty()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Logical>(true));
            if (stuff->empty())
            {
                ODL_LOG("(stuff->empty())"); //####
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptySetEmptyFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptySetClearFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set clear()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            stuff->clear();
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptySetClearFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptySetClearFunction
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty set clear()
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->clear();
            if (0 == stuff->size())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->size())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptySetClearFunction

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptySetRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            if (stuff->end() == stuff->random())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (stuff->end() == stuff->randomIterator())"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptySetRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 114 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNonEmptySetRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // non-empty set random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            stuff->addValue(std::make_shared<String>("gamma"));
            stuff->addValue(std::make_shared<String>("alpha"));
            stuff->addValue(std::make_shared<String>("delta"));
            stuff->addValue(std::make_shared<String>("beta"));
            stuff->addValue(std::make_shared<String>("epsilon"));
            result = 0;
            for (size_t ii = 0, count = (2 * stuff->size()); ii < count; ++ii)
            {
                if (stuff->end() == stuff->random())
                {
                    ODL_LOG("(stuff->end() == stuff->random())"); //####
                    result = 1;
                    break;

                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestNonEmptySetRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 115 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearingNonEmptySetUsingRandomIterator
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // clear non-empty set using random iterator
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            result = 0;
            stuff->addValue(std::make_shared<String>("gamma"));
            stuff->addValue(std::make_shared<String>("alpha"));
            stuff->addValue(std::make_shared<String>("delta"));
            stuff->addValue(std::make_shared<String>("beta"));
            stuff->addValue(std::make_shared<String>("epsilon"));
            for (size_t ii = 0, count = stuff->size(); ii < count; ++ii)
            {
                Set::iterator walker(stuff->random());

                if (stuff->end() == walker)
                {
                    ODL_LOG("(stuff->end() == walker)"); //####
                    result = 1;
                    break;

                }
                stuff->erase(walker);
            }
            if (0 == result)
            {
                if (! stuff->empty())
                {
                    ODL_LOG("(! stuff->empty())"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestClearingNonEmptySetUsingRandomIterator

#if defined(__APPLE__)
# pragma mark *** Test Case 150 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayWithArrayValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                    kStartArrayChar, kEndArrayChar,
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                    kStartArrayChar, ' ', kEndArrayChar, ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Array>());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayWithArrayValue

#if defined(__APPLE__)
# pragma mark *** Test Case 151 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayWithMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                    kStartMapChar, kEndMapChar,
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                    kStartMapChar, ' ', kEndMapChar, ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Map>());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayWithMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 152 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayWithSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                    kStartSetChar, kEndSetChar,
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                    kStartSetChar, ' ', kEndSetChar, ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Set>());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayWithSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 153 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMapWithArrayValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // map with array
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '4', '2', kKeyValueSeparator,
                        kStartArrayChar, kEndArrayChar,
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '4', '2', ' ', kKeyValueSeparator, ' ',
                        kStartArrayChar, ' ', kEndArrayChar, ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Array>());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMapWithArrayValue

#if defined(__APPLE__)
# pragma mark *** Test Case 154 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMapWithMapValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // map with map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '4', '2', kKeyValueSeparator,
                        kStartMapChar, kEndMapChar,
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '4', '2', ' ', kKeyValueSeparator, ' ',
                        kStartMapChar, ' ', kEndMapChar, ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Map>());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMapWithMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 155 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMapWithSetValue
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // map with set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '4', '2', kKeyValueSeparator,
                        kStartSetChar, kEndSetChar,
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '4', '2', ' ', kKeyValueSeparator, ' ',
                        kStartSetChar, ' ', kEndSetChar, ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Set>());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMapWithSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 200 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalMapValueWithIncompatibleKeys
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical map with incompatible keys
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    't', 'r', 'u', 'e', kKeyValueSeparator,
                        '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    't', 'r', 'u', 'e', ' ', kKeyValueSeparator, ' ',
                        '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<Double>(19.77), std::make_shared<Double>(1.2345));
            stuff->addValue(std::make_shared<String>("zebra"), std::make_shared<Double>(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalMapValueWithIncompatibleKeys

#if defined(__APPLE__)
# pragma mark *** Test Case 201 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerMapValueWithIncompatibleKeys
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer map with incompatible keys
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '4', '2', kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '4', '2', ' ', kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<Double>(19.77), std::make_shared<Double>(1.2345));
            stuff->addValue(std::make_shared<String>("zebra"), std::make_shared<Double>(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestIntegerMapValueWithIncompatibleKeys

#if defined(__APPLE__)
# pragma mark *** Test Case 202 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringMapValueWithIncompatibleKeys
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // string map with incompatible keys
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                    kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                    kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("charlie"), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<Double>(19.77), std::make_shared<Double>(1.2345));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringMapValueWithIncompatibleKeys

#if defined(__APPLE__)
# pragma mark *** Test Case 203 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalSetValueWithIncompatibleKeys
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical set with incompatible keys
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    't', 'r', 'u', 'e',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    't', 'r', 'u', 'e', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<Integer>(42));
            stuff->addValue(std::make_shared<Double>(19.77));
            stuff->addValue(std::make_shared<String>("zebra"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestLogicalSetValueWithIncompatibleKeys

#if defined(__APPLE__)
# pragma mark *** Test Case 204 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerSetValueWithIncompatibleKeys
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer set with incompatible keys
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    '4', '2',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    '4', '2', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<Double>(19.77));
            stuff->addValue(std::make_shared<String>("zebra"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestIntegerSetValueWithIncompatibleKeys

#if defined(__APPLE__)
# pragma mark *** Test Case 205 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringSetValueWithIncompatibleKeys
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // string set with incompatible keys
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartSetChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                kEndSetChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartSetChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                kEndSetChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("charlie"));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<Integer>(42));
            stuff->addValue(std::make_shared<Double>(19.77));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringSetValueWithIncompatibleKeys

#if defined(__APPLE__)
# pragma mark *** Test Case 250 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidArrayCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // valid array compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testLogicals
        {
            bool                _testValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testLogicals

        Array               stuff;
        static testLogicals testSet1l[]
        {
            { false,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { true,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(true) } // ==
        };
        const size_t        numTestValues1l{A_SIZE(testSet1l)};
        static testLogicals testSet1r[]
        {
            { false,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { true,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(true) } // ==
        };
        const size_t        numTestValues1r{A_SIZE(testSet1r)};

        stuff.addValue(std::make_shared<Logical>(true));
        stuff.addValue(std::make_shared<Logical>(true));
        stuff.addValue(std::make_shared<Logical>(true));
        for (size_t ii = 0; /*(0 == result) &&*/ (numTestValues1l > ii); ++ii)
        {
            Logical aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThan != aValue.lessThan(stuff))
            {
                ODL_LOG("(testSet1l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                result = 1;
            }
            //if (0 == result)
            {
                if (testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                    result = 1;
                }
            }
            //if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            //if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            //if (0 == result)
            {
                if (testSet1l[ii]._equalTo != aValue.equalTo(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            Logical aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThan != stuff.lessThan(aValue))
            {
                ODL_LOG("(testSet1r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalTo != stuff.equalTo(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                    result = 1;
                }
            }
        }
        if (0 == result)
        {
            static testLogicals testSet2l[]
            {
                { false,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(true) }, // ==
                { true,
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues2l{A_SIZE(testSet2l)};
            static testLogicals testSet2r[]
            {
                { false,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(true) }, // ==
                { true,
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues2r{A_SIZE(testSet2r)};

            stuff.clear();
            stuff.addValue(std::make_shared<Logical>(false));
            stuff.addValue(std::make_shared<Logical>(false));
            stuff.addValue(std::make_shared<Logical>(false));
            for (size_t ii = 0; (0 == result) && (numTestValues2l > ii); ++ii)
            {
                Logical aValue(testSet2l[ii]._testValue);

                if (testSet2l[ii]._lessThan != aValue.lessThan(stuff))
                {
                    ODL_LOG("(testSet2l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThan != aValue.greaterThan(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._equalTo != aValue.equalTo(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues2r > ii); ++ii)
            {
                Logical aValue(testSet2r[ii]._testValue);

                if (testSet2r[ii]._lessThan != stuff.lessThan(aValue))
                {
                    ODL_LOG("(testSet2r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThan != stuff.greaterThan(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._equalTo != stuff.equalTo(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                        result = 1;
                    }
                }
            }
        }
        if (0 == result)
        {
            struct testNumbers
            {
                double              _testValue;
                ComparisonStatus    _lessThan;
                ComparisonStatus    _greaterThan;
                ComparisonStatus    _lessThanOrEqual;
                ComparisonStatus    _greaterThanOrEqual;
                ComparisonStatus    _equalTo;
            }; // testNumbers

            static testNumbers  testSet3l[]
            {
                { -300,
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { -200,
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { -100,
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { -50,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { -25,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 0,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 25,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 50,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 100,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 200,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) }, // ==
                { 300,
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues3l{A_SIZE(testSet3l)};
            static testNumbers  testSet3r[]
            {
                { -300,
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) }, // ==
                { -200,
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) }, // ==
                { -100,
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) }, // ==
                { -50,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { -25,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 0,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 25,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 50,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 100,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 200,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { 300,
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues3r{A_SIZE(testSet3r)};

            stuff.clear();
            stuff.addValue(std::make_shared<Double>(123.45));
            stuff.addValue(std::make_shared<Double>(200.0));
            stuff.addValue(std::make_shared<Double>(-25.0));
            stuff.addValue(std::make_shared<Double>(-60.0));
            stuff.addValue(std::make_shared<Double>(0.0));
            for (size_t ii = 0; (0 == result) && (numTestValues3l > ii); ++ii)
            {
                Double  aValue(testSet3l[ii]._testValue);

                if (testSet3l[ii]._lessThan != aValue.lessThan(stuff))
                {
                    ODL_LOG("(testSet3l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._greaterThan != aValue.greaterThan(stuff))
                    {
                        ODL_LOG("(testSet3l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet3l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet3l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._equalTo != aValue.equalTo(stuff))
                    {
                        ODL_LOG("(testSet3l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues3r > ii); ++ii)
            {
                Double  aValue(testSet3r[ii]._testValue);

                if (testSet3r[ii]._lessThan != stuff.lessThan(aValue))
                {
                    ODL_LOG("(testSet3r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._greaterThan != stuff.greaterThan(aValue))
                    {
                        ODL_LOG("(testSet3r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet3r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet3r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._equalTo != stuff.equalTo(aValue))
                    {
                        ODL_LOG("(testSet3r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                        result = 1;
                    }
                }
            }
        }
        if (0 == result)
        {
            struct testStrings
            {
                CPtr(char)        _testValue;
                ComparisonStatus    _lessThan;
                ComparisonStatus    _greaterThan;
                ComparisonStatus    _lessThanOrEqual;
                ComparisonStatus    _greaterThanOrEqual;
                ComparisonStatus    _equalTo;
            }; // testStrings

            static testStrings  testSet4l[]
            {
                { "aaa",
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { "abc",
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { "def",
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { "ghi",
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) }, // ==
                { "zzz",
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues4l{A_SIZE(testSet4l)};
            static testStrings  testSet4r[]
            {
                { "aaa",
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) }, // ==
                { "abc",
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) }, // ==
                { "def",
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { "ghi",
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) }, // ==
                { "zzz",
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues4r{A_SIZE(testSet4r)};

            stuff.clear();
            stuff.addValue(std::make_shared<String>("abc"));
            stuff.addValue(std::make_shared<String>("def"));
            stuff.addValue(std::make_shared<String>("ghi"));
            for (size_t ii = 0; (0 == result) && (numTestValues4l > ii); ++ii)
            {
                String  aValue(testSet4l[ii]._testValue);

                if (testSet4l[ii]._lessThan != aValue.lessThan(stuff))
                {
                    ODL_LOG("(testSet4l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._greaterThan != aValue.greaterThan(stuff))
                    {
                        ODL_LOG("(testSet4l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet4l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet4l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._equalTo != aValue.equalTo(stuff))
                    {
                        ODL_LOG("(testSet4l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues4r > ii); ++ii)
            {
                String  aValue(testSet4r[ii]._testValue);

                if (testSet4r[ii]._lessThan != stuff.lessThan(aValue))
                {
                    ODL_LOG("(testSet4r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._greaterThan != stuff.greaterThan(aValue))
                    {
                        ODL_LOG("(testSet4r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet4r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet4r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._equalTo != stuff.equalTo(aValue))
                    {
                        ODL_LOG("(testSet4r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                        result = 1;
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
} // doTestValidArrayCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 251 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidLogicalMapCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // valid logical map compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testLogicals
        {
            bool                _testValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testLogicals

        static testLogicals testSet1l[]
        {
            { false,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { true,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(true) } // ==
        };
        const size_t        numTestValues1l{A_SIZE(testSet1l)};
        static testLogicals testSet1r[]
        {
            { false,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { true,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(true) } // ==
        };
        const size_t        numTestValues1r{A_SIZE(testSet1r)};
        Map                 stuff;

        stuff.addValue(std::make_shared<Logical>(true), std::make_shared<String>("abc"));
        stuff.addValue(std::make_shared<Logical>(true), std::make_shared<String>("def"));
        stuff.addValue(std::make_shared<Logical>(true), std::make_shared<String>("ghi"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            Logical aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThan != aValue.lessThan(stuff))
            {
                ODL_LOG("(testSet1l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalTo != aValue.equalTo(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            Logical aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThan != stuff.lessThan(aValue))
            {
                ODL_LOG("(testSet1r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalTo != stuff.equalTo(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                    result = 1;
                }
            }
        }
        if (0 == result)
        {
            static testLogicals testSet2l[]
            {
                { false,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(true) }, // ==
                { true,
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues2l{A_SIZE(testSet2l)};
            static testLogicals testSet2r[]
            {
                { false,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(true) }, // ==
                { true,
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues2r{A_SIZE(testSet2r)};

            stuff.clear();
            stuff.addValue(std::make_shared<Logical>(false), std::make_shared<String>("abc"));
            stuff.addValue(std::make_shared<Logical>(false), std::make_shared<String>("def"));
            stuff.addValue(std::make_shared<Logical>(false), std::make_shared<String>("ghi"));
            for (size_t ii = 0; (0 == result) && (numTestValues2l > ii); ++ii)
            {
                Logical aValue(testSet2l[ii]._testValue);

                if (testSet2l[ii]._lessThan != aValue.lessThan(stuff))
                {
                    ODL_LOG("(testSet2l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThan != aValue.greaterThan(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._equalTo != aValue.equalTo(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues2r > ii); ++ii)
            {
                Logical aValue(testSet2r[ii]._testValue);

                if (testSet2r[ii]._lessThan != stuff.lessThan(aValue))
                {
                    ODL_LOG("(testSet2r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThan != stuff.greaterThan(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._equalTo != stuff.equalTo(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                        result = 1;
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
} // doTestValidLogicalMapCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 252 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidIntegerMapCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // valid integer map compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testNumbers
        {
            int64_t             _testValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testNumbers

        static testNumbers  testSet1l[]
        {
            { -300,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -200,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -100,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 0,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 100,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 200,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { 300,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1l{A_SIZE(testSet1l)};
        static testNumbers  testSet1r[]
        {
            { -300,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { -200,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { -100,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { -50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 0,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 100,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 200,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 300,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1r{A_SIZE(testSet1r)};
        Map                 stuff;

        stuff.addValue(std::make_shared<Integer>(123), std::make_shared<String>("abc"));
        stuff.addValue(std::make_shared<Integer>(200), std::make_shared<String>("def"));
        stuff.addValue(std::make_shared<Integer>(-25), std::make_shared<String>("ghi"));
        stuff.addValue(std::make_shared<Integer>(-60), std::make_shared<String>("jkl"));
        stuff.addValue(std::make_shared<Integer>(0), std::make_shared<String>("mno"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            Integer aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThan != aValue.lessThan(stuff))
            {
                ODL_LOG("(testSet1l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalTo != aValue.equalTo(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            Integer aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThan != stuff.lessThan(aValue))
            {
                ODL_LOG("(testSet1r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalTo != stuff.equalTo(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._equalTo != stuff.equalTo(aValue))"); //####
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
} // doTestValidIntegerMapCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 253 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidStringMapCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // valid string map compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testStrings
        {
            CPtr(char)          _testValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testStrings

        static testStrings  testSet1l[]
        {
            { "aaa",
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "abc",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "def",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "ghi",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { "zzz",
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1l{A_SIZE(testSet1l)};
        static testStrings  testSet1r[]
        {
            { "aaa",
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { "abc",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { "def",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "ghi",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "zzz",
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1r{A_SIZE(testSet1r)};
        Map                 stuff;

        stuff.addValue(std::make_shared<String>("abc"), std::make_shared<String>("123"));
        stuff.addValue(std::make_shared<String>("def"), std::make_shared<String>("456"));
        stuff.addValue(std::make_shared<String>("ghi"), std::make_shared<String>("789"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            String  aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThan != aValue.lessThan(stuff))
            {
                ODL_LOG("(testSet1l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalTo != aValue.equalTo(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            String  aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThan != stuff.lessThan(aValue))
            {
                ODL_LOG("(testSet1r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalTo != stuff.equalTo(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._equalTo != stuff.equalTo(aValue))"); //####
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
} // doTestValidStringMapCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 254 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidLogicalSetCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // valid logical set compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testLogicals
        {
            bool                _testValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testLogicals

        static testLogicals testSet1l[]
        {
            { false,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { true,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(true) } // ==
        };
        const size_t        numTestValues1l{A_SIZE(testSet1l)};
        static testLogicals testSet1r[]
        {
            { false,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { true,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(true) } // ==
        };
        const size_t        numTestValues1r{A_SIZE(testSet1r)};
        Set                 stuff;

        stuff.addValue(std::make_shared<Logical>(true));
        stuff.addValue(std::make_shared<Logical>(true));
        stuff.addValue(std::make_shared<Logical>(true));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            Logical aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThan != aValue.lessThan(stuff))
            {
                ODL_LOG("(testSet1l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalTo != aValue.equalTo(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            Logical aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThan != stuff.lessThan(aValue))
            {
                ODL_LOG("(testSet1r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalTo != stuff.equalTo(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                    result = 1;
                }
            }
        }
        if (0 == result)
        {
            static testLogicals testSet2l[]
            {
                { false,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(true) }, // ==
                { true,
                    ComparisonStatus(false), // <
                    ComparisonStatus(true), // >
                    ComparisonStatus(false), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues2l{A_SIZE(testSet2l)};
            static testLogicals testSet2r[]
            {
                { false,
                    ComparisonStatus(false), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(true), // >=
                    ComparisonStatus(true) }, // ==
                { true,
                    ComparisonStatus(true), // <
                    ComparisonStatus(false), // >
                    ComparisonStatus(true), // <=
                    ComparisonStatus(false), // >=
                    ComparisonStatus(false) } // ==
            };
            const size_t        numTestValues2r{A_SIZE(testSet2r)};

            stuff.clear();
            stuff.addValue(std::make_shared<Logical>(false));
            stuff.addValue(std::make_shared<Logical>(false));
            stuff.addValue(std::make_shared<Logical>(false));
            for (size_t ii = 0; (0 == result) && (numTestValues2l > ii); ++ii)
            {
                Logical aValue(testSet2l[ii]._testValue);

                if (testSet2l[ii]._lessThan != aValue.lessThan(stuff))
                {
                    ODL_LOG("(testSet2l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThan != aValue.greaterThan(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._equalTo != aValue.equalTo(stuff))
                    {
                        ODL_LOG("(testSet2l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues2r > ii); ++ii)
            {
                Logical aValue(testSet2r[ii]._testValue);

                if (testSet2r[ii]._lessThan != stuff.lessThan(aValue))
                {
                    ODL_LOG("(testSet2r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThan != stuff.greaterThan(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._equalTo != stuff.equalTo(aValue))
                    {
                        ODL_LOG("(testSet2r[ii]._equalTo != stuff.equalTo(aValue))"); //####
                        result = 1;
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
} // doTestValidLogicalSetCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 255 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidIntegerSetCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // valid integer set compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testNumbers
        {
            int64_t             _testValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testNumbers

        static testNumbers  testSet1l[]
        {
            { -300,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -200,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -100,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 0,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 100,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 200,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { 300,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1l{A_SIZE(testSet1l)};
        static testNumbers  testSet1r[]
        {
            { -300,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { -200,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { -100,
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { -50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { -25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 0,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 25,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 50,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 100,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 200,
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { 300,
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1r{A_SIZE(testSet1r)};
        Set                 stuff;

        stuff.addValue(std::make_shared<Integer>(123));
        stuff.addValue(std::make_shared<Integer>(200));
        stuff.addValue(std::make_shared<Integer>(-25));
        stuff.addValue(std::make_shared<Integer>(-60));
        stuff.addValue(std::make_shared<Integer>(0));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            Integer aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThan != aValue.lessThan(stuff))
            {
                ODL_LOG("(testSet1l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalTo != aValue.equalTo(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            Integer aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThan != stuff.lessThan(aValue))
            {
                ODL_LOG("(testSet1r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalTo != stuff.equalTo(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._equalTo != stuff.equalTo(aValue))"); //####
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
} // doTestValidIntegerSetCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 256 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidStringSetCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // valid string set compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testStrings
        {
            CPtr(char)          _testValue;
            ComparisonStatus    _lessThan;
            ComparisonStatus    _greaterThan;
            ComparisonStatus    _lessThanOrEqual;
            ComparisonStatus    _greaterThanOrEqual;
            ComparisonStatus    _equalTo;
        }; // testStrings

        static testStrings  testSet1l[]
        {
            { "aaa",
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "abc",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "def",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "ghi",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { "zzz",
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1l{A_SIZE(testSet1l)};
        static testStrings  testSet1r[]
        {
            { "aaa",
                ComparisonStatus(false), // <
                ComparisonStatus(true), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { "abc",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(true), // >=
                ComparisonStatus(false) }, // ==
            { "def",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(false), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "ghi",
                ComparisonStatus(false), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) }, // ==
            { "zzz",
                ComparisonStatus(true), // <
                ComparisonStatus(false), // >
                ComparisonStatus(true), // <=
                ComparisonStatus(false), // >=
                ComparisonStatus(false) } // ==
        };
        const size_t        numTestValues1r{A_SIZE(testSet1r)};
        Set                 stuff;

        stuff.addValue(std::make_shared<String>("abc"));
        stuff.addValue(std::make_shared<String>("def"));
        stuff.addValue(std::make_shared<String>("ghi"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            String  aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThan != aValue.lessThan(stuff))
            {
                ODL_LOG("(testSet1l[ii]._lessThan != aValue.lessThan(stuff))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThan != aValue.greaterThan(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqual != aValue.lessThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqual != aValue.greaterThanOrEqual(stuff))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalTo != aValue.equalTo(stuff))
                {
                    ODL_LOG("(testSet1l[ii]._equalTo != aValue.equalTo(stuff))"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            String  aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThan != stuff.lessThan(aValue))
            {
                ODL_LOG("(testSet1r[ii]._lessThan != stuff.lessThan(aValue))"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThan != stuff.greaterThan(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqual != stuff.lessThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqual != stuff.greaterThanOrEqual(aValue))"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalTo != stuff.equalTo(aValue))
                {
                    ODL_LOG("(testSet1r[ii]._equalTo != stuff.equalTo(aValue))"); //####
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
} // doTestValidStringSetCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 257 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidArrayCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // invalid array compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        ComparisonStatus    status;
        Array               leftValue;
        Logical             rightValue1;
        Double              rightValue2;
        String              rightValue3;
        Blob                rightValue4;
        Array               rightValue5;
        Map                 rightValue6;
        Set                 rightValue7;
        Integer             rightValue8;
        Ptr(Value)          rightValues[]
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4,
            &rightValue5, &rightValue6, &rightValue7, &rightValue8
        };
        const size_t    numRightValues{A_SIZE(rightValues)};

        leftValue.addValue(std::make_shared<Logical>());
        leftValue.addValue(std::make_shared<Number>());
        leftValue.addValue(std::make_shared<String>());
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue = *rightValues[ii];

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
} // doTestInvalidArrayCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 258 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidLogicalMapCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // invalid logical map compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        ComparisonStatus    status;
        Map                 leftValue;
        Integer             rightValue1;
        String              rightValue2;
        Blob                rightValue3;
        Array               rightValue4;
        Map                 rightValue5;
        Set                 rightValue6;
        Double              rightValue7;
        Ptr(Value)          rightValues[]
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t    numRightValues{A_SIZE(rightValues)};

        leftValue.addValue(std::make_shared<Logical>(false), std::make_shared<String>("false"));
        leftValue.addValue(std::make_shared<Logical>(true), std::make_shared<String>("true"));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue = *rightValues[ii];

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
} // doTestInvalidLogicalMapCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 259 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidIntegerMapCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // invalid integer map compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        ComparisonStatus    status;
        Map                 leftValue;
        Logical             rightValue1;
        String              rightValue2;
        Blob                rightValue3;
        Array               rightValue4;
        Map                 rightValue5;
        Set                 rightValue6;
        Ptr(Value)          rightValues[]
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6
        };
        const size_t    numRightValues{A_SIZE(rightValues)};

        leftValue.addValue(std::make_shared<Integer>(42), std::make_shared<Double>(123.45));
        leftValue.addValue(std::make_shared<Integer>(17), std::make_shared<Double>(12.345));
        leftValue.addValue(std::make_shared<Integer>(12), std::make_shared<Double>(1234.5));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue = *rightValues[ii];

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
} // doTestInvalidIntegerMapCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 260 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidStringMapCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // invalid string map compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        ComparisonStatus    status;
        Map                 leftValue;
        Double              rightValue1;
        Logical             rightValue2;
        Blob                rightValue3;
        Array               rightValue4;
        Map                 rightValue5;
        Set                 rightValue6;
        Integer             rightValue7;
        Ptr(Value)          rightValues[]
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t    numRightValues{A_SIZE(rightValues)};

        leftValue.addValue(std::make_shared<String>("abc"), std::make_shared<String>("123"));
        leftValue.addValue(std::make_shared<String>("def"), std::make_shared<String>("456"));
        leftValue.addValue(std::make_shared<String>("ghi"), std::make_shared<String>("789"));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue = *rightValues[ii];

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
} // doTestInvalidStringMapCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 261 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidLogicalSetCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // invalid logical set compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        ComparisonStatus    status;
        Set                 leftValue;
        Double              rightValue1;
        String              rightValue2;
        Blob                rightValue3;
        Array               rightValue4;
        Map                 rightValue5;
        Set                 rightValue6;
        Integer             rightValue7;
        Ptr(Value)          rightValues[]
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t    numRightValues{A_SIZE(rightValues)};

        leftValue.addValue(std::make_shared<Logical>(false));
        leftValue.addValue(std::make_shared<Logical>(true));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue = *rightValues[ii];

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
} // doTestInvalidLogicalSetCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 262 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidIntegerSetCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // invalid integer set compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        ComparisonStatus    status;
        Set                 leftValue;
        Logical             rightValue1;
        String              rightValue2;
        Blob                rightValue3;
        Array               rightValue4;
        Map                 rightValue5;
        Set                 rightValue6;
        Ptr(Value)          rightValues[]
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6
        };
        const size_t    numRightValues{A_SIZE(rightValues)};

        leftValue.addValue(std::make_shared<Integer>(42));
        leftValue.addValue(std::make_shared<Integer>(17));
        leftValue.addValue(std::make_shared<Integer>(12));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue = *rightValues[ii];

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
} // doTestInvalidIntegerSetCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 263 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidStringSetCompares
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // invalid string set compares
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        ComparisonStatus    status;
        Set                 leftValue;
        Double              rightValue1;
        Logical             rightValue2;
        Blob                rightValue3;
        Array               rightValue4;
        Map                 rightValue5;
        Set                 rightValue6;
        Integer             rightValue7;
        Ptr(Value)          rightValues[]
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t    numRightValues{A_SIZE(rightValues)};

        leftValue.addValue(std::make_shared<String>("abc"));
        leftValue.addValue(std::make_shared<String>("def"));
        leftValue.addValue(std::make_shared<String>("ghi"));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value & aRightValue = *rightValues[ii];

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
} // doTestInvalidStringSetCompares

#if defined(__APPLE__)
# pragma mark *** Test Case 300 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayIndices
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array indices
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        Array   stuff;
        SpValue aBoolValue;
        SpValue aNumberValue;
        SpValue aStringValue;

        if (0 != stuff.size())
        {
            ODL_LOG("(0 != stuff.size())"); //####
            result = 1;
        }
        if (0 == result)
        {
            if (nullptr != stuff.at(0))
            {
                ODL_LOG("(nullptr != aValue)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if (nullptr != stuff.at(1))
            {
                ODL_LOG("nullptr != aValue"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            aBoolValue.reset(new Logical);
            stuff.addValue(aBoolValue);
            if (1 != stuff.size())
            {
                ODL_LOG("(1 != stuff.size())"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if (stuff.at(0) != aBoolValue)
            {
                ODL_LOG("(stuff.at(0) != aBoolValue)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            aNumberValue.reset(new Number);
            stuff.addValue(aNumberValue);
            if (2 != stuff.size())
            {
                ODL_LOG("(2 != stuff.size())"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if ((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue))
            {
                ODL_LOG("((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue))"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            aStringValue.reset(new String);
            stuff.addValue(aStringValue);
            if (3 != stuff.size())
            {
                ODL_LOG("(3 != stuff.size())"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if ((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue) || (stuff.at(2) != aStringValue))
            {
                ODL_LOG("((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue) || " //####
                        "(stuff.at(2) != aStringValue))"); //####
                result = 1;
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
} // doTestArrayIndices

#if defined(__APPLE__)
# pragma mark *** Test Case 301 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalMapSearches
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical map searches
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        Map             stuff;
        Map::iterator   iter;
        auto            falseString{std::make_shared<String>("false")};
        SpString        trueString;

        stuff.addValue(std::make_shared<Logical>(false), falseString);
        iter = stuff.find(std::make_shared<Logical>(true));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>(false));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != falseString)
            {
                ODL_LOG("(iter->second != falseString)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>(true));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            trueString.reset(new String("true"));
            stuff.addValue(std::make_shared<Logical>(true), trueString);
            iter = stuff.find(std::make_shared<Logical>(true));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != trueString)
            {
                ODL_LOG("(iter->second != trueString)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestLogicalMapSearches

#if defined(__APPLE__)
# pragma mark *** Test Case 302 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerMapSearches
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer map searches
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        Map             stuff;
        Map::iterator   iter;
        auto            string17{std::make_shared<String>("17")};
        SpString        string12;

        stuff.addValue(std::make_shared<Integer>(17), string17);
        iter = stuff.find(std::make_shared<Integer>(12));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>(17));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != string17)
            {
                ODL_LOG("(iter->second != string17)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>(12));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            string12.reset(new String("12"));
            stuff.addValue(std::make_shared<Integer>(12), string12);
            iter = stuff.find(std::make_shared<Integer>(12));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != string12)
            {
                ODL_LOG("(iter->second != string12)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestIntegerMapSearches

#if defined(__APPLE__)
# pragma mark *** Test Case 303 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringMapSearches
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // string map searches
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        Map             stuff;
        Map::iterator   iter;
        auto            stringOneSeven{std::make_shared<String>("17")};
        SpString        stringOneTwo;

        stuff.addValue(std::make_shared<String>("abc"), stringOneSeven);
        iter = stuff.find(std::make_shared<String>("def"));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>("abc"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != stringOneSeven)
            {
                ODL_LOG("(iter->second != stringOneSeven)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>("def"));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stringOneTwo.reset(new String("12"));
            stuff.addValue(std::make_shared<String>("def"), stringOneTwo);
            iter = stuff.find(std::make_shared<String>("def"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != stringOneTwo)
            {
                ODL_LOG("(iter->second != stringOneTwo)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestStringMapSearches

#if defined(__APPLE__)
# pragma mark *** Test Case 304 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLogicalSetSearches
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // logical set searches
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        Set             stuff;
        Set::iterator   iter;

        stuff.addValue(std::make_shared<Logical>(false));
        iter = stuff.find(std::make_shared<Logical>(true));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>(false));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>(true));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stuff.addValue(std::make_shared<Logical>(true));
            iter = stuff.find(std::make_shared<Logical>(true));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestLogicalSetSearches

#if defined(__APPLE__)
# pragma mark *** Test Case 305 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerSetSearches
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // integer set searches
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        Set             stuff;
        Set::iterator   iter;

        stuff.addValue(std::make_shared<Integer>(17));
        iter = stuff.find(std::make_shared<Integer>(12));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>(17));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>(12));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stuff.addValue(std::make_shared<Integer>(12));
            iter = stuff.find(std::make_shared<Integer>(12));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestIntegerSetSearches

#if defined(__APPLE__)
# pragma mark *** Test Case 306 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringSetSearches
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // string set searches
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        Set             stuff;
        Set::iterator   iter;

        stuff.addValue(std::make_shared<String>("abc"));
        iter = stuff.find(std::make_shared<String>("def"));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>("abc"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<String>("def"));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stuff.addValue(std::make_shared<String>("def"));
            iter = stuff.find(std::make_shared<String>("def"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Logical>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(std::make_shared<Integer>());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestStringSetSearches

#if defined(__APPLE__)
# pragma mark *** Test Case 320 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyArrayValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar, kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ', kEndArrayChar, kEndOfString
            };

            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyArrayValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 321 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularArrayValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                '1', '2', '3', '.', '4', '5',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                '1', '2', '3', '.', '4', '5', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Double>(123.45));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularArrayValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 322 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallArrayValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                '1', '2', '3', '.', '4', '5', ',',
                't', 'r', 'u', 'e', ',',
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ',',
                '4', '2',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                '1', '2', '3', '.', '4', '5', ',', ' ',
                't', 'r', 'u', 'e', ',', ' ',
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ',', ' ',
                '4', '2', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<String>("charlie"));
            stuff->addValue(std::make_shared<Integer>(42));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallArrayValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 323 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBigArrayValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // big array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            UpAuint8_t  bigBlob{new uint8_t[kBigTestSize]};

            if (nullptr != bigBlob)
            {
                std::string expectedSquishedString;
                std::string expectedString;
                char        numBuff[10];

                expectedSquishedString += kStartArrayChar;
                expectedString += kStartArrayChar;
                expectedString += ' ';
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    Ptr(uint8_t)    addr = bigBlob.get();
                    uint8_t         aByte = StaticCast(uint8_t, ReinterpretCast(intptr_t, addr) ^ ii);

                    if (0 != ii)
                    {
                        expectedString += ", ";
                        expectedSquishedString += ',';
                    }
                    bigBlob[ii] = aByte;
                    stuff->addValue(std::make_shared<Integer>(aByte));
                    snprintf(numBuff, sizeof(numBuff), "%d", aByte);
                    expectedString += numBuff;
                    expectedSquishedString += numBuff;
                }
                expectedString += ' ';
                expectedSquishedString += kEndArrayChar;
                expectedString += kEndArrayChar;
                if (0 == compareValueWithStringAsJSON(*stuff, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
                }
                if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                            "expectedSquishedString))"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestBigArrayValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 340 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar, kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ', kEndMapChar, kEndOfString
            };

            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptyMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 341 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularLogicalMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular logical map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', 't', 'r', 'u', 'e', '"', kKeyValueSeparator,
                '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', 't', 'r', 'u', 'e', '"', ' ', kKeyValueSeparator, ' ',
                '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularLogicalMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 342 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularIntegerMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular integer map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', '4', '2', '"', kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', '4', '2', '"', ' ', kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Double>(123.45));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularIntegerMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 343 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularStringMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular string map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("charlie"), std::make_shared<Double>(123.45));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularStringMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 344 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallLogicalMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small logical map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', 'f', 'a', 'l', 's', 'e', '"', kKeyValueSeparator, '4', '2', ',',
                '"', 't', 'r', 'u', 'e', '"', kKeyValueSeparator,
                '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', 'f', 'a', 'l', 's', 'e', '"', ' ', kKeyValueSeparator, ' ', '4', '2', ',', ' ',
                '"', 't', 'r', 'u', 'e', '"', ' ', kKeyValueSeparator, ' ',
                '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Logical>(false), std::make_shared<Integer>(42));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallLogicalMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 345 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallIntegerMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small integer map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', '1', '2', '"', kKeyValueSeparator, '1', '2', '3', '4', '.', '5', ',',
                '"', '1', '7', '"', kKeyValueSeparator, '1', '2', '.', '3', '4', '5', ',',
                '"', '4', '2', '"', kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', '1', '2', '"', ' ', kKeyValueSeparator, ' ', '1', '2', '3', '4', '.', '5', ',', ' ',
                '"', '1', '7', '"', ' ', kKeyValueSeparator, ' ', '1', '2', '.', '3', '4', '5', ',', ' ',
                '"', '4', '2', '"', ' ', kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<Integer>(17), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<Integer>(12), std::make_shared<Double>(1234.5));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallIntegerMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 346 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallStringMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small string map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', kKeyValueSeparator,
                '1', '2', '3', '4', '.', '5', ',',
                '"', 'd', 'e', 'l', 't', 'a', '"', kKeyValueSeparator,
                '1', '2', '3', '.', '4', '5', ',',
                '"', 'l', 'i', 'm', 'a', '"', kKeyValueSeparator,
                '1', '2', '.', '3', '4', '5',
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ', kKeyValueSeparator, ' ',
                '1', '2', '3', '4', '.', '5', ',', ' ',
                '"', 'd', 'e', 'l', 't', 'a', '"', ' ', kKeyValueSeparator, ' ',
                '1', '2', '3', '.', '4', '5', ',', ' ',
                '"', 'l', 'i', 'm', 'a', '"', ' ', kKeyValueSeparator, ' ',
                '1', '2', '.', '3', '4', '5', ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("delta"), std::make_shared<Double>(123.45));
            stuff->addValue(std::make_shared<String>("lima"), std::make_shared<Double>(12.345));
            stuff->addValue(std::make_shared<String>("charlie"), std::make_shared<Double>(1234.5));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallStringMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 360 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptySetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // empty set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar, kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ', kEndArrayChar, kEndOfString
            };

            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestEmptySetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 361 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularLogicalSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular logical set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                't', 'r', 'u', 'e',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                't', 'r', 'u', 'e', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularLogicalSetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 362 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularIntegerSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular integer set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                '4', '2',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                '4', '2', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularIntegerSetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 363 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSingularStringSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // singular string set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("charlie"));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSingularStringSetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 364 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallLogicalSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small logical set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                'f', 'a', 'l', 's', 'e', ',',
                't', 'r', 'u', 'e',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                'f', 'a', 'l', 's', 'e', ',', ' ',
                't', 'r', 'u', 'e', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<Logical>(false));
            stuff->addValue(std::make_shared<Logical>(true));
            stuff->addValue(std::make_shared<Logical>(false));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallLogicalSetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 365 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallIntegerSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small integer set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                '1', '2', ',',
                '1', '7', ',',
                '4', '2', ',',
                '1', '2', '3',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                '1', '2', ',', ' ',
                '1', '7', ',', ' ',
                '4', '2', ',', ' ',
                '1', '2', '3', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(123));
            stuff->addValue(std::make_shared<Integer>(42));
            stuff->addValue(std::make_shared<Integer>(17));
            stuff->addValue(std::make_shared<Integer>(12));
            stuff->addValue(std::make_shared<Integer>(123));
            stuff->addValue(std::make_shared<Integer>(42));
            stuff->addValue(std::make_shared<Integer>(17));
            stuff->addValue(std::make_shared<Integer>(12));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallIntegerSetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 366 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSmallStringSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // small string set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Set>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                '"', 'a', 'l', 'p', 'h', 'a', '"', ',',
                '"', 'b', 'e', 't', 'a', '"', ',',
                '"', 'd', 'e', 'l', 't', 'a', '"', ',',
                '"', 'g', 'a', 'm', 'm', 'a', '"',
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                '"', 'a', 'l', 'p', 'h', 'a', '"', ',', ' ',
                '"', 'b', 'e', 't', 'a', '"', ',', ' ',
                '"', 'd', 'e', 'l', 't', 'a', '"', ',', ' ',
                '"', 'g', 'a', 'm', 'm', 'a', '"', ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<String>("gamma"));
            stuff->addValue(std::make_shared<String>("alpha"));
            stuff->addValue(std::make_shared<String>("delta"));
            stuff->addValue(std::make_shared<String>("beta"));
            stuff->addValue(std::make_shared<String>("gamma"));
            stuff->addValue(std::make_shared<String>("alpha"));
            stuff->addValue(std::make_shared<String>("delta"));
            stuff->addValue(std::make_shared<String>("beta"));
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestSmallStringSetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 380 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayWithArrayValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with array value
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                kStartArrayChar, kEndArrayChar,
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                kStartArrayChar, ' ', kEndArrayChar, ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Array>());
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayWithArrayValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 381 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayWithMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                kStartMapChar, kEndMapChar,
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                kStartMapChar, ' ', kEndMapChar, ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Map>());
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayWithMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 382 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestArrayWithSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // array with set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Array>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartArrayChar,
                kStartArrayChar, kEndArrayChar,
                kEndArrayChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartArrayChar, ' ',
                kStartArrayChar, ' ', kEndArrayChar, ' ',
                kEndArrayChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Set>());
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestArrayWithSetValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 383 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMapWithArrayValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // map with array
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', '4', '2', '"', kKeyValueSeparator,
                kStartArrayChar, kEndArrayChar,
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', '4', '2', '"', ' ', kKeyValueSeparator, ' ',
                kStartArrayChar, ' ', kEndArrayChar, ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Array>());
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMapWithArrayValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 384 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMapWithMapValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // map with map
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', '4', '2', '"', kKeyValueSeparator,
                kStartMapChar, kEndMapChar,
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', '4', '2', '"', ' ', kKeyValueSeparator, ' ',
                kStartMapChar, ' ', kEndMapChar, ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Map>());
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMapWithMapValueAsJSON

#if defined(__APPLE__)
# pragma mark *** Test Case 385 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMapWithSetValueAsJSON
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv) // map with set
{
    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        auto    stuff{make_unique<Map>()};

        if (nullptr != stuff)
        {
            static const char   expectedSquishedString[]
            {
                kStartMapChar,
                '"', '4', '2', '"', kKeyValueSeparator,
                kStartArrayChar, kEndArrayChar,
                kEndMapChar, kEndOfString
            };
            static const char   expectedString[]
            {
                kStartMapChar, ' ',
                '"', '4', '2', '"', ' ', kKeyValueSeparator, ' ',
                kStartArrayChar, ' ', kEndArrayChar, ' ',
                kEndMapChar, kEndOfString
            };

            stuff->addValue(std::make_shared<Integer>(42), std::make_shared<Set>());
            if (0 == compareValueWithStringAsJSON(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithStringAsJSON(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedStringAsJSON(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedStringAsJSON(*stuff, " //####
                        "expectedSquishedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nullptr != stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestMapWithSetValue

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
                    case 0 :
                        // Just used to validate the random number seed.
                        result = 0;
                        break;

                    case 1 :
                        result = doTestEmptyArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestSingularArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestSmallArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestBigArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestEmptyArraySizeFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 6 :
                        result = doTestNonEmptyArraySizeFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 7 :
                        result = doTestEmptyArrayEmptyFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 8 :
                        result = doTestNonEmptyArrayEmptyFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 9 :
                        result = doTestEmptyArrayClearFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestNonEmptyArrayClearFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 11 :
                        result = doTestEmptyArrayRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestNonEmptyArrayRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestClearingNonEmptyArrayUsingRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 50 :
                        result = doTestEmptyMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 51 :
                        result = doTestSingularLogicalMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 52 :
                        result = doTestSingularIntegerMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 53 :
                        result = doTestSingularStringMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 54 :
                        result = doTestSmallLogicalMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 55 :
                        result = doTestSmallIntegerMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 56 :
                        result = doTestSmallStringMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 57 :
                        result = doTestEmptyMapSizeFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 58 :
                        result = doTestNonEmptyMapSizeFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 59 :
                        result = doTestEmptyMapEmptyFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 60 :
                        result = doTestNonEmptyMapEmptyFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 61 :
                        result = doTestEmptyMapClearFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 62 :
                        result = doTestNonEmptyMapClearFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 63 :
                        result = doTestEmptyMapRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 64 :
                        result = doTestNonEmptyMapRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 65 :
                        result = doTestClearingNonEmptyMapUsingRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 100 :
                        result = doTestEmptySetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestSingularLogicalSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestSingularIntegerSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 103 :
                        result = doTestSingularStringSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 104 :
                        result = doTestSmallLogicalSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 105 :
                        result = doTestSmallIntegerSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 106 :
                        result = doTestSmallStringSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 107 :
                        result = doTestEmptySetSizeFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 108 :
                        result = doTestNonEmptySetSizeFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 109 :
                        result = doTestEmptySetEmptyFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 110 :
                        result = doTestNonEmptySetEmptyFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 111 :
                        result = doTestEmptySetClearFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 112 :
                        result = doTestNonEmptySetClearFunction(*argv, argc - 1, argv + 2);
                        break;

                    case 113 :
                        result = doTestEmptySetRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 114 :
                        result = doTestNonEmptySetRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 115 :
                        result = doTestClearingNonEmptySetUsingRandomIterator(*argv, argc - 1, argv + 2);
                        break;

                    case 150 :
                        result = doTestArrayWithArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 151 :
                        result = doTestArrayWithMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 152 :
                        result = doTestArrayWithSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 153 :
                        result = doTestMapWithArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 154 :
                        result = doTestMapWithMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 155 :
                        result = doTestMapWithSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 200 :
                        result = doTestLogicalMapValueWithIncompatibleKeys(*argv, argc - 1, argv + 2);
                        break;

                    case 201 :
                        result = doTestIntegerMapValueWithIncompatibleKeys(*argv, argc - 1, argv + 2);
                        break;

                    case 202 :
                        result = doTestStringMapValueWithIncompatibleKeys(*argv, argc - 1, argv + 2);
                        break;

                    case 203 :
                        result = doTestLogicalSetValueWithIncompatibleKeys(*argv, argc - 1, argv + 2);
                        break;

                    case 204 :
                        result = doTestIntegerSetValueWithIncompatibleKeys(*argv, argc - 1, argv + 2);
                        break;

                    case 205 :
                        result = doTestStringSetValueWithIncompatibleKeys(*argv, argc - 1, argv + 2);
                        break;

                    case 250 :
                        result = doTestValidArrayCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 251 :
                        result = doTestValidLogicalMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 252 :
                        result = doTestValidIntegerMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 253 :
                        result = doTestValidStringMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 254 :
                        result = doTestValidLogicalSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 255 :
                        result = doTestValidIntegerSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 256 :
                        result = doTestValidStringSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 257 :
                        result = doTestInvalidArrayCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 258 :
                        result = doTestInvalidLogicalMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 259 :
                        result = doTestInvalidIntegerMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 260 :
                        result = doTestInvalidStringMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 261 :
                        result = doTestInvalidLogicalSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 262 :
                        result = doTestInvalidIntegerSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 263 :
                        result = doTestInvalidStringSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 300 :
                        result = doTestArrayIndices(*argv, argc - 1, argv + 2);
                        break;

                    case 301 :
                        result = doTestLogicalMapSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 302 :
                        result = doTestIntegerMapSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 303 :
                        result = doTestStringMapSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 304 :
                        result = doTestLogicalSetSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 305 :
                        result = doTestIntegerSetSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 306 :
                        result = doTestStringSetSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 320 :
                        result = doTestEmptyArrayValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 321 :
                        result = doTestSingularArrayValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 322 :
                        result = doTestSmallArrayValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 323 :
                        result = doTestBigArrayValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 340 :
                        result = doTestEmptyMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 341 :
                        result = doTestSingularLogicalMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 342 :
                        result = doTestSingularIntegerMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 343 :
                        result = doTestSingularStringMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 344 :
                        result = doTestSmallLogicalMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 345 :
                        result = doTestSmallIntegerMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 346 :
                        result = doTestSmallStringMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 360 :
                        result = doTestEmptySetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 361 :
                        result = doTestSingularLogicalSetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 362 :
                        result = doTestSingularIntegerSetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 363 :
                        result = doTestSingularStringSetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 364 :
                        result = doTestSmallLogicalSetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 365 :
                        result = doTestSmallIntegerSetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 366 :
                        result = doTestSmallStringSetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 380 :
                        result = doTestArrayWithArrayValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 381 :
                        result = doTestArrayWithMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 382 :
                        result = doTestArrayWithSetValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 383 :
                        result = doTestMapWithArrayValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 384 :
                        result = doTestMapWithMapValueAsJSON(*argv, argc - 1, argv + 2);
                        break;

                    case 385 :
                        result = doTestMapWithSetValueAsJSON(*argv, argc - 1, argv + 2);
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

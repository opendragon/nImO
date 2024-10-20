//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOparserTest.cpp
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
//  Created:    2016-04-13
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOblob.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOnumber.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImObufferChunk.h>
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
    ODL_ENTER(); //####
    ODL_P1(&aValue); //####
    ODL_S1(aString); //####
    StringBuffer    buff;

    aValue.printToStringBuffer(buff);
    auto    resultString{buff.getString()};
    int     result{resultString.compare(aString)};

    ODL_S2(resultString.c_str(), aString); //####
    ODL_EXIT_I(result); //####
    return result;
} // compareValueWithString

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseLogicalValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asLogical())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseLogicalValue

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseNumberValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asNumber())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseNumberValue

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseStringValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asString())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseStringValue

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseAddressValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asAddress())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseAddressValue

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseDateValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asDate())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseDateValue

#if defined(__APPLE__)
# pragma mark *** Test Case 06 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseTimeValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asTime())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseTimeValue

#if defined(__APPLE__)
# pragma mark *** Test Case 07 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseArrayValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("! ((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asArray())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseArrayValue

#if defined(__APPLE__)
# pragma mark *** Test Case 08 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseSetValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("! ((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asSet())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseSetValue

#if defined(__APPLE__)
# pragma mark *** Test Case 09 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseMapValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("! ((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asMap())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseMapValue

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseImplicitArrayValue
    (const bool expected,
     CPtr(char) inString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S2(inString, expectedString); //####
    int result{1};

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        auto    readValue{buff.convertToValue()};

        if ((nullptr != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("! ((nullptr != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (nullptr == readValue->asArray())
            {
                if (expected)
                {
                    ODL_LOG("(expected)"); //####
                    result = 1;
                }
                else
                {
                    result = 0; // wrong type returned, but it was not expected to succeed
                }
            }
            else
            {
                if (0 == compareValueWithString(*readValue, expectedString))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*readValue, expectedString))"); //####
                    result = 1;
                }
            }
        }
        else
        {
            ODL_LOG("! (readValue)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestParseImplicitArrayValue

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

        if (3 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                bool    expected{('t' == *argv[2]) || ('T' == *argv[2])};

                SetSignalHandlers(catchSignal);
                ODL_B1(expected); //####
                switch (selector)
                {
                    case 1 :
                        result = doTestParseLogicalValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 2 :
                        result = doTestParseNumberValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 3 :
                        result = doTestParseStringValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 4 :
                        result = doTestParseAddressValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 5 :
                        result = doTestParseDateValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 6 :
                        result = doTestParseTimeValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 7 :
                        result = doTestParseArrayValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 8 :
                        result = doTestParseSetValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 9 :
                        result = doTestParseMapValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 10 :
                        result = doTestParseImplicitArrayValue(expected, *(argv + 3), *(argv + 4));
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
            ODL_LOG("! (3 < --argc)"); //####
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

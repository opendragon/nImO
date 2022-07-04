//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOzeroConfTest.cpp
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
//  Created:    2017-02-10
//
//--------------------------------------------------------------------------------------------------

#if 0
#include <nImOblob.hpp>
#include <nImObufferChunk.hpp>
#include <nImOlogical.hpp>
#include <nImOnumber.hpp>
#include <nImOstring.hpp>
#include <nImOstringBuffer.hpp>
#endif//0
#include <nImOcommon.hpp>

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
using std::cerr;
using std::cout;
using std::endl;

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
/*! @brief Compare a Value object with a string.
 @param[in] aValue The object to be compared.
 @param[in] aString The string to be compared to.
 @return @c -1, @c 0 or @c 1 depending on where the string is greater than, equal to or less than
 the object representation as a string. */
static int
compareValueWithString
    (const Value &  aValue,
     const char *   aString)
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
#endif//0

#if 0
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
    (const bool     expected,
     const char *   inString,
     const char *   expectedString) // logical values
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        StringBuffer    buff;

        buff.addString(inString);
        SpValue readValue{buff.convertToValue()};

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

#endif//0

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
    (int        NOT_USED_(argc),
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
        Initialize(progName, nImO::ApplicationRole::Test);
#if 0
        if (3 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                bool expected = (('t' == *argv[2]) || ('T' == *argv[2]));
#endif //0
                SetSignalHandlers(catchSignal);
#if 0
                ODL_B1("expected <- ", expected); //####
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
                        result = doTestParseArrayValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 5 :
                        result = doTestParseSetValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 6 :
                        result = doTestParseMapValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    case 7 :
                        result = doTestParseImplicitArrayValue(expected, *(argv + 3), *(argv + 4));
                        break;

                    default :
                        break;

                }
                if (result)
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
            ODL_LOG("! (3 < --argc)"); //####
        }
#endif//0
        nImO::Terminate();
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // main

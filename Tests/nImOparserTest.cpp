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

#include <nImO/nImOblob.hpp>
#include <nImO/nImOboolean.hpp>
#include <nImO/nImObufferChunk.hpp>
#include <nImO/nImOnumber.hpp>
#include <nImO/nImOstring.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

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

using std::cerr;
using std::cout;
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

/*! @brief The number of elements in a small test. */
static const size_t kSmallTestSize = 100;

/*! @brief The number of elements in a big test. */
static const size_t kBigTestSize = 100000;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief The signal handler to catch requests to stop the service.
 @param signal The signal being handled. */
static void
catchSignal(int signal)
{
    ODL_ENTER(); //####
    ODL_LL1("signal = ", signal); //####
    std::stringstream buff;
    std::string       message("Exiting due to signal ");

    buff << signal;
    message += buff.str();
    message += " = ";
    message += nImO::NameOfSignal(signal);
#if 0
    nImO_ERROR_(message.c_str());
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param expected @c true if the test is expected to succeed, and @c false otherwise.
 @param inString The string to be used for the test.
 @param delimiters The delimiters to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestParseBooleanValue(const bool   expected,
                        const char * inString,
                        const char * delimiters) // boolean values
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "delimiters = ", delimiters); //####
    int result = 1;

    try
    {
        nImO::StringBuffer buff;

        buff.addString(inString);
        nImO::Value * readValue = nImO::Value::readFromStringBuffer(buff, 0, delimiters);

        if ((NULL != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((NULL != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (readValue->isBoolean())
            {
                buff.reset();
                readValue->printToStringBuffer(buff);
                cout << buff << endl;
                result = 0;
            }
            else if (expected)
            {
                ODL_LOG("(expected)"); //####
            }
            else
            {
                result = 0; // wrong type returned, but it was not expected to succeed
            }
            delete readValue;
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestParseBooleanValue

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param expected @c true if the test is expected to succeed, and @c false otherwise.
 @param inString The string to be used for the test.
 @param delimiters The delimiters to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestParseNumberValue(const bool   expected,
                       const char * inString,
                       const char * delimiters) // number values
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "delimiters = ", delimiters); //####
    int result = 1;

    try
    {
        nImO::StringBuffer buff;

        buff.addString(inString);
        nImO::Value * readValue = nImO::Value::readFromStringBuffer(buff, 0, delimiters);

        if ((NULL != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((NULL != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (readValue->isNumber())
            {
                buff.reset();
                readValue->printToStringBuffer(buff);
                cout << buff << endl;
                result = 0;
            }
            else if (expected)
            {
                ODL_LOG("(expected)"); //####
            }
            else
            {
                result = 0; // wrong type returned, but it was not expected to succeed
            }
            delete readValue;
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestParseNumberValue
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param expected @c true if the test is expected to succeed, and @c false otherwise.
 @param inString The string to be used for the test.
 @param delimiters The delimiters to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestParseStringValue(const bool   expected,
                       const char * inString,
                       const char * delimiters) // string values
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "delimiters = ", delimiters); //####
    int result = 1;

    try
    {
        nImO::StringBuffer buff;

        buff.addString(inString);
        nImO::Value * readValue = nImO::Value::readFromStringBuffer(buff, 0, delimiters);

        if ((NULL != readValue) == expected)
        {
            result = 0;
        }
        else
        {
            ODL_LOG("((NULL != readValue) == expected)"); //####
        }
        if (readValue)
        {
            if (readValue->isString())
            {
                buff.reset();
                readValue->printToStringBuffer(buff);
                cout << buff << endl;
                result = 0;
            }
            else if (expected)
            {
                ODL_LOG("(expected)"); //####
            }
            else
            {
                result = 0; // wrong type returned, but it was not expected to succeed
            }
            delete readValue;
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestParseStringValue
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for unit tests of the %nImO common classes.

 The first argument is the test number, the second argument is the name of the channel to be used
 with the test, the optional third argument is the machine to connect to and the optional fourth
 argument is the port number to be used. Output depends on the test being run.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used with the unit tests.
 @returns @c 0 on a successful test and @c 1 on failure. */
int
main(int      argc,
     char * * argv)
{
    std::string progName(*argv);

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
        nImO::Initialize(progName);
        if (2 < --argc)
        {
            const char * startPtr = argv[1];
            char *       endPtr;
            int          selector = strtol(startPtr, &endPtr, 10);

            ODL_LL1("selector <- ", selector); //####
            if ((startPtr != endPtr) && (! *endPtr) && (0 < selector))
            {
                bool   expected = (('t' == *argv[2]) || ('T' == *argv[2]));
                char * delimiters = ((3 < argc) ? *(argv + 4) : NULL);

                nImO::SetSignalHandlers(catchSignal);
                ODL_B1("expected <- ", expected); //####
                switch (selector)
                {
                    case 1 :
                        result = doTestParseBooleanValue(expected, *(argv + 3), delimiters);
                        break;

                    case 2 :
                        result = doTestParseNumberValue(expected, *(argv + 3), delimiters);
                        break;

                    case 3 :
                        result = doTestParseStringValue(expected, *(argv + 3), delimiters);
                        break;

                    default :
                        break;

                }
                if (result)
                {
                    ODL_LL1("%%%%%%% unit test failure = ", result); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (2 < --argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // main

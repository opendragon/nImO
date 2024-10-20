//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOnamesTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2020 by OpenDragon.
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
//  Created:    2020-03-03
//
//--------------------------------------------------------------------------------------------------

#include <Contexts/nImOtestContext.h>
#include <nImOchannelName.h>

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

#if defined(__APPLE__)
# pragma mark *** Test Case 01  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidateNetworkName
    (const bool expected,
     CPtr(char) inString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S1(inString); //####
    int result{1};

    try
    {
        bool    checked{ChannelName::validNetwork(inString)};

        if (checked == expected)
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
} // doTestValidateNetworkName

#if defined(__APPLE__)
# pragma mark *** Test Case 02  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidateNodeName
    (const bool expected,
     CPtr(char) inString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S1(inString); //####
    int result{1};

    try
    {
        bool    checked{ChannelName::validNode(inString)};

        if (checked == expected)
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
} // doTestValidateNodeName

#if defined(__APPLE__)
# pragma mark *** Test Case 03  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidatePath
    (const bool expected,
     CPtr(char) inString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S1(inString); //####
    int result{1};

    try
    {
        bool    checked{ChannelName::validPath(inString)};

        if (checked == expected)
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
} // doTestValidatePath

#if defined(__APPLE__)
# pragma mark *** Test Case 04  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestValidateTransport
    (const bool expected,
     CPtr(char) inString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S1(inString); //####
    int result{1};

    try
    {
        bool    checked{ChannelName::validTransport(inString)};

        if (checked == expected)
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
} // doTestValidateTransport

#if defined(__APPLE__)
# pragma mark *** Test Case 10  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseChannelName
    (const bool expected,
     CPtr(char) inString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S1(inString); //####
    int result{1};

    try
    {
        std::string     failed;
        SpChannelName   parsed{ChannelName::parse(inString, failed)};

        if ((nullptr != parsed) == expected)
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
} // doTestParseChannelName

#if defined(__APPLE__)
# pragma mark *** Test Case 11  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseExpectedName
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
        std::string     failed;
        SpChannelName   parsed{ChannelName::parse(inString, failed)};

        if ((nullptr != parsed) == expected)
        {
            if (expected)
            {
                if (parsed->getName() == expectedString)
                {
                    result = 0;
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
} // doTestParseExpectedName

#if defined(__APPLE__)
# pragma mark *** Test Case 12  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseExtractNetwork
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
        std::string     failed;
        SpChannelName   parsed{ChannelName::parse(inString, failed)};

        if ((nullptr != parsed) == expected)
        {
            if (expected)
            {
                if (parsed->getNetwork() == expectedString)
                {
                    result = 0;
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
} // doTestParseExtractNetwork

#if defined(__APPLE__)
# pragma mark *** Test Case 13  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseExtractNode
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
        std::string     failed;
        SpChannelName   parsed{ChannelName::parse(inString, failed)};

        if ((nullptr != parsed) == expected)
        {
            if (expected)
            {
                if (parsed->getNode() == expectedString)
                {
                    result = 0;
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
} // doTestParseExtractNode

#if defined(__APPLE__)
# pragma mark *** Test Case 14  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseExtractPath
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
        std::string     failed;
        SpChannelName   parsed{ChannelName::parse(inString, failed)};

        if ((nullptr != parsed) == expected)
        {
            if (expected)
            {
                if (parsed->getPath() == expectedString)
                {
                    result = 0;
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
} // doTestParseExtractPath

#if defined(__APPLE__)
# pragma mark *** Test Case 15  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestParseExtractProtocol
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
        std::string     failed;
        SpChannelName   parsed{ChannelName::parse(inString, failed)};

        if ((nullptr != parsed) == expected)
        {
            if (expected)
            {
                if (nImO::ChannelName::transportToName(parsed->getTransport()) == expectedString)
                {
                    result = 0;
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
} // doTestParseExtractProtocol

#if defined(__APPLE__)
# pragma mark *** Test Case 16  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] baseString The base path to be used for the test.
 @param[in] forOutputString Whether an output path is to be generated or an input path.
 @param[in] numChannelsString The number of channels for output or input.
 @param[in] channelNumberString The index of the channel.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGeneratePath
    (const bool expected,
     CPtr(char) baseString,
     CPtr(char) forOutputString,
     CPtr(char) numChannelsString,
     CPtr(char) channelNumberString,
     CPtr(char) expectedString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S4(baseString, forOutputString, numChannelsString, channelNumberString); //####
    ODL_S1(expectedString); //####
    int result{1};

    try
    {
        int64_t numChannels;
        int64_t channelNumber;

        if (ConvertToInt64(numChannelsString, numChannels) && (0 < numChannels) &&
            ConvertToInt64(channelNumberString, channelNumber) && (0 < channelNumber))
        {
            bool        forOutput{('t' == *forOutputString) || ('T' == *forOutputString)};
            std::string path;

            if (nImO::ChannelName::generatePath(baseString, forOutput, numChannels, channelNumber, path))
            {
                if (expected && (path == expectedString))
                {
                    result = 0;
                }
            }
            else
            {
                if (! expected)
                {
                    result = 0;
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
} // doTestGeneratePath

#if defined(__APPLE__)
# pragma mark *** Test Case 17  ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] expected @c true if the test is expected to succeed, and @c false otherwise.
 @param[in] inString The string to be used for the test.
 @param[in] expectedString The expected output from the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestName
    (const bool expected,
     CPtr(char) inString)
{
    ODL_ENTER(); //####
    ODL_B1(expected); //####
    ODL_S1(inString); //####
    int result{1};

    try
    {
        bool    checked{ValidNameSegment(inString)};

        if (checked == expected)
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
} // doTestName

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

        if (2 < --argc)
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
                        result = doTestValidateNetworkName(expected, *(argv + 3));
                        break;

                    case 2 :
                        result = doTestValidateNodeName(expected, *(argv + 3));
                        break;

                    case 3 :
                        result = doTestValidatePath(expected, *(argv + 3));
                        break;

                    case 4 :
                        result = doTestValidateTransport(expected, *(argv + 3));
                        break;

                    case 10 :
                        result = doTestParseChannelName(expected, *(argv + 3));
                        break;

                    case 11 :
                        if (3 < argc)
                        {
                            result = doTestParseExpectedName(expected, *(argv + 3), *(argv + 4));
                        }
                        break;

                    case 12 :
                        if (3 < argc)
                        {
                            result = doTestParseExtractNetwork(expected, *(argv + 3), *(argv + 4));
                        }
                        break;

                    case 13 :
                        if (3 < argc)
                        {
                            result = doTestParseExtractNode(expected, *(argv + 3), *(argv + 4));
                        }
                        break;

                    case 14 :
                        if (3 < argc)
                        {
                            result = doTestParseExtractPath(expected, *(argv + 3), *(argv + 4));
                        }
                        break;

                    case 15 :
                        if (3 < argc)
                        {
                            result = doTestParseExtractProtocol(expected, *(argv + 3), *(argv + 4));
                        }
                        break;

                    case 16 :
                        if (6 < argc)
                        {
                            result = doTestGeneratePath(expected, *(argv + 3), *(argv + 4), *(argv + 5), *(argv + 6), *(argv + 7));
                        }
                        break;

                    case 17 :
                        result = doTestName(expected, *(argv + 3));
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
            ODL_LOG("! (2 < --argc)"); //####
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

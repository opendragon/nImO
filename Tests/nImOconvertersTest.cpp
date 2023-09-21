//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOconvertersTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2018 by OpenDragon.
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
//  Created:    2018-06-27
//
//--------------------------------------------------------------------------------------------------

#include <Contexts/nImOtestContext.h>
#include <nImOconverters.h>

#include <iomanip>
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
using namespace std::string_literals;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

/*! @brief The number of random floating point numbers to convert. */
static const int    kNumDoubleTests = 100;

/*! @brief The expected maximum size of a buffer needed for conversion. */
static const size_t kBufferSize = 20;

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

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestInvalidArgs
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    ODL_I1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (0 < argc)
        {
            int64_t choice;

            if (ConvertToInt64(*argv, choice))
            {
                uint8_t buffer[kBufferSize];
                int64_t newInteger;
                double  newDouble;

                switch (choice)
                {
                    case 1:
                        // Test conversion bad NULL arguments
                        if ((0 == ConvertInt64ToPacketOrder(buffer, nullptr, 42)) &&
                            (0 == ConvertDoubleToPacketOrder(buffer, nullptr, 42.0)) &&
                            (0 == ConvertPacketOrderToInt64(buffer, nullptr, newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(buffer, nullptr, newDouble)) &&
                            (0 == ConvertPacketOrderToInt64(nullptr, buffer, newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(nullptr, buffer, newDouble)))
                        {
                            result = 0;
                        }
                        break;

                    case 2:
                        // Test conversion bad pointer arguments
                        if ((0 == ConvertInt64ToPacketOrder(buffer + 1, buffer, 42)) &&
                            (0 == ConvertDoubleToPacketOrder(buffer + 1, buffer, 42.0)) &&
                            (0 == ConvertPacketOrderToInt64(buffer + 1, buffer, newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(buffer + 1, buffer, newDouble)) &&
                            (0 == ConvertPacketOrderToInt64(buffer, buffer + sizeof(int64_t), newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(buffer, buffer + sizeof(double), newDouble)))
                        {
                            result = 0;
                        }
                        break;

                }
            }
            else
            {
                ODL_LOG("! ConvertToInt64(*argv, choice)"); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestInvalidArgs

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerSize
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    ODL_I1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (1 < argc)
        {
            int64_t value;
            int64_t length;

            if (ConvertToInt64(*argv, value) && ConvertToInt64(argv[1], length))
            {
                size_t  calcLength = ConvertInt64ToPacketOrder(nullptr, nullptr, value);

                if (StaticCast(int64_t, calcLength) == length)
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("calcLength != length"); //####
                }
            }
            else
            {
                ODL_LOG("! (ConvertToInt64(*argv, value) && ConvertToInt64(argv[1], length))"); //####
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
} // doTestIntegerSize

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDoubleSize
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
        double  value{(nImO::RandomUnsigned() % 10000) * 0.1};
        size_t  expectedLength{sizeof(double)};
        int64_t calcLength{StaticCast(int64_t, ConvertDoubleToPacketOrder(nullptr, nullptr, value))};

        if (calcLength == StaticCast(int64_t, expectedLength))
        {
            result = 0;
        }
        else
        {
            ODL_LOG("calcLength != expectedLength"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestDoubleSize

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerConversion
    (CPtr(char)     launchPath,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    ODL_I1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        if (0 < argc)
        {
            int64_t value;

            if (ConvertToInt64(*argv, value))
            {
                size_t  expectedLength{ConvertInt64ToPacketOrder(nullptr, nullptr, value)};
                uint8_t buffer[kBufferSize];
                size_t  convLength{ConvertInt64ToPacketOrder(buffer, buffer + sizeof(buffer) - 1, value)};

                if (expectedLength == convLength)
                {
                    int64_t newValue;
                    size_t  newLength{ConvertPacketOrderToInt64(buffer, buffer + convLength - 1, newValue)};

                    if ((newValue == value) && (newLength == convLength))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! ((newValue == value) && (newLength == convLength))"); //####
                    }
                }
                else
                {
                    ODL_LOG("expectedLength != convLength"); //####
                }
            }
            else
            {
                ODL_LOG("! ConvertToInt64(*argv, value)"); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < argc)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestIntegerConversion

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDoubleConversion
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
        for (int ii = 0; ii < kNumDoubleTests; ++ii)
        {
            double  value{(nImO::RandomUnsigned() % 10000) * 0.1};
            size_t  expectedLength{ConvertDoubleToPacketOrder(nullptr, nullptr, value)};
            uint8_t buffer[kBufferSize];
            size_t  convLength{ConvertDoubleToPacketOrder(buffer, buffer + sizeof(buffer) - 1, value)};

            if (expectedLength == convLength)
            {
                double  newValue;
                size_t  newLength{ConvertPacketOrderToDouble(buffer, buffer + convLength - 1, newValue)};

                if ((newValue == value) && (newLength == convLength))
                {
                    result = 0;
                }
                else
                {
                    result = 1;
                    ODL_LOG("! ((newValue == value) && (newLength == convLength))"); //####
                    break;

                }
            }
            else
            {
                result = 1;
                ODL_LOG("expectedLength != convLength"); //####
                break;

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
} // doTestDoubleConversion

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
                        result = doTestInvalidArgs(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestIntegerSize(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestDoubleSize(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestIntegerConversion(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestDoubleConversion(*argv, argc - 1, argv + 2);
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

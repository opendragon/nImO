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

#include <nImOconverters.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

#include <iomanip>

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
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

/*! @brief The number of random floating point numbers to convert. */
static const int kNumFloatTests = 100;

/*! @brief The expected maximum size of a buffer needed for conversion. */
static const size_t kBufferSize = 20;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief The signal handler to catch requests to stop the service.
 @param[in] signal The signal being handled. */
[[noreturn]]
static void
catchSignal(int signal)
{
    ODL_ENTER(); //####
    ODL_LL1("signal = ", signal); //####
    std::string message("Exiting due to signal ");

    message += std::to_string(signal);
    message += " = ";
    message += NameOfSignal(signal);
#if 0
    nImO_ERROR_(message.c_str());
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestInvalidArgs(UNUSED_ const char *launchPath,
                  UNUSED_ const int  argc,
                  UNUSED_ char       **argv) // invalid args
{
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;
    
    try
    {
        if (0 < argc)
        {
            int64_t choice;

            if (ConvertToLong(*argv, choice))
            {
                uint8_t buffer[kBufferSize];
                int64_t newInteger;
                double  newFloat;

                switch (choice)
                {
                    case 1:
                        // Test conversion bad NULL arguments
                        if ((0 == ConvertLongToPacketOrder(buffer, NULL, 42)) &&
                            (0 == ConvertDoubleToPacketOrder(buffer, NULL, 42.0)) &&
                            (0 == ConvertPacketOrderToLong(buffer, NULL, newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(buffer, NULL, newFloat)) &&
                            (0 == ConvertPacketOrderToLong(NULL, buffer, newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(NULL, buffer, newFloat)))
                        {
                            result = 0;
                        }
                        break;

                    case 2:
                        // Test conversion bad pointer arguments
                        if ((0 == ConvertLongToPacketOrder(buffer + 1, buffer, 42)) &&
                            (0 == ConvertDoubleToPacketOrder(buffer + 1, buffer, 42.0)) &&
                            (0 == ConvertPacketOrderToLong(buffer + 1, buffer, newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(buffer + 1, buffer, newFloat)) &&
                            (0 == ConvertPacketOrderToLong(buffer, buffer + sizeof(int64_t), newInteger)) &&
                            (0 == ConvertPacketOrderToDouble(buffer, buffer + sizeof(double), newFloat)))
                        {
                            result = 0;
                        }
                        break;

                }
            }
            else
            {
                ODL_LOG("! ConvertToLong(*argv, choice)"); //####
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestInvalidArgs
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestIntegerSize(UNUSED_ const char *launchPath,
                  UNUSED_ const int  argc,
                  UNUSED_ char       **argv) // integer size
{
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            int64_t value;
            int64_t length;
        
            if (ConvertToLong(*argv, value) && ConvertToLong(argv[1], length))
            {
                size_t  calcLength = ConvertLongToPacketOrder(NULL, NULL, value);
                
                if (static_cast<int64_t>(calcLength) == length)
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
                ODL_LOG("! (ConvertToLong(*argv, value) && ConvertToLong(argv[1], length))"); //####
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestIntegerSize
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestFloatingPointSize(UNUSED_ const char *launchPath,
                        UNUSED_ const int  argc,
                        UNUSED_ char       **argv) // floating point size
{
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        double  value = ((rand() % 10000) * 0.1);
        size_t  expectedLength = sizeof(double);
        int64_t calcLength = ConvertDoubleToPacketOrder(NULL, NULL, value);
        
        if (calcLength == static_cast<int64_t>(expectedLength))
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestFloatingPointSize
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestIntegerConversion(UNUSED_ const char *launchPath,
                        UNUSED_ const int  argc,
                        UNUSED_ char       **argv) // integer conversion
{
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (0 < argc)
        {
            int64_t value;
            
            if (ConvertToLong(*argv, value))
            {
                size_t  expectedLength = ConvertLongToPacketOrder(NULL, NULL, value);
                uint8_t buffer[kBufferSize];
                size_t  convLength = ConvertLongToPacketOrder(buffer, buffer + sizeof(buffer) - 1, value);

                if (expectedLength == convLength)
                {
                    int64_t newValue;
                    size_t  newLength = ConvertPacketOrderToLong(buffer, buffer + convLength - 1, newValue);
                    
                    if ((newValue == value) && (newLength == convLength))
                    {
                        result = 0;
                    }
                    else
                    {
cerr << newValue << " " << value << endl << newLength << " " << convLength << endl;
                        ODL_LOG("! ((newValue == value) && (newLength == convLength))"); //####
                    }
                }
                else
                {
cerr << "expectedLength != convLength" << endl;
                    ODL_LOG("expectedLength != convLength"); //####
                }
            }
            else
            {
                ODL_LOG("! ConvertToLong(*argv, value)"); //####
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestIntegerConversion
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestFloatingPointConversion(UNUSED_ const char *launchPath,
                              UNUSED_ const int  argc,
                              UNUSED_ char       **argv) // floating point conversion
{
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        for (int ii = 0; ii < kNumFloatTests; ++ii)
        {
            double  value = ((rand() % 10000) * 0.1);
            size_t  expectedLength = ConvertDoubleToPacketOrder(NULL, NULL, value);
            uint8_t buffer[kBufferSize];
            size_t  convLength = ConvertDoubleToPacketOrder(buffer, buffer + sizeof(buffer) - 1, value);
            
            if (expectedLength == convLength)
            {
                double  newValue;
                size_t  newLength = ConvertPacketOrderToDouble(buffer, buffer + convLength - 1, newValue);
                
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
    ODL_EXIT_L(result); //####
    return result;
} // doTestFloatingPointConversion
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for unit tests of the %nImO common classes.

 The first argument is the test number, the second argument is the name of the channel to be used
 with the test, the optional third argument is the machine to connect to and the optional fourth
 argument is the port number to be used. Output depends on the test being run.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the unit tests.
 @returns @c 0 on a successful test and @c 1 on failure. */
int
main(int  argc,
     char **argv)
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
        Initialize(progName);
        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToLong(argv[1], selector) && (0 < selector))
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
                        result = doTestFloatingPointSize(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestIntegerConversion(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestFloatingPointConversion(*argv, argc - 1, argv + 2);
                        break;

                    default :
                        break;

                }
                if (result)
                {
                    ODL_LL1("%%%%%%% unit test failure = ", result); //####
                }
            }
            else
            {
                ODL_LOG("! (ConvertToLong(argv[1], selector) && (0 < selector))"); //####
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
    ODL_EXIT_L(result); //####
    return result;
} // main

/*
# Test integer size for value of 0
#add_test(NAME TestIntegerSize COMMAND ${THIS_TARGET} 1 0 1)
# Test floating point size
#add_test(NAME TestFloatingPointSize COMMAND ${THIS_TARGET} 2)
# Test integer conversion for value of 0
#add_test(NAME TestIntegerConversion COMMAND ${THIS_TARGET} 3 0)
# Test floating point conversion
#add_test(NAME TestFloatingPointConversion COMMAN ${THIS_TARGET} 4)
*/
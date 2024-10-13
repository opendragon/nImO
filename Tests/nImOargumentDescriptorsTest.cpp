//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOargumentDescriptorsTest.cpp
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
//  Created:    2020-03-06
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOaddressArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOchannelArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOdoubleArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOdateArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOlogicalArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOportArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringsArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOtimeArgumentDescriptor.h>
#include <Contexts/nImOtestContext.h>

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
    auto    message{"exiting due to signal "s + std::to_string(signal) + " = "s + NameOfSignal(signal)};

    NIMO_UNUSED_VAR_(message);
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

/*! @brief Inserts tabs in the expected string.
 @param[in] inString The string to process.
 @return The input string with the two character sequence '\t' replaced with tabs. */
static std::string
fixDescriptorString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    auto    result{inString};

    for (auto pos{result.find("\\t"s)}; pos != result.npos; pos = result.find("\\t"s))
    {
        result.replace(pos, 2, "\t"s);
    }
    ODL_EXIT_s(result); //####
    return result;
} // fixDescriptorString

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddressArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<AddressArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required,
                                                                             kSelfAddressIpAddress);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<AddressArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, ""s);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<AddressArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, *argv);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<AddressArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required,
                                                                                 kSelfAddressIpAddress);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestAddressArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestBooleanArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<LogicalArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, true);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                // Since the parameters for BoolAgumentDescriptor are either true or false, it's not possible to make a failing
                // descriptor, so skip this test.
                result = 0;
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<LogicalArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required,
                                                                                 0 == strcmp(*argv, "true"));
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<LogicalArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, false);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestBooleanArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestChannelArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<ChannelArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "/out"s);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<ChannelArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, ":#"s);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<ChannelArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, *argv);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<ChannelArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "/tmp"s);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestChannelArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDoubleArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<DoubleArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 42.0, false,
                                                                            0.0, false, 0.0);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<DoubleArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 42.0, true,
                                                                            1000, true, 200);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<DoubleArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required,
                                                                                strtod(*argv, nullptr), false, 0, true, 1000);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<DoubleArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 42.0, true,
                                                                                -10, true, 10);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestDoubleArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFilePathArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<FilePathArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "/tmp/"s,
                                                                              "temp.txt"s, true);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<FilePathArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "/usr/bin"s,
                                                                              ""s, true);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<FilePathArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "/tmp/"s,
                                                                                  "stuff.txt"s);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<FilePathArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "/tmp/"s,
                                                                                  "stuff.txt"s, true);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestFilePathArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 06 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestIntegerArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<IntegerArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 42, false, 0,
                                                                             false, 0);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<IntegerArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 42, true, 1000,
                                                                             true, 200);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
                    {
                        result = 0;
                    }
                    else
                    {
                        if (! expected)
                        {
                            result = 0;
                        }
                    }
                }
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<IntegerArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required,
                                                                                 strtol(*argv, nullptr, 10), false, 0, true, 1000);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<IntegerArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 42, true,
                                                                                 -100, true, 100);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestIntegerArgumentDescriptors
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark *** Test Case 07 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestPortArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<PortArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 1234, true);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<PortArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 42, false);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<PortArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required,
                                                                              strtol(*argv, nullptr, 10), false);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<PortArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, 1234, false);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestPortArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 08 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                // All inputs for StringAgumentDescriptor are valid, so skip this test.
                result = 0;
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                // All inputs for StringAgumentDescriptor are valid, so skip this test.
                result = 0;
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<StringArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, *argv);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                // All inputs for StringAgumentDescriptor are valid, so skip this test.
                result = 0;
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 09 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestStringsArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;
        StdStringSet                allowable;

        allowable.insert("abc");
        allowable.insert("def");
        allowable.insert("$%@");
        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<StringsArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "abc"s,
                                                                             allowable);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                allowable.clear();
                testDescriptor = std::make_shared<StringsArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "abc"s,
                                                                             allowable);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<StringsArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "abc"s,
                                                                                 allowable);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<StringsArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "abc"s,
                                                                                 allowable);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            case 5 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<StringsArgumentDescriptor>("descriptor"s, "something"s,
                                                                                 ArgumentMode::Required | ArgumentMode::CaseInsensitive, "abc"s,
                                                                                 allowable);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 6 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<StringsArgumentDescriptor>("descriptor"s, "something"s,
                                                                                 ArgumentMode::Required | ArgumentMode::CaseInsensitive, "abc"s,
                                                                                 allowable);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestStringsArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestDateArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<DateArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "0/1/1"s);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<DateArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, ""s);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<DateArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, *argv);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<DateArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "0/1/1"s);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestDateArgumentDescriptors

#if defined(__APPLE__)
# pragma mark *** Test Case 11 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] subSelector The subtest to perform.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestTimeArgumentDescriptors
    (CPtr(char)     launchPath,
     const int      subSelector,
     const bool     expected,
     const int      argc,
     Ptr(Ptr(char)) argv)
{
    NIMO_UNUSED_VAR_(launchPath);
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_I2("subSelector = ", subSelector, "argc = ", argc); //####
    ODL_B1("expected = ", expected); //####
    ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        SpBaseArgumentDescriptor    testDescriptor;

        // 1) test that 'reasonable' parameters successfully build a descriptor that accepts the default value
        // 2) if there are 'unreasonable' parameters possible, test that using the default value fails
        // 3) for a range of 'reasonable' parameters, compare the descriptor description with the expected description
        // 4) for a range of 'reasonable' parameters, test for 'valid' and 'invalid' input
        switch (subSelector)
        {
            case 1 :
                // Test that 'reasonable' parameters work with the default value.
                testDescriptor = std::make_shared<TimeArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "0"s);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 2 :
                // Test that using 'unreasonable' parameters fails with the default value.
                testDescriptor = std::make_shared<TimeArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, ""s);
                if (testDescriptor->isValid())
                {
                    if (testDescriptor->validate(testDescriptor->getDefaultValue()) == expected)
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
                break;

            case 3 :
                // Check the descriptor description.
                if (2 == argc)
                {
                    testDescriptor = std::make_shared<TimeArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, *argv);
                    if (testDescriptor->isValid())
                    {
                        if ((testDescriptor->toString() == fixDescriptorString(argv[1])) == expected)
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
                break;

            case 4 :
                // Test input for validity.
                if (1 == argc)
                {
                    testDescriptor = std::make_shared<TimeArgumentDescriptor>("descriptor"s, "something"s, ArgumentMode::Required, "0"s);
                    if (testDescriptor->isValid())
                    {
                        if (testDescriptor->validate(*argv) == expected)
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
                break;

            default :
                break;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestTimeArgumentDescriptors

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
            int64_t subSelector;
            bool    expected{('t' == *argv[2]) || ('T' == *argv[2])};

            ODL_B1("expected <- ", expected); //####
            if (ConvertToInt64(argv[1], selector) && (0 < selector) && ConvertToInt64(argv[3], subSelector) && (0 < subSelector))
            {
                SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        // Address argument descriptor
                        result = doTestAddressArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;


                    case 2 :
                        // Bool argument descriptor
                        result = doTestBooleanArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 3 :
                        // Channel argument descriptor
                        result = doTestChannelArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 4 :
                        // Double argument descriptor
                        result = doTestDoubleArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 5 :
                        // File path argument descriptor
                        result = doTestFilePathArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 6 :
                        // Int argument descriptor
                        result = doTestIntegerArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 7 :
                        // Port argument descriptor
                        result = doTestPortArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 8 :
                        // String argument descriptor
                        result = doTestStringArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 9 :
                        // Strings argument descriptor
                        result = doTestStringsArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 10 :
                        // Date argument descriptor
                        result = doTestDateArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
                        break;

                    case 11 :
                        // Time argument descriptor
                        result = doTestTimeArgumentDescriptors(*argv, subSelector, expected, argc - 3, argv + 4);
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
                ODL_LOG("! (ConvertToInt64(argv[1], selector) && (0 < selector) && " //####
                        "ConvertToInt64(argv[3], subSelector) && (0 < subSelector))"); //####
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

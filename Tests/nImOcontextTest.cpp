//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOcontextTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
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
//  Created:    2023-01-25
//
//--------------------------------------------------------------------------------------------------

#include <nImOcontextWithMDNS.h>
#include <nImOcontextWithNetworking.h>
#include <nImOfilterContext.h>
#include <nImOmiscellaneousContext.h>
#include <nImOserviceContext.h>
#include <nImOsinkContext.h>
#include <nImOsourceContext.h>
#include <nImOtestContext.h>
#include <nImOutilityContext.h>

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
    std::string message{"Exiting due to signal "};

    message += std::to_string(signal);
    message += " = ";
    message += NameOfSignal(signal);
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

#if defined(__APPLE__)
# pragma mark *** Test Case 01 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateContextWithMDNS
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext("", "", false);

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateContextWithMDNS

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateContextWithNetworking
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        ContextWithNetworking   aContext("", "", false);

        NIMO_UNUSED_VAR_(aContext);
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateContextWithNetworking

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterContext
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext("", "", false);

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterContext

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousContext
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        MiscellaneousContext    aContext("");

        NIMO_UNUSED_VAR_(aContext);
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousContext

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceContext
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext("", "", false);

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceContext

#if defined(__APPLE__)
# pragma mark *** Test Case 06 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkContext
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        BlockRegistryLaunch();
        SinkContext aContext("", "", false);

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkContext

#if defined(__APPLE__)
# pragma mark *** Test Case 07 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceContext
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext("", "", false);

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceContext

#if defined(__APPLE__)
# pragma mark *** Test Case 08 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestContext
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        TestContext   aContext("");

        NIMO_UNUSED_VAR_(aContext);
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestContext

#if defined(__APPLE__)
# pragma mark *** Test Case 09 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityContext
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext("", "", false);

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityContext

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTwoContexts
    (void)
{
    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    int result = 1;

    try
    {
        UtilityContext  aContext1("", "", false);

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2("", "", false);

            NIMO_UNUSED_VAR_(aContext2);
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
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
} // doTestCreateTwoContexts

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for unit tests of the %nImO common classes.

 The first argument is the test number. Output depends on the test being run.
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
        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                SetSignalHandlers(catchSignal);
                ODL_B1("expected <- ", expected); //####
                switch (selector)
                {
                    case 1 :
                        result = doTestCreateContextWithMDNS();
                        break;

                    case 2 :
                        result = doTestCreateContextWithNetworking();
                        break;

                    case 3 :
                        result = doTestCreateFilterContext();
                        break;

                    case 4 :
                        result = doTestCreateMiscellaneousContext();
                        break;

                    case 5 :
                        result = doTestCreateServiceContext();
                        break;

                    case 6 :
                        result = doTestCreateSinkContext();
                        break;

                    case 7 :
                        result = doTestCreateSourceContext();
                        break;

                    case 8 :
                        result = doTestCreateTestContext();
                        break;

                    case 9 :
                        result = doTestCreateUtilityContext();
                        break;

                    case 10 :
                        result = doTestCreateTwoContexts();
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
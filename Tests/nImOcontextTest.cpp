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
    std::string message{"Exiting due to signal "};

    ODL_ENTER(); //####
    ODL_I1("signal = ", signal); //####
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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        ContextWithNetworking   aContext{"", "", false};

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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext{"", "", false};

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext{"", "", false};

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext{"", "", false};

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext{"", "", false};

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        TestContext   aContext{""};

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
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext{"", "", false};

        NIMO_UNUSED_VAR_(aContext);
        UnblockRegistryLaunch();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityContext

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 103 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 104 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 105 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 106 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 107 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 108 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithMDNS aContext1{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 114 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 115 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 116 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 117 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 118 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ContextWithNetworking   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 120 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 121 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 122 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 123 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 124 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 125 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 126 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 127 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 128 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        FilterContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 130 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 131 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 132 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 133 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 134 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 135 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 136 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 137 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 138 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 140 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 141 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 142 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 143 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 144 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 145 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 146 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 147 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 148 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateServiceAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        ServiceContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateServiceAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 150 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 151 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 152 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 153 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 154 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 155 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 156 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 157 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 158 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SinkContext aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 160 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 161 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 162 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 163 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 164 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 165 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 166 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 167 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 168 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        SourceContext   aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 170 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 171 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 172 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 173 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 174 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 175 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 176 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 177 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 178 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 180 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{"", "", false, ContextWithMDNS::ThreadMode::LaunchNeither};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 181 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 182 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 183 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 184 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 185 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 186 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 187 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 188 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    ODL_B1("expected = ", expected); //####
    ODL_S2("inString = ", inString, "expectedString = ", expectedString); //####
    try
    {
        BlockRegistryLaunch();
        UtilityContext  aContext1{"", "", false};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{"", "", false};

            NIMO_UNUSED_VAR_(aContext2);
            UnblockRegistryLaunch();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            UnblockRegistryLaunch();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        UnblockRegistryLaunch();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndUtilityContexts

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
    int         result = 1;

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
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

                    case 100 :
                        result = doTestCreateMDNSAndMDNSContexts();
                        break;

                    case 101 :
                        result = doTestCreateMDNSAndNetworkingContexts();
                        break;

                    case 102 :
                        result = doTestCreateMDNSAndFilterContexts();
                        break;

                    case 103 :
                        result = doTestCreateMDNSAndMiscellaneousContexts();
                        break;

                    case 104 :
                        result = doTestCreateMDNSAndServiceContexts();
                        break;

                    case 105 :
                        result = doTestCreateMDNSAndSinkContexts();
                        break;

                    case 106 :
                        result = doTestCreateMDNSAndSourceContexts();
                        break;

                    case 107 :
                        result = doTestCreateMDNSAndTestContexts();
                        break;

                    case 108 :
                        result = doTestCreateMDNSAndUtilityContexts();
                        break;

                    case 110 :
                        result = doTestCreateNetworkingAndMDNSContexts();
                        break;

                    case 111 :
                        result = doTestCreateNetworkingAndNetworkingContexts();
                        break;

                    case 112 :
                        result = doTestCreateNetworkingAndFilterContexts();
                        break;

                    case 113 :
                        result = doTestCreateNetworkingAndMiscellaneousContexts();
                        break;

                    case 114 :
                        result = doTestCreateNetworkingAndServiceContexts();
                        break;

                    case 115 :
                        result = doTestCreateNetworkingAndSinkContexts();
                        break;

                    case 116 :
                        result = doTestCreateNetworkingAndSourceContexts();
                        break;

                    case 117 :
                        result = doTestCreateNetworkingAndTestContexts();
                        break;

                    case 118 :
                        result = doTestCreateNetworkingAndUtilityContexts();
                        break;

                    case 120 :
                        result = doTestCreateFilterAndMDNSContexts();
                        break;

                    case 121 :
                        result = doTestCreateFilterAndNetworkingContexts();
                        break;

                    case 122 :
                        result = doTestCreateFilterAndFilterContexts();
                        break;

                    case 123 :
                        result = doTestCreateFilterAndMiscellaneousContexts();
                        break;

                    case 124 :
                        result = doTestCreateFilterAndServiceContexts();
                        break;

                    case 125 :
                        result = doTestCreateFilterAndSinkContexts();
                        break;

                    case 126 :
                        result = doTestCreateFilterAndSourceContexts();
                        break;

                    case 127 :
                        result = doTestCreateFilterAndTestContexts();
                        break;

                    case 128 :
                        result = doTestCreateFilterAndUtilityContexts();
                        break;

                    case 130 :
                        result = doTestCreateMiscellaneousAndMDNSContexts();
                        break;

                    case 131 :
                        result = doTestCreateMiscellaneousAndNetworkingContexts();
                        break;

                    case 132 :
                        result = doTestCreateMiscellaneousAndFilterContexts();
                        break;

                    case 133 :
                        result = doTestCreateMiscellaneousAndMiscellaneousContexts();
                        break;

                    case 134 :
                        result = doTestCreateMiscellaneousAndServiceContexts();
                        break;

                    case 135 :
                        result = doTestCreateMiscellaneousAndSinkContexts();
                        break;

                    case 136 :
                        result = doTestCreateMiscellaneousAndSourceContexts();
                        break;

                    case 137 :
                        result = doTestCreateMiscellaneousAndTestContexts();
                        break;

                    case 138 :
                        result = doTestCreateMiscellaneousAndUtilityContexts();
                        break;

                    case 140 :
                        result = doTestCreateServiceAndMDNSContexts();
                        break;

                    case 141 :
                        result = doTestCreateServiceAndNetworkingContexts();
                        break;

                    case 142 :
                        result = doTestCreateServiceAndFilterContexts();
                        break;

                    case 143 :
                        result = doTestCreateServiceAndMiscellaneousContexts();
                        break;

                    case 144 :
                        result = doTestCreateServiceAndServiceContexts();
                        break;

                    case 145 :
                        result = doTestCreateServiceAndSinkContexts();
                        break;

                    case 146 :
                        result = doTestCreateServiceAndSourceContexts();
                        break;

                    case 147 :
                        result = doTestCreateServiceAndTestContexts();
                        break;

                    case 148 :
                        result = doTestCreateServiceAndUtilityContexts();
                        break;

                    case 150 :
                        result = doTestCreateSinkAndMDNSContexts();
                        break;

                    case 151 :
                        result = doTestCreateSinkAndNetworkingContexts();
                        break;

                    case 152 :
                        result = doTestCreateSinkAndFilterContexts();
                        break;

                    case 153 :
                        result = doTestCreateSinkAndMiscellaneousContexts();
                        break;

                    case 154 :
                        result = doTestCreateSinkAndServiceContexts();
                        break;

                    case 155 :
                        result = doTestCreateSinkAndSinkContexts();
                        break;

                    case 156 :
                        result = doTestCreateSinkAndSourceContexts();
                        break;

                    case 157 :
                        result = doTestCreateSinkAndTestContexts();
                        break;

                    case 158 :
                        result = doTestCreateSinkAndUtilityContexts();
                        break;

                    case 160 :
                        result = doTestCreateSourceAndMDNSContexts();
                        break;

                    case 161 :
                        result = doTestCreateSourceAndNetworkingContexts();
                        break;

                    case 162 :
                        result = doTestCreateSourceAndFilterContexts();
                        break;

                    case 163 :
                        result = doTestCreateSourceAndMiscellaneousContexts();
                        break;

                    case 164 :
                        result = doTestCreateSourceAndServiceContexts();
                        break;

                    case 165 :
                        result = doTestCreateSourceAndSinkContexts();
                        break;

                    case 166 :
                        result = doTestCreateSourceAndSourceContexts();
                        break;

                    case 167 :
                        result = doTestCreateSourceAndTestContexts();
                        break;

                    case 168 :
                        result = doTestCreateSourceAndUtilityContexts();
                        break;

                    case 170 :
                        result = doTestCreateTestAndMDNSContexts();
                        break;

                    case 171 :
                        result = doTestCreateTestAndNetworkingContexts();
                        break;

                    case 172 :
                        result = doTestCreateTestAndFilterContexts();
                        break;

                    case 173 :
                        result = doTestCreateTestAndMiscellaneousContexts();
                        break;

                    case 174 :
                        result = doTestCreateTestAndServiceContexts();
                        break;

                    case 175 :
                        result = doTestCreateTestAndSinkContexts();
                        break;

                    case 176 :
                        result = doTestCreateTestAndSourceContexts();
                        break;

                    case 177 :
                        result = doTestCreateTestAndTestContexts();
                        break;

                    case 178 :
                        result = doTestCreateTestAndUtilityContexts();
                        break;

                    case 180 :
                        result = doTestCreateUtilityAndMDNSContexts();
                        break;

                    case 181 :
                        result = doTestCreateUtilityAndNetworkingContexts();
                        break;

                    case 182 :
                        result = doTestCreateUtilityAndFilterContexts();
                        break;

                    case 183 :
                        result = doTestCreateUtilityAndMiscellaneousContexts();
                        break;

                    case 184 :
                        result = doTestCreateUtilityAndServiceContexts();
                        break;

                    case 185 :
                        result = doTestCreateUtilityAndSinkContexts();
                        break;

                    case 186 :
                        result = doTestCreateUtilityAndSourceContexts();
                        break;

                    case 187 :
                        result = doTestCreateUtilityAndTestContexts();
                        break;

                    case 188 :
                        result = doTestCreateUtilityAndUtilityContexts();
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

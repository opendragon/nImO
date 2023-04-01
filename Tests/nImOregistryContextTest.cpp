//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOregistryContextTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO registry.
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
//  Created:    2023-04-01
//
//--------------------------------------------------------------------------------------------------

#include "../Registry/nImOregistryContext.h"
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
 @brief The test driver for the unit tests of the %nImO registry. */

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

/*! @brief The first node name for testing. */
#define NODE_NAME_1 "blort"

/*! @brief The second node name for testing. */
#define NODE_NAME_2 "blurt"

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
    (const int  signal)
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
doTestCreateRegistryContext
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext aContext{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext);
        EnableWaitForRegistry();
        result = 0;
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryContext

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestKindOfContextForRegistryContext
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext         aContext{0, nullptr, ""};
        CPtr(ServiceContext)    asService = aContext.asServiceContext();
        CPtr(UtilityContext)    asUtility = aContext.asUtilityContext();

        if ((nullptr != asService) && (nullptr == asUtility))
        {
            result = 0;
        }
        EnableWaitForRegistry();
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestKindOfContextForRegistryContext

#if defined(__APPLE__)
# pragma mark *** Test Case 20 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndMDNSContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithMDNS aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndMDNSContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 21 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndNetworkingContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ContextWithNetworking   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndNetworkingContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 22 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndFilterContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            FilterContext   aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndFilterContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 23 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndMiscellaneousContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            MiscellaneousContext    aContext2("");

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndMiscellaneousContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 24 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 25 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndServiceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            ServiceContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndServiceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 26 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndSinkContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SinkContext aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndSinkContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 27 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndSourceContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            SourceContext   aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndSourceContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 28 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndTestContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext  aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            TestContext   aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndTestContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 29 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistryAndUtilityContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        RegistryContext aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            UtilityContext  aContext2{""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateRegistryAndUtilityContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 40 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMDNSAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        ContextWithMDNS aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMDNSAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 41 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateNetworkingAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        ContextWithNetworking   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateNetworkingAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 42 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateFilterAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        FilterContext   aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateFilterAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 43 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateMiscellaneousAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        MiscellaneousContext    aContext1("");

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateMiscellaneousAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 44 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSinkAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        SinkContext aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSinkAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 45 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateSourceAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        SourceContext   aContext1{0, nullptr, ""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateSourceAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 46 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateTestAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        TestContext   aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateTestAndRegistryContexts

#if defined(__APPLE__)
# pragma mark *** Test Case 47 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateUtilityAndRegistryContexts
    (void)
{
    int result = 1;

    ODL_ENTER(); //####
    try
    {
        DisableWaitForRegistry();
        UtilityContext  aContext1{""};

        NIMO_UNUSED_VAR_(aContext1);
        try
        {
            RegistryContext  aContext2{0, nullptr, ""};

            NIMO_UNUSED_VAR_(aContext2);
            EnableWaitForRegistry();
        }
        catch (...)
        {
            // A second Context should throw an exception.
            ODL_LOG("Exception caught"); //####
            EnableWaitForRegistry();
            result = 0;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        EnableWaitForRegistry();
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCreateUtilityAndRegistryContexts

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
    int         result = 1;

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::ReportVersions();
    try
    {
        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestCreateRegistryContext();
                        break;

                    case 2 :
                        result = doTestKindOfContextForRegistryContext();
                        break;

                     case 20 :
                        result = doTestCreateRegistryAndMDNSContexts();
                        break;

                     case 21 :
                        result = doTestCreateRegistryAndNetworkingContexts();
                        break;

                     case 22 :
                        result = doTestCreateRegistryAndFilterContexts();
                        break;

                     case 23 :
                        result = doTestCreateRegistryAndMiscellaneousContexts();
                        break;

                     case 24 :
                        result = doTestCreateRegistryAndRegistryContexts();
                        break;

                     case 25 :
                        result = doTestCreateRegistryAndServiceContexts();
                        break;

                     case 26 :
                        result = doTestCreateRegistryAndSinkContexts();
                        break;

                     case 27 :
                        result = doTestCreateRegistryAndSourceContexts();
                        break;

                     case 28 :
                        result = doTestCreateRegistryAndTestContexts();
                        break;

                     case 29 :
                        result = doTestCreateRegistryAndUtilityContexts();
                        break;

                     case 40 :
                        result = doTestCreateMDNSAndRegistryContexts();
                        break;

                     case 41 :
                        result = doTestCreateNetworkingAndRegistryContexts();
                        break;

                     case 42 :
                        result = doTestCreateFilterAndRegistryContexts();
                        break;

                     case 43 :
                        result = doTestCreateMiscellaneousAndRegistryContexts();
                        break;

                     case 44 :
                        result = doTestCreateSinkAndRegistryContexts();
                        break;

                     case 45 :
                        result = doTestCreateSourceAndRegistryContexts();
                        break;

                     case 46 :
                        result = doTestCreateTestAndRegistryContexts();
                        break;

                     case 47 :
                        result = doTestCreateUtilityAndRegistryContexts();
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

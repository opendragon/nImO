//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOregistryTest.cpp
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
//  Created:    2023-01-26
//
//--------------------------------------------------------------------------------------------------

#include "../Registry/nImOregistry.h"
#include <nImOserviceContext.h>

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

/*! @brief The firsts machine address for testing. */
#define MACHINE_ADDRESS_1   IPV4_ADDR(192, 168, 100, 11)

/*! @brief The second machine address for testing. */
#define MACHINE_ADDRESS_2   IPV4_ADDR(192, 168, 100, 12)

/*! @brief The first machine name for testing. */
#define MACHINE_NAME_1 "Blort"

/*! @brief The second machine name for testing. */
#define MACHINE_NAME_2 "Blurt"

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
    std::string message{"exiting due to signal "};

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
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCreateRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // create empty Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
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
} // doTestCreateRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 02 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyRegistryForMachines
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for machines
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfMachines();

            if (statusWithInt.first.first)
            {
                if (0 == statusWithInt.second)
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == statusWithInt.second)"); //####
                }
            }
            else
            {
                ODL_LOG("! (statusWithInt.first.first)"); //####
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
} // doTestEmptyRegistryForMachines

#if defined(__APPLE__)
# pragma mark *** Test Case 03 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMachineSetWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfMachines();

            if (statusWithStrings.first.first)
            {
                StringSet   machines = statusWithStrings.second;

                if (machines.empty())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (machines.empty())"); //####
                }
            }
            else
            {
                ODL_LOG("! (statusWithStrings.first.first)"); //####
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
} // doTestMachineSetWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindMachineWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegBoolOrFailure  statusWithBool = aRegistry->isMachinePresent(MACHINE_NAME_1);

            if (statusWithBool.first.first)
            {
                if (statusWithBool.second)
                {
                    ODL_LOG("(statusWithBool.second)"); //####
                }
                else
                {
                    statusWithBool = aRegistry->isMachinePresent(MACHINE_NAME_2);
                    if (statusWithBool.first.first)
                    {
                        if (statusWithBool.second)
                        {
                            ODL_LOG("(statusWithBool.second)"); //####
                        }
                        else
                        {
                            result = 0;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithBool.first.first)"); //####
                    }
                }
            }
            else
            {
                ODL_LOG("! (statusWithBool.first.first)"); //####
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
} // doTestFindMachineWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddMachineToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);

            if (status.first)
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestAddMachineToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 06 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountMachinesWithRegistryWithOneMachine
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);

            if (status.first)
            {
                nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfMachines();

                if (statusWithInt.first.first)
                {
                    if (1 == statusWithInt.second)
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (1 == statusWithInt.second)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (statusWithInt.first.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountMachinesWithRegistryWithOneMachine

#if defined(__APPLE__)
# pragma mark *** Test Case 07 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestMachineSetWithRegistryWithOneMachine
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);

            if (status.first)
            {
                nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfMachines();

                if (statusWithStrings.first.first)
                {
                    StringSet   machines = statusWithStrings.second;

                    if (machines.end() == machines.find(MACHINE_NAME_1))
                    {
                        ODL_LOG("(machines.end() == machines.find(MACHINE_NAME_1))"); //####
                    }
                    else
                    {
                        result = 0;
                    }
                }
                else
                {
                    ODL_LOG("! (statusWithStrings.first.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestMachineSetWithRegistryWithOneMachine

#if defined(__APPLE__)
# pragma mark *** Test Case 08 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindMachineWithRegistryWithOneMachine
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);

            if (status.first)
            {
                nImO::RegBoolOrFailure  statusWithBool = aRegistry->isMachinePresent(MACHINE_NAME_1);

                if (statusWithBool.first.first)
                {
                    if (statusWithBool.second)
                    {
                        statusWithBool = aRegistry->isMachinePresent(MACHINE_NAME_2);
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("(statusWithBool.second)"); //####
                            }
                            else
                            {
                                result = 0;
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithBool.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithBool.second)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (statusWithBool.first.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestFindMachineWithRegistryWithOneMachine

#if defined(__APPLE__)
# pragma mark *** Test Case 09 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoDistinctMachinesToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);

            if (status.first)
            {
                status = aRegistry->addMachine(MACHINE_NAME_2, MACHINE_ADDRESS_2);
                if (status.first)
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestAddTwoDistinctMachinesToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountMachinesWithRegistryWithTwoMachines
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);

            if (status.first)
            {
                status = aRegistry->addMachine(MACHINE_NAME_2, MACHINE_ADDRESS_2);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfMachines();

                    if (statusWithInt.first.first)
                    {
                        if (2 == statusWithInt.second)
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (2 == statusWithInt.second)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInt.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountMachinesWithRegistryWithTwoMachines

#if defined(__APPLE__)
# pragma mark *** Test Case 11 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoIdenticalMachinesToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);

            if (status.first)
            {
                status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfMachines();

                    if (statusWithInt.first.first)
                    {
                        if (1 == statusWithInt.second)
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (1 == statusWithInt.second)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInt.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestAddTwoIdenticalMachinesToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestEmptyRegistryForNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodes();

            if (statusWithInt.first.first)
            {
                if (0 == statusWithInt.second)
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == statusWithInt.second)"); //####
                }
            }
            else
            {
                ODL_LOG("! (statusWithInt.first.first)"); //####
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
} // doTestEmptyRegistryForNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodes();

            if (statusWithStrings.first.first)
            {
                StringSet   nodes = statusWithStrings.second;

                if (nodes.empty())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (nodes.empty())"); //####
                }
            }
            else
            {
                ODL_LOG("! (statusWithStrings.first.first)"); //####
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
} // doTestNodeSetWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindNodeWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegBoolOrFailure  statusWithBool = aRegistry->isNodePresent(NODE_NAME_1);

            if (statusWithBool.first.first)
            {
                if (statusWithBool.second)
                {
                    ODL_LOG("(statusWithBool.second)"); //####
                }
                else
                {
                    statusWithBool = aRegistry->isNodePresent(NODE_NAME_2);
                    if (statusWithBool.first.first)
                    {
                        if (statusWithBool.second)
                        {
                            ODL_LOG("(statusWithBool.second)"); //####
                        }
                        else
                        {
                            result = 0;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithBool.first.first)"); //####
                    }
                }
            }
            else
            {
                ODL_LOG("! (statusWithBool.first.first)"); //####
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
} // doTestFindNodeWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 103 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddNodeToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                        nImO::ServiceType::GenericService);

                if (status.first)
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestAddNodeToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 104 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountNodesWithRegistryWithOneNode
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodes();

                    if (statusWithInt.first.first)
                    {
                        if (1 == statusWithInt.second)
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (1 == statusWithInt.second)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInt.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountNodesWithRegistryWithOneNode

#if defined(__APPLE__)
# pragma mark *** Test Case 105 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithRegistryWithOneNode
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodes();

                    if (statusWithStrings.first.first)
                    {
                        StringSet   nodes = statusWithStrings.second;

                        if (nodes.end() == nodes.find(NODE_NAME_1))
                        {
                            ODL_LOG("(nodes.end() == nodes.find(NODE_NAME_1))"); //####
                        }
                        else
                        {
                            result = 0;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithStrings.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeSetWithRegistryWithOneNode

#if defined(__APPLE__)
# pragma mark *** Test Case 106 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindNodeWithRegistryWithOneNode
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegBoolOrFailure  statusWithBool = aRegistry->isNodePresent(NODE_NAME_1);

                    if (statusWithBool.first.first)
                    {
                        if (statusWithBool.second)
                        {
                            statusWithBool = aRegistry->isNodePresent(NODE_NAME_2);
                            if (statusWithBool.first.first)
                            {
                                if (statusWithBool.second)
                                {
                                    ODL_LOG("(statusWithBool.second)"); //####
                                }
                                else
                                {
                                    result = 0;
                                }
                            }
                            else
                            {
                                ODL_LOG("! (statusWithBool.first.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithBool.second)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithBool.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestFindNodeWithRegistryWithOneNode

#if defined(__APPLE__)
# pragma mark *** Test Case 107 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeDataAddedToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress = nImO::RandomUnsigned();
            uint16_t                    randomPort = StaticCast(uint16_t, nImO::RandomUnsigned());
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName, randomAddress);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegNodeInfoOrFailure  statusWithInfo = aRegistry->getNodeInformation(NODE_NAME_1);

                    if (statusWithInfo.first.first)
                    {
                        if (statusWithInfo.second._found)
                        {
                            if ((statusWithInfo.second._name == NODE_NAME_1) && (randomAddress == statusWithInfo.second._connection._address) &&
                                (randomPort == statusWithInfo.second._connection._port) &&
                                (nImO::ServiceType::FilterService == statusWithInfo.second._serviceType))
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! ((statusWithInfo.second._name == NODE_NAME_1) && " //####
                                        "(randomAddress == statusWithInfo.second._connection._address) && " //####
                                        "(randomPort == statusWithInfo.second._connection._port) && " //####
                                        "(nImO::ServiceType::FilterService == statusWithInfo.second._serviceType))"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithInfo.second._found)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInfo.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeDataAddedToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 108 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveNodeFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove node from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(NODE_NAME_1);
                    if (status.first)
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestRemoveNodeFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 109 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountNodesWithRegistryWithNodeRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove node from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(NODE_NAME_1);
                    if (status.first)
                    {
                        nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodes();

                        if (statusWithInt.first.first)
                        {
                            if (0 == statusWithInt.second)
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! (0 == statusWithInt.second)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithInt.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountNodesWithRegistryWithNodeRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithRegistryWithNodeRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove node from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(NODE_NAME_1);
                    if (status.first)
                    {
                        nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodes();

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes = statusWithStrings.second;

                            if (nodes.empty())
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! (nodes.empty())"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithStrings.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeSetWithRegistryWithNodeRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindNodeWithRegistryNodeRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove node from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(NODE_NAME_1);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool = aRegistry->isNodePresent(NODE_NAME_1);

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("! (statusWithBool.first.first)"); //####
                            }
                            else
                            {
                                result = 0;
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithBool.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestFindNodeWithRegistryNodeRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoDistinctNodesToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestAddTwoDistinctNodesToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountNodesWithRegistryWithTwoNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodes();

                        if (statusWithInt.first.first)
                        {
                            if (2 == statusWithInt.second)
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! (2 == statusWithInt.second)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithInt.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountNodesWithRegistryWithTwoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 114 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithRegistryWithTwoNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodes();

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes = statusWithStrings.second;

                            if (nodes.end() == nodes.find(NODE_NAME_1))
                            {
                                ODL_LOG("(nodes.end() == nodes.find(NODE_NAME_1))"); //####
                            }
                            else
                            {
                                if (nodes.end() == nodes.find(NODE_NAME_2))
                                {
                                    ODL_LOG("(nodes.end() == nodes.find(NODE_NAME_2))"); //####
                                }
                                else
                                {
                                    result = 0;
                                }
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithStrings.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeSetWithRegistryWithTwoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 115 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindNodeWithRegistryWithTwoNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool = aRegistry->isNodePresent(NODE_NAME_1);

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                statusWithBool = aRegistry->isNodePresent(NODE_NAME_2);
                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("! (statusWithBool.second)"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (statusWithBool.first.first)"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (statusWithBool.second)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithBool.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestFindNodeWithRegistryWithTwoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 116 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveNodesFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove nodes from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(NODE_NAME_1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(NODE_NAME_2);
                            if (status.first)
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! (status.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (status.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestRemoveNodesFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 117 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountNodesWithRegistryWithAllNodesRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove nodes from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(NODE_NAME_1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(NODE_NAME_2);
                            if (status.first)
                            {
                                nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodes();

                                if (statusWithInt.first.first)
                                {
                                    if (0 == statusWithInt.second)
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("! (0 == statusWithInt.second)"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (statusWithInt.first.first)"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (status.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (status.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountNodesWithRegistryWithAllNodesRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 118 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithRegistryWithAllNodesRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove nodes from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(NODE_NAME_1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(NODE_NAME_2);
                            if (status.first)
                            {
                                nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodes();

                                if (statusWithStrings.first.first)
                                {
                                    StringSet   nodes = statusWithStrings.second;

                                    if (nodes.empty())
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("! (nodes.empty())"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (statusWithStrings.first.first)"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (status.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (status.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeSetWithRegistryWithAllNodesRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 119 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindNodeWithRegistryAllNodesRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove nodes from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(NODE_NAME_1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(NODE_NAME_2);
                            if (status.first)
                            {
                                nImO::RegBoolOrFailure  statusWithBool = aRegistry->isNodePresent(NODE_NAME_1);

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        ODL_LOG("(statusWithBool.second)"); //####
                                    }
                                    else
                                    {
                                        statusWithBool = aRegistry->isNodePresent(NODE_NAME_2);
                                        if (statusWithBool.first.first)
                                        {
                                            if (statusWithBool.second)
                                            {
                                                ODL_LOG("(statusWithBool.second)"); //####
                                            }
                                            else
                                            {
                                                result = 0;
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (statusWithBool.first.first)"); //####
                                        }
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (statusWithBool.first.first)"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (status.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (status.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestFindNodeWithRegistryAllNodesRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 120 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoIdenticalNodesToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two identical nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        ODL_LOG("(status.first)"); //####
                    }
                    else
                    {
                        nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodes();

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes = statusWithStrings.second;

                            if (nodes.end() == nodes.find(NODE_NAME_1))
                            {
                                ODL_LOG("(nodes.end() == nodes.find(NODE_NAME_1))"); //####
                            }
                            else
                            {
                                result = 0;
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithStrings.first.first)"); //####
                        }
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestAddTwoIdenticalNodesToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 121 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeInfoWithRegistryWithNoNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegNodeInfoVectorOrFailure    statusWithInformation = aRegistry->getInformationForAllNodes();

            if (statusWithInformation.first.first)
            {
                nImO::NodeInfoVector &  infoVector{statusWithInformation.second};

                if (0 == infoVector.size())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == infoVector.size())"); //####
                }
            }
            else
            {
                ODL_LOG("! (statusWithInformation.first.first)"); //####
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
} // doTestNodeInfoWithRegistryWithNoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 122 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeInfoWithRegistryWithOneNode
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress = nImO::RandomUnsigned();
            uint16_t                    randomPort = StaticCast(uint16_t, nImO::RandomUnsigned());
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName, randomAddress);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegNodeInfoVectorOrFailure    statusWithInformation = aRegistry->getInformationForAllNodes();

                    if (statusWithInformation.first.first)
                    {
                        nImO::NodeInfoVector &  infoVector{statusWithInformation.second};

                        if (1 == infoVector.size())
                        {
                            nImO::NodeInfo &    firstElem{infoVector[0]};

                            if ((firstElem._name == NODE_NAME_1) && (randomAddress == firstElem._connection._address) &&
                                (randomPort == firstElem._connection._port) && (nImO::ServiceType::FilterService == firstElem._serviceType))
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! ((firstElem._name == NODE_NAME_1) && (randomAddress == firstElem._connection._address) && " //####
                                        "(randomPort == firstElem._connection._port) && " //####
                                        "(nImO::ServiceType::FilterService == firstElem._serviceType))"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (1 == infoVector.size())"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInformation.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeInfoWithRegistryWithOneNode

#if defined(__APPLE__)
# pragma mark *** Test Case 123 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeInfoWithRegistryWithTwoNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress1 = StaticCast(uint32_t, nImO::RandomUnsigned());
            uint16_t                    randomPort1 = StaticCast(uint16_t, nImO::RandomUnsigned());
            std::string                 machineName1{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName1, randomAddress1);

            if (status.first)
            {
                std::string machineName2{machineName1 + "_1"};
                uint32_t    randomAddress2 = StaticCast(uint32_t, nImO::RandomUnsigned());

                status = aRegistry->addMachine(machineName2, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        uint16_t    randomPort2 = StaticCast(uint16_t, nImO::RandomUnsigned());

                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService,
                                                    nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            nImO::RegNodeInfoVectorOrFailure    statusWithInformation = aRegistry->getInformationForAllNodes();

                            if (statusWithInformation.first.first)
                            {
                                nImO::NodeInfoVector &  infoVector = statusWithInformation.second;

                                if (2 == infoVector.size())
                                {
                                    nImO::NodeInfo &    firstElem{infoVector[0]};
                                    nImO::NodeInfo &    secondElem{infoVector[1]};

                                    if (firstElem._name == NODE_NAME_1)
                                    {
                                        if (secondElem._name == NODE_NAME_2)
                                        {
                                            if ((randomAddress1 == firstElem._connection._address) && (randomPort1 == firstElem._connection._port) &&
                                                (nImO::ServiceType::FilterService == firstElem._serviceType) &&
                                                (randomAddress2 == secondElem._connection._address) &&
                                                (randomPort2 == secondElem._connection._port) &&
                                                (nImO::ServiceType::LauncherService == secondElem._serviceType))
                                            {
                                                result = 0;
                                            }
                                            else
                                            {
                                                ODL_LOG("! ((randomAddress1 == firstElem._connection._address) && " //####
                                                        "(randomPort1 == firstElem._connection._port) && " //####
                                                        "(nImO::ServiceType::FilterService == firstElem._serviceType) && " //####
                                                        "(randomAddress2 == secondElem._connection._address) && " //####
                                                        "(randomPort2 == secondElem._connection._port) && " //####
                                                        "(nImO::ServiceType::LauncherService == secondElem._serviceType))"); //####
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (secondElem._name == NODE_NAME_2)"); //####
                                        }
                                    }
                                    else if (secondElem._name == NODE_NAME_1)
                                    {
                                        if (firstElem._name == NODE_NAME_2)
                                        {
                                            if ((randomAddress2 == firstElem._connection._address) && (randomPort2 == firstElem._connection._port) &&
                                                (nImO::ServiceType::LauncherService == firstElem._serviceType) &&
                                                (randomAddress1 == secondElem._connection._address) &&
                                                (randomPort1 == secondElem._connection._port) &&
                                                (nImO::ServiceType::FilterService == secondElem._serviceType))
                                            {
                                                result = 0;
                                            }
                                            else
                                            {
                                                ODL_LOG("! ((randomAddress2 == firstElem._connection._address) && " //####
                                                        "(randomPort2 == firstElem._connection._port) && " //####
                                                        "(nImO::ServiceType::LauncherService == firstElem._serviceType) && " //####
                                                        "(randomAddress1 == secondElem._connection._address) && " //####
                                                        "(randomPort1 == secondElem._connection._port) && " //####
                                                        "(nImO::ServiceType::FilterService == secondElem._serviceType))"); //####
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (firstElem._name == NODE_NAME_2)"); //####
                                        }
                                    }
                                    else
                                    {
                                        ODL_LOG("! (secondElem._name == NODE_NAME_1)"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (2 == infoVector.size())"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (statusWithInformation.first.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (status.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeInfoWithRegistryWithTwoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 124 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLaunchDetailsWithRegistryWithNoNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegLaunchDetailsOrFailure    statusWithDetails = aRegistry->getLaunchDetails(NODE_NAME_1);

            if (statusWithDetails.first.first)
            {
                nImO::LaunchDetails details{statusWithDetails.second};

                if (! details._found)
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (! details._found)"); //####
                }
            }
            else
            {
                ODL_LOG("! (statusWithDetails.first.first)"); //####
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
} // doTestLaunchDetailsWithRegistryWithNoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 125 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLaunchDetailsWithRegistryWithOneNode
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress = nImO::RandomUnsigned();
            uint16_t                    randomPort = StaticCast(uint16_t, nImO::RandomUnsigned());
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName, randomAddress);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegLaunchDetailsOrFailure    statusWithDetails = aRegistry->getLaunchDetails(NODE_NAME_1);

                    if (statusWithDetails.first.first)
                    {
                        nImO::LaunchDetails details{statusWithDetails.second};

                        if (details._found)
                        {
                            if ((execPath == details._execPath) && (currentDir == details._launchDirectory) && (commandLine == details._commandLine))
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! ((execPath == details._execPath) && (currentDir == details._launchDirectory) && " //####
                                        "(commandLine == details._commandLine))"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (details._found)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithDetails.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestLaunchDetailsWithRegistryWithOneNode

#if defined(__APPLE__)
# pragma mark *** Test Case 126 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestLaunchDetailsWithRegistryWithTwoNodes
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress1 = StaticCast(uint32_t, nImO::RandomUnsigned());
            uint16_t                    randomPort1 = StaticCast(uint16_t, nImO::RandomUnsigned());
            std::string                 machineName1{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName1, randomAddress1);

            if (status.first)
            {
                std::string machineName2{machineName1 + "_1"};
                uint32_t    randomAddress2 = StaticCast(uint32_t, nImO::RandomUnsigned());

                status = aRegistry->addMachine(machineName2, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        uint16_t    randomPort2 = StaticCast(uint16_t, nImO::RandomUnsigned());

                        status = aRegistry->addNode(NODE_NAME_2, "!" + execPath, "?" + currentDir, "^" + commandLine,
                                                    nImO::ServiceType::LauncherService, nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            nImO::RegLaunchDetailsOrFailure    statusWithDetails = aRegistry->getLaunchDetails(NODE_NAME_1);

                            if (statusWithDetails.first.first)
                            {
                                nImO::LaunchDetails details1{statusWithDetails.second};

                                if (details1._found)
                                {
                                    if ((execPath == details1._execPath) && (currentDir == details1._launchDirectory) &&
                                        (commandLine == details1._commandLine))
                                    {
                                        statusWithDetails = aRegistry->getLaunchDetails(NODE_NAME_2);
                                        if (statusWithDetails.first.first)
                                        {
                                            nImO::LaunchDetails details2{statusWithDetails.second};

                                            if (details2._found)
                                            {
                                                if ((("!" + execPath) == details2._execPath) && (("?" + currentDir) == details2._launchDirectory) &&
                                                    (("^" + commandLine) == details2._commandLine))
                                                {
                                                    result = 0;
                                                }
                                                else
                                                {
                                                    ODL_LOG("! (((\"!\" + execPath) == details2._execPath) && " //####
                                                            "((\"?\" + currentDir) == details2._launchDirectory) && " //####
                                                            "((\"^\" + commandLine) == details2._commandLine))"); //####
                                                }
                                            }
                                            else
                                            {
                                                ODL_LOG("! (details2._found)"); //####
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (statusWithDetails.first.first)"); //####
                                        }
                                    }
                                    else
                                    {
                                        ODL_LOG("! ((execPath == details1._execPath) && (currentDir == details1._launchDirectory) && " //####
                                                "(commandLine == details1._commandLine))"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (details1._found)"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (statusWithDetails.first.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (status.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestLaunchDetailsWithRegistryWithTwoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 200 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithEmptyRegistryViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // check empty Registry for nodes
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodesOnMachine(machineName);

                if (statusWithStrings.first.first)
                {
                    StringSet   nodes = statusWithStrings.second;

                    if (nodes.empty())
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (nodes.empty())"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (statusWithStrings.first.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeSetWithEmptyRegistryViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 201 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithRegistryWithOneNodeViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodesOnMachine(machineName);

                    if (statusWithStrings.first.first)
                    {
                        StringSet   nodes = statusWithStrings.second;

                        if (nodes.end() == nodes.find(NODE_NAME_1))
                        {
                            ODL_LOG("(nodes.end() == nodes.find(NODE_NAME_1))"); //####
                        }
                        else
                        {
                            result = 0;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithStrings.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeSetWithRegistryWithOneNodeViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 202 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeSetWithRegistryWithTwoNodesViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegStringSetOrFailure statusWithStrings = aRegistry->getNamesOfNodesOnMachine(machineName);

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes = statusWithStrings.second;

                            if (nodes.end() == nodes.find(NODE_NAME_1))
                            {
                                ODL_LOG("(nodes.end() == nodes.find(NODE_NAME_1))"); //####
                            }
                            else
                            {
                                if (nodes.end() == nodes.find(NODE_NAME_2))
                                {
                                    ODL_LOG("(nodes.end() == nodes.find(NODE_NAME_2))"); //####
                                }
                                else
                                {
                                    result = 0;
                                }
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithStrings.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeSetWithRegistryWithTwoNodesViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 203 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeInfoWithRegistryWithEmptyRegistryViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                nImO::RegNodeInfoVectorOrFailure    statusWithInformation = aRegistry->getInformationForAllNodesOnMachine(machineName);

                if (statusWithInformation.first.first)
                {
                    nImO::NodeInfoVector &  infoVector{statusWithInformation.second};

                    if (0 == infoVector.size())
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == infoVector.size())"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (statusWithInformation.first.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeInfoWithRegistryWithEmptyRegistryViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 204 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeInfoWithRegistryWithOneNodeViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress = nImO::RandomUnsigned();
            uint16_t                    randomPort = StaticCast(uint16_t, nImO::RandomUnsigned());
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName, randomAddress);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegNodeInfoVectorOrFailure    statusWithInformation = aRegistry->getInformationForAllNodesOnMachine(machineName);

                    if (statusWithInformation.first.first)
                    {
                        nImO::NodeInfoVector &  infoVector{statusWithInformation.second};

                        if (1 == infoVector.size())
                        {
                            nImO::NodeInfo &    firstElem{infoVector[0]};

                            if ((firstElem._name == NODE_NAME_1) && (randomAddress == firstElem._connection._address) &&
                                (randomPort == firstElem._connection._port) && (nImO::ServiceType::FilterService == firstElem._serviceType))
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! ((firstElem._name == NODE_NAME_1) && (randomAddress == firstElem._connection._address) && " //####
                                        "(randomPort == firstElem._connection._port) && " //####
                                        "(nImO::ServiceType::FilterService == firstElem._serviceType))"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (1 == infoVector.size())"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInformation.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeInfoWithRegistryWithOneNodeViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 205 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeInfoWithRegistryWithTwoNodesViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress1 = StaticCast(uint32_t, nImO::RandomUnsigned());
            uint16_t                    randomPort1 = StaticCast(uint16_t, nImO::RandomUnsigned());
            std::string                 machineName1{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName1, randomAddress1);

            if (status.first)
            {
                std::string machineName2{machineName1 + "_1"};
                uint32_t    randomAddress2 = StaticCast(uint32_t, nImO::RandomUnsigned());

                status = aRegistry->addMachine(machineName2, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        uint16_t    randomPort2 = StaticCast(uint16_t, nImO::RandomUnsigned());

                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService,
                                                    nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            nImO::RegNodeInfoVectorOrFailure    statusWithInformation = aRegistry->getInformationForAllNodesOnMachine(machineName1);

                            if (statusWithInformation.first.first)
                            {
                                nImO::NodeInfoVector &  infoVector = statusWithInformation.second;

                                if (1 == infoVector.size())
                                {
                                    nImO::NodeInfo &    firstElem{infoVector[0]};

                                    if (firstElem._name == NODE_NAME_1)
                                    {
                                        if ((randomAddress1 == firstElem._connection._address) && (randomPort1 == firstElem._connection._port) &&
                                            (nImO::ServiceType::FilterService == firstElem._serviceType))
                                        {
                                            result = 0;
                                        }
                                        else
                                        {
                                            ODL_LOG("! ((randomAddress1 == firstElem._connection._address) && " //####
                                                    "(randomPort1 == firstElem._connection._port) && " //####
                                                    "(nImO::ServiceType::FilterService == firstElem._serviceType))"); //####
                                        }
                                    }
                                    else
                                    {
                                        ODL_LOG("! (firstElem._name == NODE_NAME_1)"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (1 == infoVector.size())"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (statusWithInformation.first.first)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (status.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestNodeInfoWithRegistryWithTwoNodesViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 206 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountNodesWithRegistryWithEmptyRegistryViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // remove nodes from Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    NIMO_UNUSED_ARG_(execPath);
    NIMO_UNUSED_ARG_(currentDir);
    NIMO_UNUSED_ARG_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodesOnMachine(machineName);

                if (statusWithInt.first.first)
                {
                    if (0 == statusWithInt.second)
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == statusWithInt.second)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (statusWithInt.first.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountNodesWithRegistryWithEmptyRegistryViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 207 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountNodesWithRegistryWithOneNodeViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add node to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodesOnMachine(machineName);

                    if (statusWithInt.first.first)
                    {
                        if (1 == statusWithInt.second)
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (1 == statusWithInt.second)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInt.first.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountNodesWithRegistryWithOneNodeViaMachineName

#if defined(__APPLE__)
# pragma mark *** Test Case 208 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountNodesWithRegistryWithTwoNodesViaMachineName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine) // add two distinct nodes to Registry
{
    int result = 1;

    NIMO_UNUSED_ARG_(launchPath);
    NIMO_UNUSED_ARG_(argc);
    NIMO_UNUSED_ARG_(argv);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status = aRegistry->addMachine(machineName);

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegIntOrFailure   statusWithInt = aRegistry->getNumberOfNodesOnMachine(machineName);

                        if (statusWithInt.first.first)
                        {
                            if (2 == statusWithInt.second)
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! (2 == statusWithInt.second)"); //####
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithInt.first.first)"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
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
} // doTestCountNodesWithRegistryWithTwoNodesViaMachineName

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
        nImO::SpContextWithNetworking   ourContext{new nImO::ServiceContext{argc, argv, progName}};

        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                std::string execPath{boost::dll::program_location().string()};
                std::string currentDir{boost::filesystem::current_path().string()};
                std::string commandLine{nImO::MakeStringFromComandLine(argc - 1, argv + 1)};

                SetSignalHandlers(catchSignal);
                switch (selector)
                {
                    case 1 :
                        result = doTestCreateRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 2 :
                        result = doTestEmptyRegistryForMachines(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 3 :
                        result = doTestMachineSetWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 4 :
                        result = doTestFindMachineWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 5 :
                        result = doTestAddMachineToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 6 :
                        result = doTestCountMachinesWithRegistryWithOneMachine(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 7 :
                        result = doTestMachineSetWithRegistryWithOneMachine(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 8 :
                        result = doTestFindMachineWithRegistryWithOneMachine(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 9 :
                        result = doTestAddTwoDistinctMachinesToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 10 :
                        result = doTestCountMachinesWithRegistryWithTwoMachines(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 11 :
                        result = doTestAddTwoIdenticalMachinesToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 100 :
                        result = doTestEmptyRegistryForNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 101 :
                        result = doTestNodeSetWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;
                        
                    case 102 :
                        result = doTestFindNodeWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 103 :
                        result = doTestAddNodeToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 104 :
                        result = doTestCountNodesWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 105 :
                        result = doTestNodeSetWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 106 :
                        result = doTestFindNodeWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 107 :
                        result = doTestNodeDataAddedToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 108 :
                        result = doTestRemoveNodeFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 109 :
                        result = doTestCountNodesWithRegistryWithNodeRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                             commandLine);
                        break;

                    case 110 :
                        result = doTestNodeSetWithRegistryWithNodeRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 111 :
                        result = doTestFindNodeWithRegistryNodeRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 112 :
                        result = doTestAddTwoDistinctNodesToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 113 :
                        result = doTestCountNodesWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 114 :
                        result = doTestNodeSetWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 115 :
                        result = doTestFindNodeWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 116 :
                        result = doTestRemoveNodesFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 117 :
                        result = doTestCountNodesWithRegistryWithAllNodesRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                 commandLine);
                        break;

                    case 118 :
                        result = doTestNodeSetWithRegistryWithAllNodesRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                              commandLine);
                        break;

                    case 119 :
                        result = doTestFindNodeWithRegistryAllNodesRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 120 :
                        result = doTestAddTwoIdenticalNodesToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 121 :
                        result = doTestNodeInfoWithRegistryWithNoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 122 :
                        result = doTestNodeInfoWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 123 :
                        result = doTestNodeInfoWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 124 :
                        result = doTestLaunchDetailsWithRegistryWithNoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 125 :
                        result = doTestLaunchDetailsWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 126 :
                        result = doTestLaunchDetailsWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                             commandLine);
                        break;

                    case 200 :
                        result = doTestNodeSetWithEmptyRegistryViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                              commandLine);
                        break;

                    case 201 :
                        result = doTestNodeSetWithRegistryWithOneNodeViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                    commandLine);
                        break;

                    case 202 :
                        result = doTestNodeSetWithRegistryWithTwoNodesViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                     commandLine);
                        break;

                    case 203 :
                        result = doTestNodeInfoWithRegistryWithEmptyRegistryViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                           currentDir, commandLine);
                        break;

                    case 204 :
                        result = doTestNodeInfoWithRegistryWithOneNodeViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                     commandLine);
                        break;

                    case 205 :
                        result = doTestNodeInfoWithRegistryWithTwoNodesViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                      commandLine);
                        break;

                    case 206 :
                        result = doTestCountNodesWithRegistryWithEmptyRegistryViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                             currentDir, commandLine);
                        break;

                    case 207 :
                        result = doTestCountNodesWithRegistryWithOneNodeViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                       commandLine);
                        break;

                    case 208 :
                        result = doTestCountNodesWithRegistryWithTwoNodesViaMachineName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                        commandLine);
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

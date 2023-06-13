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
#include <Contexts/nImOserviceContext.h>
#include <nImOchannelName.h>

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

/*! @brief The first channel path for testing. */
#define CHANNEL_PATH_1  "/blart/input/1"

/*! @brief The second channel path for testing. */
#define CHANNEL_PATH_2  "/blert/output/2"

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
    ODL_ENTER(); //####
    ODL_I1("signal = ", signal); //####
    std::string message{"exiting due to signal " + std::to_string(signal) + " = " + NameOfSignal(signal)};

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
doTestCreateRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfMachines()};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfMachines()};

            if (statusWithStrings.first.first)
            {
                StringSet   machines{statusWithStrings.second};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegBoolOrFailure  statusWithBool{aRegistry->isMachinePresent(MACHINE_NAME_1)};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1)};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1)};

            if (status.first)
            {
                nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfMachines()};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1)};

            if (status.first)
            {
                nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfMachines()};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1)};

            if (status.first)
            {
                nImO::RegBoolOrFailure  statusWithBool{aRegistry->isMachinePresent(MACHINE_NAME_1)};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1)};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1)};

            if (status.first)
            {
                status = aRegistry->addMachine(MACHINE_NAME_2, MACHINE_ADDRESS_2);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfMachines()};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1)};

            if (status.first)
            {
                status = aRegistry->addMachine(MACHINE_NAME_1, MACHINE_ADDRESS_1);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfMachines()};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodes()};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodes()};

            if (statusWithStrings.first.first)
            {
                StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegBoolOrFailure  statusWithBool{aRegistry->isNodePresent(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodes()};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodes()};

                    if (statusWithStrings.first.first)
                    {
                        StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegBoolOrFailure  statusWithBool{aRegistry->isNodePresent(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress{nImO::RandomUnsigned()};
            uint16_t                    randomPort{StaticCast(uint16_t, nImO::RandomUnsigned())};
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName, randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegNodeInfoOrFailure  statusWithInfo{aRegistry->getNodeInformation(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(NODE_NAME_1);
                    if (status.first)
                    {
                        nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodes()};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(NODE_NAME_1);
                    if (status.first)
                    {
                        nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodes()};

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(NODE_NAME_1);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->isNodePresent(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodes()};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodes()};

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->isNodePresent(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

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
                                nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodes()};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

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
                                nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodes()};

                                if (statusWithStrings.first.first)
                                {
                                    StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

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
                                nImO::RegBoolOrFailure  statusWithBool{aRegistry->isNodePresent(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

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
                        nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodes()};

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegNodeInfoVectorOrFailure    statusWithInformation{aRegistry->getInformationForAllNodes()};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress{nImO::RandomUnsigned()};
            uint16_t                    randomPort{StaticCast(uint16_t, nImO::RandomUnsigned())};
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName, randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegNodeInfoVectorOrFailure    statusWithInformation{aRegistry->getInformationForAllNodes()};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress1{StaticCast(uint32_t, nImO::RandomUnsigned())};
            uint16_t                    randomPort1{StaticCast(uint16_t, nImO::RandomUnsigned())};
            std::string                 machineName1{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName1, randomAddress1)};

            if (status.first)
            {
                std::string machineName2{machineName1 + "_1"};
                uint32_t    randomAddress2{StaticCast(uint32_t, nImO::RandomUnsigned())};

                status = aRegistry->addMachine(machineName2, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        uint16_t    randomPort2{StaticCast(uint16_t, nImO::RandomUnsigned())};

                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService,
                                                    nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            nImO::RegNodeInfoVectorOrFailure    statusWithInformation{aRegistry->getInformationForAllNodes()};

                            if (statusWithInformation.first.first)
                            {
                                nImO::NodeInfoVector &  infoVector{statusWithInformation.second};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegLaunchDetailsOrFailure    statusWithDetails{aRegistry->getLaunchDetails(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress{nImO::RandomUnsigned()};
            uint16_t                    randomPort{StaticCast(uint16_t, nImO::RandomUnsigned())};
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName, randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegLaunchDetailsOrFailure    statusWithDetails{aRegistry->getLaunchDetails(NODE_NAME_1)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress1{StaticCast(uint32_t, nImO::RandomUnsigned())};
            uint16_t                    randomPort1{StaticCast(uint16_t, nImO::RandomUnsigned())};
            std::string                 machineName1{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName1, randomAddress1)};

            if (status.first)
            {
                std::string machineName2{machineName1 + "_1"};
                uint32_t    randomAddress2{StaticCast(uint32_t, nImO::RandomUnsigned())};

                status = aRegistry->addMachine(machineName2, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        uint16_t    randomPort2{StaticCast(uint16_t, nImO::RandomUnsigned())};

                        status = aRegistry->addNode(NODE_NAME_2, "!" + execPath, "?" + currentDir, "^" + commandLine,
                                                    nImO::ServiceType::LauncherService, nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            nImO::RegLaunchDetailsOrFailure    statusWithDetails{aRegistry->getLaunchDetails(NODE_NAME_1)};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodesOnMachine(machineName)};

                if (statusWithStrings.first.first)
                {
                    StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodesOnMachine(machineName)};

                    if (statusWithStrings.first.first)
                    {
                        StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegStringSetOrFailure statusWithStrings{aRegistry->getNamesOfNodesOnMachine(machineName)};

                        if (statusWithStrings.first.first)
                        {
                            StringSet   nodes{statusWithStrings.second};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                nImO::RegNodeInfoVectorOrFailure    statusWithInformation{aRegistry->getInformationForAllNodesOnMachine(machineName)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress{nImO::RandomUnsigned()};
            uint16_t                    randomPort{StaticCast(uint16_t, nImO::RandomUnsigned())};
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName, randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    nImO::RegNodeInfoVectorOrFailure    statusWithInformation{aRegistry->getInformationForAllNodesOnMachine(machineName)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            uint32_t                    randomAddress1{StaticCast(uint32_t, nImO::RandomUnsigned())};
            uint16_t                    randomPort1{StaticCast(uint16_t, nImO::RandomUnsigned())};
            std::string                 machineName1{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName1, randomAddress1)};

            if (status.first)
            {
                std::string machineName2{machineName1 + "_1"};
                uint32_t    randomAddress2{StaticCast(uint32_t, nImO::RandomUnsigned())};

                status = aRegistry->addMachine(machineName2, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        uint16_t    randomPort2{StaticCast(uint16_t, nImO::RandomUnsigned())};

                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService,
                                                    nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            nImO::RegNodeInfoVectorOrFailure    statusWithInformation{aRegistry->getInformationForAllNodesOnMachine(machineName1)};

                            if (statusWithInformation.first.first)
                            {
                                nImO::NodeInfoVector &  infoVector{statusWithInformation.second};

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
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodesOnMachine(machineName)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodesOnMachine(machineName)};

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
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfNodesOnMachine(machineName)};

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
# pragma mark *** Test Case 300 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountChannelsWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfChannels()};

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
} // doTestCountChannelsWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 301 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindChannelWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegBoolOrFailure  statusWithBool{aRegistry->isChannelPresent(NODE_NAME_1, CHANNEL_PATH_1)};

            if (statusWithBool.first.first)
            {
                if (statusWithBool.second)
                {
                    ODL_LOG("(statusWithBool.second)"); //####
                }
                else
                {
                    statusWithBool = aRegistry->isChannelPresent(NODE_NAME_2, CHANNEL_PATH_2);
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
} // doTestFindChannelWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 302 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddChannelToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kAny);
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
} // doTestAddChannelToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 303 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountChannelsInRegistryWithOneChannel
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfChannels()};

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
} // doTestCountChannelsInRegistryWithOneChannel

#if defined(__APPLE__)
# pragma mark *** Test Case 304 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindChannelInRegistryWithOneChannel
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->isChannelPresent(NODE_NAME_1, CHANNEL_PATH_1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                statusWithBool = aRegistry->isChannelPresent(NODE_NAME_2, CHANNEL_PATH_2);
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
} // doTestFindChannelInRegistryWithOneChannel

#if defined(__APPLE__)
# pragma mark *** Test Case 305 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoChannelsToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(NODE_NAME_2, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kTCP);
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
} // doTestAddTwoChannelsToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 306 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountChannelsInRegistryWithTwoChannels
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(NODE_NAME_2, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kAny);
                            if (status.first)
                            {
                                nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfChannels()};

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
} // doTestCountChannelsInRegistryWithTwoChannels

#if defined(__APPLE__)
# pragma mark *** Test Case 307 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindChannelsInRegistryWithTwoChannels
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kTCP);
                    if (status.first)
                    {

                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(NODE_NAME_2, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kUDP);
                            if (status.first)
                            {
                                nImO::RegBoolOrFailure  statusWithBool{aRegistry->isChannelPresent(NODE_NAME_1, CHANNEL_PATH_1)};

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        statusWithBool = aRegistry->isChannelPresent(NODE_NAME_2, CHANNEL_PATH_2);
                                        if (statusWithBool.first.first)
                                        {
                                            if (statusWithBool.second)
                                            {
                                                result = 0;
                                            }
                                            else
                                            {
                                                ODL_LOG("(statusWithBool.second)"); //####
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
} // doTestFindChannelsInRegistryWithTwoChannels

#if defined(__APPLE__)
# pragma mark *** Test Case 308 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoIdenticalChannelsToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, true, "only-blort", nImO::TransportType::kTCP);
                        if (status.first)
                        {
                            ODL_LOG("(status.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestAddTwoIdenticalChannelsToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 309 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddChannelWithBadNodeNameToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_2, "/arbitrary_path", false, "", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        ODL_LOG("(status.first)"); //####
                    }
                    else
                    {
                        result = 0;
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
} // doTestAddChannelWithBadNodeNameToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 310 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddChannelWithBadChannelNameToRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, "/arbitrary&path", false, "", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        ODL_LOG("(status.first)"); //####
                    }
                    else
                    {
                        result = 0;
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
} // doTestAddChannelWithBadChannelNameToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 311 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveAllChannelsFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannelsForNode(NODE_NAME_1);
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
} // doTestRemoveAllChannelsFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 312 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountChannelsWithRegistryWithAllChannelsRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kTCP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannelsForNode(NODE_NAME_1);
                            if (status.first)
                            {
                                nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfChannels()};

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
} // doTestCountChannelsWithRegistryWithAllChannelsRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 313 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindChannelWithRegistryAllChannelsRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kAny);
                        if (status.first)
                        {
                            status = aRegistry->removeChannelsForNode(NODE_NAME_1);
                            if (status.first)
                            {
                                nImO::RegBoolOrFailure  statusWithBool{aRegistry->isChannelPresent(NODE_NAME_1, CHANNEL_PATH_1)};

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        ODL_LOG("(statusWithBool.second)"); //####
                                    }
                                    else
                                    {
                                        statusWithBool = aRegistry->isChannelPresent(NODE_NAME_1, CHANNEL_PATH_2);
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
} // doTestFindChannelWithRegistryAllChannelsRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 314 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveOneChannelFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannel(NODE_NAME_1, CHANNEL_PATH_1);
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
} // doTestRemoveOneChannelFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 315 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountChannelsWithRegistryWithOneChannelRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kTCP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannel(NODE_NAME_1, CHANNEL_PATH_1);
                            if (status.first)
                            {
                                nImO::RegIntOrFailure   statusWithInt{aRegistry->getNumberOfChannels()};

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
} // doTestCountChannelsWithRegistryWithOneChannelRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 316 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindChannelWithRegistryOneChannelRemoved
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kAny);
                        if (status.first)
                        {
                            status = aRegistry->removeChannel(NODE_NAME_1, CHANNEL_PATH_1);
                            if (status.first)
                            {
                                nImO::RegBoolOrFailure  statusWithBool{aRegistry->isChannelPresent(NODE_NAME_1, CHANNEL_PATH_1)};

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        ODL_LOG("(statusWithBool.second)"); //####
                                    }
                                    else
                                    {
                                        statusWithBool = aRegistry->isChannelPresent(NODE_NAME_1, CHANNEL_PATH_2);
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
} // doTestFindChannelWithRegistryOneChannelRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 317 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveNonexistentChannelFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->removeChannel(NODE_NAME_1, CHANNEL_PATH_2);
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestRemoveNonexistentChannelFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 318 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveChannelFromNonexistentNodeFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->removeChannel(NODE_NAME_2, CHANNEL_PATH_1);
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestRemoveChannelFromNonexistentNodeFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 320 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInfoFromEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegChannelInfoOrFailure   statusWithInfo{aRegistry->getChannelInformation(NODE_NAME_1, CHANNEL_PATH_1)};

            if (statusWithInfo.first.first)
            {
                if (statusWithInfo.second._found)
                {
                    ODL_LOG("(statusWithInfo.second._found)"); //####
                }
                else
                {
                    result = 0;
                }
            }
            else
            {
                ODL_LOG("! (statusWithInfo.first.first)"); //####
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
} // doTestGetChannelInfoFromEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 321 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInfoFromRegistryWithOneChannel
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        nImO::RegChannelInfoOrFailure   statusWithInfo{aRegistry->getChannelInformation(NODE_NAME_1, CHANNEL_PATH_1)};

                        if (statusWithInfo.first.first)
                        {
                            if (statusWithInfo.second._found)
                            {
                                if ((statusWithInfo.second._node == NODE_NAME_1) && (statusWithInfo.second._path == CHANNEL_PATH_1) &&
                                    (! statusWithInfo.second._isOutput) && (statusWithInfo.second._dataType == "<chuckles>") &&
                                    (nImO::TransportType::kAny == statusWithInfo.second._modes))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("((statusWithInfo.second._node == NODE_NAME_1) && " //####
                                            "(statusWithInfo.second._path == CHANNEL_PATH_1) && " //####
                                            "(! statusWithInfo.second._isOutput) && " //####
                                            "(statusWithInfo.second._dataType == \"<chuckles>\") && " //####
                                            "(nImO::TransportType::kAny == statusWithInfo.second._modes))"); //####
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
} // doTestGetChannelInfoFromRegistryWithOneChannel

#if defined(__APPLE__)
# pragma mark *** Test Case 322 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInfoFromRegistryWithTwoChannels
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(NODE_NAME_2, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kUDP);
                            if (status.first)
                            {
                                nImO::RegChannelInfoOrFailure   statusWithInfo{aRegistry->getChannelInformation(NODE_NAME_1, CHANNEL_PATH_1)};

                                if (statusWithInfo.first.first)
                                {
                                    if (statusWithInfo.second._found)
                                    {
                                        if ((statusWithInfo.second._node == NODE_NAME_1) && (statusWithInfo.second._path == CHANNEL_PATH_1) &&
                                            (! statusWithInfo.second._isOutput) && (statusWithInfo.second._dataType == "<chuckles>") &&
                                            (nImO::TransportType::kTCP == statusWithInfo.second._modes))
                                        {
                                            statusWithInfo = aRegistry->getChannelInformation(NODE_NAME_2, CHANNEL_PATH_2);
                                            if (statusWithInfo.first.first)
                                            {
                                                if (statusWithInfo.second._found)
                                                {
                                                    if ((statusWithInfo.second._node == NODE_NAME_2) &&
                                                        (statusWithInfo.second._path == CHANNEL_PATH_2) &&
                                                        statusWithInfo.second._isOutput && (statusWithInfo.second._dataType == "only-blort") &&
                                                        (nImO::TransportType::kUDP == statusWithInfo.second._modes))
                                                    {
                                                        result = 0;
                                                    }
                                                    else
                                                    {
                                                        ODL_LOG("((statusWithInfo.second._node == NODE_NAME_2) && "  //####
                                                                "(statusWithInfo.second._path == CHANNEL_PATH_2) && "  //####
                                                                "statusWithInfo.second._isOutput && "  //####
                                                                "(statusWithInfo.second._dataType == \"only-blort\") && " //####
                                                                "(nImO::TransportType::kUDP == statusWithInfo.second._modes))"); //####
                                                    }
                                                }
                                                else
                                                {
                                                    ODL_LOG("! (statusWithInfo.second._found)"); //####
                                                }
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("((statusWithInfo.second._node == NODE_NAME_1) && " //####
                                                    "(statusWithInfo.second._path == CHANNEL_PATH_1) && " //####
                                                    "(! statusWithInfo.second._isOutput) && " //####
                                                    "(statusWithInfo.second._dataType == \"<chuckles>\") && " //####
                                                    "(nImO::TransportType::kTCP == statusWithInfo.second._modes))"); //####
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
} // doTestGetChannelInfoFromRegistryWithTwoChannels

#if defined(__APPLE__)
# pragma mark *** Test Case 323 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInfoWithBadNodeNameFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    {
                        nImO::RegChannelInfoOrFailure   statusWithInfo{aRegistry->getChannelInformation(NODE_NAME_2, "/arbitrary_path")};

                        if (statusWithInfo.first.first)
                        {
                            if (statusWithInfo.second._found)
                            {
                                ODL_LOG("(statusWithInfo.second._found)"); //####
                            }
                            else
                            {
                                result = 0;
                            }
                        }
                        else
                        {
                            ODL_LOG("! (statusWithInfo.first.first)"); //####
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
} // doTestGetChannelInfoWithBadNodeNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 324 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInfoWithBadChannelNameFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    nImO::RegChannelInfoOrFailure   statusWithInfo{aRegistry->getChannelInformation(NODE_NAME_1, "/arbitrary&path")};

                    if (statusWithInfo.first.first)
                    {
                        ODL_LOG("(statusWithInfo.first.first)"); //####
                    }
                    else
                    {
                        result = 0;
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
} // doTestGetChannelInfoWithBadChannelNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 340 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetFromEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegChannelInfoVectorOrFailure statusWithInformation{aRegistry->getInformationForAllChannels()};

            if (statusWithInformation.first.first)
            {
                nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

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
} // doTestGetChannelSetFromEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 341 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetForNodeFromRegistryWithOneChannel
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        nImO::RegChannelInfoVectorOrFailure statusWithInformation{aRegistry->getInformationForAllChannels()};

                        if (statusWithInformation.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

                            if (1 == infoVector.size())
                            {
                                const ChannelInfo & theChannel{infoVector[0]};

                                if (theChannel._found && (theChannel._node == NODE_NAME_1) && (theChannel._path == CHANNEL_PATH_1) &&
                                    (! theChannel._isOutput) && (theChannel._dataType == "<chuckles>") &&
                                    (nImO::TransportType::kAny == theChannel._modes) && (! theChannel._inUse))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("(theChannel._found && (theChannel._node == NODE_NAME_1) && " //####
                                            "(theChannel._path == CHANNEL_PATH_1) && (! theChannel._isOutput) && " //####
                                            "(theChannel._dataType == \"<chuckles>\") && " //####
                                            "(nImO::TransportType::kAny == theChannel._modes) && (! theChannel._inUse))"); //####
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestGetChannelSetForNodeFromRegistryWithOneChannel

#if defined(__APPLE__)
# pragma mark *** Test Case 342 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetForNodeFromRegistryWithTwoChannels
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            nImO::RegChannelInfoVectorOrFailure statusWithInformation{aRegistry->getInformationForAllChannels()};

                            if (statusWithInformation.first.first)
                            {
                                nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

                                if (2 == infoVector.size())
                                {
                                    const ChannelInfo & theChannel1{infoVector[0]};
                                    const ChannelInfo & theChannel2{infoVector[1]};

                                    if (theChannel1._found && (theChannel1._node == NODE_NAME_1) && (theChannel1._path == CHANNEL_PATH_1) &&
                                        (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>") &&
                                        (nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                        (theChannel2._node == NODE_NAME_1) && (theChannel2._path == CHANNEL_PATH_2) && theChannel2._isOutput &&
                                        (theChannel2._dataType == "only-blort") && (nImO::TransportType::kUDP == theChannel2._modes) &&
                                        (! theChannel2._inUse))
                                    {
                                        result = 0;
                                    }
                                    else if (theChannel2._found && (theChannel2._node == NODE_NAME_1) && (theChannel2._path == CHANNEL_PATH_1) &&
                                             (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>") &&
                                             (nImO::TransportType::kTCP == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                             (theChannel1._node == NODE_NAME_1) && (theChannel1._path == CHANNEL_PATH_2) &&
                                             theChannel1._isOutput && (theChannel1._dataType == "only-blort") &&
                                             (nImO::TransportType::kUDP == theChannel1._modes) && (! theChannel1._inUse))
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("(theChannel2._found && (theChannel2._node == NODE_NAME_1) && " //####
                                                "(theChannel2._path == CHANNEL_PATH_1) && (! theChannel2._isOutput) && " //####
                                                "(theChannel2._dataType == \"<chuckles>\") && " //####
                                                "(nImO::TransportType::kTCP == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                "theChannel1._found && (theChannel1._node == NODE_NAME_1) && " //####
                                                "(theChannel1._path == CHANNEL_PATH_2) && theChannel1._isOutput && " //####
                                                "(theChannel1._dataType == \"only-blort\") && " //####
                                                "(nImO::TransportType::kUDP == theChannel1._modes) && (! theChannel1._inUse))"); //####
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
} // doTestGetChannelSetForNodeFromRegistryWithTwoChannels

#if defined(__APPLE__)
# pragma mark *** Test Case 343 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetForNodesFromRegistryWithTwoNodesWithChannels
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kAny);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(NODE_NAME_2, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                nImO::RegChannelInfoVectorOrFailure statusWithInformation{aRegistry->getInformationForAllChannels()};

                                if (statusWithInformation.first.first)
                                {
                                    nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

                                    if (2 == infoVector.size())
                                    {
                                        const ChannelInfo & theChannel1{infoVector[0]};
                                        const ChannelInfo & theChannel2{infoVector[1]};

                                        if (theChannel1._found && (theChannel1._node == NODE_NAME_1) && (theChannel1._path == CHANNEL_PATH_1) &&
                                            (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>") &&
                                            (nImO::TransportType::kAny == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                            (theChannel2._node == NODE_NAME_2) && (theChannel2._path == CHANNEL_PATH_2) && theChannel2._isOutput &&
                                            (theChannel2._dataType == "only-blort") && (nImO::TransportType::kTCP == theChannel2._modes) &&
                                            (! theChannel2._inUse))
                                        {
                                            result = 0;
                                        }
                                        else if (theChannel2._found && (theChannel2._node == NODE_NAME_1) && (theChannel2._path == CHANNEL_PATH_1) &&
                                                 (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>") &&
                                                 (nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                                 (theChannel1._node == NODE_NAME_2) && (theChannel1._path == CHANNEL_PATH_2) &&
                                                 theChannel1._isOutput && (theChannel1._dataType == "only-blort") &&
                                                 (nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse))
                                        {
                                            result = 0;
                                        }
                                        else
                                        {
                                            ODL_LOG("(theChannel2._found && (theChannel2._node == NODE_NAME_1) && " //####
                                                    "(theChannel2._path == CHANNEL_PATH_1) && (! theChannel2._isOutput) && " //####
                                                    "(theChannel2._dataType == \"<chuckles>\") && " //####
                                                    "(nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                    "theChannel1._found && (theChannel1._node == NODE_NAME_2) && " //####
                                                    "(theChannel1._path == CHANNEL_PATH_2) && theChannel1._isOutput && " //####
                                                    "(theChannel1._dataType == \"only-blort\") && " //####
                                                    "(nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse))"); //####
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
} // doTestGetChannelSetForNodesFromRegistryWithTwoNodesWithChannels

#if defined(__APPLE__)
# pragma mark *** Test Case 344 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetForMachineFromRegistryWithOneChannel
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegChannelInfoVectorOrFailure statusWithInformation{aRegistry->getInformationForAllChannelsOnMachine(machineName)};

                        if (statusWithInformation.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

                            if (1 == infoVector.size())
                            {
                                const ChannelInfo & theChannel{infoVector[0]};

                                if (theChannel._found && (theChannel._node == NODE_NAME_1) && (theChannel._path == CHANNEL_PATH_1) &&
                                    (! theChannel._isOutput) && (theChannel._dataType == "<chuckles>") &&
                                    (nImO::TransportType::kUDP == theChannel._modes) && (! theChannel._inUse))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("(theChannel._found && (theChannel._node == NODE_NAME_1) && " //####
                                            "(theChannel._path == CHANNEL_PATH_1) && (! theChannel._isOutput) && " //####
                                            "(theChannel._dataType == \"<chuckles>\") && " //####
                                            "(nImO::TransportType::kUDP == theChannel._modes) && (! theChannel._inUse))"); //####
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestGetChannelSetForMachineFromRegistryWithOneChannel

#if defined(__APPLE__)
# pragma mark *** Test Case 345 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetForMachineFromRegistryWithTwoChannels
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kTCP);
                        if (status.first)
                        {
                            nImO::RegChannelInfoVectorOrFailure statusWithInformation{aRegistry->getInformationForAllChannelsOnMachine(machineName)};

                            if (statusWithInformation.first.first)
                            {
                                nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

                                if (2 == infoVector.size())
                                {
                                    const ChannelInfo & theChannel1{infoVector[0]};
                                    const ChannelInfo & theChannel2{infoVector[1]};

                                    if (theChannel1._found && (theChannel1._node == NODE_NAME_1) && (theChannel1._path == CHANNEL_PATH_1) &&
                                        (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>") &&
                                        (nImO::TransportType::kAny == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                        (theChannel2._node == NODE_NAME_1) && (theChannel2._path == CHANNEL_PATH_2) && theChannel2._isOutput &&
                                        (theChannel2._dataType == "only-blort") && (nImO::TransportType::kTCP == theChannel2._modes) &&
                                        (! theChannel2._inUse))
                                    {
                                        result = 0;
                                    }
                                    else if (theChannel2._found && (theChannel2._node == NODE_NAME_1) && (theChannel2._path == CHANNEL_PATH_1) &&
                                             (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>") &&
                                             (nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                             (theChannel1._node == NODE_NAME_1) && (theChannel1._path == CHANNEL_PATH_2) &&
                                             theChannel1._isOutput && (theChannel1._dataType == "only-blort") &&
                                             (nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse))
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("(theChannel2._found && (theChannel2._node == NODE_NAME_1) && " //####
                                                "(theChannel2._path == CHANNEL_PATH_1) && (! theChannel2._isOutput) && " //####
                                                "(theChannel2._dataType == \"<chuckles>\") && " //####
                                                "(nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                "theChannel1._found && (theChannel1._node == NODE_NAME_1) && " //####
                                                "(theChannel1._path == CHANNEL_PATH_2) && theChannel1._isOutput && " //####
                                                "(theChannel1._dataType == \"only-blort\") && " //####
                                                "(nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse))"); //####
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
} // doTestGetChannelSetForMachineFromRegistryWithTwoChannels

#if defined(__APPLE__)
# pragma mark *** Test Case 346 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetForMachineFromRegistryWithTwoNodesWithChannels
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(NODE_NAME_2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(NODE_NAME_2, CHANNEL_PATH_2, true, "only-blort", nImO::TransportType::kAny);
                            if (status.first)
                            {
                                nImO::RegChannelInfoVectorOrFailure
                                                                statusWithInformation{aRegistry->getInformationForAllChannelsOnMachine(machineName)};

                                if (statusWithInformation.first.first)
                                {
                                    nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

                                    if (2 == infoVector.size())
                                    {
                                        const ChannelInfo & theChannel1{infoVector[0]};
                                        const ChannelInfo & theChannel2{infoVector[1]};

                                        if (theChannel1._found && (theChannel1._node == NODE_NAME_1) && (theChannel1._path == CHANNEL_PATH_1) &&
                                            (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>") &&
                                            (nImO::TransportType::kUDP == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                            (theChannel2._node == NODE_NAME_2) && (theChannel2._path == CHANNEL_PATH_2) && theChannel2._isOutput &&
                                            (theChannel2._dataType == "only-blort") && (nImO::TransportType::kAny == theChannel2._modes) &&
                                            (! theChannel2._inUse))
                                        {
                                            result = 0;
                                        }
                                        else if (theChannel2._found && (theChannel2._node == NODE_NAME_1) && (theChannel2._path == CHANNEL_PATH_1) &&
                                                 (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>") &&
                                                 (nImO::TransportType::kUDP == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                                 (theChannel1._node == NODE_NAME_2) && (theChannel1._path == CHANNEL_PATH_2) &&
                                                 theChannel1._isOutput && (theChannel1._dataType == "only-blort") &&
                                                 (nImO::TransportType::kAny == theChannel1._modes) && (! theChannel1._inUse))
                                        {
                                            result = 0;
                                        }
                                        else
                                        {
                                            ODL_LOG("(theChannel2._found && (theChannel2._node == NODE_NAME_1) && " //####
                                                    "(theChannel2._path == CHANNEL_PATH_1) && (! theChannel2._isOutput) && " //####
                                                    "(theChannel2._dataType == \"<chuckles>\") && " //####
                                                    "(nImO::TransportType::kUDP == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                    "theChannel1._found && (theChannel1._node == NODE_NAME_2) && " //####
                                                    "(theChannel1._path == CHANNEL_PATH_2) && theChannel1._isOutput && " //####
                                                    "(theChannel1._dataType == \"only-blort\") && " //####
                                                    "(nImO::TransportType::kAny == theChannel1._modes) && (! theChannel1._inUse))"); //####
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
} // doTestGetChannelSetForMachineFromRegistryWithTwoNodesWithChannels

#if defined(__APPLE__)
# pragma mark *** Test Case 347 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetWithBadNodeNameFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        nImO::RegChannelInfoVectorOrFailure statusWithInformation{aRegistry->getInformationForAllChannelsOnNode(NODE_NAME_2)};

                        if (statusWithInformation.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

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
} // doTestGetChannelSetWithBadNodeNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 348 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelSetWithBadMachineNameFromRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
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
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            std::string                 machineName{nImO::GetShortComputerName()};
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegChannelInfoVectorOrFailure
                                                        statusWithInformation{aRegistry->getInformationForAllChannelsOnMachine(machineName + "!!")};

                        if (statusWithInformation.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInformation.second};

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
} // doTestGetChannelSetWithBadMachineNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 350 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInUseWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_1)};

            if (statusWithBool.first.first)
            {
                ODL_LOG("(statusWithBool.first.first)"); //####
            }
            else
            {
                result = 0;
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
} // doTestGetChannelInUseWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 351 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSetChannelInUseWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->setChannelInUse(NODE_NAME_1, CHANNEL_PATH_1)};

            if (status.first)
            {
                ODL_LOG("(statusWithBool.first.first)"); //####
            }
            else
            {
                result = 0;
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
} // doTestSetChannelInUseWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 352 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearChannelInUseWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegSuccessOrFailure   status{aRegistry->clearChannelInUse(NODE_NAME_1, CHANNEL_PATH_1)};

            if (status.first)
            {
                ODL_LOG("(status.first)"); //####
            }
            else
            {
                result = 0;
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
} // doTestClearChannelInUseWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 353 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestChannelInUseCanBeSet
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("(statusWithBool.second)"); //####
                            }
                            else
                            {
                                status = aRegistry->setChannelInUse(NODE_NAME_1, CHANNEL_PATH_1);
                                if (status.first)
                                {
                                    statusWithBool = aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_1);
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
                                    ODL_LOG("! (status.first)"); //####
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestChannelInUseCanBeSet

#if defined(__APPLE__)
# pragma mark *** Test Case 354 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestChannelInUseCanBeCleared
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("(statusWithBool.second)"); //####
                            }
                            else
                            {
                                status = aRegistry->setChannelInUse(NODE_NAME_1, CHANNEL_PATH_1);
                                if (status.first)
                                {
                                    statusWithBool = aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_1);
                                    if (statusWithBool.first.first)
                                    {
                                        if (statusWithBool.second)
                                        {
                                            status = aRegistry->clearChannelInUse(NODE_NAME_1, CHANNEL_PATH_1);
                                            if (status.first)
                                            {
                                                statusWithBool = aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_1);
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
                                                ODL_LOG("! (status.first)"); //####
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
} // doTestChannelInUseCanBeCleared

#if defined(__APPLE__)
# pragma mark *** Test Case 355 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInUseWithBadNodeName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUse(NODE_NAME_2, CHANNEL_PATH_1)};

                        if (statusWithBool.first.first)
                        {
                            ODL_LOG("(statusWithBool.first.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestGetChannelInUseWithBadNodeName

#if defined(__APPLE__)
# pragma mark *** Test Case 356 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSetChannelInUseWithBadNodeName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->setChannelInUse(NODE_NAME_1, CHANNEL_PATH_2);
                        if (status.first)
                        {
                            ODL_LOG("(status.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestSetChannelInUseWithBadNodeName

#if defined(__APPLE__)
# pragma mark *** Test Case 357 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearChannelInUseWithBadNodeName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->clearChannelInUse(NODE_NAME_1, CHANNEL_PATH_2);
                        if (status.first)
                        {
                            ODL_LOG("(status.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestClearChannelInUseWithBadNodeName

#if defined(__APPLE__)
# pragma mark *** Test Case 358 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetChannelInUseWithBadChannelName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_2)};

                        if (statusWithBool.first.first)
                        {
                            ODL_LOG("(statusWithBool.first.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestGetChannelInUseWithBadChannelName

#if defined(__APPLE__)
# pragma mark *** Test Case 359 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestSetChannelInUseWithBadChannelName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->setChannelInUse(NODE_NAME_2, CHANNEL_PATH_1);
                        if (status.first)
                        {
                            ODL_LOG("(status.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestSetChannelInUseWithBadChannelName

#if defined(__APPLE__)
# pragma mark *** Test Case 360 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
    doTestClearChannelInUseWithBadChannelName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->clearChannelInUse(NODE_NAME_2, CHANNEL_PATH_1);
                        if (status.first)
                        {
                            ODL_LOG("(status.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestClearChannelInUseWithBadChannelName

#if defined(__APPLE__)
# pragma mark *** Test Case 361 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetAndSetChannelInUse
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUseAndSet(NODE_NAME_1, CHANNEL_PATH_1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("(statusWithBool.second)"); //####
                            }
                            else
                            {
                                statusWithBool = aRegistry->getChannelInUse(NODE_NAME_1, CHANNEL_PATH_1);
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
} // doTestGetAndSetChannelInUse

#if defined(__APPLE__)
# pragma mark *** Test Case 362 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetAndSetChannelInUseWithEmptyRegistry
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

    try
    {
        std::unique_ptr<nImO::Registry> aRegistry{new nImO::Registry{context}};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUseAndSet(NODE_NAME_1, CHANNEL_PATH_1)};

            if (statusWithBool.first.first)
            {
                ODL_LOG("(statusWithBool.first.first)"); //####
            }
            else
            {
                result = 0;
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
} // doTestGetAndSetChannelInUseWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 363 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetAndSetChannelInUseWithBadNodeName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUseAndSet(NODE_NAME_2, CHANNEL_PATH_1)};

                        if (statusWithBool.first.first)
                        {
                            ODL_LOG("(statusWithBool.first.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestGetAndSetChannelInUseWithBadNodeName

#if defined(__APPLE__)
# pragma mark *** Test Case 364 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetAndSetChannelInUseWithBadChannelName
    (CPtr(char)                     launchPath,
     const int                      argc,
     Ptr(Ptr(char))                 argv,
     nImO::SpContextWithNetworking  context,
     const std::string &            execPath,
     const std::string &            currentDir,
     const std::string &            commandLine)
{
    NIMO_UNUSED_VAR_(launchPath);
    NIMO_UNUSED_VAR_(argc);
    NIMO_UNUSED_VAR_(argv);
    NIMO_UNUSED_VAR_(execPath);
    NIMO_UNUSED_VAR_(currentDir);
    NIMO_UNUSED_VAR_(commandLine);
    ODL_ENTER(); //####
    //ODL_S1("launchPath = ", launchPath); //####
    //ODL_I1("argc = ", argc); //####
    //ODL_P1("argv = ", argv); //####
    int result{1};

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
            nImO::RegSuccessOrFailure   status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(NODE_NAME_1, CHANNEL_PATH_1, false, "<chuckles>", nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        nImO::RegBoolOrFailure  statusWithBool{aRegistry->getChannelInUseAndSet(NODE_NAME_1, CHANNEL_PATH_2)};

                        if (statusWithBool.first.first)
                        {
                            ODL_LOG("(statusWithBool.first.first)"); //####
                        }
                        else
                        {
                            result = 0;
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
} // doTestGetAndSetChannelInUseWithBadChannelName

#if defined(__APPLE__)
# pragma mark *** Test Case 380 ***
#endif // defined(__APPLE__)

//                        result = doTestCountChannelConnectionsWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 381 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsFromEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                              commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 382 ***
#endif // defined(__APPLE__)

//                        result = doTestCountChannelConnectionsInRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                       commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 383 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForNodeFromRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                              currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 384 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForNodeFromRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                               currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 385 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForNodesFromRegistryWithTwoNodesWithChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                         execPath, currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 386 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                 currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 387 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                  currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 388 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithTwoNodesWithChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                           execPath, currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 389 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsWithBadNodeNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                        commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 390 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsWithBadMachineNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                           currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 400 ***
#endif // defined(__APPLE__)

//                        result = doTestCountChannelConnectionsWithRegistryWithTwoConnectedChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                   currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 401 ***
#endif // defined(__APPLE__)

//                        result = doTestConnectChannelsWithRegistryWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                     commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 402 ***
#endif // defined(__APPLE__)

//                        result = doTestConnectChannelsWithRegistryWithBadNodeName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                  commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 403 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForNodeFromRegistryWithTwoConnectedChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                        execPath, currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 404 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithTwoConnectedChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                           execPath, currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 405 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelDetailsForInputChannelFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                    commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 406 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelDetailsForOutputChannelFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                     commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 407 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelDetailsForInputChannelFromRegistryWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                      currentDir, commandLine);

#if defined(__APPLE__)
# pragma mark *** Test Case 408 ***
#endif // defined(__APPLE__)

//                        result = doTestGetChannelDetailsForOutputChannelFromRegistryWithBadChannelName(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                       execPath, currentDir, commandLine);

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

                    case 300 :
                        result = doTestCountChannelsWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 301 :
                        result = doTestFindChannelWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 302 :
                        result = doTestAddChannelToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 303 :
                        result = doTestCountChannelsInRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                             commandLine);
                        break;

                    case 304 :
                        result = doTestFindChannelInRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 305 :
                        result = doTestAddTwoChannelsToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 306 :
                        result = doTestCountChannelsInRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                              commandLine);
                        break;

                    case 307 :
                        result = doTestFindChannelsInRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                             commandLine);
                        break;

                    case 308 :
                        result = doTestAddTwoIdenticalChannelsToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 309:
                        result = doTestAddChannelWithBadNodeNameToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 310:
                        result = doTestAddChannelWithBadChannelNameToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                              commandLine);
                        break;

                    case 311:
                        result = doTestRemoveAllChannelsFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 312:
                        result = doTestCountChannelsWithRegistryWithAllChannelsRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                       commandLine);
                        break;

                    case 313:
                        result = doTestFindChannelWithRegistryAllChannelsRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                 commandLine);
                        break;

                    case 314:
                        result = doTestRemoveOneChannelFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 315:
                        result = doTestCountChannelsWithRegistryWithOneChannelRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                      commandLine);
                        break;

                    case 316:
                        result = doTestFindChannelWithRegistryOneChannelRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                commandLine);
                        break;

                    case 317:
                        result = doTestRemoveNonexistentChannelFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 318:
                        result = doTestRemoveChannelFromNonexistentNodeFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                    commandLine);
                        break;

                    case 320 :
                        result = doTestGetChannelInfoFromEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 321 :
                        result = doTestGetChannelInfoFromRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                commandLine);
                        break;

                    case 322 :
                        result = doTestGetChannelInfoFromRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                 commandLine);
                        break;

                    case 323 :
                        result = doTestGetChannelInfoWithBadNodeNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                 commandLine);
                        break;

                    case 324 :
                        result = doTestGetChannelInfoWithBadChannelNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                    commandLine);
                        break;

                    case 340 :
                        result = doTestGetChannelSetFromEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 341 :
                        result = doTestGetChannelSetForNodeFromRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                      commandLine);
                        break;

                    case 342 :
                        result = doTestGetChannelSetForNodeFromRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                       commandLine);
                        break;

                    case 343 :
                        result = doTestGetChannelSetForNodesFromRegistryWithTwoNodesWithChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                 currentDir, commandLine);
                        break;

                    case 344 :
                        result = doTestGetChannelSetForMachineFromRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                         commandLine);
                        break;

                    case 345 :
                        result = doTestGetChannelSetForMachineFromRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                          commandLine);
                        break;

                    case 346 :
                        result = doTestGetChannelSetForMachineFromRegistryWithTwoNodesWithChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                   currentDir, commandLine);
                        break;

                    case 347 :
                        result = doTestGetChannelSetWithBadNodeNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                commandLine);
                        break;

                    case 348 :
                        result = doTestGetChannelSetWithBadMachineNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                   commandLine);
                        break;

                    case 350 :
                        result = doTestGetChannelInUseWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 351 :
                        result = doTestSetChannelInUseWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 352 :
                        result = doTestClearChannelInUseWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 353 :
                        result = doTestChannelInUseCanBeSet(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 354 :
                        result = doTestChannelInUseCanBeCleared(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 355 :
                        result = doTestGetChannelInUseWithBadNodeName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 356 :
                        result = doTestSetChannelInUseWithBadNodeName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 357 :
                        result = doTestClearChannelInUseWithBadNodeName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 358 :
                        result = doTestGetChannelInUseWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 359 :
                        result = doTestSetChannelInUseWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 360 :
                        result = doTestClearChannelInUseWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 361 :
                        result = doTestGetAndSetChannelInUse(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 362 :
                        result = doTestGetAndSetChannelInUseWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                              commandLine);
                        break;

                    case 363 :
                        result = doTestGetAndSetChannelInUseWithBadNodeName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 364 :
                        result = doTestGetAndSetChannelInUseWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                               commandLine);
                        break;

                    case 380 :
//                        result = doTestCountChannelConnectionsWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                commandLine);
                        break;

                    case 381 :
//                        result = doTestGetChannelConnectionsFromEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                              commandLine);
                        break;

                    case 382 :
//                        result = doTestCountChannelConnectionsInRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                       commandLine);
                        break;

                    case 383 :
//                        result = doTestGetChannelConnectionsForNodeFromRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                              currentDir, commandLine);
                        break;

                    case 384 :
//                        result = doTestGetChannelConnectionsForNodeFromRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                               currentDir, commandLine);
                        break;

                    case 385 :
//                        result = doTestGetChannelConnectionsForNodesFromRegistryWithTwoNodesWithChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                         execPath, currentDir, commandLine);
                        break;

                    case 386 :
//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithOneChannel(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                 currentDir, commandLine);
                        break;

                    case 387 :
//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithTwoChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                  currentDir, commandLine);
                        break;

                    case 388 :
//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithTwoNodesWithChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                           execPath, currentDir, commandLine);
                        break;

                    case 389 :
//                        result = doTestGetChannelConnectionsWithBadNodeNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                        commandLine);
                        break;

                    case 390 :
//                        result = doTestGetChannelConnectionsWithBadMachineNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                           currentDir, commandLine);
                        break;

                    case 400 :
//                        result = doTestCountChannelConnectionsWithRegistryWithTwoConnectedChannels(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                   currentDir, commandLine);
                        break;

                    case 401 :
//                        result = doTestConnectChannelsWithRegistryWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                     commandLine);
                        break;

                    case 402 :
//                        result = doTestConnectChannelsWithRegistryWithBadNodeName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                  commandLine);
                        break;

                    case 403 :
//                        result = doTestGetChannelConnectionsForNodeFromRegistryWithTwoConnectedChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                        execPath, currentDir, commandLine);
                        break;

                    case 404 :
//                        result = doTestGetChannelConnectionsForMachineFromRegistryWithTwoConnectedChannels(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                           execPath, currentDir, commandLine);
                        break;

                    case 405 :
//                        result = doTestGetChannelDetailsForInputChannelFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                    commandLine);
                        break;

                    case 406 :
//                        result = doTestGetChannelDetailsForOutputChannelFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
//                                                                                     commandLine);
                        break;

                    case 407 :
//                        result = doTestGetChannelDetailsForInputChannelFromRegistryWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath,
//                                                                                                      currentDir, commandLine);
                        break;

                    case 408 :
//                        result = doTestGetChannelDetailsForOutputChannelFromRegistryWithBadChannelName(*argv, argc - 1, argv + 2, ourContext,
//                                                                                                       execPath, currentDir, commandLine);
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

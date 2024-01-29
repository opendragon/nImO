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
#include <nImOmainSupport.h>

#include <string>

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

/*! @brief A bad machine name for testing. */
static const std::string    kBadMachineName{"bad_machine____"s};

/*! @brief A bad node name for testing. */
static const std::string    kBadNodeName{"bad_node____"s};

/*! @brief A bad channel path for testing. */
static const std::string    kBadChannelPath{"/bad_path____"s};

/*! @brief The first application name for testing. */
static const std::string    kAppName1{"ApplicationOne"s};

/*! @brief The second application name for testing. */
static const std::string    kAppName2{"ApplicationTwo"s};

/*! @brief The first application description for testing. */
static const std::string    kAppDescr1{"first app"s};

/*! @brief The second application description for testing. */
static const std::string    kAppDescr2{"second app"s};

/*! @brief The first channel path for testing. */
static const std::string    kChannelPath1{"/blart/input/1"s};

/*! @brief The second channel path for testing. */
static const std::string    kChannelPath2{"/blert/output/2"s};

/*! @brief The firsts machine address for testing. */
static const auto   kMachineAddress1{nImO::BytesToIPv4Address(192, 168, 100, 11)};

/*! @brief The second machine address for testing. */
static const auto   kMachineAddress2{nImO::BytesToIPv4Address(192, 168, 100, 12)};

/*! @brief The first machine name for testing. */
static const std::string    kMachineName1{"Blort"s};

/*! @brief The second machine name for testing. */
static const std::string    kMachineName2{"Blurt"s};

/*! @brief The first node name for testing. */
static const std::string    kNodeName1{"blort"s};

/*! @brief The second node name for testing. */
static const std::string    kNodeName2{"blurt"s};

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
    auto    message{"exiting due to signal "s + std::to_string(signal) + " = "s + NameOfSignal(signal)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInt{aRegistry->getNumberOfMachines()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithStrings{aRegistry->getNamesOfMachines()};

            if (statusWithStrings.first.first)
            {
                StdStringSet    machines{statusWithStrings.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithBool{aRegistry->isMachinePresent(kMachineName1)};

            if (statusWithBool.first.first)
            {
                if (statusWithBool.second)
                {
                    ODL_LOG("(statusWithBool.second)"); //####
                }
                else
                {
                    statusWithBool = aRegistry->isMachinePresent(kMachineName2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(kMachineName1, kMachineAddress1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(kMachineName1, kMachineAddress1)};

            if (status.first)
            {
                auto    statusWithInt{aRegistry->getNumberOfMachines()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(kMachineName1, kMachineAddress1)};

            if (status.first)
            {
                auto    statusWithStrings{aRegistry->getNamesOfMachines()};

                if (statusWithStrings.first.first)
                {
                    StdStringSet    machines = statusWithStrings.second;

                    if (machines.end() == machines.find(kMachineName1))
                    {
                        ODL_LOG("(machines.end() == machines.find(kMachineName1))"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(kMachineName1, kMachineAddress1)};

            if (status.first)
            {
                auto    statusWithBool{aRegistry->isMachinePresent(kMachineName1)};

                if (statusWithBool.first.first)
                {
                    if (statusWithBool.second)
                    {
                        statusWithBool = aRegistry->isMachinePresent(kMachineName2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(kMachineName1, kMachineAddress1)};

            if (status.first)
            {
                status = aRegistry->addMachine(kMachineName2, kMachineAddress2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(kMachineName1, kMachineAddress1)};

            if (status.first)
            {
                status = aRegistry->addMachine(kMachineName2, kMachineAddress2);
                if (status.first)
                {
                    auto    statusWithInt{aRegistry->getNumberOfMachines()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(kMachineName1, kMachineAddress1)};

            if (status.first)
            {
                status = aRegistry->addMachine(kMachineName1, kMachineAddress1);
                if (status.first)
                {
                    auto    statusWithInt{aRegistry->getNumberOfMachines()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInt{aRegistry->getNumberOfNodes()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithStrings{aRegistry->getNamesOfNodes()};

            if (statusWithStrings.first.first)
            {
                StdStringSet    nodes{statusWithStrings.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithBool{aRegistry->isNodePresent(kNodeName1)};

            if (statusWithBool.first.first)
            {
                if (statusWithBool.second)
                {
                    ODL_LOG("(statusWithBool.second)"); //####
                }
                else
                {
                    statusWithBool = aRegistry->isNodePresent(kNodeName2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    auto    statusWithInt{aRegistry->getNumberOfNodes()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    auto    statusWithStrings{aRegistry->getNamesOfNodes()};

                    if (statusWithStrings.first.first)
                    {
                        StdStringSet    nodes{statusWithStrings.second};

                        if (nodes.end() == nodes.find(kNodeName1))
                        {
                            ODL_LOG("(nodes.end() == nodes.find(kNodeName1))"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    auto    statusWithBool{aRegistry->isNodePresent(kNodeName1)};

                    if (statusWithBool.first.first)
                    {
                        if (statusWithBool.second)
                        {
                            statusWithBool = aRegistry->isNodePresent(kNodeName2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    randomAddress{StaticCast(IPv4Address, nImO::RandomUnsigned())};
            auto    randomPort{StaticCast(IPv4Port, nImO::RandomUnsigned())};
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName(), randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    auto    statusWithInfo{aRegistry->getNodeInformation(kNodeName1)};

                    if (statusWithInfo.first.first)
                    {
                        if (statusWithInfo.second._found)
                        {
                            if ((statusWithInfo.second._name == kNodeName1) && (randomAddress == statusWithInfo.second._connection._address) &&
                                (randomPort == statusWithInfo.second._connection._port) &&
                                (nImO::ServiceType::FilterService == statusWithInfo.second._serviceType))
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! ((statusWithInfo.second._name == kNodeName1) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(kNodeName1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(kNodeName1);
                    if (status.first)
                    {
                        auto    statusWithInt{aRegistry->getNumberOfNodes()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(kNodeName1);
                    if (status.first)
                    {
                        auto    statusWithStrings{aRegistry->getNamesOfNodes()};

                        if (statusWithStrings.first.first)
                        {
                            StdStringSet    nodes{statusWithStrings.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->removeNode(kNodeName1);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->isNodePresent(kNodeName1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        auto    statusWithInt{aRegistry->getNumberOfNodes()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        auto    statusWithStrings{aRegistry->getNamesOfNodes()};

                        if (statusWithStrings.first.first)
                        {
                            StdStringSet    nodes{statusWithStrings.second};

                            if (nodes.end() == nodes.find(kNodeName1))
                            {
                                ODL_LOG("(nodes.end() == nodes.find(kNodeName1))"); //####
                            }
                            else
                            {
                                if (nodes.end() == nodes.find(kNodeName2))
                                {
                                    ODL_LOG("(nodes.end() == nodes.find(kNodeName2))"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->isNodePresent(kNodeName1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                statusWithBool = aRegistry->isNodePresent(kNodeName2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(kNodeName1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(kNodeName2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(kNodeName1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(kNodeName2);
                            if (status.first)
                            {
                                auto    statusWithInt{aRegistry->getNumberOfNodes()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(kNodeName1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(kNodeName2);
                            if (status.first)
                            {
                                auto    statusWithStrings{aRegistry->getNamesOfNodes()};

                                if (statusWithStrings.first.first)
                                {
                                    StdStringSet    nodes{statusWithStrings.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->removeNode(kNodeName1);
                        if (status.first)
                        {
                            status = aRegistry->removeNode(kNodeName2);
                            if (status.first)
                            {
                                auto    statusWithBool{aRegistry->isNodePresent(kNodeName1)};

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        ODL_LOG("(statusWithBool.second)"); //####
                                    }
                                    else
                                    {
                                        statusWithBool = aRegistry->isNodePresent(kNodeName2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        ODL_LOG("(status.first)"); //####
                    }
                    else
                    {
                        auto    statusWithStrings{aRegistry->getNamesOfNodes()};

                        if (statusWithStrings.first.first)
                        {
                            StdStringSet    nodes{statusWithStrings.second};

                            if (nodes.end() == nodes.find(kNodeName1))
                            {
                                ODL_LOG("(nodes.end() == nodes.find(kNodeName1))"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getInformationForAllNodes()};

            if (statusWithInfo.first.first)
            {
                auto    infoVector{statusWithInfo.second};

                if (infoVector.empty())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (infoVector.empty())"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    randomAddress{StaticCast(IPv4Address, nImO::RandomUnsigned())};
            auto    randomPort{StaticCast(IPv4Port, nImO::RandomUnsigned())};
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName(), randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    auto    statusWithInfo{aRegistry->getInformationForAllNodes()};

                    if (statusWithInfo.first.first)
                    {
                        auto    infoVector{statusWithInfo.second};

                        if (1 == infoVector.size())
                        {
                            nImO::NodeInfo &    firstElem{infoVector[0]};

                            if ((firstElem._name == kNodeName1) && (randomAddress == firstElem._connection._address) &&
                                (randomPort == firstElem._connection._port) && (nImO::ServiceType::FilterService == firstElem._serviceType))
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! ((firstElem._name == kNodeName1) && (randomAddress == firstElem._connection._address) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    randomAddress1{StaticCast(IPv4Address, nImO::RandomUnsigned())};
            auto    randomPort1{StaticCast(IPv4Port, nImO::RandomUnsigned())};
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName, randomAddress1)};

            if (status.first)
            {
                auto    randomAddress2{StaticCast(IPv4Address, nImO::RandomUnsigned())};

                status = aRegistry->addMachine(machineName + "_1"s, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        auto    randomPort2{StaticCast(IPv4Port, nImO::RandomUnsigned())};

                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService,
                                                    nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            auto    statusWithInfo{aRegistry->getInformationForAllNodes()};

                            if (statusWithInfo.first.first)
                            {
                                auto    infoVector{statusWithInfo.second};

                                if (2 == infoVector.size())
                                {
                                    nImO::NodeInfo &    firstElem{infoVector[0]};
                                    nImO::NodeInfo &    secondElem{infoVector[1]};

                                    if (firstElem._name == kNodeName1)
                                    {
                                        if (secondElem._name == kNodeName2)
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
                                            ODL_LOG("! (secondElem._name == kNodeName2)"); //####
                                        }
                                    }
                                    else if (secondElem._name == kNodeName1)
                                    {
                                        if (firstElem._name == kNodeName2)
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
                                            ODL_LOG("! (firstElem._name == kNodeName2)"); //####
                                        }
                                    }
                                    else
                                    {
                                        ODL_LOG("! (secondElem._name == kNodeName1)"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (2 == infoVector.size())"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithDetails{aRegistry->getLaunchDetails(kNodeName1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    randomAddress{StaticCast(IPv4Address, nImO::RandomUnsigned())};
            auto    randomPort{StaticCast(IPv4Port, nImO::RandomUnsigned())};
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName(), randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    auto    statusWithDetails{aRegistry->getLaunchDetails(kNodeName1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    randomAddress1{StaticCast(IPv4Address, nImO::RandomUnsigned())};
            auto    randomPort1{StaticCast(IPv4Port, nImO::RandomUnsigned())};
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName, randomAddress1)};

            if (status.first)
            {
                auto    randomAddress2{StaticCast(IPv4Address, nImO::RandomUnsigned())};

                status = aRegistry->addMachine(machineName + "_1"s, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        auto    randomPort2{StaticCast(IPv4Port, nImO::RandomUnsigned())};

                        status = aRegistry->addNode(kNodeName2, "!"s + execPath, "?"s + currentDir, "^"s + commandLine,
                                                    nImO::ServiceType::LauncherService, nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            auto    statusWithDetails{aRegistry->getLaunchDetails(kNodeName1)};

                            if (statusWithDetails.first.first)
                            {
                                nImO::LaunchDetails details1{statusWithDetails.second};

                                if (details1._found)
                                {
                                    if ((execPath == details1._execPath) && (currentDir == details1._launchDirectory) &&
                                        (commandLine == details1._commandLine))
                                    {
                                        statusWithDetails = aRegistry->getLaunchDetails(kNodeName2);
                                        if (statusWithDetails.first.first)
                                        {
                                            nImO::LaunchDetails details2{statusWithDetails.second};

                                            if (details2._found)
                                            {
                                                if ((("!"s + execPath) == details2._execPath) && (("?"s + currentDir) == details2._launchDirectory) &&
                                                    (("^"s + commandLine) == details2._commandLine))
                                                {
                                                    result = 0;
                                                }
                                                else
                                                {
                                                    ODL_LOG("! (((\"!\"s + execPath) == details2._execPath) && " //####
                                                            "((\"?\"s + currentDir) == details2._launchDirectory) && " //####
                                                            "((\"^\"s + commandLine) == details2._commandLine))"); //####
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
# pragma mark *** Test Case 127 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestNodeInfoWithEmptyRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getNodeInformation(kNodeName1)};

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
} // doTestNodeInfoWithEmptyRegistry

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                auto    statusWithStrings{aRegistry->getNamesOfNodesOnMachine(machineName)};

                if (statusWithStrings.first.first)
                {
                    StdStringSet    nodes{statusWithStrings.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    auto    statusWithStrings{aRegistry->getNamesOfNodesOnMachine(machineName)};

                    if (statusWithStrings.first.first)
                    {
                        StdStringSet    nodes{statusWithStrings.second};

                        if (nodes.end() == nodes.find(kNodeName1))
                        {
                            ODL_LOG("(nodes.end() == nodes.find(kNodeName1))"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        auto    statusWithStrings{aRegistry->getNamesOfNodesOnMachine(machineName)};

                        if (statusWithStrings.first.first)
                        {
                            StdStringSet    nodes{statusWithStrings.second};

                            if (nodes.end() == nodes.find(kNodeName1))
                            {
                                ODL_LOG("(nodes.end() == nodes.find(kNodeName1))"); //####
                            }
                            else
                            {
                                if (nodes.end() == nodes.find(kNodeName2))
                                {
                                    ODL_LOG("(nodes.end() == nodes.find(kNodeName2))"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                auto    statusWithInfo{aRegistry->getInformationForAllNodesOnMachine(machineName)};

                if (statusWithInfo.first.first)
                {
                    auto    infoVector{statusWithInfo.second};

                    if (infoVector.empty())
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (infoVector.empty())"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    randomAddress{StaticCast(IPv4Address, nImO::RandomUnsigned())};
            auto    randomPort{StaticCast(IPv4Port, nImO::RandomUnsigned())};
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName, randomAddress)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                            nImO::Connection(randomAddress, randomPort));
                if (status.first)
                {
                    auto    statusWithInfo{aRegistry->getInformationForAllNodesOnMachine(machineName)};

                    if (statusWithInfo.first.first)
                    {
                        auto    infoVector{statusWithInfo.second};

                        if (1 == infoVector.size())
                        {
                            nImO::NodeInfo &    firstElem{infoVector[0]};

                            if ((firstElem._name == kNodeName1) && (randomAddress == firstElem._connection._address) &&
                                (randomPort == firstElem._connection._port) && (nImO::ServiceType::FilterService == firstElem._serviceType))
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! ((firstElem._name == kNodeName1) && (randomAddress == firstElem._connection._address) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    randomAddress1{StaticCast(IPv4Address, nImO::RandomUnsigned())};
            auto    randomPort1{StaticCast(IPv4Port, nImO::RandomUnsigned())};
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName, randomAddress1)};

            if (status.first)
            {
                auto    randomAddress2{StaticCast(IPv4Address, nImO::RandomUnsigned())};

                status = aRegistry->addMachine(machineName + "_1"s, randomAddress2);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                nImO::Connection(randomAddress1, randomPort1));
                    if (status.first)
                    {
                        auto    randomPort2{StaticCast(IPv4Port, nImO::RandomUnsigned())};

                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService,
                                                    nImO::Connection(randomAddress2, randomPort2));
                        if (status.first)
                        {
                            auto    statusWithInfo{aRegistry->getInformationForAllNodesOnMachine(machineName)};

                            if (statusWithInfo.first.first)
                            {
                                auto    infoVector{statusWithInfo.second};

                                if (1 == infoVector.size())
                                {
                                    nImO::NodeInfo &    firstElem{infoVector[0]};

                                    if (firstElem._name == kNodeName1)
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
                                        ODL_LOG("! (firstElem._name == kNodeName1)"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (1 == infoVector.size())"); //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                auto    statusWithInt{aRegistry->getNumberOfNodesOnMachine(machineName)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    auto    statusWithInt{aRegistry->getNumberOfNodesOnMachine(machineName)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        auto    statusWithInt{aRegistry->getNumberOfNodesOnMachine(machineName)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInt{aRegistry->getNumberOfChannels()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithBool{aRegistry->isChannelPresent(kNodeName1, kChannelPath1)};

            if (statusWithBool.first.first)
            {
                if (statusWithBool.second)
                {
                    ODL_LOG("(statusWithBool.second)"); //####
                }
                else
                {
                    statusWithBool = aRegistry->isChannelPresent(kNodeName2, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kAny);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        auto    statusWithInt{aRegistry->getNumberOfChannels()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->isChannelPresent(kNodeName1, kChannelPath1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                statusWithBool = aRegistry->isChannelPresent(kNodeName2, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, true, "only-blort"s, nImO::TransportType::kTCP);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, true, "only-blort"s, nImO::TransportType::kAny);
                            if (status.first)
                            {
                                auto    statusWithInt{aRegistry->getNumberOfChannels()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, true, "only-blort"s, nImO::TransportType::kUDP);
                            if (status.first)
                            {
                                auto    statusWithBool{aRegistry->isChannelPresent(kNodeName1, kChannelPath1)};

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        statusWithBool = aRegistry->isChannelPresent(kNodeName2, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, "only-blort"s, nImO::TransportType::kTCP);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName2, "/arbitrary_path"s, false, ""s, nImO::TransportType::kUDP);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, "/arbitrary&path"s, false, ""s, nImO::TransportType::kAny);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannelsForNode(kNodeName1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kTCP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannelsForNode(kNodeName1);
                            if (status.first)
                            {
                                auto    statusWithInt{aRegistry->getNumberOfChannels()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kAny);
                        if (status.first)
                        {
                            status = aRegistry->removeChannelsForNode(kNodeName1);
                            if (status.first)
                            {
                                auto    statusWithBool{aRegistry->isChannelPresent(kNodeName1, kChannelPath1)};

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        ODL_LOG("(statusWithBool.second)"); //####
                                    }
                                    else
                                    {
                                        statusWithBool = aRegistry->isChannelPresent(kNodeName1, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannel(kNodeName1, kChannelPath1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kTCP);
                        if (status.first)
                        {
                            status = aRegistry->removeChannel(kNodeName1, kChannelPath1);
                            if (status.first)
                            {
                                auto    statusWithInt{aRegistry->getNumberOfChannels()};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kAny);
                        if (status.first)
                        {
                            status = aRegistry->removeChannel(kNodeName1, kChannelPath1);
                            if (status.first)
                            {
                                auto    statusWithBool{aRegistry->isChannelPresent(kNodeName1, kChannelPath1)};

                                if (statusWithBool.first.first)
                                {
                                    if (statusWithBool.second)
                                    {
                                        ODL_LOG("(statusWithBool.second)"); //####
                                    }
                                    else
                                    {
                                        statusWithBool = aRegistry->isChannelPresent(kNodeName1, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->removeChannel(kNodeName1, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, ""s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->removeChannel(kNodeName2, kChannelPath1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getChannelInformation(kNodeName1, kChannelPath1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        auto    statusWithInfo{aRegistry->getChannelInformation(kNodeName1, kChannelPath1)};

                        if (statusWithInfo.first.first)
                        {
                            if (statusWithInfo.second._found)
                            {
                                if ((statusWithInfo.second._node == kNodeName1) && (statusWithInfo.second._path == kChannelPath1) &&
                                    (! statusWithInfo.second._isOutput) && (statusWithInfo.second._dataType == "<chuckles>"s) &&
                                    (nImO::TransportType::kAny == statusWithInfo.second._modes))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("((statusWithInfo.second._node == kNodeName1) && " //####
                                            "(statusWithInfo.second._path == kChannelPath1) && " //####
                                            "(! statusWithInfo.second._isOutput) && " //####
                                            "(statusWithInfo.second._dataType == \"<chuckles>\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, true, "only-blort"s, nImO::TransportType::kUDP);
                            if (status.first)
                            {
                                auto    statusWithInfo{aRegistry->getChannelInformation(kNodeName1, kChannelPath1)};

                                if (statusWithInfo.first.first)
                                {
                                    if (statusWithInfo.second._found)
                                    {
                                        if ((statusWithInfo.second._node == kNodeName1) && (statusWithInfo.second._path == kChannelPath1) &&
                                            (! statusWithInfo.second._isOutput) && (statusWithInfo.second._dataType == "<chuckles>"s) &&
                                            (nImO::TransportType::kTCP == statusWithInfo.second._modes))
                                        {
                                            statusWithInfo = aRegistry->getChannelInformation(kNodeName2, kChannelPath2);
                                            if (statusWithInfo.first.first)
                                            {
                                                if (statusWithInfo.second._found)
                                                {
                                                    if ((statusWithInfo.second._node == kNodeName2) &&
                                                        (statusWithInfo.second._path == kChannelPath2) &&
                                                        statusWithInfo.second._isOutput && (statusWithInfo.second._dataType == "only-blort"s) &&
                                                        (nImO::TransportType::kUDP == statusWithInfo.second._modes))
                                                    {
                                                        result = 0;
                                                    }
                                                    else
                                                    {
                                                        ODL_LOG("((statusWithInfo.second._node == kNodeName2) && "  //####
                                                                "(statusWithInfo.second._path == kChannelPath2) && "  //####
                                                                "statusWithInfo.second._isOutput && "  //####
                                                                "(statusWithInfo.second._dataType == \"only-blort\"s) && " //####
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
                                            ODL_LOG("((statusWithInfo.second._node == kNodeName1) && " //####
                                                    "(statusWithInfo.second._path == kChannelPath1) && " //####
                                                    "(! statusWithInfo.second._isOutput) && " //####
                                                    "(statusWithInfo.second._dataType == \"<chuckles>\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    {
                        auto    statusWithInfo{aRegistry->getChannelInformation(kNodeName2, "/arbitrary_path")};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    auto    statusWithInfo{aRegistry->getChannelInformation(kNodeName1, "/arbitrary&path")};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getInformationForAllChannels()};

            if (statusWithInfo.first.first)
            {
                nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        auto    statusWithInfo{aRegistry->getInformationForAllChannels()};

                        if (statusWithInfo.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

                            if (1 == infoVector.size())
                            {
                                const ChannelInfo & theChannel{infoVector[0]};

                                if (theChannel._found && (theChannel._node == kNodeName1) && (theChannel._path == kChannelPath1) &&
                                    (! theChannel._isOutput) && (theChannel._dataType == "<chuckles>"s) &&
                                    (nImO::TransportType::kAny == theChannel._modes) && (! theChannel._inUse))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("(theChannel._found && (theChannel._node == kNodeName1) && " //####
                                            "(theChannel._path == kChannelPath1) && (! theChannel._isOutput) && " //####
                                            "(theChannel._dataType == \"<chuckles>\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            auto    statusWithInfo{aRegistry->getInformationForAllChannels()};

                            if (statusWithInfo.first.first)
                            {
                                nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

                                if (2 == infoVector.size())
                                {
                                    const ChannelInfo & theChannel1{infoVector[0]};
                                    const ChannelInfo & theChannel2{infoVector[1]};

                                    if (theChannel1._found && (theChannel1._node == kNodeName1) && (theChannel1._path == kChannelPath1) &&
                                        (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>"s) &&
                                        (nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                        (theChannel2._node == kNodeName1) && (theChannel2._path == kChannelPath2) && theChannel2._isOutput &&
                                        (theChannel2._dataType == "only-blort"s) && (nImO::TransportType::kUDP == theChannel2._modes) &&
                                        (! theChannel2._inUse))
                                    {
                                        result = 0;
                                    }
                                    else if (theChannel2._found && (theChannel2._node == kNodeName1) && (theChannel2._path == kChannelPath1) &&
                                             (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>"s) &&
                                             (nImO::TransportType::kTCP == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                             (theChannel1._node == kNodeName1) && (theChannel1._path == kChannelPath2) &&
                                             theChannel1._isOutput && (theChannel1._dataType == "only-blort"s) &&
                                             (nImO::TransportType::kUDP == theChannel1._modes) && (! theChannel1._inUse))
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("(theChannel2._found && (theChannel2._node == kNodeName1) && " //####
                                                "(theChannel2._path == kChannelPath1) && (! theChannel2._isOutput) && " //####
                                                "(theChannel2._dataType == \"<chuckles>\"s) && " //####
                                                "(nImO::TransportType::kTCP == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                "theChannel1._found && (theChannel1._node == kNodeName1) && " //####
                                                "(theChannel1._path == kChannelPath2) && theChannel1._isOutput && " //####
                                                "(theChannel1._dataType == \"only-blort\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kAny);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, true, "only-blort"s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                auto    statusWithInfo{aRegistry->getInformationForAllChannels()};

                                if (statusWithInfo.first.first)
                                {
                                    nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

                                    if (2 == infoVector.size())
                                    {
                                        const ChannelInfo & theChannel1{infoVector[0]};
                                        const ChannelInfo & theChannel2{infoVector[1]};

                                        if (theChannel1._found && (theChannel1._node == kNodeName1) && (theChannel1._path == kChannelPath1) &&
                                            (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>"s) &&
                                            (nImO::TransportType::kAny == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                            (theChannel2._node == kNodeName2) && (theChannel2._path == kChannelPath2) && theChannel2._isOutput &&
                                            (theChannel2._dataType == "only-blort"s) && (nImO::TransportType::kTCP == theChannel2._modes) &&
                                            (! theChannel2._inUse))
                                        {
                                            result = 0;
                                        }
                                        else if (theChannel2._found && (theChannel2._node == kNodeName1) && (theChannel2._path == kChannelPath1) &&
                                                 (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>"s) &&
                                                 (nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                                 (theChannel1._node == kNodeName2) && (theChannel1._path == kChannelPath2) &&
                                                 theChannel1._isOutput && (theChannel1._dataType == "only-blort"s) &&
                                                 (nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse))
                                        {
                                            result = 0;
                                        }
                                        else
                                        {
                                            ODL_LOG("(theChannel2._found && (theChannel2._node == kNodeName1) && " //####
                                                    "(theChannel2._path == kChannelPath1) && (! theChannel2._isOutput) && " //####
                                                    "(theChannel2._dataType == \"<chuckles>\"s) && " //####
                                                    "(nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                    "theChannel1._found && (theChannel1._node == kNodeName2) && " //####
                                                    "(theChannel1._path == kChannelPath2) && theChannel1._isOutput && " //####
                                                    "(theChannel1._dataType == \"only-blort\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithInfo{aRegistry->getInformationForAllChannelsOnMachine(machineName)};

                        if (statusWithInfo.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

                            if (1 == infoVector.size())
                            {
                                const ChannelInfo & theChannel{infoVector[0]};

                                if (theChannel._found && (theChannel._node == kNodeName1) && (theChannel._path == kChannelPath1) &&
                                    (! theChannel._isOutput) && (theChannel._dataType == "<chuckles>"s) &&
                                    (nImO::TransportType::kUDP == theChannel._modes) && (! theChannel._inUse))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("(theChannel._found && (theChannel._node == kNodeName1) && " //####
                                            "(theChannel._path == kChannelPath1) && (! theChannel._isOutput) && " //####
                                            "(theChannel._dataType == \"<chuckles>\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath2, true, "only-blort"s, nImO::TransportType::kTCP);
                        if (status.first)
                        {
                            auto    statusWithInfo{aRegistry->getInformationForAllChannelsOnMachine(machineName)};

                            if (statusWithInfo.first.first)
                            {
                                nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

                                if (2 == infoVector.size())
                                {
                                    const ChannelInfo & theChannel1{infoVector[0]};
                                    const ChannelInfo & theChannel2{infoVector[1]};

                                    if (theChannel1._found && (theChannel1._node == kNodeName1) && (theChannel1._path == kChannelPath1) &&
                                        (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>"s) &&
                                        (nImO::TransportType::kAny == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                        (theChannel2._node == kNodeName1) && (theChannel2._path == kChannelPath2) && theChannel2._isOutput &&
                                        (theChannel2._dataType == "only-blort"s) && (nImO::TransportType::kTCP == theChannel2._modes) &&
                                        (! theChannel2._inUse))
                                    {
                                        result = 0;
                                    }
                                    else if (theChannel2._found && (theChannel2._node == kNodeName1) && (theChannel2._path == kChannelPath1) &&
                                             (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>"s) &&
                                             (nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                             (theChannel1._node == kNodeName1) && (theChannel1._path == kChannelPath2) &&
                                             theChannel1._isOutput && (theChannel1._dataType == "only-blort"s) &&
                                             (nImO::TransportType::kTCP == theChannel1._modes) && (! theChannel1._inUse))
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("(theChannel2._found && (theChannel2._node == kNodeName1) && " //####
                                                "(theChannel2._path == kChannelPath1) && (! theChannel2._isOutput) && " //####
                                                "(theChannel2._dataType == \"<chuckles>\"s) && " //####
                                                "(nImO::TransportType::kAny == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                "theChannel1._found && (theChannel1._node == kNodeName1) && " //####
                                                "(theChannel1._path == kChannelPath2) && theChannel1._isOutput && " //####
                                                "(theChannel1._dataType == \"only-blort\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                    if (status.first)
                    {
                        status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, true, "only-blort"s, nImO::TransportType::kAny);
                            if (status.first)
                            {
                                auto    statusWithInfo{aRegistry->getInformationForAllChannelsOnMachine(machineName)};

                                if (statusWithInfo.first.first)
                                {
                                    nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

                                    if (2 == infoVector.size())
                                    {
                                        const ChannelInfo & theChannel1{infoVector[0]};
                                        const ChannelInfo & theChannel2{infoVector[1]};

                                        if (theChannel1._found && (theChannel1._node == kNodeName1) && (theChannel1._path == kChannelPath1) &&
                                            (! theChannel1._isOutput) && (theChannel1._dataType == "<chuckles>"s) &&
                                            (nImO::TransportType::kUDP == theChannel1._modes) && (! theChannel1._inUse) && theChannel2._found &&
                                            (theChannel2._node == kNodeName2) && (theChannel2._path == kChannelPath2) && theChannel2._isOutput &&
                                            (theChannel2._dataType == "only-blort"s) && (nImO::TransportType::kAny == theChannel2._modes) &&
                                            (! theChannel2._inUse))
                                        {
                                            result = 0;
                                        }
                                        else if (theChannel2._found && (theChannel2._node == kNodeName1) && (theChannel2._path == kChannelPath1) &&
                                                 (! theChannel2._isOutput) && (theChannel2._dataType == "<chuckles>"s) &&
                                                 (nImO::TransportType::kUDP == theChannel2._modes) && (! theChannel2._inUse) && theChannel1._found &&
                                                 (theChannel1._node == kNodeName2) && (theChannel1._path == kChannelPath2) &&
                                                 theChannel1._isOutput && (theChannel1._dataType == "only-blort"s) &&
                                                 (nImO::TransportType::kAny == theChannel1._modes) && (! theChannel1._inUse))
                                        {
                                            result = 0;
                                        }
                                        else
                                        {
                                            ODL_LOG("(theChannel2._found && (theChannel2._node == kNodeName1) && " //####
                                                    "(theChannel2._path == kChannelPath1) && (! theChannel2._isOutput) && " //####
                                                    "(theChannel2._dataType == \"<chuckles>\"s) && " //####
                                                    "(nImO::TransportType::kUDP == theChannel2._modes) && (! theChannel2._inUse) && " //####
                                                    "theChannel1._found && (theChannel1._node == kNodeName2) && " //####
                                                    "(theChannel1._path == kChannelPath2) && theChannel1._isOutput && " //####
                                                    "(theChannel1._dataType == \"only-blort\"s) && " //####
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kTCP);
                    if (status.first)
                    {
                        auto    statusWithInfo{aRegistry->getInformationForAllChannelsOnNode(kNodeName2)};

                        if (statusWithInfo.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithInfo{aRegistry->getInformationForAllChannelsOnMachine(machineName + "!!"s)};

                        if (statusWithInfo.first.first)
                        {
                            nImO::ChannelInfoVector &   infoVector{statusWithInfo.second};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithBool{aRegistry->getChannelInUse(kNodeName1, kChannelPath1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->setChannelInUse(kNodeName1, kChannelPath1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->clearChannelInUse(kNodeName1, kChannelPath1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->getChannelInUse(kNodeName1, kChannelPath1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("(statusWithBool.second)"); //####
                            }
                            else
                            {
                                status = aRegistry->setChannelInUse(kNodeName1, kChannelPath1);
                                if (status.first)
                                {
                                    statusWithBool = aRegistry->getChannelInUse(kNodeName1, kChannelPath1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->getChannelInUse(kNodeName1, kChannelPath1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("(statusWithBool.second)"); //####
                            }
                            else
                            {
                                status = aRegistry->setChannelInUse(kNodeName1, kChannelPath1);
                                if (status.first)
                                {
                                    statusWithBool = aRegistry->getChannelInUse(kNodeName1, kChannelPath1);
                                    if (statusWithBool.first.first)
                                    {
                                        if (statusWithBool.second)
                                        {
                                            status = aRegistry->clearChannelInUse(kNodeName1, kChannelPath1);
                                            if (status.first)
                                            {
                                                statusWithBool = aRegistry->getChannelInUse(kNodeName1, kChannelPath1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->getChannelInUse(kNodeName2, kChannelPath1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->setChannelInUse(kNodeName1, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->clearChannelInUse(kNodeName1, kChannelPath2);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->getChannelInUse(kNodeName1, kChannelPath2)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->setChannelInUse(kNodeName2, kChannelPath1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        status = aRegistry->clearChannelInUse(kNodeName2, kChannelPath1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->getChannelInUseAndSet(kNodeName1, kChannelPath1)};

                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                ODL_LOG("(statusWithBool.second)"); //####
                            }
                            else
                            {
                                statusWithBool = aRegistry->getChannelInUse(kNodeName1, kChannelPath1);
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithBool{aRegistry->getChannelInUseAndSet(kNodeName1, kChannelPath1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->getChannelInUseAndSet(kNodeName2, kChannelPath1)};

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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, false, "<chuckles>"s, nImO::TransportType::kUDP);
                    if (status.first)
                    {
                        auto    statusWithBool{aRegistry->getChannelInUseAndSet(kNodeName1, kChannelPath2)};

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

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountConnectionsWithEmptyRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

       if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInt{aRegistry->getNumberOfConnections()};

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
} // doTestCountConnectionsWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 381 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddConnectionToRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
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
} // doTestAddConnectionToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 382 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountConnectionsInRegistryWithOneConnection
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    auto    statusWithInt{aRegistry->getNumberOfConnections()};

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
} // doTestCountConnectionsInRegistryWithOneConnection

#if defined(__APPLE__)
# pragma mark *** Test Case 383 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoConnectionsToRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);

                            if (status.first)
                            {
                                status = aRegistry->addChannel(kNodeName1, kChannelPath2, false, "blort"s, nImO::TransportType::kUDP);
                                if (status.first)
                                {
                                    status = aRegistry->addChannel(kNodeName2, kChannelPath1, true, "blort"s, nImO::TransportType::kAny);
                                    if (status.first)
                                    {
                                        status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                          nImO::TransportType::kTCP);
                                        if (status.first)
                                        {
                                            status = aRegistry->addConnection(kNodeName2, kChannelPath1, kNodeName1, kChannelPath2, "blort",
                                                                              nImO::TransportType::kUDP);
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
} // doTestAddTwoConnectionsToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 384 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountConnectionsInRegistryWithTwoConnections
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);

                            if (status.first)
                            {
                                status = aRegistry->addChannel(kNodeName1, kChannelPath2, false, "blort"s, nImO::TransportType::kUDP);
                                if (status.first)
                                {
                                    status = aRegistry->addChannel(kNodeName2, kChannelPath1, true, "blort"s, nImO::TransportType::kAny);
                                    if (status.first)
                                    {
                                        status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                          nImO::TransportType::kTCP);
                                        if (status.first)
                                        {
                                            status = aRegistry->addConnection(kNodeName2, kChannelPath1, kNodeName1, kChannelPath2, "blort",
                                                                              nImO::TransportType::kUDP);
                                            if (status.first)
                                            {
                                                auto    statusWithInt{aRegistry->getNumberOfConnections()};

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
} // doTestCountConnectionsInRegistryWithTwoConnections

#if defined(__APPLE__)
# pragma mark *** Test Case 385 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveOneConnectionFromRegistryViaFrom
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    status = aRegistry->removeConnection(kNodeName1, kChannelPath1, true);
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
} // doTestRemoveOneConnectionFromRegistryViaFrom

#if defined(__APPLE__)
# pragma mark *** Test Case 386 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestRemoveOneConnectionFromRegistryViaTo
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    status = aRegistry->removeConnection(kNodeName2, kChannelPath2, false);
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
} // doTestRemoveOneConnectionFromRegistryViaTo

#if defined(__APPLE__)
# pragma mark *** Test Case 387 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountConnectionsWithRegistryWithOneConnectionRemoved
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    status = aRegistry->removeConnection(kNodeName2, kChannelPath2, false);
                                    if (status.first)
                                    {
                                        auto    statusWithInt{aRegistry->getNumberOfConnections()};

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
} // doTestCountConnectionsWithRegistryWithOneConnectionRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 388 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestConnectChannelsWithRegistryWithBadChannelName
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kBadChannelPath, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    ODL_LOG("(status.first)"); //####
                                }
                                else
                                {
                                    status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kBadChannelPath, ""s,
                                                                      nImO::TransportType::kTCP);
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
} // doTestConnectChannelsWithRegistryWithBadChannelName

#if defined(__APPLE__)
# pragma mark *** Test Case 389 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestConnectChannelsWithRegistryWithBadNodeName
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kBadNodeName, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    ODL_LOG("(status.first)"); //####
                                }
                                else
                                {
                                    status = aRegistry->addConnection(kNodeName1, kChannelPath1, kBadNodeName, kChannelPath2, ""s,
                                                                      nImO::TransportType::kTCP);
                                    if (status.first)
                                    {
                                        ODL_LOG("! (status.first)"); //####
                                    }
                                    else
                                    {
                                        result = 0;
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
} // doTestConnectChannelsWithRegistryWithBadNodeName

#if defined(__APPLE__)
# pragma mark *** Test Case 390 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsFromEmptyRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getInformationForAllConnections()};

            if (statusWithInfo.first.first)
            {
                nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

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
} // doTestGetConnectionsFromEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 391 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsForNodeFromRegistryWithOneConnection
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    auto    statusWithInfo{aRegistry->getInformationForAllConnectionsOnNode(kNodeName1)};

                                    if (statusWithInfo.first.first)
                                    {
                                        nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

                                        if (1 == infoVector.size())
                                        {
                                            nImO::ConnectionInfo &  connection{infoVector[0]};

                                            if ((connection._fromNode == kNodeName1) && (connection._fromPath == kChannelPath1) &&
                                                (connection._toNode == kNodeName2) && (connection._toPath == kChannelPath2) &&
                                                (connection._dataType == ""s) && (connection._mode == nImO::TransportType::kTCP))
                                            {
                                                result = 0;
                                            }
                                            else
                                            {
                                                ODL_LOG("! ((connection._fromNode == kNodeName1) && " //####
                                                        "(connection._fromPath == kChannelPath1) && (connection._toNode == kNodeName2) && " //####
                                                        "(connection._toPath == kChannelPath2) && (connection._dataType == \"\"s) && " //####
                                                        "(connection._mode == nImO::TransportType::kTCP))"); //####
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetConnectionsForNodeFromRegistryWithOneConnection

#if defined(__APPLE__)
# pragma mark *** Test Case 392 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsForNodeFromRegistryWithTwoConnections
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addChannel(kNodeName1, kChannelPath2, false, "blort"s, nImO::TransportType::kUDP);
                                if (status.first)
                                {
                                    status = aRegistry->addChannel(kNodeName2, kChannelPath1, true, "blort"s, nImO::TransportType::kAny);
                                    if (status.first)
                                    {
                                        status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                          nImO::TransportType::kTCP);
                                        if (status.first)
                                        {
                                            status = aRegistry->addConnection(kNodeName2, kChannelPath1, kNodeName1, kChannelPath2, "blort",
                                                                              nImO::TransportType::kUDP);
                                            if (status.first)
                                            {
                                                auto    statusWithInfo{aRegistry->getInformationForAllConnectionsOnNode(kNodeName1)};

                                                if (statusWithInfo.first.first)
                                                {
                                                    nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

                                                    if (2 == infoVector.size())
                                                    {
                                                        nImO::ConnectionInfo &  connection1{infoVector[0]};
                                                        nImO::ConnectionInfo &  connection2{infoVector[1]};

                                                        if (((connection1._fromNode == kNodeName1) && (connection1._fromPath == kChannelPath1) &&
                                                            (connection1._toNode == kNodeName2) && (connection1._toPath == kChannelPath2) &&
                                                            (connection1._dataType == ""s) && (connection1._mode == nImO::TransportType::kTCP) &&
                                                            (connection2._fromNode == kNodeName2) && (connection2._fromPath == kChannelPath1) &&
                                                            (connection2._toNode == kNodeName1) && (connection2._toPath == kChannelPath2) &&
                                                            (connection2._dataType == "blort"s) && (connection2._mode == nImO::TransportType::kUDP)) ||
                                                            ((connection2._fromNode == kNodeName1) && (connection2._fromPath == kChannelPath1) &&
                                                            (connection2._toNode == kNodeName2) && (connection2._toPath == kChannelPath2) &&
                                                            (connection2._dataType == ""s) && (connection2._mode == nImO::TransportType::kTCP) &&
                                                            (connection1._fromNode == kNodeName2) && (connection1._fromPath == kChannelPath1) &&
                                                            (connection1._toNode == kNodeName1) && (connection1._toPath == kChannelPath2) &&
                                                            (connection1._dataType == "blort"s) && (connection1._mode == nImO::TransportType::kUDP)))
                                                        {
                                                            result = 0;
                                                        }
                                                        else
                                                        {
                                                            ODL_LOG("! (((connection1._fromNode == kNodeName1) && " //####
                                                                    "(connection1._fromPath == kChannelPath1) && " //####
                                                                    "(connection1._toNode == kNodeName2) && " //####
                                                                    "(connection1._toPath == kChannelPath2) && " //####
                                                                    "(connection1._dataType == \"\"s) && "//####
                                                                    "(connection1._mode == nImO::TransportType::kTCP) && " //####
                                                                    "(connection2._fromNode == kNodeName2) && " //####
                                                                    "(connection2._fromPath == kChannelPath1) && " //####
                                                                    "(connection2._toNode == kNodeName1) && " //####
                                                                    "(connection2._toPath == kChannelPath2) && " //####
                                                                    "(connection2._dataType == \"blort\"s) && " //####
                                                                    "(connection2._mode == nImO::TransportType::kUDP)) || " //####
                                                                    "((connection2._fromNode == kNodeName1) && " //####
                                                                    "(connection2._fromPath == kChannelPath1) && " //####
                                                                    "(connection2._toNode == kNodeName2) && " //####
                                                                    "(connection2._toPath == kChannelPath2) && " //####
                                                                    "(connection2._dataType == \"\"s) && " //####
                                                                    "(connection2._mode == nImO::TransportType::kTCP) && " //####
                                                                    "(connection1._fromNode == kNodeName2) && " //####
                                                                    "(connection1._fromPath == kChannelPath1) && " //####
                                                                    "(connection1._toNode == kNodeName1) && " //####
                                                                    "(connection1._toPath == kChannelPath2) && " //####
                                                                    "(connection1._dataType == \"blort\"s) && " //####
                                                                    "(connection1._mode == nImO::TransportType::kUDP)))"); //####
                                                        }
                                                    }
                                                    else
                                                    {
                                                        ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetConnectionsForNodeFromRegistryWithTwoConnections

#if defined(__APPLE__)
# pragma mark *** Test Case 393 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsForNodesFromRegistryWithTwoNodesWithConnections
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addChannel(kNodeName1, kChannelPath2, false, "blort"s, nImO::TransportType::kUDP);
                                if (status.first)
                                {
                                    status = aRegistry->addChannel(kNodeName2, kChannelPath1, true, "blort"s, nImO::TransportType::kAny);
                                    if (status.first)
                                    {
                                        status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                          nImO::TransportType::kTCP);
                                        if (status.first)
                                        {
                                            status = aRegistry->addConnection(kNodeName2, kChannelPath1, kNodeName1, kChannelPath2, "blort",
                                                                              nImO::TransportType::kUDP);
                                            if (status.first)
                                            {
                                                auto    statusWithInfo{aRegistry->getInformationForAllConnections()};

                                                if (statusWithInfo.first.first)
                                                {
                                                    nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

                                                    if (2 == infoVector.size())
                                                    {
                                                        nImO::ConnectionInfo &  connection1{infoVector[0]};
                                                        nImO::ConnectionInfo &  connection2{infoVector[1]};

                                                        if (((connection1._fromNode == kNodeName1) && (connection1._fromPath == kChannelPath1) &&
                                                            (connection1._toNode == kNodeName2) && (connection1._toPath == kChannelPath2) &&
                                                            (connection1._dataType == ""s) && (connection1._mode == nImO::TransportType::kTCP) &&
                                                            (connection2._fromNode == kNodeName2) && (connection2._fromPath == kChannelPath1) &&
                                                            (connection2._toNode == kNodeName1) && (connection2._toPath == kChannelPath2) &&
                                                            (connection2._dataType == "blort"s) && (connection2._mode == nImO::TransportType::kUDP)) ||
                                                            ((connection2._fromNode == kNodeName1) && (connection2._fromPath == kChannelPath1) &&
                                                            (connection2._toNode == kNodeName2) && (connection2._toPath == kChannelPath2) &&
                                                            (connection2._dataType == ""s) && (connection2._mode == nImO::TransportType::kTCP) &&
                                                            (connection1._fromNode == kNodeName2) && (connection1._fromPath == kChannelPath1) &&
                                                            (connection1._toNode == kNodeName1) && (connection1._toPath == kChannelPath2) &&
                                                            (connection1._dataType == "blort"s) && (connection1._mode == nImO::TransportType::kUDP)))
                                                        {
                                                            result = 0;
                                                        }
                                                        else
                                                        {
                                                            ODL_LOG("! (((connection1._fromNode == kNodeName1) && " //####
                                                                    "(connection1._fromPath == kChannelPath1) && " //####
                                                                    "(connection1._toNode == kNodeName2) && " //####
                                                                    "(connection1._toPath == kChannelPath2) && " //####
                                                                    "(connection1._dataType == \"\"s) && "//####
                                                                    "(connection1._mode == nImO::TransportType::kTCP) && " //####
                                                                    "(connection2._fromNode == kNodeName2) && " //####
                                                                    "(connection2._fromPath == kChannelPath1) && " //####
                                                                    "(connection2._toNode == kNodeName1) && " //####
                                                                    "(connection2._toPath == kChannelPath2) && " //####
                                                                    "(connection2._dataType == \"blort\"s) && " //####
                                                                    "(connection2._mode == nImO::TransportType::kUDP)) || " //####
                                                                    "((connection2._fromNode == kNodeName1) && " //####
                                                                    "(connection2._fromPath == kChannelPath1) && " //####
                                                                    "(connection2._toNode == kNodeName2) && " //####
                                                                    "(connection2._toPath == kChannelPath2) && " //####
                                                                    "(connection2._dataType == \"\"s) && " //####
                                                                    "(connection2._mode == nImO::TransportType::kTCP) && " //####
                                                                    "(connection1._fromNode == kNodeName2) && " //####
                                                                    "(connection1._fromPath == kChannelPath1) && " //####
                                                                    "(connection1._toNode == kNodeName1) && " //####
                                                                    "(connection1._toPath == kChannelPath2) && " //####
                                                                    "(connection1._dataType == \"blort\"s) && " //####
                                                                    "(connection1._mode == nImO::TransportType::kUDP)))"); //####
                                                        }
                                                    }
                                                    else
                                                    {
                                                        ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetConnectionsForNodesFromRegistryWithTwoNodesWithConnections

#if defined(__APPLE__)
# pragma mark *** Test Case 394 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsForMachineFromRegistryWithOneConnection
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    auto    statusWithInfo{aRegistry->getInformationForAllConnectionsOnMachine(machineName)};

                                    if (statusWithInfo.first.first)
                                    {
                                        nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

                                        if (1 == infoVector.size())
                                        {
                                            nImO::ConnectionInfo &  connection{infoVector[0]};

                                            if ((connection._fromNode == kNodeName1) && (connection._fromPath == kChannelPath1) &&
                                                (connection._toNode == kNodeName2) && (connection._toPath == kChannelPath2) &&
                                                (connection._dataType == ""s) && (connection._mode == nImO::TransportType::kTCP))
                                            {
                                                result = 0;
                                            }
                                            else
                                            {
                                                ODL_LOG("! ((connection._fromNode == kNodeName1) && " //####
                                                        "(connection._fromPath == kChannelPath1) && (connection._toNode == kNodeName2) && " //####
                                                        "(connection._toPath == kChannelPath2) && (connection._dataType == \"\"s) && " //####
                                                        "(connection._mode == nImO::TransportType::kTCP))"); //####
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetConnectionsForMachineFromRegistryWithOneConnection

#if defined(__APPLE__)
# pragma mark *** Test Case 395 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsForMachineFromRegistryWithTwoConnections
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    machineName{nImO::GetShortComputerName()};
            auto    status{aRegistry->addMachine(machineName)};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addChannel(kNodeName1, kChannelPath2, false, "blort"s, nImO::TransportType::kUDP);
                                if (status.first)
                                {
                                    status = aRegistry->addChannel(kNodeName2, kChannelPath1, true, "blort"s, nImO::TransportType::kAny);
                                    if (status.first)
                                    {
                                        status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                          nImO::TransportType::kTCP);
                                        if (status.first)
                                        {
                                            status = aRegistry->addConnection(kNodeName2, kChannelPath1, kNodeName1, kChannelPath2, "blort",
                                                                              nImO::TransportType::kUDP);
                                            if (status.first)
                                            {
                                                auto    statusWithInfo{aRegistry->getInformationForAllConnectionsOnMachine(machineName)};

                                                if (statusWithInfo.first.first)
                                                {
                                                    nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

                                                    if (2 == infoVector.size())
                                                    {
                                                        nImO::ConnectionInfo &  connection1{infoVector[0]};
                                                        nImO::ConnectionInfo &  connection2{infoVector[1]};

                                                        if (((connection1._fromNode == kNodeName1) && (connection1._fromPath == kChannelPath1) &&
                                                            (connection1._toNode == kNodeName2) && (connection1._toPath == kChannelPath2) &&
                                                            (connection1._dataType == ""s) && (connection1._mode == nImO::TransportType::kTCP) &&
                                                            (connection2._fromNode == kNodeName2) && (connection2._fromPath == kChannelPath1) &&
                                                            (connection2._toNode == kNodeName1) && (connection2._toPath == kChannelPath2) &&
                                                            (connection2._dataType == "blort"s) && (connection2._mode == nImO::TransportType::kUDP)) ||
                                                            ((connection2._fromNode == kNodeName1) && (connection2._fromPath == kChannelPath1) &&
                                                            (connection2._toNode == kNodeName2) && (connection2._toPath == kChannelPath2) &&
                                                            (connection2._dataType == ""s) && (connection2._mode == nImO::TransportType::kTCP) &&
                                                            (connection1._fromNode == kNodeName2) && (connection1._fromPath == kChannelPath1) &&
                                                            (connection1._toNode == kNodeName1) && (connection1._toPath == kChannelPath2) &&
                                                            (connection1._dataType == "blort"s) && (connection1._mode == nImO::TransportType::kUDP)))
                                                        {
                                                            result = 0;
                                                        }
                                                        else
                                                        {
                                                            ODL_LOG("! (((connection1._fromNode == kNodeName1) && " //####
                                                                    "(connection1._fromPath == kChannelPath1) && " //####
                                                                    "(connection1._toNode == kNodeName2) && " //####
                                                                    "(connection1._toPath == kChannelPath2) && " //####
                                                                    "(connection1._dataType == \"\"s) && "//####
                                                                    "(connection1._mode == nImO::TransportType::kTCP) && " //####
                                                                    "(connection2._fromNode == kNodeName2) && " //####
                                                                    "(connection2._fromPath == kChannelPath1) && " //####
                                                                    "(connection2._toNode == kNodeName1) && " //####
                                                                    "(connection2._toPath == kChannelPath2) && " //####
                                                                    "(connection2._dataType == \"blort\"s) && " //####
                                                                    "(connection2._mode == nImO::TransportType::kUDP)) || " //####
                                                                    "((connection2._fromNode == kNodeName1) && " //####
                                                                    "(connection2._fromPath == kChannelPath1) && " //####
                                                                    "(connection2._toNode == kNodeName2) && " //####
                                                                    "(connection2._toPath == kChannelPath2) && " //####
                                                                    "(connection2._dataType == \"\"s) && " //####
                                                                    "(connection2._mode == nImO::TransportType::kTCP) && " //####
                                                                    "(connection1._fromNode == kNodeName2) && " //####
                                                                    "(connection1._fromPath == kChannelPath1) && " //####
                                                                    "(connection1._toNode == kNodeName1) && " //####
                                                                    "(connection1._toPath == kChannelPath2) && " //####
                                                                    "(connection1._dataType == \"blort\"s) && " //####
                                                                    "(connection1._mode == nImO::TransportType::kUDP)))"); //####
                                                        }
                                                    }
                                                    else
                                                    {
                                                        ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetConnectionsForMachineFromRegistryWithTwoConnections

#if defined(__APPLE__)
# pragma mark *** Test Case 396 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsWithBadNodeNameFromRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getInformationForAllConnectionsOnNode(kBadNodeName)};

            if (statusWithInfo.first.first)
            {
                nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

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
} // doTestGetConnectionsWithBadNodeNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 397 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionsWithBadMachineNameFromRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getInformationForAllConnectionsOnMachine(kBadMachineName)};

            if (statusWithInfo.first.first)
            {
                nImO::ConnectionInfoVector &    infoVector{statusWithInfo.second};

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
} // doTestGetConnectionsWithBadMachineNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 398 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionInfoWithEmptyRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInfo{aRegistry->getConnectionInformation(kNodeName1, kChannelPath1, false)};

            if (statusWithInfo.first.first)
            {
                nImO::ConnectionInfo &  info1{statusWithInfo.second};

                if (info1._found)
                {
                    ODL_LOG("(info1._found)"); //####
                }
                else
                {
                    statusWithInfo = aRegistry->getConnectionInformation(kNodeName1, kChannelPath1, true);
                    if (statusWithInfo.first.first)
                    {
                        nImO::ConnectionInfo &  info2{statusWithInfo.second};

                        if (info2._found)
                        {
                            ODL_LOG("(info2._found)"); //####
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
} // doTestGetConnectionInfoWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 399 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionInfoInRegistryWithOneConnection
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    auto    statusWithInfo{aRegistry->getConnectionInformation(kNodeName1, kChannelPath1, false)};

                                    if (statusWithInfo.first.first)
                                    {
                                        nImO::ConnectionInfo &  connection1{statusWithInfo.second};

                                        if (connection1._found)
                                        {
                                            ODL_LOG("(connection1._found)"); //####
                                        }
                                        else
                                        {
                                            statusWithInfo = aRegistry->getConnectionInformation(kNodeName1, kChannelPath1, true);
                                            if (statusWithInfo.first.first)
                                            {
                                                nImO::ConnectionInfo &  connection2{statusWithInfo.second};

                                                if (connection2._found && (connection2._fromNode == kNodeName1) &&
                                                    (connection2._fromPath == kChannelPath1) && (connection2._toNode == kNodeName2) &&
                                                    (connection2._toPath == kChannelPath2) && (connection2._dataType == ""s) &&
                                                    (connection2._mode == nImO::TransportType::kTCP))
                                                {
                                                    result = 0;
                                                }
                                                else
                                                {
                                                    ODL_LOG("! (connection2._found && (connection2._fromNode == kNodeName1) && " //####
                                                            "(connection2._fromPath == kChannelPath1) && " //####
                                                            "(connection2._toNode == kNodeName2) && " //####
                                                            "(connection2._toPath == kChannelPath2) && (connection2._dataType == \"\"s) && " //####
                                                            "(connection2._mode == nImO::TransportType::kTCP))"); //####
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
} // doTestGetConnectionInfoInRegistryWithOneConnection

#if defined(__APPLE__)
# pragma mark *** Test Case 400 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionInfoWithBadNodeNameFromRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    auto    statusWithInfo{aRegistry->getConnectionInformation(kBadNodeName, kChannelPath1, false)};

                                    if (statusWithInfo.first.first)
                                    {
                                        ODL_LOG("(statusWithInfo.first.first)"); //####
                                    }
                                    else
                                    {
                                        statusWithInfo = aRegistry->getConnectionInformation(kBadNodeName, kChannelPath1, true);
                                        if (statusWithInfo.first.first)
                                        {
                                            ODL_LOG("(statusWithInfo.first.first)"); //####
                                        }
                                        else
                                        {
                                            result = 0;
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
} // doTestGetConnectionInfoWithBadNodeNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 401 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetConnectionInfoWithBadChannelNameFromRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                if (status.first)
                {
                    status = aRegistry->addChannel(kNodeName1, kChannelPath1, true, ""s, nImO::TransportType::kAny);
                    if (status.first)
                    {
                        status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::GenericService);
                        if (status.first)
                        {
                            status = aRegistry->addChannel(kNodeName2, kChannelPath2, false, ""s, nImO::TransportType::kTCP);
                            if (status.first)
                            {
                                status = aRegistry->addConnection(kNodeName1, kChannelPath1, kNodeName2, kChannelPath2, ""s,
                                                                  nImO::TransportType::kTCP);
                                if (status.first)
                                {
                                    auto    statusWithInfo{aRegistry->getConnectionInformation(kNodeName1, kBadChannelPath, false)};

                                    if (statusWithInfo.first.first)
                                    {
                                        ODL_LOG("(statusWithInfo.first.first)"); //####
                                    }
                                    else
                                    {
                                        statusWithInfo = aRegistry->getConnectionInformation(kNodeName1, kBadChannelPath, true);
                                        if (statusWithInfo.first.first)
                                        {
                                            ODL_LOG("(statusWithInfo.first.first)"); //####
                                        }
                                        else
                                        {
                                            result = 0;
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
} // doTestGetConnectionInfoWithBadChannelNameFromRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 500 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountApplicationsWithEmptyRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithInt{aRegistry->getNumberOfApplications()};

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
} // doTestCountApplicationsWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 501 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
TestAddApplicationWithOneLauncherToRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
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
} // TestAddApplicationWithOneLauncherToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 502 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountApplicationsInRegistryWithOneApplicationFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        auto    statusWithInt{aRegistry->getNumberOfApplications()};

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
} // doTestCountApplicationsInRegistryWithOneApplicationFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 503 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddTwoApplicationsFromOneLauncherToRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName2, kAppDescr2);
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
} // doTestAddTwoApplicationsFromOneLauncherToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 504 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountApplicationsInRegistryWithTwoApplicationsFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName2, kAppDescr2);
                        if (status.first)
                        {
                            auto    statusWithInt{aRegistry->getNumberOfApplications()};

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCountApplicationsInRegistryWithTwoApplicationsFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 505 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearApplicationsWithEmptyRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->clearAppListForLauncher(kNodeName1)};

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
} // doTestClearApplicationsWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 506 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearApplicationsInRegistryWithOneApplicationFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        status = aRegistry->clearAppListForLauncher(kNodeName1);
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
} // doTestClearApplicationsInRegistryWithOneApplicationFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 507 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountAfterClearApplicationsInRegistryWithOneApplicationFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        status = aRegistry->clearAppListForLauncher(kNodeName1);
                        if (status.first)
                        {
                            auto    statusWithInt{aRegistry->getNumberOfApplications()};

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCountAfterClearApplicationsInRegistryWithOneApplicationFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 508 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearApplicationsInRegistryWithTwoApplicationsFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        status = aRegistry->clearAppListForLauncher(kNodeName1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName1, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                status = aRegistry->clearAppListForLauncher(kNodeName1);
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
} // doTestClearApplicationsInRegistryWithTwoApplicationsFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 509 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountAfterClearApplicationsInRegistryWithTwoApplicationsFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        status = aRegistry->clearAppListForLauncher(kNodeName1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName1, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                status = aRegistry->clearAppListForLauncher(kNodeName1);
                                if (status.first)
                                {
                                    auto    statusWithInt{aRegistry->getNumberOfApplications()};

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
} // doTestCountAfterClearApplicationsInRegistryWithTwoApplicationsFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 510 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestAddApplicationsFromTwoLaunchersToRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName2, kAppDescr2);
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
} // doTestAddApplicationsFromTwoLaunchersToRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 511 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountApplicationsInRegistryWithApplicationsFromTwoLaunchers
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                auto    statusWithInt{aRegistry->getNumberOfApplications()};

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
} // doTestCountApplicationsInRegistryWithApplicationsFromTwoLaunchers

#if defined(__APPLE__)
# pragma mark *** Test Case 512 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestClearApplicationsInRegistryWithApplicationsFromTwoLaunchers
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                status = aRegistry->clearAppListForLauncher(kNodeName1);
                                if (status.first)
                                {
                                    status = aRegistry->clearAppListForLauncher(kNodeName2);
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
} // doTestClearApplicationsInRegistryWithApplicationsFromTwoLaunchers

#if defined(__APPLE__)
# pragma mark *** Test Case 513 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountAfterClearApplicationsInRegistryWithApplicationsFromTwoLaunchers
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                status = aRegistry->clearAppListForLauncher(kNodeName1);
                                if (status.first)
                                {
                                    auto    statusWithInt{aRegistry->getNumberOfApplications()};

                                    if (statusWithInt.first.first)
                                    {
                                        if (1 == statusWithInt.second)
                                        {
                                            status = aRegistry->clearAppListForLauncher(kNodeName2);
                                            if (status.first)
                                            {
                                                statusWithInt = aRegistry->getNumberOfApplications();
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
} // doTestCountAfterClearApplicationsInRegistryWithApplicationsFromTwoLaunchers

#if defined(__APPLE__)
# pragma mark *** Test Case 514 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountApplicationsInRegistryWithOneApplicationFromOneLauncherPerLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        auto    statusWithInt{aRegistry->getNumberOfApplicationsOnNode(kNodeName1)};

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
} // doTestCountApplicationsInRegistryWithOneApplicationFromOneLauncherPerLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 515 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountApplicationsInRegistryWithApplicationsFromTwoLaunchersPerLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                auto    statusWithInt{aRegistry->getNumberOfApplicationsOnNode(kNodeName1)};

                                if (statusWithInt.first.first)
                                {
                                    if (1 == statusWithInt.second)
                                    {
                                        statusWithInt = aRegistry->getNumberOfApplicationsOnNode(kNodeName2);
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
} // doTestCountApplicationsInRegistryWithApplicationsFromTwoLaunchersPerLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 516 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetApplicationInformationInRegistryWithOneApplicationFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        auto    statusWithInfo{aRegistry->getInformationForAllApplications()};

                        if (statusWithInfo.first.first)
                        {
                            auto    infoVector{statusWithInfo.second};

                            if (1 == infoVector.size())
                            {
                                auto    walker{*infoVector.begin()};

                                if (walker._found && (kNodeName1 == walker._launcherName) && (kAppName1 == walker._appName) &&
                                    (kAppDescr1 == walker._appDescription))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("! (walker._found && (kNodeName1 == walker._launcherName) && " //####
                                            "(kAppName1 == walker._appName) && (kAppDescr1 == walker._appDescription))"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetApplicationInformationInRegistryWithOneApplicationFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 517 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetApplicationInformationInRegistryWithTwoApplicationsFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                {
                        status = aRegistry->addAppToList(kNodeName1, kAppName2, kAppDescr2);
                        if (status.first)
                        {
                            auto    statusWithInfo{aRegistry->getInformationForAllApplications()};

                            if (statusWithInfo.first.first)
                            {
                                auto    infoVector{statusWithInfo.second};

                                if (2 == infoVector.size())
                                {
                                    auto    elem1{infoVector[0]};
                                    auto    elem2{infoVector[1]};

                                    if (elem1._found && (kNodeName1 == elem1._launcherName) && (kAppName1 == elem1._appName) &&
                                        (kAppDescr1 == elem1._appDescription) && elem2._found && (kNodeName1 == elem2._launcherName) &&
                                        (kAppName2 == elem2._appName) && (kAppDescr2 == elem2._appDescription))
                                    {
                                        result = 0;
                                    }
                                    else if (elem1._found && (kNodeName1 == elem1._launcherName) && (kAppName2 == elem1._appName) &&
                                             (kAppDescr2 == elem1._appDescription) && elem2._found && (kNodeName1 == elem2._launcherName) &&
                                             (kAppName1 == elem2._appName) && (kAppDescr1 == elem2._appDescription))
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("! (elem1._found && (kNodeName1 == elem1._launcherName) && " //####
                                                "(kAppName2 == elem1._appName) && (kAppDescr2 == elem1._appDescription) && " //####
                                                "elem2._found && (kNodeName1 == elem2._launcherName) && " //####
                                                "(kAppName1 == elem2._appName) && (kAppDescr1 == elem2._appDescription))"); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (2 == infoVector.size())"); //####
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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;

    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestGetApplicationInformationInRegistryWithTwoApplicationsFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 518 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetApplicationInformationInRegistryWithApplicationsFromTwoLaunchers
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                auto    statusWithInfo{aRegistry->getInformationForAllApplications()};

                                if (statusWithInfo.first.first)
                                {
                                    auto    infoVector{statusWithInfo.second};

                                    if (2 == infoVector.size())
                                    {
                                        auto    elem1{infoVector[0]};
                                        auto    elem2{infoVector[1]};

                                        if (elem1._found && (kNodeName1 == elem1._launcherName) && (kAppName1 == elem1._appName) &&
                                            (kAppDescr1 == elem1._appDescription) && elem2._found && (kNodeName2 == elem2._launcherName) &&
                                            (kAppName2 == elem2._appName) && (kAppDescr2 == elem2._appDescription))
                                        {
                                            result = 0;
                                        }
                                        else if (elem1._found && (kNodeName2 == elem1._launcherName) && (kAppName2 == elem1._appName) &&
                                                 (kAppDescr2 == elem1._appDescription) && elem2._found && (kNodeName1 == elem2._launcherName) &&
                                                 (kAppName1 == elem2._appName) && (kAppDescr1 == elem2._appDescription))
                                        {
                                            result = 0;
                                        }
                                        else
                                        {
                                            ODL_LOG("! (elem1._found && (kNodeName2 == elem1._launcherName) && " //####
                                                    "(kAppName2 == elem1._appName) && (kAppDescr2 == elem1._appDescription) && " //####
                                                    "elem2._found && (kNodeName1 == elem2._launcherName) && " //####
                                                    "(kAppName1 == elem2._appName) && (kAppDescr1 == elem2._appDescription))"); //####
                                        }
                                    }
                                    else
                                    {
                                        ODL_LOG("! (2 == infoVector.size())"); //####
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
} // doTestGetApplicationInformationInRegistryWithApplicationsFromTwoLaunchers

#if defined(__APPLE__)
# pragma mark *** Test Case 519 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetApplicationInformationInRegistryWithOneApplicationFromOneLauncherPerLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        auto    statusWithInfo{aRegistry->getInformationForAllApplicationsOnNode(kNodeName1)};

                        if (statusWithInfo.first.first)
                        {
                            auto    infoVector{statusWithInfo.second};

                            if (1 == infoVector.size())
                            {
                                auto    elem1{infoVector[0]};

                                if (elem1._found && (kNodeName1 == elem1._launcherName) && (kAppName1 == elem1._appName) &&
                                    (kAppDescr1 == elem1._appDescription))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("! (elem1._found && (kNodeName1 == elem1._launcherName) && " //####
                                            "(kAppName1 == elem1._appName) && (kAppDescr1 == elem1._appDescription))"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetApplicationInformationInRegistryWithOneApplicationFromOneLauncherPerLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 520 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetApplicationInformationInRegistryWithApplicationsFromTwoLaunchersPerLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName2, kAppDescr2);
                            if (status.first)
                            {
                                auto    statusWithInfo{aRegistry->getInformationForAllApplicationsOnNode(kNodeName1)};

                                if (statusWithInfo.first.first)
                                {
                                    auto    infoVector{statusWithInfo.second};

                                    if (1 == infoVector.size())
                                    {
                                        auto    elem1{infoVector[0]};

                                        if (elem1._found && (kNodeName1 == elem1._launcherName) && (kAppName1 == elem1._appName) &&
                                            (kAppDescr1 == elem1._appDescription))
                                        {
                                            statusWithInfo = aRegistry->getInformationForAllApplicationsOnNode(kNodeName2);
                                            if (statusWithInfo.first.first)
                                            {
                                                infoVector = statusWithInfo.second;
                                                if (1 == infoVector.size())
                                                {
                                                    auto    elem2{infoVector[0]};

                                                    if (elem2._found && (kNodeName2 == elem2._launcherName) && (kAppName2 == elem2._appName) &&
                                                        (kAppDescr2 == elem2._appDescription))
                                                    {
                                                        result = 0;
                                                    }
                                                    else
                                                    {
                                                        ODL_LOG("! (elem2._found && (kNodeName2 == elem2._launcherName) && " //####
                                                                "(kAppName2 == elem2._appName) && (kAppDescr2 == elem2._appDescription))"); //####
                                                    }
                                                }
                                                else
                                                {
                                                    ODL_LOG("! (1 == infoVector.size())"); //####
                                                }
                                            }
                                            else
                                            {
                                                ODL_LOG("! (statusWithInfo.first.first)"); //####
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (elem1._found && (kNodeName1 == elem1._launcherName) && " //####
                                                    "(kAppName1 == elem1._appName) && (kAppDescr1 == elem1._appDescription))"); //####
                                        }
                                    }
                                    else
                                    {
                                        ODL_LOG("! (1 == infoVector.size())"); //####
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
} // doTestGetApplicationInformationInRegistryWithApplicationsFromTwoLaunchersPerLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 521 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetNodeNamesInRegistryWithEmptyRegistry
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    statusWithNames{aRegistry->getNodesWithApplication(kAppName1)};

            if (statusWithNames.first.first)
            {
                if (0 == statusWithNames.second.size())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == statusWithNames.size())"); //####
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
} // doTestGetNodeNamesInRegistryWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 522 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetNodeNamesInRegistryWithOneUnmatchingApplicationFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        auto    statusWithNames{aRegistry->getNodesWithApplication(kAppName2)};

                        if (statusWithNames.first.first)
                        {
                            if (0 == statusWithNames.second.size())
                            {
                                result = 0;
                            }
                            else
                            {
                                ODL_LOG("! (0 == statusWithNames.size())"); //####
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
} // doTestGetNodeNamesInRegistryWithOneUnmatchingApplicationFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 523 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetNodeNamesInRegistryWithOneUnmatchingApplicationFromTwoLaunchers
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName1, kAppDescr1);
                            if (status.first)
                            {
                                auto    statusWithNames{aRegistry->getNodesWithApplication(kAppName2)};

                                if (statusWithNames.first.first)
                                {
                                    if (0 == statusWithNames.second.size())
                                    {
                                        result = 0;
                                    }
                                    else
                                    {
                                        ODL_LOG("! (0 == statusWithNames.size())"); //####
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
} // doTestGetNodeNamesInRegistryWithOneUnmatchingApplicationFromTwoLaunchers

#if defined(__APPLE__)
# pragma mark *** Test Case 524 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetNodeNamesInRegistryWithOneMatchingApplicationFromOneLauncher
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                    if (status.first)
                    {
                        auto    statusWithNames{aRegistry->getNodesWithApplication(kAppName1)};

                        if (statusWithNames.first.first)
                        {
                            if (1 == statusWithNames.second.size())
                            {
                                if (statusWithNames.second.end() != statusWithNames.second.find(kNodeName1))
                                {
                                    result = 0;
                                }
                                else
                                {
                                    ODL_LOG("! (statusWithNames.second.end() != statusWithNames.second.find(kNodeName1))"); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (1 == statusWithNames.size())"); //####
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
} // doTestGetNodeNamesInRegistryWithOneMatchingApplicationFromOneLauncher

#if defined(__APPLE__)
# pragma mark *** Test Case 525 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestGetNodeNamesInRegistryWithOneMatchingApplicationFromTwoLaunchers
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
        auto    aRegistry{std::make_unique<nImO::Registry>(context)};

        if (nullptr == aRegistry)
        {
            ODL_LOG("(nullptr == aRegistry)"); //####
        }
        else
        {
            auto    status{aRegistry->addMachine(nImO::GetShortComputerName())};

            if (status.first)
            {
                status = aRegistry->addNode(kNodeName1, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                if (status.first)
                {
                    status = aRegistry->addNode(kNodeName2, execPath, currentDir, commandLine, nImO::ServiceType::LauncherService);
                    if (status.first)
                    {
                        status = aRegistry->addAppToList(kNodeName1, kAppName1, kAppDescr1);
                        if (status.first)
                        {
                            status = aRegistry->addAppToList(kNodeName2, kAppName1, kAppDescr1);
                            if (status.first)
                            {
                                auto    statusWithNames{aRegistry->getNodesWithApplication(kAppName1)};

                                if (statusWithNames.first.first)
                                {
                                    if (2 == statusWithNames.second.size())
                                    {
                                        if (statusWithNames.second.end() != statusWithNames.second.find(kNodeName1))
                                        {
                                            if (statusWithNames.second.end() != statusWithNames.second.find(kNodeName2))
                                            {
                                                result = 0;
                                            }
                                            else
                                            {
                                                ODL_LOG("! (statusWithNames.second.end() != statusWithNames.second.find(kNodeName2))"); //####
                                            }
                                        }
                                        else
                                        {
                                            ODL_LOG("! (statusWithNames.second.end() != statusWithNames.second.find(kNodeName1))"); //####
                                        }
                                    }
                                    else
                                    {
                                        ODL_LOG("! (2 == statusWithNames.size())"); //####
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
} // doTestGetNodeNamesInRegistryWithOneMatchingApplicationFromTwoLaunchers

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
        auto    ourContext{std::make_shared<nImO::ServiceContext>(argc, argv, progName)};

        if (0 < --argc)
        {
            int64_t selector;

            if (ConvertToInt64(argv[1], selector) && (0 < selector))
            {
                auto    execPath{nImO::GetPathToExecutable()};
                auto    currentDir{boost::filesystem::current_path().string()};
                auto    commandLine{nImO::MakeStringFromCommandLine(argc - 1, argv + 1)};

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

                    case 127 :
                        result = doTestNodeInfoWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
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
                        result = doTestCountConnectionsWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                commandLine);
                        break;

                    case 381 :
                        result = doTestAddConnectionToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 382 :
                        result = doTestCountConnectionsInRegistryWithOneConnection(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                          commandLine);
                        break;

                    case 383 :
                        result = doTestAddTwoConnectionsToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 384 :
                        result = doTestCountConnectionsInRegistryWithTwoConnections(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                    commandLine);
                        break;

                    case 385 :
                        result = doTestRemoveOneConnectionFromRegistryViaFrom(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                              commandLine);
                        break;

                    case 386 :
                        result = doTestRemoveOneConnectionFromRegistryViaTo(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 387 :
                        result = doTestCountConnectionsWithRegistryWithOneConnectionRemoved(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                            currentDir, commandLine);
                        break;

                    case 388 :
                        result = doTestConnectChannelsWithRegistryWithBadChannelName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                     commandLine);
                        break;

                    case 389 :
                        result = doTestConnectChannelsWithRegistryWithBadNodeName(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                  commandLine);
                        break;

                    case 390 :
                        result = doTestGetConnectionsFromEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 391 :
                        result = doTestGetConnectionsForNodeFromRegistryWithOneConnection(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                          commandLine);
                        break;

                    case 392 :
                        result = doTestGetConnectionsForNodeFromRegistryWithTwoConnections(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                           currentDir, commandLine);
                        break;

                    case 393 :
                        result = doTestGetConnectionsForNodesFromRegistryWithTwoNodesWithConnections(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                     currentDir, commandLine);
                        break;

                    case 394 :
                        result = doTestGetConnectionsForMachineFromRegistryWithOneConnection(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                             currentDir, commandLine);
                        break;

                    case 395 :
                        result = doTestGetConnectionsForMachineFromRegistryWithTwoConnections(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                              currentDir, commandLine);
                        break;

                    case 396 :
                        result = doTestGetConnectionsWithBadNodeNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                        commandLine);
                        break;

                    case 397 :
                        result = doTestGetConnectionsWithBadMachineNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                           currentDir, commandLine);
                        break;

                    case 398 :
                        result = doTestGetConnectionInfoWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 399 :
                        result = doTestGetConnectionInfoInRegistryWithOneConnection(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                    commandLine);
                        break;

                    case 400 :
                        result = doTestGetConnectionInfoWithBadNodeNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                    commandLine);
                        break;

                    case 401 :
                        result = doTestGetConnectionInfoWithBadChannelNameFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                       commandLine);
                        break;

                    case 500 :
                        result = doTestCountApplicationsWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 501 :
                        result = TestAddApplicationWithOneLauncherToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                             commandLine);
                        break;

                    case 502 :
                        result = doTestCountApplicationsInRegistryWithOneApplicationFromOneLauncher(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                    currentDir, commandLine);
                        break;

                    case 503 :
                        result = doTestAddTwoApplicationsFromOneLauncherToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                   commandLine);
                        break;

                    case 504 :
                        result = doTestCountApplicationsInRegistryWithTwoApplicationsFromOneLauncher(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                     currentDir, commandLine);
                        break;

                    case 505 :
                        result = doTestClearApplicationsWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 506 :
                        result = doTestClearApplicationsInRegistryWithOneApplicationFromOneLauncher(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                    currentDir, commandLine);
                        break;

                    case 507 :
                        result = doTestCountAfterClearApplicationsInRegistryWithOneApplicationFromOneLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                              execPath, currentDir, commandLine);
                        break;

                    case 508 :
                        result = doTestClearApplicationsInRegistryWithTwoApplicationsFromOneLauncher(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                     currentDir, commandLine);
                        break;

                    case 509 :
                        result = doTestCountAfterClearApplicationsInRegistryWithTwoApplicationsFromOneLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                               execPath, currentDir, commandLine);
                        break;

                    case 510 :
                        result = doTestAddApplicationsFromTwoLaunchersToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                 commandLine);
                        break;

                    case 511 :
                        result = doTestCountApplicationsInRegistryWithApplicationsFromTwoLaunchers(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                   currentDir, commandLine);
                        break;

                    case 512 :
                        result = doTestClearApplicationsInRegistryWithApplicationsFromTwoLaunchers(*argv, argc - 1, argv + 2, ourContext, execPath,
                                                                                                   currentDir, commandLine);
                        break;

                    case 513 :
                        result = doTestCountAfterClearApplicationsInRegistryWithApplicationsFromTwoLaunchers(*argv, argc - 1, argv + 2, ourContext,
                                                                                                             execPath, currentDir, commandLine);
                        break;

                    case 514 :
                        result = doTestCountApplicationsInRegistryWithOneApplicationFromOneLauncherPerLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                               execPath, currentDir, commandLine);
                        break;

                    case 515 :
                        result = doTestCountApplicationsInRegistryWithApplicationsFromTwoLaunchersPerLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                              execPath, currentDir, commandLine);
                        break;

                    case 516 :
                        result = doTestGetApplicationInformationInRegistryWithOneApplicationFromOneLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                            execPath, currentDir, commandLine);
                        break;

                    case 517 :
                        result = doTestGetApplicationInformationInRegistryWithTwoApplicationsFromOneLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                             execPath, currentDir, commandLine);
                        break;

                    case 518 :
                        result = doTestGetApplicationInformationInRegistryWithApplicationsFromTwoLaunchers(*argv, argc - 1, argv + 2, ourContext,
                                                                                                           execPath, currentDir, commandLine);
                        break;

                    case 519 :
                        result = doTestGetApplicationInformationInRegistryWithOneApplicationFromOneLauncherPerLauncher(*argv, argc - 1, argv + 2,
                                                                                                                       ourContext, execPath,
                                                                                                                       currentDir, commandLine);
                        break;

                    case 520 :
                        result = doTestGetApplicationInformationInRegistryWithApplicationsFromTwoLaunchersPerLauncher(*argv, argc - 1, argv + 2,
                                                                                                                      ourContext, execPath,
                                                                                                                      currentDir, commandLine);
                        break;

                    case 521 :
                        result = doTestGetNodeNamesInRegistryWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                               commandLine);
                        break;

                    case 522 :
                        result = doTestGetNodeNamesInRegistryWithOneUnmatchingApplicationFromOneLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                         execPath, currentDir, commandLine);
                        break;

                    case 523 :
                        result = doTestGetNodeNamesInRegistryWithOneUnmatchingApplicationFromTwoLaunchers(*argv, argc - 1, argv + 2, ourContext,
                                                                                                          execPath, currentDir, commandLine);
                        break;

                    case 524 :
                        result = doTestGetNodeNamesInRegistryWithOneMatchingApplicationFromOneLauncher(*argv, argc - 1, argv + 2, ourContext,
                                                                                                       execPath, currentDir, commandLine);
                        break;

                    case 525 :
                        result = doTestGetNodeNamesInRegistryWithOneMatchingApplicationFromTwoLaunchers(*argv, argc - 1, argv + 2, ourContext,
                                                                                                        execPath, currentDir, commandLine);
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

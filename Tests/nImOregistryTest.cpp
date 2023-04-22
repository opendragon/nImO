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
# pragma mark *** Test Case 03 ***
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
# pragma mark *** Test Case 04 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindWithEmptyRegistry
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
                    ODL_LOG("(statusWithInt.second)"); //####
                }
                else
                {
                    statusWithBool = aRegistry->isNodePresent(NODE_NAME_2);
                    if (statusWithBool.first.first)
                    {
                        if (statusWithBool.second)
                        {
                            ODL_LOG("(statusWithInt.second)"); //####
                        }
                        else
                        {
                            result = 0;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (statusWithInt.first.first)"); //####
                    }
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
} // doTestFindWithEmptyRegistry

#if defined(__APPLE__)
# pragma mark *** Test Case 05 ***
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
# pragma mark *** Test Case 06 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountWithRegistryWithOneNode
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCountWithRegistryWithOneNode

#if defined(__APPLE__)
# pragma mark *** Test Case 07 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
# pragma mark *** Test Case 08 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindWithRegistryWithOneNode
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestFindWithRegistryWithOneNode

#if defined(__APPLE__)
# pragma mark *** Test Case 09 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
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
# pragma mark *** Test Case 10 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
# pragma mark *** Test Case 11 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountWithRegistryWithNodeRemoved
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCountWithRegistryWithNodeRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 12 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
# pragma mark *** Test Case 13 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindWithRegistryNodeRemoved
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestFindWithRegistryNodeRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 14 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
# pragma mark *** Test Case 15 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountWithRegistryWithTwoNodes
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCountWithRegistryWithTwoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 16 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
# pragma mark *** Test Case 17 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindWithRegistryWithTwoNodes
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestFindWithRegistryWithTwoNodes

#if defined(__APPLE__)
# pragma mark *** Test Case 18 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
# pragma mark *** Test Case 19 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestCountWithRegistryWithAllNodesRemoved
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestCountWithRegistryWithAllNodesRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 20 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestTestNodeSetWithRegistryWithAllNodesRemoved
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestTestNodeSetWithRegistryWithAllNodesRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 21 ***
#endif // defined(__APPLE__)

/*! @brief Perform a test case.
 @param[in] launchPath The command-line name used to launch the service.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used for the test.
 @return @c 0 on success and @c 1 on failure. */
static int
doTestFindWithRegistryAllNodesRemoved
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result); //####
    return result;
} // doTestFindWithRegistryAllNodesRemoved

#if defined(__APPLE__)
# pragma mark *** Test Case 22 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine,
                                                                    nImO::ServiceType::GenericService);

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
# pragma mark *** Test Case 23 ***
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
# pragma mark *** Test Case 24 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
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
# pragma mark *** Test Case 25 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                                    nImO::Connection(randomAddress1, randomPort1));

            if (status.first)
            {
                uint32_t    randomAddress2 = StaticCast(uint32_t, nImO::RandomUnsigned());
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
                                        (randomAddress2 == secondElem._connection._address) && (randomPort2 == secondElem._connection._port) &&
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
                                        (randomAddress1 == secondElem._connection._address) && (randomPort1 == secondElem._connection._port) &&
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
# pragma mark *** Test Case 26 ***
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
# pragma mark *** Test Case 27 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
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
# pragma mark *** Test Case 28 ***
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
            nImO::RegSuccessOrFailure   status = aRegistry->addNode(NODE_NAME_1, execPath, currentDir, commandLine, nImO::ServiceType::FilterService,
                                                                    nImO::Connection(randomAddress1, randomPort1));

            if (status.first)
            {
                uint32_t    randomAddress2 = StaticCast(uint32_t, nImO::RandomUnsigned());
                uint16_t    randomPort2 = StaticCast(uint16_t, nImO::RandomUnsigned());

                status = aRegistry->addNode(NODE_NAME_2, "!" + execPath, "?" + currentDir, "^" + commandLine, nImO::ServiceType::LauncherService,
                                            nImO::Connection(randomAddress2, randomPort2));
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
                        result = doTestEmptyRegistryForNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 3 :
                        result = doTestNodeSetWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;
                        
                    case 4 :
                        result = doTestFindWithEmptyRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 5 :
                        result = doTestAddNodeToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 6 :
                        result = doTestCountWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 7 :
                        result = doTestNodeSetWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 8 :
                        result = doTestFindWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 9 :
                        result = doTestNodeDataAddedToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 10 :
                        result = doTestRemoveNodeFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 11 :
                        result = doTestCountWithRegistryWithNodeRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 12 :
                        result = doTestNodeSetWithRegistryWithNodeRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 13 :
                        result = doTestFindWithRegistryNodeRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 14 :
                        result = doTestAddTwoDistinctNodesToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 15 :
                        result = doTestCountWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 16 :
                        result = doTestNodeSetWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 17 :
                        result = doTestFindWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 18 :
                        result = doTestRemoveNodesFromRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 19 :
                        result = doTestCountWithRegistryWithAllNodesRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 20 :
                        result = doTestTestNodeSetWithRegistryWithAllNodesRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
                                                                                  commandLine);
                        break;

                    case 21 :
                        result = doTestFindWithRegistryAllNodesRemoved(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 22 :
                        result = doTestAddTwoIdenticalNodesToRegistry(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 23 :
                        result = doTestNodeInfoWithRegistryWithNoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 24 :
                        result = doTestNodeInfoWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 25 :
                        result = doTestNodeInfoWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 26 :
                        result = doTestLaunchDetailsWithRegistryWithNoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 27 :
                        result = doTestLaunchDetailsWithRegistryWithOneNode(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir, commandLine);
                        break;

                    case 28 :
                        result = doTestLaunchDetailsWithRegistryWithTwoNodes(*argv, argc - 1, argv + 2, ourContext, execPath, currentDir,
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

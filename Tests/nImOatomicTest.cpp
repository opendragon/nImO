//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOatomicTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-03-22
//
//--------------------------------------------------------------------------------------------------

#include <nImO/nImOblob.hpp>
#include <nImO/nImObufferChunk.hpp>
#include <nImO/nImOdouble.hpp>
#include <nImO/nImOinteger.hpp>
#include <nImO/nImOlogical.hpp>
#include <nImO/nImOstring.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The test driver for the unit tests of the %nImO common library. */

/*! @namespace nImO::Test
 @brief The classes used for unit testing of the %nImO classes. */
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

/*! @brief The number of elements in a small test. */
static const size_t kSmallTestSize = 100;

/*! @brief The number of elements in a big test. */
static const size_t kBigTestSize = 100000;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief The signal handler to catch requests to stop the service.
 @param[in] signal The signal being handled. */
static void
catchSignal(int signal)
{
    ODL_ENTER(); //####
    ODL_LL1("signal = ", signal); //####
    std::stringstream buff;
    std::string       message("Exiting due to signal ");

    buff << signal;
    message += buff.str();
    message += " = ";
    message += NameOfSignal(signal);
#if 0
    nImO_ERROR_(message.c_str());
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

/*! @brief Compare a Value object with a string.
 @param[in] aValue The object to be compared.
 @param[in] aString The string to be compared to.
 @returns @c -1, @c 0 or @c 1 depending on where the string is greater than, equal to or less than
 the object representation as a string. */
static int
compareValueWithString(const Value &aValue,
                       const char        *aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    StringBuffer buff;
    int                result;
    size_t             length;

    aValue.printToStringBuffer(buff);
    result = strcmp(buff.getString(length), aString);
    ODL_S2("got: ", buff.getString(length), "expected: ", aString); //####
    ODL_EXIT_LL(result); //####
    return result;
} // compareValueWithString

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
doTestEmptyBufferChunk(const char *launchPath,
                       const int  argc,
                       char       **argv) // empty buffer chunk
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpBufferChunk stuff(new BufferChunk(false));

        if (stuff)
        {
            if (0 == stuff->getDataSize())
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == stuff->getDataSize())"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestEmptyBufferChunk
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
doTestBufferChunkWithSingleByte(const char *launchPath,
                                const int  argc,
                                char       **argv) // buffer chunk with 1 byte of data
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpBufferChunk stuff(new BufferChunk(false));

        if (stuff)
        {
            uint8_t data = (reinterpret_cast<intptr_t>(stuff.get()) &0x00FF);

            stuff->appendData(&data, sizeof(data));
            if (1 == stuff->getDataSize())
            {
                const uint8_t *storedData = stuff->getData();

                if (storedData && (data == *storedData))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (storedData && (data == *storedData))"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 == stuff->getDataSize())"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestBufferChunkWithSingleByte
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
doTestFilledBufferChunk(const char *launchPath,
                        const int  argc,
                        char       **argv) // buffer chunk filled with data
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpBufferChunk stuff(new BufferChunk(false));

        if (stuff)
        {
            size_t howMuch = stuff->getAvailableBytes();

            if (1 < howMuch)
            {
                uint8_t data = (reinterpret_cast<intptr_t>(stuff.get()) &0x00FF);

                for (size_t ii = 0; howMuch > ii; ++ii)
                {
                    uint8_t newData = static_cast<uint8_t>((data + ii) &0x00FF);

                    stuff->appendData(&newData, sizeof(newData));
                }
                if ((0 == stuff->getAvailableBytes()) && (howMuch == stuff->getDataSize()))
                {
                    const uint8_t *storedData = stuff->getData();

                    if (storedData)
                    {
                        result = 0;
                        for (size_t ii = 0; (0 == result) && (howMuch > ii); ++ii)
                        {
                            uint8_t aValue = storedData[ii];
                            uint8_t expectedValue = static_cast<uint8_t>((data + ii) &0x00FF);

                            if (aValue != expectedValue)
                            {
                                ODL_LOG("(aValue != expectedValue)"); //####
                                result = 1;
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (storedData)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (((0 == stuff->getAvailableBytes()) && (howMuch == " //####
                            "stuff->getDataSize()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 < howMuch)"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestFilledBufferChunk
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
doTestOverfilledBufferChunk(const char *launchPath,
                            const int  argc,
                            char       **argv) // buffer chunk overfilled with data
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpBufferChunk stuff(new BufferChunk(false));

        if (stuff)
        {
            size_t howMuch = stuff->getAvailableBytes();

            if (1 < howMuch)
            {
                uint8_t data = (reinterpret_cast<intptr_t>(stuff.get()) &0x00FF);

                for (size_t ii = 0; howMuch >= ii; ++ii)
                {
                    uint8_t newData = static_cast<uint8_t>((data + ii) &0x00FF);

                    stuff->appendData(&newData, sizeof(newData));
                }
                if ((0 == stuff->getAvailableBytes()) && (howMuch == stuff->getDataSize()))
                {
                    const uint8_t *storedData = stuff->getData();

                    if (storedData)
                    {
                        result = 0;
                        for (size_t ii = 0; (0 == result) && (howMuch > ii); ++ii)
                        {
                            uint8_t aValue = storedData[ii];
                            uint8_t expectedValue = static_cast<uint8_t>((data + ii) &0x00FF);

                            if (aValue != expectedValue)
                            {
                                ODL_LOG("(aValue != expectedValue)"); //####
                                result = 1;
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (storedData)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (((0 == stuff->getAvailableBytes()) && (howMuch == " //####
                            "stuff->getDataSize()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 < howMuch)"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestOverfilledBufferChunk
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
doTestBufferChunkReset(const char *launchPath,
                       const int  argc,
                       char       **argv) // resetting buffer chunk
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpBufferChunk stuff(new BufferChunk(false));

        if (stuff)
        {
            uint8_t data = (reinterpret_cast<intptr_t>(stuff.get()) &0x00FF);

            stuff->appendData(&data, sizeof(data));
            if (1 == stuff->getDataSize())
            {
                stuff->reset();
                if (0 == stuff->getDataSize())
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == stuff->getDataSize())"); //####
                }
            }
            else
            {
                ODL_LOG("! (1 == stuff->getDataSize())"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestBufferChunkReset
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 10 ***
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
doTestEmptyStringBuffer(const char *launchPath,
                        const int  argc,
                        char       **argv) // empty string buffer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpStringBuffer stuff(new StringBuffer);

        if (stuff)
        {
            if (0 == stuff->getLength())
            {
                size_t     length = 0;
                const char *outString = stuff->getString(length);

                if (outString)
                {
                    if ((0 == length) && (0 == strlen(outString)))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! ((0 == length) && (0 == strlen(outString)))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! outString"); //####
                }
            }
            else
            {
                ODL_LOG("! (0 == stuff->getLength())"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestEmptyStringBuffer
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 11 ***
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
doTestStringBufferWithCharacters(const char *launchPath,
                                 const int  argc,
                                 char       **argv) // string buffer with character string
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char           *inString = *argv;
            const char           *outString = argv[1];
            size_t               outLength = strlen(outString);
            UpStringBuffer stuff(new StringBuffer);

            if (stuff)
            {
                stuff->addString(inString);
                size_t resultLength = stuff->getLength();

                if (resultLength == outLength)
                {
                    const char *resultString = stuff->getString(resultLength);

                    if (resultString && (0 == strcmp(resultString, outString)))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (resultString && (0 == strcmp(resultString, " //####
                                "outString)))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (resultLength == outLength)"); //####
                }
            }
            else
            {
                ODL_LOG("! (stuff)"); //####
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
} // doTestStringBufferWithCharacters
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 12 ***
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
doTestStringBufferWithLogical(const char *launchPath,
                              const int  argc,
                              char       **argv) // string buffer with boolean
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char *outString = argv[1];
            int64_t    value;

            if (ConvertToLong(*argv, value) && (0 <= value))
            {
                UpStringBuffer stuff(new StringBuffer);

                if (stuff)
                {
                    bool asBool = (0 != value);

                    stuff->addBool(asBool);
                    size_t     length;
                    const char *resultString = stuff->getString(length);

                    if (0 == strcmp(outString, resultString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == strcmp(outString, resultString))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
                }
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
} // doTestStringBufferWithLogical
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 13 ***
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
doTestStringBufferWithInteger(const char *launchPath,
                              const int  argc,
                              char       **argv) // string buffer with integer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char *outString = argv[1];
            int64_t    value;

            if (ConvertToLong(*argv, value))
            {
                UpStringBuffer stuff(new StringBuffer);

                if (stuff)
                {
                    stuff->addLong(value);
                    size_t     length;
                    const char *resultString = stuff->getString(length);

                    if (0 == strcmp(outString, resultString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == strcmp(outString, resultString))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
                }
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
} // doTestStringBufferWithInteger
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 14 ***
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
doTestStringBufferWithString(const char *launchPath,
                             const int  argc,
                             char       **argv) // string buffer with string
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char           *inString = *argv;
            const char           *outString = argv[1];
            size_t               outLength = strlen(outString);
            UpStringBuffer stuff(new StringBuffer);

            if (stuff)
            {
                stuff->addString(inString, true);
                size_t resultLength = stuff->getLength();

                if (resultLength == outLength)
                {
                    const char *resultString = stuff->getString(resultLength);

                    if (resultString && (0 == strcmp(resultString, outString)))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (resultString && (0 == strcmp(resultString, " //####
                                "outString)))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (resultLength == outLength)"); //####
                }
            }
            else
            {
                ODL_LOG("! (stuff)"); //####
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
} // doTestStringBufferWithString
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 15 ***
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
doTestStringBufferWithSpecialCharacters(const char *launchPath,
                                        const int  argc,
                                        char       **argv) // string buffer with special chars
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        const char           *inString = "abc\tdef\f\rghi\302";
        const char           *outString = "\"abc\\tdef\\f\\rghi\\M-B\"";
        size_t               outLength = strlen(outString);
        UpStringBuffer stuff(new StringBuffer);

        if (stuff)
        {
            stuff->addString(inString, true);
            size_t resultLength = stuff->getLength();

            if (resultLength == outLength)
            {
                const char *resultString = stuff->getString(resultLength);

                if (resultString && (0 == strcmp(resultString, outString)))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (resultString && (0 == strcmp(resultString, outString)))"); //####
                }
            }
            else
            {
                ODL_LOG("! (resultLength == outLength)"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestStringBufferWithSpecialCharacters
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 16 ***
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
doTestStringBufferWithDouble(const char *launchPath,
                             const int  argc,
                             char       **argv) // string buffer with floating point
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char *outString = argv[1];
            double     value;

            if (ConvertToDouble(*argv, value))
            {
                UpStringBuffer stuff(new StringBuffer);

                if (stuff)
                {
                    stuff->addDouble(value);
                    size_t     length;
                    const char *resultString = stuff->getString(length);

                    for (result = 0; *outString && *resultString; ++outString, ++resultString)
                    {
                        char outChar = tolower(*outString);
                        char resultChar = tolower(*resultString);

                        if (outChar != resultChar)
                        {
                            break;
                        }

                    }
                    if (*outString || *resultString)
                    {
                        ODL_LOG("(*outString || *resultString)"); //####
                        result = 1;
                    }
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
                }
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
} // doTestStringBufferWithDouble
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 17 ***
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
doTestBigStringBuffer(const char *launchPath,
                      const int  argc,
                      char       **argv) // big string buffer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpStringBuffer stuff(new StringBuffer);

        if (stuff)
        {
            const char *bigString = "abcdefghijklmnopqrstuvwxyz0123456789";
            size_t     bigLength = strlen(bigString);

            for (size_t ii = 0; kBigTestSize > ii; ++ii)
            {
                stuff->addString(bigString);
            }
            size_t     length = 0;
            const char *resultString = stuff->getString(length);

            if ((bigLength * kBigTestSize) == length)
            {
                result = 0;
                for (size_t ii = 0; (0 == result) && (kBigTestSize > ii);
                     ++ii, resultString += bigLength)
                {
                    if (0 != CompareBytes(bigString, resultString, bigLength))
                    {
                        ODL_LOG("(0 != CompareBytes(bigString, resultString, " //####
                                "bigLength))"); //####
                        result = 1;
                    }
                }
            }
            else
            {
                ODL_LOG("! ((bigLength * kBigTestSize) == length)"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestBigStringBuffer
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 18 ***
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
doTestStringBufferWithEmptyBlob(const char *launchPath,
                                const int  argc,
                                char       **argv) // string buffer with empty blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpStringBuffer stuff(new StringBuffer);

        if (stuff)
        {
            stuff->addBytes(nullptr, 0);
            size_t     length;
            const char *resultString = stuff->getString(length);
            const char *expectedString = "%0%%";

            if (0 == strcmp(resultString, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == strcmp(resultString, expectedString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestStringBufferWithEmptyBlob
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 19 ***
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
doTestStringBufferWithSmallBlob(const char *launchPath,
                                const int  argc,
                                char       **argv) // string buffer with simple blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpStringBuffer stuff(new StringBuffer);

        if (stuff)
        {
            UpAuint8_t smallBlob(new uint8_t[kSmallTestSize]);

            if (smallBlob)
            {
                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    uint8_t *addr = smallBlob.get();
                    uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(addr) ^ ii);

                    smallBlob[ii] = aByte;
                }
                stuff->addBytes(smallBlob.get(), kSmallTestSize);
                size_t            length;
                const char        *resultString = stuff->getString(length);
                std::string       expectedString("%");
                std::stringstream buff;

                buff << kSmallTestSize;
                expectedString += buff.str() + "%";
                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    static char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
                    uint8_t     aByte = smallBlob[ii];
                    char        highByte = hexDigits[(aByte >> 4) &0x0F];
                    char        lowByte = hexDigits[aByte &0x0F];

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%";
                if (0 == strcmp(resultString, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == strcmp(resultString, expectedString.c_str()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (smallBlob)"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestStringBufferWithSmallBlob
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 20 ***
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
doTestStringBufferWithBigBlob(const char *launchPath,
                              const int  argc,
                              char       **argv) // string buffer with big blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpStringBuffer stuff(new StringBuffer);

        if (stuff)
        {
            UpAuint8_t bigBlob(new uint8_t[kBigTestSize]);

            if (bigBlob)
            {
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    uint8_t *addr = bigBlob.get();
                    uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(addr) ^ ii);

                    bigBlob[ii] = aByte;
                }
                stuff->addBytes(bigBlob.get(), kBigTestSize);
                size_t            length;
                const char        *resultString = stuff->getString(length);
                std::string       expectedString("%");
                std::stringstream buff;

                buff << kBigTestSize;
                expectedString += buff.str() + "%";
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    static char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
                    uint8_t     aByte = bigBlob[ii];
                    char        highByte = hexDigits[(aByte >> 4) &0x0F];
                    char        lowByte = hexDigits[aByte &0x0F];

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%";
                if (0 == strcmp(resultString, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == strcmp(resultString, expectedString.c_str()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (bigBlob)"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestStringBufferWithBigBlob
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 21 ***
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
doTestStringBufferReset(const char *launchPath,
                        const int  argc,
                        char       **argv) // resetting string buffer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpStringBuffer stuff(new StringBuffer);

        if (stuff)
        {
            stuff->addString("abcdef");
            stuff->reset();
            size_t resultLength = stuff->getLength();

            if (0 == resultLength)
            {
                const char *resultString = stuff->getString(resultLength);

                if (resultString && (0 == strlen(resultString)))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (resultString && (0 == strlen(resultString)))"); //####
                }
            }
            else
            {
                ODL_LOG("! (0 == stuff->getLength())"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestStringBufferReset
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 50 ***
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
doTestDefaultLogicalValue(const char *launchPath,
                          const int  argc,
                          char       **argv) // default boolean value
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        std::unique_ptr<Logical> stuff(new Logical);

        if (stuff)
        {
            if (0 == compareValueWithString(*stuff, "false"))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, \"false\"))"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestDefaultLogicalValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 51 ***
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
doTestLogicalValue(const char *launchPath,
                   const int  argc,
                   char       **argv) // boolean values
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char *outString = argv[1];
            int64_t    value;

            if (ConvertToLong(*argv, value) && (0 <= value))
            {
                std::unique_ptr<Logical> stuff(new Logical(0 != value));

                if (stuff)
                {
                    if (0 == compareValueWithString(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
                }
            }
            else
            {
                ODL_LOG("! ((startPtr != endPtr) && (! *endPtr) && (0 <= value))"); //####
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
} // doTestLogicalValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 52 ***
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
doTestDefaultIntegerValue(const char *launchPath,
                          const int  argc,
                          char       **argv) // default integer value
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        std::unique_ptr<Integer> stuff(new Integer);

        if (stuff)
        {
            if ((0 == compareValueWithString(*stuff, "0")) && (nullptr != stuff->asInteger()))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! ((0 == compareValueWithString(*stuff, \"0\")) && " //####
                        "(nullptr != stuff->asInteger()))"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestDefaultIntegerValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 53 ***
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
doTestNumberValue(const char *launchPath,
                  const int  argc,
                  char       **argv) // number values
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            const char *outString = argv[1];
            int64_t    intValue;

            if (ConvertToLong(*argv, intValue))
            {
                std::unique_ptr<Integer> stuff(new Integer(intValue));

                if (stuff)
                {
                    if (0 == compareValueWithString(*stuff, outString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
                }
            }
            else
            {
                double floatValue;

                if (ConvertToDouble(*argv, floatValue))
                {
                    std::unique_ptr<Double> stuff(new Double(floatValue));

                    if (stuff)
                    {
                        if (0 == compareValueWithString(*stuff, outString))
                        {
                            result = 0;
                        }
                        else
                        {
                            ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! (stuff)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! ((startPtr != endPtr) && (! *endPtr))"); //####
                }
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
} // doTestNumberValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 54 ***
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
doTestDefaultStringValue(const char *launchPath,
                         const int  argc,
                         char       **argv) // default string value
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpString stuff(new String);

        if (stuff)
        {
            if (0 == compareValueWithString(*stuff, "\"\""))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("(0 == compareValueWithString(*stuff, \"\\\"\\\"\"))"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestDefaultStringValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 55 ***
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
doTestStringValue(const char *launchPath,
                  const int  argc,
                  char       **argv) // string values
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        if (1 < argc)
        {
            UpString stuff(new String(*argv));

            if (stuff)
            {
                if (0 == compareValueWithString(*stuff, argv[1]))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, argv[1]))"); //####
                }
            }
            else
            {
                ODL_LOG("! (stuff)"); //####
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
} // doTestStringValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 56 ***
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
doTestStringValueWithEscapes(const char *launchPath,
                             const int  argc,
                             char       **argv) // string value with escapes
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        const char     *inString = "abc\tdef\f\rghi\302";
        const char     *outString = "\"abc\\tdef\\f\\rghi\\M-B\"";
        UpString stuff(new String(inString));

        if (stuff)
        {
            if (0 == compareValueWithString(*stuff, outString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, outString))"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestStringValueWithEscapes
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 57 ***
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
doTestDefaultBlobValue(const char *launchPath,
                       const int  argc,
                       char       **argv) // default blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        std::unique_ptr<Blob> stuff(new Blob);

        if (stuff)
        {
            if (0 == compareValueWithString(*stuff, "%0%%"))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, \"%0%%\"))"); //####
            }
        }
        else
        {
            ODL_LOG("! (stuff)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestDefaultBlobValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 58 ***
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
doTestSmallBlobValue(const char *launchPath,
                     const int  argc,
                     char       **argv) // small blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpAuint8_t smallBlob(new uint8_t[kSmallTestSize]);

        if (smallBlob)
        {
            for (size_t ii = 0; kSmallTestSize > ii; ++ii)
            {
                uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(smallBlob.get()) ^
                                                     ii);

                smallBlob[ii] = aByte;
            }
            std::unique_ptr<Blob> stuff(new Blob(smallBlob.get(), kSmallTestSize));

            if (stuff)
            {
                std::string       expectedString("%");
                std::stringstream buff;

                buff << kSmallTestSize;
                expectedString += buff.str() + "%";
                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    static char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
                    uint8_t     aByte = smallBlob[ii];
                    char        highByte = hexDigits[(aByte >> 4) &0x0F];
                    char        lowByte = hexDigits[aByte &0x0F];

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%";
                if (0 == compareValueWithString(*stuff, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, " //####
                            "expectedString.c_str()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (stuff)"); //####
            }
        }
        else
        {
            ODL_LOG("! (smallBlob)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestSmallBlobValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 59 ***
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
doTestBigBlobValue(const char *launchPath,
                   const int  argc,
                   char       **argv) // big blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpAuint8_t bigBlob(new uint8_t[kBigTestSize]);

        if (bigBlob)
        {
            for (size_t ii = 0; kBigTestSize > ii; ++ii)
            {
                uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(bigBlob.get()) ^
                                                     ii);

                bigBlob[ii] = aByte;
            }
            std::unique_ptr<Blob> stuff(new Blob(bigBlob.get(), kBigTestSize));

            if (stuff)
            {
                std::string       expectedString("%");
                std::stringstream buff;

                buff << kBigTestSize;
                expectedString += buff.str() + "%";
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    static char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
                    uint8_t     aByte = bigBlob[ii];
                    char        highByte = hexDigits[(aByte >> 4) &0x0F];
                    char        lowByte = hexDigits[aByte &0x0F];

                    expectedString += highByte;
                    expectedString += lowByte;
                }
                expectedString += "%";
                if (0 == compareValueWithString(*stuff, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, " //####
                            "expectedString.c_str()))"); //####
                }
            }
            else
            {
                ODL_LOG("! (stuff)"); //####
            }
        }
        else
        {
            ODL_LOG("! (bigBlob)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestBigBlobValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 60 ***
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
doTestLogicalCopyAndAssign(const char *launchPath,
                           const int  argc,
                           char       **argv) // boolean copy and assign
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result;

    try
    {
        Logical falseStuff(false);
        Logical trueStuff(true);

        if ((! falseStuff.getValue()) && trueStuff.getValue())
        {
            Logical falseCopy(falseStuff);
            Logical trueCopy(trueStuff);

            if ((falseCopy.getValue() == falseStuff.getValue()) &&
                (trueCopy.getValue() == trueStuff.getValue()))
            {
                falseCopy = trueStuff;
                trueCopy = falseStuff;
                if ((falseCopy.getValue() == trueStuff.getValue()) &&
                    (trueCopy.getValue() == falseStuff.getValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((falseCopy.getValue() == trueStuff.getValue()) && " //####
                            "(trueCopy.getValue() == falseStuff.getValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((falseCopy.getValue() == falseStuff.getValue()) && " //####
                        "(trueCopy.getValue() == trueStuff.getValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((! falseStuff.getValue()) && trueStuff.getValue())"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestLogicalCopyAndAssign
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 61 ***
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
doTestIntegerCopyAndAssign(const char *launchPath,
                           const int  argc,
                           char       **argv) // integer copy and assign
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        static const int64_t value1 = -1234;
        static const int64_t value2 = 0;
        static const int64_t value3 = 2345;
        Integer negativeStuff(value1);
        Integer zeroStuff(value2);
        Integer positiveStuff(value3);

        if ((value1 == negativeStuff.getIntegerValue()) &&
            (value2 == zeroStuff.getIntegerValue()) &&
            (value3 == positiveStuff.getIntegerValue()))
        {
            Integer negativeCopy(negativeStuff);
            Integer zeroCopy(zeroStuff);
            Integer positiveCopy(positiveStuff);

            if ((negativeCopy.getIntegerValue() == negativeStuff.getIntegerValue()) &&
                (zeroCopy.getIntegerValue() == zeroStuff.getIntegerValue()) &&
                (positiveCopy.getIntegerValue() == positiveStuff.getIntegerValue()))
            {
                negativeCopy = zeroStuff;
                zeroCopy = positiveStuff;
                positiveCopy = negativeStuff;
                if ((negativeCopy.getIntegerValue() == zeroStuff.getIntegerValue()) &&
                    (zeroCopy.getIntegerValue() == positiveStuff.getIntegerValue()) &&
                    (positiveCopy.getIntegerValue() == negativeStuff.getIntegerValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((negativeCopy.getIntegerValue() == " //####
                            "zeroStuff.getIntegerValue()) && " //####
                            "(zeroCopy.getIntegerValue() == " //####
                            "positiveStuff.getIntegerValue()) && " //####
                            "(positiveCopy.getIntegerValue() == " //####
                            "negativeStuff.getIntegerValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((negativeCopy.getIntegerValue() == " //####
                        "negativeStuff.getIntegerValue()) && " //####
                        "(zeroCopy.getIntegerValue() == " //####
                        "zeroStuff.getIntegerValue()) && " //####
                        "(positiveCopy.getIntegerValue() == " //####
                        "positiveStuff.getIntegerValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((value1 == negativeStuff.getIntegerValue()) && " //####
                    "(value2 == zeroStuff.getIntegerValue()) && " //####
                    "(value3 == positiveStuff.getIntegerValue()))"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestIntegerCopyAndAssign
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 62 ***
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
doTestDoubleCopyAndAssign(const char *launchPath,
                          const int  argc,
                          char       **argv) // floating point copy and assign
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        static const double value1 = -1234.5;
        static const double value2 = 0.0;
        static const double value3 = 2345.6;
        Double negativeStuff(value1);
        Double zeroStuff(value2);
        Double positiveStuff(value3);

        if ((value1 == negativeStuff.getDoubleValue()) &&
            (value2 == zeroStuff.getDoubleValue()) &&
            (value3 == positiveStuff.getDoubleValue()))
        {
            Double negativeCopy(negativeStuff);
            Double zeroCopy(zeroStuff);
            Double positiveCopy(positiveStuff);

            if ((negativeCopy.getDoubleValue() == negativeStuff.getDoubleValue()) &&
                (zeroCopy.getDoubleValue() == zeroStuff.getDoubleValue()) &&
                (positiveCopy.getDoubleValue() == positiveStuff.getDoubleValue()))
            {
                negativeCopy = zeroStuff;
                zeroCopy = positiveStuff;
                positiveCopy = negativeStuff;
                if ((negativeCopy.getDoubleValue() == zeroStuff.getDoubleValue()) &&
                    (zeroCopy.getDoubleValue() == positiveStuff.getDoubleValue()) &&
                    (positiveCopy.getDoubleValue() == negativeStuff.getDoubleValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((negativeCopy.getDoubleValue() == " //####
                            "zeroStuff.getDoubleValue()) && " //####
                            "(zeroCopy.getDoubleValue() == " //####
                            "positiveStuff.getDoubleValue()) && " //####
                            "(positiveCopy.getDoubleValue() == " //####
                            "negativeStuff.getDoubleValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((negativeCopy.getDoubleValue() == " //####
                        "negativeStuff.getDoubleValue()) && " //####
                        "(zeroCopy.getDoubleValue() == zeroStuff.getDoubleValue()) && " //####
                        "(positiveCopy.getDoubleValue() == " //####
                        "positiveStuff.getDoubleValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((value1 == negativeStuff.getDoubleValue()) && " //####
                    "(value2 == zeroStuff.getDoubleValue()) && " //####
                    "(value3 == positiveStuff.getDoubleValue()))"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestDoubleCopyAndAssign
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 63 ***
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
doTestStringCopyAndAssign(const char *launchPath,
                          const int  argc,
                          char       **argv) // string copy and assign
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        String emptyString;
        String shortString("alphabetagamma");

        if ((0 == emptyString.getValue().length()) &&
            (shortString.getValue() == "alphabetagamma"))
        {
            String emptyCopy(emptyString);
            String shortCopy(shortString);

            if ((emptyCopy.getValue() == emptyString.getValue()) &&
                (shortCopy.getValue() == shortString.getValue()))
            {
                emptyCopy = shortString;
                shortCopy = emptyString;
                if ((emptyCopy.getValue() == shortString.getValue()) &&
                    (shortCopy.getValue() == emptyString.getValue()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! ((emptyCopy.getValue() == shortString.getValue()) && " //####
                            "(shortCopy.getValue() == emptyString.getValue()))"); //####
                    result = 1;
                }
            }
            else
            {
                ODL_LOG("! ((emptyCopy.getValue() == emptyString.getValue()) && " //####
                        "(shortCopy.getValue() == shortString.getValue()))"); //####
                result = 1;
            }
        }
        else
        {
            ODL_LOG("! ((0 == emptyString.getValue().length()) && " //####
                    "(shortString.getValue() == \"alphabetagamma\"))"); //####
            result = 1;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_L(result); //####
    return result;
} // doTestStringCopyAndAssign
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 64 ***
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
doTestBlobCopyAndAssign(const char *launchPath,
                        const int  argc,
                        char       **argv) // blob copy and assign
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 1;

    try
    {
        UpAuint8_t bigBlob(new uint8_t[kBigTestSize]);
        UpAuint8_t smallBlob(new uint8_t[kSmallTestSize]);

        if (bigBlob && smallBlob)
        {
            for (size_t ii = 0; kBigTestSize > ii; ++ii)
            {
                uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(bigBlob.get()) ^
                                                     ii);

                bigBlob[ii] = aByte;
            }
            for (size_t ii = 0; kSmallTestSize > ii; ++ii)
            {
                uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(smallBlob.get()) ^
                                                     ii);

                smallBlob[ii] = aByte;
            }
            Blob    smallStuff(smallBlob.get(), kSmallTestSize);
            Blob    bigStuff(bigBlob.get(), kBigTestSize);
            size_t        smallLength = 0;
            size_t        bigLength = 0;
            const uint8_t *smallValue = smallStuff.getValue(smallLength);
            const uint8_t *bigValue = bigStuff.getValue(bigLength);

            result = ((kSmallTestSize == smallLength) ? 0 : 1);
            if (0 == result)
            {
                result = CompareBytes(smallValue, smallBlob.get(), kSmallTestSize);
            }
            if (0 == result)
            {
                result = ((kBigTestSize == bigLength) ? 0 : 1);
                if (0 == result)
                {
                    result = CompareBytes(bigValue, bigBlob.get(), kBigTestSize);
                }
            }
            if (0 == result)
            {
                Blob smallCopy(smallStuff);
                Blob bigCopy(bigStuff);

                smallLength = bigLength = 0;
                smallValue = smallCopy.getValue(smallLength);
                bigValue = bigCopy.getValue(bigLength);
                result = ((kSmallTestSize == smallLength) ? 0 : 1);
                if (0 == result)
                {
                    result = CompareBytes(smallValue, smallBlob.get(), kSmallTestSize);
                }
                if (0 == result)
                {
                    result = ((kBigTestSize == bigLength) ? 0 : 1);
                    if (0 == result)
                    {
                        result = CompareBytes(bigValue, bigBlob.get(), kBigTestSize);
                    }
                }
                if (0 == result)
                {
                    smallCopy = bigStuff;
                    bigCopy = smallStuff;
                    smallLength = bigLength = 0;
                    smallValue = smallCopy.getValue(smallLength);
                    bigValue = bigCopy.getValue(bigLength);
                    result = ((kBigTestSize == smallLength) ? 0 : 1);
                    if (0 == result)
                    {
                        result = CompareBytes(smallValue, bigBlob.get(), kBigTestSize);
                    }
                    if (0 == result)
                    {
                        result = ((kSmallTestSize == bigLength) ? 0 : 1);
                        if (0 == result)
                        {
                            result = CompareBytes(bigValue, smallBlob.get(), kSmallTestSize);
                        }
                    }
                }
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
} // doTestBlobCopyAndAssign
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 80 ***
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
doTestValidLogicalCompares(const char *launchPath,
                           const int  argc,
                           char       **argv) // valid boolean compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct tests
        {
            bool _leftValue;
            bool _rightValue;
            bool _lessThanResult;
            bool _lessThanValid;
            bool _greaterThanResult;
            bool _greaterThanValid;
            bool _lessThanOrEqualResult;
            bool _lessThanOrEqualValid;
            bool _greaterThanOrEqualResult;
            bool _greaterThanOrEqualValid;
            bool _equalToResult;
            bool _equalToValid;
        }; // tests

        const tests testSet[] =
        {
            // left  right  <            >            <=           >=           ==
            { false, false, false, true, false, true, true,  true, true,  true, true,  true },
            { false, true,  true,  true, false, true, true,  true, false, true, false, true },
            { true,  false, false, true, true,  true, false, true, true,  true, false, true },
            { true,  true,  false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t numTests = (sizeof(testSet) / sizeof(testSet[0]));

        for (size_t ii = 0; (0 == result) && (numTests > ii); ++ii)
        {
            bool          valid = false;
            Logical leftValue(testSet[ii]._leftValue);
            Logical rightValue(testSet[ii]._rightValue);

            if (testSet[ii]._lessThanResult != leftValue.lessThan(rightValue, valid))
            {
                ODL_LOG("(testSet[ii]._lessThanResult != leftValue.lessThan(rightValue, " //####
                        "valid))"); //####
                result = 1;
            }
            else if (testSet[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._greaterThanResult != leftValue.greaterThan(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._greaterThanResult != " //####
                            "leftValue.greaterThan(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._lessThanOrEqualResult != leftValue.lessThanOrEqual(rightValue,
                                                                                    valid))
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqualResult != " //####
                            "leftValue.lessThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._greaterThanOrEqualResult !=
                    leftValue.greaterThanOrEqual(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqualResult != " //####
                            "leftValue.greaterThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._equalToResult != leftValue.equalTo(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._equalToResult != leftValue.equalTo(rightValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
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
} // doTestValidLogicalCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 81 ***
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
doTestValidNumberCompares(const char *launchPath,
                          const int  argc,
                          char       **argv) // valid number compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct testsI2I
        {
            int64_t _leftValue;
            int64_t _rightValue;
            bool _lessThanResult;
            bool _lessThanValid;
            bool _greaterThanResult;
            bool _greaterThanValid;
            bool _lessThanOrEqualResult;
            bool _lessThanOrEqualValid;
            bool _greaterThanOrEqualResult;
            bool _greaterThanOrEqualValid;
            bool _equalToResult;
            bool _equalToValid;
        }; // testsI2I
        struct testsI2R
        {
            int64_t _leftValue;
            double _rightValue;
            bool _lessThanResult;
            bool _lessThanValid;
            bool _greaterThanResult;
            bool _greaterThanValid;
            bool _lessThanOrEqualResult;
            bool _lessThanOrEqualValid;
            bool _greaterThanOrEqualResult;
            bool _greaterThanOrEqualValid;
            bool _equalToResult;
            bool _equalToValid;
        }; // testsI2R
        struct testsR2I
        {
            double _leftValue;
            int64_t _rightValue;
            bool _lessThanResult;
            bool _lessThanValid;
            bool _greaterThanResult;
            bool _greaterThanValid;
            bool _lessThanOrEqualResult;
            bool _lessThanOrEqualValid;
            bool _greaterThanOrEqualResult;
            bool _greaterThanOrEqualValid;
            bool _equalToResult;
            bool _equalToValid;
        }; // testsR2I
        struct testsR2R
        {
            double _leftValue;
            double _rightValue;
            bool _lessThanResult;
            bool _lessThanValid;
            bool _greaterThanResult;
            bool _greaterThanValid;
            bool _lessThanOrEqualResult;
            bool _lessThanOrEqualValid;
            bool _greaterThanOrEqualResult;
            bool _greaterThanOrEqualValid;
            bool _equalToResult;
            bool _equalToValid;
        }; // testsR2R

        const testsI2I testSet1[] =
        {
            // l   r  <            >            <=           >=           ==
            { 0,   0, false, true, false, true, true,  true, true,  true, true,  true },
            { 0,   1, true,  true, false, true, true,  true, false, true, false, true },
            { 0,  -1, false, true, true,  true, false, true, true,  true, false, true },
            { 1,   0, false, true, true,  true, false, true, true,  true, false, true },
            { -1,  0, true,  true, false, true, true,  true, false, true, false, true },
            { 1,   1, false, true, false, true, true,  true, true,  true, true,  true },
            { -1, -1, false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t numTests1 = (sizeof(testSet1) / sizeof(testSet1[0]));
        const testsI2R testSet2[] =
        {
            // l   r  <            >            <=           >=           ==
            { 0,   0, false, true, false, true, true,  true, true,  true, true,  true },
            { 0,   1, true,  true, false, true, true,  true, false, true, false, true },
            { 0,  -1, false, true, true,  true, false, true, true,  true, false, true },
            { 1,   0, false, true, true,  true, false, true, true,  true, false, true },
            { -1,  0, true,  true, false, true, true,  true, false, true, false, true },
            { 1,   1, false, true, false, true, true,  true, true,  true, true,  true },
            { -1, -1, false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t numTests2 = (sizeof(testSet2) / sizeof(testSet2[0]));
        const testsR2I testSet3[] =
        {
            // l   r  <            >            <=           >=           ==
            { 0,   0, false, true, false, true, true,  true, true,  true, true,  true },
            { 0,   1, true,  true, false, true, true,  true, false, true, false, true },
            { 0,  -1, false, true, true,  true, false, true, true,  true, false, true },
            { 1,   0, false, true, true,  true, false, true, true,  true, false, true },
            { -1,  0, true,  true, false, true, true,  true, false, true, false, true },
            { 1,   1, false, true, false, true, true,  true, true,  true, true,  true },
            { -1, -1, false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t numTests3 = (sizeof(testSet3) / sizeof(testSet3[0]));
        const testsR2R testSet4[] =
        {
            // l   r  <            >            <=           >=           ==
            { 0,   0, false, true, false, true, true,  true, true,  true, true,  true },
            { 0,   1, true,  true, false, true, true,  true, false, true, false, true },
            { 0,  -1, false, true, true,  true, false, true, true,  true, false, true },
            { 1,   0, false, true, true,  true, false, true, true,  true, false, true },
            { -1,  0, true,  true, false, true, true,  true, false, true, false, true },
            { 1,   1, false, true, false, true, true,  true, true,  true, true,  true },
            { -1, -1, false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t numTests4 = (sizeof(testSet4) / sizeof(testSet4[0]));

        for (size_t ii = 0; (0 == result) && (numTests1 > ii); ++ii)
        {
            bool          valid = false;
            Integer leftValue(testSet1[ii]._leftValue);
            Integer rightValue(testSet1[ii]._rightValue);

            if (testSet1[ii]._lessThanResult != leftValue.lessThan(rightValue, valid))
            {
                ODL_LOG("(testSet1[ii]._lessThanResult != leftValue.lessThan(rightValue, " //####
                        "valid))"); //####
                result = 1;
            }
            else if (testSet1[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                valid = false;
                if (testSet1[ii]._greaterThanResult != leftValue.greaterThan(rightValue, valid))
                {
                    ODL_LOG("(testSet1[ii]._greaterThanResult != " //####
                            "leftValue.greaterThan(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet1[ii]._lessThanOrEqualResult != leftValue.lessThanOrEqual(rightValue,
                                                                                     valid))
                {
                    ODL_LOG("(testSet1[ii]._lessThanOrEqualResult != " //####
                            "leftValue.lessThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet1[ii]._greaterThanOrEqualResult !=
                    leftValue.greaterThanOrEqual(rightValue, valid))
                {
                    ODL_LOG("(testSet1[ii]._greaterThanOrEqualResult != " //####
                            "leftValue.greaterThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet1[ii]._equalToResult != leftValue.equalTo(rightValue, valid))
                {
                    ODL_LOG("(testSet1[ii]._equalToResult != leftValue.equalTo(rightValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTests2 > ii); ++ii)
        {
            bool          valid = false;
            Integer leftValue(testSet2[ii]._leftValue);
            Double  rightValue(testSet2[ii]._rightValue);

            if (testSet2[ii]._lessThanResult != leftValue.lessThan(rightValue, valid))
            {
                ODL_LOG("(testSet2[ii]._lessThanResult != leftValue.lessThan(rightValue, " //####
                        "valid))"); //####
                result = 1;
            }
            else if (testSet2[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet2[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                valid = false;
                if (testSet2[ii]._greaterThanResult != leftValue.greaterThan(rightValue, valid))
                {
                    ODL_LOG("(testSet2[ii]._greaterThanResult != " //####
                            "leftValue.greaterThan(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet2[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet2[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet2[ii]._lessThanOrEqualResult != leftValue.lessThanOrEqual(rightValue,
                                                                                     valid))
                {
                    ODL_LOG("(testSet2[ii]._lessThanOrEqualResult != " //####
                            "leftValue.lessThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet2[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet2[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet2[ii]._greaterThanOrEqualResult !=
                    leftValue.greaterThanOrEqual(rightValue, valid))
                {
                    ODL_LOG("(testSet2[ii]._greaterThanOrEqualResult != " //####
                            "leftValue.greaterThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet2[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet2[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet2[ii]._equalToResult != leftValue.equalTo(rightValue, valid))
                {
                    ODL_LOG("(testSet2[ii]._equalToResult != leftValue.equalTo(rightValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet2[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet2[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTests3 > ii); ++ii)
        {
            bool          valid = false;
            Double  leftValue(testSet3[ii]._leftValue);
            Integer rightValue(testSet3[ii]._rightValue);

            if (testSet3[ii]._lessThanResult != leftValue.lessThan(rightValue, valid))
            {
                ODL_LOG("(testSet3[ii]._lessThanResult != leftValue.lessThan(rightValue, " //####
                        "valid))"); //####
                result = 1;
            }
            else if (testSet3[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet3[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                valid = false;
                if (testSet3[ii]._greaterThanResult != leftValue.greaterThan(rightValue, valid))
                {
                    ODL_LOG("(testSet3[ii]._greaterThanResult != " //####
                            "leftValue.greaterThan(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet3[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet3[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet3[ii]._lessThanOrEqualResult != leftValue.lessThanOrEqual(rightValue,
                                                                                     valid))
                {
                    ODL_LOG("(testSet3[ii]._lessThanOrEqualResult != " //####
                            "leftValue.lessThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet3[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet3[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet3[ii]._greaterThanOrEqualResult !=
                    leftValue.greaterThanOrEqual(rightValue, valid))
                {
                    ODL_LOG("(testSet3[ii]._greaterThanOrEqualResult != " //####
                            "leftValue.greaterThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet3[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet3[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet3[ii]._equalToResult != leftValue.equalTo(rightValue, valid))
                {
                    ODL_LOG("(testSet3[ii]._equalToResult != leftValue.equalTo(rightValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet3[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet3[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTests4 > ii); ++ii)
        {
            bool         valid = false;
            Double leftValue(testSet4[ii]._leftValue);
            Double rightValue(testSet4[ii]._rightValue);

            if (testSet4[ii]._lessThanResult != leftValue.lessThan(rightValue, valid))
            {
                ODL_LOG("(testSet4[ii]._lessThanResult != leftValue.lessThan(rightValue, " //####
                        "valid))"); //####
                result = 1;
            }
            else if (testSet4[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet4[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                valid = false;
                if (testSet4[ii]._greaterThanResult != leftValue.greaterThan(rightValue, valid))
                {
                    ODL_LOG("(testSet4[ii]._greaterThanResult != " //####
                            "leftValue.greaterThan(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet4[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet4[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet4[ii]._lessThanOrEqualResult != leftValue.lessThanOrEqual(rightValue,
                                                                                     valid))
                {
                    ODL_LOG("(testSet4[ii]._lessThanOrEqualResult != " //####
                            "leftValue.lessThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet4[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet4[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet4[ii]._greaterThanOrEqualResult !=
                    leftValue.greaterThanOrEqual(rightValue, valid))
                {
                    ODL_LOG("(testSet4[ii]._greaterThanOrEqualResult != " //####
                            "leftValue.greaterThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet4[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet4[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet4[ii]._equalToResult != leftValue.equalTo(rightValue, valid))
                {
                    ODL_LOG("(testSet4[ii]._equalToResult != leftValue.equalTo(rightValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet4[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet4[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
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
} // doTestValidNumberCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 82 ***
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
doTestValidStringCompares(const char *launchPath,
                          const int  argc,
                          char       **argv) // valid string compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct tests
        {
            const char *_leftValue;
            const char *_rightValue;
            bool _lessThanResult;
            bool _lessThanValid;
            bool _greaterThanResult;
            bool _greaterThanValid;
            bool _lessThanOrEqualResult;
            bool _lessThanOrEqualValid;
            bool _greaterThanOrEqualResult;
            bool _greaterThanOrEqualValid;
            bool _equalToResult;
            bool _equalToValid;
        }; // tests

        const tests testSet[] =
        {
            // left  right    <            >            <=           >=           ==
            { "",    "",      false, true, false, true, true,  true, true,  true, true,  true },
            { "",    "abc",   true,  true, false, true, true,  true, false, true, false, true },
            { "abc",  "",     false, true, true,  true, false, true, true,  true, false, true },
            { "abc",  "abc",  false, true, false, true, true,  true, true,  true, true,  true },
            { "abc",  "def",  true,  true, false, true, true,  true, false, true, false, true },
            { "def",  "abc",  false, true, true,  true, false, true, true,  true, false, true },
            { "abc",  "abcd", true,  true, false, true, true,  true, false, true, false, true },
            { "abcd", "abc",  false, true, true,  true, false, true, true,  true, false, true }
        };
        const size_t numTests = (sizeof(testSet) / sizeof(testSet[0]));

        for (size_t ii = 0; (0 == result) && (numTests > ii); ++ii)
        {
            bool         valid = false;
            String leftValue(testSet[ii]._leftValue);
            String rightValue(testSet[ii]._rightValue);

            if (testSet[ii]._lessThanResult != leftValue.lessThan(rightValue, valid))
            {
                ODL_LOG("(testSet[ii]._lessThanResult != leftValue.lessThan(rightValue, " //####
                        "valid))"); //####
                result = 1;
            }
            else if (testSet[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._greaterThanResult != leftValue.greaterThan(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._greaterThanResult != " //####
                            "leftValue.greaterThan(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._lessThanOrEqualResult != leftValue.lessThanOrEqual(rightValue,
                                                                                    valid))
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqualResult != " //####
                            "leftValue.lessThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._greaterThanOrEqualResult !=
                    leftValue.greaterThanOrEqual(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqualResult != " //####
                            "leftValue.greaterThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._equalToResult != leftValue.equalTo(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._equalToResult != leftValue.equalTo(rightValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
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
} // doTestValidStringCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 83 ***
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
doTestValidBlobCompares(const char *launchPath,
                        const int  argc,
                        char       **argv) // valid blob compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        struct tests
        {
            const Blob *_leftValue;
            const Blob *_rightValue;
            bool _lessThanResult;
            bool _lessThanValid;
            bool _greaterThanResult;
            bool _greaterThanValid;
            bool _lessThanOrEqualResult;
            bool _lessThanOrEqualValid;
            bool _greaterThanOrEqualResult;
            bool _greaterThanOrEqualValid;
            bool _equalToResult;
            bool _equalToValid;
        }; // tests

        const uint8_t blobData1[] = { 1, 2, 3, 4, 5, 6 };
        const uint8_t blobData2[] = { 1, 2, 3, 4, 5, 6, 7 };
        const uint8_t blobData3[] = { 1, 2, 3, 4, 5, 7 };
        const size_t  blobSize1 = (sizeof(blobData1) / sizeof(blobData1[0]));
        const size_t  blobSize2 = (sizeof(blobData2) / sizeof(blobData2[0]));
        const size_t  blobSize3 = (sizeof(blobData3) / sizeof(blobData3[0]));
        Blob    blob0;
        Blob    blob1(blobData1, blobSize1);
        Blob    blob2(blobData2, blobSize2);
        Blob    blob3(blobData3, blobSize3);
        const tests   testSet[] =
        {
            // left   right   <            >            <=           >=           ==
            { &blob0, &blob0, false, true, false, true, true,  true, true,  true, true,  true },
            { &blob0, &blob1, true,  true, false, true, true,  true, false, true, false, true },
            { &blob1, &blob0, false, true, true,  true, false, true, true,  true, false, true },
            { &blob1, &blob1, false, true, false, true, true,  true, true,  true, true,  true },
            { &blob1, &blob3, true,  true, false, true, true,  true, false, true, false, true },
            { &blob3, &blob1, false, true, true,  true, false, true, true,  true, false, true },
            { &blob1, &blob2, true,  true, false, true, true,  true, false, true, false, true },
            { &blob2, &blob1, false, true, true,  true, false, true, true,  true, false, true }
        };
        const size_t numTests = (sizeof(testSet) / sizeof(testSet[0]));

        for (size_t ii = 0; (0 == result) && (numTests > ii); ++ii)
        {
            bool             valid = false;
            const Blob &leftValue = *testSet[ii]._leftValue;
            const Blob &rightValue = *testSet[ii]._rightValue;

            if (testSet[ii]._lessThanResult != leftValue.lessThan(rightValue, valid))
            {
                ODL_LOG("(testSet[ii]._lessThanResult != leftValue.lessThan(rightValue, " //####
                        "valid))"); //####
                result = 1;
            }
            else if (testSet[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._greaterThanResult != leftValue.greaterThan(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._greaterThanResult != " //####
                            "leftValue.greaterThan(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._lessThanOrEqualResult != leftValue.lessThanOrEqual(rightValue,
                                                                                    valid))
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqualResult != " //####
                            "leftValue.lessThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._greaterThanOrEqualResult !=
                    leftValue.greaterThanOrEqual(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqualResult != " //####
                            "leftValue.greaterThanOrEqual(rightValue, valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                valid = false;
                if (testSet[ii]._equalToResult != leftValue.equalTo(rightValue, valid))
                {
                    ODL_LOG("(testSet[ii]._equalToResult != leftValue.equalTo(rightValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
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
} // doTestValidBlobCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 84 ***
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
doTestInvalidLogicalCompares(const char *launchPath,
                             const int  argc,
                             char       **argv) // invalid boolean compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        bool          valid = false;
        Logical leftValue;
        Number  rightValue1;
        String  rightValue2;
        Blob    rightValue3;
        Value   *rightValues[] = { &rightValue1, &rightValue2, &rightValue3 };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value &aRightValue = *rightValues[ii];

            valid = false;
            leftValue.lessThan(aRightValue, valid);
            if (valid)
            {
                ODL_LOG("(valid)"); //####
                result = 1;
            }
            else
            {
                leftValue.greaterThan(aRightValue, valid);
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.lessThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.greaterThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.equalTo(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
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
} // doTestInvalidLogicalCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 85 ***
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
doTestInvalidNumberCompares(const char *launchPath,
                            const int  argc,
                            char       **argv) // invalid number compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        bool          valid = false;
        Number  leftValue;
        Logical rightValue1;
        String  rightValue2;
        Blob    rightValue3;
        Value   *rightValues[] = { &rightValue1, &rightValue2, &rightValue3 };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value &aRightValue = *rightValues[ii];

            valid = false;
            leftValue.lessThan(aRightValue, valid);
            if (valid)
            {
                ODL_LOG("(valid)"); //####
                result = 1;
            }
            else
            {
                leftValue.greaterThan(aRightValue, valid);
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.lessThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.greaterThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.equalTo(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
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
} // doTestInvalidNumberCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 86 ***
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
doTestInvalidStringCompares(const char *launchPath,
                            const int  argc,
                            char       **argv) // invalid string compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        bool          valid = false;
        String  leftValue;
        Logical rightValue1;
        Number  rightValue2;
        Blob    rightValue3;
        Value   *rightValues[] = { &rightValue1, &rightValue2, &rightValue3 };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value &aRightValue = *rightValues[ii];

            valid = false;
            leftValue.lessThan(aRightValue, valid);
            if (valid)
            {
                ODL_LOG("(valid)"); //####
                result = 1;
            }
            else
            {
                leftValue.greaterThan(aRightValue, valid);
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.lessThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.greaterThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.equalTo(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
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
} // doTestInvalidStringCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 87 ***
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
doTestInvalidBlobCompares(const char *launchPath,
                          const int  argc,
                          char       **argv) // invalid blob compares
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath,argc,argv)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    ODL_LL1("argc = ", argc); //####
    ODL_P1("argv = ", argv); //####
    int result = 0;

    try
    {
        bool          valid = false;
        Blob    leftValue;
        Logical rightValue1;
        Number  rightValue2;
        String  rightValue3;
        Value   *rightValues[] = { &rightValue1, &rightValue2, &rightValue3 };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            Value &aRightValue = *rightValues[ii];

            valid = false;
            leftValue.lessThan(aRightValue, valid);
            if (valid)
            {
                ODL_LOG("(valid)"); //####
                result = 1;
            }
            else
            {
                leftValue.greaterThan(aRightValue, valid);
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.lessThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.greaterThanOrEqual(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
                else
                {
                    leftValue.equalTo(aRightValue, valid);
                }
            }
            if (0 == result)
            {
                if (valid)
                {
                    ODL_LOG("(valid)"); //####
                    result = 1;
                }
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
} // doTestInvalidBlobCompares
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
                        result = doTestEmptyBufferChunk(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestBufferChunkWithSingleByte(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestFilledBufferChunk(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestOverfilledBufferChunk(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestBufferChunkReset(*argv, argc - 1, argv + 2);
                        break;

                    case 10 :
                        result = doTestEmptyStringBuffer(*argv, argc - 1, argv + 2);
                        break;

                    case 11 :
                        result = doTestStringBufferWithCharacters(*argv, argc - 1, argv + 2);
                        break;

                    case 12 :
                        result = doTestStringBufferWithLogical(*argv, argc - 1, argv + 2);
                        break;

                    case 13 :
                        result = doTestStringBufferWithInteger(*argv, argc - 1, argv + 2);
                        break;

                    case 14 :
                        result = doTestStringBufferWithString(*argv, argc - 1, argv + 2);
                        break;

                    case 15 :
                        result = doTestStringBufferWithSpecialCharacters(*argv, argc - 1, argv + 2);
                        break;

                    case 16 :
                        result = doTestStringBufferWithDouble(*argv, argc - 1, argv + 2);
                        break;

                    case 17 :
                        result = doTestBigStringBuffer(*argv, argc - 1, argv + 2);
                        break;

                    case 18 :
                        result = doTestStringBufferWithEmptyBlob(*argv, argc - 1, argv + 2);
                        break;

                    case 19 :
                        result = doTestStringBufferWithSmallBlob(*argv, argc - 1, argv + 2);
                        break;

                    case 20 :
                        result = doTestStringBufferWithBigBlob(*argv, argc - 1, argv + 2);
                        break;

                    case 21 :
                        result = doTestStringBufferReset(*argv, argc - 1, argv + 2);
                        break;

                    case 50 :
                        result = doTestDefaultLogicalValue(*argv, argc - 1, argv + 2);
                        break;

                    case 51 :
                        result = doTestLogicalValue(*argv, argc - 1, argv + 2);
                        break;

                    case 52 :
                        result = doTestDefaultIntegerValue(*argv, argc - 1, argv + 2);
                        break;

                    case 53 :
                        result = doTestNumberValue(*argv, argc - 1, argv + 2);
                        break;

                    case 54 :
                        result = doTestDefaultStringValue(*argv, argc - 1, argv + 2);
                        break;

                    case 55 :
                        result = doTestStringValue(*argv, argc - 1, argv + 2);
                        break;

                    case 56 :
                        result = doTestStringValueWithEscapes(*argv, argc - 1, argv + 2);
                        break;

                    case 57 :
                        result = doTestDefaultBlobValue(*argv, argc - 1, argv + 2);
                        break;

                    case 58 :
                        result = doTestSmallBlobValue(*argv, argc - 1, argv + 2);
                        break;

                    case 59 :
                        result = doTestBigBlobValue(*argv, argc - 1, argv + 2);
                        break;

                    case 60 :
                        result = doTestLogicalCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 61 :
                        result = doTestIntegerCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 62 :
                        result = doTestDoubleCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 63 :
                        result = doTestStringCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 64 :
                        result = doTestBlobCopyAndAssign(*argv, argc - 1, argv + 2);
                        break;

                    case 80 :
                        result = doTestValidLogicalCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 81 :
                        result = doTestValidNumberCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 82 :
                        result = doTestValidStringCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 83 :
                        result = doTestValidBlobCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 84 :
                        result = doTestInvalidLogicalCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 85 :
                        result = doTestInvalidNumberCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 86 :
                        result = doTestInvalidStringCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 87 :
                        result = doTestInvalidBlobCompares(*argv, argc - 1, argv + 2);
                        break;

                    default :
                        break;

                }
                if (result)
                {
                    ODL_LL1("%%%%%%% unit test failure = ", result); //####
                }
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

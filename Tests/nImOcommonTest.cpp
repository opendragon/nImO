//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOcommonTest.cpp
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

#include <nImO/nImObufferChunk.hpp>
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
 @param signal The signal being handled. */
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
    message += nImO::NameOfSignal(signal);
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestEmptyBufferChunk(const char * launchPath,
                       const int    argc,
                       char * *     argv) // empty buffer chunk
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::BufferChunk * stuff = new nImO::BufferChunk;
        
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
            delete stuff;
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestBufferChunkWithSingleByte(const char * launchPath,
                                const int    argc,
                                char * *     argv) // buffer chunk with 1 byte of data
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::BufferChunk * stuff = new nImO::BufferChunk;
        
        if (stuff)
        {
            uint8_t data = (reinterpret_cast<intptr_t>(stuff) & 0x00FF);
            
            stuff->appendData(&stuff, 1);
            if (1 == stuff->getDataSize())
            {
                const uint8_t * storedData = stuff->getData();
                
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
            delete stuff;
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestFilledBufferChunk(const char * launchPath,
                        const int    argc,
                        char * *     argv) // buffer chunk filled with data
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::BufferChunk * stuff = new nImO::BufferChunk;
        
        if (stuff)
        {
            size_t howMuch = stuff->getAvailableBytes();
            
            if (1 < howMuch)
            {
                uint8_t data = (reinterpret_cast<intptr_t>(stuff) & 0x00FF);

                for (size_t ii = 0; howMuch > ii; ++ii)
                {
                    uint8_t newData = static_cast<uint8_t>((data + ii) & 0x00FF);
                    
                    stuff->appendData(&newData, 1);
                }
                if ((0 == stuff->getAvailableBytes()) && (howMuch == stuff->getDataSize()))
                {
                    const uint8_t * storedData = stuff->getData();
                    
                    if (storedData)
                    {
                        result = 0;
                        for (size_t ii = 0; howMuch > ii; ++ii)
                        {
                            uint8_t aValue = storedData[ii];
                            uint8_t expectedValue = static_cast<uint8_t>((data + ii) & 0x00FF);
                            
                            if (aValue != expectedValue)
                            {
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
            delete stuff;
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestOverfilledBufferChunk(const char * launchPath,
                            const int    argc,
                            char * *     argv) // buffer chunk overfilled with data
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::BufferChunk * stuff = new nImO::BufferChunk;
        
        if (stuff)
        {
            size_t howMuch = stuff->getAvailableBytes();
            
            if (1 < howMuch)
            {
                uint8_t data = (reinterpret_cast<intptr_t>(stuff) & 0x00FF);
                
                for (size_t ii = 0; howMuch >= ii; ++ii)
                {
                    uint8_t newData = static_cast<uint8_t>((data + ii) & 0x00FF);
                    
                    stuff->appendData(&newData, 1);
                }
                if ((0 == stuff->getAvailableBytes()) && (howMuch == stuff->getDataSize()))
                {
                    const uint8_t * storedData = stuff->getData();
                    
                    if (storedData)
                    {
                        result = 0;
                        for (size_t ii = 0; howMuch > ii; ++ii)
                        {
                            uint8_t aValue = storedData[ii];
                            uint8_t expectedValue = static_cast<uint8_t>((data + ii) & 0x00FF);
                            
                            if (aValue != expectedValue)
                            {
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
            delete stuff;
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestBufferChunkReset(const char * launchPath,
                       const int    argc,
                       char * *     argv) // resetting buffer chunk
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::BufferChunk * stuff = new nImO::BufferChunk;
        
        if (stuff)
        {
            uint8_t data = (reinterpret_cast<intptr_t>(stuff) & 0x00FF);
            
            stuff->appendData(&stuff, 1);
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
            delete stuff;
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
# pragma mark *** Test Case 06 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestEmptyStringBuffer(const char * launchPath,
                        const int    argc,
                        char * *     argv) // empty string buffer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::StringBuffer * stuff = new nImO::StringBuffer;
        
        if (stuff)
        {
            if (0 == stuff->getLength())
            {
                size_t       length = 0;
                const char * outString = stuff->getString(length);
               
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
            delete stuff;
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
# pragma mark *** Test Case 07 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithCharacters(const char * launchPath,
                                 const int    argc,
                                 char * *     argv) // string buffer with character string
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        if (1 < argc)
        {
            const char *         inString = *argv;
            const char *         outString = argv[1];
            size_t               outLength = strlen(outString);
            nImO::StringBuffer * stuff = new nImO::StringBuffer;
           
            if (stuff)
            {
                stuff->addString(inString);
                size_t resultLength = stuff->getLength();

                if (resultLength == outLength)
                {
                    const char * resultString = stuff->getString(resultLength);
                   
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
                delete stuff;
            }
            else
            {
                ODL_LOG("! (stuff)"); //####
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
} // doTestStringBufferWithCharacters
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 08 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithBoolean(const char * launchPath,
                              const int    argc,
                              char * *     argv) // string buffer with boolean
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        if (1 < argc)
        {
            const char * outString = argv[1];
            const char * startPtr = *argv;
            char *       endPtr;
            int          value = strtol(startPtr, &endPtr, 10);

            if ((startPtr != endPtr) && (! *endPtr) && (0 <= value))
            {
                nImO::StringBuffer * stuff = new nImO::StringBuffer;

                if (stuff)
                {
                    bool asBool = (0 != value);

                    stuff->addBool(asBool);
                    size_t       length;
                    const char * resultString = stuff->getString(length);

                    if (0 == strcmp(outString, resultString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == strcmp(outString, resultString))"); //####
                    }
                    delete stuff;
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
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
} // doTestStringBufferWithBoolean
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 09 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithInteger(const char * launchPath,
                              const int    argc,
                              char * *     argv) // string buffer with integer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        if (1 < argc)
        {
            const char * outString = argv[1];
            const char * startPtr = *argv;
            char *       endPtr;
            int          value = strtol(startPtr, &endPtr, 10);

            if ((startPtr != endPtr) && (! *endPtr))
            {
                nImO::StringBuffer * stuff = new nImO::StringBuffer;

                if (stuff)
                {
                    stuff->addLong(value);
                    size_t       length;
                    const char * resultString = stuff->getString(length);

                    if (0 == strcmp(outString, resultString))
                    {
                        result = 0;
                    }
                    else
                    {
                        ODL_LOG("! (0 == strcmp(outString, resultString))"); //####
                    }
                    delete stuff;
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
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
} // doTestStringBufferWithInteger
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithString(const char * launchPath,
                             const int    argc,
                             char * *     argv) // string buffer with string
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        if (1 < argc)
        {
            const char *         inString = *argv;
            const char *         outString = argv[1];
            size_t               outLength = strlen(outString);
            nImO::StringBuffer * stuff = new nImO::StringBuffer;
            
            if (stuff)
            {
                stuff->addString(inString, true);
                size_t resultLength = stuff->getLength();

                if (resultLength == outLength)
                {
                    const char * resultString = stuff->getString(resultLength);
                    
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
                delete stuff;
            }
            else
            {
                ODL_LOG("! (stuff)"); //####
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
} // doTestStringBufferWithString
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithSpecialCharacters(const char * launchPath,
                                        const int    argc,
                                        char * *     argv) // string buffer with special chars
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        const char *         inString = "abc\tdef\f\rghi\302";
        const char *         outString = "\"abc\\tdef\\f\\rghi\\M-B\"";
        size_t               outLength = strlen(outString);
        nImO::StringBuffer * stuff = new nImO::StringBuffer;
        
        if (stuff)
        {
            stuff->addString(inString, true);
            size_t resultLength = stuff->getLength();
            
            if (resultLength == outLength)
            {
                const char * resultString = stuff->getString(resultLength);
                
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
            delete stuff;
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
# pragma mark *** Test Case 12 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithFloatingPoint(const char * launchPath,
                                    const int    argc,
                                    char * *     argv) // string buffer with floating point
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        if (1 < argc)
        {
            const char * outString = argv[1];
            const char * startPtr = *argv;
            char *       endPtr;
            double       value = strtod(startPtr, &endPtr);

            if ((startPtr != endPtr) && (! *endPtr))
            {
                nImO::StringBuffer * stuff = new nImO::StringBuffer;

                if (stuff)
                {
                    stuff->addDouble(value);
                    size_t       length;
                    const char * resultString = stuff->getString(length);

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
                        result = 1;
                    }
                    else
                    {
                        ODL_LOG("! (*outString || *resultString)"); //####
                    }
                    delete stuff;
                }
                else
                {
                    ODL_LOG("! (stuff)"); //####
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
} // doTestStringBufferWithFloatingPoint
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestBigStringBuffer(const char * launchPath,
                      const int    argc,
                      char * *     argv) // big string buffer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::StringBuffer * stuff = new nImO::StringBuffer;
        
        if (stuff)
        {
            const char * bigString = "abcdefghijklmnopqrstuvwxyz0123456789";
            size_t       bigLength = strlen(bigString);

            for (size_t ii = 0; kBigTestSize > ii; ++ii)
            {
                stuff->addString(bigString);
            }
            size_t       length = 0;
            const char * resultString = stuff->getString(length);

            if ((bigLength * kBigTestSize) == length)
            {
                result = 0;
                for (size_t ii = 0; kBigTestSize > ii; ++ii, resultString += bigLength)
                {
                    if (memcmp(bigString, resultString, bigLength))
                    {
                        result = 1;
                        break;
                    }

                }
            }
            else
            {
                ODL_LOG("! ((bigLength * kBigTestSize) == length)"); //####
            }
            delete stuff;
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
# pragma mark *** Test Case 14 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferWithEmptyBlob(const char * launchPath,
                                const int    argc,
                                char * *     argv) // string buffer with empty blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::StringBuffer * stuff = new nImO::StringBuffer;
        
        if (stuff)
        {
            stuff->addBlob(NULL, 0);
            size_t       length;
            const char * resultString = stuff->getString(length);
            const char * expectedString = "%0%%";

            if (0 == strcmp(resultString, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == strcmp(resultString, expectedString))"); //####
            }
            delete stuff;
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
# pragma mark *** Test Case 15 ***
#endif // defined(__APPLE__)

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
/*! @brief Perform a test case.
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
TestStringBufferWithSmallBlob(const char * launchPath,
                              const int    argc,
                              char * *     argv) // string buffer with simple blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::StringBuffer * stuff = new nImO::StringBuffer;
        
        if (stuff)
        {
            uint8_t * smallBlob = new uint8_t[kSmallTestSize];

            if (smallBlob)
            {
                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(smallBlob) ^ ii);

                    smallBlob[ii] = aByte;
                }
                stuff->addBlob(smallBlob, kSmallTestSize);
                size_t            length;
                const char *      resultString = stuff->getString(length);
                std::string       expectedString("%");
                std::stringstream buff;

                buff << kSmallTestSize;
                expectedString += buff.str() + "%";
                for (size_t ii = 0; kSmallTestSize > ii; ++ii)
                {
                    static char    hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                                   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
                    uint8_t        aByte = smallBlob[ii];
                    char           highByte = hexDigits[(aByte >> 4) & 0x0F];
                    char           lowByte = hexDigits[aByte & 0x0F];

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
                delete[] smallBlob;
            }
            delete stuff;
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
} // TestStringBufferWithSmallBlob
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
TestStringBufferWithBigBlob(const char * launchPath,
                            const int    argc,
                            char * *     argv) // string buffer with big blob
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::StringBuffer * stuff = new nImO::StringBuffer;
        
        if (stuff)
        {
            uint8_t * bigBlob = new uint8_t[kBigTestSize];

            if (bigBlob)
            {
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(bigBlob) ^ ii);

                    bigBlob[ii] = aByte;
                }
                stuff->addBlob(bigBlob, kBigTestSize);
                size_t            length;
                const char *      resultString = stuff->getString(length);
                std::string       expectedString("%");
                std::stringstream buff;

                buff << kBigTestSize;
                expectedString += buff.str() + "%";
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    static char    hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                                   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
                    uint8_t        aByte = bigBlob[ii];
                    char           highByte = hexDigits[(aByte >> 4) & 0x0F];
                    char           lowByte = hexDigits[aByte & 0x0F];

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
                delete[] bigBlob;
            }
            delete stuff;
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
} // TestStringBufferWithBigBlob
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
 @param launchPath The command-line name used to launch the service.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used for the test.
 @returns @c 0 on success and @c 1 on failure. */
static int
doTestStringBufferReset(const char * launchPath,
                        const int    argc,
                        char * *     argv) // resetting string buffer
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(launchPath)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_S1("launchPath = ", launchPath); //####
    int result = 1;
    
    try
    {
        nImO::StringBuffer * stuff = new nImO::StringBuffer;
        
        if (stuff)
        {
            stuff->addString("abcdef");
            stuff->reset();
            size_t resultLength = stuff->getLength();

            if (0 == resultLength)
            {
                const char * resultString = stuff->getString(resultLength);
                    
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
            delete stuff;
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
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for unit tests of the %nImO common classes.
 
 The first argument is the test number, the second argument is the name of the channel to be used
 with the test, the optional third argument is the machine to connect to and the optional fourth
 argument is the port number to be used. Output depends on the test being run.
 @param argc The number of arguments in 'argv'.
 @param argv The arguments to be used with the unit tests.
 @returns @c 0 on a successful test and @c 1 on failure. */
int
main(int      argc,
     char * * argv)
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
        nImO::Initialize(progName);
        if (0 < --argc)
        {
            const char * startPtr = argv[1];
            char *       endPtr;
            int          selector = strtol(startPtr, &endPtr, 10);
            
            if ((startPtr != endPtr) && (! *endPtr) && (0 < selector))
            {
                nImO::SetSignalHandlers(catchSignal);
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

                    case 6 :
                        result = doTestEmptyStringBuffer(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 7 :
                        result = doTestStringBufferWithCharacters(*argv, argc - 1, argv + 2);
                        break;
                    
                    case 8 :
                        result = doTestStringBufferWithBoolean(*argv, argc - 1, argv + 2);
                        break;
                    
                    case 9 :
                        result = doTestStringBufferWithInteger(*argv, argc - 1, argv + 2);
                        break;
                    
                    case 10 :
                        result = doTestStringBufferWithString(*argv, argc - 1, argv + 2);
                        break;
                    
                    case 11 :
                        result = doTestStringBufferWithSpecialCharacters(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 12 :
                        result = doTestStringBufferWithFloatingPoint(*argv, argc - 1, argv + 2);
                        break;
                    
                    case 13 :
                        result = doTestBigStringBuffer(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 14 :
                        result = doTestStringBufferWithEmptyBlob(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 15 :
                        result = TestStringBufferWithSmallBlob(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 16 :
                        result = TestStringBufferWithBigBlob(*argv, argc - 1, argv + 2);
                        break;
                        
                    case 17 :
                        result = doTestStringBufferReset(*argv, argc - 1, argv + 2);
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
    }
    ODL_EXIT_L(result); //####
    return result;
} // main

//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImOcontainerTest.cpp
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
//  Created:    2016-04-05
//
//--------------------------------------------------------------------------------------------------

#include <nImO/nImOarray.hpp>
#include <nImO/nImOblob.hpp>
#include <nImO/nImOboolean.hpp>
#include <nImO/nImObufferChunk.hpp>
#include <nImO/nImOdouble.hpp>
#include <nImO/nImOinteger.hpp>
#include <nImO/nImOmap.hpp>
#include <nImO/nImOset.hpp>
#include <nImO/nImOstring.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#include <stdio.h>

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

using std::cerr;
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

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
    message += nImO::NameOfSignal(signal);
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
compareValueWithSquishedString(const nImO::Value &aValue,
                               const char        *aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    nImO::StringBuffer buff;
    int                result;
    size_t             length;

    aValue.printToStringBuffer(buff, true);
    result = strcmp(buff.getString(length), aString);
    ODL_S2("got: ", buff.getString(length), "expected: ", aString); //####
    ODL_EXIT_LL(result); //####
    return result;
} // compareValueWithSquishedString

/*! @brief Compare a Value object with a string.
 @param[in] aValue The object to be compared.
 @param[in] aString The string to be compared to.
 @returns @c -1, @c 0 or @c 1 depending on where the string is greater than, equal to or less than
 the object representation as a string. */
static int
compareValueWithString(const nImO::Value &aValue,
                       const char        *aString)
{
    ODL_ENTER(); //###
    ODL_P1("aValue = ", &aValue); //####
    ODL_S1("aString = ", aString); //####
    nImO::StringBuffer buff;
    int                result;
    size_t             length;

    aValue.printToStringBuffer(buff);
    result = strcmp(buff.getString(length), aString);
    ODL_S2("got: ", buff.getString(length), "expected: ", aString); //####
    ODL_EXIT_LL(result); //####
    return result;
} // compareValueWithString

#if defined(__APPLE__)
# pragma mark *** Test Case 1 ***
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
doTestEmptyArrayValue(const char *launchPath,
                      const int  argc,
                      char       **argv) // empty array value
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
        nImO::Array *stuff = new nImO::Array;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartArrayChar, nImO::kEndArrayChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartArrayChar, ' ', nImO::kEndArrayChar, '\0'
            };

            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestEmptyArrayValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 2 ***
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
doTestSingularArrayValue(const char *launchPath,
                         const int  argc,
                         char       **argv) // singular array value
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
        nImO::Array *stuff = new nImO::Array;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartArrayChar,
                    '1', '2', '3', '.', '4', '5',
                nImO::kEndArrayChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartArrayChar, ' ',
                    '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndArrayChar, '\0'
            };

            stuff->addValue(new nImO::Double(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSingularArrayValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 3 ***
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
doTestSmallArrayValue(const char *launchPath,
                      const int  argc,
                      char       **argv) // small array value
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
        nImO::Array *stuff = new nImO::Array;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartArrayChar,
                    '1', '2', '3', '.', '4', '5', ' ',
                    't', 'r', 'u', 'e', ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                    '4', '2',
                nImO::kEndArrayChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartArrayChar, ' ',
                    '1', '2', '3', '.', '4', '5', ' ',
                    't', 'r', 'u', 'e', ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                    '4', '2', ' ',
                nImO::kEndArrayChar, '\0'
            };

            stuff->addValue(new nImO::Double(123.45));
            stuff->addValue(new nImO::Boolean(true));
            stuff->addValue(new nImO::String("charlie"));
            stuff->addValue(new nImO::Integer(42));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSmallArrayValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 4 ***
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
doTestBigArrayValue(const char *launchPath,
                    const int  argc,
                    char       **argv) // big array value
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
        nImO::Array *stuff = new nImO::Array;

        if (stuff)
        {
            uint8_t *bigBlob = new uint8_t[kBigTestSize];

            if (bigBlob)
            {
                std::string expectedSquishedString;
                std::string expectedString;
                char        numBuff[10];

                expectedSquishedString += nImO::kStartArrayChar;
                expectedString += nImO::kStartArrayChar;
                expectedString += ' ';
                for (size_t ii = 0; kBigTestSize > ii; ++ii)
                {
                    uint8_t aByte = static_cast<uint8_t>(reinterpret_cast<intptr_t>(bigBlob) ^ ii);

                    if (0 != ii)
                    {
                        expectedSquishedString += ' ';
                    }
                    bigBlob[ii] = aByte;
                    stuff->addValue(new nImO::Integer(aByte));
                    snprintf(numBuff, sizeof(numBuff), "%d ", aByte);
                    expectedString += numBuff;
                    snprintf(numBuff, sizeof(numBuff), "%d", aByte);
                    expectedSquishedString += numBuff;
                }
                expectedSquishedString += nImO::kEndArrayChar;
                expectedString += nImO::kEndArrayChar;
                if (0 == compareValueWithString(*stuff, expectedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
                }
                if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString.c_str()))
                {
                    result = 0;
                }
                else
                {
                    ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                            "expectedSquishedString))"); //####
                }
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
} // doTestBigArrayValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 41 ***
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
doTestEmptyMapValue(const char *launchPath,
                    const int  argc,
                    char       **argv) // empty map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar, nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ', nImO::kEndMapChar, '\0'
            };

            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestEmptyMapValue
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
doTestSingularBooleanMapValue(const char *launchPath,
                              const int  argc,
                              char       **argv) // singular boolean map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    't', 'r', 'u', 'e', nImO::kKeyValueSeparator,
                        '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    't', 'r', 'u', 'e', ' ', nImO::kKeyValueSeparator, ' ',
                        '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Boolean(true), new nImO::Double(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSingularBooleanMapValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 22 ***
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
doTestSingularIntegerMapValue(const char *launchPath,
                              const int  argc,
                              char       **argv) // singular integer map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '4', '2', nImO::kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '4', '2', ' ', nImO::kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42),
                            new nImO::Double(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSingularIntegerMapValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 23 ***
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
doTestSingularStringMapValue(const char *launchPath,
                             const int  argc,
                             char       **argv) // singular string map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                        nImO::kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                        nImO::kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::String("charlie"), new nImO::Double(123.45));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSingularStringMapValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 24 ***
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
doTestSmallBooleanMapValue(const char *launchPath,
                           const int  argc,
                           char       **argv) // small boolean map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    'f', 'a', 'l', 's', 'e', nImO::kKeyValueSeparator, '4', '2', ' ',
                    't', 'r', 'u', 'e', nImO::kKeyValueSeparator,
                    '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    'f', 'a', 'l', 's', 'e', ' ', nImO::kKeyValueSeparator, ' ', '4', '2', ' ',
                    't', 'r', 'u', 'e', ' ', nImO::kKeyValueSeparator, ' ',
                    '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Boolean(true), new nImO::Double(123.45));
            stuff->addValue(new nImO::Boolean(false),
                            new nImO::Integer(42));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSmallBooleanMapValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 25 ***
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
doTestSmallIntegerMapValue(const char *launchPath,
                           const int  argc,
                           char       **argv) // small integer map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '1', '2', nImO::kKeyValueSeparator, '1', '2', '3', '4', '.', '5', ' ',
                    '1', '7', nImO::kKeyValueSeparator, '1', '2', '.', '3', '4', '5', ' ',
                    '4', '2', nImO::kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '1', '2', ' ', nImO::kKeyValueSeparator, ' ', '1', '2', '3', '4', '.', '5', ' ',
                    '1', '7', ' ', nImO::kKeyValueSeparator, ' ', '1', '2', '.', '3', '4', '5', ' ',
                    '4', '2', ' ', nImO::kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42),
                            new nImO::Double(123.45));
            stuff->addValue(new nImO::Integer(17),
                            new nImO::Double(12.345));
            stuff->addValue(new nImO::Integer(12),
                            new nImO::Double(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSmallIntegerMapValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 26 ***
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
doTestSmallStringMapValue(const char *launchPath,
                          const int  argc,
                          char       **argv) // small string map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', nImO::kKeyValueSeparator,
                        '1', '2', '3', '4', '.', '5', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', nImO::kKeyValueSeparator,
                        '1', '2', '3', '.', '4', '5', ' ',
                    '"', 'l', 'i', 'm', 'a', '"', nImO::kKeyValueSeparator,
                        '1', '2', '.', '3', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ', nImO::kKeyValueSeparator, ' ',
                        '1', '2', '3', '4', '.', '5', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', ' ', nImO::kKeyValueSeparator, ' ',
                        '1', '2', '3', '.', '4', '5', ' ',
                    '"', 'l', 'i', 'm', 'a', '"', ' ', nImO::kKeyValueSeparator, ' ',
                        '1', '2', '.', '3', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::String("delta"), new nImO::Double(123.45));
            stuff->addValue(new nImO::String("lima"), new nImO::Double(12.345));
            stuff->addValue(new nImO::String("charlie"), new nImO::Double(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSmallStringMapValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 40 ***
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
doTestEmptySetValue(const char *launchPath,
                    const int  argc,
                    char       **argv) // empty map
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar, nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ', nImO::kEndSetChar, '\0'
            };

            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestEmptySetValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 41 ***
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
doTestSingularBooleanSetValue(const char *launchPath,
                              const int  argc,
                              char       **argv) // singular boolean map
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    't', 'r', 'u', 'e',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    't', 'r', 'u', 'e', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::Boolean(true));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSingularBooleanSetValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 42 ***
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
doTestSingularIntegerSetValue(const char *launchPath,
                              const int  argc,
                              char       **argv) // singular integer map
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    '4', '2',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    '4', '2', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSingularIntegerSetValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 43 ***
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
doTestSingularStringSetValue(const char *launchPath,
                             const int  argc,
                             char       **argv) // singular string map
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::String("charlie"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSingularStringSetValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 44 ***
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
doTestSmallBooleanSetValue(const char *launchPath,
                           const int  argc,
                           char       **argv) // small boolean map
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    'f', 'a', 'l', 's', 'e', ' ',
                    't', 'r', 'u', 'e',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    'f', 'a', 'l', 's', 'e', ' ',
                    't', 'r', 'u', 'e', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::Boolean(true));
            stuff->addValue(new nImO::Boolean(false));
            stuff->addValue(new nImO::Boolean(true));
            stuff->addValue(new nImO::Boolean(false));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSmallBooleanSetValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 45 ***
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
doTestSmallIntegerSetValue(const char *launchPath,
                           const int  argc,
                           char       **argv) // small integer map
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    '1', '2', ' ',
                    '1', '7', ' ',
                    '4', '2', ' ',
                    '1', '2', '3',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    '1', '2', ' ',
                    '1', '7', ' ',
                    '4', '2', ' ',
                    '1', '2', '3', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::Integer(123));
            stuff->addValue(new nImO::Integer(42));
            stuff->addValue(new nImO::Integer(17));
            stuff->addValue(new nImO::Integer(12));
            stuff->addValue(new nImO::Integer(123));
            stuff->addValue(new nImO::Integer(42));
            stuff->addValue(new nImO::Integer(17));
            stuff->addValue(new nImO::Integer(12));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSmallIntegerSetValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 46 ***
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
doTestSmallStringSetValue(const char *launchPath,
                          const int  argc,
                          char       **argv) // small string map
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    '"', 'a', 'l', 'p', 'h', 'a', '"', ' ',
                    '"', 'b', 'e', 't', 'a', '"', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', ' ',
                    '"', 'g', 'a', 'm', 'm', 'a', '"',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    '"', 'a', 'l', 'p', 'h', 'a', '"', ' ',
                    '"', 'b', 'e', 't', 'a', '"', ' ',
                    '"', 'd', 'e', 'l', 't', 'a', '"', ' ',
                    '"', 'g', 'a', 'm', 'm', 'a', '"', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::String("gamma"));
            stuff->addValue(new nImO::String("alpha"));
            stuff->addValue(new nImO::String("delta"));
            stuff->addValue(new nImO::String("beta"));
            stuff->addValue(new nImO::String("gamma"));
            stuff->addValue(new nImO::String("alpha"));
            stuff->addValue(new nImO::String("delta"));
            stuff->addValue(new nImO::String("beta"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestSmallStringSetValue
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
doTestArrayWithArrayValue(const char *launchPath,
                          const int  argc,
                          char       **argv) // array with array value
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
        nImO::Array *stuff = new nImO::Array;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartArrayChar,
                    nImO::kStartArrayChar, nImO::kEndArrayChar,
                nImO::kEndArrayChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartArrayChar, ' ',
                    nImO::kStartArrayChar, ' ', nImO::kEndArrayChar, ' ',
                nImO::kEndArrayChar, '\0'
            };

            stuff->addValue(new nImO::Array);
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestArrayWithArrayValue
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
doTestArrayWithMapValue(const char *launchPath,
                        const int  argc,
                        char       **argv) // array with map
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
        nImO::Array *stuff = new nImO::Array;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartArrayChar,
                    nImO::kStartMapChar, nImO::kEndMapChar,
                nImO::kEndArrayChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartArrayChar, ' ',
                    nImO::kStartMapChar, ' ', nImO::kEndMapChar, ' ',
                nImO::kEndArrayChar, '\0'
            };

            stuff->addValue(new nImO::Map);
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestArrayWithMapValue
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
doTestArrayWithSetValue(const char *launchPath,
                        const int  argc,
                        char       **argv) // array with set
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
        nImO::Array *stuff = new nImO::Array;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartArrayChar,
                    nImO::kStartSetChar, nImO::kEndSetChar,
                nImO::kEndArrayChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartArrayChar, ' ',
                    nImO::kStartSetChar, ' ', nImO::kEndSetChar, ' ',
                nImO::kEndArrayChar, '\0'
            };

            stuff->addValue(new nImO::Set);
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestArrayWithSetValue
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
doTestMapWithArrayValue(const char *launchPath,
                        const int  argc,
                        char       **argv) // map with array
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '4', '2', nImO::kKeyValueSeparator,
                        nImO::kStartArrayChar, nImO::kEndArrayChar,
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '4', '2', ' ', nImO::kKeyValueSeparator, ' ',
                        nImO::kStartArrayChar, ' ', nImO::kEndArrayChar, ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42), new nImO::Array());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestMapWithArrayValue
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
doTestMapWithMapValue(const char *launchPath,
                      const int  argc,
                      char       **argv) // map with map
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '4', '2', nImO::kKeyValueSeparator,
                        nImO::kStartMapChar, nImO::kEndMapChar,
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '4', '2', ' ', nImO::kKeyValueSeparator, ' ',
                        nImO::kStartMapChar, ' ', nImO::kEndMapChar, ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42), new nImO::Map());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestMapWithMapValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 65 ***
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
doTestMapWithSetValue(const char *launchPath,
                      const int  argc,
                      char       **argv) // map with set
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '4', '2', nImO::kKeyValueSeparator,
                        nImO::kStartSetChar, nImO::kEndSetChar,
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '4', '2', ' ', nImO::kKeyValueSeparator, ' ',
                        nImO::kStartSetChar, ' ', nImO::kEndSetChar, ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42), new nImO::Set());
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestMapWithSetValue
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
doTestBooleanMapValueWithIncompatibleKeys(const char *launchPath,
                                          const int  argc,
                                          char       **argv) // boolean map with incompatible keys
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    't', 'r', 'u', 'e', nImO::kKeyValueSeparator,
                        '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    't', 'r', 'u', 'e', ' ', nImO::kKeyValueSeparator, ' ',
                        '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Boolean(true), new nImO::Double(123.45));
            stuff->addValue(new nImO::Integer(42), new nImO::Double(12.345));
            stuff->addValue(new nImO::Double(19.77), new nImO::Double(1.2345));
            stuff->addValue(new nImO::String("zebra"), new nImO::Double(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestBooleanMapValueWithIncompatibleKeys
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
doTestIntegerMapValueWithIncompatibleKeys(const char *launchPath,
                                          const int  argc,
                                          char       **argv) // integer map with incompatible keys
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '4', '2', nImO::kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '4', '2', ' ', nImO::kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42), new nImO::Double(123.45));
            stuff->addValue(new nImO::Boolean(true), new nImO::Double(123.45));
            stuff->addValue(new nImO::Double(19.77), new nImO::Double(1.2345));
            stuff->addValue(new nImO::String("zebra"), new nImO::Double(1234.5));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestIntegerMapValueWithIncompatibleKeys
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
doTestStringMapValueWithIncompatibleKeys(const char *launchPath,
                                         const int  argc,
                                         char       **argv) // string map with incompatible keys
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
        nImO::Map *stuff = new nImO::Map;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartMapChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                    nImO::kKeyValueSeparator, '1', '2', '3', '.', '4', '5',
                nImO::kEndMapChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartMapChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                    nImO::kKeyValueSeparator, ' ', '1', '2', '3', '.', '4', '5', ' ',
                nImO::kEndMapChar, '\0'
            };

            stuff->addValue(new nImO::String("charlie"), new nImO::Double(123.45));
            stuff->addValue(new nImO::Boolean(true), new nImO::Double(123.45));
            stuff->addValue(new nImO::Integer(42), new nImO::Double(12.345));
            stuff->addValue(new nImO::Double(19.77), new nImO::Double(1.2345));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestStringMapValueWithIncompatibleKeys
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
doTestBooleanSetValueWithIncompatibleKeys(const char *launchPath,
                                          const int  argc,
                                          char       **argv) // boolean set with incompatible keys
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    't', 'r', 'u', 'e',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    't', 'r', 'u', 'e', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::Boolean(true));
            stuff->addValue(new nImO::Integer(42));
            stuff->addValue(new nImO::Double(19.77));
            stuff->addValue(new nImO::String("zebra"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestBooleanSetValueWithIncompatibleKeys
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
doTestIntegerSetValueWithIncompatibleKeys(const char *launchPath,
                                          const int  argc,
                                          char       **argv) // integer set with incompatible keys
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    '4', '2',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    '4', '2', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::Integer(42));
            stuff->addValue(new nImO::Boolean(true));
            stuff->addValue(new nImO::Double(19.77));
            stuff->addValue(new nImO::String("zebra"));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestIntegerSetValueWithIncompatibleKeys
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
doTestStringSetValueWithIncompatibleKeys(const char *launchPath,
                                         const int  argc,
                                         char       **argv) // string set with incompatible keys
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
        nImO::Set *stuff = new nImO::Set;

        if (stuff)
        {
            static const char expectedSquishedString[] =
            {
                nImO::kStartSetChar,
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"',
                nImO::kEndSetChar, '\0'
            };
            static const char expectedString[] =
            {
                nImO::kStartSetChar, ' ',
                    '"', 'c', 'h', 'a', 'r', 'l', 'i', 'e', '"', ' ',
                nImO::kEndSetChar, '\0'
            };

            stuff->addValue(new nImO::String("charlie"));
            stuff->addValue(new nImO::Boolean(true));
            stuff->addValue(new nImO::Integer(42));
            stuff->addValue(new nImO::Double(19.77));
            if (0 == compareValueWithString(*stuff, expectedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithString(*stuff, expectedString))"); //####
            }
            if (0 == compareValueWithSquishedString(*stuff, expectedSquishedString))
            {
                result = 0;
            }
            else
            {
                ODL_LOG("! (0 == compareValueWithSquishedString(*stuff, " //####
                        "expectedSquishedString))"); //####
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
} // doTestStringSetValueWithIncompatibleKeys
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 100 ***
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
doTestValidArrayCompares(const char *launchPath,
                         const int  argc,
                         char       **argv) // valid array compares
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
        struct testBooleans
        {
            bool _testValue;
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
        }; // testBooleans

        nImO::Array         stuff;
        static testBooleans testSet1l[] =
        {
            // test  <            >            <=           >=           ==
            { false, true,  true, false, true, true,  true, false, true, false, true },
            { true,  false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t        numTestValues1l = (sizeof(testSet1l) / sizeof(testSet1l[0]));
        static testBooleans testSet1r[] =
        {
            // test  <            >            <=           >=          ==
            { false, false, true, true,  true, false, true, true, true, false, true },
            { true,  false, true, false, true, true,  true, true, true, true,  true }
        };
        const size_t        numTestValues1r = (sizeof(testSet1r) / sizeof(testSet1r[0]));

        stuff.addValue(new nImO::Boolean(true));
        stuff.addValue(new nImO::Boolean(true));
        stuff.addValue(new nImO::Boolean(true));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            bool          valid = false;
            nImO::Boolean aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
            {
                ODL_LOG("(testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))"); //####
                result = 1;
            }
            else if (testSet1l[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1l[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualResult != " //####
                            "aValue.lessThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                         valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualResult != " //####
                            "aValue.greaterThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            bool          valid = false;
            nImO::Boolean aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
            {
                ODL_LOG("(testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))"); //####
                result = 1;
            }
            else if (testSet1r[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1r[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualResult != " //####
                            "stuff.lessThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                        valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualResult != " //####
                            "stuff.greaterThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        if (0 == result)
        {
            static testBooleans testSet2l[] =
            {
                // test  <            >            <=           >=          ==
                { false, false, true, false, true, true,  true, true, true, true,  true },
                { true,  false, true, true,  true, false, true, true, true, false, true }
            };
            const size_t        numTestValues2l = (sizeof(testSet2l) / sizeof(testSet2l[0]));
            static testBooleans testSet2r[] =
            {
                // test  <            >            <=          >=           ==
                { false, false, true, false, true, true, true, true,  true, true,  true },
                { true,  true,  true, false, true, true, true, false, true, false, true }
            };
            const size_t        numTestValues2r = (sizeof(testSet2r) / sizeof(testSet2r[0]));

            stuff.clear();
            stuff.addValue(new nImO::Boolean(false));
            stuff.addValue(new nImO::Boolean(false));
            stuff.addValue(new nImO::Boolean(false));
            for (size_t ii = 0; (0 == result) && (numTestValues2l > ii); ++ii)
            {
                bool          valid = false;
                nImO::Boolean aValue(testSet2l[ii]._testValue);

                if (testSet2l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
                {
                    ODL_LOG("(testSet2l[ii]._lessThanResult != aValue.lessThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet2l[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet2l[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanResult != " //####
                                "aValue.greaterThan(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff,
                                                                                       valid))
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqualResult != " //####
                                "aValue.lessThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                             valid))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqualResult != " //####
                                "aValue.greaterThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                    {
                        ODL_LOG("(testSet2l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._equalToValid != valid)"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues2r > ii); ++ii)
            {
                bool          valid = false;
                nImO::Boolean aValue(testSet2r[ii]._testValue);

                if (testSet2r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
                {
                    ODL_LOG("(testSet2r[ii]._lessThanResult != stuff.lessThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet2r[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet2r[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanResult != " //####
                                "stuff.greaterThan(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue,
                                                                                      valid))
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqualResult != " //####
                                "stuff.lessThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                            valid))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqualResult != " //####
                                "stuff.greaterThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                    {
                        ODL_LOG("(testSet2r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._equalToValid != valid)"); //####
                        result = 1;
                    }
                }
            }
        }
        if (0 == result)
        {
            struct testNumbers
            {
                double _testValue;
                bool   _lessThanResult;
                bool   _lessThanValid;
                bool   _greaterThanResult;
                bool   _greaterThanValid;
                bool   _lessThanOrEqualResult;
                bool   _lessThanOrEqualValid;
                bool   _greaterThanOrEqualResult;
                bool   _greaterThanOrEqualValid;
                bool   _equalToResult;
                bool   _equalToValid;
            }; // testNumbers

            static testNumbers testSet3l[] =
            {
                // test <            >            <=           >=           ==
                { -300, true,  true, false, true, true,  true, false, true, false, true },
                { -200, true,  true, false, true, true,  true, false, true, false, true },
                { -100, true,  true, false, true, true,  true, false, true, false, true },
                { -50,  false, true, false, true, false, true, false, true, false, true },
                { -25,  false, true, false, true, false, true, false, true, false, true },
                { 0,    false, true, false, true, false, true, false, true, false, true },
                { 25,   false, true, false, true, false, true, false, true, false, true },
                { 50,   false, true, false, true, false, true, false, true, false, true },
                { 100,  false, true, false, true, false, true, false, true, false, true },
                { 200,  false, true, false, true, false, true, true,  true, false, true },
                { 300,  false, true, true,  true, false, true, true,  true, false, true }
            };
            const size_t       numTestValues3l = (sizeof(testSet3l) / sizeof(testSet3l[0]));
            static testNumbers testSet3r[] =
            {
                // test <            >            <=           >=           ==
                { -300, false, true, true,  true, false, true, true,  true, false, true },
                { -200, false, true, true,  true, false, true, true,  true, false, true },
                { -100, false, true, true,  true, false, true, true,  true, false, true },
                { -50,  false, true, false, true, false, true, false, true, false, true },
                { -25,  false, true, false, true, false, true, false, true, false, true },
                { 0,    false, true, false, true, false, true, false, true, false, true },
                { 25,   false, true, false, true, false, true, false, true, false, true },
                { 50,   false, true, false, true, false, true, false, true, false, true },
                { 100,  false, true, false, true, false, true, false, true, false, true },
                { 200,  false, true, false, true, true,  true, false, true, false, true },
                { 300,  true,  true, false, true, true,  true, false, true, false, true }
            };
            const size_t       numTestValues3r = (sizeof(testSet3r) / sizeof(testSet3r[0]));

            stuff.clear();
            stuff.addValue(new nImO::Double(123.45));
            stuff.addValue(new nImO::Double(200.0));
            stuff.addValue(new nImO::Double(-25.0));
            stuff.addValue(new nImO::Double(-60.0));
            stuff.addValue(new nImO::Double(0.0));
            for (size_t ii = 0; (0 == result) && (numTestValues3l > ii); ++ii)
            {
                bool         valid = false;
                nImO::Double aValue(testSet3l[ii]._testValue);

                if (testSet3l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
                {
                    ODL_LOG("(testSet3l[ii]._lessThanResult != aValue.lessThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet3l[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet3l[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                    {
                        ODL_LOG("(testSet3l[ii]._greaterThanResult != " //####
                                "aValue.greaterThan(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet3l[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet3l[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff,
                                                                                       valid))
                    {
                        ODL_LOG("(testSet3l[ii]._lessThanOrEqualResult != " //####
                                "aValue.lessThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet3l[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet3l[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                             valid))
                    {
                        ODL_LOG("(testSet3l[ii]._greaterThanOrEqualResult != " //####
                                "aValue.greaterThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet3l[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet3l[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                    {
                        ODL_LOG("(testSet3l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet3l[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet3l[ii]._equalToValid != valid)"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues3r > ii); ++ii)
            {
                bool         valid = false;
                nImO::Double aValue(testSet3r[ii]._testValue);

                if (testSet3r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
                {
                    ODL_LOG("(testSet3r[ii]._lessThanResult != stuff.lessThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet3r[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet3r[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                    {
                        ODL_LOG("(testSet3r[ii]._greaterThanResult != " //####
                                "stuff.greaterThan(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet3r[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet3r[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue,
                                                                                      valid))
                    {
                        ODL_LOG("(testSet3r[ii]._lessThanOrEqualResult != " //####
                                "stuff.lessThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet3r[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet3r[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                            valid))
                    {
                        ODL_LOG("(testSet3r[ii]._greaterThanOrEqualResult != " //####
                                "stuff.greaterThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet3r[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet3r[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet3r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                    {
                        ODL_LOG("(testSet3r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet3r[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet3r[ii]._equalToValid != valid)"); //####
                        result = 1;
                    }
                }
            }
        }
        if (0 == result)
        {
            struct testStrings
            {
                const char *_testValue;
                bool       _lessThanResult;
                bool       _lessThanValid;
                bool       _greaterThanResult;
                bool       _greaterThanValid;
                bool       _lessThanOrEqualResult;
                bool       _lessThanOrEqualValid;
                bool       _greaterThanOrEqualResult;
                bool       _greaterThanOrEqualValid;
                bool       _equalToResult;
                bool       _equalToValid;
            }; // testStrings

            static testStrings testSet4l[] =
            {
                // test  <            >            <=           >=           ==
                { "aaa", true,  true, false, true, true,  true, false, true, false, true },
                { "abc", false, true, false, true, true,  true, false, true, false, true },
                { "def", false, true, false, true, false, true, false, true, false, true },
                { "ghi", false, true, false, true, false, true, true,  true, false, true },
                { "zzz", false, true, true,  true, false, true, true,  true, false, true }
            };
            const size_t       numTestValues4l = (sizeof(testSet4l) / sizeof(testSet4l[0]));
            static testStrings testSet4r[] =
            {
                // test  <            >            <=           >=           ==
                { "aaa", false, true, true,  true, false, true, true,  true, false, true },
                { "abc", false, true, false, true, false, true, true,  true, false, true },
                { "def", false, true, false, true, false, true, false, true, false, true },
                { "ghi", false, true, false, true, true,  true, false, true, false, true },
                { "zzz", true,  true, false, true, true,  true, false, true, false, true }
            };
            const size_t       numTestValues4r = (sizeof(testSet4r) / sizeof(testSet4r[0]));

            stuff.clear();
            stuff.addValue(new nImO::String("abc"));
            stuff.addValue(new nImO::String("def"));
            stuff.addValue(new nImO::String("ghi"));
            for (size_t ii = 0; (0 == result) && (numTestValues4l > ii); ++ii)
            {
                bool         valid = false;
                nImO::String aValue(testSet4l[ii]._testValue);

                if (testSet4l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
                {
                    ODL_LOG("(testSet4l[ii]._lessThanResult != aValue.lessThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet4l[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet4l[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                    {
                        ODL_LOG("(testSet4l[ii]._greaterThanResult != " //####
                                "aValue.greaterThan(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet4l[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet4l[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff,
                                                                                       valid))
                    {
                        ODL_LOG("(testSet4l[ii]._lessThanOrEqualResult != " //####
                                "aValue.lessThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet4l[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet4l[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                             valid))
                    {
                        ODL_LOG("(testSet4l[ii]._greaterThanOrEqualResult != " //####
                                "aValue.greaterThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet4l[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet4l[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                    {
                        ODL_LOG("(testSet4l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet4l[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet4l[ii]._equalToValid != valid)"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues4r > ii); ++ii)
            {
                bool         valid = false;
                nImO::String aValue(testSet4r[ii]._testValue);

                if (testSet4r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
                {
                    ODL_LOG("(testSet4r[ii]._lessThanResult != stuff.lessThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet4r[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet4r[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                    {
                        ODL_LOG("(testSet4r[ii]._greaterThanResult != " //####
                                "stuff.greaterThan(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet4r[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet4r[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue,
                                                                                      valid))
                    {
                        ODL_LOG("(testSet4r[ii]._lessThanOrEqualResult != " //####
                                "stuff.lessThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet4r[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet4r[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                            valid))
                    {
                        ODL_LOG("(testSet4r[ii]._greaterThanOrEqualResult != " //####
                                "stuff.greaterThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet4r[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet4r[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet4r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                    {
                        ODL_LOG("(testSet4r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet4r[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet4r[ii]._equalToValid != valid)"); //####
                        result = 1;
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
} // doTestValidArrayCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 101 ***
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
doTestValidBooleanMapCompares(const char *launchPath,
                              const int  argc,
                              char       **argv) // valid boolean map compares
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
        struct testBooleans
        {
            bool _testValue;
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
        }; // testBooleans

        static testBooleans testSet1l[] =
        {
            // test  <            >            <=           >=           ==
            { false, true,  true, false, true, true,  true, false, true, false, true },
            { true,  false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t        numTestValues1l = (sizeof(testSet1l) / sizeof(testSet1l[0]));
        static testBooleans testSet1r[] =
        {
            // test  <            >            <=           >=          ==
            { false, false, true, true,  true, false, true, true, true, false, true },
            { true,  false, true, false, true, true,  true, true, true, true,  true }
        };
        const size_t        numTestValues1r = (sizeof(testSet1r) / sizeof(testSet1r[0]));
        nImO::Map           stuff;

        stuff.addValue(new nImO::Boolean(true), new nImO::String("abc"));
        stuff.addValue(new nImO::Boolean(true), new nImO::String("def"));
        stuff.addValue(new nImO::Boolean(true), new nImO::String("ghi"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            bool          valid = false;
            nImO::Boolean aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
            {
                ODL_LOG("(testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))"); //####
                result = 1;
            }
            else if (testSet1l[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1l[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualResult != " //####
                            "aValue.lessThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                         valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualResult != " //####
                            "aValue.greaterThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            bool          valid = false;
            nImO::Boolean aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
            {
                ODL_LOG("(testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))"); //####
                result = 1;
            }
            else if (testSet1r[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1r[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualResult != " //####
                            "stuff.lessThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                        valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualResult != " //####
                            "stuff.greaterThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        if (0 == result)
        {
            static testBooleans testSet2l[] =
            {
                // test  <            >            <=           >=          ==
                { false, false, true, false, true, true,  true, true, true, true,  true },
                { true,  false, true, true,  true, false, true, true, true, false, true }
            };
            const size_t        numTestValues2l = (sizeof(testSet2l) / sizeof(testSet2l[0]));
            static testBooleans testSet2r[] =
            {
                // test  <            >            <=          >=           ==
                { false, false, true, false, true, true, true, true,  true, true,  true },
                { true,  true,  true, false, true, true, true, false, true, false, true }
            };
            const size_t        numTestValues2r = (sizeof(testSet2r) / sizeof(testSet2r[0]));

            stuff.clear();
            stuff.addValue(new nImO::Boolean(false), new nImO::String("abc"));
            stuff.addValue(new nImO::Boolean(false), new nImO::String("def"));
            stuff.addValue(new nImO::Boolean(false), new nImO::String("ghi"));
            for (size_t ii = 0; (0 == result) && (numTestValues2l > ii); ++ii)
            {
                bool          valid = false;
                nImO::Boolean aValue(testSet2l[ii]._testValue);

                if (testSet2l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
                {
                    ODL_LOG("(testSet2l[ii]._lessThanResult != aValue.lessThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet2l[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet2l[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanResult != " //####
                                "aValue.greaterThan(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff,
                                                                                       valid))
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqualResult != " //####
                                "aValue.lessThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                             valid))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqualResult != " //####
                                "aValue.greaterThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                    {
                        ODL_LOG("(testSet2l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._equalToValid != valid)"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues2r > ii); ++ii)
            {
                bool          valid = false;
                nImO::Boolean aValue(testSet2r[ii]._testValue);

                if (testSet2r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
                {
                    ODL_LOG("(testSet2r[ii]._lessThanResult != stuff.lessThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet2r[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet2r[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanResult != " //####
                                "stuff.greaterThan(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue,
                                                                                      valid))
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqualResult != " //####
                                "stuff.lessThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                            valid))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqualResult != " //####
                                "stuff.greaterThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                    {
                        ODL_LOG("(testSet2r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._equalToValid != valid)"); //####
                        result = 1;
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
} // doTestValidBooleanMapCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 102 ***
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
doTestValidIntegerMapCompares(const char *launchPath,
                              const int  argc,
                              char       **argv) // valid integer map compares
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
        struct testNumbers
        {
            int64_t _testValue;
            bool    _lessThanResult;
            bool    _lessThanValid;
            bool    _greaterThanResult;
            bool    _greaterThanValid;
            bool    _lessThanOrEqualResult;
            bool    _lessThanOrEqualValid;
            bool    _greaterThanOrEqualResult;
            bool    _greaterThanOrEqualValid;
            bool    _equalToResult;
            bool    _equalToValid;
        }; // testNumbers

        static testNumbers testSet1l[] =
        {
            // test <            >            <=           >=           ==
            { -300, true,  true, false, true, true,  true, false, true, false, true },
            { -200, true,  true, false, true, true,  true, false, true, false, true },
            { -100, true,  true, false, true, true,  true, false, true, false, true },
            { -50,  false, true, false, true, false, true, false, true, false, true },
            { -25,  false, true, false, true, false, true, false, true, false, true },
            { 0,    false, true, false, true, false, true, false, true, false, true },
            { 25,   false, true, false, true, false, true, false, true, false, true },
            { 50,   false, true, false, true, false, true, false, true, false, true },
            { 100,  false, true, false, true, false, true, false, true, false, true },
            { 200,  false, true, false, true, false, true, true,  true, false, true },
            { 300,  false, true, true,  true, false, true, true,  true, false, true }
        };
        const size_t       numTestValues1l = (sizeof(testSet1l) / sizeof(testSet1l[0]));

        static testNumbers testSet1r[] =
        {
            // test <            >            <=           >=           ==
            { -300, false, true, true,  true, false, true, true,  true, false, true },
            { -200, false, true, true,  true, false, true, true,  true, false, true },
            { -100, false, true, true,  true, false, true, true,  true, false, true },
            { -50,  false, true, false, true, false, true, false, true, false, true },
            { -25,  false, true, false, true, false, true, false, true, false, true },
            { 0,    false, true, false, true, false, true, false, true, false, true },
            { 25,   false, true, false, true, false, true, false, true, false, true },
            { 50,   false, true, false, true, false, true, false, true, false, true },
            { 100,  false, true, false, true, false, true, false, true, false, true },
            { 200,  false, true, false, true, true,  true, false, true, false, true },
            { 300,  true,  true, false, true, true,  true, false, true, false, true }
        };
        const size_t       numTestValues1r = (sizeof(testSet1r) / sizeof(testSet1r[0]));
        nImO::Map          stuff;

        stuff.addValue(new nImO::Integer(123), new nImO::String("abc"));
        stuff.addValue(new nImO::Integer(200), new nImO::String("def"));
        stuff.addValue(new nImO::Integer(-25), new nImO::String("ghi"));
        stuff.addValue(new nImO::Integer(-60), new nImO::String("jkl"));
        stuff.addValue(new nImO::Integer(0), new nImO::String("mno"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            bool          valid = false;
            nImO::Integer aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
            {
                ODL_LOG("(testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))"); //####
                result = 1;
            }
            else if (testSet1l[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1l[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualResult != " //####
                            "aValue.lessThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                         valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualResult != " //####
                            "aValue.greaterThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            bool          valid = false;
            nImO::Integer aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
            {
                ODL_LOG("(testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))"); //####
                result = 1;
            }
            else if (testSet1r[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1r[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualResult != " //####
                            "stuff.lessThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                        valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualResult != " //####
                            "stuff.greaterThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._equalToValid != valid)"); //####
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
} // doTestValidIntegerMapCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 103 ***
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
doTestValidStringMapCompares(const char *launchPath,
                             const int  argc,
                             char       **argv) // valid string map compares
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
        struct testStrings
        {
            const char *_testValue;
            bool       _lessThanResult;
            bool       _lessThanValid;
            bool       _greaterThanResult;
            bool       _greaterThanValid;
            bool       _lessThanOrEqualResult;
            bool       _lessThanOrEqualValid;
            bool       _greaterThanOrEqualResult;
            bool       _greaterThanOrEqualValid;
            bool       _equalToResult;
            bool       _equalToValid;
        }; // testStrings

        static testStrings testSet1l[] =
        {
            // test  <            >            <=           >=           ==
            { "aaa", true,  true, false, true, true,  true, false, true, false, true },
            { "abc", false, true, false, true, true,  true, false, true, false, true },
            { "def", false, true, false, true, false, true, false, true, false, true },
            { "ghi", false, true, false, true, false, true, true,  true, false, true },
            { "zzz", false, true, true,  true, false, true, true,  true, false, true }
        };
        const size_t       numTestValues1l = (sizeof(testSet1l) / sizeof(testSet1l[0]));
        static testStrings testSet1r[] =
        {
            // test  <            >            <=           >=           ==
            { "aaa", false, true, true,  true, false, true, true,  true, false, true },
            { "abc", false, true, false, true, false, true, true,  true, false, true },
            { "def", false, true, false, true, false, true, false, true, false, true },
            { "ghi", false, true, false, true, true,  true, false, true, false, true },
            { "zzz", true,  true, false, true, true,  true, false, true, false, true }
        };
        const size_t       numTestValues1r = (sizeof(testSet1r) / sizeof(testSet1r[0]));
        nImO::Map          stuff;

        stuff.addValue(new nImO::String("abc"), new nImO::String("123"));
        stuff.addValue(new nImO::String("def"), new nImO::String("456"));
        stuff.addValue(new nImO::String("ghi"), new nImO::String("789"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            bool         valid = false;
            nImO::String aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
            {
                ODL_LOG("(testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))"); //####
                result = 1;
            }
            else if (testSet1l[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1l[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualResult != " //####
                            "aValue.lessThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                         valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualResult != " //####
                            "aValue.greaterThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            bool         valid = false;
            nImO::String aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
            {
                ODL_LOG("(testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))"); //####
                result = 1;
            }
            else if (testSet1r[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1r[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualResult != " //####
                            "stuff.lessThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                        valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualResult != " //####
                            "stuff.greaterThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._equalToValid != valid)"); //####
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
} // doTestValidStringMapCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 104 ***
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
doTestValidBooleanSetCompares(const char *launchPath,
                              const int  argc,
                              char       **argv) // valid boolean set compares
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
        struct testBooleans
        {
            bool _testValue;
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
        }; // testBooleans

        static testBooleans testSet1l[] =
        {
            // test  <            >            <=           >=           ==
            { false, true,  true, false, true, true,  true, false, true, false, true },
            { true,  false, true, false, true, true,  true, true,  true, true,  true }
        };
        const size_t        numTestValues1l = (sizeof(testSet1l) / sizeof(testSet1l[0]));
        static testBooleans testSet1r[] =
        {
            // test  <            >            <=           >=          ==
            { false, false, true, true,  true, false, true, true, true, false, true },
            { true,  false, true, false, true, true,  true, true, true, true,  true }
        };
        const size_t        numTestValues1r = (sizeof(testSet1r) / sizeof(testSet1r[0]));
        nImO::Set           stuff;

        stuff.addValue(new nImO::Boolean(true));
        stuff.addValue(new nImO::Boolean(true));
        stuff.addValue(new nImO::Boolean(true));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            bool          valid = false;
            nImO::Boolean aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
            {
                ODL_LOG("(testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))"); //####
                result = 1;
            }
            else if (testSet1l[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1l[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualResult != " //####
                            "aValue.lessThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                         valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualResult != " //####
                            "aValue.greaterThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            bool          valid = false;
            nImO::Boolean aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
            {
                ODL_LOG("(testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))"); //####
                result = 1;
            }
            else if (testSet1r[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1r[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualResult != " //####
                            "stuff.lessThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                        valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualResult != " //####
                            "stuff.greaterThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        if (0 == result)
        {
            static testBooleans testSet2l[] =
            {
                // test  <            >            <=           >=          ==
                { false, false, true, false, true, true,  true, true, true, true,  true },
                { true,  false, true, true,  true, false, true, true, true, false, true }
            };
            const size_t        numTestValues2l = (sizeof(testSet2l) / sizeof(testSet2l[0]));
            static testBooleans testSet2r[] =
            {
                // test  <            >            <=          >=           ==
                { false, false, true, false, true, true, true, true,  true, true,  true },
                { true,  true,  true, false, true, true, true, false, true, false, true }
            };
            const size_t        numTestValues2r = (sizeof(testSet2r) / sizeof(testSet2r[0]));

            stuff.clear();
            stuff.addValue(new nImO::Boolean(false));
            stuff.addValue(new nImO::Boolean(false));
            stuff.addValue(new nImO::Boolean(false));
            for (size_t ii = 0; (0 == result) && (numTestValues2l > ii); ++ii)
            {
                bool          valid = false;
                nImO::Boolean aValue(testSet2l[ii]._testValue);

                if (testSet2l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
                {
                    ODL_LOG("(testSet2l[ii]._lessThanResult != aValue.lessThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet2l[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet2l[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanResult != " //####
                                "aValue.greaterThan(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff,
                                                                                       valid))
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqualResult != " //####
                                "aValue.lessThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                             valid))
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqualResult != " //####
                                "aValue.greaterThanOrEqual(stuff, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                    {
                        ODL_LOG("(testSet2l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet2l[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet2l[ii]._equalToValid != valid)"); //####
                        result = 1;
                    }
                }
            }
            for (size_t ii = 0; (0 == result) && (numTestValues2r > ii); ++ii)
            {
                bool          valid = false;
                nImO::Boolean aValue(testSet2r[ii]._testValue);

                if (testSet2r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
                {
                    ODL_LOG("(testSet2r[ii]._lessThanResult != stuff.lessThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet2r[ii]._lessThanValid != valid)
                {
                    ODL_LOG("(testSet2r[ii]._lessThanValid != valid)"); //####
                    result = 1;
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanResult != " //####
                                "stuff.greaterThan(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._greaterThanValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue,
                                                                                      valid))
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqualResult != " //####
                                "stuff.lessThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._lessThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._lessThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                            valid))
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqualResult != " //####
                                "stuff.greaterThanOrEqual(aValue, valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._greaterThanOrEqualValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._greaterThanOrEqualValid != valid)"); //####
                        result = 1;
                    }
                }
                if (0 == result)
                {
                    if (testSet2r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                    {
                        ODL_LOG("(testSet2r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                                "valid))"); //####
                        result = 1;
                    }
                    else if (testSet2r[ii]._equalToValid != valid)
                    {
                        ODL_LOG("(testSet2r[ii]._equalToValid != valid)"); //####
                        result = 1;
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
} // doTestValidBooleanSetCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 105 ***
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
doTestValidIntegerSetCompares(const char *launchPath,
                              const int  argc,
                              char       **argv) // valid integer set compares
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
        struct testNumbers
        {
            int64_t _testValue;
            bool    _lessThanResult;
            bool    _lessThanValid;
            bool    _greaterThanResult;
            bool    _greaterThanValid;
            bool    _lessThanOrEqualResult;
            bool    _lessThanOrEqualValid;
            bool    _greaterThanOrEqualResult;
            bool    _greaterThanOrEqualValid;
            bool    _equalToResult;
            bool    _equalToValid;
        }; // testNumbers

        static testNumbers testSet1l[] =
        {
            // test <            >            <=           >=           ==
            { -300, true,  true, false, true, true,  true, false, true, false, true },
            { -200, true,  true, false, true, true,  true, false, true, false, true },
            { -100, true,  true, false, true, true,  true, false, true, false, true },
            { -50,  false, true, false, true, false, true, false, true, false, true },
            { -25,  false, true, false, true, false, true, false, true, false, true },
            { 0,    false, true, false, true, false, true, false, true, false, true },
            { 25,   false, true, false, true, false, true, false, true, false, true },
            { 50,   false, true, false, true, false, true, false, true, false, true },
            { 100,  false, true, false, true, false, true, false, true, false, true },
            { 200,  false, true, false, true, false, true, true,  true, false, true },
            { 300,  false, true, true,  true, false, true, true,  true, false, true }
        };
        const size_t       numTestValues1l = (sizeof(testSet1l) / sizeof(testSet1l[0]));

        static testNumbers testSet1r[] =
        {
            // test <            >            <=           >=           ==
            { -300, false, true, true,  true, false, true, true,  true, false, true },
            { -200, false, true, true,  true, false, true, true,  true, false, true },
            { -100, false, true, true,  true, false, true, true,  true, false, true },
            { -50,  false, true, false, true, false, true, false, true, false, true },
            { -25,  false, true, false, true, false, true, false, true, false, true },
            { 0,    false, true, false, true, false, true, false, true, false, true },
            { 25,   false, true, false, true, false, true, false, true, false, true },
            { 50,   false, true, false, true, false, true, false, true, false, true },
            { 100,  false, true, false, true, false, true, false, true, false, true },
            { 200,  false, true, false, true, true,  true, false, true, false, true },
            { 300,  true,  true, false, true, true,  true, false, true, false, true }
        };
        const size_t       numTestValues1r = (sizeof(testSet1r) / sizeof(testSet1r[0]));
        nImO::Set          stuff;

        stuff.addValue(new nImO::Integer(123));
        stuff.addValue(new nImO::Integer(200));
        stuff.addValue(new nImO::Integer(-25));
        stuff.addValue(new nImO::Integer(-60));
        stuff.addValue(new nImO::Integer(0));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            bool          valid = false;
            nImO::Integer aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
            {
                ODL_LOG("(testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))"); //####
                result = 1;
            }
            else if (testSet1l[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1l[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualResult != " //####
                            "aValue.lessThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                         valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualResult != " //####
                            "aValue.greaterThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            bool          valid = false;
            nImO::Integer aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
            {
                ODL_LOG("(testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))"); //####
                result = 1;
            }
            else if (testSet1r[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1r[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanResult != " //####
                            "stuff.greaterThan(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualResult != " //####
                            "stuff.lessThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                        valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualResult != " //####
                            "stuff.greaterThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._equalToValid != valid)"); //####
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
} // doTestValidIntegerSetCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 106 ***
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
doTestValidStringSetCompares(const char *launchPath,
                             const int  argc,
                             char       **argv) // valid string set compares
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
        struct testStrings
        {
            const char *_testValue;
            bool       _lessThanResult;
            bool       _lessThanValid;
            bool       _greaterThanResult;
            bool       _greaterThanValid;
            bool       _lessThanOrEqualResult;
            bool       _lessThanOrEqualValid;
            bool       _greaterThanOrEqualResult;
            bool       _greaterThanOrEqualValid;
            bool       _equalToResult;
            bool       _equalToValid;
        }; // testStrings

        static testStrings testSet1l[] =
        {
            // test  <            >            <=           >=           ==
            { "aaa", true,  true, false, true, true,  true, false, true, false, true },
            { "abc", false, true, false, true, true,  true, false, true, false, true },
            { "def", false, true, false, true, false, true, false, true, false, true },
            { "ghi", false, true, false, true, false, true, true,  true, false, true },
            { "zzz", false, true, true,  true, false, true, true,  true, false, true }
        };
        const size_t       numTestValues1l = (sizeof(testSet1l) / sizeof(testSet1l[0]));
        static testStrings testSet1r[] =
        {
            // test  <            >            <=           >=           ==
            { "aaa", false, true, true,  true, false, true, true,  true, false, true },
            { "abc", false, true, false, true, false, true, true,  true, false, true },
            { "def", false, true, false, true, false, true, false, true, false, true },
            { "ghi", false, true, false, true, true,  true, false, true, false, true },
            { "zzz", true,  true, false, true, true,  true, false, true, false, true }
        };
        const size_t       numTestValues1r = (sizeof(testSet1r) / sizeof(testSet1r[0]));
        nImO::Set          stuff;

        stuff.addValue(new nImO::String("abc"));
        stuff.addValue(new nImO::String("def"));
        stuff.addValue(new nImO::String("ghi"));
        for (size_t ii = 0; (0 == result) && (numTestValues1l > ii); ++ii)
        {
            bool         valid = false;
            nImO::String aValue(testSet1l[ii]._testValue);

            if (testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))
            {
                ODL_LOG("(testSet1l[ii]._lessThanResult != aValue.lessThan(stuff, valid))"); //####
                result = 1;
            }
            else if (testSet1l[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1l[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanResult != aValue.greaterThan(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._lessThanOrEqualResult != aValue.lessThanOrEqual(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualResult != " //####
                            "aValue.lessThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._greaterThanOrEqualResult != aValue.greaterThanOrEqual(stuff,
                                                                                         valid))
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualResult != " //####
                            "aValue.greaterThanOrEqual(stuff, valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1l[ii]._equalToResult != aValue.equalTo(stuff, valid))
                {
                    ODL_LOG("(testSet1l[ii]._equalToResult != aValue.equalTo(stuff, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1l[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1l[ii]._equalToValid != valid)"); //####
                    result = 1;
                }
            }
        }
        for (size_t ii = 0; (0 == result) && (numTestValues1r > ii); ++ii)
        {
            bool         valid = false;
            nImO::String aValue(testSet1r[ii]._testValue);

            if (testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))
            {
                ODL_LOG("(testSet1r[ii]._lessThanResult != stuff.lessThan(aValue, valid))"); //####
                result = 1;
            }
            else if (testSet1r[ii]._lessThanValid != valid)
            {
                ODL_LOG("(testSet1r[ii]._lessThanValid != valid)"); //####
                result = 1;
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanResult != stuff.greaterThan(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._lessThanOrEqualResult != stuff.lessThanOrEqual(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualResult != " //####
                            "stuff.lessThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._lessThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._lessThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._greaterThanOrEqualResult != stuff.greaterThanOrEqual(aValue,
                                                                                        valid))
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualResult != " //####
                            "stuff.greaterThanOrEqual(aValue, valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._greaterThanOrEqualValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._greaterThanOrEqualValid != valid)"); //####
                    result = 1;
                }
            }
            if (0 == result)
            {
                if (testSet1r[ii]._equalToResult != stuff.equalTo(aValue, valid))
                {
                    ODL_LOG("(testSet1r[ii]._equalToResult != stuff.equalTo(aValue, " //####
                            "valid))"); //####
                    result = 1;
                }
                else if (testSet1r[ii]._equalToValid != valid)
                {
                    ODL_LOG("(testSet1r[ii]._equalToValid != valid)"); //####
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
} // doTestValidStringSetCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 107 ***
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
doTestInvalidArrayCompares(const char *launchPath,
                           const int  argc,
                           char       **argv) // invalid array compares
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
        nImO::Array   leftValue;
        nImO::Boolean rightValue1;
        nImO::Double  rightValue2;
        nImO::String  rightValue3;
        nImO::Blob    rightValue4;
        nImO::Array   rightValue5;
        nImO::Map     rightValue6;
        nImO::Set     rightValue7;
        nImO::Integer rightValue8;
        nImO::Value   *rightValues[] =
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4,
            &rightValue5, &rightValue6, &rightValue7, &rightValue8
        };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        leftValue.addValue(new nImO::Boolean);
        leftValue.addValue(new nImO::Number);
        leftValue.addValue(new nImO::String);
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            nImO::Value &aRightValue = *rightValues[ii];

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
} // doTestInvalidArrayCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 108 ***
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
doTestInvalidBooleanMapCompares(const char *launchPath,
                                const int  argc,
                                char       **argv) // invalid boolean map compares
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
        nImO::Map     leftValue;
        nImO::Integer rightValue1;
        nImO::String  rightValue2;
        nImO::Blob    rightValue3;
        nImO::Array   rightValue4;
        nImO::Map     rightValue5;
        nImO::Set     rightValue6;
        nImO::Double  rightValue7;
        nImO::Value   *rightValues[] =
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        leftValue.addValue(new nImO::Boolean(false), new nImO::String("false"));
        leftValue.addValue(new nImO::Boolean(true), new nImO::String("true"));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            nImO::Value &aRightValue = *rightValues[ii];

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
} // doTestInvalidBooleanMapCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 109 ***
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
doTestInvalidIntegerMapCompares(const char *launchPath,
                                const int  argc,
                                char       **argv) // invalid integer map compares
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
        nImO::Map     leftValue;
        nImO::Boolean rightValue1;
        nImO::String  rightValue2;
        nImO::Blob    rightValue3;
        nImO::Array   rightValue4;
        nImO::Map     rightValue5;
        nImO::Set     rightValue6;
        nImO::Value   *rightValues[] =
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6
        };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        leftValue.addValue(new nImO::Integer(42), new nImO::Double(123.45));
        leftValue.addValue(new nImO::Integer(17), new nImO::Double(12.345));
        leftValue.addValue(new nImO::Integer(12), new nImO::Double(1234.5));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            nImO::Value &aRightValue = *rightValues[ii];

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
} // doTestInvalidIntegerMapCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 110 ***
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
doTestInvalidStringMapCompares(const char *launchPath,
                               const int  argc,
                               char       **argv) // invalid string map compares
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
        nImO::Map     leftValue;
        nImO::Double  rightValue1;
        nImO::Boolean rightValue2;
        nImO::Blob    rightValue3;
        nImO::Array   rightValue4;
        nImO::Map     rightValue5;
        nImO::Set     rightValue6;
        nImO::Integer rightValue7;
        nImO::Value   *rightValues[] =
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        leftValue.addValue(new nImO::String("abc"), new nImO::String("123"));
        leftValue.addValue(new nImO::String("def"), new nImO::String("456"));
        leftValue.addValue(new nImO::String("ghi"), new nImO::String("789"));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            nImO::Value &aRightValue = *rightValues[ii];

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
} // doTestInvalidStringMapCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 111 ***
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
doTestInvalidBooleanSetCompares(const char *launchPath,
                                const int  argc,
                                char       **argv) // invalid boolean set compares
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
        nImO::Set     leftValue;
        nImO::Double  rightValue1;
        nImO::String  rightValue2;
        nImO::Blob    rightValue3;
        nImO::Array   rightValue4;
        nImO::Map     rightValue5;
        nImO::Set     rightValue6;
        nImO::Integer rightValue7;
        nImO::Value   *rightValues[] =
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        leftValue.addValue(new nImO::Boolean(false));
        leftValue.addValue(new nImO::Boolean(true));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            nImO::Value &aRightValue = *rightValues[ii];

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
} // doTestInvalidBooleanSetCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 112 ***
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
doTestInvalidIntegerSetCompares(const char *launchPath,
                                const int  argc,
                                char       **argv) // invalid integer set compares
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
        nImO::Set     leftValue;
        nImO::Boolean rightValue1;
        nImO::String  rightValue2;
        nImO::Blob    rightValue3;
        nImO::Array   rightValue4;
        nImO::Map     rightValue5;
        nImO::Set     rightValue6;
        nImO::Value   *rightValues[] =
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6
        };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        leftValue.addValue(new nImO::Integer(42));
        leftValue.addValue(new nImO::Integer(17));
        leftValue.addValue(new nImO::Integer(12));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            nImO::Value &aRightValue = *rightValues[ii];

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
} // doTestInvalidIntegerSetCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 113 ***
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
doTestInvalidStringSetCompares(const char *launchPath,
                               const int  argc,
                               char       **argv) // invalid string set compares
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
        nImO::Set     leftValue;
        nImO::Double  rightValue1;
        nImO::Boolean rightValue2;
        nImO::Blob    rightValue3;
        nImO::Array   rightValue4;
        nImO::Map     rightValue5;
        nImO::Set     rightValue6;
        nImO::Integer rightValue7;
        nImO::Value   *rightValues[] =
        {
            &rightValue1, &rightValue2, &rightValue3, &rightValue4, &rightValue5, &rightValue6,
            &rightValue7
        };
        const size_t  numRightValues = (sizeof(rightValues) / sizeof(rightValues[0]));

        leftValue.addValue(new nImO::String("abc"));
        leftValue.addValue(new nImO::String("def"));
        leftValue.addValue(new nImO::String("ghi"));
        for (size_t ii = 0; (0 == result) && (numRightValues > ii); ++ii)
        {
            nImO::Value &aRightValue = *rightValues[ii];

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
} // doTestInvalidStringSetCompares
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 120 ***
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
doTestArrayIndices(const char *launchPath,
                   const int  argc,
                   char       **argv) // array indices
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
        nImO::Array   stuff;
        nImO::Boolean *aBoolValue;
        nImO::Number  *aNumberValue;
        nImO::String  *aStringValue;

        if (0 != stuff.size())
        {
            ODL_LOG("(0 != stuff.size())"); //####
            result = 1;
        }
        if (0 == result)
        {
            if (NULL != stuff.at(0))
            {
                ODL_LOG("(NULL != aValue)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if (NULL != stuff.at(1))
            {
                ODL_LOG("NULL != aValue"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            aBoolValue = new nImO::Boolean;
            stuff.addValue(aBoolValue);
            if (1 != stuff.size())
            {
                ODL_LOG("(1 != stuff.size())"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if (stuff.at(0) != aBoolValue)
            {
                ODL_LOG("(stuff.at(0) != aBoolValue)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            aNumberValue = new nImO::Number;
            stuff.addValue(aNumberValue);
            if (2 != stuff.size())
            {
                ODL_LOG("(2 != stuff.size())"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if ((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue))
            {
                ODL_LOG("((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue))"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            aStringValue = new nImO::String;
            stuff.addValue(aStringValue);
            if (3 != stuff.size())
            {
                ODL_LOG("(3 != stuff.size())"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            if ((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue) ||
                (stuff.at(2) != aStringValue))
            {
                ODL_LOG("((stuff.at(0) != aBoolValue) || (stuff.at(1) != aNumberValue) || " //####
                        "(stuff.at(2) != aStringValue))"); //####
                result = 1;
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
} // doTestArrayIndices
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 121 ***
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
doTestBooleanMapSearches(const char *launchPath,
                         const int  argc,
                         char       **argv) // boolean map searches
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
        nImO::Map           stuff;
        nImO::Map::iterator iter;
        nImO::String        *falseString = new nImO::String("false");
        nImO::String        *trueString;

        stuff.addValue(new nImO::Boolean(false), falseString);
        iter = stuff.find(nImO::Boolean(true));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean(false));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != falseString)
            {
                ODL_LOG("(iter->second != falseString)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean(true));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            trueString = new nImO::String("true");
            stuff.addValue(new nImO::Boolean(true), trueString);
            iter = stuff.find(nImO::Boolean(true));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != trueString)
            {
                ODL_LOG("(iter->second != trueString)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestBooleanMapSearches
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 122 ***
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
doTestIntegerMapSearches(const char *launchPath,
                         const int  argc,
                         char       **argv) // integer map searches
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
        nImO::Map           stuff;
        nImO::Map::iterator iter;
        nImO::String        *string17 = new nImO::String("17");
        nImO::String        *string12;

        stuff.addValue(new nImO::Integer(17), string17);
        iter = stuff.find(nImO::Integer(12));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer(17));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != string17)
            {
                ODL_LOG("(iter->second != string17)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer(12));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            string12 = new nImO::String("12");
            stuff.addValue(new nImO::Integer(12), string12);
            iter = stuff.find(nImO::Integer(12));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != string12)
            {
                ODL_LOG("(iter->second != string12)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestIntegerMapSearches
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 123 ***
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
doTestStringMapSearches(const char *launchPath,
                        const int  argc,
                        char       **argv) // string map searches
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
        nImO::Map           stuff;
        nImO::Map::iterator iter;
        nImO::String        *stringOneSeven = new nImO::String("17");
        nImO::String        *stringOneTwo;

        stuff.addValue(new nImO::String("abc"), stringOneSeven);
        iter = stuff.find(nImO::String("def"));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String("abc"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != stringOneSeven)
            {
                ODL_LOG("(iter->second != stringOneSeven)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String("def"));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stringOneTwo = new nImO::String("12");
            stuff.addValue(new nImO::String("def"), stringOneTwo);
            iter = stuff.find(nImO::String("def"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
            else if (iter->second != stringOneTwo)
            {
                ODL_LOG("(iter->second != stringOneTwo)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestStringMapSearches
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 124 ***
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
doTestBooleanSetSearches(const char *launchPath,
                         const int  argc,
                         char       **argv) // boolean set searches
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
        nImO::Set           stuff;
        nImO::Set::iterator iter;

        stuff.addValue(new nImO::Boolean(false));
        iter = stuff.find(nImO::Boolean(true));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean(false));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean(true));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stuff.addValue(new nImO::Boolean(true));
            iter = stuff.find(nImO::Boolean(true));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestBooleanSetSearches
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 125 ***
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
doTestIntegerSetSearches(const char *launchPath,
                         const int  argc,
                         char       **argv) // integer set searches
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
        nImO::Set           stuff;
        nImO::Set::iterator iter;

        stuff.addValue(new nImO::Integer(17));
        iter = stuff.find(nImO::Integer(12));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer(17));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer(12));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stuff.addValue(new nImO::Integer(12));
            iter = stuff.find(nImO::Integer(12));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestIntegerSetSearches
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 126 ***
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
doTestStringSetSearches(const char *launchPath,
                        const int  argc,
                        char       **argv) // string set searches
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
        nImO::Set           stuff;
        nImO::Set::iterator iter;

        stuff.addValue(new nImO::String("abc"));
        iter = stuff.find(nImO::String("def"));
        if (stuff.end() != iter)
        {
            ODL_LOG("(stuff.end() != iter)"); //####
            result = 1;
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String("abc"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::String("def"));
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            stuff.addValue(new nImO::String("def"));
            iter = stuff.find(nImO::String("def"));
            if (stuff.end() == iter)
            {
                ODL_LOG("(stuff.end() == iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Boolean());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
            }
        }
        if (0 == result)
        {
            iter = stuff.find(nImO::Integer());
            if (stuff.end() != iter)
            {
                ODL_LOG("(stuff.end() != iter)"); //####
                result = 1;
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
} // doTestStringSetSearches
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
        nImO::Initialize(progName);
        if (0 < --argc)
        {
            const char *startPtr = argv[1];
            char       *endPtr;
            int        selector = strtol(startPtr, &endPtr, 10);

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
                        result = doTestEmptyArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestSingularArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestSmallArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestBigArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 20 :
                        result = doTestEmptyMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 21 :
                        result = doTestSingularBooleanMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 22 :
                        result = doTestSingularIntegerMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 23 :
                        result = doTestSingularStringMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 24 :
                        result = doTestSmallBooleanMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 25 :
                        result = doTestSmallIntegerMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 26 :
                        result = doTestSmallStringMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 40 :
                        result = doTestEmptySetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 41 :
                        result = doTestSingularBooleanSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 42 :
                        result = doTestSingularIntegerSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 43 :
                        result = doTestSingularStringSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 44 :
                        result = doTestSmallBooleanSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 45 :
                        result = doTestSmallIntegerSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 46 :
                        result = doTestSmallStringSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 60 :
                        result = doTestArrayWithArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 61 :
                        result = doTestArrayWithMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 62 :
                        result = doTestArrayWithSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 63 :
                        result = doTestMapWithArrayValue(*argv, argc - 1, argv + 2);
                        break;

                    case 64 :
                        result = doTestMapWithMapValue(*argv, argc - 1, argv + 2);
                        break;

                    case 65 :
                        result = doTestMapWithSetValue(*argv, argc - 1, argv + 2);
                        break;

                    case 80 :
                        result = doTestBooleanMapValueWithIncompatibleKeys(*argv, argc - 1,
                                                                           argv + 2);
                        break;

                    case 81 :
                        result = doTestIntegerMapValueWithIncompatibleKeys(*argv, argc - 1,
                                                                           argv + 2);
                        break;

                    case 82 :
                        result = doTestStringMapValueWithIncompatibleKeys(*argv, argc - 1,
                                                                          argv + 2);
                        break;

                    case 83 :
                        result = doTestBooleanSetValueWithIncompatibleKeys(*argv, argc - 1,
                                                                           argv + 2);
                        break;

                    case 84 :
                        result = doTestIntegerSetValueWithIncompatibleKeys(*argv, argc - 1,
                                                                           argv + 2);
                        break;

                    case 85 :
                        result = doTestStringSetValueWithIncompatibleKeys(*argv, argc - 1,
                                                                           argv + 2);
                        break;

                    case 100 :
                        result = doTestValidArrayCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 101 :
                        result = doTestValidBooleanMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 102 :
                        result = doTestValidIntegerMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 103 :
                        result = doTestValidStringMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 104 :
                        result = doTestValidBooleanSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 105 :
                        result = doTestValidIntegerSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 106 :
                        result = doTestValidStringSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 107 :
                        result = doTestInvalidArrayCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 108 :
                        result = doTestInvalidBooleanMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 109 :
                        result = doTestInvalidIntegerMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 110 :
                        result = doTestInvalidStringMapCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 111 :
                        result = doTestInvalidBooleanSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 112 :
                        result = doTestInvalidIntegerSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 113 :
                        result = doTestInvalidStringSetCompares(*argv, argc - 1, argv + 2);
                        break;

                    case 120 :
                        result = doTestArrayIndices(*argv, argc - 1, argv + 2);
                        break;

                    case 121 :
                        result = doTestBooleanMapSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 122 :
                        result = doTestIntegerMapSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 123 :
                        result = doTestStringMapSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 124 :
                        result = doTestBooleanSetSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 125 :
                        result = doTestIntegerSetSearches(*argv, argc - 1, argv + 2);
                        break;

                    case 126 :
                        result = doTestStringSetSearches(*argv, argc - 1, argv + 2);
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

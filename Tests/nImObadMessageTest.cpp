//--------------------------------------------------------------------------------------------------
//
//  File:       Tests/nImObadMessageTest.cpp
//
//  Project:    nImO
//
//  Contains:   The test driver for the unit tests of the nImO common library.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2017 by OpenDragon.
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
//  Created:    2017-03-06
//
//--------------------------------------------------------------------------------------------------

#include <nImOarray.hpp>
#include <nImOblob.hpp>
#include <nImObufferChunk.hpp>
#include <nImOdouble.hpp>
#include <nImOflaw.hpp>
#include <nImOinteger.hpp>
#include <nImOlogical.hpp>
#include <nImOmap.hpp>
#include <nImOmessage.hpp>
#include <nImOset.hpp>
#include <nImOstring.hpp>
#include <nImOstringBuffer.hpp>

//#include <ODEnableLogging.h>
#include <ODLogging.h>

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
using std::cerr;
using std::cout;
using std::endl;

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
static void
catchSignal(int signal)
{
    ODL_ENTER(); //####
    ODL_LL1("signal = ", signal); //####
    std::string message("Exiting due to signal ");

    message += std::to_string(signal);
    message += " = ";
    message += NameOfSignal(signal);
#if 0
    nImO_ERROR_(message.c_str());
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // catchSignal

/*! @brief Extract a Value from a Message and verify what was stored.
 @param[in,out] stuff The Message to be modified.
 @param[in] insertedContents The data to be added to the Message.
 @param[in] insertedSize The size of the data added to the Message.
 @param[in] expectedFlawString The expected Flaw result from the Message.
 @returns Zero on success and non-zero on failure. */
static int
attemptExtractValueAndCheck(Message           &stuff,
                            const DataKind    *insertedContents,
                            const size_t      insertedSize,
                            const std::string &expectedFlawString)
{
    ODL_ENTER(); //####
    ODL_P2("stuff = ", &stuff, "insertedContents = ", insertedContents); //####
    ODL_LL1("insertedSize = ", insertedSize); //####
    ODL_S1s("expectedFlawString = ", expectedFlawString); //####
    ODL_PACKET("inserted", insertedContents, insertedSize); //####
    int result = 1;

    stuff.open(false);
    stuff.appendBytes(insertedContents, insertedSize);
    SpValue extractedValue(stuff.getValue());

    ODL_P1("extractedValue <- ", extractedValue.get()); //####
    stuff.close();
    if (nullptr == extractedValue)
    {
        ODL_LOG("(nullptr == extractedValue)"); //####
    }
    else
    {
        const Flaw *asFlaw = extractedValue->asFlaw();
                    
        if (asFlaw)
        {
            ODL_LOG("(asFlaw)"); //####
            ODL_LOG(asFlaw->getDescription().c_str()); //####
            if (asFlaw->getDescription() == expectedFlawString)
            {
                ODL_LOG("(asFlaw->getDescription() == expectedFlawString)"); //####
                result = 0;
            }
            stuff.reset();
        }
    }
    ODL_EXIT_LL(result); //####
    return result;
} // attemptExtractValueAndCheck

#if defined(__APPLE__)
# pragma mark *** Test Case 001 ***
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
doTestMessageInitialEndTag(const char *launchPath,
                           const int  argc,
                           char       **argv) // message wrong initial tag
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
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            ODL_LOG("(stuff)"); //####
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with incorrect start tag @0");
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
} // doTestMessageInitialEndTag 
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 002 ***
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
doTestMessageTerminalStartTag(const char *launchPath,
                              const int  argc,
                              char       **argv) // message wrong terminal tag
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
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // End of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Message with incorrect end tag @1");
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
} // doTestMessageTerminalStartTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 003 ***
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
doTestEmptyMessageWithContent(const char *launchPath,
                              const int  argc,
                              char       **argv) // empty message with content
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
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Message
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Message with incorrect end tag @1");
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
} // doTestEmptyMessageWithContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 004 ***
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
doTestNonEmptyMessageWithoutContent(const char *launchPath,
                                    const int  argc,
                                    char       **argv) // non-empty message without content
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
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with mismatched initial Value tag @1");
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
} // doTestNonEmptyMessageWithoutContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 005 ***
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
doTestNonEmptyMessageWithMismatchedInitialStartTag(const char *launchPath,
                                                   const int  argc,
                                                   char       **argv) // message with mismatched tag
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
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with mismatched initial Value tag @1");
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
} // doTestNonEmptyMessageWithMismatchedInitialStartTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 006 ***
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
doTestNonEmptyMessageWithMismatchedTerminalEndTag(const char *launchPath,
                                                  const int  argc,
                                                  char       **argv) // message with mismatched tag
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
        auto stuff(make_unique<Message>());

        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedIntegerValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));

            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Message with mismatched end Value tag @2");
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
} // doTestNonEmptyMessageWithMismatchedTerminalEndTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 007 ***
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
doTestNonEmptyMessageWithInvalidContentTag(const char *launchPath,
                                           const int  argc,
                                           char       **argv) // message with invalid content tag
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Invalid
                DataKind::EscapeValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1");
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
} // doTestEmptyStringMessage
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 008 ***
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
doTestNonEmptyMessageWithZeroFloatCount(const char *launchPath,
                                        const int  argc,
                                        char       **argv) // message with bad float count
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue,
                // Double
                DataKind::Double | DataKind::DoubleShortCount |
                  ((0 - DataKindDoubleShortCountMinValue) &
                  DataKind::DoubleShortCountMask),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedDoubleValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Bad count for Double @2");
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
} // doTestNonEmptyMessageWithZeroFloatCount
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 009 ***
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
doTestNonEmptyMessageWithStringWithInvalidLength(const char *launchPath,
                                                 const int  argc,
                                                 char       **argv) // message with string with
                                                                    // invalid length
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                  DataKind::StringOrBlobLongLengthValue |
                  ((1 - 1) & DataKind::StringOrBlobLongLengthMask),
                static_cast<DataKind>(42),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Null Value read @4");
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
} // doTestNonEmptyMessageWithStringWithInvalidLength
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 010 ***
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
doTestNonEmptyMessageWithBlobWithInvalidLength(const char *launchPath,
                                               const int  argc,
                                               char       **argv) // message with blob with
                                                                  // invalid length
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue,
                // String
                DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                  DataKind::StringOrBlobLongLengthValue |
                  ((1 - 1) & DataKind::StringOrBlobLongLengthMask),
                static_cast<DataKind>(42),
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedStringOrBlobValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Null Value read @4");
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
} // doTestNonEmptyMessageWithBlobWithInvalidLength
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 020 ***
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
doTestNonEmptyMessageWithArrayWithInitialEndTag(const char *launchPath,
                                                const int  argc,
                                                char       **argv) // message with array with
                                                                   // initial end tag
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1");
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
} // doTTestNonEmptyMessageWithArrayWithInitialEndTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 021 ***
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
doTestNonEmptyMessageWithArrayWithTerminalStartTag(const char *launchPath,
                                                   const int  argc,
                                                   char       **argv) // message with array with
                                                                      // terminal start tag
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Array with incorrect end tag @2");
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
} // doTestNonEmptyMessageWithArrayWithTerminalStartTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 022 ***
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
doTestNonEmptyMessageWithEmptyArrayWithContent(const char *launchPath,
                                               const int  argc,
                                               char       **argv) // message with empty array with
                                                                  // content
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Array with incorrect end tag @2");
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
} // doTestNonEmptyMessageWithEmptyArrayWithContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 023 ***
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
doTestNonEmptyMessageWithNonEmptyArrayWithoutContent(const char *launchPath,
                                                     const int  argc,
                                                     char       **argv) // message with nonempty
                                                                        // array without content
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @3");
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
} // doTestNonEmptyMessageWithNonEmptyArrayWithoutContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 024 ***
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
doTestNonEmptyMessageWithNonEmptyArrayWithInvalidCount(const char *launchPath,
                                                       const int  argc,
                                                       char       **argv) // message with nonempty
                                                                          // array with invalid
                                                                          // count
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((1 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0 + DataKindIntegerShortValueMinValue - 1),
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Array with zero or negative count @4");
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
} // doTestNonEmptyMessageWithNonEmptyArrayWithInvalidCount
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 025 ***
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
doTestNonEmptyMessageWithNonEmptyArrayWithTooFewValues(const char *launchPath,
                                                       const int  argc,
                                                       char       **argv) // message with array with
                                                                          // too few values
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((3 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @5");
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
} // doTestNonEmptyMessageWithNonEmptyArrayWithTooFewValues
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 026 ***
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
doTestNonEmptyMessageWithNonEmptyArrayWithTooManyValues(const char *launchPath,
                                                        const int  argc,
                                                        char       **argv) // message with array
                                                                           // with too many values
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Non-empty Array with incorrect end tag @5");
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
} // doTestNonEmptyMessageWithNonEmptyArrayWithTooManyValues
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 027 ***
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
doTestNonEmptyMessageWithNonEmptyArrayWithTooManyFloats(const char *launchPath,
                                                        const int  argc,
                                                        char       **argv) // message with array
                                                                           // with too many floats
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Array
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Double
                DataKind::Double | DataKind::DoubleLongCount |
                  ((1 - 1) & DataKind::DoubleLongCountMask),
                static_cast<DataKind>(3),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 0
                static_cast<DataKind>(0x3F), static_cast<DataKind>(0xF0),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 1
                static_cast<DataKind>(0x40), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00),
                static_cast<DataKind>(0x00), static_cast<DataKind>(0x00), // 2
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Array
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeArray |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Non-empty Array with incorrect end tag @29");
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
} // doTestNonEmptyMessageWithNonEmptyArrayWithTooManyFloats
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 040 ***
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
doTestNonEmptyMessageWithMapWithInitialEndTag(const char *launchPath,
                                              const int  argc,
                                              char       **argv) // message with map with
                                                                 // initial end tag
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1");
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
} // doTestNonEmptyMessageWithMapWithInitialEndTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 041 ***
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
doTestNonEmptyMessageWithMapWithTerminalStartTag(const char *launchPath,
                                                 const int  argc,
                                                 char       **argv) // message with map with
                                                                    // terminal start tag
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Map with incorrect end tag @2");
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
} // doTestNonEmptyMessageWithMapWithTerminalStartTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 042 ***
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
doTestNonEmptyMessageWithEmptyMapWithContent(const char *launchPath,
                                             const int  argc,
                                             char       **argv) // message with empty map with
                                                                // content
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Map with incorrect end tag @2");
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
} // doTestNonEmptyMessageWithEmptyMapWithContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 043 ***
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
doTestNonEmptyMessageWithNonEmptyMapWithoutContent(const char *launchPath,
                                                   const int  argc,
                                                   char       **argv) // message with nonempty
                                                                      // map without content
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @3");
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
} // doTestNonEmptyMessageWithNonEmptyMapWithoutContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 044 ***
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
doTestNonEmptyMessageWithNonEmptyMapWithInvalidCount(const char *launchPath,
                                                     const int  argc,
                                                     char       **argv) // message with nonempty
                                                                        // map with invalid count
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((1 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0 + DataKindIntegerShortValueMinValue - 1),
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Map with zero or negative count @4");
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
} // doTestNonEmptyMessageWithNonEmptyMapWithInvalidCount
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 045 ***
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
doTestNonEmptyMessageWithNonEmptyMapWithTooFewValues(const char *launchPath,
                                                     const int  argc,
                                                     char       **argv) // message with map with
                                                                        // too few values
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((3 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalTrueValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalTrueValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @7");
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
} // doTestNonEmptyMessageWithNonEmptyMapWithTooFewValues
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 046 ***
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
doTestNonEmptyMessageWithNonEmptyMapWithTooManyValues(const char *launchPath,
                                                      const int  argc,
                                                      char       **argv) // message with map with
                                                                         // too many values
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((1 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalTrueValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalTrueValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Non-empty Map with incorrect end tag @5");
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
} // doTestNonEmptyMessageWithNonEmptyMapWithTooManyValues
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 047 ***
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
doTestNonEmptyMessageWithNonEmptyMapWithIncompletePair(const char *launchPath,
                                                       const int  argc,
                                                       char       **argv) // message with map with
                                                                          // incomplete pair
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Map
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalTrueValue,
                // End of Map
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeMap |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @6");
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
} // doTestNonEmptyMessageWithNonEmptyMapWithIncompletePair
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 060 ***
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
doTestNonEmptyMessageWithSetWithInitialEndTag(const char *launchPath,
                                              const int  argc,
                                              char       **argv) // message with set with
                                                                 // initial end tag
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @1");
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
} // doTTestNonEmptyMessageWithSetWithInitialEndTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 061 ***
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
doTestNonEmptyMessageWithSetWithTerminalStartTag(const char *launchPath,
                                                 const int  argc,
                                                 char       **argv) // message with set with
                                                                    // terminal start tag
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Set with incorrect end tag @2");
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
} // doTestNonEmptyMessageWithSetWithTerminalStartTag
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 062 ***
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
doTestNonEmptyMessageWithEmptySetWithContent(const char *launchPath,
                                             const int  argc,
                                             char       **argv) // message with empty set with
                                                                // content
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Empty Set with incorrect end tag @2");
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
} // doTestNonEmptyMessageWithEmptySetWithContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 063 ***
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
doTestNonEmptyMessageWithNonEmptySetWithoutContent(const char *launchPath,
                                                   const int  argc,
                                                   char       **argv) // message with nonempty
                                                                      // set without content
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @3");
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
} // doTestNonEmptyMessageWithNonEmptySetWithoutContent
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 064 ***
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
doTestNonEmptyMessageWithNonEmptySetWithInvalidCount(const char *launchPath,
                                                     const int  argc,
                                                     char       **argv) // message with nonempty
                                                                        // set with invalid count
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer | DataKind::IntegerLongValue |
                  ((1 - 1) & DataKind::IntegerLongValueCountMask),
                static_cast<DataKind>(0 + DataKindIntegerShortValueMinValue - 1),
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Set with zero or negative count @4");
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
} // doTestNonEmptyMessageWithNonEmptySetWithInvalidCount
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 065 ***
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
doTestNonEmptyMessageWithNonEmptySetWithTooFewValues(const char *launchPath,
                                                     const int  argc,
                                                     char       **argv) // message with set with
                                                                        // too few values
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((3 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @5");
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
} // doTestNonEmptyMessageWithNonEmptySetWithTooFewValues
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark *** Test Case 066 ***
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
doTestNonEmptyMessageWithNonEmptySetWithTooManyValues(const char *launchPath,
                                                      const int  argc,
                                                      char       **argv) // message with set with
                                                                         // too many values
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
        auto stuff(make_unique<Message>());
        
        if (stuff)
        {
            static const DataKind bytesToInsert[] =
            {
                // Start of Message
                DataKind::StartOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue,
                // Start of Set
                DataKind::Other | DataKind::OtherContainerStart |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // Signed Integer
                DataKind::Integer |
                  DataKind::IntegerShortValue |
                  ((2 + DataKindIntegerShortValueMinValue - 1) &
                  DataKind::IntegerShortValueValueMask),
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // Logical
                DataKind::Other | DataKind::OtherLogical |
                  DataKind::OtherLogicalFalseValue,
                // End of Set
                DataKind::Other | DataKind::OtherContainerEnd |
                  DataKind::OtherContainerTypeSet |
                  DataKind::OtherContainerNonEmptyValue,
                // End of Message
                DataKind::EndOfMessageValue |
                  DataKind::OtherMessageNonEmptyValue |
                  DataKind::OtherMessageExpectedOtherValue
            };
            const size_t insertionCount = (sizeof(bytesToInsert) / sizeof(*bytesToInsert));
            
            result = attemptExtractValueAndCheck(*stuff, bytesToInsert, insertionCount,
                                                 "Unexpected character in Message @6");
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
} // doTestNonEmptyMessageWithNonEmptySetWithTooManyValues
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
                    case 1 :
                        result = doTestMessageInitialEndTag(*argv, argc - 1, argv + 2);
                        break;

                    case 2 :
                        result = doTestMessageTerminalStartTag(*argv, argc - 1, argv + 2);
                        break;

                    case 3 :
                        result = doTestEmptyMessageWithContent(*argv, argc - 1, argv + 2);
                        break;

                    case 4 :
                        result = doTestNonEmptyMessageWithoutContent(*argv, argc - 1, argv + 2);
                        break;

                    case 5 :
                        result = doTestNonEmptyMessageWithMismatchedInitialStartTag(*argv,
                                                                                    argc - 1,
                                                                                    argv + 2);
                        break;

                    case 6 :
                        result = doTestNonEmptyMessageWithMismatchedTerminalEndTag(*argv, argc - 1,
                                                                                   argv + 2);
                        break;

                    case 7 :
                        result = doTestNonEmptyMessageWithInvalidContentTag(*argv, argc - 1,
                                                                            argv + 2);
                        break;

                    case 8 :
                        result = doTestNonEmptyMessageWithZeroFloatCount(*argv, argc - 1, argv + 2);
                        break;

                    case 9 :
                        result = doTestNonEmptyMessageWithStringWithInvalidLength(*argv, argc - 1,
                                                                                  argv + 2);
                        break;

                    case 10 :
                        result = doTestNonEmptyMessageWithBlobWithInvalidLength(*argv, argc - 1,
                                                                                argv + 2);
                        break;

                    case 20 :
                        result = doTestNonEmptyMessageWithArrayWithInitialEndTag(*argv, argc - 1,
                                                                                 argv + 2);
                        break;

                    case 21 :
                        result = doTestNonEmptyMessageWithArrayWithTerminalStartTag(*argv, argc - 1,
                                                                                    argv + 2);
                        break;

                    case 22 :
                        result = doTestNonEmptyMessageWithEmptyArrayWithContent(*argv, argc - 1,
                                                                                argv + 2);
                        break;

                    case 23 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithoutContent(*argv,
                                                                                      argc - 1,
                                                                                      argv + 2);
                        break;

                    case 24 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithInvalidCount(*argv,
                                                                                        argc - 1,
                                                                                        argv + 2);
                        break;

                    case 25 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithTooFewValues(*argv,
                                                                                        argc - 1,
                                                                                        argv + 2);
                        break;

                    case 26 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithTooManyValues(*argv,
                                                                                         argc - 1,
                                                                                         argv + 2);
                        break;

                    case 27 :
                        result = doTestNonEmptyMessageWithNonEmptyArrayWithTooManyFloats(*argv,
                                                                                         argc - 1,
                                                                                         argv + 2);
                        break;

                    case 40 :
                        result = doTestNonEmptyMessageWithMapWithInitialEndTag(*argv, argc - 1,
                                                                               argv + 2);
                        break;

                    case 41 :
                        result = doTestNonEmptyMessageWithMapWithTerminalStartTag(*argv, argc - 1,
                                                                                  argv + 2);
                        break;

                    case 42 :
                        result = doTestNonEmptyMessageWithEmptyMapWithContent(*argv, argc - 1,
                                                                              argv + 2);
                        break;

                    case 43 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithoutContent(*argv, argc - 1,
                                                                                    argv + 2);
                        break;

                    case 44 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithInvalidCount(*argv,
                                                                                      argc - 1,
                                                                                      argv + 2);
                        break;

                    case 45 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithTooFewValues(*argv,
                                                                                      argc - 1,
                                                                                      argv + 2);
                        break;

                    case 46 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithTooManyValues(*argv,
                                                                                       argc - 1,
                                                                                       argv + 2);
                        break;

                    case 47 :
                        result = doTestNonEmptyMessageWithNonEmptyMapWithIncompletePair(*argv,
                                                                                        argc - 1,
                                                                                        argv + 2);
                        break;

                    case 60 :
                        result = doTestNonEmptyMessageWithSetWithInitialEndTag(*argv, argc - 1,
                                                                               argv + 2);
                        break;
                        
                    case 61 :
                        result = doTestNonEmptyMessageWithSetWithTerminalStartTag(*argv, argc - 1,
                                                                                  argv + 2);
                        break;
                        
                    case 62 :
                        result = doTestNonEmptyMessageWithEmptySetWithContent(*argv, argc - 1,
                                                                              argv + 2);
                        break;
                        
                    case 63 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithoutContent(*argv,
                                                                                    argc - 1,
                                                                                    argv + 2);
                        break;
                        
                    case 64 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithInvalidCount(*argv,
                                                                                      argc - 1,
                                                                                      argv + 2);
                        break;
                        
                    case 65 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithTooFewValues(*argv,
                                                                                      argc - 1,
                                                                                      argv + 2);
                        break;
                        
                    case 66 :
                        result = doTestNonEmptyMessageWithNonEmptySetWithTooManyValues(*argv,
                                                                                       argc - 1,
                                                                                       argv + 2);
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

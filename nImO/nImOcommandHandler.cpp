//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO command handlers.
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
//  Created:    2023-03-25
//
//--------------------------------------------------------------------------------------------------

#include <nImOcommandHandler.h>

#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmessage.h>
#include <nImOcommonCommands.h>
#include <nImOmainSupport.h>
#include <nImOMIMESupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif // defined(__APPLE__)
#include <boost/algorithm/string/join.hpp>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO command handlers. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::CommandHandler::CommandHandler
    (SpServiceContext   owner) :
        _owner{owner}
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::CommandHandler::CommandHandler

nImO::CommandHandler::~CommandHandler
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::CommandHandler::~CommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::CommandHandler::sendComplexResponse
    (BTCP::socket &         socket,
     const std::string &    responseKey,
     const std::string &    responseText,
     SpValue                contents)
    const
{
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "contents = ", contents.get()); //####
    ODL_S2s("responseKey = ", responseKey, "responseText = ", responseText); //####
    bool    okSoFar{sendComplexResponseWithContext(_owner, socket, responseKey, responseText, contents)};

    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendComplexResponse

bool
nImO::CommandHandler::sendComplexResponseWithContext
    (SpServiceContext       context,
     BTCP::socket &         socket,
     const std::string &    responseKey,
     const std::string &    responseText,
     SpValue                contents)
{
    ODL_ENTER(); //####
    ODL_P3("context = ", context.get(), "socket = ", &socket, "contents = ", contents.get()); //####
    ODL_S2s("responseKey = ", responseKey, "responseText = ", responseText); //####
    bool    okSoFar{false};
    Message responseToSend;
    auto    responseArray{std::make_shared<Array>()};

    responseToSend.open(true);
    responseArray->addValue(std::make_shared<String>(responseKey));
    responseArray->addValue(contents);
    responseToSend.setValue(responseArray);
    responseToSend.close();
    if (0 < responseToSend.getLength())
    {
        auto    asString{responseToSend.getBytes()};

        if (asString.empty())
        {
            ODL_LOG("(asString.empty())"); //####
        }
        else
        {
            std::atomic_bool    keepGoing{true};
            StringVector        outVec;

            EncodeBytesAsMIME(outVec, asString);
            auto    outString{nImO::PackageMessage(outVec)};

            ODL_S1("outString <- ", outString->c_str()); //####
            // send the encoded message to the requestor.
#if defined(nImO_ChattyTcpLogging)
            context->report("sending response"s);
#endif /* defined(nImO_ChattyTcpLogging) */
            boost::asio::async_write(socket, boost::asio::buffer(outString->c_str(), outString->length()),
                                      [context, &keepGoing, &okSoFar, responseText]
                                      (const BSErr &        ec,
                                       const std::size_t    bytes_transferred)
                                      {
                                        NIMO_UNUSED_VAR_(bytes_transferred);
                                        if (ec)
                                        {
                                            if (BAErr::operation_aborted == ec)
                                            {
#if defined(nImO_ChattyTcpLogging)
                                                context->report("async_write() operation cancelled"s);
#endif /* defined(nImO_ChattyTcpLogging) */
                                                ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                            }
                                            else
                                            {
                                                context->report("async_write() failed -> "s + ec.message());
                                            }
                                            keepGoing = false;
                                            ODL_B1("keepGoing <- ", keepGoing); //####
                                        }
                                        else
                                        {
                                            context->report(responseText + " response sent"s);
                                            okSoFar = true;
                                            keepGoing = false;
                                        }
                                      });
            for ( ; keepGoing && gKeepRunning; )
            {
                boost::this_thread::yield();
            }
        }
    }
    else
    {
        ODL_LOG("! (0 < responseToSend.getLength())"); //####
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendComplexResponseWithContext

bool
nImO::CommandHandler::sendSimpleResponse
    (BTCP::socket &         socket,
     const std::string &    responseKey,
     const std::string &    responseText,
     const bool             wasOK)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("socket = ", &socket); //####
    ODL_S2s("responseKey = ", responseKey, "responseText = ", responseText); //####
    ODL_B1("wasOK = ", wasOK); //####
    bool    okSoFar{sendSimpleResponseWithContext(_owner, socket, responseKey, responseText, wasOK)};

    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendSimpleResponse

bool
nImO::CommandHandler::sendSimpleResponseWithContext
    (SpServiceContext       context,
     BTCP::socket &         socket,
     const std::string &    responseKey,
     const std::string &    responseText,
     const bool             wasOK)
{
    ODL_ENTER(); //####
    ODL_P2("context = ", context.get(), "socket = ", &socket); //####
    ODL_S2s("responseKey = ", responseKey, "responseText = ", responseText); //####
    ODL_B1("wasOK = ", wasOK); //####
    bool    okSoFar{false};
    Message responseToSend;
    auto    responseArray{std::make_shared<Array>()};

    responseToSend.open(true);
    responseArray->addValue(std::make_shared<String>(responseKey));
    responseArray->addValue(std::make_shared<Logical>(wasOK));
    responseToSend.setValue(responseArray);
    responseToSend.close();
    if (0 < responseToSend.getLength())
    {
        auto    asString{responseToSend.getBytes()};

        if (asString.empty())
        {
            ODL_LOG("(asString.empty())"); //####
        }
        else
        {
            std::atomic_bool    keepGoing{true};
            StringVector        outVec;

            EncodeBytesAsMIME(outVec, asString);
            auto    outString{nImO::PackageMessage(outVec)};

            ODL_S1("outString <- ", outString->c_str()); //####
            // send the encoded message to the requestor.
#if defined(nImO_ChattyTcpLogging)
            context->report("sending response"s);
#endif /* defined(nImO_ChattyTcpLogging) */
            boost::asio::async_write(socket, boost::asio::buffer(outString->c_str(), outString->length()),
                                      [context, &keepGoing, &okSoFar, responseText]
                                      (const BSErr &        ec,
                                       const std::size_t    bytes_transferred)
                                      {
                                        NIMO_UNUSED_VAR_(bytes_transferred);
                                        if (ec)
                                        {
                                            if (BAErr::operation_aborted == ec)
                                            {
#if defined(nImO_ChattyTcpLogging)
                                                context->report("async_write() operation cancelled"s);
#endif /* defined(nImO_ChattyTcpLogging) */
                                                ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                            }
                                            else
                                            {
                                                context->report("async_write() failed -> "s + ec.message());
                                            }
                                            keepGoing = false;
                                            ODL_B1("keepGoing <- ", keepGoing); //####
                                        }
                                        else
                                        {
                                            context->report(responseText + " response sent"s);
                                            okSoFar = true;
                                            keepGoing = false;
                                            ODL_B1("keepGoing <- ", keepGoing); //####
                                        }
                                      });
            for ( ; keepGoing && gKeepRunning; )
            {
                boost::this_thread::yield();
            }
        }
    }
    else
    {
        ODL_LOG("! (0 < responseToSend.getLength())"); //####
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendSimpleResponseWithContext

void
nImO::CommandHandler::sendStatusReport
    (SpServiceContext       context,
     Connection             whereToSend,
     const std::string &    statusChange)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("context = ", context.get()); //####
    ODL_S1s("statusChange = ", statusChange); //####
    BUDP::endpoint  theEndpoint{BAIP::address_v4(whereToSend._address), whereToSend._port};
    BUDP::socket    theSocket{*context->getService(), theEndpoint.protocol()};
    Message         messageToSend;
    auto            statusCopy{std::make_shared<String>(statusChange)};

    messageToSend.open(true);
    messageToSend.setValue(statusCopy);
    messageToSend.close();
    if (0 < messageToSend.getLength())
    {
        auto    asString{messageToSend.getBytes()};

        if (asString.empty())
        {
            ODL_LOG("(asString.empty())"); //####
        }
        else
        {
            StringVector    outVec;

            EncodeBytesAsMIME(outVec, asString);
            auto    outString(std::make_shared<std::string>(boost::algorithm::join(outVec, "\n"s)));

            // send the encoded message to the logging ports
            theSocket.async_send_to(boost::asio::buffer(*outString), theEndpoint,
                                      [outString]
                                      (const BSErr          ec,
                                       const std::size_t    length)
                                      {
                                        NIMO_UNUSED_VAR_(ec);
                                        NIMO_UNUSED_VAR_(length);
                                      });
        }
    }
    else
    {
        ODL_LOG("! (0 < messageToSend.getLength())"); //####
    }
} // nImO::CommandHandler::sendStatusReport

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::CommandHandler::SendBadResponse
    (SpServiceContext   context,
     SpSocketTCP        socket)
{
    ODL_ENTER(); //####
    ODL_P2("context = ", context.get(), "socket = ", socket.get()); //####
    sendSimpleResponseWithContext(context, *socket.get(), nImO::kBadResponse, "unknown"s, false);
    ODL_EXIT(); //####
} // nImO::CommandHandler::SendBadResponse

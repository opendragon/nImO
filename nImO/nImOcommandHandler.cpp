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

#include <nImOarray.h>
#include <nImOcommonCommands.h>
#include <nImOlogical.h>
#include <nImOmainSupport.h>
#include <nImOmessage.h>
#include <nImOMIMESupport.h>
#include <nImOstring.h>

//#include <odlEnable.h>
#include <odlInclude.h>

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
    (SpContextWithNetworking    owner) :
        _owner(owner)
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
    (asio::ip::tcp::socket &    socket,
     const std::string          responseKey,
     SpValue                    contents)
    const
{
    bool    okSoFar = sendComplexResponseWithContext(_owner, socket, responseKey, contents);

    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "contents = ", contents.get()); //####
    ODL_S1s("responseKey = ", responseKey); //####
    ODL_B1("wasOK = ", wasOK); //####
    ODL_B1("okSoFar <- ", okSoFar); //!!!
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendComplexResponse

bool
nImO::CommandHandler::sendComplexResponseWithContext
    (SpContextWithNetworking    context,
     asio::ip::tcp::socket &    socket,
     const std::string          responseKey,
     SpValue                    contents)
{
    bool    okSoFar = false;
    Message responseToSend;
    SpArray responseArray{new Array};

    ODL_OBJENTER(); //####
    ODL_P3("context = ", context.get(), "socket = ", &socket, "contents = ", contents.get()); //####
    ODL_S1s("responseKey = ", responseKey); //####
    ODL_B1("wasOK = ", wasOK); //####
    ODL_B1("okSoFar <- ", okSoFar); //!!!
    responseToSend.open(true);
    responseArray->addValue(std::make_shared<String>(responseKey));
    responseArray->addValue(contents);
    responseToSend.setValue(responseArray);
    responseToSend.close();
    if (0 < responseToSend.getLength())
    {
        auto    asString{responseToSend.getBytes()};

        if (0 < asString.length())
        {
            std::atomic<bool>   keepGoing{true};
            StringVector        outVec;

            EncodeBytesAsMIME(outVec, asString);
            auto    outString{nImO::PackageMessage(outVec)};

            ODL_S1("outString <- ", outString->c_str());//!!!
            // send the encoded message to the requestor.
#if defined(nImO_ChattyTcpLogging)
            context->report("sending response");
#endif /* defined(nImO_ChattyTcpLogging) */
            asio::async_write(socket, asio::buffer(outString->c_str(), outString->length()),
                              [context, &keepGoing, &okSoFar]
                              (const system::error_code &   ec,
                               const std::size_t            NIMO_UNUSED_PARAM_(bytes_transferred))
                              {
                                if (ec)
                                {
                                    if (asio::error::operation_aborted == ec)
                                    {
#if defined(nImO_ChattyTcpLogging)
                                        context->report("write operation cancelled");
#endif /* defined(nImO_ChattyTcpLogging) */
                                        ODL_LOG("(asio::error::operation_aborted == ec)"); //####
                                    }
                                    else
                                    {
                                        context->report("async_write failed");
                                    }
                                    keepGoing = false;
                                    ODL_B1("keepGoing <- ", keepGoing); //!!
                                }
                                else
                                {
#if defined(nImO_ChattyTcpLogging)
                                    context->report("response sent");
#endif /* defined(nImO_ChattyTcpLogging) */
                                    okSoFar = true;
                                    keepGoing = false;
                                    ODL_B2("okSoFar <- ", okSoFar, "keepGoing <- ", keepGoing); //!!
                                }
                              });
            for ( ; keepGoing && gKeepRunning; )
            {
                this_thread::yield();
            }
        }
        else
        {
            ODL_LOG("! (0 < asString.length())"); //####
        }
    }
    else
    {
        ODL_LOG("! (0 < responseToSend.getLength())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendComplexResponseWithContext

bool
nImO::CommandHandler::sendSimpleResponse
    (asio::ip::tcp::socket &    socket,
     const std::string          responseKey,
     const bool                 wasOK)
    const
{
    bool    okSoFar = sendSimpleResponseWithContext(_owner, socket, responseKey, wasOK);

    ODL_OBJENTER(); //####
    ODL_P1("socket = ", &socket); //####
    ODL_S1s("responseKey = ", responseKey); //####
    ODL_B1("wasOK = ", wasOK); //####
    ODL_B1("okSoFar <- ", okSoFar); //!!!
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendSimpleResponse

bool
nImO::CommandHandler::sendSimpleResponseWithContext
    (SpContextWithNetworking    context,
     asio::ip::tcp::socket &    socket,
     const std::string          responseKey,
     const bool                 wasOK)
{
    bool    okSoFar = false;
    Message responseToSend;
    SpArray responseArray{new Array};

    ODL_OBJENTER(); //####
    ODL_P2("context = ", context.get(), "socket = ", &socket); //####
    ODL_S1s("responseKey = ", responseKey); //####
    ODL_B1("wasOK = ", wasOK); //####
    ODL_B1("okSoFar <- ", okSoFar); //!!!
    responseToSend.open(true);
    responseArray->addValue(std::make_shared<String>(responseKey));
    responseArray->addValue(std::make_shared<Logical>(wasOK));
    responseToSend.setValue(responseArray);
    responseToSend.close();
    if (0 < responseToSend.getLength())
    {
        auto    asString{responseToSend.getBytes()};

        if (0 < asString.length())
        {
            std::atomic<bool>   keepGoing{true};
            StringVector        outVec;

            EncodeBytesAsMIME(outVec, asString);
            auto    outString{nImO::PackageMessage(outVec)};

            ODL_S1("outString <- ", outString->c_str());//!!!
            // send the encoded message to the requestor.
#if defined(nImO_ChattyTcpLogging)
            context->report("sending response");
#endif /* defined(nImO_ChattyTcpLogging) */
            asio::async_write(socket, asio::buffer(outString->c_str(), outString->length()),
                              [context, &keepGoing, &okSoFar]
                              (const system::error_code &   ec,
                               const std::size_t            NIMO_UNUSED_PARAM_(bytes_transferred))
                              {
                                if (ec)
                                {
                                    if (asio::error::operation_aborted == ec)
                                    {
#if defined(nImO_ChattyTcpLogging)
                                        context->report("write operation cancelled");
#endif /* defined(nImO_ChattyTcpLogging) */
                                        ODL_LOG("(asio::error::operation_aborted == ec)"); //####
                                    }
                                    else
                                    {
                                        context->report("async_write failed");
                                    }
                                    keepGoing = false;
                                    ODL_B1("keepGoing <- ", keepGoing); //!!
                                }
                                else
                                {
#if defined(nImO_ChattyTcpLogging)
                                    context->report("response sent");
#endif /* defined(nImO_ChattyTcpLogging) */
                                    okSoFar = true;
                                    keepGoing = false;
                                    ODL_B2("okSoFar <- ", okSoFar, "keepGoing <- ", keepGoing); //!!
                                }
                              });
            for ( ; keepGoing && gKeepRunning; )
            {
                this_thread::yield();
            }
        }
        else
        {
            ODL_LOG("! (0 < asString.length())"); //####
        }
    }
    else
    {
        ODL_LOG("! (0 < responseToSend.getLength())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::CommandHandler::sendSimpleResponseWithContext

void
nImO::CommandHandler::sendStatusReport
    (SpContextWithNetworking    context,
     Connection                 whereToSend,
     const std::string &        statusChange)
    const
{
    auto                    statusCopy{std::make_shared<std::string>(statusChange)};
    asio::ip::udp::endpoint theEndpoint{asio::ip::address_v4(whereToSend._address), whereToSend._port};
    asio::ip::udp::socket   theSocket{*context->getService(), theEndpoint.protocol()};

    ODL_OBJENTER(); //####
    theSocket.async_send_to(asio::buffer(*statusCopy), theEndpoint,
                              [statusCopy]
                              (const system::error_code NIMO_UNUSED_PARAM_(ec),
                               const std::size_t        NIMO_UNUSED_PARAM_(length))
                              {
                              });
    ODL_OBJEXIT(); //####
} // nImO::CommandHandler::sendStatusReport

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::CommandHandler::SendBadResponse
    (SpContextWithNetworking    context,
     SPsocketTCP                socket)
{
    ODL_ENTER(); //####
    ODL_P2("context = ", context.get(), "socket = ", socket.get()); //####
    sendSimpleResponseWithContext(context, *socket.get(), nImO::kBadResponse, false);
    ODL_EXIT(); //####
} // nImO::CommandHandler::SendBadResponse

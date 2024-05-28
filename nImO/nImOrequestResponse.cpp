//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOrequestResponse.cpp
//
//  Project:    nImO
//
//  Contains:   The function definitions for the nImO request/response mechanism.
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

#include <nImOrequestResponse.h>

#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmessage.h>
#include <Contexts/nImOcontextWithMDNS.h>
#include <Contexts/nImOutilityContext.h>
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
 @brief The function definitions for the %nImO request/response mechanism. */
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

/*! @brief Extract the response data and pass it on to a request-specific handler.
 @param[in] handler The request-specific handler, @c nullptr if not needed.
 @param[in] incoming The response to be processed.
 @param[in] expectedKey The expected reponse key.
 @param[out] failureReason A description of the reason for a failure.
 @return @c true if there were no issues with the response. */
static bool
handleResponse
    (Ptr(nImO::ResponseHandler) handler,
     const std::string &        incoming,
     const std::string &        expectedKey,
     std::string &              failureReason)
{
    ODL_ENTER(); //####
    ODL_P2("handler = ", handler, "failureReason = ", &failureReason); //####
    ODL_S2s("incoming = ", incoming, "expectedKey = ", expectedKey); //####
    bool    wasOK{false};

    if (nullptr == handler)
    {
        ODL_LOG("(nullptr == handler)"); //####
        failureReason = "No handler provided"s;
    }
    else
    {
        // We need to strip off the Message separator first.
        auto                trimmed{nImO::UnpackageMessage(incoming)};
        nImO::ByteVector    rawStuff{};

        ODL_S1s("trimmed <- ", trimmed); //####
        // Ignore a request that can't be processed...
        if (nImO::DecodeMIMEToBytes(trimmed, rawStuff))
        {
            auto    stuff{std::make_unique<nImO::Message>()};

            if (stuff && (0 < rawStuff.size()))
            {
                stuff->open(false);
                stuff->appendBytes(rawStuff.data(), rawStuff.size());
                auto    contents{stuff->getValue()};

                stuff->close();
                if (stuff->readAtEnd() && contents)
                {
                    auto    asArray{contents->asArray()};

                    if ((nullptr != asArray) && (0 < asArray->size()))
                    {
                        auto    response{(*asArray)[0]->asString()};

                        if (nullptr == response)
                        {
                            ODL_LOG("(nullptr == response)"); //####
                            failureReason = "Message did not contain a string"s;
                        }
                        else
                        {
                            ODL_S1s("response->getValue() = ", response->getValue()); //####
                            if (expectedKey == response->getValue())
                            {
                                wasOK = handler->doIt(*asArray);
                                if (! wasOK)
                                {
                                    ODL_LOG("(! wasOK)"); //####
                                    failureReason = "Response handler rejected message"s;
                                }
                            }
                            else
                            {
                                ODL_LOG("! (expectedKey == response->getValue())"); //####
                                failureReason = "Unexpected response [" + response->getValue() + "]"s;
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! ((nullptr != asArray) && (0 < asArray->size()))"); //####
                        failureReason = "Invalid message format"s;
                    }
                }
                else
                {
                    ODL_LOG("! (stuff->readAtEnd() && contents)"); //####
                    failureReason = "Incomplete message"s;
                }
            }
            else
            {
                ODL_LOG("! (stuff && (0 < rawStuff.size()))"); //####
                failureReason = "Decoded message was empty"s;
            }
        }
        else
        {
            ODL_LOG("! (nImO::DecodeMIMEToBytes(trimmed, rawStuff))"); //####
            failureReason = "Could not decode message"s;
        }
    }
    ODL_EXIT_B(wasOK); //####
    return wasOK;
} // handleResponse

static void
handleWriteCompletion
    (nImO::SpContextWithNetworking  context,
     nImO::SpSocketTCP              socket,
     Ptr(nImO::ResponseHandler)     handler,
     nImO::SpBool                   keepGoing,
     const std::string &            responseKey,
     nImO::SpSuccessOrFailure       status)
{
    ODL_ENTER(); //####
    ODL_P4("context = ", context.get(), "socket = ", socket.get(), "handler = ", handler, "keepGoing = ", keepGoing.get()); //####
    ODL_P1("status = ", status.get()); //####
    ODL_S1s("responseKey = ", responseKey); //####
#if defined(nImO_ChattyTcpUdpLogging)
    context->report("command sent."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
    auto    rB{std::make_shared<boost::asio::streambuf>()};

    boost::asio::async_read_until(*socket, *rB, nImO::MatchMessageSeparator,
                                [context, rB, handler, keepGoing, &responseKey, status]
                                (const BSErr &      ec3,
                                 const std::size_t  size)
                                {
                                    NIMO_UNUSED_VAR_(size);
                                    if (ec3)
                                    {
                                        if (BAErr::operation_aborted == ec3)
                                        {
#if defined(nImO_ChattyTcpUdpLogging)
                                            context->report("async_read_until() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                            ODL_LOG("(BAErr::operation_aborted == ec3)"); //####
                                        }
                                        else
                                        {
                                            auto    errMessage{"async_read_until() failed -> "s + ec3.message() + "."s};

                                            context->report(errMessage);
                                            *status = std::make_pair(false, errMessage);
                                        }
                                    }
                                    else
                                    {
                                        std::string handleThis{buffers_begin(rB->data()), buffers_end(rB->data())};

#if defined(nImO_ChattyTcpUdpLogging)
                                        context->report("got response."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                        if (nullptr != handler)
                                        {
                                            std::string failureReason{};

                                            if (! handleResponse(handler, handleThis, responseKey, failureReason))
                                            {
                                                *status = std::make_pair(false, failureReason);
                                            }
                                        }
                                    }
                                    *keepGoing = false;
                                    ODL_B1("keepGoing <- ", *keepGoing); //####
                                });
    ODL_EXIT(); //####
} // handleWriteCompletion

static void
handleConnectCompletion
    (nImO::SpContextWithNetworking  context,
     nImO::SpSocketTCP              socket,
     nImO::SpStdString              outString,
     Ptr(nImO::ResponseHandler)     handler,
     nImO::SpBool                   keepGoing,
     const std::string &            responseKey,
     nImO::SpSuccessOrFailure       status)
{
    ODL_ENTER(); //####
    ODL_P4("context = ", context.get(), "socket = ", socket.get(), "outString = ", outString.get(), "handler = ", handler); //####
    ODL_P2("keepGoing = ", keepGoing.get(), "status = ", status.get()); //####
    ODL_S1s("responseKey = ", responseKey); //####
#if defined(nImO_ChattyTcpUdpLogging)
    context->report("command connection request accepted."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
    boost::asio::async_write(*socket, boost::asio::buffer(outString->c_str(), outString->length()),
                              [socket, context, handler, keepGoing, &responseKey, status]
                              (const BSErr &        ec2,
                               const std::size_t    bytes_transferred)
                              {
                                NIMO_UNUSED_VAR_(bytes_transferred);
                                if (ec2)
                                {
                                    if (BAErr::operation_aborted == ec2)
                                    {
#if defined(nImO_ChattyTcpUdpLogging)
                                        context->report("async_write() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                        ODL_LOG("(BAErr::operation_aborted == ec2)"); //####
                                    }
                                    else
                                    {
                                        auto    errMessage{"async_write() failed -> "s + ec2.message() + "."s};

                                        context->report(errMessage);
                                        *status = std::make_pair(false, errMessage);
                                    }
                                    *keepGoing = false;
                                    ODL_B1("keepGoing <- ", *keepGoing); //####
                                }
                                else
                                {
                                    handleWriteCompletion(context, socket, handler, keepGoing, responseKey, status);
                                }
                            });
    ODL_EXIT(); //####
} // handleConnectCompletion

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

nImO::SuccessOrFailure
nImO::SendRequestWithArgumentsAndNonEmptyResponse
    (SpContextWithNetworking    context,
     Connection &               connection,
     Ptr(ResponseHandler)       handler,
     Ptr(Array)                 arguments,
     const std::string &        requestKey,
     const std::string &        responseKey)
{
    ODL_ENTER(); //####
    ODL_P4("context = ", context.get(), "connection = ", &connection, "handler = ", handler, "arguments = ", arguments); //####
    ODL_S2s("requestKey = ", requestKey, "responseKey = ", responseKey); //####
    Message requestToSend;
    auto    requestArray{std::make_shared<Array>()};
    auto    status{std::make_shared<SuccessOrFailure>(true, ""s)};

    requestToSend.open(true);
    requestArray->addValue(std::make_shared<String>(requestKey));
    if (nullptr != arguments)
    {
        requestArray->addEntries(*arguments);
    }
    requestToSend.setValue(requestArray);
    requestToSend.close();
    if (0 < requestToSend.getLength())
    {
        auto    asString{requestToSend.getString()};

        if (asString.empty())
        {
            ODL_LOG("(asString.empty())"); //####
            *status = std::make_pair(false, "asString.empty()"s);
        }
        else
        {
            StdStringVector outVec{};
            auto            keepGoing{std::make_shared<bool>(true)};

            EncodeBytesAsMIME(outVec, asString);
            auto    outString{nImO::PackageMessage(outVec)};

            ODL_S1("outString <- ", outString->c_str()); //####
            // Make a connection to the service whose address is in the connection argument.
            auto            socket{std::make_shared<BTCP::socket>(*context->getService())};
            BTCP::endpoint  endpoint{BAIP::make_address_v4(connection._address), connection._port};

            socket->async_connect(endpoint,
                                 [context, handler, socket, &outString, keepGoing, &responseKey, status]
                                 (const BSErr & ec1)
                                 {
                                    if (ec1)
                                    {
                                        if (BAErr::operation_aborted == ec1)
                                        {
#if defined(nImO_ChattyTcpUdpLogging)
                                            context->report("async_connect() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                            ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                        }
                                        else
                                        {
                                            auto    errMessage{"async_connect() failed -> "s + ec1.message() + "."s};

                                            context->report(errMessage);
                                            *status = std::make_pair(false, errMessage);
                                        }
                                        *keepGoing = false;
                                        ODL_B1("keepGoing <- ", *keepGoing); //####
                                    }
                                    else
                                    {
                                        handleConnectCompletion(context, socket, outString, handler, keepGoing, responseKey, status);
                                    }
                                });
            for ( ; *keepGoing && gKeepRunning; )
            {
                boost::this_thread::yield();
            }
        }
    }
    else
    {
        ODL_LOG("! (0 < requestToSend.getLength())"); //####
        *status = std::make_pair(false, "0 >= requestToSend.getLength()"s);
    }
    ODL_EXIT(); //####
    return *status;
} // nImO::SendRequestWithArgumentsAndNonEmptyResponse

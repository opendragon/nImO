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
#include <ContainerTypes/nImOarray.h>
#include <ContainerTypes/nImOmessage.h>
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
 @param[in] expectedKey The expected reponse key. */
static void
handleResponse
    (Ptr(nImO::ResponseHandler) handler,
     const std::string &        incoming,
     const std::string &        expectedKey)
{
    ODL_ENTER(); //####
    ODL_P1("handler = ", handler); //####
    ODL_S2s("incoming = ", incoming, "expectedKey = ", expectedKey); //####
    if (nullptr != handler)
    {
        // We need to strip off the Message separator first.
        std::string         trimmed{nImO::UnpackageMessage(incoming)};
        nImO::ByteVector    rawStuff;

        ODL_S1s("trimmed <- ", trimmed); //####
        // Ignore a request that can't be processed...
        if (nImO::DecodeMIMEToBytes(trimmed, rawStuff))
        {
            auto    stuff{std::make_unique<nImO::Message>()};

            if ((nullptr != stuff) && (0 < rawStuff.size()))
            {
                stuff->open(false);
                stuff->appendBytes(rawStuff.data(), rawStuff.size());
                nImO::SpValue   contents{stuff->getValue()};

                stuff->close();
                if (stuff->readAtEnd() && (nullptr != contents))
                {
                    CPtr(nImO::Array)   asArray{contents->asArray()};

                    if ((nullptr != asArray) && (0 < asArray->size()))
                    {
                        CPtr(nImO::String)  response{(*asArray)[0]->asString()};

                        if ((nullptr != response) && (expectedKey == response->getValue()))
                        {
                            handler->doIt(*asArray);
                        }
                        else
                        {
                            ODL_LOG("! ((nullptr != response) && (expectedKey == response->getValue()))"); //####
                        }
                    }
                    else
                    {
                        ODL_LOG("! ((nullptr != asArray) && (0 < asArray->size()))"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (stuff->readAtEnd() && (nullptr != contents))"); //####
                }
            }
            else
            {
                ODL_LOG("! ((nullptr != stuff) && (0 < rawStuff.size()))"); //####
            }
        }
        else
        {
            ODL_LOG("! (nImO::DecodeMIMEToBytes(trimmed, rawStuff))"); //####
        }
    }
    else
    {
        ODL_LOG("! (nullptr != handler)"); //####
    }
    ODL_EXIT(); //####
} // handleResponse

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
    Message             requestToSend;
    auto                requestArray{std::make_shared<Array>()};
    SuccessOrFailure    status{true, ""};

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
        auto    asString{requestToSend.getBytes()};

        if (asString.empty())
        {
            ODL_LOG("(asString.empty())"); //####
            status = std::make_pair(false, "asString.empty()");
        }
        else
        {
            StringVector        outVec;
            std::atomic<bool>   keepGoing{true};

            EncodeBytesAsMIME(outVec, asString);
            auto    outString{nImO::PackageMessage(outVec)};

            ODL_S1("outString <- ", outString->c_str()); //####
            // Make a connection to the service whose address is in the connection argument.
            BTCP::socket   socket{*context->getService()};
            BTCP::endpoint endpoint{BAIP::make_address_v4(connection._address), connection._port};

            socket.async_connect(endpoint,
                                 [context, handler, &socket, &outString, &keepGoing, &responseKey, &status]
                                 (const BSErr & ec1)
                                 {
                                    if (ec1)
                                    {
                                        if (BAErr::operation_aborted == ec1)
                                        {
#if defined(nImO_ChattyTcpLogging)
                                            context->report("async_connect() operation cancelled");
#endif /* defined(nImO_ChattyTcpLogging) */
                                            ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                        }
                                        else
                                        {
                                            context->report("async_connect() failed");
                                            status = std::make_pair(false, "async_connect() failed");
                                        }
                                        keepGoing = false;
                                        ODL_B1("keepGoing <- ", keepGoing); //####
                                    }
                                    else
                                    {
#if defined(nImO_ChattyTcpLogging)
                                        context->report("connection request accepted");
#endif /* defined(nImO_ChattyTcpLogging) */
                                        boost::asio::async_write(socket, boost::asio::buffer(outString->c_str(), outString->length()),
                                                                  [&socket, context, handler, &keepGoing, &responseKey, &status]
                                                                  (const BSErr &        ec2,
                                                                   const std::size_t    bytes_transferred)
                                                                  {
                                                                    NIMO_UNUSED_VAR_(bytes_transferred);
                                                                    if (ec2)
                                                                    {
                                                                        if (BAErr::operation_aborted == ec2)
                                                                        {
#if defined(nImO_ChattyTcpLogging)
                                                                            context->report("async_write() operation cancelled");
#endif /* defined(nImO_ChattyTcpLogging) */
                                                                            ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                                                        }
                                                                        else
                                                                        {
                                                                            context->report("async_write() failed");
                                                                            status = std::make_pair(false, "async_write() failed");
                                                                        }
                                                                        keepGoing = false;
                                                                        ODL_B1("keepGoing <- ", keepGoing); //####
                                                                    }
                                                                    else
                                                                    {
#if defined(nImO_ChattyTcpLogging)
                                                                        context->report("command sent");
#endif /* defined(nImO_ChattyTcpLogging) */
                                                                        auto    rB{std::make_shared<boost::asio::streambuf>()};

                                                                        boost::asio::async_read_until(socket, *rB, MatchMessageSeparator,
                                                                                                [context, rB, handler, &keepGoing, &responseKey,
                                                                                                 &status]
                                                                                                (const BSErr &      ec,
                                                                                                 const std::size_t  size)
                                                                                                {
                                                                                                    NIMO_UNUSED_VAR_(size);
                                                                                                    if (ec)
                                                                                                    {
                                                                                                        if (BAErr::operation_aborted == ec)
                                                                                                        {
#if defined(nImO_ChattyTcpLogging)
                                                                                                            context->report("read_until() operation "
                                                                                                                            "cancelled");
#endif /* defined(nImO_ChattyTcpLogging) */
                                                                                                            ODL_LOG("(BAErr::operation_aborted "
                                                                                                                    "== ec)"); //####
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            context->report("async_read_until() "
                                                                                                                            "failed");
                                                                                                            status = std::make_pair(false,
                                                                                                                                "async_read_until() "
                                                                                                                                    "failed");
                                                                                                        }
                                                                                                    }
                                                                                                    else
                                                                                                    {
                                                                                                        std::string handleThis{buffers_begin(rB->data()),
                                                                                                                                buffers_end(rB->data())};

#if defined(nImO_ChattyTcpLogging)
                                                                                                        context->report("got response");
#endif /* defined(nImO_ChattyTcpLogging) */
                                                                                                        handleResponse(handler, handleThis,
                                                                                                                       responseKey);
                                                                                                    }
                                                                                                    keepGoing = false;
                                                                                                    ODL_B1("keepGoing <- ", keepGoing); //####
                                                                                                });
                                                                    }
                                                                });
                                    }
                                });
            for ( ; keepGoing && gKeepRunning; )
            {
                boost::this_thread::yield();
            }
            socket.shutdown(BTCP::socket::shutdown_both);
        }
    }
    else
    {
        ODL_LOG("! (0 < requestToSend.getLength())"); //####
        status = std::make_pair(false, "0 >= requestToSend.getLength()");
    }
    ODL_EXIT(); //####
    return status;
} // nImO::SendRequestWithArgumentsAndNonEmptyResponse

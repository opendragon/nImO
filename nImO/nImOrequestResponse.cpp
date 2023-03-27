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

#include <nImOarray.h>
#include <nImOcontextWithMDNS.h>
#include <nImOmessage.h>
#include <nImOMIMESupport.h>
#include <nImOstring.h>

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
     const std::string          incoming,
     const std::string          expectedKey)
{
    if (nullptr != handler)
    {
        // We need to strip off the Message separator first.
        std::string         trimmed{incoming.substr(0, incoming.length() - (sizeof(MIME_MESSAGE_TERMINATOR_) - 1))};
        nImO::ByteVector    rawStuff;

        // Ignore a request that can't be processed...
        if (nImO::DecodeMIMEToBytes(trimmed, rawStuff))
        {
            auto    stuff{make_unique<nImO::Message>()};

            if ((nullptr != stuff) && (0 < rawStuff.size()))
            {
                stuff->open(false);
                stuff->appendBytes(rawStuff.data(), rawStuff.size());
                nImO::SpValue       contents{stuff->getValue()};
                CPtr(nImO::Array)   asArray{contents->asArray()};

                stuff->close();
                if (stuff->readAtEnd() && (nullptr != asArray) && (0 < asArray->size()))
                {
                    //nImO::SpValue       firstElement{(*asArray)[0]};
                    CPtr(nImO::String)  response{(*asArray)[0]->asString()};

                    if ((nullptr != response) && (expectedKey == response->getValue()))
                    {
                        handler->doIt(*asArray);
                    }
                    else
                    {
                        ODL_LOG("! (expectedKey == (*asArray)[0])"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (stuff->readAtEnd() && (nullptr != asArray) && (0 < asArray->size()))"); //####
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

void
nImO::SendRequestWithoutResponse
    (ContextWithMDNS &  context,
     Connection &       connection,
     const std::string  requestKey,
     const std::string  responseKey)
{
    Message requestToSend;
    SpArray requestArray{new Array};

    ODL_ENTER(); //####
    ODL_OBJENTER(); //####
    requestToSend.open(true);
    requestArray->addValue(std::make_shared<String>(requestKey));
    requestToSend.setValue(requestArray);
    requestToSend.close();
    if (0 < requestToSend.getLength())
    {
        auto    asString{requestToSend.getBytes()};

        if (0 < asString.length())
        {
            StringVector        outVec;
            std::atomic<bool>   keepGoing{true};

            EncodeBytesAsMIME(outVec, asString);
            auto    outString{nImO::PackageMessage(outVec)};

            // Make a connection to the service whose address is in the connection argument.
            asio::ip::tcp::socket   socket{*context.getService()};
            asio::ip::tcp::endpoint endpoint{asio::ip::make_address_v4(connection._address), connection._port};

            socket.async_connect(endpoint,
                                 [&context, &socket, &outString, &keepGoing, &responseKey]
                                 (const system::error_code &    ec1)
                                 {
                                    if (ec1)
                                    {
                                        context.report("async_connect failed");
                                        keepGoing = false;
                                    }
                                    else
                                    {
#if defined(nImO_ChattyTcpLogging)
                                        context.report("connection request accepted");
#endif /* defined(nImO_ChattyTcpLogging) */
                                        asio::async_write(socket, asio::buffer(outString->c_str(), outString->length()),
                                                          [&socket, &context, &keepGoing, &responseKey]
                                                          (const system::error_code &   ec2,
                                                           const std::size_t            NIMO_UNUSED_PARAM_(bytes_transferred))
                                                          {
                                                            if (ec2)
                                                            {
                                                                context.report("async_write failed");
                                                                keepGoing = false;
                                                            }
                                                            else
                                                            {
#if defined(nImO_ChattyTcpLogging)
                                                                context.report("command sent");
#endif /* defined(nImO_ChattyTcpLogging) */
                                                                asio::streambuf responseBuffer;

                                        asio::async_read_until(socket, responseBuffer, MatchMessageSeparator,
                                                                [&context, &responseBuffer, &keepGoing, &responseKey]
                                                                (const system::error_code & ec,
                                                                 const std::size_t          NIMO_UNUSED_PARAM_(size))
                                                                {
                                                                    if (ec)
                                                                    {
                                                                        context.report("async_read_until failed");
                                                                    }
                                                                    else
                                                                    {
#if defined(nImO_ChattyTcpLogging)
                                                                        context.report("got response");
#endif /* defined(nImO_ChattyTcpLogging) */
                                                                        handleResponse(nullptr, std::string{buffers_begin(responseBuffer.data()),                                               buffers_end(responseBuffer.data())},
                                                                                       responseKey);
                                                                    }
                                                                    keepGoing = false;
                                                                });
                                                            }});
                                    }});
            for ( ; keepGoing; )
            {
                thread::yield();
            }
            socket.close();
        }
        else
        {
            ODL_LOG("! (0 < asString.length())"); //####
        }
    }
    else
    {
        ODL_LOG("! (0 < requestToSend.getLength())"); //####
    }
    ODL_OBJEXIT(); //####
    ODL_EXIT(); //####
} // nImO::SendRequestWithoutResponse

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommandSession.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a nImO command session.
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
//  Created:    2023-01-14
//
//--------------------------------------------------------------------------------------------------

#include <nImOcommandSession.h>

#include <BasicTypes/nImOstring.h>
#include <BasicTypes/nImOvalue.h>
#include <ContainerTypes/nImOarray.h>
#include <ContainerTypes/nImOmessage.h>
#include <Contexts/nImOserviceContext.h>
#include <nImOcommandHandler.h>
#include <nImOmainSupport.h>
#include <nImOMIMESupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a %nImO command session. */
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

/*! @brief Handle the received request.
 @param[in,out] owner The owning Context for the session.
 @param[in,out] socket The TCP/IP socket to use for communication.
 @param[in] incoming The received request.
 @return @c true if the request was responded to. */
static bool
processRequest
    (nImO::SpContextWithNetworking  owner,
     nImO::SPsocketTCP              socket,
     const std::string &            incoming)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "socket = ", socket.get()); //####
    ODL_S1s("incoming = ", incoming); //####
    // We need to strip off the Message separator first.
    bool                okSoFar{false};
    std::string         trimmed{nImO::UnpackageMessage(incoming)};
    nImO::ByteVector    rawStuff;

    ODL_S1s("trimmed <- ", trimmed); //####
    // Ignore a request that can't be processed...
    if (nImO::DecodeMIMEToBytes(trimmed, rawStuff))
    {
        auto    stuff{make_unique<nImO::Message>()};

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
                    CPtr(nImO::String)  request{(*asArray)[0]->asString()};

                    if (nullptr == request)
                    {
                        ODL_LOG("(nullptr == request)"); //####
                    }
                    else
                    {
                        Ptr(nImO::CommandHandler)   handler{owner->asServiceContext()->getHandler(request->getValue())};

                        if (nullptr == handler)
                        {
                            ODL_LOG("(nullptr == handler)"); //####
                        }
                        else
                        {
                            okSoFar = handler->doIt(*socket.get(), *asArray);
                        }
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
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // processRequest

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::CommandSession::CommandSession
    (SpContextWithNetworking    owner) :
        _owner{owner}
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    try
    {
        _socket.reset(new asio::ip::tcp::socket(*_owner->getService()));
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::CommandSession::CommandSession

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::CommandSession::start
    (void)
{
    ODL_OBJENTER(); //####
    std::atomic<bool>   keepGoing{true};

#if defined(nImO_ChattyTcpLogging)
    _owner->report("retrieving request");
#endif /* defined(nImO_ChattyTcpLogging) */
    asio::async_read_until(*_socket, _buffer, MatchMessageSeparator,
                            [this, &keepGoing]
                            (const system::error_code & ec,
                             const std::size_t          size)
                            {
                                NIMO_UNUSED_VAR_(size);
                                if (ec)
                                {
                                    if (asio::error::operation_aborted == ec)
                                    {
#if defined(nImO_ChattyTcpLogging)
                                        _owner->report("async_read_until() operation cancelled");
#endif /* defined(nImO_ChattyTcpLogging) */
                                        ODL_LOG("(asio::error::operation_aborted == ec)"); //####
                                    }
                                    else
                                    {
                                        _owner->report("async_read_until() failed");
                                    }
                                }
                                else
                                {
#if defined(nImO_ChattyTcpLogging)
                                    _owner->report("got request");
#endif /* defined(nImO_ChattyTcpLogging) */
                                    if (! processRequest(_owner, _socket, std::string{buffers_begin(_buffer.data()), buffers_end(_buffer.data())}))
                                    {
                                        CommandHandler::SendBadResponse(_owner, _socket);
                                    }
                                }
                                keepGoing = false;
                                ODL_B1("keepGoing <- ", keepGoing); //####
                            });
    for ( ; keepGoing && gKeepRunning; )
    {
        this_thread::yield();
    }
    if (gPendingStop)
    {
        gKeepRunning = false;
        ODL_B1("gKeepRunning <- ", gKeepRunning); //####
    }
    ODL_OBJEXIT(); //####
} // nImO::CommandSession::start

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOinChannel.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO incoming connections to services.
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
//  Created:    2023-04-14
//
//--------------------------------------------------------------------------------------------------

#include <nImOinChannel.h>

#include <Contexts/nImOinputOutputContext.h>
#include <nImOmainSupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO incoming connections to services. */
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

nImO::InChannel::InChannel
    (ReceiveQueue &         inQueue,
     InputOutputContext &   context,
     const std::string &    path,
     const int              index) :
        inherited{context, path, index}, _inQueue(inQueue)
{
    ODL_ENTER(); //####
    ODL_P2("inQueue = ", &inQueue, "context = ", &context); //####
    ODL_S1s("path = ", path); //####
    ODL_I1("index = ", index); //####
    ODL_EXIT_P(this); //####
} // nImO::InChannel::InChannel

nImO::InChannel::~InChannel
    (void)
{
    ODL_OBJENTER(); //####
    stop();
    _tcpAcceptor.reset();
    ODL_OBJEXIT(); //####
} // nImO::InChannel::~InChannel

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::InChannel::receiveTcpMessages
    (void)
{
    ODL_ENTER(); //####
    if (gKeepRunning)
    {
        auto    rB{std::make_shared<boost::asio::streambuf>()};

        boost::asio::async_read_until(*_tcpSocket, *rB, nImO::MatchMessageSeparator,
                                    [this, rB]
                                    (const BSErr &      ec,
                                     const std::size_t  size)
                                    {
                                        NIMO_UNUSED_VAR_(size);
                                        if (ec)
                                        {
                                            if (BAErr::operation_aborted == ec)
                                            {
#if defined(nImO_ChattyTcpUdpLogging)
                                                _context.report("async_read_until() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                                ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                            }
                                            else
                                            {
                                                auto    errMessage{"async_read_until() failed -> "s + ec.message() + "."s};

                                                _context.report(errMessage);
                                            }
                                        }
                                        else
                                        {
                                            std::string receivedAsString{buffers_begin(rB->data()), buffers_end(rB->data())};
                                            auto        trimmed{UnpackageMessage(receivedAsString)};

                                            ODL_S1s("trimmed <- ", trimmed); //####
#if defined(nImO_ChattyTcpUdpLogging)
                                            _context.report("got message."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                            _inQueue.addRawBytesAsMessage(_index, trimmed);
                                            _statistics.update(trimmed.length());
                                            receiveTcpMessages();
                                        }
                                    });
    }
    ODL_EXIT(); //####
} // nImO::InChannel::receiveTcpMessages

void
nImO::InChannel::receiveUdpMessages
    (void)
{
    ODL_ENTER(); //####
    if (gKeepRunning)
    {
        _udpSocket->async_receive_from(boost::asio::buffer(_rawData), _udpSenderEndpoint,
                                       [this]
                                       (const BSErr         ec,
                                        const std::size_t   length)
                                       {
                                           if (ec)
                                           {
                                               if (BAErr::operation_aborted == ec)
                                               {
#if defined(nImO_ChattyTcpUdpLogging)
                                                   _context.report("async_read_until() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                                   ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                               }
                                               else
                                               {
                                                   auto    errMessage{"async_read_until() failed -> "s + ec.message() + "."s};

                                                   _context.report(errMessage);
                                               }

                                           }
                                           else
                                           {
                                               auto senderAddress{_udpSenderEndpoint.address().to_v4().to_uint()};
                                               auto senderPort{_udpSenderEndpoint.port()};

                                               if (_unfiltered || ((_matchAddress == senderAddress) && (_matchPort == senderPort)))
                                               {
                                                   std::string  receivedAsString{_rawData.data(), length};
                                                   auto         trimmed{UnpackageMessage(receivedAsString)};

                                                   ODL_S1s("trimmed <- ", trimmed); //####
#if defined(nImO_ChattyTcpUdpLogging)
                                                   _context.report("got message."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                                   _inQueue.addRawBytesAsMessage(_index, senderAddress, senderPort, trimmed);
                                                   _statistics.update(trimmed.length());
                                               }
                                               receiveUdpMessages();
                                           }
                                       });
    }
    ODL_EXIT(); //####
} // nImO::InChannel::receiveUdpMessages

bool
nImO::InChannel::setUp
    (const TransportType    mode)
{
    ODL_OBJENTER(); //####
    ODL_I1("mode = ", StaticCast(int, mode)); //####
    bool    okSoFar{false};

    _connection._transport = mode;
    // Set up network activity.
    if (TransportType::kUDP == _connection._transport)
    {
        BAIP::address_v4    inAddress{0};
        BUDP::endpoint      inEndpoint{inAddress, 0};

        _udpSocket = std::make_shared<BUDP::socket>(*_context.getService());
        _udpSocket->open(inEndpoint.protocol());
        _udpSocket->set_option(BUDP::socket::reuse_address(true));
        _udpSocket->bind(inEndpoint);
        _connection._address = ntohl(ContextWithMDNS::gServiceAddressIpv4.sin_addr.s_addr);
        _connection._port = _udpSocket->local_endpoint().port();
        okSoFar = true;
        ODL_B1("okSoFar = ", okSoFar); //####
#if defined(nImO_ChattyTcpUdpLogging)
        _context.report("local port = "s + std::to_string(_connection._port) + "."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
    }
    else
    {
        if (TransportType::kTCP == _connection._transport)
        {
            _tcpAcceptor = std::make_shared<BTCP::acceptor>(*_context.getService());
            _tcpAcceptor->open(BTCP::v4());
            _tcpAcceptor->listen();
            _connection._address = ntohl(ContextWithMDNS::gServiceAddressIpv4.sin_addr.s_addr);
            _connection._port = _tcpAcceptor->local_endpoint().port();
#if defined(nImO_ChattyTcpUdpLogging)
            _context.report("acceptor port = "s + std::to_string(_connection._port) + "."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
            _tcpSocket = std::make_shared<BTCP::socket>(*_context.getService());
            okSoFar = true;
            ODL_B1("okSoFar = ", okSoFar); //####
        }
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::InChannel::setUp

bool
nImO::InChannel::start
    (const IPv4Address  senderAddress,
     const IPv4Port     senderPort)
{
    ODL_OBJENTER(); //####
    ODL_X1("senderAddress = ", senderAddress); //####
    ODL_I1("senderPort = ", senderPort); //####
    bool    okSoFar{false};

    _matchAddress = senderAddress;
    _matchPort = senderPort;
    // Start network activity.
    if (TransportType::kUDP == _connection._transport)
    {
        _unfiltered = ((BytesToIPv4Address(0, 0, 0, 0) == _matchAddress) && (0 == _matchPort));
        _udpConnected = true;
        ODL_B2("_unfiltered <- ", _unfiltered, "_udpConnected <- ", _udpConnected); //####
        receiveUdpMessages();
        okSoFar = true;
        ODL_B1("okSoFar = ", okSoFar); //####
    }
    else
    {
        if (TransportType::kTCP == _connection._transport)
        {
            // Start the acceptor listening.
            _unfiltered = true;
            _tcpAcceptor->async_accept(*_tcpSocket,
                                       [this]
                                       (const BSErr ec)
                                       {
                                            if (ec)
                                            {
                                                if (BAErr::operation_aborted == ec)
                                                {
#if defined(nImO_ChattyTcpUdpLogging)
                                                    _context.report("async_accept() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                                    ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                                }
                                                else
                                                {
                                                    _context.report("async_accept() failed -> "s + ec.message() + "."s);
                                                }
                                            }
                                            else
                                            {
                                                _tcpConnected = true;
                                                ODL_B1("_tcpConnected <- ", _tcpConnected); //####
                                                receiveTcpMessages();
                                            }
                                       });
            okSoFar = true;
            ODL_B1("okSoFar = ", okSoFar); //####
        }
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::InChannel::start

bool
nImO::InChannel::stop
    (void)
{
    ODL_OBJENTER(); //####
    bool    okSoFar{false};

    // Stop network activity and clear state.
    if (TransportType::kUDP == _connection._transport)
    {
        if (_udpSocket->is_open())
        {
            _udpSocket->cancel();
        }
        _udpConnected = false;
        ODL_B1("_udpConnected <- ", _udpConnected); //####
        okSoFar = true;
        ODL_B1("okSoFar = ", okSoFar); //####
    }
    else
    {
        if (TransportType::kTCP == _connection._transport)
        {
            if (_tcpSocket->is_open())
            {
                _tcpSocket->cancel();
            }
            if (_tcpAcceptor->is_open())
            {
                _tcpAcceptor->close();
            }
            _tcpConnected = false;
            ODL_B1("_tcpConnected <- ", _tcpConnected); //####
            okSoFar = true;
            ODL_B1("okSoFar = ", okSoFar); //####
        }
        else
        {
            okSoFar = true;
            ODL_B1("okSoFar = ", okSoFar); //####
        }
    }
    _connection._transport = TransportType::kUnknown;
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::InChannel::stop

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

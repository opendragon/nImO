//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOoutChannel.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO outgoing connections to services.
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

#include <nImOoutChannel.h>

#include <Containers/nImOmap.h>
#include <Containers/nImOmessage.h>
#include <Contexts/nImOinputOutputContext.h>
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
 @brief The class definition for %nImO outgoing connections to services. */
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

nImO::OutChannel::OutChannel
    (InputOutputContext &   context,
     const std::string &    path,
     const int              index) :
        inherited{context, path, index}
{
    ODL_ENTER(); //####
    ODL_P1("context = ", &context); //####
    ODL_S1s("path = ", path); //####
    ODL_I1("index = ", index); //####
    ODL_EXIT_P(this); //####
} // nImO::OutChannel::OutChannel

nImO::OutChannel::~OutChannel
    (void)
{
    ODL_OBJENTER(); //####
    stop();
    ODL_OBJEXIT(); //####
} // nImO::OutChannel::~OutChannel

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::OutChannel::send
    (SpValue    valueToSend)
{
    ODL_OBJENTER(); //####
    ODL_P1("valueToSend = ",valueToSend.get()); //####
    bool    okSoFar{false};

    if (nullptr == valueToSend)
    {
        ODL_LOG("(nullptr == valueToSend)"); //####
    }
    else if (TransportType::kUnknown == _connection._transport)
    {
        okSoFar = true; // if the channel hasn't been configured, just throw the message away but it's not an error.
    }
    else
    {
        Message messageToSend;

        messageToSend.open(true);
        messageToSend.setValue(valueToSend);
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
                StdStringVector outVec;

                EncodeBytesAsMIME(outVec, asString);
                auto    outString{PackageMessage(outVec)};

                // send the encoded message to the receiver
                if (TransportType::kUDP == _connection._transport)
                {
                    _udpSocket->async_send_to(boost::asio::buffer(*outString), _udpSendpoint,
                                              [this, outString]
                                              (const BSErr          ec,
                                               const std::size_t    length)
                                              {
                                                NIMO_UNUSED_VAR_(length);
                                                if (ec)
                                                {
                                                    if (BAErr::operation_aborted == ec)
                                                    {
#if defined(nImO_ChattyTcpUdpLogging)
                                                        _context.report("async_send_to() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                                        ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                                    }
                                                    else
                                                    {
                                                        auto    errMessage{"async_send_to() failed -> "s + ec.message() + "."s};

                                                        _context.report(errMessage);
                                                    }
                                                }
                                              });
                    okSoFar = true;
                }
                else if (TransportType::kTCP == _connection._transport)
                {
                    if (_tcpConnected)
                    {
                        boost::asio::async_write(*_tcpSocket, boost::asio::buffer(*outString),
                                                 [this, outString]
                                                 (const BSErr &        ec,
                                                  const std::size_t    bytes_transferred)
                                                 {
                                                    NIMO_UNUSED_VAR_(bytes_transferred);
                                                    if (ec)
                                                    {
                                                        if (BAErr::operation_aborted == ec)
                                                        {
#if defined(nImO_ChattyTcpUdpLogging)
                                                            _context.report("async_write() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                                            ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                                        }
                                                        else
                                                        {
                                                            auto    errMessage{"async_write() failed -> "s + ec.message() + "."s};

                                                            _context.report(errMessage);
                                                        }
                                                    }
                                                 });
                    }
                    okSoFar = true;
                }
            }
        }
        else
        {
            ODL_LOG("! (0 < messageToSend.getLength())"); //####
        }
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::OutChannel::send

bool
nImO::OutChannel::setUp
    (const IPv4Address      receiveAddress,
     const IPv4Port         receivePort,
     const TransportType    mode)
{
    ODL_OBJENTER(); //####
    ODL_X1("receiveAddress = ", receiveAddress); //####
    ODL_I2("receivePort = ", receivePort, "mode = ", StaticCast(int, mode)); //####
    bool                okSoFar{false};
    BAIP::address_v4    outAddress{0};
    BAIP::address_v4    destAddress{receiveAddress};

    _connection._transport = mode;
    _destinationAddress = receiveAddress;
    _destinationPort = receivePort;
    // Set up network activity.
    if (TransportType::kUDP == _connection._transport)
    {
        BUDP::endpoint  outEndpoint{outAddress, 0};

        _udpSocket = std::make_shared<BUDP::socket>(*_context.getService());
        _udpSocket->open(outEndpoint.protocol());
        _udpSocket->set_option(BUDP::socket::reuse_address(true));
        _udpSocket->bind(outEndpoint);
        _connection._address = ntohl(ContextWithMDNS::gServiceAddressIpv4.sin_addr.s_addr);
        _connection._port = _udpSocket->local_endpoint().port();
#if defined(nImO_ChattyTcpUdpLogging)
        _context.report("local port = "s + std::to_string(_connection._port) + ", destination port = "s + std::to_string(_destinationPort) + "."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
        _udpSendpoint.address(destAddress);
        _udpSendpoint.port(_destinationPort);
        okSoFar = true;
    }
    else if (TransportType::kTCP == _connection._transport)
    {
        BTCP::endpoint  outEndpoint{outAddress, 0};

        _tcpSocket = std::make_shared<BTCP::socket>(*_context.getService());
#if defined(nImO_ChattyTcpUdpLogging)
        _context.report("destination port = "s + std::to_string(_destinationPort) + "."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
        _tcpSendpoint.address(destAddress);
        _tcpSendpoint.port(_destinationPort);
        okSoFar = true;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::OutChannel::setUp

bool
nImO::OutChannel::start
    (void)
{
    ODL_OBJENTER(); //####
    bool    okSoFar{false};

    // Start network activity.
    if (TransportType::kUDP == _connection._transport)
    {
        _udpConnected = true;
        ODL_B1("_udpConnected <- ", _udpConnected); //####
        okSoFar = true;
    }
    else if (TransportType::kTCP == _connection._transport)
    {
        _tcpSocket->async_connect(_tcpSendpoint,
                                  [this]
                                  (const BSErr  ec)
                                  {
                                    if (ec)
                                    {
                                        if (BAErr::operation_aborted == ec)
                                        {
#if defined(nImO_ChattyTcpUdpLogging)
                                            _context.report("async_connect() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                                            ODL_LOG("(BAErr::operation_aborted == ec)"); //####
                                        }
                                        else
                                        {
                                            auto    errMessage{"async_connect() failed -> "s + ec.message() + "."s};

                                            _context.report(errMessage);
                                        }
                                    }
                                    else
                                    {
                                        _connection._address = ntohl(ContextWithMDNS::gServiceAddressIpv4.sin_addr.s_addr);
                                        _connection._port = _tcpSocket->local_endpoint().port();
                                        _tcpConnected = true;
                                        ODL_B1("_tcpConnected <- ", _tcpConnected); //####
                                    }
                                  });
        for ( ; gKeepRunning && (! _tcpConnected); )
        {
            boost::this_thread::yield();
        }
        okSoFar = true;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::OutChannel::start

bool
nImO::OutChannel::stop
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
        okSoFar = true;
    }
    else if (TransportType::kTCP == _connection._transport)
    {
        if (_tcpSocket->is_open())
        {
            _tcpSocket->cancel();
            okSoFar = true;
        }
    }
    else
    {
        okSoFar = true;
    }
    _connection._transport = TransportType::kUnknown;
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::OutChannel::stop

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

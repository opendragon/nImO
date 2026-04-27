//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOreceiveFromMessagePort.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO handling messages on a multicast port.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2026 by OpenDragon.
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
//  Created:    2026-04-26
//
//--------------------------------------------------------------------------------------------------

#include <nImOreceiveFromMulticast.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for for receiving %nImO messages from a multicast group. */
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

nImO::ReceiveFromMulticast::ReceiveFromMulticast
    (nImO::SPservice            service,
     const nImO::Connection &   theConnection,
     nImO::ReceiveQueue &       theQueue) :
        _queue(theQueue), _socket(*service)
{
    ODL_ENTER(); //####
    ODL_P2(service.get(), &theQueue); //####
    BAIP::address_v4    listenAddress{0};
    BAIP::address_v4    multicastAddress{theConnection._address};
    BUDP::endpoint      listenEndpoint{listenAddress, theConnection._port};

    _socket.open(listenEndpoint.protocol());
    _socket.set_option(BUDP::socket::reuse_address(true));
    _socket.bind(listenEndpoint);
    // Join the multicast group.
    _socket.set_option(BAIP::multicast::join_group(multicastAddress));
    receiveAMessage();
    ODL_EXIT_P(this); //####
} // nImO::ReceiveFromMulticast::ReceiveFromMulticast

nImO::ReceiveFromMulticast::~ReceiveFromMulticast
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::ReceiveFromMulticast::~ReceiveFromMulticast

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::ReceiveFromMulticast::receiveAMessage
    (void)
{
    ODL_OBJENTER(); //####
    if (nImO::gKeepRunning)
    {
        _socket.async_receive_from(BA::buffer(_data), _senderEndpoint,
                                   [this]
                                   (const BSErr         ec,
                                    const std::size_t   length)
                                   {
                                       if (! ec)
                                       {
                                           std::string          receivedAsString{_data.data(), length};
                                           nImO::IPv4Address    senderAddress{_senderEndpoint.address().to_v4().to_uint()};
                                           nImO::IPv4Port       senderPort{_senderEndpoint.port()};

                                           _queue.addRawBytesAsMessage(0, senderAddress, senderPort, receivedAsString);
                                           receiveAMessage();
                                       }
                                   });
    }
    ODL_OBJEXIT(); //####
} // nImO::ReceiveFromMulticast::receiveAMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

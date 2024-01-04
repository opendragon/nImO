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

#include <Contexts/nImOinputOutputContext.h>

//#include <odlEnable.h>
#include <odlInclude.h>

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
nImO::OutChannel::setUp
    (const IPv4Address      receiveAddress,
     const IPv4Port         receivePort,
     const TransportType    mode)
{
    ODL_OBJENTER(); //####
    ODL_I3("receiveAddress = ", receiveAddress, "receivePort = ", receivePort, "mode = ", StaticCast(int, mode)); //####
    bool    okSoFar{false};

    _connection._transport = mode;
    _destinationAddress = receiveAddress;
    _destinationPort = receivePort;
    // Set up network activity.
    if (TransportType::kUDP == _connection._transport)
    {
        BAIP::address_v4    outAddress{0};
        BUDP::endpoint      outEndpoint{outAddress, 0};

        _udpSocket.open(outEndpoint.protocol());
        _udpSocket.set_option(BUDP::socket::reuse_address(true));
        _udpSocket.bind(outEndpoint);
        _connection._address = ntohl(ContextWithMDNS::gServiceAddressIpv4.sin_addr.s_addr);
        _connection._port = _udpSocket.local_endpoint().port();
        okSoFar = true;
    }
    else if (TransportType::kTCP == _connection._transport)
    {
//TBD!
        std::cerr << "** " << ODL_FUNC_NAME_ << " ** Unimplemented **\n";
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
        //TBD?!?!
        okSoFar = true;
    }
    else if (TransportType::kTCP == _connection._transport)
    {
//TBD!
        std::cerr << "** " << ODL_FUNC_NAME_ << " ** Unimplemented **\n";
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

    if (_active)
    {
        // Stop network activity and clear state.
        _active = false;
        if (TransportType::kUDP == _connection._transport)
        {
//TBD!
            std::cerr << "** " << ODL_FUNC_NAME_ << " ** Unimplemented **\n";
        }
        else if (TransportType::kTCP == _connection._transport)
        {
//TBD!
            std::cerr << "** " << ODL_FUNC_NAME_ << " ** Unimplemented **\n";
        }
    }
    else
    {
        okSoFar = true;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::OutChannel::stop

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

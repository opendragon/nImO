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
    (const std::string &    path,
     const int              index) :
        inherited{path, index}
{
    ODL_ENTER(); //####
    ODL_I1("index = ", index); //####
    ODL_EXIT_P(this); //####
} // nImO::InChannel::InChannel

nImO::InChannel::InChannel
    (InChannel &&  other)
    noexcept :
        inherited{std::move(other)}, _matchAddress{other._matchAddress}, _matchPort{other._matchPort}
{
    ODL_ENTER(); //####
    other._matchAddress = BytesToIPv4Address(0, 0, 0, 0);
    other._matchPort = 0;
    ODL_EXIT_P(this); //####
} // nImO::InChannel::InChannel

nImO::InChannel::~InChannel
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::InChannel::~InChannel

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::InChannel &
nImO::InChannel::operator=
    (InChannel &&    other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _matchAddress = other._matchAddress;
        other._matchAddress = BytesToIPv4Address(0, 0, 0, 0);
        _matchPort = other._matchPort;
        other._matchPort = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::InChannel::operator=

bool
nImO::InChannel::setUp
    (const TransportType    mode)
{
    ODL_OBJENTER(); //####
    bool    okSoFar{false};

    _connection._transport = mode;
    // TBD - set up network activity.
    switch (_connection._transport)
    {
        case TransportType::kTCP :
            // TBD!
            break;

        case TransportType::kUDP :
            // TBD!
            break;

        default :
            // Should never get here!
            break;

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
    ODL_I2("senderAddress = ", senderAddress, "senderPort = ", senderPort); //####
    bool    okSoFar{false};

    _matchAddress = senderAddress;
    _matchPort = senderPort;
    // TBD - start network activity.
    switch (_connection._transport)
    {
        case TransportType::kTCP :
            // TBD!
            break;

        case TransportType::kUDP :
            // TBD!
            break;

        default :
            // Should never get here!
            break;

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

    // TBD - stop network activity and clear state.
    switch (_connection._transport)
    {
        case TransportType::kTCP :
            // TBD!
            break;

        case TransportType::kUDP :
            // TBD!
            break;

        default :
            // Should never get here!
            break;

    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::InChannel::stop

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

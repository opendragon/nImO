//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOsendToMessagePort.cpp
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

#include <nImOsendToMulticastPort.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <Containers/nImOmessage.h>
#include <nImOMIMESupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for for sending %nImO messages to a multicast group. */
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

nImO::SendToMulticastPort::SendToMulticastPort
    (nImO::SPservice            service,
     const nImO::Connection &   theConnection) :
        _connection{theConnection}, _endpoint{BAIP::address_v4(_connection._address), _connection._port},
        _socket{*service, _endpoint.protocol()}
{
    ODL_ENTER(); //####
    ODL_P1(service.get()); //####
    BAIP::address_v4    multicastAddress{_connection._address};

    // Join the multicast group.
    _socket.set_option(BAIP::multicast::join_group(multicastAddress));
    ODL_EXIT_P(this); //####
} // nImO::SendToMulticastPort::SendToMulticastPort

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::SendToMulticastPort::sendValues
    (SpMap  valuesToSend)
{
    ODL_OBJENTER(); //####
    ODL_P1(valuesToSend.get()); //####
    bool    okSoFar{false};

    if (valuesToSend)
    {
        Message messageToSend;
//        auto    messageMap{std::make_shared<Map>()};

        messageToSend.open(true);
//        messageMap->addValue(std::make_shared<String>(key), valueToSend);
//        messageMap->addValue(std::make_shared<String>(kComputerNameKey), _computerName);
//        messageMap->addValue(std::make_shared<String>(kTagKey), _tag);
//        if (nullptr != _commandPort)
//        {
//            messageMap->addValue(std::make_shared<String>(kCommandPortKey), _commandPort);
//        }
        messageToSend.setValue(valuesToSend);
        messageToSend.close();
        if (0 < messageToSend.getLength())
        {
            if (auto asString{messageToSend.getString()}; asString.empty())
            {
                ODL_LOG("(asString.empty())"); //####
            }
            else
            {
                StdStringVector outVec;

                EncodeBytesAsMIME(outVec, asString);
                auto    outString(std::make_shared<std::string>(boost::algorithm::join(outVec, "\n"s)));

                // send the encoded message to the logging ports
                _socket.async_send_to(BA::buffer(*outString), _endpoint,
                                      [outString]
                                      (const BSErr          ec,
                                       const std::size_t    length)
                                      {
                                        NIMO_UNUSED_VAR_(ec);
                                        NIMO_UNUSED_VAR_(length);
                                      });
                okSoFar = true;
                ODL_B1(okSoFar); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < messageToSend.getLength())"); //####
        }
    }
    else
    {
        ODL_LOG("! (valuesToSend)"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::SendToMulticastPort::sendValues

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

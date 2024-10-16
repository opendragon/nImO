//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOlogger.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO logging mechanism.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2022 by OpenDragon.
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
//  Created:    2022-07-19
//
//--------------------------------------------------------------------------------------------------

#include <nImOlogger.h>

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <Containers/nImOmessage.h>
#include <nImOMIMESupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if MAC_OR_LINUX_OR_BSD_
# include <unistd.h>
#else // not MAC_OR_LINUX_OR_BSD_
# include <winsock.h>
#endif // not MAC_OR_LINUX_OR_BSD_

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
 @brief The class definition for the %nImO logging mechanism. */
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

const std::string   nImO::kCommandPortKey{"commandPort"s};

const std::string   nImO::kComputerNameKey{"computer"s};

const std::string   nImO::kMessageKey{"message"s};

const std::string   nImO::kTagKey{"tag"s};

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Logger::Logger
    (SPservice              service,
     const std::string &    tagForLogging,
     const Connection &     logConnection):
        _connection{logConnection}, _endpoint{BAIP::address_v4(_connection._address), _connection._port},
        _socket{*service, _endpoint.protocol()}, _commandPort{nullptr}
{
    _computerName = std::make_shared<String>(GetShortComputerName());
    _tag = std::make_shared<String>(tagForLogging);
    ODL_EXIT_P(this); //####
} // nImO::Logger::Logger

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::Logger::report
    (CPtr(char) stringToSend)
{
    ODL_OBJENTER(); //####
    ODL_S1(stringToSend); //####
    bool    okSoFar;

    if ((nullptr != stringToSend) && (0 < strlen(stringToSend)))
    {
        okSoFar = report(std::make_shared<String>(stringToSend));
        ODL_B1(okSoFar); //####
    }
    else
    {
        okSoFar = false;
        ODL_B1(okSoFar); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::Logger::report

bool
nImO::Logger::report
    (const std::string &    stringToSend)
{
    ODL_OBJENTER(); //####
    ODL_S1s(stringToSend); //####
    bool    okSoFar;

    if (stringToSend.empty())
    {
        okSoFar = false;
        ODL_B1(okSoFar); //####
    }
    else
    {
        okSoFar = report(std::make_shared<String>(stringToSend));
        ODL_B1(okSoFar); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::Logger::report

bool
nImO::Logger::report
    (const StdStringVector &    stringsToSend)
{
    ODL_OBJENTER(); //####
    ODL_P1(&stringsToSend); //####
    bool    okSoFar;

    if (1 <= stringsToSend.size())
    {
        if (1 < stringsToSend.size())
        {
            auto    stringArray{std::make_shared<Array>()};

            for (size_t ii = 0; ii < stringsToSend.size(); ++ii)
            {
                stringArray->addValue(std::make_shared<String>(stringsToSend[ii]));
            }
            okSoFar = report(stringArray);
            ODL_B1(okSoFar); //####
        }
        else
        {
            okSoFar = report(stringsToSend[0]);
            ODL_B1(okSoFar); //####
        }
    }
    else
    {
        okSoFar = false;
        ODL_B1(okSoFar); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::Logger::report

bool
nImO::Logger::report
    (SpValue    valueToSend)
{
    ODL_OBJENTER(); //####
    ODL_P1(valueToSend.get()); //####
    bool    okSoFar{false};

    if (valueToSend)
    {
        Message messageToSend;
        auto    messageMap{std::make_shared<Map>()};

        messageToSend.open(true);
        messageMap->addValue(std::make_shared<String>(kMessageKey), valueToSend);
        messageMap->addValue(std::make_shared<String>(kComputerNameKey), _computerName);
        messageMap->addValue(std::make_shared<String>(kTagKey), _tag);
        if (nullptr != _commandPort)
        {
            messageMap->addValue(std::make_shared<String>(kCommandPortKey), _commandPort);
        }
        messageToSend.setValue(messageMap);
        messageToSend.close();
        if (0 < messageToSend.getLength())
        {
            auto    asString{messageToSend.getString()};

            if (asString.empty())
            {
                ODL_LOG("(asString.empty())"); //####
            }
            else
            {
                StdStringVector outVec;

                EncodeBytesAsMIME(outVec, asString);
                auto    outString(std::make_shared<std::string>(boost::algorithm::join(outVec, "\n"s)));

                // send the encoded message to the logging ports
                _socket.async_send_to(boost::asio::buffer(*outString), _endpoint,
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
        ODL_LOG("! (valueToSend)"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::Logger::report

void
nImO::Logger::setCommandPort
    (const IPv4Port commandPort)
{
    ODL_OBJENTER(); //####
    ODL_I1(commandPort); //####
    _commandPort.reset();
    if (0 < commandPort)
    {
        _commandPort = std::make_shared<Integer>(commandPort);
    }
    ODL_OBJEXIT(); //####
} // nImO::Logger::setCommandPort

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

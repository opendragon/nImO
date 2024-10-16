//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/CommandHandlers/nImOsetUpSenderCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO set up sender command handler.
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
//  Created:    2023-12-25
//
//--------------------------------------------------------------------------------------------------

#include <CommandHandlers/nImOsetUpSenderCommandHandler.h>

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <nImOinputOutputCommands.h>
#include <nImOoutChannel.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO set up sender command handler. */
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

nImO::SetUpSenderCommandHandler::SetUpSenderCommandHandler
    (SpInputOutputContext   owner) :
        inherited{owner}
{
    ODL_ENTER(); //####
    ODL_P1(owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::SetUpSenderCommandHandler::SetUpSenderCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::SetUpSenderCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments,
     std::string &  reason)
    const
{
    ODL_OBJENTER(); //####
    ODL_P3(&socket, &arguments, &reason); //####
    bool    okSoFar{false};

    _ownerForInputOutput->report("set up sender request received."s);
    if (5 < arguments.size())
    {
        auto    pathString{arguments[1]->asString()};
        auto    addressValue{arguments[2]->asAddress()};
        auto    portValue{arguments[3]->asInteger()};
        auto    dataTypeString{arguments[4]->asString()};
        auto    modeValue{arguments[5]->asInteger()};

        if ((nullptr != pathString) && (nullptr != addressValue) && (nullptr != portValue) && (nullptr != dataTypeString) && (nullptr != modeValue))
        {
            auto    theChannel{_ownerForInputOutput->getOutputChannel(pathString->getValue())};

            if (theChannel)
            {
                auto    receiveAddress{addressValue->getAddressValue()};
                auto    receivePort{StaticCast(IPv4Port, portValue->getIntegerValue())};
                auto    mode{StaticCast(TransportType, modeValue->getIntegerValue())};

                if (theChannel->setUp(receiveAddress, receivePort, mode))
                {
                    auto    theConnection{theChannel->getConnection()};
                    auto    infoArray{std::make_shared<Array>()};

                    infoArray->addValue(std::make_shared<Address>(theConnection._address));
                    infoArray->addValue(std::make_shared<Integer>(theConnection._port));
                    okSoFar = sendComplexResponse(socket, kSetUpSenderResponse, "set up sender"s, infoArray, reason);
                    ODL_B1(okSoFar); //####
                }
                else
                {
                    ODL_LOG("! (theChannel->setUp(receiveAddress, receivePort, mode))"); //####
                    reason = "Problem setting up output channel"s;
                }
            }
            else
            {
                ODL_LOG("! (theChannel)"); //####
                reason = "No output channel with that name"s;
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != pathString) && (nullptr != addressValue) && (nullptr != portValue) && (nullptr != dataTypeString) && " //####
                    "(nullptr != modeValue))"); //####
            reason = "One or more invalid arguments"s;
        }
    }
    else
    {
        ODL_LOG("! (5 < arguments.size())"); //####
        reason = "Missing argument(s)"s;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::SetUpSenderCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Registry/CommandHandlers/nImOgetInformationForAllChannelsOnNodeCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'get information for all channels on node' command handler.
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
//  Created:    2023-05-21
//
//--------------------------------------------------------------------------------------------------

#include "nImOgetInformationForAllChannelsOnNodeCommandHandler.h"

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <nImOregistryCommands.h>
#include <nImOregistryTypes.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO 'get information for all channels on node' command handler. */
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

nImO::GetInformationForAllChannelsOnNodeCommandHandler::GetInformationForAllChannelsOnNodeCommandHandler
    (SpServiceContext   owner,
     SpRegistry         theRegistry) :
        inherited{owner, theRegistry}
{
    ODL_ENTER(); //####
    ODL_P2(owner.get(), theRegistry.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::GetInformationForAllChannelsOnNodeCommandHandler::GetInformationForAllChannelsOnNodeCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::GetInformationForAllChannelsOnNodeCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments,
     std::string &  reason)
    const
{
    NIMO_UNUSED_VAR_(arguments);
    ODL_OBJENTER(); //####
    ODL_P3(&socket, &arguments, &reason); //####
    bool    okSoFar{false};

    _owner->report("get information for all channels on node request received."s);
    if (1 < arguments.size())
    {
        auto    asString{arguments[1]->asString()};

        if (nullptr == asString)
        {
            ODL_LOG("(nullptr == asString)"); //####
            reason = "Invalid argument(s)"s;
        }
        else
        {
            auto    statusWithInfoVector{_registry->getInformationForAllChannelsOnNode(asString->getValue())};

            if (statusWithInfoVector.first.first)
            {
                auto    channelArray{std::make_shared<Array>()};

                for (auto & walker : statusWithInfoVector.second)
                {
                    auto    infoArray{std::make_shared<Array>()};

                    infoArray->addValue(std::make_shared<Logical>(walker._found));
                    infoArray->addValue(std::make_shared<String>(walker._node));
                    infoArray->addValue(std::make_shared<String>(walker._path));
                    infoArray->addValue(std::make_shared<Logical>(walker._isOutput));
                    infoArray->addValue(std::make_shared<String>(walker._dataType));
                    infoArray->addValue(std::make_shared<Integer>(StaticCast(int, walker._modes)));
                    infoArray->addValue(std::make_shared<Logical>(walker._inUse));
                    channelArray->addValue(infoArray);
                }
                okSoFar = sendComplexResponse(socket, kGetInformationForAllChannelsOnNodeResponse, "get information for all channels on node"s,
                                              channelArray, reason);
                ODL_B1(okSoFar); //####
            }
            else
            {
                ODL_LOG("! (statusWithInfoVector.first.first)"); //####
                reason = "getInformationForAllChannelsOnNode() returned '"s + statusWithInfoVector.first.second + "'"s;
            }
        }
    }
    else
    {
        ODL_LOG("! (0 < arguments.size())"); //####
        reason = "Missing argument(s)"s;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetInformationForAllChannelsOnNodeCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

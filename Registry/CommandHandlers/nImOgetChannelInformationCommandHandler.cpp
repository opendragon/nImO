//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Registry/CommandHandlers/nImOgetChannelInformationCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'get channel information' command handler.
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

#include "nImOgetChannelInformationCommandHandler.h"

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
 @brief The class definition for the %nImO 'get channel information' command handler. */
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

nImO::GetChannelInformationCommandHandler::GetChannelInformationCommandHandler
    (SpServiceContext   owner,
     SpRegistry         theRegistry) :
        inherited{owner, theRegistry}
{
    ODL_ENTER(); //####
    ODL_P2(owner.get(), theRegistry.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::GetChannelInformationCommandHandler::GetChannelInformationCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::GetChannelInformationCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments,
     std::string &  reason)
    const
{
    NIMO_UNUSED_VAR_(arguments);
    ODL_OBJENTER(); //####
    ODL_P3(&socket, &arguments, &reason); //####
    bool    okSoFar{false};

    _owner->report("get channel information request received."s);
    if (2 < arguments.size())
    {
        auto    asString1{arguments[1]->asString()};
        auto    asString2{arguments[2]->asString()};

        if ((nullptr != asString1) && (nullptr != asString2))
        {
            auto    statusWithInfo{_registry->getChannelInformation(asString1->getValue(), asString2->getValue())};

            if (statusWithInfo.first.first)
            {
                ChannelInfo &   theInfo{statusWithInfo.second};
                auto            infoArray{std::make_shared<Array>()};

                infoArray->addValue(std::make_shared<Logical>(theInfo._found));
                infoArray->addValue(std::make_shared<String>(theInfo._node));
                infoArray->addValue(std::make_shared<String>(theInfo._path));
                infoArray->addValue(std::make_shared<Logical>(theInfo._isOutput));
                infoArray->addValue(std::make_shared<String>(theInfo._dataType));
                infoArray->addValue(std::make_shared<Integer>(StaticCast(int, theInfo._modes)));
                infoArray->addValue(std::make_shared<Logical>(theInfo._inUse));
                okSoFar = sendComplexResponse(socket, kGetChannelInformationResponse, "get channel information"s, infoArray, reason);
                ODL_B1(okSoFar); //####
            }
            else
            {
                ODL_LOG("! (statusWithInfo.first.first)"); //####
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != asString1) && (nullptr != asString2))"); //####
            reason = "One or more invalid arguments"s;
        }
    }
    else
    {
        ODL_LOG("! (2 < arguments.size())"); //####
        reason = "Missing argument(s)"s;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetChannelInformationCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO command handlers.
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
//  Created:    2023-03-25
//
//--------------------------------------------------------------------------------------------------

#include <nImOcommandHandler.h>

#include <nImOarray.h>
#include <nImOlogical.h>
#include <nImOmessage.h>
#include <nImOMIMESupport.h>
#include <nImOstring.h>

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
 @brief The class definition for %nImO command handlers. */
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

nImO::CommandHandler::CommandHandler
    (void)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::ServiceContext::ServiceContext

nImO::CommandHandler::~CommandHandler
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::CommandHandler::~CommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::CommandHandler::sendResponse
    (const std::string  responseKey,
     const bool         wasOK)
    const
{
    Message responseToSend;
    SpArray responseArray{new Array};

    ODL_OBJENTER(); //####
    responseToSend.open(true);
    responseArray->addValue(std::make_shared<String>(responseKey));
    responseArray->addValue(std::make_shared<Logical>(wasOK));
    responseToSend.setValue(responseArray);
    responseToSend.close();
    if (0 < responseToSend.getLength())
    {
        auto    asString{responseToSend.getBytes()};

        if (0 < asString.length())
        {
            StringVector    outVec;

            EncodeBytesAsMIME(outVec, asString);
            auto    outString(std::make_shared<std::string>(boost::algorithm::join(outVec, "\n") + kMessageSentinel));

            // send the encoded message to the requestor
//            _socket.async_send_to(asio::buffer(*outString), _endpoint,
//                                  [outString]
//                                  (const system::error_code NIMO_UNUSED_PARAM_(ec),
//                                   const std::size_t        NIMO_UNUSED_PARAM_(length))
//                                  {
//                                  });
        }
        else
        {
            ODL_LOG("! (0 < asString.length())"); //####
        }
    }
    else
    {
        ODL_LOG("! (0 < responseToSend.getLength())"); //####
    }
    ODL_OBJEXIT(); //####
} // nImO::CommandHandler::sendResponse

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

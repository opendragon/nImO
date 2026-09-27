//--------------------------------------------------------------------------------------------------
//
//  File:       nImOwatchThread.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a thread to transfer information from nImO to a window.
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
//  Created:    2026-09-27
//
//--------------------------------------------------------------------------------------------------

#include "nImOwatchThread.h"
#include "nImOwatchWindow.h"

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <Containers/nImOstringBuffer.h>
#include <nImOmainSupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a thread to transfer information from #nImO to a window. */
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

std::atomic_bool    nImO::gWatchThreadStop;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::WatchThread::WatchThread
    (nImO::ReceiveQueue &   theQueue,
     Ptr(QObject)           parent) :
        inherited(parent), _receiveQueue(theQueue)
{
    ODL_ENTER(); //####
    ODL_P2(&theQueue, parent); //####
    ODL_EXIT_P(this); //####
}   // nImO::WatcherThread::WatcherThread

nImO::WatchThread::~WatchThread
    (void)
{
    ODL_ENTER(); //####
    ODL_EXIT(); //####
}   // nImO::WatcherThread::~WatcherThread

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::WatchThread::run
    (void)
{
    ODL_ENTER(); //####
    auto    theWindow{ReinterpretCast(Ptr(WatchWindow), parent())};

    for ( ; nImO::gKeepRunning && (! gWatchThreadStop); )
    {
        if (_receiveQueue.hasMessage())
        {
            auto    nextData{_receiveQueue.getNextMessage()};
            auto    tag{nextData->_tag};
            bool    processThisMessage;

            switch (tag)
            {
                case kMessageFromLog :
                    processThisMessage = theWindow->isWatchLogChecked();
                    break;

                case kMessageFromRegistrySearch :
                    processThisMessage = theWindow->isWatchRegistrySearchChecked();
                    break;

                case kMessageFromStatus :
                    processThisMessage = theWindow->isWatchStatusChecked();
                    break;

                default :
                    processThisMessage = false;
                    break;

            }
            if (nImO::gKeepRunning && processThisMessage && (! gWatchThreadStop))
            {
                time_t              rawTime;
                std::string         nowAsString;
                BAIP::address_v4    sender{nextData->_receivedAddress};
                char                timeBuffer[80];
                auto                addressString{"["s + sender.to_string() + "]"s};
                nImO::StringBuffer  aLine;
                nImO::StringBuffer  bLine;

                time(&rawTime);
                strftime(timeBuffer, sizeof(timeBuffer), "@%F/%T ", localtime(&rawTime));
                if (auto asMap{nextData->_receivedMessage->asMap()}; nullptr == asMap)
                {
                    // 'old' style or a status message
                    if (auto asArray{nextData->_receivedMessage->asArray()}; nullptr == asArray)
                    {
                        aLine.addString(addressString);
                        aLine.addString(timeBuffer);
                        if (auto asString{nextData->_receivedMessage->asString()}; nullptr == asString)
                        {
                            nextData->_receivedMessage->printToStringBuffer(bLine);
                            aLine.addBuffer(bLine);
                            bLine.reset();
                        }
                        else
                        {
                            aLine.addString(asString->getValue());
                        }
                        emit addLine(aLine.getString().c_str());
                    }
                    else
                    {
                        for (size_t ii{0}, numElements{asArray->size()}; ii < numElements; ++ii)
                        {
                            auto    element{asArray->at(ii)};

                            aLine.addString(addressString);
                            aLine.addString(timeBuffer);
                            if (auto asString{element->asString()}; nullptr == asString)
                            {
                                element->printToStringBuffer(bLine);
                                aLine.addBuffer(bLine);
                                bLine.reset();
                            }
                            else
                            {
                                aLine.addString(asString->getValue());
                            }
                            emit addLine(aLine.getString().c_str());
                            aLine.reset();
                        }
                    }
                }
                else
                {
                    auto            commandPortKey{std::make_shared<nImO::String>(nImO::kCommandPortKey)};
                    auto            computerNameKey{std::make_shared<nImO::String>(nImO::kComputerNameKey)};
                    auto            tagKey{std::make_shared<nImO::String>(nImO::kTagKey)};
                    auto            messageKey{std::make_shared<nImO::String>(nImO::kMessageKey)};
                    // Get the computer name
                    nImO::SpValue   theComputerName;
                    nImO::SpValue   theCommandPort;
                    nImO::SpValue   theTag;

                    if (auto anIterator{asMap->find(computerNameKey)}; anIterator == asMap->end())
                    {
                        theComputerName = nullptr;
                    }
                    else
                    {
                        theComputerName = anIterator->second;
                    }
                    // Get the command port
                    if (auto anIterator{asMap->find(commandPortKey)}; anIterator == asMap->end())
                    {
                        theCommandPort = nullptr;
                    }
                    else
                    {
                        theCommandPort = anIterator->second;
                    }
                    // Get the tag
                    if (auto anIterator{asMap->find(tagKey)}; anIterator == asMap->end())
                    {
                        theTag = nullptr;
                    }
                    else
                    {
                        theTag = anIterator->second;
                    }
                    // Get the message
                    if (auto anIterator{asMap->find(messageKey)}; anIterator != asMap->end())
                    {
                        auto        theMessage{anIterator->second};
                        std::string tagText;
                        std::string computerNameText;
                        std::string commandPortText;

                        if (theTag)
                        {
                            if (auto asString{theTag->asString()}; nullptr != asString)
                            {
                                tagText = "#"s + asString->getValue();
                            }
                        }
                        if (theComputerName)
                        {
                            if (auto asString{theComputerName->asString()}; nullptr != asString)
                            {
                                computerNameText = asString->getValue();
                            }
                        }
                        if (theCommandPort)
                        {
                            if (auto asInteger{theCommandPort->asInteger()}; nullptr != asInteger)
                            {
                                commandPortText = "-"s + std::to_string(asInteger->getIntegerValue());
                            }
                        }
                        auto    prefix{addressString + computerNameText + tagText + commandPortText + timeBuffer};

                        if (auto asArray{theMessage->asArray()}; nullptr == asArray)
                        {
                            aLine.addString(prefix);
                            if (auto asString{theMessage->asString()}; nullptr == asString)
                            {
                                theMessage->printToStringBuffer(bLine);
                                aLine.addBuffer(bLine);
                                bLine.reset();
                            }
                            else
                            {
                                aLine.addString(asString->getValue());
                            }
                            emit addLine(aLine.getString().c_str());
                        }
                        else
                        {
                            for (size_t ii{0}, numElements{asArray->size()}; ii < numElements; ++ii)
                            {
                                auto    element{asArray->at(ii)};

                                aLine.addString(prefix);
                                if (auto asString{element->asString()}; nullptr == asString)
                                {
                                    element->printToStringBuffer(bLine);
                                    aLine.addBuffer(bLine);
                                    bLine.reset();
                                }
                                else
                                {
                                    aLine.addString(asString->getValue());
                                }
                                emit addLine(aLine.getString().c_str());
                                aLine.reset();
                            }
                        }
                    }
                }
                nextData.reset();               
            }
        }
        else
        {
            yieldCurrentThread();
        }
    }
    ODL_EXIT(); //####
}   // nImO::WatchThread::run

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

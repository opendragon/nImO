//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOreceiveQueue.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for data used with nImO network receivers.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-01-03
//
//--------------------------------------------------------------------------------------------------

#include <nImOreceiveQueue.h>

#include <Containers/nImOmessage.h>
#include <nImOmainSupport.h>
#include <nImOMIMESupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for data used with %nImO network receivers. */
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

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::ReceiveQueue::addRawBytesAsMessage
    (const int              tag,
     const IPv4Address      senderAddress,
     const IPv4Port         senderPort,
     const std::string &    receivedAsString)
{
    ODL_OBJENTER(); //####
    if (! _stop)
    {
        ByteVector  inBytes;

        // We need to convert the raw data to a string!
        if (DecodeMIMEToBytes(receivedAsString, inBytes))
        {
            auto    newMessage{std::make_shared<Message>()};

            newMessage->open(false);
            newMessage->appendBytes(inBytes.data(), inBytes.size());
            auto newData{std::make_shared<ReceivedData>(tag, newMessage->getValue(), senderAddress, senderPort)};

            {
                std::lock_guard<std::mutex>  lock{_receivedLock};

                _receivedData.push_back(newData);
            }
            newMessage->close();
            _receivedCondition.notify_one();
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ReceiveQueue::addRawBytesAsMessage

nImO::SpReceivedData
nImO::ReceiveQueue::getNextMessage
    (void)
{
    ODL_OBJENTER(); //####
    SpReceivedData  nextMessage;

    boost::this_thread::yield();
    {
        // Check for messages.
        std::unique_lock<std::mutex>    lock{_receivedLock};

        for ( ; (! _stop) && gKeepRunning && (0 == _receivedData.size()); )
        {
            boost::this_thread::yield();
            _receivedCondition.wait(lock);
        }
        if ((! _stop) && gKeepRunning)
        {
            nextMessage = _receivedData.front();
            _receivedData.pop_front();
        }
    }
    ODL_OBJEXIT_P(nextMessage.get()); //####
    return nextMessage;
} // nImO::ReceiveQueue::getNextMessage

void
nImO::ReceiveQueue::stop
    (void)
{
    _stop = true;
    {
        std::lock_guard<std::mutex>  lock{_receivedLock};

        _receivedData.clear();
    }
    _receivedCondition.notify_one();
} // nImO::ReceiveQueue::stop

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

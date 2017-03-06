//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOmessage.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a message.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-04-24
//
//--------------------------------------------------------------------------------------------------

#include "nImOmessage.hpp"

#include <nImO/nImOarray.hpp>
#include <nImO/nImObufferChunk.hpp>
#include <nImO/nImOinvalid.hpp>
#include <nImO/nImOlogical.hpp>
#include <nImO/nImOvalue.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#include <inttypes.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a message. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace nImO;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The lead byte for an empty Message. */
static const DataKind kInitEmptyMessageValue = (nImO::DataKind::StartOfMessageValue |
                                                nImO::DataKind::OtherMessageEmptyValue);

/*! @brief The mask byte for checking lead/trailing bytes for Messages. */
static const DataKind kInitTermMessageMask = (nImO::DataKind::Mask |
                                              nImO::DataKind::OtherTypeMask |
                                              nImO::DataKind::OtherMessageStartEndMask |
                                              nImO::DataKind::OtherMessageEmptyMask);

/*! @brief The trailing byte for an empty Message. */
static const DataKind kTermEmptyMessageValue = (nImO::DataKind::EndOfMessageValue |
                                                nImO::DataKind::OtherMessageEmptyValue);

/*! @brief The lead byte for a non-empty Message. */
static const DataKind kInitNonEmptyMessageValue = (nImO::DataKind::StartOfMessageValue |
                                                   nImO::DataKind::OtherMessageNonEmptyValue);

/*! @brief The trailing byte for a non-empty Message. */
static const DataKind kTermNonEmptyMessageValue = (nImO::DataKind::EndOfMessageValue |
                                                   nImO::DataKind::OtherMessageNonEmptyValue);

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

nImO::Message::Message(void) :
    inherited(false), _cachedTransmissionString(), _readPosition(0), _state(MessageState::Unknown),
    _headerAdded(false)
{
    ODL_ENTER(); //####
    ODL_LL2("_readPosition <- ", _readPosition, "_state <- ", toUType(_state)); //####
    ODL_B1("_headerAdded <- ", _headerAdded); //####
    ODL_EXIT_P(this); //####
} // nImO::Message::Message

nImO::Message::~Message(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Message::~Message

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Message::appendBytes(const uint8_t *data,
                           const size_t  numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1("data = ", data); //####
    ODL_LL1("numBytes = ", numBytes); //####
    // Invalidate the cache.
    _cachedTransmissionString.clear();
    inherited::appendBytes(data, numBytes);
    ODL_OBJEXIT(); //####
} // nImO::Message::appendBytes

nImO::Message &
nImO::Message::close(void)
{
    ODL_OBJENTER(); //####
    switch (_state)
    {
    case MessageState::OpenForReading :
        // TBD
        break;

    case MessageState::OpenForWriting :
        if (! _headerAdded)
        {
            static const DataKind emptyMessage[] =
            {
                DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
            };
            const size_t emptyMessageLength = (sizeof(emptyMessage) / sizeof(*emptyMessage));

            appendBytes(emptyMessage, emptyMessageLength);
        }
        break;

    default :
        break;

    }
    _state = MessageState::Closed;
    ODL_LL1("_state <- ", toUType(_state)); //####
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::close

std::string
nImO::Message::getBytes(void)
{
    ODL_OBJENTER(); //####
    std::string result;

    if (MessageState::Closed == _state)
    {
        ODL_LOG("(MessageState::Closed == _state)"); //####
        lock();
        result = inherited::getBytes();
        unlock();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Message:getBytes

std::string
nImO::Message::getBytesForTransmission(void)
{
    ODL_OBJENTER(); //####
    if (0 == _cachedTransmissionString.size())
    {
        ODL_LOG("(0 == _cachedTransmissionString.size())"); //####
        auto   intermediate(getBytes());
        size_t length = intermediate.size();
        
        if (1 < length)
        {
            ODL_LOG("(intermediate && (1 < length))"); //####
            // First, check that the buffer starts correctly.
            if (DataKind::StartOfMessageValue == (intermediate[0] & DataKind::StartOfMessageMask))
            {
                // Next, count the number of bytes that will need to be escaped, and generate the
                // byte sum.
                uint64_t sum = intermediate[0];
                size_t   escapeCount = 0;
                
                for (size_t ii = 1; ii < length; ++ii)
                {
                    uint8_t aByte = intermediate[ii];
                    
                    sum += aByte;
                    if ((DataKind::StartOfMessageValue == (aByte & DataKind::StartOfMessageMask)) ||
                        (DataKind::EscapeValue == static_cast<DataKind>(aByte)))
                    {
                        ++escapeCount;
                    }
                }
                // Calculate the checksum byte and correct the escape and start counts if it will
                // need to be escaped.
                uint8_t checkSum = static_cast<uint8_t>(0x00FF & ~sum);
                ODL_XL2("sum = ", sum, "checkSum = ", checkSum); //####

                if ((DataKind::StartOfMessageValue == (checkSum & DataKind::StartOfMessageMask)) ||
                    (DataKind::EscapeValue == static_cast<DataKind>(checkSum)))
                {
                    ++escapeCount;
                }
                ODL_LL1("escapeCount = ", escapeCount); //####
                _cachedTransmissionString.reserve(length + escapeCount + 1);
                // Copy the start-of-message byte to the new set of bytes.
                _cachedTransmissionString += intermediate[0];
                for (size_t ii = 1; ii < length; ++ii)
                {
                    uint8_t aByte = intermediate[ii];
                    
                    if ((DataKind::StartOfMessageValue == (aByte & DataKind::StartOfMessageMask)) ||
                        (DataKind::EscapeValue == static_cast<DataKind>(aByte)))
                    {
                        _cachedTransmissionString += toUType(DataKind::EscapeValue);
                        _cachedTransmissionString += (aByte ^ 0x0080);
                    }
                    else
                    {
                        _cachedTransmissionString += aByte;
                    }
                }
                // Copy the checksum to the end of the new set of bytes.
                if ((DataKind::StartOfMessageValue == (checkSum & DataKind::StartOfMessageMask)) ||
                    (DataKind::EscapeValue == static_cast<DataKind>(checkSum)))
                {
                    _cachedTransmissionString += toUType(DataKind::EscapeValue);
                    _cachedTransmissionString += (checkSum ^ 0x0080);
                }
                else
                {
                    _cachedTransmissionString += checkSum;
                }
            }
            else
            {
                ODL_LOG("! (DataKind::StartOfMessageValue == (*intermediate & " //####
                        "DataKind::StartOfMessageMask))"); //####
            }
        }
        else
        {
            ODL_LOG("! (1 < length)"); //####
        }
    }
    ODL_PACKET("_cachedTransmissionString", _cachedTransmissionString.data(), //####
               _cachedTransmissionString.size()); //####
    ODL_OBJEXIT(); //####
    return _cachedTransmissionString;
} // nImO::Message::getBytesForTransmission

size_t
nImO::Message::getLength(void)
const
{
    ODL_OBJENTER(); //####
    size_t totalLength;

    if (MessageState::Closed == _state)
    {
        ODL_LOG("(MessageState::Closed == _state)"); //####
        totalLength = inherited::getLength();
    }
    else
    {
        ODL_LOG("! (MessageState::Closed == _state)"); //####
        totalLength = 0;
    }
    ODL_OBJEXIT_LL(totalLength); //####
    return totalLength;
} // nImO::Message::getLength

nImO::SpValue
nImO::Message::getValue(void)
{
    ODL_OBJENTER(); //####
    SpValue result;

    if (MessageState::OpenForReading == _state)
    {
        ODL_LOG("(MessageState::OpenForReading == _state)"); //####
        size_t savedPosition = _readPosition;
        bool   atEnd;
        int    aByte = getByte(_readPosition, atEnd);

        ODL_XL1("aByte <- ", aByte); //####
        ODL_B1("atEnd <- ", atEnd); //####
        if (atEnd)
        {
            ODL_LOG("(atEnd)"); //####
            _readPosition = savedPosition;
            ODL_LL1("_readPosition <- ", _readPosition); //####
        }
        else
        {
            if (kInitEmptyMessageValue == (aByte & kInitTermMessageMask))
            {
                aByte = getByte(++_readPosition, atEnd);
                ODL_LL2("aByte <- ", aByte, "_readPosition <- ", _readPosition); //####
                ODL_B1("atEnd <- ", atEnd); //####
                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    _readPosition = savedPosition;
                    ODL_LL1("_readPosition <- ", _readPosition); //####
                }
                else if (kTermEmptyMessageValue == (aByte & kInitTermMessageMask))
                {
                    // Step to the next byte.
                    ++_readPosition;
                    ODL_LL1("_readPosition <- ", _readPosition); //####
                }
                else
                {
                    ODL_LOG("! (kTermEmptyMessageValue == (aByte & kInitTermMessageMask))"); //####
                    result.reset(new Invalid("Empty Message with incorrect end tag @",
                                             _readPosition));
                }
            }
            else if (kInitNonEmptyMessageValue == (aByte & kInitTermMessageMask))
            {
                DataKind initTag = (aByte & DataKind::OtherMessageExpectedTypeMask);

                ODL_XL1("initTag <- ", toUType(initTag)); //####
                aByte = getByte(++_readPosition, atEnd);
                ODL_LL2("aByte <- ", aByte, "_readPosition <- ", _readPosition); //####
                ODL_B1("atEnd <- ", atEnd); //####
                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    _readPosition = savedPosition;
                    ODL_LL1("_readPosition <- ", _readPosition); //####
                }
                else
                {
                    ODL_LOG("! (atEnd)"); //####
                    DataKind nextTag = ((aByte >>
                                          toUType(DataKind::OtherMessageExpectedTypeShift)) &
                                        DataKind::OtherMessageExpectedTypeMask);

                    ODL_XL1("nextTag <- ", toUType(nextTag)); //####
                    if (nextTag == initTag)
                    {
                        result = Value::getValueFromMessage(*this, _readPosition, aByte, nullptr);
                        ODL_P1("result <- ", result.get()); //####
                        ODL_LL2("_readPosition <- ", _readPosition, "status <- ", //####
                                toUType(status)); //####
                        if (nullptr == result)
                        {
                            result.reset(new Invalid("Null Value read @", _readPosition));
                        }
                        else if (! result->asFlaw())
                        {
                            ODL_LOG("(! result->asFlaw())"); //####
                            aByte = getByte(_readPosition, atEnd);
                            ODL_XL1("aByte <- ", aByte); //####
                            ODL_B1("atEnd <- ", atEnd); //####
                            if (atEnd)
                            {
                                ODL_LOG("(atEnd)"); //####
                                _readPosition = savedPosition;
                                ODL_LL1("_readPosition <- ", _readPosition); //####
                                result.reset();
                                ODL_P1("result <- ", result.get()); //####
                            }
                            else if (kTermNonEmptyMessageValue == (aByte & kInitTermMessageMask))
                            {
                                nextTag = (aByte & DataKind::OtherMessageExpectedTypeMask);
                                ODL_XL1("nextTag <- ", toUType(nextTag)); //####
                                if (nextTag == initTag)
                                {
                                    // Step to the next byte.
                                    ++_readPosition;
                                }
                                else
                                {
                                    ODL_LOG("! (nextTag == initTag)"); //####
                                    result.reset(new Invalid("Message with mismatched end Value "
                                                             "tag @", _readPosition));
                                }
                            }
                            else
                            {
                                ODL_LOG("! (kTermNonEmptyMessageValue == " //####
                                        "(aByte & kInitTermMessageMask))"); //####
                                result.reset(new Invalid("Message with incorrect end tag @",
                                                         _readPosition));
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (nextTag == initTag)"); //####
                        result.reset(new Invalid("Message with mismatched initial Value tag @",
                                                 _readPosition));
                    }
                }
            }
            else
            {
                ODL_LOG("! (kInitNonEmptyMessageValue == (aByte & kInitTermMessageMask))"); //####
                result.reset(new Invalid("Message with incorrect start tag @", _readPosition));
            }
        }
    }
    else
    {
        ODL_LOG("! (MessageState::OpenForReading == _state)"); //####
        result.reset(new Invalid("Message is not open for reading"));
    }
    ODL_OBJEXIT_P(result.get()); //####
    return result;
} // nImO::Message::getValue

void
nImO::Message::lock(void)
{
    ODL_OBJENTER(); //####
//TBD
    ODL_OBJEXIT(); //####
} // nImO::Message::lock

nImO::Message &
nImO::Message::open(const bool forWriting)
{
    ODL_OBJENTER(); //####
    ODL_B1("forWriting = ", forWriting); //####
    if (forWriting)
    {
        _state = MessageState::OpenForWriting;
    }
    else
    {
        _state = MessageState::OpenForReading;
    }
    ODL_LL1("_state <- ", toUType(_state)); //####
    reset();
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::open

nImO::ChunkArray &
nImO::Message::reset(void)
{
    ODL_OBJENTER(); //####
    // Invalidate the cache.
    _cachedTransmissionString.clear();
    lock();
    inherited::reset();
    _headerAdded = false;
    ODL_B1("_headerAdded -> ", _headerAdded); //####
    _readPosition = 0;
    ODL_LL1("_readPosition <- ", _readPosition); //####
    unlock();
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::reset

nImO::Message &
nImO::Message::setValue(const nImO::Value &theValue)
{
    ODL_OBJENTER(); //####
    ODL_P1("theValue = ", &theValue); //####
    reset();
    if (MessageState::OpenForWriting == _state)
    {
        ODL_LOG("(MessageState::OpenForWriting == _state)"); //####
        lock();
        DataKind typeTag = theValue.getTypeTag();
        DataKind headerByte = (DataKind::StartOfMessageValue |
                               DataKind::OtherMessageNonEmptyValue | typeTag);
        DataKind trailerByte = (DataKind::EndOfMessageValue |
                                DataKind::OtherMessageNonEmptyValue | typeTag);

        appendBytes(&headerByte, sizeof(headerByte));
        _headerAdded = true;
        ODL_B1("_headerAdded <- ", _headerAdded); //####
        theValue.writeToMessage(*this);
        appendBytes(&trailerByte, sizeof(trailerByte));
        unlock();
    }
    else
    {
        ODL_LOG("! (MessageState::OpenForWriting == _state)"); //####
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::setValue

void
nImO::Message::unlock(void)
{
    ODL_OBJENTER(); //####
//TBD
    ODL_OBJEXIT(); //####
} // nImO::Message::unlock

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

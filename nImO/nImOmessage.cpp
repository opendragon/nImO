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

#include <nImOmessage.h>

#include <nImOarray.h>
#include <nImObufferChunk.h>
#include <nImOinvalid.h>
#include <nImOlogical.h>
#include <nImOMIMESupport.h>
#include <nImOvalue.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#include <inttypes.h>

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
static const DataKind   kInitEmptyMessageValue = (nImO::DataKind::StartOfMessageValue |
                                                  nImO::DataKind::OtherMessageEmptyValue);

/*! @brief The mask byte for checking lead/trailing bytes for Messages. */
static const DataKind   kInitTermMessageMask = (nImO::DataKind::Mask |
                                                nImO::DataKind::OtherTypeMask |
                                                nImO::DataKind::OtherMessageStartEndMask |
                                                nImO::DataKind::OtherMessageEmptyMask);

/*! @brief The trailing byte for an empty Message. */
static const DataKind   kTermEmptyMessageValue = (nImO::DataKind::EndOfMessageValue |
                                                  nImO::DataKind::OtherMessageEmptyValue);

/*! @brief The lead byte for a non-empty Message. */
static const DataKind   kInitNonEmptyMessageValue = (nImO::DataKind::StartOfMessageValue |
                                                     nImO::DataKind::OtherMessageNonEmptyValue);

/*! @brief The trailing byte for a non-empty Message. */
static const DataKind   kTermNonEmptyMessageValue = (nImO::DataKind::EndOfMessageValue |
                                                     nImO::DataKind::OtherMessageNonEmptyValue);

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

const std::string   nImO::kMessageSentinel{MIME_MESSAGE_TERMINATOR_};

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Message::Message
    (void) :
        inherited(false), _lock(), _cachedTransmissionString(), _readPosition(0),
        _state(MessageState::Unknown), _headerAdded(false)
{
    ODL_ENTER(); //####
    ODL_I2("_readPosition <- ", _readPosition, "_state <- ", toUType(_state)); //####
    ODL_B1("_headerAdded <- ", _headerAdded); //####
    ODL_EXIT_P(this); //####
} // nImO::Message::Message

nImO::Message::Message
    (Message && other)
    noexcept :
        inherited(std::move(other)), _lock(), _cachedTransmissionString(other._cachedTransmissionString),
        _readPosition(other._readPosition), _state(other._state), _headerAdded(other._headerAdded)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_I2("_readPosition <- ", _readPosition, "_state <- ", toUType(_state)); //####
    ODL_B1("_headerAdded <- ", _headerAdded); //####
    other._cachedTransmissionString = "";
    other._readPosition = 0;
    other._state = MessageState::Unknown;
    other._headerAdded = false;
    ODL_EXIT_P(this); //####
} // nImO::Message::Message

nImO::Message::~Message
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Message::~Message

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Message::appendBytes
    (CPtr(uint8_t)  data,
     const size_t   numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1("data = ", data); //####
    ODL_I1("numBytes = ", numBytes); //####
    ODL_PACKET("data", data, numBytes); //####
    // Invalidate the cache.
    _cachedTransmissionString.clear();
    inherited::appendBytes(data, numBytes);
    ODL_OBJEXIT(); //####
} // nImO::Message::appendBytes

nImO::Message &
nImO::Message::close
    (void)
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
                static const DataKind   emptyMessage[]
                {
                    DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                    DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
                };
                const size_t    emptyMessageLength{A_SIZE(emptyMessage)};

                appendBytes(emptyMessage, emptyMessageLength);
            }
            break;

        default :
            break;

    }
    _state = MessageState::Closed;
    ODL_I1("_state <- ", toUType(_state)); //####
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::close

std::string
nImO::Message::getBytes
    (void)
{
    std::string result;

    ODL_OBJENTER(); //####
    if (MessageState::Closed == _state)
    {
        ODL_LOG("(MessageState::Closed == _state)"); //####
        std::lock_guard<std::mutex> guard(_lock);

        result = inherited::getBytes();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Message:getBytes

size_t
nImO::Message::getLength
    (void)
    const
{
    size_t  totalLength;

    ODL_OBJENTER(); //####
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
    ODL_OBJEXIT_I(totalLength); //####
    return totalLength;
} // nImO::Message::getLength

nImO::SpValue
nImO::Message::getValue
    (const bool allowClosed)
{
    SpValue result;

    ODL_OBJENTER(); //####
    ODL_B1("allowClosed = ", allowClosed); //####
    if ((MessageState::OpenForReading == _state) || (allowClosed && (MessageState::Closed == _state)))
    {
        ODL_LOG("((MessageState::OpenForReading == _state) || (allowClosed && " //####
                "(MessageState::Closed == _state)))"); //####
        size_t  savedPosition = _readPosition;
        bool    atEnd;
        int     aByte = getByte(_readPosition, atEnd);

        ODL_X1("aByte <- ", aByte); //####
        ODL_B1("atEnd <- ", atEnd); //####
        if (atEnd)
        {
            ODL_LOG("(atEnd)"); //####
            _readPosition = savedPosition;
            ODL_I1("_readPosition <- ", _readPosition); //####
        }
        else
        {
            if (kInitEmptyMessageValue == (aByte & kInitTermMessageMask))
            {
                aByte = getByte(++_readPosition, atEnd);
                ODL_I2("aByte <- ", aByte, "_readPosition <- ", _readPosition); //####
                ODL_B1("atEnd <- ", atEnd); //####
                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    _readPosition = savedPosition;
                    ODL_I1("_readPosition <- ", _readPosition); //####
                }
                else if (kTermEmptyMessageValue == (aByte & kInitTermMessageMask))
                {
                    // Step to the next byte.
                    ++_readPosition;
                    ODL_I1("_readPosition <- ", _readPosition); //####
                }
                else
                {
                    ODL_LOG("! (kTermEmptyMessageValue == (aByte & kInitTermMessageMask))"); //####
                    result.reset(new Invalid("Empty Message with incorrect end tag", _readPosition));
                }
            }
            else if (kInitNonEmptyMessageValue == (aByte & kInitTermMessageMask))
            {
                DataKind    initTag = (aByte & DataKind::OtherMessageExpectedTypeMask);

                ODL_X1("initTag <- ", toUType(initTag)); //####
                aByte = getByte(++_readPosition, atEnd);
                ODL_I2("aByte <- ", aByte, "_readPosition <- ", _readPosition); //####
                ODL_B1("atEnd <- ", atEnd); //####
                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    _readPosition = savedPosition;
                    ODL_I1("_readPosition <- ", _readPosition); //####
                }
                else
                {
                    ODL_LOG("! (atEnd)"); //####
                    DataKind    nextTag = ((aByte >> toUType(DataKind::OtherMessageExpectedTypeShift)) &
                                           DataKind::OtherMessageExpectedTypeMask);

                    ODL_X1("nextTag <- ", toUType(nextTag)); //####
                    if (nextTag == initTag)
                    {
                        result = Value::getValueFromMessage(*this, _readPosition, aByte, nullptr);
                        ODL_P1("result <- ", result.get()); //####
                        ODL_I1("_readPosition <- ", _readPosition); //####
                        if (nullptr == result)
                        {
                            result.reset(new Invalid("Null Value read", _readPosition));
                        }
                        else if (! result->asFlaw())
                        {
                            ODL_LOG("(! result->asFlaw())"); //####
                            aByte = getByte(_readPosition, atEnd);
                            ODL_X1("aByte <- ", aByte); //####
                            ODL_B1("atEnd <- ", atEnd); //####
                            if (atEnd)
                            {
                                ODL_LOG("(atEnd)"); //####
                                _readPosition = savedPosition;
                                ODL_I1("_readPosition <- ", _readPosition); //####
                                result.reset();
                                ODL_P1("result <- ", result.get()); //####
                            }
                            else if (kTermNonEmptyMessageValue == (aByte & kInitTermMessageMask))
                            {
                                nextTag = (aByte & DataKind::OtherMessageExpectedTypeMask);
                                ODL_X1("nextTag <- ", toUType(nextTag)); //####
                                if (nextTag == initTag)
                                {
                                    // Step to the next byte.
                                    ++_readPosition;
                                }
                                else
                                {
                                    ODL_LOG("! (nextTag == initTag)"); //####
                                    result.reset(new Invalid("Message with mismatched end Value tag", _readPosition));
                                }
                            }
                            else
                            {
                                ODL_LOG("! (kTermNonEmptyMessageValue == " //####
                                        "(aByte & kInitTermMessageMask))"); //####
                                result.reset(new Invalid("Message with incorrect end tag", _readPosition));
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (nextTag == initTag)"); //####
                        result.reset(new Invalid("Message with mismatched initial Value tag", _readPosition));
                    }
                }
            }
            else
            {
                ODL_LOG("! (kInitNonEmptyMessageValue == (aByte & kInitTermMessageMask))"); //####
                result.reset(new Invalid("Message with incorrect start tag", _readPosition));
            }
        }
    }
    else
    {
        ODL_LOG("! ((MessageState::OpenForReading == _state) || (allowClosed && " //####
                "(MessageState::Closed == _state)))"); //####
        result.reset(new Invalid("Message is not open for reading or is not closed"));
    }
    ODL_OBJEXIT_P(result.get()); //####
    return result;
} // nImO::Message::getValue

nImO::Message &
nImO::Message::open
    (const bool forWriting)
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
    reset();
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::open

nImO::Message &
nImO::Message::operator=
    (Message && other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _cachedTransmissionString = other._cachedTransmissionString;
        _readPosition = other._readPosition;
        _state = other._state;
        _headerAdded = other._headerAdded;
        other._cachedTransmissionString = "";
        other._readPosition = 0;
        other._state = MessageState::Unknown;
        other._headerAdded = false;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::operator=

nImO::ChunkArray &
nImO::Message::reset
    (void)
{
    ODL_OBJENTER(); //####
    // Invalidate the cache.
    _cachedTransmissionString.clear();
    std::lock_guard<std::mutex> guard(_lock);

    inherited::reset();
    _headerAdded = false;
    ODL_B1("_headerAdded -> ", _headerAdded); //####
    _readPosition = 0;
    ODL_I1("_readPosition <- ", _readPosition); //####
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::reset

nImO::Message &
nImO::Message::setValue
    (SpValue    theValue)
{
    ODL_OBJENTER(); //####
    ODL_P1("theValue = ", theValue.get()); //####
    reset();
    if (MessageState::OpenForWriting == _state)
    {
        ODL_LOG("(MessageState::OpenForWriting == _state)"); //####
        std::lock_guard<std::mutex> guard(_lock);

        DataKind    typeTag = theValue->getTypeTag();
        DataKind    headerByte = (DataKind::StartOfMessageValue | DataKind::OtherMessageNonEmptyValue | typeTag);
        DataKind    trailerByte = (DataKind::EndOfMessageValue | DataKind::OtherMessageNonEmptyValue | typeTag);

        appendBytes(&headerByte, sizeof(headerByte));
        _headerAdded = true;
        ODL_B1("_headerAdded <- ", _headerAdded); //####
        theValue->writeToMessage(*this);
        appendBytes(&trailerByte, sizeof(trailerByte));
    }
    else
    {
        ODL_LOG("! (MessageState::OpenForWriting == _state)"); //####
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::setValue

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

std::pair<BufferIterator, bool>
nImO::MatchMessageSeparator
    (BufferIterator begin,
     BufferIterator end)
{
    BufferIterator  ii = begin;

    for ( ; ii != end; )
    {
        std::string checker{ii++, end};

        if (checker == MIME_MESSAGE_TERMINATOR_)
        {
            return std::make_pair(ii, true);
        }
    }
    return std::make_pair(ii, false);
} // nImO::MatchMessageSeparator

std::shared_ptr<std::string>
nImO::PackageMessage
    (StringVector & outVec)
{
    return std::make_shared<std::string>(boost::algorithm::join(outVec, "\n") + "\n" + kMessageSentinel);
} // nImO::PackageMessage

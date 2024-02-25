//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOmessage.cpp
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

#include <Containers/nImOmessage.h>

#include <BasicTypes/nImOinvalid.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOvalue.h>
#include <Containers/nImOarray.h>
#include <Containers/nImObufferChunk.h>
#include <nImOMIMESupport.h>

#include <inttypes.h>
#include <string>

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
static const DataKind   kInitEmptyMessageValue{nImO::DataKind::StartOfMessageValue | nImO::DataKind::OtherMessageEmptyValue};

/*! @brief The mask byte for checking lead/trailing bytes for Messages. */
static const DataKind   kInitTermMessageMask{nImO::DataKind::Mask |
                                                nImO::DataKind::OtherTypeMask |
                                                nImO::DataKind::OtherMessageStartEndMask |
                                                nImO::DataKind::OtherMessageEmptyMask};

/*! @brief The trailing byte for an empty Message. */
static const DataKind   kTermEmptyMessageValue{nImO::DataKind::EndOfMessageValue | nImO::DataKind::OtherMessageEmptyValue};

/*! @brief The lead byte for a non-empty Message. */
static const DataKind   kInitNonEmptyMessageValue{nImO::DataKind::StartOfMessageValue | nImO::DataKind::OtherMessageNonEmptyValue};

/*! @brief The trailing byte for a non-empty Message. */
static const DataKind   kTermNonEmptyMessageValue{nImO::DataKind::EndOfMessageValue | nImO::DataKind::OtherMessageNonEmptyValue};

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

const std::string   nImO::kMessageSentinel{kMiMeMessageTerminator};

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
        inherited{false}, _lock{}
{
    ODL_ENTER(); //####
    ODL_I2("_readPosition <- ", _readPosition, "_state <- ", toUType(_state)); //####
    ODL_B1("_headerAdded <- ", _headerAdded); //####
    ODL_EXIT_P(this); //####
} // nImO::Message::Message

nImO::Message::Message
    (Message && other)
    noexcept :
        inherited{std::move(other)}, _lock{}, _cachedTransmissionString{std::move(other._cachedTransmissionString)},
        _readPosition{other._readPosition}, _state{other._state}, _headerAdded{other._headerAdded}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_I2("_readPosition <- ", _readPosition, "_state <- ", toUType(_state)); //####
    ODL_B1("_headerAdded <- ", _headerAdded); //####
    other._readPosition = 0;
    other._state = MessageState::Unknown;
    other._headerAdded = false;
    ODL_EXIT_P(this); //####
} // nImO::Message::Message

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
            break;

        case MessageState::OpenForWriting :
            if (! _headerAdded)
            {
                static const DataKind   emptyMessage[]
                {
                    DataKind::StartOfMessageValue | DataKind::OtherMessageEmptyValue,
                    DataKind::EndOfMessageValue | DataKind::OtherMessageEmptyValue
                };
                constexpr size_t    emptyMessageLength{numElementsInArray(emptyMessage)};

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
    ODL_OBJENTER(); //####
    std::string result;

    if (MessageState::Closed == _state)
    {
        ODL_LOG("(MessageState::Closed == _state)"); //####
        std::lock_guard<std::mutex> guard{_lock};

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
    ODL_OBJENTER(); //####
    size_t  totalLength;

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
    ODL_OBJENTER(); //####
    ODL_B1("allowClosed = ", allowClosed); //####
    SpValue result;

    if ((MessageState::OpenForReading == _state) || (allowClosed && (MessageState::Closed == _state)))
    {
        ODL_LOG("((MessageState::OpenForReading == _state) || (allowClosed && " //####
                "(MessageState::Closed == _state)))"); //####
        size_t  savedPosition{_readPosition};
        bool    atEnd;
        int     aByte{getByte(_readPosition, atEnd)};

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
                    result = std::make_shared<Invalid>("Empty Message with incorrect end tag", _readPosition);
                }
            }
            else if (kInitNonEmptyMessageValue == (aByte & kInitTermMessageMask))
            {
                DataKind    initTag{aByte & DataKind::OtherMessageExpectedTypeMask};

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
                    DataKind    nextTag{(aByte >> toUType(DataKind::OtherMessageExpectedTypeShift)) & DataKind::OtherMessageExpectedTypeMask};

                    ODL_X1("nextTag <- ", toUType(nextTag)); //####
                    if (nextTag == initTag)
                    {
                        result = Value::getValueFromMessage(*this, _readPosition, aByte, nullptr);
                        ODL_P1("result <- ", result.get()); //####
                        ODL_I1("_readPosition <- ", _readPosition); //####
                        if (result)
                        {
                            if (! result->asFlaw())
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
                                        result = std::make_shared<Invalid>("Message with mismatched end Value tag", _readPosition);
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (kTermNonEmptyMessageValue == " //####
                                            "(aByte & kInitTermMessageMask))"); //####
                                    result = std::make_shared<Invalid>("Message with incorrect end tag", _readPosition);
                                }
                            }
                        }
                        else
                        {
                            result = std::make_shared<Invalid>("Null Value read", _readPosition);
                        }
                    }
                    else
                    {
                        ODL_LOG("! (nextTag == initTag)"); //####
                        result = std::make_shared<Invalid>("Message with mismatched initial Value tag", _readPosition);
                    }
                }
            }
            else
            {
                ODL_LOG("! (kInitNonEmptyMessageValue == (aByte & kInitTermMessageMask))"); //####
                result = std::make_shared<Invalid>("Message with incorrect start tag", _readPosition);
            }
        }
    }
    else
    {
        ODL_LOG("! ((MessageState::OpenForReading == _state) || (allowClosed && " //####
                "(MessageState::Closed == _state)))"); //####
        result = std::make_shared<Invalid>("Message is not open for reading or is not closed");
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
        _cachedTransmissionString = std::move(other._cachedTransmissionString);
        _readPosition = other._readPosition;
        _state = other._state;
        _headerAdded = other._headerAdded;
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
    std::lock_guard<std::mutex> guard{_lock};

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
        std::lock_guard<std::mutex> guard{_lock};
        DataKind                    typeTag{theValue->getTypeTag()};
        DataKind                    headerByte{DataKind::StartOfMessageValue | DataKind::OtherMessageNonEmptyValue | typeTag};
        DataKind                    trailerByte{DataKind::EndOfMessageValue | DataKind::OtherMessageNonEmptyValue | typeTag};

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
    auto    ii{begin};

    for ( ; ii != end; )
    {
        std::string checker{ii++, end};

        if (kMiMeMessageTerminator == checker)
        {
            return std::make_pair(ii, true);
        }
    }
    return std::make_pair(ii, false);
} // nImO::MatchMessageSeparator

nImO::SpStdString
nImO::PackageMessage
    (StdStringVector &  outVec)
{
    return std::make_shared<std::string>(boost::algorithm::join(outVec, "\n"s) + "\n"s + kMessageSentinel);
} // nImO::PackageMessage

std::string
nImO::UnpackageMessage
    (const std::string &    inString)
{
    return inString.substr(0, inString.length() - (kMessageSentinel.length() + 1));
} // nImO::UnpackageMessage

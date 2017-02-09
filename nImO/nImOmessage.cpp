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
#include <nImO/nImOboolean.hpp>
#include <nImO/nImObufferChunk.hpp>
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
static const uint8_t kInitEmptyMessageValue = (nImO::kKindOther |
                                               nImO::kKindOtherMessage |
                                               nImO::kKindOtherMessageStartValue |
                                               nImO::kKindOtherMessageEmptyValue);

/*! @brief The mask byte for checking lead/trailing bytes for Messages. */
static const uint8_t kInitTermMessageMask = (nImO::kKindMask |
                                             nImO::kKindOtherTypeMask |
                                             nImO::kKindOtherMessageStartEndMask |
                                             nImO::kKindOtherMessageEmptyMask);

/*! @brief The trailing byte for an empty Message. */
static const uint8_t kTermEmptyMessageValue = (nImO::kKindOther |
                                               nImO::kKindOtherMessage |
                                               nImO::kKindOtherMessageEndValue |
                                               nImO::kKindOtherMessageEmptyValue);

/*! @brief The lead byte for a non-empty Message. */
static const uint8_t kInitNonEmptyMessageValue = (nImO::kKindOther |
                                                  nImO::kKindOtherMessage |
                                                  nImO::kKindOtherMessageStartValue |
                                                  nImO::kKindOtherMessageNonEmptyValue);

/*! @brief The trailing byte for a non-empty Message. */
static const uint8_t kTermNonEmptyMessageValue = (nImO::kKindOther |
                                                  nImO::kKindOtherMessage |
                                                  nImO::kKindOtherMessageEndValue |
                                                  nImO::kKindOtherMessageNonEmptyValue);

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
    inherited(false), _readPosition(0), _state(kMessageStateUnknown), _headerAdded(false)
{
    ODL_ENTER(); //####
    ODL_LL2("_readPosition <- ", _readPosition, "_state <- ", _state); //####
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

nImO::Message &
nImO::Message::close(void)
{
    ODL_OBJENTER(); //####
    switch (_state)
    {
    case kMessageStateOpenForReading :
        // TBD
        break;

    case kMessageStateOpenForWriting :
        if (! _headerAdded)
        {
            static const uint8_t emptyMessage[] =
            {
                kKindOther + kKindOtherMessage + kKindOtherMessageStartValue +
                  kKindOtherMessageEmptyValue,
                kKindOther + kKindOtherMessage + kKindOtherMessageEndValue +
                  kKindOtherMessageEmptyValue
            };
            const size_t emptyMessageLength = (sizeof(emptyMessage) / sizeof(*emptyMessage));

            appendBytes(emptyMessage, emptyMessageLength);
        }
        break;

    default :
        break;

    }
    _state = kMessageStateClosed;
    ODL_LL1("_state <- ", _state); //####
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::close

const uint8_t *
nImO::Message::getBytes(size_t &length)
{
    ODL_OBJENTER(); //####
    ODL_P1("length = ", &length); //####
    const uint8_t * result;

    if (kMessageStateClosed == _state)
    {
        ODL_LOG("(kMessageStateClosed == _state)"); //####
        lock();
        result = inherited::getBytes(length);
        unlock();
    }
    else
    {
        ODL_LOG("! (kMessageStateClosed == _state)"); //####
        result = NULL;
        length = 0;
        ODL_LL1("length <- ", length); //####
    }
    ODL_OBJEXIT_P(result); //####
    return result;
} // getBytes

size_t
nImO::Message::getLength(void)
const
{
    ODL_OBJENTER(); //####
    size_t totalLength;

    if (kMessageStateClosed == _state)
    {
        ODL_LOG("(kMessageStateClosed == _state)"); //####
        totalLength = inherited::getLength();
    }
    else
    {
        ODL_LOG("! (kMessageStateClosed == _state)"); //####
        totalLength = 0;
    }
    ODL_OBJEXIT_LL(totalLength); //####
    return totalLength;
} // nImO::Message::getLength

nImO::SpValue
nImO::Message::getValue(nImO::ReadStatus &status)
{
    ODL_OBJENTER(); //####
    ODL_P1("status = ", &status); //####
    SpValue result;

    if (kMessageStateOpenForReading == _state)
    {
        ODL_LOG("(kMessageStateOpenForReading == _state)"); //####
        size_t  savedPosition = _readPosition;
        int     aByte = getByte(_readPosition);

        ODL_XL1("aByte <- ", aByte); //#### 
        if (kEndToken == aByte)
        {
            ODL_LOG("(kEndToken == aByte)"); //####
            status = kReadIncomplete;
            _readPosition = savedPosition;
            ODL_LL2("status <- ", status, "_readPosition <- ", _readPosition); //####
        }
        else
        {
            if (kInitEmptyMessageValue == (aByte &kInitTermMessageMask))
            {
                aByte = getByte(++_readPosition);
                ODL_LL2("aByte <- ", aByte, "_readPosition <- ", _readPosition); //####
                if (kEndToken == aByte)
                {
                    ODL_LOG("(kEndToken == aByte)"); //####
                    status = kReadIncomplete;
                    _readPosition = savedPosition;
                    ODL_LL2("status <- ", status, "_readPosition <- ", _readPosition); //####
                }
                else if (kTermEmptyMessageValue == (aByte &kInitTermMessageMask))
                {
                    aByte = getByte(++_readPosition);
                    ODL_LL2("aByte <- ", aByte, "_readPosition <- ", _readPosition); //####
                    if (kEndToken == aByte)
                    {
                        ODL_LOG("(kEndToken == aByte)"); //####
                        status = kReadSuccessfulAtEnd;
                        ODL_LL1("status <- ", status); //####
                    }
                    else
                    {
                        ODL_LOG("! (kEndToken == aByte)"); //####
                        status = kReadSuccessful;
                        ODL_LL1("status <- ", status); //####
                    }
                }
                else
                {
                    ODL_LOG("! (kTermEmptyMessageValue == (aByte &kInitTermMessageMask))"); //####
                    status = kReadInvalid;
                    ODL_LL1("status <- ", status); //####
                }
            }
            else if (kInitNonEmptyMessageValue == (aByte &kInitTermMessageMask))
            {
                uint8_t initTag = (aByte &kKindOtherMessageExpectedTypeMask);

                ODL_XL1("initTag <- ", initTag); //####
                aByte = getByte(++_readPosition);
                ODL_LL2("aByte <- ", aByte, "_readPosition <- ", _readPosition); //####
                if (kEndToken == aByte)
                {
                    ODL_LOG("(kEndToken == aByte)"); //####
                    status = kReadIncomplete;
                    _readPosition = savedPosition;
                    ODL_LL2("status <- ", status, "_readPosition <- ", _readPosition); //####
                }
                else
                {
                    ODL_LOG("! (kEndToken == aByte)"); //####
                    uint8_t nextTag = ((aByte >> kKindOtherMessageExpectedTypeShift) &
                                       kKindOtherMessageExpectedTypeMask);

                    ODL_XL1("nextTag <- ", nextTag); //####
                    if (nextTag == initTag)
                    {
                        result = Value::getValueFromMessage(*this, _readPosition, aByte, status,
                                                            NULL);
                        ODL_P1("result <- ", result.get()); //####
                        ODL_LL2("_readPosition <- ", _readPosition, "status <- ", status); //####
                        if (NULL == result)
                        {
                            ODL_LOG("(NULL == result)"); //####
                        }
                        else
                        {
                            aByte = getByte(_readPosition);
                            ODL_XL1("aByte <- ", aByte); //####
                            if (kEndToken == aByte)
                            {
                                ODL_LOG("(kEndToken == aByte)"); //####
                                status = kReadIncomplete;
                                _readPosition = savedPosition;
                                ODL_LL2("status <- ", status, "_readPosition <- ", //####
                                        _readPosition); //####
                                result.reset();
                                ODL_P1("result <- ", result.get()); //####
                            }
                            else if (kTermNonEmptyMessageValue == (aByte &kInitTermMessageMask))
                            {
                                nextTag = (aByte &kKindOtherMessageExpectedTypeMask);
                                ODL_XL1("nextTag <- ", nextTag); //####
                                if (nextTag == initTag)
                                {
                                    aByte = getByte(++_readPosition);
                                    ODL_LL2("aByte <- ", aByte, "_readPosition <- ", //####
                                            _readPosition); //####
                                    if (kEndToken == aByte)
                                    {
                                        ODL_LOG("(kEndToken == aByte)"); //####
                                        status = kReadSuccessfulAtEnd;
                                        ODL_LL1("status <- ", status); //####
                                    }
                                    else
                                    {
                                        ODL_LOG("! (kEndToken == aByte)"); //####
                                        status = kReadSuccessful;
                                        ODL_LL1("status <- ", status); //####
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (nextTag == initTag)"); //####
                                    status = kReadInvalid;
                                    ODL_LL1("status <- ", status); //####
                                    result.reset();
                                    ODL_P1("result <- ", result.get()); //####
                                }
                            }
                            else
                            {
                                ODL_LOG("! (kTermNonEmptyMessageValue == " //####
                                        "(aByte &kInitTermMessageMask))"); //####
                                status = kReadInvalid;
                                ODL_LL1("status <- ", status); //####
                                result.reset();
                                ODL_P1("result <- ", result.get()); //####
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (nextTag == initTag)"); //####
                        status = kReadInvalid;
                        ODL_LL1("status <- ", status); //####
                    }
                }
            }
            else
            {
                ODL_LOG("! (kInitNonEmptyMessageValue == (aByte &kInitTermMessageMask))"); //####
                status = kReadInvalid;
                ODL_LL1("status <- ", status); //####
            }
        }
    }
    else
    {
        ODL_LOG("! (kMessageStateOpenForReading == _state)"); //####
        status = kReadInvalid;
        ODL_LL1("status <- ", status); //####
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
        _state = kMessageStateOpenForWriting;
    }
    else
    {
        _state = kMessageStateOpenForReading;
    }
    ODL_LL1("_state <- ", _state); //####
    reset();
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::open

nImO::ChunkArray &
nImO::Message::reset(void)
{
    ODL_OBJENTER(); //####
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
    if (kMessageStateOpenForWriting == _state)
    {
        ODL_LOG("(kMessageStateOpenForWriting == _state)"); //####
        lock();
        uint8_t typeTag = theValue.getTypeTag();
        uint8_t headerByte = kKindOther + kKindOtherMessage + kKindOtherMessageStartValue +
                             kKindOtherMessageNonEmptyValue + typeTag;
        uint8_t trailerByte = kKindOther + kKindOtherMessage + kKindOtherMessageEndValue +
                              kKindOtherMessageNonEmptyValue + typeTag;

        appendBytes(&headerByte, sizeof(headerByte));
        _headerAdded = true;
        ODL_B1("_headerAdded <- ", _headerAdded); //####
        theValue.writeToMessage(*this);
        appendBytes(&trailerByte, sizeof(trailerByte));
        unlock();
    }
    else
    {
        ODL_LOG("! (kMessageStateOpenForWriting == _state)"); //####
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

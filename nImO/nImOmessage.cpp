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

/*! @brief The tag values for message contents. */
enum DataKind
{
    /*! @brief The mask for the kind of data that follows. */
    kKindMask = 0x00C0,
    
    /*! @brief The data that follows is a signed integer value. */
    kKindSignedInteger = 0x0000,
    
        /*! @brief The mask for the size of the signed integer value. */
        kKindSignedIntegerSizeMask = 0x0020,
    
        /*! @brief The signed integer value is in the range -16..15 and is contained within this
         byte. */
        kKindSignedIntegerShortValue = 0x0000,
    
            /*! @brief The mask for the value of the signed integer. */
            kKindSignedIntegerShortValueValueMask = 0x001F,
    
        /*! @brief The signed integer value follows this byte. */
        kKindSignedIntegerLongValue = 0x0020,
    
            /*! @brief The mask for the count of the number of bytes (1..8) that contain the signed
             integer value.
             Note that the count contained in the byte is one less than the actual count. */
            kKindSignedIntegerLongValueCountMask = 0x0007,
    
    /*! @brief The data that follows is one or more floating-point values. */
    kKindFloatingPoint = 0x0040,
    
        /*! @brief The mask for the size of the floating-point values. */
        kKindFloatingPointSizeMask = 0x0020,
    
        /*! @brief The floating-point values are of type 'float' and occupy 32 bits. */
        kKindFloatingPointFloatValue = 0x0000,
    
        /*! @brief The floating-point values are of type 'double' and occupy 64 bits. */
        kKindFloatingPointDoubleValue = 0x0020,
    
        /*! @brief The mask for the size of the count of floating-point values. */
        kKindFloatingPointCountMask = 0x0010,
    
        /*! @brief The count of the number of floating-point values is in the range 1..16 and is
         contained within this byte.
         Note that the count contained in the byte is one less than the actual count. */
        kKindFloatingPointShortCount = 0x0000,
    
            /*! @brief The mask for the count of the number of floating-point values. */
            kKindFloatingPointShortCountMask = 0x000F,
    
        /*! @brief The count of the number of floating-point values is contained in the next byte(s)
         and the size of the count (1..8) is contained in this byte.
         Note that the size of the count contained in the byte is one less than the actual size of
         the count; the count itself is the actual count. */
        kKindFloatingPointLongCount = 0x0010,
    
            /*! @brief The mask for the size of the count of floating-point values. */
            kKindFloatingPointLongCountMask = 0x0007,
    
    /*! @brief The data that follows is a String or Blob. */
    kKindStringOrBlob = 0x0080,
    
        /*! @brief The mask for the type of data - String or Blob. */
        kKindStringOrBlobTypeMask = 0x0020,
    
        /*! @brief The data that follows is a non-@c NULL-terminated String. */
        kKindStringOrBlobStringValue = 0x0000,
    
        /*! @brief The data that follows is a Blob. */
        kKindStringOrBlobBlobValue = 0x0020,
    
        /*! @brief The mask for the length of the data that follows. */
        kKindStringOrBlobLengthMask = 0x0010,
    
        /*! @brief The length of the data is in the range 0..15 and is contained within this
         byte. */
        kKindStringOrBlobShortLengthValue = 0x0000,

            /*! @brief The mask for the length of the data. */
            kKindStringOrBlobShortLengthMask = 0x000F,
    
        /*! @brief The length of the data is contained in the next byte(s). */
        kKindStringOrBlobLongLengthValue = 0x0010,
    
            /*! @brief The mask for the count of the number of bytes (1..8) that contain the length
             of the data.
             Note that the count contained in the byte is one less than the actual count; the length
             is the actual length. */
            kKindStringOrBlobLongLengthMask = 0x0007,
    
    /*! @brief The data that follows is a Boolean or a Container. */
    kKindOther = 0x00C0,
    
        /*! @brief The mask for the type of value that follows. */
        kKindOtherTypeMask = 0x0030,
    
        /*! @brief The value is a Boolean. */
        kKindOtherBoolean = 0x0000,
    
            /*! @brief The mask for the value of the Boolean. */
            kKindOtherBooleanValueMask = 0x0001,
    
            /*! @brief The value is @c false. */
            kKindOtherBooleanFalseValue = 0x0000,
    
            /*! @brief The value is @c true. */
            kKindOtherBooleanTrueValue = 0x00001,
    
        /*! @brief The value that follows is a Container. */
        kKindOtherContainerStart = 0x0010,
    
        /*! @brief The value that preceeded this was a Container. */
        kKindOtherContainerEnd = 0x0020,
    
        /*! @brief The mask for the type of Container. */
        kKindOtherContainerTypeMask = 0x000C,
    
        /*! @brief The container is an Array. */
        kKindOtherContainerTypeArray = 0x0000,
    
        /*! @brief The container is a Map. */
        kKindOtherContainerTypeMap = 0x0004,
    
        /*! @brief The container is a Set. */
        kKindOtherContainerTypeSet = 0x0008,
    
        /*! @brief The mask for the empty / non-empty state of the Container. */
        kKindOtherContainerEmptyMask = 0x0001,
    
        /*! @brief The Container is empty; no count of the number of elements follows. */
        kKindOtherContainerEmptyValue = 0x0000,
    
        /*! @brief The Container is non-empty and the count of the number of elements follows, as a
         signed integer value. */
        kKindOtherContainerNonEmptyValue = 0x0001,
    
        /*! @brief The value that follows is a Message. */
        kKindOtherMessage = 0x0030,
    
            /*! @brief The mask for the start / end state of the Message. */
            kKindOtherMessageStartEndMask = 0x0008,
    
            /*! @brief The data that follows form a Message. */
            kKindOtherMessageStartValue = 0x0000,
    
            /*! @brief The data that preceeded this was a Message. */
            kKindOtherMessageEndValue = 0x0008,
    
            /*! @brief The mask for the empty / non-empty state of the Message. */
            kKindOtherMessageEmptyMask = 0x0004,
    
            /*! @brief The Message is empty. */
            kKindOtherMessageEmptyValue = 0x0000,
    
            /*! @brief The Message is non-empty; the type flag (top two-bits) of the first Value in
             the Message, if the start of the Message or of the last Value in the Message, if the
             end of the Message, is contained in the byte. */
            kKindOtherMessageNonEmptyValue = 0x0004,
    
            /*! @brief The mask for the type of the immediately enclosed Value in the Message - the
             first Value, if the start of the Message, and the last Value if the end of the
             Message. */
            kKindOtherMessageExpectedTypeMask = 0x0003
}; // DataKind

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
    _buffers(new BufferChunk *[1]), _cachedOutput(NULL), _numChunks(1)
{
    ODL_ENTER(); //####
    ODL_P2("_buffers <- ", _buffers, "_cachedOutput <- ", _cachedOutput); //####
    ODL_LL1("_numChunks <- ", _numChunks); //####
    *_buffers = new BufferChunk;
    ODL_EXIT_P(this); //####
} // nImO::Message::Message

nImO::Message::~Message(void)
{
    ODL_OBJENTER(); //####
    delete _cachedOutput;
    if (_buffers)
    {
        for (size_t ii = 0; _numChunks > ii; ++ii)
        {
            delete _buffers[ii];
        }
        delete _buffers;
    }
    ODL_OBJEXIT(); //####
} // nImO::Message::~Message

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if 0
nImO::Message &
nImO::Message::addBool(const bool aBool)
{
    ODL_OBJENTER(); //####
    ODL_B1("aBool = ", aBool); //####
    addString(Boolean::getCanonicalRepresentation(aBool));
    ODL_EXIT_P(this); //####
    return *this;
} // nImO::Message::addBool

nImO::Message &
nImO::Message::addBytes(const uint8_t * inBytes,
                        const size_t    numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1("inBytes = ", inBytes); //####
    ODL_LL1("numBytes = ", numBytes); //####
    static const char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    
    addChar(kBlobSeparator).addLong(numBytes).addChar(kBlobSeparator);
    for (size_t ii = 0; numBytes > ii; ++ii)
    {
        uint8_t aByte = inBytes[ii];
        
        addChar(hexDigits[(aByte >> 4) & 0x0F]).addChar(hexDigits[aByte & 0x0F]);
    }
    addChar(kBlobSeparator);
    ODL_EXIT_P(this); //####
    return *this;
} // nImO::Message::addBytes

nImO::Message &
nImO::Message::addDouble(const double aDouble)
{
    ODL_OBJENTER(); //####
    ODL_D1("aDouble = ", aDouble); //####
    char numBuff[kNumBuffSize];

#if MAC_OR_LINUX_
    snprintf(numBuff, sizeof(numBuff), "%g", aDouble);
#else // ! MAC_OR_LINUX_
    sprintf_s(numBuff, sizeof(numBuff), "%g", aDouble);
#endif // ! MAC_OR_LINUX_
    ODL_S1("numBuff <- ", numBuff); //####
    appendChars(numBuff, strlen(numBuff) * sizeof(numBuff[0]));
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::addDouble

nImO::Message &
nImO::Message::addLong(const int64_t aLong)
{
    ODL_OBJENTER(); //####
    ODL_LL1("aLong = ", aLong); //####
    char numBuff[kNumBuffSize];

    snprintf(numBuff, sizeof(numBuff), "%" PRId64, aLong);
    ODL_S1("numBuff <- ", numBuff); //####
    appendChars(numBuff, strlen(numBuff) * sizeof(numBuff[0]));
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::addLong

nImO::Message &
nImO::Message::addString(const char * aString)
{
    ODL_OBJENTER(); //####
    ODL_S1("aString = ", aString); //####
    if (aString)
    {
        size_t length = strlen(aString);

        appendChars(aString, length * sizeof(*aString));
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::addString

nImO::Message &
nImO::Message::addString(const std::string & aString)
{
    ODL_OBJENTER(); //####
    ODL_S1s("aString = ", aString); //####
    size_t length = aString.length();

    appendChars(aString.c_str(), length * sizeof(*aString.c_str()));
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::addString

void
nImO::Message::appendBytes(const uint8_t * data,
                           const size_t    numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1("data = ", data); //####
    ODL_LL1("numBytes = ", numBytes); //####
    if (data && (0 < numBytes))
    {
        const char * walker = data;

        if (_cachedOutput)
        {
            delete[] _cachedOutput;
            _cachedOutput = NULL;
        }
        for (size_t bytesLeft = numBytes; 0 < bytesLeft; )
        {
            BufferChunk * lastChunk = _buffers[_numChunks - 1];
            size_t        available = lastChunk->getAvailableBytes();

            if (bytesLeft <= available)
            {
                lastChunk->appendData(walker, bytesLeft * sizeof(*data));
                bytesLeft = 0;
            }
            else
            {
                BufferChunk * prevChunk = lastChunk;

                lastChunk = new BufferChunk;
                if (lastChunk)
                {
                    BufferChunk * * newBuffers = new BufferChunk *[_numChunks + 1];

                    if (newBuffers)
                    {
                        memcpy(newBuffers, _buffers, sizeof(*_buffers) * _numChunks);
                        delete[] _buffers;
                        _buffers = newBuffers;
                        ODL_P1("_buffers <- ", _buffers); //####
                        _buffers[_numChunks++] = lastChunk;
                        ODL_LL1("_numChunks <- ", _numChunks); //####
                        prevChunk->appendData(walker, available);
                        walker += available;
                        bytesLeft -= available;
                    }
                    else
                    {
                        delete lastChunk;
                        bytesLeft = 0;
                    }
                }
                else
                {
                    bytesLeft = 0;
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::Message::appendBytes

nImO::Value * nImO::Message::convertToValue(void)
const
{
    ODL_OBJENTER(); //####
    size_t  position = 0;
    Value * result = Value::readFrommessage(*this, position);
    
    ODL_P1("result <- ", result); //####
    if (result)
    {
        bool    done = false;
        bool    valid = true;
        Array * holder = NULL;
        
        for ( ; ! done; )
        {
            int aChar = getChar(position);
            
            // Skip any whitespace after the value
            ODL_C1("aChar <- ", aChar); //####
            for ( ; isspace(aChar); )
            {
                aChar = getChar(++position);
                ODL_C1("aChar <- ", aChar); //####
                ODL_LL1("position <- ", position); //####
            }
            if (kEndCharacter == aChar)
            {
                if (holder)
                {
                    holder->addValue(result);
                }
                done = true;
            }
            else
            {
                if (NULL == holder)
                {
                    holder = new Array;
                    ODL_P1("holder <- ", holder); //####
                }
                holder->addValue(result);
                result = Value::readFrommessage(*this, position);
                ODL_P1("result <- ", result); //####
                if (! result)
                {
                    ODL_LOG("(! result)"); //####
                    valid = false;
                    done = true;
                }
            }
        }
        if (valid)
        {
            if (holder)
            {
                result = holder;
                ODL_P1("result <- ", result); //####
            }
        }
        else
        {
            ODL_LOG("! (valid)"); //####
            delete holder;
            delete result;
            result = NULL;
        }
    }
    else
    {
        ODL_LOG("! (result)"); //####
    }
    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Message::convertToValue

int
nImO::Message::getByte(const size_t index)
const
{
    ODL_OBJENTER(); //####
    int result = kEndCharacter;

    if (_buffers)
    {
        size_t chunkNumber = (index / BufferChunk::kBufferSize);
        size_t offset = (index % BufferChunk::kBufferSize);

        if (_numChunks > chunkNumber)
        {
            BufferChunk * aChunk = _buffers[chunkNumber];

            if (NULL != aChunk)
            {
                if (offset < aChunk->getDataSize())
                {
                    const uint8_t * thisData = aChunk->getData();

                    result = *(thisData + offset);
                }
            }
        } 
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Message::getByte
#endif//0

const uint8_t *
nImO::Message::getBytes(size_t & length)
{
    ODL_OBJENTER(); //####
    ODL_P1("length = ", &length); //####
    length = 0;
    if (! _cachedOutput)
    {
        size_t cachedSize = getLength();

        _cachedOutput = new uint8_t[cachedSize + 1];
        if (_cachedOutput)
        {
            uint8_t * walker = _cachedOutput;

            for (size_t ii = 0; _numChunks > ii; ++ii)
            {
                BufferChunk * aChunk = _buffers[ii];

                if (NULL != aChunk)
                {
                    size_t nn = aChunk->getDataSize();

                    if (0 < nn)
                    {
                        memcpy(walker, aChunk->getData(), nn);
                        walker += nn;
                    }
                }
            }
            *walker = '\0';
            length = cachedSize;
        }
    }
    ODL_OBJEXIT_P(_cachedOutput); //####
    return _cachedOutput;
} // getBytes

size_t
nImO::Message::getLength(void)
const
{
    ODL_OBJENTER(); //####
    size_t totalLength = 0;
    
    if (_buffers)
    {
        BufferChunk * aChunk = _buffers[_numChunks - 1];
        
        totalLength = ((_numChunks - 1) * BufferChunk::kBufferSize);
        if (NULL != aChunk)
        {
            totalLength += aChunk->getDataSize();
        }
    }
    ODL_OBJEXIT_LL(totalLength); //####
    return totalLength;
} // nImO::Message::getLength

nImO::Message &
nImO::Message::reset(void)
{
    ODL_OBJENTER(); //####
    if (_cachedOutput)
    {
        delete[] _cachedOutput;
        _cachedOutput = NULL;
    }
    if (1 < _numChunks)
    {
        for (size_t ii = 1; _numChunks > ii; ++ii)
        {
            BufferChunk * aChunk = _buffers[ii];

            if (NULL != aChunk)
            {
                delete aChunk;
            }
        }
        BufferChunk * firstChunk = *_buffers;

        delete[] _buffers;
        _buffers = new BufferChunk *[1];
        *_buffers = firstChunk;
    }
    _buffers[0]->reset();
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Message::reset

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

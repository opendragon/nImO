//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOchunkArray.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a string buffer.
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
//  Created:    2016-05-03
//
//--------------------------------------------------------------------------------------------------

#include "nImOchunkArray.hpp"

//#include <nImO/nImOarray.hpp>
//#include <nImO/nImOboolean.hpp>
#include <nImO/nImObufferChunk.hpp>
//#include <nImO/nImOvalue.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#include <inttypes.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for an array of chunks. */
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

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

const int nImO::ChunkArray::kEndToken = -1;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::ChunkArray::ChunkArray(const bool padWithNull) :
    _buffers(new BufferChunk *[1]), _numChunks(1), _cachedOutput(NULL), _cachedLength(0),
    _buffersArePadded(padWithNull), _cachedIsFirstBuffer(false)
{
    ODL_ENTER(); //####
    ODL_B1("padWithNull = ", padWithNull); //####
    ODL_P2("_buffers <- ", _buffers, "_cachedOutput <- ", _cachedOutput); //####
    ODL_LL2("_cachedLength <-", _cachedLength, "_numChunks <- ", _numChunks); //####
    ODL_B2("_buffersArePadded <- ", _buffersArePadded, "_cachedIsFirstBuffer <- ",
           _cachedIsFirstBuffer); //####
    *_buffers = new BufferChunk(_buffersArePadded);
    ODL_EXIT_P(this); //####
} // nImO::ChunkArray::ChunkArray

nImO::ChunkArray::~ChunkArray(void)
{
    ODL_OBJENTER(); //####
    if (! _cachedIsFirstBuffer)
    {
        ODL_LOG("(! _cachedIsFirstBuffer)"); //####
        delete[] _cachedOutput;
    }
    if (_buffers)
    {
        ODL_LOG("(_buffers)"); //####
        for (size_t ii = 0; _numChunks > ii; ++ii)
        {
            delete _buffers[ii];
        }
        delete[] _buffers;
    }
    ODL_OBJEXIT(); //####
} // nImO::ChunkArray::~ChunkArray

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::ChunkArray::appendBytes(const uint8_t * data,
                              const size_t    numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1("data = ", data); //####
    ODL_LL1("numBytes = ", numBytes); //####
    if (data && (0 < numBytes))
    {
        ODL_LOG("(data && (0 < numBytes))"); //####
        const uint8_t * walker = data;

        if (_cachedOutput)
        {
            ODL_LOG("(_cachedOutput)"); //####
            if (! _cachedIsFirstBuffer)
            {
                ODL_LOG("(! _cachedIsFirstBuffer)"); //####
                delete[] _cachedOutput;
            }
            _cachedOutput = NULL;
            ODL_P1("_cachedOutput <- ", _cachedOutput); //####
        }
        for (size_t bytesLeft = numBytes; 0 < bytesLeft; )
        {
            BufferChunk * lastChunk = _buffers[_numChunks - 1];
            size_t        available = lastChunk->getAvailableBytes();

            if (bytesLeft <= available)
            {
                ODL_LOG("(bytesLeft <= available)"); //####
                lastChunk->appendData(walker, bytesLeft * sizeof(*data));
                bytesLeft = 0;
            }
            else
            {
                ODL_LOG("! (bytesLeft <= available)"); //####
                BufferChunk * prevChunk = lastChunk;

                lastChunk = new BufferChunk(_buffersArePadded);
                if (lastChunk)
                {
                    ODL_LOG("(lastChunk)"); //####
                    BufferChunk * * newBuffers = new BufferChunk *[_numChunks + 1];

                    if (newBuffers)
                    {
                        ODL_LOG("(newBuffers)"); //####
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
                        ODL_LOG("! (newBuffers)"); //####
                        delete lastChunk;
                        bytesLeft = 0;
                    }
                }
                else
                {
                    ODL_LOG("! (lastChunk)"); //####
                    bytesLeft = 0;
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ChunkArray::appendBytes

int
nImO::ChunkArray::getByte(const size_t index)
const
{
    ODL_OBJENTER(); //####
    ODL_LL1("index = ", index); //####
    int result = kEndToken;

    if (_buffers)
    {
        ODL_LOG("(_buffers)"); //####
        size_t chunkNumber = (index / BufferChunk::kBufferSize);
        size_t offset = (index % BufferChunk::kBufferSize);

        if (_numChunks > chunkNumber)
        {
            ODL_LOG("(_numChunks > chunkNumber)"); //####
            BufferChunk * aChunk = _buffers[chunkNumber];

            if (NULL != aChunk)
            {
                ODL_LOG("(NULL != aChunk)"); //####
                if (offset < aChunk->getDataSize())
                {
                    ODL_LOG("(offset < aChunk->getDataSize())"); //####
                    const uint8_t * thisData = aChunk->getData();

                    result = *(thisData + offset);
                }
            }
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::ChunkArray::getByte

const uint8_t *
nImO::ChunkArray::getBytes(size_t & length)
{
    ODL_OBJENTER(); //####
    ODL_P1("length = ", &length); //####
    if (_cachedOutput)
    {
        ODL_LOG("(_cachedOutput)"); //####
        length = _cachedLength;
        ODL_LL1("length <- ", length); //####
    }
    else
    {
        ODL_LOG("! (_cachedOutput)"); //####
        length = 0;
        ODL_LL1("length <- ", length); //####
        if (1 < _numChunks)
        {
            ODL_LOG("(1 < _numChunks)"); //####
            size_t cachedSize = getLength();

            _cachedOutput = new uint8_t[cachedSize + (_buffersArePadded ? 1 : 0)];
            ODL_P1("_cachedOutput <- ", _cachedOutput); //####
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
                if (_buffersArePadded)
                {
                    *walker = '\0';
                }
                length = cachedSize;
                ODL_LL1("length <- ", length); //####
                _cachedIsFirstBuffer = false;
                ODL_B1("_cachedIsFirstBuffer <- ", _cachedIsFirstBuffer); //####
            }
        }
        else
        {
            ODL_LOG("(1 < _numChunks)"); //####
            _cachedOutput = const_cast<uint8_t *>(_buffers[0]->getData());
            ODL_P1("_cachedOutput <- ", _cachedOutput); //####
            length = _buffers[0]->getDataSize();
            ODL_LL1("length <- ", length); //####
            _cachedIsFirstBuffer = true;
            ODL_B1("_cachedIsFirstBuffer <- ", _cachedIsFirstBuffer); //####
        }
        _cachedLength = length;
        ODL_LL1("_cachedLength <- ", _cachedLength); //####
    }
    ODL_OBJEXIT_P(_cachedOutput); //####
    return _cachedOutput;
} // getBytes

size_t
nImO::ChunkArray::getLength(void)
const
{
    ODL_OBJENTER(); //####
    size_t totalLength = 0;

    if (_buffers)
    {
        ODL_LOG("(_buffers)"); //####
        BufferChunk * aChunk = _buffers[_numChunks - 1];

        totalLength = ((_numChunks - 1) * BufferChunk::kBufferSize);
        if (NULL != aChunk)
        {
            ODL_LOG("(NULL != aChunk)"); //####
            totalLength += aChunk->getDataSize();
        }
    }
    ODL_OBJEXIT_LL(totalLength); //####
    return totalLength;
} // nImO::ChunkArray::getLength

nImO::ChunkArray &
nImO::ChunkArray::reset(void)
{
    ODL_OBJENTER(); //####
    if (_cachedOutput)
    {
        ODL_LOG("(_cachedOutput)"); //####
        if (! _cachedIsFirstBuffer)
        {
            ODL_LOG("(! _cachedIsFirstBuffer)"); //####
            delete[] _cachedOutput;
        }
        _cachedOutput = NULL;
        ODL_P1("_cachedOutput <- ", _cachedOutput); //####
    }
    if (1 < _numChunks)
    {
        ODL_LOG("(1 < _numChunks)"); //####
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
} // nImO::ChunkArray::reset

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
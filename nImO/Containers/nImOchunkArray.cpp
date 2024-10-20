//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOchunkArray.cpp
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

#include <Containers/nImOchunkArray.h>

#include <Containers/nImObufferChunk.h>

#include <inttypes.h>
#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

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

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::ChunkArray::ChunkArray
    (const bool padWithNull) :
        _buffers{new Ptr(BufferChunk)[1]}, _buffersArePadded{padWithNull}, _cachedString{}, _numChunks{1}
{
    ODL_ENTER(); //####
    ODL_B1(padWithNull); //####
    ODL_P1(_buffers); //####
    ODL_I1(_numChunks); //####
    ODL_B1(_buffersArePadded); //####
    *_buffers = new BufferChunk(_buffersArePadded);
    ODL_EXIT_P(this); //####
} // nImO::ChunkArray::ChunkArray

nImO::ChunkArray::ChunkArray
    (ChunkArray &&  other)
    noexcept :
        _buffers{other._buffers}, _buffersArePadded{other._buffersArePadded}, _cachedString{other._cachedString},
        _numChunks{other._numChunks}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    other._buffers = nullptr;
    other._buffersArePadded = false;
    other._cachedString = ""s;
    other._numChunks = 0;
    ODL_EXIT_P(this); //####
} // nImO::ChunkArray::ChunkArray

nImO::ChunkArray::~ChunkArray
    (void)
{
    ODL_OBJENTER(); //####
    if (nullptr != _buffers)
    {
        ODL_LOG("(nullptr != _buffers)"); //####
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
nImO::ChunkArray::appendBytes
    (CPtr(uint8_t)  data,
     const size_t   numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1(data); //####
    ODL_I1(numBytes); //####
    if ((nullptr != data) && (0 < numBytes))
    {
        ODL_LOG("((nullptr != data) && (0 < numBytes))"); //####
        CPtr(uint8_t)   walker{data};

        // Invalidate the cache.
        _cachedString.clear();
        for (size_t bytesLeft = numBytes; 0 < bytesLeft; )
        {
            Ptr(BufferChunk)    lastChunk{_buffers[_numChunks - 1]};
            size_t              available{lastChunk->getAvailableBytes()};

            if (bytesLeft <= available)
            {
                ODL_LOG("(bytesLeft <= available)"); //####
                lastChunk->appendData(walker, bytesLeft * sizeof(*data));
                bytesLeft = 0;
            }
            else
            {
                ODL_LOG("! (bytesLeft <= available)"); //####
                Ptr(BufferChunk)    prevChunk{lastChunk};

                lastChunk = new BufferChunk(_buffersArePadded);
                if (nullptr == lastChunk)
                {
                    ODL_LOG("(nullptr == lastChunk)"); //####
                    bytesLeft = 0;
                }
                else
                {
                    auto    newBuffers{new Ptr(BufferChunk)[_numChunks + 1]};

                    if (nullptr == newBuffers)
                    {
                        ODL_LOG("(nullptr == newBuffers)"); //####
                        delete lastChunk;
                        bytesLeft = 0;
                    }
                    else
                    {
                        memcpy(newBuffers, _buffers, sizeof(*_buffers) * _numChunks);
                        delete[] _buffers;
                        _buffers = newBuffers;
                        ODL_P1(_buffers); //####
                        _buffers[_numChunks++] = lastChunk;
                        ODL_I1(_numChunks); //####
                        prevChunk->appendData(walker, available);
                        walker += available;
                        bytesLeft -= available;
                    }
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ChunkArray::appendBytes

bool
nImO::ChunkArray::atEnd
    (const size_t   index)
    const
{
    ODL_OBJENTER(); //####
    ODL_I1(index); //####
    bool    result{true};

    if (nullptr != _buffers)
    {
        ODL_LOG("(nullptr != _buffers)"); //####
        size_t  chunkNumber{index / BufferChunk::kBufferSize};
        size_t  offset{index % BufferChunk::kBufferSize};

        ODL_I2(chunkNumber, offset); //####
        if (_numChunks > chunkNumber)
        {
            ODL_LOG("(_numChunks > chunkNumber)"); //####
            Ptr(BufferChunk)    aChunk{_buffers[chunkNumber]};

            if (nullptr != aChunk)
            {
                ODL_LOG("(nullptr != aChunk)"); //####
                if (offset < aChunk->getDataSize())
                {
                    ODL_LOG("(offset < aChunk->getDataSize())"); //####
                    result = false;
                }
            }
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::ChunkArray::atEnd

int
nImO::ChunkArray::getByte
    (const size_t   index,
     bool &         atEnd)
    const
{
    ODL_OBJENTER(); //####
    ODL_I1(index); //####
    int result{-1};

    atEnd = true;
    ODL_B1(atEnd); //####
    if (nullptr != _buffers)
    {
        ODL_LOG("(nullptr != _buffers)"); //####
        size_t  chunkNumber{index / BufferChunk::kBufferSize};
        size_t  offset{index % BufferChunk::kBufferSize};

        ODL_I2(chunkNumber, offset); //####
        if (_numChunks > chunkNumber)
        {
            ODL_LOG("(_numChunks > chunkNumber)"); //####
            Ptr(BufferChunk)    aChunk{_buffers[chunkNumber]};

            if (nullptr != aChunk)
            {
                ODL_LOG("(nullptr != aChunk)"); //####
                if (offset < aChunk->getDataSize())
                {
                    ODL_LOG("(offset < aChunk->getDataSize())"); //####
                    CPtr(uint8_t)   thisData{aChunk->getData()};

                    result = *(thisData + offset);
                    atEnd = false;
                    ODL_B1(atEnd); //####
                }
            }
        }
    }
    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::ChunkArray::getByte

size_t
nImO::ChunkArray::getLength
    (void)
    const
{
    ODL_OBJENTER(); //####
    size_t  totalLength{0};

    if (nullptr != _buffers)
    {
        ODL_LOG("(nullptr != _buffers)"); //####
        CPtr(BufferChunk)   aChunk{_buffers[_numChunks - 1]};

        totalLength = ((_numChunks - 1) * BufferChunk::kBufferSize);
        if (nullptr != aChunk)
        {
            ODL_LOG("(nullptr != aChunk)"); //####
            totalLength += aChunk->getDataSize();
        }
    }
    ODL_OBJEXIT_I(totalLength); //####
    return totalLength;
} // nImO::ChunkArray::getLength

std::string
nImO::ChunkArray::getString
    (void)
{
    ODL_OBJENTER(); //####
    if (0 == _cachedString.size())
    {
        ODL_LOG("(0 == _cachedString.size())"); //####
        _cachedString = getString(0);
    }
    ODL_OBJEXIT_s(_cachedString); //####
    return _cachedString;
} // nImO::ChunkArray::getString

std::string
nImO::ChunkArray::getString
    (const size_t   index)
    const
{
    ODL_OBJENTER(); //####
    ODL_I1(index); //####
    std::string result;
    size_t      length{getLength()};
    size_t      walker{0};

    ODL_I2(length, walker); //####
    if (index < length)
    {
        for (size_t ii = 0; _numChunks > ii; ++ii)
        {
            CPtr(BufferChunk)   aChunk{_buffers[ii]};

            if (nullptr != aChunk)
            {
                ODL_LOG("(nullptr != aChunk)"); //####
                auto    data{aChunk->getData()};

                for (size_t jj = 0, nn = aChunk->getDataSize(); nn > jj; ++jj, ++data)
                {
                    if (walker++ >= index)
                    {
                        result += *data;
                    }
                    ODL_I2(walker, jj); //####
                }
            }
        }
    }
    ODL_OBJEXIT_s(result); //####
    return result;
} // nImO::ChunkArray::getString

nImO::ChunkArray &
nImO::ChunkArray::operator=
    (ChunkArray &&  other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        _buffers = other._buffers;
        _buffersArePadded = other._buffersArePadded;
        _cachedString = other._cachedString;
        _numChunks = other._numChunks;
        other._buffers = nullptr;
        other._buffersArePadded = false;
        other._cachedString = ""s;
        other._numChunks = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::ChunkArray::operator=

nImO::ChunkArray &
nImO::ChunkArray::reset
    (void)
{
    ODL_OBJENTER(); //####
    // Invalidate the cache.
    _cachedString.clear();
    if (1 < _numChunks)
    {
        ODL_LOG("(1 < _numChunks)"); //####
        for (size_t ii = 1; _numChunks > ii; ++ii)
        {
            Ptr(BufferChunk)    aChunk{_buffers[ii]};

            if (nullptr != aChunk)
            {
                delete aChunk;
            }
        }
        Ptr(BufferChunk)    firstChunk{*_buffers};

        delete[] _buffers;
        _buffers = new Ptr(BufferChunk)[1];
        *_buffers = firstChunk;
    }
    _buffers[0]->reset();
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::ChunkArray::reset

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

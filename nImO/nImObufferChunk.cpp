//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImObufferChunk.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a chunk of a buffer.
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
//  Created:    2016-03-28
//
//--------------------------------------------------------------------------------------------------

#include "nImObufferChunk.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a chunk of a buffer. */
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

const size_t nImO::BufferChunk::kBufferSize = 1000;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::BufferChunk::BufferChunk(const bool addPadding) :
    _buffer(new uint8_t[kBufferSize + (addPadding ? 1 : 0)]), _bufferEnd(nullptr),
    _write(nullptr), _padded(addPadding)
{
    ODL_ENTER(); //####
    ODL_B1("addPadding = ", addPadding); //####
    ODL_P1("_buffer <- ", _buffer.get()); //####
    if (_buffer)
    {
        ODL_LOG("(_buffer)"); //####
        _write = _buffer.get();
        _bufferEnd = _write + kBufferSize;
        ODL_P2("_bufferEnd <- ", _bufferEnd, "_write <- ", _write); //####
        ODL_LL1("[size] <- ", getDataSize()); //####
        if (_padded)
        {
            ODL_LOG("(_padded)"); //####
            *_write = 0;
        }
    }
    ODL_EXIT_P(this); //####
} // nImO::BufferChunk::BufferChunk

nImO::BufferChunk::~BufferChunk(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::BufferChunk::~BufferChunk

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::BufferChunk &
nImO::BufferChunk::appendData(const void   *data,
                              const size_t numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1("data = ", data); //####
    ODL_LL1("numBytes = ", numBytes); //####
    size_t actualCount = ((getAvailableBytes() < numBytes) ? getAvailableBytes() : numBytes);

    if (0 < actualCount)
    {
        ODL_LOG("(0 < actualCount)"); //####
	ODL_PACKET("data", data, actualCount); //####
        memcpy(_write, data, actualCount);
        _write += actualCount;
        ODL_P1("_write <- ", _write); //####
        ODL_LL1("[size] <- ", getDataSize()); //####
        if (_padded)
        {
            ODL_LOG("(_padded)"); //####
            *_write = 0;
        }
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::BufferChunk::appendData

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

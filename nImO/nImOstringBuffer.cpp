//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstringBuffer.cpp
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
//  Created:    2016-03-28
//
//--------------------------------------------------------------------------------------------------

#include "nImOstringBuffer.hpp"

#include <nImO/nImObufferChunk.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#include <inttypes.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a string buffer. */
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

/*! @brief The size of a scratch buffer to use when formatting numeric values. */
static const size_t kNumBuffSize = 100;

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

nImO::StringBuffer::StringBuffer(void) :
    _buffers(new BufferChunk *[1]), _cachedOutput(NULL), _numChunks(1)
{
    ODL_ENTER(); //####
    ODL_P2("_buffers <- ", _buffers, "_cachedOutput <- ", _cachedOutput); //####
    ODL_LL1("_numChunks <- ", _numChunks); //####
    *_buffers = new BufferChunk;
    ODL_EXIT_P(this); //####
} // nImO::StringBuffer::StringBuffer

nImO::StringBuffer::~StringBuffer(void)
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
} // StringBuffer::~StringBuffer

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::StringBuffer::addBytes(const char * data,
                             const size_t numBytes)
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
                lastChunk->appendData(walker, bytesLeft);
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
} // nImO::StringBuffer::addBytes

nImO::StringBuffer &
nImO::StringBuffer::addChar(const char aChar)
{
    ODL_OBJENTER(); //####
    ODL_C1("aChar = ", aChar); //####
    char temp = aChar;

    addBytes(&temp, 1);
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addChar

nImO::StringBuffer &
nImO::StringBuffer::addDouble(const double aDouble)
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
    addBytes(numBuff, strlen(numBuff));
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addDouble

nImO::StringBuffer &
nImO::StringBuffer::addLong(const int64_t aLong)
{
    ODL_OBJENTER(); //####
    ODL_LL1("aLong = ", aLong); //####
    char numBuff[kNumBuffSize];
    
    snprintf(numBuff, sizeof(numBuff), "%" PRId64, aLong);
    ODL_S1("numBuff <- ", numBuff); //####
    addBytes(numBuff, strlen(numBuff));
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addLong

nImO::StringBuffer &
nImO::StringBuffer::addString(const char * aString)
{
    ODL_OBJENTER(); //####
    ODL_S1("aString = ", aString); //####
    if (aString)
    {
        addBytes(aString, strlen(aString));
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addString

nImO::StringBuffer &
nImO::StringBuffer::addString(const std::string & aString)
{
    ODL_OBJENTER(); //####
    ODL_S1s("aString = ", aString); //####
    addBytes(aString.c_str(), aString.length());
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addString

nImO::StringBuffer &
nImO::StringBuffer::addTab(void)
{
    ODL_OBJENTER(); //####
    char aTab = '\t';

    addBytes(&aTab, 1);
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addTab

size_t
nImO::StringBuffer::getLength(void)
const
{
    ODL_OBJENTER(); //####
    size_t totalLength = 0;

    if (_buffers)
    {
        for (size_t ii = 0; _numChunks > ii; ++ii)
        {
            BufferChunk * aChunk = _buffers[ii];

            if (aChunk)
            {
                totalLength += aChunk->getDataSize();
            }
        }
    }
    ODL_OBJEXIT_LL(totalLength); //####
    return totalLength;
} // nImO::StringBuffer::getLength

const char *
nImO::StringBuffer::getString(size_t & length)
{
    ODL_OBJENTER(); //####
    ODL_P1("length = ", &length); //####
    length = 0;
    if (! _cachedOutput)
    {
        size_t cachedSize = getLength();

        if (0 < cachedSize)
        {
            _cachedOutput = new char[cachedSize + 1];
        }
        if (_cachedOutput)
        {
            char * walker = _cachedOutput;

            for (size_t ii = 0; _numChunks > ii; ++ii)
            {
                BufferChunk * aChunk = _buffers[ii];

                if (aChunk)
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
} // getString
        
nImO::StringBuffer &
nImO::StringBuffer::reset(void)
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

            if (aChunk)
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
} // nImO::StringBuffer::reset

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

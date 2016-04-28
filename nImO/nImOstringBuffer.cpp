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

/*! @brief The canonical names for control characters. */
static const char * kCanonicalControl[] =
{
    "C-@", // 00 NUL
    "C-A", // 01 SOH
    "C-B", // 02 STX
    "C-C", // 03 ETX
    "C-D", // 04 EOT
    "C-E", // 05 ENQ
    "C-F", // 06 ACK
    "a", // 07 BEL
    "b", // 08 BS
    "t", // 09 HT
    "n", // 0A LF
    "v", // 0B VT
    "f", // 0C FF
    "r", // 0D CR
    "C-N", // 0E SO
    "C-O", // 0F SI
    "C-P", // 10 DLE
    "C-Q", // 11 DC1
    "C-R", // 12 DC2
    "C-S", // 13 DC3
    "C-T", // 14 DC4
    "C-U", // 15 NAK
    "C-V", // 16 SYN
    "C-W", // 17 ETB
    "C-X", // 18 CAN
    "C-Y", // 19 EM
    "C-Z", // 1A SUB
    "e", // 1B ESC
    "C-`", // 1C FS
    "C-]", // 1D GS
    "C-^", // 1E RS
    "C-_" // 1F US
}; // kCanonicalControl

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

const int nImO::StringBuffer::kEndCharacter = -1;

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
    _buffers(new BufferChunk *[1]), _cachedOutput(NULL), _cachedLength(0), _numChunks(1),
    _cachedIsFirstBuffer(false)
{
    ODL_ENTER(); //####
    ODL_P2("_buffers <- ", _buffers, "_cachedOutput <- ", _cachedOutput); //####
    ODL_LL2("_cachedLength <-", _cachedLength, "_numChunks <- ", _numChunks); //####
    ODL_B1("_cachedIsFirstBuffer <- ", _cachedIsFirstBuffer); //####
    *_buffers = new BufferChunk(true);
    ODL_EXIT_P(this); //####
} // nImO::StringBuffer::StringBuffer

nImO::StringBuffer::~StringBuffer(void)
{
    ODL_OBJENTER(); //####
    if (! _cachedIsFirstBuffer)
    {
        delete[] _cachedOutput;
    }
    if (_buffers)
    {
        for (size_t ii = 0; _numChunks > ii; ++ii)
        {
            delete _buffers[ii];
        }
        delete _buffers;
    }
    ODL_OBJEXIT(); //####
} // nImO::StringBuffer::~StringBuffer

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::StringBuffer &
nImO::StringBuffer::addBool(const bool aBool)
{
    ODL_OBJENTER(); //####
    ODL_B1("aBool = ", aBool); //####
    addString(Boolean::getCanonicalRepresentation(aBool));
    ODL_EXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addBool

nImO::StringBuffer &
nImO::StringBuffer::addBytes(const uint8_t * inBytes,
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
} // nImO::StringBuffer::addBytes

nImO::StringBuffer &
nImO::StringBuffer::addChar(const char aChar)
{
    ODL_OBJENTER(); //####
    ODL_C1("aChar = ", aChar); //####
    char temp = aChar;

    appendChars(&temp, sizeof(temp));
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
    appendChars(numBuff, strlen(numBuff) * sizeof(numBuff[0]));
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
    appendChars(numBuff, strlen(numBuff) * sizeof(numBuff[0]));
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addLong

nImO::StringBuffer &
nImO::StringBuffer::addString(const char * aString,
                              const bool   addQuotes)
{
    ODL_OBJENTER(); //####
    ODL_S1("aString = ", aString); //####
    ODL_B1("addQuotes = ", addQuotes); //####
    if (aString)
    {
        size_t length = strlen(aString);

        if (addQuotes)
        {
            processCharacters(aString, length);
        }
        else
        {
            appendChars(aString, length * sizeof(*aString));
        }
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addString

nImO::StringBuffer &
nImO::StringBuffer::addString(const std::string & aString,
                              const bool          addQuotes)
{
    ODL_OBJENTER(); //####
    ODL_S1s("aString = ", aString); //####
    ODL_B1("addQuotes = ", addQuotes); //####
    size_t length = aString.length();

    if (addQuotes)
    {
        processCharacters(aString.c_str(), length);
    }
    else
    {
        appendChars(aString.c_str(), length * sizeof(*aString.c_str()));
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addString

nImO::StringBuffer &
nImO::StringBuffer::addTab(void)
{
    ODL_OBJENTER(); //####
    addChar('\t');
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addTab

void
nImO::StringBuffer::appendChars(const char * data,
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
            if (! _cachedIsFirstBuffer)
            {
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
                lastChunk->appendData(walker, bytesLeft * sizeof(*data));
                bytesLeft = 0;
            }
            else
            {
                BufferChunk * prevChunk = lastChunk;

                lastChunk = new BufferChunk(true);
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
} // nImO::StringBuffer::appendChars

nImO::Value * nImO::StringBuffer::convertToValue(void)
const
{
    ODL_OBJENTER(); //####
    size_t  position = 0;
    Value * result = Value::readFromStringBuffer(*this, position);

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
                result = Value::readFromStringBuffer(*this, position);
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
} // nImO::StringBuffer::convertToValue

int
nImO::StringBuffer::getChar(const size_t index)
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
} // nImO::StringBuffer::getChar

size_t
nImO::StringBuffer::getLength(void)
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
} // nImO::StringBuffer::getLength

const char *
nImO::StringBuffer::getString(size_t & length)
{
    ODL_OBJENTER(); //####
    ODL_P1("length = ", &length); //####
    if (_cachedOutput)
    {
        length = _cachedLength;
        ODL_LL1("length <- ", length); //####
    }
    else
    {
        length = 0;
        ODL_LL1("length <- ", length); //####
        if (1 < _numChunks)
        {
            size_t cachedSize = getLength();

            _cachedOutput = new char[cachedSize + 1];
            ODL_P1("_cachedOutput <- ", _cachedOutput); //####
            if (_cachedOutput)
            {
                char * walker = _cachedOutput;

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
                ODL_LL1("length <- ", length); //####
                _cachedIsFirstBuffer = false;
                ODL_B1("_cachedIsFirstBuffer <- ", _cachedIsFirstBuffer); //####
            }
        }
        else
        {
            _cachedOutput = reinterpret_cast<char *>(const_cast<uint8_t *>(_buffers[0]->getData()));
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
} // getString

void
nImO::StringBuffer::processCharacters(const char * aString,
                                      const size_t length)
{
    ODL_ENTER(); //####
    ODL_S1("aString = ", aString); //####
    ODL_LL1("length = ", length); //####
    // First, determine how many of each kind of quote character there are, and if there are
    // 'special' characters - control characters or characters with the high bit set
    bool   hasSpecials = false;
    size_t numSingleQuotes = 0;
    size_t numDoubleQuotes = 0;
    size_t numEscapes = 0;

    for (size_t ii = 0; length > ii; ++ii)
    {
        uint8_t aByte = static_cast<uint8_t>(aString[ii]);

        if ((0x20 > aByte) || (0 != (aByte & 0x80)))
        {
            hasSpecials = true;
        }
        else if (kSingleQuote == aByte)
        {
            ++numSingleQuotes;
        }
        else if (kDoubleQuote == aByte)
        {
            ++numDoubleQuotes;
        }
        else if (kEscapeChar == aByte)
        {
            ++numEscapes;
        }
    }
    if (hasSpecials || (0 < (numDoubleQuotes + numSingleQuotes + numEscapes)))
    {
        char delimiter = ((numDoubleQuotes > numSingleQuotes) ? kSingleQuote : kDoubleQuote);

        appendChars(&delimiter, sizeof(delimiter));
        for (size_t ii = 0; length > ii; ++ii)
        {
            uint8_t aByte = static_cast<uint8_t>(aString[ii]);

            if ((0x20 > aByte) || (0 != (aByte & 0x80)))
            {
                appendChars(&kEscapeChar, sizeof(kEscapeChar));
                if (0x20 > aByte)
                {
                    const char * controlString = kCanonicalControl[aByte];

                    appendChars(controlString, strlen(controlString) * sizeof(*controlString));
                }
                else
                {
                    aByte &= 0x07F;
                    if (' ' == aByte)
                    {
                        // Meta-blank is very special
                        static const char metaBlank[] = { '2', '4', '0' };

                        appendChars(metaBlank, sizeof(metaBlank));
                    }
                    else if (0x7F == aByte)
                    {
                        // As is 0xFF
                        static const char metaDel[] = { '3', '7', '7' };

                        appendChars(metaDel, sizeof(metaDel));
                    }
                    else if (delimiter == aByte)
                    {
                        // Make sure that we don't break if there's a meta-quote of some form!
                        static const char metaDoubleQuote[] = { '2', '4', '2' };
                        static const char metaSingleQuote[] = { '2', '4', '7' };

                        if (kSingleQuote == aByte)
                        {
                            appendChars(metaSingleQuote, sizeof(metaSingleQuote));
                        }
                        else
                        {
                            appendChars(metaDoubleQuote, sizeof(metaDoubleQuote));
                        }
                    }
                    else
                    {
                        // 'Regular' meta characters
                        static const char metaPrefix[] = { 'M', '-' };

                        appendChars(metaPrefix, sizeof(metaPrefix));
                        if (0x20 > aByte)
                        {
                            const char * controlString = kCanonicalControl[aByte];

                            appendChars(&kEscapeChar, sizeof(kEscapeChar));
                            appendChars(controlString, strlen(controlString) *
                                        sizeof(*controlString));
                        }
                        else
                        {
                            appendChars(reinterpret_cast<const char *>(&aByte), sizeof(char));
                        }
                    }
                }
            }
            else
            {
                // Handle normal escapes - nested delimiters and the escape character
                if ((delimiter == aByte) || (kEscapeChar == aByte))
                {
                    appendChars(&kEscapeChar, sizeof(kEscapeChar));
                }
                appendChars(aString + ii, sizeof(*aString));
            }
        }
        appendChars(&delimiter, sizeof(delimiter));
    }
    else
    {
        // Nothing special
        appendChars(&kDoubleQuote, sizeof(kDoubleQuote));
        appendChars(aString, length * sizeof(*aString));
        appendChars(&kDoubleQuote, sizeof(kDoubleQuote));
    }
    ODL_EXIT(); //####
} // nImO::StringBuffer::processCharacters

nImO::StringBuffer &
nImO::StringBuffer::reset(void)
{
    ODL_OBJENTER(); //####
    if (_cachedOutput)
    {
        if (! _cachedIsFirstBuffer)
        {
            delete[] _cachedOutput;
        }
        _cachedOutput = NULL;
        ODL_P1("_cachedOutput <- ", _cachedOutput); //####
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
} // nImO::StringBuffer::reset

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

std::ostream &
nImO::operator <<(std::ostream       &       out,
                  const nImO::StringBuffer & aBuffer)
{
    ODL_ENTER(); //###
    ODL_P2("out = ", &out, "aBuffer = ", &aBuffer); //####
    for (size_t ii = 0; aBuffer._numChunks > ii; ++ii)
    {
        BufferChunk * aChunk = aBuffer._buffers[ii];

        if (NULL != aChunk)
        {
           size_t nn = aChunk->getDataSize();

           if (0 < nn)
           {
               out.write(reinterpret_cast<const char *>(aChunk->getData()), nn);
           }
        }
    }
    ODL_EXIT_P(&out); //####
    return out;
} // nImO::operator <<

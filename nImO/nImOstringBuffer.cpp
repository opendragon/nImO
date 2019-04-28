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

#include <nImOarray.hpp>
#include <nImObufferChunk.hpp>
#include <nImOlogical.hpp>
#include <nImOvalue.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

#include <inttypes.h>
//#include <stdio.h>

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

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::StringBuffer::StringBuffer
    (void) :
        inherited(true)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::StringBuffer::StringBuffer

nImO::StringBuffer::~StringBuffer
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::StringBuffer::~StringBuffer

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::StringBuffer &
nImO::StringBuffer::addBool
    (const bool aBool)
{
    ODL_OBJENTER(); //####
    ODL_B1("aBool = ", aBool); //####
    addString(Logical::getCanonicalRepresentation(aBool));
    ODL_EXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addBool

nImO::StringBuffer &
nImO::StringBuffer::addBytes
    (const uint8_t *    inBytes,
     const size_t       numBytes)
{
    ODL_OBJENTER(); //####
    ODL_P1("inBytes = ", inBytes); //####
    ODL_I1("numBytes = ", numBytes); //####
    static const char hexDigits[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    addChar(kBlobSeparator).addLong(numBytes).addChar(kBlobSeparator);
    for (size_t ii = 0; numBytes > ii; ++ii)
    {
        uint8_t aByte = inBytes[ii];

        addChar(hexDigits[(aByte >> 4) &0x0F]).addChar(hexDigits[aByte &0x0F]);
    }
    addChar(kBlobSeparator);
    ODL_EXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addBytes

nImO::StringBuffer &
nImO::StringBuffer::addString
    (const char *   aString,
     const bool     addQuotes)
{
    ODL_OBJENTER(); //####
    ODL_S1("aString = ", aString); //####
    ODL_B1("addQuotes = ", addQuotes); //####
    if (aString)
    {
        size_t  length = strlen(aString);

        if (addQuotes)
        {
            processCharacters(aString, length);
        }
        else
        {
            inherited::appendBytes(reinterpret_cast<const uint8_t *>(aString), length * sizeof(*aString));
        }
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addString

nImO::StringBuffer &
nImO::StringBuffer::addString
    (const std::string &    aString,
     const bool             addQuotes)
{
    ODL_OBJENTER(); //####
    ODL_S1s("aString = ", aString); //####
    ODL_B1("addQuotes = ", addQuotes); //####
    size_t  length = aString.length();

    if (addQuotes)
    {
        processCharacters(aString.c_str(), length);
    }
    else
    {
        inherited::appendBytes(reinterpret_cast<const uint8_t *>(aString.c_str()), length * sizeof(*aString.c_str()));
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::StringBuffer::addString

nImO::SpValue
nImO::StringBuffer::convertToValue
    (void)
    const
{
    ODL_OBJENTER(); //####
    size_t  position = 0;
    SpValue result(Value::readFromStringBuffer(*this, position));

    ODL_P1("result <- ", result.get()); //####
    if (result)
    {
        bool    atEnd;
        bool    done = false;
        bool    valid = true;
        SpArray holder;

        for ( ; ! done; )
        {
            int aChar = getChar(position, atEnd);

            // Skip any whitespace after the value
            ODL_C1("aChar <- ", aChar); //####
            ODL_B1("atEnd <- ", atEnd); //####
            for ( ; (! atEnd) && isspace(aChar); )
            {
                aChar = getChar(++position, atEnd);
                ODL_C1("aChar <- ", aChar); //####
                ODL_B1("atEnd <- ", atEnd); //####
                ODL_I1("position <- ", position); //####
            }
            if (atEnd)
            {
                if (holder)
                {
                    holder->addValue(result);
                }
                done = true;
            }
            else
            {
                if (nullptr == holder)
                {
                    holder.reset(new Array);
                    ODL_P1("holder <- ", holder.get()); //####
                }
                holder->addValue(result);
                result = Value::readFromStringBuffer(*this, position);
                ODL_P1("result <- ", result.get()); //####
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
                ODL_P1("result <- ", result.get()); //####
            }
        }
        else
        {
            ODL_LOG("! (valid)"); //####
            result.reset();
        }
    }
    else
    {
        ODL_LOG("! (result)"); //####
    }
    ODL_OBJEXIT_P(result.get()); //####
    return result;
} // nImO::StringBuffer::convertToValue

void
nImO::StringBuffer::processCharacters
    (const char *   aString,
     const size_t   length)
{
    ODL_ENTER(); //####
    ODL_S1("aString = ", aString); //####
    ODL_I1("length = ", length); //####
    // First, determine how many of each kind of quote character there are, and if there are
    // 'special' characters - control characters or characters with the high bit set
    bool    hasSpecials = false;
    size_t  numSingleQuotes = 0;
    size_t  numDoubleQuotes = 0;
    size_t  numEscapes = 0;

    for (size_t ii = 0; length > ii; ++ii)
    {
        uint8_t aByte = static_cast<uint8_t>(aString[ii]);

        if ((0x20 > aByte) || (0 != (aByte &0x80)))
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
        uint8_t delimiter = ((numDoubleQuotes > numSingleQuotes) ? kSingleQuote : kDoubleQuote);

        inherited::appendBytes(&delimiter, sizeof(delimiter));
        for (size_t ii = 0; length > ii; ++ii)
        {
            uint8_t aByte = static_cast<uint8_t>(aString[ii]);

            if ((0x20 > aByte) || (0 != (aByte &0x80)))
            {
                inherited::appendBytes(&kEscapeChar, sizeof(kEscapeChar));
                if (0x20 > aByte)
                {
                    const char *    controlString = kCanonicalControl[aByte];

                    inherited::appendBytes(reinterpret_cast<const uint8_t *>(controlString),
                                           strlen(controlString) * sizeof(*controlString));
                }
                else
                {
                    aByte &= 0x07F;
                    if (' ' == aByte)
                    {
                        // Meta-blank is very special
                        static const uint8_t    metaBlank[] = { '2', '4', '0' };

                        inherited::appendBytes(metaBlank, sizeof(metaBlank));
                    }
                    else if (0x7F == aByte)
                    {
                        // As is 0xFF
                        static const uint8_t    metaDel[] = { '3', '7', '7' };

                        inherited::appendBytes(metaDel, sizeof(metaDel));
                    }
                    else if (delimiter == aByte)
                    {
                        // Make sure that we don't break if there's a meta-quote of some form!
                        static const uint8_t    metaDoubleQuote[] = { '2', '4', '2' };
                        static const uint8_t    metaSingleQuote[] = { '2', '4', '7' };

                        if (kSingleQuote == aByte)
                        {
                            inherited::appendBytes(metaSingleQuote, sizeof(metaSingleQuote));
                        }
                        else
                        {
                            inherited::appendBytes(metaDoubleQuote, sizeof(metaDoubleQuote));
                        }
                    }
                    else
                    {
                        // 'Regular' meta characters
                        static const uint8_t    metaPrefix[] = { 'M', '-' };

                        inherited::appendBytes(metaPrefix, sizeof(metaPrefix));
                        if (0x20 > aByte)
                        {
                            const char *    controlString = kCanonicalControl[aByte];

                            inherited::appendBytes(&kEscapeChar, sizeof(kEscapeChar));
                            inherited::appendBytes(reinterpret_cast<const uint8_t *>(controlString),
                                                   strlen(controlString) * sizeof(*controlString));
                        }
                        else
                        {
                            inherited::appendBytes(&aByte, sizeof(aByte));
                        }
                    }
                }
            }
            else
            {
                // Handle normal escapes - nested delimiters and the escape character
                if ((delimiter == aByte) || (kEscapeChar == aByte))
                {
                    inherited::appendBytes(&kEscapeChar, sizeof(kEscapeChar));
                }
                inherited::appendBytes(reinterpret_cast<const uint8_t *>(aString + ii), sizeof(*aString));
            }
        }
        inherited::appendBytes(&delimiter, sizeof(delimiter));
    }
    else
    {
        // Nothing special
        inherited::appendBytes(&kDoubleQuote, sizeof(kDoubleQuote));
        inherited::appendBytes(reinterpret_cast<const uint8_t *>(aString), length * sizeof(*aString));
        inherited::appendBytes(&kDoubleQuote, sizeof(kDoubleQuote));
    }
    ODL_EXIT(); //####
} // nImO::StringBuffer::processCharacters

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

std::ostream &
nImO::operator <<
    (std::ostream &             out,
     const nImO::StringBuffer & aBuffer)
{
    ODL_ENTER(); //###
    ODL_P2("out = ", &out, "aBuffer = ", &aBuffer); //####
    for (size_t ii = 0; aBuffer._numChunks > ii; ++ii)
    {
        BufferChunk *   aChunk = aBuffer._buffers[ii];

        if (nullptr != aChunk)
        {
           size_t   nn = aChunk->getDataSize();

           if (0 < nn)
           {
               out.write(reinterpret_cast<const char *>(aChunk->getData()), nn);
           }
        }
    }
    ODL_EXIT_P(&out); //####
    return out;
} // nImO::operator <<

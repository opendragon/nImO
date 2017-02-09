//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOvalue.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO general values.
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
//  Created:    2016-03-21
//
//--------------------------------------------------------------------------------------------------

#include "nImOvalue.hpp"

#include <nImO/nImOarray.hpp>
#include <nImO/nImOblob.hpp>
#include <nImO/nImOboolean.hpp>
#include <nImO/nImOdouble.hpp>
#include <nImO/nImOinteger.hpp>
#include <nImO/nImOmap.hpp>
#include <nImO/nImOmessage.hpp>
#include <nImO/nImOnumber.hpp>
#include <nImO/nImOset.hpp>
#include <nImO/nImOstring.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO general values. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

nImO::Value::ExtractorMap nImO::Value::gExtractors;

nImO::Value::BufferReaderMap nImO::Value::gReaders;

std::string nImO::Value::gTerminators;

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

nImO::Value::Value(void)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Value::Value

nImO::Value::~Value(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Value::~Value

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Value::addToExtractionMap(const uint8_t          aByte,
                                const uint8_t          aMask,
                                nImO::Value::Extractor theExtractor)
{
    ODL_ENTER(); //####
    ODL_LL2("aByte = ", aByte, "aMask = ", aMask); //####
    ODL_P1("theExtractor = ", &theExtractor); //####
    if ((0 != aMask) && (NULL != theExtractor))
    {
        for (uint8_t ii = 0; 255 > ii; ++ii)
        {
            if (aByte == (aMask &ii))
            {
                ExtractorMap::value_type keyValue(ii, theExtractor);

                gExtractors.insert(keyValue);
            }
        }        
    }
    ODL_EXIT(); //####
} // addToExtractionMap

int64_t
nImO::Value::extractInt64FromMessage(const nImO::Message &theMessage,
                                     const int           leadByte,
                                     size_t              &position,
                                     nImO::ReadStatus    &status)
{
    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "status = ", &status); //####
    ODL_XL1("leadByte = ", leadByte); //####
    int64_t result = 0;

    if (kKindInteger == (leadByte &kKindMask))
    {
        bool isShort = (kKindIntegerShortValue == (kKindIntegerSizeMask & leadByte));

        ++position; // We can accept the lead byte
        ODL_LL1("position <- ", position); //####
        if (isShort)
        {
            ODL_LOG("(isShort)"); //####
            uint8_t shortBits = (kKindIntegerShortValueValueMask & leadByte);
            bool    isNegative = (kKindIntegerShortValueSignBit ==
                                  (kKindIntegerShortValueSignBit & leadByte));

            if (isNegative)
            {
                ODL_LOG("(isNegative)"); //####
                int64_t tempValue = (-1 &(~ kKindIntegerShortValueValueMask));

                result = (tempValue | shortBits);
            }
            else
            {
                ODL_LOG("! (isNegative)"); //####
                result = shortBits;
            }
            status = kReadSuccessful;
            ODL_LL1("status <- ", status); //####
        }
        else
        {
            ODL_LOG("! (isShort)"); //####
            size_t        size = (kKindIntegerLongValueCountMask & leadByte) + 1;
            NumberAsBytes holder;
            bool          okSoFar = true;

            for (size_t ii = 0; okSoFar && (size > ii); ++ii)
            {
                int aByte = theMessage.getByte(position);

                if (Message::kEndToken == aByte)
                {
                    ODL_LOG("(Message::kEndToken == aByte)"); //####
                    status = kReadIncomplete;
                    ODL_LL1("status <- ", status); //####
                    okSoFar = false;
                }
                else
                {
                    holder[ii] = static_cast<uint8_t>(aByte);
                    ++position;
                    ODL_LL1("position <- ", position); //####
                }
            }
            if (okSoFar)
            {
                result = B2I(holder, size);
                status = kReadSuccessful;
                ODL_LL1("status <- ", status); //####
            }
        }
    }
    else
    {
        ODL_LOG("! (kKindInteger == (leadByte &kKindMask))"); //####
        status = kReadInvalid;
        ODL_LL1("status <- ", status); //####
    }
    ODL_EXIT_LL(result); //####
    return result;
} // nImO::Value::extractInt64FromMessage

nImO::SpValue
nImO::Value::getValueFromMessage(const nImO::Message &inMessage,
                                 size_t              &position,
                                 const int           leadByte,
                                 nImO::ReadStatus    &status,
                                 nImO::SpArray       parent)
{
    ODL_ENTER(); //####
    ODL_P4("inMessage = ", &inMessage, "position = ", &position, "status = ", &status,
           "parent = ", parent.get()); //####
    ODL_XL1("leadByte = ", leadByte); //####
    SpValue              result;
    ExtractorMapIterator match = gExtractors.find(static_cast<uint8_t>(leadByte));

    if (gExtractors.end() == match)
    {
        ODL_LOG("(gExtractors.end() == match)"); //####
        status = kReadInvalid;
        ODL_LL1("status <- ", status); //####
    }
    else
    {
        Extractor handler = match->second;

        if (NULL == handler)
        {
            ODL_LOG("(NULL == handler)"); //####
            status = kReadInvalid;
            ODL_LL1("status <- ", status); //####
        }
        else
        {
            result = handler(inMessage, leadByte, position, status, parent);
            ODL_P1("result <- ", result.get()); //####
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Value::getValueFromMessage

void
nImO::Value::initialize(void)
{
    ODL_ENTER(); //####
    const char *prefixes = Boolean::getInitialCharacters();

    if (NULL != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Boolean::readFromStringBuffer);

            gReaders.insert(aValue);
        }
    }
    prefixes = Number::getInitialCharacters();
    if (NULL != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Number::readFromStringBuffer);

            gReaders.insert(aValue);
        }
    }
    prefixes = String::getInitialCharacters();
    if (NULL != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &String::readFromStringBuffer);

            gReaders.insert(aValue);
        }
    }
    prefixes = Array::getInitialCharacters();
    if (NULL != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Array::readFromStringBuffer);

            gReaders.insert(aValue);
        }
    }
    prefixes = Map::getInitialCharacters();
    if (NULL != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Map::readFromStringBuffer);

            gReaders.insert(aValue);
        }
    }
    prefixes = Set::getInitialCharacters();
    if (NULL != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Set::readFromStringBuffer);

            gReaders.insert(aValue);
        }
    }
    const char *suffixes = Array::getTerminalCharacters();

    gTerminators = StringBuffer::kEndToken;
    if (NULL != suffixes)
    {
        gTerminators += suffixes;
    }
    suffixes = Map::getTerminalCharacters();
    if (NULL != suffixes)
    {
        gTerminators += suffixes;
    }
    suffixes = Set::getTerminalCharacters();
    if (NULL != suffixes)
    {
        gTerminators += suffixes;
    }
    uint8_t   aByte = 0;
    uint8_t   aMask = 0;
    Extractor theExtractor = NULL;

    Array::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Blob::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Boolean::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Double::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Integer::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Map::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Set::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    String::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    ODL_EXIT(); //####
} // nImO::Value::initialize

bool
nImO::Value::isLegalTerminator(const char aChar)
{
    ODL_ENTER(); //####
    ODL_C1("aChar = ", aChar); //####
    bool result;

    if (isspace(aChar))
    {
        result = true;
    }
    else if (std::string::npos == gTerminators.find(aChar))
    {
        result = false;
    }
    else
    {
        result = true;
    }
    ODL_EXIT_B(result); //####
    return result;
} // nImO::Value::isLegalTerminator

nImO::SpValue
nImO::Value::readFromStringBuffer(const nImO::StringBuffer &inBuffer,
                                  size_t                   &position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    SpValue result;
    size_t  localIndex = position;
    int     aChar = inBuffer.getChar(localIndex);

    // Skip over whitespace
    for ( ; isspace(aChar); )
    {
        aChar = inBuffer.getChar(++localIndex);
    }
    if (StringBuffer::kEndToken == aChar)
    {
        ODL_LOG("(StringBuffer::kEndToken == aChar)"); //####
    }
    else
    {
        BufferReaderIterator match = gReaders.find(aChar);

        if (gReaders.end() == match)
        {
            ODL_LOG("(gReaders.end() == match)"); //####
        }
        else
        {
            BufferReader handler = match->second;

            if (NULL == handler)
            {
                ODL_LOG("(NULL == handler)"); //####
            }
            else
            {
                result = handler(inBuffer, localIndex);
                if (NULL != result)
                {
                    position = localIndex;
                }
            }
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Value::readFromStringBuffer

void
nImO::Value::writeInt64ToMessage(nImO::Message &outMessage,
                                 const int64_t outValue)
{
    ODL_ENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    ODL_LL1("outValue = ", outValue); //####
    if ((kKindIntegerShortValueMinValue <= outValue) &&
        (kKindIntegerShortValueMaxValue >= outValue))
    {
        ODL_LOG("((kKindIntegerShortValueMinValue <= outValue) && " //####
                "(kKindIntegerShortValueMaxValue >= outValue))"); //####
        uint8_t stuff = kKindInteger + kKindIntegerShortValue +
                        (outValue &kKindIntegerShortValueValueMask);

        outMessage.appendBytes(&stuff, sizeof(stuff));
    }
    else
    {
        ODL_LOG("! ((kKindIntegerShortValueMinValue <= outValue) && " //####
                "(kKindIntegerShortValueMaxValue >= outValue))"); //####
        NumberAsBytes numBuff;
        size_t        numBytes = I2B(outValue, numBuff);

        if (0 < numBytes)
        {
            ODL_LOG("(0 < numBytes)"); //####
            uint8_t stuff = kKindInteger + kKindIntegerLongValue +
                            ((numBytes - 1) &kKindIntegerLongValueCountMask);

            outMessage.appendBytes(&stuff, sizeof(stuff));
            outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
        }
    }
    ODL_EXIT(); //####
} // nImO::Value::writeInt64ToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

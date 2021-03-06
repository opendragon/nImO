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

#include <nImOarray.hpp>
#include <nImOblob.hpp>
#include <nImOdouble.hpp>
#include <nImOinteger.hpp>
#include <nImOinvalid.hpp>
#include <nImOlogical.hpp>
#include <nImOmap.hpp>
#include <nImOmessage.hpp>
#include <nImOnumber.hpp>
#include <nImOset.hpp>
#include <nImOstring.hpp>
#include <nImOstringBuffer.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

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

nImO::Value::Value
    (void)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Value::Value

nImO::Value::~Value
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Value::~Value

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Value::addToExtractionMap
    (const DataKind         aByte,
     const DataKind         aMask,
     nImO::Value::Extractor theExtractor)
{
    ODL_ENTER(); //####
    ODL_I2("aByte = ", toUType(aByte), "aMask = ", toUType(aMask)); //####
    ODL_P1("theExtractor = ", &theExtractor); //####
    uint8_t lByte = toUType(aByte);
    uint8_t lMask = toUType(aMask);

    if ((0 != lMask) && (nullptr != theExtractor))
    {
        for (uint8_t ii = 0; 255 > ii; ++ii)
        {
            if (lByte == (lMask & ii))
            {
                ExtractorMap::value_type    keyValue(ii, theExtractor);

                gExtractors.emplace(keyValue);
            }
        }
    }
    ODL_EXIT(); //####
} // addToExtractionMap

const nImO::Array *
nImO::Value::asArray
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asArray

const nImO::Blob *
nImO::Value::asBlob
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asBlob

const nImO::Container *
nImO::Value::asContainer
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asContainer

const nImO::Double *
nImO::Value::asDouble
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asDouble

const nImO::Flaw *
nImO::Value::asFlaw
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asFlaw

const nImO::Integer *
nImO::Value::asInteger
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asInteger

const nImO::Logical *
nImO::Value::asLogical
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asLogical

const nImO::Map *
nImO::Value::asMap
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asMap

const nImO::Number *
nImO::Value::asNumber
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asNumber

const nImO::Set *
nImO::Value::asSet
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asSet

const nImO::String *
nImO::Value::asString
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::Value::asString

bool
nImO::Value::deeplyEqualTo
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(&other == this); //####
    return (&other == this);
} // nImO::Value::deeplyEqualTo

nImO::Enumerable
nImO::Value::enumerationType
    (void)
    const
{
    ODL_OBJENTER(); //####
    Enumerable  result = Enumerable::NotEnumerable;

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Value::enumerationType

nImO::ComparisonStatus
nImO::Value::equalTo
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        result.clear();
    }
    ODL_OBJEXIT();
    return result;
} // nImO::Value::equalTo

int64_t
nImO::Value::extractInt64FromMessage
    (const nImO::Message &  theMessage,
     const int              leadByte,
     size_t &               position,
     nImO::IntStatus &      status)
{
    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "status = ", &status); //####
    ODL_X1("leadByte = ", leadByte); //####
    int64_t result = 0;

    if (DataKind::Integer == (leadByte & DataKind::Mask))
    {
        bool    isShort = (DataKind::IntegerShortValue == (DataKind::IntegerSizeMask & leadByte));

        ++position; // We can accept the lead byte
        ODL_I1("position <- ", position); //####
        if (isShort)
        {
            ODL_LOG("(isShort)"); //####
            DataKind    shortBits = (DataKind::IntegerShortValueValueMask & leadByte);
            bool        isNegative = (DataKind::IntegerShortValueSignBit == (DataKind::IntegerShortValueSignBit & leadByte));

            if (isNegative)
            {
                ODL_LOG("(isNegative)"); //####
                int64_t tempValue = (-1 & (~ toUType(DataKind::IntegerShortValueValueMask)));

                result = (tempValue | toUType(shortBits));
            }
            else
            {
                ODL_LOG("! (isNegative)"); //####
                result = toUType(shortBits);
            }
            status = IntStatus::Successful;
            ODL_I1("status <- ", toUType(status)); //####
        }
        else
        {
            ODL_LOG("! (isShort)"); //####
            size_t          size = toUType(DataKind::IntegerLongValueCountMask & leadByte) + 1;
            NumberAsBytes   holder;
            bool            atEnd;
            bool            okSoFar = true;

            for (size_t ii = 0; okSoFar && (size > ii); ++ii)
            {
                int aByte = theMessage.getByte(position, atEnd);

                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    status = IntStatus::Incomplete;
                    ODL_I1("status <- ", toUType(status)); //####
                    okSoFar = false;
                }
                else
                {
                    holder[ii] = StaticCast(uint8_t, aByte);
                    ++position;
                    ODL_I1("position <- ", position); //####
                }
            }
            if (okSoFar)
            {
                result = B2I(holder, size);
                status = IntStatus::Successful;
                ODL_I1("status <- ", toUType(status)); //####
            }
        }
    }
    else
    {
        ODL_LOG("! (DataKind::Integer == (leadByte & DataKind::Mask))"); //####
        status = IntStatus::Invalid;
        ODL_I1("status <- ", toUType(status)); //####
    }
    ODL_EXIT_I(result); //####
    return result;
} // nImO::Value::extractInt64FromMessage

nImO::DataKind
nImO::Value::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result = StaticCast(DataKind, 0);

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Value::getTypeTag

nImO::SpValue
nImO::Value::getValueFromMessage
    (const nImO::Message &  inMessage,
     size_t &               position,
     const int              leadByte,
     nImO::SpArray          parent)
{
    ODL_ENTER(); //####
    ODL_P3("inMessage = ", &inMessage, "position = ", &position, "parent = ", parent.get()); //####
    ODL_X1("leadByte = ", leadByte); //####
    SpValue result;
    auto    match{gExtractors.find(StaticCast(uint8_t, leadByte))};

    if (gExtractors.end() == match)
    {
        ODL_LOG("(gExtractors.end() == match)"); //####
        result.reset(new Invalid("Unexpected character in Message @", position));
    }
    else
    {
        Extractor   handler = match->second;

        if (nullptr == handler)
        {
            ODL_LOG("(nullptr == handler)"); //####
            result.reset(new Invalid("No handler for character in Message @", position));
        }
        else
        {
            result = handler(inMessage, leadByte, position, parent);
            ODL_P1("result <- ", result.get()); //####
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Value::getValueFromMessage

nImO::ComparisonStatus
nImO::Value::greaterThan
    (const nImO::Value &    NOT_USED_(other))
    const
{
    ODL_OBJENTER(); //####
    ComparisonStatus    result(false, false);

    //ODL_P1("other = ", &other); //####
    ODL_OBJEXIT();
    return result;
} // nImO::Value::greaterThan

nImO::ComparisonStatus
nImO::Value::greaterThanOrEqual
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        result.clear();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Value::greaterThanOrEqual

void
nImO::Value::initialize
    (void)
{
    ODL_ENTER(); //####
    const char *    prefixes = Logical::getInitialCharacters();

    if (nullptr != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue   aValue(*prefixes, &Logical::readFromStringBuffer);

            gReaders.emplace(aValue);
        }
    }
    prefixes = Number::getInitialCharacters();
    if (nullptr != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue   aValue(*prefixes, &Number::readFromStringBuffer);

            gReaders.emplace(aValue);
        }
    }
    prefixes = String::getInitialCharacters();
    if (nullptr != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue   aValue(*prefixes, &String::readFromStringBuffer);

            gReaders.emplace(aValue);
        }
    }
    prefixes = Array::getInitialCharacters();
    if (nullptr != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue   aValue(*prefixes, &Array::readFromStringBuffer);

            gReaders.emplace(aValue);
        }
    }
    prefixes = Map::getInitialCharacters();
    if (nullptr != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue   aValue(*prefixes, &Map::readFromStringBuffer);

            gReaders.emplace(aValue);
        }
    }
    prefixes = Set::getInitialCharacters();
    if (nullptr != prefixes)
    {
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue   aValue(*prefixes, &Set::readFromStringBuffer);

            gReaders.emplace(aValue);
        }
    }
    const char *    suffixes = Array::getTerminalCharacters();

    gTerminators = suffixes;
    suffixes = Map::getTerminalCharacters();
    if (nullptr != suffixes)
    {
        gTerminators += suffixes;
    }
    suffixes = Set::getTerminalCharacters();
    if (nullptr != suffixes)
    {
        gTerminators += suffixes;
    }
    DataKind    aByte = StaticCast(DataKind, 0);
    DataKind    aMask = StaticCast(DataKind, 0);
    Extractor   theExtractor = nullptr;

    Array::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Blob::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Double::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Integer::getExtractionInfo(aByte, aMask, theExtractor);
    addToExtractionMap(aByte, aMask, theExtractor);
    Logical::getExtractionInfo(aByte, aMask, theExtractor);
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
nImO::Value::isLegalTerminator
    (const char aChar)
{
    ODL_ENTER(); //####
    ODL_C1("aChar = ", aChar); //####
    bool    result;

    if (isspace(aChar))
    {
        result = true;
    }
    else if (gTerminators.npos == gTerminators.find(aChar))
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

nImO::ComparisonStatus
nImO::Value::lessThan
    (const nImO::Value &    NOT_USED_(other))
    const
{
    ODL_OBJENTER(); //####
    ComparisonStatus    result(false, false);

    //ODL_P1("other = ", &other); //####
    ODL_OBJEXIT();
    return result;
} // nImO::Value::lessThan

nImO::ComparisonStatus
nImO::Value::lessThanOrEqual
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        result.clear();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Value::lessThanOrEqual

std::ostream &
nImO::Value::operator <<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    std::ios_base::fmtflags  originalFormat = out.flags();

    out << std::hex << "0x" << ReinterpretCast(int64_t, this);
    out.flags(originalFormat);
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Value::operator <<

void
nImO::Value::printToStringBuffer
    (nImO::StringBuffer &   NOT_USED_(outBuffer),
     const bool             NOT_USED_(squished))
    const
{
    ODL_OBJENTER(); //####
    //ODL_P1("outBuffer = ", &outBuffer); //####
    //ODL_B1("squished = ", squished); //####
    ODL_OBJEXIT(); //####
} // nImO::Value::printToStringBuffer

nImO::SpValue
nImO::Value::readFromStringBuffer
    (const nImO::StringBuffer & inBuffer,
     size_t &                   position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    SpValue result;
    size_t  localIndex = position;
    bool    atEnd;
    int     aChar = inBuffer.getChar(localIndex, atEnd);

    // Skip over whitespace
    for ( ; (! atEnd) && isspace(aChar); )
    {
        aChar = inBuffer.getChar(++localIndex, atEnd);
    }
    if (atEnd)
    {
        ODL_LOG("(atEnd)"); //####
    }
    else
    {
        auto    match{gReaders.find(aChar)};

        if (gReaders.end() == match)
        {
            ODL_LOG("(gReaders.end() == match)"); //####
        }
        else
        {
            BufferReader    handler{match->second};

            if (nullptr == handler)
            {
                ODL_LOG("(nullptr == handler)"); //####
            }
            else
            {
                result = handler(inBuffer, localIndex);
                if (nullptr == result)
                {
                    ODL_LOG("(nullptr == result)"); //####
                }
                else
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
nImO::Value::writeInt64ToMessage
    (nImO::Message &    outMessage,
     const int64_t      outValue)
{
    ODL_ENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    ODL_I1("outValue = ", outValue); //####
    if ((DataKindIntegerShortValueMinValue <= outValue) &&
        (DataKindIntegerShortValueMaxValue >= outValue))
    {
        ODL_LOG("((DataKindIntegerShortValueMinValue <= outValue) && " //####
                "(DataKindIntegerShortValueMaxValue >= outValue))"); //####
        DataKind    stuff = (DataKind::Integer | DataKind::IntegerShortValue |
                              (StaticCast(DataKind, outValue) &
                               DataKind::IntegerShortValueValueMask));

        outMessage.appendBytes(&stuff, sizeof(stuff));
    }
    else
    {
        ODL_LOG("! ((DataKindIntegerShortValueMinValue <= outValue) && " //####
                "(DataKindIntegerShortValueMaxValue >= outValue))"); //####
        NumberAsBytes   numBuff;
        size_t          numBytes = I2B(outValue, numBuff);

        if (0 < numBytes)
        {
            ODL_LOG("(0 < numBytes)"); //####
            DataKind    stuff = (DataKind::Integer | DataKind::IntegerLongValue |
                                  (StaticCast(DataKind, numBytes - 1) &
                                   DataKind::IntegerLongValueCountMask));

            outMessage.appendBytes(&stuff, sizeof(stuff));
            outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
        }
    }
    ODL_EXIT(); //####
} // nImO::Value::writeInt64ToMessage

void
nImO::Value::writeToMessage
    (nImO::Message &    NOT_USED_(outMessage))
    const
{
    ODL_OBJENTER(); //####
    //ODL_P1("outMessage = ", &outMessage); //####
    ODL_OBJEXIT(); //####
} // nImO::Value::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

std::ostream &
nImO::operator <<
    (std::ostream &         out,
     const nImO::Value &    aValue)
{
    ODL_ENTER(); //###
    ODL_P2("out = ", &out, "aValue = ", &aValue); //####
    aValue.operator<<(out);
    ODL_EXIT_P(&out); //####
    return out;
} // nImO::operator <<

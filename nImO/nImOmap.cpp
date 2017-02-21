//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOmap.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO maps.
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

#include "nImOmap.hpp"

#include <nImO/nImOarray.hpp>
#include <nImO/nImOinteger.hpp>
#include <nImO/nImOmessage.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO maps. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

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

nImO::Map::Map(void) :
    inherited1(), inherited2(), _keyKind(Enumerable::Unknown)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Map::

nImO::Map::Map(const nImO::Map &other) :
    inherited1(), inherited2(), _keyKind(Enumerable::Unknown)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Map::Map

nImO::Map::~Map(void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Map::~Map

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Map::addEntries(const nImO::Map &other)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    if ((other._keyKind == _keyKind) || (Enumerable::Unknown == _keyKind))
    {
        for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
        {
            MapValue aValue = *walker;
            SpValue  key(aValue.first);
            SpValue  mappedValue(aValue.second);

            addValue(key, mappedValue);
        }
    }
    ODL_EXIT(); //####
} // nImO::Map::addEntries

nImO::Map::InsertResult
nImO::Map::addValue(nImO::SpValue newKey,
                    nImO::SpValue newValue)
{
    ODL_OBJENTER(); //####
    ODL_P2("newKey = ", newKey.get(), "newValue = ", newValue.get()); //####
    InsertResult result;

    if ((nullptr == newKey) || (nullptr == newValue))
    {
        result = InsertResult(inherited2::end(), false);
    }
    else
    {
        if (Enumerable::Unknown == _keyKind)
        {
            _keyKind = newKey->enumerationType();
        }
        if (newKey->enumerationType() == _keyKind)
        {
            MapValue keyValue(newKey, newValue);

            result = inherited2::insert(keyValue);
        }
        else
        {
            result = InsertResult(inherited2::end(), false);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::addValue

void
nImO::Map::clear(void)
{
    ODL_OBJENTER(); //####
    inherited2::clear();
    _keyKind = Enumerable::Unknown;
    ODL_OBJEXIT(); //####
} // nImO::Map::clear

bool
nImO::Map::deeplyEqualTo(const nImO::Value &other)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result = (&other == this);
    
    if (! result)
    {
        const Map *otherPtr = other.asMap();
        
        if (otherPtr && (size() == otherPtr->size()))
        {
            const_iterator thisWalker(inherited2::begin());
            const_iterator otherWalker(otherPtr->inherited2::begin());
            
            for (result = true; result && (thisWalker != inherited2::end());
                 ++thisWalker, ++otherWalker)
            {
                SpValue thisKey(thisWalker->first);
                SpValue otherKey(otherWalker->first);
                
                if ((nullptr != thisKey) && (nullptr != otherKey))
                {
                    result = thisKey->deeplyEqualTo(*otherKey);
                    if (result)
                    {
                        SpValue thisValue(thisWalker->second);
                        SpValue otherValue(otherWalker->second);
                        
                        if ((nullptr != thisValue) && (nullptr != otherValue))
                        {
                            result = thisValue->deeplyEqualTo(*otherValue);
                        }
                        else
                        {
                            result = false;
                        }
                    }
                }
                else
                {
                    result = false;
                }
            }
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Map::deeplyEqualTo

bool
nImO::Map::equalTo(const nImO::Value &other,
                   bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (Enumerable::Unknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(walker->first);

        if (aValue)
        {
            result &= aValue->equalTo(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::equalTo

nImO::SpValue
nImO::Map::extractValue(const nImO::Message &theMessage,
                        const int           leadByte,
                        size_t              &position,
                        nImO::ReadStatus    &status,
                        nImO::SpArray       parentValue)
{
    ODL_ENTER(); //####
    ODL_P4("theMessage = ", &theMessage, "position = ", &position, "status = ", &status, //####
           "parentValue = ", parentValue.get()); //####
    ODL_XL1("leadByte = ", leadByte); //####
    SpValue result;
    bool    isEmpty = (static_cast<int>(DataKind::OtherContainerEmptyValue) == (static_cast<int>(DataKind::OtherContainerEmptyMask) & leadByte));
    int     aByte;

    ++position; // We will always accept the lead byte
    ODL_LL1("position <- ", position); //####
    if (isEmpty)
    {
        ODL_LOG("(isEmpty)"); //####
        aByte = theMessage.getByte(position);
        ODL_XL1("aByte <- ", aByte); //####
        if (Message::kEndToken == aByte)
        {
            ODL_LOG("(Message::kEndToken == aByte)"); //####
            status = ReadStatus::Incomplete;
            ODL_LL1("status <- ", static_cast<int>(status)); //####
        }
        else
        {
            ODL_LOG("! (Message::kEndToken == aByte)"); //####
            static const uint8_t endMarker = (static_cast<uint8_t>(DataKind::Other) + static_cast<uint8_t>(DataKind::OtherContainerEnd) +
                                              static_cast<uint8_t>(DataKind::OtherContainerTypeMap) +
                                              static_cast<uint8_t>(DataKind::OtherContainerEmptyValue));

            if (endMarker == aByte)
            {
                ODL_LOG("(endMarker == aByte)"); //####
                result.reset(new Map);
                status = ReadStatus::Successful;
                ++position;
                ODL_LL2("status <- ", static_cast<int>(status), "position <- ", position); //####
            }
            else
            {
                ODL_LOG("! (endMarker == aByte)"); //####
                status = ReadStatus::Invalid;
                ODL_LL1("status <- ", static_cast<int>(status)); //####
            }
        }
    }
    else
    {
        ODL_LOG("! (isEmpty)"); //####
        aByte = theMessage.getByte(position);
        ODL_XL1("aByte <- ", aByte); //####
        if (Message::kEndToken == aByte)
        {
            ODL_LOG("(Message::kEndToken == aByte)"); //####
            status = ReadStatus::Incomplete;
            ODL_LL1("status <- ", static_cast<int>(status)); //####
        }
        else
        {
            ODL_LOG("! (Message::kEndToken == aByte)"); //####
            int64_t elementCount = extractInt64FromMessage(theMessage, aByte, position, status);

            if (ReadStatus::Successful == status)
            {
                ODL_LOG("(ReadStatus::Successful == status)"); //####
                elementCount -= DataKindIntegerShortValueMinValue - 1;
                ODL_LL1("elementCount <- ", elementCount); //####
                if (0 >= elementCount)
                {
                    ODL_LOG("(0 >= elementCount)"); //####
                    status = ReadStatus::Invalid;
                    ODL_LL1("status <- ", static_cast<int>(status)); //####
                }
                else
                {
                    SpMap aMap(new Map);

                    result = aMap;
                    if (nullptr == result)
                    {
                        ODL_LOG("(nullptr == result)"); //####
                        status = ReadStatus::Invalid;
                        ODL_LL1("status <- ", static_cast<int>(status)); //####
                    }
                    else
                    {
                        bool okSoFar = true;

                        for ( ; okSoFar && (elementCount > static_cast<int64_t>(aMap->size())); )
                        {
                            aByte = theMessage.getByte(position);
                            ODL_XL1("aByte <- ", aByte); //####
                            if (Message::kEndToken == aByte)
                            {
                                ODL_LOG("(Message::kEndToken == aByte)"); //####
                                status = ReadStatus::Incomplete;
                                okSoFar = false;
                            }
                            else
                            {
                                SpValue kValue(getValueFromMessage(theMessage, position, aByte,
                                                                   status, nullptr));

                                if (nullptr == kValue)
                                {
                                    ODL_LOG("(nullptr == aValue)"); //####
                                    okSoFar = false;
                                }
                                else
                                {
                                    ODL_LOG("! (nullptr == aValue)"); //####
                                    aByte = theMessage.getByte(position);
                                    ODL_XL1("aByte <- ", aByte); //####
                                    if (Message::kEndToken == aByte)
                                    {
                                        ODL_LOG("(Message::kEndToken == aByte)"); //####
                                        status = ReadStatus::Incomplete;
                                        okSoFar = false;
                                    }
                                    else
                                    {
                                        SpValue vValue(getValueFromMessage(theMessage, position,
                                                                           aByte, status, nullptr));

                                        if (nullptr == vValue)
                                        {
                                            ODL_LOG("(nullptr == aValue)"); //####
                                            okSoFar = false;
                                        }
                                        else
                                        {
                                            ODL_LOG("! (nullptr == aValue)"); //####
                                            aMap->addValue(kValue, vValue);
                                        }
                                    }
                                }
                            }
                        }
                        if (okSoFar)
                        {
                            aByte = theMessage.getByte(position);
                            ODL_XL1("aByte <- ", aByte); //####
                            if (Message::kEndToken == aByte)
                            {
                                ODL_LOG("(Message::kEndToken == aByte)"); //####
                                status = ReadStatus::Incomplete;
                                ODL_LL1("status <- ", static_cast<int>(status)); //####
                                okSoFar = false;
                            }
                            else
                            {
                                ODL_LOG("! (Message::kEndToken == aByte)"); //####
                                static const uint8_t endMarker = (static_cast<uint8_t>(DataKind::Other) +
                                                                  static_cast<uint8_t>(DataKind::OtherContainerEnd) +
                                                                  static_cast<uint8_t>(DataKind::OtherContainerTypeMap) +
                                                                  static_cast<uint8_t>(DataKind::OtherContainerNonEmptyValue));
                    
                                if (endMarker == aByte)
                                {
                                    ODL_LOG("(endMarker == aByte)"); //####
                                    status = ReadStatus::Successful;
                                    ++position;
                                    ODL_LL2("status <- ", static_cast<int>(status), "position <- ", position); //####
                                }
                                else
                                {
                                    ODL_LOG("! (endMarker == aByte)"); //####
                                    status = ReadStatus::Invalid;
                                    ODL_LL1("status <- ", static_cast<int>(status)); //####
                                    okSoFar = false;
                                }
                            }
                        }
                        if (! okSoFar)
                        {
                            ODL_LOG("(! okSoFar)"); //####
                            result.reset();
                        }
                    }
                }
            }
            else
            {
                ODL_LOG("! (ReadStatus::Successful == status)"); //####
            }
        }
    }
    if ((nullptr != parentValue) && (nullptr != result))
    {
        ODL_LOG("((nullptr != parentValue) && (nullptr != result))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Map::extractValue

nImO::Map::iterator
nImO::Map::find(nImO::SpValue key)
{
    ODL_OBJENTER(); //####
    ODL_P1("key = ", &key); //####
    iterator result;

    if (key->enumerationType() == _keyKind)
    {
        result = inherited2::find(key);
    }
    else
    {
        result = inherited2::end();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::find

nImO::Map::const_iterator
nImO::Map::find(const nImO::SpValue key)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("key = ", &key); //####
    const_iterator result;

    if (key->enumerationType() == _keyKind)
    {
        result = inherited2::find(key);
    }
    else
    {
        result = inherited2::end();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::find

void
nImO::Map::getExtractionInfo(uint8_t                &aByte,
                             uint8_t                &aMask,
                             nImO::Value::Extractor &theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (static_cast<uint8_t>(DataKind::Other) | static_cast<uint8_t>(DataKind::OtherContainerStart) | static_cast<uint8_t>(DataKind::OtherContainerTypeMap));
    aMask = (static_cast<uint8_t>(DataKind::Mask) | static_cast<uint8_t>(DataKind::OtherTypeMask) | static_cast<uint8_t>(DataKind::OtherContainerTypeMask));
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Map::getExtractionInfo

const char *
nImO::Map::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char initialChars[] = { kStartMapChar, '\0' };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Map::getInitialCharacters

const char *
nImO::Map::getTerminalCharacters(void)
{
    ODL_ENTER(); //####
    static const char terminalChars[] = { kEndMapChar, kKeyValueSeparator, '\0' };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Map::getTerminalCharacters

bool
nImO::Map::greaterThan(const nImO::Value &other,
                       bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (Enumerable::Unknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(walker->first);

        if (aValue)
        {
            result &= aValue->greaterThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::greaterThan

bool
nImO::Map::greaterThanOrEqual(const nImO::Value &other,
                              bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (Enumerable::Unknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(walker->first);

        if (aValue)
        {
            result &= aValue->greaterThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::greaterThanOrEqual

bool
nImO::Map::lessThan(const nImO::Value &other,
                    bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (Enumerable::Unknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(walker->first);

        if (aValue)
        {
            result &= aValue->lessThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::lessThan

bool
nImO::Map::lessThanOrEqual(const nImO::Value &other,
                           bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (Enumerable::Unknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(walker->first);

        if (aValue)
        {
            result &= aValue->lessThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::lessThanOrEqual

nImO::Map &
nImO::Map::operator =(const nImO::Map &other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        clear();
        addEntries(other);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Map::operator=

void
nImO::Map::printToStringBuffer(nImO::StringBuffer &outBuffer,
                               const bool         squished)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    bool first = true;

    outBuffer.addChar(kStartMapChar);
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        MapValue aValue = *walker;

        if ((! squished) || (! first))
        {
            outBuffer.addChar(' ');
        }
        aValue.first->printToStringBuffer(outBuffer);
        if (! squished)
        {
            outBuffer.addChar(' ');
        }
        outBuffer.addChar(kKeyValueSeparator);
        if (! squished)
        {
            outBuffer.addChar(' ');
        }
        aValue.second->printToStringBuffer(outBuffer);
        first = false;
    }
    if (! squished)
    {
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndMapChar);
    ODL_OBJEXIT(); //####
} // nImO::Map::printToStringBuffer

nImO::SpValue
nImO::Map::readFromStringBuffer(const nImO::StringBuffer &inBuffer,
                                size_t                   &position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    bool   done = false;
    bool   valid = false;
    SpMap  result(new Map);
    size_t localIndex = position;
    int    aChar = inBuffer.getChar(localIndex++);

    ODL_P1("result <- ", result.get()); //####
    ODL_C1("aChar <- ", aChar); //####
    ODL_LL1("localIndex <- ", localIndex); //####
    if (kStartMapChar == aChar)
    {
        for ( ; ! done; )
        {
            // Skip whitespace
            for (aChar = inBuffer.getChar(localIndex); isspace(aChar);
                 aChar = inBuffer.getChar(++localIndex))
            {
                ODL_LL1("localIndex <- ", localIndex); //####
                ODL_C1("aChar <- ", aChar); //####
            }
            ODL_LL1("localIndex = ", localIndex); //####
            ODL_C1("aChar = ", aChar); //####
            // Check for the closing bracket
            if (StringBuffer::kEndToken == aChar)
            {
                ODL_LOG("(StringBuffer::kEndToken == aChar)"); //####
                done = true;
            }
            else if (kEndMapChar == aChar)
            {
                done = valid = true;
            }
            else
            {
                SpValue keyValue(Value::readFromStringBuffer(inBuffer, localIndex));

                ODL_LL1("localIndex <- ", localIndex); //####
                if (nullptr == keyValue)
                {
                    ODL_LOG("(nullptr == keyValue)"); //####
                    done = true;
                }
                else
                {
                    Enumerable elementType = keyValue->enumerationType();

                    if ((Enumerable::Unknown == elementType) ||
                        (Enumerable::NotEnumerable == elementType))
                    {
                        ODL_LOG("((Enumerable::Unknown == elementType) || " //####
                                "(Enumerable::NotEnumerable == elementType))"); //####
                        keyValue.reset();
                        done = true;
                    }
                    else if (0 < result->size())
                    {
                        if (result->_keyKind != elementType)
                        {
                            ODL_LOG("(result->_keyKind != elementType)"); //####
                            keyValue.reset();
                            done = true;
                        }
                    }
                }
                if (nullptr != keyValue)
                {
                    // Skip whitespace
                    for (aChar = inBuffer.getChar(localIndex); isspace(aChar);
                         aChar = inBuffer.getChar(++localIndex))
                    {
                        ODL_LL1("localIndex <- ", localIndex); //####
                        ODL_C1("aChar <- ", aChar); //####
                    }
                    ODL_LL1("localIndex = ", localIndex); //####
                    ODL_C1("aChar = ", aChar); //####
                    // Check for the closing bracket
                    if (StringBuffer::kEndToken == aChar)
                    {
                        ODL_LOG("(StringBuffer::kEndToken == aChar)"); //####
                        done = true;
                    }
                    else if (kEndMapChar == aChar)
                    {
                        ODL_LOG("(kEndMapChar == aChar)"); //####
                        done = true;
                    }
                    else if (kKeyValueSeparator == aChar)
                    {
                        ++localIndex;
                        SpValue assocValue(Value::readFromStringBuffer(inBuffer, localIndex));

                        if (nullptr == assocValue)
                        {
                            ODL_LOG("(nullptr == assocValue)"); //####
                            done = true;
                        }
                        else
                        {
                            result->addValue(keyValue, assocValue);
                        }
                    }
                }
            }
        }
    }
    else
    {
        ODL_LOG("! (kStartMapChar == aChar)"); //####
    }
    if (valid)
    {
        position = localIndex + 1;
    }
    else
    {
        ODL_LOG("! (valid)"); //####
        result.reset();
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Map::readFromStringBuffer

void
nImO::Map::writeToMessage(nImO::Message &outMessage)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    if (0 < inherited2::size())
    {
        ODL_LOG("(0 < inherited2::size())"); //####
        uint8_t startMap = static_cast<uint8_t>(DataKind::Other) + static_cast<uint8_t>(DataKind::OtherContainerStart) +
                             static_cast<uint8_t>(DataKind::OtherContainerTypeMap) +
                             static_cast<uint8_t>(DataKind::OtherContainerNonEmptyValue);
        uint8_t endMap = static_cast<uint8_t>(DataKind::Other) + static_cast<uint8_t>(DataKind::OtherContainerEnd) +
                           static_cast<uint8_t>(DataKind::OtherContainerTypeMap) +
                           static_cast<uint8_t>(DataKind::OtherContainerNonEmptyValue);

        outMessage.appendBytes(&startMap, sizeof(startMap));
        writeInt64ToMessage(outMessage, inherited2::size() + DataKindIntegerShortValueMinValue - 1);
        for (const_iterator walker(inherited2::begin()); (inherited2::end() != walker); ++walker)
        {
            MapValue aValue = *walker;

            aValue.first->writeToMessage(outMessage);
            aValue.second->writeToMessage(outMessage);
        }
        outMessage.appendBytes(&endMap, sizeof(endMap)); 
    }
    else
    {
        ODL_LOG("! (0 < inherited2::size())"); //####
        static const uint8_t stuff[] =
        {
            static_cast<uint8_t>(DataKind::Other) + static_cast<uint8_t>(DataKind::OtherContainerStart) + static_cast<uint8_t>(DataKind::OtherContainerTypeMap) +
              static_cast<uint8_t>(DataKind::OtherContainerEmptyValue),
            static_cast<uint8_t>(DataKind::Other) + static_cast<uint8_t>(DataKind::OtherContainerEnd) + static_cast<uint8_t>(DataKind::OtherContainerTypeMap) +
              static_cast<uint8_t>(DataKind::OtherContainerEmptyValue)
        };

        outMessage.appendBytes(stuff, sizeof(stuff));
    }
    ODL_OBJEXIT(); //####
} // nImO::Map::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

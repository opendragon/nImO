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

#include <nImOarray.hpp>
#include <nImOinteger.hpp>
#include <nImOinvalid.hpp>
#include <nImOmessage.hpp>
#include <nImOstringBuffer.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

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

nImO::Map::Map
    (void) :
        inherited1(), inherited2(), _keyKind(Enumerable::Unknown)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Map::

nImO::Map::Map
    (const nImO::Map &  other) :
        inherited1(), inherited2(), _keyKind(Enumerable::Unknown)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Map::Map

nImO::Map::~Map
    (void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Map::~Map

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Map::addEntries
    (const nImO::Map &  other)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    if ((other._keyKind == _keyKind) || (Enumerable::Unknown == _keyKind))
    {
        for (auto & walker : other)
        {
            SpValue key{walker.first};
            SpValue mappedValue{walker.second};

            addValue(key, mappedValue);
        }
    }
    ODL_EXIT(); //####
} // nImO::Map::addEntries

nImO::Map::InsertResult
nImO::Map::addValue
    (nImO::SpValue  newKey,
     nImO::SpValue  newValue)
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

            result = inherited2::emplace(keyValue);
        }
        else
        {
            result = InsertResult(inherited2::end(), false);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::addValue

const nImO::Map *
nImO::Map::asMap
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Map::asMap

bool
nImO::Map::deeplyEqualTo
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result = (&other == this);

    if (! result)
    {
        const Map * otherPtr = other.asMap();

        if (otherPtr && (size() == otherPtr->size()))
        {
            auto    thisWalker{inherited2::begin()};
            auto    otherWalker{otherPtr->inherited2::begin()};

            for (result = true; result && (thisWalker != inherited2::end()); ++thisWalker, ++otherWalker)
            {
                SpValue thisKey{thisWalker->first};
                SpValue otherKey{otherWalker->first};

                if ((nullptr != thisKey) && (nullptr != otherKey))
                {
                    result = thisKey->deeplyEqualTo(*otherKey);
                    if (result)
                    {
                        SpValue thisValue{thisWalker->second};
                        SpValue otherValue{otherWalker->second};

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

nImO::ComparisonStatus
nImO::Map::equalTo
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
            {
                SpValue aValue{walker->first};

                if (aValue)
                {
                    result &= aValue->equalTo(other);
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::equalTo

nImO::SpValue
nImO::Map::extractValue
    (const nImO::Message &  theMessage,
     const int              leadByte,
     size_t &               position,
     nImO::SpArray          parentValue)
{
    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "parentValue = ", //####
           parentValue.get()); //####
    ODL_X1("leadByte = ", leadByte); //####
    SpValue result;
    bool    atEnd;
    bool    isEmpty = (DataKind::OtherContainerEmptyValue == (DataKind::OtherContainerEmptyMask & leadByte));
    int     aByte;

    ++position; // We will always accept the lead byte
    ODL_I1("position <- ", position); //####
    if (isEmpty)
    {
        ODL_LOG("(isEmpty)"); //####
        aByte = theMessage.getByte(position, atEnd);
        ODL_X1("aByte <- ", aByte); //####
        ODL_B1("atEnd <- ", atEnd); //####
        if (atEnd)
        {
            ODL_LOG("(atEnd)"); //####
        }
        else
        {
            ODL_LOG("! (atEnd)"); //####
            static const DataKind   endMarker = (DataKind::Other | DataKind::OtherContainerEnd |
                                                 DataKind::OtherContainerTypeMap | DataKind::OtherContainerEmptyValue);

            if (toUType(endMarker) == aByte)
            {
                ODL_LOG("(toUType(endMarker) == aByte)"); //####
                result.reset(new Map);
                ++position;
                ODL_I1("position <- ", position); //####
            }
            else
            {
                ODL_LOG("! (toUType(endMarker) == aByte)"); //####
                result.reset(new Invalid("Empty Map with incorrect end tag @", position));
            }
        }
    }
    else
    {
        ODL_LOG("! (isEmpty)"); //####
        aByte = theMessage.getByte(position, atEnd);
        ODL_X1("aByte <- ", aByte); //####
        ODL_B1("atEnd <- ", atEnd); //####
        if (atEnd)
        {
            ODL_LOG("(atEnd)"); //####
        }
        else
        {
            ODL_LOG("! (atEnd)"); //####
            IntStatus   numStatus;
            int64_t     elementCount = extractInt64FromMessage(theMessage, aByte, position, numStatus);

            if (IntStatus::Successful == numStatus)
            {
                ODL_LOG("(IntStatus::Successful == status)"); //####
                elementCount -= DataKindIntegerShortValueMinValue - 1;
                ODL_I1("elementCount <- ", elementCount); //####
                if (0 >= elementCount)
                {
                    ODL_LOG("(0 >= elementCount)"); //####
                    result.reset(new Invalid("Map with zero or negative count @", position));
                }
                else
                {
                    auto    aMap{std::make_shared<Map>()};

                    result = aMap;
                    if (nullptr == result)
                    {
                        ODL_LOG("(nullptr == result)"); //####
                        result.reset(new Invalid("Could not allocate a Map"));
                    }
                    else
                    {
                        bool    okSoFar = true;

                        for ( ; okSoFar && (elementCount > StaticCast(int64_t, aMap->size())); )
                        {
                            aByte = theMessage.getByte(position, atEnd);
                            ODL_X1("aByte <- ", aByte); //####
                            ODL_B1("atEnd <- ", atEnd); //####
                            if (atEnd)
                            {
                                ODL_LOG("(atEnd)"); //####
                                result.reset();
                                okSoFar = false;
                            }
                            else
                            {
                                SpValue keyValue{getValueFromMessage(theMessage, position, aByte, nullptr)};

                                if (nullptr == keyValue)
                                {
                                    ODL_LOG("(nullptr == aValue)"); //####
                                    result.reset(new Invalid("Null key Value read @", position));
                                    okSoFar = false;
                                }
                                else if (keyValue->asFlaw())
                                {
                                    ODL_LOG("(keyValue->asFlaw())"); //####
                                    result = keyValue;
                                    okSoFar = false;
                                }
                                else
                                {
                                    ODL_LOG("! (keyValue->asFlaw())"); //####
                                    aByte = theMessage.getByte(position, atEnd);
                                    ODL_X1("aByte <- ", aByte); //####
                                    ODL_B1("atEnd <- ", atEnd); //####
                                    if (atEnd)
                                    {
                                        ODL_LOG("(atEnd)"); //####
                                        result.reset();
                                        okSoFar = false;
                                    }
                                    else
                                    {
                                        SpValue vValue{getValueFromMessage(theMessage, position, aByte, nullptr)};

                                        if (nullptr == vValue)
                                        {
                                            ODL_LOG("(nullptr == aValue)"); //####
                                            result.reset(new Invalid("Null value Value read @", position));
                                            okSoFar = false;
                                        }
                                        else if (vValue->asFlaw())
                                        {
                                            ODL_LOG("(vValue->asFlaw())"); //####
                                            result = vValue;
                                            okSoFar = false;
                                        }
                                        else
                                        {
                                            ODL_LOG("! (vValue->asFlaw())"); //####
                                            aMap->addValue(keyValue, vValue);
                                        }
                                    }
                                }
                            }
                        }
                        if (okSoFar)
                        {
                            aByte = theMessage.getByte(position, atEnd);
                            ODL_X1("aByte <- ", aByte); //####
                            ODL_B1("atEnd <- ", atEnd); //####
                            if (atEnd)
                            {
                                ODL_LOG("(atEnd)"); //####
                                result.reset();
                                okSoFar = false;
                            }
                            else
                            {
                                ODL_LOG("! (atEnd)"); //####
                                static const DataKind   endMarker = (DataKind::Other | DataKind::OtherContainerEnd |
                                                                     DataKind::OtherContainerTypeMap |
                                                                     DataKind::OtherContainerNonEmptyValue);

                                if (toUType(endMarker) == aByte)
                                {
                                    ODL_LOG("(toUType(endMarker) == aByte)"); //####
                                    ++position;
                                    ODL_I1("position <- ", position); //####
                                }
                                else
                                {
                                    ODL_LOG("! (toUType(endMarker) == aByte)"); //####
                                    result.reset(new Invalid("Non-empty Map with incorrect end tag @", position));
                                    okSoFar = false;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                ODL_LOG("! (IntStatus::Successful == status)"); //####
            }
        }
    }
    if ((nullptr != parentValue) && (nullptr != result) && (! result->asFlaw()))
    {
        ODL_LOG("((nullptr != parentValue) && (nullptr != result) && (! result->asFlaw()))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Map::extractValue

void
nImO::Map::getExtractionInfo
    (DataKind &                 aByte,
     DataKind &                 aMask,
     nImO::Value::Extractor &   theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeMap);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherContainerTypeMask);
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Map::getExtractionInfo

const char *
nImO::Map::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   initialChars[] = { kStartMapChar, '\0' };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Map::getInitialCharacters

const char *
nImO::Map::getTerminalCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   terminalChars[] = { kEndMapChar, kKeyValueSeparator, '\0' };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Map::getTerminalCharacters

nImO::DataKind
nImO::Map::getTypeTag
    (void)
    const
{
    ODL_OBJENTER();
    DataKind    result = DataKind::OtherMessageExpectedOtherValue;

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Map::getTypeTag

nImO::ComparisonStatus
nImO::Map::greaterThan
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other == this)
    {
        result = false;
    }
    else if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
    {
        result.clear();
    }
    else
    {
        for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
        {
            SpValue aValue{walker->first};

            if (aValue)
            {
                result &= aValue->greaterThan(other);
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::greaterThan

nImO::ComparisonStatus
nImO::Map::greaterThanOrEqual
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
            {
                SpValue aValue{walker->first};

                if (aValue)
                {
                    result &= aValue->greaterThanOrEqual(other);
                }
            }
        }
    }
//    bool    result = ((other.enumerationType() == _keyKind) && (inherited2::begin() != inherited2::end()));
//
//    validComparison = (Enumerable::Unknown != _keyKind);
//    ODL_B1("validComparison <- ", validComparison); //####
//    for (auto walker(inherited2::begin()); validComparison && (inherited2::end() != walker); ++walker)
//    {
//        SpValue aValue{walker->first};
//
//        if (aValue)
//        {
//            result &= aValue->greaterThanOrEqual(other, validComparison);
//        }
//    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Map::lessThan
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other == this)
    {
        result = false;
    }
    else if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
    {
        result.clear();
    }
    else
    {
        for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
        {
            SpValue aValue{walker->first};

            if (aValue)
            {
                result &= aValue->lessThan(other);
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::lessThan

nImO::ComparisonStatus
nImO::Map::lessThanOrEqual
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
            {
                SpValue aValue{walker->first};

                if (aValue)
                {
                    result &= aValue->lessThanOrEqual(other);
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::lessThanOrEqual

std::ostream &
nImO::Map::operator <<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << kStartMapChar;
    for (auto & walker : *this)
    {
        out << " " << *walker.first << " " << kKeyValueSeparator << " " << *walker.second;
    }
    out << " " << kEndMapChar;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Map::operator <<

void
nImO::Map::printToStringBuffer
    (nImO::StringBuffer &   outBuffer,
     const bool             squished)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    bool    first = true;

    outBuffer.addChar(kStartMapChar);
    for (auto & walker : *this)
    {
        if ((! squished) || (! first))
        {
            outBuffer.addChar(' ');
        }
        walker.first->printToStringBuffer(outBuffer);
        if (! squished)
        {
            outBuffer.addChar(' ');
        }
        outBuffer.addChar(kKeyValueSeparator);
        if (! squished)
        {
            outBuffer.addChar(' ');
        }
        walker.second->printToStringBuffer(outBuffer);
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
nImO::Map::readFromStringBuffer
    (const nImO::StringBuffer & inBuffer,
     size_t &                   position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    bool    atEnd;
    bool    done = false;
    bool    valid = false;
    auto    result{std::make_shared<Map>()};
    size_t  localIndex = position;
    int     aChar = inBuffer.getChar(localIndex++, atEnd);

    ODL_P1("result <- ", result.get()); //####
    ODL_C1("aChar <- ", aChar); //####
    ODL_B1("atEnd <- ", atEnd); //####
    ODL_I1("localIndex <- ", localIndex); //####
    if ((! atEnd) && (kStartMapChar == aChar))
    {
        for ( ; ! done; )
        {
            // Skip whitespace
            for (aChar = inBuffer.getChar(localIndex, atEnd); (! atEnd) && isspace(aChar);
                 aChar = inBuffer.getChar(++localIndex, atEnd))
            {
                ODL_I1("localIndex <- ", localIndex); //####
                ODL_C1("aChar <- ", aChar); //####
                ODL_B1("atEnd <- ", atEnd); //####
            }
            ODL_I1("localIndex = ", localIndex); //####
            ODL_C1("aChar = ", aChar); //####
            // Check for the closing bracket
            if (atEnd)
            {
                ODL_LOG("(atEnd)"); //####
                done = true;
            }
            else if (kEndMapChar == aChar)
            {
                done = valid = true;
            }
            else
            {
                SpValue keyValue{Value::readFromStringBuffer(inBuffer, localIndex)};

                ODL_I1("localIndex <- ", localIndex); //####
                if (nullptr == keyValue)
                {
                    ODL_LOG("(nullptr == keyValue)"); //####
                    done = true;
                }
                else
                {
                    Enumerable  elementType = keyValue->enumerationType();

                    if ((Enumerable::Unknown == elementType) || (Enumerable::NotEnumerable == elementType))
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
                    for (aChar = inBuffer.getChar(localIndex, atEnd); (! atEnd) && isspace(aChar);
                         aChar = inBuffer.getChar(++localIndex, atEnd))
                    {
                        ODL_I1("localIndex <- ", localIndex); //####
                        ODL_C1("aChar <- ", aChar); //####
                    }
                    ODL_I1("localIndex = ", localIndex); //####
                    ODL_C1("aChar = ", aChar); //####
                    ODL_B1("atEnd <- ", atEnd); //####
                    // Check for the closing bracket
                    if (atEnd)
                    {
                        ODL_LOG("(atEnd)"); //####
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
                        SpValue assocValue{Value::readFromStringBuffer(inBuffer, localIndex)};

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
        ODL_LOG("! ((! atEnd) && (kStartMapChar == aChar))"); //####
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
nImO::Map::writeToMessage
    (nImO::Message &    outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    if (0 < inherited2::size())
    {
        ODL_LOG("(0 < inherited2::size())"); //####
        const DataKind  startMap = (DataKind::Other | DataKind::OtherContainerStart |
                                    DataKind::OtherContainerTypeMap |
                                    DataKind::OtherContainerNonEmptyValue);
        const DataKind  endMap = (DataKind::Other | DataKind::OtherContainerEnd |
                                  DataKind::OtherContainerTypeMap |
                                  DataKind::OtherContainerNonEmptyValue);

        outMessage.appendBytes(&startMap, sizeof(startMap));
        writeInt64ToMessage(outMessage, StaticCast(int, inherited2::size()) + DataKindIntegerShortValueMinValue - 1);
        for (auto & walker : *this)
        {
            walker.first->writeToMessage(outMessage);
            walker.second->writeToMessage(outMessage);
        }
        outMessage.appendBytes(&endMap, sizeof(endMap));
    }
    else
    {
        ODL_LOG("! (0 < inherited2::size())"); //####
        static const DataKind   stuff[] =
        {
            DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeMap |
              DataKind::OtherContainerEmptyValue,
            DataKind::Other | DataKind::OtherContainerEnd | DataKind::OtherContainerTypeMap |
              DataKind::OtherContainerEmptyValue
        };

        outMessage.appendBytes(stuff, sizeof(stuff));
    }
    ODL_OBJEXIT(); //####
} // nImO::Map::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

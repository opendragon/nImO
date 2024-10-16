//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOmap.cpp
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

#include <Containers/nImOmap.h>

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOinvalid.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmessage.h>
#include <Containers/nImOstringBuffer.h>

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
        inherited1{}, inherited2{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Map::

nImO::Map::Map
    (const Map &    other) :
        inherited1{}, inherited2{}, _keyKind{Enumerable::Unknown}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Map::Map

nImO::Map::Map
    (Map && other)
    noexcept:
        inherited1{std::move(other)}, inherited2{std::move(other)}, _keyKind{other._keyKind}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    addEntries(other);
    other.clear();
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
    (const Map &    other)
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
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
    (SpValue    newKey,
     SpValue    newValue)
{
    ODL_OBJENTER(); //####
    ODL_P2(newKey.get(), newValue.get()); //####
    InsertResult result;

    if (newKey && newValue)
    {
        if (Enumerable::Unknown == _keyKind)
        {
            _keyKind = newKey->enumerationType();
        }
        if (newKey->enumerationType() == _keyKind)
        {
            MapValue keyValue{newKey, newValue};

            result = inherited2::emplace(keyValue);
        }
        else
        {
            result = InsertResult(inherited2::end(), false);
        }
    }
    else
    {
        result = InsertResult(inherited2::end(), false);
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::addValue

CPtr(nImO::Map)
nImO::Map::asMap
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Map::asMap

void
nImO::Map::clear
    (void)
{
    ODL_OBJENTER(); //####
    inherited2::clear();
    _keyKind = Enumerable::Unknown;
    ODL_OBJEXIT(); //####
} // nImO::Map::clear

bool
nImO::Map::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    bool    result{&other == this};

    if (! result)
    {
        auto    otherPtr{other.asMap()};

        if ((nullptr != otherPtr) && (size() == otherPtr->size()))
        {
            auto    thisWalker{inherited2::begin()};
            auto    otherWalker{otherPtr->inherited2::begin()};

            for (result = true; result && (thisWalker != inherited2::end()); ++thisWalker, ++otherWalker)
            {
                auto    thisKey{thisWalker->first};
                auto    otherKey{otherWalker->first};

                if (thisKey && otherKey)
                {
                    result = thisKey->deeplyEqualTo(*otherKey);
                    if (0 != result)
                    {
                        auto    thisValue{thisWalker->second};
                        auto    otherValue{otherWalker->second};

                        if (thisValue && otherValue)
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

std::ostream &
nImO::Map::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&output); //####
    output << "map of " << size() << " elements and a key type of ";
    switch (_keyKind)
    {
        case Enumerable::Address :
            output << "address";
            break;

        case Enumerable::Logical :
            output << "logical";
            break;

        case Enumerable::Integer :
            output << "integer";
            break;

        case Enumerable::String :
            output << "string";
            break;

        case Enumerable::Date :
            output << "date";
            break;

        case Enumerable::Time :
            output << "time";
            break;

        default :
            output << "<unknown>";
            break;

    }
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::Map::describe

bool
nImO::Map::empty
    (void)
    const
{
    ODL_OBJENTER(); //####
    bool    result{inherited2::empty()};

    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Map::empty

nImO::ComparisonStatus
nImO::Map::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker.first)
                {
                    result &= walker.first->equalTo(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Map::equalTo

nImO::SpValue
nImO::Map::extractValue
    (const Message &    theMessage,
     const int          leadByte,
     size_t &           position,
     SpArray            parentValue)
{
    ODL_ENTER(); //####
    ODL_P3(&theMessage, &position, parentValue.get()); //####
    ODL_X1(leadByte); //####
    SpValue result;
    bool    atEnd;
    bool    isEmpty{DataKind::OtherContainerEmptyValue == (DataKind::OtherContainerEmptyMask & leadByte)};
    int     aByte;

    ++position; // We will always accept the lead byte
    ODL_I1(position); //####
    if (isEmpty)
    {
        ODL_LOG("(isEmpty)"); //####
        aByte = theMessage.getByte(position, atEnd);
        ODL_X1(aByte); //####
        ODL_B1(atEnd); //####
        if (atEnd)
        {
            ODL_LOG("(atEnd)"); //####
        }
        else
        {
            ODL_LOG("! (atEnd)"); //####
            static const DataKind   endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                DataKind::OtherContainerTypeMap | DataKind::OtherContainerEmptyValue};

            if (toUType(endMarker) == aByte)
            {
                ODL_LOG("(toUType(endMarker) == aByte)"); //####
                result = std::make_shared<Map>();
                ++position;
                ODL_I1(position); //####
            }
            else
            {
                ODL_LOG("! (toUType(endMarker) == aByte)"); //####
                result = std::make_shared<Invalid>("Empty Map with incorrect end tag", position);
            }
        }
    }
    else
    {
        ODL_LOG("! (isEmpty)"); //####
        aByte = theMessage.getByte(position, atEnd);
        ODL_X1(aByte); //####
        ODL_B1(atEnd); //####
        if (atEnd)
        {
            ODL_LOG("(atEnd)"); //####
        }
        else
        {
            ODL_LOG("! (atEnd)"); //####
            IntStatus   numStatus;
            auto        elementCount{extractInt64FromMessage(theMessage, aByte, position, numStatus)};

            if (IntStatus::Successful == numStatus)
            {
                ODL_LOG("(IntStatus::Successful == status)"); //####
                elementCount -= kDataKindIntegerShortValueMinValue - 1;
                ODL_I1(elementCount); //####
                if (0 >= elementCount)
                {
                    ODL_LOG("(0 >= elementCount)"); //####
                    result = std::make_shared<Invalid>("Map with zero or negative count", position);
                }
                else
                {
                    auto    aMap{std::make_shared<Map>()};

                    result = aMap;
                    if (result)
                    {
                        bool    okSoFar{true};

                        for ( ; okSoFar && (elementCount > StaticCast(int64_t, aMap->size())); )
                        {
                            aByte = theMessage.getByte(position, atEnd);
                            ODL_X1(aByte); //####
                            ODL_B1(atEnd); //####
                            if (atEnd)
                            {
                                ODL_LOG("(atEnd)"); //####
                                result.reset();
                                okSoFar = false;
                                ODL_B1(okSoFar); //####
                            }
                            else
                            {
                                auto    keyValue{getValueFromMessage(theMessage, position, aByte, nullptr)};

                                if (keyValue)
                                {
                                    if (keyValue->asFlaw())
                                    {
                                        ODL_LOG("(keyValue->asFlaw())"); //####
                                        result = keyValue;
                                        okSoFar = false;
                                        ODL_B1(okSoFar); //####
                                    }
                                    else
                                    {
                                        ODL_LOG("! (keyValue->asFlaw())"); //####
                                        aByte = theMessage.getByte(position, atEnd);
                                        ODL_X1(aByte); //####
                                        ODL_B1(atEnd); //####
                                        if (atEnd)
                                        {
                                            ODL_LOG("(atEnd)"); //####
                                            result.reset();
                                            okSoFar = false;
                                            ODL_B1(okSoFar); //####
                                        }
                                        else
                                        {
                                            auto    vValue{getValueFromMessage(theMessage, position, aByte, nullptr)};

                                            if (vValue)
                                            {
                                                if (vValue->asFlaw())
                                                {
                                                    ODL_LOG("(vValue->asFlaw())"); //####
                                                    result = vValue;
                                                    okSoFar = false;
                                                    ODL_B1(okSoFar); //####
                                                }
                                                else
                                                {
                                                    ODL_LOG("! (vValue->asFlaw())"); //####
                                                    aMap->addValue(keyValue, vValue);
                                                }
                                            }
                                            else
                                            {
                                                ODL_LOG("! (vValue)"); //####
                                                result = std::make_shared<Invalid>("Null value Value read", position);
                                                okSoFar = false;
                                                ODL_B1(okSoFar); //####
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    ODL_LOG("! (aValue)"); //####
                                    result = std::make_shared<Invalid>("Null key Value read", position);
                                    okSoFar = false;
                                    ODL_B1(okSoFar); //####
                                }
                            }
                        }
                        if (okSoFar)
                        {
                            aByte = theMessage.getByte(position, atEnd);
                            ODL_X1(aByte); //####
                            ODL_B1(atEnd); //####
                            if (atEnd)
                            {
                                ODL_LOG("(atEnd)"); //####
                                result.reset();
                                okSoFar = false;
                                ODL_B1(okSoFar); //####
                            }
                            else
                            {
                                ODL_LOG("! (atEnd)"); //####
                                static const DataKind   endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                                    DataKind::OtherContainerTypeMap |
                                                                    DataKind::OtherContainerNonEmptyValue};

                                if (toUType(endMarker) == aByte)
                                {
                                    ODL_LOG("(toUType(endMarker) == aByte)"); //####
                                    ++position;
                                    ODL_I1(position); //####
                                }
                                else
                                {
                                    ODL_LOG("! (toUType(endMarker) == aByte)"); //####
                                    result = std::make_shared<Invalid>("Non-empty Map with incorrect end tag", position);
                                    okSoFar = false;
                                    ODL_B1(okSoFar); //####
                                }
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (result)"); //####
                        result = std::make_shared<Invalid>("Could not allocate a Map");
                    }
                }
            }
            else
            {
                ODL_LOG("! (IntStatus::Successful == status)"); //####
            }
        }
    }
    if (parentValue && result && (! result->asFlaw()))
    {
        ODL_LOG("(parentValue && result && (! result->asFlaw()))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Map::extractValue

nImO::Value::Extractor
nImO::Map::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2(&aByte, &aMask); //####
    aByte = (DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeMap);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherContainerTypeMask);
    ODL_EXIT(); //####
    return extractValue;
} // nImO::Map::getExtractionInfo

CPtr(char)
nImO::Map::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   initialChars[]{ kStartMapChar, kEndOfString };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Map::getInitialCharacters

nImO::SpSet
nImO::Map::getKeys
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_shared<Set>()};

    for (auto & walker : *this)
    {
        result->addValue(walker.first);
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::getKeys

CPtr(char)
nImO::Map::getTerminalCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   terminalChars[]{ kEndMapChar, kKeyValueSeparator, kEndOfString };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Map::getTerminalCharacters

nImO::DataKind
nImO::Map::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedOtherValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Map::getTypeTag

nImO::ComparisonStatus
nImO::Map::greaterThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{};

    if (&other == this)
    {
        result = false;
    }
    else
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker.first)
                {
                    result &= walker.first->greaterThan(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Map::greaterThan

nImO::ComparisonStatus
nImO::Map::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker.first)
                {
                    result &= walker.first->greaterThanOrEqual(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Map::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Map::lessThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{};

    if (&other == this)
    {
        result = false;
    }
    else
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker.first)
                {
                    result &= walker.first->lessThan(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Map::lessThan

nImO::ComparisonStatus
nImO::Map::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        if ((Enumerable::Unknown == _keyKind) || (other.enumerationType() != _keyKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker.first)
                {
                    result &= walker.first->lessThanOrEqual(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Map::lessThanOrEqual

nImO::Map &
nImO::Map::operator=
    (Map && other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited1::operator=(std::move(other));
        inherited2::operator=(std::move(other));
        addEntries(other);
        other.clear();
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Map::operator=

std::ostream &
nImO::Map::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&out); //####
    out << kStartMapChar;
    for (auto & walker : *this)
    {
        out << " " << *walker.first << " " << kKeyValueSeparator << " " << *walker.second;
    }
    out << " " << kEndMapChar;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Map::operator<<

void
nImO::Map::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&outBuffer); //####
    ODL_B1(squished); //####
    bool    first{true};

    outBuffer.appendChar(kStartMapChar);
    for (auto & walker : *this)
    {
        if (! first)
        {
            outBuffer.appendChar(',');
        }
        if ((! squished) || (! first))
        {
            outBuffer.appendChar(' ');
        }
        walker.first->printToStringBuffer(outBuffer);
        if (! squished)
        {
            outBuffer.appendChar(' ');
        }
        outBuffer.appendChar(kKeyValueSeparator);
        if (! squished)
        {
            outBuffer.appendChar(' ');
        }
        walker.second->printToStringBuffer(outBuffer);
        first = false;
    }
    if (! squished)
    {
        outBuffer.appendChar(' ');
    }
    outBuffer.appendChar(kEndMapChar);
    ODL_OBJEXIT(); //####
} // nImO::Map::printToStringBuffer

void
nImO::Map::printToStringBufferAsJSON
    (StringBuffer & outBuffer,
     const bool     asKey,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(asKey);
    ODL_OBJENTER(); //####
    ODL_P1(&outBuffer); //####
    ODL_B2(asKey, squished); //####
    bool    first{true};

    outBuffer.appendChar(kStartMapChar);
    for (auto & walker : *this)
    {
        if (! first)
        {
            outBuffer.appendChar(',');
        }
        if ((! squished) || (! first))
        {
            outBuffer.appendChar(' ');
        }
        SpValue keyValue = walker.first;

        keyValue->printToStringBufferAsJSON(outBuffer, true);
        if (! squished)
        {
            outBuffer.appendChar(' ');
        }
        outBuffer.appendChar(':');
        if (! squished)
        {
            outBuffer.appendChar(' ');
        }
        walker.second->printToStringBufferAsJSON(outBuffer);
        first = false;
    }
    if (! squished)
    {
        outBuffer.appendChar(' ');
    }
    outBuffer.appendChar(kEndMapChar);
    ODL_OBJEXIT(); //####
} // nImO::Map::printToStringBufferAsJSON

nImO::Map::const_iterator
nImO::Map::random
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{inherited2::begin()};
    size_t  howMany{size()};

    if (0 < howMany)
    {
        for (size_t ii = 0, keyNumber = (nImO::RandomUnsigned() % howMany); ii < keyNumber; ++ii)
        {
            ++result;
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} /* nImO::Map::random */

nImO::Map::iterator
nImO::Map::random
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{inherited2::begin()};
    size_t  howMany{size()};

    if (0 < howMany)
    {
        for (size_t ii = 0, keyNumber = (nImO::RandomUnsigned() % howMany); ii < keyNumber; ++ii)
        {
            ++result;
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} /* nImO::Map::random */

nImO::SpValue
nImO::Map::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2(&inBuffer, &position); //####
    bool    atEnd;
    bool    done{false};
    bool    valid{false};
    auto    result{std::make_shared<Map>()};
    size_t  localIndex{position};
    int     aChar{inBuffer.getChar(localIndex++, atEnd)};

    ODL_P1(result.get()); //####
    ODL_C1(aChar); //####
    ODL_B1(atEnd); //####
    ODL_I1(localIndex); //####
    if ((! atEnd) && (kStartMapChar == aChar))
    {
        for ( ; ! done; )
        {
            inBuffer.skipOverWhiteSpace(localIndex, aChar, atEnd);
            ODL_I1(localIndex); //####
            ODL_C1(aChar); //####
            ODL_B1(atEnd); //####
            // Check for the closing bracket
            if (atEnd)
            {
                ODL_LOG("(atEnd)"); //####
                done = true;
            }
            else
            {
                if (kEndMapChar == aChar)
                {
                    done = valid = true;
                }
                else
                {
                    auto    keyValue{Value::readFromStringBuffer(inBuffer, localIndex)};

                    ODL_I1(localIndex); //####
                    if (keyValue)
                    {
                        auto    elementType{keyValue->enumerationType()};

                        if ((Enumerable::Unknown == elementType) || (Enumerable::NotEnumerable == elementType))
                        {
                            ODL_LOG("((Enumerable::Unknown == elementType) || " //####
                                    "(Enumerable::NotEnumerable == elementType))"); //####
                            keyValue.reset();
                            done = true;
                        }
                        else
                        {
                            if (0 < result->size())
                            {
                                if (result->_keyKind != elementType)
                                {
                                    ODL_LOG("(result->_keyKind != elementType)"); //####
                                    keyValue.reset();
                                    done = true;
                                }
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (keyValue)"); //####
                        done = true;
                    }
                    if (keyValue)
                    {
                        inBuffer.skipOverWhiteSpace(localIndex, aChar, atEnd);
                        ODL_I1(localIndex); //####
                        ODL_C1(aChar); //####
                        ODL_B1(atEnd); //####
                        // Check for the closing bracket
                        if (atEnd)
                        {
                            ODL_LOG("(atEnd)"); //####
                            done = true;
                        }
                        else
                        {
                            if (kEndMapChar == aChar)
                            {
                                ODL_LOG("(kEndMapChar == aChar)"); //####
                                done = true;
                            }
                            else
                            {
                                if (kKeyValueSeparator == aChar)
                                {
                                    ++localIndex;
                                    auto    assocValue{Value::readFromStringBuffer(inBuffer, localIndex)};

                                    if (assocValue)
                                    {
                                        result->addValue(keyValue, assocValue);
                                    }
                                    else
                                    {
                                        ODL_LOG("! (assocValue)"); //####
                                        done = true;
                                    }
                                }
                            }
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

size_t
nImO::Map::size
    (void)
    const
{
    ODL_OBJENTER(); //####
    size_t  result{inherited2::size()};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Map::size

void
nImO::Map::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&outMessage); //####
    if (0 < inherited2::size())
    {
        ODL_LOG("(0 < inherited2::size())"); //####
        const DataKind  startMap{DataKind::Other | DataKind::OtherContainerStart |
                                    DataKind::OtherContainerTypeMap |
                                    DataKind::OtherContainerNonEmptyValue};
        const DataKind  endMap{DataKind::Other | DataKind::OtherContainerEnd |
                                DataKind::OtherContainerTypeMap |
                                DataKind::OtherContainerNonEmptyValue};

        outMessage.appendBytes(&startMap, sizeof(startMap));
        writeInt64ToMessage(outMessage, StaticCast(int, inherited2::size()) + kDataKindIntegerShortValueMinValue - 1);
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
        static const DataKind   stuff[]
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

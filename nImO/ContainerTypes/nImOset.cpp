//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ContainerTypes/nImOset.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO sets.
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

#include <ContainerTypes/nImOset.h>

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOinvalid.h>
#include <ContainerTypes/nImOarray.h>
#include <ContainerTypes/nImOmessage.h>
#include <ContainerTypes/nImOstringBuffer.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO sets. */
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

nImO::Set::Set
    (void) :
        inherited1{}, inherited2{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Set::Set

nImO::Set::Set
    (const Set &    other) :
        inherited1{}, inherited2{}, _keyKind{other._keyKind}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Set::Set

nImO::Set::Set
    (Set && other)
    noexcept :
        inherited1{std::move(other)}, inherited2{std::move(other)}, _keyKind{other._keyKind}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    other.clear();
    ODL_EXIT_P(this); //####
} // nImO::Set::Set

nImO::Set::~Set
    (void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Set::~Set

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Set::addEntries
    (const Set &    other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if ((other._keyKind == _keyKind) || (Enumerable::Unknown == _keyKind))
    {
        for (auto & walker : other)
        {
            addValue(walker);
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::Set::addEntries

nImO::Set::InsertResult
nImO::Set::addValue
    (SpValue    val)
{
    ODL_OBJENTER(); //####
    ODL_P1("val = ", val.get()); //####
    InsertResult    result;

    if (nullptr == val)
    {
        result = { inherited2::end(), false };
    }
    else
    {
        if (Enumerable::Unknown == _keyKind)
        {
            _keyKind = val->enumerationType();
        }
        if (val->enumerationType() == _keyKind)
        {
            result = inherited2::emplace(val);
        }
        else
        {
            result = { inherited2::end(), false };
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::addValue

CPtr(nImO::Set)
nImO::Set::asSet
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Set::asSet

void
nImO::Set::clear
    (void)
{
    ODL_OBJENTER(); //####
    inherited2::clear();
    _keyKind = Enumerable::Unknown;
    ODL_OBJEXIT(); //####
} // nImO::Set::clear

bool
nImO::Set::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(Set)   otherPtr{other.asSet()};

        if ((nullptr != otherPtr) && (size() == otherPtr->size()))
        {
            auto    thisWalker{inherited2::begin()};
            auto    otherWalker{otherPtr->inherited2::begin()};

            for (result = true; result && (thisWalker != inherited2::end()); ++thisWalker, ++otherWalker)
            {
                SpValue thisValue{*thisWalker};
                SpValue otherValue{*otherWalker};

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
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Set::deeplyEqualTo

bool
nImO::Set::empty
    (void)
    const
{
    ODL_OBJENTER(); //####
    bool    result{inherited2::empty()};

    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Set::empty

nImO::ComparisonStatus
nImO::Set::equalTo
    (const Value &  other)
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
                SpValue aValue{*walker};

                if (nullptr != aValue)
                {
                    result &= aValue->equalTo(other);
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::equalTo

nImO::SpValue
nImO::Set::extractValue
    (const Message &    theMessage,
     const int          leadByte,
     size_t &           position,
     SpArray            parentValue)
{
    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "parentValue = ", parentValue.get()); //####
    ODL_X1("leadByte = ", leadByte); //####
    SpValue result;
    bool    atEnd;
    bool    isEmpty{DataKind::OtherContainerEmptyValue == (DataKind::OtherContainerEmptyMask & leadByte)};
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
            static const DataKind   endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                DataKind::OtherContainerTypeSet | DataKind::OtherContainerEmptyValue};

            if (toUType(endMarker) == aByte)
            {
                ODL_LOG("(toUType(endMarker) == aByte)"); //####
                result = std::make_shared<Set>();
                ++position;
                ODL_I1("position <- ", position); //####
            }
            else
            {
                ODL_LOG("! (toUType(endMarker) == aByte)"); //####
                result = std::make_shared<Invalid>("Empty Set with incorrect end tag", position);
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
            int64_t     elementCount{extractInt64FromMessage(theMessage, aByte, position, numStatus)};

            if (IntStatus::Successful == numStatus)
            {
                ODL_LOG("(IntStatus::Successful == status)"); //####
                elementCount -= DataKindIntegerShortValueMinValue - 1;
                ODL_I1("elementCount <- ", elementCount); //####
                if (0 >= elementCount)
                {
                    ODL_LOG("(0 >= elementCount)"); //####
                    result = std::make_shared<Invalid>("Set with zero or negative count", position);
                }
                else
                {
                    auto    aSet{std::make_shared<Set>()};

                    result = aSet;
                    if (nullptr == result)
                    {
                        ODL_LOG("(nullptr == result)"); //####
                        result = std::make_shared<Invalid>("Could not allocate a Set");
                    }
                    else
                    {
                        bool    okSoFar{true};

                        for ( ; okSoFar && (elementCount > StaticCast(int64_t, aSet->size())); )
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
                                SpValue aValue{getValueFromMessage(theMessage, position, aByte, nullptr)};

                                if (nullptr == aValue)
                                {
                                    ODL_LOG("(nullptr == aValue)"); //####
                                    result = std::make_shared<Invalid>("Null Value read", position);
                                    okSoFar = false;
                                }
                                else if (aValue->asFlaw())
                                {
                                    ODL_LOG("(aValue->asFlaw())"); //####
                                    result = aValue;
                                    okSoFar = false;
                                }
                                else
                                {
                                    ODL_LOG("! (aValue->asFlaw())"); //####
                                    aSet->addValue(aValue);
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
                                static const DataKind   endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                                    DataKind::OtherContainerTypeSet |
                                                                    DataKind::OtherContainerNonEmptyValue};

                                if (toUType(endMarker) == aByte)
                                {
                                    ODL_LOG("(toUType(endMarker) == aByte)"); //####
                                    ++position;
                                    ODL_I1("position <- ", position); //####
                                }
                                else
                                {
                                    ODL_LOG("! (toUType(endMarker) == aByte)"); //####
                                    result = std::make_shared<Invalid>("Non-empty Set with incorrect end tag", position);
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
} // nImO::Set::extractValue

void
nImO::Set::getExtractionInfo
    (DataKind &                 aByte,
     DataKind &                 aMask,
     nImO::Value::Extractor &   theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeSet);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherContainerTypeMask);
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Set::getExtractionInfo

CPtr(char)
nImO::Set::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   initialChars[]{ kStartSetChar, kEndOfString };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Set::getInitialCharacters

CPtr(char)
nImO::Set::getTerminalCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   terminalChars[]{ kEndSetChar, kEndOfString };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Set::getTerminalCharacters

nImO::DataKind
nImO::Set::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedOtherValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Set::getTypeTag

nImO::ComparisonStatus
nImO::Set::greaterThan
    (const Value &  other)
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
            SpValue aValue{*walker};

            if (nullptr != aValue)
            {
                result &= aValue->greaterThan(other);
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::greaterThan

nImO::ComparisonStatus
nImO::Set::greaterThanOrEqual
    (const Value &  other)
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
                SpValue aValue{*walker};

                if (nullptr != aValue)
                {
                    result &= aValue->greaterThanOrEqual(other);
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Set::lessThan
    (const Value &  other)
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
            SpValue aValue{*walker};

            if (nullptr != aValue)
            {
                result &= aValue->lessThan(other);
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::lessThan

nImO::ComparisonStatus
nImO::Set::lessThanOrEqual
    (const Value &  other)
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
                SpValue aValue{*walker};

                if (nullptr != aValue)
                {
                    result &= aValue->lessThanOrEqual(other);
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::lessThanOrEqual

nImO::Set &
nImO::Set::operator=
    (Set && other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited1::operator=(std::move(other));
        inherited2::operator=(std::move(other));
        addEntries(other);
        other.clear();
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Set::operator=

std::ostream &
nImO::Set::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << kStartSetChar;
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (nullptr != aValue)
        {
            out << " " << *aValue;
        }
    }
    out << " " << kEndSetChar;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Set::operator<<

void
nImO::Set::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    bool first{true};

    outBuffer.addChar(kStartSetChar);
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (nullptr != aValue)
        {
            if ((! squished) || (! first))
            {
                outBuffer.addChar(' ');
            }
            aValue->printToStringBuffer(outBuffer);
            first = false;
        }
    }
    if (! squished)
    {
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndSetChar);
    ODL_OBJEXIT(); //####
} // nImO::Set::printToStringBuffer

void
nImO::Set::printToStringBufferAsJSON
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    bool first{true};

    outBuffer.addChar(kStartArrayChar);
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (nullptr != aValue)
        {
            if (! first)
            {
                outBuffer.addChar(',');
            }
            if ((! squished) || (! first))
            {
                outBuffer.addChar(' ');
            }
            aValue->printToStringBufferAsJSON(outBuffer);
            first = false;
        }
    }
    if (! squished)
    {
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndArrayChar);
    ODL_OBJEXIT(); //####
} // nImO::Set::printToStringBufferAsJSON

nImO::Set::const_iterator
nImO::Set::random
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
} /* nImO::Set::random */

nImO::Set::iterator
nImO::Set::random
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
} /* nImO::Set::random */

nImO::SpValue
nImO::Set::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    bool    atEnd;
    bool    done{false};
    bool    valid{false};
    auto    result{std::make_shared<Set>()};
    size_t  localIndex{position};
    int     aChar{inBuffer.getChar(localIndex++, atEnd)};

    ODL_P1("result <- ", result.get()); //####
    ODL_C1("aChar <- ", aChar); //####
    ODL_B1("atEnd <- ", atEnd); //####
    ODL_I1("localIndex <- ", localIndex); //####
    if ((! atEnd) && (kStartSetChar == aChar))
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
            else if (kEndSetChar == aChar)
            {
                done = valid = true;
            }
            else
            {
                SpValue element{Value::readFromStringBuffer(inBuffer, localIndex)};

                ODL_I1("localIndex <- ", localIndex); //####
                if (nullptr == element)
                {
                    ODL_LOG("(nullptr == element)"); //####
                    done = true;
                }
                else
                {
                    Enumerable  elementType{element->enumerationType()};

                    if ((Enumerable::Unknown == elementType) ||
                        (Enumerable::NotEnumerable == elementType))
                    {
                        ODL_LOG("((Enumerable::Unknown == elementType) || " //####
                                "(Enumerable::NotEnumerable == elementType))"); //####
                        element.reset();
                        done = true;
                    }
                    else if (0 < result->size())
                    {
                        if (result->_keyKind == elementType)
                        {
                            result->addValue(element);
                        }
                        else
                        {
                            ODL_LOG("! (result->_keyKind == elementType)"); //####
                            element.reset();
                            done = true;
                        }
                    }
                    else
                    {
                        result->addValue(element);
                    }
                }
            }
        }
    }
    else
    {
        ODL_LOG("! ((! atEnd) && (kStartSetChar == aChar))"); //####
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
} // nImO::Set::readFromStringBuffer

size_t
nImO::Set::size
    (void)
    const
{
    ODL_OBJENTER(); //####
    size_t  result{inherited2::size()};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Set::size

void
nImO::Set::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    if (0 < inherited2::size())
    {
        ODL_LOG("(0 < inherited2::size())"); //####
        const DataKind  startSet{DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeSet |
                                    DataKind::OtherContainerNonEmptyValue};
        const DataKind  endSet{DataKind::Other | DataKind::OtherContainerEnd | DataKind::OtherContainerTypeSet |
                                DataKind::OtherContainerNonEmptyValue};

        outMessage.appendBytes(&startSet, sizeof(startSet));
        writeInt64ToMessage(outMessage, StaticCast(int, inherited2::size()) + DataKindIntegerShortValueMinValue - 1);
        for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
        {
            SpValue aValue{*walker};

            if (nullptr != aValue)
            {
                aValue->writeToMessage(outMessage);
            }
        }
        outMessage.appendBytes(&endSet, sizeof(endSet));
    }
    else
    {
        ODL_LOG("! (0 < inherited2::size())"); //####
        static const DataKind    stuff[]
        {
            DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeSet |
              DataKind::OtherContainerEmptyValue,
            DataKind::Other | DataKind::OtherContainerEnd | DataKind::OtherContainerTypeSet |
              DataKind::OtherContainerEmptyValue
        };

        outMessage.appendBytes(stuff, sizeof(stuff));
    }
    ODL_OBJEXIT(); //####
} // nImO::Set::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

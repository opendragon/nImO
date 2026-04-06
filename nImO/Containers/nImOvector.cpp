//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOvector.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO vectors.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2026 by OpenDragon.
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
//  Created:    2026-04-06
//
//--------------------------------------------------------------------------------------------------

#include <Containers/nImOvector.h>

#include <BasicTypes/nImOdouble.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOinvalid.h>
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
 @brief The class definition for %nImO vectors. */
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

nImO::Vector::Vector
    (void) :
        inherited1{}, inherited2{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Vector::Vector

nImO::Vector::Vector
    (const Vector & other) :
        inherited1{}, inherited2{}, _dataKind{other._dataKind}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Vector::Vector

nImO::Vector::Vector
    (Vector &&   other)
    noexcept :
        inherited1{std::move(other)}, inherited2{std::move(other)}, _dataKind{std::exchange(other._dataKind, BasicType::Unknown)}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    addEntries(other);
    other.clear();
    ODL_EXIT_P(this); //####
} // nImO::Vector::Vector

nImO::Vector::~Vector
    (void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Vector::~Vector

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::Vector &
nImO::Vector::addEntries
    (const Vector & other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if ((other._dataKind == _dataKind) || (BasicType::Unknown == _dataKind))
    {
        for (const auto & walker : other)
        {
            addValue(walker);
        }
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Vector::addEntries

bool
nImO::Vector::addValue
    (SpValue    newElement)
{
    ODL_OBJENTER(); //####
    ODL_P1(newElement.get()); //####
    bool    result{false};

    if (newElement)
    {
        if (BasicType::Unknown == _dataKind)
        {
            _dataKind = newElement->basicType();
        }
        if (newElement->basicType() == _dataKind)
        {
            inherited2::emplace_back(newElement);
            result = true;
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Vector::addValue

void
nImO::Vector::appendValue
    (SpValue    newElement)
{
    ODL_OBJENTER(); //####
    ODL_P1(newElement.get()); //####
    addValue(newElement);
    ODL_OBJEXIT(); //####
} // nImO::Vector::appendValue

CPtr(nImO::Vector)
nImO::Vector::asVector
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Vector::asVector

void
nImO::Vector::clear
(void)
{
    ODL_OBJENTER(); //####
    inherited2::clear();
    _dataKind = BasicType::Unknown;
    ODL_OBJEXIT(); //####
} // nImO::Vector::clear

bool
nImO::Vector::deeplyEqualTo
    (const Value &  other,
     const bool     ignoreCase)
    const
{
    NIMO_UNUSED_VAR_(ignoreCase);
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ODL_B1(ignoreCase); //####
    bool    result{&other == this};

    if (! result)
    {
        if (auto otherPtr{other.asVector()}; (nullptr != otherPtr) && (size() == otherPtr->size()))
        {
            auto    thisWalker{inherited2::begin()};
            auto    otherWalker{otherPtr->inherited2::begin()};

            for (result = true; result && (thisWalker != inherited2::end()); ++thisWalker, ++otherWalker)
            {
                auto    thisValue{*thisWalker};
                auto    otherValue{*otherWalker};

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
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Vector::deeplyEqualTo

std::ostream &
nImO::Vector::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&output); //####
    output << "vector of " << size() << " elements and a data type of ";
    switch (_dataKind)
    {
        case BasicType::Address :
            output << "address";
            break;

        case BasicType::Date :
            output << "date";
            break;

        case BasicType::Double :
            output << "double";
            break;

        case BasicType::Logical :
            output << "logical";
            break;

        case BasicType::Integer :
            output << "integer";
            break;

        case BasicType::String :
            output << "string";
            break;

        case BasicType::Time :
            output << "time";
            break;

        default :
            output << "<unknown>";
            break;

    }
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::Vector::describe

bool
nImO::Vector::empty
    (void)
    const
{
    ODL_OBJENTER(); //####
    bool    result{inherited2::empty()};

    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Vector::empty

nImO::ComparisonStatus
nImO::Vector::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    // Note that all the values must be validated.
    if ((BasicType::Unknown == _dataKind) || (other.basicType() != _dataKind))
    {
        result.clear();
    }
    else
    {
        for (auto & walker : *this)
        {
            if (walker)
            {
                result &= walker->equalTo(other);
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Vector::equalTo

nImO::SpValue
nImO::Vector::extractValue
    (const Message &    theMessage,
     const int          leadByte,
     size_t &           position,
     SpValue            parentValue)
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
        if (! atEnd)
        {
            ODL_LOG("(! atEnd)"); //####
            static const DataKind   endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                DataKind::OtherContainerTypeVector | DataKind::OtherContainerEmptyValue};

            if (toUType(endMarker) == aByte)
            {
                ODL_LOG("(endMarker == aByte)"); //####
                result = std::make_shared<Vector>();
                ++position;
                ODL_I1(position); //####
            }
            else
            {
                ODL_LOG("! (endMarker == aByte)"); //####
                result = std::make_shared<Invalid>("Empty Vector with incorrect end tag", position);
            }
        }
    }
    else
    {
        ODL_LOG("! (isEmpty)"); //####
        aByte = theMessage.getByte(position, atEnd);
        ODL_X1(aByte); //####
        ODL_B1(atEnd); //####
        if (! atEnd)
        {
            ODL_LOG("(! atEnd)"); //####
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
                    result = std::make_shared<Invalid>("Vector with zero or negative count", position);
                }
                else
                {
                    auto    aVector{std::make_shared<Vector>()};

                    result = aVector;
                    if (result)
                    {
                        bool    okSoFar{true};

                        for ( ; okSoFar && (elementCount > StaticCast(int64_t, aVector->size())); )
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
                                auto    aValue{getValueFromMessage(theMessage, position, aByte, aVector)};

                                if (aValue)
                                {
                                    if (aValue->asFlaw())
                                    {
                                        ODL_LOG("(aValue->asFlaw())"); //####
                                        result = aValue;
                                        okSoFar = false;
                                        ODL_B1(okSoFar); //####
                                    }
                                    else
                                    {
                                        ODL_LOG("! (aValue->asFlaw())"); //####
                                        aVector->addValue(aValue);
                                    }
                                }
                                else
                                {
                                    ODL_LOG("(nullptr == aValue)"); //####
                                    result = std::make_shared<Invalid>("Null Value read", position);
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
                                okSoFar = false; // cppcheck-suppress unreadVariable
                                ODL_B1(okSoFar); //####
                            }
                            else
                            {
                                ODL_LOG("! (atEnd)"); //####
                                static const DataKind endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                                DataKind::OtherContainerTypeVector |
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
                                    result = std::make_shared<Invalid>("Non-empty Vector with incorrect end tag", position);
                                }
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (result)"); //####
                        result = std::make_shared<Invalid>("Could not allocate an Vector");
                    }
                }
            }
            else
            {
                ODL_LOG("! (IntStatus::Successful == numStatus)"); //####
            }
        }
    }
    if (result && (! result->asFlaw()))
    {
        ODL_LOG("(result && (! result->asFlaw()))"); //####
        addValueToParent(parentValue, result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Vector::extractValue

nImO::Value::Extractor
nImO::Vector::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2(&aByte, &aMask); //####
    aByte = (DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeVector);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherContainerTypeMask);
    ODL_EXIT(); //####
    return extractValue;
} // nImO::Vector::getExtractionInfo

CPtr(char)
nImO::Vector::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   initialChars[]{ kStartVectorChar, kEndOfString };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Vector::getInitialCharacters

CPtr(char)
nImO::Vector::getTerminalCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   terminalChars[]{ kEndVectorChar, kEndOfString };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Vector::getTerminalCharacters

nImO::DataKind
nImO::Vector::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedOtherValue};

    ODL_OBJEXIT_I(StaticCast(int, result));
    return result;
} // nImO::Vector::getTypeTag

nImO::ComparisonStatus
nImO::Vector::greaterThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    if (&other == this)
    {
        result = false;
    }
    else
    {
        if ((BasicType::Unknown == _dataKind) || (other.basicType() != _dataKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker)
                {
                    result &= walker->greaterThan(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Vector::greaterThan

nImO::ComparisonStatus
nImO::Vector::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        if ((BasicType::Unknown == _dataKind) || (other.basicType() != _dataKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker)
                {
                    result &= walker->greaterThanOrEqual(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Vector::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Vector::lessThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    if (&other == this)
    {
        result = false;
    }
    else
    {
        if ((BasicType::Unknown == _dataKind) || (other.basicType() != _dataKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker)
                {
                    result &= walker->lessThan(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Vector::lessThan

nImO::ComparisonStatus
nImO::Vector::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        if ((BasicType::Unknown == _dataKind) || (other.basicType() != _dataKind))
        {
            result.clear();
        }
        else
        {
            for (auto & walker : *this)
            {
                if (walker)
                {
                    result &= walker->lessThanOrEqual(other);
                }
            }
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Vector::lessThanOrEqual

nImO::Vector &
nImO::Vector::operator=
    (Vector &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited1::operator=(std::move(other));
        inherited2::operator=(std::move(other));
        _dataKind = std::exchange(other._dataKind, BasicType::Unknown);
        addEntries(other);
        other.clear();
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Vector::operator=

std::ostream &
nImO::Vector::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&out); //####
    out << kStartVectorChar;
    for (const auto & walker : *this)
    {
        if (walker)
        {
            out << " " << *walker;
        }
    }
    out << " " << kEndVectorChar;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Vector::operator<<

void
nImO::Vector::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&outBuffer); //####
    ODL_B1(squished); //####
    bool    first{true};

    outBuffer.appendChar(kStartVectorChar);
    for (auto & walker : *this)
    {
        if (walker)
        {
            if (! first)
            {
                outBuffer.appendChar(',');
            }
            if ((! squished) || (! first))
            {
                outBuffer.appendChar(' ');
            }
            walker->printToStringBuffer(outBuffer, squished);
            first = false;
        }
    }
    if (! squished)
    {
        outBuffer.appendChar(' ');
    }
    outBuffer.appendChar(kEndVectorChar);
    ODL_OBJEXIT(); //####
} // nImO::Vector::printToStringBuffer

void
nImO::Vector::printToStringBufferAsJSON
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

    outBuffer.appendChar(kStartArrayChar);
    for (auto & walker : *this)
    {
        if (walker)
        {
            if (! first)
            {
                outBuffer.appendChar(',');
            }
            if ((! squished) || (! first))
            {
                outBuffer.appendChar(' ');
            }
            walker->printToStringBufferAsJSON(outBuffer, false, squished);
            first = false;
        }
    }
    if (! squished)
    {
        outBuffer.appendChar(' ');
    }
    outBuffer.appendChar(kEndArrayChar);
    ODL_OBJEXIT(); //####
} // nImO::Vector::printToStringBufferAsJSON

nImO::Vector::const_iterator
nImO::Vector::random
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{inherited2::begin()};
    size_t  howMany{size()};

    if (0 < howMany)
    {
        for (size_t ii{0}, keyNumber{nImO::RandomUnsigned() % howMany}; ii < keyNumber; ++ii)
        {
            ++result;
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} /* nImO::Vector::random */

nImO::Vector::iterator
nImO::Vector::random
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{inherited2::begin()};
    size_t  howMany{size()};

    if (0 < howMany)
    {
        for (size_t ii{0}, keyNumber{nImO::RandomUnsigned() % howMany}; ii < keyNumber; ++ii)
        {
            ++result;
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} /* nImO::Vector::random */

nImO::SpValue
nImO::Vector::readFromStringBuffer // cppcheck-suppress duplInheritedMember
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2(&inBuffer, &position); //####
    bool    atEnd{false};
    bool    valid{false};
    auto    result{std::make_shared<Vector>()};
    size_t  localIndex{position};
    int     aChar{inBuffer.getChar(localIndex++, atEnd)};

    ODL_P1(result.get()); //####
    ODL_I1(localIndex); //####
    ODL_C1(aChar); //####
    ODL_B1(atEnd); //####
    if ((! atEnd) && (kStartVectorChar == aChar))
    {
        for (bool done{false}; ! done; )
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
                if (kEndVectorChar == aChar)
                {
                    done = valid = true;
                }
                else
                {
                    auto    element{Value::readFromStringBuffer(inBuffer, localIndex)};

                    ODL_I1(localIndex); //####
                    if (element)
                    {
                        auto    elementType{element->basicType()};

                        if ((BasicType::Unknown == elementType) ||
                            (BasicType::NotBasic == elementType))
                        {
                            ODL_LOG("((BasicType::Unknown == elementType) || " //####
                                    "(BasicType::NotBasic == elementType))"); //####
                            element.reset();
                            done = true;
                        }
                        else
                        {
                            if (0 < result->size())
                            {
                                if (result->_dataKind == elementType)
                                {
                                    result->addValue(element);
                                }
                                else
                                {
                                    ODL_LOG("! (result->_dataKind == elementType)"); //####
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
                    else
                    {
                        ODL_LOG("! (element)"); //####
                        done = true;
                    }
                }
            }
        }
    }
    else
    {
        ODL_LOG("! (kStartVectorChar == aChar)"); //####
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
} // nImO::Vector::readFromStringBuffer

size_t
nImO::Vector::size
    (void)
    const
{
    ODL_OBJENTER(); //####
    size_t  result{inherited2::size()};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Vector::size

void
nImO::Vector::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_ENTER(); //####
    ODL_P1(&outMessage); //####
    if (0 < inherited2::size())
    {
        ODL_LOG("(0 < inherited2::size())"); //####
        DataKind    startVector{DataKind::Other | DataKind::OtherContainerStart |
                                DataKind::OtherContainerTypeVector | DataKind::OtherContainerNonEmptyValue};
        DataKind    endVector{DataKind::Other | DataKind::OtherContainerEnd |
                                DataKind::OtherContainerTypeVector | DataKind::OtherContainerNonEmptyValue};

        outMessage.appendBytes(&startVector, sizeof(startVector));
        writeInt64ToMessage(outMessage, StaticCast(int, inherited2::size()) + kDataKindIntegerShortValueMinValue - 1);
        for (auto & walker : *this)
        {
            if (walker)
            {
                walker->writeToMessage(outMessage);
            }
        }
        outMessage.appendBytes(&endVector, sizeof(endVector));
    }
    else
    {
        ODL_LOG("! (0 < inherited2::size())"); //####
        static const DataKind   stuff[]
        {
            (DataKind::Other | DataKind::OtherContainerStart |
                DataKind::OtherContainerTypeVector |
             DataKind::OtherContainerEmptyValue),
            (DataKind::Other | DataKind::OtherContainerEnd |
                DataKind::OtherContainerTypeVector |
                DataKind::OtherContainerEmptyValue)
        };

        outMessage.appendBytes(stuff, sizeof(stuff));
    }
    ODL_EXIT(); //####
} // nImO::Vector::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

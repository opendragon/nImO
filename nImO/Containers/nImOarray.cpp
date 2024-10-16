//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOarray.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO arrays.
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

#include <Containers/nImOarray.h>

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
 @brief The class definition for %nImO arrays. */
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

nImO::Array::Array
    (void) :
        inherited1{}, inherited2{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::Array
    (const Array &  other) :
        inherited1{}, inherited2{}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::Array
    (Array &&   other)
    noexcept :
        inherited1{std::move(other)}, inherited2{std::move(other)}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    addEntries(other);
    other.clear();
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::~Array
    (void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Array::~Array

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::Array &
nImO::Array::addEntries
    (const Array &  other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    for (auto & walker : other)
    {
        addValue(walker);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Array::addEntries

CPtr(nImO::Array)
nImO::Array::asArray
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Array::asArray

void
nImO::Array::clear
(void)
{
    ODL_OBJENTER(); //####
    inherited2::clear();
    ODL_OBJEXIT(); //####
} // nImO::Array::clear

bool
nImO::Array::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(Array) otherPtr{other.asArray()};

        if ((nullptr != otherPtr) && (size() == otherPtr->size()))
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
} // nImO::Array::deeplyEqualTo

std::ostream &
nImO::Array::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&output); //####
    output << "array of " << size() << " elements";
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::Array::describe

bool
nImO::Array::empty
    (void)
    const
{
    ODL_OBJENTER(); //####
    bool    result{inherited2::empty()};

    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Array::empty

nImO::ComparisonStatus
nImO::Array::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    // Note that all the values must be validated.
    for (auto & walker : *this)
    {
        if (walker)
        {
            result &= walker->equalTo(other);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Array::equalTo

nImO::SpValue
nImO::Array::extractValue
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
        if (! atEnd)
        {
            ODL_LOG("(! atEnd)"); //####
            static const DataKind   endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                DataKind::OtherContainerTypeArray | DataKind::OtherContainerEmptyValue};

            if (toUType(endMarker) == aByte)
            {
                ODL_LOG("(endMarker == aByte)"); //####
                result = std::make_shared<Array>();
                ++position;
                ODL_I1(position); //####
            }
            else
            {
                ODL_LOG("! (endMarker == aByte)"); //####
                result = std::make_shared<Invalid>("Empty Array with incorrect end tag", position);
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
                    result = std::make_shared<Invalid>("Array with zero or negative count", position);
                }
                else
                {
                    auto    anArray{std::make_shared<Array>()};

                    result = anArray;
                    if (result)
                    {
                        bool    okSoFar{true};

                        for ( ; okSoFar && (elementCount > StaticCast(int64_t, anArray->size())); )
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
                                auto    aValue{getValueFromMessage(theMessage, position, aByte, anArray)};

                                // Note that it is the responsibility of the extractor to add to
                                // this Array, so it's not correct for this loop to perform an
                                // append operation.
                                if (aValue)
                                {
                                    if (aValue->asFlaw())
                                    {
                                        ODL_LOG("(aValue->asFlaw())"); //####
                                        result = aValue;
                                        okSoFar = false;
                                        ODL_B1(okSoFar); //####
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
                                okSoFar = false;
                                ODL_B1(okSoFar); //####
                            }
                            else
                            {
                                ODL_LOG("! (atEnd)"); //####
                                static const DataKind endMarker{DataKind::Other | DataKind::OtherContainerEnd |
                                                                DataKind::OtherContainerTypeArray |
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
                                    result = std::make_shared<Invalid>("Non-empty Array with incorrect end tag", position);
                                }
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (result)"); //####
                        result = std::make_shared<Invalid>("Could not allocate an Array");
                    }
                }
            }
            else
            {
                ODL_LOG("! (IntStatus::Successful == numStatus)"); //####
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
} // nImO::Array::extractValue

nImO::Value::Extractor
nImO::Array::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2(&aByte, &aMask); //####
    aByte = (DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeArray);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherContainerTypeMask);
    ODL_EXIT(); //####
    return extractValue;
} // nImO::Array::getExtractionInfo

CPtr(char)
nImO::Array::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   initialChars[]{ kStartArrayChar, kEndOfString };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Array::getInitialCharacters

CPtr(char)
nImO::Array::getTerminalCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   terminalChars[]{ kEndArrayChar, kEndOfString };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Array::getTerminalCharacters

nImO::DataKind
nImO::Array::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedOtherValue};

    ODL_OBJEXIT_I(StaticCast(int, result));
    return result;
} // nImO::Array::getTypeTag

nImO::ComparisonStatus
nImO::Array::greaterThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    // Note that all the values must be validated.
    for (auto & walker : *this)
    {
        if (walker)
        {
            result &= walker->greaterThan(other);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Array::greaterThan

nImO::ComparisonStatus
nImO::Array::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    // Note that all the values must be validated.
    for (auto & walker : *this)
    {
        if (walker)
        {
            result &= walker->greaterThanOrEqual(other);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Array::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Array::lessThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    // Note that all the values must be validated.
    for (auto & walker : *this)
    {
        if (walker)
        {
            result &= walker->lessThan(other);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Array::lessThan

nImO::ComparisonStatus
nImO::Array::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    // Note that all the values must be validated.
    for (auto & walker : *this)
    {
        if (walker)
        {
            result &= walker->lessThanOrEqual(other);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Array::lessThanOrEqual

nImO::Array &
nImO::Array::operator=
    (Array &&   other)
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
} // nImO::Array::operator=

std::ostream &
nImO::Array::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&out); //####
    out << kStartArrayChar;
    for (auto & walker : *this)
    {
        if (walker)
        {
            out << " " << *walker;
        }
    }
    out << " " << kEndArrayChar;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Array::operator<<

void
nImO::Array::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&outBuffer); //####
    ODL_B1(squished); //####
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
            walker->printToStringBuffer(outBuffer, squished);
            first = false;
        }
    }
    if (! squished)
    {
        outBuffer.appendChar(' ');
    }
    outBuffer.appendChar(kEndArrayChar);
    ODL_OBJEXIT(); //####
} // nImO::Array::printToStringBuffer

void
nImO::Array::printToStringBufferAsJSON
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
} // nImO::Array::printToStringBufferAsJSON

nImO::Array::const_iterator
nImO::Array::random
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
} /* nImO::Array::random */

nImO::Array::iterator
nImO::Array::random
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
} /* nImO::Array::random */

nImO::SpValue
nImO::Array::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2(&inBuffer, &position); //####
    bool    atEnd;
    bool    done{false};
    bool    valid{false};
    auto    result{std::make_shared<Array>()};
    size_t  localIndex{position};
    int     aChar{inBuffer.getChar(localIndex++, atEnd)};

    ODL_P1(result.get()); //####
    ODL_I1(localIndex); //####
    ODL_C1(aChar); //####
    ODL_B1(atEnd); //####
    if ((! atEnd) && (kStartArrayChar == aChar))
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
                if (kEndArrayChar == aChar)
                {
                    done = valid = true;
                }
                else
                {
                    auto    element{Value::readFromStringBuffer(inBuffer, localIndex)};

                    ODL_I1(localIndex); //####
                    if (element)
                    {
                        result->addValue(element);
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
        ODL_LOG("! (kStartArrayChar == aChar)"); //####
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
} // nImO::Array::readFromStringBuffer

size_t
nImO::Array::size
    (void)
    const
{
    ODL_OBJENTER(); //####
    size_t  result{inherited2::size()};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Array::size

void
nImO::Array::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_ENTER(); //####
    ODL_P1(&outMessage); //####
    if (0 < inherited2::size())
    {
        ODL_LOG("(0 < inherited2::size())"); //####
        DataKind           startArray{DataKind::Other | DataKind::OtherContainerStart |
                                        DataKind::OtherContainerTypeArray |
                                        DataKind::OtherContainerNonEmptyValue};
        DataKind           endArray{DataKind::Other | DataKind::OtherContainerEnd |
                                    DataKind::OtherContainerTypeArray |
                                    DataKind::OtherContainerNonEmptyValue};
        std::queue<double> doublesSeen;

        outMessage.appendBytes(&startArray, sizeof(startArray));
        writeInt64ToMessage(outMessage, StaticCast(int, inherited2::size()) + kDataKindIntegerShortValueMinValue - 1);
        for (auto & walker : *this)
        {
            if (walker)
            {
                // Check for sequences of Double values
                auto    doubleValue{walker->asDouble()};

                if (nullptr == doubleValue)
                {
                    Double::writeValuesToMessage(doublesSeen, outMessage);
                    walker->writeToMessage(outMessage);
                }
                else
                {
                    doublesSeen.push(doubleValue->getDoubleValue());
                }
            }
        }
        // Write out any held Double values
        Double::writeValuesToMessage(doublesSeen, outMessage);
        outMessage.appendBytes(&endArray, sizeof(endArray));
    }
    else
    {
        ODL_LOG("! (0 < inherited2::size())"); //####
        static const DataKind   stuff[]
        {
            (DataKind::Other | DataKind::OtherContainerStart |
             DataKind::OtherContainerTypeArray |
             DataKind::OtherContainerEmptyValue),
            (DataKind::Other | DataKind::OtherContainerEnd |
             DataKind::OtherContainerTypeArray |
             DataKind::OtherContainerEmptyValue)
        };

        outMessage.appendBytes(stuff, sizeof(stuff));
    }
    ODL_EXIT(); //####
} // nImO::Array::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

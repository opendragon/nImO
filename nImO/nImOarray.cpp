//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOarray.cpp
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

#include "nImOarray.hpp"

#include <nImOdouble.hpp>
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
        inherited1(), inherited2()
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::Array
    (const nImO::Array &    other) :
        inherited1(), inherited2()
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
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
    (const nImO::Array &    other)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    for (auto & walker : other)
    {
        addValue(walker);
    }
    ODL_EXIT_P(this); //####
    return *this;
} // nImO::Array::addEntries

const nImO::Array *
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
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result = (&other == this);

    if (! result)
    {
        const Array *   otherPtr = other.asArray();

        if (otherPtr && (size() == otherPtr->size()))
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
} // nImO::Array::deeplyEqualTo

bool
nImO::Array::empty
    (void)
    const
{
    ODL_ENTER(); //####
    bool    result = inherited2::empty();

    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Array::empty

nImO::ComparisonStatus
nImO::Array::equalTo
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{inherited2::begin() != inherited2::end()};

    // Note that all the values must be validated.
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (aValue)
        {
            result &= aValue->equalTo(other);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Array::equalTo

nImO::SpValue
nImO::Array::extractValue
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
        if (! atEnd)
        {
            ODL_LOG("(! atEnd)"); //####
            static const DataKind   endMarker = (DataKind::Other | DataKind::OtherContainerEnd |
                                                 DataKind::OtherContainerTypeArray | DataKind::OtherContainerEmptyValue);

            if (toUType(endMarker) == aByte)
            {
                ODL_LOG("(endMarker == aByte)"); //####
                result.reset(new Array);
                ++position;
                ODL_I1("position <- ", position); //####
            }
            else
            {
                ODL_LOG("! (endMarker == aByte)"); //####
                result.reset(new Invalid("Empty Array with incorrect end tag @", position));
            }
        }
    }
    else
    {
        ODL_LOG("! (isEmpty)"); //####
        aByte = theMessage.getByte(position, atEnd);
        ODL_X1("aByte <- ", aByte); //####
        ODL_B1("atEnd <- ", atEnd); //####
        if (! atEnd)
        {
            ODL_LOG("(! atEnd)"); //####
            IntStatus numStatus;
            int64_t   elementCount = extractInt64FromMessage(theMessage, aByte, position, numStatus);

            if (IntStatus::Successful == numStatus)
            {
                ODL_LOG("(IntStatus::Successful == status)"); //####
                elementCount -= DataKindIntegerShortValueMinValue - 1;
                ODL_I1("elementCount <- ", elementCount); //####
                if (0 >= elementCount)
                {
                    ODL_LOG("(0 >= elementCount)"); //####
                    result.reset(new Invalid("Array with zero or negative count @", position));
                }
                else
                {
                    auto    anArray{std::make_shared<Array>()};

                    result = anArray;
                    if (nullptr == result)
                    {
                        ODL_LOG("(nullptr == result)"); //####
                        result.reset(new Invalid("Could not allocate an Array"));
                    }
                    else
                    {
                        bool    okSoFar = true;

                        for ( ; okSoFar && (elementCount > StaticCast(int64_t, anArray->size())); )
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
                                SpValue aValue{getValueFromMessage(theMessage, position, aByte, anArray)};

                                // Note that it is the responsibility of the extractor to add to
                                // this Array, so it's not correct for this loop to perform an
                                // append operation.
                                if (nullptr == aValue)
                                {
                                    ODL_LOG("(nullptr == aValue)"); //####
                                    result.reset(new Invalid("Null Value read @", position));
                                    okSoFar = false;
                                }
                                else if (aValue->asFlaw())
                                {
                                    ODL_LOG("(aValue->asFlaw())"); //####
                                    result = aValue;
                                    okSoFar = false;
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
                                static const DataKind endMarker = (DataKind::Other | DataKind::OtherContainerEnd |
                                                                   DataKind::OtherContainerTypeArray |
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
                                    result.reset(new Invalid("Non-empty Array with incorrect end "
                                                             "tag @", position));
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                ODL_LOG("! (IntStatus::Successful == numStatus)"); //####
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
} // nImO::Array::extractValue

void
nImO::Array::getExtractionInfo
    (DataKind &                 aByte,
     DataKind &                 aMask,
     nImO::Value::Extractor &   theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (DataKind::Other | DataKind::OtherContainerStart | DataKind::OtherContainerTypeArray);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherContainerTypeMask);
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Array::getExtractionInfo

const char *
nImO::Array::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   initialChars[] = { kStartArrayChar, '\0' };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Array::getInitialCharacters

const char *
nImO::Array::getTerminalCharacters
    (void)
{
    ODL_ENTER(); //####
    static const char   terminalChars[] = { kEndArrayChar, '\0' };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Array::getTerminalCharacters

nImO::DataKind
nImO::Array::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result = DataKind::OtherMessageExpectedOtherValue;

    ODL_OBJEXIT_I(StaticCast(int, result));
    return result;
} // nImO::Array::getTypeTag

nImO::ComparisonStatus
nImO::Array::greaterThan
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result(inherited2::begin() != inherited2::end());

    // Note that all the values must be validated.
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (aValue)
        {
            result &= aValue->greaterThan(other);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Array::greaterThan

nImO::ComparisonStatus
nImO::Array::greaterThanOrEqual
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result(inherited2::begin() != inherited2::end());

    // Note that all the values must be validated.
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (aValue)
        {
            result &= aValue->greaterThanOrEqual(other);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Array::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Array::lessThan
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result(inherited2::begin() != inherited2::end());

    // Note that all the values must be validated.
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (aValue)
        {
            result &= aValue->lessThan(other);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Array::lessThan

nImO::ComparisonStatus
nImO::Array::lessThanOrEqual
    (const nImO::Value &    other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result(inherited2::begin() != inherited2::end());

    // Note that all the values must be validated.
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (aValue)
        {
            result &= aValue->lessThanOrEqual(other);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Array::lessThanOrEqual

std::ostream &
nImO::Array::operator <<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << kStartArrayChar;
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (nullptr != aValue)
        {
            out << " " << *aValue;
        }
    }
    out << " " << kEndArrayChar;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Array::operator <<

void
nImO::Array::printToStringBuffer
    (nImO::StringBuffer &   outBuffer,
     const bool             squished)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    bool    first = true;

    outBuffer.addChar(kStartArrayChar);
    for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue{*walker};

        if (nullptr != aValue)
        {
            if ((! squished) || (! first))
            {
                outBuffer.addChar(' ');
            }
            aValue->printToStringBuffer(outBuffer, squished);
            first = false;
        }
    }
    if (! squished)
    {
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndArrayChar);
    ODL_OBJEXIT(); //####
} // nImO::Array::printToStringBuffer

nImO::Array::const_iterator
nImO::Array::random
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result(inherited2::begin());
    size_t  howMany = size();

    if (0 < howMany)
    {
        for (size_t ii = 0, keyNumber = (rand() % howMany); ii < keyNumber; ++ii)
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
    auto    result(inherited2::begin());
    size_t  howMany = size();

    if (0 < howMany)
    {
        for (size_t ii = 0, keyNumber = (rand() % howMany); ii < keyNumber; ++ii)
        {
            ++result;
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} /* nImO::Array::random */

nImO::SpValue
nImO::Array::readFromStringBuffer
    (const nImO::StringBuffer & inBuffer,
     size_t &                   position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    bool    atEnd;
    bool    done = false;
    bool    valid = false;
    auto    result{std::make_shared<Array>()};
    size_t  localIndex = position;
    int     aChar = inBuffer.getChar(localIndex++, atEnd);

    ODL_P1("result <- ", result.get()); //####
    ODL_I1("localIndex <- ", localIndex); //####
    ODL_C1("aChar <- ", aChar); //####
    ODL_B1("atEnd <- ", atEnd); //####
    if ((! atEnd) && (kStartArrayChar == aChar))
    {
        for ( ; ! done; )
        {
            // Skip whitespace
            for (aChar = inBuffer.getChar(localIndex, atEnd); (! atEnd) && isspace(aChar); aChar = inBuffer.getChar(++localIndex, atEnd))
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
            else if (kEndArrayChar == aChar)
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
                    result->addValue(element);
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
    ODL_ENTER(); //####
    size_t  result = inherited2::size();

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Array::size

void
nImO::Array::writeToMessage
    (nImO::Message &    outMessage)
    const
{
    ODL_ENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    if (0 < inherited2::size())
    {
        ODL_LOG("(0 < inherited2::size())"); //####
        DataKind           startArray = (DataKind::Other | DataKind::OtherContainerStart |
                                         DataKind::OtherContainerTypeArray |
                                         DataKind::OtherContainerNonEmptyValue);
        DataKind           endArray = (DataKind::Other | DataKind::OtherContainerEnd |
                                       DataKind::OtherContainerTypeArray |
                                       DataKind::OtherContainerNonEmptyValue);
        std::queue<double> doublesSeen;

        outMessage.appendBytes(&startArray, sizeof(startArray));
        writeInt64ToMessage(outMessage, StaticCast(int, inherited2::size()) + DataKindIntegerShortValueMinValue - 1);
        for (auto walker(inherited2::begin()); inherited2::end() != walker; ++walker)
        {
            SpValue aValue{*walker};

            if (aValue)
            {
                // Check for sequences of Double values
                const Double *  doubleValue = aValue->asDouble();

                if (nullptr == doubleValue)
                {
                    Double::writeValuesToMessage(doublesSeen, outMessage);
                    aValue->writeToMessage(outMessage);
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
        static const DataKind   stuff[] =
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

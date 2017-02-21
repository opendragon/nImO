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

#include <nImO/nImOdouble.hpp>
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

nImO::Array::Array(void) :
    inherited1(), inherited2()
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::Array(const nImO::Array &other) :
    inherited1(), inherited2()
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::~Array(void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Array::~Array

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Array::addEntries(const nImO::Array &other)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    for (const_iterator walker(other.inherited2::begin()); other.inherited2::end() != walker;
         ++walker)
    {
        addValue(*walker);
    }
    ODL_EXIT(); //####
} // nImO::Array::addEntries

nImO::Array &
nImO::Array::addValue(nImO::SpValue newElement)
{
    ODL_OBJENTER(); //####
    ODL_P1("newElement = ", newElement.get()); //####
    if (nullptr != newElement)
    {
        inherited2::push_back(newElement);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Array::addValue

nImO::SpValue
nImO::Array::at(const nImO::Array::size_type index)
const
{
    ODL_OBJENTER(); //####
    SpValue result;

    if (index < inherited2::size())
    {
        result = inherited2::at(index);
    }
    else
    {
        result = nullptr;
    }
    ODL_OBJEXIT_P(result.get()); //####
    return result;
} // nImO::Array::at

void
nImO::Array::clear(void)
{
    ODL_OBJENTER(); //####
    inherited2::clear();
    ODL_OBJEXIT(); //####
} // nImO::Array::clear

bool
nImO::Array::deeplyEqualTo(const nImO::Value &other)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result = (&other == this);
    
    if (! result)
    {
        const Array *otherPtr = other.asArray();
        
        if (otherPtr && (size() == otherPtr->size()))
        {
            const_iterator thisWalker(inherited2::begin());
            const_iterator otherWalker(otherPtr->inherited2::begin());

            for (result = true; result && (thisWalker != inherited2::end());
                 ++thisWalker, ++otherWalker)
            {
                SpValue thisValue(*thisWalker);
                SpValue otherValue(*otherWalker);
                
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
nImO::Array::equalTo(const nImO::Value &other,
                     bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    // Note that all the values must be validated.
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(*walker);

        if (aValue)
        {
            result &= aValue->equalTo(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::equalTo

nImO::SpValue
nImO::Array::extractValue(const nImO::Message &theMessage,
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
    bool    isEmpty = (static_cast<int>(DataKind::OtherContainerEmptyValue) ==
                       (static_cast<int>(DataKind::OtherContainerEmptyMask) & leadByte));
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
            static const DataKind endMarker = (DataKind::Other | DataKind::OtherContainerEnd |
                                               DataKind::OtherContainerTypeArray |
                                               DataKind::OtherContainerEmptyValue);

            if (static_cast<uint8_t>(endMarker) == aByte)
            {
                ODL_LOG("(endMarker == aByte)"); //####
                result.reset(new Array);
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
                elementCount -= static_cast<int64_t>(DataKindIntegerShortValueMinValue) - 1;
                ODL_LL1("elementCount <- ", elementCount); //####
                if (0 >= elementCount)
                {
                    ODL_LOG("(0 >= elementCount)"); //####
                    status = ReadStatus::Invalid;
                    ODL_LL1("status <- ", static_cast<int>(status)); //####
                }
                else
                {
                    SpArray anArray(new Array);

                    result = anArray;
                    if (nullptr == result)
                    {
                        ODL_LOG("(nullptr == result)"); //####
                        status = ReadStatus::Invalid;
                        ODL_LL1("status <- ", static_cast<int>(status)); //####
                    }
                    else
                    {
                        bool okSoFar = true;

                        for ( ; okSoFar && (elementCount > static_cast<int64_t>(anArray->size())); )
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
                                SpValue aValue(getValueFromMessage(theMessage, position, aByte,
                                                                   status, anArray));

                                // Note that it is the responsibility of the extractor to add to
                                // this Array, so it's not correct for this loop to perform an
                                // append operation.
                                if (nullptr == aValue)
                                {
                                    ODL_LOG("(nullptr == aValue)"); //####
                                    okSoFar = false;
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
                                static const DataKind endMarker = (DataKind::Other |
                                                                   DataKind::OtherContainerEnd |
                                                               DataKind::OtherContainerTypeArray |
                                                           DataKind::OtherContainerNonEmptyValue);

                                if (static_cast<uint8_t>(endMarker) == aByte)
                                {
                                    ODL_LOG("(static_cast<uint8_t>(endMarker) == aByte)"); //####
                                    status = ReadStatus::Successful;
                                    ++position;
                                    ODL_LL2("status <- ", static_cast<int>(status), "position <- ", position); //####
                                }
                                else
                                {
                                    ODL_LOG("! (static_cast<uint8_t>(endMarker) == aByte)"); //####
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
} // nImO::Array::extractValue

void
nImO::Array::getExtractionInfo(uint8_t                &aByte,
                               uint8_t                &aMask,
                               nImO::Value::Extractor &theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = static_cast<uint8_t>(DataKind::Other | DataKind::OtherContainerStart |
                                 DataKind::OtherContainerTypeArray);
    aMask = static_cast<uint8_t>(DataKind::Mask | DataKind::OtherTypeMask |
                                 DataKind::OtherContainerTypeMask);
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Array::getExtractionInfo

const char *
nImO::Array::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char initialChars[] = { kStartArrayChar, '\0' };

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Array::getInitialCharacters

const char *
nImO::Array::getTerminalCharacters(void)
{
    ODL_ENTER(); //####
    static const char terminalChars[] = { kEndArrayChar, '\0' };

    ODL_EXIT_S(terminalChars); //####
    return terminalChars;
} // nImO::Array::getTerminalCharacters

bool
nImO::Array::greaterThan(const nImO::Value &other,
                         bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(*walker);

        if (aValue)
        {
            result &= aValue->greaterThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::greaterThan

bool
nImO::Array::greaterThanOrEqual(const nImO::Value &other,
                                bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(*walker);

        if (aValue)
        {
            result &= aValue->greaterThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::greaterThanOrEqual

bool
nImO::Array::lessThan(const nImO::Value &other,
                      bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(*walker);

        if (aValue)
        {
            result &= aValue->lessThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::lessThan

bool
nImO::Array::lessThanOrEqual(const nImO::Value &other,
                             bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        SpValue aValue(*walker);

        if (aValue)
        {
            result &= aValue->lessThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::lessThanOrEqual

nImO::Array &
nImO::Array::operator =(const nImO::Array &other)
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
} // nImO::Array::operator=

void
nImO::Array::printToStringBuffer(nImO::StringBuffer &outBuffer,
                                 const bool         squished)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    bool first = true;

    outBuffer.addChar(kStartArrayChar);
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        SpValue aValue(*walker);

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

nImO::SpValue
nImO::Array::readFromStringBuffer(const nImO::StringBuffer &inBuffer,
                                  size_t                   &position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    bool    done = false;
    bool    valid = false;
    SpArray result(new Array);
    size_t  localIndex = position;
    int     aChar = inBuffer.getChar(localIndex++);

    ODL_P1("result <- ", result.get()); //####
    ODL_LL1("localIndex <- ", localIndex); //####
    ODL_C1("aChar <- ", aChar); //####
    if (kStartArrayChar == aChar)
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
                ODL_LOG("(StringBuffer::kEndCharacter == aChar)"); //####
                done = true;
            }
            else if (kEndArrayChar == aChar)
            {
                done = valid = true;
            }
            else
            {
                SpValue element(Value::readFromStringBuffer(inBuffer, localIndex));

                ODL_LL1("localIndex <- ", localIndex); //####
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

void
nImO::Array::writeToMessage(nImO::Message &outMessage)
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
        writeInt64ToMessage(outMessage, inherited2::size() +
                            static_cast<int64_t>(DataKindIntegerShortValueMinValue) - 1);
        for (const_iterator walker(inherited2::begin()); (inherited2::end() != walker); ++walker)
        {
            SpValue aValue(*walker);

            if (aValue)
            {
                // Check for sequences of Double values
                const Double *doubleValue = aValue->asDouble();
                
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
        static const DataKind stuff[] =
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

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOdouble.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO numeric values.
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
//  Created:    2016-04-26
//
//--------------------------------------------------------------------------------------------------

#include "nImOdouble.hpp"

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
 @brief The class definition for %nImO numeric values. */
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

nImO::Double::Double(void) :
    inherited(), _floatValue(0)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Double::Double

nImO::Double::Double(const double initialValue) :
    inherited(), _floatValue(initialValue)
{
    ODL_ENTER(); //####
    ODL_D1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Double::Double

nImO::Double::Double(const nImO::Double &other) :
    inherited(), _floatValue(other._floatValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Double::Double

nImO::Double::~Double(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Double::~Double

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

const nImO::Double *
nImO::Double::asDouble(void)
const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Double::asDouble

bool
nImO::Double::deeplyEqualTo(const nImO::Value &other)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result = (&other == this);

    if (! result)
    {
        const Double *otherPtr = other.asDouble();

        if (nullptr != otherPtr)
        {
            result = (_floatValue == otherPtr->_floatValue);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Double::deeplyEqualTo

nImO::Enumerable
nImO::Double::enumerationType(void)
const
{
    ODL_OBJENTER(); //####
    Enumerable result = Enumerable::NotEnumerable;

    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Double::enumerationType

bool
nImO::Double::equalTo(const nImO::Value &other,
                      bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.equalTo(*this, validComparison);
                }
            }
            else
            {
                result = (_floatValue == intPtr->getIntegerValue());
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_floatValue == doublePtr->_floatValue);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Double::equalTo

nImO::SpValue
nImO::Double::extractValue(const nImO::Message &theMessage,
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
    bool    atEnd;
    bool    isShort = (DataKind::DoubleShortCount == (DataKind::DoubleCountMask & leadByte));
    int64_t howMany;

    ++position; // We will always accept the lead byte
    ODL_LL1("position <- ", position); //####
    if (isShort)
    {
        howMany = toUType(DataKind::DoubleShortCountMask & leadByte) + 1;
        ODL_LL1("howMany <- ", howMany);
    }
    else
    {
        size_t        size = toUType(DataKind::DoubleLongCountMask & leadByte) + 1;
        NumberAsBytes holder;
        bool          okSoFar = true;

        for (size_t ii = 0; okSoFar && (size > ii); ++ii)
        {
            int aByte = theMessage.getByte(position, atEnd);

            if (atEnd)
            {
                ODL_LOG("(atEnd)"); //####
                status = ReadStatus::Incomplete;
                ODL_LL1("status <- ", toUType(status)); //####
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
            howMany = B2I(holder, size);
            ODL_LL1("howMany <- ", howMany);
        }
        else
        {
            howMany = 0;
        }
    }
    if (0 < howMany)
    {
        bool          okSoFar = ((1 == howMany) || (nullptr != parentValue));
        NumberAsBytes holder;

        status = ReadStatus::Invalid;
        ODL_LL1("status <- ", toUType(status)); //####
        for (int64_t ii = 0; okSoFar && (howMany > ii); ++ii)
        {
            for (size_t jj = 0; okSoFar && (sizeof(int64_t) > jj); ++jj)
            {
                int aByte = theMessage.getByte(position, atEnd);

                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    status = ReadStatus::Incomplete;
                    ODL_LL1("status <- ", toUType(status)); //####
                    okSoFar = false;
                }
                else
                {
                    holder[jj] = static_cast<uint8_t>(aByte);
                    ++position;
                    ODL_LL1("position <- ", position); //####
                }
            }
            if (okSoFar)
            {
                result.reset(new Double(B2D(holder)));
                if ((nullptr != parentValue) && (nullptr != result))
                {
                    ODL_LOG("((nullptr != parentValue) && (nullptr != result))"); //####
                    parentValue->addValue(result);
                }
            }
            else
            {
                result.reset();
            }
        }
        if (okSoFar)
        {
            status = ReadStatus::Successful;
            ODL_LL1("status <- ", toUType(status)); //####
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Double::extractValue

void
nImO::Double::getExtractionInfo(DataKind               &aByte,
                                DataKind               &aMask,
                                nImO::Value::Extractor &theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = DataKind::Double;
    aMask = DataKind::Mask;
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Double::getExtractionInfo

nImO::DataKind
nImO::Double::getTypeTag(void)
const
{
    ODL_OBJENTER(); //####
    DataKind result = DataKind::OtherMessageExpectedDoubleValue;

    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Double::getTypeTag

bool
nImO::Double::greaterThan(const nImO::Value &other,
                          bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.lessThan(*this, validComparison);
                }
            }
            else
            {
                result = (_floatValue > intPtr->getIntegerValue());
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_floatValue > doublePtr->_floatValue);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Double::greaterThan

bool
nImO::Double::greaterThanOrEqual(const nImO::Value &other,
                                 bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.lessThanOrEqual(*this, validComparison);
                }
            }
            else
            {
                result = (_floatValue >= intPtr->getIntegerValue());
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_floatValue >= doublePtr->_floatValue);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Double::greaterThanOrEqual

bool
nImO::Double::lessThan(const nImO::Value &other,
                       bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.greaterThan(*this, validComparison);
                }
            }
            else
            {
                result = (_floatValue < intPtr->getIntegerValue());
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_floatValue < doublePtr->_floatValue);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Double::lessThan

bool
nImO::Double::lessThanOrEqual(const nImO::Value &other,
                              bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.greaterThanOrEqual(*this, validComparison);
                }
            }
            else
            {
                result = (_floatValue <= intPtr->getIntegerValue());
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_floatValue <= doublePtr->_floatValue);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Double::lessThanOrEqual

nImO::Double &
nImO::Double::operator =(const nImO::Double &other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _floatValue = other._floatValue;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Double::operator=

nImO::Double &
nImO::Double::operator =(const double value)
{
    ODL_OBJENTER(); //####
    ODL_D1("value = ", value); //####
    _floatValue = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Double::operator=

void
nImO::Double::printToStringBuffer(nImO::StringBuffer &outBuffer,
                                  const bool         squished)
const
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(squished)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addDouble(_floatValue);
    ODL_OBJEXIT(); //####
} // nImO::Double::printToStringBuffer

void
nImO::Double::writeToMessage(nImO::Message &outMessage)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    NumberAsBytes numBuff;

    D2B(_floatValue, numBuff);
    DataKind stuff = (DataKind::Double | DataKind::DoubleShortCount |
                      ((1 - DataKindDoubleShortCountMinValue) & DataKind::DoubleShortCountMask));

    outMessage.appendBytes(&stuff, sizeof(stuff));
    outMessage.appendBytes(numBuff, sizeof(numBuff));
    ODL_OBJEXIT(); //####
} // nImO::Double::writeToMessage

void
nImO::Double::writeValuesToMessage(std::queue<double> &values,
                                   nImO::Message      &outMessage)
{
    ODL_ENTER(); //####
    ODL_P2("values = ", &values, "outMessage = ", &outMessage); //####
    NumberAsBytes numBuff;
    size_t        numValues = values.size();

    // First, the count.
    if (0 < numValues)
    {
        ODL_LOG("(0 < numValues)"); //####
        if (static_cast<size_t>(DataKindDoubleShortCountMaxValue) < numValues)
        {
            ODL_LOG("(static_cast<size_t>(DataKindDoubleShortCountMaxValue) < numValues)"); //####
            size_t numBytes = I2B(numValues, numBuff);

            if (0 < numBytes)
            {
                ODL_LOG("(0 < numBytes)"); //####
                DataKind countTag = (DataKind::Double | DataKind::DoubleLongCount |
                                     (DataKind::DoubleLongCountMask & (numBytes - 1)));

                outMessage.appendBytes(&countTag, sizeof(countTag));
                outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
            }
        }
        else
        {
            ODL_LOG("! (static_cast<size_t>(DataKindDoubleShortCountMaxValue) < numValues)"); //####
            DataKind countTag = (DataKind::Double | DataKind::DoubleShortCount |
                                 ((numValues - DataKindDoubleShortCountMinValue) &
                                                       DataKind::DoubleShortCountMask));

            outMessage.appendBytes(&countTag, sizeof(countTag));
        }
        // And now the values.
        for ( ; ! values.empty(); values.pop())
        {
            double aValue = values.front();

            D2B(aValue, numBuff);
            outMessage.appendBytes(numBuff, sizeof(numBuff));
        }
    }
    ODL_EXIT(); //####
} // nImO::Double::writeValuesToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

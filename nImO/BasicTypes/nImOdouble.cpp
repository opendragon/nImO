//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOdouble.cpp
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

#include <BasicTypes/nImOdouble.h>

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

nImO::Double::Double
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Double::Double

nImO::Double::Double
    (const double   initialValue) :
        inherited{}, _floatValue{initialValue}
{
    ODL_ENTER(); //####
    ODL_D1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Double::Double

nImO::Double::Double
    (const Double & other) :
        inherited{}, _floatValue{other._floatValue}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Double::Double

nImO::Double::Double
    (Double &&  other)
    noexcept :
        inherited{std::move(other)}, _floatValue{other._floatValue}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._floatValue = 0;
    ODL_EXIT_P(this); //####
} // nImO::Double::Double

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::Double)
nImO::Double::asDouble
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Double::asDouble

bool
nImO::Double::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(Double)    otherPtr{other.asDouble()};

        if (nullptr != otherPtr)
        {
            result = (_floatValue == otherPtr->_floatValue);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Double::deeplyEqualTo

std::ostream &
nImO::Double::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("output = ", &output); //####
    output << "double";
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::Double::describe

nImO::Enumerable
nImO::Double::enumerationType
    (void)
    const
{
    ODL_OBJENTER(); //####
    Enumerable  result{Enumerable::NotEnumerable};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Double::enumerationType

nImO::ComparisonStatus
nImO::Double::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.equalTo(*this);
                }
            }
            else
            {
                result = (_floatValue == intPtr->getIntegerValue());
            }
        }
        else
        {
            result = (_floatValue == doublePtr->_floatValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Double::equalTo

nImO::SpValue
nImO::Double::extractValue
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
    bool    isShort{DataKind::DoubleShortCount == (DataKind::DoubleCountMask & leadByte)};
    int64_t howMany;

    ++position; // We will always accept the lead byte
    ODL_I1("position <- ", position); //####
    if (isShort)
    {
        howMany = toUType(DataKind::DoubleShortCountMask & leadByte) + 1;
        ODL_I1("howMany <- ", howMany);
    }
    else
    {
        size_t          size{StaticCast(size_t, toUType(DataKind::DoubleLongCountMask & leadByte) + 1)};
        NumberAsBytes   holder;
        bool            okSoFar{true};

        for (size_t ii = 0; okSoFar && (size > ii); ++ii)
        {
            int aByte{theMessage.getByte(position, atEnd)};

            if (atEnd)
            {
                ODL_LOG("(atEnd)"); //####
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
            howMany = B2I(holder, size);
            ODL_I1("howMany <- ", howMany);
        }
        else
        {
            howMany = 0;
        }
    }
    if (0 < howMany)
    {
        bool            okSoFar{(1 == howMany) || (nullptr != parentValue)};
        NumberAsBytes   holder;

        if (! okSoFar)
        {
            result = std::make_shared<Invalid>("Bad count for Double", position);
        }
        for (int64_t ii = 0; okSoFar && (howMany > ii); ++ii)
        {
            for (size_t jj = 0; okSoFar && (sizeof(int64_t) > jj); ++jj)
            {
                int aByte{theMessage.getByte(position, atEnd)};

                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    result.reset();
                    okSoFar = false;
                }
                else
                {
                    holder[jj] = StaticCast(uint8_t, aByte);
                    ++position;
                    ODL_I1("position <- ", position); //####
                }
            }
            if (okSoFar)
            {
                result = std::make_shared<Double>(B2D(holder));
                if (parentValue && result)
                {
                    ODL_LOG("(parentValue && result)"); //####
                    parentValue->addValue(result);
                }
            }
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Double::extractValue

nImO::Value::Extractor
nImO::Double::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2("aByte = ", &aByte, "aMask = ", &aMask); //####
    aByte = DataKind::Double;
    aMask = DataKind::Mask;
    ODL_EXIT(); //####
    return extractValue;
} // nImO::Double::getExtractionInfo

nImO::DataKind
nImO::Double::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedDoubleValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Double::getTypeTag

nImO::ComparisonStatus
nImO::Double::greaterThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other == this)
    {
        result = false;
    }
    else
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.lessThan(*this);
                }
            }
            else
            {
                result = (_floatValue > intPtr->getIntegerValue());
            }
        }
        else
        {
            result = (_floatValue > doublePtr->_floatValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Double::greaterThan

nImO::ComparisonStatus
nImO::Double::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.lessThanOrEqual(*this);
                }
            }
            else
            {
                result = (_floatValue >= intPtr->getIntegerValue());
            }
        }
        else
        {
            result = (_floatValue >= doublePtr->_floatValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Double::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Double::lessThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other == this)
    {
        result = false;
    }
    else
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.greaterThan(*this);
                }
            }
            else
            {
                result = (_floatValue < intPtr->getIntegerValue());
            }
        }
        else
        {
            result = (_floatValue < doublePtr->_floatValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Double::lessThan

nImO::ComparisonStatus
nImO::Double::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.greaterThanOrEqual(*this);
                }
            }
            else
            {
                result = (_floatValue <= intPtr->getIntegerValue());
            }
        }
        else
        {
            result = (_floatValue <= doublePtr->_floatValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Double::lessThanOrEqual

nImO::Double &
nImO::Double::operator=
    (Double &&  other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _floatValue = other._floatValue;
        other._floatValue = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Double::operator=

std::ostream &
nImO::Double::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << _floatValue;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Double::operator<<

void
nImO::Double::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addDouble(_floatValue);
    ODL_OBJEXIT(); //####
} // nImO::Double::printToStringBuffer

void
nImO::Double::printToStringBufferAsJSON
    (StringBuffer & outBuffer,
     const bool     asKey,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(asKey);
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B2("asKey = ", asKey, "squished = ", squished); //####
    outBuffer.addDouble(_floatValue);
    ODL_OBJEXIT(); //####
} // nImO::Double::printToStringBufferAsJSON

void
nImO::Double::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    NumberAsBytes   numBuff;

    D2B(_floatValue, numBuff);
    DataKind    stuff{DataKind::Double | DataKind::DoubleShortCount |
                        ((1 - kDataKindDoubleShortCountMinValue) & DataKind::DoubleShortCountMask)};

    outMessage.appendBytes(&stuff, sizeof(stuff));
    outMessage.appendBytes(numBuff, sizeof(numBuff));
    ODL_OBJEXIT(); //####
} // nImO::Double::writeToMessage

void
nImO::Double::writeValuesToMessage
    (std::queue<double> &   values,
     nImO::Message &        outMessage)
{
    ODL_ENTER(); //####
    ODL_P2("values = ", &values, "outMessage = ", &outMessage); //####
    NumberAsBytes   numBuff;
    size_t          numValues{values.size()};

    // First, the count.
    if (0 < numValues)
    {
        ODL_LOG("(0 < numValues)"); //####
        if (StaticCast(size_t, kDataKindDoubleShortCountMaxValue) < numValues)
        {
            ODL_LOG("(StaticCast(size_t, kDataKindDoubleShortCountMaxValue) < numValues)"); //####
            size_t  numBytes{I2B(numValues, numBuff)};

            if (0 < numBytes)
            {
                ODL_LOG("(0 < numBytes)"); //####
                DataKind    countTag{DataKind::Double | DataKind::DoubleLongCount |
                                        (DataKind::DoubleLongCountMask &
                                         StaticCast(DataKind, numBytes - 1))};

                outMessage.appendBytes(&countTag, sizeof(countTag));
                outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
            }
        }
        else
        {
            ODL_LOG("! (StaticCast(size_t, kDataKindDoubleShortCountMaxValue) < numValues)"); //####
            DataKind    countTag{DataKind::Double | DataKind::DoubleShortCount |
                                    (StaticCast(DataKind, numValues - kDataKindDoubleShortCountMinValue) &
                                     DataKind::DoubleShortCountMask)};

            outMessage.appendBytes(&countTag, sizeof(countTag));
        }
        // And now the values.
        for ( ; ! values.empty(); values.pop())
        {
            double  aValue{values.front()};

            D2B(aValue, numBuff);
            outMessage.appendBytes(numBuff, sizeof(numBuff));
        }
    }
    ODL_EXIT(); //####
} // nImO::Double::writeValuesToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

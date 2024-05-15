//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOdate.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO Date values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-05-15
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOdate.h>

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
 @brief The class definition for %nImO Date values. */
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

/*! @brief Convert a 32-bit unsigned value into a sequence of bytes in network order.
 @param[out] outValue The byte sequence.
 @param[in] inValue The input value. */
static void
convertToIntArray
    (nImO::DateTime::DateTimeInts & outValue,
     const uint32_t                 inValue)
{
    outValue[2] = StaticCast(uint16_t, inValue % 31) + 1;
    outValue[1] = StaticCast(uint16_t, (inValue / 31) % 12) + 1;
    outValue[0] = StaticCast(uint16_t, (inValue / (31 * 12)) % 10000) + 1;
} // convertToIntArray

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Date::Date
    (void) :
        inherited{true}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Date::Date

nImO::Date::Date
    (const uint32_t initialValue) :
        inherited{initialValue, true}
{
    ODL_ENTER(); //####
    ODL_X1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Date::Date

nImO::Date::Date
    (const DateTimeBytes &  initialValue) :
        inherited{initialValue, true}
{
    ODL_ENTER(); //####
    ODL_P1("initialValue = ", &initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Date::Date

nImO::Date::Date
    (const Date &   other) :
        inherited{other}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Date::Date

nImO::Date::Date
    (Date && other)
    noexcept :
        inherited{std::move(other)}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Date::Date

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::Date)
nImO::Date::asDate
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Date::asDate

bool
nImO::Date::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(Date)   otherPtr{other.asDate()};

        if (nullptr != otherPtr)
        {
            result = (_dateTimeValue == otherPtr->_dateTimeValue);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Date::deeplyEqualTo

std::ostream &
nImO::Date::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("output = ", &output); //####
    output << "date";
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::Date::describe

nImO::Enumerable
nImO::Date::enumerationType
    (void)
    const
{
    ODL_OBJENTER(); //####
    Enumerable  result{Enumerable::Date};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Date::enumerationType

nImO::ComparisonStatus
nImO::Date::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Date)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
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
            result = (_dateTimeValue == otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Date::equalTo

nImO::ComparisonStatus
nImO::Date::greaterThan
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
        CPtr(Date)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
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
            result = (_dateTimeValue > otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Date::greaterThan

nImO::ComparisonStatus
nImO::Date::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Date)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
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
            result = (_dateTimeValue >= otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Date::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Date::lessThan
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
        CPtr(Date)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
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
            result = (_dateTimeValue < otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Date::lessThan

nImO::ComparisonStatus
nImO::Date::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Date)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
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
            result = (_dateTimeValue <= otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Date::lessThanOrEqual

std::ostream &
nImO::Date::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    DateTimeInts    ints;

    convertToIntArray(ints, _dateTimeValue);
    out << kStartDateTimeChar << kSecondCharForDate << ints[0] << kDateSeparator << ints[1] << kDateSeparator << ints[2];
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Date::operator<<

void
nImO::Date::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    DateTimeInts    ints;

    convertToIntArray(ints, _dateTimeValue);
    outBuffer.appendChar(kStartDateTimeChar);
    outBuffer.appendChar(kSecondCharForDate);
    outBuffer.addLong(ints[0]);
    outBuffer.appendChar(kDateSeparator);
    outBuffer.addLong(ints[1]);
    outBuffer.appendChar(kDateSeparator);
    outBuffer.addLong(ints[2]);
    ODL_OBJEXIT(); //####
} // nImO::Date::printToStringBuffer

void
nImO::Date::printToStringBufferAsJSON
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
    DateTimeInts    ints;

    convertToIntArray(ints, _dateTimeValue);
    outBuffer.appendChar(kDoubleQuote);
    outBuffer.addLong(ints[0]);
    outBuffer.appendChar(kDateSeparator);
    outBuffer.addLong(ints[1]);
    outBuffer.appendChar(kDateSeparator);
    outBuffer.addLong(ints[2]);
    outBuffer.appendChar(kDoubleQuote);
    ODL_OBJEXIT(); //####
} // nImO::Date::printToStringBufferAsJSON

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

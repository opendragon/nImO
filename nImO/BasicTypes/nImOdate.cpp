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

#include <BasicTypes/nImOvalue.h>
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

/*! @brief Extract the day from a date.
 @param[in] aDate The date to be processed.
 @return The day part of the date. */
static constexpr uint16_t
dayFromDateTime
    (const nImO::DateTimeValue  aDate)
{
    return StaticCast(uint16_t, aDate % (nImO::kMaxDay + 1));
} // dayFromDateTime

/*! @brief Extract the month from a date.
 @param[in] aDate The date to be processed.
 @return The month part of the date. */
static constexpr uint16_t
monthFromDateTime
    (const nImO::DateTimeValue  aDate)
{
    return StaticCast(uint16_t, (aDate / (nImO::kMaxDay + 1)) % (nImO::kMaxMonth + 1));
} // monthFromDateTime

/*! @brief Extract the year from a date.
 @param[in] aDate The date to be processed.
 @return The year part of the date. */
static constexpr uint16_t
yearFromDateTime
    (const nImO::DateTimeValue  aDate)
{
    return StaticCast(uint16_t, (aDate / ((nImO::kMaxDay + 1) * (nImO::kMaxMonth + 1))) % (nImO::kMaxYear + 1));
} // yearFromDateTime

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Date::Date
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Date::Date

nImO::Date::Date
    (const DateTimeValue    initialValue) :
        inherited{initialValue}
{
    ODL_ENTER(); //####
    ODL_X1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Date::Date

nImO::Date::Date
    (const DateTimeBytes &  initialValue) :
        inherited{initialValue}
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

uint16_t
nImO::Date::day
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{dayFromDateTime(_dateTimeValue)};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Date::day

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

nImO::SpValue
nImO::Date::extractValue
    (const Message &    theMessage,
     const int          leadByte,
     size_t &           position,
     SpArray            parentValue)
{
    NIMO_UNUSED_VAR_(leadByte);
    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "parentValue = ", parentValue.get()); //####
    ODL_X1("leadByte = ", leadByte); //####
    SpValue         result;
    DateTimeValue   accumulator{0};
    bool            atEnd{false};

    ++position; // We will always accept the lead byte
    for (int ii = 0; (ii < 4) && (! atEnd); ++ii)
    {
        uint8_t aByte = theMessage.getByte(position, atEnd);

        ODL_X1("aByte <- ", aByte); //####
        ODL_B1("atEnd <- ", atEnd); //####
        if (atEnd)
        {
            ODL_LOG("(atEnd)"); //####
        }
        else
        {
            accumulator = ((accumulator << 8) | aByte);
            ++position;
            ODL_I1("position <- ", position); //####
        }
    }
    if (atEnd)
    {
        ODL_LOG("(atEnd)"); //####
        result.reset();
    }
    else
    {
        result = std::make_shared<Date>(accumulator);
    }
    if (parentValue && result)
    {
        ODL_LOG("(parentValue && result)"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Date::extractValue

nImO::Value::Extractor
nImO::Date::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2("aByte = ", &aByte, "aMask = ", &aMask); //####
    aByte = (DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
             DataKind::OtherMiscellaneousTypeBitFieldTypeDate);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherMiscellaneousTypeMask |
             DataKind::OtherMiscellaneousTypeBitFieldTypeMask);
    ODL_EXIT(); //####
    return extractValue;
} // nImO::Date::getExtractionInfo

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

uint16_t
nImO::Date::month
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{monthFromDateTime(_dateTimeValue)};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Date::month

std::ostream &
nImO::Date::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << kStartDateTimeChar << kSecondCharForDate << ConvertDateToString(_dateTimeValue);
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
    outBuffer.appendChar(kStartDateTimeChar);
    outBuffer.appendChar(kSecondCharForDate);
    outBuffer.addString(ConvertDateToString(_dateTimeValue));
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
    outBuffer.appendChar(kDoubleQuote);
    outBuffer.addString(ConvertDateToString(_dateTimeValue));
    outBuffer.appendChar(kDoubleQuote);
    ODL_OBJEXIT(); //####
} // nImO::Date::printToStringBufferAsJSON

void
nImO::Date::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    DataKind        stuff{DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                            DataKind::OtherMiscellaneousTypeBitFieldTypeDate};
    DateTimeBytes   bytes;

    convertToByteArray(bytes, _dateTimeValue);
    outMessage.appendBytes(&stuff, sizeof(stuff));
    outMessage.appendBytes(bytes, sizeof(bytes));
    ODL_OBJEXIT(); //####
} // nImO::Date::writeToMessage

uint16_t
nImO::Date::year
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{yearFromDateTime(_dateTimeValue)};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Date::year

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

std::string
nImO::ConvertDateToString
    (const DateTimeValue    value)
{
    ODL_ENTER(); //####
    ODL_I1("value = ", value);
    std::string result{std::to_string(yearFromDateTime(value)) + kDateSeparator +
                        std::to_string(monthFromDateTime(value)) + kDateSeparator +
                        std::to_string(dayFromDateTime(value))};

    ODL_EXIT_s(result); //####
    return result;
} // nImO::ConvertDateToString

bool
nImO::GetDatePieces
    (Date::DatePieces &     pieces,
     const std::string &    inString,
     Ptr(size_t)            processedLength)
{
    // y/m/d
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    ODL_P1("processedLength = ", processedLength); //####
    bool            okSoFar{true};
    const int       maxs[] = { kMaxYear, kMaxMonth, kMaxDay };
    const int       mins[] = { kMinYear, kMinMonth, kMinDay };
    const size_t    numE{numElementsInArray(pieces)};

    for (size_t ii = 0; ii < numE; ++ii)
    {
        pieces[ii] = mins[ii];
    }
    if (0 < inString.length())
    {
        CPtr(char)  beginPtr{inString.c_str()};
        Ptr(char)   endPtr{nullptr};
        CPtr(char)  walker{beginPtr};

        for (size_t ii = 0; okSoFar && (ii < numE); ++ii)
        {
            int64_t value{strtoll(walker, &endPtr, 10)};

            if (walker == endPtr)
            {
                okSoFar = false;
                ODL_B1("okSoFar <- ", okSoFar); //####
            }
            else
            {
                if ((maxs[ii] < value) || (mins[ii] > value))
                {
                    okSoFar = false;
                    ODL_B1("okSoFar <- ", okSoFar); //####
                }
                else
                {
                    char    aChar{*endPtr};

                    ODL_C1("aChar <- ", aChar); //####
                    if (((kEndOfString == aChar) || Value::isLegalTerminator(aChar)) && (ii == (numE - 1)))
                    {
                        pieces[ii] = StaticCast(uint16_t, value);
                        ODL_I1("pieces[ii] <- ", pieces[ii]); //####
                    }
                    else
                    {
                        if ((kDateSeparator == aChar) && (ii < (numE - 1)))
                        {
                            pieces[ii] = StaticCast(uint16_t, value);
                            ODL_I1("pieces[ii] <- ", pieces[ii]); //####
                            walker = endPtr + 1;
                        }
                        else
                        {
                            okSoFar = false;
                            ODL_B1("okSoFar <- ", okSoFar); //####
                        }
                    }
                }
            }
        }
        if (okSoFar && (nullptr != processedLength))
        {
            *processedLength = endPtr - beginPtr;
            ODL_I1("*processedLength <- ", *processedLength); //####
        }
    }
    else
    {
        okSoFar = false;
        ODL_B1("okSoFar <- ", okSoFar); //####
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetDatePieces

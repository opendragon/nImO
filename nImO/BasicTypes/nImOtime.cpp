//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOtime.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO Time values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2025 by OpenDragon.
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

#include <BasicTypes/nImOtime.h>

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
 @brief The class definition for %nImO Time values. */
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

/*! @brief Convert a 16-bit unsigned value into a string with a specific width.
 @param[out] value The input value.
 @param[in] numDigits The requested number of digits.
 @return The value as a string of the specified width. */
static std::string
paddedDecimal
    (const uint16_t value,
     const int      numDigits)
{
    std::string result{std::to_string(value)};
    int         numToPad{numDigits - StaticCast(int, result.length())};
    std::string padding;

    if (0 < numToPad)
    {
        padding = std::string(numToPad, '0');
    }
    return padding + result;
} // paddedDecimal

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Time::Time
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Time::Time

nImO::Time::Time
    (const DateTimeValue    initialValue) :
        inherited{initialValue}
{
    ODL_ENTER(); //####
    ODL_X1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Time::Time

nImO::Time::Time
    (const DateTimeBytes &  initialValue) :
        inherited{initialValue}
{
    ODL_ENTER(); //####
    ODL_P1("initialValue = ", &initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Time::Time

nImO::Time::Time
    (const Time &    other) :
        inherited{other}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Time::Time

nImO::Time::Time
    (Time && other)
    noexcept :
        inherited{std::move(other)}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Time::Time

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::Time)
nImO::Time::asTime
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Time::asTime

bool
nImO::Time::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(Time)   otherPtr{other.asTime()};

        if (nullptr != otherPtr)
        {
            result = (_dateTimeValue == otherPtr->_dateTimeValue);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Time::deeplyEqualTo

std::ostream &
nImO::Time::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("output = ", &output); //####
    output << "time";
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::Time::describe

nImO::Enumerable
nImO::Time::enumerationType
    (void)
    const
{
    ODL_OBJENTER(); //####
    Enumerable  result{Enumerable::Time};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Time::enumerationType

nImO::ComparisonStatus
nImO::Time::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Time)   otherPtr{other.asTime()};

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
} // nImO::Time::equalTo

nImO::SpValue
nImO::Time::extractValue
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
        result = std::make_shared<Time>(accumulator);
    }
    if (parentValue && result)
    {
        ODL_LOG("(parentValue && result)"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Time::extractValue

nImO::Value::Extractor
nImO::Time::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2("aByte = ", &aByte, "aMask = ", &aMask); //####
    aByte = (DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
             DataKind::OtherMiscellaneousTypeBitFieldTypeTime);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherMiscellaneousTypeMask |
             DataKind::OtherMiscellaneousTypeBitFieldTypeMask);
    ODL_EXIT(); //####
    return extractValue;
} // nImO::Time::getExtractionInfo

nImO::ComparisonStatus
nImO::Time::greaterThan
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
        CPtr(Time)   otherPtr{other.asTime()};

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
} // nImO::Time::greaterThan

nImO::ComparisonStatus
nImO::Time::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Time)   otherPtr{other.asTime()};

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
} // nImO::Time::greaterThanOrEqual

uint16_t
nImO::Time::hour
    (void)
    const
{
    ODL_OBJENTER(); //####
    uint16_t    result{StaticCast(uint16_t, (_dateTimeValue / ((nImO::kMaxMilliseconds + 1) * (nImO::kMaxSeconds + 1) * (nImO::kMaxSeconds + 1))) % (nImO::kMaxHours + 1))};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Time::hour

nImO::ComparisonStatus
nImO::Time::lessThan
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
        CPtr(Time)   otherPtr{other.asTime()};

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
} // nImO::Time::lessThan

nImO::ComparisonStatus
nImO::Time::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Time)   otherPtr{other.asTime()};

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
} // nImO::Time::lessThanOrEqual

uint16_t
nImO::Time::millisecond
    (void)
    const
{
    ODL_OBJENTER(); //####
    uint16_t    result{StaticCast(uint16_t, _dateTimeValue % (nImO::kMaxMilliseconds + 1))};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Time::millisecond

uint16_t
nImO::Time::minute
    (void)
    const
{
    ODL_OBJENTER(); //####
    uint16_t    result{StaticCast(uint16_t, (_dateTimeValue / ((nImO::kMaxMilliseconds + 1) * (nImO::kMaxSeconds + 1))) % (nImO::kMaxSeconds + 1))};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Time::minute

std::ostream &
nImO::Time::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << kStartDateTimeChar << kSecondCharForTime << paddedDecimal(hour(), 2) << kTimeSeparator << paddedDecimal(minute(), 2) <<
            kTimeSeparator << paddedDecimal(second(), 2) << kSecondMillisecondSeparator << paddedDecimal(millisecond(), 3);
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Time::operator<<

void
nImO::Time::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.appendChar(kStartDateTimeChar);
    outBuffer.appendChar(kSecondCharForTime);
    outBuffer.addString(paddedDecimal(hour(), 2));
    outBuffer.appendChar(kTimeSeparator);
    outBuffer.addString(paddedDecimal(minute(), 2));
    outBuffer.appendChar(kTimeSeparator);
    outBuffer.addString(paddedDecimal(second(), 2));
    outBuffer.appendChar(kSecondMillisecondSeparator);
    outBuffer.addString(paddedDecimal(millisecond(), 3));
    ODL_OBJEXIT(); //####
} // nImO::Time::printToStringBuffer

void
nImO::Time::printToStringBufferAsJSON
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
    outBuffer.addString(paddedDecimal(hour(), 2));
    outBuffer.appendChar(kTimeSeparator);
    outBuffer.addString(paddedDecimal(minute(), 2));
    outBuffer.appendChar(kTimeSeparator);
    outBuffer.addString(paddedDecimal(second(), 2));
    outBuffer.appendChar(kSecondMillisecondSeparator);
    outBuffer.addString(paddedDecimal(millisecond(), 3));
    outBuffer.appendChar(kDoubleQuote);
    ODL_OBJEXIT(); //####
} // nImO::Time::printToStringBufferAsJSON

uint16_t
nImO::Time::second
    (void)
    const
{
    ODL_OBJENTER(); //####
    uint16_t    result{StaticCast(uint16_t, (_dateTimeValue / (nImO::kMaxMilliseconds + 1)) % (nImO::kMaxSeconds + 1))};

    ODL_OBJEXIT_I(result); //####
    return result;
} // nImO::Time::second

void
nImO::Time::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    DataKind        stuff{DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                            DataKind::OtherMiscellaneousTypeBitFieldTypeTime};
    DateTimeBytes   bytes;

    convertToByteArray(bytes, _dateTimeValue);
    outMessage.appendBytes(&stuff, sizeof(stuff));
    outMessage.appendBytes(bytes, sizeof(bytes));
    ODL_OBJEXIT(); //####
} // nImO::Time::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

bool
nImO::GetTimePieces
    (Time::TimePieces &     pieces,
     const std::string &    inString,
     Ptr(size_t)            processedLength)
{
    // y/m/d
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    ODL_P1("processedLength = ", processedLength); //####
    bool            okSoFar{true};
    const int       maxs[] = { kMaxHours, kMaxMinutes, kMaxSeconds, kMaxMilliseconds };
    const int       mins[] = { 0, 0, 0, 0 };
    const size_t    numE{numElementsInArray(pieces)};
    CPtr(char)      beginPtr{inString.c_str()};
    Ptr(char)       endPtr{nullptr};
    CPtr(char)      walker{beginPtr};

    for (size_t ii = 0; ii < numE; ++ii)
    {
        pieces[ii] = mins[ii];
    }
    for (size_t ii = 0; okSoFar && (ii < numE); ++ii)
    {
        int64_t value{strtoll(walker, &endPtr, 10)};

        if (walker == endPtr)
        {
            okSoFar = false;
            ODL_B1("okSoFar = ", okSoFar); //####
        }
        else
        {
            if ((maxs[ii] < value) || (mins[ii] > value))
            {
                okSoFar = false;
                ODL_B1("okSoFar = ", okSoFar); //####
            }
            else
            {
                char    aChar{*endPtr};

                ODL_C1("aChar = ", aChar); //####
                if ((kEndOfString == aChar) || Value::isLegalTerminator(aChar))
                {
                    pieces[ii] = StaticCast(uint16_t, value);
                    ODL_I1("pieces[ii] = ", pieces[ii]); //####
                    break;

                }
                if ((kSecondMillisecondSeparator == aChar) && (ii == (numE - 2)))
                {
                    pieces[ii] = StaticCast(uint16_t, value);
                    ODL_I1("pieces[ii] = ", pieces[ii]); //####
                    walker = endPtr + 1;
                }
                else
                {
                    if ((kTimeSeparator == aChar) && (ii < (numE - 1)))
                    {
                        pieces[ii] = StaticCast(uint16_t, value);
                        ODL_I1("pieces[ii] = ", pieces[ii]); //####
                        walker = endPtr + 1;
                    }
                    else
                    {
                        okSoFar = false;
                        ODL_B1("okSoFar = ", okSoFar); //####
                    }
                }
            }
        }
    }
    if (okSoFar && (nullptr != processedLength))
    {
        *processedLength = endPtr - beginPtr;
        ODL_I1("*processedLength = ", *processedLength); //####
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetTimePieces

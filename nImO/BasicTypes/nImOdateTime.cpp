//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOdateTime.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO Date and Time values.
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
//  Created:    2024-05-14
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOdateTime.h>

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
 @brief The class definition for %nImO Date and Time values. */
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
convertToByteArray
    (nImO::DateTime::DateTimeBytes &    outValue,
     const uint32_t                     inValue)
{
    outValue[0] = StaticCast(uint8_t, (inValue >> 24) & 0x0FF);
    outValue[1] = StaticCast(uint8_t, (inValue >> 16) & 0x0FF);
    outValue[2] = StaticCast(uint8_t, (inValue >> 8) & 0x0FF);
    outValue[3] = StaticCast(uint8_t, inValue & 0x0FF);
} // convertToByteArray

/*! @brief Convert a 32-bit unsigned value into a sequence of bytes in network order.
 @param[out] outValue The byte sequence.
 @param[in] inValue The input value. */
static void
convertToIntArray
    (nImO::DateTime::DateTimeInts & outValue,
     const uint32_t                 inValue,
     const bool                     isDate)
{
    if (isDate)
    {
        outValue[2] = StaticCast(uint16_t, inValue % 31) + 1;
        outValue[1] = StaticCast(uint16_t, (inValue / 31) % 12) + 1;
        outValue[0] = StaticCast(uint16_t, (inValue / (31 * 12)) % 10000) + 1;
    }
    else
    {
        outValue[3] = StaticCast(uint16_t, inValue % 1000);
        outValue[2] = StaticCast(uint16_t, (inValue / 1000) % 60);
        outValue[1] = StaticCast(uint16_t, (inValue / (1000 * 160)) % 60);
        outValue[0] = StaticCast(uint16_t, (inValue / (1000 * 60 * 60)) % 24);
    }
} // convertToIntArray

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

nImO::DateTime::DateTime
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (const uint32_t initialValue,
     const bool     isDate) :
        inherited{}, _dateTimeValue{initialValue}, _isDate{isDate}
{
    ODL_ENTER(); //####
    ODL_X1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (const DateTimeBytes &  initialValue,
     const bool             isDate) :
        inherited{}, _isDate(isDate)
{
    ODL_ENTER(); //####
    ODL_P1("initialValue = ", &initialValue); //####
    ODL_B1("isDate = ", isDate); //####
    _dateTimeValue = ((initialValue[0] << 24) | (initialValue[1] << 16) | (initialValue[2] << 8) | initialValue[3]);
    ODL_X1("_dateTimeValue = ", _dateTimeValue); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (const DateTime &    other) :
        inherited{}, _dateTimeValue{other._dateTimeValue}, _isDate{other._isDate}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (DateTime && other)
    noexcept :
        inherited{std::move(other)}, _dateTimeValue{other._dateTimeValue}, _isDate{other._isDate}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._dateTimeValue = 0;
    other._isDate = false;
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::DateTime)
nImO::DateTime::asDate
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return (_isDate ? this : nullptr);
} // nImO::DateTime::asDate

CPtr(nImO::DateTime)
nImO::DateTime::asTime
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return (_isDate ? nullptr : this);
} // nImO::DateTime::asTime

bool
nImO::DateTime::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        if (_isDate)
        {
            CPtr(DateTime)   otherPtr{other.asDate()};

            if (nullptr != otherPtr)
            {
                result = (_dateTimeValue == otherPtr->_dateTimeValue);
            }
        }
        else
        {
            CPtr(DateTime)   otherPtr{other.asTime()};

            if (nullptr != otherPtr)
            {
                result = (_dateTimeValue == otherPtr->_dateTimeValue);
            }
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::DateTime::deeplyEqualTo

std::ostream &
nImO::DateTime::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("output = ", &output); //####
    output << (_isDate ? "date" : "time");
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::DateTime::describe

nImO::Enumerable
nImO::DateTime::enumerationType
    (void)
    const
{
    ODL_OBJENTER(); //####
    Enumerable  result{_isDate ? Enumerable::Date : Enumerable::Time};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::DateTime::enumerationType

nImO::ComparisonStatus
nImO::DateTime::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(DateTime)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
        {
            otherPtr = other.asTime();
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
        else
        {
            result = (_dateTimeValue == otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::DateTime::equalTo

nImO::SpValue
nImO::DateTime::extractValue
    (const Message &    theMessage,
     const int          leadByte,
     size_t &           position,
     SpArray            parentValue)
{
    NIMO_UNUSED_VAR_(leadByte);
    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "parentValue = ", parentValue.get()); //####
    ODL_X1("leadByte = ", leadByte); //####
    SpValue     result;
    uint32_t    accumulator{0};
    bool        atEnd{false};
    bool        isDate{DataKind::OtherMiscellaneousDateTimeDateValue == (DataKind::OtherMiscellaneousDateTimeValueMask & leadByte)};

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
        result = std::make_shared<DateTime>(accumulator, isDate);
    }
    if (parentValue && result)
    {
        ODL_LOG("(parentValue && result)"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::DateTime::extractValue

nImO::Value::Extractor
nImO::DateTime::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2("aByte = ", &aByte, "aMask = ", &aMask); //####
    aByte = (DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeDateTime);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherMiscellaneousTypeMask);
    ODL_EXIT(); //####
    return extractValue;
} // nImO::DateTime::getExtractionInfo

CPtr(char)
nImO::DateTime::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static CPtr(char)   initialChars{"$"};

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::DateTime::getInitialCharacters

nImO::DataKind
nImO::DateTime::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedOtherValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::DateTime::getTypeTag

nImO::ComparisonStatus
nImO::DateTime::greaterThan
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
        CPtr(DateTime)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
        {
            otherPtr = other.asTime();
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
        else
        {
            result = (_dateTimeValue > otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::DateTime::greaterThan

nImO::ComparisonStatus
nImO::DateTime::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(DateTime)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
        {
            otherPtr = other.asTime();
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
        else
        {
            result = (_dateTimeValue >= otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::DateTime::greaterThanOrEqual

nImO::ComparisonStatus
nImO::DateTime::lessThan
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
        CPtr(DateTime)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
        {
            otherPtr = other.asTime();
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
        else
        {
            result = (_dateTimeValue < otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::DateTime::lessThan

nImO::ComparisonStatus
nImO::DateTime::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(DateTime)   otherPtr{other.asDate()};

        if (nullptr == otherPtr)
        {
            otherPtr = other.asTime();
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
        else
        {
            result = (_dateTimeValue <= otherPtr->_dateTimeValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::DateTime::lessThanOrEqual

nImO::DateTime &
nImO::DateTime::operator=
    (DateTime && other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _dateTimeValue = other._dateTimeValue;
        _isDate = other._isDate;
        other._dateTimeValue = 0;
        other._isDate = false;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::DateTime::operator=

std::ostream &
nImO::DateTime::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    DateTimeInts    ints;

    convertToIntArray(ints, _dateTimeValue, _isDate);
    out << kStartDateTimeChar;
    if (_isDate)
    {
        out << kSecondCharForDate << paddedDecimal(ints[0], 4) << kDateSeparator << paddedDecimal(ints[1], 2) << kDateSeparator <<
                paddedDecimal(ints[2], 2);
    }
    else
    {
        out << kSecondCharForTime << paddedDecimal(ints[0], 2) << kTimeSeparator << paddedDecimal(ints[1], 2) << kTimeSeparator <<
                paddedDecimal(ints[2], 2) << kSecondMillisecondSeparator << paddedDecimal(ints[3], 3);
    }
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::DateTime::operator<<

void
nImO::DateTime::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    DateTimeInts    ints;

    convertToIntArray(ints, _dateTimeValue, _isDate);
    outBuffer.appendChar(kStartDateTimeChar);
    if (_isDate)
    {
        outBuffer.appendChar(kSecondCharForDate);
        outBuffer.addString(paddedDecimal(ints[0], 4));
        outBuffer.appendChar(kDateSeparator);
        outBuffer.addString(paddedDecimal(ints[1], 2));
        outBuffer.appendChar(kDateSeparator);
        outBuffer.addString(paddedDecimal(ints[2], 2));
    }
    else
    {
        outBuffer.appendChar(kSecondCharForTime);
        outBuffer.addString(paddedDecimal(ints[0], 2));
        outBuffer.appendChar(kTimeSeparator);
        outBuffer.addString(paddedDecimal(ints[1], 2));
        outBuffer.appendChar(kTimeSeparator);
        outBuffer.addString(paddedDecimal(ints[2], 2));
        outBuffer.appendChar(kSecondMillisecondSeparator);
        outBuffer.addString(paddedDecimal(ints[3], 3));
    }
    ODL_OBJEXIT(); //####
} // nImO::DateTime::printToStringBuffer

void
nImO::DateTime::printToStringBufferAsJSON
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

    convertToIntArray(ints, _dateTimeValue, _isDate);
    outBuffer.appendChar(kDoubleQuote);
    if (_isDate)
    {
        outBuffer.addString(paddedDecimal(ints[0], 4));
        outBuffer.appendChar(kDateSeparator);
        outBuffer.addString(paddedDecimal(ints[1], 2));
        outBuffer.appendChar(kDateSeparator);
        outBuffer.addString(paddedDecimal(ints[2], 2));
    }
    else
    {
        outBuffer.addString(paddedDecimal(ints[0], 2));
        outBuffer.appendChar(kTimeSeparator);
        outBuffer.addString(paddedDecimal(ints[1], 2));
        outBuffer.appendChar(kTimeSeparator);
        outBuffer.addString(paddedDecimal(ints[2], 2));
        outBuffer.appendChar(kSecondMillisecondSeparator);
        outBuffer.addString(paddedDecimal(ints[3], 3));
    }
    outBuffer.appendChar(kDoubleQuote);
    ODL_OBJEXIT(); //####
} // nImO::DateTime::printToStringBufferAsJSON

nImO::SpValue
nImO::DateTime::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    SpValue result;
//    size_t  localIndex{position};
//    bool    atEnd;
//    int     aChar{inBuffer.getChar(localIndex++, atEnd)};
//
//    if ((! atEnd) && (kStartAddressChar == aChar))
//    {
//        uint64_t    collector{0};
//        bool        okSoFar{true};
//        bool        digitSeen{false};
//        IPv4Address totalValue{0};
//
//        for (int ii = 0; ii <= 2; ++ii)
//        {
//            for ( ; okSoFar; )
//            {
//                aChar = inBuffer.getChar(localIndex, atEnd);
//                ODL_C1("aChar = ", aChar); //####
//                if (atEnd)
//                {
//                    ODL_LOG("(atEnd)"); //####
//                    okSoFar = false;
//                }
//                else
//                {
//                    if (isdigit(aChar))
//                    {
//                        digitSeen = true;
//                        if (0 < collector)
//                        {
//                            collector = (collector * 10) + (aChar - '0');
//                        }
//                        else
//                        {
//                            collector = (aChar - '0');
//                        }
//                        ODL_X1("collector = ", collector); //####
//                        ++localIndex;
//                        ODL_I1("localIndex = ", localIndex); //####
//                    }
//                    else
//                    {
//                        if (kAddressSeparator == aChar)
//                        {
//                            if ((! digitSeen) || (255 < collector))
//                            {
//                                okSoFar = false;
//                            }
//                            else
//                            {
//                                ++localIndex;
//                                ODL_I1("localIndex = ", localIndex); //####
//                                break;
//                            }
//                        }
//                        else
//                        {
//                            okSoFar = false;
//                        }
//                    }
//                }
//            }
//            if (okSoFar)
//            {
//                totalValue = (totalValue << 8) + StaticCast(IPv4Address, collector);
//                ODL_I1("totalValue = ", totalValue); //####
//                digitSeen = false;
//                collector = 0;
//                ODL_X1("collector = ", collector); //####
//            }
//            else
//            {
//                break;
//            }
//        }
//        for ( ; okSoFar; )
//        {
//            aChar = inBuffer.getChar(localIndex, atEnd);
//            ODL_C1("aChar = ", aChar); //####
//            if (atEnd || isLegalTerminator(aChar))
//            {
//                if (digitSeen && (255 >= collector))
//                {
//                    // unexpected character seen, but valid so far
//                    break;
//                }
//                else
//                {
//                    okSoFar = false;
//                }
//            }
//            else
//            {
//                if (isdigit(aChar))
//                {
//                    digitSeen = true;
//                    if (0 < collector)
//                    {
//                        collector = (collector * 10) + (aChar - '0');
//                    }
//                    else
//                    {
//                        collector = (aChar - '0');
//                    }
//                    ODL_X1("collector = ", collector); //####
//                    ++localIndex;
//                    ODL_I1("localIndex = ", localIndex); //####
//                }
//                else
//                {
//                    okSoFar = false;
//                }
//            }
//        }
//        if (okSoFar)
//        {
//            totalValue = (totalValue << 8) + StaticCast(IPv4Address, collector);
//            ODL_X1("totalValue = ", totalValue); //####
//            result = std::make_shared<DateTime>(totalValue);
//        }
//    }
//    else
//    {
//        ODL_LOG("! ((! atEnd) && (kStartAddressChar == aChar))"); //####
//    }
//    if (result)
//    {
//        position = localIndex;
//    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Logical::readFromStringBuffer

void
nImO::DateTime::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    DataKind        stuff{DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeDateTime |
                        (_isDate ? DataKind::OtherMiscellaneousDateTimeDateValue : DataKind::OtherMiscellaneousDateTimeTimeValue)};
    DateTimeBytes   bytes;

    convertToByteArray(bytes, _dateTimeValue);
    outMessage.appendBytes(&stuff, sizeof(stuff));
    outMessage.appendBytes(bytes, sizeof(bytes));
    ODL_OBJEXIT(); //####
} // nImO::DateTime::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOaddress.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO IPv4 address values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
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
//  Created:    2023-09-18
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOaddress.h>

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
 @brief The class definition for %nImO IPv4 address values. */
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
    (nImO::Address::IPv4Bytes & outValue,
     const nImO::IPv4Address    inValue)
{
    outValue[0] = StaticCast(uint8_t, (inValue >> 24) & 0x0FF);
    outValue[1] = StaticCast(uint8_t, (inValue >> 16) & 0x0FF);
    outValue[2] = StaticCast(uint8_t, (inValue >> 8) & 0x0FF);
    outValue[3] = StaticCast(uint8_t, inValue & 0x0FF);
} // convertToByteArray

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Address::Address
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Address::Address

nImO::Address::Address
    (const IPv4Address  initialValue) :
        inherited{}, _addressValue{initialValue}
{
    ODL_ENTER(); //####
    ODL_X1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Address::Address

nImO::Address::Address
    (const IPv4Bytes &  initialValue) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_P1("initialValue = ", &initialValue); //####
    _addressValue = ((initialValue[0] << 24) | (initialValue[1] << 16) | (initialValue[2] << 8) | initialValue[3]);
    ODL_X1("_addressValue = ", _addressValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Address::Address

nImO::Address::Address
    (const Address &    other) :
        inherited{}, _addressValue{other._addressValue}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Address::Address

nImO::Address::Address
    (Address && other)
    noexcept :
        inherited{std::move(other)}, _addressValue{other._addressValue}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._addressValue = 0;
    ODL_EXIT_P(this); //####
} // nImO::Address::Address

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::Address)
nImO::Address::asAddress
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Address::asAddress

bool
nImO::Address::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(Address)   otherPtr{other.asAddress()};

        if (nullptr != otherPtr)
        {
            result = (_addressValue == otherPtr->_addressValue);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Address::deeplyEqualTo

std::ostream &
nImO::Address::describe
    (std::ostream & output)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("output = ", &output); //####
    output << "address";
    ODL_OBJEXIT_P(&output); //####
    return output;
} // nImO::Address::describe

nImO::Enumerable
nImO::Address::enumerationType
    (void)
    const
{
    ODL_OBJENTER(); //####
    Enumerable  result{Enumerable::Address};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Address::enumerationType

nImO::ComparisonStatus
nImO::Address::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Address)   otherPtr{other.asAddress()};

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
            result = (_addressValue == otherPtr->_addressValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Address::equalTo

nImO::SpValue
nImO::Address::extractValue
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
    IPv4Address accumulator{0};
    bool        atEnd{false};

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
        result = std::make_shared<Address>(accumulator);
    }
    if (parentValue && result)
    {
        ODL_LOG("(parentValue && result)"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Address::extractValue

nImO::Value::Extractor
nImO::Address::getExtractionInfo
    (DataKind & aByte,
     DataKind & aMask)
{
    ODL_ENTER(); //####
    ODL_P2("aByte = ", &aByte, "aMask = ", &aMask); //####
    aByte = (DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
             DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address);
    aMask = (DataKind::Mask | DataKind::OtherTypeMask | DataKind::OtherMiscellaneousTypeMask |
             DataKind::OtherMiscellaneousTypeBitFieldTypeMask);
    ODL_EXIT(); //####
    return extractValue;
} // nImO::Address::getExtractionInfo

CPtr(char)
nImO::Address::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static CPtr(char)   initialChars{"@"};

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Address::getInitialCharacters

nImO::DataKind
nImO::Address::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedOtherValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Address::getTypeTag

nImO::ComparisonStatus
nImO::Address::greaterThan
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
        CPtr(Address)   otherPtr{other.asAddress()};

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
            result = (_addressValue > otherPtr->_addressValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Address::greaterThan

nImO::ComparisonStatus
nImO::Address::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Address)   otherPtr{other.asAddress()};

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
            result = (_addressValue >= otherPtr->_addressValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Address::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Address::lessThan
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
        CPtr(Address)   otherPtr{other.asAddress()};

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
            result = (_addressValue < otherPtr->_addressValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Address::lessThan

nImO::ComparisonStatus
nImO::Address::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result{};

    if (&other != this)
    {
        CPtr(Address)   otherPtr{other.asAddress()};

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
            result = (_addressValue <= otherPtr->_addressValue);
        }
    }
    ODL_EXIT_B(result.value()); //####
    return result;
} // nImO::Address::lessThanOrEqual

nImO::Address &
nImO::Address::operator=
    (Address && other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _addressValue = other._addressValue;
        other._addressValue = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Address::operator=

std::ostream &
nImO::Address::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    IPv4Bytes   bytes;

    convertToByteArray(bytes, _addressValue);
    out << kStartAddressChar << std::to_string(bytes[0]) << kAddressSeparator << std::to_string(bytes[1]) << kAddressSeparator <<
            std::to_string(bytes[2]) << kAddressSeparator << std::to_string(bytes[3]);
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Address::operator<<

void
nImO::Address::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    IPv4Bytes   bytes;

    convertToByteArray(bytes, _addressValue);
    outBuffer.appendChar(kStartAddressChar);
    for (int ii = 0; ii <= 3; ++ii)
    {
        if (0 != ii)
        {
            outBuffer.appendChar(kAddressSeparator);
        }
        outBuffer.addString(std::to_string(bytes[ii]));
    }
    ODL_OBJEXIT(); //####
} // nImO::Address::printToStringBuffer

void
nImO::Address::printToStringBufferAsJSON
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
    IPv4Bytes   bytes;

    convertToByteArray(bytes, _addressValue);
    outBuffer.appendChar(kDoubleQuote);
    for (int ii = 0; ii <= 3; ++ii)
    {
        if (0 != ii)
        {
            outBuffer.appendChar(kAddressSeparator);
        }
        outBuffer.addString(std::to_string(bytes[ii]));
    }
    outBuffer.appendChar(kDoubleQuote);
    ODL_OBJEXIT(); //####
} // nImO::Address::printToStringBufferAsJSON

nImO::SpValue
nImO::Address::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    SpValue result;
    size_t  localIndex{position};
    bool    atEnd;
    int     aChar{inBuffer.getChar(localIndex++, atEnd)};

    if ((! atEnd) && (kStartAddressChar == aChar))
    {
        uint64_t    collector{0};
        bool        okSoFar{true};
        bool        digitSeen{false};
        IPv4Address totalValue{0};

        for (int ii = 0; ii <= 2; ++ii)
        {
            for ( ; okSoFar; )
            {
                aChar = inBuffer.getChar(localIndex, atEnd);
                ODL_C1("aChar <- ", aChar); //####
                if (atEnd)
                {
                    ODL_LOG("(atEnd)"); //####
                    okSoFar = false;
                    ODL_B1("okSoFar <- ", okSoFar); //####
                }
                else
                {
                    if (isdigit(aChar))
                    {
                        digitSeen = true;
                        ODL_B1("digitSeen <- ", digitSeen); //####
                        if (0 < collector)
                        {
                            collector = (collector * 10) + (aChar - '0');
                        }
                        else
                        {
                            collector = (aChar - '0');
                        }
                        ODL_X1("collector <- ", collector); //####
                        ++localIndex;
                        ODL_I1("localIndex <- ", localIndex); //####
                    }
                    else
                    {
                        if (kAddressSeparator == aChar)
                        {
                            if ((! digitSeen) || (255 < collector))
                            {
                                okSoFar = false;
                                ODL_B1("okSoFar <- ", okSoFar); //####
                            }
                            else
                            {
                                ++localIndex;
                                ODL_I1("localIndex <- ", localIndex); //####
                                break;
                            }
                        }
                        else
                        {
                            okSoFar = false;
                            ODL_B1("okSoFar <- ", okSoFar); //####
                        }
                    }
                }
            }
            if (okSoFar)
            {
                totalValue = (totalValue << 8) + StaticCast(IPv4Address, collector);
                ODL_I1("totalValue <- ", totalValue); //####
                digitSeen = false;
                ODL_B1("digitSeen <- ", digitSeen); //####
                collector = 0;
                ODL_X1("collector <- ", collector); //####
            }
            else
            {
                break;
            }
        }
        for ( ; okSoFar; )
        {
            aChar = inBuffer.getChar(localIndex, atEnd);
            ODL_C1("aChar = ", aChar); //####
            if (atEnd || isLegalTerminator(aChar))
            {
                if (digitSeen && (255 >= collector))
                {
                    // unexpected character seen, but valid so far
                    break;
                }
                else
                {
                    okSoFar = false;
                    ODL_B1("okSoFar <- ", okSoFar); //####
                }
            }
            else
            {
                if (isdigit(aChar))
                {
                    digitSeen = true;
                    ODL_B1("digitSeen <- ", digitSeen); //####
                    if (0 < collector)
                    {
                        collector = (collector * 10) + (aChar - '0');
                    }
                    else
                    {
                        collector = (aChar - '0');
                    }
                    ODL_X1("collector <- ", collector); //####
                    ++localIndex;
                    ODL_I1("localIndex <- ", localIndex); //####
                }
                else
                {
                    okSoFar = false;
                    ODL_B1("okSoFar <- ", okSoFar); //####
                }
            }
        }
        if (okSoFar)
        {
            totalValue = (totalValue << 8) + StaticCast(IPv4Address, collector);
            ODL_X1("totalValue <- ", totalValue); //####
            result = std::make_shared<Address>(totalValue);
        }
    }
    else
    {
        ODL_LOG("! ((! atEnd) && (kStartAddressChar == aChar))"); //####
    }
    if (result)
    {
        position = localIndex;
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Address::readFromStringBuffer

void
nImO::Address::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    DataKind    stuff{DataKind::Other | DataKind::OtherMiscellaneous | DataKind::OtherMiscellaneousTypeBitField |
                        DataKind::OtherMiscellaneousTypeBitFieldTypeIPv4Address};
    IPv4Bytes   bytes;

    convertToByteArray(bytes, _addressValue);
    outMessage.appendBytes(&stuff, sizeof(stuff));
    outMessage.appendBytes(bytes, sizeof(bytes));
    ODL_OBJEXIT(); //####
} // nImO::Address::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOstring.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO string values.
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

#include <BasicTypes/nImOstring.h>

#include <ContainerTypes/nImOarray.h>
#include <ContainerTypes/nImOmessage.h>
#include <ContainerTypes/nImOstringBuffer.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO string values. */
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

nImO::String::String
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String
    (const std::string &    initialValue) :
        inherited{}, _value{initialValue}
{
    ODL_ENTER(); //####
    ODL_S1s("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String
    (CPtr(char) initialValue) :
        inherited{}, _value{initialValue}
{
    ODL_ENTER(); //####
    ODL_S1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String
    (const String & other) :
        inherited{}, _value{other._value}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String
    (String &&  other)
    noexcept :
        inherited{std::move(other)}, _value{std::move(other._value)}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::~String
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::String::~String

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::String)
nImO::String::asString
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::String::asString

bool
nImO::String::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(String)    otherPtr{other.asString()};

        if (nullptr != otherPtr)
        {
            result = (_value == otherPtr->_value);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::deeplyEqualTo

nImO::Enumerable
nImO::String::enumerationType
    (void)
    const
{
    ODL_OBJENTER(); //####
    Enumerable  result{Enumerable::String};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::String::enumerationType

nImO::ComparisonStatus
nImO::String::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        CPtr(String)    otherPtr{other.asString()};

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
            result = (_value == otherPtr->_value);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::String::equalTo

nImO::SpValue
nImO::String::extractValue
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
    bool    isShort{DataKind::StringOrBlobShortLengthValue == (DataKind::StringOrBlobLengthMask & leadByte)};
    size_t  numBytes{0};

    ++position; // We will always accept the lead byte
    ODL_I1("position <- ", position); //####
    if (isShort)
    {
        ODL_LOG("(isShort)"); //####
        numBytes = toUType(DataKind::StringOrBlobShortLengthMask & leadByte);
        ODL_I1("numBytes <- ", numBytes); //####
    }
    else
    {
        size_t          size{StaticCast(size_t, toUType(DataKind::IntegerLongValueCountMask & leadByte) + 1)};
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
            numBytes = B2I(holder, size);
            ODL_I1("numBytes <- ", numBytes); //####
        }
    }
    if (0 < numBytes)
    {
        std::unique_ptr<char[]> holder{new char[numBytes + 1]};
        bool                    okSoFar{nullptr != holder};

        for (size_t ii = 0; okSoFar && (numBytes > ii); ++ii)
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
                holder[ii] = StaticCast(char, aByte);
                ++position;
                ODL_I1("position <- ", position); //####
            }
        }
        if (okSoFar)
        {
            holder[numBytes] = kEndOfString;
            result.reset(new String(holder.get()));
            ODL_I1("numBytes <- ", numBytes); //####
        }
    }
    else
    {
        result.reset(new String);
    }
    if ((nullptr != parentValue) && (nullptr != result) && (! result->asFlaw()))
    {
        ODL_LOG("((nullptr != parentValue) && (nullptr != result))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::String::extractValue

void
nImO::String::getExtractionInfo
    (DataKind &                 aByte,
     DataKind &                 aMask,
     nImO::Value::Extractor &   theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (DataKind::StringOrBlob | DataKind::StringOrBlobStringValue);
    aMask = (DataKind::Mask | DataKind::StringOrBlobTypeMask);
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::String::getExtractionInfo

CPtr(char)
nImO::String::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static CPtr(char)   initialChars{"\"'"};

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::String::getInitialCharacters

nImO::DataKind
nImO::String::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedStringOrBlobValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::String::getTypeTag

nImO::ComparisonStatus
nImO::String::greaterThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other == this)
    {
        result = false;
    }
    else
    {
        CPtr(String)    otherPtr{other.asString()};

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
            result = (_value > otherPtr->_value);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::String::greaterThan

nImO::ComparisonStatus
nImO::String::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        CPtr(String)    otherPtr{other.asString()};

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
            result = (_value >= otherPtr->_value);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::String::greaterThanOrEqual

nImO::ComparisonStatus
nImO::String::lessThan
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other == this)
    {
        result = false;
    }
    else
    {
        CPtr(String)    otherPtr{other.asString()};

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
            result = (_value < otherPtr->_value);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::String::lessThan

nImO::ComparisonStatus
nImO::String::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        CPtr(String)    otherPtr{other.asString()};

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
            result = (_value <= otherPtr->_value);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::String::lessThanOrEqual

nImO::String &
nImO::String::operator=
    (String &&  other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _value = std::move(other._value);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::String::operator=

std::ostream &
nImO::String::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << "\"" << _value << "\"";
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::String::operator<<

void
nImO::String::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addString(_value, true);
    ODL_OBJEXIT(); //####
} // nImO::String::printToStringBuffer

void
nImO::String::printToStringBufferAsJSON
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addString(_value, true);
    ODL_OBJEXIT(); //####
} // nImO::String::printToStringBufferAsJSON

nImO::SpValue
nImO::String::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    SpValue result;
    size_t  localIndex{position};
    bool    atEnd;
    int     aChar{inBuffer.getChar(localIndex++, atEnd)};

    if ((! atEnd) && ((kSingleQuote == aChar) || (kDoubleQuote == aChar)))
    {
        enum class ScanState
        {
            Normal,
            SawEscape,
            SawEscapeOctal1,
            SawEscapeOctal2,
            SawEscapeSmallC,
            SawEscapeBigC,
            SawEscapeBigCminus,
            SawEscapeBigM,
            SawEscapeBigMminus,
            SawEscapeBigMminusEscape,
            SawEscapeBigMminusEscapeBigC,
            SawEscapeBigMminusEscapeBigCminus
        }; // ScanState

        bool                done{false};
        bool                valid{false};
        const char          delimiter{StaticCast(char, aChar)};
        int                 octalSum;
        ScanState           state{ScanState::Normal};
        StringBuffer        holding;
        static CPtr(char)   standardEscapes{"abtnvfrs"};
        static CPtr(char)   standardEscapesActual{"\a\b\t\n\v\f\r "};

        for ( ; ! done; )
        {
            aChar = inBuffer.getChar(localIndex++, atEnd);
            if (atEnd)
            {
                ODL_LOG("(atEnd)"); //####
                done = true; // saw end of buffer before delimiter
            }
            else
            {
                switch (state)
                {
                    case ScanState::Normal :
                        if (delimiter == aChar)
                        {
                            valid = isLegalTerminator(inBuffer.getChar(localIndex, atEnd));
                            if (atEnd)
                            {
                                valid = true;
                            }
                            done = true; // possibly ready to use
                        }
                        else if (kEscapeChar == aChar)
                        {
                            state = ScanState::SawEscape;
                        }
                        else
                        {
                            holding.addChar(aChar);
                        }
                        break;

                    case ScanState::SawEscape :
                        if (delimiter == aChar)
                        {
                            holding.addChar(aChar);
                            state = ScanState::Normal;
                        }
                        else
                        {
                            CPtr(char)  whichEscape{strchr(standardEscapes, aChar)};

                            if (nullptr == whichEscape)
                            {
                                switch (aChar)
                                {
                                    case '0' :
                                    case '1' :
                                    case '2' :
                                    case '3' :
                                    case '4' :
                                    case '5' :
                                    case '6' :
                                    case '7' :
                                        octalSum = aChar - '0';
                                        state = ScanState::SawEscapeOctal1;
                                        break;

                                    case 'c' :
                                        state = ScanState::SawEscapeSmallC;
                                        break;

                                    case 'C' :
                                        state = ScanState::SawEscapeBigC;
                                        break;

                                    case 'M' :
                                        state = ScanState::SawEscapeBigM;
                                        break;

                                    default :
                                        ODL_LOG("default"); //####
                                        done = true; // unrecognized escape sequence
                                        break;

                                }
                            }
                            else
                            {
                                CPtr(char)  replacement{standardEscapesActual + (whichEscape - standardEscapes)};

                                holding.addChar(*replacement);
                                state = ScanState::Normal;
                            }
                        }
                        break;

                    case ScanState::SawEscapeOctal1 :
                        switch (aChar)
                        {
                            case '0' :
                            case '1' :
                            case '2' :
                            case '3' :
                            case '4' :
                            case '5' :
                            case '6' :
                            case '7' :
                                octalSum *= 8;
                                octalSum += aChar - '0';
                                state = ScanState::SawEscapeOctal2;
                                break;

                            default :
                                ODL_LOG("default"); //####
                                done = true; // unrecognized escape sequence
                                break;

                        }
                        break;

                    case ScanState::SawEscapeOctal2 :
                        switch (aChar)
                        {
                            case '0' :
                            case '1' :
                            case '2' :
                            case '3' :
                            case '4' :
                            case '5' :
                            case '6' :
                            case '7' :
                                octalSum *= 8;
                                octalSum += aChar - '0';
                                holding.addChar(StaticCast(char, octalSum));
                                state = ScanState::Normal;
                                break;

                            default :
                                ODL_LOG("default"); //####
                                done = true; // unrecognized escape sequence
                                break;

                        }
                        break;

                    case ScanState::SawEscapeSmallC :
                        aChar = toupper(aChar);
                        if (('@' <= aChar) && ('_' >= aChar))
                        {
                            holding.addChar(aChar - '@');
                            state = ScanState::Normal;
                        }
                        else
                        {
                            ODL_LOG("! (('@' <= aChar) && ('_' >= aChar))"); //####
                            done = true; // unrecognized escape sequence
                        }
                        break;

                    case ScanState::SawEscapeBigC :
                        if ('-' == aChar)
                        {
                            state = ScanState::SawEscapeBigCminus;
                        }
                        else
                        {
                            ODL_LOG("! ('-' == aChar)"); //####
                            done = true; // unrecognized escape sequence
                        }
                        break;

                    case ScanState::SawEscapeBigCminus :
                        aChar = toupper(aChar);
                        if (('@' <= aChar) && ('_' >= aChar))
                        {
                            holding.addChar(aChar - '@');
                            state = ScanState::Normal;
                        }
                        else
                        {
                            ODL_LOG("! (('@' <= aChar) && ('_' >= aChar))"); //####
                            done = true; // unrecognized escape sequence
                        }
                        break;

                    case ScanState::SawEscapeBigM :
                        if ('-' == aChar)
                        {
                            state = ScanState::SawEscapeBigMminus;
                        }
                        else
                        {
                            ODL_LOG("! ('-' == aChar)"); //####
                            done = true; // unrecognized escape sequence
                        }
                        break;

                    case ScanState::SawEscapeBigMminus :
                        if (kEscapeChar == aChar)
                        {
                            state = ScanState::SawEscapeBigMminusEscape;
                        }
                        else
                        {
                            holding.addChar(aChar | 0x080);
                            state = ScanState::Normal;
                        }
                        break;

                    case ScanState::SawEscapeBigMminusEscape :
                        if ('C' == aChar)
                        {
                            state = ScanState::SawEscapeBigMminusEscapeBigC;
                        }
                        else
                        {
                            ODL_LOG("! ('C' == aChar)"); //####
                            done = true; // unrecognized escape sequence
                        }
                        break;

                    case ScanState::SawEscapeBigMminusEscapeBigC :
                        if ('-' == aChar)
                        {
                            state = ScanState::SawEscapeBigMminusEscapeBigCminus;
                        }
                        else
                        {
                            ODL_LOG("! ('-' == aChar)"); //####
                            done = true; // unrecognized escape sequence
                        }
                        break;

                    case ScanState::SawEscapeBigMminusEscapeBigCminus :
                        aChar = toupper(aChar);
                        if (('@' <= aChar) && ('_' >= aChar))
                        {
                            holding.addChar((aChar - '@') | 0x080);
                            state = ScanState::Normal;
                        }
                        else
                        {
                            ODL_LOG("! (('@' <= aChar) && ('_' >= aChar))"); //####
                            done = true; // unrecognized escape sequence
                        }
                        break;

                    default :
                        ODL_LOG("default"); //####
                        done = true; // unrecognized sequence
                        break;

                }
            }
        }
        if (valid)
        {
            result.reset(new String(holding.getString()));
            if (nullptr != result)
            {
                position = localIndex;
            }
        }
        else
        {
            ODL_LOG("! (valid)"); //####
        }
    }
    else
    {
        ODL_LOG("! ((! atEnd) && ((kSingleQuote == aChar) || (kDoubleQuote == aChar)))"); //####
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::String::readFromStringBuffer

void
nImO::String::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_ENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    size_t length{_value.length()};

    if (0 < length)
    {
        ODL_LOG("(0 < length)"); //####
        if (15 < length)
        {
            ODL_LOG("(15 < length)"); //####
            NumberAsBytes   numBuff;
            size_t          numBytes{I2B(length, numBuff)};

            if (0 < numBytes)
            {
                ODL_LOG("(0 < numBytes)"); //####
                DataKind    stuff{DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                                    DataKind::StringOrBlobLongLengthValue |
                                    (DataKind::StringOrBlobLongLengthMask &
                                     StaticCast(DataKind, numBytes - 1))};

                outMessage.appendBytes(&stuff, sizeof(stuff));
                outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
            }
        }
        else
        {
            ODL_LOG("! (15 < length)"); //####
            DataKind    stuff{DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                                DataKind::StringOrBlobShortLengthValue |
                                (DataKind::StringOrBlobShortLengthMask &
                                 StaticCast(DataKind, length))};

            outMessage.appendBytes(&stuff, sizeof(stuff));
        }
        for (size_t ii = 0; length > ii; ++ii)
        {
            uint8_t stuff{StaticCast(uint8_t, _value.at(ii))};

            outMessage.appendBytes(&stuff, sizeof(stuff));
        }
    }
    else
    {
        ODL_LOG("! (0 < length)"); //####
        DataKind    stuff{DataKind::StringOrBlob | DataKind::StringOrBlobStringValue |
                            DataKind::StringOrBlobShortLengthValue |
                            (DataKind::StringOrBlobShortLengthMask & 0)};

        outMessage.appendBytes(&stuff, sizeof(stuff));
    }
    ODL_EXIT(); //####
} // nImO::String::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

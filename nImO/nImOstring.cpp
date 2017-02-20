//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstring.cpp
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

#include "nImOstring.hpp"

#include <nImO/nImOarray.hpp>
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

nImO::String::String(void) :
    inherited(), _value()
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String(const std::string &initialValue) :
    inherited(), _value(initialValue)
{
    ODL_ENTER(); //####
    ODL_S1s("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String(const char *initialValue) :
    inherited(), _value(initialValue)
{
    ODL_ENTER(); //####
    ODL_S1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String(const nImO::String &other) :
    inherited(), _value(other._value)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::~String(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::String::~String

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::String::deeplyEqualTo(const nImO::Value &other)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result = (&other == this);
    
    if (! result)
    {
        const String *otherPtr = other.asString();
        
        if (nullptr != otherPtr)
        {
            result = (_value == otherPtr->_value);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::deeplyEqualTo

bool
nImO::String::equalTo(const nImO::Value &other,
                      bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const String *otherPtr = other.asString();
        
        if (nullptr == otherPtr)
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
            result = (_value == otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::equalTo

nImO::SpValue
nImO::String::extractValue(const nImO::Message &theMessage,
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
    bool    isShort = (kKindStringOrBlobShortLengthValue ==
                       (kKindStringOrBlobLengthMask & leadByte));
    size_t  numBytes = 0;
    
    ++position; // We will always accept the lead byte
    ODL_LL1("position <- ", position); //####
    if (isShort)
    {
        ODL_LOG("(isShort)"); //####
        numBytes = (kKindStringOrBlobShortLengthMask & leadByte);
        status = kReadSuccessful;
        ODL_LL2("numBytes <- ", numBytes, "status <- ", status); //####
    }
    else
    {
        size_t        size = (kKindIntegerLongValueCountMask & leadByte) + 1;
        NumberAsBytes holder;
        bool          okSoFar = true;
        
        for (size_t ii = 0; okSoFar && (size > ii); ++ii)
        {
            int aByte = theMessage.getByte(position);
            
            if (Message::kEndToken == aByte)
            {
                ODL_LOG("(Message::kEndToken == aByte)"); //####
                status = kReadIncomplete;
                ODL_LL1("status <- ", status); //####
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
            numBytes = B2I(holder, size);
            status = kReadSuccessful;
            ODL_LL2("numBytes <- ", numBytes, "status <- ", status); //####
        }
    }
    if (0 < numBytes)
    {
        std::unique_ptr<char[]> holder(new char[numBytes + 1]);
        bool                    okSoFar = (nullptr != holder);
        
        for (size_t ii = 0; okSoFar && (numBytes > ii); ++ii)
        {
            int aByte = theMessage.getByte(position);
            
            if (Message::kEndToken == aByte)
            {
                ODL_LOG("(Message::kEndToken == aByte)"); //####
                status = kReadIncomplete;
                ODL_LL1("status <- ", status); //####
                okSoFar = false;
            }
            else
            {
                holder[ii] = static_cast<char>(aByte);
                ++position;
                ODL_LL1("position <- ", position); //####
            }
        }
        if (okSoFar)
        {
            holder[numBytes] = '\0';
            result.reset(new String(holder.get()));
            status = kReadSuccessful;
            ODL_LL2("numBytes <- ", numBytes, "status <- ", status); //####
        }
        else
        {
            result.reset();
        }
    }
    else
    {
        result.reset(new String);
    }
    if ((nullptr != parentValue) && (nullptr != result))
    {
        ODL_LOG("((nullptr != parentValue) && (nullptr != result))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::String::extractValue

void
nImO::String::getExtractionInfo(uint8_t                &aByte,
                                uint8_t                &aMask,
                                nImO::Value::Extractor &theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (kKindStringOrBlob | kKindStringOrBlobStringValue);
    aMask = (kKindMask | kKindStringOrBlobTypeMask);
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::String::getExtractionInfo

const char *
nImO::String::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char *initialChars = "\"'";

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::String::getInitialCharacters

bool
nImO::String::greaterThan(const nImO::Value &other,
                          bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const String *otherPtr = other.asString();
        
        if (nullptr == otherPtr)
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
            result = (_value > otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::greaterThan

bool
nImO::String::greaterThanOrEqual(const nImO::Value &other,
                                 bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const String *otherPtr = other.asString();
        
        if (nullptr == otherPtr)
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
            result = (_value >= otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::greaterThanOrEqual

bool
nImO::String::lessThan(const nImO::Value &other,
                       bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const String *otherPtr = other.asString();
        
        if (nullptr == otherPtr)
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
            result = (_value < otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::lessThan

bool
nImO::String::lessThanOrEqual(const nImO::Value &other,
                              bool              &validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else
    {
        const String *otherPtr = other.asString();
        
        if (nullptr == otherPtr)
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
            result = (_value <= otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::lessThanOrEqual

nImO::String &
nImO::String::operator =(const nImO::String &other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _value = other._value;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::String::operator=

nImO::String &
nImO::String::operator =(const std::string &value)
{
    ODL_OBJENTER(); //####
    ODL_S1s("value = ", value); //####
    _value = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::String::operator=

nImO::String &
nImO::String::operator =(const char *value)
{
    ODL_OBJENTER(); //####
    ODL_S1("value = ", value); //####
    _value = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::String::operator=

void
nImO::String::printToStringBuffer(nImO::StringBuffer &outBuffer,
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
    outBuffer.addString(_value, true);
    ODL_OBJEXIT(); //####
} // nImO::String::printToStringBuffer

nImO::SpValue
nImO::String::readFromStringBuffer(const nImO::StringBuffer &inBuffer,
                                   size_t                   &position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    SpValue result;
    size_t  localIndex = position;
    int     aChar = inBuffer.getChar(localIndex++);

    if ((kSingleQuote == aChar) || (kDoubleQuote == aChar))
    {
        enum ScanState
        {
            kScanNormal,
            kScanSawEscape,
            kScanSawEscapeOctal1,
            kScanSawEscapeOctal2,
            kScanSawEscapeSmallC,
            kScanSawEscapeBigC,
            kScanSawEscapeBigCminus,
            kScanSawEscapeBigM,
            kScanSawEscapeBigMminus,
            kScanSawEscapeBigMminusEscape,
            kScanSawEscapeBigMminusEscapeBigC,
            kScanSawEscapeBigMminusEscapeBigCminus
        }; // ScanState

        bool              done = false;
        bool              valid = false;
        const char        delimiter = aChar;
        int               octalSum;
        ScanState         state = kScanNormal;
        StringBuffer      holding;
        static const char *standardEscapes = "abtnvfres";
        static const char *standardEscapesActual = "\a\b\t\n\v\f\r\e ";

        for ( ; ! done; )
        {
            aChar = inBuffer.getChar(localIndex++);
            if (StringBuffer::kEndToken == aChar)
            {
                ODL_LOG("(StringBuffer::kEndToken == aChar)"); //####
                done = true; // saw end of buffer before delimiter
            }
            else
            {
                switch (state)
                {
                case kScanNormal :
                    if (delimiter == aChar)
                    {
                        valid = isLegalTerminator(inBuffer.getChar(localIndex));
                        done = true; // possibly ready to use
                    }
                    else if (kEscapeChar == aChar)
                    {
                        state = kScanSawEscape;
                    }
                    else
                    {
                        holding.addChar(aChar);
                    }
                    break;

                case kScanSawEscape :
                    if (delimiter == aChar)
                    {
                        holding.addChar(aChar);
                        state = kScanNormal;
                    }
                    else
                    {
                        const char *whichEscape = strchr(standardEscapes, aChar);

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
                                state = kScanSawEscapeOctal1;
                                break;

                            case 'c' :
                                state = kScanSawEscapeSmallC;
                                break;

                            case 'C' :
                                state = kScanSawEscapeBigC;
                                break;

                            case 'M' :
                                state = kScanSawEscapeBigM;
                                break;

                            default :
                                ODL_LOG("default"); //####
                                done = true; // unrecognized escape sequence
                                break;

                            }
                        }
                        else
                        {
                            const char *replacement = standardEscapesActual +
                                                      (whichEscape - standardEscapes);

                            holding.addChar(*replacement);
                            state = kScanNormal;
                        }
                    }
                    break;

                case kScanSawEscapeOctal1 :
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
                        state = kScanSawEscapeOctal2;
                        break;

                    default :
                        ODL_LOG("default"); //####
                        done = true; // unrecognized escape sequence
                        break;

                    }
                    break;

                case kScanSawEscapeOctal2 :
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
                        holding.addChar(static_cast<char>(octalSum));
                        state = kScanNormal;
                        break;

                    default :
                        ODL_LOG("default"); //####
                        done = true; // unrecognized escape sequence
                        break;

                    }
                    break;

                case kScanSawEscapeSmallC :
                    aChar = toupper(aChar);
                    if (('@' <= aChar) && ('_' >= aChar))
                    {
                        holding.addChar(aChar - '@');
                        state = kScanNormal;
                    }
                    else
                    {
                        ODL_LOG("! (('@' <= aChar) && ('_' >= aChar))"); //####
                        done = true; // unrecognized escape sequence
                    }
                    break;

                case kScanSawEscapeBigC :
                    if ('-' == aChar)
                    {
                        state = kScanSawEscapeBigCminus;
                    }
                    else
                    {
                        ODL_LOG("! ('-' == aChar)"); //####
                        done = true; // unrecognized escape sequence
                    }
                    break;

                case kScanSawEscapeBigCminus :
                    aChar = toupper(aChar);
                    if (('@' <= aChar) && ('_' >= aChar))
                    {
                        holding.addChar(aChar - '@');
                        state = kScanNormal;
                    }
                    else
                    {
                        ODL_LOG("! (('@' <= aChar) && ('_' >= aChar))"); //####
                        done = true; // unrecognized escape sequence
                    }
                    break;

                case kScanSawEscapeBigM :
                    if ('-' == aChar)
                    {
                        state = kScanSawEscapeBigMminus;
                    }
                    else
                    {
                        ODL_LOG("! ('-' == aChar)"); //####
                        done = true; // unrecognized escape sequence
                    }
                    break;

                case kScanSawEscapeBigMminus :
                    if (kEscapeChar == aChar)
                    {
                        state = kScanSawEscapeBigMminusEscape;
                    }
                    else
                    {
                        holding.addChar(aChar | 0x080);
                        state = kScanNormal;
                    }
                    break;

                case kScanSawEscapeBigMminusEscape :
                    if ('C' == aChar)
                    {
                        state = kScanSawEscapeBigMminusEscapeBigC;
                    }
                    else
                    {
                        ODL_LOG("! ('C' == aChar)"); //####
                        done = true; // unrecognized escape sequence
                    }
                    break;

                case kScanSawEscapeBigMminusEscapeBigC :
                    if ('-' == aChar)
                    {
                        state = kScanSawEscapeBigMminusEscapeBigCminus;
                    }
                    else
                    {
                        ODL_LOG("! ('-' == aChar)"); //####
                        done = true; // unrecognized escape sequence
                    }
                    break;

                case kScanSawEscapeBigMminusEscapeBigCminus :
                    aChar = toupper(aChar);
                    if (('@' <= aChar) && ('_' >= aChar))
                    {
                        holding.addChar((aChar - '@') | 0x080);
                        state = kScanNormal;
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
            size_t length = 0;

            result.reset(new String(holding.getString(length)));
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
        ODL_LOG("! ((kSingleQuote == aChar) || (kDoubleQuote == aChar))"); //####
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::String::readFromStringBuffer

void
nImO::String::writeToMessage(nImO::Message &outMessage)
const
{
    ODL_ENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    size_t length = _value.length();

    if (0 < length)
    {
        ODL_LOG("(0 < length)"); //####
        if (15 < length)
        {
            ODL_LOG("(15 < length)"); //####
            NumberAsBytes numBuff;
            size_t        numBytes = I2B(length, numBuff);

            if (0 < numBytes)
            {
                ODL_LOG("(0 < numBytes)"); //####
                uint8_t stuff = kKindStringOrBlob + kKindStringOrBlobStringValue +
                                kKindStringOrBlobLongLengthValue +
                                (kKindStringOrBlobLongLengthMask &(numBytes - 1));

                outMessage.appendBytes(&stuff, sizeof(stuff));
                outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
            }
        }
        else
        {
            ODL_LOG("! (15 < length)"); //####
            uint8_t stuff = kKindStringOrBlob + kKindStringOrBlobStringValue +
                            kKindStringOrBlobShortLengthValue +
                            (kKindStringOrBlobShortLengthMask &length);

            outMessage.appendBytes(&stuff, sizeof(stuff));
        }
        for (size_t ii = 0; length > ii; ++ii)
        {
            uint8_t stuff = _value.at(ii);

            outMessage.appendBytes(&stuff, sizeof(stuff));
        }
    }
    else
    {
        ODL_LOG("! (0 < length)"); //####
        uint8_t stuff = kKindStringOrBlob + kKindStringOrBlobStringValue +
                        kKindStringOrBlobShortLengthValue +
                        (kKindStringOrBlobShortLengthMask &0);

        outMessage.appendBytes(&stuff, sizeof(stuff));
    }
    ODL_EXIT(); //####
} // nImO::String::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

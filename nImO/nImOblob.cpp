//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOblob.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO 'blob' values.
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
//  Created:    2016-03-22
//
//--------------------------------------------------------------------------------------------------

#include <nImOblob.h>

#include <nImOarray.h>
#include <nImOmessage.h>
#include <nImOstringBuffer.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO 'blob' values. */
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

/*! @brief Compare two byte sequences.
 @param[in] leftValue A pointer to the left sequence.
 @param[in] leftSize The number of bytes in the left sequence.
 @param[in] rightValue A pointer to the right sequence.
 @param[in] rightSize The number of bytes in the right sequence.
 @return @c 1 if the left sequence is lexicographically greater than
 the right sequence, @c 0 if they are the same sequence and @c -1 if
 the left sequence is lexicographically less than the right sequence. */
static int
compareBytes
    (CPtr(uint8_t)  leftValue,
     const size_t   leftSize,
     CPtr(uint8_t)  rightValue,
     const size_t   rightSize)
{
    ODL_ENTER(); //####
    ODL_P2("leftValue = ", leftValue, "rightValue = ", rightValue); //####
    ODL_I2("leftSize = ", leftSize, "rightSize = ", rightSize); //####
    int result;

    if (0 == leftSize)
    {
        if (0 == rightSize)
        {
            result = 0; // Both are empty
        }
        else
        {
            result = -1; // Left is empty, right is not
        }
    }
    else if (0 == rightSize)
    {
        result = 1; // Right is empty, left is not
    }
    else
    {
        size_t firstCount;

        if (leftSize > rightSize)
        {
            firstCount = rightSize;
        }
        else
        {
            firstCount = leftSize;
        }
        result = 0;
        for (size_t ii = 0; (0 == result) && (firstCount > ii); ++ii)
        {
            uint8_t leftByte{leftValue[ii]};
            uint8_t rightByte{rightValue[ii]};

            if (leftByte > rightByte)
            {
                result = 1; // Left sequence is greater
            }
            else if (leftByte < rightByte)
            {
                result = -1; // Right sequence is greater
            }
        }
        if (0 == result)
        {
            // The shorter sequence is a prefix of the longer sequence
            if (leftSize > rightSize)
            {
                result = 1; // Left sequence is longer
            }
            else if (leftSize < rightSize)
            {
                result = -1; // Right sequence is longer
            }
        }
    }
    ODL_EXIT_I(result); //####
    return result;
} // compareBytes

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Blob::Blob
    (void) :
        inherited(), _value(), _size(0)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Blob::Blob
    (CPtr(uint8_t)  data,
     const size_t   size) :
        inherited(), _value(), _size(0)
{
    ODL_ENTER(); //####
    ODL_P1("datat = ", data); //####
    ODL_I1("size = ", size); //####
    if ((nullptr != data) && (0 < size))
    {
        _size = size;
        _value.reset(new uint8_t[_size]);
        memcpy(_value.get(), data, _size);
    }
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Blob::Blob
    (const Blob &   other) :
        inherited(), _value(), _size(0)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    if (0 < other._size)
    {
        _size = other._size;
        _value.reset(new uint8_t[_size]);
        memcpy(_value.get(), other._value.get(), _size);
    }
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Blob::Blob
    (Blob &&    other)
    noexcept :
        inherited(std::move(other)), _value(std::move(other._value)), _size(other._size)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._size = 0;
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Blob::~Blob
    (void)
{
    ODL_OBJENTER(); //####
    removeAllEntries();
    ODL_OBJEXIT(); //####
} // nImO::Blob::~Blob

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::Blob)
nImO::Blob::asBlob
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Blob::asBlob

bool
nImO::Blob::deeplyEqualTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool    result{&other == this};

    if (! result)
    {
        CPtr(Blob)  otherPtr{other.asBlob()};

        if (nullptr != otherPtr)
        {
            result = (0 == compareBytes(_value.get(), _size, otherPtr->_value.get(), otherPtr->_size));
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Blob::deeplyEqualTo

nImO::ComparisonStatus
nImO::Blob::equalTo
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        CPtr(Blob)  otherPtr{other.asBlob()};

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
            result = (0 == compareBytes(_value.get(), _size, otherPtr->_value.get(), otherPtr->_size));
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Blob::equalTo

nImO::SpValue
nImO::Blob::extractValue
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
        UpAuint8_t  holder{new uint8_t[numBytes]};
        bool        okSoFar{nullptr != holder};

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
                holder[ii] = StaticCast(uint8_t, aByte);
                ++position;
                ODL_I1("position <- ", position); //####
            }
        }
        if (okSoFar)
        {
            result.reset(new Blob(holder.get(), numBytes));
            ODL_I1("numBytes <- ", numBytes); //####
        }
    }
    else
    {
        result.reset(new Blob);
    }
    if ((nullptr != parentValue) && (nullptr != result) && (! result->asFlaw()))
    {
        ODL_LOG("((nullptr != parentValue) && (nullptr != result))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Blob::extractValue

void
nImO::Blob::getExtractionInfo
    (DataKind &                 aByte,
     DataKind &                 aMask,
     nImO::Value::Extractor &   theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue);
    aMask = (DataKind::Mask | DataKind::StringOrBlobTypeMask);
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Blob::getExtractionInfo

nImO::DataKind
nImO::Blob::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedStringOrBlobValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Blob::getTypeTag

nImO::ComparisonStatus
nImO::Blob::greaterThan
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
        CPtr(Blob)  otherPtr{other.asBlob()};

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
            result = (0 < compareBytes(_value.get(), _size, otherPtr->_value.get(), otherPtr->_size));
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Blob::greaterThan

nImO::ComparisonStatus
nImO::Blob::greaterThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        CPtr(Blob)  otherPtr{other.asBlob()};

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
            result = (0 <= compareBytes(_value.get(), _size, otherPtr->_value.get(), otherPtr->_size));
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Blob::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Blob::lessThan
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
        CPtr(Blob)  otherPtr{other.asBlob()};

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
            result = (0 > compareBytes(_value.get(), _size, otherPtr->_value.get(), otherPtr->_size));
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Blob::lessThan

nImO::ComparisonStatus
nImO::Blob::lessThanOrEqual
    (const Value &  other)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ComparisonStatus    result;

    if (&other != this)
    {
        CPtr(Blob)  otherPtr{other.asBlob()};

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
            result = (0 >= compareBytes(_value.get(), _size, otherPtr->_value.get(), otherPtr->_size));
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Blob::lessThanOrEqual

nImO::Blob &
nImO::Blob::operator=
    (const Blob &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        removeAllEntries();
        if (0 < other._size)
        {
            _size = other._size;
            _value.reset(new uint8_t[_size]);
            memcpy(_value.get(), other._value.get(), _size);
        }
    }
    ODL_OBJEXIT_P(this);
    return *this;
} // nImO::Blob::operator=

nImO::Blob &
nImO::Blob::operator=
    (Blob &&    other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _value = std::move(other._value);
        _size = other._size;
        other._size = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Blob::operator=

std::ostream &
nImO::Blob::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << "Blob(#bytes=" << _size << ")";
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Blob::operator<<

void
nImO::Blob::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addBytes(_value.get(), _size);
    ODL_OBJEXIT(); //####
} // nImO::Blob::printToStringBuffer

void
nImO::Blob::printToStringBufferAsJSON
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_VAR_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addString("<blob>");
    ODL_OBJEXIT(); //####
} // nImO::Blob::printToStringBufferAsJSON

void
nImO::Blob::writeToMessage
    (Message &  outMessage)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    if (0 < _size)
    {
        ODL_LOG("(0 < _size)"); //####
        if (15 < _size)
        {
            ODL_LOG("(15 < _size)"); //####
            NumberAsBytes   numBuff;
            size_t          numBytes{I2B(_size, numBuff)};

            if (0 < numBytes)
            {
                ODL_LOG("(0 < numBytes)"); //####
                DataKind    stuff{DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                                    DataKind::StringOrBlobLongLengthValue |
                                    (DataKind::StringOrBlobLongLengthMask &
                                     StaticCast(DataKind, numBytes - 1))};

                outMessage.appendBytes(&stuff, sizeof(stuff));
                outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
            }
        }
        else
        {
            ODL_LOG("! (15 < _size)"); //####
            DataKind    stuff{DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                                DataKind::StringOrBlobShortLengthValue |
                                (DataKind::StringOrBlobShortLengthMask &
                                 StaticCast(DataKind, _size))};

            outMessage.appendBytes(&stuff, sizeof(stuff));
        }
        outMessage.appendBytes(_value.get(), _size);
    }
    else
    {
        ODL_LOG("! (0 < _size)"); //####
        DataKind    stuff{DataKind::StringOrBlob | DataKind::StringOrBlobBlobValue |
                            DataKind::StringOrBlobShortLengthValue | (DataKind::StringOrBlobShortLengthMask & 0)};

        outMessage.appendBytes(&stuff, sizeof(stuff));
    }
    ODL_OBJEXIT(); //####
} // nImO::Blob::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

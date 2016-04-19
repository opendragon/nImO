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

#include "nImOblob.hpp"

#include <nImO/nImOstringbuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

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
 @param leftValue A pointer to the left sequence.
 @param leftSize The number of bytes in the left sequence.
 @param rightValue A pointer to the right sequence.
 @param rightSize The number of bytes in the right sequence.
 @returns @c 1 if the left sequence is lexicographically greater than
 the right sequence, @c 0 if they are the same sequence and @c -1 if
 the left sequence is lexicographically less than the right sequence. */
static int
compareBytes(const uint8_t * leftValue,
             const size_t    leftSize,
             const uint8_t * rightValue,
             const size_t    rightSize)
{
    ODL_ENTER(); //####
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
            uint8_t leftByte = leftValue[ii];
            uint8_t rightByte = rightValue[ii];

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
    ODL_EXIT_LL(result); //####
    return result;
} // compareBytes

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Blob::Blob(void) :
    inherited(), _value(NULL), _size(0)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Blob::Blob(const uint8_t * data,
                 const size_t    size) :
    inherited(), _value(NULL), _size(0)
{
    ODL_ENTER(); //####
    ODL_P1("datat = ", data); //####
    ODL_LL1("size = ", size); //####
    if (data && (0 < size))
    {
        _size = size;
        _value = new uint8_t[_size];
        memcpy(_value, data, _size);
    }
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Blob::Blob(const nImO::Blob & other) :
    inherited(), _value(NULL), _size(0)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    if (0 < other._size)
    {
        _size = other._size;
        _value = new uint8_t[_size];
        memcpy(_value, other._value, _size);
    }
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Blob::~Blob(void)
{
    ODL_OBJENTER(); //####
    removeAllEntries();
    ODL_OBJEXIT(); //####
} // nImO::Blob::~Blob

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Blob::addToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addBlob(_value, _size);
    ODL_OBJEXIT(); //####
} // nImO::Blob::addToStringBuffer

nImO::Value *
nImO::Blob::clone(void)
const
{
    ODL_OBJENTER(); //####
    Blob * result = new Blob(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Blob::copy

bool
nImO::Blob::equalTo(const Value & other,
                    bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBlob())
    {
        const Blob & otherRef = static_cast<const Blob &>(other);

        result = (0 == compareBytes(_value, _size, otherRef._value, otherRef._size));
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.equalTo(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Blob::equalTo

bool
nImO::Blob::greaterThan(const Value & other,
                        bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBlob())
    {
        const Blob & otherRef = static_cast<const Blob &>(other);

        result = (0 < compareBytes(_value, _size, otherRef._value, otherRef._size));
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.lessThan(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Blob::greaterThan

bool
nImO::Blob::greaterThanOrEqual(const Value & other,
                               bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBlob())
    {
        const Blob & otherRef = static_cast<const Blob &>(other);

        result = (0 <= compareBytes(_value, _size, otherRef._value, otherRef._size));
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.lessThanOrEqual(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Blob::greaterThanOrEqual

bool
nImO::Blob::lessThan(const Value & other,
                     bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBlob())
    {
        const Blob & otherRef = static_cast<const Blob &>(other);

        result = (0 > compareBytes(_value, _size, otherRef._value, otherRef._size));
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.greaterThan(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Blob::lessThan

bool
nImO::Blob::lessThanOrEqual(const Value & other,
                            bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBlob())
    {
        const Blob & otherRef = static_cast<const Blob &>(other);

        result = (0 >= compareBytes(_value, _size, otherRef._value, otherRef._size));
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.greaterThanOrEqual(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Blob::lessThanOrEqual

nImO::Blob &
nImO::Blob::operator =(const nImO::Blob & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        removeAllEntries();
        if (0 < other._size)
        {
            _size = other._size;
            _value = new uint8_t[_size];
            memcpy(_value, other._value, _size);
        }
    }
    ODL_OBJEXIT_P(this);
    return *this;
} // nImO::Blob::operator=

void
nImO::Blob::removeAllEntries(void)
{
    ODL_OBJENTER(); //####
    delete[] _value;
    _size = 0;
    _value = NULL;
    ODL_OBJEXIT(); //####
} // nImO::Blob::removeAllEntries

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

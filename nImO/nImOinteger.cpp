//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOinteger.cpp
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

#include "nImOinteger.hpp"

#include <nImO/nImOcommon.hpp>
#include <nImO/nImOdouble.hpp>
#include <nImO/nImOmessage.hpp>
#include <nImO/nImOstringbuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

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

nImO::Integer::Integer(void) :
    inherited(), _intValue(0)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::Integer(const int64_t initialValue) :
    inherited(), _intValue(initialValue)
{
    ODL_ENTER(); //####
    ODL_LL1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::Integer(const nImO::Integer & other) :
    inherited(), _intValue(other._intValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::~Integer(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Integer::~Integer

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::Value *
nImO::Integer::clone(void)
const
{
    ODL_OBJENTER(); //####
    Integer * result = new Integer(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Integer::copy

bool
nImO::Integer::equalTo(const nImO::Value & other,
                       bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isDouble())
    {
        ODL_LOG("(other.isDouble())"); //####
        const Double & otherRef = static_cast<const Double &>(other);

        result = (_intValue == otherRef.getDoubleValue());
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isInteger())
    {
        ODL_LOG("(other.isInteger())"); //####
        const Integer & otherRef = static_cast<const Integer &>(other);

        result = (_intValue == otherRef._intValue);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.equalTo(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::equalTo

bool
nImO::Integer::greaterThan(const nImO::Value & other,
                           bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isDouble())
    {
        ODL_LOG("(other.isDouble())"); //####
        const Double & otherRef = static_cast<const Double &>(other);

        result = (_intValue > otherRef.getDoubleValue());
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isInteger())
    {
        ODL_LOG("(other.isInteger())"); //####
        const Integer & otherRef = static_cast<const Integer &>(other);

        result = (_intValue > otherRef._intValue);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.lessThan(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::greaterThan

bool
nImO::Integer::greaterThanOrEqual(const nImO::Value & other,
                                  bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isDouble())
    {
        ODL_LOG("(other.isDouble())"); //####
        const Double & otherRef = static_cast<const Double &>(other);

        result = (_intValue >= otherRef.getDoubleValue());
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isInteger())
    {
        ODL_LOG("(other.isInteger())"); //####
        const Integer & otherRef = static_cast<const Integer &>(other);

        result = (_intValue >= otherRef._intValue);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.lessThanOrEqual(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::greaterThanOrEqual

bool
nImO::Integer::lessThan(const nImO::Value & other,
                        bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isDouble())
    {
        ODL_LOG("(other.isDouble())"); //####
        const Double & otherRef = static_cast<const Double &>(other);

        result = (_intValue < otherRef.getDoubleValue());
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isInteger())
    {
        ODL_LOG("(other.isInteger())"); //####
        const Integer & otherRef = static_cast<const Integer &>(other);

        result = (_intValue < otherRef._intValue);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.greaterThan(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::lessThan

bool
nImO::Integer::lessThanOrEqual(const nImO::Value & other,
                               bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isDouble())
    {
        ODL_LOG("(other.isDouble())"); //####
        const Double & otherRef = static_cast<const Double &>(other);

        result = (_intValue <= otherRef.getDoubleValue());
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isInteger())
    {
        ODL_LOG("(other.isInteger())"); //####
        const Integer & otherRef = static_cast<const Integer &>(other);

        result = (_intValue <= otherRef._intValue);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.greaterThanOrEqual(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::lessThanOrEqual

nImO::Integer &
nImO::Integer::operator =(const nImO::Integer & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _intValue = other._intValue;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Integer::operator=

nImO::Integer &
nImO::Integer::operator =(const int64_t value)
{
    ODL_OBJENTER(); //####
    ODL_LL1("value = ", value); //####
    _intValue = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Integer::operator=

void
nImO::Integer::printToStringBuffer(nImO::StringBuffer & outBuffer,
                                   const bool           squished)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addLong(_intValue);
    ODL_OBJEXIT(); //####
} // nImO::Integer::printToStringBuffer

void
nImO::Integer::writeToMessage(nImO::Message & outMessage)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    if ((-16 <= _intValue) && (15 >= _intValue))
    {
        ODL_LOG("((-16 <= _intValue) && (15 >= _intValue))"); //####
        uint8_t stuff = kKindInteger + kKindIntegerShortValue +
                        (_intValue & kKindIntegerShortValueValueMask);

        outMessage.appendBytes(&stuff, sizeof(stuff));
    }
    else
    {
        ODL_LOG("! ((-16 <= _intValue) && (15 >= _intValue))"); //####
        NumberAsBytes numBuff;
        size_t        numBytes = I2B(_intValue, numBuff);

        if (0 < numBytes)
        {
            ODL_LOG("(0 < numBytes)"); //####
            uint8_t stuff = kKindInteger + kKindIntegerLongValue +
                            ((numBytes - 1) & kKindIntegerLongValueCountMask);

            outMessage.appendBytes(&stuff, sizeof(stuff));
            outMessage.appendBytes(numBuff + sizeof(numBuff) - numBytes, numBytes);
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::Integer::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
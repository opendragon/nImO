//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOset.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO sets.
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

#include "nImOset.hpp"

#include <nImO/nImOstringbuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO sets. */
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

nImO::Set::Set(void) :
    inherited1(), inherited2(), _keyKind(kEnumerableUnknown)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Set::Set

nImO::Set::Set(const nImO::Set & other) :
    inherited1(), inherited2(), _keyKind(kEnumerableUnknown)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Blob::Blob

nImO::Set::~Set(void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Set::~Set

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Set::addEntries(const nImO::Set & other)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    if ((other._keyKind == _keyKind) || (kEnumerableUnknown == _keyKind))
    {
        for (const_iterator walker(other.begin()); other.end() != walker; ++walker)
        {
            Value * aValue = (*walker)->clone();

            addValue(aValue);
        }
    }
    ODL_EXIT(); //####
} // nImO::Set::addEntries

void
nImO::Set::addToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addChar(kStartSetChar);
    outBuffer.addChar(' ');
    for (const_iterator walker(begin()); end() != walker; ++walker)
    {
        Value * aValue = *walker;

        aValue->addToStringBuffer(outBuffer);
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndSetChar);
    ODL_OBJEXIT(); //####
} // nImO::Set::addToStringBuffer

nImO::Set::insertResult
nImO::Set::addValue(Value * val)
{
    ODL_OBJENTER(); //####
    ODL_P1("val = ", val); //####
    insertResult result;

    if (NULL == val)
    {
        result = insertResult(end(), false);
    }
    else
    {
        if (kEnumerableUnknown == _keyKind)
        {
            _keyKind = val->enumerationType();
        }
        if (val->enumerationType() == _keyKind)
        {
            result = inherited2::insert(val);
            if (! result.second)
            {
                delete val;
            }
        }
        else
        {
            result = insertResult(end(), false);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::addValue

void
nImO::Set::clear(void)
{
    ODL_OBJENTER(); //####
    for (const_iterator walker(begin()); end() != walker; ++walker)
    {
        Value * aValue = *walker;

        delete aValue;
    }
    inherited2::clear();
    _keyKind = kEnumerableUnknown;
    ODL_OBJEXIT(); //####
} // nImO::Set::clear

nImO::Value *
nImO::Set::clone(void)
const
{
    ODL_OBJENTER(); //####
    Set * result = new Set(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Set::copy

bool
nImO::Set::equalTo(const Value & other,
                   bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

#if 0
    if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value == otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.equalTo(*this, validComparison);
    }
    else
#endif//0
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Set::equalTo

bool
nImO::Set::greaterThan(const Value & other,
                       bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

#if 0
    if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value > otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.lessThan(*this, validComparison);
    }
    else
#endif//0
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Set::greaterThan

bool
nImO::Set::greaterThanOrEqual(const Value & other,
                              bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

#if 0
    if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value >= otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.lessThanOrEqual(*this, validComparison);
    }
    else
#endif//0
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Set::greaterThanOrEqual

bool
nImO::Set::lessThan(const Value & other,
                    bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

#if 0
    if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value < otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.greaterThan(*this, validComparison);
    }
    else
#endif//0
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Set::lessThan

bool
nImO::Set::lessThanOrEqual(const Value & other,
                           bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

#if 0
    if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value <= otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.greaterThanOrEqual(*this, validComparison);
    }
    else
#endif//0
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Set::lessThanOrEqual

nImO::Set &
nImO::Set::operator =(const nImO::Set & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        clear();
        addEntries(other);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Set::operator=

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

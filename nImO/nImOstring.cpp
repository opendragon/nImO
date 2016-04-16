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

#include <nImO/nImOstringbuffer.hpp>

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

nImO::String::String(const std::string & initialValue) :
    inherited(), _value(initialValue)
{
    ODL_ENTER(); //####
    ODL_S1s("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String(const char * initialValue) :
    inherited(), _value(initialValue)
{
    ODL_ENTER(); //####
    ODL_S1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::String::String

nImO::String::String(const nImO::String & other) :
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

void
nImO::String::addToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addString(_value, true);
    ODL_OBJEXIT(); //####
} // nImO::String::addToStringBuffer

nImO::Value *
nImO::String::clone(void)
const
{
    ODL_OBJENTER(); //####
    String * result = new String(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::String::copy

bool
nImO::String::equalTo(const Value & other,
                      bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
    }
    else if (other.isString())
    {
        const String & otherRef = static_cast<const String &>(other);

        result = (_value == otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.equalTo(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::equalTo

bool
nImO::String::greaterThan(const Value & other,
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
    }
    else if (other.isString())
    {
        const String & otherRef = static_cast<const String &>(other);

        result = (_value > otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.lessThan(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::greaterThan

bool
nImO::String::greaterThanOrEqual(const Value & other,
                                 bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
    }
    else if (other.isString())
    {
        const String & otherRef = static_cast<const String &>(other);

        result = (_value >= otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.lessThanOrEqual(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::greaterThanOrEqual

bool
nImO::String::lessThan(const Value & other,
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
    }
    else if (other.isString())
    {
        const String & otherRef = static_cast<const String &>(other);

        result = (_value < otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.greaterThan(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::lessThan

bool
nImO::String::lessThanOrEqual(const Value & other,
                              bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
    }
    else if (other.isString())
    {
        const String & otherRef = static_cast<const String &>(other);

        result = (_value <= otherRef._value);
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.greaterThanOrEqual(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::String::lessThanOrEqual

nImO::String &
nImO::String::operator =(const nImO::String & other)
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
nImO::String::operator =(const std::string & value)
{
    ODL_OBJENTER(); //####
    ODL_S1s("value = ", value); //####
    _value = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::String::operator=

nImO::String &
nImO::String::operator =(const char * value)
{
    ODL_OBJENTER(); //####
    ODL_S1("value = ", value); //####
    _value = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::String::operator=

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

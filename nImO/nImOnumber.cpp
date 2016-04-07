//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOnumber.cpp
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
//  Created:    2016-03-21
//
//--------------------------------------------------------------------------------------------------

#include "nImOnumber.hpp"

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

nImO::Number::Number(void) :
    inherited(), _intValue(0), _floatValue(0), _valueIsFloat(false)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Number::Number

nImO::Number::Number(const int64_t initialValue) :
    inherited(), _intValue(initialValue), _floatValue(0), _valueIsFloat(false)
{
    ODL_ENTER(); //####
    ODL_LL1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Number::Number

nImO::Number::Number(const double initialValue) :
    inherited(), _intValue(0), _floatValue(initialValue), _valueIsFloat(true)
{
    ODL_ENTER(); //####
    ODL_D1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Number::Number

nImO::Number::Number(const nImO::Number & other) :
    inherited(), _intValue(other._intValue), _floatValue(other._floatValue),
    _valueIsFloat(other._valueIsFloat)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Number::Number

nImO::Number::~Number(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Number::~Number

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Number::addToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    if (_valueIsFloat)
    {
        outBuffer.addDouble(_floatValue);
    }
    else
    {
        outBuffer.addLong(_intValue);
    }
    ODL_OBJEXIT(); //####
} // nImO::Number::addToStringBuffer

nImO::Value *
nImO::Number::clone(void)
const
{
    ODL_OBJENTER(); //####
    Number * result = new Number(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Number::copy

bool
nImO::Number::greaterThan(const Value & other,
                          bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    const Number * otherPtr = dynamic_cast<const Number *>(&other);
    bool           result;

    if (otherPtr)
    {
        if (_valueIsFloat)
        {
            result = (_floatValue > ((otherPtr->_valueIsFloat) ? otherPtr->_floatValue :
                                     otherPtr->_intValue));
        }
        else
        {
            result = (static_cast<double>(_intValue) > ((otherPtr->_valueIsFloat) ?
                                                        otherPtr->_floatValue :
                                                        otherPtr->_intValue));
        }
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.lessThan(*this, validComparison);
    }
    else
    {
        result = false;
        validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Number::greaterThan

bool
nImO::Number::lessThan(const Value & other,
                       bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    const Number * otherPtr = dynamic_cast<const Number *>(&other);
    bool           result;

    if (otherPtr)
    {
        if (_valueIsFloat)
        {
            result = (_floatValue < ((otherPtr->_valueIsFloat) ? otherPtr->_floatValue :
                                     otherPtr->_intValue));
        }
        else
        {
            result = (static_cast<double>(_intValue) < ((otherPtr->_valueIsFloat) ?
                                                        otherPtr->_floatValue :
                                                        otherPtr->_intValue));
        }
        validComparison = true;
    }
    else if (other.isContainer())
    {
        result = other.greaterThan(*this, validComparison);
    }
    else
    {
        result = false;
        validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Number::lessThan

nImO::Number &
nImO::Number::operator =(const nImO::Number & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _valueIsFloat = other._valueIsFloat;
        _intValue = other._intValue;
        _floatValue = other._floatValue;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Number::operator=

nImO::Number &
nImO::Number::operator =(const double value)
{
    ODL_OBJENTER(); //####
    ODL_D1("value = ", value); //####
    _valueIsFloat = true;
    _floatValue = value;
    _intValue = 0;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Number::operator=

nImO::Number &
nImO::Number::operator =(const int64_t value)
{
    ODL_OBJENTER(); //####
    ODL_LL1("value = ", value); //####
    _valueIsFloat = false;
    _floatValue = 0;
    _intValue = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Number::operator=
        
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

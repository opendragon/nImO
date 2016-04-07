//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOarray.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO arrays.
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

#include "nImOarray.hpp"

#include <nImO/nImOstringbuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO arrays. */
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

nImO::Array::Array(void) :
    inherited1(), inherited2()
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::Array(const nImO::Array & other) :
    inherited1(), inherited2()
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Array::Array

nImO::Array::~Array(void)
{
    ODL_OBJENTER(); //####
    removeAllEntries();
    ODL_OBJEXIT(); //####
} // nImO::Array::~Array

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Array::addEntries(const nImO::Array & other)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    for (const_iterator walker(other.begin()); other.end() != walker; ++walker)
    {
        Value * aValue = (*walker)->clone();

        push_back(aValue);
    }
    ODL_EXIT(); //####
} // nImO::Array::addEntries

void
nImO::Array::addToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addChar(kStartArrayChar);
    outBuffer.addChar(' ');
    for (const_iterator walker(begin()); end() != walker; ++walker)
    {
        Value * aValue = *walker;

        aValue->addToStringBuffer(outBuffer);
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndArrayChar);
    ODL_OBJEXIT(); //####
} // nImO::Array::addToStringBuffer

nImO::Value *
nImO::Array::clone(void)
const
{
    ODL_OBJENTER(); //####
    Array * result = new Array(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Array::copy

bool
nImO::Array::greaterThan(const Value & other,
                         bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    const Array * otherPtr = dynamic_cast<const Array *>(&other);
    bool          result;

    if (otherPtr)
    {
#if 0
        //TBD
        result = (_value > otherPtr->_value);
        validComparison = true;
#else//0
        result = false;
        validComparison = false;
#endif//0
    }
    else if (other.isContainer())
    {
        result = validComparison = false;
    }
    else if (0 < size())
    {
        result = validComparison = true;
        for (const_iterator walker(begin()); result && (end() != walker); ++walker)
        {
            bool    lV = true;
            Value * aValue = *walker;

            result = aValue->greaterThan(other, lV);
            validComparison &= lV;
        }
    }
    else
    {
        result = false;
        validComparison = true;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Array::greaterThan

bool
nImO::Array::lessThan(const Value & other,
                      bool &        validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    const Array * otherPtr = dynamic_cast<const Array *>(&other);
    bool          result;

    if (otherPtr)
    {
#if 0
        //TBD
        result = (_value < otherPtr->_value);
        validComparison = true;
#else//0
        result = false;
        validComparison = false;
#endif//0
    }
    else if (other.isContainer())
    {
        result = validComparison = false;
    }
    else if (0 < size())
    {
        result = validComparison = true;
        for (const_iterator walker(begin()); result && (end() != walker); ++walker)
        {
            bool    lV = true;
            Value * aValue = *walker;

            result = aValue->lessThan(other, lV);
            validComparison &= lV;
        }
    }
    else
    {
        result = validComparison = true;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Array::lessThan

nImO::Array &
nImO::Array::operator =(const nImO::Array & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        removeAllEntries();
        addEntries(other);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Array::operator=

void
nImO::Array::removeAllEntries(void)
{
    ODL_OBJENTER(); //####
    clear();
    for (const_iterator walker(begin()); end() != walker; ++walker)
    {
        Value * aValue = *walker;

        delete aValue;
    }
    ODL_OBJEXIT(); //####
} // nImO::Array::removeAllEntries

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

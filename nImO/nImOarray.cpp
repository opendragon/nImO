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
    clear();
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
    for (const_iterator walker(other.inherited2::begin()); other.inherited2::end() != walker;
         ++walker)
    {
        Value * aValue = (*walker)->clone();

        addValue(aValue);
    }
    ODL_EXIT(); //####
} // nImO::Array::addEntries

nImO::Array &
nImO::Array::addValue(nImO::Value * newElement)
{
    ODL_OBJENTER(); //####
    ODL_P1("newElement = ", newElement); //####
    if (NULL != newElement)
    {
        inherited2::push_back(newElement);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Array::addValue

nImO::Value *
nImO::Array::at(const size_t index)
const
{
    ODL_OBJENTER(); //####
    Value * result;

    if (index < inherited2::size())
    {
        result = inherited2::at(index);
    }
    else
    {
        result = NULL;
    }
    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Array::at

void
nImO::Array::clear(void)
{
    ODL_OBJENTER(); //####
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        Value * aValue = *walker;

        delete aValue;
    }
    inherited2::clear();
    ODL_OBJEXIT(); //####
} // nImO::Array::clear

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
nImO::Array::equalTo(const nImO::Value & other,
                     bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    // Note that all the values must be validated.
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        Value * aValue = *walker;

        if (aValue)
        {
            result &= aValue->equalTo(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::equalTo

const char *
nImO::Array::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char * initialChars = "(";

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Array::getInitialCharacters

bool
nImO::Array::greaterThan(const nImO::Value & other,
                         bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        Value * aValue = *walker;

        if (aValue)
        {
            result &= aValue->greaterThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::greaterThan

bool
nImO::Array::greaterThanOrEqual(const nImO::Value & other,
                                bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        Value * aValue = *walker;

        if (aValue)
        {
            result &= aValue->greaterThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::greaterThanOrEqual

bool
nImO::Array::lessThan(const nImO::Value & other,
                      bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        Value * aValue = *walker;

        if (aValue)
        {
            result &= aValue->lessThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::lessThan

bool
nImO::Array::lessThanOrEqual(const nImO::Value & other,
                             bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = (inherited2::begin() != inherited2::end());

    validComparison = result;
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison &&
         (inherited2::end() != walker); ++walker)
    {
        Value * aValue = *walker;

        if (aValue)
        {
            result &= aValue->lessThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Array::lessThanOrEqual

nImO::Array &
nImO::Array::operator =(const nImO::Array & other)
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
} // nImO::Array::operator=

void
nImO::Array::printToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addChar(kStartArrayChar);
    outBuffer.addChar(' ');
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        Value * aValue = *walker;
        
        aValue->printToStringBuffer(outBuffer);
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndArrayChar);
    ODL_OBJEXIT(); //####
} // nImO::Array::printToStringBuffer

nImO::Value *
nImO::Array::readFromStringBuffer(const nImO::StringBuffer & inBuffer,
                                  const size_t               fromIndex,
                                  const char *               termChars,
                                  size_t *                   updatedIndex)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "updatedIndex = ", updatedIndex); //####
    ODL_LL1("fromIndex = ", fromIndex); //####
    ODL_S1("termChars = ", termChars); //####
    //bool    done = false;
    //bool    eatWhitespace = false;
    //bool    valid = false;
    Value * result = NULL;
    size_t  localIndex = fromIndex;
    int     aChar = inBuffer.getChar(localIndex++);
    int     endChar = StringBuffer::getEndChar();

    ODL_EXIT_P(result); //####
    return result;
} // nImO::Array::readFromStringBuffer
 
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

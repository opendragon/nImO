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
        for (const_iterator walker(other.inherited2::begin()); other.inherited2::end() != walker;
             ++walker)
        {
            Value * aValue = (*walker)->clone();

            addValue(aValue);
        }
    }
    ODL_EXIT(); //####
} // nImO::Set::addEntries

nImO::Set::InsertResult
nImO::Set::addValue(nImO::Value * val)
{
    ODL_OBJENTER(); //####
    ODL_P1("val = ", val); //####
    InsertResult result;

    if (NULL == val)
    {
        result = InsertResult(inherited2::end(), false);
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
            result = InsertResult(inherited2::end(), false);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::addValue

void
nImO::Set::clear(void)
{
    ODL_OBJENTER(); //####
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
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
nImO::Set::equalTo(const nImO::Value & other,
                   bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
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
} // nImO::Set::equalTo

nImO::Set::iterator
nImO::Set::find(const nImO::Value & key)
{
    ODL_OBJENTER(); //####
    ODL_P1("key = ", &key); //####
    iterator result;

    if (key.enumerationType() == _keyKind)
    {
        result = inherited2::find(&const_cast<Value &>(key));
    }
    else
    {
        result = inherited2::end();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::find

nImO::Set::const_iterator
nImO::Set::find(const nImO::Value & key)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("key = ", &key); //####
    const_iterator result;

    if (key.enumerationType() == _keyKind)
    {
        result = inherited2::find(&const_cast<Value &>(key));
    }
    else
    {
        result = inherited2::end();
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Set::find

const char *
nImO::Set::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char * initialChars = "[";

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Set::getInitialCharacters

bool
nImO::Set::greaterThan(const nImO::Value & other,
                       bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
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
} // nImO::Set::greaterThan

bool
nImO::Set::greaterThanOrEqual(const nImO::Value & other,
                              bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
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
} // nImO::Set::greaterThanOrEqual

bool
nImO::Set::lessThan(const nImO::Value & other,
                    bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
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
} // nImO::Set::lessThan

bool
nImO::Set::lessThanOrEqual(const nImO::Value & other,
                           bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) &&
                   (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
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

void
nImO::Set::printToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addChar(kStartSetChar);
    outBuffer.addChar(' ');
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        Value * aValue = *walker;
        
        aValue->printToStringBuffer(outBuffer);
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndSetChar);
    ODL_OBJEXIT(); //####
} // nImO::Set::printToStringBuffer

nImO::Value *
nImO::Set::readFromStringBuffer(const nImO::StringBuffer & inBuffer,
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
} // nImO::Set::readFromStringBuffer
 
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
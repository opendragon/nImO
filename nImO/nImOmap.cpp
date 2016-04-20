//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOmap.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO maps.
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

#include "nImOmap.hpp"

#include <nImO/nImOstringbuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO maps. */
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

nImO::Map::Map(void) :
    inherited1(), inherited2(), _keyKind(kEnumerableUnknown)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Map::

nImO::Map::Map(const nImO::Map & other) :
    inherited1(), inherited2(), _keyKind(kEnumerableUnknown)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    addEntries(other);
    ODL_EXIT_P(this); //####
} // nImO::Map::Map

nImO::Map::~Map(void)
{
    ODL_OBJENTER(); //####
    clear();
    ODL_OBJEXIT(); //####
} // nImO::Map::~Map

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Map::addEntries(const nImO::Map & other)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    if ((other._keyKind == _keyKind) || (kEnumerableUnknown == _keyKind))
    {
        for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
        {
            mapValue aValue = *walker;
            Value *  key = aValue.first->clone();
            Value *  mappedValue = aValue.second->clone();

            addValue(key, mappedValue);
        }
    }
    ODL_EXIT(); //####
} // nImO::Map::addEntries

nImO::Map::insertResult
nImO::Map::addValue(nImO::Value * newKey,
                    nImO::Value * newValue)
{
    ODL_OBJENTER(); //####
    ODL_P2("newKey = ", newKey, "newValue = ", newValue); //####
    insertResult result;

    if ((NULL == newKey) || (NULL == newValue))
    {
        delete newKey;
        delete newValue;
        result = insertResult(inherited2::end(), false);
    }
    else
    {
        if (kEnumerableUnknown == _keyKind)
        {
            _keyKind = newKey->enumerationType();
        }
        if (newKey->enumerationType() == _keyKind)
        {
            mapValue keyValue(newKey, newValue);

            result = inherited2::insert(keyValue);
            if (! result.second)
            {
                delete newKey;
                delete newValue;
            }
        }
        else
        {
            result = insertResult(inherited2::end(), false);
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Map::addValue

void
nImO::Map::clear(void)
{
    ODL_OBJENTER(); //####
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        mapValue aValue = *walker;

        delete aValue.first;
        delete aValue.second;
    }
    inherited2::clear();
    _keyKind = kEnumerableUnknown;
    ODL_OBJEXIT(); //####
} // nImO::Map::clear

nImO::Value *
nImO::Map::clone(void)
const
{
    ODL_OBJENTER(); //####
    Map * result = new Map(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Map::copy

bool
nImO::Map::equalTo(const nImO::Value & other,
                   bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) && (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison && (inherited2::end() != walker); ++walker)
    {
        Value * aValue = walker->first;

        if (aValue)
        {
            result &= aValue->equalTo(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::equalTo

nImO::Map::iterator
nImO::Map::find(const nImO::Value & key)
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
} // nImO::Map::find

nImO::Map::const_iterator
nImO::Map::find(const nImO::Value & key)
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
} // nImO::Map::find

bool
nImO::Map::greaterThan(const nImO::Value & other,
                       bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) && (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison && (inherited2::end() != walker); ++walker)
    {
        Value * aValue = walker->first;

        if (aValue)
        {
            result &= aValue->greaterThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::greaterThan

bool
nImO::Map::greaterThanOrEqual(const nImO::Value & other,
                              bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) && (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison && (inherited2::end() != walker); ++walker)
    {
        Value * aValue = walker->first;

        if (aValue)
        {
            result &= aValue->greaterThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::greaterThanOrEqual

bool
nImO::Map::lessThan(const nImO::Value & other,
                    bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) && (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison && (inherited2::end() != walker); ++walker)
    {
        Value * aValue = walker->first;

        if (aValue)
        {
            result &= aValue->lessThan(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::lessThan

bool
nImO::Map::lessThanOrEqual(const nImO::Value & other,
                           bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", validComparison); //####
    bool result = ((other.enumerationType() == _keyKind) && (inherited2::begin() != inherited2::end()));

    validComparison = (kEnumerableUnknown != _keyKind);
    ODL_B1("validComparison <- ", validComparison); //####
    for (const_iterator walker(inherited2::begin()); validComparison && (inherited2::end() != walker); ++walker)
    {
        Value * aValue = walker->first;

        if (aValue)
        {
            result &= aValue->lessThanOrEqual(other, validComparison);
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Map::lessThanOrEqual

nImO::Map &
nImO::Map::operator =(const nImO::Map & other)
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
} // nImO::Map::operator=

void
nImO::Map::printToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addChar(kStartMapChar);
    outBuffer.addChar(' ');
    for (const_iterator walker(inherited2::begin()); inherited2::end() != walker; ++walker)
    {
        mapValue aValue = *walker;
        
        aValue.first->printToStringBuffer(outBuffer);
        outBuffer.addChar(' ');
        outBuffer.addChar(kKeyValueSeparator);
        outBuffer.addChar(' ');
        aValue.second->printToStringBuffer(outBuffer);
        outBuffer.addChar(' ');
    }
    outBuffer.addChar(kEndMapChar);
    ODL_OBJEXIT(); //####
} // nImO::Map::printToStringBuffer

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

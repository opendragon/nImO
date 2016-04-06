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
    else
    {
        _size = 0;
        _value = NULL;
    }
    ODL_EXIT_P(this); //####
} // nImO::Blob

nImO::Blob::~Blob(void)
{
    ODL_OBJENTER(); //####
    delete[] _value;
    ODL_OBJEXIT(); //####
} // nImO::Blob::~Blob

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

DEFINE_ADDTOSTRINGBUFFER_(nImO::Blob)
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addBlob(_value, _size);
    ODL_OBJEXIT(); //####
} // nImO::Blob::addToStringBuffer

DEFINE_GREATERTHAN_(nImO::Blob)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    const Blob * otherPtr = dynamic_cast<const Blob *>(&other);
    bool         result;

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
        result = other.lessThan(*this, validComparison);
    }
    else
    {
        result = false;
        validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Blob::greaterThan

DEFINE_LESSTHAN_(nImO::Blob)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    const Blob * otherPtr = dynamic_cast<const Blob *>(&other);
    bool         result;

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
        result = other.greaterThan(*this, validComparison);
    }
    else
    {
        result = false;
        validComparison = false;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Blob::lessThan

nImO::Blob &
nImO::Blob::operator =(const nImO::Blob & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        delete[] _value;
        if (0 < other._size)
        {
            _size = other._size;
            _value = new uint8_t[_size];
            memcpy(_value, other._value, _size);
        }
        else
        {
            _size = 0;
            _value = NULL;
        }
    }
    ODL_OBJEXIT_P(this);
    return *this;
} // operator=

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

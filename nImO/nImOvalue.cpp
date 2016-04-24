//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOvalue.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO general values.
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

#include "nImOvalue.hpp"

#include <nImO/nImOarray.hpp>
#include <nImO/nImOboolean.hpp>
#include <nImO/nImOmap.hpp>
#include <nImO/nImOnumber.hpp>
#include <nImO/nImOset.hpp>
#include <nImO/nImOstring.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO general values. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

nImO::Value::BufferReaderMap nImO::Value::gReaders;

std::string nImO::Value::gTerminators;

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

nImO::Value::Value(void)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Value::Value

nImO::Value::~Value(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Value::~Value

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::Value::initialize(void)
{
    ODL_ENTER(); //####
    const char * prefixes = Boolean::getInitialCharacters();
  
    if (NULL != prefixes)
    { 
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Boolean::readFromStringBuffer);

            gReaders.insert(aValue);
        } 
    }
    prefixes = Number::getInitialCharacters();
    if (NULL != prefixes)
    { 
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Number::readFromStringBuffer);

            gReaders.insert(aValue);
        } 
    }
    prefixes = String::getInitialCharacters();
    if (NULL != prefixes)
    { 
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &String::readFromStringBuffer);

            gReaders.insert(aValue);
        } 
    }
    prefixes = Array::getInitialCharacters();
    if (NULL != prefixes)
    { 
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Array::readFromStringBuffer);

            gReaders.insert(aValue);
        } 
    }
    prefixes = Map::getInitialCharacters();
    if (NULL != prefixes)
    { 
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Map::readFromStringBuffer);

            gReaders.insert(aValue);
        } 
    }
    prefixes = Set::getInitialCharacters();
    if (NULL != prefixes)
    { 
        for ( ; '\0' != *prefixes; ++prefixes)
        {
            BufferReaderValue aValue(*prefixes, &Set::readFromStringBuffer);

            gReaders.insert(aValue);
        } 
    }
    const char * suffixes = Array::getTerminalCharacters();
    
    gTerminators = StringBuffer::kEndCharacter;
    if (NULL != suffixes)
    {
        gTerminators += suffixes;
    }
    suffixes = Map::getTerminalCharacters();
    if (NULL != suffixes)
    {
        gTerminators += suffixes;
    }
    suffixes = Set::getTerminalCharacters();
    if (NULL != suffixes)
    {
        gTerminators += suffixes;
    }
    ODL_EXIT(); //####
} // nImO::Value::initialize

bool
nImO::Value::isLegalTerminator(const char aChar)
{
    ODL_ENTER(); //####
    ODL_C1("aChar = ", aChar); //####
    bool result;
    
    if (isspace(aChar))
    {
        result = true;
    }
    else if (std::string::npos == gTerminators.find(aChar))
    {
        result = false;
    }
    else
    {
        result = true;
    }
    ODL_EXIT_B(result); //####
    return result;
} // nImO::Value::isLegalTerminator

nImO::Value *
nImO::Value::readFromStringBuffer(const nImO::StringBuffer & inBuffer,
                                  size_t &                   position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    //bool    done = false;
    //bool    eatWhitespace = false;
    //bool    valid = false;
    Value * result = NULL;
    size_t  localIndex = position;
    int     aChar = inBuffer.getChar(localIndex);

    // Skip over whitespace
    for ( ; isspace(aChar); )
    {
        aChar = inBuffer.getChar(++localIndex);
    }
    if (StringBuffer::kEndCharacter == aChar)
    {
        ODL_LOG("(StringBuffer::kEndCharacter == aChar)"); //####
    }
    else
    {
        BufferReaderIterator match = gReaders.find(aChar);

        if (gReaders.end() == match)
        {
            ODL_LOG("(gReaders.end() == match)"); //####
        }
        else
        {
            BufferReader handler = match->second;

            if (NULL == handler)
            {
                ODL_LOG("(NULL == handler)"); //####
            }
            else
            {
                result = handler(inBuffer, localIndex);
                if (NULL != result)
                {
                    position = localIndex;
                }
            }
        }
    }
    ODL_EXIT_P(result); //####
    return result;
} // nImO::Value::readFromStringBuffer
 
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

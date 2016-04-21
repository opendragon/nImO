//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOboolean.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO boolean values.
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

#include "nImOboolean.hpp"

#include <nImO/nImOstringbuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO boolean values. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The standard textual representation of a @c false value. */
static const std::string kCanonicalFalse("false");

/*! @brief The standard textual representation of a @c true value. */
static const std::string kCanonicalTrue("true");

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

nImO::Boolean::Boolean(void) :
    inherited(), _value(false)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Boolean::Boolean

nImO::Boolean::Boolean(const bool initialValue) :
    inherited(), _value(initialValue)
{
    ODL_ENTER(); //####
    ODL_B1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Boolean::Boolean

nImO::Boolean::Boolean(const nImO::Boolean & other) :
    inherited(), _value(other._value)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Boolean::Boolean

nImO::Boolean::~Boolean(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Boolean::~Boolean

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::Value *
nImO::Boolean::clone(void)
const
{
    ODL_OBJENTER(); //####
    Boolean * result = new Boolean(*this);

    ODL_OBJEXIT_P(result); //####
    return result;
} // nImO::Boolean::copy

bool
nImO::Boolean::equalTo(const nImO::Value & other,
                       bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value == otherRef._value);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.equalTo(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Boolean::equalTo

const std::string &
nImO::Boolean::getCanonicalRepresentation(const bool aValue)
{
    ODL_ENTER(); //####
    const std::string & result = (aValue ? kCanonicalTrue : kCanonicalFalse);

    ODL_EXIT_P(&result); //####
    return result;
} // nImO::Boolean::getCanonicalRepresentation

const char *
nImO::Boolean::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char * initialChars = "ftFT";

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Boolean::getInitialCharacters

bool
nImO::Boolean::greaterThan(const nImO::Value & other,
                           bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value > otherRef._value);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.lessThan(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Boolean::greaterThan

bool
nImO::Boolean::greaterThanOrEqual(const nImO::Value & other,
                                  bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value >= otherRef._value);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.lessThanOrEqual(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Boolean::greaterThanOrEqual

bool
nImO::Boolean::lessThan(const nImO::Value & other,
                        bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value < otherRef._value);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.greaterThan(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Boolean::lessThan

bool
nImO::Boolean::lessThanOrEqual(const nImO::Value & other,
                               bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isBoolean())
    {
        const Boolean & otherRef = static_cast<const Boolean &>(other);

        result = (_value <= otherRef._value);
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        result = other.greaterThanOrEqual(*this, validComparison);
    }
    else
    {
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Boolean::lessThanOrEqual

nImO::Boolean &
nImO::Boolean::operator =(const nImO::Boolean & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _value = other._value;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Boolean::operator=

nImO::Boolean &
nImO::Boolean::operator =(const bool value)
{
    ODL_OBJENTER(); //####
    ODL_B1("value = ", value); //####
    _value = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Boolean::operator=

void
nImO::Boolean::printToStringBuffer(nImO::StringBuffer & outBuffer)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    outBuffer.addBool(_value);
    ODL_OBJEXIT(); //####
} // nImO::Boolean::printToStringBuffer

nImO::Value *
nImO::Boolean::readFromStringBuffer(const nImO::StringBuffer & inBuffer,
                                    const size_t               fromIndex,
                                    const char *               termChars,
                                    size_t *                   updatedIndex)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "updatedIndex = ", updatedIndex); //####
    ODL_LL1("fromIndex = ", fromIndex); //####
    ODL_S1("termChars = ", termChars); //####
    bool    done = false;
    bool    eatWhitespace = false;
    bool    valid = false;
    Value * result = NULL;
    size_t  localIndex = fromIndex;
    int     aChar = inBuffer.getChar(localIndex++);
    int     endChar = StringBuffer::getEndChar();

    // Select which form of the value that is in the buffer:
    if ((aChar == 'f') || (aChar == 'F'))
    {
        for (size_t ii = 1, len = kCanonicalFalse.length(); (! done); )
        {
            aChar = tolower(inBuffer.getChar(localIndex++));
            if (endChar == aChar)
            {
                if (NULL == termChars)
                {
                    done = valid = true; // the character seen is the buffer end
                }
                else
                {
                    done = true; // terminator not seen
                }
            }
            else if (eatWhitespace)
            {
                if (! isspace(aChar))
                {
                    if (NULL == termChars)
                    {
                        done = valid = true; // no terminators, but only whitespace after value
                    }
                    else if (NULL == strchr(termChars, aChar))
                    {
                        done = true; // the next character is unexpected        
                    }
                    else
                    {
                        done = valid = true; // terminator seen after the whitespace
                    }
                }
            }
            else if (kCanonicalFalse[ii] == aChar)
            {
                if (len == ++ii)
                {
                    // the last character of the reference value was seen, look for a terminator
                    eatWhitespace = true;
                }
            }
            else if (isspace(aChar))
            {
                // string ended via whitespace
                eatWhitespace = true;
            }
            else if (NULL == termChars)
            {
                // no terminators, so this is likely not a valid string
                done = true;
            }
            else if (NULL == strchr(termChars, aChar))
            {
                // not one of the terminators, so this is likely not a valid string
                done = true;
            }
            else
            {
                // one of the terminators, so we can stop
                done = valid = true;
            }
        }
        if (valid)
        {
            result = new Boolean(false);
        }
    }
    else if ((aChar == 't') || (aChar == 'T'))
    {
        for (size_t ii = 1, len = kCanonicalTrue.length(); (! done); )
        {
            aChar = tolower(inBuffer.getChar(localIndex++));
            if (endChar == aChar)
            {
                if (NULL == termChars)
                {
                    done = valid = true; // the character seen is the buffer end
                }
                else
                {
                    done = true; // terminator not seen
                }
            }
            else if (eatWhitespace)
            {
                if (! isspace(aChar))
                {
                    if (NULL == termChars)
                    {
                        done = valid = true; // no terminators, but only whitespace after value
                    }
                    else if (NULL == strchr(termChars, aChar))
                    {
                        done = true; // the next character is unexpected        
                    }
                    else
                    {
                        done = valid = true; // terminator seen after the whitespace
                    }
                }
            }
            else if (kCanonicalTrue[ii] == aChar)
            {
                if (len == ++ii)
                {
                    // the last character of the reference value was seen, look for a terminator
                    eatWhitespace = true;
                }
            }
            else if (isspace(aChar))
            {
                // string ended via whitespace
                eatWhitespace = true;
            }
            else if (NULL == termChars)
            {
                // no terminators, so this is likely not a valid string
                done = true;
            }
            else if (NULL == strchr(termChars, aChar))
            {
                // not one of the terminators, so this is likely not a valid string
                done = true;
            }
            else
            {
                // one of the terminators, so we can stop
                done = valid = true;
            }
        }
        if (valid)
        {
            result = new Boolean(true);
        }
    }
    if ((NULL != result) && (NULL != updatedIndex))
    {
        *updatedIndex = localIndex - 1;
    }
    ODL_EXIT_P(result); //####
    return result;
} // nImO::Boolean::readFromStringBuffer

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

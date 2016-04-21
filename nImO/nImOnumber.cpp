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
nImO::Number::equalTo(const nImO::Value & other,
                      bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isNumber())
    {
        ODL_LOG("(other.isNumber())"); //####
        const Number & otherRef = static_cast<const Number &>(other);

        if (_valueIsFloat)
        {
            ODL_D1("_floatValue = ", _floatValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (_floatValue == otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_floatValue == otherRef._intValue);
            }
        }
        else
        {
            ODL_LL1("_intValue = ", _intValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (static_cast<double>(_intValue) == otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_intValue == otherRef._intValue);
            }
        }
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.equalTo(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Number::equalTo

const char *
nImO::Number::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char * initialChars = "+-.0123456789";

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Number::getInitialCharacters

bool
nImO::Number::greaterThan(const nImO::Value & other,
                          bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isNumber())
    {
        ODL_LOG("(other.isNumber())"); //####
        const Number & otherRef = static_cast<const Number &>(other);

        if (_valueIsFloat)
        {
            ODL_D1("_floatValue = ", _floatValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (_floatValue > otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_floatValue > otherRef._intValue);
            }
        }
        else
        {
            ODL_LL1("_intValue = ", _intValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (static_cast<double>(_intValue) > otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_intValue > otherRef._intValue);
            }
        }
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.lessThan(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Number::greaterThan

bool
nImO::Number::greaterThanOrEqual(const nImO::Value & other,
                                 bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isNumber())
    {
        ODL_LOG("(other.isNumber())"); //####
        const Number & otherRef = static_cast<const Number &>(other);

        if (_valueIsFloat)
        {
            ODL_D1("_floatValue = ", _floatValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (_floatValue >= otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_floatValue >= otherRef._intValue);
            }
        }
        else
        {
            ODL_LL1("_intValue = ", _intValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (static_cast<double>(_intValue) >= otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_intValue >= otherRef._intValue);
            }
        }
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.lessThanOrEqual(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Number::greaterThanOrEqual

bool
nImO::Number::lessThan(const nImO::Value & other,
                       bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = false;
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isNumber())
    {
        ODL_LOG("(other.isNumber())"); //####
        const Number & otherRef = static_cast<const Number &>(other);

        if (_valueIsFloat)
        {
            ODL_D1("_floatValue = ", _floatValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (_floatValue < otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_floatValue < otherRef._intValue);
            }
        }
        else
        {
            ODL_LL1("_intValue = ", _intValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (static_cast<double>(_intValue) < otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_intValue < otherRef._intValue);
            }
        }
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.greaterThan(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Number::lessThan

bool
nImO::Number::lessThanOrEqual(const nImO::Value & other,
                              bool &              validComparison)
const
{
    ODL_OBJENTER(); //####
    ODL_P2("other = ", &other, "validComparison = ", &validComparison); //####
    bool result;

    if (&other == this)
    {
        ODL_LOG("(&other == this)"); //####
        result = validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isNumber())
    {
        ODL_LOG("(other.isNumber())"); //####
        const Number & otherRef = static_cast<const Number &>(other);

        if (_valueIsFloat)
        {
            ODL_D1("_floatValue = ", _floatValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (_floatValue <= otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_floatValue <= otherRef._intValue);
            }
        }
        else
        {
            ODL_LL1("_intValue = ", _intValue); //####
            if (otherRef._valueIsFloat)
            {
                ODL_D1("otherRef._floatValue = ", otherRef._floatValue); //####
                result = (static_cast<double>(_intValue) <= otherRef._floatValue);
            }
            else
            {
                ODL_LL1("otherRef._intValue = ", otherRef._intValue); //####
                result = (_intValue <= otherRef._intValue);
            }
        }
        validComparison = true;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    else if (other.isContainer())
    {
        ODL_LOG("(other.isContainer())"); //####
        result = other.greaterThanOrEqual(*this, validComparison);
    }
    else
    {
        ODL_LOG("! (other.isContainer())"); //####
        result = validComparison = false;
        ODL_B1("validComparison <- ", validComparison); //####
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Number::lessThanOrEqual

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

void
nImO::Number::printToStringBuffer(nImO::StringBuffer & outBuffer)
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
} // nImO::Number::printToStringBuffer

nImO::Value *
nImO::Number::readFromStringBuffer(const nImO::StringBuffer & inBuffer,
                                   const size_t               fromIndex,
                                   const char *               termChars,
                                   size_t *                   updatedIndex)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "updatedIndex = ", updatedIndex); //####
    ODL_LL1("fromIndex = ", fromIndex); //####
    ODL_S1("termChars = ", termChars); //####
    enum ScanState
    {
        kScanInitial,
        kScanIntegerDigitSeen,
        kScanFractionStartSeen,
        kScanExponentStart,
        kScanExponentSeen,
        kScanTrailingWhitespace
    }; // ScanState

    bool      done = false;
    bool      eatWhitespace = false;
    bool      isDouble = false;
    bool      needsAdigit = false;
    bool      sawInitialMinus = false;
    bool      sawInitialPlus = false;
    bool      sawExponentMinus = false;
    bool      sawExponentPlus = false;
    bool      sawDecimalPoint = false;
    bool      valid = false;
    int64_t   integerPart = 0;
    int64_t   fractionPart = 0;
    int       exponent = 0;
    int       fractionPower = 0;
    ScanState currentState = kScanInitial;
    Value *   result = NULL;
    size_t    localIndex = fromIndex;
    int       endChar = StringBuffer::getEndChar();

    for (int aChar; (! done); )
    {
        aChar = tolower(inBuffer.getChar(localIndex++));
        switch (currentState)
        {
        case kScanInitial :
            if ('+' == aChar)
            {
               if (sawInitialMinus || sawInitialPlus)
               {
                   done = true; // more than one sign character
               }
               else
               {
                   sawInitialPlus = true;
               }
            }
            else if ('-' == aChar)
            {
               if (sawInitialMinus || sawInitialPlus)
               {
                   done = true; // more than one sign character
               }
               else
               {
                   sawInitialMinus = true;
               }
            }
            else if ('.' == aChar)
            {
                sawDecimalPoint = needsAdigit = isDouble = true;
                currentState = kScanFractionStartSeen;
            }
            else if (isdigit(aChar))
            {
                currentState = kScanIntegerDigitSeen;
                integerPart = aChar - '0';
            }
            else
            {
                done = true; // unexpected character
            }
            break;

        case kScanIntegerDigitSeen :
            if ('.' == aChar)
            {
                isDouble = true;
                currentState = kScanFractionStartSeen;
            }
            else if ('e' == aChar)
            {
                isDouble = true;
                currentState = kScanExponentStart;
            }
            else if (endChar == aChar)
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
            else if (isdigit(aChar))
            {
                integerPart *= 10;
                integerPart += aChar - '0';
            }
            else if (isspace(aChar))
            {
                currentState = kScanTrailingWhitespace;
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
            break;

        case kScanFractionStartSeen :
            if ('e' == aChar)
            {
                if (needsAdigit)
                {
                    done = true; // decimal point with no trailing digits
                }
                else
                {
                    currentState = kScanExponentStart;
                }
            }
            else if (endChar == aChar)
            {
                if (NULL == termChars)
                {
                    if (needsAdigit)
                    {
                        done = true; // decimal point with no trailing digits
                    }
                    else
                    {
                        done = valid = true; // the character seen is the buffer end
                    }
                }
                else
                {
                    done = true; // terminator not seen
                }
            }
            else if (isdigit(aChar))
            {
                needsAdigit = false;
                fractionPart *= 10;
                fractionPart += aChar - '0';
                ++fractionPower;
            }
            else if (isspace(aChar))
            {
                if (needsAdigit)
                {
                    done = true; // decimal point with no trailing digits
                }
                else
                {
                    currentState = kScanTrailingWhitespace;
                }
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
            else if (needsAdigit)
            {
                done = true; // decimal point with no trailing digits
            }
            else
            {
                // one of the terminators, so we can stop
                done = valid = true;
            }
            break;

        case kScanExponentStart :
            if ('+' == aChar)
            {
               if (sawExponentMinus || sawExponentPlus)
               {
                   done = true; // more than one sign character
               }
               else
               {
                   sawExponentPlus = true;
               }
            }
            else if ('-' == aChar)
            {
               if (sawExponentMinus || sawExponentPlus)
               {
                   done = true; // more than one sign character
               }
               else
               {
                   sawExponentMinus = true;
               }
            }
            else if (isdigit(aChar))
            {
                currentState = kScanExponentSeen;
                exponent = aChar - '0';
            }
            else
            {
                done = true; // unexpected character
            }
            break;

        case kScanExponentSeen :
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
            else if (isdigit(aChar))
            {
                exponent *= 10;
                exponent += aChar - '0';
            }
            else if (isspace(aChar))
            {
                currentState = kScanTrailingWhitespace;
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
            break;

        case kScanTrailingWhitespace :
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
            else if (! isspace(aChar))
            {
                if (NULL == termChars)
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
            break;

        default :
            break;

        }
    }
    if (valid)
    {
        if (isDouble)
        {
            double fullNumber;
            
            if (0 == exponent)
            {
                fullNumber = integerPart + (fractionPart / std::pow(10.0, fractionPower));
            }
            else if (sawExponentMinus)
            {
                fullNumber = ((integerPart + (fractionPart / std::pow(10.0, fractionPower))) /
                              std::pow(10.0, exponent));
            }
            else if (exponent > fractionPower)
            {
                fullNumber = ((integerPart * std::pow(10.0, exponent)) +
                              (fractionPart * std::pow(10.0, exponent - fractionPower)));
            }
            else if (exponent < fractionPower)
            {
                fullNumber = ((integerPart * std::pow(10.0, exponent)) +
                              (fractionPart / std::pow(10.0, fractionPower - exponent)));
            }
            else
            {
                fullNumber = (integerPart * std::pow(10.0, exponent)) + fractionPart;
            }
            result = new Number(sawInitialMinus ? -fullNumber : fullNumber);
        }
        else
        {
            result = new Number(sawInitialMinus ? -integerPart : integerPart);
        }
        if (NULL != updatedIndex)
        {
            *updatedIndex = localIndex - 1;
        }
    }
    ODL_EXIT_P(result); //####
    return result;
} // nImO::Number::readFromStringBuffer
 
#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

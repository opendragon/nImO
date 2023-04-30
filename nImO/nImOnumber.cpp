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

#include <nImOnumber.h>

#include <nImOdouble.h>
#include <nImOinteger.h>
#include <nImOstringBuffer.h>

//#include <odlEnable.h>
#include <odlInclude.h>

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

nImO::Number::Number
    (void) :
        inherited()
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Number::Number

nImO::Number::Number
    (Number &&  other)
    noexcept :
        inherited()
{
    NIMO_UNUSED_VAR_(other);
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Number::Number

nImO::Number::~Number
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Number::~Number

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::Number)
nImO::Number::asNumber
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Number::asNumber

CPtr(char)
nImO::Number::getInitialCharacters
    (void)
{
    static CPtr(char)   initialChars{"+-.0123456789"};

    ODL_ENTER(); //####
    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Number::getInitialCharacters

nImO::Number &
nImO::Number::operator=
    (Number &&    other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Number::operator=

nImO::SpValue
nImO::Number::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    enum class ScanState
    {
        Initial,
        IntegerDigitSeen,
        FractionStartSeen,
        ExponentStart,
        ExponentSeen
    }; // ScanState

    bool        atEnd;
    bool        done = false;
    bool        isDouble = false;
    bool        needsAdigit = false;
    bool        sawInitialMinus = false;
    bool        sawInitialPlus = false;
    bool        sawExponentMinus = false;
    bool        sawExponentPlus = false;
    bool        valid = false;
    int64_t     integerPart = 0;
    int64_t     fractionPart = 0;
    int         exponent = 0;
    int         fractionPower = 0;
    ScanState   currentState = ScanState::Initial;
    SpValue     result;
    size_t      localIndex = position;

    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    for (int aChar; (! done); )
    {
        aChar = tolower(inBuffer.getChar(localIndex++, atEnd));
        ODL_I2("aChar <- ", aChar, "localIndex <- ", localIndex); //####
        ODL_B1("atEnd <- ", atEnd); //####
        switch (currentState)
        {
            case ScanState::Initial :
                if ('+' == aChar)
                {
                   if (sawInitialMinus || sawInitialPlus)
                   {
                       ODL_LOG("(sawInitialMinus || sawInitialPlus)"); //####
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
                       ODL_LOG("(sawInitialMinus || sawInitialPlus)"); //####
                       done = true; // more than one sign character
                   }
                   else
                   {
                       sawInitialMinus = true;
                   }
                }
                else if ('.' == aChar)
                {
                    needsAdigit = isDouble = true;
                    currentState = ScanState::FractionStartSeen;
                }
                else if (isdigit(aChar))
                {
                    currentState = ScanState::IntegerDigitSeen;
                    integerPart = aChar - '0';
                }
                else
                {
                    ODL_LOG("! (isdigit(aChar))"); //####
                    done = true; // unexpected character
                }
                break;

            case ScanState::IntegerDigitSeen :
                if ('.' == aChar)
                {
                    isDouble = true;
                    currentState = ScanState::FractionStartSeen;
                }
                else if ('e' == aChar)
                {
                    isDouble = true;
                    currentState = ScanState::ExponentStart;
                }
                else if (atEnd || isLegalTerminator(aChar))
                {
                    // unexpected character seen, but valid so far
                    --localIndex;
                    done = valid = true;
                }
                else if (isdigit(aChar))
                {
                    integerPart *= 10;
                    integerPart += aChar - '0';
                }
                else
                {
                    ODL_LOG("! (isDigit(aChar))"); //####
                    done = true;
                }
                break;

            case ScanState::FractionStartSeen :
                if ('e' == aChar)
                {
                if (needsAdigit)
                    {
                        done = true; // decimal point with no trailing digits
                    }
                    else
                    {
                        currentState = ScanState::ExponentStart;
                    }
                }
                else if (atEnd || isLegalTerminator(aChar))
                {
                    if (needsAdigit)
                    {
                        ODL_LOG("(needsAdigit)"); //####
                        done = true; // decimal point with no trailing digits
                    }
                    else
                    {
                        --localIndex;
                        done = valid = true; // the character seen is the end of the value
                    }
                }
                else if (isdigit(aChar))
                {
                    needsAdigit = false;
                    fractionPart *= 10;
                    fractionPart += aChar - '0';
                    ++fractionPower;
                }
                else
                {
                    ODL_LOG("! (isDigit(aChar))"); //####
                    done = true; // decimal point with no trailing digits
                }
                break;

            case ScanState::ExponentStart :
                if ('+' == aChar)
                {
                   if (sawExponentMinus || sawExponentPlus)
                   {
                       ODL_LOG("(sawExponentMinus || sawExponentPlus)"); //####
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
                       ODL_LOG("(sawExponentMinus || sawExponentPlus)"); //####
                       done = true; // more than one sign character
                   }
                   else
                   {
                       sawExponentMinus = true;
                   }
                }
                else if (isdigit(aChar))
                {
                    currentState = ScanState::ExponentSeen;
                    exponent = aChar - '0';
                }
                else
                {
                    ODL_LOG("! (isdigit(aChar))"); //####
                    done = true; // unexpected character
                }
                break;

            case ScanState::ExponentSeen :
                if (atEnd || isLegalTerminator(aChar))
                {
                    --localIndex;
                    done = valid = true; // the character seen is the buffer end
                }
                else if (isdigit(aChar))
                {
                    exponent *= 10;
                    exponent += aChar - '0';
                }
                else
                {
                    ODL_LOG("! (isDigit(aChar))"); //####
                    done = true;
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
            double  fullNumber;

            if (0 == exponent)
            {
                fullNumber = integerPart + (fractionPart / std::pow(10.0, fractionPower));
            }
            else if (sawExponentMinus)
            {
                fullNumber = ((integerPart + (fractionPart / std::pow(10.0, fractionPower))) / std::pow(10.0, exponent));
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
            result.reset(new Double(sawInitialMinus ? -fullNumber : fullNumber));
        }
        else
        {
            result.reset(new Integer(sawInitialMinus ? -integerPart : integerPart));
        }
        position = localIndex;
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Number::readFromStringBuffer

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOinteger.cpp
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
//  Created:    2016-04-26
//
//--------------------------------------------------------------------------------------------------

#include "nImOinteger.hpp"

#include <nImOarray.hpp>
#include <nImOcommon.hpp>
#include <nImOdouble.hpp>
#include <nImOmessage.hpp>
#include <nImOstringBuffer.hpp>

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

nImO::Integer::Integer(void) :
    inherited(), _intValue(0)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::Integer(const int64_t initialValue) :
    inherited(), _intValue(initialValue)
{
    ODL_ENTER(); //####
    ODL_LL1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::Integer(const nImO::Integer &other) :
    inherited(), _intValue(other._intValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::~Integer(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Integer::~Integer

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

const nImO::Integer *
nImO::Integer::asInteger(void)
const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Integer::asInteger

bool
nImO::Integer::deeplyEqualTo(const nImO::Value &other)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result = (&other == this);

    if (! result)
    {
        const Integer *otherPtr = other.asInteger();

        if (nullptr != otherPtr)
        {
            result = (_intValue == otherPtr->_intValue);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::deeplyEqualTo

nImO::Enumerable
nImO::Integer::enumerationType(void)
const
{
    ODL_OBJENTER(); //####
    Enumerable result = Enumerable::Integer;

    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Integer::enumerationType

bool
nImO::Integer::equalTo(const nImO::Value &other,
                       bool              &validComparison)
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
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.equalTo(*this, validComparison);
                }
            }
            else
            {
                result = (_intValue == intPtr->_intValue);
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_intValue == doublePtr->getDoubleValue());
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::equalTo

nImO::SpValue
nImO::Integer::extractValue(const nImO::Message &theMessage,
                            const int           leadByte,
                            size_t              &position,
                            nImO::SpArray       parentValue)
{
    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "parentValue = ", //####
           parentValue.get()); //####
    ODL_XL1("leadByte = ", leadByte); //####
    SpValue   result;
    IntStatus numStatus;
    int64_t   holder = extractInt64FromMessage(theMessage, leadByte, position, numStatus);

    if (IntStatus::Successful == numStatus)
    {
        result.reset(new Integer(holder));
    }
    else
    {
        ODL_LOG("! (numStatus::Successful == status)"); //####
        result.reset();
    }
    if ((nullptr != parentValue) && (nullptr != result))
    {
        ODL_LOG("((nullptr != parentValue) && (nullptr != result))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Integer::extractValue

void
nImO::Integer::getExtractionInfo(DataKind               &aByte,
                                 DataKind               &aMask,
                                 nImO::Value::Extractor &theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = DataKind::Integer;
    aMask = DataKind::Mask;
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Integer::getExtractionInfo

nImO::DataKind
nImO::Integer::getTypeTag(void)
const
{
    ODL_OBJENTER(); //####
    DataKind result = DataKind::OtherMessageExpectedIntegerValue;

    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Integer::getTypeTag

bool
nImO::Integer::greaterThan(const nImO::Value &other,
                           bool              &validComparison)
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
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.lessThan(*this, validComparison);
                }
            }
            else
            {
                result = (_intValue > intPtr->_intValue);
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_intValue > doublePtr->getDoubleValue());
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::greaterThan

bool
nImO::Integer::greaterThanOrEqual(const nImO::Value &other,
                                  bool              &validComparison)
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
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.lessThanOrEqual(*this, validComparison);
                }
            }
            else
            {
                result = (_intValue >= intPtr->_intValue);
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_intValue >= doublePtr->getDoubleValue());
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::greaterThanOrEqual

bool
nImO::Integer::lessThan(const nImO::Value &other,
                        bool              &validComparison)
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
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.greaterThan(*this, validComparison);
                }
            }
            else
            {
                result = (_intValue < intPtr->_intValue);
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_intValue < doublePtr->getDoubleValue());
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::lessThan

bool
nImO::Integer::lessThanOrEqual(const nImO::Value &other,
                               bool              &validComparison)
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
    else
    {
        const Double *doublePtr = other.asDouble();

        if (nullptr == doublePtr)
        {
            const Integer *intPtr = other.asInteger();

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result = validComparison = false;
                    ODL_B1("validComparison <- ", validComparison); //####
                }
                else
                {
                    result = other.greaterThanOrEqual(*this, validComparison);
                }
            }
            else
            {
                result = (_intValue <= intPtr->_intValue);
                validComparison = true;
                ODL_B1("validComparison <- ", validComparison); //####
            }
        }
        else
        {
            result = (_intValue <= doublePtr->getDoubleValue());
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::lessThanOrEqual

void
nImO::Integer::printToStringBuffer(nImO::StringBuffer &outBuffer,
                                   const bool         squished)
const
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(squished)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addLong(_intValue);
    ODL_OBJEXIT(); //####
} // nImO::Integer::printToStringBuffer

void
nImO::Integer::writeToMessage(nImO::Message &outMessage)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    writeInt64ToMessage(outMessage, _intValue);
    ODL_OBJEXIT(); //####
} // nImO::Integer::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

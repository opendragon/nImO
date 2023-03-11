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

#include <nImOinteger.h>

#include <nImOarray.h>
#include <nImOcommon.h>
#include <nImOdouble.h>
#include <nImOmessage.h>
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

nImO::Integer::Integer
    (void) :
        inherited(), _intValue(0)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::Integer
    (const int64_t  initialValue) :
        inherited(), _intValue(initialValue)
{
    ODL_ENTER(); //####
    ODL_I1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::Integer
    (const Integer &    other) :
        inherited(), _intValue(other._intValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::Integer
    (Integer && other)
    noexcept :
        inherited(std::move(other)), _intValue(other._intValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._intValue = 0;
    ODL_EXIT_P(this); //####
} // nImO::Integer::Integer

nImO::Integer::~Integer
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Integer::~Integer

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(nImO::Integer)
nImO::Integer::asInteger
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::Integer::asInteger

bool
nImO::Integer::deeplyEqualTo
    (const Value &  other)
    const
{
    bool    result = (&other == this);

    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (! result)
    {
        CPtr(Integer)   otherPtr{other.asInteger()};

        if (nullptr != otherPtr)
        {
            result = (_intValue == otherPtr->_intValue);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Integer::deeplyEqualTo

nImO::Enumerable
nImO::Integer::enumerationType
    (void)
    const
{
    Enumerable  result = Enumerable::Integer;

    ODL_OBJENTER(); //####
    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Integer::enumerationType

nImO::ComparisonStatus
nImO::Integer::equalTo
    (const Value &  other)
    const
{
    ComparisonStatus    result;

    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (&other != this)
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.equalTo(*this);
                }
            }
            else
            {
                result = (_intValue == intPtr->_intValue);
            }
        }
        else
        {
            result = (_intValue == doublePtr->getDoubleValue());
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Integer::equalTo

nImO::SpValue
nImO::Integer::extractValue
    (const Message &    theMessage,
     const int          leadByte,
     size_t &           position,
     SpArray            parentValue)
{
    SpValue     result;
    IntStatus   numStatus;
    int64_t     holder = extractInt64FromMessage(theMessage, leadByte, position, numStatus);

    ODL_ENTER(); //####
    ODL_P3("theMessage = ", &theMessage, "position = ", &position, "parentValue = ", //####
           parentValue.get()); //####
    ODL_X1("leadByte = ", leadByte); //####
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
nImO::Integer::getExtractionInfo
    (DataKind &                 aByte,
     DataKind &                 aMask,
     nImO::Value::Extractor &   theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = DataKind::Integer;
    aMask = DataKind::Mask;
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Integer::getExtractionInfo

nImO::DataKind
nImO::Integer::getTypeTag
    (void)
    const
{
    DataKind    result = DataKind::OtherMessageExpectedIntegerValue;

    ODL_OBJENTER(); //####
    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::Integer::getTypeTag

nImO::ComparisonStatus
nImO::Integer::greaterThan
    (const Value &  other)
    const
{
    ComparisonStatus    result;

    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (&other == this)
    {
        result = false;
    }
    else
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.lessThan(*this);
                }
            }
            else
            {
                result = (_intValue > intPtr->_intValue);
            }
        }
        else
        {
            result = (_intValue > doublePtr->getDoubleValue());
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Integer::greaterThan

nImO::ComparisonStatus
nImO::Integer::greaterThanOrEqual
    (const Value &  other)
    const
{
    ComparisonStatus    result;

    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (&other != this)
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.lessThanOrEqual(*this);
                }
            }
            else
            {
                result = (_intValue >= intPtr->_intValue);
            }
        }
        else
        {
            result = (_intValue >= doublePtr->getDoubleValue());
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Integer::greaterThanOrEqual

nImO::ComparisonStatus
nImO::Integer::lessThan
    (const Value &    other)
    const
{
    ComparisonStatus    result;

    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (&other == this)
    {
        result = false;
    }
    else
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.greaterThan(*this);
                }
            }
            else
            {
                result = (_intValue < intPtr->_intValue);
            }
        }
        else
        {
            result = (_intValue < doublePtr->getDoubleValue());
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Integer::lessThan

nImO::ComparisonStatus
nImO::Integer::lessThanOrEqual
    (const Value &  other)
    const
{
    ComparisonStatus    result;

    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (&other != this)
    {
        CPtr(Double)    doublePtr{other.asDouble()};

        if (nullptr == doublePtr)
        {
            CPtr(Integer)   intPtr{other.asInteger()};

            if (nullptr == intPtr)
            {
                if (nullptr == other.asContainer())
                {
                    result.clear();
                }
                else
                {
                    result = other.greaterThanOrEqual(*this);
                }
            }
            else
            {
                result = (_intValue <= intPtr->_intValue);
            }
        }
        else
        {
            result = (_intValue <= doublePtr->getDoubleValue());
        }
    }
    ODL_OBJEXIT(); //####
    return result;
} // nImO::Integer::lessThanOrEqual

nImO::Integer &
nImO::Integer::operator=
    (Integer && other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _intValue = other._intValue;
        other._intValue = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Integer::operator=

std::ostream &
nImO::Integer::operator<<
    (std::ostream & out)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("out = ", &out); //####
    out << _intValue;
    ODL_OBJEXIT_P(&out); //####
    return out;
} // nImO::Integer::operator<<

void
nImO::Integer::printToStringBuffer
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_ARG_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addLong(_intValue);
    ODL_OBJEXIT(); //####
} // nImO::Integer::printToStringBuffer

void
nImO::Integer::printToStringBufferAsJSON
    (StringBuffer & outBuffer,
     const bool     squished)
    const
{
    NIMO_UNUSED_ARG_(squished);
    ODL_OBJENTER(); //####
    ODL_P1("outBuffer = ", &outBuffer); //####
    ODL_B1("squished = ", squished); //####
    outBuffer.addLong(_intValue);
    ODL_OBJEXIT(); //####
} // nImO::Integer::printToStringBufferAsJSON

void
nImO::Integer::writeToMessage
    (Message &  outMessage)
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

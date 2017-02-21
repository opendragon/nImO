//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOlogical.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO logical values.
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

#include "nImOlogical.hpp"

#include <nImO/nImOarray.hpp>
#include <nImO/nImOmessage.hpp>
#include <nImO/nImOstringBuffer.hpp>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO logical values. */
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

nImO::Logical::Logical(void) :
    inherited(), _value(false)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Logical::Logical

nImO::Logical::Logical(const bool initialValue) :
    inherited(), _value(initialValue)
{
    ODL_ENTER(); //####
    ODL_B1("initialValue = ", initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::Logical::Logical

nImO::Logical::Logical(const nImO::Logical &other) :
    inherited(), _value(other._value)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::Logical::Logical

nImO::Logical::~Logical(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::Logical::~Logical

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::Logical::deeplyEqualTo(const nImO::Value &other)
const
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    bool result = (&other == this);

    if (! result)
    {
        const Logical *otherPtr = other.asLogical();
        
        if (nullptr != otherPtr)
        {
            result = (_value == otherPtr->_value);
        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::Logical::deeplyEqualTo

bool
nImO::Logical::equalTo(const nImO::Value &other,
                       bool              &validComparison)
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
    else
    {
        const Logical *otherPtr = other.asLogical();
        
        if (nullptr == otherPtr)
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
            result = (_value == otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Logical::equalTo

#if (! MAC_OR_LINUX_)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! MAC_OR_LINUX_
nImO::SpValue
nImO::Logical::extractValue(const nImO::Message &theMessage,
                            const int           leadByte,
                            size_t              &position,
                            nImO::ReadStatus    &status,
                            nImO::SpArray       parentValue)
{
#if (! defined(ODL_ENABLE_LOGGING_))
# if MAC_OR_LINUX_
#  pragma unused(theMessage)
# endif // MAC_OR_LINUX_
#endif // ! defined(ODL_ENABLE_LOGGING_)
    ODL_ENTER(); //####
    ODL_P4("theMessage = ", &theMessage, "position = ", &position, "status = ", &status, //####
           "parentValue = ", parentValue.get()); //####
    ODL_XL1("leadByte = ", leadByte); //####
    SpValue result(new Logical(static_cast<int>(DataKind::OtherLogicalTrueValue) ==
                                (static_cast<int>(DataKind::OtherLogicalValueMask) & leadByte)));

    ++position; // We will always accept the lead byte
    status = ReadStatus::Successful;
    ODL_LL2("position <- ", position, "status <- ", static_cast<int>(status)); //####
    if ((nullptr != parentValue) && (nullptr != result))
    {
        ODL_LOG("((nullptr != parentValue) && (nullptr != result))"); //####
        parentValue->addValue(result);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Logical::extractValue
#if (! MAC_OR_LINUX_)
# pragma warning(pop)
#endif // ! MAC_OR_LINUX_

const std::string &
nImO::Logical::getCanonicalRepresentation(const bool aValue)
{
    ODL_ENTER(); //####
    const std::string &result = (aValue ? kCanonicalTrue : kCanonicalFalse);

    ODL_EXIT_P(&result); //####
    return result;
} // nImO::Logical::getCanonicalRepresentation

void
nImO::Logical::getExtractionInfo(uint8_t                &aByte,
                                 uint8_t                &aMask,
                                 nImO::Value::Extractor &theExtractor)
{
    ODL_ENTER(); //####
    ODL_P3("aByte = ", &aByte, "aMask = ", &aMask, "theExtractor = ", &theExtractor); //####
    aByte = (static_cast<uint8_t>(DataKind::Other) | static_cast<uint8_t>(DataKind::OtherLogical));
    aMask = (static_cast<uint8_t>(DataKind::Mask) | static_cast<uint8_t>(DataKind::OtherTypeMask));
    theExtractor = extractValue;
    ODL_EXIT(); //####
} // nImO::Logical::getExtractionInfo

const char *
nImO::Logical::getInitialCharacters(void)
{
    ODL_ENTER(); //####
    static const char *initialChars = "ftFT";

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::Logical::getInitialCharacters

bool
nImO::Logical::greaterThan(const nImO::Value &other,
                           bool              &validComparison)
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
    else
    {
        const Logical *otherPtr = other.asLogical();
        
        if (nullptr == otherPtr)
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
            result = (_value > otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Logical::greaterThan

bool
nImO::Logical::greaterThanOrEqual(const nImO::Value &other,
                                  bool              &validComparison)
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
    else
    {
        const Logical *otherPtr = other.asLogical();
        
        if (nullptr == otherPtr)
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
            result = (_value >= otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Logical::greaterThanOrEqual

bool
nImO::Logical::lessThan(const nImO::Value &other,
                        bool              &validComparison)
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
    else
    {
        const Logical *otherPtr = other.asLogical();
        
        if (nullptr == otherPtr)
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
            result = (_value < otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Logical::lessThan

bool
nImO::Logical::lessThanOrEqual(const nImO::Value &other,
                               bool              &validComparison)
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
    else
    {
        const Logical *otherPtr = other.asLogical();
        
        if (nullptr == otherPtr)
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
            result = (_value <= otherPtr->_value);
            validComparison = true;
            ODL_B1("validComparison <- ", validComparison); //####
        }
    }
    ODL_OBJEXIT_LL(result); //####
    return result;
} // nImO::Logical::lessThanOrEqual

nImO::Logical &
nImO::Logical::operator =(const nImO::Logical &other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _value = other._value;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Logical::operator=

nImO::Logical &
nImO::Logical::operator =(const bool value)
{
    ODL_OBJENTER(); //####
    ODL_B1("value = ", value); //####
    _value = value;
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::Logical::operator=

void
nImO::Logical::printToStringBuffer(nImO::StringBuffer &outBuffer,
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
    outBuffer.addBool(_value);
    ODL_OBJEXIT(); //####
} // nImO::Logical::printToStringBuffer

nImO::SpValue
nImO::Logical::readFromStringBuffer(const nImO::StringBuffer &inBuffer,
                                    size_t                   &position)
{
    ODL_ENTER(); //####
    ODL_P2("inBuffer = ", &inBuffer, "position = ", &position); //####
    bool              candidateValue = false;
    SpValue           result;
    size_t            localIndex = position;
    int               aChar = inBuffer.getChar(localIndex++);
    const std::string *candidate;

    // Select which form of the value that is in the buffer:
    if (('f' == aChar) || ('F' == aChar))
    {
        candidate = &kCanonicalFalse;
    }
    else if (('t' == aChar) || ('T' == aChar))
    {
        candidate = &kCanonicalTrue;
        candidateValue = true;
    }
    else
    {
        candidate = nullptr;
    }
    if (nullptr != candidate)
    {
        bool done = false;
        bool valid = false;

        for (size_t ii = 1, len = candidate->length(); ! done; )
        {
            aChar = tolower(inBuffer.getChar(localIndex));
            if (isLegalTerminator(aChar))
            {
                done = valid = true; // the character seen is the buffer end
            }
            else if ((*candidate)[ii] == aChar)
            {
                ++localIndex;
                if (len == ++ii)
                {
                    // the last character of the reference value was seen
                    valid = isLegalTerminator(inBuffer.getChar(localIndex));
                    done = true;
                }
            }
            else
            {
                // valid so far
                done = true;
            }
        }
        if (valid)
        {
            result.reset(new Logical(candidateValue));
        }
    }
    if (nullptr != result)
    {
        position = localIndex;
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::Logical::readFromStringBuffer

void
nImO::Logical::writeToMessage(nImO::Message &outMessage)
const
{
    ODL_ENTER(); //####
    ODL_P1("outMessage = ", &outMessage); //####
    uint8_t stuff = static_cast<uint8_t>(DataKind::Other) + static_cast<uint8_t>(DataKind::OtherLogical) + (_value ? static_cast<uint8_t>(DataKind::OtherLogicalTrueValue) :
                                                               static_cast<uint8_t>(DataKind::OtherLogicalFalseValue));

    outMessage.appendBytes(&stuff, sizeof(stuff));
    ODL_EXIT(); //####
} // nImO::Logical::writeToMessage

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

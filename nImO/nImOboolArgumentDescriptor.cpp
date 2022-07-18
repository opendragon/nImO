//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOboolArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a boolean
//              command-line argument.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2015 by H Plus Technologies Ltd. and Simon Fraser University.
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
//  Created:    2015-08-25
//
//--------------------------------------------------------------------------------------------------

#include "nImOboolArgumentDescriptor.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a boolean command-line
 argument. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace nImO;

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

BoolArgumentDescriptor::BoolArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const bool             defaultValue) :
        inherited(argName, argDescription, argMode), _defaultValue(defaultValue)
{
    ODL_ENTER(); //####
    ODL_S2s("argName = ", argName, "argDescription = ", argDescription); //####
    ODL_B1("defaultValue = ", defaultValue); //####
    ODL_EXIT_P(this); //####
} // BoolArgumentDescriptor::BoolArgumentDescriptor

BoolArgumentDescriptor::BoolArgumentDescriptor
    (const BoolArgumentDescriptor & other) :
        inherited(other), _defaultValue(other._defaultValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // BoolArgumentDescriptor::BoolArgumentDescriptor

BoolArgumentDescriptor::~BoolArgumentDescriptor
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // BoolArgumentDescriptor::~BoolArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

SpBaseArgumentDescriptor
BoolArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_shared<BoolArgumentDescriptor>(*this)};

    ODL_EXIT_P(result.get());
    return result;
} // BoolArgumentDescriptor::clone

std::string
BoolArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{_defaultValue ? "1" : "0"};

    ODL_OBJEXIT_s(result); //####
    return result;
} // BoolArgumentDescriptor::getDefaultValue

std::string
BoolArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{_defaultValue ? "true" : "false"};

    ODL_OBJEXIT_s(result); //####
    return result;
} // BoolArgumentDescriptor::getPrintableDefaultValue

std::string
BoolArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{_currentValue ? "1" : "0"};

    ODL_OBJEXIT_s(result); //####
    return result;
} // BoolArgumentDescriptor::getProcessedValue

bool
BoolArgumentDescriptor::isLogical
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(true); //####
    return true;
} // BoolArgumentDescriptor::isLogical

SpBaseArgumentDescriptor
BoolArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor    result;
    StringVector                inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::BoolTypeTag, 3, name, argMode, inVector))
    {
        bool        okSoFar = true;
        bool        defaultValue;
        std::string defaultString{inVector[0]};
        std::string description{inVector[1]};

        if (0 < defaultString.length())
        {
            if ('1' == defaultString[0])
            {
                defaultValue = true;
            }
            else if ('0' == defaultString[0])
            {
                defaultValue = false;
            }
            else
            {
                okSoFar = false;
            }
        }
        else
        {
            okSoFar = false;
        }
        if (okSoFar)
        {
            result.reset(new BoolArgumentDescriptor(name, description, argMode, defaultValue));
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // BoolArgumentDescriptor::parseArgString

void
BoolArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_B1("_currentValue <- ", _currentValue); //####
    ODL_OBJEXIT(); //####
} // BoolArgumentDescriptor::setToDefaultValue

void
BoolArgumentDescriptor::swap
    (BoolArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    std::swap(_defaultValue, other._defaultValue);
    std::swap(_currentValue, other._currentValue);
    ODL_OBJEXIT(); //####
} // BoolArgumentDescriptor::swap

std::string
BoolArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{prefixFields("B")};

    result += suffixFields(getDefaultValue());
    ODL_OBJEXIT_s(result); //####
    return result;
} // BoolArgumentDescriptor::toString

bool
BoolArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    bool    boolValue;
    char    firstChar = tolower(value[0]);

    if (('0' == firstChar) || ('f' == firstChar) || ('n' == firstChar))
    {
        boolValue = false;
        setValidity(true);
        ODL_B1("_valid <- ", isValid()); //####
    }
    else if (('1' == firstChar) || ('t' == firstChar) || ('y' == firstChar))
    {
        boolValue = true;
        setValidity(true);
        ODL_B1("_valid <- ", isValid()); //####
    }
    else
    {
        setValidity(false);
        ODL_B1("_valid <- ", isValid()); //####
    }
    if (isValid())
    {
        _currentValue = boolValue;
        ODL_B1("_currentValue <- ", _currentValue); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // BoolArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

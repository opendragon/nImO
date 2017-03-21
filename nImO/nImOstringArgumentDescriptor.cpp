//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstringArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
//              string-type command-line argument.
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
//  Created:    2015-05-15
//
//--------------------------------------------------------------------------------------------------

#include "nImOstringArgumentDescriptor.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a string-type
 command-line argument. */
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

StringArgumentDescriptor::StringArgumentDescriptor(const std::string  &argName,
                                                   const std::string  &argDescription,
                                                   const ArgumentMode argMode,
                                                   const std::string  &defaultValue) :
    inherited(argName, argDescription, argMode), _defaultValue(defaultValue)
{
    ODL_ENTER(); //####
    ODL_S3s("argName = ", argName, "argDescription = ", argDescription, "defaultValue = ", //####
            defaultValue); //####
    ODL_EXIT_P(this); //####
} // StringArgumentDescriptor::StringArgumentDescriptor

StringArgumentDescriptor::StringArgumentDescriptor(const StringArgumentDescriptor &other) :
    inherited(other), _defaultValue(other._defaultValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // StringArgumentDescriptor::StringArgumentDescriptor

StringArgumentDescriptor::~StringArgumentDescriptor(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // StringArgumentDescriptor::~StringArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if 0
void
StringArgumentDescriptor::addValueToBottle(yarp::os::Bottle &container)
{
    ODL_ENTER(); //####
    ODL_P1("container = ", &container); //####
    container.addString(getProcessedValue());
    ODL_EXIT(); //####
} // StringArgumentDescriptor::addValueToBottle
#endif//0

SpBaseArgumentDescriptor
StringArgumentDescriptor::clone(void)
const
{
    ODL_OBJENTER(); //####
    auto result = std::make_shared<StringArgumentDescriptor>(*this);

    ODL_EXIT_P(result.get());
    return result;
} // StringArgumentDescriptor::clone

std::string
StringArgumentDescriptor::getDefaultValue(void)
{
    ODL_OBJENTER(); //####
    std::string result(_defaultValue);

    ODL_OBJEXIT_s(result); //####
    return result;
} // StringArgumentDescriptor::getDefaultValue

std::string
StringArgumentDescriptor::getProcessedValue(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_s(_currentValue); //####
    return _currentValue;
} // StringArgumentDescriptor::getProcessedValue

SpBaseArgumentDescriptor
StringArgumentDescriptor::parseArgString(const std::string &inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor result;
    StringVector             inVector;

    if (partitionString(inString, 3, inVector))
    {
        ArgumentMode argMode;
        bool         okSoFar = true;
        std::string  name(inVector[0]);
        std::string  typeTag(inVector[1]);
        std::string  modeString(inVector[2]);
        std::string  defaultString(inVector[3]);
        std::string  description(inVector[4]);

        if (typeTag != "S")
        {
            okSoFar = false;
        }
        if (okSoFar)
        {
            argMode = ModeFromString(modeString);
            okSoFar = (ArgumentMode::Unknown != argMode);
        }
        else
        {
            argMode = ArgumentMode::Unknown;
        }
        if (okSoFar)
        {
            result.reset(new StringArgumentDescriptor(name, description, argMode, defaultString));
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // StringArgumentDescriptor::parseArgString

void
StringArgumentDescriptor::setToDefaultValue(void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_S1s("_currentValue <- ", _currentValue); //####
    ODL_OBJEXIT(); //####
} // StringArgumentDescriptor::setToDefaultValue

void
StringArgumentDescriptor::swap(StringArgumentDescriptor &other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    std::swap(_currentValue, other._currentValue);
    std::swap(_defaultValue, other._defaultValue);
    ODL_OBJEXIT(); //####
} // StringArgumentDescriptor::swap

std::string
StringArgumentDescriptor::toString(void)
{
    ODL_OBJENTER(); //####
    std::string result(prefixFields("S"));

    result += suffixFields(_defaultValue);
    ODL_OBJEXIT_s(result); //####
    return result;
} // StringArgumentDescriptor::toString

bool
StringArgumentDescriptor::validate(const std::string &value)
{
    ODL_OBJENTER(); //####
    _valid = true;
    ODL_B1("_valid <- ", _valid); //####
    if (_valid)
    {
        _currentValue = value;
        ODL_S1s("_currentValue <- ", _currentValue); //####
    }
    ODL_OBJEXIT_B(_valid); //####
    return _valid;
} // StringArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

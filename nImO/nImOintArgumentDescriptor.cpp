//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOintArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent an integer
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
//  Created:    2015-05-15
//
//--------------------------------------------------------------------------------------------------

#include "nImOintArgumentDescriptor.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent an integer command-line
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

IntArgumentDescriptor::IntArgumentDescriptor(const std::string  &argName,
                                             const std::string  &argDescription,
                                             const ArgumentMode argMode,
                                             const int          defaultValue,
                                             const bool         hasMinimumValue,
                                             const int          minimumValue,
                                             const bool         hasMaximumValue,
                                             const int          maximumValue) :
    inherited(argName, argDescription, argMode), _defaultValue(defaultValue),
    _maximumValue(maximumValue), _minimumValue(minimumValue), _hasMaximumValue(hasMaximumValue),
    _hasMinimumValue(hasMinimumValue)
{
    ODL_ENTER(); //####
    ODL_S2s("argName = ", argName, "argDescription = ", argDescription); //####
    ODL_LL3("defaultValue = ", defaultValue, "minimumValue = ", minimumValue, //####
            "maximumValue = ", maximumValue); //####
    ODL_B2("hasMinimumValue = ", hasMinimumValue, "hasMaximumValue = ", hasMaximumValue); //####
    ODL_EXIT_P(this); //####
} // IntArgumentDescriptor::IntArgumentDescriptor

IntArgumentDescriptor::IntArgumentDescriptor(const IntArgumentDescriptor &other) :
    inherited(other), _defaultValue(other._defaultValue), _maximumValue(other._maximumValue),
    _minimumValue(other._minimumValue), _hasMaximumValue(other._hasMaximumValue),
    _hasMinimumValue(other._hasMinimumValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // IntArgumentDescriptor::IntArgumentDescriptor

IntArgumentDescriptor::~IntArgumentDescriptor(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // IntArgumentDescriptor::~IntArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if 0
void
IntArgumentDescriptor::addValueToBottle(yarp::os::Bottle &container)
{
    ODL_ENTER(); //####
    ODL_P1("container = ", &container); //####
    container.addInt(_currentValue);
    ODL_EXIT(); //####
} // IntArgumentDescriptor::addValueToBottle
#endif//0

SpBaseArgumentDescriptor
IntArgumentDescriptor::clone(void)
const
{
    ODL_OBJENTER(); //####
    auto result = std::make_shared<IntArgumentDescriptor>(*this);

    ODL_EXIT_P(result.get());
    return result;
} // IntArgumentDescriptor::clone

std::string
IntArgumentDescriptor::getDefaultValue(void)
{
    ODL_OBJENTER(); //####
    std::string result = std::to_string(_defaultValue);

    ODL_OBJEXIT_s(result); //####
    return result;
} // IntArgumentDescriptor::getDefaultValue

std::string
IntArgumentDescriptor::getProcessedValue(void)
{
    ODL_OBJENTER(); //####
    std::string result = std::to_string(_currentValue);

    ODL_OBJEXIT_s(result); //####
    return result;
} // IntArgumentDescriptor::getProcessedValue

SpBaseArgumentDescriptor
IntArgumentDescriptor::parseArgString(const std::string &inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor result;
    StringVector             inVector;

    if (partitionString(inString, 5, inVector))
    {
        ArgumentMode argMode;
        bool         okSoFar = true;
        int          defaultValue;
        int          maxValue;
        int          minValue;
        std::string  name(inVector[0]);
        std::string  typeTag(inVector[1]);
        std::string  modeString(inVector[2]);
        std::string  minValString(inVector[3]);
        std::string  maxValString(inVector[4]);
        std::string  defaultString(inVector[5]);
        std::string  description(inVector[6]);

        if (typeTag != "I")
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
        if (okSoFar && (0 < defaultString.length()))
        {
            int64_t intValue;

            if (nImO::ConvertToLong(defaultString.c_str(), intValue))
            {
                defaultValue = static_cast<int>(intValue);
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar && (0 < minValString.length()))
        {
            int64_t intValue;

            if (nImO::ConvertToLong(minValString.c_str(), intValue))
            {
                minValue = static_cast<int>(intValue);
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar && (0 < maxValString.length()))
        {
            int64_t intValue;

            if (nImO::ConvertToLong(maxValString.c_str(), intValue))
            {
                maxValue = static_cast<int>(intValue);
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar)
        {
            bool hasMaximumValue = (0 < maxValString.length());
            bool hasMinimumValue = (0 < minValString.length());

            result.reset(new IntArgumentDescriptor(name, description, argMode, defaultValue,
                                                   hasMinimumValue,
                                                   hasMinimumValue ? minValue : 0,
                                                   hasMaximumValue,
                                                   hasMaximumValue ? maxValue : 0));
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // IntArgumentDescriptor::parseArgString

void
IntArgumentDescriptor::setToDefaultValue(void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_LL1("_currentValue <- ", _currentValue); //####
    ODL_OBJEXIT(); //####
} // IntArgumentDescriptor::setToDefaultValue

void
IntArgumentDescriptor::swap(IntArgumentDescriptor &other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    std::swap(_argumentReference, other._argumentReference);
    std::swap(_defaultValue, other._defaultValue);
    std::swap(_currentValue, other._currentValue);
    std::swap(_maximumValue, other._maximumValue);
    std::swap(_minimumValue, other._minimumValue);
    std::swap(_hasMaximumValue, other._hasMaximumValue);
    std::swap(_hasMinimumValue, other._hasMinimumValue);
    ODL_OBJEXIT(); //####
} // IntArgumentDescriptor::swap

std::string
IntArgumentDescriptor::toString(void)
{
    ODL_OBJENTER(); //####
    std::string result(prefixFields("I"));

    result += _parameterSeparator;
    if (_hasMinimumValue)
    {
        result += std::to_string(_minimumValue);
    }
    result += _parameterSeparator;
    if (_hasMaximumValue)
    {
        result += std::to_string(_maximumValue);
    }
    result += suffixFields(getDefaultValue());
    ODL_OBJEXIT_s(result); //####
    return result;
} // IntArgumentDescriptor::toString

bool
IntArgumentDescriptor::validate(const std::string &value)
{
    ODL_OBJENTER(); //####
    int64_t intValue;

    if (nImO::ConvertToLong(value.c_str(), intValue))
    {
        _valid = true;
        ODL_B1("_valid <- ", _valid); //####
        if (_hasMinimumValue && (intValue < _minimumValue))
        {
            _valid = false;
            ODL_B1("_valid <- ", _valid); //####
        }
        if (_hasMaximumValue && (intValue > _maximumValue))
        {
            _valid = false;
            ODL_B1("_valid <- ", _valid); //####
        }
    }
    else
    {
        _valid = false;
        ODL_B1("_valid <- ", _valid); //####
    }
    if (_valid)
    {
        _currentValue = static_cast<int>(intValue);
        ODL_LL1("_currentValue <- ", _currentValue); //####
    }
    ODL_OBJEXIT_B(_valid); //####
    return _valid;
} // IntArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOdoubleArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a floating
//              point command-line argument.
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

#include "nImOdoubleArgumentDescriptor.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a floating point
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

DoubleArgumentDescriptor::DoubleArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const double           defaultValue,
     const bool             hasMinimumValue,
     const double           minimumValue,
     const bool             hasMaximumValue,
     const double           maximumValue) :
        inherited(argName, argDescription, argMode), _defaultValue(defaultValue),
        _maximumValue(maximumValue), _minimumValue(minimumValue), _hasMaximumValue(hasMaximumValue),
        _hasMinimumValue(hasMinimumValue)
{
    ODL_ENTER(); //####
    ODL_S2s("argName = ", argName, "argDescription = ", argDescription); //####
    ODL_D3("defaultValue = ", defaultValue, "minimumValue = ", minimumValue, //####
           "maximumValue = ", maximumValue); //####
    ODL_B2("hasMinimumValue = ", hasMinimumValue, "hasMaximumValue = ", hasMaximumValue); //####
    ODL_EXIT_P(this); //####
} // DoubleArgumentDescriptor::DoubleArgumentDescriptor

DoubleArgumentDescriptor::DoubleArgumentDescriptor
    (const DoubleArgumentDescriptor &   other) :
        inherited(other), _defaultValue(other._defaultValue), _maximumValue(other._maximumValue),
        _minimumValue(other._minimumValue), _hasMaximumValue(other._hasMaximumValue),
        _hasMinimumValue(other._hasMinimumValue)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // DoubleArgumentDescriptor::DoubleArgumentDescriptor

DoubleArgumentDescriptor::~DoubleArgumentDescriptor
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // DoubleArgumentDescriptor::~DoubleArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

SpBaseArgumentDescriptor
DoubleArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_shared<DoubleArgumentDescriptor>(*this)};

    ODL_EXIT_P(result.get());
    return result;
} // DoubleArgumentDescriptor::clone

std::string
DoubleArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{nImO::ConvertDoubleToString(_defaultValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::getDefaultValue

std::string
DoubleArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{getDefaultValue()};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::getPrintableDefaultValue

std::string
DoubleArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{nImO::ConvertDoubleToString(_currentValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::getProcessedValue

SpBaseArgumentDescriptor
DoubleArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor    result;
    StringVector                inVector;

    if (partitionString(inString, 5, inVector))
    {
        ArgumentMode    argMode;
        bool            okSoFar = true;
        double          defaultValue = 0;
        double          maxValue = 0;
        double          minValue = 0;
        std::string     name{inVector[0]};
        std::string     typeTag{inVector[1]};
        std::string     modeString{inVector[2]};
        std::string     minValString{inVector[3]};
        std::string     maxValString{inVector[4]};
        std::string     defaultString{inVector[5]};
        std::string     description{inVector[6]};

        if ("D" != typeTag)
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
            double  dblValue;

            if (nImO::ConvertToDouble(defaultString, dblValue))
            {
                minValue = defaultValue;
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar && (0 < minValString.length()))
        {
            double  dblValue;

            if (nImO::ConvertToDouble(minValString, dblValue))
            {
                minValue = dblValue;
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar && (0 < maxValString.length()))
        {
            double  dblValue;

            if (nImO::ConvertToDouble(maxValString, dblValue))
            {
                maxValue = dblValue;
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar)
        {
            bool    hasMaximumValue = (0 < maxValString.length());
            bool    hasMinimumValue = (0 < minValString.length());

            result.reset(new DoubleArgumentDescriptor(name, description, argMode, defaultValue,
                                                      hasMinimumValue, hasMinimumValue ? minValue : 0,
                                                      hasMaximumValue, hasMaximumValue ? maxValue : 0));
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // DoubleArgumentDescriptor::parseArgString

void
DoubleArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_D1("_currentValue <- ", _currentValue); //####
    ODL_OBJEXIT(); //####
} // DoubleArgumentDescriptor::setToDefaultValue

void
DoubleArgumentDescriptor::swap
    (DoubleArgumentDescriptor & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    std::swap(_currentValue, other._currentValue);
    std::swap(_defaultValue, other._defaultValue);
    std::swap(_maximumValue, other._maximumValue);
    std::swap(_minimumValue, other._minimumValue);
    std::swap(_hasMaximumValue, other._hasMaximumValue);
    std::swap(_hasMinimumValue, other._hasMinimumValue);
    ODL_OBJEXIT(); //####
} // DoubleArgumentDescriptor::swap

std::string
DoubleArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{prefixFields("D")};

    result += getParameterSeparator();
    if (_hasMinimumValue)
    {
        result += ConvertDoubleToString(_minimumValue);
    }
    result += getParameterSeparator();
    if (_hasMaximumValue)
    {
        result += ConvertDoubleToString(_maximumValue);
    }
    result += suffixFields(getDefaultValue());
    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::toString

bool
DoubleArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    double  dblValue;

    if (nImO::ConvertToDouble(value, dblValue))
    {
        setValidity(true);
        ODL_B1("_valid <- ", isValid()); //####
        if (_hasMinimumValue && (dblValue < _minimumValue))
        {
            setValidity(false);
            ODL_B1("_valid <- ", isValid()); //####
        }
        if (_hasMaximumValue && (dblValue > _maximumValue))
        {
            setValidity(false);
            ODL_B1("_valid <- ", isValid()); //####
        }
    }
    else
    {
        setValidity(false);
        ODL_B1("_valid <- ", isValid()); //####
    }
    if (isValid())
    {
        _currentValue = dblValue;
        ODL_D1("_currentValue <- ", _currentValue); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // DoubleArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

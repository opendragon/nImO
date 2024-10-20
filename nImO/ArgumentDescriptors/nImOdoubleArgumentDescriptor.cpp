//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOdoubleArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a floating
//              point command-line argument.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2015 by OpenDragon.
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

#include <ArgumentDescriptors/nImOdoubleArgumentDescriptor.h>

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
        inherited{argName, argDescription, argMode}, _defaultValue{defaultValue},
        _maximumValue{maximumValue}, _minimumValue{minimumValue}, _hasMaximumValue{hasMaximumValue},
        _hasMinimumValue{hasMinimumValue}
{
    ODL_ENTER(); //####
    ODL_S2s(argName, argDescription); //####
    ODL_I1(argMode); //####
    ODL_D3(defaultValue, minimumValue, maximumValue); //####
    ODL_B2(hasMinimumValue, hasMaximumValue); //####
    ODL_EXIT_P(this); //####
} // DoubleArgumentDescriptor::DoubleArgumentDescriptor

DoubleArgumentDescriptor::DoubleArgumentDescriptor
    (const DoubleArgumentDescriptor &   other) :
        inherited{other}, _defaultValue{other._defaultValue}, _maximumValue{other._maximumValue},
        _minimumValue{other._minimumValue}, _hasMaximumValue{other._hasMaximumValue},
        _hasMinimumValue{other._hasMinimumValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // DoubleArgumentDescriptor::DoubleArgumentDescriptor

DoubleArgumentDescriptor::DoubleArgumentDescriptor
    (DoubleArgumentDescriptor &&    other)
    noexcept :
        inherited{std::move(other)}, _defaultValue{other._defaultValue}, _maximumValue{other._maximumValue},
        _minimumValue{other._minimumValue}, _hasMaximumValue{other._hasMaximumValue},
        _hasMinimumValue{other._hasMinimumValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    other._defaultValue = other._maximumValue = other._minimumValue = 0;
    other._hasMaximumValue = other._hasMinimumValue = false;
    ODL_EXIT_P(this); //####
} // DoubleArgumentDescriptor::DoubleArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
DoubleArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<DoubleArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // DoubleArgumentDescriptor::clone

std::string
DoubleArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{inherited::describe()};

    result += ", a double with a default value of "s + getDefaultValue();
    if (_hasMinimumValue)
    {
        if (_hasMaximumValue)
        {
            result += " with a maximum of "s + ConvertDoubleToString(_maximumValue) + " and a minimum of "s +
                        ConvertDoubleToString(_minimumValue);
        }
        else
        {
            result += " and a minimum of "s + ConvertDoubleToString(_minimumValue);
        }
    }
    else
    {
        if (_hasMaximumValue)
        {
            result += " and a maximum of "s + ConvertDoubleToString(_maximumValue);
        }
    }
    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::describe

std::string
DoubleArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{nImO::ConvertDoubleToString(_defaultValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::getDefaultValue

std::string
DoubleArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{getDefaultValue()};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::getPrintableDefaultValue

std::string
DoubleArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{nImO::ConvertDoubleToString(_currentValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DoubleArgumentDescriptor::getProcessedValue

DoubleArgumentDescriptor &
DoubleArgumentDescriptor::operator=
    (const DoubleArgumentDescriptor &   other)
{
    if (this != &other)
    {
        DoubleArgumentDescriptor    temp{other};

        swap(temp);
    }
    return *this;
} // DoubleArgumentDescriptor::operator=

DoubleArgumentDescriptor &
DoubleArgumentDescriptor::operator=
    (DoubleArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _defaultValue = other._defaultValue;
        _maximumValue = other._maximumValue;
        _minimumValue = other._minimumValue;
        _hasMaximumValue = other._hasMaximumValue;
        _hasMinimumValue = other._hasMinimumValue;
        other._defaultValue = other._maximumValue = other._minimumValue = 0;
        other._hasMaximumValue = other._hasMinimumValue = false;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // DoubleArgumentDescriptor::operator=

SpBaseArgumentDescriptor
DoubleArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::DoubleTypeTag, 5, name, argMode, inVector))
    {
        bool    okSoFar{true};
        double  defaultValue{0};
        double  maxValue{0};
        double  minValue{0};
        auto    minValString{inVector[0]};
        auto    maxValString{inVector[1]};
        auto    defaultString{inVector[2]};
        auto    description{inVector[3]};

        if (defaultString.empty())
        {
            okSoFar = false;
            ODL_B1(okSoFar); //####
        }
        else
        {
            double  dblValue;

            if (ConvertToDouble(defaultString, dblValue))
            {
                minValue = defaultValue;
            }
            else
            {
                okSoFar = false;
                ODL_B1(okSoFar); //####
            }
        }
        if (okSoFar && (! minValString.empty()))
        {
            double  dblValue;

            if (ConvertToDouble(minValString, dblValue))
            {
                minValue = dblValue;
            }
            else
            {
                okSoFar = false;
                ODL_B1(okSoFar); //####
            }
        }
        if (okSoFar && (! maxValString.empty()))
        {
            double  dblValue;

            if (ConvertToDouble(maxValString, dblValue))
            {
                maxValue = dblValue;
            }
            else
            {
                okSoFar = false;
                ODL_B1(okSoFar); //####
            }
        }
        if (okSoFar)
        {
            bool    hasMaximumValue{! maxValString.empty()};
            bool    hasMinimumValue{! minValString.empty()};

            result = std::make_shared<DoubleArgumentDescriptor>(name, description, argMode, defaultValue, hasMinimumValue,
                                                                hasMinimumValue ? minValue : 0, hasMaximumValue,
                                                                hasMaximumValue ? maxValue : 0);
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
    ODL_D1(_currentValue); //####
    ODL_OBJEXIT(); //####
} // DoubleArgumentDescriptor::setToDefaultValue

void
DoubleArgumentDescriptor::swap
    (DoubleArgumentDescriptor & other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
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
    auto    result{prefixFields(ArgumentTypeTag::DoubleTypeTag) + getParameterSeparator()};

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
    ODL_S1s(value); //####
    double  dblValue;

    if (ConvertToDouble(value, dblValue))
    {
        setValidity(true);
        ODL_B1(isValid()); //####
        if (_hasMinimumValue && (dblValue < _minimumValue))
        {
            setValidity(false);
            ODL_B1(isValid()); //####
        }
        if (_hasMaximumValue && (dblValue > _maximumValue))
        {
            setValidity(false);
            ODL_B1(isValid()); //####
        }
    }
    else
    {
        setValidity(false);
        ODL_B1(isValid()); //####
    }
    if (isValid())
    {
        _currentValue = dblValue;
        ODL_D1(_currentValue); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // DoubleArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

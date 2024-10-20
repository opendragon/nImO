//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOintegerArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent an integer
//              command-line argument.
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

#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>

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

IntegerArgumentDescriptor::IntegerArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const int              defaultValue,
     const bool             hasMinimumValue,
     const int              minimumValue,
     const bool             hasMaximumValue,
     const int              maximumValue) :
        inherited{argName, argDescription, argMode}, _defaultValue{defaultValue},
        _maximumValue{maximumValue}, _minimumValue{minimumValue}, _hasMaximumValue{hasMaximumValue},
        _hasMinimumValue{hasMinimumValue}
{
    ODL_ENTER(); //####
    ODL_S2s(argName, argDescription); //####
    ODL_I1(argMode); //####
    ODL_I3(defaultValue, minimumValue, maximumValue); //####
    ODL_B2(hasMinimumValue, hasMaximumValue); //####
    ODL_EXIT_P(this); //####
} // IntegerArgumentDescriptor::IntegerArgumentDescriptor

IntegerArgumentDescriptor::IntegerArgumentDescriptor
    (const IntegerArgumentDescriptor &  other) :
        inherited{other}, _defaultValue{other._defaultValue}, _maximumValue{other._maximumValue},
        _minimumValue{other._minimumValue}, _hasMaximumValue{other._hasMaximumValue},
        _hasMinimumValue{other._hasMinimumValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // IntegerArgumentDescriptor::IntegerArgumentDescriptor

IntegerArgumentDescriptor::IntegerArgumentDescriptor
    (IntegerArgumentDescriptor &&   other)
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
} // IntegerArgumentDescriptor::IntegerArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
IntegerArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<IntegerArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // IntegerArgumentDescriptor::clone

std::string
IntegerArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{inherited::describe()};

    result += ", an integer with a default value of "s + getDefaultValue();
    if (_hasMinimumValue)
    {
        if (_hasMaximumValue)
        {
            result += " with a maximum of "s + std::to_string(_maximumValue) + " and a minimum of "s +
                        std::to_string(_minimumValue);
        }
        else
        {
            result += " and a minimum of "s + std::to_string(_minimumValue);
        }
    }
    else
    {
        if (_hasMaximumValue)
        {
            result += " and a maximum of "s + std::to_string(_maximumValue);
        }
    }
    ODL_OBJEXIT_s(result); //####
    return result;
} // IntegerArgumentDescriptor::describe

std::string
IntegerArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{std::to_string(_defaultValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // IntegerArgumentDescriptor::getDefaultValue

std::string
IntegerArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{getDefaultValue()};

    ODL_OBJEXIT_s(result); //####
    return result;
} // IntegerArgumentDescriptor::getPrintableDefaultValue

std::string
IntegerArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{std::to_string(_currentValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // IntegerArgumentDescriptor::getProcessedValue

IntegerArgumentDescriptor &
IntegerArgumentDescriptor::operator=
    (const IntegerArgumentDescriptor &  other)
{
    if (this != &other)
    {
        IntegerArgumentDescriptor   temp{other};

        swap(temp);
    }
    return *this;
} // IntegerArgumentDescriptor::operator=

IntegerArgumentDescriptor &
IntegerArgumentDescriptor::operator=
    (IntegerArgumentDescriptor &&   other)
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
} // IntegerArgumentDescriptor::operator=

SpBaseArgumentDescriptor
IntegerArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::IntegerTypeTag, 5, name, argMode, inVector))
    {
        bool    okSoFar{true};
        int     defaultValue{0};
        int     maxValue;
        int     minValue{0};
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
            int64_t intValue;

            if (ConvertToInt64(defaultString, intValue))
            {
                defaultValue = StaticCast(int, intValue);
            }
            else
            {
                okSoFar = false;
                ODL_B1(okSoFar); //####
            }
        }
        if (okSoFar && (! minValString.empty()))
        {
            int64_t intValue;

            if (ConvertToInt64(minValString, intValue))
            {
                minValue = StaticCast(int, intValue);
            }
            else
            {
                okSoFar = false;
                ODL_B1(okSoFar); //####
            }
        }
        if (okSoFar && (! maxValString.empty()))
        {
            int64_t intValue;

            if (ConvertToInt64(maxValString, intValue))
            {
                maxValue = StaticCast(int, intValue);
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

            result = std::make_shared<IntegerArgumentDescriptor>(name, description, argMode, defaultValue, hasMinimumValue,
                                                                 hasMinimumValue ? minValue : 0, hasMaximumValue,
                                                                 hasMaximumValue ? maxValue : 0);
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // IntegerArgumentDescriptor::parseArgString

void
IntegerArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_I1(_currentValue); //####
    ODL_OBJEXIT(); //####
} // IntegerArgumentDescriptor::setToDefaultValue

void
IntegerArgumentDescriptor::swap
    (IntegerArgumentDescriptor &    other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    inherited::swap(other);
    std::swap(_defaultValue, other._defaultValue);
    std::swap(_currentValue, other._currentValue);
    std::swap(_maximumValue, other._maximumValue);
    std::swap(_minimumValue, other._minimumValue);
    std::swap(_hasMaximumValue, other._hasMaximumValue);
    std::swap(_hasMinimumValue, other._hasMinimumValue);
    ODL_OBJEXIT(); //####
} // IntegerArgumentDescriptor::swap

std::string
IntegerArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{prefixFields(ArgumentTypeTag::IntegerTypeTag) + getParameterSeparator()};

    if (_hasMinimumValue)
    {
        result += std::to_string(_minimumValue);
    }
    result += getParameterSeparator();
    if (_hasMaximumValue)
    {
        result += std::to_string(_maximumValue);
    }
    result += suffixFields(getDefaultValue());
    ODL_OBJEXIT_s(result); //####
    return result;
} // IntegerArgumentDescriptor::toString

bool
IntegerArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    ODL_S1s(value); //####
    int64_t intValue;

    if (ConvertToInt64(value, intValue))
    {
        setValidity(true);
        ODL_B1(isValid()); //####
        if (_hasMinimumValue && (intValue < _minimumValue))
        {
            setValidity(false);
            ODL_B1(isValid()); //####
        }
        if (_hasMaximumValue && (intValue > _maximumValue))
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
        _currentValue = StaticCast(int, intValue);
        ODL_I1(_currentValue); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // IntegerArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

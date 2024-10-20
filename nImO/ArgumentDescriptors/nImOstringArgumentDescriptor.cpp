//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOstringArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
//              string-type command-line argument.
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

#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>

#include <string>

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

StringArgumentDescriptor::StringArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const std::string &    defaultValue) :
        inherited{argName, argDescription, argMode}, _defaultValue{defaultValue}
{
    ODL_ENTER(); //####
    ODL_S3s(argName, argDescription, defaultValue); //####
    ODL_I1(argMode); //####
    ODL_EXIT_P(this); //####
} // StringArgumentDescriptor::StringArgumentDescriptor

StringArgumentDescriptor::StringArgumentDescriptor
    (const StringArgumentDescriptor &   other) :
        inherited{other}, _currentValue{other._currentValue}, _defaultValue{other._defaultValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // StringArgumentDescriptor::StringArgumentDescriptor

StringArgumentDescriptor::StringArgumentDescriptor
    (StringArgumentDescriptor &&    other)
    noexcept :
        inherited{std::move(other)}, _currentValue{std::move(other._currentValue)},
        _defaultValue{std::move(other._defaultValue)}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // StringArgumentDescriptor::StringArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
StringArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<StringArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // StringArgumentDescriptor::clone

std::string
StringArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{inherited::describe()};

    result += ", a string with a default value of "s + getDefaultValue();
    ODL_OBJEXIT_s(result); //####
    return result;
} // StringArgumentDescriptor::describe

std::string
StringArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{_defaultValue};

    ODL_OBJEXIT_s(result); //####
    return result;
} // StringArgumentDescriptor::getDefaultValue

std::string
StringArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{"\""s + getDefaultValue() + "\""s};

    ODL_OBJEXIT_s(result); //####
    return result;
} // StringArgumentDescriptor::getPrintableDefaultValue

std::string
StringArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_s(_currentValue); //####
    return _currentValue;
} // StringArgumentDescriptor::getProcessedValue

StringArgumentDescriptor &
StringArgumentDescriptor::operator=
    (const StringArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        StringArgumentDescriptor    temp{other};

        swap(temp);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // StringArgumentDescriptor::operator=

StringArgumentDescriptor &
StringArgumentDescriptor::operator=
    (StringArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _currentValue = std::move(other._currentValue);
        _defaultValue = std::move(other._defaultValue);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // StringArgumentDescriptor::operator=

SpBaseArgumentDescriptor
StringArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::StringTypeTag, 3, name, argMode, inVector))
    {
        auto    defaultString{inVector[0]};
        auto    description{inVector[1]};

        result = std::make_shared<StringArgumentDescriptor>(name, description, argMode, defaultString);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // StringArgumentDescriptor::parseArgString

void
StringArgumentDescriptor::setCurrentValue
    (const std::string &    newValue)
{
    ODL_OBJENTER(); //####
    ODL_S1s(newValue); //####
    _currentValue = newValue;
    ODL_OBJEXIT(); //####
} // StringArgumentDescriptor::setCurrentValue

void
StringArgumentDescriptor::setDefaultValue
    (const std::string &    newValue)
{
    ODL_OBJENTER(); //####
    ODL_S1s(newValue); //####
    _defaultValue = newValue;
    ODL_OBJEXIT(); //####
} // StringArgumentDescriptor::setDefaultValue

void
StringArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_S1s(_currentValue); //####
    ODL_OBJEXIT(); //####
} // StringArgumentDescriptor::setToDefaultValue

void
StringArgumentDescriptor::swap
    (StringArgumentDescriptor & other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    inherited::swap(other);
    std::swap(_currentValue, other._currentValue);
    std::swap(_defaultValue, other._defaultValue);
    ODL_OBJEXIT(); //####
} // StringArgumentDescriptor::swap

std::string
StringArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{prefixFields(ArgumentTypeTag::StringTypeTag)};

    result += suffixFields(_defaultValue);
    ODL_OBJEXIT_s(result); //####
    return result;
} // StringArgumentDescriptor::toString

bool
StringArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    ODL_S1s(value); //####
    setValidity(true);
    ODL_B1(isValid()); //####
    if (isValid())
    {
        _currentValue = value;
        ODL_S1s(_currentValue); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // StringArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

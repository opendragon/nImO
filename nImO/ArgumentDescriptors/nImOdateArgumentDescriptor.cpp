//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOdateArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a date
//              command-line argument.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-05-27
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOdateArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a date
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

DateArgumentDescriptor::DateArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const std::string &    defaultValue) :
        inherited{argName, argDescription, argMode}
{
    ODL_ENTER(); //####
    ODL_S3s(argName, argDescription, defaultValue); //####
    ODL_I1(argMode); //####
    setValidity(setDefaultValue(defaultValue));
    ODL_B1(isValid()); //####
    ODL_EXIT_P(this); //####
} // DateArgumentDescriptor::DateArgumentDescriptor

DateArgumentDescriptor::DateArgumentDescriptor
    (const DateArgumentDescriptor &  other) :
        inherited{other}, _currentValue(other._currentValue)
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // DateArgumentDescriptor::DateArgumentDescriptor

DateArgumentDescriptor::DateArgumentDescriptor
    (DateArgumentDescriptor &&   other)
    noexcept :
        inherited{std::move(other)}, _currentValue{other._currentValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    other._currentValue = 0;
    ODL_EXIT_P(this); //####
} // DateArgumentDescriptor::DateArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
DateArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<DateArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // DateArgumentDescriptor::clone

std::string
DateArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{BaseArgumentDescriptor::describe()};

    result += ", a date "s;
    ODL_OBJEXIT_s(result); //####
    return result;
} // DateArgumentDescriptor::describe

std::string
DateArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{ConvertDateToString(_defaultValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DateArgumentDescriptor::getDefaultValue

std::string
DateArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{getDefaultValue()};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DateArgumentDescriptor::getPrintableDefaultValue

std::string
DateArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{ConvertDateToString(_currentValue)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DateArgumentDescriptor::getProcessedValue

DateArgumentDescriptor &
DateArgumentDescriptor::operator=
    (const DateArgumentDescriptor &   other)
{
    if (this != &other)
    {
        DateArgumentDescriptor   temp{other};

        swap(temp);
    }
    return *this;
} // DateArgumentDescriptor::operator=

DateArgumentDescriptor &
DateArgumentDescriptor::operator=
    (DateArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _currentValue = other._currentValue;
        other._currentValue = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // DateArgumentDescriptor::operator=

SpBaseArgumentDescriptor
DateArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::DateTypeTag, 3, name, argMode, inVector))
    {
        bool                okSoFar{true};
        auto                defaultString{inVector[0]};
        auto                description{inVector[1]};
        Date::DatePieces    pieces;

        okSoFar = GetDatePieces(pieces, defaultString);
        ODL_B1(okSoFar); //####
        if (okSoFar)
        {
            result = std::make_shared<DateArgumentDescriptor>(name, description, argMode, defaultString);
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // DateArgumentDescriptor::parseArgString

bool
DateArgumentDescriptor::setCurrentValue
    (const std::string &    newValue)
{
    ODL_OBJENTER(); //####
    ODL_S1s(newValue); //####
    Date::DatePieces    pieces;
    bool                okSoFar = GetDatePieces(pieces, newValue);

    ODL_B1(okSoFar); //####
    if (okSoFar)
    {
        _currentValue = MakeDateValue(pieces);
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // DateArgumentDescriptor::setCurrentValue

bool
DateArgumentDescriptor::setDefaultValue
    (const std::string &    newValue)
{
    ODL_OBJENTER(); //####
    ODL_S1s(newValue); //####
    Date::DatePieces    pieces;
    bool                okSoFar = GetDatePieces(pieces, newValue);

    ODL_B1(okSoFar); //####
    if (okSoFar)
    {
        _defaultValue = MakeDateValue(pieces);
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // DateArgumentDescriptor::setDefaultValue

void
DateArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_I1(_currentValue); //####
    ODL_OBJEXIT(); //####
} // DateArgumentDescriptor::setToDefaultValue

void
DateArgumentDescriptor::swap
    (DateArgumentDescriptor &    other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    inherited::swap(other);
    std::swap(_currentValue, other._currentValue);
    ODL_OBJEXIT(); //####
} // DateArgumentDescriptor::swap

std::string
DateArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{prefixFields(ArgumentTypeTag::DateTypeTag) + suffixFields(getDefaultValue())};

    ODL_OBJEXIT_s(result); //####
    return result;
} // DateArgumentDescriptor::toString

bool
DateArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    ODL_S1s(value); //####
    Date::DatePieces    pieces;

    setValidity(GetDatePieces(pieces, value));
    ODL_B1(isValid()); //####
    if (isValid())
    {
        setCurrentValue(value);
        ODL_I1(getCurrentValue()); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // DateArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

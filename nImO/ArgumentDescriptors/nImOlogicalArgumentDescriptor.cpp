//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOlogicalArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a boolean
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
//  Created:    2015-08-25
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOlogicalArgumentDescriptor.h>

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

LogicalArgumentDescriptor::LogicalArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const bool             defaultValue) :
        inherited{argName, argDescription, argMode}, _defaultValue{defaultValue}
{
    ODL_ENTER(); //####
    ODL_S2s(argName, argDescription); //####
    ODL_I1(argMode); //####
    ODL_B1(defaultValue); //####
    ODL_EXIT_P(this); //####
} // LogicalArgumentDescriptor::LogicalArgumentDescriptor

LogicalArgumentDescriptor::LogicalArgumentDescriptor
    (const LogicalArgumentDescriptor & other) :
        inherited{other}, _defaultValue{other._defaultValue}, _currentValue{other._currentValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // LogicalArgumentDescriptor::LogicalArgumentDescriptor

LogicalArgumentDescriptor::LogicalArgumentDescriptor
    (LogicalArgumentDescriptor &&   other)
    noexcept :
        inherited{std::move(other)}, _defaultValue{other._defaultValue}, _currentValue{other._currentValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    other._currentValue = other._defaultValue = false;
    ODL_EXIT_P(this); //####
} // LogicalArgumentDescriptor::LogicalArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
LogicalArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<LogicalArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // LogicalArgumentDescriptor::clone

std::string
LogicalArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{inherited::describe()};

    result += ", a logical with a default value of "s + getDefaultValue();
    ODL_OBJEXIT_s(result); //####
    return result;
} // LogicalArgumentDescriptor::describe

std::string
LogicalArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{_defaultValue ? "1"s : "0"s};

    ODL_OBJEXIT_s(result); //####
    return result;
} // LogicalArgumentDescriptor::getDefaultValue

std::string
LogicalArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{_defaultValue ? "true"s : "false"s};

    ODL_OBJEXIT_s(result); //####
    return result;
} // LogicalArgumentDescriptor::getPrintableDefaultValue

std::string
LogicalArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{_currentValue ? "1"s : "0"s};

    ODL_OBJEXIT_s(result); //####
    return result;
} // LogicalArgumentDescriptor::getProcessedValue

bool
LogicalArgumentDescriptor::isLogical
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(true); //####
    return true;
} // LogicalArgumentDescriptor::isLogical

LogicalArgumentDescriptor &
LogicalArgumentDescriptor::operator=
    (const LogicalArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        LogicalArgumentDescriptor   temp{other};

        swap(temp);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // LogicalArgumentDescriptor::operator=

LogicalArgumentDescriptor &
LogicalArgumentDescriptor::operator=
    (LogicalArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _defaultValue = other._defaultValue;
        _currentValue = other._currentValue;
        other._currentValue = other._defaultValue = false;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // LogicalArgumentDescriptor::operator=

SpBaseArgumentDescriptor
LogicalArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::BoolTypeTag, 3, name, argMode, inVector))
    {
        bool    okSoFar{true};
        bool    defaultValue;
        auto    defaultString{inVector[0]};
        auto    description{inVector[1]};

        if (defaultString.empty())
        {
            okSoFar = false;
            ODL_B1(okSoFar); //####
        }
        else
        {
            if ('1' == defaultString[0])
            {
                defaultValue = true;
            }
            else
            {
                if ('0' == defaultString[0])
                {
                    defaultValue = false;
                }
                else
                {
                    okSoFar = false;
                    ODL_B1(okSoFar); //####
                }
            }
        }
        if (okSoFar)
        {
            result = std::make_shared<LogicalArgumentDescriptor>(name, description, argMode, defaultValue);
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // LogicalArgumentDescriptor::parseArgString

void
LogicalArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_B1(_currentValue); //####
    ODL_OBJEXIT(); //####
} // LogicalArgumentDescriptor::setToDefaultValue

void
LogicalArgumentDescriptor::swap
    (LogicalArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    inherited::swap(other);
    std::swap(_defaultValue, other._defaultValue);
    std::swap(_currentValue, other._currentValue);
    ODL_OBJEXIT(); //####
} // LogicalArgumentDescriptor::swap

std::string
LogicalArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{prefixFields(ArgumentTypeTag::BoolTypeTag) + suffixFields(getDefaultValue())};

    ODL_OBJEXIT_s(result); //####
    return result;
} // LogicalArgumentDescriptor::toString

bool
LogicalArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    ODL_S1s(value); //####
    bool    boolValue;
    char    firstChar{StaticCast(char, tolower(value[0]))};

    if (('0' == firstChar) || ('f' == firstChar) || ('n' == firstChar))
    {
        boolValue = false;
        setValidity(true);
        ODL_B1(isValid()); //####
    }
    else
    {
        if (('1' == firstChar) || ('t' == firstChar) || ('y' == firstChar))
        {
            boolValue = true;
            setValidity(true);
            ODL_B1(isValid()); //####
        }
        else
        {
            setValidity(false);
            ODL_B1(isValid()); //####
        }
    }
    if (isValid())
    {
        _currentValue = boolValue;
        ODL_B1(_currentValue); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // LogicalArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

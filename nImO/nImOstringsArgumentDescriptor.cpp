//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstringsArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
//              string-type command-line argument.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2020 by OpenDragon.
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
//  Created:    2020-03-07
//
//--------------------------------------------------------------------------------------------------

#include "nImOstringsArgumentDescriptor.hpp"

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

StringsArgumentDescriptor::StringsArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const std::string &    defaultValue,
     const StringSet        allowedValues) :
        inherited(argName, argDescription, argMode), _defaultValue(defaultValue), _allowedValues(allowedValues)
{
    ODL_ENTER(); //####
    ODL_S3s("argName = ", argName, "argDescription = ", argDescription, "defaultValue = ", //####
            defaultValue); //####
    ODL_EXIT_P(this); //####
} // StringsArgumentDescriptor::StringsArgumentDescriptor

StringsArgumentDescriptor::StringsArgumentDescriptor
    (const StringsArgumentDescriptor &   other) :
        inherited(other), _defaultValue(other._defaultValue), _allowedValues(other._allowedValues)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // StringsArgumentDescriptor::StringsArgumentDescriptor

StringsArgumentDescriptor::~StringsArgumentDescriptor
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // StringsArgumentDescriptor::~StringsArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

SpBaseArgumentDescriptor
StringsArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_shared<StringsArgumentDescriptor>(*this)};

    ODL_EXIT_P(result.get());
    return result;
} // StringsArgumentDescriptor::clone

std::string
StringsArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{_defaultValue};

    ODL_OBJEXIT_s(result); //####
    return result;
} // StringsArgumentDescriptor::getDefaultValue

std::string
StringsArgumentDescriptor::getPrintableDefaultValue
(void)
{
    ODL_OBJENTER(); //####
    std::string result{"\""};

    result += getDefaultValue();
    result += "\"";
    ODL_OBJEXIT_s(result); //####
    return result;
} // StringsArgumentDescriptor::getPrintableDefaultValue

std::string
StringsArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_s(_currentValue); //####
    return _currentValue;
} // StringsArgumentDescriptor::getProcessedValue

SpBaseArgumentDescriptor
StringsArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor    result;
    StringVector                inVector;

    if (partitionString(inString, 3, inVector, 4))
    {
        ArgumentMode    argMode;
        bool            okSoFar = true;
        std::string     name{inVector[0]};
        std::string     typeTag{inVector[1]};
        std::string     modeString{inVector[2]};
        std::string     defaultString{inVector[3]};
        std::string     stringList{inVector[4]};
        std::string     description{inVector[5]};

        if ("L" != typeTag)
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
            StringSet   allowedValues;

            // We need to split the input into keys.
            for ( ; 0 < stringList.length(); )
            {
                size_t  indx = stringList.find(getParameterSeparator());

                if (stringList.npos == indx)
                {
                    // Make sure to strip off any trailing newlines!
                    for (size_t ii = stringList.length(); 0 < ii; --ii)
                    {
                        if ('\n' == stringList[ii - 1])
                        {
                            stringList = stringList.substr(0, ii - 1);
                        }
                        else
                        {
                            break;

                        }
                    }
                    allowedValues.insert(stringList);
                    stringList = "";
                }
                else
                {
                    allowedValues.insert(stringList.substr(0, indx));
                    stringList = stringList.substr(indx + 1);
                }
            }
            // Copy the values in stringList into allowedValues
            result.reset(new StringsArgumentDescriptor(name, description, argMode, defaultString, allowedValues));
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // StringsArgumentDescriptor::parseArgString

void
StringsArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    _currentValue = _defaultValue;
    ODL_S1s("_currentValue <- ", _currentValue); //####
    ODL_OBJEXIT(); //####
} // StringsArgumentDescriptor::setToDefaultValue

void
StringsArgumentDescriptor::swap
    (StringsArgumentDescriptor & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    std::swap(_currentValue, other._currentValue);
    std::swap(_defaultValue, other._defaultValue);
    std::swap(_allowedValues, other._allowedValues);
    ODL_OBJEXIT(); //####
} // StringsArgumentDescriptor::swap

std::string
StringsArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{prefixFields("L")};

    result += getParameterSeparator();
    std::string scratch;

    for (auto & walker : _allowedValues)
    {
        scratch += walker;
    }
    char    delim = identifyDelimiter(scratch);

    result += delim;
    for (auto walker(_allowedValues.begin()); walker != _allowedValues.end(); ++walker)
    {
        if (walker != _allowedValues.begin())
        {
            result += getParameterSeparator();
        }
        result += *walker;
    }
    result += delim;
    result += suffixFields(_defaultValue);
    ODL_OBJEXIT_s(result); //####
    return result;
} // StringsArgumentDescriptor::toString

bool
StringsArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    setValidity(_allowedValues.find(value) != _allowedValues.end());
    ODL_B1("_valid <- ", isValid()); //####
    if (isValid())
    {
        _currentValue = value;
        ODL_S1s("_currentValue <- ", _currentValue); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // StringsArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

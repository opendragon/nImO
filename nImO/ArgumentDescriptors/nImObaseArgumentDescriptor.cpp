//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImObaseArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
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

#include <ArgumentDescriptors/nImObaseArgumentDescriptor.h>

#include <ArgumentDescriptors/nImOaddressArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOchannelArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOdateArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOdoubleArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOextraArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOlogicalArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOportArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringsArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOtimeArgumentDescriptor.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOmap.h>
#include <nImOargumentParameterKeys.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the minimal functionality required to represent a command-line
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

std::string BaseArgumentDescriptor::_parameterSeparator{"\t"s};

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

BaseArgumentDescriptor::BaseArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode) :
        _argDescription{argDescription}, _argMode{argMode}, _argName{argName}, _valid{true}
{
    ODL_ENTER(); //####
    ODL_S2s(argName, argDescription); //####
    ODL_I1(argMode); //####
    ODL_EXIT_P(this); //####
} // BaseArgumentDescriptor::BaseArgumentDescriptor

BaseArgumentDescriptor::BaseArgumentDescriptor
    (const BaseArgumentDescriptor & other) :
        _argDescription{other._argDescription}, _argMode{other._argMode}, _argName{other._argName},
        _valid{other._valid}, _wasSeen{other._wasSeen}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // BaseArgumentDescriptor::BaseArgumentDescriptor

BaseArgumentDescriptor::BaseArgumentDescriptor
    (BaseArgumentDescriptor &&  other)
    noexcept :
        _argDescription{std::move(other._argDescription)}, _argMode{std::exchange(other._argMode, ArgumentMode::Unknown)},
        _argName{std::move(other._argName)}, _valid{std::exchange(other._valid, false)}, _wasSeen{std::exchange(other._wasSeen, false)}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // BaseArgumentDescriptor::BaseArgumentDescriptor

BaseArgumentDescriptor::~BaseArgumentDescriptor
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // BaseArgumentDescriptor::~BaseArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
BaseArgumentDescriptor::addFieldsToMap
    (SpMap  theMap)
{
    ODL_OBJENTER(); //####
    ODL_P1(theMap.get());
    theMap->addValue(std::make_shared<String>(kDescriptionParameterKey), std::make_shared<String>(_argDescription));
    theMap->addValue(std::make_shared<String>(kNameParameterKey), std::make_shared<String>(_argName));
    theMap->addValue(std::make_shared<String>(kModeParameterKey), std::make_shared<Integer>(toUType(_argMode)));
    theMap->addValue(std::make_shared<String>(kTypeParameterKey), std::make_shared<String>(toUType(getType())));
    theMap->addValue(std::make_shared<String>(kCurrentValueParameterKey), std::make_shared<String>(getProcessedValue()));
    ODL_OBJEXIT(); //####
} // BaseArgumentDescriptor::addFieldsToMap

std::string
BaseArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{_argName};

    if (isOptional())
    {
        result += " (optional)"s;
    }
    else
    {
        if (isRequired())
        {
            result += " (required)"s;
        }
    }
    if (isMutable())
    {
        result += " (mutable)"s;
    }
    result += ": "s + _argDescription;
    ODL_OBJEXIT_s(result); //####
    return result;
} // BaseArgumentDescriptor::describe

char
BaseArgumentDescriptor::identifyDelimiter
    (const std::string &    valueToCheck)
{
    ODL_ENTER(); //####
    ODL_S1s(valueToCheck); //####
    static const char possibles[]{"~!@#$%^&*_-+=|;\"'?./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrtuvwxyz0123456789"};
    char              charToUse{possibles[0]};

    if (! valueToCheck.empty())
    {
        // Determine an appropriate delimiter
        for (char possible : possibles)
        {
            if (valueToCheck.npos == valueToCheck.find(possible, 0))
            {
                charToUse = possible;
                break;

            }
        }
    }
    ODL_EXIT_C(charToUse); //####
    return charToUse;
} // BaseArgumentDescriptor::identifyDelimiter

bool
BaseArgumentDescriptor::isExtra
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(false); //####
    return false;
} // BaseArgumentDescriptor::isExtra

bool
BaseArgumentDescriptor::isForFiles
    (bool & isForOutput)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&isForOutput); //####
    isForOutput = false;
    ODL_OBJEXIT_B(false); //####
    return false;
} // BaseArgumentDescriptor::isForFiles

bool
BaseArgumentDescriptor::isLogical
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(false); //####
    return false;
} // BaseArgumentDescriptor::isLogical

nImO::ArgumentMode
BaseArgumentDescriptor::modeFromString
    (const std::string &    modeString)
{
    ODL_ENTER(); //####
    ODL_S1s(modeString); //####
    ArgumentMode result{ArgumentMode::Unknown};
    int64_t      modeAsInt;

    if (ConvertToInt64(modeString, modeAsInt))
    {
        // Check that only the known bits are set!
        if (0 == (modeAsInt & ~ toUType(ArgumentMode::Mask)))
        {
            // Only known bits were set.
            result = StaticCast(ArgumentMode, modeAsInt);
        }
    }
    ODL_EXIT_I(StaticCast(int, result)); //####
    return result;
} // BaseArgumentDescriptor::modeFromString

BaseArgumentDescriptor &
BaseArgumentDescriptor::operator=
    (const BaseArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        _argDescription = other._argDescription;
        _argMode = other._argMode;
        _argName = other._argName;
        _valid = other._valid;
        _wasSeen = other._wasSeen;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // BaseArgumentDescriptor::operator=

BaseArgumentDescriptor &
BaseArgumentDescriptor::operator=
    (BaseArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        _argDescription = std::move(other._argDescription);
        _argMode = std::exchange(other._argMode, ArgumentMode::Unknown);
        _argName = std::move(other._argName);
        _valid = std::exchange(other._valid, false);
        _wasSeen = std::exchange(other._wasSeen, false);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // BaseArgumentDescriptor::operator=

bool
BaseArgumentDescriptor::partitionString
    (const std::string &    inString,
     const ArgumentTypeTag  expectedTag,
     const size_t           indexOfDefaultValue,
     std::string &          name,
     ArgumentMode &         argMode,
     StdStringVector &      result,
     const size_t           indexOfListValue)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    ODL_C1(expectedTag); //####
    ODL_I2(indexOfDefaultValue, indexOfListValue); //####
    ODL_P3(&name, &argMode, &result); //####
    bool    okSoFar{false};
    auto    workingCopy{inString};

    // We need to split the input into fields.
    result.clear();
    for (size_t fieldNumber{0}; 0 < workingCopy.length(); ++fieldNumber)
    {
        if ((indexOfDefaultValue == fieldNumber) || ((0 < indexOfListValue) && (indexOfListValue == fieldNumber)))
        {
            // The default value and list fields are special, as they have two delimiters - the inner one,
            // which is a character that is not present in the default value field, and the normal separator character.
            char    innerChar{workingCopy[0]};

            workingCopy = workingCopy.substr(1);
            if (workingCopy.empty())
            {
                break;

            }
            size_t  innerIndx{workingCopy.find(innerChar, 0)};

            if (workingCopy.npos == innerIndx) // cppcheck-suppress knownConditionTrueFalse
            {
                // Badly formatted - the matching delimiter is missing!
                break;

            }
            result.emplace_back(workingCopy.substr(0, innerIndx));
            workingCopy = workingCopy.substr(innerIndx + 1);
            if (! workingCopy.empty()) // cppcheck-suppress knownConditionTrueFalse
            {
                if (0 == workingCopy.find(_parameterSeparator))
                {
                    workingCopy = workingCopy.substr(1);
                    okSoFar = true;
                    ODL_B1(okSoFar); //####
                }
                else
                {
                    // Badly formatted - the delimiter is not followed by the separator!
                    break;

                }
            }
        }
        else
        {
            size_t  indx{workingCopy.find(_parameterSeparator)};

            if (workingCopy.npos == indx)
            {
                // Make sure to strip off any trailing newlines!
                for (size_t ii{workingCopy.length()}; 0 < ii; --ii)
                {
                    if (kEndOfLine == workingCopy[ii - 1])
                    {
                        workingCopy = workingCopy.substr(0, ii - 1);
                    }
                    else
                    {
                        break;

                    }
                }
                result.emplace_back(workingCopy);
                workingCopy = "";
            }
            else
            {
                result.emplace_back(workingCopy.substr(0, indx));
                workingCopy = workingCopy.substr(indx + 1);
            }
        }
    }
    okSoFar &= (result.size() > indexOfDefaultValue);
    if (okSoFar)
    {
        auto    typeTag{result[1]};
        auto    modeString{result[2]};

        name = result[0];
        if ((1 != typeTag.length()) || (expectedTag != StaticCast(ArgumentTypeTag, typeTag[0])))
        {
            okSoFar = false;
            ODL_B1(okSoFar); //####
        }
        if (okSoFar)
        {
            argMode = modeFromString(modeString);
            okSoFar = (ArgumentMode::Unknown != argMode);
            ODL_B1(okSoFar); //####
        }
        else
        {
            argMode = ArgumentMode::Unknown;
        }
        if (okSoFar)
        {
            result.erase(result.begin(), result.begin() + 3); // drop the first three elements
        }
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // BaseArgumentDescriptor::partitionString

std::string
BaseArgumentDescriptor::prefixFields
    (const ArgumentTypeTag  tagForField)
    const
{
    ODL_OBJENTER(); //####
    ODL_C1(tagForField); //####
    auto    result{_argName + _parameterSeparator + StaticCast(char, tagForField) + _parameterSeparator + std::to_string(toUType(_argMode))};

    ODL_OBJEXIT_s(result); //####
    return result;
} // BaseArgumentDescriptor::prefixFields

void
BaseArgumentDescriptor::setValidity
    (const bool isValid)
{
    ODL_OBJENTER(); //####
    ODL_B1(isValid); //####
    _valid = isValid;
    ODL_OBJEXIT(); //####
} // BaseArgumentDescriptor::setValidity

std::string
BaseArgumentDescriptor::suffixFields
    (const std::string &    defaultToUse)
{
    ODL_OBJENTER(); //####
    ODL_S1s(defaultToUse); //####
    char    charToUse{identifyDelimiter(defaultToUse)};
    auto    result{_parameterSeparator + charToUse + defaultToUse + charToUse + _parameterSeparator + _argDescription};

    ODL_OBJEXIT_s(result); //####
    return result;
} // BaseArgumentDescriptor::suffixFields

void
BaseArgumentDescriptor::swap
    (BaseArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    std::swap(_valid, other._valid);
    std::swap(_argDescription, other._argDescription);
    std::swap(_argName, other._argName);
    std::swap(_argMode, other._argMode);
    ODL_OBJEXIT(); //####
} // BaseArgumentDescriptor::swap

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

std::string
nImO::ArgTypeTagToArgTypeName
    (const char typeTag)
{
    ODL_ENTER(); //####
    ODL_C1(typeTag); //####
    std::string     result;
    ArgumentTypeTag candidate{typeTag};

    switch (candidate)
    {
        case ArgumentTypeTag::AddressTypeTag :
            result = "Address";
            break;

        case ArgumentTypeTag::ChannelTypeTag :
            result = "Channel";
            break;

        case ArgumentTypeTag::DateTypeTag :
            result = "Date";
            break;

        case ArgumentTypeTag::DoubleTypeTag :
            result = "Double";
            break;

        case ArgumentTypeTag::ExtraTypeTag :
            result = "Extra";
            break;

        case ArgumentTypeTag::FilePathTypeTag :
            result = "FilePath";
            break;

        case ArgumentTypeTag::IntegerTypeTag :
            result = "Integer";
            break;

        case ArgumentTypeTag::LogicalTypeTag :
            result = "Logical";
            break;

        case ArgumentTypeTag::PortTypeTag :
            result = "Port";
            break;

        case ArgumentTypeTag::StringsTypeTag :
            result = "Strings";
            break;

        case ArgumentTypeTag::StringTypeTag :
            result = "String";
            break;

        case ArgumentTypeTag::TimeTypeTag :
            result = "Time";
            break;

        default :
            break;

    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::ArgTypeTagToArgTypeName

std::string
nImO::ArgumentModeToDescription
    (const ArgumentMode argMode)
{
    ODL_ENTER(); //####
    ODL_I1(toUType(argMode)); //####
    std::string result;

    if (ArgumentMode::Unknown == argMode)
    {
        result = "Unknown"s;
    }
    else
    {
        if (ArgumentMode::Optional == (argMode & ArgumentMode::Optional))
        {
            result = "Required";
        }
        else
        {
            result = "Optional";
        }
        if (ArgumentMode::Password == (argMode & ArgumentMode::Password))
        {
            result += ",Password";
        }
        if (ArgumentMode::CaseInsensitive == (argMode & ArgumentMode::CaseInsensitive))
        {
            result += ",CaseInsensitive";
        }
        if (ArgumentMode::Mutable == (argMode & ArgumentMode::Mutable))
        {
            result += ",Mutable";
        }
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::ArgumentModeToDescription

std::string
nImO::ArgumentsToArgString
    (const DescriptorVector &   arguments)
{
    ODL_ENTER(); //####
    ODL_P1(&arguments); //####
    std::string result;
    size_t      numOptional{0};

    for (SpBaseArgumentDescriptor anArg : arguments)
    {
        if (nullptr != anArg)
        {
            if (0 < result.length())
            {
                result += " "s;
            }
            if (anArg->isOptional())
            {
                result += "["s;
                ++numOptional;
            }
            result += anArg->argumentName();
            if (anArg->isMutable())
            {
                result += "*"s;
            }
        }
    }
    if (0 < numOptional)
    {
        result += std::string(numOptional, ']');
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::ArgumentsToArgString

void
nImO::ArgumentsToDescriptionArray
    (const DescriptorVector &  arguments,
     StdStringVector &         output,
     const size_t              minSpace)
{
    ODL_ENTER(); //####
    ODL_P2(&arguments, &output); //####
    ODL_I1(minSpace); //####
    bool        sawMutable{false};
    int         nameSize{-1};
    int         optionSize{-1};
    const int   kOptionStringLen{20}; // '(Optional, default=)'

    // Determine the width of the 'name' column.
    for (SpBaseArgumentDescriptor anArg : arguments)
    {
        if (nullptr != anArg)
        {
            auto    len{StaticCast(int, anArg->argumentName().length())};

            if (nameSize < len)
            {
                nameSize = len;
            }
            if (anArg->isOptional())
            {
                len = StaticCast(int, anArg->getPrintableDefaultValue().length());
                if (optionSize < len)
                {
                    optionSize = len;
                }
            }
            if (anArg->isMutable())
            {
                sawMutable = true;
            }
        }
    }
    if (0 < nameSize)
    {
        nameSize += StaticCast(int, minSpace) + (sawMutable ? 1 : 0);
        if (0 < optionSize)
        {
            optionSize += StaticCast(int, minSpace);
        }
        for (SpBaseArgumentDescriptor anArg : arguments)
        {
            if (nullptr != anArg)
            {
                auto    aLine{anArg->argumentName()};

                if (sawMutable)
                {
                    aLine += (anArg->isMutable() ? "*"s : " "s);
                }
                aLine += std::string(nameSize - aLine.length(), ' ');
                if (0 < optionSize)
                {
                    if (anArg->isOptional())
                    {
                        auto    anOption{anArg->getPrintableDefaultValue()};

                        aLine += "(Optional, default="s + anOption + ")"s + std::string(optionSize - anOption.length(), ' ');
                    }
                    else
                    {
                        aLine += std::string(optionSize + kOptionStringLen, ' ');
                    }
                }
                aLine += anArg->argumentDescription();
                output.emplace_back(aLine);
            }
        }
    }
    ODL_EXIT(); //####
} // nImO::ArgumentsToDescriptionArray

std::string
nImO::CombineArguments
    (const DescriptorVector &   arguments,
     const std::string &        sep)
{
    ODL_ENTER(); //####
    ODL_P1(&arguments); //####
    ODL_S1s(sep); //####
    std::string result;

    for (SpBaseArgumentDescriptor anArg : arguments)
    {
        if (nullptr != anArg)
        {
            if (0 < result.length())
            {
                result += sep;
            }
            result += anArg->getProcessedValue();
        }
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::CombineArguments

SpBaseArgumentDescriptor
nImO::ConvertStringToDescriptor
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    auto    result{AddressArgumentDescriptor::parseArgString(inString)};

    if (! result)
    {
        result = ChannelArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = DateArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = DoubleArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = ExtraArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = FilePathArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = IntegerArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = LogicalArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = PortArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = StringArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = StringsArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = TimeArgumentDescriptor::parseArgString(inString);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::ConvertStringToDescriptors

bool
nImO::ProcessAnArgument
    (SpBaseArgumentDescriptor   anArg,
     const std::string &        argValue)
{
    ODL_ENTER(); //####
    ODL_P1(anArg.get()); //####
    bool    result{true};

    anArg->setToDefaultValue();
    if (anArg->validate(argValue))
    {
        anArg->markSeen();
    }
    else
    {
        result = false;
        ODL_B1(result); //####
    }
    ODL_EXIT_B(result); //####
    return result;
} // nImO::ProcessAnArgument

bool
nImO::ProcessArguments
    (const DescriptorVector &   arguments,
     Option_::Parser &          parseResult,
     std::string &              badArgs)
{
    ODL_ENTER(); //####
    ODL_P3(&arguments, &parseResult, &badArgs); //####
    bool    result{true};
    bool    sawExtra{false};
    bool    sawOptional{false};
    size_t  numArgs{arguments.size()};
    auto    numValues{StaticCast(size_t, parseResult.nonOptionsCount())};
    size_t  numToCheck{std::min(numArgs, numValues)};

    ODL_I3(numArgs, numValues, numToCheck); //####
    // Set all arguments to their default values, so that they are all defined.
    badArgs = ""s;
    for (SpBaseArgumentDescriptor anArg : arguments)
    {
        if (nullptr != anArg)
        {
            anArg->setToDefaultValue();
        }
    }
    // Check if there are required arguments after optional arguments or the trailing argument placeholders.
    // Note that we don't care how many trailing argument placeholders there are, but they must
    // follow the optional arguments, which follow the mandatory ones.
    for (SpBaseArgumentDescriptor anArg : arguments)
    {
        if (nullptr != anArg)
        {
            ODL_LOG("(nullptr != anArg)"); //####
            if (anArg->isExtra())
            {
                ODL_LOG("(anArg->isExtra())"); //####
                sawExtra = true;
            }
            else
            {
                if (anArg->isOptional())
                {
                    ODL_LOG("(anArg->isOptional())"); //####
                    result = (! sawExtra);
                    ODL_B1(result); //####
                    sawOptional = true;
                }
                else
                {
                    result = ((! sawOptional) && (! sawExtra));
                    ODL_B1(result); //####
                }
            }
            if (! result)
            {
                break;

            }
        }
    }
    // Check the arguments with matching descriptions, unless it is a placeholder for extra arguments.
    if (result)
    {
        for (size_t ii{0}; numToCheck > ii; ++ii)
        {
            auto    anArg{arguments[ii]};

            if ((nullptr != anArg) && (! anArg->isExtra()))
            {
                ODL_LOG("((nullptr != anArg) && (! anArg->isExtra()))"); //####
                if (anArg->validate(parseResult.nonOption(StaticCast(int, ii))))
                {
                    anArg->markSeen();
                }
                else
                {
                    if (! badArgs.empty())
                    {
                        badArgs += ", "s;
                    }
                    badArgs += anArg->argumentName();
                    result = false;
                    ODL_B1(result); //####
                }
            }
        }
    }
    // Check the unmatched descriptions: if extra, just skip since it is a placeholder for trailing
    // arguments; if optional, use the default and if neither extra nor optional it's mandatory and
    // unsatisfied.
    for (size_t ii{numToCheck}; numArgs > ii; ++ii)
    {
        auto    anArg{arguments[ii]};

        if ((nullptr != anArg) && (! anArg->isExtra()))
        {
            ODL_LOG("((nullptr != anArg) && (! anArg->isExtra()))"); //####
            ODL_I1(anArg->argumentMode()); //####
            if (! anArg->isOptional())
            {
                ODL_LOG("(! anArg->isOptional())"); //####
                if (! badArgs.empty())
                {
                    badArgs += ", "s;
                }
                badArgs += anArg->argumentName();
                result = false;
                ODL_B1(result); //####
            }
        }
    }
    ODL_EXIT_B(result); //####
    return result;
} // nImO::ProcessArguments

bool
nImO::PromptForValues
    (const DescriptorVector &   arguments)
{
    ODL_ENTER(); //####
    ODL_P1(&arguments); //####
    bool    result{true};
    char    inChar;

    for (size_t ii{0}, mm{arguments.size()}; mm > ii; ++ii)
    {
        auto    anArg{arguments[ii]};

        if ((nullptr != anArg) && (! anArg->isExtra()))
        {
            auto        currentValue{anArg->getProcessedValue()};
            auto        defaultValue{anArg->getDefaultValue()};
            std::string inputLine{};

            std::cout << "\t" << anArg->argumentDescription() << " (default=" << defaultValue << ", current=" << currentValue << "): ";
            std::cout.flush();
            // Eat whitespace until we get something useful.
            for ( ; ; )
            {
                inChar = std::cin.peek();
                if (isspace(inChar))
                {
                    // Eat it.
                    if (kEndOfLine == inChar)
                    {
                        break;

                    }
                    std::cin.get();
                }
                else
                {
                    break;

                }
                if (! std::cin)
                {
                    break;

                }
            }
            if (getline(std::cin, inputLine))
            {
                if (inputLine.empty())
                {
                    if (anArg->isOptional())
                    {
                        inputLine = defaultValue;
                        if (mm > (ii + 1))
                        {
                            std::cout << "An empty optional value has been entered.\n"
                                            "The remaining arguments will be set to their defaults.\n";
                        }
                        if (! anArg->validate(inputLine))
                        {
                            result = false;
                        }
                        break;

                    }
                    else
                    {
                        if (currentValue.empty())
                        {
                            inputLine = defaultValue;
                        }
                        else
                        {
                            inputLine = currentValue;
                        }
                    }
                }
                if (! anArg->validate(inputLine))
                {
                    std::cout << "The value supplied does not meet the criteria for the parameter.\n";
                    result = false;
                }
            }
        }
    }
    ODL_EXIT_B(result); //####
    return result;
} // nImO::PromptForValues

std::string
nImO::ReformatString
    (const std::string &    inString,
     const char             typeChar)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    ODL_C1(typeChar); //####
    std::string result{};

    switch (StaticCast(ArgumentTypeTag, typeChar))
    {
        case ArgumentTypeTag::DoubleTypeTag :
            result = inString;
            break;

        case ArgumentTypeTag::IntegerTypeTag :
        case ArgumentTypeTag::PortTypeTag :
            result = inString;
            break;

        case ArgumentTypeTag::LogicalTypeTag :
            result = (('1' == inString[0]) ? "true" : "false");
            break;

        default :
            result = CHAR_DOUBLEQUOTE_ + SanitizeString(inString) + CHAR_DOUBLEQUOTE_;
            break;

    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::ReformatString

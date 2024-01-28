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
#include <ArgumentDescriptors/nImOdoubleArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOextraArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOlogicalArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOportArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringsArgumentDescriptor.h>

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
    ODL_S2s("argName = ", argName, "argDescription = ", argDescription); //####
    ODL_I1("argMode = ", StaticCast(int64_t, argMode)); //####
    ODL_EXIT_P(this); //####
} // BaseArgumentDescriptor::BaseArgumentDescriptor

BaseArgumentDescriptor::BaseArgumentDescriptor
    (const BaseArgumentDescriptor & other) :
        _argDescription{other._argDescription}, _argMode{other._argMode}, _argName{other._argName},
        _valid{other._valid}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // BaseArgumentDescriptor::BaseArgumentDescriptor

BaseArgumentDescriptor::BaseArgumentDescriptor
    (BaseArgumentDescriptor &&  other)
    noexcept :
        _argDescription{other._argDescription}, _argMode{other._argMode}, _argName{other._argName},
        _valid{other._valid}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._argDescription = other._argName = "";
    other._argMode = ArgumentMode::Unknown;
    other._valid = false;
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
    else if (isRequired())
    {
        result += " (required)"s;
    }
    result += ": "s + _argDescription;
    ODL_OBJEXIT_s(result); //####
    return result;
} // BaseArgumentDescriptor::describe

char
BaseArgumentDescriptor::identifyDelimiter
    (const std::string &    valueToCheck)
{
    static const char possibles[]{"~!@#$%^&*_-+=|;\"'?./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrtuvwxyz0123456789"};
    char              charToUse{possibles[0]};

    if (! valueToCheck.empty())
    {
        // Determine an appropriate delimiter
        for (size_t ii = 0, mm = sizeof(possibles); mm > ii; ++ii)
        {
            if (valueToCheck.npos == valueToCheck.find(possibles[ii], 0))
            {
                charToUse = possibles[ii];
                break;

            }
        }
    }
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
    ODL_P1("isForOutput = ", &isForOutput); //####
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
    ODL_S1s("modeString = ", modeString); //####
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
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _argDescription = other._argDescription;
        _argMode = other._argMode;
        _argName = other._argName;
        _valid = other._valid;
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
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        _argDescription = std::move(other._argDescription);
        _argMode = other._argMode;
        _argName = std::move(other._argName);
        _valid = other._valid;
        other._argMode = ArgumentMode::Unknown;
        other._valid = false;
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
    ODL_S1s("inString = ", inString); //####
    ODL_C1("expectedTag = ", expectedTag); //####
    ODL_I2("indexOfDefaultValue = ", indexOfDefaultValue, "indexOfListValue = ", indexOfListValue); //####
    ODL_P3("name = ", &name, "argMode = ", &argMode, "result = ", &result); //####
    bool    okSoFar{false};
    auto    workingCopy{inString};

    // We need to split the input into fields.
    result.clear();
    for (size_t fieldNumber = 0; 0 < workingCopy.length(); ++fieldNumber)
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

            if (workingCopy.npos == innerIndx)
            {
                // Badly formatted - the matching delimiter is missing!
                break;

            }
            result.emplace_back(workingCopy.substr(0, innerIndx));
            workingCopy = workingCopy.substr(innerIndx + 1);
            if (! workingCopy.empty())
            {
                if (0 == workingCopy.find(_parameterSeparator))
                {
                    workingCopy = workingCopy.substr(1);
                    okSoFar = true;
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
                for (size_t ii = workingCopy.length(); 0 < ii; --ii)
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
        }
        if (okSoFar)
        {
            argMode = modeFromString(modeString);
            okSoFar = (ArgumentMode::Unknown != argMode);
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
    ODL_C1("tagForField = ", tagForField); //####
    auto    result{_argName + _parameterSeparator + StaticCast(char, tagForField) + _parameterSeparator + std::to_string(toUType(_argMode))};

    ODL_OBJEXIT_s(result); //####
    return result;
} // BaseArgumentDescriptor::prefixFields

void
BaseArgumentDescriptor::setValidity
    (const bool isValid)
{
    ODL_OBJENTER(); //####
    ODL_B1("isValid = ", isValid); //####
    _valid = isValid;
    ODL_OBJEXIT(); //####
} // BaseArgumentDescriptor::setValidity

std::string
BaseArgumentDescriptor::suffixFields
    (const std::string &    defaultToUse)
{
    ODL_OBJENTER(); //####
    ODL_S1s("defaultToUse = ", defaultToUse); //####
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
    ODL_P1("other = ", &other); //####
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
nImO::ArgumentsToArgString
    (const DescriptorVector &   arguments)
{
    ODL_ENTER(); //####
    ODL_P1("arguments = ", &arguments); //####
    std::string result;
    size_t      numOptional{0};

    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        auto    anArg{arguments[ii]};

        if (nullptr != anArg)
        {
            if (0 < ii)
            {
                result += " "s;
            }
            if (anArg->isOptional())
            {
                result += "["s;
                ++numOptional;
            }
            result += anArg->argumentName();
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
     StdStringVector &              output,
     const size_t                   minSpace)
{
    ODL_ENTER(); //####
    ODL_P2("arguments = ", &arguments, "output = ", &output); //####
    ODL_I1("minSpace = ", minSpace); //####
    int       nameSize{-1};
    int       optionSize{-1};
    const int kOptionStringLen{20}; // '(Optional, default=)'

    // Determine the width of the 'name' column.
    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        auto    anArg{arguments[ii]};

        if (nullptr != anArg)
        {
            int len{StaticCast(int, anArg->argumentName().length())};

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
        }
    }
    if (0 < nameSize)
    {
        nameSize += StaticCast(int, minSpace);
        if (0 < optionSize)
        {
            optionSize += StaticCast(int, minSpace);
        }
        for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
        {
            auto    anArg{arguments[ii]};

            if (nullptr != anArg)
            {
                auto    aLine{anArg->argumentName()};

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
    ODL_P1("arguments = ", &arguments); //####
    ODL_S1s("sep = ", sep); //####
    std::string result;

    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        auto    anArg{arguments[ii]};

        if (0 < ii)
        {
            result += sep;
        }
        if (nullptr != anArg)
        {
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
    ODL_S1s("inString = ", inString); //####
    auto    result{AddressArgumentDescriptor::parseArgString(inString)};

    if (nullptr == result)
    {
        result = LogicalArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = ChannelArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = DoubleArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = ExtraArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = FilePathArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = IntegerArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = PortArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = StringArgumentDescriptor::parseArgString(inString);
    }
    if (nullptr == result)
    {
        result = StringsArgumentDescriptor::parseArgString(inString);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::ConvertStringToDescriptors

bool
nImO::ProcessArguments
    (const DescriptorVector &   arguments,
     Option_::Parser &          parseResult,
     std::string &              badArgs)
{
    ODL_ENTER(); //####
    ODL_P3("arguments = ", &arguments, "parseResult = ", &parseResult, "badArgs = ", &badArgs); //####
    bool   result{true};
    bool   sawExtra{false};
    bool   sawOptional{false};
    size_t numArgs{arguments.size()};
    size_t numValues{StaticCast(size_t, parseResult.nonOptionsCount())};
    size_t numToCheck{std::min(numArgs, numValues)};

    ODL_I3("numArgs <- ", numArgs, "numValues <-", numValues, "numToCheck <- ", numToCheck); //####
    // Set all arguments to their default values, so that they are all defined.
    badArgs = ""s;
    for (size_t ii = 0; numArgs > ii; ++ii)
    {
        auto    anArg{arguments[ii]};

        if (nullptr != anArg)
        {
            anArg->setToDefaultValue();
        }
    }
    // Check if there are required arguments after optional arguments or the trailing argument placeholders.
    // Note that we don't care how many trailing argument placeholders there are, but they must
    // follow the optional arguments, which follow the mandatory ones.
    for (size_t ii = 0; result && (numArgs > ii); ++ii)
    {
        auto    anArg{arguments[ii]};

        if (nullptr != anArg)
        {
            ODL_LOG("(nullptr != anArg)"); //####
            if (anArg->isExtra())
            {
                ODL_LOG("(anArg->isExtra())"); //####
                sawExtra = true;
            }
            else if (anArg->isOptional())
            {
                ODL_LOG("(anArg->isOptional())"); //####
                result = (! sawExtra);
                ODL_B1("result <- ", result); //####
                sawOptional = true;
            }
            else
            {
                result = (! sawOptional) && (! sawExtra);
                ODL_B1("result <- ", result); //####
            }
        }
    }
    // Check the arguments with matching descriptions, unless it is a placeholder for extra arguments.
    if (0 != result)
    {
        for (size_t ii = 0; numToCheck > ii; ++ii)
        {
            auto    anArg{arguments[ii]};

            if ((nullptr != anArg) && (! anArg->isExtra()))
            {
                ODL_LOG("((nullptr != anArg) && (! anArg->isExtra()))"); //####
                if (! anArg->validate(parseResult.nonOption(StaticCast(int, ii))))
                {
                    if (! badArgs.empty())
                    {
                        badArgs += ", "s;
                    }
                    badArgs += anArg->argumentName();
                    result = false;
                    ODL_B1("result <- ", result); //####
                }
            }
        }
    }
    // Check the unmatched descriptions: if extra, just skip since it is a placeholder for trailing
    // arguments; if optional, use the default and if neither extra nor optional it's mandatory and
    // unsatisfied.
    for (size_t ii = numToCheck; numArgs > ii; ++ii)
    {
        auto    anArg{arguments[ii]};

        if ((nullptr != anArg) && (! anArg->isExtra()))
        {
            ODL_LOG("((nullptr != anArg) && (! anArg->isExtra()))"); //####
            ODL_I1("arg mode = ", anArg->argumentMode()); //####
            if (! anArg->isOptional())
            {
                ODL_LOG("(! anArg->isOptional())"); //####
                if (! badArgs.empty())
                {
                    badArgs += ", "s;
                }
                badArgs += anArg->argumentName();
                result = false;
                ODL_B1("result <- ", result); //####
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
    ODL_P1("arguments = ", &arguments); //####
    bool    result{true};
    char    inChar;

    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
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

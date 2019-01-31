//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImObaseArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
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

#include "nImObaseArgumentDescriptor.hpp"

#include <nImOaddressArgumentDescriptor.hpp>
#include <nImOboolArgumentDescriptor.hpp>
#include <nImOchannelArgumentDescriptor.hpp>
#include <nImOdoubleArgumentDescriptor.hpp>
#include <nImOextraArgumentDescriptor.hpp>
#include <nImOfilePathArgumentDescriptor.hpp>
#include <nImOintArgumentDescriptor.hpp>
#include <nImOportArgumentDescriptor.hpp>
#include <nImOstringArgumentDescriptor.hpp>

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

std::string BaseArgumentDescriptor::_parameterSeparator("\t");

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

BaseArgumentDescriptor::BaseArgumentDescriptor(const std::string  &argName,
                                               const std::string  &argDescription,
                                               const ArgumentMode argMode) :
    _valid(true), _argDescription(argDescription), _argName(argName), _argMode(argMode)
{
    ODL_ENTER(); //####
    ODL_S2s("argName = ", argName, "argDescription = ", argDescription); //####
    ODL_EXIT_P(this); //####
} // BaseArgumentDescriptor::BaseArgumentDescriptor

BaseArgumentDescriptor::BaseArgumentDescriptor(const BaseArgumentDescriptor &other) :
    _valid(other._valid), _argDescription(other._argDescription), _argName(other._argName),
    _argMode(other._argMode)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // BaseArgumentDescriptor::BaseArgumentDescriptor

BaseArgumentDescriptor::~BaseArgumentDescriptor(void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // BaseArgumentDescriptor::~BaseArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
BaseArgumentDescriptor::isExtra(void)
const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(false); //####
    return false;
} // BaseArgumentDescriptor::isExtra

bool
BaseArgumentDescriptor::isForFiles(bool &isForOutput)
const
{
    ODL_OBJENTER(); //####
    isForOutput = false;
    ODL_OBJEXIT_B(false); //####
    return false;
} // BaseArgumentDescriptor::isForFiles

bool
BaseArgumentDescriptor::isLogical(void)
const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(false); //####
    return false;
} // BaseArgumentDescriptor::isLogical

bool
BaseArgumentDescriptor::partitionString(const std::string &inString,
                                        const size_t      indexOfDefaultValue,
                                        StringVector      &result)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    ODL_I1("indexOfDefaultValue = ", indexOfDefaultValue); //####
    ODL_P1("result = ", &result); //####
    bool        okSoFar = false;
    std::string workingCopy(inString);

    // We need to split the input into 'type and tag'
    result.clear();
    for (size_t fieldNumber = 0; 0 < workingCopy.length(); ++fieldNumber)
    {
        if (indexOfDefaultValue == fieldNumber)
        {
            // The default value field is special, as it has two delimiters - the inner one, which
            // is a character that is not present in the default value field, and the normal
            // separator character.
            char innerChar = workingCopy[0];

            workingCopy = workingCopy.substr(1);
            if (0 < workingCopy.length())
            {
                size_t innerIndx = workingCopy.find(innerChar, 0);

                if (std::string::npos == innerIndx)
                {
                    // Badly formatted - the matching delimiter is missing!
                    break;
                }

                result.emplace_back(workingCopy.substr(0, innerIndx));
                workingCopy = workingCopy.substr(innerIndx + 1);
                if (0 < workingCopy.length())
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
                break;
            }

        }
        else
        {
            size_t indx = workingCopy.find(_parameterSeparator);

            if (std::string::npos == indx)
            {
                // Make sure to strip off any trailing newlines!
                for (size_t ii = workingCopy.length(); 0 < ii; --ii)
                {
                    if ('\n' == workingCopy[ii - 1])
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
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // BaseArgumentDescriptor::partitionString

std::string
BaseArgumentDescriptor::prefixFields(const std::string &tagForField)
const
{
    ODL_OBJENTER(); //####
    ODL_S1s("tagForField = ", tagForField); //####
    std::string result(_argName);

    result += (_parameterSeparator + tagForField + _parameterSeparator +
               std::to_string(toUType(_argMode)));
    ODL_OBJEXIT_s(result); //####
    return result;
} // BaseArgumentDescriptor::prefixFields

std::string
BaseArgumentDescriptor::suffixFields(const std::string &defaultToUse)
{
    ODL_OBJENTER(); //####
    ODL_S1s("defaultToUse = ", defaultToUse); //####
    static const char possibles[] = "~!@#$%^&*_-+=|;\"'?./ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "abcdefghijklmnopqrtuvwxyz0123456789";
    char              charToUse = possibles[0];
    std::string       result(_parameterSeparator);

    if (0 < defaultToUse.length())
    {
        // Determine an appropriate delimiter
        for (size_t ii = 0, mm = sizeof(possibles); mm > ii; ++ii)
        {
            if (defaultToUse.npos == defaultToUse.find(possibles[ii], 0))
            {
                charToUse = possibles[ii];
                break;
            }

        }
    }
    result += charToUse;
    result += defaultToUse + charToUse + _parameterSeparator + _argDescription;
    ODL_OBJEXIT_s(result); //####
    return result;
} // BaseArgumentDescriptor::suffixFields

void
BaseArgumentDescriptor::swap(BaseArgumentDescriptor &other)
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
nImO::ArgumentsToArgString(const DescriptorVector &arguments)
{
    ODL_ENTER(); //####
    ODL_P1("arguments = ", &arguments); //####
    std::string result;
    size_t      numOptional = 0;

    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (anArg)
        {
            if (0 < ii)
            {
                result += " ";
            }
            if (anArg->isOptional())
            {
                result += "[";
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
nImO::ArgumentsToDescriptionArray(const DescriptorVector &arguments,
                                  StringVector           &output,
                                  const size_t           minSpace)
{
    ODL_ENTER(); //####
    ODL_P2("arguments = ", &arguments, "output = ", &output); //####
    int nameSize = -1;

    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (anArg)
        {
            int len = static_cast<int>(anArg->argumentName().length());

            if (nameSize < len)
            {
                nameSize = len;
            }
        }
    }
    if (0 < nameSize)
    {
        nameSize += static_cast<int>(minSpace);
        for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
        {
            BaseArgumentDescriptor *anArg = arguments[ii];

            if (anArg)
            {
                std::string aLine(anArg->argumentName());
                size_t      len = aLine.length();

                aLine += std::string(nameSize - len, ' ');
                if (anArg->isOptional())
                {
                    aLine += "(Optional) ";
                }
                aLine += anArg->argumentDescription();
                output.emplace_back(aLine);
            }
        }
    }
    ODL_EXIT(); //####
} // nImO::ArgumentsToDescriptionArray

std::string
nImO::CombineArguments(const DescriptorVector &arguments,
                       const std::string      &sep)
{
    ODL_ENTER(); //####
    ODL_S1s("sep = ", sep); //####
    std::string result;

    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (0 < ii)
        {
            result += sep;
        }
        if (anArg)
        {
            result += anArg->getProcessedValue();
        }
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::CombineArguments

SpBaseArgumentDescriptor
nImO::ConvertStringToArgument(const std::string &inString)
{
    ODL_ENTER(); //####
    SpBaseArgumentDescriptor result;

    result = AddressArgumentDescriptor::parseArgString(inString);
    if (! result)
    {
        result = BoolArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = ChannelArgumentDescriptor::parseArgString(inString);
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
        result = IntArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = PortArgumentDescriptor::parseArgString(inString);
    }
    if (! result)
    {
        result = StringArgumentDescriptor::parseArgString(inString);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::ConvertStringToArguments

#if 0
void
nImO::CopyArgumentsToBottle(const DescriptorVector &arguments,
                            yarp::os::Bottle       &container)
{
    ODL_ENTER(); //####
    ODL_P2("arguments = ", &arguments, "container = ", &container); //####
    container.clear();
    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (anArg && (! anArg->isRequired()) && (! anArg->isExtra()))
        {
            anArg->addValueToBottle(container);
        }
    }
    ODL_EXIT(); //####
} // nImO::CopyArgumentsToBottle
#endif//0

nImO::ArgumentMode
nImO::ModeFromString(const std::string &modeString)
{
    ODL_ENTER(); //####
    ODL_S1s("modeString = ", modeString); //####
    ArgumentMode result = ArgumentMode::Unknown;
    int64_t      modeAsInt;

    if (nImO::ConvertToInt64(modeString.c_str(), modeAsInt))
    {
        // Check that only the known bits are set!
        if (0 == (modeAsInt & ~toUType(ArgumentMode::Mask)))
        {
            // Only known bits were set.
            result = static_cast<ArgumentMode>(modeAsInt);
        }
    }
    ODL_EXIT_I(static_cast<int>(result)); //####
    return result;
} // nImO::ModeFromString

bool
nImO::ProcessArguments(const DescriptorVector &arguments,
                       Option_::Parser        &parseResult,
                       std::string            &badArgs)
{
    ODL_ENTER(); //####
    ODL_P3("arguments = ", &arguments, "parseResult = ", &parseResult, "badArgs = ", //####
           &badArgs); //####
    bool   result = true;
    bool   sawExtra = false;
    bool   sawOptional = false;
    size_t numArgs = arguments.size();
    size_t numValues = parseResult.nonOptionsCount();
    size_t numToCheck = (std::min)(numArgs, numValues);

    ODL_I3("numArgs <- ", numArgs, "numValues <-", numValues, "numToCheck <- ", numToCheck); //####
    // Set all arguments to their default values, so that they are all defined.
    badArgs = "";
    for (size_t ii = 0; numArgs > ii; ++ii)
    {
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (anArg)
        {
            anArg->setToDefaultValue();
        }
    }
    // Check if there are required arguments after optional arguments or the trailing arguments
    // placeholder.
    // Note that we don't care how many trailing arguments placeholders there are, but they must
    // follow the optional arguments, which follow the mandatory ones.
    for (size_t ii = 0; result && (numArgs > ii); ++ii)
    {
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (anArg)
        {
            ODL_LOG("(anArg)"); //####
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
    // Check the arguments with matching descriptions, unless it is a placeholder for extra
    // arguments.
    if (result)
    {
        for (size_t ii = 0; numToCheck > ii; ++ii)
        {
            BaseArgumentDescriptor *anArg = arguments[ii];

            if (anArg && (! anArg->isExtra()))
            {
                ODL_LOG("(anArg && (! anArg->isExtra()))"); //####
                if (! anArg->validate(parseResult.nonOption(static_cast<int>(ii))))
                {
                    if (0 < badArgs.length())
                    {
                        badArgs += ", ";
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
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (anArg && (! anArg->isExtra()))
        {
            ODL_LOG("(anArg && (! anArg->isExtra()))"); //####
            ODL_I1("arg mode = ", anArg->argumentMode()); //####
            if (! anArg->isOptional())
            {
                ODL_LOG("(! anArg->isOptional())"); //####
                if (0 < badArgs.length())
                {
                    badArgs += ", ";
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
nImO::PromptForValues(const DescriptorVector &arguments)
{
    ODL_ENTER(); //####
    ODL_P1("arguments = ", &arguments); //####
    bool result = true;
    char inChar;

    // Eat the trailing newline from the request.
    inChar = std::cin.peek();
    if (isspace(inChar))
    {
        // Eat it.
        if ('\n' == inChar)
        {
            std::cin.get();
        }
    }
    for (size_t ii = 0, mm = arguments.size(); mm > ii; ++ii)
    {
        BaseArgumentDescriptor *anArg = arguments[ii];

        if (anArg && (! anArg->isRequired()) && (! anArg->isExtra()))
        {
            std::string currentValue(anArg->getProcessedValue().c_str());
            std::string defaultValue(anArg->getDefaultValue().c_str());
            std::string inputLine;

            std::cout << anArg->argumentDescription().c_str();
            std::cout << " (default=" << defaultValue << ", current=" << currentValue << "): ";
            std::cout.flush();
            // Eat whitespace until we get something useful.
            for ( ; ; )
            {
                inChar = std::cin.peek();
                if (isspace(inChar))
                {
                    // Eat it.
                    if ('\n' == inChar)
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
                if (! inputLine.length())
                {
                    if (currentValue.length())
                    {
                        inputLine = currentValue;
                    }
                    else
                    {
                        inputLine = defaultValue;
                    }
                }
                if (! anArg->validate(inputLine))
                {
                    result = false;
                }
            }
        }
    }
    ODL_EXIT_B(result); //####
    return result;
} // nImO::PromptForValues

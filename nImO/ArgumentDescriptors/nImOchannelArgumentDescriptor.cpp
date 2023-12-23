//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOchannelArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
//              channel-type command-line argument.
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

#include <ArgumentDescriptors/nImOchannelArgumentDescriptor.h>

#include <nImOchannelName.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a channel-type
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

ChannelArgumentDescriptor::ChannelArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const std::string &    defaultValue) :
        inherited{argName, argDescription, argMode}, _defaultValue{defaultValue}
{
    ODL_ENTER(); //####
    ODL_S3s("argName = ", argName, "argDescription = ", argDescription, "defaultValue = ", defaultValue); //####
    ODL_I1("argMode = ", StaticCast(int64_t, argMode)); //####
    ODL_EXIT_P(this); //####
} // ChannelArgumentDescriptor::ChannelArgumentDescriptor

ChannelArgumentDescriptor::ChannelArgumentDescriptor
    (const ChannelArgumentDescriptor &  other) :
        inherited{other}, _defaultValue{other._defaultValue}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // ChannelArgumentDescriptor::ChannelArgumentDescriptor

ChannelArgumentDescriptor::ChannelArgumentDescriptor
    (ChannelArgumentDescriptor &&   other)
    noexcept :
        inherited{std::move(other)}, _currentValue{std::move(other._currentValue)},
        _defaultValue{std::move(other._defaultValue)}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // ChannelArgumentDescriptor::ChannelArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
ChannelArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<ChannelArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // ChannelArgumentDescriptor::clone

std::string
ChannelArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{_defaultValue};

    ODL_OBJEXIT_s(result); //####
    return result;
} // ChannelArgumentDescriptor::getDefaultValue

std::string
ChannelArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{_defaultValue};

    ODL_OBJEXIT_s(result); //####
    return result;
} // ChannelArgumentDescriptor::getPrintableDefaultValue

std::string
ChannelArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result;

    if (_currentValue)
    {
        result = _currentValue->getName();
    }
    ODL_OBJEXIT_s(result); //####
    return result;
} // ChannelArgumentDescriptor::getProcessedValue

ChannelArgumentDescriptor &
ChannelArgumentDescriptor::operator=
    (const ChannelArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        ChannelArgumentDescriptor   temp{other};

        swap(temp);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // ChannelArgumentDescriptor::operator=

ChannelArgumentDescriptor &
ChannelArgumentDescriptor::operator=
    (ChannelArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _currentValue = std::move(other._currentValue);
        _defaultValue = std::move(other._defaultValue);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // ChannelArgumentDescriptor::operator=

SpBaseArgumentDescriptor
ChannelArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor    result;
    StringVector                inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::ChannelTypeTag, 3, name, argMode, inVector))
    {
        std::string defaultString{inVector[0]};
        std::string description{inVector[1]};
        std::string failReason;

        if (ChannelName::parse(defaultString, failReason))
        {
            result = std::make_shared<ChannelArgumentDescriptor>(name, description, argMode, defaultString);
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // ChannelArgumentDescriptor::parseArgString

void
ChannelArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    if (_defaultValue.empty())
    {
        _currentValue.reset();
    }
    else
    {
        std::string failReason;

        _currentValue = ChannelName::parse(_defaultValue, failReason);
    }
    ODL_P1("_currentValue = ", _currentValue.get()); //####
    ODL_OBJEXIT(); //####
} // ChannelArgumentDescriptor::setToDefaultValue

void
ChannelArgumentDescriptor::swap
    (ChannelArgumentDescriptor &    other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    std::swap(_currentValue, other._currentValue);
    std::swap(_defaultValue, other._defaultValue);
    ODL_OBJEXIT(); //####
} // ChannelArgumentDescriptor::swap

std::string
ChannelArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{prefixFields(ArgumentTypeTag::ChannelTypeTag) + suffixFields(getDefaultValue())};

    ODL_OBJEXIT_s(result); //####
    return result;
} // ChannelArgumentDescriptor::toString

bool
ChannelArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    ODL_S1s("value = ", value); //####
    std::string     failReason;
    SpChannelName   trialValue{ChannelName::parse(value, failReason)};

    setValidity(nullptr != trialValue);
    ODL_B1("_valid <- ", isValid()); //####
    if (isValid())
    {
        _currentValue = trialValue;
        ODL_S1s("_currentValue <- ", _currentValue->getName()); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // ChannelArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOextraArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
//              placeholder for trailing command-line arguments.
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
//  Created:    2015-06-08
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOextraArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a placeholder for
 trailing command-line arguments. */
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

ExtraArgumentDescriptor::ExtraArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription) :
        inherited{argName, argDescription, ArgumentMode::Optional}
{
    ODL_ENTER(); //####
    ODL_S2s("argName = ", argName, "argDescription = ", argDescription); //####
    ODL_EXIT_P(this); //####
} // ExtraArgumentDescriptor::ExtraArgumentDescriptor

ExtraArgumentDescriptor::ExtraArgumentDescriptor
    (const ExtraArgumentDescriptor &    other) :
        inherited{other}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // ExtraArgumentDescriptor::ExtraArgumentDescriptor

ExtraArgumentDescriptor::ExtraArgumentDescriptor
    (ExtraArgumentDescriptor && other)
    noexcept :
        inherited{std::move(other)}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // ExtraArgumentDescriptor::ExtraArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
ExtraArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<ExtraArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // ExtraArgumentDescriptor::clone

std::string
ExtraArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{inherited::describe()};

    result += ", extra unchecked arguments"s;
    ODL_OBJEXIT_s(result); //####
    return result;
} // ExtraArgumentDescriptor::describe

std::string
ExtraArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result;

    ODL_OBJEXIT_s(result); //####
    return result;
} // ExtraArgumentDescriptor::getDefaultValue

std::string
ExtraArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{getDefaultValue()};

    ODL_OBJEXIT_s(result); //####
    return result;
} // ExtraArgumentDescriptor::getPrintableDefaultValue

std::string
ExtraArgumentDescriptor::getProcessedValue
    (void)
{
    ODL_OBJENTER(); //####
    std::string result;

    ODL_OBJEXIT_s(result); //####
    return result;
} // ExtraArgumentDescriptor::getProcessedValue

bool
ExtraArgumentDescriptor::isExtra
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(true); //####
    return true;
} // ExtraArgumentDescriptor::isExtra

ExtraArgumentDescriptor &
ExtraArgumentDescriptor::operator=
    (const ExtraArgumentDescriptor &    other)
{
    if (this != &other)
    {
        ExtraArgumentDescriptor temp{other};

        swap(temp);
    }
    return *this;
} // ExtraArgumentDescriptor::operator=

ExtraArgumentDescriptor &
ExtraArgumentDescriptor::operator=
    (ExtraArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // ExtraArgumentDescriptor::operator=

SpBaseArgumentDescriptor
ExtraArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::ExtraTypeTag, 3, name, argMode, inVector))
    {
        auto    defaultString{inVector[0]}; // ignored
        auto    description{inVector[1]};

        result = std::make_shared<ExtraArgumentDescriptor>(name, description);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // ExtraArgumentDescriptor::parseArgString

void
ExtraArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // ExtraArgumentDescriptor::setToDefaultValue

void
ExtraArgumentDescriptor::swap
    (ExtraArgumentDescriptor &  other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    ODL_OBJEXIT(); //####
} // ExtraArgumentDescriptor::swap

std::string
ExtraArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{prefixFields(ArgumentTypeTag::ExtraTypeTag) + suffixFields(""s)};

    ODL_OBJEXIT_s(result); //####
    return result;
} // ExtraArgumentDescriptor::toString

bool
ExtraArgumentDescriptor::validate
    (const std::string &    value)
{
    NIMO_UNUSED_VAR_(value);
    ODL_OBJENTER(); //####
    ODL_S1s("value = ", value); //####
    //ODL_P1("value = ", &value); //####
    setValidity(true);
    ODL_B1("_valid <- ", isValid()); //####
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // ExtraArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

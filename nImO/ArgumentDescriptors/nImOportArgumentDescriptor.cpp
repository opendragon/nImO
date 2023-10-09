//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOportArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a port
//              number command-line argument.
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
//  Created:    2015-05-21
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOportArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a port number
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

PortArgumentDescriptor::PortArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const int              defaultValue,
     const bool             isSystemPort) :
        inherited{argName, argDescription, argMode, defaultValue, true,
                    isSystemPort ? 0 : kMinimumPortAllowed, true, kMaximumPortAllowed},
        _isSystemPort{isSystemPort}
{
    ODL_ENTER(); //####
    ODL_S2s("argName = ", argName, "argDescription = ", argDescription); //####
    ODL_I2("argMode = ", StaticCast(int64_t, argMode), "defaultValue = ", defaultValue); //####
    ODL_B1("isSystemPort = ", isSystemPort); //####
    ODL_EXIT_P(this); //####
} // PortArgumentDescriptor::PortArgumentDescriptor

PortArgumentDescriptor::PortArgumentDescriptor
    (const PortArgumentDescriptor & other) :
        inherited{other}, _isSystemPort{other._isSystemPort}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // PortArgumentDescriptor::PortArgumentDescriptor

PortArgumentDescriptor::PortArgumentDescriptor
    (PortArgumentDescriptor &&  other)
    noexcept :
        inherited{std::move(other)}, _isSystemPort{other._isSystemPort}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._isSystemPort = false;
    ODL_EXIT_P(this); //####
} // PortArgumentDescriptor::PortArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
PortArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<PortArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // PortArgumentDescriptor::clone

PortArgumentDescriptor &
PortArgumentDescriptor::operator=
    (const PortArgumentDescriptor & other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        PortArgumentDescriptor  temp{other};

        swap(temp);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // PortArgumentDescriptor::operator=

PortArgumentDescriptor &
PortArgumentDescriptor::operator=
    (PortArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _isSystemPort = other._isSystemPort;
        other._isSystemPort = false;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // PortArgumentDescriptor::operator=

SpBaseArgumentDescriptor
PortArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    SpBaseArgumentDescriptor    result;
    StringVector                inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::PortTypeTag, 4, name, argMode, inVector))
    {
        bool        okSoFar{true};
        bool        isSystemPort{false};
        int         defaultValue{0};
        std::string portClass{inVector[0]};
        std::string defaultString{inVector[1]};
        std::string description{inVector[2]};

        if ("s" == portClass)
        {
            isSystemPort = true;
        }
        else if ("r" != portClass)
        {
            okSoFar = false;
        }
        if (okSoFar && (0 < defaultString.length()))
        {
            int64_t intValue;

            if (ConvertToInt64(defaultString, intValue))
            {
                defaultValue = StaticCast(int, intValue);
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar)
        {
            result = std::make_shared<PortArgumentDescriptor>(name, description, argMode, defaultValue, isSystemPort);
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // PortArgumentDescriptor::parseArgString

void
PortArgumentDescriptor::swap
    (PortArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    inherited::swap(other);
    std::swap(_isSystemPort, other._isSystemPort);
    ODL_OBJEXIT(); //####
} // PortArgumentDescriptor::swap

std::string
PortArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{prefixFields(ArgumentTypeTag::PortTypeTag) + getParameterSeparator() + (_isSystemPort ? "s"s : "r"s) +
                        suffixFields(getDefaultValue())};

    ODL_OBJEXIT_s(result); //####
    return result;
} // PortArgumentDescriptor::toString

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

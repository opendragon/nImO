//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOaddressArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent an IP
//              address command-line argument.
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
//  Created:    2015-05-17
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOaddressArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent an IP address
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

AddressArgumentDescriptor::AddressArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const std::string &    defaultValue,
     Ptr(struct in_addr)    addrBuff) :
        inherited{argName, argDescription, argMode, defaultValue}, _addrBuff{addrBuff}
{
    ODL_ENTER(); //####
    ODL_S3s(argName, argDescription, defaultValue); //####
    ODL_I1(argMode); //####
    ODL_P1(addrBuff); //####
    if (kSelfAddressName == inherited::getDefaultValue())
    {
        setDefaultValue(kSelfAddressIpAddress);
    }
    ODL_EXIT_P(this); //####
} // AddressArgumentDescriptor::AddressArgumentDescriptor

AddressArgumentDescriptor::AddressArgumentDescriptor
    (const AddressArgumentDescriptor &  other) :
        inherited{other}, _addrBuff{nullptr}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // AddressArgumentDescriptor::AddressArgumentDescriptor

AddressArgumentDescriptor::AddressArgumentDescriptor
    (AddressArgumentDescriptor &&   other)
    noexcept :
        inherited{std::move(other)}, _addrBuff{other._addrBuff}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    other._addrBuff = nullptr;
    ODL_EXIT_P(this); //####
} // AddressArgumentDescriptor::AddressArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
AddressArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<AddressArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // AddressArgumentDescriptor::clone

std::string
AddressArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{BaseArgumentDescriptor::describe()};

    result += ", an IPv4 address with a default value of "s + getDefaultValue();
    ODL_OBJEXIT_s(result); //####
    return result;
} // AddressArgumentDescriptor::describe

AddressArgumentDescriptor &
AddressArgumentDescriptor::operator=
    (const AddressArgumentDescriptor &   other)
{
    if (this != &other)
    {
        AddressArgumentDescriptor   temp{other};

        swap(temp);
    }
    return *this;
} // AddressArgumentDescriptor::operator=

AddressArgumentDescriptor &
AddressArgumentDescriptor::operator=
    (AddressArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _addrBuff = other._addrBuff;
        other._addrBuff = nullptr;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // AddressArgumentDescriptor::operator=

SpBaseArgumentDescriptor
AddressArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::AddressTypeTag, 3, name, argMode, inVector))
    {
        bool            okSoFar{true};
        auto            defaultString{inVector[0]};
        auto            description{inVector[1]};
        struct in_addr  addrBuff;

        if (kSelfAddressName == defaultString)
        {
            defaultString = kSelfAddressIpAddress;
        }
#if MAC_OR_LINUX_OR_BSD_
        okSoFar = (0 < inet_pton(AF_INET, defaultString.c_str(), &addrBuff));
#else // not MAC_OR_LINUX_OR_BSD_
        okSoFar = (0 < InetPton(AF_INET, defaultString.c_str(), &addrBuff));
#endif // not MAC_OR_LINUX_OR_BSD_
        ODL_B1(okSoFar); //####
        if (okSoFar)
        {
            result = std::make_shared<AddressArgumentDescriptor>(name, description, argMode, defaultString);
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // AddressArgumentDescriptor::parseArgString

void
AddressArgumentDescriptor::swap
    (AddressArgumentDescriptor &    other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    inherited::swap(other);
    std::swap(_addrBuff, other._addrBuff);
    ODL_OBJEXIT(); //####
} // AddressArgumentDescriptor::swap

std::string
AddressArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{prefixFields(ArgumentTypeTag::AddressTypeTag) + suffixFields(getDefaultValue())};

    ODL_OBJEXIT_s(result); //####
    return result;
} // AddressArgumentDescriptor::toString

bool
AddressArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    ODL_S1s(value); //####
    std::string testValue;

    if (kSelfAddressName == value)
    {
        testValue = kSelfAddressIpAddress;
    }
    else
    {
        testValue = value;
    }
    if (nullptr == _addrBuff)
    {
        struct in_addr  addrBuff;

#if MAC_OR_LINUX_OR_BSD_
        setValidity(0 < inet_pton(AF_INET, testValue.c_str(), &addrBuff));
#else // not MAC_OR_LINUX_OR_BSD_
        setValidity(0 < InetPton(AF_INET, testValue.c_str(), &addrBuff));
#endif // not MAC_OR_LINUX_OR_BSD_
        ODL_B1(isValid()); //####
    }
    else
    {
#if MAC_OR_LINUX_OR_BSD_
        setValidity(0 < inet_pton(AF_INET, testValue.c_str(), _addrBuff));
#else // not MAC_OR_LINUX_OR_BSD_
        setValidity(0 < InetPton(AF_INET, testValue.c_str(), _addrBuff));
#endif // not MAC_OR_LINUX_OR_BSD_
        ODL_B1(isValid()); //####
    }
    if (isValid())
    {
        setCurrentValue(testValue);
        ODL_S1s(getCurrentValue()); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // AddressArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

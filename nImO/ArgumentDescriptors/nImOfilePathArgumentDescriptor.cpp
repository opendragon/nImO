//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOfilePathArgumentDescriptor.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the minimal functionality required to represent a
//              filepath-type command-line argument.
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

#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if MAC_OR_LINUX_OR_BSD_
# include <unistd.h>
#else // not MAC_OR_LINUX_OR_BSD_
# include <io.h>
#endif // not MAC_OR_LINUX_OR_BSD_

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definition for the minimal functionality required to represent a filepath-type
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

/*! @brief Check if a file path is acceptable.
 @param[in] thePath The file path to be checked.
 @param[in] forOutput @c true if the file is to be written to and @c false otherwise.
 @param[in] emptyIsOK @c true if the file path can be empty and @c false otherwise.
 @return @c true if the file path is acceptable and @c false otherwise. */
static bool
checkFilePath
    (CPtr(char) thePath,
     const bool forOutput,
     const bool emptyIsOK)
{
    ODL_ENTER(); //####
    ODL_S1(thePath); //####
    ODL_B2(forOutput, emptyIsOK); //####
    bool    okSoFar;

    if (forOutput)
    {
        std::string dirPath{thePath};
        size_t      lastDelim{dirPath.rfind(kDirectorySeparator[0])};

        if (dirPath.npos == lastDelim)
        {
            if (0 < strlen(thePath))
            {
                okSoFar = true;
                ODL_B1(okSoFar); //####
            }
            else
            {
                okSoFar = emptyIsOK;
                ODL_B1(okSoFar); //####
            }
        }
        else
        {
            dirPath = dirPath.substr(0, lastDelim);
#if MAC_OR_LINUX_OR_BSD_
            okSoFar = (0 == access(dirPath.c_str(), W_OK));
#else // not MAC_OR_LINUX_OR_BSD_
            okSoFar = (0 == _access(dirPath.c_str(), 2));
#endif // not MAC_OR_LINUX_OR_BSD_
            ODL_B1(okSoFar); //####
        }
    }
    else
    {
        if (0 < strlen(thePath))
        {
            // The file must exist and be readable.
#if MAC_OR_LINUX_OR_BSD_
            okSoFar = (0 == access(thePath, R_OK));
#else // not MAC_OR_LINUX_OR_BSD_
            okSoFar = (0 == _access(thePath, 4));
#endif // not MAC_OR_LINUX_OR_BSD_
            ODL_B1(okSoFar); //####
        }
        else
        {
            okSoFar = emptyIsOK;
            ODL_B1(okSoFar); //####
        }
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // checkFilePath

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

FilePathArgumentDescriptor::FilePathArgumentDescriptor
    (const std::string &    argName,
     const std::string &    argDescription,
     const ArgumentMode     argMode,
     const std::string &    pathPrefix,
     const std::string &    pathSuffix,
     const bool             forOutput,
     const bool             useRandomPath) :
        inherited{argName, argDescription, argMode, pathPrefix},
        _pathPrefix{pathPrefix}, _pathSuffix{pathSuffix}, _defaultSet{false}, _forOutput{forOutput},
        _useRandomPath{useRandomPath}
{
    ODL_ENTER(); //####
    ODL_S4s(argName, argDescription, pathPrefix, pathSuffix); //####
    ODL_I1(argMode); //####
    ODL_B2(forOutput, useRandomPath); //####
    getDefaultValue();
    ODL_EXIT_P(this); //####
} // FilePathArgumentDescriptor::FilePathArgumentDescriptor

FilePathArgumentDescriptor::FilePathArgumentDescriptor
    (const FilePathArgumentDescriptor & other) :
        inherited{other}, _pathPrefix{other._pathPrefix}, _pathSuffix{other._pathSuffix},
        _defaultSet{false}, _forOutput{other._forOutput}, _useRandomPath{other._useRandomPath}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // FilePathArgumentDescriptor::FilePathArgumentDescriptor

FilePathArgumentDescriptor::FilePathArgumentDescriptor
    (FilePathArgumentDescriptor &&  other)
    noexcept :
        inherited{std::move(other)}, _pathPrefix{std::move(other._pathPrefix)},
        _pathSuffix{std::move(other._pathSuffix)}, _defaultSet{other._defaultSet}, _forOutput{other._forOutput},
        _useRandomPath{other._useRandomPath}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    other._defaultSet = other._forOutput = other._useRandomPath = false;
    ODL_EXIT_P(this); //####
} // FilePathArgumentDescriptor::FilePathArgumentDescriptor

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

UpBaseArgumentDescriptor
FilePathArgumentDescriptor::clone
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto    result{std::make_unique<FilePathArgumentDescriptor>(*this)};

    ODL_OBJEXIT_P(result.get());
    return result;
} // FilePathArgumentDescriptor::clone

std::string
FilePathArgumentDescriptor::describe
    (void)
{
    ODL_OBJENTER(); //####
    std::string result{BaseArgumentDescriptor::describe()};

    result += ", a file path for "s + (_forOutput ? "output"s : "input"s) + " with a default value of "s + getDefaultValue();
    ODL_OBJEXIT_s(result); //####
    return result;
} // FilePathArgumentDescriptor::describe

std::string
FilePathArgumentDescriptor::getDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    if (! _defaultSet)
    {
        setDefaultValue(_pathPrefix);
        ODL_S1s(inherited::getDefaultValue()); //####
        if (_useRandomPath)
        {
            setDefaultValue(inherited::getDefaultValue() + GetRandomHexString());
            ODL_S1s(inherited::getDefaultValue()); //####
        }
        setDefaultValue(inherited::getDefaultValue() + _pathSuffix);
        ODL_S1s(inherited::getDefaultValue()); //####
        _defaultSet = true;
        ODL_B1(_defaultSet); //####
    }
    ODL_OBJEXIT_s(inherited::getDefaultValue()); //####
    return inherited::getDefaultValue();
} // FilePathArgumentDescriptor::getDefaultValue

std::string
FilePathArgumentDescriptor::getPrintableDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    auto    result{getDefaultValue()};

    ODL_OBJEXIT_s(result); //####
    return result;
} // FilePathArgumentDescriptor::getPrintableDefaultValue

bool
FilePathArgumentDescriptor::isForFiles
    (bool & isForOutput)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&isForOutput); //####
    isForOutput = _forOutput;
    ODL_OBJEXIT_B(true); //####
    return true;
} // FilePathArgumentDescriptor::isForFiles

FilePathArgumentDescriptor &
FilePathArgumentDescriptor::operator=
    (const FilePathArgumentDescriptor & other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        FilePathArgumentDescriptor  temp{other};

        swap(temp);
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // FilePathArgumentDescriptor::operator=

FilePathArgumentDescriptor &
FilePathArgumentDescriptor::operator=
    (FilePathArgumentDescriptor &&   other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _pathPrefix = std::move(other._pathPrefix);
        _pathSuffix = std::move(other._pathSuffix);
        _defaultSet = other._defaultSet;
        _forOutput = other._forOutput;
        _useRandomPath = other._useRandomPath;
        other._defaultSet = other._forOutput = other._useRandomPath = false;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // FilePathArgumentDescriptor::operator=

SpBaseArgumentDescriptor
FilePathArgumentDescriptor::parseArgString
    (const std::string &    inString)
{
    ODL_ENTER(); //####
    ODL_S1s(inString); //####
    SpBaseArgumentDescriptor    result;
    StdStringVector             inVector;
    std::string                 name;
    ArgumentMode                argMode;

    if (partitionString(inString, ArgumentTypeTag::FilePathTypeTag, 6, name, argMode, inVector))
    {
        bool    forOutput{false};
        bool    okSoFar{true};
        bool    usesRandom{false};
        auto    direction{inVector[0]};
        auto    suffixValue{inVector[1]};
        auto    randomFlag{inVector[2]};
        auto    defaultString{inVector[3]};
        auto    description{inVector[4]};

        if ("o" == direction)
        {
            forOutput = true;
        }
        else
        {
            if ("i" != direction)
            {
                okSoFar = false;
                ODL_B1(okSoFar); //####
            }
        }
        if (okSoFar)
        {
            if ("1" == randomFlag)
            {
                usesRandom = true;
            }
            else
            {
                if ("0" != randomFlag)
                {
                    okSoFar = false;
                    ODL_B1(okSoFar); //####
                }
            }
        }
        if (okSoFar)
        {
            std::string tempString{defaultString};

            if (usesRandom)
            {
                tempString += GetRandomHexString();
            }
            tempString += suffixValue;
            okSoFar = checkFilePath(tempString.c_str(), forOutput, 0 == (toUType(argMode) & toUType(ArgumentMode::Optional)));
            ODL_B1(okSoFar); //####
        }
        if (okSoFar)
        {
            result = std::make_shared<FilePathArgumentDescriptor>(name, description, argMode, defaultString, suffixValue, forOutput,
                                                                  usesRandom);
        }
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // FilePathArgumentDescriptor::parseArgString

void
FilePathArgumentDescriptor::setToDefaultValue
    (void)
{
    ODL_OBJENTER(); //####
    setCurrentValue(getDefaultValue());
    ODL_S1s(getCurrentValue()); //####
    ODL_OBJEXIT(); //####
} // FilePathArgumentDescriptor::setToDefaultValue

void
FilePathArgumentDescriptor::swap
    (FilePathArgumentDescriptor &   other)
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    inherited::swap(other);
    std::swap(_pathPrefix, other._pathPrefix);
    std::swap(_pathSuffix, other._pathSuffix);
    std::swap(_defaultSet, other._defaultSet);
    std::swap(_forOutput, other._forOutput);
    std::swap(_useRandomPath, other._useRandomPath);
    ODL_OBJEXIT(); //####
} // FilePathArgumentDescriptor::swap

std::string
FilePathArgumentDescriptor::toString
    (void)
{
    ODL_OBJENTER(); //####
    auto    oldDefault{inherited::getDefaultValue()};
    auto    result{prefixFields(ArgumentTypeTag::FilePathTypeTag) + getParameterSeparator() + (_forOutput ? "o"s : "i"s) +
                    getParameterSeparator() + _pathSuffix + getParameterSeparator() + (_useRandomPath ? "1"s : "0"s) +
                    suffixFields(_pathPrefix)};

    NIMO_UNUSED_VAR_(oldDefault);
    ODL_OBJEXIT_s(result); //####
    return result;
} // FilePathArgumentDescriptor::toString

bool
FilePathArgumentDescriptor::validate
    (const std::string &    value)
{
    ODL_OBJENTER(); //####
    ODL_S1s(value); //####
    setValidity(checkFilePath(value.c_str(), _forOutput, false));
    ODL_B1(isValid()); //####
    if (isValid())
    {
        setCurrentValue(value);
        ODL_S1s(getCurrentValue()); //####
    }
    ODL_OBJEXIT_B(isValid()); //####
    return isValid();
} // FilePathArgumentDescriptor::validate

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

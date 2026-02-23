//--------------------------------------------------------------------------------------------------
//
//  File:       nImOgetParametersMain.cpp
//
//  Project:    nImO
//
//  Contains:   A tool to get the parameters of an active nImO service.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2025 by OpenDragon.
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
//  Created:    2025-11-10
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOfilePathArgumentDescriptor.h>
#include <ArgumentDescriptors/nImOstringArgumentDescriptor.h>
#include <BasicTypes/nImOdouble.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <BasicTypes/nImOvalue.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <Contexts/nImOutilityContext.h>
#include <nImOargumentParameterKeys.h>
#include <nImOinputOutputCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOrequestResponse.h>
#include <nImOstandardOptions.h>
#include <ResponseHandlers/nImOgetParametersResponseHandler.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A tool to get the parameters of an active #nImO service. */

/*! @dir GetParameters
 @brief The set of files that implement the GetParameters tool. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Format a value string based on output mode.
 @param[in] inString The original string.
 @param[in] typeString The value type.
 @param[in] flavour The desired output format.
 @return The formatted string. */
static std::string
adjustValue
    (const std::string &        inString,
     const char                 typeChar,
     const nImO::OutputFlavour  flavour)
{
    std::string result{};

    if ((nImO::OutputFlavour::kFlavourNiMo == flavour) || (nImO::OutputFlavour::kFlavourJSON == flavour))
    {
        result = nImO::ReformatString(inString, typeChar);
    }
    else
    {
        result = nImO::SanitizeString(inString);
    }
    return result;
} // adjustValue

/*! @brief Write the argument type dependent fields to standard output.
 @param[in] aParamMap The fields to be written out.
 @param[in] typeString The value type.
 @param[in] flavour The desired output format.
 @param[in] canHaveQuotes @c true check for double quotes in the value to be written. */
static void
writeOutArgTypeDependentFields
    (CPtr(nImO::Map)            aParamMap,
     const char                 typeChar,
     const nImO::OutputFlavour  flavour,
     const bool                 canHaveQuotes)
{
    auto    defaultFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kDefaultParameterKey))};
    auto    hasMaximumFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kHasMaximumParameterKey))};
    auto    hasMinimumFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kHasMinimumParameterKey))};
    auto    maximumFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kMaximumParameterKey))};
    auto    minimumFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kMinimumParameterKey))};

    switch (StaticCast(nImO::ArgumentTypeTag, typeChar))
    {
        case nImO::ArgumentTypeTag::ChannelTypeTag :
        case nImO::ArgumentTypeTag::DateTypeTag :
        case nImO::ArgumentTypeTag::StringTypeTag :
        case nImO::ArgumentTypeTag::TimeTypeTag :
            // Default is a string-type value
            if (aParamMap->end() != defaultFieldIter)
            {
                auto    defaultString{nImO::SanitizeString(defaultFieldIter->second->asString()->getValue(), canHaveQuotes)};

                switch (flavour)
                {
                    case nImO::OutputFlavour::kFlavourNormal :
                        std::cout << "; default: " << defaultString;
                        break;

                    case nImO::OutputFlavour::kFlavourJSON :
                        std::cout << ", " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << defaultString << CHAR_DOUBLEQUOTE_;
                        break;

                    case nImO::OutputFlavour::kFlavourNiMo :
                        std::cout << " " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ <<
                                    defaultString << CHAR_DOUBLEQUOTE_;
                        break;

                    case nImO::OutputFlavour::kFlavourTabs :
                        std::cout << "\t" << defaultString;
                        break;

                    default :
                        break;

                }
            }
            break;

        case nImO::ArgumentTypeTag::DoubleTypeTag :
            if ((aParamMap->end() != defaultFieldIter) && (aParamMap->end() != hasMaximumFieldIter) && (aParamMap->end() != hasMinimumFieldIter) &&
                (aParamMap->end() != maximumFieldIter) && (aParamMap->end() != minimumFieldIter))
            {
                auto    defaultValue{defaultFieldIter->second->asDouble()->getDoubleValue()};
                auto    hasMaximum{hasMaximumFieldIter->second->asLogical()->getValue()};
                auto    hasMaximumString{nImO::Logical::getCanonicalRepresentation(hasMaximum)};
                auto    hasMinimum{hasMinimumFieldIter->second->asLogical()->getValue()};
                auto    hasMinimumString{nImO::Logical::getCanonicalRepresentation(hasMinimum)};
                auto    maximumValue{maximumFieldIter->second->asDouble()->getDoubleValue()};
                auto    minimumValue{minimumFieldIter->second->asDouble()->getDoubleValue()};

                switch (flavour)
                {
                    case nImO::OutputFlavour::kFlavourNormal :
                        std::cout << "; default: " << defaultValue << "; hasMinimum: " << hasMinimumString;
                        if (hasMinimum)
                        {
                            std::cout << "; minimumValue: " << minimumValue;
                        }
                        std::cout << "; hasMaximum: " << hasMaximumString;
                        if (hasMaximum)
                        {
                            std::cout << "; maximumValue: " << maximumValue;
                        }
                        break;

                    case nImO::OutputFlavour::kFlavourJSON :
                        std::cout << ", " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ ": " << defaultValue <<
                                    ", " CHAR_DOUBLEQUOTE_ "hasMinimum" CHAR_DOUBLEQUOTE_ ": " << hasMinimumString;
                        if (hasMinimum)
                        {
                            std::cout << ", " CHAR_DOUBLEQUOTE_ "minimumValue" CHAR_DOUBLEQUOTE_ ": " << minimumValue;
                        }
                        std::cout << ", " CHAR_DOUBLEQUOTE_ "hasMaximum" CHAR_DOUBLEQUOTE_ ": " << hasMaximumString;
                        if (hasMaximum)
                        {
                            std::cout << ", " CHAR_DOUBLEQUOTE_ "maximumValue" CHAR_DOUBLEQUOTE_ ": " << maximumValue;
                        }
                        break;

                    case nImO::OutputFlavour::kFlavourNiMo :
                        std::cout << " " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << defaultValue <<
                                    " " CHAR_DOUBLEQUOTE_ "hasMinimum" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << hasMinimumString;
                        if (hasMinimum)
                        {
                            std::cout << " " CHAR_DOUBLEQUOTE_ "minimumValue" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << minimumValue;
                        }
                        std::cout << " " CHAR_DOUBLEQUOTE_ "hasMaximum" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << hasMaximumString;
                        if (hasMaximum)
                        {
                            std::cout << " " CHAR_DOUBLEQUOTE_ "maximumValue" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << maximumValue;
                        };
                        break;

                    case nImO::OutputFlavour::kFlavourTabs :
                        std::cout << "\t" << defaultValue << "\t" << hasMinimumString << "\t" << minimumValue << "\t" << hasMaximum << "\t" << maximumValue;
                        break;

                    default :
                        break;

                }
            }
            break;

        case nImO::ArgumentTypeTag::FilePathTypeTag :
            {
                auto    pathPrefixFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kPathPrefixParameterKey))};
                auto    pathSuffixFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kPathSuffixParameterKey))};
                auto    forOutputFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kForOutputParameterKey))};
                auto    useRandomPathFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kUseRandomPathParameterKey))};

                if ((aParamMap->end() != pathPrefixFieldIter) && (aParamMap->end() != pathSuffixFieldIter) &&
                    (aParamMap->end() != forOutputFieldIter) && (aParamMap->end() != useRandomPathFieldIter))
                {
                    auto    pathPrefixString{nImO::SanitizeString(pathPrefixFieldIter->second->asString()->getValue(), canHaveQuotes)};
                    auto    pathSuffixString{nImO::SanitizeString(pathSuffixFieldIter->second->asString()->getValue(), canHaveQuotes)};
                    auto    forOutputString{nImO::Logical::getCanonicalRepresentation(forOutputFieldIter->second->asLogical()->getValue())};
                    auto    useRandomPathString{nImO::Logical::getCanonicalRepresentation(useRandomPathFieldIter->second->asLogical()->getValue())};

                    switch (flavour)
                    {
                        case nImO::OutputFlavour::kFlavourNormal :
                            std::cout << "; pathPrefix: " << pathPrefixString << "; pathSuffix: " << pathSuffixString << "; forOutput: " << forOutputString <<
                                        "; useRandomPath: " << useRandomPathString;
                            break;

                        case nImO::OutputFlavour::kFlavourJSON :
                            std::cout << ", " CHAR_DOUBLEQUOTE_ "pathPrefix" CHAR_DOUBLEQUOTE_ ": " << CHAR_DOUBLEQUOTE_ << pathPrefixString <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "pathSuffix" CHAR_DOUBLEQUOTE_ ": " << CHAR_DOUBLEQUOTE_ << pathSuffixString <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "forOutput" CHAR_DOUBLEQUOTE_ ": " << forOutputString <<
                                        ", " CHAR_DOUBLEQUOTE_ "useRandomPath" CHAR_DOUBLEQUOTE_ ": " << useRandomPathString;
                            break;

                        case nImO::OutputFlavour::kFlavourNiMo :
                            std::cout << " " CHAR_DOUBLEQUOTE_ "pathPrefix" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << CHAR_DOUBLEQUOTE_ <<
                                        pathPrefixString << CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "pathSuffix" CHAR_DOUBLEQUOTE_ " " <<
                                        nImO::kKeyValueSeparator << " " << CHAR_DOUBLEQUOTE_ << pathSuffixString <<
                                        " " CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "forOutput" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator <<
                                        " " << forOutputString << " " CHAR_DOUBLEQUOTE_ "useRandomPath" CHAR_DOUBLEQUOTE_ " " <<
                                        nImO::kKeyValueSeparator << " " << useRandomPathString;
                            break;

                        case nImO::OutputFlavour::kFlavourTabs :
                            std::cout << "\t" << pathPrefixString << "\t" << pathSuffixString << "\t" << forOutputString << "\t" << useRandomPathString;
                            break;

                        default :
                            break;

                    }
                }
            }
            break;

        case nImO::ArgumentTypeTag::IntegerTypeTag :
            if ((aParamMap->end() != defaultFieldIter) && (aParamMap->end() != hasMaximumFieldIter) && (aParamMap->end() != hasMinimumFieldIter) &&
                (aParamMap->end() != maximumFieldIter) && (aParamMap->end() != minimumFieldIter))
            {
                auto    defaultValue{defaultFieldIter->second->asInteger()->getIntegerValue()};
                auto    hasMaximum{hasMaximumFieldIter->second->asLogical()->getValue()};
                auto    hasMaximumString{nImO::Logical::getCanonicalRepresentation(hasMaximum)};
                auto    hasMinimum{hasMinimumFieldIter->second->asLogical()->getValue()};
                auto    hasMinimumString{nImO::Logical::getCanonicalRepresentation(hasMinimum)};
                auto    maximumValue{maximumFieldIter->second->asInteger()->getIntegerValue()};
                auto    minimumValue{minimumFieldIter->second->asInteger()->getIntegerValue()};

                switch (flavour)
                {
                    case nImO::OutputFlavour::kFlavourNormal :
                        std::cout << "; default: " << defaultValue << "; hasMinimum: " << hasMinimumString;
                        if (hasMinimum)
                        {
                            std::cout << "; minimumValue: " << minimumValue;
                        }
                        std::cout << "; hasMaximum: " << hasMaximumString;
                        if (hasMaximum)
                        {
                            std::cout << "; maximumValue: " << maximumValue;
                        }
                        break;

                    case nImO::OutputFlavour::kFlavourJSON :
                        std::cout << ", " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ ": " << defaultValue <<
                                    ", " CHAR_DOUBLEQUOTE_ "hasMinimum" CHAR_DOUBLEQUOTE_ ": " << hasMinimumString;
                        if (hasMinimum)
                        {
                            std::cout << ", " CHAR_DOUBLEQUOTE_ "minimumValue" CHAR_DOUBLEQUOTE_ ": " << minimumValue;
                        }
                        std::cout << ", " CHAR_DOUBLEQUOTE_ "hasMaximum" CHAR_DOUBLEQUOTE_ ": " << hasMaximumString;
                        if (hasMaximum)
                        {
                            std::cout << ", " CHAR_DOUBLEQUOTE_ "maximumValue" CHAR_DOUBLEQUOTE_ ": " << maximumValue;
                        }
                        break;

                    case nImO::OutputFlavour::kFlavourNiMo :
                        std::cout << " " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << defaultValue <<
                                    " " CHAR_DOUBLEQUOTE_ "hasMinimum" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << hasMinimumString;
                        if (hasMinimum)
                        {
                            std::cout << " " CHAR_DOUBLEQUOTE_ "minimumValue" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << minimumValue;
                        }
                        std::cout << " " CHAR_DOUBLEQUOTE_ "hasMaximum" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << hasMaximumString;
                        if (hasMaximum)
                        {
                            std::cout << " " CHAR_DOUBLEQUOTE_ "maximumValue" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << maximumValue;
                        };
                        break;

                    case nImO::OutputFlavour::kFlavourTabs :
                        std::cout << "\t" << defaultValue << "\t" << hasMinimumString << "\t" << minimumValue << "\t" << hasMaximum << "\t" << maximumValue;
                        break;

                    default :
                        break;

                }
            }
            break;

        case nImO::ArgumentTypeTag::LogicalTypeTag :
            // Just default, which is a Logical
            if (aParamMap->end() != defaultFieldIter)
            {
                auto    defaultString{nImO::Logical::getCanonicalRepresentation(defaultFieldIter->second->asLogical()->getValue())};

                switch (flavour)
                {
                    case nImO::OutputFlavour::kFlavourNormal :
                        std::cout << "; default: " << defaultString;
                        break;

                    case nImO::OutputFlavour::kFlavourJSON :
                        std::cout << ", " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ ": " << defaultString;
                        break;

                    case nImO::OutputFlavour::kFlavourNiMo :
                        std::cout << " " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << defaultString;
                        break;

                    case nImO::OutputFlavour::kFlavourTabs :
                        std::cout << "\t" << defaultString;
                        break;

                    default :
                        break;

                }
            }
            break;

        case nImO::ArgumentTypeTag::PortTypeTag :
            if (aParamMap->end() != defaultFieldIter)
            {
                auto    isSystemPortFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kIsSystemPortParameterKey))};

                if (aParamMap->end() != isSystemPortFieldIter)
                {
                    auto    defaultValue{defaultFieldIter->second->asInteger()->getIntegerValue()};
                    auto    isSystemPortString{nImO::Logical::getCanonicalRepresentation(isSystemPortFieldIter->second->asLogical()->getValue())};

                    switch (flavour)
                    {
                        case nImO::OutputFlavour::kFlavourNormal :
                            std::cout << "; default: " << defaultValue << "; isSystemPort: " << isSystemPortString;
                            break;

                        case nImO::OutputFlavour::kFlavourJSON :
                            std::cout << ", " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ ": " << defaultValue <<
                                        ", " CHAR_DOUBLEQUOTE_ "isSystemPort" CHAR_DOUBLEQUOTE_ ": " << isSystemPortString;
                            break;

                        case nImO::OutputFlavour::kFlavourNiMo :
                            std::cout << " " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << defaultValue <<
                                        " " CHAR_DOUBLEQUOTE_ "isSystemPort" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " << isSystemPortString;
                            break;

                        case nImO::OutputFlavour::kFlavourTabs :
                            std::cout << "\t" << defaultValue << "\t" << isSystemPortString;
                            break;

                        default :
                            break;

                    }
                }
            }
            break;

        case nImO::ArgumentTypeTag::StringsTypeTag :
            if (aParamMap->end() != defaultFieldIter)
            {
                auto    defaultString{nImO::SanitizeString(defaultFieldIter->second->asString()->getValue(), canHaveQuotes)};
                auto    allowedValuesFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kAllowedValuesParameterKey))};

                if (aParamMap->end() != allowedValuesFieldIter)
                {
                    if (auto allowedValuesSet{allowedValuesFieldIter->second->asSet()}; nullptr != allowedValuesSet)
                    {
                        bool    firstValue{true};

                        switch (flavour)
                        {
                            case nImO::OutputFlavour::kFlavourNormal :
                                std::cout << "; default: " << defaultString << "; allowedValues: (";
                                for (auto walker : *allowedValuesSet)
                                {
                                    if (auto stuff{walker->asString()}; nullptr != stuff)
                                    {
                                        auto    allowedString{nImO::SanitizeString(stuff->getValue(), canHaveQuotes)};

                                        if (! firstValue)
                                        {
                                            std::cout << ", ";
                                        }
                                        std::cout << allowedString;
                                    }
                                }
                                std::cout << ")";
                                break;

                            case nImO::OutputFlavour::kFlavourJSON :
                                std::cout << ", " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << defaultString <<
                                            CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "allowedValues" CHAR_DOUBLEQUOTE_ ": [ ";
                                for (auto walker : *allowedValuesSet)
                                {
                                    if (auto stuff{walker->asString()}; nullptr != stuff)
                                    {
                                        auto    allowedString{nImO::SanitizeString(stuff->getValue(), canHaveQuotes)};

                                        if (! firstValue)
                                        {
                                            std::cout << ", ";
                                        }
                                        std::cout << CHAR_DOUBLEQUOTE_ << allowedString << CHAR_DOUBLEQUOTE_;
                                    }
                                }
                                std::cout << " ]";
                                break;

                            case nImO::OutputFlavour::kFlavourNiMo :
                                std::cout << " " CHAR_DOUBLEQUOTE_ "default" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ <<
                                            defaultString << CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "allowedValues" CHAR_DOUBLEQUOTE_ " " <<
                                            nImO::kKeyValueSeparator << " " << nImO::kStartSetChar << " ";
                                for (auto walker : *allowedValuesSet)
                                {
                                    if (auto stuff{walker->asString()}; nullptr != stuff)
                                    {
                                        auto    allowedString{nImO::SanitizeString(stuff->getValue(), canHaveQuotes)};

                                        if (! firstValue)
                                        {
                                            std::cout << " ";
                                        }
                                        std::cout << CHAR_DOUBLEQUOTE_ << allowedString << CHAR_DOUBLEQUOTE_;
                                    }
                                }
                                std::cout << " " << nImO::kEndSetChar;
                                break;

                            case nImO::OutputFlavour::kFlavourTabs :
                                std::cout << "\t" << defaultString << "\t(";
                                std::cout << ")";
                                break;

                            default :
                                break;

                        }
                    }
                }
            }
            break;

        default :
            break;

    }
} // writeOutArgTypeDependentFields

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for the tool.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::StringArgumentDescriptor>("node"s,
                                                                                      "Node to be interrogated"s,
                                                                                      nImO::ArgumentMode::Required)};
    nImO::DescriptorVector  argumentList{};
    nImO::StandardOptions   optionValues{};
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(firstArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Get parameters of a node"s, "nImOgetParameters node"s, 2025,
                                     nImO::kCopyrightName, optionValues, nullptr, nImO::kSkipAutolaunchOption | nImO::kSkipMachineOption | nImO::kSkipNodeOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>("getParameter"s, optionValues._logging)};
            auto                nodeName{firstArg->getCurrentValue()};
            nImO::Connection    registryConnection{};

            if (ourContext->asUtilityContext()->findTheRegistry(registryConnection))
            {
                auto    proxy{nImO::RegistryProxy::create(ourContext, registryConnection)};
                auto    statusWithInfo{proxy->getNodeInformation(nodeName)};

                if (statusWithInfo.first.first)
                {
                    if (statusWithInfo.second._found)
                    {
                        // Send Get Parameters command to the node.
                        if (optionValues._expanded)
                        {
                            ourContext->report("Sending get parameters request to '"s + nodeName + "'."s);
                        }
                        auto    handler{std::make_unique<nImO::GetParametersResponseHandler>()};
                        auto    status{nImO::SendRequestWithNoArgumentsAndNonEmptyResponse(ourContext, statusWithInfo.second._connection, handler.get(),
                                                                                           nImO::kGetParametersRequest, nImO::kGetParametersResponse)};

                        if (status.first)
                        {
                            nImO::SpArray   result{handler->result()};

                            if (nImO::OutputFlavour::kFlavourJSON == optionValues._flavour)
                            {
                                std::cout << " [ ";
                            }
                            else
                            {
                                if (nImO::OutputFlavour::kFlavourNiMo == optionValues._flavour)
                                {
                                    std::cout << " " << nImO::kStartArrayChar << " ";
                                }
                            }
                            for (auto walker{result->begin()}; walker != result->end(); )
                            {
                                if (auto aParamMap{(*walker)->asMap()}; nullptr == aParamMap)
                                {
                                    ODL_LOG("(nullptr == aParamMap)"); //####
                                }
                                else
                                {
                                    if (nImO::OutputFlavour::kFlavourJSON == optionValues._flavour)
                                    {
                                        std::cout << "{ ";
                                    }
                                    else
                                    {
                                        if (nImO::OutputFlavour::kFlavourNiMo == optionValues._flavour)
                                        {
                                            std::cout << nImO::kStartMapChar << " ";
                                        }
                                    }
                                    bool    canHaveQuotes{(nImO::OutputFlavour::kFlavourJSON != optionValues._flavour) &&
                                                            (nImO::OutputFlavour::kFlavourNiMo != optionValues._flavour)};
                                    auto    nameFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kNameParameterKey))};
                                    auto    modeFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kModeParameterKey))};
                                    auto    typeFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kTypeParameterKey))};
                                    auto    descriptionFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kDescriptionParameterKey))};
                                    auto    currentValueFieldIter{aParamMap->find(std::make_shared<nImO::String>(nImO::kCurrentValueParameterKey))};

                                    if ((aParamMap->end() != nameFieldIter) && (aParamMap->end() != modeFieldIter) && (aParamMap->end() != typeFieldIter) &&
                                        (aParamMap->end() != descriptionFieldIter) && (aParamMap->end() != currentValueFieldIter))
                                    {
                                        auto    nameString{nImO::SanitizeString(nameFieldIter->second->asString()->getValue(), canHaveQuotes)};
                                        auto    modeValue{modeFieldIter->second->asInteger()->getIntegerValue()};
                                        auto    typeString{typeFieldIter->second->asString()->getValue()};
                                        auto    descriptionString{nImO::SanitizeString(descriptionFieldIter->second->asString()->getValue(), canHaveQuotes)};
                                        auto    currentValueString{currentValueFieldIter->second->asString()->getValue()};
                                        auto    modeString{nImO::ArgumentModeToDescription(StaticCast(nImO::ArgumentMode, modeValue))};
                                        auto    fullTypeString{nImO::ArgTypeTagToArgTypeName(typeString[1])};

                                        currentValueString = adjustValue(currentValueString, typeString[1], optionValues._flavour);
                                        switch (optionValues._flavour)
                                        {
                                            case nImO::OutputFlavour::kFlavourNormal :
                                                std::cout << "name: " << nameString << "; type: " << fullTypeString << "; mode: " << modeString <<
                                                            "; description: " << descriptionString << "; value: " << currentValueString;
                                                break;

                                            case nImO::OutputFlavour::kFlavourJSON :
                                                std::cout << CHAR_DOUBLEQUOTE_ "name" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << nameString <<
                                                            CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "type" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                                            fullTypeString << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "mode" CHAR_DOUBLEQUOTE_ ": "
                                                            CHAR_DOUBLEQUOTE_ << modeString << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "description"
                                                            CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << descriptionString <<
                                                            CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "value" CHAR_DOUBLEQUOTE_ ": " <<
                                                            currentValueString;
                                                break;

                                            case nImO::OutputFlavour::kFlavourNiMo :
                                                std::cout << CHAR_DOUBLEQUOTE_ "name" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ <<
                                                            nameString << CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "type" CHAR_DOUBLEQUOTE_ " " <<
                                                            nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ << fullTypeString <<
                                                            CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "mode" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator <<
                                                            " " CHAR_DOUBLEQUOTE_ << modeString << CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "description"
                                                            CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator << " " CHAR_DOUBLEQUOTE_ << descriptionString <<
                                                            CHAR_DOUBLEQUOTE_ " " CHAR_DOUBLEQUOTE_ "value" CHAR_DOUBLEQUOTE_ " " << nImO::kKeyValueSeparator <<
                                                            " " << currentValueString;
                                                break;

                                            case nImO::OutputFlavour::kFlavourTabs :
                                                std::cout << nameString << "\t" << fullTypeString << "\t" <<    modeString << "\t" << descriptionString << "\t" <<
                                                            currentValueString;
                                                break;

                                            default :
                                                break;

                                        }
                                        writeOutArgTypeDependentFields(aParamMap, typeString[1], optionValues._flavour, canHaveQuotes);
                                    }
                                    if (nImO::OutputFlavour::kFlavourJSON == optionValues._flavour)
                                    {
                                        std::cout << " }";
                                    }
                                    else
                                    {
                                        if (nImO::OutputFlavour::kFlavourNiMo == optionValues._flavour)
                                        {
                                            std::cout << " " << nImO::kEndMapChar;
                                        }
                                    }
                                }
                                ++walker;
                                if (nImO::OutputFlavour::kFlavourJSON == optionValues._flavour)
                                {
                                    if (result->end() != walker)
                                    {
                                        std::cout << ",\n";
                                    }
                                }
                                else
                                {
                                    if (nImO::OutputFlavour::kFlavourNiMo == optionValues._flavour)
                                    {
                                        if (result->end() != walker)
                                        {
                                            std::cout << "\n";
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "\n";
                                    }
                                }
                            }
                            if (nImO::OutputFlavour::kFlavourJSON == optionValues._flavour)
                            {
                                std::cout << " ]\n";
                            }
                            else
                            {
                                if (nImO::OutputFlavour::kFlavourNiMo == optionValues._flavour)
                                {
                                    std::cout << " " << nImO::kEndArrayChar << "\n";
                                }
                            }
                        }
                        else
                        {
                            ourContext->report("Problem getting the parameters of node "s + nodeName + ": "s + status.second + "."s);
                            exitCode = 1;
                        }
                    }
                    else
                    {
                        ourContext->report("Unknown node: '"s + nodeName + "'."s);
                    }
                }
                else
                {
                    std::cerr << "Problem with 'getNodeInformation': " << statusWithInfo.first.second << ".\n";
                    exitCode = 1;
                }
            }
            else
            {
                ourContext->report("Registry not found."s);
                exitCode = 2;
            }
            ourContext->report("Exiting."s, false);
        }
        catch (const std::string &  fault)
        {
            std::cerr << "Exception: " << fault << "\n";
            exitCode = -1;
        }
        catch (...)
        {
            ODL_LOG("Exception caught"); //####
            exitCode = -1;
        }
    }
    ODL_EXIT_I(exitCode); //####
    return exitCode;
} // main

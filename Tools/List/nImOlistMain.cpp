//--------------------------------------------------------------------------------------------------
//
//  File:       nImOlistMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to report the visible nImO objects.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-02-19
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOstringsArgumentDescriptor.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOmap.h>
#include <Contexts/nImOutilityContext.h>
#include <nImOchannelName.h>
#include <nImOlauncherCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOstandardOptions.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to report the visible #nImO objects. */

/*! @dir List
 @brief The set of files that implement the List application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The position within a sequence of outputs. */
enum class Placement
{
    /*! @brief The first output element. */
    kFirst,

    /*! @brief An intermediate output element. */
    kMiddle,

    /*! @brief The last output element. */
    kLast,

    /*! @brief A solitary output element. */
    kSolitary

}; // Placement

/*! @brief The available choices. */
enum class Choice
{
    /*! @brief Return information on the known applications. */
    kApps,

    /*! @brief Return information on the known channels. */
    kChan,

    /*! @brief Return information on the known connections. */
    kConn,

    /*! @brief Return information on the known machine. */
    kMach,

    /*! @brief Return information on the known nodes. */
    kNode,

    /*! @brief Return information on the known applications, channels, connections and services. */
    kAll

}; // Choice

/*! @brief Convenience structure for choices. */
struct ChoiceInfo final
{
    /*! @brief A particular choice. */
    Choice  _choice{Choice::kAll};

    /*! @brief The description of the choice. */
    std::string _description{};

    /*! @brief The constructor.
     @param[in] choice The choice value associated with the description.
     @param[in] description The text describing the choice. */
    ChoiceInfo
        (const Choice           choice,
         const std::string &    description) :
            _choice(choice), _description(description)
    {
    }

}; // ChoiceInfo

using ChoiceMap = std::map<std::string, ChoiceInfo>;

static ChoiceMap  lChoiceMap;

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Writes out a description of the 'choice' argument.
 @param[in,out] outStream The stream to write to. */
static void
helpForList
    (std::ostream & outStream)
{
    size_t  choiceWidth{0};

    outStream << "Available choices:\n";
    for (auto walker(lChoiceMap.begin()); walker != lChoiceMap.end(); ++walker)
    {
        size_t  thisWidth{walker->first.length()};

        if (thisWidth > choiceWidth)
        {
            choiceWidth = thisWidth;
        }
    }
    choiceWidth += 2;
    for (auto walker(lChoiceMap.begin()); walker != lChoiceMap.end(); ++walker)
    {
        std::string padding;

        padding.append(choiceWidth - walker->first.length(), ' ');
        outStream << "  " << walker->first << padding << walker->second._description << "\n";
    }
} // helpForList

/*! @brief Output the known applications.
 @param[in] proxy The connection to the Registry.
 @param[in] options The options to apply.
 @param[in] shouldSanitize @c true if strings should be sanitized.
 @param[in] thePlacement Where the output is in a sequence.
 @return @c true if no errors encountered or @c false if there was a problem. */
static bool
listApplications
    (nImO::RegistryProxy &      proxy,
     nImO::StandardOptions &    options,
     const bool                 shouldSanitize,
     const Placement            thePlacement = Placement::kSolitary)
{
    bool    okSoFar{true};
    auto    statusWithAllApplications{proxy.getInformationForAllApplications()};

    if (statusWithAllApplications.first.first)
    {
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kFirst :
                    std::cout << "{ ";
                    break;

                default :
                    break;

            }
            std::cout << CHAR_DOUBLEQUOTE_ "applications" CHAR_DOUBLEQUOTE_ ":";
        }
        else
        {
            std::cout << "Applications:\n";
        }
        nImO::ApplicationInfoVector &   applications{statusWithAllApplications.second};

        if (applications.empty())
        {
            switch (options._flavour)
            {
                case nImO::OutputFlavour::kFlavourNormal :
                    std::cout << "\t** No applications **\n";
                    break;

                case nImO::OutputFlavour::kFlavourJSON :
                    std::cout << " [ ]";
                    break;

                case nImO::OutputFlavour::kFlavourTabs :
                    std::cout << "** No applications **\n";
                    break;

                default :
                    break;

            }
        }
        else
        {
            auto        applicationMap{std::make_shared<nImO::Map>()};
            auto        applicationSubMap{std::make_shared<nImO::Map>()};
            auto        deescriptionKey{std::make_shared<nImO::String>(nImO::kDescriptionKey)};
            auto        nameKey{std::make_shared<nImO::String>(nImO::kPathKey)};
            std::string nodeName{};

            for (auto walker(applications.begin()); walker != applications.end(); ++walker)
            {
                auto    theInfo{*walker};

                if (theInfo._found)
                {
                    if (theInfo._launcherName != nodeName)
                    {
                        if (! nodeName.empty())
                        {
                            applicationMap->addValue(std::make_shared<nImO::String>(nodeName), applicationSubMap);
                            applicationSubMap.reset();
                        }
                        nodeName = theInfo._launcherName;
                    }
                    applicationSubMap->addValue(std::make_shared<nImO::String>(theInfo._appName),
                                                std::make_shared<nImO::String>(theInfo._appDescription));
                }
            }
            if (! applicationSubMap->empty())
            {
                applicationMap->addValue(std::make_shared<nImO::String>(nodeName), applicationSubMap);
                applicationSubMap.reset();
            }
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " [ ";
            }
            for (auto walker(applicationMap->begin()); walker != applicationMap->end(); )
            {
                auto    launcherName{nImO::SanitizeString(walker->first->asString()->getValue(), shouldSanitize)};
                auto    appSubMap{walker->second->asMap()};

                switch (options._flavour)
                {
                    case nImO::OutputFlavour::kFlavourNormal :
                        std::cout << "\t" << launcherName << "\n";
                        break;

                    case nImO::OutputFlavour::kFlavourJSON :
                        std::cout << "{ " << CHAR_DOUBLEQUOTE_ "launcher" CHAR_DOUBLEQUOTE_ ": " << CHAR_DOUBLEQUOTE_ <<
                                    launcherName << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "applications" CHAR_DOUBLEQUOTE_ ": ";
                        break;

                    default :
                        break;

                }
                if (appSubMap->empty())
                {
                    if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                    {
                        std::cout << "[ ]";
                    }
                }
                else
                {
                    if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                    {
                        std::cout << "[\n";
                    }
                    for (auto subWalker(appSubMap->begin()); subWalker != appSubMap->end(); )
                    {
                        auto    appName{nImO::SanitizeString(subWalker->first->asString()->getValue(), shouldSanitize)};
                        auto    appDescr{nImO::SanitizeString(subWalker->second->asString()->getValue(), shouldSanitize)};

                        switch (options._flavour)
                        {
                            case nImO::OutputFlavour::kFlavourNormal :
                                std::cout << "\t\t" << appName << "\t" << appDescr;
                                break;

                            case nImO::OutputFlavour::kFlavourJSON :
                                std::cout << "{ " CHAR_DOUBLEQUOTE_ "name" CHAR_DOUBLEQUOTE_ ": " << CHAR_DOUBLEQUOTE_ << appName <<
                                            CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "description" CHAR_DOUBLEQUOTE_ ": " <<
                                            CHAR_DOUBLEQUOTE_ << appDescr << CHAR_DOUBLEQUOTE_ " }";
                                break;

                            case nImO::OutputFlavour::kFlavourTabs :
                                std::cout << launcherName << "\t" << appName << "\t" << appDescr;
                                break;

                            default :
                                break;

                        }
                        ++subWalker;
                        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                        {
                            if (appSubMap->end() != subWalker)
                            {
                                std::cout << ",\n";
                            }
                        }
                        else
                        {
                            std::cout << "\n";
                        }
                    }
                    if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                    {
                        std::cout << " ]";
                    }
                }
                ++walker;
                if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                {
                    if (applicationMap->end() != walker)
                    {
                        std::cout << ",\n";
                    }
                }
            }
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " ]";
            }
        }
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kLast :
                    std::cout << " }";
                    break;

                case Placement::kMiddle :
                case Placement::kFirst :
                    std::cout << ",";
                    break;

                default :
                    break;

            }
            std::cout << "\n";
        }
    }
    else
    {
        std::cerr << "Problem with 'getInformationForAllApplications': " << statusWithAllApplications.first.second << "\n";
        okSoFar = false;
    }
    return okSoFar;
} // listApplications

/*! @brief Output the known channels.
 @param[in] proxy The connection to the Registry.
 @param[in] options The options to apply.
 @param[in] shouldSanitize @c true if strings should be sanitized.
 @param[in] thePlacement Where the output is in a sequence.
 @return @c true if no errors encountered or @c false if there was a problem. */
static bool
listChannels
    (nImO::RegistryProxy &      proxy,
     nImO::StandardOptions &    options,
     const bool                 shouldSanitize,
     const Placement            thePlacement = Placement::kSolitary)
{
    bool    okSoFar{true};
    auto    statusWithAllChannels{proxy.getInformationForAllChannels()};

    if (statusWithAllChannels.first.first)
    {
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kFirst :
                    std::cout << "{ ";
                    break;

                default :
                    break;

            }
            std::cout << CHAR_DOUBLEQUOTE_ "channels" CHAR_DOUBLEQUOTE_ ":";
        }
        else
        {
            std::cout << "Channels:\n";
        }
        nImO::ChannelInfoVector &   channels{statusWithAllChannels.second};

        if (channels.empty())
        {
            switch (options._flavour)
            {
                case nImO::OutputFlavour::kFlavourNormal :
                    std::cout << "\t** No channels **\n";
                    break;

                case nImO::OutputFlavour::kFlavourJSON :
                    std::cout << " [ ]";
                    break;

                case nImO::OutputFlavour::kFlavourTabs :
                    std::cout << "** No channels **\n";
                    break;

                default :
                    break;

            }
        }
        else
        {
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " [ ";
            }
            for (auto walker(channels.begin()); walker != channels.end(); )
            {
                auto    theInfo{*walker};

                if (theInfo._found)
                {
                    auto        node{nImO::SanitizeString(theInfo._node, shouldSanitize)};
                    auto        path{nImO::SanitizeString(theInfo._path, shouldSanitize)};
                    auto        dataType{nImO::SanitizeString(theInfo._dataType, shouldSanitize)};
                    std::string modes;

                    switch (theInfo._modes)
                    {
                        case nImO::TransportType::kAny :
                            modes = nImO::kProtocolAnyName;
                            break;

                        case nImO::TransportType::kUnknown :
                            modes = nImO::kProtocolUnknownName;
                            break;

                        case nImO::TransportType::kTCP :
                            modes = nImO::kProtocolTcpName;
                            break;

                        case nImO::TransportType::kUDP :
                            modes = nImO::kProtocolUdpName;
                            break;

                        default :
                            if (nImO::TransportType::kTCP == (theInfo._modes & nImO::TransportType::kTCP))
                            {
                                modes = nImO::kProtocolTcpName;
                                if (nImO::TransportType::kUDP == (theInfo._modes & nImO::TransportType::kUDP))
                                {
                                    modes += "+"s + nImO::kProtocolUdpName;
                                }
                            }
                            else if (nImO::TransportType::kUDP == (theInfo._modes & nImO::TransportType::kUDP))
                            {
                                modes = nImO::kProtocolUdpName;
                            }
                            break;
                            
                    }
                    switch (options._flavour)
                    {
                        case nImO::OutputFlavour::kFlavourNormal :
                            std::cout << "\t" << node << " " << path << " '" << dataType << "' " << std::boolalpha << theInfo._isOutput << " " <<
                                        modes << " " << std::boolalpha << theInfo._inUse;
                            break;

                        case nImO::OutputFlavour::kFlavourJSON :
                            std::cout << "{ " << CHAR_DOUBLEQUOTE_ "node" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << node << CHAR_DOUBLEQUOTE_ ", "
                                        CHAR_DOUBLEQUOTE_ "path" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << path << CHAR_DOUBLEQUOTE_ ", "
                                        CHAR_DOUBLEQUOTE_ "dataType" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << dataType << CHAR_DOUBLEQUOTE_ ", "
                                        CHAR_DOUBLEQUOTE_ "isOutput" CHAR_DOUBLEQUOTE_ ": " << std::boolalpha << theInfo._isOutput << ", "
                                        CHAR_DOUBLEQUOTE_ "modes" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << modes << CHAR_DOUBLEQUOTE_ ", "
                                        CHAR_DOUBLEQUOTE_ "inUse" CHAR_DOUBLEQUOTE_ ": " << std::boolalpha << theInfo._inUse << " }";
                            break;

                        case nImO::OutputFlavour::kFlavourTabs :
                            std::cout << node << "\t" << path << "\t" << dataType << "\t" << std::boolalpha << theInfo._isOutput << "\t" << modes <<
                                        "\t" << std::boolalpha << theInfo._inUse;
                            break;

                        default :
                            break;

                    }
                    ++walker;
                    if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                    {
                        if (channels.end() != walker)
                        {
                            std::cout << ",\n";
                        }
                    }
                    else
                    {
                        std::cout << "\n";
                    }
                }
                else
                {
                    ++walker;
                }
            }
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " ]";
            }
        }
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kLast :
                    std::cout << " }";
                    break;

                case Placement::kMiddle :
                case Placement::kFirst :
                    std::cout << ",";
                    break;

                default :
                    break;

            }
            std::cout << "\n";
        }
    }
    else
    {
        std::cerr << "Problem with 'getInformationForAllChannels': " << statusWithAllChannels.first.second << "\n";
        okSoFar = false;
    }
    return okSoFar;
} // listChannels

/*! @brief Output the known connections.
 @param[in] proxy The connection to the Registry.
 @param[in] options The options to apply.
 @param[in] shouldSanitize @c true if strings should be sanitized.
 @param[in] thePlacement Where the output is in a sequence.
 @return @c true if no errors encountered or @c false if there was a problem. */
static bool
listConnections
    (nImO::RegistryProxy &      proxy,
     nImO::StandardOptions &    options,
     const bool                 shouldSanitize,
     const Placement            thePlacement = Placement::kSolitary)
{
    bool    okSoFar{true};
    auto    statusWithAllConnections{proxy.getInformationForAllConnections()};

    if (statusWithAllConnections.first.first)
    {
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kFirst :
                    std::cout << "{ ";
                    break;

                default :
                    break;

            }
            std::cout << CHAR_DOUBLEQUOTE_ "connections" CHAR_DOUBLEQUOTE_ ":";
        }
        else
        {
            std::cout << "Connections:\n";
        }
        nImO::ConnectionInfoVector &    connections{statusWithAllConnections.second};

        if (connections.empty())
        {
            switch (options._flavour)
            {
                case nImO::OutputFlavour::kFlavourNormal :
                    std::cout << "\t** No connections **\n";
                    break;

                case nImO::OutputFlavour::kFlavourJSON :
                    std::cout << " [ ]";
                    break;

                case nImO::OutputFlavour::kFlavourTabs :
                    std::cout << "** No connections **\n";
                    break;

                default :
                    break;

            }
        }
        else
        {
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " [ ";
            }
            for (auto walker(connections.begin()); walker != connections.end(); )
            {
                auto    theInfo{*walker};

                if (theInfo._found)
                {
                    auto        fromNode{nImO::SanitizeString(theInfo._fromNode, shouldSanitize)};
                    auto        fromPath{nImO::SanitizeString(theInfo._fromPath, shouldSanitize)};
                    auto        toNode{nImO::SanitizeString(theInfo._toNode, shouldSanitize)};
                    auto        toPath{nImO::SanitizeString(theInfo._toPath, shouldSanitize)};
                    auto        dataType{nImO::SanitizeString(theInfo._dataType, shouldSanitize)};
                    std::string mode;

                    switch (theInfo._mode)
                    {
                        case nImO::TransportType::kAny :
                            mode = nImO::kProtocolAnyName;
                            break;

                        case nImO::TransportType::kUnknown :
                            mode = nImO::kProtocolUnknownName;
                            break;

                        case nImO::TransportType::kTCP :
                            mode = nImO::kProtocolTcpName;
                            break;

                        case nImO::TransportType::kUDP :
                            mode = nImO::kProtocolUdpName;
                            break;

                        default :
                            if (nImO::TransportType::kTCP == (theInfo._mode & nImO::TransportType::kTCP))
                            {
                                mode = nImO::kProtocolTcpName;
                                if (nImO::TransportType::kUDP == (theInfo._mode & nImO::TransportType::kUDP))
                                {
                                    mode += '+' + nImO::kProtocolUdpName;
                                }
                            }
                            else if (nImO::TransportType::kUDP == (theInfo._mode & nImO::TransportType::kUDP))
                            {
                                mode = nImO::kProtocolUdpName;
                            }
                            break;

                    }
                    switch (options._flavour)
                    {
                        case nImO::OutputFlavour::kFlavourNormal :
                            std::cout << "\t" << fromNode << " " << fromPath << " " << toNode << " " << toPath << " '" << dataType << "' " << mode;
                            break;

                        case nImO::OutputFlavour::kFlavourJSON :
                            std::cout << "{ " << CHAR_DOUBLEQUOTE_ "fromNode" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << fromNode <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "fromPath" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << fromPath <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "toNode" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << toNode <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "toPath" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << toPath <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "dataType" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << dataType <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "mode" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << mode <<
                                        CHAR_DOUBLEQUOTE_ " }";
                            break;

                        case nImO::OutputFlavour::kFlavourTabs :
                            std::cout << fromNode << "\t" << fromPath << "\t" << toNode << "\t" << toPath << "\t" << dataType << "\t" << mode;
                            break;

                        default :
                            break;

                    }
                    ++walker;
                    if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                    {
                        if (connections.end() != walker)
                        {
                            std::cout << ",\n";
                        }
                    }
                    else
                    {
                        std::cout << "\n";
                    }

                }
                else
                {
                    ++walker;
                }
            }
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " ]";
            }
        }
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kLast :
                    std::cout << " }";
                    break;

                case Placement::kMiddle :
                case Placement::kFirst :
                    std::cout << ",";
                    break;

                default :
                    break;

            }
            std::cout << "\n";
        }
    }
    else
    {
        std::cerr << "Problem with 'getInformationForAllConnections': " << statusWithAllConnections.first.second << "\n";
        okSoFar = false;
    }
    return okSoFar;
} // listConnections

/*! @brief Output the known machines.
 @param[in] proxy The connection to the Registry.
 @param[in] options The options to apply.
 @param[in] shouldSanitize @c true if strings should be sanitized.
 @param[in] thePlacement Where the output is in a sequence.
 @return @c true if no errors encountered or @c false if there was a problem. */
static bool
listMachines
    (nImO::RegistryProxy &      proxy,
     nImO::StandardOptions &    options,
     const bool                 shouldSanitize,
     const Placement            thePlacement = Placement::kSolitary)
{
    bool    okSoFar{true};
    auto    statusWithAllMachines{proxy.getInformationForAllMachines()};

    if (statusWithAllMachines.first.first)
    {
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kFirst :
                    std::cout << "{ ";
                    break;

                default :
                    break;

            }
            std::cout << CHAR_DOUBLEQUOTE_ "machines" CHAR_DOUBLEQUOTE_ ":";
        }
        else
        {
            std::cout << "Machines:\n";
        }
        nImO::MachineInfoVector &   machines{statusWithAllMachines.second};

        if (machines.empty())
        {
            switch (options._flavour)
            {
                case nImO::OutputFlavour::kFlavourNormal :
                    std::cout << "\t** No machines **\n";
                    break;

                case nImO::OutputFlavour::kFlavourJSON :
                    std::cout << " [ ]";
                    break;

                case nImO::OutputFlavour::kFlavourTabs :
                    std::cout << "** No machines **\n";
                    break;

                default :
                    break;

            }
        }
        else
        {
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " [ ";
            }
            for (auto walker(machines.begin()); walker != machines.end(); )
            {
                auto    theInfo{*walker};

                if (theInfo._found)
                {
                    auto                machineName{nImO::SanitizeString(theInfo._name, shouldSanitize)};
                    BAIP::address_v4    address{theInfo._address};

                    switch (options._flavour)
                    {
                        case nImO::OutputFlavour::kFlavourNormal :
                            std::cout << "\t" << machineName << " " << address.to_string();
                            break;

                        case nImO::OutputFlavour::kFlavourJSON :
                            std::cout << "{ " << CHAR_DOUBLEQUOTE_ "name" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << machineName <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "address" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                        address.to_string() << CHAR_DOUBLEQUOTE_ " }";
                            break;

                        case nImO::OutputFlavour::kFlavourTabs :
                            std::cout << machineName << "\t" << address.to_string();
                            break;

                        default :
                            break;

                    }
                    ++walker;
                    if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                    {
                        if (machines.end() != walker)
                        {
                            std::cout << ",\n";
                        }
                    }
                    else
                    {
                        std::cout << "\n";
                    }
                }
                else
                {
                    ++walker;
                }
            }
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " ]";
            }
        }
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kLast :
                    std::cout << " }";
                    break;

                case Placement::kMiddle :
                case Placement::kFirst :
                    std::cout << ",";
                    break;

                default :
                    break;

            }
            std::cout << "\n";
        }
    }
    else
    {
        std::cerr << "Problem with 'getInformationForAllMachines': " << statusWithAllMachines.first.second << "\n";
        okSoFar = false;
    }
    return okSoFar;
} // listMachines

/*! @brief Return a human-readable representation of the service type.
 @param[in] theType The service type of interest.
 @return The service type as a string. */
static std::string
mapServiceTypeToString
    (const nImO::ServiceType    theType)
{
    std::string result;

    switch (theType)
    {
        case nImO::ServiceType::GenericService :
            result = "Generic";
            break;

        case nImO::ServiceType::LauncherService :
            result = "Launcher";
            break;

        case nImO::ServiceType::FilterService :
            result = "Input/Output";
            break;

        case nImO::ServiceType::InputService :
            result = "Input";
            break;

        case nImO::ServiceType::OutputService :
            result = "Output";
            break;

    }
    return result;
} // mapServiceTypeToString

/*! @brief Output the known nodes.
 @param[in] proxy The connection to the Registry.
 @param[in] options The options to apply.
 @param[in] shouldSanitize @c true if strings should be sanitized.
 @param[in] thePlacement Where the output is in a sequence.
 @return @c true if no errors encountered or @c false if there was a problem. */
static bool
listNodes
    (nImO::RegistryProxy &      proxy,
     nImO::StandardOptions &    options,
     const bool                 shouldSanitize,
     const Placement            thePlacement = Placement::kSolitary)
{
    bool    okSoFar{true};
    auto    statusWithAllNodes{proxy.getInformationForAllNodes()};

    if (statusWithAllNodes.first.first)
    {
        nImO::NodeInfoVector &  nodes{statusWithAllNodes.second};

        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kFirst :
                    std::cout << "{ ";
                    break;

                default :
                    break;

            }
            std::cout << CHAR_DOUBLEQUOTE_ "nodes" CHAR_DOUBLEQUOTE_ ":";
        }
        else
        {
            std::cout << "Nodes:\n";
        }
        if (nodes.empty())
        {
            switch (options._flavour)
            {
                case nImO::OutputFlavour::kFlavourNormal :
                    std::cout << "\t** No nodes **\n";
                    break;

                case nImO::OutputFlavour::kFlavourJSON :
                    std::cout << " [ ]";
                    break;

                case nImO::OutputFlavour::kFlavourTabs :
                    std::cout << "** No nodes **\n";
                    break;

                default :
                    break;

            }
        }
        else
        {
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " [ ";
            }
            for (auto walker(nodes.begin()); walker != nodes.end(); )
            {
                auto    theInfo{*walker};

                if (theInfo._found)
                {
                    auto                nodeName{nImO::SanitizeString(theInfo._name, shouldSanitize)};
                    auto                serviceType{mapServiceTypeToString(theInfo._serviceType)};
                    BAIP::address_v4    address{theInfo._connection._address};

                    switch (options._flavour)
                    {
                        case nImO::OutputFlavour::kFlavourNormal :
                            std::cout << "\t" << nodeName << " " << address.to_string() << " " << theInfo._connection._port << " [" << serviceType << "]";
                            break;

                        case nImO::OutputFlavour::kFlavourJSON :
                            std::cout << "{ " << CHAR_DOUBLEQUOTE_ "name" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << nodeName <<
                                        CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "address" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                        address.to_string() << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "port" CHAR_DOUBLEQUOTE_ ": "
                                        CHAR_DOUBLEQUOTE_ << theInfo._connection._port << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "serviceType" CHAR_DOUBLEQUOTE_ ": "
                                        CHAR_DOUBLEQUOTE_ << serviceType << CHAR_DOUBLEQUOTE_;
                            if (! options._expanded)
                            {
                                std::cout << " }";
                            }
                            break;

                        case nImO::OutputFlavour::kFlavourTabs :
                            std::cout << nodeName << "\t" << address.to_string() << "\t" << theInfo._connection._port << "\t" << serviceType;
                            break;

                        default :
                            break;

                    }
                    if (options._expanded)
                    {
                        auto    statusWithDetails{proxy.getLaunchDetails(theInfo._name)};

                        if (statusWithDetails.first.first)
                        {
                            nImO::LaunchDetails &   details{statusWithDetails.second};

                            switch (options._flavour)
                            {
                                case nImO::OutputFlavour::kFlavourNormal :
                                    std::cout << " " << details._execPath << " " << details._launchDirectory << " " << details._commandLine;
                                    break;

                                case nImO::OutputFlavour::kFlavourJSON :
                                    std::cout << ", " CHAR_DOUBLEQUOTE_ "execPath" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                    nImO::SanitizeString(details._execPath, true) << CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "launchDirectory"
                                    CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ << nImO::SanitizeString(details._launchDirectory, true) <<
                                    CHAR_DOUBLEQUOTE_ ", " CHAR_DOUBLEQUOTE_ "commandLine" CHAR_DOUBLEQUOTE_ ": " CHAR_DOUBLEQUOTE_ <<
                                    nImO::SanitizeString(details._commandLine, true) << CHAR_DOUBLEQUOTE_ " }";
                                    break;

                                case nImO::OutputFlavour::kFlavourTabs :
                                    std::cout << "\t" << details._execPath << "\t" << details._launchDirectory << "\t" << details._commandLine;
                                    break;

                                default :
                                    break;

                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'getLaunchDetails': " << statusWithDetails.first.second << "\n";
                            okSoFar = false;
                        }
                    }
                    ++walker;
                    if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
                    {
                        if (nodes.end() != walker)
                        {
                            std::cout << ",\n";
                        }
                    }
                    else
                    {
                        std::cout << "\n";
                    }
                }
                else
                {
                    ++walker;
                }
            }
            if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
            {
                std::cout << " ]";
            }
        }
        if (nImO::OutputFlavour::kFlavourJSON == options._flavour)
        {
            switch (thePlacement)
            {
                case Placement::kSolitary :
                case Placement::kLast :
                    std::cout << " }";
                    break;

                case Placement::kMiddle :
                case Placement::kFirst :
                    std::cout << ",";
                    break;

                default :
                    break;

            }
            std::cout << "\n";
        }
    }
    else
    {
        std::cerr << "Problem with 'getInformationForAllNodes': " << statusWithAllNodes.first.second << "\n";
        okSoFar = false;
    }
    return okSoFar;
} // listNodes

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for reporting the visible #nImO channels.

 Standard output will receive a list of the visible #nImO channels.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string progName{*argv};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    lChoiceMap.insert({"apps", ChoiceInfo{Choice::kApps, "available applications"}});
    lChoiceMap.insert({"chan", ChoiceInfo{Choice::kChan, "available channels"}});
    lChoiceMap.insert({"conn", ChoiceInfo{Choice::kConn, "active connections"}});
    lChoiceMap.insert({"mach", ChoiceInfo{Choice::kMach, "active machines"}});
    lChoiceMap.insert({"node", ChoiceInfo{Choice::kNode, "active nodes"}});
    lChoiceMap.insert({"all", ChoiceInfo{Choice::kAll, "all"}});
    nImO::StdStringSet  choiceSet;

    for (auto & walker : lChoiceMap)
    {
        choiceSet.insert(walker.first);
    }
    nImO::StringsArgumentDescriptor firstArg{"choice"s, "Objects to report"s, nImO::ArgumentMode::Optional, "all"s, choiceSet};
    nImO::DescriptorVector          argumentList{};
    nImO::StandardOptions           optionValues{};
    int                             exitCode{0};

    argumentList.push_back(&firstArg);
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "List information about objects in the nImO space"s, "nImOlist node"s, 2016,
                                     nImO::kCopyrightName, optionValues, helpForList, nImO::kSkipLoggingOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                ourContext{std::make_shared<nImO::UtilityContext>(progName, "list"s, optionValues._logging)};
            nImO::Connection    registryConnection{};

            if (ourContext->asUtilityContext()->findRegistry(registryConnection))
            {
                auto    choice{firstArg.getCurrentValue()};
                auto    match{lChoiceMap.find(choice)};
                bool    shouldSanitize{nImO::OutputFlavour::kFlavourJSON == optionValues._flavour};

                if (match != lChoiceMap.end())
                {
                    nImO::RegistryProxy proxy{ourContext, registryConnection};

                    switch (match->second._choice)
                    {
                        case Choice::kApps :
                            if (! listApplications(proxy, optionValues, shouldSanitize))
                            {
                                exitCode = 1;
                            }
                            break;

                        case Choice::kChan :
                            if (! listChannels(proxy, optionValues, shouldSanitize))
                            {
                                exitCode = 1;
                            }
                            break;

                        case Choice::kConn :
                            if (! listConnections(proxy, optionValues, shouldSanitize))
                            {
                                exitCode = 1;
                            }
                            break;

                        case Choice::kMach :
                            if (! listMachines(proxy, optionValues, shouldSanitize))
                            {
                                exitCode = 1;
                            }
                            break;

                        case Choice::kNode :
                            if (! listNodes(proxy, optionValues, shouldSanitize))
                            {
                                exitCode = 1;
                            }
                            break;

                        case Choice::kAll :
                            if (! (listMachines(proxy, optionValues, shouldSanitize, Placement::kFirst) &&
                                   listNodes(proxy, optionValues, shouldSanitize, Placement::kMiddle) &&
                                   listApplications(proxy, optionValues, shouldSanitize, Placement::kMiddle) &&
                                   listChannels(proxy, optionValues, shouldSanitize, Placement::kMiddle) &&
                                   listConnections(proxy, optionValues, shouldSanitize, Placement::kLast)))
                            {
                                exitCode = 1;
                            }
                            break;

                    }
                }
            }
            else
            {
                ourContext->report("Registry not found."s);
                exitCode = 2;
            }
            ourContext->report("exiting."s);
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

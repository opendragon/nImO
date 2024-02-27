//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOchannelName.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the names of nImO channels.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2020 by OpenDragon.
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
//  Created:    2020-03-04
//
//--------------------------------------------------------------------------------------------------

#include <nImOchannelName.h>

#include <regex>
#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the names of %nImO channels. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#define ALPHA_OR_DOLLAR_STRING  "[[:alnum:]$]"
#define NAME_MATCH_STRING       ALPHA_OR_DOLLAR_STRING "+([_.-]" ALPHA_OR_DOLLAR_STRING "+)*"
#define PATH_MATCH_STRING       "(/" NAME_MATCH_STRING ")+"
#define TRANSPORT_MATCH_STRING  "([Uu][Dd][Pp]|[Tt][Cc][Pp]|[Aa][Nn][Yy])"

/*! @brief The character that ends the network part of a ChannelName. */
constexpr char  kEndNetwork{':'};

/*! @brief The character that starts the protocol part of a ChannelName. */
constexpr char  kStartProtocol{'#'};

/*! @brief A regular expression describing the syntax of a channel name. */
static std::regex   lChannelNameMatch{"^((" NAME_MATCH_STRING ")?:)?(" NAME_MATCH_STRING ")?(" PATH_MATCH_STRING ")(#" TRANSPORT_MATCH_STRING ")?$",
                                        std::regex::extended};

/*! @brief A regular expression describing the syntax of a name. */
static std::regex   lNameMatch{"^" NAME_MATCH_STRING "$", std::regex::extended};

/*! @brief A regular expression describing the syntax of a path. */
static std::regex   lPathMatch{"^" PATH_MATCH_STRING "$", std::regex::extended};

/*! @brief A regular expression describing the syntax of a transport value. */
static std::regex   lTransportMatch{"^" TRANSPORT_MATCH_STRING "$", std::regex::extended};

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

const std::string   nImO::kProtocolAnyName{"any"s}; // must be lower-case!

const std::string   nImO::kProtocolTcpName{"tcp"s}; // must be lower-case!

const std::string   nImO::kProtocolUdpName{"udp"s}; // must be lower-case!

const std::string   nImO::kProtocolUnknownName{"unknown"s};

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::ChannelName::ChannelName
    (const ChannelName &  other) :
        _network{other._network}, _node{other._node}, _path{other._path}, _transport{other._transport}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::ChannelName::ChannelName

nImO::ChannelName::ChannelName
    (ChannelName && other)
    noexcept :
        _network{std::move(other._network)}, _node{std::move(other._node)}, _path{std::move(other._path)},
        _transport{other._transport}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._transport = TransportType::kUnknown;
    ODL_EXIT_P(this); //####
} // nImO::ChannelName::ChannelName

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::ChannelName::generatePath
    (const std::string &    base,
     const bool             forOutput,
     const int64_t          numChannels,
     const int64_t          channelNumber,
     std::string &          path)
{
    ODL_ENTER(); //####
    ODL_S1s("base = ", base); //####
    ODL_B1("forOutput = ", forOutput); //####
    ODL_I2("numChannels = ", numChannels, "channelNumber = ", channelNumber); //####
    bool    okSoFar;

    if ((channelNumber > 0) && (channelNumber <= numChannels))
    {
        if (base.empty())
        {
            okSoFar = true;
            path = ""s;
        }
        else
        {
            std::string     problem;
            SpChannelName   parsed{parse(base, problem)};

            if (parsed)
            {
                okSoFar = true;
                path = parsed->_path;
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar)
        {
            path += (forOutput ? "/out"s : "/in"s);
            if (1 < numChannels)
            {
                path += std::to_string(channelNumber);
            }
        }
    }
    else
    {
        okSoFar = false;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ChannelName::generatePath

std::string
nImO::ChannelName::getName
    (void)
    const
{
    ODL_OBJENTER(); //####
    std::string result;

    if (! _network.empty())
    {
        result += _network + kEndNetwork;
    }
    if (! _node.empty())
    {
        result += _node;
    }
    result += _path;
    if (TransportType::kUnknown != _transport)
    {
        result += kStartProtocol + transportToName(_transport);
    }
    ODL_OBJEXIT_s(result); //####
    return result;
} // nImO::ChannelName::getName

nImO::ChannelName &
nImO::ChannelName::operator=
    (const ChannelName &  other)
{
    ODL_OBJENTER(); //####
    _network = other._network;
    _node = other._node;
    _path = other._path;
    _transport = other._transport;
    ODL_OBJEXIT(); //####
    return *this;
} // nImO::ChannelName::operator=

/*! @brief The move assignment operator.
 @param[in] other The object to be moved.
 @return The updated object. */
nImO::ChannelName &
nImO::ChannelName::operator=
    (ChannelName &&  other)
    noexcept
{
    ODL_OBJENTER(); //####
    _network = std::move(other._network);
    _node = std::move(other._node);
    _path = std::move(other._path);
    _transport = other._transport;
    other._transport = TransportType::kUnknown;
    ODL_OBJEXIT(); //####
    return *this;
} // nImO::ChannelName::operator=

nImO::SpChannelName
nImO::ChannelName::parse
    (const std::string &    input,
     std::string &          problemDescription)
{
    ODL_ENTER(); //####
    ODL_S1s("input = ", input); //####
    ODL_P1("problemDescription = ", &problemDescription); //####
    SpChannelName   result;
    std::string     networkName;
    std::string     nodeName;
    std::string     path;
    std::smatch     matches;
    TransportType   protocol{TransportType::kUnknown};
    bool            okSoFar{std::regex_match(input, matches, lChannelNameMatch)};

    if (okSoFar)
    {
        // Submatch 2 = network [can be empty]
        networkName = matches[2].str();
        // Submatch 4 = node name
        nodeName = matches[4].str();
        // Submatch 6 = path
        path = matches[6].str();
        // Submatch 10 = transport [can be empty]
        protocol = transportFromName(matches[10].str());
        result = std::make_shared<ChannelName>();
        result->_network = networkName;
        result->_node = nodeName;
        result->_path = path;
        result->_transport = protocol;
    }
    else
    {
        problemDescription = "Unable to parse channel name"s;
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::ChannelName::parse

void
nImO::ChannelName::swap
    (ChannelName &  other)
{
    ODL_ENTER(); //####
    _network.swap(other._network);
    _node.swap(other._node);
    _path.swap(other._path);
    std::swap(_transport, other._transport);
    ODL_EXIT(); //####
} // nImO::ChannelName::swap

nImO::TransportType
nImO::ChannelName::transportFromName
    (const std::string &    aName)
{
    ODL_ENTER(); //####
    ODL_S1s("aName = ", aName); //####
    auto    protocol{TransportType::kUnknown};
    auto    nameToCheck{ConvertToLowerCase(aName)};

    if (nameToCheck == transportToName(TransportType::kAny))
    {
        protocol = TransportType::kAny;
    }
    else if (nameToCheck == transportToName(TransportType::kUDP))
    {
        protocol = TransportType::kUDP;
    }
    else if (nameToCheck == transportToName(TransportType::kTCP))
    {
        protocol = TransportType::kTCP;
    }
    ODL_EXIT_I(StaticCast(int, protocol)); //####
    return protocol;
} // nImO::ChannelName::transportFromName

nImO::StdStringSet
nImO::ChannelName::transportNames
    (void)
{
    ODL_ENTER(); //####
    StdStringSet    result;

    result.insert(kProtocolAnyName);
    result.insert(kProtocolUdpName);
    result.insert(kProtocolTcpName);
    ODL_EXIT(); //####
    return result;
} // nImO::ChannelName::transportNames

std::string
nImO::ChannelName::transportToName
    (const TransportType    aValue)
{
    ODL_ENTER(); //####
    ODL_I1("aValue = ", StaticCast(int64_t, aValue)); //####
    std::string result;

    switch (aValue)
    {
        case TransportType::kAny :
            result = kProtocolAnyName;
            break;

        case TransportType::kTCP :
            result = kProtocolTcpName;
            break;

        case TransportType::kUDP :
            result = kProtocolUdpName;
            break;

        case TransportType::kUnknown :
            result = kProtocolUnknownName;
            break;

    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::ChannelName::transportToName

bool
nImO::ChannelName::validNetwork
    (const std::string &    input)
{
    ODL_ENTER(); //####
    ODL_S1s("input = ", input); //####
    bool    result{std::regex_match(input, lNameMatch)};

    ODL_EXIT_B(result); //####
    return result;
} // nImO::ChannelName::validNetwork

bool
nImO::ChannelName::validNode
    (const std::string &    input)
{
    ODL_ENTER(); //####
    ODL_S1s("input = ", input); //####
    bool    result{std::regex_match(input, lNameMatch)};

    ODL_EXIT_B(result); //####
    return result;
} // nImO::ChannelName::validNode

bool
nImO::ChannelName::validPath
    (const std::string &    input)
{
    ODL_ENTER(); //####
    ODL_S1s("input = ", input); //####
    bool    result{std::regex_match(input, lPathMatch)};

    ODL_EXIT_B(result); //####
    return result;
} // nImO::ChannelName::validPath

bool
nImO::ChannelName::validTransport
    (const std::string &    input)
{
    ODL_ENTER(); //####
    ODL_S1s("input = ", input); //####
    bool    result{std::regex_match(input, lTransportMatch)};

    ODL_EXIT_B(result); //####
    return result;
} // nImO::ChannelName::validTransport

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

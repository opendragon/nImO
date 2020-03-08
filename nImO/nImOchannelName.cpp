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

#include "nImOchannelName.hpp"

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

/*! @brief The character that ends the network part of a ChannelName. */
static const char   kEndNetwork = ':';

/*! @brief The character that starts the path part of a ChannelName. */
static const char   kStartPath = '/';

/*! @brief The character that starts the protocol part of a ChannelName. */
static const char   kStartProtocol = '#';

/*! @brief The standard name for the TCP protocol. */
static const std::string    kProtocolTcpName = "tcp";

/*! @brief The standard name for the UDP protocol. */
static const std::string    kProtocolUdpName = "udp";

/*! @brief The standard name for an unknown protocol. */
static const std::string    kProtocolUnknownName = "unknown";

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Check a character for legitimacy.
 @param[in] aChar The character to check.
 @param[in] slashAllowed @c true if a forward slash can appear.
 @return @c true if the character is legal. */
static bool
checkChar
    (const char aChar,
     const bool slashAllowed = false)
{
    ODL_ENTER(); //####
    ODL_C1("aChar = ", aChar); //####
    ODL_B1("slashAllowed = ", slashAllowed); //####
    bool    result;

    if (isalnum(aChar))
    {
        result = true;
    }
    else if (('$' == aChar) || ('_' == aChar) || ('-' == aChar) || ('.' == aChar))
    {
        result = true;
    }
    else if ('/' == aChar)
    {
        result = slashAllowed;
    }
    else
    {
        result = false;
    }
    ODL_EXIT_B(result); //####
    return result;
} // checkChar

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::ChannelName::ChannelName
    (void) :
        _transport(Transport::Unknown)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::ChannelName::ChannelName

nImO::ChannelName::ChannelName
    (const nImO::ChannelName &  other) :
        _network(other._network), _node(other._node), _path(other._path), _transport(other._transport)
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_EXIT_P(this); //####
} // nImO::ChannelName::ChannelName

nImO::ChannelName::~ChannelName
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::ChannelName::~ChannelName

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

std::string
nImO::ChannelName::getName
    (void)
    const
{
    ODL_OBJENTER(); //####
    std::string result;

    ODL_OBJEXIT(); //####
    if (0 < _network.length())
    {
        result += _network;
        result += kEndNetwork;
    }
    if (0 < _node.length())
    {
        result += _node;
    }
    result += kStartPath;
    result += _path;
    if (Transport::Unknown != _transport)
    {
        result += kStartProtocol;
        result += transportToName(_transport);
    }
    ODL_OBJEXIT_s(result); //####
    return result;
} // nImO::ChannelName::getName

nImO::SpChannelName
nImO::ChannelName::parse
    (const std::string &    input,
     std::string &          problemDescription)
{
    ODL_ENTER(); //####
    ODL_S1s("input = ", input); //####
    ODL_P1("problemDescription = ", &problemDescription); //####
    bool            okSoFar;
    enum
    {
        kNetwork,
        kNode,
        kPath,
        kProtocol
    }               scanState = kNetwork;
    SpChannelName   result;
    std::string     networkName;
    std::string     nodeName;
    std::string     path;
    std::string     protocolName;
    Transport       protocol;

    if (0 == input.length())
    {
        problemDescription = "Empty name";
        okSoFar = false;
    }
    else
    {
        problemDescription = "";
        okSoFar = true;
    }
    for (size_t ii = 0, mm = input.length(); okSoFar && (ii < mm); ++ii)
    {
        char    cc = input[ii];

        switch (scanState)
        {
            case kNetwork :
                switch (cc)
                {
                    case kEndNetwork :
                        scanState = kNode;
                        break;

                    case kStartPath :
                        nodeName = networkName;
                        networkName = "";
                        scanState = kPath;
                        break;

                    case kStartProtocol :
                        problemDescription = "Missing parts in name";
                        okSoFar = false;
                        break;

                    default :
                        if (checkChar(cc))
                        {
                            networkName += cc;
                        }
                        else
                        {
                            problemDescription = "Illegal character in string";
                            okSoFar = false;
                        }
                        break;

                }
                break;

            case kNode :
                switch (cc)
                {
                    case kEndNetwork :
                        problemDescription = "Illegal character in string";
                        okSoFar = false;
                        break;

                    case kStartPath :
                        scanState = kPath;
                        break;

                    case kStartProtocol :
                        problemDescription = "Missing parts in name";
                        okSoFar = false;
                        break;

                    default :
                        if (checkChar(cc))
                        {
                            nodeName += cc;
                        }
                        else
                        {
                            problemDescription = "Illegal character in string";
                            okSoFar = false;
                        }
                        break;

                }
                break;

            case kPath :
                switch (cc)
                {
                    case kEndNetwork :
                        problemDescription = "Illegal character in string";
                        okSoFar = false;
                        break;

                    case kStartProtocol :
                        scanState = kProtocol;
                        break;

                    default :
                        if (checkChar(cc, true))
                        {
                            path += cc;
                        }
                        else
                        {
                            problemDescription = "Illegal character in string";
                            okSoFar = false;
                        }
                        break;

                }
                break;

            case kProtocol :
                if (checkChar(cc))
                {
                    protocolName += cc;
                }
                else
                {
                    problemDescription = "Illegal character in string";
                    okSoFar = false;
                }
                break;

        }
    }
    okSoFar &= (0 < path.length());
    if (okSoFar)
    {
        if (protocolName == transportToName(Transport::UDP))
        {
            protocol = Transport::UDP;
        }
        else if (protocolName == transportToName(Transport::TCP))
        {
            protocol = Transport::TCP;
        }
        else if (protocolName == "")
        {
            if (scanState == kProtocol)
            {
                problemDescription = "Invalid protocol";
                okSoFar = false;
            }
            else
            {
                protocol = Transport::Unknown;
            }
        }
        else
        {
            problemDescription = "Invalid protocol";
            okSoFar = false;
        }
    }
    if (okSoFar)
    {
        result = SpChannelName(new ChannelName());
        result->_network = networkName;
        result->_node = nodeName;
        result->_path = path;
        result->_transport = protocol;
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::ChannelName::parse

nImO::StringSet
nImO::ChannelName::transportNames
    (void)
{
    ODL_ENTER(); //####
    StringSet   result;

    result.insert(kProtocolUdpName);
    result.insert(kProtocolTcpName);
    ODL_EXIT(); //####
    return result;
} // nImO::ChannelName::transportNames

std::string
nImO::ChannelName::transportToName
    (const nImO::Transport    aValue)
{
    ODL_ENTER(); //####
    std::string result;

    switch (aValue)
    {
        case Transport::TCP :
            result = kProtocolTcpName;
            break;

        case Transport::UDP :
            result = kProtocolUdpName;
            break;

        case Transport::Unknown :
            result = kProtocolUnknownName;
            break;

    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::ChannelName::transportToName

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)


//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOsearchContext.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO execution contexts that can search for the Registry.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2022 by OpenDragon.
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
//  Created:    2022-07-18
//
//--------------------------------------------------------------------------------------------------

#include <Contexts/nImOsearchContext.h>

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <Containers/nImOstringBuffer.h>
#include <nImOmainSupport.h>
#include <nImOreceiveFromMulticast.h>
#include <nImOregistryCommands.h>
#include <nImOsendToMulticast.h>
#include <nImOstandardOptions.h>

#if MAC_OR_LINUX_OR_BSD_
# include <ifaddrs.h>
#endif // MAC_OR_LINUX_OR_BSD_
#include <regex>
#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif // defined(__APPLE__)
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO execution contexts that can search for the Registry. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The Registry launch path value to be used if none is specified in the configuration file. */
static const std::string    kDefaultRegistryLaunchPath{"$$/nImOregistry"s};

/*! @brief The Registry mDNS name value to be used if none is specified in the configuration file. */
static const std::string    kDefaultRegistryName{"registry_1"s};

/*! @brief The multicast connection to be used for the search for the Registry, if none is specified in the configuration file. */
static nImO::Connection kDefaultRegistrySearchConnection{StaticCast(nImO::IPv4Address, nImO::BytesToIPv4Address(239, 17, 12, 1)), 1956};

/*! @brief The Registry mode value to be used if none is specified in the configuration file. */
static const nImO::RegistryMode kDefaultRegistrySearchMode{nImO::RegistryMode::kBoth};

/*! @brief The Registry search retries value to be used if none is specified in the configuration file. */
constexpr int   kDefaultRegistrySearchRetries{5};

/*! @brief The Registry search timeout value to be used if none is specified in the configuration file. */
constexpr int   kDefaultRegistryTimeout{1};

/*! @brief The standard name for either mode. */
static const std::string   kModeBothName{"both"s}; // must be lower-case!

/*! @brief The standard name for the mDNS mode. */
static const std::string   kModeMdnsName{"mdns"s}; // must be lower-case!

/*! @brief The standard name for the multicast mode. */
static const std::string   kModeMulticastName{"multicast"s}; // must be lower-case!

/*! @brief The standard name for an unknown mode. */
static const std::string   kModeUnknownName{"unknown"s};

/*! @brief A regular expression describing the syntax of a Registry name. */
static const std::regex kNameMatch{"^[[:alnum:]][[:alnum:]_]*$", std::regex::extended};

/*! @brief The key for the mDNS name of the Registry to support multiple nImO networks on a LAN. */
static const std::string    kRegistryNameKey{"registry name"s};

/*! @brief The key for the options to apply when autolaunching the Registry. */
static const std::string    kRegistryOptionsKey{"registry options"s};

/*! @brief The key for the path to the Registry executable to use when autolaunching the Registry. */
static const std::string    kRegistryPathKey{"registry path"s};

/*! @brief The key for the Registry search multicast address in the configuration file. */
static const std::string    kRegistrySearchAddressKey{"registry search address"s};

/*! @brief The key for the search mode of the Registry. */
static const std::string    kRegistrySearchModeKey{"registry search mode"s};

/*! @brief The key for the Registry multicast search port in the configuration file. */
static const std::string    kRegistrySearchPortKey{"registry search port"s};

/*! @brief The key for the maximum number of attempts to find a running Registry. */
static const std::string    kRegistrySearchRetriesKey{"registry search retries"s};

/*! @brief The key for the maximum number of seconds to watch for a running Registry. */
static const std::string    kRegistryTimeoutKey{"registry search timeout"s};

/*! @brief The buffer used to hold an IP address. */
static char lAddrBuffer[64];

/*! @brief Set to @c true when the browser thread has started. */
static std::atomic_bool lBrowserThreadStarted{false};

/*! @brief Set to @c true to cause the browser thread to terminate. */
static std::atomic_bool lBrowserThreadStop{false};

/*! @brief Set to @c true when the browser thread has terminated. */
static std::atomic_bool lBrowserThreadStopped{false};

/*! @brief The buffer to hold a received mDNS reply structure. */
static char lEntryBuffer[256];

/*! @brief @c true if the application needs to performa a single check for the Registry. */
static std::atomic_bool lPerformSingleRegistryCheck{false};

/*! @brief Set to @c true to cause the loop looking for the Registry to terminate. */
static std::atomic_bool lStopRegistryLoop{false};

/*! @brief The buffer used to hold TXT records from a received mDNS reply structure. */
static mDNS::record_txt_t   lTxtBuffer[128];

/*! @brief @c true if the application should wait for the Registry. */
static std::atomic_bool    lWaitForRegistry{true};

namespace nImO
{

    /*! @brief A class to dispatch requests from received mDNS records to the active context. */
    class RecordHandler
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] owner The owning context. */
            explicit RecordHandler
                (nImO::SearchContext &  owner) :
                    _owner(owner), _processing(false)
            {
            }

            /* @brief Extract the first part of a dot-delimited string.
             @param[in] inString The string to be processed.
             @return The first segment of the input string, up to but not including the separating period character. */
            static inline std::string
            firstPartOfPath
                (const std::string &    inString)
            {
                std::string             outString{};
                std::string::size_type  period{inString.find('.')};

                if (std::string::npos == period)
                {
                    outString = inString;
                }
                else
                {
                    outString = inString.substr(0, period - 1);
                }
                return outString;
            }

            /* @brief Handle the situation when the Registry quits before data is collected. */
            inline void
            markDone
                (void)
            {
                if (_processing)
                {
                    _owner._havePort = _owner._haveAddress = _processing = false;
                    ODL_B3(_owner._havePort, _owner._haveAddress, _processing); //####
                }
            }

            /* @brief Handle an A record.
             @param[in] entryData The name of the server.
             @param[in] aData The IPv4 address of the server. */
            inline void
            processAData
                (const mDNS::string_t &    entryData,
                 const mDNS::string_t &    aData)
                const
            {
                NIMO_UNUSED_VAR_(entryData);
                NIMO_UNUSED_VAR_(aData);
                if (_processing)
                {
                    // Note that the A records are ignored.
                    _owner.report("A Data"s);
                }
            }

            /* @brief Handle an AAAA record.
             @param[in] entryData The name of the server.
             @param[in] aaaaData The IPv6 address of the server. */
            inline void
            processAaaaData
                (const mDNS::string_t &    entryData,
                 const mDNS::string_t &    aaaaData)
                const
            {
                NIMO_UNUSED_VAR_(entryData);
                NIMO_UNUSED_VAR_(aaaaData);
                if (_processing)
                {
                    // Note that the AAAA records are ignored.
                    _owner.report("AAAA Data"s);
                }
            }

            /* @brief Handle a PTR record.
             @param[in] entryData The name of the server.
             @param[in] entry The kind of PTR record.
             @param[in] ptrData The associated data for the PTR record. */
            inline void
            processPtrData
                (const mDNS::string_t &     entryData,
                 const mDNS::entry_type_t   entry,
                 const mDNS::string_t &     ptrData)
            {
                if (mDNS::kEntryTypeAnswer == entry)
                {
                    auto    _entryData{mdns_string_to_std_string(entryData)};

                    if (_owner.getRegistryServiceName() == _entryData)
                    {
                        _owner.report("PTR Data"s);
                        _owner._registryTag = firstPartOfPath(mdns_string_to_std_string(ptrData));
                        _owner._havePort = _owner._haveAddress = false;
                        _processing = true;
                        ODL_B3(_owner._havePort, _owner._haveAddress, _processing); //####
                    }
                    else
                    {
                        _processing = false;
                        ODL_B1(_processing); //####
                    }
                }
                else
                {
                    _processing = false;
                    ODL_B1(_processing); //####
                }
            }

            /* @brief Handle an SRV record.
             @param[in] port The IP port for the Registry. */
            inline void
            processSrvData
                (const int  port)
            {
                if (_processing)
                {
                    _owner.report("SRV Data"s);
                    _owner._registryPort = port;
                    _owner._havePort = true;
                    ODL_B1(_owner._havePort); //####
                }
            }

            /* @brief Handle a TXT record.
             @param[in] keyData The key for the TXT record.
             @param[in] valueData The value associated with the key. */
            inline void
            processTxtData
                (const mDNS::string_t &    keyData,
                 const mDNS::string_t &    valueData)
            {
                if (_processing)
                {
                    auto    keyString{mdns_string_to_std_string(keyData)};

                    if (kRegistryAddressKey == keyString)
                    {
                        _owner.report("TXT Data"s);
                        _owner._registryPreferredAddress = mdns_string_to_std_string(valueData);
                        _owner._haveAddress = true;
                        ODL_B1(_owner._haveAddress); //####
                    }
                }
            }

        protected :
            // Protected methods.

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The owning context. */
            nImO::SearchContext &   _owner;

            /*! @brief @c true if this record is to be processed. */
            bool    _processing;

    }; // RecordHandler

} // nImO

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

char nImO::SearchContext::gNameBuffer[256];

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Find the IPv4 and IPv6 addresses for the machine, if available. */
static void
getLocalAddresses
    (void)
{
    ODL_ENTER(); //####
#if MAC_OR_LINUX_OR_BSD_
    Ptr(struct ifaddrs)         addresses{nullptr};
#else // not MAC_OR_LINUX_OR_BSD_
    Ptr(IP_ADAPTER_ADDRESSES)   adapterAddress{nullptr};
    ULONG                       addressSize{8000};
    uint                        ret{};
    uint                        numRetries{4};
#endif // not MAC_OR_LINUX_OR_BSD_

#if MAC_OR_LINUX_OR_BSD_
    if (-1 == getifaddrs(&addresses))
    {
        throw "Failed to get network adapter addresses"s;

    }
    bool    firstIpv4{true};
    bool    firstIpv6{true};

    for (Ptr(struct ifaddrs) address{addresses}; nullptr != address; address = address->ifa_next)
    {
        if (nullptr != address->ifa_addr)
        {
            if (AF_INET == address->ifa_addr->sa_family)
            {
                auto &  saddr{*ReinterpretCast(Ptr(struct sockaddr_in), address->ifa_addr)};

                if (nImO::BytesToIPv4Address(127, 0, 0, 1) != ntohl(saddr.sin_addr.s_addr))
                {
                    if (firstIpv4)
                    {
                        nImO::SearchContext::gServiceAddressIpv4 = saddr;
                        firstIpv4 = false;
                    }
                    nImO::NetworkingContext::gHasIpv4 = true;
                }
            }
            else
            {
                if (AF_INET6 == address->ifa_addr->sa_family)
                {
                    auto &                  saddr{*ReinterpretCast(Ptr(struct sockaddr_in6), address->ifa_addr)};
                    static const uint8_t    localHost[]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
                    static const uint8_t    localHostMapped[]{ 0, 0, 0,    0,    0,    0, 0, 0,
                                                               0, 0, 0xff, 0xff, 0x7f, 0, 0, 1 };

                    if ((0 == (IFF_LOOPBACK & address->ifa_flags)) &&
                        (0 != memcmp(saddr.sin6_addr.s6_addr, localHost, sizeof(localHost))) &&
                        (0 != memcmp(saddr.sin6_addr.s6_addr, localHostMapped, sizeof(localHostMapped))))
                    {
                        if (firstIpv6)
                        {
                            nImO::SearchContext::gServiceAddressIpv6 = saddr;
                            firstIpv6 = false;
                        }
                        nImO::SearchContext::gHasIpv6 = true;
                    }
                }
            }
        }
    }
    freeifaddrs(addresses);
#else // not MAC_OR_LINUX_OR_BSD_
    do
    {
        adapterAddress = ReinterpretCast(Ptr(IP_ADAPTER_ADDRESSES), malloc(addressSize));
        ret = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_ANYCAST, 0, adapterAddress, &addressSize);
        if (ERROR_BUFFER_OVERFLOW == ret)
        {
            free(adapterAddress);
            adapterAddress = nullptr;
            addressSize *= 2;
        }
        else
        {
            break;

        }
    }
    while (numRetries-- > 0);
    if ((nullptr == adapterAddress) || (ret != NO_ERROR))
    {
        free(adapterAddress);
        throw "Failed to get network adapter addresses"s;

    }
    bool    firstIpv4{true};
    bool    firstIpv6{true};

    for (PIP_ADAPTER_ADDRESSES adapter{adapterAddress}; nullptr != adapter; adapter = adapter->Next)
    {
        if (TUNNEL_TYPE_TEREDO == adapter->TunnelType)
        {
            continue;

        }
        if (adapter->OperStatus != IfOperStatusUp)
        {
            continue;

        }
        for (CPtr(IP_ADAPTER_UNICAST_ADDRESS) unicast{adapter->FirstUnicastAddress}; nullptr != unicast; unicast = unicast->Next)
        {
            if (nullptr != unicast->Address.lpSockaddr)
            {
                if (AF_INET == unicast->Address.lpSockaddr->sa_family)
                {
                    const auto &    saddr{*ReinterpretCast(Ptr(struct sockaddr_in), unicast->Address.lpSockaddr)};

                    if ((saddr.sin_addr.S_un.S_un_b.s_b1 != 127) || (saddr.sin_addr.S_un.S_un_b.s_b2 != 0) ||
                        (saddr.sin_addr.S_un.S_un_b.s_b3 != 0) || (saddr.sin_addr.S_un.S_un_b.s_b4 != 1))
                    {
                        if (firstIpv4)
                        {
                            nImO::SearchContext::gServiceAddressIpv4 = saddr;
                            firstIpv4 = false;
                        }
                        nImO::NetworkingContext::gHasIpv4 = true;
                    }
                }
                else
                {
                    if (AF_INET6 == unicast->Address.lpSockaddr->sa_family)
                    {
                        const auto &        saddr{*ReinterpretCast(Ptr(struct sockaddr_in6), unicast->Address.lpSockaddr)};
                        static const uchar  localHost[]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
                        static const uchar  localHostMapped[]{ 0, 0, 0,    0,    0,    0, 0, 0,
                                                               0, 0, 0xff, 0xff, 0x7f, 0, 0, 1 };

                        if ((NldsPreferred == unicast->DadState) &&
                            (0 != memcmp(saddr.sin6_addr.s6_addr, localHost, sizeof(localHost))) &&
                            (0 != memcmp(saddr.sin6_addr.s6_addr, localHostMapped, sizeof(localHostMapped))))
                        {
                            if (firstIpv6)
                            {
                                nImO::SearchContext::gServiceAddressIpv6 = saddr;
                                firstIpv6 = false;
                            }
                            nImO::SearchContext::gHasIpv6 = true;
                        }
                    }
                }
            }
        }
    }
    free(adapterAddress);
#endif // not MAC_OR_LINUX_OR_BSD_
    if ((! nImO::NetworkingContext::gHasIpv4) && (! nImO::SearchContext::gHasIpv6))
    {
        throw "No usable network addresses found."s;
        
    }
    ODL_EXIT(); //####
} // getLocalAddresses

/*! @brief Handle received mDNS query requests. */
static bool
queryCallback
    (const int                  sock,
     const struct sockaddr &    from,
     const size_t               addrLen,
     const mDNS::entry_type_t   entry,
     const uint16_t             queryId,
     const uint16_t             rType,
     const uint16_t             rClass,
     const uint32_t             ttl,
     CPtr(void)                 data,
     const size_t               size,
     const size_t               nameOffset,
     const size_t               nameLength,
     const size_t               recordOffset,
     const size_t               recordLength,
     Ptr(void)                  userData)
{
    NIMO_UNUSED_VAR_(sock);
    NIMO_UNUSED_VAR_(entry);
    NIMO_UNUSED_VAR_(queryId);
    NIMO_UNUSED_VAR_(rClass);
    NIMO_UNUSED_VAR_(nameLength);
    auto                    workOffset{nameOffset};
    mDNS::string_t          fromAddrStr{nImO::IpAddressToMdnsString(lAddrBuffer, sizeof(lAddrBuffer), from, addrLen)};
    mDNS::string_t          entryStr{mDNSP::string_extract(data, size, workOffset, lEntryBuffer, sizeof(lEntryBuffer))};
    auto                    handlerPtr{ReinterpretCast(Ptr(nImO::RecordHandler), userData)};
    nImO::RecordHandler &   handler{*handlerPtr};

    switch (rType)
    {
        case mDNS::kRecordTypePTR:
        {
            mDNS::string_t    nameStr{mDNS::record_parse_ptr(data, size, recordOffset, recordLength, nImO::SearchContext::gNameBuffer,
                                                             sizeof(nImO::SearchContext::gNameBuffer))};

            if (0 < ttl)
            {
                handler.processPtrData(entryStr, entry, nameStr);
            }
            else
            {
                handler.markDone();
            }
            release_mdns_string(nameStr);
        }
            break;

        case mDNS::kRecordTypeSRV:
        {
            mDNS::record_srv_t    srv{mDNS::record_parse_srv(data, size, recordOffset, recordLength, nImO::SearchContext::gNameBuffer,
                                                             sizeof(nImO::SearchContext::gNameBuffer))};

            if (0 < ttl)
            {
                handler.processSrvData(srv.port);
            }
            release_mdns_string(srv.name);
        }
            break;

        case mDNS::kRecordTypeA:
        {
            struct sockaddr_in    addr;

            mDNS::record_parse_a(data, size, recordOffset, recordLength, addr);
            mDNS::string_t    addrStr{nImO::Ipv4AddressToMdnsString(nImO::SearchContext::gNameBuffer, sizeof(nImO::SearchContext::gNameBuffer),
                                                                    addr, sizeof(addr))};

            if (0 < ttl)
            {
                handler.processAData(entryStr, addrStr);
            }
            release_mdns_string(addrStr);
        }
            break;

        case mDNS::kRecordTypeAAAA:
        {
            struct sockaddr_in6    addr;

            mDNS::record_parse_aaaa(data, size, recordOffset, recordLength, addr);
            mDNS::string_t    addrStr{nImO::Ipv6AddressToMdnsString(nImO::SearchContext::gNameBuffer, sizeof(nImO::SearchContext::gNameBuffer),
                                                                    addr, sizeof(addr))};

            if (0 < ttl)
            {
                handler.processAaaaData(entryStr, addrStr);
            }
            release_mdns_string(addrStr);
        }
            break;

        case mDNS::kRecordTypeTXT:
        {
            size_t    parsed{mDNS::record_parse_txt(data, size, recordOffset, recordLength, lTxtBuffer, numElementsInArray(lTxtBuffer))};

            for (size_t itxt{0}; itxt < parsed; ++itxt)
            {
                if (0 < ttl)
                {
                    handler.processTxtData(lTxtBuffer[itxt].key, lTxtBuffer[itxt].value);
                }
                release_mdns_string(lTxtBuffer[itxt].key);
                release_mdns_string(lTxtBuffer[itxt].value);
            }
        }
            break;

        default:
            break;

    }
    release_mdns_string(fromAddrStr);
    release_mdns_string(entryStr);
    return true;
} // queryCallback

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::SearchContext::SearchContext
    (const std::string &    tagForLogging,
     const bool             logging,
     const bool             startBrowser) :
        inherited{tagForLogging, logging, 4 /* browse + announce + send + receive */}, _buffer{new char[kBufferCapacity]},
        _numSockets{0}, _registrySearchConnection{kDefaultRegistrySearchConnection},
        _registrySearchMode{kDefaultRegistrySearchMode}, _browserThread{nullptr}, _registryName{kDefaultRegistryName},
        _startBrowser{startBrowser}
{
    ODL_ENTER(); //####
    ODL_S1s(tagForLogging); //####
    ODL_B2(logging, startBrowser); //####
    auto    retValue{GetConfiguredValue(kRegistryNameKey)};

    if (retValue)
    {
        SpValue actualValue{*retValue};

        if (auto asString{actualValue->asString()}; nullptr == asString)
        {
            std::cerr << "Invalid name (" << kRegistryNameKey << ") in configuration file; using default name.\n";
            _registryName = kDefaultRegistryName;
        }
        else
        {
            auto    candidate{asString->getValue()};

            if (std::regex_match(candidate, kNameMatch))
            {
                _registryName = candidate;
            }
            else
            {
                std::cerr << "Invalid name (" << kRegistryNameKey << ") in configuration file; using default name.\n";
                _registryName = kDefaultRegistryName;
            }
        }
    }
    retValue = GetConfiguredValue(kRegistryTimeoutKey);
    if (retValue)
    {
        SpValue actualValue{*retValue};

        if (auto asInteger{actualValue->asInteger()}; nullptr == asInteger)
        {
            std::cerr << "Invalid timeout (" << kRegistryTimeoutKey << ") in configuration file; using default.\n";
            _registrySearchTimeout = kDefaultRegistryTimeout;
        }
        else
        {
            auto    tempValue{StaticCast(int, asInteger->getIntegerValue())};

            if (0 < tempValue)
            {
                _registrySearchTimeout = tempValue;
            }
            else
            {
                std::cerr << "Invalid timeout (" << kRegistryTimeoutKey << ") in configuration file; using default.\n";
                _registrySearchTimeout = kDefaultRegistryTimeout;
            }
        }
    }
    else
    {
        _registrySearchTimeout = kDefaultRegistryTimeout;
    }
    retValue = GetConfiguredValue(kRegistrySearchRetriesKey);
    if (retValue)
    {
        SpValue actualValue{*retValue};

        if (auto asInteger{actualValue->asInteger()}; nullptr == asInteger)
        {
            std::cerr << "Invalid retries (" << kRegistrySearchRetriesKey << ") in configuration file; using default.\n";
            _registrySearchRetries = kDefaultRegistrySearchRetries;
        }
        else
        {
            auto    tempValue{StaticCast(int, asInteger->getIntegerValue())};

            if (0 < tempValue)
            {
                _registrySearchRetries = tempValue;
            }
            else
            {
                std::cerr << "Invalid retries (" << kRegistrySearchRetriesKey << ") in configuration file; using default.\n";
                _registrySearchRetries = kDefaultRegistrySearchRetries;
            }
        }
    }
    else
    {
        _registrySearchRetries = kDefaultRegistrySearchRetries;
    }
    // Get the address and port to use to search for the Registry.
    retValue = GetConfiguredValue(kRegistrySearchAddressKey);
    if (retValue)
    {
        SpValue actualValue{*retValue};

        if (auto asAddress{actualValue->asAddress()}; nullptr == asAddress)
        {
            std::cerr << "Invalid address (" << kRegistrySearchAddressKey << ") in configuration file; ignored.\n";
        }
        else
        {
            auto    tempValue{asAddress->getAddressValue()};

            if (239 == (tempValue >> 24))
            {
                _registrySearchConnection._address = tempValue;
            }
            else
            {
                std::cerr << "Invalid address (" << kRegistrySearchAddressKey << ") in configuration file; using default address.\n";
            }
        }
    }
    retValue = GetConfiguredValue(kRegistrySearchPortKey);
    if (retValue)
    {
        SpValue actualValue{*retValue};

        if (auto asInteger{actualValue->asInteger()}; nullptr == asInteger)
        {
            std::cerr << "Invalid port (" << kRegistrySearchPortKey << ") in configuration file; ignored.\n";
        }
        else
        {
            int64_t tempValue{asInteger->getIntegerValue()};

            if ((0 < tempValue) && (tempValue <= 0x0FFFF))
            {
                _registrySearchConnection._port = StaticCast(IPv4Port, tempValue);
            }
            else
            {
                std::cerr << "Invalid port (" << kRegistrySearchPortKey << ") in configuration file; using default port.\n";
            }
        }
    }
    retValue = GetConfiguredValue(kRegistryPathKey);
    if (retValue)
    {
        SpValue actualValue{*retValue};

        if (auto asString{actualValue->asString()}; nullptr == asString)
        {
            std::cerr << "Invalid path (" << kRegistryPathKey << ") in configuration file; using default path.\n";
            _registryLaunchPath = kDefaultRegistryLaunchPath;
        }
        else
        {
            _registryLaunchPath = asString->getValue();
        }
        if (3 < _registryLaunchPath.length())
        {
            if (_registryLaunchPath.substr(0, 3) == "$$/"s)
            {
                _registryLaunchPath = nImO_BIN_DIR_ + _registryLaunchPath.substr(3);
            }
        }
    }
    retValue = GetConfiguredValue(kRegistryOptionsKey);
    if (retValue)
    {
        SpValue actualValue{*retValue};

        _registryLaunchOptions.clear();
        if (auto asArray{actualValue->asArray()}; nullptr == asArray)
        {
            std::cerr << "Invalid options (" << kRegistryOptionsKey << ") in configuration file; ignored.\n";
        }
        else
        {
            for (const auto & walker : *asArray)
            {
                if (auto anOptionString{walker->asString()}; nullptr == anOptionString)
                {
                    ODL_LOG("(nullptr == anOptionString)"); //####
                }
                else
                {
                    _registryLaunchOptions.addValue(walker);
                }
            }
        }
    }
    retValue = GetConfiguredValue(kRegistrySearchModeKey);
    if (retValue)
    {
        SpValue actualValue{*retValue};

        if (auto asString{actualValue->asString()}; nullptr == asString)
        {
            std::cerr << "Invalid mode (" << kRegistrySearchModeKey << ") in configuration file; using default mode.\n";
            _registrySearchMode = kDefaultRegistrySearchMode;
        }
        else
        {
            auto    requested{asString->getValue()};
            auto    mode{modeFromName(requested)};

            if (RegistryMode::kUnknown == mode)
            {
                std::cerr << "Invalid mode (" << kRegistrySearchModeKey << ") in configuration file; using default mode.\n";
            }
            else
            {
                _registrySearchMode = mode;
            }
        }
    }
    if (getLoggingInfo() == _registrySearchConnection)
    {
        throw "The logging connection and the Registry search connection are the same."s;

    }
    else
    {
        if (getStatusInfo() == _registrySearchConnection)
        {
            throw "The Registry search connection and the status connection are the same."s;

        }
    }
    getLocalAddresses();
    openSockets();
    ODL_EXIT_P(this); //####
} // nImO::SearchContext::SearchContext

nImO::SearchContext::~SearchContext
    (void)
{
    ODL_OBJENTER(); //####
    DisableWaitForRegistry();
    stopGatheringAnnouncements();
    closeSockets();
    if (nullptr != _buffer)
    {
        delete[] _buffer;
        _buffer = nullptr;
    }
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::~SearchContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::SearchContext::checkReceiveQueue
    (void)
{
    ODL_OBJENTER(); //####
    if (_receiveQueue.hasMessage() && gKeepRunning)
    {
        auto    nextData{_receiveQueue.getNextMessage()};

        if (nImO::gKeepRunning)
        {
            if (nextData)
            {
                auto    contents{nextData->_receivedMessage};

                if (contents)
                {
                    if (auto asString{contents->asString()}; nullptr != asString)
                    {
                        auto            received{asString->getValue()};
                        StdStringVector pieces;

                        boost::algorithm::split(pieces, received, boost::is_any_of(kStatusSeparator));
                        if ((pieces.size() == 3) && (kRegistryResponse == pieces[0]))
                        {
                            int64_t intValue;

                            if (ConvertToInt64(pieces[2], intValue))
                            {
                                _registryPreferredAddress = pieces[1];
                                _registryPort = StaticCast(IPv4Port, intValue);
                                _haveAddress = _havePort = true;
                            }
                        }
                    }
                }
            }
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::checkReceiveQueue

void
nImO::SearchContext::closeSockets
    (void)
    const
{
    ODL_OBJENTER(); //####
    for (int isock{0}; isock < _numSockets; ++isock)
    {
        mDNS::socket_close(_sockets[isock]);
    }
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::closeSockets

void
nImO::SearchContext::executeBrowser
    (SearchContext &    owner)
{
    ODL_ENTER(); //####
    ODL_P1(&owner); //####
    ODL_I1(owner._numSockets); //####
    if (0 < owner._numSockets)
    {
        RecordHandler   handler{owner};
        struct timeval  timeout;

        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        owner.report("browser thread starting."s);
        lBrowserThreadStarted = true;
        ODL_B1(lBrowserThreadStarted); //####
        for ( ; ; )
        {
            if (lBrowserThreadStop || (owner._havePort && owner._haveAddress))
            {
                break;

            }
            int     nfds{0};
            fd_set  readfs;

            FD_ZERO(&readfs);
            for (int isock{0}; isock < owner._numSockets; ++isock)
            {
                if (lBrowserThreadStop)
                {
                    break;

                }
                if (owner._sockets[isock] >= nfds)
                {
                    nfds = owner._sockets[isock] + 1;
                }
#if (! MAC_OR_LINUX_OR_BSD_)
# pragma option push -w-csu
#endif /* not MAC_OR_LINUX_OR_BSD_ */
                FD_SET(owner._sockets[isock], &readfs);
#if (! MAC_OR_LINUX_OR_BSD_)
# pragma option pop
#endif /* not MAC_OR_LINUX_OR_BSD_ */
            }
            auto    res{select(nfds, &readfs, nullptr, nullptr, &timeout)};

            if (res >= 0)
            {
                for (int isock{0}; (0 < res) && (isock < owner._numSockets); ++isock)
                {
                    if (lBrowserThreadStop)
                    {
                        break;

                    }
                    if (FD_ISSET(owner._sockets[isock], &readfs))
                    {
                        mDNS::query_recv(owner._sockets[isock], owner._buffer, kBufferCapacity, queryCallback, &handler,
                                         owner._queryId[isock]);
                    }
#if (! MAC_OR_LINUX_OR_BSD_)
# pragma option push -w-csu
#endif /* not MAC_OR_LINUX_OR_BSD_ */
                    FD_SET(owner._sockets[isock], &readfs);
#if (! MAC_OR_LINUX_OR_BSD_)
# pragma option pop
#endif /* not MAC_OR_LINUX_OR_BSD_ */
                }
                if (owner._requestNewScan)
                {
                    owner._requestNewScan = false;
                    ODL_B1(owner._requestNewScan); //####
                    owner.report("Sending mDNS query: "s + owner.getRegistryServiceName() + "."s);
                    for (int isock{0}; isock < owner._numSockets; ++isock)
                    {
                        if (lBrowserThreadStop)
                        {
                            break;

                        }
                        owner._queryId[isock] = mDNS::query_send(owner._sockets[isock], mDNS::kRecordTypePTR, owner.getRegistryServiceName().c_str(),
                                                                 owner.getRegistryServiceName().length(), owner._buffer, kBufferCapacity, 0);
                        if (owner._queryId[isock] < 0)
                        {
                            owner.report("Failed to send mDNS query: "s + std::string(strerror(errno)) + "."s);
                        }
                    }
                }
            }
            else
            {
                break;

            }
        }
    }
    lBrowserThreadStarted = false;
    lBrowserThreadStopped = true;
    ODL_B2(lBrowserThreadStarted, lBrowserThreadStopped); //####
    owner.report("browser thread terminating."s);
    ODL_EXIT(); //####
} // nImO::SearchContext::executeBrowser

bool
nImO::SearchContext::findAndLaunchTheRegistry
    (void)
{
    ODL_OBJENTER(); //####
    bool    launched{false};
    bool    wasEnabled{lWaitForRegistry};

    lWaitForRegistry = false;
    lPerformSingleRegistryCheck = true;
    ODL_B2(lWaitForRegistry, lPerformSingleRegistryCheck); //####
    gatherAnnouncements();
    if ((! _havePort) || (! _haveAddress))
    {
        auto            regPath{_registryLaunchPath};
        auto            regOptions{_registryLaunchOptions};
        StdStringVector commandLine{};

        report("Registry was not found so it will be launched.");
        for (const auto & walker : regOptions)
        {
            if (auto anOptionString{walker->asString()}; nullptr == anOptionString)
            {
                ODL_LOG("(nullptr == anOptionString)"); //####
            }
            else
            {
                auto    anOption{anOptionString->getValue()};

                if (0 < anOption.length())
                {
                    auto    optionChar{anOption.substr(0, 1)};
                    auto    optionValue{anOption.substr(1, anOption.length())};

                    commandLine.push_back(MakeOption(optionChar));
                    if (! optionValue.empty())
                    {
                        commandLine.push_back(optionValue);
                    }
                }
                else
                {
                    ODL_LOG("! (0 < anOption.length())"); //####
                }
            }
        }
        // Add the standard logging option if the requesting application is being logged.
        if (loggingIsEnabled())
        {
            commandLine.push_back(kLoggingShortOptionString);
        }
#if (CALC_BOOST_VERSION_(1, 85) >= BOOST_VERSION)
        // We need to put the new process in it's own group so that it will be fully detached.
        BP::group   aGroup;

        aGroup.detach();
        // Make sure to 'throw away' any standard output from the child process.
        BP::child   cc{regPath, BP::args(commandLine), BP::std_out > BP::null, aGroup};

        cc.detach();
#else /* CALC_BOOST_VERSION_(1, 85) < BOOST_VERSION */
#endif /* CALC_BOOST_VERSION_(1, 85) < BOOST_VERSION */
        launched = true;
    }
    if (wasEnabled)
    {
        lWaitForRegistry = true;
        lPerformSingleRegistryCheck = false;
        ODL_B2(lWaitForRegistry, lPerformSingleRegistryCheck); //####
    }
    ODL_OBJEXIT_B(launched); //####
    return launched;
} // nImO::SearchContext::findAndLaunchTheRegistry

bool
nImO::SearchContext::findTheRegistry
    (Connection &   connection)
{
    ODL_OBJENTER(); //####
    ODL_P1(&connection); //####
    bool    found{false};

    if (lWaitForRegistry && ((! _havePort) || (! _haveAddress)))
    {
        gatherAnnouncements();
    }
    if (_havePort && _haveAddress)
    {
        connection._address = BAIP::make_address_v4(_registryPreferredAddress).to_uint();
        connection._port = _registryPort;
        stopGatheringAnnouncements();
        found = true;
    }
    ODL_OBJEXIT_B(found); //####
    return found;
} // nImO::SearchContext::findTheRegistry

void
nImO::SearchContext::gatherAnnouncements
    (void)
{
    ODL_OBJENTER(); //####
    if (_startBrowser && (RegistryMode::kUnknown != _registrySearchMode))
    {
        bool    okSoFar{true};

        lBrowserThreadStopped = lBrowserThreadStop = false;
        ODL_B2(lBrowserThreadStopped, lBrowserThreadStop); //####
        _havePort = _haveAddress = false;
        ODL_B2(_havePort, _haveAddress); //####
        if (RegistryMode::kMDNS == (RegistryMode::kMDNS & _registrySearchMode))
        {
            _browserThread = new boost::thread([this]
                                                (void)
                                                {
                                                    ODL_LOG("browser thread started"); //####
                                                    executeBrowser(*this);
                                                    ODL_LOG("browser thread ended"); //####
                                                });
            ODL_P1(_browserThread); //####
            _pool.add_thread(_browserThread);
            for (int isock{0}; isock < _numSockets; ++isock)
            {
                _queryId[isock] = mDNS::query_send(_sockets[isock], mDNS::kRecordTypePTR, getRegistryServiceName().c_str(),
                                                   getRegistryServiceName().length(), _buffer, kBufferCapacity, 0);
                if (_queryId[isock] < 0)
                {
                    report("Failed to send mDNS query: "s + std::string(strerror(errno)) + "."s);
                    okSoFar = false;
                    ODL_B1(okSoFar); //####
                }
            }
        }
        if (RegistryMode::kMulticast == (RegistryMode::kMulticast & _registrySearchMode))
        {
            if (setUpMulticastPorts())
            {
                sendGetAddressRequest();
            }
        }
        if (okSoFar)
        {
            _timedOut = false;
            _retryCount = 0;
            BAS_t   timeOutTimer{*getService()};
            int     maxTime{_registrySearchTimeout * _registrySearchRetries};

            report("Timeout = "s + std::to_string(maxTime) + " seconds."s);
            timeOutTimer.expires_after(std::chrono::seconds(_registrySearchTimeout));
            timeOutTimer.async_wait([this, &timeOutTimer]
                                    (const BSErr &  error)
                                    {
                                        if (error)
                                        {
                                            _timedOut = true;
                                        }
                                        else
                                        {
                                            handleTimerEvent(timeOutTimer);
                                        }
                                    });
            report("Waiting..."s);
            for ( ; (! _timedOut) && (! lStopRegistryLoop) && ((! _havePort) || (! _haveAddress)); )
            {
                boost::this_thread::yield();
                checkReceiveQueue();
            }
            if (! _timedOut)
            {
                timeOutTimer.cancel();
            }
        }
        stopGatheringAnnouncements();
    }
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::gatherAnnouncements

void
nImO::SearchContext::handleTimerEvent
    (BAS_t &    timer)
{
    ODL_OBJENTER(); //####
    ODL_P1(&timer); //####
    if (++_retryCount >= _registrySearchRetries)
    {
        report("Timed out!"s);
        _timedOut = true;
    }
    else
    {
        if (gKeepRunning && (RegistryMode::kMulticast == (RegistryMode::kMulticast & _registrySearchMode)))
        {
            sendGetAddressRequest();
        }
        timer.expires_after(std::chrono::seconds(_registrySearchTimeout));
        timer.async_wait([this, &timer]
                            (const BSErr &  error)
                            {
                                if (error)
                                {
                                    _timedOut = true;
                                }
                                else
                                {
                                    if (gKeepRunning)
                                    {
                                        report("Retrying..."s);
                                        handleTimerEvent(timer);
                                    }
                                    else
                                    {
                                        lStopRegistryLoop = true;
                                    }
                                }
                            });
    }
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::handleTimerEvent

nImO::RegistryMode
nImO::SearchContext::modeFromName
    (const std::string &    aName)
{
    ODL_ENTER(); //####
    ODL_S1s(aName); //####
    auto    mode{RegistryMode::kUnknown};
    auto    nameToCheck{ConvertToLowerCase(aName)};

    if (nameToCheck == modeToName(RegistryMode::kBoth))
    {
        mode = RegistryMode::kBoth;
    }
    else
    {
        if (nameToCheck == modeToName(RegistryMode::kMDNS))
        {
            mode = RegistryMode::kMDNS;
        }
        else
        {
            if (nameToCheck == modeToName(RegistryMode::kMulticast))
            {
                mode = RegistryMode::kMulticast;
            }
        }
    }
    ODL_EXIT_I(StaticCast(int, mode)); //####
    return mode;
} // nImO::SearchContext::modeFromName

std::string
nImO::SearchContext::modeToName
    (const RegistryMode aValue)
{
    ODL_ENTER(); //####
    ODL_I1(StaticCast(int64_t, aValue)); //####
    std::string result;

    switch (aValue)
    {
        case RegistryMode::kBoth :
            result = kModeBothName;
            break;

        case RegistryMode::kMDNS :
            result = kModeMdnsName;
            break;

        case RegistryMode::kMulticast :
            result = kModeMulticastName;
            break;

        default :
            result = kModeUnknownName;
            break;

    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::SearchContext::modeToName

void
nImO::SearchContext::openSockets
    (void)
{
    ODL_OBJENTER(); //####
    if (gHasIpv4)
    {
        struct sockaddr_in    sock_addr;

        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = INADDR_ANY;
        sock_addr.sin_port = htons(MDNS_PORT);
        auto    sock{mDNS::socket_open_ipv4(sock_addr)};

        if (sock >= 0)
        {
            _sockets[_numSockets++] = sock;
        }
    }
    if (gHasIpv6)
    {
        struct sockaddr_in6    sock_addr;

        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin6_family = AF_INET6;
        sock_addr.sin6_addr = in6addr_any;
        sock_addr.sin6_port = htons(MDNS_PORT);
        auto    sock{mDNS::socket_open_ipv6(sock_addr)};

        if (sock >= 0)
        {
            _sockets[_numSockets++] = sock;
        }
    }
    ODL_I1(_numSockets);
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::openSockets

void
nImO::SearchContext::sendGetAddressRequest
    (void)
{
    ODL_OBJENTER(); //####
    _registrySendPort->sendValue(std::make_shared<String>(kRegistryRequest));
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::sendGetAddressRequest

bool
nImO::SearchContext::setUpMulticastPorts
    (void)
{
    ODL_OBJENTER(); //####
    bool    okSoFar;

    _registryReceivePort = std::make_shared<nImO::ReceiveFromMulticast>(getService(), getRegistrySearchInfo(), _receiveQueue);
    ODL_P1(_registryReceivePort.get()); //####
    if (_registryReceivePort)
    {
        okSoFar = true;
    }
    else
    {
        report("The Registry multicast receive connection could not be established."s);
        okSoFar = false;
    }
    if (okSoFar)
    {
        _registrySendPort = std::make_shared<nImO::SendToMulticast>(getService(), _registrySearchConnection);
        ODL_P1(_registrySendPort.get()); //####
        if (! _registrySendPort)
        {
            report("The Registry multicast send connection could not be established."s);
            _registryReceivePort.reset();
            okSoFar = false;
        }
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::SearchContext::setUpMulticastPorts

void
nImO::SearchContext::stopGatheringAnnouncements
    (void)
{
    ODL_OBJENTER(); //####
    if (_startBrowser && (nullptr != _browserThread))
    {
        lBrowserThreadStop = true;
        ODL_B1(lBrowserThreadStop); //####
        if (lWaitForRegistry && lBrowserThreadStarted && (! lBrowserThreadStopped))
        {
            for ( ; ! lBrowserThreadStopped; )
            {
                boost::this_thread::yield();
            }
        }
        _browserThread->join();
        _browserThread = nullptr;
    }
    if (RegistryMode::kMulticast == (RegistryMode::kMulticast & _registrySearchMode))
    {
        _registryReceivePort.reset();
        _registrySendPort.reset();
    }
    ODL_OBJEXIT(); //####
} // nImO::SearchContext::stopGatheringAnnouncements

bool
nImO::SearchContext::waitForRegistry
    (void)
{
    ODL_OBJENTER(); //####
    bool    wasFound{false};

    if (lWaitForRegistry)
    {
        for ( ; (! lStopRegistryLoop) && ((! _havePort) || (! _haveAddress)); )
        {
            gatherAnnouncements();
        }
        wasFound = (_havePort && _haveAddress);
    }
    else
    {
        if (lPerformSingleRegistryCheck)
        {
            gatherAnnouncements();
            wasFound = (_havePort && _haveAddress);
        }
    }
    ODL_OBJEXIT_B(wasFound); //####
    return wasFound;
} // nImO::SearchContext::waitForRegistry

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::DisableWaitForRegistry
    (const bool allowOneCheck)
{
    ODL_ENTER(); //####
    ODL_B1(allowOneCheck); //####
    lWaitForRegistry = false;
    lPerformSingleRegistryCheck = allowOneCheck;
    ODL_B2(lWaitForRegistry, lPerformSingleRegistryCheck); //####
    ODL_EXIT(); //####
} // nImO::DisableWaitForRegistry

void
nImO::EnableWaitForRegistry
    (void)
{
    ODL_ENTER(); //####
    lWaitForRegistry = true;
    lPerformSingleRegistryCheck = false;
    ODL_B2(lWaitForRegistry, lPerformSingleRegistryCheck); //####
    ODL_EXIT(); //####
} // nImO::EnableWaitForRegistry

void
nImO::InterruptRegistryWait
    (void)
{
    ODL_ENTER(); //####
    lStopRegistryLoop = true;
    ODL_B1(lStopRegistryLoop); //####
    ODL_EXIT(); //####
} // nImO::InterruptRegistryWait

mDNS::string_t
nImO::IpAddressToMdnsString
    (Ptr(char)                  buffer,
     const size_t               capacity,
     const struct sockaddr &    addr,
     const size_t               addrLen)
{
    if (AF_INET6 == addr.sa_family)
    {
        return Ipv6AddressToMdnsString(buffer, capacity, ReinterpretCast(const struct sockaddr_in6 &, addr), addrLen);

    }
    return Ipv4AddressToMdnsString(buffer, capacity, ReinterpretCast(const struct sockaddr_in &, addr), addrLen);
} // nImO::IpAddressToMdnsString

mDNS::string_t
nImO::Ipv4AddressToMdnsString
    (Ptr(char)                  buffer,
     const size_t               capacity,
     const struct sockaddr_in & addr,
     const size_t               addrLen)
{
    char    host[NI_MAXHOST]{ 0 };
    char    service[NI_MAXSERV]{ 0 };
    auto    ret{getnameinfo(ReinterpretCast(CPtr(struct sockaddr), &addr), StaticCast(socklen_t, addrLen), host,
                            NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST)};
    int     len{0};

    if (0 == ret)
    {
        if (0 == addr.sin_port)
        {
            len = snprintf(buffer, capacity, "%s", host);
        }
        else
        {
            len = snprintf(buffer, capacity, "%s:%s", host, service);
        }
    }
    if (len >= StaticCast(int, capacity))
    {
        len = StaticCast(int, capacity) - 1;
    }
    return make_mdns_string(buffer, len);
} // nImO::Ipv4AddressToMdnsString

std::string
nImO::Ipv4AddressToStdString
    (const struct sockaddr_in & addr,
     const size_t               addrLen)
{
    char            addrBuffer[64];
    mDNS::string_t  mdnsString{nImO::Ipv4AddressToMdnsString(addrBuffer, sizeof(addrBuffer), addr, addrLen)};
    auto            result{mdns_string_to_std_string(mdnsString)};

    release_mdns_string(mdnsString);
    return result;
} // nImO::Ipv4AddressToStdString

mDNS::string_t
nImO::Ipv6AddressToMdnsString
    (Ptr(char)                      buffer,
     const size_t                   capacity,
     const struct sockaddr_in6 &    addr,
     const size_t                   addrLen)
{
    char    host[NI_MAXHOST]{ 0 };
    char    service[NI_MAXSERV]{ 0 };
    auto    ret{getnameinfo(ReinterpretCast(CPtr(struct sockaddr), &addr), StaticCast(socklen_t, addrLen), host,
                            NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST)};
    int     len{0};

    if (0 == ret)
    {
        if (0 == addr.sin6_port)
        {
            len = snprintf(buffer, capacity, "%s", host);
        }
        else
        {
            len = snprintf(buffer, capacity, "[%s]:%s", host, service);
        }
    }
    if (len >= StaticCast(int, capacity))
    {
        len = StaticCast(int, capacity) - 1;
    }
    return make_mdns_string(buffer, len);
} // nImO::Ipv6AddressToMdnsString

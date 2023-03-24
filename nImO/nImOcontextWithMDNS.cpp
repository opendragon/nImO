//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithMDNS.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO execution contexts that use mDNS.
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

#include <nImOcontextWithMDNS.h>

#include <nImOannounceServiceData.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if MAC_OR_LINUX_
//# include <netdb.h>
# include <ifaddrs.h>
#endif // MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO execution contexts that use mDNS. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The size of the MDNS I/O buffer. */
const size_t    kBufferCapacity = 2048;

/*! @brief @c true if an IPv4 address was found. */
static bool lHasIpv4 = false;

/*! @brief @c true if an IPv6 address was found. */
static bool lHasIpv6 = false;

/*! @brief @c true if the application needs to performa a single check for the Registry. */
static bool lPerformSingleRegistryCheck = false;

/*! @brief @c true if the application should wait for the Registry. */
static bool lWaitForRegistry = true;

/*! @brief The first IPv4 address found. */
static struct sockaddr_in   lServiceAddressIpv4;

/*@ @brief The first IPv6 address found. */
static struct sockaddr_in6  lServiceAddressIpv6;

/*! @brief Set to @c true to cause the announcer thread to terminate. */
static std::atomic<bool>    lAnnouncerThreadStop;

/*! @brief Set to @c true when the browser thread has started. */
static std::atomic<bool>    lBrowserThreadStarted;

/*! @brief Set to @c true to cause the browser thread to terminate. */
static std::atomic<bool>    lBrowserThreadStop;

/*! @brief Set to @c true when the browser thread has terminated. */
static std::atomic<bool>    lBrowserThreadStopped;

/*! @brief Set to @c true to cause the loop looking for the Registry to terminate. */
static std::atomic<bool>    lStopRegistryLoop;

/*! @brief The buffer used to hold an IP address. */
static char lAddrBuffer[64];

/*! @brief The buffer to hold a received mDNS reply structure. */
static char lEntryBuffer[256];

/*! @brief The buffer used to record the name from a mDNS request. */
static char lNameBuffer[256];

/*! @brief The buffer used to send replies for mDNS requests. */
static char lSendBuffer[1024];

/*! @brief The buffer used to hold TXT records from a received mDNS reply structure. */
static mDNS::record_txt_t   lTxtBuffer[128];

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
                (nImO::ContextWithMDNS &    owner) :
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
                std::string             outString;
                std::string::size_type  period = inString.find('.');

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
                    _owner._havePort = false;
                    _owner._haveAddress = false;
                    _processing = false;
                }
            }

            /* @brief Handle an A record.
             @param[in] entryData The name of the server.
             @param[in] aData The IPv4 address of the server. */
            inline void
            processAData
                (const mDNS::string_t &    entryData,
                 const mDNS::string_t &    aData)
            {
                NIMO_UNUSED_ARG_(entryData);
                NIMO_UNUSED_ARG_(aData);
                if (_processing)
                {
                    // Note that the A records are ignored.
                    _owner.report("A Data");
                }
            }

            /* @brief Handle an AAAA record.
             @param[in] entryData The name of the server.
             @param[in] aaaaData The IPv6 address of the server. */
            inline void
            processAaaaData
                (const mDNS::string_t &    entryData,
                 const mDNS::string_t &    aaaaData)
            {
                NIMO_UNUSED_ARG_(entryData);
                NIMO_UNUSED_ARG_(aaaaData);
                if (_processing)
                {
                    // Note that the AAAA records are ignored.
                    _owner.report("AAAA Data");
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
                    std::string _entryData = mdns_string_to_std_string(entryData);

                    if (NIMO_REGISTRY_SERVICE_NAME == _entryData)
                    {
                        _owner.report("PTR Data");
                        _owner._registryTag = firstPartOfPath(mdns_string_to_std_string(ptrData));
                        _owner._havePort = false;
                        _owner._haveAddress = false;
                        _processing = true;
                    }
                    else
                    {
                        _processing = false;
                    }
                }
                else
                {
                    _processing = false;
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
                    _owner.report("SRV Data");
                    _owner._registryPort = port;
                    _owner._havePort = true;
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
                    std::string keyString{mdns_string_to_std_string(keyData)};

                    if (NIMO_REGISTRY_ADDRESS_KEY == keyString)
                    {
                        _owner.report("TXT Data");
                        _owner._registryPreferredAddress = mdns_string_to_std_string(valueData);
                        _owner._haveAddress = true;
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
            nImO::ContextWithMDNS & _owner;

            /*! @brief @c true if this record is to be processed. */
            bool    _processing;

    }; // RecordHandler

} // nImO

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Find the IPv4 and IPv6 addresses for the machine, if available. */
static void
getLocalAddresses
    (void)
{
#if MAC_OR_LINUX_
    Ptr(struct ifaddrs)         addresses = nullptr;
#else // not MAC_OR_LINUX_
    Ptr(IP_ADAPTER_ADDRESSES)   adapterAddress = nullptr;
    ULONG                       addressSize = 8000;
    uint                        ret;
    uint                        numRetries = 4;
#endif // not MAC_OR_LINUX_

    ODL_ENTER(); //####
#if MAC_OR_LINUX_
    if (-1 == getifaddrs(&addresses))
    {
        throw "Failed to get network adapter addresses";
    }
    bool    firstIpv4 = true;
    bool    firstIpv6 = true;

    for (Ptr(struct ifaddrs) address = addresses; nullptr != address; address = address->ifa_next)
    {
        if (AF_INET == address->ifa_addr->sa_family)
        {
            struct sockaddr_in &    saddr = *ReinterpretCast(Ptr(struct sockaddr_in), address->ifa_addr);

            if (IPV4_ADDR(127, 0, 0, 1) != ntohl(saddr.sin_addr.s_addr))
            {
                if (firstIpv4)
                {
                    lServiceAddressIpv4 = saddr;
                    firstIpv4 = false;
                }
                lHasIpv4 = true;
            }
        }
        else if (AF_INET6 == address->ifa_addr->sa_family)
        {
            struct sockaddr_in6 &   saddr = *ReinterpretCast(Ptr(struct sockaddr_in6), address->ifa_addr);
            static const uint8_t    localHost[] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 1 };
            static const uint8_t    localHostMapped[] = { 0, 0, 0,    0,    0,    0, 0, 0,
                                                          0, 0, 0xff, 0xff, 0x7f, 0, 0, 1 };

            if ((0 == (IFF_LOOPBACK & address->ifa_flags)) &&
                (0 != memcmp(saddr.sin6_addr.s6_addr, localHost, sizeof(localHost))) &&
                (0 != memcmp(saddr.sin6_addr.s6_addr, localHostMapped, sizeof(localHostMapped))))
            {
                if (firstIpv6)
                {
                    lServiceAddressIpv6 = saddr;
                    firstIpv6 = false;
                }
                lHasIpv6 = true;
            }
        }
    }
    freeifaddrs(addresses);
#else // not MAC_OR_LINUX_
    do
    {
        adapterAddress = ReinterpretCast(Ptr(IP_ADAPTER_ADDRESSES), malloc(addressSize));
        ret = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_ANYCAST, 0, adapterAddress,
                                   &addressSize);
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
        throw "Failed to get network adapter addresses";
    }
    bool    firstIpv4 = true;
    bool    firstIpv6 = true;

    for (PIP_ADAPTER_ADDRESSES adapter = adapterAddress; nullptr != adapter; adapter = adapter->Next)
    {
        if (TUNNEL_TYPE_TEREDO == adapter->TunnelType)
        {
            continue;

        }
        if (adapter->OperStatus != IfOperStatusUp)
        {
            continue;

        }
        for (Ptr(IP_ADAPTER_UNICAST_ADDRESS) unicast = adapter->FirstUnicastAddress; nullptr != unicast;
             unicast = unicast->Next)
        {
            if (AF_INET == unicast->Address.lpSockaddr->sa_family)
            {
                struct sockaddr_in &    saddr = *ReinterpretCast(Ptr(struct sockaddr_in), unicast->Address.lpSockaddr);

                if ((saddr.sin_addr.S_un.S_un_b.s_b1 != 127) || (saddr.sin_addr.S_un.S_un_b.s_b2 != 0) ||
                    (saddr.sin_addr.S_un.S_un_b.s_b3 != 0) || (saddr.sin_addr.S_un.S_un_b.s_b4 != 1))
                {
                    if (firstIpv4)
                    {
                        lServiceAddressIpv4 = saddr;
                        firstIpv4 = false;
                    }
                    lHasIpv4 = true;
                }
            }
            else if (AF_INET6 == unicast->Address.lpSockaddr->sa_family)
            {
                struct sockaddr_in6 &   saddr = *ReinterpretCast(Ptr(struct sockaddr_in6), unicast->Address.lpSockaddr);
                static const uchar      localHost[] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 0, 1 };
                static const uchar      localHostMapped[] = { 0, 0, 0,    0,    0,    0, 0, 0,
                                                              0, 0, 0xff, 0xff, 0x7f, 0, 0, 1 };

                if ((NldsPreferred == unicast->DadState) &&
                    (0 != memcmp(saddr.sin6_addr.s6_addr, localHost, sizeof(localHost))) &&
                    (0 != memcmp(saddr.sin6_addr.s6_addr, localHostMapped, sizeof(localHostMapped))))
                {
                    if (firstIpv6)
                    {
                        lServiceAddressIpv6 = saddr;
                        firstIpv6 = false;
                    }
                    lHasIpv6 = true;
                }
            }
        }
    }
    free(adapterAddress);
#endif // not MAC_OR_LINUX_
    if ((! lHasIpv4) && (! lHasIpv6))
    {
        throw "No usable network addresses found.";
    }
    ODL_EXIT(); //####
} // getLocalAddresses

/*! @brief Handle received mDNS service requests. */
static bool
announcementServiceCallback
    (const int                  sock,
     const struct sockaddr &    from,
     const size_t               addrLen,
     mDNS::entry_type_t         entry,
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
    bool    result;

    NIMO_UNUSED_ARG_(ttl);
    NIMO_UNUSED_ARG_(nameLength);
    NIMO_UNUSED_ARG_(recordOffset);
    NIMO_UNUSED_ARG_(recordLength);
    if ((mDNS::kEntryTypeQuestion == entry) && (! lAnnouncerThreadStop))
    {
        const char                          kDnsSd[] = "_services._dns-sd._udp.local.";
        CPtr(nImO::AnnounceServiceData)     servicePtr = ReinterpretCast(CPtr(nImO::AnnounceServiceData), userData);
        const nImO::AnnounceServiceData &   serviceData = *servicePtr;
        size_t                              offset = nameOffset;
        mDNS::string_t                      name = mDNS::mDNSPrivate::string_extract(data, size, offset, lNameBuffer,
                                                                                     sizeof(lNameBuffer));

        if (((sizeof(kDnsSd) - 1) == name.length) && (0 == strncmp(name.str, kDnsSd, sizeof(kDnsSd) - 1)))
        {
            if ((mDNS::kRecordTypePTR == rType) || (mDNS::kRecordTypeANY == rType))
            {
                // The PTR query was for the DNS-SD domain, send answer with a PTR record for the
                // service name we advertise, typically on the "<_service-name>._tcp.local." format

                // Answer PTR record reverse mapping "<_service-name>._tcp.local." to
                // "<hostname>.<_service-name>._tcp.local."
                mDNS::record_t  answer;
                // Send the answer, unicast or multicast depending on flag in query
                bool            unicast = (0 != (rClass & MDNS_UNICAST_RESPONSE));

                answer.name = name;
                answer.type = mDNS::kRecordTypePTR;
                answer.data.ptr.name = serviceData._serviceName;
                if (unicast)
                {
                    mDNS::query_answer_unicast(sock, &from, addrLen, lSendBuffer, sizeof(lSendBuffer), queryId,
                                               StaticCast(mDNS::record_type_t, rType), name.str, name.length, answer,
                                               nullptr, 0, nullptr, 0);
                }
                else
                {
                    mDNS::query_answer_multicast(sock, lSendBuffer, sizeof(lSendBuffer), answer, nullptr, 0, nullptr, 0);
                }
            }
        }
        else if ((name.length == serviceData._serviceName.length) &&
                 (0 == strncmp(name.str, serviceData._serviceName.str, name.length)))
        {
            if ((mDNS::kRecordTypePTR == rType) || (mDNS::kRecordTypeANY == rType))
            {
                // The PTR query was for our service (usually "<_service-name._tcp.local"), answer a PTR
                // record reverse mapping the queried service name to our service instance name
                // (typically on the "<hostname>.<_service-name>._tcp.local." format), and add
                // additional records containing the SRV record mapping the service instance name to our
                // qualified hostname (typically "<hostname>.local.") and port, as well as any IPv4/IPv6
                // address for the hostname as A/AAAA records, and two test TXT records

                // Answer PTR record reverse mapping "<_service-name>._tcp.local." to
                // "<hostname>.<_service-name>._tcp.local."
                mDNS::record_t  answer = serviceData._recordPTR;
                mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                size_t          additionalCount = 0;

                // SRV record mapping "<hostname>.<_service-name>._tcp.local." to
                // "<hostname>.local." with port. Set weight & priority to 0.
                memset(&additional, 0, sizeof(additional));
                additional[additionalCount++] = serviceData._recordSRV;
                // A/AAAA records mapping "<hostname>.local." to IPv4/IPv6 addresses
                if (AF_INET == serviceData._addressIpv4.sin_family)
                {
                    additional[additionalCount++] = serviceData._recordA;
                }
                if (AF_INET6 == serviceData._addressIpv6.sin6_family)
                {
                    additional[additionalCount++] = serviceData._recordAAAA;
                }
                // Add TXT records for our service instance name, will be coalesced into
                // one record with both key-value pair strings by the library
                for (size_t ii = 0; ii < nImO::kNumTxtRecords; ++ii)
                {
                    additional[additionalCount++] = serviceData._recordTXT[ii];
                }
                // Send the answer, unicast or multicast depending on flag in query
                bool    unicast = (0 != (rClass & MDNS_UNICAST_RESPONSE));

                // Send the answer, unicast or multicast depending on flag in query
                if (unicast)
                {
                    mDNS::query_answer_unicast(sock, &from, addrLen, lSendBuffer, sizeof(lSendBuffer), queryId,
                                               StaticCast(mDNS::record_type_t, rType), name.str, name.length, answer,
                                               nullptr, 0, additional, additionalCount);
                }
                else
                {
                    mDNS::query_answer_multicast(sock, lSendBuffer, sizeof(lSendBuffer), answer, nullptr, 0, additional,
                                                 additionalCount);
                }
            }
        }
        else if ((name.length == serviceData._serviceInstance.length) &&
                 (0 == strncmp(name.str, serviceData._serviceInstance.str, name.length)))
        {
            if ((mDNS::kRecordTypeSRV == rType) || (mDNS::kRecordTypeANY == rType))
            {
                // The SRV query was for our service instance (usually
                // "<hostname>.<_service-name._tcp.local"), answer a SRV record mapping the service
                // instance name to our qualified hostname (typically "<hostname>.local.") and port, as
                // well as any IPv4/IPv6 address for the hostname as A/AAAA records, and two test TXT
                // records

                // Answer PTR record reverse mapping "<_service-name>._tcp.local." to
                // "<hostname>.<_service-name>._tcp.local."
                mDNS::record_t  answer = serviceData._recordSRV;
                mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                size_t          additionalCount = 0;

                // A/AAAA records mapping "<hostname>.local." to IPv4/IPv6 addresses
                memset(&additional, 0, sizeof(additional));
                if (AF_INET == serviceData._addressIpv4.sin_family)
                {
                    additional[additionalCount++] = serviceData._recordA;
                }
                if (AF_INET6 == serviceData._addressIpv6.sin6_family)
                {
                    additional[additionalCount++] = serviceData._recordAAAA;
                }
                // Add TXT records for our service instance name, will be coalesced into
                // one record with both key-value pair strings by the library
                for (size_t ii = 0; ii < nImO::kNumTxtRecords; ++ii)
                {
                    additional[additionalCount++] = serviceData._recordTXT[ii];
                }
                // Send the answer, unicast or multicast depending on flag in query
                bool    unicast = (0 != (rClass & MDNS_UNICAST_RESPONSE));

                if (unicast)
                {
                    mDNS::query_answer_unicast(sock, &from, addrLen, lSendBuffer, sizeof(lSendBuffer), queryId,
                                               StaticCast(mDNS::record_type_t, rType), name.str, name.length, answer,
                                               nullptr, 0, additional, additionalCount);
                }
                else
                {
                    mDNS::query_answer_multicast(sock, lSendBuffer, sizeof(lSendBuffer), answer, nullptr, 0, additional,
                                                 additionalCount);
                }
            }
        }
        else if ((name.length == serviceData._hostNameQualified.length) &&
                 (0 == strncmp(name.str, serviceData._hostNameQualified.str, name.length)))
        {
            if (((mDNS::kRecordTypeA == rType) || (mDNS::kRecordTypeANY == rType)) &&
                (AF_INET == serviceData._addressIpv4.sin_family))
            {
                // The A query was for our qualified hostname (typically "<hostname>.local.") and we
                // have an IPv4 address, answer with an A record mapping the hostname to an IPv4
                // address, as well as any IPv6 address for the hostname, and two test TXT records

                // Answer A records mapping "<hostname>.local." to IPv4 address
                mDNS::record_t  answer = serviceData._recordA;
                mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                size_t          additionalCount = 0;

                // AAAA record mapping "<hostname>.local." to IPv6 addresses
                memset(&additional, 0, sizeof(additional));
                if (AF_INET6 == serviceData._addressIpv6.sin6_family)
                {
                    additional[additionalCount++] = serviceData._recordAAAA;
                }
                // Add TXT records for our service instance name, will be coalesced into
                // one record with both key-value pair strings by the library
                for (size_t ii = 0; ii < nImO::kNumTxtRecords; ++ii)
                {
                    additional[additionalCount++] = serviceData._recordTXT[ii];
                }
                // Send the answer, unicast or multicast depending on flag in query
                bool    unicast = (0 != (rClass & MDNS_UNICAST_RESPONSE));

                if (unicast)
                {
                    mDNS::query_answer_unicast(sock, &from, addrLen, lSendBuffer, sizeof(lSendBuffer), queryId,
                                               StaticCast(mDNS::record_type_t, rType), name.str, name.length, answer,
                                               nullptr, 0, additional, additionalCount);
                }
                else
                {
                    mDNS::query_answer_multicast(sock, lSendBuffer, sizeof(lSendBuffer), answer, nullptr, 0, additional,
                                                 additionalCount);
                }
            }
            else if (((mDNS::kRecordTypeAAAA == rType) || (mDNS::kRecordTypeANY == rType)) &&
                     (AF_INET6 == serviceData._addressIpv6.sin6_family))
            {
                // The AAAA query was for our qualified hostname (typically "<hostname>.local.") and we
                // have an IPv6 address, answer with an AAAA record mappiing the hostname to an IPv6
                // address, as well as any IPv4 address for the hostname, and two test TXT records

                // Answer AAAA records mapping "<hostname>.local." to IPv6 address
                mDNS::record_t  answer = serviceData._recordAAAA;
                mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                size_t          additionalCount = 0;

                // A record mapping "<hostname>.local." to IPv4 addresses
                memset(&additional, 0, sizeof(additional));
                if (AF_INET == serviceData._addressIpv4.sin_family)
                {
                    additional[additionalCount++] = serviceData._recordA;
                }
                // Add TXT records for our service instance name, will be coalesced into
                // one record with both key-value pair strings by the library
                for (size_t ii = 0; ii < nImO::kNumTxtRecords; ++ii)
                {
                    additional[additionalCount++] = serviceData._recordTXT[ii];
                }
                // Send the answer, unicast or multicast depending on flag in query
                bool    unicast = (0 != (rClass & MDNS_UNICAST_RESPONSE));

                if (unicast)
                {
                    mDNS::query_answer_unicast(sock, &from, addrLen, lSendBuffer, sizeof(lSendBuffer), queryId,
                                               StaticCast(mDNS::record_type_t, rType), name.str, name.length, answer,
                                               nullptr, 0, additional, additionalCount);
                }
                else
                {
                    mDNS::query_answer_multicast(sock, lSendBuffer, sizeof(lSendBuffer), answer, nullptr, 0, additional,
                                                 additionalCount);
                }
            }
        }
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
} // announcementServiceCallback

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
    NIMO_UNUSED_ARG_(sock);
    NIMO_UNUSED_ARG_(entry);
    NIMO_UNUSED_ARG_(queryId);
    NIMO_UNUSED_ARG_(rClass);
    NIMO_UNUSED_ARG_(nameLength);
    size_t                      workOffset = nameOffset;
    mDNS::string_t              fromAddrStr = nImO::IpAddressToMdnsString(lAddrBuffer, sizeof(lAddrBuffer), from, addrLen);
    mDNS::string_t              entryStr = mDNS::mDNSPrivate::string_extract(data, size, workOffset, lEntryBuffer,
                                                                             sizeof(lEntryBuffer));
    Ptr(nImO::RecordHandler)    handlerPtr = ReinterpretCast(Ptr(nImO::RecordHandler), userData);
    nImO::RecordHandler &       handler = *handlerPtr;

//#if DUMP_RAW_DATA
//    dumpData(data, size, name_offset, record_offset, record_length, entry, rtype, rclass, ttl);
//#endif /* DUMP_RAW_DATA */
    switch (rType)
    {
        case mDNS::kRecordTypePTR:
        {
            mDNS::string_t    nameStr = mDNS::record_parse_ptr(data, size, recordOffset, recordLength, lNameBuffer,
                                                               sizeof(lNameBuffer));

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
            mDNS::record_srv_t    srv = mDNS::record_parse_srv(data, size, recordOffset, recordLength, lNameBuffer,
                                                               sizeof(lNameBuffer));

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
            mDNS::string_t    addrStr = nImO::Ipv4AddressToMdnsString(lNameBuffer, sizeof(lNameBuffer), addr, sizeof(addr));

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
            mDNS::string_t    addrStr = nImO::Ipv6AddressToMdnsString(lNameBuffer, sizeof(lNameBuffer), addr, sizeof(addr));

            if (0 < ttl)
            {
                handler.processAaaaData(entryStr, addrStr);
            }
            release_mdns_string(addrStr);
        }
            break;

        case mDNS::kRecordTypeTXT:
        {
            size_t    parsed = mDNS::record_parse_txt(data, size, recordOffset, recordLength, lTxtBuffer,
                                                      A_SIZE(lTxtBuffer));

            for (size_t itxt = 0; itxt < parsed; ++itxt)
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

nImO::ContextWithMDNS::ContextWithMDNS
    (const std::string &    executableName,
     const std::string &    tag,
     const bool             logging,
     const ThreadMode       whichThreads,
     const std::string &    nodeName) :
        inherited(executableName, tag, logging, 2 /* browse + announce */, nodeName), _numSockets(0),
        _whichThreads(whichThreads), _announceData(nullptr), _buffer(new char[kBufferCapacity])
{
    ODL_ENTER(); //####
    //ODL_S3s("progName = ", executableName, "tag = ", tag, "nodeName = ", nodeName); //####
    //ODL_B1("logging = ", logging); //####
    getLocalAddresses();
    openSockets();
    ODL_EXIT_P(this); //####
} // nImO::ContextWithMDNS::ContextWithMDNS

nImO::ContextWithMDNS::~ContextWithMDNS
    (void)
{
    ODL_OBJENTER(); //####
    stopGatheringAnnouncements();
    removeAnnouncement();
    closeSockets();
    if (nullptr != _announceData)
    {
        delete _announceData;
    }
    if (nullptr != _buffer)
    {
        delete[] _buffer;
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::~ContextWithMDNS

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::ContextWithMDNS::closeSockets
    (void)
{
    ODL_OBJENTER(); //####
    for (int isock = 0; isock < _numSockets; ++isock)
    {
        mDNS::socket_close(_sockets[isock]);
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::closeSockets

void
nImO::ContextWithMDNS::executeAnnouncer
    (ContextWithMDNS &  owner)
{
    struct timeval timeout;

    ODL_ENTER(); //####
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    owner.report("Announcer thread starting.");
    for ( ; ; )
    {
        if (lAnnouncerThreadStop)
        {
            break;

        }
        int     nfds = 0;
        fd_set  readfs;

        FD_ZERO(&readfs);
        for (int isock = 0; isock < owner._numSockets; ++isock)
        {
            if (lAnnouncerThreadStop)
            {
                break;

            }
            if (owner._sockets[isock] >= nfds)
            {
                nfds = owner._sockets[isock] + 1;
            }
#if (! MAC_OR_LINUX_)
# pragma option push -w-csu
#endif /* not MAC_OR_LINUX_ */
            FD_SET(owner._sockets[isock], &readfs);
#if (! MAC_OR_LINUX_)
# pragma option pop
#endif /* not MAC_OR_LINUX_ */
        }
        if (! lAnnouncerThreadStop)
        {
            int    res = select(nfds, &readfs, nullptr, nullptr, &timeout);

            if (res >= 0)
            {
                for (int isock = 0; (0 < res) && (isock < owner._numSockets); ++isock)
                {
                    if (lAnnouncerThreadStop)
                    {
                        break;

                    }
                    if (FD_ISSET(owner._sockets[isock], &readfs))
                    {
                        mDNS::socket_listen(owner._sockets[isock], owner._buffer, kBufferCapacity,
                                            announcementServiceCallback, owner._announceData);
                    }
#if (! MAC_OR_LINUX_)
# pragma option push -w-csu
#endif /* not MAC_OR_LINUX_ */
                    FD_SET(owner._sockets[isock], &readfs);
#if (! MAC_OR_LINUX_)
# pragma option pop
#endif /* not MAC_OR_LINUX_ */
                }
            }
            else
            {
                break;

            }
        }
    }
    owner.report("Announcer thread terminating.");
    ODL_EXIT(); //####
} // nImO::ContextWithMDNS::executeAnnouncer

void
nImO::ContextWithMDNS::executeBrowser
    (ContextWithMDNS &  owner)
{
    RecordHandler   handler(owner);
    struct timeval  timeout;

    ODL_ENTER(); //####
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    owner.report("Browser thread starting.");
    lBrowserThreadStarted = true;
    for ( ; ; )
    {
        if (lBrowserThreadStop || (owner._havePort && owner._haveAddress))
        {
            break;

        }
        int     nfds = 0;
        fd_set  readfs;

        FD_ZERO(&readfs);
        for (int isock = 0; isock < owner._numSockets; ++isock)
        {
            if (lBrowserThreadStop)
            {
                break;

            }
            if (owner._sockets[isock] >= nfds)
            {
                nfds = owner._sockets[isock] + 1;
            }
#if (! MAC_OR_LINUX_)
# pragma option push -w-csu
#endif /* not MAC_OR_LINUX_ */
            FD_SET(owner._sockets[isock], &readfs);
#if (! MAC_OR_LINUX_)
# pragma option pop
#endif /* not MAC_OR_LINUX_ */
        }
        int    res = select(nfds, &readfs, nullptr, nullptr, &timeout);

        if (res >= 0)
        {
            for (int isock = 0; (0 < res) && (isock < owner._numSockets); ++isock)
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
#if (! MAC_OR_LINUX_)
# pragma option push -w-csu
#endif /* not MAC_OR_LINUX_ */
                FD_SET(owner._sockets[isock], &readfs);
#if (! MAC_OR_LINUX_)
# pragma option pop
#endif /* not MAC_OR_LINUX_ */
            }
            if (owner._requestNewScan)
            {
                owner._requestNewScan = false;
                owner.report("Sending mDNS query: " + std::string(NIMO_REGISTRY_SERVICE_NAME));
                for (int isock = 0; isock < owner._numSockets; ++isock)
                {
                    if (lBrowserThreadStop)
                    {
                        break;

                    }
                    owner._queryId[isock] = mDNS::query_send(owner._sockets[isock], mDNS::kRecordTypePTR,
                                                               NIMO_REGISTRY_SERVICE_NAME,
                                                               sizeof(NIMO_REGISTRY_SERVICE_NAME) - 1, owner._buffer,
                                                               kBufferCapacity, 0);
                    if (owner._queryId[isock] < 0)
                    {
                        owner.report("Failed to send mDNS query: " + std::string(strerror(errno)));
                    }
                }
            }
        }
        else
        {
            break;

        }
    }
    lBrowserThreadStarted = false;
    lBrowserThreadStopped = true;
    owner.report("Browser thread terminating.");
    ODL_EXIT(); //####
} // nImO::ContextWithMDNS::executeBrowser

bool
nImO::ContextWithMDNS::findRegistry
    (Connection &   connection,
     const bool     quietly)
{
    bool    found;

    ODL_OBJENTER(); //####
    if (lWaitForRegistry && ((! _havePort) || (! _haveAddress)))
    {
        gatherAnnouncements(quietly);
    }
    if (_havePort && _haveAddress)
    {
        connection._address = asio::ip::address_v4::from_string(_registryPreferredAddress).to_ulong();
        connection._port = _registryPort;
        found = true;
    }
    else
    {
        found = false;
    }
    ODL_OBJEXIT_B(found); //####
    return found;
} // nImO::ContextWithMDNS::findRegistry

void
nImO::ContextWithMDNS::gatherAnnouncements
    (const bool quietly)
{
    ODL_OBJENTER(); //####
    if (ThreadMode::LaunchBrowser == (ThreadMode::LaunchBrowser & _whichThreads))
    {
        bool    okSoFar = true;

        lBrowserThreadStopped = false;
        lBrowserThreadStop = false;
        _havePort = false;
        _haveAddress = false;
        _pool.create_thread([this]
                            (void)
                            {
                                executeBrowser(*this);
                            });
        for (int isock = 0; isock < _numSockets; ++isock)
        {
            _queryId[isock] = mDNS::query_send(_sockets[isock], mDNS::kRecordTypePTR, NIMO_REGISTRY_SERVICE_NAME,
                                               sizeof(NIMO_REGISTRY_SERVICE_NAME) - 1, _buffer, kBufferCapacity, 0);
            if (_queryId[isock] < 0)
            {
                report("Failed to send mDNS query: " + std::string(strerror(errno)));
                okSoFar = false;
            }
        }
        if (okSoFar)
        {
            std::atomic<bool>       timedOut(false);
            asio::deadline_timer    timeOutTimer(*getService());

            report("timeout = " + std::to_string(getRegistrySearchTimeout()));
            timeOutTimer.expires_from_now(posix_time::seconds(getRegistrySearchTimeout()));
            timeOutTimer.async_wait([this, quietly, &timedOut]
                                   (const system::error_code &  error)
                                   {
                                       if (0 == error.value())
                                       {
                                           if (! quietly)
                                           {
                                               report("timed out!");
                                           }
                                           timedOut = true;
                                       }
                                   });
            if (! quietly)
            {
                report("waiting...");
            }
            for ( ; (! timedOut) && (! lStopRegistryLoop) && ((! _havePort) || (! _haveAddress)); )
            {
                thread::yield();
            }
            if (! timedOut)
            {
                timeOutTimer.cancel();
            }
        }
        stopGatheringAnnouncements();
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::gatherAnnouncements

bool
nImO::ContextWithMDNS::makePortAnnouncement
    (const uint16_t         port,
     const std::string &    serviceName,
     const std::string &    hostName,
     const std::string &    dataKey)
{
    bool    okSoFar;

    ODL_OBJENTER(); //####
    if (nullptr != _announceData)
    {
        delete _announceData;
        _announceData = nullptr;
    }
    if (ThreadMode::LaunchAnnouncer == (ThreadMode::LaunchAnnouncer & _whichThreads))
    {
        char        addressBuffer[64];
        std::string hostAddress;

        lAnnouncerThreadStop = false;
        _announceData = new AnnounceServiceData(lServiceAddressIpv4, lServiceAddressIpv6);
        _pool.create_thread([this]
                            (void)
                            {
                                executeAnnouncer(*this);
                            });
        if (lHasIpv4)
        {
            mDNS::string_t  addressString{Ipv4AddressToMdnsString(addressBuffer, sizeof(addressBuffer), lServiceAddressIpv4,
                                                                  sizeof(lServiceAddressIpv4))};

            hostAddress = addressString.str;
            release_mdns_string(addressString);
        }
        else if (lHasIpv6)
        {
            mDNS::string_t  addressString{Ipv6AddressToMdnsString(addressBuffer, sizeof(addressBuffer), lServiceAddressIpv6,
                                                                  sizeof(lServiceAddressIpv6))};

            hostAddress = addressString.str;
            release_mdns_string(addressString);
        }
        else
        {
            hostAddress = SELF_ADDRESS_IPADDR_;
        }
        okSoFar = _announceData->setServiceData(port, serviceName, hostName, dataKey, hostAddress);
        if (okSoFar)
        {
            // Send an announcement on startup of service
            mDNS::record_t    additional[kNumTxtRecords + 3];
            size_t            additionalCount = 0;

            memset(additional, 0, sizeof(additional));
            additional[additionalCount++] = _announceData->_recordSRV;
            if (AF_INET == _announceData->_addressIpv4.sin_family)
            {
                additional[additionalCount++] = _announceData->_recordA;
            }
            if (AF_INET6 == _announceData->_addressIpv6.sin6_family)
            {
                additional[additionalCount++] = _announceData->_recordAAAA;
            }
            for (size_t ii = 0; ii < kNumTxtRecords; ++ii)
            {
                additional[additionalCount++] = _announceData->_recordTXT[ii];
            }
            for (int isock = 0; isock < _numSockets; ++isock)
            {
                mDNS::announce_multicast(_sockets[isock], _buffer, kBufferCapacity, _announceData->_recordPTR, nullptr,
                                         0, additional, additionalCount);
            }
            report("mDNS announcements sent.");
        }
    }
    else
    {
        okSoFar = false;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ContextWithMDNS::makePortAnnouncement

void
nImO::ContextWithMDNS::openSockets
    (void)
{
    ODL_OBJENTER(); //####
    if (lHasIpv4)
    {
        struct sockaddr_in    sock_addr;

        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = INADDR_ANY;
        sock_addr.sin_port = htons(MDNS_PORT);
        int    sock = mDNS::socket_open_ipv4(sock_addr);

        if (sock >= 0)
        {
            _sockets[_numSockets++] = sock;
        }
    }
    if (lHasIpv6)
    {
        struct sockaddr_in6    sock_addr;

        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin6_family = AF_INET6;
        sock_addr.sin6_addr = in6addr_any;
        sock_addr.sin6_port = htons(MDNS_PORT);
        int    sock = mDNS::socket_open_ipv6(sock_addr);

        if (sock >= 0)
        {
            _sockets[_numSockets++] = sock;
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::openSockets

void
nImO::ContextWithMDNS::removeAnnouncement
    (void)
{
    ODL_OBJENTER(); //####
    if (ThreadMode::LaunchAnnouncer == (ThreadMode::LaunchAnnouncer & _whichThreads))
    {
        if (nullptr != _announceData)
        {
            // Send a goodbye on end of service
            mDNS::record_t    additional[kNumTxtRecords + 3];
            size_t            additionalCount = 0;

            memset(additional, 0, sizeof(additional));
            additional[additionalCount++] = _announceData->_recordSRV;
            if (AF_INET == _announceData->_addressIpv4.sin_family)
            {
                additional[additionalCount++] = _announceData->_recordA;
            }
            if (AF_INET6 == _announceData->_addressIpv6.sin6_family)
            {
                additional[additionalCount++] = _announceData->_recordAAAA;
            }
            for (size_t ii = 0; ii < kNumTxtRecords; ++ii)
            {
                additional[additionalCount++] = _announceData->_recordTXT[ii];
            }
            report("mDNS 'goodbyes' sent.");
            for (int isock = 0; isock < _numSockets; ++isock)
            {
                mDNS::goodbye_multicast(_sockets[isock], _buffer, kBufferCapacity, _announceData->_recordPTR, 0, 0,
                                        additional, additionalCount);
            }
        }
        lAnnouncerThreadStop = true;
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::removeAnnouncement

void
nImO::ContextWithMDNS::stopGatheringAnnouncements
    (void)
{
    ODL_OBJENTER(); //####
    if (ThreadMode::LaunchBrowser == (ThreadMode::LaunchBrowser & _whichThreads))
    {
        if (lWaitForRegistry && lBrowserThreadStarted)
        {
            lBrowserThreadStop = true;
            for ( ; ! lBrowserThreadStopped; )
            {
                thread::yield();
            }
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::stopGatheringAnnouncements

bool
nImO::ContextWithMDNS::waitForRegistry
    (void)
{
    bool    wasFound;

    ODL_OBJENTER(); //####
    if (lWaitForRegistry)
    {
        for ( ; (! lStopRegistryLoop) && ((! _havePort) || (! _haveAddress)); )
        {
            gatherAnnouncements(true);
        }
        wasFound = (_havePort && _haveAddress);
    }
    else if (lPerformSingleRegistryCheck)
    {
        gatherAnnouncements(true);
        wasFound = (_havePort && _haveAddress);
    }
    else
    {
        wasFound = false;
    }
    ODL_OBJEXIT_B(wasFound); //####
    return wasFound;
} // nImO::ContextWithMDNS::waitForRegistry

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::DisableWaitForRegistry
    (const bool allowOneCheck)
{
    ODL_ENTER(); //####
    lWaitForRegistry = false;
    lPerformSingleRegistryCheck = allowOneCheck;
    ODL_EXIT(); //####
} // nImO::DisableWaitForRegistry

void
nImO::EnableWaitForRegistry
(void)
{
    ODL_ENTER(); //####
    lWaitForRegistry = true;
    lPerformSingleRegistryCheck = false;
    ODL_EXIT(); //####
} // nImO::EnableWaitForRegistry

void
nImO::InterruptRegistryWait
    (void)
{
    ODL_ENTER(); //####
    lStopRegistryLoop = true;
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
    char    host[NI_MAXHOST] = { 0 };
    char    service[NI_MAXSERV] = { 0 };
    int     ret = getnameinfo(ReinterpretCast(CPtr(struct sockaddr), &addr), StaticCast(socklen_t, addrLen), host,
                              NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST);
    int     len = 0;

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
    mDNS::string_t  mdnsString = nImO::Ipv4AddressToMdnsString(addrBuffer, sizeof(addrBuffer), addr, addrLen);
    std::string     result{mdns_string_to_std_string(mdnsString)};

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
    char    host[NI_MAXHOST] = { 0 };
    char    service[NI_MAXSERV] = { 0 };
    int     ret = getnameinfo(ReinterpretCast(CPtr(struct sockaddr), &addr), StaticCast(socklen_t, addrLen), host,
                              NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV | NI_NUMERICHOST);
    int     len = 0;

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

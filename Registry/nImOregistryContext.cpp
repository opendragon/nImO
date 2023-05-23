//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryContext.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'registry' execution context.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
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
//  Created:    2023-04-01
//
//--------------------------------------------------------------------------------------------------

#include "nImOregistryContext.h"

#include <nImOannounceServiceData.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the 'utility' %nImO execution context. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief Set to @c true to cause the announcer thread to terminate. */
static std::atomic<bool>    lAnnouncerThreadStop;

/*! @brief The buffer used to send replies for mDNS requests. */
static char lSendBuffer[1024];

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

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

    NIMO_UNUSED_VAR_(ttl);
    NIMO_UNUSED_VAR_(nameLength);
    NIMO_UNUSED_VAR_(recordOffset);
    NIMO_UNUSED_VAR_(recordLength);
    if ((mDNS::kEntryTypeQuestion == entry) && (! lAnnouncerThreadStop))
    {
        const char                          kDnsSd[]{"_services._dns-sd._udp.local."};
        CPtr(nImO::AnnounceServiceData)     servicePtr{ReinterpretCast(CPtr(nImO::AnnounceServiceData), userData)};

        if (nullptr == servicePtr)
        {
            result = false;
        }
        else
        {
            const nImO::AnnounceServiceData &   serviceData{*servicePtr};
            size_t                              offset{nameOffset};
            mDNS::string_t                      name{mDNS::mDNSPrivate::string_extract(data, size, offset, nImO::ContextWithMDNS::gNameBuffer,
                                                                                       sizeof(nImO::ContextWithMDNS::gNameBuffer))};

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
                    bool            unicast{0 != (rClass & MDNS_UNICAST_RESPONSE)};

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
                    mDNS::record_t  answer{serviceData._recordPTR};
                    mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                    size_t          additionalCount{0};

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
                    bool    unicast{0 != (rClass & MDNS_UNICAST_RESPONSE)};

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
                    mDNS::record_t  answer{serviceData._recordSRV};
                    mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                    size_t          additionalCount{0};

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
                    bool    unicast{0 != (rClass & MDNS_UNICAST_RESPONSE)};

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
                    mDNS::record_t  answer{serviceData._recordA};
                    mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                    size_t          additionalCount{0};

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
                    bool    unicast{0 != (rClass & MDNS_UNICAST_RESPONSE)};

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
                    mDNS::record_t  answer{serviceData._recordAAAA};
                    mDNS::record_t  additional[nImO::kNumTxtRecords + 3];
                    size_t          additionalCount{0};

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
                    bool    unicast{0 != (rClass & MDNS_UNICAST_RESPONSE)};

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
    }
    else
    {
        result = false;
    }
    return result;
} // announcementServiceCallback

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::RegistryContext::RegistryContext
    (const int              argc,
     Ptr(Ptr(char))         argv,
     const std::string &    executableName,
     const bool             logging,
     const bool             startAnnouncer) :
        inherited(argc, argv, executableName, "registry", logging, true, ""), _announcerThread(nullptr), _announceData(nullptr),
        _startAnnouncer(startAnnouncer)
{
    ODL_ENTER(); //####
    ODL_S1s("executableName = ", executableName); //####
    ODL_B1("logging = ", logging); //####
    try
    {

    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::RegistryContext::RegistryContext

nImO::RegistryContext::~RegistryContext
    (void)
{
    ODL_OBJENTER(); //####
    removeAnnouncement();
    if (nullptr != _announceData)
    {
        delete _announceData;
        _announceData = nullptr;
    }
    ODL_OBJEXIT(); //####
} // nImO::RegistryContext::~RegistryContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::RegistryContext::executeAnnouncer
    (RegistryContext &  owner)
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", &owner); //####
    struct timeval timeout;

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    owner.report("announcer thread starting.");
    for ( ; ; )
    {
        if (lAnnouncerThreadStop)
        {
            break;

        }
        int     nfds{0};
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
            int    res{select(nfds, &readfs, nullptr, nullptr, &timeout)};

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
    owner.report("announcer thread terminating.");
    ODL_EXIT(); //####
} // nImO::RegistryContext::executeAnnouncer

bool
nImO::RegistryContext::makePortAnnouncement
    (const uint16_t         port,
     const std::string &    serviceName,
     const std::string &    hostName,
     const std::string &    dataKey)
{
    ODL_OBJENTER(); //####
    ODL_I1("port = ", port); //####
    ODL_S3s("serviceName = ", serviceName, "hostName = ", hostName, "dataKey = ", dataKey); //####
    bool    okSoFar;

    if (nullptr != _announceData)
    {
        delete _announceData;
        _announceData = nullptr;
    }
    if (_startAnnouncer)
    {
        char        addressBuffer[64];
        std::string hostAddress;

        lAnnouncerThreadStop = false;
        ODL_B1("lAnnouncerThreadStop <- ", lAnnouncerThreadStop); //####
        _announceData = new AnnounceServiceData(gServiceAddressIpv4, gServiceAddressIpv6);
        ODL_P1("_announceData <- ", _announceData); //####
        _announcerThread = new boost::thread([this]
                                                (void)
                                                {
                                                    ODL_LOG("announcer thread started"); //####
                                                    executeAnnouncer(*this);
                                                    ODL_LOG("announcer thread ended"); //####
                                                });
        ODL_P1("announcer thread = ", _announcerThread); //####
        _pool.add_thread(_announcerThread);
        if (nImO::ContextWithMDNS::gHasIpv4)
        {
            mDNS::string_t  addressString{Ipv4AddressToMdnsString(addressBuffer, sizeof(addressBuffer), nImO::ContextWithMDNS::gServiceAddressIpv4,
                                                                  sizeof(nImO::ContextWithMDNS::gServiceAddressIpv4))};

            hostAddress = addressString.str;
            release_mdns_string(addressString);
        }
        else if (nImO::ContextWithMDNS::gHasIpv6)
        {
            mDNS::string_t  addressString{Ipv6AddressToMdnsString(addressBuffer, sizeof(addressBuffer), nImO::ContextWithMDNS::gServiceAddressIpv6,
                                                                  sizeof(nImO::ContextWithMDNS::gServiceAddressIpv6))};

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
            size_t            additionalCount{0};

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
} // nImO::RegistryContext::makePortAnnouncement

void
nImO::RegistryContext::removeAnnouncement
    (void)
{
    ODL_OBJENTER(); //####
    if (_startAnnouncer)
    {
        if (nullptr != _announceData)
        {
            // Send a goodbye on end of service
            mDNS::record_t    additional[kNumTxtRecords + 3];
            size_t            additionalCount{0};

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
        if (nullptr != _announcerThread)
        {
            lAnnouncerThreadStop = true;
            ODL_B1("lAnnouncerThreadStop <- ", lAnnouncerThreadStop); //####
            _announcerThread->join();
            _announcerThread = nullptr;
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::RegistryContext::removeAnnouncement

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

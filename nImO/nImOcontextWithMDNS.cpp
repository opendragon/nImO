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

//#include <odlEnable.h>
#include <odlInclude.h>

#if MAC_OR_LINUX_
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

/*! @brief @c true if the application needs to performa a single check for the Registry. */
static std::atomic<bool>    lPerformSingleRegistryCheck;

/*! @brief @c true if the application should wait for the Registry. */
static std::atomic<bool>    lWaitForRegistry{true};

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
                    ODL_B3("_owner._havePort <- ", _owner._havePort, "_owner._haveAddress <- ", _owner._haveAddress, //####
                           "_processing <- ", _processing); //####
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
                NIMO_UNUSED_VAR_(entryData);
                NIMO_UNUSED_VAR_(aData);
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
                NIMO_UNUSED_VAR_(entryData);
                NIMO_UNUSED_VAR_(aaaaData);
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
                        ODL_B3("_owner._havePort <- ", _owner._havePort, "_owner._haveAddress <- ", _owner._haveAddress, //####
                               "_processing <- ", _processing); //####
                    }
                    else
                    {
                        _processing = false;
                        ODL_B1("_processing <- ", _processing); //####
                    }
                }
                else
                {
                    _processing = false;
                    ODL_B1("_processing <- ", _processing); //####
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
                    ODL_B1("_owner._havePort <- ", _owner._havePort); //####
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
                        ODL_B1("_owner._haveAddress <- ", _owner._haveAddress); //####
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

char nImO::ContextWithMDNS::gNameBuffer[256];

struct sockaddr_in   nImO::ContextWithMDNS::gServiceAddressIpv4;

struct sockaddr_in6  nImO::ContextWithMDNS::gServiceAddressIpv6;

bool nImO::ContextWithMDNS::gHasIpv4 = false;

bool nImO::ContextWithMDNS::gHasIpv6 = false;

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
        if (nullptr != address->ifa_addr)
        {
            if (AF_INET == address->ifa_addr->sa_family)
            {
                struct sockaddr_in &    saddr = *ReinterpretCast(Ptr(struct sockaddr_in), address->ifa_addr);

                if (IPV4_ADDR(127, 0, 0, 1) != ntohl(saddr.sin_addr.s_addr))
                {
                    if (firstIpv4)
                    {
                        nImO::ContextWithMDNS::gServiceAddressIpv4 = saddr;
                        firstIpv4 = false;
                    }
                    nImO::ContextWithMDNS::gHasIpv4 = true;
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
                        nImO::ContextWithMDNS::gServiceAddressIpv6 = saddr;
                        firstIpv6 = false;
                    }
                    nImO::ContextWithMDNS::gHasIpv6 = true;
                }
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
            if (nullptr != unicast->Address.lpSockaddr)
            {
                if (AF_INET == unicast->Address.lpSockaddr->sa_family)
                {
                    struct sockaddr_in &    saddr = *ReinterpretCast(Ptr(struct sockaddr_in), unicast->Address.lpSockaddr);

                    if ((saddr.sin_addr.S_un.S_un_b.s_b1 != 127) || (saddr.sin_addr.S_un.S_un_b.s_b2 != 0) ||
                        (saddr.sin_addr.S_un.S_un_b.s_b3 != 0) || (saddr.sin_addr.S_un.S_un_b.s_b4 != 1))
                    {
                        if (firstIpv4)
                        {
                            nImO::ContextWithMDNS::gServiceAddressIpv4 = saddr;
                            firstIpv4 = false;
                        }
                        nImO::ContextWithMDNS::gHasIpv4 = true;
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
                            nImO::ContextWithMDNS::gServiceAddressIpv6 = saddr;
                            firstIpv6 = false;
                        }
                        nImO::ContextWithMDNS::gHasIpv6 = true;
                    }
                }
            }
        }
    }
    free(adapterAddress);
#endif // not MAC_OR_LINUX_
    if ((! nImO::ContextWithMDNS::gHasIpv4) && (! nImO::ContextWithMDNS::gHasIpv6))
    {
        throw "No usable network addresses found.";
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
            mDNS::string_t    nameStr = mDNS::record_parse_ptr(data, size, recordOffset, recordLength, nImO::ContextWithMDNS::gNameBuffer,
                                                               sizeof(nImO::ContextWithMDNS::gNameBuffer));

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
            mDNS::record_srv_t    srv = mDNS::record_parse_srv(data, size, recordOffset, recordLength, nImO::ContextWithMDNS::gNameBuffer,
                                                               sizeof(nImO::ContextWithMDNS::gNameBuffer));

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
            mDNS::string_t    addrStr = nImO::Ipv4AddressToMdnsString(nImO::ContextWithMDNS::gNameBuffer, sizeof(nImO::ContextWithMDNS::gNameBuffer),
                                                                      addr, sizeof(addr));

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
            mDNS::string_t    addrStr = nImO::Ipv6AddressToMdnsString(nImO::ContextWithMDNS::gNameBuffer, sizeof(nImO::ContextWithMDNS::gNameBuffer),
                                                                      addr, sizeof(addr));

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
     const bool             startBrowser,
     const std::string &    nodeName) :
        inherited(executableName, tag, logging, 2 /* browse + announce */, nodeName), _numSockets(0),
        _buffer(new char[kBufferCapacity]), _startBrowser(startBrowser), _browserThread(nullptr)
{
    ODL_ENTER(); //####
    ODL_S3s("executableName = ", executableName, "tag = ", tag, "nodeName = ", nodeName); //####
    ODL_B2("logging = ", logging, "startBrowser = ", startBrowser); //####
    getLocalAddresses();
    openSockets();
    ODL_EXIT_P(this); //####
} // nImO::ContextWithMDNS::ContextWithMDNS

nImO::ContextWithMDNS::~ContextWithMDNS
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
nImO::ContextWithMDNS::executeBrowser
    (ContextWithMDNS &  owner)
{
    RecordHandler   handler(owner);
    struct timeval  timeout;

    ODL_ENTER(); //####
    ODL_P1("owner = ", &owner); //####
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    owner.report("browser thread starting.");
    lBrowserThreadStarted = true;
    ODL_B1("lBrowserThreadStarted <- ", lBrowserThreadStarted); //####
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
                    mDNS::query_recv(owner._sockets[isock], owner._buffer, nImO::ContextWithMDNS::kBufferCapacity, queryCallback, &handler,
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
                ODL_B1("owner._requestNewScan <- ", owner._requestNewScan); //####
                owner.report("Sending mDNS query: " + std::string(NIMO_REGISTRY_SERVICE_NAME));
                for (int isock = 0; isock < owner._numSockets; ++isock)
                {
                    if (lBrowserThreadStop)
                    {
                        break;

                    }
                    owner._queryId[isock] = mDNS::query_send(owner._sockets[isock], mDNS::kRecordTypePTR, NIMO_REGISTRY_SERVICE_NAME,
                                                             sizeof(NIMO_REGISTRY_SERVICE_NAME) - 1, owner._buffer,
                                                             nImO::ContextWithMDNS::kBufferCapacity, 0);
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
    ODL_B2("lBrowserThreadStarted <- ", lBrowserThreadStarted, "lBrowserThreadStopped <- ", lBrowserThreadStopped); //####
    owner.report("browser thread terminating.");
    ODL_EXIT(); //####
} // nImO::ContextWithMDNS::executeBrowser

bool
nImO::ContextWithMDNS::findRegistry
    (Connection &   connection,
     const bool     quietly)
{
    bool    found;

    ODL_OBJENTER(); //####
    ODL_P1("connection = ", &connection); //####
    ODL_B1("quietly = ", quietly); //####
    if (lWaitForRegistry && ((! _havePort) || (! _haveAddress)))
    {
        gatherAnnouncements(quietly);
    }
    if (_havePort && _haveAddress)
    {
        connection._address = asio::ip::address_v4::from_string(_registryPreferredAddress).to_ulong();
        connection._port = _registryPort;
        stopGatheringAnnouncements();
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
    ODL_B1("quietly = ", quietly); //####
    if (_startBrowser)
    {
        bool    okSoFar = true;

        lBrowserThreadStopped = false;
        lBrowserThreadStop = false;
        ODL_B2("lBrowserThreadStopped <- ", lBrowserThreadStopped, "lBrowserThreadStop <- ", lBrowserThreadStop); //####
        _havePort = false;
        _haveAddress = false;
        ODL_B2("_havePort <- ", _havePort, "_haveAddress <- ", _haveAddress); //####
        _browserThread = new boost::thread([this]
                                            (void)
                                            {
                                                ODL_LOG("browser thread started"); //####
                                                executeBrowser(*this);
                                                ODL_LOG("browser thread ended"); //####
                                            });
        ODL_P1("browser thread = ", _browserThread); //####
        _pool.add_thread(_browserThread);
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
                                       if (! error)
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
                this_thread::yield();
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

void
nImO::ContextWithMDNS::openSockets
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
        int    sock = mDNS::socket_open_ipv4(sock_addr);

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
        int    sock = mDNS::socket_open_ipv6(sock_addr);

        if (sock >= 0)
        {
            _sockets[_numSockets++] = sock;
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::openSockets

void
nImO::ContextWithMDNS::stopGatheringAnnouncements
    (void)
{
    ODL_OBJENTER(); //####
    if (_startBrowser && (nullptr != _browserThread))
    {
        lBrowserThreadStop = true;
        ODL_B1("lBrowserThreadStop <- ", lBrowserThreadStop); //####
        if (lWaitForRegistry && lBrowserThreadStarted && (! lBrowserThreadStopped))
        {
            for ( ; ! lBrowserThreadStopped; )
            {
                this_thread::yield();
            }
        }
        _browserThread->join();
        _browserThread = nullptr;
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
    ODL_B1("allowOneCheck = ", allowOneCheck); //####
    lWaitForRegistry = false;
    lPerformSingleRegistryCheck = allowOneCheck;
    ODL_B2("lWaitForRegistry <- ", lWaitForRegistry, "lPerformSingleRegistryCheck <- ", lPerformSingleRegistryCheck); //####
    ODL_EXIT(); //####
} // nImO::DisableWaitForRegistry

void
nImO::EnableWaitForRegistry
    (void)
{
    ODL_ENTER(); //####
    lWaitForRegistry = true;
    lPerformSingleRegistryCheck = false;
    ODL_B2("lWaitForRegistry <- ", lWaitForRegistry, "lPerformSingleRegistryCheck <- ", lPerformSingleRegistryCheck); //####
    ODL_EXIT(); //####
} // nImO::EnableWaitForRegistry

void
nImO::InterruptRegistryWait
    (void)
{
    ODL_ENTER(); //####
    lStopRegistryLoop = true;
    ODL_B1("lStopRegistryLoop <- ", lStopRegistryLoop); //####
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

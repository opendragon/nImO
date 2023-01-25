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

#include "nImOcontextWithMDNS.h"

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

/*! @brief The root path for MDNS queries. */
#define NIMO_MDNS_PATH  "_nimo._tcp.local."

/*! @brief @c true if an IPv4 address was found. */
static bool lHasIpv4 = false;

/*! @brief @c true if an IPv6 address was found. */
static bool lHasIpv6 = false;

/*! @brief The first IPv4 address found. */
static struct sockaddr_in   lServiceAddressIpv4;

/*@ @brief The first IPv6 address found. */
static struct sockaddr_in6  lServiceAddressIpv6;

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
    ODL_ENTER(); //####
#if MAC_OR_LINUX_
    Ptr(struct ifaddrs)         addresses;
#else // not MAC_OR_LINUX_
    Ptr(IP_ADAPTER_ADDRESSES)   adapterAddress;
    ULONG                       addressSize = 8000;
    uint                        ret;
    uint                        numRetries = 4;
#endif // not MAC_OR_LINUX_

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
     const std::string &    nodeName) :
        inherited(executableName, tag, logging, 2 /* browse + announce */, nodeName), _numSockets(0)
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
    closeSockets();
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

bool
nImO::ContextWithMDNS::findRegistry
    (void)
{
    ODL_OBJENTER(); //####
    bool    found = false;

    //TBD
    ODL_OBJEXIT_B(found); //####
    return found;
} // nImO::ContextWithMDNS::findRegistry

void
nImO::ContextWithMDNS::gatherAnnouncements
    (void)
{
    ODL_OBJENTER(); //####
    //TBD
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::gatherAnnouncements

void
nImO::ContextWithMDNS::launchRegistryIfNotActive
    (void)
{
    ODL_OBJENTER(); //####
    //TBD
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::launchRegistryIfNotActive

void
nImO::ContextWithMDNS::makeAnnouncement
    (void)
{
    ODL_OBJENTER(); //####
    //TBD
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::makeAnnouncement

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
    //TBD
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::removeAnnouncement

void
nImO::ContextWithMDNS::stopGatheringAnnouncements
    (void)
{
    ODL_OBJENTER(); //####
    //TBD
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::stopGatheringAnnouncements

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::BlockRegistryLaunch
    (void)
{
    ODL_ENTER(); //####
    ODL_EXIT(); //####
} // nImO::BlockRegistryLaunch

void
nImO::UnblockRegistryLaunch
    (void)
{
    ODL_ENTER(); //####
    ODL_EXIT(); //####
} // nImO::UnblockRegistryLaunch





#if 0
GetShortComputerName()

//---------------------------- SetUpAnnouncer -------------------------------
void __fastcall TfrmMain::SetUpAnnouncer
(const AnsiString &    hostName)
{
    lTraceObject.SetDeferredStreamName(hostName + mess_dash + IntToStr(GetTcpServerPort()) + ".log");
    gAnnouncementThread = new T_AnnounceServiceThread(lTraceObject, hostName, CADSIM_MDNS_PATH, GetTcpServerPort(),
                                                      GetTcpServerAddress());
    gAnnouncementThread->OnTerminate = doTerminateAnnouncementThread;
    gAnnouncementThread->Start();
}
//---------------------------- End SetUpAnnouncer ---------------------------

AnsiString    hostName;
char            hostnameBuffer[256];
DWORD            hostnameSize = StaticCast(DWORD, sizeof(hostnameBuffer));

SetUpTcpServer(mainForm);
if (GetComputerNameA(hostnameBuffer, &hostnameSize))
{
    stripDomain(hostnameBuffer);
    hostName = hostnameBuffer;
}
SetUpAnnouncer(mainForm, hostName);


//---------------------------- stripDomain ----------------------------------
//---------------------------- End stripDomain ------------------------------
#endif//0

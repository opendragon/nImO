//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOannounceServiceData.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for data used with nImO announcements.
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
//  Created:    2023-01-29
//
//--------------------------------------------------------------------------------------------------

#include <nImOannounceServiceData.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for data used with %nImO announcements. */
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

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::AnnounceServiceData::AnnounceServiceData
    (const struct sockaddr_in &     addressIpv4,
     const struct sockaddr_in6 &    addressIpv6) :
        _addressIpv4{addressIpv4}, _addressIpv6{addressIpv6}
{
    ODL_ENTER(); //####
    ODL_P2("addressIpv4 = ", &addressIpv4, "addressIpv6 = ", &addressIpv6); //####
    ODL_EXIT_P(this); //####
} // nImO::AnnounceServiceData::AnnounceServiceData

nImO::AnnounceServiceData::~AnnounceServiceData
    (void)
{
    ODL_OBJENTER(); //####
    delete[] _serviceNameBuffer;
    release_mdns_string(_hostName);
    release_mdns_string(_hostNameQualified);
    release_mdns_string(_recordA.name);
    release_mdns_string(_recordAAAA.name);
    release_mdns_string(_recordPTR.name);
    release_mdns_string(_recordPTR.data.ptr.name);
    release_mdns_string(_recordSRV.name);
    release_mdns_string(_recordSRV.data.srv.name);
    release_mdns_string(_serviceInstance);
    release_mdns_string(_serviceName);
    for (size_t ii = 0; ii < kNumTxtRecords; ++ii)
    {
        release_mdns_string(_recordTXT[ii].name);
        release_mdns_string(_recordTXT[ii].data.txt.key);
        release_mdns_string(_recordTXT[ii].data.txt.value);
    }
    ODL_OBJEXIT(); //####
} // nImO::AnnounceServiceData::~AnnounceServiceData

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::AnnounceServiceData::setServiceData
    (const IPv4Port         port,
     const std::string &    serviceName,
     const std::string &    hostName,
     const std::string &    dataKey,
     const std::string &    hostAddress)
{
    ODL_OBJENTER(); //####
    ODL_I1("port = ", port); //####
    ODL_S4s("serviceName = ", serviceName, "hostName = ", hostName, "dataKey = ", dataKey, "hostAddress = ", hostAddress); //####
    bool    okSoFar;
    size_t  serviceNameLength{serviceName.length()};
    size_t  hostNameLength{hostName.length()};

    if ((0 < serviceNameLength) && (0 < hostNameLength))
    {
        _port = port;
        _serviceNameBuffer = StaticCast(Ptr(char), malloc(serviceNameLength + 2));
        memcpy(_serviceNameBuffer, serviceName.c_str(), serviceNameLength);
        if (_serviceNameBuffer[serviceNameLength - 1] != '.')
        {
            _serviceNameBuffer[serviceNameLength++] = '.';
        }
        _serviceNameBuffer[serviceNameLength] = kEndOfString;
        std::string     scratchName{_serviceNameBuffer};
        mDNS::string_t  serviceString{make_mdns_string(scratchName.c_str(), scratchName.length())};
        mDNS::string_t  hostNameString{make_mdns_string(hostName.c_str(), hostNameLength)};
        // Build the service instance "<hostname>.<_service-name>._tcp.local." string
        std::string     serviceInstanceBuffer{hostNameString.str};

        serviceInstanceBuffer += "-"s + std::to_string(_port) + "."s;
        serviceInstanceBuffer += serviceString.str;
        mDNS::string_t  serviceInstanceString{make_mdns_string(serviceInstanceBuffer.c_str())};
        // Build the "<hostname>.local." string
        std::string     qualifiedHostnameBuffer{hostNameString.str};

        qualifiedHostnameBuffer += ".local."s;
        mDNS::string_t hostnameQualifiedQtring{make_mdns_string(qualifiedHostnameBuffer.c_str())};

        _serviceName = make_mdns_string(serviceString);
        _hostName = make_mdns_string(hostNameString);
        _serviceInstance = make_mdns_string(serviceInstanceString);
        _hostNameQualified = make_mdns_string(hostnameQualifiedQtring);
        release_mdns_string(serviceString);
        release_mdns_string(hostNameString);
        release_mdns_string(serviceInstanceString);
        release_mdns_string(hostnameQualifiedQtring);
        // Setup our mDNS records

        // PTR record reverse mapping "<_service-name>._tcp.local." to
        // "<hostname>.<_service-name>._tcp.local."
        _recordPTR.name = make_mdns_string(_serviceName);
        _recordPTR.type = mDNS::kRecordTypePTR;
        _recordPTR.data.ptr.name = make_mdns_string(_serviceInstance);
        // SRV record mapping "<hostname>.<_service-name>._tcp.local." to
        // "<hostname>.local." with port. Set weight & priority to 0.
        _recordSRV.name = make_mdns_string(_serviceInstance);
        _recordSRV.type = mDNS::kRecordTypeSRV;
        _recordSRV.data.srv.name = make_mdns_string(_hostNameQualified);
        _recordSRV.data.srv.port = _port;
        _recordSRV.data.srv.priority = 0;
        _recordSRV.data.srv.weight = 0;
        // A/AAAA records mapping "<hostname>.local." to IPv4/IPv6 addresses
        _recordA.name = make_mdns_string(_hostNameQualified);
        _recordA.type = mDNS::kRecordTypeA;
        _recordA.data.a.addr = _addressIpv4;
        _recordAAAA.name = make_mdns_string(_hostNameQualified);
        _recordAAAA.type = mDNS::kRecordTypeAAAA;
        _recordAAAA.data.aaaa.addr = _addressIpv6;
        // Add TXT records for our service instance name, will be coalesced into
        // one record with both key-value pair strings by the library
        _recordTXT[0].name = make_mdns_string(_serviceInstance);
        _recordTXT[0].type = mDNS::kRecordTypeTXT;
        _recordTXT[0].data.txt.key = make_mdns_string(dataKey.c_str(), dataKey.length());
        _recordTXT[0].data.txt.value = make_mdns_string(hostAddress.c_str(), hostAddress.length());
        okSoFar = true;
    }
    else
    {
        okSoFar = false;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::AnnounceServiceData::setServiceName

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

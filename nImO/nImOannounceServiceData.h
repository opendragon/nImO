//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOannounceServiceData.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for data used with nImO announcements.
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

#if (! defined(nImOannounceServiceData_H_))
# define nImOannounceServiceData_H_ /* Header guard */

# include <nImOcommon.h>

# if MAC_OR_LINUX_OR_BSD_
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
# endif // MAC_OR_LINUX_OR_BSD_
# include <mdns.hpp>
# if MAC_OR_LINUX_OR_BSD_
#  pragma GCC diagnostic pop
# endif // MAC_OR_LINUX_OR_BSD_

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for data used with %nImO announcements. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The maximum number of TXT records to send. */
    static const size_t    kNumTxtRecords{1};

    /*! @brief A class to provide data for nImO announcments. */
    class AnnounceServiceData final
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor. */
            AnnounceServiceData
                (const struct sockaddr_in &     addressIpv4,
                 const struct sockaddr_in6 &    addressIpv6);

            /*! @brief The destructor. */
            ~AnnounceServiceData
                (void);

            /*! @brief Set up the service and host name fields.
             @param[in] port The port number to use.
             @param[in] serviceName The name of the service being announced.
             @param[in] hostName The name of the computer.
             @param[in] dataKey The key for the instance-specific data.
             @param[in] hostAddress The IP address of the service.
             @return @c true if the mDNS announcement was constructed. */
            bool
            setServiceData
                (const IPv4Port         port,
                 const std::string &    serviceName,
                 const std::string &    hostName,
                 const std::string &    dataKey,
                 const std::string &    hostAddress);

        protected :
            // Protected methods.

        private :
            // Private methods.

        public :
            // Public fields.

            /*! @brief The IPv4 address to use. */
            struct sockaddr_in  _addressIpv4{};

            /*! @brief The Ipv6 address to use. */
            struct sockaddr_in6 _addressIpv6{};

            /*! @brief The name of the computer. */
            mDNS::string_t  _hostName;

            /*! @brief The qualified name of the computer. */
            mDNS::string_t  _hostNameQualified;

            /*! @brief The port number to report. */
            int _port{0};

            /*! @brief The data for A records. */
            mDNS::record_t  _recordA;

            /*! @brief The data for AAAA records. */
            mDNS::record_t  _recordAAAA;

            /*! @brief The data for PTR records. */
            mDNS::record_t  _recordPTR;

            /*! @brief The data for SRV records. */
            mDNS::record_t  _recordSRV;

            /*! @brief The data for TXT records. */
            mDNS::record_t  _recordTXT[kNumTxtRecords];

            /*! @brief The name of this particular copy of the service. */
            mDNS::string_t  _serviceInstance;

            /*! @brief The name of the service to report via mDNS. */
            mDNS::string_t  _serviceName;

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief Used to construct the service name. */
            Ptr(char)   _serviceNameBuffer{nullptr};

    }; // AnnounceServiceData

} // nImO

#endif // not defined(nImOannounceServiceData_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOcontextWithMDNS.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO execution contexts that use mDNS.
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

#if (! defined(nImOcontextWithMDNS_H_))
# define nImOcontextWithMDNS_H_ /* Header guard */

# include <Contexts/nImOcontextWithNetworking.h>

# if MAC_OR_LINUX_
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
# endif // MAC_OR_LINUX_
# include <mdns.hpp>
# if MAC_OR_LINUX_
#  pragma GCC diagnostic pop
# endif // MAC_OR_LINUX_

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO execution contexts that use mDNS. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief The Registry service for MDNS queries. */
# define NIMO_REGISTRY_SERVICE_NAME  "_nimo_registry._tcp.local."

namespace nImO
{
    // Forward references
    class AnnounceServiceData;
    class RecordHandler;

    /*! @brief A class to provide support for an application that uses mDNS. */
    class ContextWithMDNS : public ContextWithNetworking
    {

        public :
            // Public type definitions.

            /*! @brief The size of the MDNS I/O buffer. */
            static const size_t kBufferCapacity{2048};

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ContextWithNetworking;

            friend class RecordHandler;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] executable The name of the executing program.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] startBrowser @c true if the browser thread is to be started.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            ContextWithMDNS
                (const std::string &    executableName,
                 const std::string &    tagForLogging = ""s,
                 const bool             logging = false,
                 const bool             startBrowser = false,
                 const std::string &    nodeName = ""s);

            /*! @brief The destructor. */
            ~ContextWithMDNS
                (void)
                override;

            /*! @brief Find the Registry if it's running.
             @param[out] connection The IP address and port of the Registry, if found.
             @param[in] quietly @c true if reporting a failure is suppressed.
             @return @c true if the Registry is located. */
            bool
            findRegistry
                (Connection &   connection,
                 const bool     quietly = false);

            /*! @brief Find the Registry if it's running.
             @param[in] quietly @c true if reporting a failure is suppressed.
             @return @c true if the Registry is located. */
            inline bool
            findRegistry
                (const bool quietly = false)
            {
                Connection  ignoredConnection;

                return findRegistry(ignoredConnection, quietly);
            }

        protected :
            // Protected methods.

            /*! @brief Wait until the Registry is located.
             @return @c true if the Registry was located. */
            bool
            waitForRegistry
                (void);

        private :
            // Private methods.

            /*! @brief Close the open sockets. */
            void
            closeSockets
                (void);

            /*! @brief The browset thread function.
             @param[in,out] owner The owning object for the thread. */
            static void
            executeBrowser
                (ContextWithMDNS &  owner);

            /*! @brief Collect announcements via mDNS.
             @param[in] quietly @c true if reporting a failure is suppressed. */
            void
            gatherAnnouncements
                (const bool quietly = false);

            /*! @brief Create the sockets to be used. */
            void
            openSockets
                (void);

            /*! @brief Stop collecting announcements via mDNS. */
            void
            stopGatheringAnnouncements
                (void);

        public :
            // Public fields.

            /*! @brief The buffer used to record the name from a mDNS request. */
            static char gNameBuffer[256];

            /*! @brief The first IPv4 address found. */
            static struct sockaddr_in   gServiceAddressIpv4;

            /*@ @brief The first IPv6 address found. */
            static struct sockaddr_in6  gServiceAddressIpv6;

            /*! @brief @c true if an IPv4 address was found. */
            static bool gHasIpv4;

            /*! @brief @c true if an IPv6 address was found. */
            static bool gHasIpv6;

        protected :
            // Protected fields.

            /*! @brief The number of sockets in use. */
            int _numSockets;

            /*! @brief The sockets to use. */
            int _sockets[8];

            /*! @brief The buffer to be used for MDNS I/O operations. */
            Ptr(char)   _buffer;

        private :
            // Private fields.

            /*! @brief Set to @c true to initiate a new scan of announcements. */
            std::atomic_bool    _requestNewScan{false};

            /*! @brief The active query identifiers. */
            int _queryId[8];

            /*! @brief @c true if the browser thread is to be launched. */
            bool  _startBrowser{false};

            /*! @brief The identifying tag for the Registry process. */
            std::string _registryTag{};

            /*! @brief The IP port for connections to the Registry process. */
            IPv4Port    _registryPort{0};

            /*! @brief The preferred address for connections to the Registry process. */
            std::string _registryPreferredAddress{};

            /*! @brief Set to @c true when the Registry has reported its address. */
            std::atomic_bool    _haveAddress{false};

            /*! @brief Set to @c true when the Registry has reported its port. */
            std::atomic_bool    _havePort{false};

            /*! @brief The thread which executes the browser code. */
            Ptr(boost::thread)  _browserThread{nullptr};

    }; // ContextWithMDNS

    /*! @brief The key in the mDNS data for the Registry address. */
    const std::string kRegistryAddressKey{"registry_address"};

    /*! @brief Don't wait for the Registry - used with the Registry and test programs.
     @param[in] allowOneCheck @c true if there a single scan for the Registry is done instead. */
    void
    DisableWaitForRegistry
        (const bool allowOneCheck = false);

    /*! @brief Wait for the Registry - used with the test programs. */
    void
    EnableWaitForRegistry
        (void);

    /*! @brief Stop the loop that is waiting for the Registry. */
    void
    InterruptRegistryWait
        (void);

    /*! @brief Convert an IP address to an MDNS string.
     @param[in,out] buffer Temporary buffer to use for conversion.
     @param[in] capacity The size of the temporary buffer.
     @param[in] addr The address to convert.
     @param[in] addrLen The size of the address. */
    mDNS::string_t
    IpAddressToMdnsString
        (Ptr(char)                  buffer,
         const size_t               capacity,
         const struct sockaddr &    addr,
         const size_t               addrLen);

    /*! @brief Convert an IPv4 address to an MDNS string.
     @param[in,out] buffer Temporary buffer to use for conversion.
     @param[in] capacity The size of the temporary buffer.
     @param[in] addr The address to convert.
     @param[in] addrLen The size of the address. */
    mDNS::string_t
    Ipv4AddressToMdnsString
        (Ptr(char)                  buffer,
         const size_t               capacity,
         const struct sockaddr_in & addr,
         const size_t               addrLen);

    /*! @brief Convert an IPv4 address to a standard string.
     @param[in] addr The address to convert.
     @param[in] addrLen The size of the address. */
    std::string
    Ipv4AddressToStdString
        (const struct sockaddr_in & addr,
         const size_t               addrLen);

    /*! @brief Convert an IPv6 address to an MDNS string.
     @param[in,out] buffer Temporary buffer to use for conversion.
     @param[in] capacity The size of the temporary buffer.
     @param[in] addr The address to convert.
     @param[in] addrLen The size of the address. */
    mDNS::string_t
    Ipv6AddressToMdnsString
        (Ptr(char)                      buffer,
         const size_t                   capacity,
         const struct sockaddr_in6 &    addr,
         const size_t                   addrLen);

} // nImO

#endif // not defined(nImOcontextWithMDNS_H_)

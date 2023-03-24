//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithMDNS.h
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

# include <nImOcontextWithNetworking.h>

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

/*! @brief The key in the mDNS data for the Registry address. */
# define NIMO_REGISTRY_ADDRESS_KEY  "registry_address"

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

            /*! @brief Which threads to launch. */
            enum class ThreadMode : uint8_t
            {
                /*! @brief Neither thread is to be launched. */
                LaunchNeither = 0x00,

                /*! @brief The announcer thread is to be launched. */
                LaunchAnnouncer = 0x01,

                /*! @brief The browser thread is to be launched. */
                LaunchBrowser = 0x02,

                /*! @brief The browser thread is to be launched. */
                LaunchBoth = (LaunchAnnouncer | LaunchBrowser)

            }; // ThreadMode

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
             @param[in] tag The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] whichThreads Which threads, if any, to start.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            ContextWithMDNS
                (const std::string &    executableName,
                 const std::string &    tag,
                 const bool             logging,
                 const ThreadMode       whichThreads,
                 const std::string &    nodeName = "");

            /*! @brief The destructor. */
            virtual
            ~ContextWithMDNS
                (void);

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

            /*! @brief Send a port announcement via mDNS.
             @param[in] port The port number being announced.
             @param[in] serviceName The mDNS service name.
             @param[in] hostName The name of the computer.
             @param[in] dataKey The key for the instance-specific data.
             @return @c true if the announcement was constructed and sent. */
            bool
            makePortAnnouncement
                (const uint16_t         port,
                 const std::string &    serviceName,
                 const std::string &    hostName,
                 const std::string &    dataKey);

        protected :
            // Protected methods.

            /*! @brief Retract the announcement via mDNS. */
            void
            removeAnnouncement
                (void);

            /*! @brief Stop collecting announcements via mDNS. */
            void
            stopGatheringAnnouncements
                (void);

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

            /*! @brief The announcer thread function.
             @param[in,out] owner The owning object for the thread. */
            static void
            executeAnnouncer
                (ContextWithMDNS &  owner);

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

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief Set to @c true to initiate a new scan of announcements. */
            std::atomic<bool>   _requestNewScan;

            /*! @brief The active query identifiers. */
            int _queryId[8];

            /*! @brief The sockets to use. */
            int _sockets[8];

            /*! @brief The number of sockets in use. */
            int _numSockets;

            /*! @brief Which threads are to be launched. */
            ThreadMode  _whichThreads;

            /*! @brief Data to be used with the announcer thread. */
            Ptr(AnnounceServiceData)    _announceData;

            /*! @brief The buffer to be used for MDNS I/O operations. */
            Ptr(char)   _buffer;

            /*! @brief The identifying tag for the Registry process. */
            std::string _registryTag;

            /*! @brief The IP port for connections to the Registry process. */
            uint16_t    _registryPort;

            /*! @brief The preferred address for connections to the Registry process. */
            std::string _registryPreferredAddress;

            /*! @brief Set to @c true when the Registry has reported its address. */
            std::atomic<bool>   _haveAddress;

            /*! @brief Set to @c true when the Registry has reported its port. */
            std::atomic<bool>   _havePort;

    }; // ContextWithMDNS

    UnaryAndBinaryOperators(ContextWithMDNS::ThreadMode)

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

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOsearchContext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO execution contexts that can search for the Registry.
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

#if (! defined(nImOsearchContext_H_))
# define nImOsearchContext_H_ /* Header guard */

# include <Contexts/nImOnetworkingContext.h>

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
 @brief The class declaration for %nImO execution contexts that can search for the Registry. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    // Forward references
    class AnnounceServiceData;
    class RecordHandler;

    /*! @brief A class to provide support for an application that can search for the Registry. */
    class SearchContext : public NetworkingContext
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
            using inherited = NetworkingContext;

            friend class RecordHandler;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] startBrowser @c true if the browser thread is to be started. */
            SearchContext // cppcheck-suppress noExplicitConstructor
                (const std::string &    tagForLogging = ""s,
                 const bool             logging = false,
                 const bool             startBrowser = false);

            /*! @brief The destructor. */
            ~SearchContext
                (void)
                override;

            /*! @brief Find and launch the Registry if it's not running.
             @return @c true if the Registry was launched. */
            bool
            findAndLaunchTheRegistry
                (void);

            /*! @brief Find the Registry if it's running.
             @param[out] connection The IP address and port of the Registry, if found.
             @return @c true if the Registry is located. */
            bool
            findTheRegistry
                (Connection &   connection);

            /*! @brief Find the Registry if it's running.
             @return @c true if the Registry is located. */
            inline bool
            findTheRegistry
                (void)
            {
                Connection  ignoredConnection;

                return findTheRegistry(ignoredConnection);
            }

            /*! @brief Return the mDNS name of the Registry. */
            inline const std::string &
            getRegistryName
                (void)
                const
            {
                return _registryName;
            }

            /*! @brief Return the address and port to use for locating the Registry.
             @return The address and port to use for searching for the Registry. */
            inline Connection
            getRegistrySearchInfo
                (void)
                const
            {
                return _registrySearchConnection;
            }

            /*! @brief Return the full mDNS name of the Registry. */
            inline std::string
            getRegistryServiceName
                (void)
                const
            {
                return "_nimo_"s + getRegistryName() + "._tcp.local."s;
            }

            /*! @brief Returns RegistryMode value corresponding to a name.
             @param[in] aName The name of the RegistryMode to be converted.
             @return The RegistryMode value corresponding to the name. */
            static RegistryMode
            modeFromName
                (const std::string &    aName);

            /*! @brief Returns the name corresponding to a RegistryMode value.
             @param[in] aValue The RegistryMode value to be converted.
             @return The standard name for the RegistryMode value. */
            static std::string
            modeToName
                (const RegistryMode aValue);

        protected :
            // Protected methods.

            /*! @brief Wait until the Registry is located.
             @return @c true if the Registry was located. */
            bool
            waitForRegistry
                (void);

        private :
            // Private methods.

            /*! @brief Handle any messages on the receive queue. */
            void
            checkReceiveQueue
                (void);

            /*! @brief Close the open sockets. */
            void
            closeSockets
                (void)
                const;

            /*! @brief The browser thread function.
             @param[in,out] owner The owning object for the thread. */
            static void
            executeBrowser
                (SearchContext &    owner);

            /*! @brief Collect announcements via mDNS or multicast. */
            void
            gatherAnnouncements
                (void);

            /*! @brief The function to call when a timer has expired.
             @param[in,out] timer The active timer object. */
            void
            handleTimerEvent
                (BAD_t &    timer);

            /*! @brief Create the sockets to be used. */
            void
            openSockets
                (void);

            /*! @brief Send an address request via the multicast port.*/
            void
            sendGetAddressRequest
                (void);

            /*! @brief Stop collecting announcements via mDNS. */
            void
            stopGatheringAnnouncements
                (void);

        public :
            // Public fields.

            /*! @brief The buffer used to record the name from a mDNS request. */
            static char gNameBuffer[256];

        protected :
            // Protected fields.

            /*! @brief The buffer to be used for MDNS I/O operations. */
            Ptr(char)   _buffer;

            /*! @brief The number of sockets in use. */
            int _numSockets;

            /*! @brief The sockets to use. */
            int _sockets[8];

        private :
            // Private fields.

            /*! @brief The thread which executes the browser code. */
            Ptr(boost::thread)  _browserThread{nullptr};

            /*! @brief Set to @c true when the Registry has reported its address. */
            std::atomic_bool    _haveAddress{false};

            /*! @brief Set to @c true when the Registry has reported its port. */
            std::atomic_bool    _havePort{false};

            /*! @brief The active query identifiers. */
            int _queryId[8];

            /*! @brief The options to be applied when launching the Registry automatically. */
            Array   _registryLaunchOptions;

            /*! @brief The path to the Registry executable to be used when launching the Registry automatically. */
            std::string _registryLaunchPath;

            /*! @brief The mDNS name of the Registry. */
            std::string _registryName;

            /*! @brief The IP port for connections to the Registry process. */
            IPv4Port    _registryPort{0};

            /*! @brief The preferred address for connections to the Registry process. */
            std::string _registryPreferredAddress{};

            /*! @brief The multicast search connection used for the Registry. */
            Connection  _registrySearchConnection{};

            /*! @brief The search mode of the Registry. */
            RegistryMode    _registrySearchMode;

            /*! @brief The multicast port to be used for Registry searches. */
            SpSendToMulticastPort   _registryRequestPort{};

            /*! @brief The multicast port to be used for Registry searches. */
            SpReceiveFromMulticastPort    _registryResponsePort{};

            /*! @brief The maximum number of retries when searching for the Registry. */
            int _registrySearchRetries{0};

            /*! @brief The number of seconds before timeout occurs when searching for the Registry. */
            int _registrySearchTimeout{0};

            /*! @brief The identifying tag for the Registry process. */
            std::string _registryTag{};

            /*! @brief Set to @c true to initiate a new scan of announcements. */
            std::atomic_bool    _requestNewScan{false};

            /*! @brief The number of retries that have been performed. */
            int _retryCount{0};

            /*! @brief @c true if the browser thread is to be launched. */
            bool  _startBrowser{false};

            /*! @brief Set to @c true to indicate that the Registry was not found in the specified time interval. */
            std::atomic_bool    _timedOut{false};

    }; // SearchContext

    /*! @brief The key in the mDNS data for the Registry address. */
    const std::string kRegistryAddressKey{"registry_address"};

    /*! @brief Don't wait for the Registry - used with the Registry and test programs.
     @param[in] allowOneCheck @c true if a single scan for the Registry is done instead. */
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

#endif // not defined(nImOsearchContext_H_)

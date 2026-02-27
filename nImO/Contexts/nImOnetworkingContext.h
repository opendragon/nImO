//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOnetworkingContext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO execution contexts that use networking.
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
//  Created:    2022-12-14
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOnetworkingContext_H_))
# define nImOnetworkingContext_H_ /* Header guard */

# include <Containers/nImOarray.h>
# include <Containers/nImOmessage.h>
# include <Contexts/nImOcontext.h>
# include <nImOlogger.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO execution contexts that use networking. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief A class to provide support for an application that uses networking. */
    class NetworkingContext : public Context
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = Context;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] numReservedThreads The number of threads which the application will need for itself. */
            NetworkingContext // cppcheck-suppress noExplicitConstructor
                (const std::string &    tagForLogging = ""s,
                 const bool             logging = false,
                 const int              numReservedThreads = 0);

            /*! @brief The destructor. */
            ~NetworkingContext
                (void)
                override;

            /*! @brief Is this an InputOutputContext?
             @return @c nullptr. */
            virtual Ptr(InputOutputContext)
            asInputOutputContext
                (void);

            /*! @brief Is this an InputOutputContext?
             @return @c nullptr. */
            virtual CPtr(InputOutputContext)
            asInputOutputContext
                (void)
                const;

            /*! @brief Is this a ServiceContext?
             @return @c nullptr. */
            virtual Ptr(ServiceContext)
            asServiceContext
                (void);

            /*! @brief Is this a ServiceContext?
             @return @c nullptr. */
            virtual CPtr(ServiceContext)
            asServiceContext
                (void)
                const;

            /*! @brief Is this a UtilityContext?
             @return @c nullptr. */
            virtual Ptr(UtilityContext)
            asUtilityContext
                (void);

            /*! @brief Is this a UtilityContext?
             @return @c nullptr. */
            virtual CPtr(UtilityContext)
            asUtilityContext
                (void)
                const;

            /*! @brief Return the address and port to use for logging.
             @return The address and port to use for logging. */
            inline Connection
            getLoggingInfo
                (void)
                const
            {
                return _logConnection;
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
            gerRegistrySearchInfo
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
                return "_nimo_" + getRegistryName() + "._tcp.local."s;
            }

            /*! @brief Return the address and port to use for logging.
             @return The address and port to use for logging.. */
            inline Connection
            getStatusInfo
                (void)
                const
            {
                return _statusConnection;
            }

            /*! @brief Log a message.
             @param[in] stringToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (CPtr(char) stringToSend)
                const;

            /*! @brief Log a message.
             @param[in] stringToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (const std::string &    stringToSend)
                const;

            /*! @brief Log a message.
             @param[in] stringsToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (const StdStringVector &    stringsToSend)
                const;

            /*! @brief Set the symbolic name for the current process.
             @param[in] newTag The symbolic name for the current process. */
            void
            setTag
                (const std::string &    newTag);

        protected :
            // Protected methods.

            /*! @brief Return the options to be applied when launching the Registry automatically. */
            inline const Array &
            getRegistryLaunchOptions
                (void)
                const
            {
                return _registryLaunchOptions;
            }

            /*! @brief Return the path to the executable to be used when launching the Registry automatically. */
            inline const std::string &
            getRegistryLaunchPath
                (void)
                const
            {
                return _registryLaunchPath;
            }

            /*! @brief Return the search mode of the Registry. */
            inline RegistryMode
            getRegistrySearchMode
                (void)
                const
            {
                return _registrySearchMode;
            }

            /*! @brief Return the maximum number of retries allowed for the search for an active Registry. */
            inline int
            getRegistrySearchRetries
                (void)
                const
            {
                return _registrySearchRetries;
            }

            /*! @brief Return the number of seconds allowed for the search for an active Registry. */
            inline int
            getRegistrySearchTimeout
                (void)
                const
            {
                return _registrySearchTimeout;
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

            /*! @brief Set the command port for the next message.
             @param[in] port The command port number. */
            void
            setCommandPort
                (const IPv4Port commandPort);

        private :
            // Private methods.

        public :
            // Public fields.

            /*! @brief @c true if an IPv4 address was found. */
            static bool gHasIpv4;

            /*! @brief @c true if an IPv6 address was found. */
            static bool gHasIpv6;

            /*! @brief The first IPv4 address found. */
            static struct sockaddr_in   gServiceAddressIpv4;

            /*@ @brief The first IPv6 address found. */
            static struct sockaddr_in6  gServiceAddressIpv6;

        protected :
            // Protected fields.

            /*! @brief The pool of active threads. */
            boost::thread_group _pool;

        private :
            // Private fields.

            /*! @brief The multicast connection used for logging. */
            Connection  _logConnection{};

            /*! @brief The active logger. */
            std::shared_ptr<Logger> _logger{nullptr};

            /*! @brief Mutex to protect against simultaneous access to the logger. */
            mutable std::mutex  _loggerLock;

            /*! @brief @c true if logging has been enabled. */
            bool _loggingEnabled{false};

            /*! @brief The options to be applied when launching the Registry automatically. */
            Array   _registryLaunchOptions;

            /*! @brief The path to the Registry executable to be used when launching the Registry automatically. */
            std::string _registryLaunchPath;

            /*! @brief The mDNS name of the Registry. */
            std::string _registryName;

            /*! @brief The multicast search connection used for the Registry. */
            Connection  _registrySearchConnection{};

            /*! @brief The search mode of the Registry. */
            RegistryMode    _registrySearchMode;

            /*! @brief The maximum number of retries when searching for the Registry. */
            int _registrySearchRetries{0};

            /*! @brief The number of seconds before timeout occurs when searching for the Registry. */
            int _registrySearchTimeout{0};

            /*! @brief The multicast connection used for status changes. */
            Connection  _statusConnection{};

            /*! @brief A 'dummy' operation to keep the service queue alive. */
            UPwork  _work{};

# if (! MAC_OR_LINUX_OR_BSD_)
            /*! @brief Required for Windows networking. */
            WSADATA _wsaData;
# endif // not MAC_OR_LINUX_OR_BSD_

    }; // NetworkingContext

    /*! @brief A holder for a shared pointer to a NetworkingContext. */
    using SpNetworkingContext = std::shared_ptr<NetworkingContext>;

    /*! @brief The standard name for either mode. */
    extern const std::string    kModeBothName;

    /*! @brief The standard name for the mDNS mode. */
    extern const std::string    kModeMdnsName;

    /*! @brief The standard name for the multicast mode. */
    extern const std::string    kModeMulticastName;

    /*! @brief The standard name for an unknown mode. */
    extern const std::string    kModeUnknownName;

} // nImO

#endif // not defined(nImOnetworkingContext_H_)

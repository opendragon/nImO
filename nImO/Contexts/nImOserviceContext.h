//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOserviceContext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO execution contexts that use a command port.
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
//  Created:    2022-07-05
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOserviceContext_H_))
# define nImOserviceContext_H_ /* Header guard */

# include <Contexts/nImOcontextWithMDNS.h>
# include <nImOcallbackFunction.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO execution contexts that use a command port. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    class CommandHandler;
    class CommandSession;

    /*! @brief A holder for a unique pointer to a CommandHandler. */
    using SpCommandHandler = std::shared_ptr<CommandHandler>;

    /*! @brief A holder for a shared pointer to a CommandSession. */
    using SpCommandSession = std::shared_ptr<CommandSession>;

    /*! @brief A class to provide support for an application that uses a command port. */
    class ServiceContext : public ContextWithMDNS
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ContextWithMDNS;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] argc The number of arguments in 'argv'.
             @param[in] argv The command-line arguments provided to the application.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] startBrowser @c true if the browser thread is to be started.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            ServiceContext
                (const int              argc,
                 Ptr(Ptr(char))         argv,
                 const std::string &    tagForLogging = ""s,
                 const bool             logging = false,
                 const bool             startBrowser = false,
                 const std::string &    nodeName = ""s);

            /*! @brief The destructor. */
            ~ServiceContext
                (void)
                override;

            /*! @brief Add a command handler to the set of handlers.
             @param[in] commandName The name of the command to be handled.
             @param[in] theHandler The command handler to be added.
             @return @c true if the handler was successfully added. */
            bool
            addHandler
                (const std::string &    commandName,
                 SpCommandHandler       theHandler);

            /*! @brief Add the standard command handlers for a ServiceContext.
             @param[in] context The Context to be updated.
             @param[in] stopCallback A callback to be used when a stop command is processed. */
            static void
            addStandardHandlers
                (SpServiceContext       context,
                 Ptr(CallbackFunction)  stopCallback = nullptr);

            /*! @brief Is this a ServiceContext?
             @return @c this. */
            Ptr(ServiceContext)
            asServiceContext
                (void)
                override;

            /*! @brief Is this a ServiceContext?
             @return @c this. */
            CPtr(ServiceContext)
            asServiceContext
                (void)
                const
                override;

            /*! @brief Remove a session from the set of known sessions.
             @param[in] aSession The session to remove. */
            void
            forgetSession
                (SpCommandSession   aSession);

            /*! @brief Return the command-line arguments provided to the application.
             @return The command-line arguments provided to the application. */
            inline SpArray
            getCommandLine
                (void)
                const
            {
                return _commandLine;
            }

            /*! @brief Returns the address for the command port.
             @return The address of the command port. */
            inline IPv4Address
            getCommandAddress
                (void)
                const
            {
                return _commandAddress;
            }

            /*! @brief Returns a Connection that specifies the command port.
             @return A Connection with the command port details. */
            Connection
            getCommandConnection
                (void)
                const;

            /*! @brief Returns the port number for the command port.
             @return The port number of the command port. */
            inline IPv4Port
            getCommandPort
                (void)
                const
            {
                return _commandPort;
            }

            /*! @brief Retrieve a command handler from the set of handlers.
             @param[in] commandName The name of the command to be retrieved.
             @return @c nullptr if the handler was not found else the handler with the provided name. */
            SpCommandHandler
            getHandler
                (const std::string &    commandName)
                const;

            /*! @brief Returns the name of the service.
             @return The name of the service. */
            inline std::string
            getName
                (void)
                const
            {
                return _nodeName;
            }

            /*! @brief Remove a command handler from the set of handlers.
             @param[in] commandName The name of the command to be removed.
             @return @c true if the handler was successfully removed. */
            bool
            removeHandler
                (const std::string &    commandName);

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Create the command port to be used. */
            void
            createCommandPort
                (void);

            /*! @brief Destroy the command port. */
            void
            destroyCommandPort
                (void);

            /*! @brief Handle an asynchronous accept request.
             @param[in] newSession The command session for the request.
             @param[in] error The error status of the request. */
            void
            handleAccept
                (SpCommandSession   newSession,
                 const BSErr &      error);

            /*! @brief Remvoe all the command handlers. */
            void
            removeHandlers
                (void);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The acceptor for command port connections. */
            BTCP::acceptor  _acceptor;

            /*! @brief The command-line provided to the application. */
            SpArray _commandLine{};

            /*! @brief The command address. */
            IPv4Address _commandAddress{0};

            /*! @brief The command port. */
            IPv4Port    _commandPort{0};

            /*! @brief Set to @c false to stop asynchronous operations. */
            std::atomic_bool    _keepGoing{false};

            /*! @brief The active sessions. */
            std::set<SpCommandSession>  _sessions{};

            /*! @brief The command handlers. */
            std::map<std::string, SpCommandHandler> _commandHandlers{};

            /*! @brief The @nImO-visible name of the executing program. */
            std::string _nodeName{};

    }; // ServiceContext

} // nImO

#endif // not defined(nImOserviceContext_H_)

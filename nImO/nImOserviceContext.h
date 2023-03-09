//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOserviceContext.h
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

#if (! defined(nImOcontextWithCommandPort_H_))
# define nImOcontextWithCommandPort_H_ /* Header guard */

# include <nImOcontextWithMDNS.h>
# include <nImOcommandSession.h>

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
             @param[in] executable The name of the executing program.
             @param[in] tag The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] whichThreads Which threads, if any, to start.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            ServiceContext
                (const std::string &    executableName,
                 const std::string &    tag,
                 const bool             logging,
                 const ThreadMode       whichThreads = ThreadMode::LaunchBrowser,
                 const std::string &    nodeName = "");

            /*! @brief The destructor. */
            virtual
            ~ServiceContext
                (void);

            /*! @brief Remove a session from the set of known sessions.
             @param[in] aSession The session to remove. */
            void
            forgetSession
                (Ptr(CommandSession)    aSession);

            /*! @brief Returns the port number for the command port.
             @return The port number of the command port. */
            inline uint16_t
            getCommandPort
                (void)
                const
            {
                return _commandPort;
            }

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
                (Ptr(CommandSession)        newSession,
                 const system::error_code & error);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The acceptor for command port connections. */
            asio::ip::tcp::acceptor _acceptor;

            /*! @brief The command port. */
            uint16_t    _commandPort;

            /*! @brief Set to @c false to stop asynchronous operations. */
            std::atomic<bool>   _keepGoing;

            /*! @brief The active sessions. */
            std::set<Ptr(CommandSession)>   _sessions;

    }; // ServiceContext

#if 0
bool
ProcessStandardServiceOptions
    (const int                     argc,
     char * *                      argv,
     Utilities::DescriptorVector & argumentDescriptions,
     const YarpString &            serviceDescription,
     const YarpString &            matchingCriteria,
     const int                     year,
     const char *                  copyrightHolder,
     bool &                        goWasSet,
     bool &                        reportEndpoint,
     bool &                        reportOnExit,
     YarpString &                  tag,
     YarpString &                  serviceEndpointName,
     YarpString &                  servicePortNumber,
     AddressTagModifier &          modFlag,
     const OptionsMask             skipOptions,
     YarpStringVector *            arguments);
#endif//0

} // nImO

#endif // not defined(nImOcontextWithCommandPort_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryContext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the nImO 'registry' execution context.
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
//  Created:    2023-04-01
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOregistryContext_H_))
# define nImOregistryContext_H_ /* Header guard */

# include <Contexts/nImOserviceContext.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the 'utility' %nImO execution context. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide support for the 'registry' application. */
    class RegistryContext final : public ServiceContext
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ServiceContext;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] argc The number of arguments in 'argv'.
             @param[in] argv The command-line arguments provided to the application.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] startAnnnouncer @c true if the announcer thread is to be started. */
            RegistryContext
                (const int      argc,
                 Ptr(Ptr(char)) argv,
                 const bool     logging = false,
                 const bool     startAnnouncer = false);

            /*! @brief The destructor. */
            ~RegistryContext
                (void)
                override;

            /*! @brief Send a port announcement via mDNS.
             @param[in] port The port number being announced.
             @param[in] serviceName The mDNS service name.
             @param[in] hostName The name of the computer.
             @param[in] dataKey The key for the instance-specific data.
             @return @c true if the announcement was constructed and sent. */
            bool
            makePortAnnouncement
                (const IPv4Port         port,
                 const std::string &    serviceName,
                 const std::string &    hostName,
                 const std::string &    dataKey);

            /*! @brief Retract the announcement via mDNS. */
            void
            removeAnnouncement
                (void);

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief The announcer thread function.
             @param[in,out] owner The owning object for the thread. */
            static void
            executeAnnouncer
                (RegistryContext &  owner);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The thread which executes the announcer code. */
            Ptr(boost::thread)  _announcerThread{nullptr};

            /*! @brief Data to be used with the announcer thread. */
            std::unique_ptr<AnnounceServiceData>    _announceData{nullptr};

            /*! @brief @c true if the announcer thread is to be launched. */
            bool  _startAnnouncer{false};

    }; // RegistryContext

} // nImO

#endif // not defined(nImOregistryContext_H_)

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
# include <nImOlogger.h>
# include <nImOmessage.h>

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

namespace nImO
{
    /*! @brief A class to provide support for an application that uses mDNS. */
    class ContextWithMDNS : public ContextWithNetworking
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ContextWithNetworking;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] executable The name of the executing program.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            ContextWithMDNS
                (const std::string &    executableName,
                 const bool             logging,
                 const std::string &    nodeName = "");

            /*! @brief The destructor. */
            virtual
            ~ContextWithMDNS
                (void);

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
            (const StringVector &   stringsToSend)
            const;

        protected :
            // Protected methods.

        private :
            // Private methods.

//            /*! @brief Add a new listening port for the logged messages. */
//            void
//            addListeningPort
//                (void);

//            /*! @brief Remove a listening port. */
//            void
//            removeListeningPort
//                (void);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The multicast address used for logging. */
            uint32_t    _logAddress;

            /*! @brief The multicast port used for logging. */
            uint16_t    _logPort;

            /*! @brief @c true if logging has been enabled. */
            bool _loggingEnabled;

            /*! @brief The active logger. */
            Ptr(Logger) _logger;

    }; // ContextWithMDNS

} // nImO

#endif // ! defined(nImOcontextWithMDNS_H_)
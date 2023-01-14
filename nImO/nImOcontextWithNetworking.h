//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithNetworking.h
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

#if (! defined(nImOcontextWithNetworking_H_))
# define nImOcontextWithNetworking_H_ /* Header guard */

# include <nImOcontext.h>
# include <nImOlogger.h>
# include <nImOmessage.h>

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

/*! @brief A macro to convert four integers into an IPv4 address. */
# define IPV4_ADDR(a_, b_, c_, d_) \
                    (((a_ & 0x0ff) << 24) | ((b_ & 0x0ff) << 16) | ((c_ & 0x0ff) << 8) | (d_ & 0x0ff))

namespace nImO
{
    /*! @brief A class to provide support for an application that uses networking. */
    class ContextWithNetworking : public Context
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
             @param[in] executable The name of the executing program.
             @param[in] tag The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] numReservedThreads The number of threads which the application will need for itself.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            ContextWithNetworking
                (const std::string &    executableName,
                 const std::string &    tag,
                 const bool             logging,
                 const int              numReservedThreads = 0,
                 const std::string &    nodeName = "");

            /*! @brief The destructor. */
            virtual
            ~ContextWithNetworking
                (void);

            /*! @brief Return the address and port to use for logging.
             @param[out] address The address for logging.
             @param[out] port The port for logging. */
            inline void
            getLoggingInfo
                (uint32_t & address,
                 uint16_t & port)
                const
            {
                address = _logAddress;
                port = _logPort;
            }

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

        public :
            // Public fields.

        protected :
            // Protected fields.

            /*! @brief The pool of active threads. */
            boost::thread_group _pool;

        private :
            // Private fields.

            /*! @brief A 'dummy' operation to keep the service queue alive. */
            UPwork  _work;

            /*! @brief The multicast address used for logging. */
            uint32_t    _logAddress;

            /*! @brief The multicast port used for logging. */
            uint16_t    _logPort;

            /*! @brief @c true if logging has been enabled. */
            bool _loggingEnabled;

            /*! @brief The active logger. */
            Ptr(Logger) _logger;

# if (! MAC_OR_LINUX_)
            /*! @brief Required for Windows networking. */
            WSADATA _wsaData;
# endif // not MAC_OR_LINUX_

    }; // ContextWithNetworking

} // nImO

#endif // not defined(nImOcontextWithNetworking_H_)

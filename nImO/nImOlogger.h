//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOlogger.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the nImO logging mechanism.
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
//  Created:    2022-07-19
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOlogger_H_))
# define nImOlogger_H_ /* Header guard */

# include <ContainerTypes/nImOmessage.h>
# include <Contexts/nImOcontext.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the %nImO logging mechanism. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief The key for the commmand port in a log message. */
    extern const std::string    kCommandPortKey;

    /*! @brief The key for the computer name in a log message. */
    extern const std::string    kComputerNameKey;

    /*! @brief The key for the message in a log message. */
    extern const std::string    kMessageKey;

    /*! @brief The The key for the tag in a log message. */
    extern const std::string    kTagKey;

    /*! @brief A class to provide the @nImO logging mechanism. */
    class Logger final
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] service The I/O service to attach to.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logConnection The multicast connection to use. */
            Logger
                (SPservice              service,
                 const std::string &    tagForLogging,
                 const Connection &     logConnection);

            /*! @brief Log a simple message.
             @param[in] stringToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (CPtr(char) stringToSend);

            /*! @brief Log a simple message.
             @param[in] stringToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (const std::string &    stringToSend);

            /*! @brief Log a message.
             @param[in] valueToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (SpValue    valueToSend);

            /*! @brief Log a complex message.
             @param[in] stringsToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (const StringVector &   stringsToSend);

            /*! @brief Set the command port for the next message.
             @param[in] port The command port number. */
            void
            setCommandPort
                (const uint16_t commandPort);

        protected :
            // Protected methods.

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The multicast connection used for logging. */
            Connection  _connection{};

            /*! @brief The endpoint for a multicast transmission. */
            BUDP::endpoint  _endpoint{};
        
            /*! @brief The socket for a multicast transmission. */
            BUDP::socket    _socket;

            /*! @brief The symbolic name for the current process. */
            SpString    _tag{};

            /*! @brief The name of the computer. */
            SpString    _computerName{};

            /*! @brief The command port for the requesting Context. */
            SpInteger   _commandPort{};

    }; // Logger

} // nImO

#endif // not defined(nImOlogger_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOlogger.hpp
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

#if (! defined(nImOlogger_HPP_))
# define nImOlogger_HPP_ /* Header guard */

# include <nImOmessage.hpp>

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

            /*! @brief The constructor. */
            Logger
                (void);

            /*! @brief The destructor. */
            virtual
            ~Logger
                (void);

            /*! @brief Add a new listening port for the logged messages. */
            void
            addListeningPort
                (void);

            /*! @brief Remove a listening port. */
            void
            removeListeningPort
                (void);

            /*! @brief Log a message.
             @param[in] messageToSend The message to be logged.
             @return @c true if the message was successfully logged. */
            bool
            report
                (Message &  messageToSend)
                const;

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Remove all listening ports. */
            void
            removeAllListeningPorts
                (void);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

    }; // Logger

} // nImO

#endif // ! defined(nImOlogger_HPP_)

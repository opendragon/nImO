//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOreceiveFromMulticast.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO handling messages on a multicast port.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2026 by OpenDragon.
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
//  Created:    2026-04-26
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOreceiveFromMulticast_H_))
# define nImOreceiveFromMulticast_H_ /* Header guard */

# include <Contexts/nImOcontext.h>
# include <nImOmainSupport.h>
# include <nImOreceiveQueue.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for receiving %nImO messages from a multicast group. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to handle receiving messages from a multicast group. */
    class ReceiveFromMulticast final
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
             @param[in] runFlag A reference to the flag that is used to stop execution.
             @param[in] theConnection The connection to listen on.
             @param[in] theQueue The receive queue to be updated. */
            ReceiveFromMulticast
                (nImO::SPservice            service,
                 const nImO::Connection &   theConnection,
                 nImO::ReceiveQueue &       theQueue);

            /*! @brief The destructor. */
            ~ReceiveFromMulticast
                (void);

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Receive a message. */
            void
            receiveAMessage
                (void);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief Where to store received messages. */
            nImO::ReceiveQueue &  _queue;

            /*! @brief The socket for a multicast reception. */
            BUDP::socket    _socket;

            /*! @brief The sender's endpoint. */
            BUDP::endpoint  _senderEndpoint{};

            /*! @brief A buffer for the raw message data. */
            std::array<char, 2048>  _data{};

    }; // ReceiveFromMulticast

} // nImO

#endif // not defined(nImOreceiveFromMulticast_H_)

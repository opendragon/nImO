//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOinChannel.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO incoming connections to services.
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
//  Created:    2023-04-14
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOinChannel_H_))
# define nImOinChannel_H_ /* Header guard */

# include <nImObaseChannel.h>
# include <nImOreceiveQueue.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO incoming connections to services. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide incoming connections to services. */
    class InChannel final : public BaseChannel
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = BaseChannel;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] inQueue The queue where incoming messages are placed.
             @param[in] context The owning context
             @param[in] path The path for the channel.
             @param[in] index The index of the channel. */
            InChannel
                (ReceiveQueue &         inQueue,
                 InputOutputContext &   context,
                 const std::string &    path,
                 const int              index = 0);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            InChannel
                (InChannel &&   other)
                noexcept = delete;

            /*! @brief The destructor. */
            virtual
            ~InChannel
                (void)
                override;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            InChannel &
            operator=
                (InChannel && other)
                noexcept = delete;

            /*! @brief Receive messages via the TCP socket. */
            void
            receiveTcpMessages
                (void);

            /*! @brief Receive messages via the UDP socket. */
            void
            receiveUdpMessages
                (void);

            bool
            setUp
                (const TransportType    mode);

            /*! @brief Start the channel.
             @param[in] senderAddress The allowed address for messages.
             @param[in] senderPort The allowed port for messages.
             @return @c true if the channel was successfully started. */
            bool
            start
                (const IPv4Address  senderAddress,
                 const IPv4Port     senderPort);

            /*! @brief Stop the channel and clear settings.
             @return @c true if the channel was successfully stopped. */
            bool
            stop
                (void)
                override;

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

            /*! @brief The source IP address to match against. */
            IPv4Address _matchAddress{0};

            /*! @brief The source port to match against. */
            IPv4Port    _matchPort{0};

            /*! @brief The acceptor TCP connections. */
            SpAcceptorTCP   _tcpAcceptor{};

            /*! @brief The sender's endpoint for TCP. */
            BTCP::endpoint  _tcpSenderEndpoint{};

            /*! @brief The sender's endpoint for UDP. */
            BUDP::endpoint  _udpSenderEndpoint{};

            /*! @brief A buffer for the raw message data. */
            std::array<char, 2048>  _rawData{};

            /*! @brief The destination for incoming messages. */
            ReceiveQueue &  _inQueue;

            /*! @brief @c true if the sender address and port are ignored. */
            bool    _unfiltered{false};

    }; // InChannel

} // nImO

#endif // not defined(nImOinChannel_H_)

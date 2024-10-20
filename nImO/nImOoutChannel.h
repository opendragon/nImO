//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOoutChannel.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO outgoing connections to services.
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

#if (! defined(nImOoutChannel_H_))
# define nImOoutChannel_H_ /* Header guard */

# include <nImObaseChannel.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO outgoing connections to services. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide outgoing connections to services. */
    class OutChannel final : public BaseChannel
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
             @param[in] context The owning context
             @param[in] path The path for the channel.
             @param[in] index The index of the channel. */
            OutChannel
                (InputOutputContext &   context,
                 const std::string &    path,
                 const int              index = 0);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            OutChannel
                (OutChannel &&    other)
                noexcept = delete;

            /*! @brief The destructor. */
            virtual
            ~OutChannel
                (void)
                override;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            OutChannel &
            operator=
                (OutChannel && other)
                noexcept = delete;

            /*! @brief Send a message.
             @param[in] valueToSend The message to be sent.
             @return @c true if the message was successfully sent. */
            bool
            send
                (SpValue    valueToSend);

            /*! @brief Configure the netowkr port for the channel.
             @param[in] receiveAddress The address of the receiver.
             @param[in] receivePort The port of the receiver.
             @param[in] mode The transport mode to use.
             @return @c true if the network information for the channel was set up. */
            bool
            setUp
                (const IPv4Address      receiveAddress,
                 const IPv4Port         receivePort,
                 const TransportType    mode);

            /*! @brief Start the channel.
             @return @c true if the channel was successfully started. */
            bool
            start
                (void);

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

            /*! @brief The target IP address. */
            IPv4Address _destinationAddress{0};

            /*! @brief The target port. */
            IPv4Port    _destinationPort{0};

            /*! @brief The target endpoint for UDP. */
            BTCP::endpoint  _tcpSendpoint{};

            /*! @brief The target endpoint for UDP. */
            BUDP::endpoint  _udpSendpoint{};

    }; // OutChannel

} // nImO

#endif // not defined(nImOoutChannel_H_)

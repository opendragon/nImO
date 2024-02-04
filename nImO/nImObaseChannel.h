//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImObaseChannel.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO connections to services.
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

#if (! defined(nImObaseChannel_H_))
# define nImObaseChannel_H_ /* Header guard */

# include <nImOchannelStatistics.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO connections to services. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    class InputOutputContext;

    /*! @brief A class to provide connections to services. */
    class BaseChannel
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The destructor. */
            virtual
            ~BaseChannel
                (void);

            /*! @brief Return the connection.
             @return The connection. */
            inline const Connection &
            getConnection
                (void)
                const
            {
                return _connection;
            }

            /*! @brief Return the name.
             @return The name. */
            inline std::string
            getName
                (void)
                const
            {
                return _name;
            }

            /*! @brief Retrieve the current statistics.
             @param[out] numberOfBytes The number of bytes transferred.
             @param[out] numberOfMessage The number of messages transferred. */
            inline void
            getStatistics
                (int64_t &  numberOfBytes,
                 int64_t &  numberOfMessages)
            {
                _statistics.get(numberOfBytes, numberOfMessages);
            }

            /*! @brief Return @c true if the channel is connected.
             @return @c true if the channel is connected. */
            bool
            isConnected
                (void)
                const;

            /*! @brief Stop the channel and clear settings.
             @return @c true if the channel was successfully stopped. */
            virtual bool
            stop
                (void) = 0;

        protected :
            // Protected methods.

            /*! @brief The constructor.
             @param[in] context The owning context
             @param[in] path The path for the channel.
             @param[in] index The index of the channel. */
            BaseChannel
                (InputOutputContext &   context,
                 const std::string &    path,
                 const int              index = 0);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            BaseChannel
                (BaseChannel &&    other)
                noexcept = delete;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            BaseChannel &
            operator=
                (BaseChannel && other)
                noexcept = delete;

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

            /*! @brief The owning context. */
            InputOutputContext &    _context;

            /*! @brief The socket to use for TCP communication. */
            SpSocketTCP    _tcpSocket{};

            /*! @brief The socket to use for UDP communication. */
            SpSocketUDP    _udpSocket{};

            /*! @brief The IP address, port and mode for the communication. */
            Connection  _connection{};

            /*! @brief The name to be used when connecting or disconnecting. */
            std::string _name{};

            /*! @brief The index for the channel. */
            int _index{0};

            /*! @brief @c true once a TCP connection has been established. */
            std::atomic_bool    _tcpConnected{false};

            /*! @brief @c true once a UDP connection has been established. */
            std::atomic_bool    _udpConnected{false};

            /*! @brief The transfer statistics for the channel. */
            ChannelStatistics    _statistics{};

        private :
            // Private fields.

    }; // BaseChannel

} // nImO

#endif // not defined(nImObaseChannel_H_)

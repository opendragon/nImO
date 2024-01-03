//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOreceivedData.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for data used with nImO network receivers.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-01-03
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOreceivedData_H_))
# define nImOreceivedData_H_ /* Header guard */

# include <nImOcommon.h>

# if MAC_OR_LINUX_
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
# endif // MAC_OR_LINUX_
# include <mdns.hpp>
# if MAC_OR_LINUX_
#  pragma GCC diagnostic pop
# endif // MAC_OR_LINUX_

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for data used with %nImO network receivers. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A structure to hold a received message. */
    struct ReceivedData final
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
             @param[in] tag The channel index for the message.
             @param[in] receivedMessage The message from the sender.
             @param[in] receivedAddress The send IP address. */
            inline ReceivedData
                (const int                  tag,
                 nImO::SpValue              receivedMessage,
                 const nImO::IPv4Address    receivedAddress,
                 const nImO::IPv4Port       receivedPort) :
                _receivedMessage(receivedMessage), _receivedAddress(receivedAddress), _receivedPort(receivedPort), _tag{tag}
            {
            }

        protected :
            // Protected methods.

        private :
            // Private methods.

        public :
            // Public fields.

            /*! @brief The message from the sender. */
            nImO::SpValue   _receivedMessage{};

            /*! @brief The IP address of the sender. */
            nImO::IPv4Address   _receivedAddress{};

            /*! @brief The IP port of the sender. */
            nImO::IPv4Port  _receivedPort{};

            /*! @brief The tag for the associated Message. */
            int _tag;

        protected :
            // Protected fields.

        private :
            // Private fields.

    }; // ReceivedData

    /*! @brief A holder for a shared pointer to ReceivedData. */
    using SpReceivedData = std::shared_ptr<ReceivedData>;

} // nImO

#endif // not defined(nImOreceivedData_H_)

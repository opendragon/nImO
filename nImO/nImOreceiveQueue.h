//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOreceiveQueue.h
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

#if (! defined(nImOreceiveQueue_H_))
# define nImOreceiveQueue_H_ /* Header guard */

# include <nImOreceivedData.h>

# if MAC_OR_LINUX_OR_BSD_
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
# endif // MAC_OR_LINUX_OR_BSD_
# include <mdns.hpp>
# if MAC_OR_LINUX_OR_BSD_
#  pragma GCC diagnostic pop
# endif // MAC_OR_LINUX_OR_BSD_

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
    class ReceiveQueue final
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief Convert raw bytes to a message and add to the queue.
             @param[in] tag The input channel index.
             @param[in] senderAddress The sender's IP address.
             @param[in] senderPort The sender's port.
             @param[in] receivedAsString The raw data as a string. */
            void
            addRawBytesAsMessage
                (const int              tag,
                 const IPv4Address      senderAddress,
                 const IPv4Port         senderPort,
                 const std::string &    receivedAsString);

            /*! @brief Convert raw bytes to a message and add to the queue.
             @param[in] tag The input channel index.
             @param[in] receivedAsString The raw data as a string. */
            void
            addRawBytesAsMessage
                (const int              tag,
                 const std::string &    receivedAsString)
            {
                addRawBytesAsMessage(tag, 0, 0, receivedAsString);
            }

            /*! @brief Return the next available message in the queue if there is one.
             @return The next available message or an empty pointer if the queue is being stopped. */
            SpReceivedData
            getNextMessage
                (void);

            /*! @brief Empty the queue and stop adding to it.*/
            void
            stop
                (void);

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

            /*! @brief The sequence of received messages. */
            std::deque<nImO::SpReceivedData>    _receivedData{};

            /*! @brief Used to protect the sequence of received messages. */
            std::mutex _receivedLock{};

            /*! @brief Used to indicate that the sequence of received messages is ready to use. */
            std::condition_variable    _receivedCondition{};

            /*! @brief Set to @c true to disable and empty the queue. */
            std::atomic_bool    _stop{false};

    }; // ReceiveQueue

} // nImO

#endif // not defined(nImOreceiveQueue_H_)

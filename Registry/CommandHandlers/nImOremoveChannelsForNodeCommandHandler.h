//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Registry/CommandHandlers/nImOremoveChannelsForNodeCommandHandler.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the nImO 'remove channels for node' command handler.
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
//  Created:    2023-05-21
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOremoveChannelsForNodeCommandHandler_H_))
# define nImOremoveChannelsForNodeCommandHandler_H_ /* Header guard */

# include "nImOregistryCommandHandler.h"

# include "../nImOregistry.h"

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the %nImO 'remove channels for node' command handler. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide a handler for the 'remove channels for node' command. */
    class RemoveChannelsForNodeCommandHandler final : public RegistryCommandHandler
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = RegistryCommandHandler;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] owner The owning Context.
             @param[in] theRegistry The Registry to use when processing a request.
             @param[in] statusConnection Where to report status changes. */
            RemoveChannelsForNodeCommandHandler
                (SpServiceContext   owner,
                 SpRegistry         theRegistry,
                 const Connection & statusConnection);

            /*! @brief Handle the command, returning @c true if successful.
             @param[in] socket The socket where the response should be sent.
             @param[in] arguments The arguments to the command, with the first element being the command received.
             @param[out] failureReason The reason for a failure to send a response.
             @return @c true if a response was sent. */
            bool
            doIt
                (BTCP::socket & socket,
                 const Array &  arguments,
                 std::string &  reason)
                const
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

            /*! @brief The multicast connection used for status reports. */
            Connection  _statusConnection{};

    }; // RemoveChannelsForNodeCommandHandler

} // nImO

#endif // not defined(nImOremoveChannelsForNodeCommandHandler_H_)

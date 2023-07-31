//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommandHandler.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO command handlers.
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
//  Created:    2023-03-25
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOcommandHandler_H_))
# define nImOcommandHandler_H_ /* Header guard */

# include <Contexts/nImOcontextWithMDNS.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO command handlers. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide functors used to process commands. */
    class CommandHandler
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
            ~CommandHandler
                (void);

            /*! @brief The copy constructor.
            @param[in] other The object to be copied. */
            CommandHandler
                (const CommandHandler &  other) = delete;

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            CommandHandler
                (CommandHandler &&    other) = delete;

            /*! @brief Handle the command, returning @c true if successful.
             @param[in] socket The socket where the response should be sent.
             @param[in] arguments The arguments to the command, with the first element being the command received.
             @return @c true if a response was sent. */
            virtual bool
            doIt
                (asio::ip::tcp::socket &    socket,
                 const Array &              arguments)
                const = 0;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            CommandHandler &
            operator=
                (const CommandHandler &  other) = delete;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            CommandHandler &
            operator=
                (CommandHandler &&  other) = delete;

            /*! @brief Send a response to satisfy the requesters pending read.
             @parm[in] context The context for the responder.
             @param[in,out] socket The TCP/IP socket to use for communication. */
            static void
            SendBadResponse
                (SpContextWithNetworking    context,
                 SPsocketTCP                socket);

        protected :
            // Protected methods.

            /*! @brief The constructor.
             @param[in] owner The owning Context.  */
            CommandHandler
                (SpContextWithNetworking    owner);

            /*! @brief Send a complex reponse for the command.
             @param[in] socket The socket where the response should be sent.
             @param[in] responseKey The response type.
             @param[in] responseText The description of the response.
             @param[in] contents The data for the response..
             @return @c true if a response was sent. */
            bool
            sendComplexResponse
                (asio::ip::tcp::socket &    socket,
                 const std::string          responseKey,
                 const std::string          responseText,
                 SpValue                    contents)
                const;

            /*! @brief Send a simple reponse for the command.
             @param[in] socket The socket where the response should be sent.
             @param[in] responseKey The response type.
             @param[in] responseText The description of the response.
             @param[in] wasOK @c true if the command succeeded and @c false otherwise.
             @return @c true if a response was sent. */
            bool
            sendSimpleResponse
                (asio::ip::tcp::socket &    socket,
                 const std::string          responseKey,
                 const std::string          responseText,
                 const bool                 wasOK = false)
                const;

            /*! @brief Send a status report.
             @param[in] context The context for the responder.
             @param[in] whereToSend The multiport address and port to send the status report to.
             @param[in] statusChange The status change details. */
            void
            sendStatusReport
                (SpContextWithNetworking    context,
                 Connection                 whereToSend,
                 const std::string &        statusChange)
                const;

        private :
            // Private methods.

            /*! @brief Send a simple reponse for the command.
             @param[in] context The context for the responder.
             @param[in] socket The socket where the response should be sent.
             @param[in] responseKey The response type.
             @param[in] responseText The description of the response.
             @param[in] contents The data for the response..
             @return @c true if a response was sent. */
            static bool
            sendComplexResponseWithContext
                (SpContextWithNetworking    context,
                 asio::ip::tcp::socket &    socket,
                 const std::string          responseKey,
                 const std::string          responseText,
                 SpValue                    contents);

            /*! @brief Send a simple reponse for the command.
             @param[in] context The context for the responder.
             @param[in] socket The socket where the response should be sent.
             @param[in] responseKey The response type.
             @param[in] responseText The description of the response.
             @param[in] wasOK @c true if the command succeeded and @c false otherwise.
             @return @c true if a response was sent. */
            static bool
            sendSimpleResponseWithContext
                (SpContextWithNetworking    context,
                 asio::ip::tcp::socket &    socket,
                 const std::string          responseKey,
                 const std::string          responseText,
                 const bool                 wasOK);

        public :
            // Public fields.

        protected :
            // Protected fields.

            /*! @brief The owning Context. */
            SpContextWithNetworking _owner{};

        private :
            // Private fields.

    }; // CommandHandler

} // nImO

#endif // not defined(nImOcommandHandler_H_)

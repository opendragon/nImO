//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOcontext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the nImO execution context.
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
//  Created:    2022-07-05
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOcontext_H_))
# define nImOcontext_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
# endif // defined(__APPLE__)
# include <boost/asio/read_until.hpp>
# include <boost/bind/bind.hpp>
# include <boost/dll/runtime_symbol_info.hpp>
# include <boost/filesystem.hpp>
# include <boost/shared_array.hpp>
# include <boost/thread.hpp>
# include <boost/thread/locks.hpp>
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the %nImO execution context. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief A holder for a shared pointer to an Asio service . */
    using SPservice = std::shared_ptr<asio::io_service>;

    /*! @brief A holder for a shared pointer to an Asio TCP/IP socket. */
    using SPsocketTCP = std::shared_ptr<asio::ip::tcp::socket>;

    /*! @brief A holder for a shared pointer to an Asio UDP/IP socket. */
    using SPsocketUDP = std::shared_ptr<asio::ip::udp::socket>;

    /*! @brief A holder for a unique pointer to an Asio 'work' placeholder. */
    using UPwork = std::unique_ptr<asio::io_service::work>;

    /*! @brief A class to provide binary data with unknown structure. */
    class Context
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            Context
                (const Context &  other) = delete;

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Context
                (Context &&  other)
                noexcept = delete;

            /*! @brief The destructor. */
            virtual
            ~Context
                (void);

            /*! @brief Return the I/O service.
             @return The I/O service. */
            inline SPservice
            getService
                (void)
            {
                return _service;
            }

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            Context &
            operator=
                (const Context &  other) = delete;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            Context &
            operator=
                (Context &&  other)
                noexcept = delete;

        protected :
            // Protected methods.

            /*! @brief The constructor.
            @param[in] executable The name of the executing program.
            @param[in] nodeName The @nImO-visible name of the executing program. */
            Context
                (const std::string &    executableName,
                 const std::string &    nodeName = "");

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

            /*! @brief The name of the executing program. */
            std::string _executableName{};

            /*! @brief The @nImO-visible name of the executing program. */
            std::string _nodeName{};

        private :
            // Private fields.

            /*! @brief The service object to be used for asynchronous operations. */
            SPservice   _service{};

    }; // Context

} // nImO

#endif // not defined(nImOcontext_H_)

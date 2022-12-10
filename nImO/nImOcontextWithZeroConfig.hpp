//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithZeroConfig.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO execution contexts that use mDNS.
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
//  Created:    2022-07-18
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOcontextWithZeroConfig_HPP_))
# define nImOcontextWithZeroConfig_HPP_ /* Header guard */

# include <nImOcontext.hpp>
# include <nImOlogger.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO execution contexts that use mDNS. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide support for an application that uses mDNS. */
    class ContextWithZeroConfig : public Context
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = Context;

        public :
            // Public methods.

            /*! @brief The destructor. */
            virtual
            ~ContextWithZeroConfig
                (void);

            /*! @brief Log a message.
            @param[in] message The message to be logged. */
            void
            report
                (const std::string &    message)
                const;

        protected :
            // Protected methods.

            /*! @brief The constructor.
            @param[in] executable The name of the executing program.
            @param[in] logging @c true if the executing program is to be logged.
            @param[in] nodeName The @nImO-visible name of the executing program. */
            ContextWithZeroConfig
                (const std::string &    executableName,
                 const bool             logging,
                 const std::string &    nodeName = "");

        private :
            // Private methods.

            /*! @brief Add a new listening port for the logged messages. */
            void
            addListeningPort
                (void);

            /*! @brief Remove a listening port. */
            void
            removeListeningPort
                (void);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.
            Logger *    _logger;

    }; // ContextWithZeroConfig

} // nImO

#endif // ! defined(nImOcontextWithZeroConfig_HPP_)

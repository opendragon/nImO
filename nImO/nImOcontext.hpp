//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontext.hpp
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

#if (! defined(nImOcontext_HPP_))
# define nImOcontext_HPP_ /* Header guard */

# include <nImOcommon.hpp>

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

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
# endif // defined(__APPLE__)
# include <boost/asio.hpp>
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

using namespace boost;

namespace nImO
{
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

            /*! @brief The destructor. */
            virtual
            ~Context
                (void);

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
            std::string _executableName;

            /*! @brief The @nImO-visible name of the executing program. */
            std::string _nodeName;

            /*! @brief The service object to be used for asynchronous operations. */
            asio::io_service    _ios;

        private :
            // Private fields.

    }; // Context

} // nImO

#endif // ! defined(nImOcontext_HPP_)

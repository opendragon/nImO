//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithCommandPort.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO execution contexts that use a command port.
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

#if (! defined(nImOcontextWithCommandPort_HPP_))
# define nImOcontextWithCommandPort_HPP_ /* Header guard */

# include <nImOcontextWithZeroConfig.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO execution contexts that use a command port. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide support for an application that uses a command port. */
    class ContextWithCommandPort : public ContextWithZeroConfig
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ContextWithZeroConfig;

        public :
            // Public methods.

            /*! @brief The destructor. */
            virtual
            ~ContextWithCommandPort
                (void);

        protected :
            // Protected methods.

            /*! @brief The constructor.
            @param[in] executable The name of the executing program.
            @param[in] logging @c true if the executing program is to be logged.
            @param[in] autoLaunchRegistry @c true if the Registry program is to be launched if not already running.
            @param[in] nodeName The @nImO-visible name of the executing program. */
            ContextWithCommandPort
                (const std::string &    executableName,
                const bool             logging,
                const bool             autoLaunchRegistry = true,
                const std::string &    nodeName = "");

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

    }; // ContextWithCommandPort

} // nImO

#endif // ! defined(nImOcontextWithCommandPort_HPP_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOutilityContext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the nImO 'utility' execution context.
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

#if (! defined(nImOutilityContext_H_))
# define nImOutilityContext_H_ /* Header guard */

# include <Contexts/nImOcontextWithMDNS.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the 'utility' %nImO execution context. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide support for a 'utility' application. */
    class UtilityContext final : public ContextWithMDNS
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ContextWithMDNS;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged. */
            UtilityContext
                (const std::string &    tagForLogging = ""s,
                 const bool             logging = false);

            /*! @brief Is this a UtilityContext?
             @return @c this. */
            Ptr(UtilityContext)
            asUtilityContext
                (void)
                override;

            /*! @brief Is this a UtilityContext?
             @return @c this. */
            CPtr(UtilityContext)
            asUtilityContext
                (void)
                const
                override;

            /*! @brief Log a message.
             @param[in] stringToSend The message to be logged.
             @param[in] andCerr @c true if the message is to be written to the standard error stream.
             @return @c true if the message was successfully logged. */
            bool
            report
                (CPtr(char) stringToSend,
                 const bool andCerr = true)
                const;

            /*! @brief Log a message.
             @param[in] stringToSend The message to be logged.
             @param[in] andCerr @c true if the message is to be written to the standard error stream.
             @return @c true if the message was successfully logged. */
            bool
            report
                (const std::string &    stringToSend,
                 const bool             andCerr = true)
                const;

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

    }; // UtilityContext

} // nImO

#endif // not defined(nImOutilityContext_H_)

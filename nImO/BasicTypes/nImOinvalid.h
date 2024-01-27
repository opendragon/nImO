//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOinvalid.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO invalid values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2017 by OpenDragon.
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
//  Created:    2017-03-05
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOinvalid_H_))
# define nImOinvalid_H_ /* Header guard */

# include <BasicTypes/nImOflaw.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO invalid values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide descriptions of invalid values. */
    class Invalid final : public Flaw
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = Flaw;

        public :
            // Public methods.

            /*! @brief The constructor. */
            Invalid
                (void);

            /*! @brief The constructor.
            @param[in] description A textual description of the problem encountered. */
            explicit Invalid
                (const std::string &    description);

            /*! @brief The constructor.
            @param[in] description A textual description of the problem encountered.
            @param[in] position A number that represents an offset where the problem occurred. */
            Invalid
                (const std::string &    description,
                 const int64_t          position);

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            Invalid
                (Invalid &&	other)
                noexcept;

            /*! @brief Write a short description of the Value to a stream.
             @param[in/out] output The stream to write to. */
            void
            describe
                (std::ostream & output)
                const
                override;

            /*! @brief Return a textual description of the Flaw.
            @return A textual description of the Flaw. */
            std::string
            getDescription
                (void)
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

            /*! @brief A description of what was found to be invalid. */
            std::string _description{};

    }; // Invalid

} // nImO

#endif // not defined(nImOinvalid_H_)

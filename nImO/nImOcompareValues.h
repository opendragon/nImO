//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcompareValues.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO comparing pointers to values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-04-03
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOcompareValues_H_))
# define nImOcompareValues_H_ /* Header guard */

# include <BasicTypes/nImOvalue.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the %nImO value comparison functional objects. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide values that are used to compare pointers to values. */
    class CompareValues final
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor. */
            CompareValues
                (void) = default;

            /*! @brief The copy constructor.
            @param[in] other The object to be copied. */
            inline CompareValues
                (const CompareValues &	other)
            {
                NIMO_UNUSED_VAR_(other);
            }

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            CompareValues
                (CompareValues &&	other)
                noexcept = default;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            CompareValues &
            operator=
                (CompareValues &&    other)
                noexcept;

            /*! @brief Compare two Values, returning @c true if the first is less than the second.
            @param[in] lhs The first Value to be compared.
            @param[in] rhs The second Value to be compared.
            @return @c true if the first Value is less than the second. */
            bool
            operator()
                (SpValue    lhs,
                 SpValue    rhs)
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

    }; // CompareValues

} // nImO

#endif // not defined(nImOcompareValues_H_)

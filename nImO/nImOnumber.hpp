//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOnumber.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO numeric values.
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
//  Created:    2016-03-21
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOnumber_HPP_))
# define nImOnumber_HPP_ /* Header guard */

# include <nImO/nImOatom.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO numeric values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide numeric values. */
    class Number : public Atom
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        typedef Atom inherited;

        public :
        // Public methods.

        /*! @brief The constructor. */
        Number(void);

        /*! @brief The destructor. */
        virtual
        ~Number(void);

        /*! @brief Return non-@c NULL if the object is a Number.
         @returns Non-@c NULL if the object is a Number and @c NULL otherwise. */
        virtual inline const Number *
        asNumber(void)
        const
        override
        {
            return this;
        } // asNumber
        
        /*! @brief Return the characters that can appear as the start of a Number.
         @returns The characters that can appear as the start of a Number. */
        static const char *
        getInitialCharacters(void);

        /*! @brief Convert a readable representation of the object in a buffer into an object.
         @param[in] inBuffer The buffer to be scanned.
         @param[in,out] position Where in the buffer to start.
         @returns A new object if there is a valid object in the buffer and @c NULL otherwise. */
        static SpValue
        readFromStringBuffer(const StringBuffer &inBuffer,
                             size_t             &position);

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

    }; // Number

} // nImO

#endif // ! defined(nImOnumber_HPP_)

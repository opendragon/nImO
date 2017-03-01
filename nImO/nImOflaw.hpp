//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOflaw.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO error or flaw values.
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
//  Created:    2017-02-28
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOflaw_HPP_))
# define nImOflaw_HPP_ /* Header guard */

# include <nImO/nImOvalue.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO error or flaw values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide simple values. */
    class Flaw : public Value
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        using inherited = Value;

    public :
        // Public methods.

        /*! @brief The destructor. */
        virtual
        ~Flaw(void);

        /*! @brief Return non-@c nullptr if the object is a Flaw.
         @returns Non-@c nullptr if the object is a Double and @c nullptr otherwise. */
        virtual inline const Flaw *
        asFlaw(void)
        const
        override
        {
            return this;
        } // asFlaw

        /*! @brief Return a textual description of the Flaw.
         @returns A textual description of the Flaw. */
        virtual std::string
        getDescription(void)
        const = 0;

    protected :
        // Protected methods.

        /*! @brief The constructor. */
        Flaw(void);
        
    private :
        // Private methods.

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

    }; // Flaw

} // nImO

#endif // ! defined(nImOflaw_HPP_)

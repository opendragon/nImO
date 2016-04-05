//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOset.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO sets.
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

#if (! defined(nImOset_HPP_))
# define nImOset_HPP_ /* Header guard */

# include <nImO/nImOcompareValues.hpp>
# include <nImO/nImOcontainer.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO sets. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide collections with set-like behaviour. */
    class Set : public Container,
                public std::set<Value *, CompareValues>
    {
    public :
        // Public type definitions.

        /*! @brief The return result from the insert method. */
        typedef std::pair<std::set<Value *, CompareValues>::iterator, bool> insertResult;

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The first class that this class is derived from. */
        typedef Container inherited1;

        /*! @brief The second class that this class is derived from. */
        typedef std::set<Value *, CompareValues> inherited2;

    public :
        // Public methods.

        /*! @brief The constructor. */
        Set(void);

        /*! @brief The destructor. */
        ~Set(void);

        /*! @fn virtual void
                addToStringBuffer(StringBuffer & outBuffer)
         @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to. */
        DECLARE_ADDTOSTRINGBUFFER_;

        /*! @fn bool
                greaterThan(const Value & other,
                            bool &        validComparison)
                const
         @brief Return the relative ordering of two Sets.
         @param other The Set to be compared with.
         @param validComparison @c true if the Sets were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Sets. */
        DECLARE_GREATERTHAN_;

        /*! @brief Override the standard insert operation to ignore inserting incompatible values.
         @param val Value to be inserted.
         @returns A pair<iterator, bool> indicating the success or failure of the insert
         operation. */
        insertResult insert(Value * val);

        /*! @fn bool
                lessThan(const Value & other,
                         bool &        validComparison)
                const
         @brief Return the relative ordering of two Sets.
         @param other The Set to be compared with.
         @param validComparison @c true if the Sets were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Sets. */
        DECLARE_LESSTHAN_;

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

        /*! @brief The kind of key being used. */
        Enumerable _keyKind;

    }; // Set

} // nImO

#endif // ! defined(nImOset_HPP_)

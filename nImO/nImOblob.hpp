//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOblob.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO 'blob' values.
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
//  Created:    2016-03-22
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOblob_HPP_))
# define nImOblob_HPP_ /* Header guard */

# include <nImO/nImOvalue.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO 'blob' values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide binary data with unknown structure. */
    class Blob : public Value
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        typedef Value inherited;

    public :
        // Public methods.

        /*! @brief The constructor. */
        Blob(void);

        /*! @brief The constructor.
         @param data The data to be placed in the object.
         @param size The number of bytes in the data. */
        Blob(const uint8_t * data,
             const size_t    size);

        /*! @brief The copy constructor.
         @param other The object to be copied. */
        Blob(const Blob & other);
        
        /*! @brief The destructor. */
        ~Blob(void);

        /*! @fn virtual void
                addToStringBuffer(StringBuffer & outBuffer)
         @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to. */
        DECLARE_ADDTOSTRINGBUFFER_;

#if 0
        /*! @brief Return the value of the object.
         @returns The value of the object. */
        bool getValue(void)
        const
        {
            return _value;
        } // getValue
#endif//0
        
        /*! @fn bool
                greaterThan(const Value & other,
                            bool &        validComparison)
                const
         @brief Return the relative ordering of two Blobs.
         @param other The Blob to be compared with.
         @param validComparison @c true if the Blobs were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Blobs. */
        DECLARE_GREATERTHAN_;

        /*! @fn bool
                lessThan(const Value & other,
                         bool &        validComparison)
                const
         @brief Return the relative ordering of two Blobs.
         @param other The Blob to be compared with.
         @param validComparison @c true if the Blobs were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Blobs. */
        DECLARE_LESSTHAN_;

        /*! @brief The assignment operator.
         @param other The object to be copied.
         @returns The updated object. */
        Blob &
        operator =(const Blob & other);
        
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

        /*! @brief The associated value. */
        uint8_t * _value;

        /*! @brief The size of the associated value. */
        size_t _size;

    }; // Blob

} // nImO

#endif // ! defined(nImOblob_HPP_)

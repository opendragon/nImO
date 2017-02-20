//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstringBuffer.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for a string buffer.
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
//  Created:    2016-03-28
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOstringBuffer_HPP_))
# define nImOstringBuffer_HPP_ /* Header guard */

# include <nImO/nImOchunkArray.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a string buffer. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The data constituting a string buffer. */
    class StringBuffer : public ChunkArray
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        typedef ChunkArray inherited;

    public :
        // Public methods.

        /*! @brief The constructor. */
        StringBuffer(void);

        /*! @brief The destructor. */
        virtual
        ~StringBuffer(void);

        /*! @brief Add a boolean value to the buffer.
         @param[in] aBool The value to add.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addBool(const bool aBool);

        /*! @brief Add a sequence of bytes to the buffer.
         @param[in] inBytes The bytes to be added.
         @param[in] numBytes The number of bytes to add.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addBytes(const uint8_t *inBytes,
                 const size_t  numBytes);

        /*! @brief Add a character to the buffer.
         @param[in] aChar The character to add.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addChar(const char aChar);

        /*! @brief Add a character string representation of a floating-point value to the buffer.
         @param[in] aDouble The value to add.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addDouble(const double aDouble);

        /*! @brief Add a character string representation of an integer value to the buffer.
         @param[in] aLong The value to add.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addLong(const int64_t aLong);

        /*! @brief Add a character string to the buffer.
         @param[in] aString The value to add.
         @param[in] addQuotes @c true if the string is to be delimited by quote characters.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addString(const char *aString,
                  const bool addQuotes = false);

        /*! @brief Add a character string to the buffer.
         @param[in] aString The value to add.
         @param[in] addQuotes @c true if the string is to be delimited by quote characters.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addString(const std::string &aString,
                  const bool        addQuotes = false);

        /*! @brief Add a horizontal tab character to the buffer.
         @returns The StringBuffer object so that cascading can be done. */
        StringBuffer &
        addTab(void);

        /*! @brief Convert the buffer to a Value.
         @returns The Value represented by the buffer contents. */
        SpValue convertToValue(void)
        const;

        /*! @brief Return the character found at a particular index.
         @param[in] index The zero-based location in the buffer.
         @returns The character found at the provided index, or the 'end' character if the index
         is not within the buffer. */
        inline int
        getChar(const size_t index)
        const
        {
            return inherited::getByte(index);
        } // getChar

        /*! @brief Return a copy of the characters in the buffer as well as the number of valid
         characters present.
         @param[in,out] length Set to the number of valid characters in the buffer.
         @returns A pointer to a copy of the characters in the buffer. */
        inline const char *
        getString(size_t &length)
        {
            return reinterpret_cast<const char *>(inherited::getBytes(length));
        } // getString

        friend std::ostream &
        operator <<(std::ostream       &out,
                    const StringBuffer &aBuffer);

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        StringBuffer(const StringBuffer &other) = delete;

        /*! @brief The assignment operator.
         @param[in] other The object to be copied.
         @returns The updated object. */
        StringBuffer &
        operator =(const StringBuffer &other) = delete;

        /*! @brief Add quotes and escapes to a string.
         @param[in] aString The string to be processed.
         @param[in] length The length of the string. */
        void
        processCharacters(const char   *aString,
                          const size_t length);

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

    }; // StringBuffer

    /*! @brief Insert a readable version of the buffer into an
     output stream.
     @param[in,out] out The stream to be added to.
     @param[in] aBuffer The StringBuffer to be printed.
     @returns The modified stream. */
    std::ostream &
    operator <<(std::ostream       &out,
                const StringBuffer &aBuffer);

} // nImO

#endif // ! defined(nImOstringBuffer_HPP_)

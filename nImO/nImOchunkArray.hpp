//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOchunkArray.hpp
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
//  Created:    2016-05-03
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOchunkArray_HPP_))
# define nImOchunkArray_HPP_ /* Header guard */

# include <nImO/nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for an array of chunks. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The data constituting an array of chunks. */
    class ChunkArray
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

    public :
        // Public methods.

        /*! @brief The constructor.
         @param[in] padWithNull @c true if the data needs to be @c NULL-terminated. */
        ChunkArray(const bool padWithNull = false);

        /*! @brief The destructor. */
        virtual
        ~ChunkArray(void);

        /*! @brief Add some bytes to the buffer.
         @param[in] data The bytes to be added.
         @param[in] numBytes The number of bytes to add. */
        void
        appendBytes(const uint8_t *data,
                    const size_t  numBytes);

        /*! @brief Return the byte found at a particular index.
         @param[in] index The zero-based location in the buffer.
         @returns The byte found at the provided index, or the 'end' token if the index is not
         within the buffer. */
        int
        getByte(const size_t index)
        const;

        /*! @brief Return a copy of the bytes in the buffer as well as the number of valid
         bytes present.
         Note that the returned pointer may become invalid at any time, so it should be either
         used immediately or copied.
         @param[out] length Set to the number of valid bytes in the buffer.
         @returns A pointer to a copy of the bytes in the buffer. */
        virtual const uint8_t *
        getBytes(size_t &length);

        /*! @brief Return the number of valid bytes in the buffer.
         @returns The number of valid bytes in the buffer. */
        virtual size_t
        getLength(void)
        const;

        /*! @brief Prepare the buffer for reuse.
         @returns The ChunkArray object so that cascading can be done. */
        virtual ChunkArray &
        reset(void);

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        ChunkArray(const ChunkArray &other);

        /*! @brief The assignment operator.
         @param[in] other The object to be copied.
         @returns The updated object. */
        ChunkArray &
        operator =(const ChunkArray &other);

    public :
        // Public fields.

        /*! @brief The value used to represent the end of the buffer. */
        static const int kEndToken;

    protected :
        // Protected fields.

        /*! @brief The internal buffers used to hold the assembled text. */
        BufferChunk **_buffers;

        /*! @brief The number of buffer chunks being used. */
        size_t _numChunks;

    private :
        // Private fields.

        /*! @brief The cached value of the buffer. */
        uint8_t *_cachedOutput;

        /*! @brief The cached value of the length of the buffer. */
        size_t _cachedLength;

        /*! @brief @c true if the buffers will have an extra byte for @c NULL termination and
         @c false otherwise. */
        bool _buffersArePadded;

        /*! @brief @c true if _cachedOutput just points to the first buffer. */
        bool _cachedIsFirstBuffer;

    }; // ChunkArray

} // nImO

#endif // ! defined(nImOchunkArray_HPP_)

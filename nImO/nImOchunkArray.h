//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOchunkArray.h
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

#if (! defined(nImOchunkArray_H_))
# define nImOchunkArray_H_ /* Header guard */

# include <nImOcommon.h>

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
            @param[in] padWithNull @c true if the data needs to be @c nullptr-terminated. */
            ChunkArray
                (const bool padWithNull = false);

            /*! @brief The copy constructor.
            @param[in] other The object to be copied. */
            ChunkArray
                (const ChunkArray & other) = delete;

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            ChunkArray
                (ChunkArray &&	other)
                noexcept;

            /*! @brief The destructor. */
            virtual
            ~ChunkArray
                (void);

            /*! @brief Add some bytes to the buffer.
            @param[in] data The bytes to be added.
            @param[in] numBytes The number of bytes to add. */
            virtual void
            appendBytes
                (CPtr(uint8_t)  data,
                 const size_t   numBytes);

            /*! @brief Add some bytes to the buffer.
            @param[in] data The bytes to be added.
            @param[in] numBytes The number of bytes to add. */
            inline void
            appendBytes
                (CPtr(DataKind) data,
                 const size_t   numBytes)
            {
                appendBytes(ReinterpretCast(CPtr(uint8_t), data), numBytes);
            }

            /*! @brief Add some bytes to the buffer.
             @param[in] data The bytes to be added.
             @param[in] numBytes The number of bytes to add. */
            inline void
            appendBytes
                (CPtr(char)     data,
                 const size_t   numBytes)
            {
                appendBytes(ReinterpretCast(CPtr(uint8_t), data), numBytes);
            }

            /*! @brief Return @c true if a particular index is past the end of the buffer.
            @param[in] index The zero-based location in the buffer.
            @return @c true if the index is past the end of the buffer. */
            bool
            atEnd
                (const size_t   index)
                const;

            /*! @brief Return the byte found at a particular index.
            @param[in] index The zero-based location in the buffer.
            @param[out] atEnd @c true if the index is past the end of the buffer.
            @return The byte found at the provided index. */
            int
            getByte
                (const size_t   index,
                 bool &         atEnd)
                const;

            /*! @brief Return a copy of the bytes in the buffer.
            @return A copy of the bytes in the buffer. */
            virtual std::string
            getBytes
                (void);

            /*! @brief Return the number of valid bytes in the buffer.
            @return The number of valid bytes in the buffer. */
            virtual size_t
            getLength
                (void)
                const;

            /*! @brief The copy assignment operator.
            @param[in] other The object to be copied.
            @return The updated object. */
            ChunkArray &
            operator =
                (const ChunkArray & other) = delete;

            /*! @brief The move assignment operator.
            @param[in] other The object to be moved.
            @return The updated object. */
            ChunkArray &
            operator =
                (ChunkArray &&  other)
                noexcept;

            /*! @brief Prepare the buffer for reuse.
            @return The ChunkArray object so that cascading can be done. */
            virtual ChunkArray &
            reset
                (void);

        protected :
            // Protected methods.

            /*! @brief Return a chunk.
            @param[in] index The index of a chunk.
            @return The selected chunk. */
            inline BufferChunk *
            getBufferChunk
                (const size_t   index)
                const
            {
                return _buffers[index];
            }

            /*! @brief Return the number of chunks.
            @return The number of chunks. */
            inline size_t
            getNumChunks
                (void)
                const
            {
                return _numChunks;
            }

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The internal buffers used to hold the assembled text. */
            Ptr(Ptr(BufferChunk))   _buffers;

            /*! @brief @c true if the buffers will have an extra byte for @c NULL termination and
            @c false otherwise. */
            bool    _buffersArePadded;

            /*! @brief The cached value of the buffer. */
            std::string _cachedString;

            /*! @brief The number of buffer chunks being used. */
            size_t  _numChunks;

    }; // ChunkArray

} // nImO

#endif // ! defined(nImOchunkArray_H_)

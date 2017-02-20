//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImObufferChunk.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for a chunk of a buffer.
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

#if (! defined(nImObufferChunk_HPP_))
# define nImObufferChunk_HPP_ /* Header guard */

# include <nImO/nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a chunk of a buffer. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The data constituting a chunk of a buffer. */
    class BufferChunk
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
         @param[in] addPadding @c true if a single byte of padding is added to each buffer.
         The padding is to support direct access to a chunk as a @c nullptr-terminated
         string. */
        BufferChunk(const bool addPadding);

        /*! @brief The destructor. */
        virtual
        ~BufferChunk(void);

        /*! @brief Add a sequence of bytes to the chunk.
         @param[in] data The bytes to be added.
         @param[in] numBytes The number of bytes to add.

         Note that if there is insufficient space, the added data will be truncated.
         @returns The BufferChunk object so that cascading can be done. */
        BufferChunk &
        appendData(const void   *data,
                   const size_t numBytes);

        /*! @brief Return the number of available bytes in the chunk.
         @returns The number of available bytes in the chunk. */
        inline size_t
        getAvailableBytes(void)
        const
        {
            return static_cast<size_t>(_bufferEnd - _write);
        } // getAvailableBytes

        /*! @brief Return the stored data.
         @returns A pointer to the stored data. */
        inline const uint8_t *
        getData(void)
        const
        {
            return _buffer.get();
        } // getData

        /*! @brief Return the number of bytes used in the chunk.
         @returns The number of bytes used in the chunk. */
        inline size_t
        getDataSize(void)
        const
        {
            return static_cast<size_t>(_write - _buffer.get());
        } // getDataSize

        /*! @brief Prepare the buffer for reuse.
         @returns The BufferChunk object so that cascading can be done. */
        BufferChunk &
        reset(void);

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        BufferChunk(const BufferChunk &other);

        /*! @brief The assignment operator.
         @param[in] other The object to be copied.
         @returns The updated object. */
        BufferChunk &
        operator =(const BufferChunk &other);

    public :
        // Public fields.

        /*! @brief The size to use for the buffer. */
        static const size_t kBufferSize;

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The internal buffer used to hold the assembled data. */
        nImO::UpAuint8_t _buffer;

        /*! @brief The byte just past the end of the internal buffer. */
        uint8_t *_bufferEnd;

        /*! @brief The next byte to write in the internal buffer. */
        uint8_t *_write;

        /*! @brief @c true if the buffer has an extra byte. */
        bool _padded;

    }; // BufferChunk

} // nImO

#endif // ! defined(nImObufferChunk_HPP_)

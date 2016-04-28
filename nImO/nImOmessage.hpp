//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOmessage.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for a message.
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
//  Created:    2016-04-24
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOmessage_HPP_))
# define nImOmessage_HPP_ /* Header guard */

# include <nImO/nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a message. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    class BufferChunk;
    class Value;

    /*! @brief The data constituting a message. */
    class Message
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
        Message(void);

        /*! @brief The destructor. */
        virtual
        ~Message(void);

        /*! @brief Add some bytes to the buffer.
         @param data The bytes to be added.
         @param numBytes The number of bytes to add. */
        void
        appendBytes(const uint8_t * data,
                    const size_t    numBytes);

        /*! @brief Close the Message, completing its contents.
         @returns The message object so that cascading can be done. */
        Message &
        close(void);

#if 0
        /*! @brief Add a boolean value to the buffer.
         @param aBool The value to add.
         @returns The message object so that cascading can be done. */
        Message &
        addBool(const bool aBool);

        /*! @brief Add a sequence of bytes to the buffer.
         @param inBytes The bytes to be added.
         @param numBytes The number of bytes to add.
         @returns The message object so that cascading can be done. */
        Message &
        addBytes(const uint8_t * inBytes,
                 const size_t    numBytes);

        /*! @brief Add a character string representation of a floating-point value to the buffer.
         @param aDouble The value to add.
         @returns The message object so that cascading can be done. */
        Message &
        addDouble(const double aDouble);

        /*! @brief Add a character string representation of an integer value to the buffer.
         @param aLong The value to add.
         @returns The message object so that cascading can be done. */
        Message &
        addLong(const int64_t aLong);

        /*! @brief Add a character string to the buffer.
         @param aString The value to add.
         @returns The message object so that cascading can be done. */
        Message &
        addString(const char * aString);

        /*! @brief Add a character string to the buffer.
         @param aString The value to add.
         @returns The message object so that cascading can be done. */
        Message &
        addString(const std::string & aString);

        /*! @brief Convert the buffer to a Value.
         @returns The Value represented by the buffer contents. */
        Value * convertToValue(void)
        const;

        /*! @brief Return the character found at a particular index.
         @param index The zero-based location in the buffer.
         @returns The character found at the provided index, or the 'end' character if the index
         is not within the buffer. */
        int
        getByte(const size_t index)
        const;
#endif//0

        /*! @brief Return a copy of the bytes in the buffer as well as the number of valid bytes
         present.
         @param length Set to the number of valid bytes in the buffer.
         @returns A pointer to a copy of the bytes in the buffer. */
        const uint8_t *
        getBytes(size_t & length);

        /*! @brief Return the number of valid characters in the buffer.
         @returns The number of valid characters in the buffer. */
        size_t
        getLength(void)
        const;

        /*! @brief Return @c true if the Message is closed and @c false otherwise.
         @returns @c true if the Message is closed and @c false otherwise. */
        inline bool
        isClosed(void)
        const
        {
            return _closed;
        } // isClosed

        /*! @brief Open the Message, so that data can be added.
         @returns The message object so that cascading can be done. */
        Message &
        open(void);

        /*! @brief Prepare the message for reuse.
         @returns The message object so that cascading can be done. */
        Message &
        reset(void);

        /*! @brief Set the contents of the message.
         @param theValue The value to be put in the message.
         @returns The message object so that cascading can be done. */
        Message &
        setValue(const Value & theValue);

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief The copy constructor.
         @param other The object to be copied. */
        Message(const Message & other);

        /*! @brief The assignment operator.
         @param other The object to be copied.
         @returns The updated object. */
        Message &
        operator =(const Message & other);

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The internal buffers used to hold the assembled text. */
        BufferChunk * * _buffers;

        /*! @brief The cached value of the buffer. */
        uint8_t * _cachedOutput;

        /*! @brief The cached value of the length of the buffer. */
        size_t _cachedLength;
        
        /*! @brief The number of buffer chunks being used. */
        size_t _numChunks;

        /*! @brief @c true if the initial header bytes are present in the buffer. */
        bool _headerAdded;

        /*! @brief @c true if the message has been closed and can be interrogated. */
        bool _closed;

        /*! @brief @c true if _cachedOutput just points to the first buffer. */
        bool _cachedIsFirstBuffer;

    }; // Message

} // nImO

#endif // ! defined(nImOmessage_HPP_)

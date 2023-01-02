//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOmessage.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for a Message.
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

#if (! defined(nImOmessage_H_))
# define nImOmessage_H_ /* Header guard */

# include <nImOchunkArray.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a Message. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The data constituting a Message. */
    class Message final : public ChunkArray
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ChunkArray;

        public :
            // Public methods.

            /*! @brief The constructor. */
            Message
                (void);

            /*! @brief The copy constructor.
            @param[in] other The object to be copied. */
            Message
                (const Message &    other) = delete;

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            Message
                (Message && other)
                noexcept;

            /*! @brief The destructor. */
            virtual
            ~Message
                (void);

            /*! @brief Add some bytes to the buffer.
            @param[in] data The bytes to be added.
            @param[in] numBytes The number of bytes to add. */
            virtual void
            appendBytes
                (CPtr(uint8_t)  data,
                 const size_t   numBytes)
                override;

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

            /*! @brief Close the Message, completing its contents.
            @return The Message object so that cascading can be done. */
            Message &
            close
                (void);

            /*! @brief Return a copy of the bytes in the buffer.
            @return A copy of the bytes in the buffer. */
            virtual std::string
            getBytes
                (void)
                override;

            /*! @brief Return the number of valid bytes in the buffer.
            @return The number of valid bytes in the buffer. */
            virtual size_t
            getLength
                (void)
                const
                override;

            /*! @brief Return the next Value in the Message.
            @param[in] allowClosed @c true if the state can be closed @c false if the Message must be
            opened for reading
            @return The next Value in the Message or @c nullptr if the Value cannot be retrieved or
            a Flaw if the Value is invalid. */
            SpValue
            getValue
                (const bool allowClosed = false);

            /*! @brief Open the Message, so that data can be read or written.
            @param[in] forWriting @c true if the Message is being written to and @c false if it's being
            read.
            @return The Message object so that cascading can be done. */
            Message &
            open
                (const bool forWriting);

            /*! @brief The copy assignment operator.
            @param[in] other The object to be copied.
            @return The updated object. */
            Message &
            operator=
                (const Message &    other) = delete;

            /*! @brief The move assignment operator.
            @param[in] other The object to be moved.
            @return The updated object. */
            Message &
            operator=
                (Message && other)
                noexcept;

            /*! @brief Return @c true if the read position is past the last character.
            @return @c true if the read position is past the last character. */
            inline bool
            readAtEnd
                (void)
                const
            {
                return atEnd(_readPosition);
            }

            /*! @brief Prepare the Message for reuse.
            @return The Message object so that cascading can be done. */
            ChunkArray &
            reset
                (void)
                override;

            /*! @brief Set the contents of the Message.
            @param[in] theValue The value to be put in the Message.
            @return The Message object so that cascading can be done. */
            Message &
            setValue
                (SpValue    theValue);

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

            /*! @brief Mutual-exclusion protection. */
            mutable std::mutex  _lock;

            /*! @brief The cached value of the buffer for transmission. */
            std::string _cachedTransmissionString;

            /*! @brief The position of the next byte being read. */
            size_t  _readPosition;

            /*! @brief The state of the object. */
            MessageState    _state;

            /*! @brief @c true if the initial header bytes are present in the buffer. */
            bool    _headerAdded;

    }; // Message

} // nImO

#endif // ! defined(nImOmessage_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOvector.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO vectors.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2026 by OpenDragon.
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
//  Created:    2026-04-06
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOvector_H_))
# define nImOvector_H_ /* Header guard */

# include <Containers/nImOcontainer.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO vectors. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The standard class on which Vector is based. */
    using VectorBase = std::vector<SpValue>;

    /*! @brief A class to provide collections with vector-like behaviour.

     Note that Vectors 'own' their data and will perform a delete of the
     contained elements on deletion. */
    class Vector final : public Container,
                            public VectorBase
    {

        public :
            // Public type definitions.

            /*! @brief The non-const iterator for Vectors. */
            using iterator = VectorBase::iterator;

            /*! @brief The const iterator for Vectors. */
            using const_iterator = VectorBase::const_iterator;

            /*! @brief The non-const iterator for Vectors. */
            using reverse_iterator = VectorBase::reverse_iterator;

            /*! @brief The const iterator for Vectors. */
            using const_reverse_iterator = VectorBase::const_reverse_iterator;

            /*! @brief The size of indices. */
            using size_type = VectorBase::size_type;

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The first class that this class is derived from. */
            using inherited1 = Container;

            /*! @brief The second class that this class is derived from. */
            using inherited2 = VectorBase;

        public :
            // Public methods.

            /*! @brief The constructor. */
            Vector
                (void);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            Vector
                (const Vector & other);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Vector
                (Vector &&  other)
                noexcept;

            /*! @brief The destructor. */
            ~Vector
                (void)
                override;

            /*! @brief Add the entries from another Vector.
              @param[in] other The object to be copied from. */
            Vector &
            addEntries
                (const Vector & other);

            /*! @brief Add a Value to the end of the Vector.
             @param[in] newElement The Value to be added.
             @return @c true if the Value was added. */
            bool
            addValue
                (SpValue    newElement);

            /*! @brief Add a Value to the end of the Vector.
             @param[in] newElement The Value to be added.
             @return The Container. */
            void
            appendValue
                (SpValue    newElement)
                override;

            /*! @brief Return non-@c nullptr if the object is a Vector.
             @return Non-@c nullptr if the object is a Vector and @c nullptr otherwise. */
            CPtr(Vector)
            asVector
                (void)
                const
                override;

            /*! @brief Returns the element at position index in the Vector.
             @param[in] index The position of the element in the Vector.
             @return The element at the given position, or @c nullptr if the index is out of range. */
            inline SpValue
            at
                (const size_type    index = 0)
                const
            {
                SpValue result;

                if (index < inherited2::size())
                {
                    result = inherited2::at(index);
                }
                else
                {
                    result = nullptr;
                }
                return result;
            }

            /*! @brief Remove all entries from the Vector. */
            void
            clear
                (void)
                override;

            /*! @brief Return @c true if two Values are structurally identical.
             @param[in] other The Value to be compared with.
             @param[in] ignoreCase @c true if case-insensitive comparison.
             @return @c true if the two Values are structurally identical. */
            bool
            deeplyEqualTo
                (const Value &  other,
                 const bool     ignoreCase = false)
                const
                override;

            /*! @brief Write a short description of the Value to a stream.
             @param[in/out] output The stream to write to.
             @return The modified stream. */
            std::ostream &
            describe
                (std::ostream & output)
                const
                override;

            /*! @brief Return @c true if the Vector is empty. */
            bool
            empty
                (void)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            equalTo
                (const Value &  other)
                const
                override;

            /*! @brief Return the kind of data used with the Vector.
             @return The kind of data used with the Vector.*/
            inline BasicType
            getDataKind
                (void)
                const
            {
                return _dataKind;
            }

            /*! @brief Get the extraction information for Vector objects.
             @param[out] aByte The byte value that indicates the start of a Vector value.
             @param[out] aMask The mask to apply to a lead byte.
             @return The function to perform when the lead byte is seen. */
            static Extractor
            getExtractionInfo
                (DataKind & aByte,
                 DataKind & aMask);

            /*! @brief Return the characters that can appear as the start of a Vector.
             @return The characters that can appear as the start of a Vector. */
            static CPtr(char)
            getInitialCharacters
                (void);

            /*! @brief Return the characters that can appear as the end of a Vector.
             @return The characters that can appear as the end of a Vector. */
            static CPtr(char)
            getTerminalCharacters
                (void);

            /*! @brief Return the type tag for the Value for use with Messages.
             @return The type tag for the Value for use with Messages. */
            DataKind
            getTypeTag
                (void)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            greaterThan
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            greaterThanOrEqual
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            lessThan
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            lessThanOrEqual
                (const Value &  other)
                const
                override;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            inline Vector &
            operator=
                (const Vector & other)
            {
                if (this != &other)
                {
                    clear();
                    addEntries(other);
                }
                return *this;
            }

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            Vector &
            operator=
                (Vector &&  other)
                noexcept;

            /*! @brief Add a readable representation of the object to the buffer.
             @param[in,out] outBuffer The buffer to be appended to.
             @param[in] squished @c true if the output has no unnecessary characters and @c false if it
             is as readable as possible. */
            void
            printToStringBuffer
                (StringBuffer & outBuffer,
                 const bool     squished = false)
                const
                override;

            /*! @brief Add a JSON representation of the object to the buffer.
             @param[in,out] outBuffer The buffer to be appended to.
             @param[in] asKey The value is a key.
             @param[in] squished @c true if the output has no unnecessary characters and @c false if it
             is as readable as possible. */
            void
            printToStringBufferAsJSON
                (StringBuffer & outBuffer,
                 const bool     asKey = false,
                 const bool     squished = false)
                const
                override;

            /*! @brief Return a random iterator from the Vector. */
            const_iterator
            random
                (void)
                const;

            /*! @brief Return a random iterator from the Vector. */
            iterator
            random
                (void);

            /*! @brief Convert a readable representation of the object in a buffer into an object.
             @param[in] inBuffer The buffer to be scanned.
             @param[in,out] position Where in the buffer to start.
             @return A new object if there is a valid object in the buffer and @c nullptr otherwise. */
            static SpValue
            readFromStringBuffer // cppcheck-suppress duplInheritedMember
                (const StringBuffer &   inBuffer,
                 size_t &               position);

            /*! @brief Returns the number of elements in the Vector. */
            size_t
            size
                (void)
                const
                override;

            /*! @brief Add a binary representation of the object to the message.
             @param[in] outMessage The Message to be appended to. */
            void
            writeToMessage
                (Message &  outMessage)
                const
                override;

        protected :
            // Protected methods.

            /*! @brief Insert a readable version of the object into an output stream.
             @param[in,out] out The stream to be added to.
             @param[in] aValue The object to be printed.
             @return The modified stream. */
            std::ostream &
            operator<<
                (std::ostream & out)
                const
                override;

        private :
            // Private methods.

            /*! @brief Extracts Value objects from a Message.
             Note that the parentValue argument is normally @c nullptr, and is used for handling
             multiple floating-point numbers in a sequence; if a series of Double values are extracted,
             they are directly added to the Vector and the last Value is returned as the result of the
             function; for all other Value objects, the (single) Value that is extracted is added to
             the Vector to simplify the logic, as well as being returned.
             @param[in] theMessage The Message being processed.
             @param[in] leadByte The initial byte of the Value.
             @param[in,out] position The location of the next byte to be processed.
             @param[in] parentValue A pointer to the Value that will contain the new object.
             @return @c nullptr if the Value could not be extracted because the Message ended before
             the Value did, a Flaw if the Value could not be extracted because it was not correct and
             a non-Flaw Value if extraction was successful. */
            static SpValue
            extractValue
                (const Message &    theMessage,
                 const int          leadByte,
                 size_t &           position,
                 SpValue            parentValue);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The kind of data being stored. */
            BasicType   _dataKind{BasicType::Unknown};

    }; // Vector

} // nImO

#endif // not defined(nImOvector_H_)

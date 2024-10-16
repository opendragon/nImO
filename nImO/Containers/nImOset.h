//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOset.h
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

#if (! defined(nImOset_H_))
# define nImOset_H_ /* Header guard */

# include <Containers/nImOcontainer.h>
# include <nImOcompareValues.h>

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
    /*! @brief The standard class on which Array is based. */
    using SetBase = std::set<SpValue, CompareValues>;

    /*! @brief A class to provide collections with set-like behaviour.

     Note that Sets 'own' their data and will perform a delete of the
     contained elements on deletion. */
    class Set final : public Container,
                      public SetBase
    {

        public :
            // Public type definitions.

            /*! @brief The non-const iterator for Sets. */
            using iterator = SetBase::iterator;

            /*! @brief The const iterator for Sets. */
            using const_iterator = SetBase::const_iterator;

            /*! @brief The non-const iterator for Sets. */
            using reverse_iterator = SetBase::reverse_iterator;

            /*! @brief The const iterator for Sets. */
            using const_revese_iterator = SetBase::const_reverse_iterator;

            /*! @brief The return result from the insert method. */
            using InsertResult = std::pair<SetBase::iterator, bool>;

            /*! @brief The size of indices. */
            using size_type = SetBase::size_type;

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The first class that this class is derived from. */
            using inherited1 = Container;

            /*! @brief The second class that this class is derived from. */
            using inherited2 = SetBase;

        public :
            // Public methods.

            /*! @brief The constructor. */
            Set
                (void);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            Set
                (const Set &    other);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Set
                (Set && other)
                noexcept;

            /*! @brief The destructor. */
            ~Set
                (void)
                override;

            /*! @brief Override the standard insert operation to ignore inserting incompatible values.
             @param[in] val Value to be inserted.
             @return A pair<iterator, bool> indicating the success or failure of the insert
             operation. */
            InsertResult
            addValue
                (SpValue    val);

            /*! @brief Return non-@c nullptr if the object is a Set.
             @return Non-@c nullptr if the object is a Set and @c nullptr otherwise. */
            CPtr(Set)
            asSet
                (void)
                const
                override;

            /*! @brief Remove all entries from the Set. */
            void
            clear
                (void)
                override;

            /*! @brief Return @c true if two Values are structurally identical.
             @param[in] other The Value to be compared with.
             @return @c true if the two Values are structurally identical. */
            bool
            deeplyEqualTo
                (const Value &  other)
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

            /*! @brief Return @c true if the Set is empty. */
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

            /*! @brief Search the Set for an element with the given key value and return an iterator
             to it, or Set::end if not found.
             @param[in] key The key to be searched for.
             @return An iterator for the given key key value or Set::end if not found. */
            iterator
            find
                (SpValue    key)
            {
                iterator    result;

                if (key->enumerationType() == _keyKind)
                {
                    result = inherited2::find(key);
                }
                else
                {
                    result = inherited2::end();
                }
                return result;
            } // find

            /*! @brief Search the Set for an element with the given key value and return an iterator
             to it, or Set::end if not found.
             @param[in] key The key to be searched for.
             @return An iterator for the given key key value or Set::end if not found. */
            const_iterator
            find
                (SpValue    key)
                const
            {
                const_iterator  result;

                if (key->enumerationType() == _keyKind)
                {
                    result = inherited2::find(key);
                }
                else
                {
                    result = inherited2::end();
                }
                return result;
            } // find

            /*! @brief Get the extraction information for Set objects.
             @param[out] aByte The byte value that indicates the start of a Set value.
             @param[out] aMask The mask to apply to a lead byte.
             @return The function to perform when the lead byte is seen. */
            static Extractor
            getExtractionInfo
                (DataKind & aByte,
                 DataKind & aMask);

            /*! @brief Return the characters that can appear as the start of a Set.
             @return The characters that can appear as the start of a Set. */
            static CPtr(char)
            getInitialCharacters
                (void);

            /*! @brief Return the kind of key used with the Set.
             @return The kind of key used with the Set.*/
            inline Enumerable
            getKeyKind
                (void)
                const
            {
                return _keyKind;
            }

            /*! @brief Return the characters that can appear as the end of a Set.
             @return The characters that can appear as the end of a Set. */
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
            Set &
            operator=
                (const Set &    other)
            {
                if (this != &other)
                {
                    clear();
                    addEntries(other);
                }
                return *this;
            } // operator=

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            Set &
            operator=
                (Set && other)
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

            /*! @brief Return a random iterator from the Set. */
            const_iterator
            random
                (void)
                const;

            /*! @brief Return a random iterator from the Set. */
            iterator
            random
                (void);

            /*! @brief Convert a readable representation of the object in a buffer into an object.
             @param[in] inBuffer The buffer to be scanned.
             @param[in,out] position Where in the buffer to start.
             @return A new object if there is a valid object in the buffer and @c nullptr otherwise. */
            static SpValue
            readFromStringBuffer
                (const StringBuffer &   inBuffer,
                 size_t &               position);

            /*! @brief Returns the number of elements in the Set. */
            size_t
            size
                (void)
                const
                override;

            /*! @brief Add a binary representation of the object to the message.
             @param[in,out] outMessage The Message to be appended to. */
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

            /*! @brief Add the entries from another Set.
             @param[in] other The object to be copied from. */
            void
            addEntries
                (const Set &    other);

            /*! @brief Extracts Value objects from a Message.
             Note that the parentValue argument is normally @c nullptr, and is used for handling
             multiple floating-point numbers in a sequence; if a series of Double values are extracted,
             they are directly added to the Array and the last Value is returned as the result of the
             function; for all other Value objects, the (single) Value that is extracted is added to
             the Array to simplify the logic, as well as being returned.
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
                 SpArray            parentValue);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The kind of key being used. */
            Enumerable  _keyKind{Enumerable::Unknown};

    }; // Set

} // nImO

#endif // not defined(nImOset_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOmap.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO maps.
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

#if (! defined(nImOmap_H_))
# define nImOmap_H_ /* Header guard */

# include <nImOcompareValues.h>
# include <nImOcontainer.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO maps. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The standard class on which Array is based. */
    using MapBase = std::map<SpValue, SpValue, CompareValues>;

    /*! @brief A class to provide collections with hashtable-like behaviour.

     Note that Maps 'own' their data and will perform a delete of the
     contained elements and their keys on deletion. */
    class Map final : public Container,
                      public MapBase
    {

        public :
            // Public type definitions.

            /*! @brief The non-const iterator for Maps. */
            using iterator = MapBase::iterator;

            /*! @brief The const iterator for Maps. */
            using const_iterator = MapBase::const_iterator;

            /*! @brief The non-const iterator for Maps. */
            using reverse_iterator = MapBase::reverse_iterator;

            /*! @brief The const iterator for Maps. */
            using const_reverse_iterator = MapBase::const_reverse_iterator;

            /*! @brief The return result from the insert method. */
            using InsertResult = std::pair<MapBase::iterator, bool>;

            /*! @brief The size of indices. */
            using size_type = MapBase::size_type;

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The first class that this class is derived from. */
            using inherited1 = Container;

            /*! @brief The second class that this class is derived from. */
            using inherited2 = MapBase;

            /*! @brief The type of value to be inserted. */
            using MapValue = MapBase::value_type;

        public :
            // Public methods.

            /*! @brief The constructor. */
            Map
                (void);

            /*! @brief The copy constructor.
            @param[in] other The object to be copied. */
            Map
                (const Map &    other);

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            Map
                (Map && other)
                noexcept;

            /*! @brief The destructor. */
            virtual
            ~Map
                (void);

            /*! @brief Override the standard insert operation to ignore inserting incompatible values.
            @param[in] newKey The key for the Value.
            @param[in] newValue The Value to be inserted.
            @return A pair<iterator, bool> indicating the success or failure of the insert
            operation. */
            InsertResult
            addValue
                (SpValue    newKey,
                 SpValue    newValue);

            /*! @brief Return non-@c nullptr if the object is a Map.
            @return Non-@c nullptr if the object is a Map and @c nullptr otherwise. */
            virtual CPtr(Map)
            asMap
                (void)
                const
                override;

            /*! @brief Remove all entries from the Map. */
            virtual void
            clear
                (void)
                override;

            /*! @brief Return @c true if two Values are structurally identical.
            @param[in] other The Value to be compared with.
            @return @c true if the two Values are structurally identical. */
            virtual bool
            deeplyEqualTo
                (const Value &  other)
                const
                override;

            /*! @brief Return @c true if the Map is empty. */
            virtual bool
            empty
                (void)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
            @param[in] other The Value to be compared with.
            @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            equalTo
                (const Value &  other)
                const
                override;

            /*! @brief Search the Map for an element with the given key value and return an iterator
            to it, or Map::end if not found.
            @param[in] key The key to be searched for.
            @return An iterator for the given key key value or Map::end if not found. */
            inline iterator
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
            }


            /*! @brief Search the Map for an element with the given key value and return an iterator
            to it, or Map::end if not found.
            @param[in] key The key to be searched for.
            @return An iterator for the given key key value or Map::end if not found. */
            inline const_iterator
            find
                (const SpValue  key)
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
            }

            /*! @brief Get the extraction information for Map objects.
            @param[out] aByte The byte value that indicates the start of a Map value.
            @param[out] aMask The mask to apply to a lead byte.
            @param[out] theExtractor The function to perform when the lead byte is seen. */
            static void
            getExtractionInfo
                (DataKind &     aByte,
                 DataKind &     aMask,
                 Extractor &    theExtractor);

            /*! @brief Return the characters that can appear as the start of a Map.
            @return The characters that can appear as the start of a Map. */
            static CPtr(char)
            getInitialCharacters
                (void);

            /*! @brief Return the characters that can appear as the end of a Map.
            @return The characters that can appear as the end of a Map. */
            static CPtr(char)
            getTerminalCharacters
                (void);

            /*! @brief Return the type tag for the Value for use with Messages.
            @return The type tag for the Value for use with Messages. */
            virtual DataKind
            getTypeTag
                (void)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
            @param[in] other The Value to be compared with.
            @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            greaterThan
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
            @param[in] other The Value to be compared with.
            @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            greaterThanOrEqual
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
            @param[in] other The Value to be compared with.
            @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            lessThan
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
            @param[in] other The Value to be compared with.
            @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            lessThanOrEqual
                (const Value &  other)
                const
                override;

            /*! @brief The copy assignment operator.
            @param[in] other The object to be copied.
            @return The updated object. */
            inline Map &
            operator=
                (const Map &    other)
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
            Map &
            operator=
                (Map && other)
                noexcept;

            /*! @brief Add a readable representation of the object to the buffer.
            @param[in,out] outBuffer The buffer to be appended to.
            @param[in] squished @c true if the output has no unnecessary characters and @c false if it
            is as readable as possible. */
            virtual void
            printToStringBuffer
                (StringBuffer & outBuffer,
                 const bool     squished = false)
                const
                override;

            /*! @brief Return a random iterator from the Map. */
            const_iterator
            random
                (void)
                const;

            /*! @brief Return a random iterator from the Map. */
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

            /*! @brief Returns the number of elements in the Map. */
            virtual size_t
            size
                (void)
                const
                override;

            /*! @brief Add a binary representation of the object to the message.
            @param[in,out] outMessage The Message to be appended to. */
            virtual void
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
            virtual std::ostream &
            operator<<
                (std::ostream & out)
                const
                override;

        private :
            // Private methods.

            /*! @brief Add the entries from another Map.
            @param[in] other The object to be copied from. */
            void
            addEntries
                (const Map &    other);

            /*! @brief Extracts Value objects from a Message.
            Note that the parentValue argument is normally @c nullptr, and is used for handling
            multiple floating-point numbers in a sequence; if a series of Double values are
            extracted, they are directly added to the Array and the last Value is returned as
            the result of the function; for all other Value objects, the (single) Value that is
            extracted is added to the Array to simplify the logic, as well as being returned.
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
            Enumerable  _keyKind;

    }; // Map

} // nImO

#endif // not defined(nImOmap_H_)

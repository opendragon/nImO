//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOset.hpp
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

#if (! defined(nImOset_HPP_))
# define nImOset_HPP_ /* Header guard */

# include <nImOcompareValues.hpp>
# include <nImOcontainer.hpp>

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
    class Set : public Container,
                private SetBase
    {
    public :
        // Public type definitions.

        /*! @brief The non-const iterator for Arrays. */
        using iterator = SetBase::iterator;

        /*! @brief The const iterator for Arrays. */
        using const_iterator = SetBase::const_iterator;

        /*! @brief The non-const iterator for Arrays. */
        using reverse_iterator = SetBase::reverse_iterator;

        /*! @brief The const iterator for Arrays. */
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

        /*! @brief The destructor. */
        virtual
        ~Set
            (void);

        /*! @brief Override the standard insert operation to ignore inserting incompatible values.
         @param[in] val Value to be inserted.
         @returns A pair<iterator, bool> indicating the success or failure of the insert
         operation. */
        InsertResult
        addValue
            (SpValue    val);

        /*! @brief Return non-@c nullptr if the object is a Set.
         @returns Non-@c nullptr if the object is a Set and @c nullptr otherwise. */
        virtual const Set *
        asSet
            (void)
            const
            override;

        /*! @brief Return an iterator pointing to the first element of the Array.
         @returns An iterator pointing to the first element of the Array. */
        inline iterator
        begin
            (void)
        {
            return inherited2::begin();
        } // begin

        /*! @brief Return an iterator pointing to the first element of the Array.
         @returns An iterator pointing to the first element of the Array. */
        inline const_iterator
        begin
            (void)
            const
        {
            return inherited2::begin();
        } // begin

        /*! @brief Remove all entries from the Set. */
        inline void
        clear
            (void)
        {
            inherited2::clear();
            _keyKind = Enumerable::Unknown;
        } // clear

        /*! @brief Return @c true if two Values are structurally identical.
         @param[in] other The Value to be compared with.
         @returns @c true if the two Values are structurally identical. */
        virtual bool
        deeplyEqualTo
            (const Value &  other)
            const
            override;

        /*! @brief Return an iterator pointing past the last element of the Array.
         @returns An iterator pointing past the last element of the Array. */
        inline iterator
        end
            (void)
        {
            return inherited2::end();
        } // end

        /*! @brief Return an iterator pointing past the last element of the Array.
         @returns An iterator pointing past the last element of the Array. */
        inline const_iterator
        end
            (void)
            const
        {
            return inherited2::end();
        } // end

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        equalTo
            (const Value &  other,
             bool &         validComparison)
            const
            override;

        /*! @brief Search the Map for an element with the given key value an return an iterator
         to it, or Map::end if not found.
         @param[in] key The key to be searched for.
         @returns An iterator for the given key key value or Map::end if not found. */
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

        /*! @brief Search the Map for an element with the given key value an return an iterator
         to it, or Map::end if not found.
         @param[in] key The key to be searched for.
         @returns An iterator for the given key key value or Map::end if not found. */
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
         @param[out] theExtractor The function to perform when the lead byte is seen. */
        static void
        getExtractionInfo
            (DataKind &     aByte,
             DataKind &     aMask,
             Extractor &    theExtractor);

        /*! @brief Return the characters that can appear as the start of a Set.
         @returns The characters that can appear as the start of a Set. */
        static const char *
        getInitialCharacters
            (void);

        /*! @brief Return the characters that can appear as the end of a Set.
         @returns The characters that can appear as the end of a Set. */
        static const char *
        getTerminalCharacters
            (void);

        /*! @brief Return the type tag for the Value for use with Messages.
         @returns The type tag for the Value for use with Messages. */
        virtual DataKind
        getTypeTag
            (void)
            const
            override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        greaterThan
            (const Value &  other,
             bool &         validComparison)
            const
            override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        greaterThanOrEqual
            (const Value &  other,
             bool &         validComparison)
            const
            override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        lessThan
            (const Value &  other,
             bool &         validComparison)
            const
            override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        lessThanOrEqual
            (const Value &  other,
             bool &         validComparison)
            const
            override;

        /*! @brief The assignment operator.
         @param[in] other The object to be copied.
         @returns The updated object. */
        Set &
        operator =
            (const Set &    other)
        {
            if (this != &other)
            {
                clear();
                addEntries(other);
            }
            return *this;
        } // operator =

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

        /*! @brief Convert a readable representation of the object in a buffer into an object.
         @param[in] inBuffer The buffer to be scanned.
         @param[in,out] position Where in the buffer to start.
         @returns A new object if there is a valid object in the buffer and @c nullptr otherwise. */
        static SpValue
        readFromStringBuffer
            (const StringBuffer &   inBuffer,
             size_t &               position);

        /*! @brief Returns the number of elements in the Set.
         @returns The number of elements in the Set. */
        inline size_type
        size
            (void)
            const
        {
            return inherited2::size();
        } // size

        /*! @brief Add a binary representation of the object to the message.
         @param[in,out] outMessage The Message to be appended to. */
        virtual void
        writeToMessage
            (Message &  outMessage)
            const
            override;

    protected :
        // Protected methods.

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
         @returns @c nullptr if the Value could not be extracted because the Message ended before
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

    }; // Set

} // nImO

#endif // ! defined(nImOset_HPP_)

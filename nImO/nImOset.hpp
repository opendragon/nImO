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

# include <nImO/nImOcompareValues.hpp>
# include <nImO/nImOcontainer.hpp>

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
    typedef std::set<Value *, CompareValues> SetBase;

    /*! @brief A class to provide collections with set-like behaviour.

     Note that Sets 'own' their data and will perform a delete of the
     contained elements on deletion. */
    class Set : public Container,
                private SetBase
    {
    public :
        // Public type definitions.

        /*! @brief The non-const iterator for Arrays. */
        typedef SetBase::iterator iterator;

        /*! @brief The const iterator for Arrays. */
        typedef SetBase::const_iterator const_iterator;

        /*! @brief The non-const iterator for Arrays. */
        typedef SetBase::reverse_iterator reverse_iterator;

        /*! @brief The const iterator for Arrays. */
        typedef SetBase::const_reverse_iterator const_reverse_iterator;

        /*! @brief The return result from the insert method. */
        typedef std::pair<SetBase::iterator, bool> InsertResult;

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The first class that this class is derived from. */
        typedef Container inherited1;

        /*! @brief The second class that this class is derived from. */
        typedef SetBase inherited2;

    public :
        // Public methods.

        /*! @brief The constructor. */
        Set(void);

        /*! @brief The copy constructor.
         @param other The object to be copied. */
        Set(const Set & other);

        /*! @brief The destructor. */
        ~Set(void);

        /*! @brief Override the standard insert operation to ignore inserting incompatible values.
         @param val Value to be inserted.
         @returns A pair<iterator, bool> indicating the success or failure of the insert
         operation. */
        InsertResult
        addValue(Value * val);

        /*! @brief Return an iterator pointing to the first element of the Array.
         @returns An iterator pointing to the first element of the Array. */
        inline iterator
        begin(void)
        {
            return inherited2::begin();
        } // begin

        /*! @brief Return an iterator pointing to the first element of the Array.
         @returns An iterator pointing to the first element of the Array. */
        inline const_iterator
        begin(void)
        const
        {
            return inherited2::begin();
        } // begin

        /*! @brief Remove all entries from the Set. */
        void
        clear(void);

        /*! @brief Return a copy of the object.
         @returns Returns a copy of the object. */
        virtual Value *
        clone(void)
        const;

        /*! @brief Return an iterator pointing past the last element of the Array.
         @returns An iterator pointing past the last element of the Array. */
        inline iterator
        end(void)
        {
            return inherited2::end();
        } // end

        /*! @brief Return an iterator pointing past the last element of the Array.
         @returns An iterator pointing past the last element of the Array. */
        inline const_iterator
        end(void)
        const
        {
            return inherited2::end();
        } // end

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        equalTo(const Value & other,
                bool &        validComparison)
        const;

        /*! @brief Search the Map for an element with the given key value an return an iterator
         to it, or Map::end if not found.
         @param key The key to be searched for.
         @returns An iterator for the given key key value or Map::end if not found. */
        iterator
        find(const Value & key);

        /*! @brief Search the Map for an element with the given key value an return an iterator
         to it, or Map::end if not found.
         @param key The key to be searched for.
         @returns An iterator for the given key key value or Map::end if not found. */
        const_iterator
        find(const Value & key)
        const;

        /*! @brief Return the characters that can appear as the start of a Set.
         @returns The characters that can appear as the start of a Set. */
        static const char *
        getInitialCharacters(void);

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        greaterThan(const Value & other,
                    bool &        validComparison)
        const;

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        greaterThanOrEqual(const Value & other,
                           bool &        validComparison)
        const;

        /*! @brief Return @c true if the object is a Set.
         @returns @c true if the object is a Set and @c false otherwise. */
        virtual inline bool
        isSet(void)
        const
        {
            return true;
        } // isSet

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        lessThan(const Value & other,
                 bool &        validComparison)
        const;

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        lessThanOrEqual(const Value & other,
                        bool &        validComparison)
        const;

        /*! @brief The assignment operator.
         @param other The object to be copied.
         @returns The updated object. */
        Set &
        operator =(const Set & other);

        /*! @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to. */
        virtual void
        printToStringBuffer(StringBuffer & outBuffer)
        const;
        
        /*! @brief Convert a readable representation of the object in a buffer into an object.
         @param inBuffer The buffer to be scanned.
         @param fromIndex Where in the buffer to start.
         @param termChars The expected termination characters - @c NULL is anything is legal.
         @param updatedIndex The next location in the buffer to be processed.
         @returns A new object if there is a valid object in the buffer and @c NULL otherwise. */       
        static Value *
        readFromStringBuffer(const StringBuffer & inBuffer,
                             const size_t         fromIndex = 0,
                             const char *         termChars = NULL,
                             size_t *             updatedIndex = NULL);
 
        /*! @brief Returns the number of elements in the Set.
         @returns The number of elements in the Set. */
        inline size_t
        size(void)
        const
        {
            return inherited2::size();
        } // size

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Add the entries from another Set.
          @param other The object to be copied from. */
        void
        addEntries(const Set & other);

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The kind of key being used. */
        Enumerable _keyKind;

    }; // Set

} // nImO

#endif // ! defined(nImOset_HPP_)
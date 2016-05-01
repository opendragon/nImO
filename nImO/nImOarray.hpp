//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOarray.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO arrays.
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

#if (! defined(nImOarray_HPP_))
# define nImOarray_HPP_ /* Header guard */

# include <nImO/nImOcontainer.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO arrays. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The standard class on which Array is based. */
    typedef std::vector<Value *> ArrayBase;

    /*! @brief A class to provide collections with array-like behaviour.

     Note that Arrays 'own' their data and will perform a delete of the
     contained elements on deletion. */
    class Array : public Container,
                  private ArrayBase
    {
    public :
        // Public type definitions.

        /*! @brief The non-const iterator for Arrays. */
        typedef ArrayBase::iterator iterator;

        /*! @brief The const iterator for Arrays. */
        typedef ArrayBase::const_iterator const_iterator;

        /*! @brief The non-const iterator for Arrays. */
        typedef ArrayBase::reverse_iterator reverse_iterator;

        /*! @brief The const iterator for Arrays. */
        typedef ArrayBase::const_reverse_iterator const_reverse_iterator;

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The first class that this class is derived from. */
        typedef Container inherited1;

        /*! @brief The second class that this class is derived from. */
        typedef ArrayBase inherited2;

    public :
        // Public methods.

        /*! @brief The constructor. */
        Array(void);

        /*! @brief The copy constructor.
         @param other The object to be copied. */
        Array(const Array & other);

        /*! @brief The destructor. */
        virtual
        ~Array(void);

        /*! @brief Add a Value to the end of the Array.
         @param newElement The Value to be added.
         @returns The updated Array. */
        Array &
        addValue(Value * newElement);

        /*! @brief Returns the element at position index in the Array.
         @param index The position of the element in the Array.
         @returns The element at the given position, or @c NULL if the index is out of range. */
        Value *
        at(const size_t index)
        const;

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

        /*! @brief Remove all entries from the Array. */
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

        /*! @brief Return a reverse iterator pointing to the first element of the Array.
         @returns A reverse iterator pointing to the first element of the Array. */
        inline const_reverse_iterator
        rbegin(void)
        const
        {
            return inherited2::rbegin();
        } // rbegin
        
        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        equalTo(const Value & other,
                bool &        validComparison)
        const;

        /*! @brief Return the characters that can appear as the start of an Array.
         @returns The characters that can appear as the start of an Array. */
        static const char *
        getInitialCharacters(void);

        /*! @brief Return the characters that can appear as the end of an Array.
         @returns The characters that can appear as the end of an Array. */
        static const char *
        getTerminalCharacters(void);

        /*! @brief Return the type tag for the Value for use with Messages.
         @returns The type tag for the Value for use with Messages. */
        virtual inline uint8_t
        getTypeTag(void)
        const
        {
            return kKindOtherMessageExpectedOtherValue;
        } // getTypeTag

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

        /*! @brief Return @c true if the object is an Array.
         @returns @c true if the object is an Array and @c false otherwise. */
        virtual inline bool
        isArray(void)
        const
        {
            return true;
        } // isArray

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
        Array &
        operator =(const Array & other);

        /*! @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to.
         @param squished @c true if the output has no unnecessary characters and @c false if it
         is as readable as possible. */
        virtual void
        printToStringBuffer(StringBuffer & outBuffer,
                            const bool     squished = false)
        const;

        /*! @brief Convert a readable representation of the object in a buffer into an object.
         @param inBuffer The buffer to be scanned.
         @param position Where in the buffer to start.
         @returns A new object if there is a valid object in the buffer and @c NULL otherwise. */
        static Value *
        readFromStringBuffer(const StringBuffer & inBuffer,
                             size_t &             position);

        /*! @brief Return a reverse iterator pointing to the first element of the Array.
         @returns A reverse iterator pointing to the first element of the Array. */
        inline reverse_iterator
        rbegin(void)
        {
            return inherited2::rbegin();
        } // rbegin

        /*! @brief Return a reverse iterator pointing past the first element of the Array.
         @returns A reverse iterator pointing past the first element of the Array. */
        inline reverse_iterator
        rend(void)
        {
            return inherited2::rend();
        } // rend

        /*! @brief Return a reverse iterator pointing past the first element of the Array.
         @returns A reverse iterator pointing past the first element of the Array. */
        inline const_reverse_iterator
        rend(void)
        const
        {
            return inherited2::rend();
        } // rend

        /*! @brief Returns the number of elements in the Array.
         @returns The number of elements in the Array. */
        inline size_t
        size(void)
        const
        {
            return inherited2::size();
        } // size

        /*! @brief Add a binary representation of the object to the message.
         @param outMessage The Message to be appended to. */
        virtual void
        writeToMessage(Message & outMessage)
        const;

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Add the entries from another Array.
          @param other The object to be copied from. */
        void
        addEntries(const Array & other);

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

    }; // Array

} // nImO

#endif // ! defined(nImOarray_HPP_)

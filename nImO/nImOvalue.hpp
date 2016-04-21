//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOvalue.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO general values.
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

#if (! defined(nImOvalue_HPP_))
# define nImOvalue_HPP_ /* Header guard */

# include <nImO/nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO general values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    class StringBuffer;

    /*! @brief A class to provide general value behaviours. */
    class Value
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.
       
    private :
        // Private type definitions.
        
        /*! @brief The function pointer for StringBuffer readers. */ 
        typedef Value * (*BufferReader)
            (const StringBuffer & inBuffer,
             const size_t         fromIndex,
             const char *         termChars,
             size_t *             updatedIndex);

        /*! @brief The map from characters to BufferReaders. */
        typedef std::map<char, BufferReader> BufferReaderMap;

        /*! @brief The non-const iterator for BufferReaderMaps. */
        typedef BufferReaderMap::iterator BufferReaderIterator;
        
        /*! @brief The return result from the insert method. */
        typedef std::pair<BufferReaderMap::iterator, bool> BufferReaderInsertResult;

        /*! @brief The type of value to be inserted. */
        typedef BufferReaderMap::value_type BufferReaderValue;

    public :
        // Public methods.

        /*! @brief The destructor. */
        ~Value(void);

        /*! @brief Return a copy of the object.
         @returns Returns a copy of the object. */
        virtual inline Value *
        clone(void)
        const
        {
            return NULL;
        } // copy

        /*! @brief Return the enumeraton type of an object.
         @returns The enumeration type of an object. */
        virtual inline Enumerable
        enumerationType(void)
        const
        {
            return kEnumerableNotEnumerable;
        } // enumerationType

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        equalTo(const Value & other,
                bool &        validComparison)
        const
        {
            validComparison = (&other == this);
            return (&other == this);
        } // equalTo

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        greaterThan(const Value & other,
                    bool &        validComparison)
        const
        {
            validComparison = false;
            return false;
        } // greaterThan

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        greaterThanOrEqual(const Value & other,
                           bool &        validComparison)
        const
        {
            validComparison = (&other == this);
            return (&other == this);
        } // greaterThanOrEqual

        /*! @brief Set up the global structures used. */
        static void
        initialize(void);

        /*! @brief Return @c true if the object is an Array.
         @returns @c true if the object is an Array and @c false otherwise. */
        virtual inline bool
        isArray(void)
        const
        {
            return false;
        } // isArray

        /*! @brief Return @c true if the object is a Blob.
         @returns @c true if the object is a Blob and @c false otherwise. */
        virtual inline bool
        isBlob(void)
        const
        {
            return false;
        } // isBlob

        /*! @brief Return @c true if the object is a Boolean.
         @returns @c true if the object is a Boolean and @c false otherwise. */
        virtual inline bool
        isBoolean(void)
        const
        {
            return false;
        } // isBoolean

        /*! @brief Return @c true if the object is a Container.
         @returns @c true if the object is a Container and @c false otherwise. */
        virtual inline bool
        isContainer(void)
        const
        {
            return false;
        } // isContainer

        /*! @brief Return @c true if the object is a Map.
         @returns @c true if the object is a Map and @c false otherwise. */
        virtual inline bool
        isMap(void)
        const
        {
            return false;
        } // isMap

        /*! @brief Return @c true if the object is a Number.
         @returns @c true if the object is a Number and @c false otherwise. */
        virtual inline bool
        isNumber(void)
        const
        {
            return false;
        } // isNumber

        /*! @brief Return @c true if the object is a Set.
         @returns @c true if the object is a Set and @c false otherwise. */
        virtual inline bool
        isSet(void)
        const
        {
            return false;
        } // isSet

        /*! @brief Return @c true if the object is a String.
         @returns @c true if the object is a String and @c false otherwise. */
        virtual inline bool
        isString(void)
        const
        {
            return false;
        } // isString

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        lessThan(const Value & other,
                 bool &        validComparison)
        const
        {
            validComparison = false;
            return false;
        } // lessThan

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        lessThanOrEqual(const Value & other,
                        bool &        validComparison)
        const
        {
            validComparison = (&other == this);
            return (&other == this);
        } // lessThanOrEqual

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator <(const Value & other)
        {
            bool valid = false;
            bool result = lessThan(other, valid);

            return (valid && result);
        } // operator <

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator >(const Value & other)
        {
            bool valid = false;
            bool result = greaterThan(other, valid);

            return (valid && result);
        } // operator >

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator <=(const Value & other)
        {
            bool valid = false;
            bool result = lessThanOrEqual(other, valid);

            return (valid && result);
        } // operator <=

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator >=(const Value & other)
        {
            bool valid = false;
            bool result = greaterThanOrEqual(other, valid);

            return (valid && result);
        } // operator >=

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator ==(const Value & other)
        {
            bool valid = false;
            bool result = equalTo(other, valid);

            return (valid && result);
        } // operator ==

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator !=(const Value & other)
        {
            bool valid = false;
            bool result = ! equalTo(other, valid);

            return (valid && result);
        } // operator !=

        /*! @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to. */
        virtual inline void
        printToStringBuffer(StringBuffer & outBuffer)
        const
        {
        } // printToStringBuffer
        
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
 
    protected :
        // Protected methods.

        /*! @brief The constructor. */
        Value(void);

    private :
        // Private methods.

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The table of StringBuffer readers. */
        static BufferReaderMap gReaders;

    }; // Value

} // nImO

#endif // ! defined(nImOvalue_HPP_)

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
    // Forward declarations.

    class Blob;
    class Boolean;
    class Container;
    class Double;
    class Integer;
    class Number;
    class String;

    /*! @brief A class to provide general value behaviours. */
    class Value
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

        /*! @brief A pointer to a function that extracts Value objects from a Message.
         Note that the parentValue argument is normally @c NULL, and is used for handling multiple
         floating-point numbers in a sequence; if a series of Double values are extracted, they are
         directly added to the Array and the last Value is returned as the result of the function;
         for all other Value objects, the (single) Value that is extracted is added to the Array to
         simplify the logic, as well as being returned.
         @param[in] theMessage The Message being processed.
         @param[in] leadByte The initial byte of the Value.
         @param[in,out] position The location of the next byte to be processed.
         @param[out] status Whether the extraction was successful.
         @param[in] parentValue A pointer to the Value that will contain the new object.
         @returns @c NULL if there is a problem with the extraction and non-@c NULL if
         a Value was found and processed. */
        typedef Value *
           (* Extractor)
               (const Message &theMessage,
                const int     leadByte,
                size_t        &position,
                ReadStatus    &status,
                Array         *parentValue);

    private :
        // Private type definitions.

        /*! @brief The function pointer for StringBuffer readers.
         @param[in] inBuffer TBD
         @param[in,out] position TBD
         @returns TBD */
        typedef Value *
            (* BufferReader)
                (const StringBuffer &inBuffer,
                 size_t             &position);

        /*! @brief The map from characters to BufferReaders. */
        typedef std::map<char, BufferReader> BufferReaderMap;

        /*! @brief The non-const iterator for BufferReaderMaps. */
        typedef BufferReaderMap::iterator BufferReaderIterator;

        /*! @brief The return result from the insert method. */
        typedef std::pair<BufferReaderMap::iterator, bool> BufferReaderInsertResult;

        /*! @brief The type of value to be inserted. */
        typedef BufferReaderMap::value_type BufferReaderValue;

        /*! @brief The map from bytes to Extractors. */
        typedef std::map<uint8_t, Extractor> ExtractorMap;

        /*! @brief The non-const iterator for ExtractorMaps. */
        typedef ExtractorMap::iterator ExtractorMapIterator;

    public :
        // Public methods.

        /*! @brief The destructor. */
        virtual
        ~Value(void);

        /*! @brief Return non-@c NULL if the object is an Array.
         @returns Non-@c NULL if the object is an Array and @c NULL otherwise. */
        virtual inline const Array *
        asArray(void)
        const
        {
            return NULL;
        } // asArray
        
        /*! @brief Return non-@c NULL if the object is a Blob.
         @returns Non-@c NULL if the object is a Blob and @c NULL otherwise. */
        virtual inline const Blob *
        asBlob(void)
        const
        {
            return NULL;
        } // asBlob
        
        /*! @brief Return non-@c NULL if the object is a Boolean.
         @returns Non-@c NULL if the object is a Boolean and @c NULL otherwise. */
        virtual inline const Boolean *
        asBoolean(void)
        const
        {
            return NULL;
        } // asBoolean
        
        /*! @brief Return non-@c NULL if the object is a Container.
         @returns Non-@c NULL if the object is a Container and @c NULL otherwise. */
        virtual inline const Container *
        asContainer(void)
        const
        {
            return NULL;
        } // asContainer
        
        /*! @brief Return non-@c NULL if the object is a Double.
         @returns Non-@c NULL if the object is a Double and @c NULL otherwise. */
        virtual inline const Double *
        asDouble(void)
        const
        {
            return NULL;
        } // asDouble
        
        /*! @brief Return non-@c NULL if the object is an Integer.
         @returns Non-@c NULL if the object is an Integer and @c NULL otherwise. */
        virtual inline const Integer *
        asInteger(void)
        const
        {
            return NULL;
        } // asInteger
        
        /*! @brief Return non-@c NULL if the object is a Map.
         @returns Non-@c NULL if the object is a Map and @c NULL otherwise. */
        virtual inline const Map *
        asMap(void)
        const
        {
            return NULL;
        } // asMap
        
        /*! @brief Return non-@c NULL if the object is a Number.
         @returns Non-@c NULL if the object is a Number and @c NULL otherwise. */
        virtual inline const Number *
        asNumber(void)
        const
        {
            return NULL;
        } // asNumber
        
        /*! @brief Return non-@c NULL if the object is a Set.
         @returns Non-@c NULL if the object is a Set and @c NULL otherwise. */
        virtual inline const Set *
        asSet(void)
        const
        {
            return NULL;
        } // asSet
        
        /*! @brief Return non-@c NULL if the object is a String.
         @returns Non-@c NULL if the object is a String and @c NULL otherwise. */
        virtual inline const String *
        asString(void)
        const
        {
            return NULL;
        } // asString
        
        /*! @brief Return a copy of the object.
         @returns Returns a copy of the object. */
        virtual inline Value *
        clone(void)
        const
        {
            return NULL;
        } // copy

        /*! @brief Return @c true if two Values are structurally identical.
         @param[in] other The Value to be compared with.
         @returns @c true if the two Values are structurally identical. */
        virtual inline bool
        deeplyEqualTo(const Value &other)
        const
        {
            return (&other == this);
        } // deeplyEqualTo

        /*! @brief Return the enumeraton type of an object.
         @returns The enumeration type of an object. */
        virtual inline Enumerable
        enumerationType(void)
        const
        {
            return kEnumerableNotEnumerable;
        } // enumerationType

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        equalTo(const Value &other,
                bool        &validComparison)
        const
        {
            validComparison = (&other == this);
            return (&other == this);
        } // equalTo

        /*! @brief Return the type tag for the Value for use with Messages.
         @returns The type tag for the Value for use with Messages. */
        virtual inline uint8_t
        getTypeTag(void)
        const
        {
            return 0;
        } // getTypeTag

        /*! @brief Extract a Value for a Message.
         @param[in] inMessage The Message containing the Value.
         @param[in,out] position The position in the Message where the Value starts.
         @param[in] leadByte The initial byte of the Value representation.
         @param[out] status The status of the extraction operation.
         @param[in] parent A pointer to the Value that will contain the new object.
         @returns @c NULL if the Value was not successfully extracted and non-@c NULL on
         success. */
        static Value *
        getValueFromMessage(const Message &inMessage,
                            size_t        &position,
                            const int     leadByte,
                            ReadStatus    &status,
                            Array         *parent);

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        greaterThan(const Value &other,
                    bool        &validComparison)
        const
        {
# if MAC_OR_LINUX_
#  pragma unused(other)
# endif // MAC_OR_LINUX_
            validComparison = false;
            return false;
        } // greaterThan

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        greaterThanOrEqual(const Value &other,
                           bool        &validComparison)
        const
        {
            validComparison = (&other == this);
            return (&other == this);
        } // greaterThanOrEqual

        /*! @brief Set up the global structures used. */
        static void
        initialize(void);

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        lessThan(const Value &other,
                 bool        &validComparison)
        const
        {
# if MAC_OR_LINUX_
#  pragma unused(other)
# endif // MAC_OR_LINUX_
            validComparison = false;
            return false;
        } // lessThan

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual inline bool
        lessThanOrEqual(const Value &other,
                        bool        &validComparison)
        const
        {
            validComparison = (&other == this);
            return (&other == this);
        } // lessThanOrEqual

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator <(const Value &other)
        {
            bool valid = false;
            bool result = lessThan(other, valid);

            return (valid && result);
        } // operator <

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator >(const Value &other)
        {
            bool valid = false;
            bool result = greaterThan(other, valid);

            return (valid && result);
        } // operator >

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator <=(const Value &other)
        {
            bool valid = false;
            bool result = lessThanOrEqual(other, valid);

            return (valid && result);
        } // operator <=

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator >=(const Value &other)
        {
            bool valid = false;
            bool result = greaterThanOrEqual(other, valid);

            return (valid && result);
        } // operator >=

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator ==(const Value &other)
        {
            bool valid = false;
            bool result = equalTo(other, valid);

            return (valid && result);
        } // operator ==

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @returns The relative ordering of the two Values. */
        inline bool
        operator !=(const Value &other)
        {
            bool valid = false;
            bool result = ! equalTo(other, valid);

            return (valid && result);
        } // operator !=

        /*! @brief Add a readable representation of the object to the buffer.
         @param[in,out] outBuffer The buffer to be appended to.
         @param[in] squished @c true if the output has no unnecessary characters and @c false if it
         is as readable as possible. */
        virtual inline void
        printToStringBuffer(StringBuffer &outBuffer,
                            const bool   squished = false)
        const
        {
# if MAC_OR_LINUX_
#  pragma unused(outBuffer,squished)
# endif // MAC_OR_LINUX_
        } // printToStringBuffer

        /*! @brief Convert a readable representation of the object in a buffer into an object.
         @param[in] inBuffer The buffer to be scanned.
         @param[in,out] position Where in the buffer to start.
         @returns A new object if there is a valid object in the buffer and @c NULL otherwise. */
        static Value *
        readFromStringBuffer(const StringBuffer &inBuffer,
                             size_t             &position);

        /*! @brief Add a binary representation of the object to the Message.
         @param[in,out] outMessage The Message to be appended to. */
        virtual inline void
        writeToMessage(Message &outMessage)
        const
        {
# if MAC_OR_LINUX_
#  pragma unused(outMessage)
# endif // MAC_OR_LINUX_
        } // writeToMessage

    protected :
        // Protected methods.

        /*! @brief The constructor. */
        Value(void);

        /*! @brief Extracts an integer value from a Message.
         @param[in] theMessage The Message being processed.
         @param[in] leadByte The initial byte from the Message.
         @param[in,out] position The location of the next byte to be processed.
         @param[out] status Whether the extraction was successful.
         @returns Zero if there is a problem with the extraction. */
        static int64_t
        extractInt64FromMessage(const Message &theMessage,
                                const int     leadByte,
                                size_t        &position,
                                ReadStatus    &status);

        /*! @brief Returns @c true if the character can appear immediately after a Value in a
         string.
         @param[in] aChar The character of interest.
         @returns @c true if the character can appear immediately after a Value in a string. */
        static bool isLegalTerminator(const char aChar);

        /*! @brief Add a binary representation of an integer to the Message.
         @param[in,out] outMessage The Message to be appended to.
         @param[in] outValue The integer to be appended. */
        static void
        writeInt64ToMessage(Message       &outMessage,
                            const int64_t outValue);

    private :
        // Private methods.

        /*! @brief Update the Extractor map with the given values.
         @param[in] aByte The basic value to be used as the index.
         @param[in] aMask The bits of interest in the value.
         @param[in] theExtractor The function to be recorded. */
        static void
        addToExtractionMap(const uint8_t aByte,
                           const uint8_t aMask,
                           Extractor     theExtractor);
    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The table of Message extractors. */
        static ExtractorMap gExtractors;

        /*! @brief The table of StringBuffer readers. */
        static BufferReaderMap gReaders;

        /*! @brief The legal terminating characters for a Value. */
        static std::string gTerminators;

    }; // Value

} // nImO

#endif // ! defined(nImOvalue_HPP_)

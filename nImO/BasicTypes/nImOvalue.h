//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOvalue.h
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

#if (! defined(nImOvalue_H_))
# define nImOvalue_H_ /* Header guard */

# include <nImOcommon.h>
# include <nImOcomparisonStatus.h>

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
    class Container;
    class Date;
    class Double;
    class Number;
    class Time;

    /*! @brief The status of a conversion operation from a numeric string to an int64_t value. */
    enum class IntStatus
    {
        /*! @brief Conversion was successful. */
        Successful,

        /*! @brief The numeric string was incomplete and more data is needed. */
        Incomplete,

        /*! @brief Invalid characters were found in the numeric string. */
        Invalid

    }; // IntStatus

    /*! @brief A class to provide general value behaviours. */
    class Value
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

            /*! @brief A pointer to a function that extracts Value objects from a Message.
             Note that the parentValue argument is normally @c nullptr, and is used for handling
             multiple floating-point numbers in a sequence; if a series of Double values are extracted,
             they are directly added to the Array and the last Value is returned as the result of the
             function; for all other Value objects, the (single) Value that is extracted is added to
             the Array to simplify the logic, as well as being returned.
             @param[in] theMessage The Message being processed.
             @param[in] leadByte The initial byte of the Value.
             @param[in,out] position The location of the next byte to be processed.
             @param[in] parentValue A pointer to the Value that will contain the new object.
             @return @c nullptr if there is a problem with the extraction and non-@c nullptr if
             a Value was found and processed. */
            using Extractor = SpValue (*)
                (const Message & theMessage,
                 const int       leadByte,
                 size_t &        position,
                 SpArray         parentValue);

        private :
            // Private type definitions.

            /*! @brief The function pointer for StringBuffer readers.
             @param[in] inBuffer The buffer to be read from.
             @param[in,out] position The position for the next read.
             @return The next Value in the StringBuffer. */
            using BufferReader = SpValue (*)
                    (const StringBuffer &   inBuffer,
                     size_t &               position);

            /*! @brief The map from characters to BufferReaders. */
            using BufferReaderMap = std::map<char, BufferReader>;

            /*! @brief The non-const iterator for BufferReaderMaps. */
            using BufferReaderIterator = BufferReaderMap::iterator;

            /*! @brief The return result from the insert method. */
            using BufferReaderInsertResult = std::pair<BufferReaderMap::iterator, bool>;

            /*! @brief The type of value to be inserted. */
            using BufferReaderValue = BufferReaderMap::value_type;

            /*! @brief The map from bytes to Extractors. */
            using ExtractorMap = std::map<uint8_t, Extractor>;

            /*! @brief The non-const iterator for ExtractorMaps. */
            using ExtractorMapIterator = ExtractorMap::iterator;

        public :
            // Public methods.

            /*! @brief The destructor. */
            virtual
            ~Value
                (void);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Value
                (Value &&	other)
                noexcept = default;

            /*! @brief Return non-@c nullptr if the object is an Array.
             @return Non-@c nullptr if the object is an Array and @c nullptr otherwise. */
            virtual CPtr(Address)
            asAddress
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is an Array.
             @return Non-@c nullptr if the object is an Array and @c nullptr otherwise. */
            virtual CPtr(Array)
            asArray
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Blob.
             @return Non-@c nullptr if the object is a Blob and @c nullptr otherwise. */
            virtual CPtr(Blob)
            asBlob
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Container.
             @return Non-@c nullptr if the object is a Container and @c nullptr otherwise. */
            virtual CPtr(Container)
            asContainer
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Date.
             @return Non-@c nullptr if the object is a Date and @c nullptr otherwise. */
            virtual CPtr(Date)
            asDate
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Double.
             @return Non-@c nullptr if the object is a Double and @c nullptr otherwise. */
            virtual CPtr(Double)
            asDouble
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Flaw.
             @return Non-@c nullptr if the object is a Double and @c nullptr otherwise. */
            virtual CPtr(Flaw)
            asFlaw
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is an Integer.
             @return Non-@c nullptr if the object is an Integer and @c nullptr otherwise. */
            virtual CPtr(Integer)
            asInteger
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Logical.
             @return Non-@c nullptr if the object is a Logical and @c nullptr otherwise. */
            virtual CPtr(Logical)
            asLogical
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Map.
             @return Non-@c nullptr if the object is a Map and @c nullptr otherwise. */
            virtual CPtr(Map)
            asMap
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Number.
             @return Non-@c nullptr if the object is a Number and @c nullptr otherwise. */
            virtual CPtr(Number)
            asNumber
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Set.
             @return Non-@c nullptr if the object is a Set and @c nullptr otherwise. */
            virtual CPtr(Set)
            asSet
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a String.
             @return Non-@c nullptr if the object is a String and @c nullptr otherwise. */
            virtual CPtr(String)
            asString
                (void)
                const;

            /*! @brief Return non-@c nullptr if the object is a Time.
             @return Non-@c nullptr if the object is a Time and @c nullptr otherwise. */
            virtual CPtr(Time)
            asTime
                (void)
                const;

            /*! @brief Return @c true if two Values are structurally identical.
             @param[in] other The Value to be compared with.
             @return @c true if the two Values are structurally identical. */
            virtual bool
            deeplyEqualTo
                (const Value &  other)
                const;

            /*! @brief Write a short description of the Value to a stream.
             @param[in/out] output The stream to write to.
             @return The modified stream. */
            virtual std::ostream &
            describe
                (std::ostream & output)
                const = 0;

            /*! @brief Return the enumeration type of an object.
             @return The enumeration type of an object. */
            virtual Enumerable
            enumerationType
                (void)
                const;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            equalTo
                (const Value &  other)
                const;

            /*! @brief Return the type tag for the Value for use with Messages.
             @return The type tag for the Value for use with Messages. */
            virtual DataKind
            getTypeTag
                (void)
                const;

            /*! @brief Extract a Value for a Message.
             @param[in] inMessage The Message containing the Value.
             @param[in,out] position The position in the Message where the Value starts.
             @param[in] leadByte The initial byte of the Value representation.
             @param[in] parent A pointer to the Value that will contain the new object.
             @return @c nullptr if the Value was not successfully extracted and non-@c nullptr on
             success. */
            static SpValue
            getValueFromMessage
                (const Message &    inMessage,
                 size_t &           position,
                 const int          leadByte,
                 SpArray            parent);

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            greaterThan
                (const Value &  other)
                const;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            greaterThanOrEqual
                (const Value &  other)
                const;

            /*! @brief Set up the global structures used. */
            static void
            initialize
                (void);

            /*! @brief Returns @c true if the character can appear immediately after a Value in a
             string.
             @param[in] aChar The character of interest.
             @return @c true if the character can appear immediately after a Value in a string. */
            static bool
            isLegalTerminator
                (const char aChar);

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            lessThan
                (const Value &  other)
                const;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            virtual ComparisonStatus
            lessThanOrEqual
                (const Value &  other)
                const;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            inline bool
            operator<
                (const Value &  other)
            {
                ComparisonStatus    result{lessThan(other)};

                return (result.value() && result.isValid());
            }

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            inline bool
            operator>
                (const Value &  other)
            {
                ComparisonStatus    result{greaterThan(other)};

                return (result.value() && result.isValid());
            }

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            inline bool
            operator<=
                (const Value &  other)
            {
                ComparisonStatus    result{lessThanOrEqual(other)};

                return (result.value() && result.isValid());
            }

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            inline bool
            operator>=
                (const Value &  other)
            {
                ComparisonStatus    result{greaterThanOrEqual(other)};

                return (result.value() && result.isValid());
            }

            /*! @brief Return @c true if the two Values are equal.
             @param[in] other The Value to be compared with.
             @return @c true if the two Values are comparable and equal. */
            inline bool
            operator==
                (const Value &  other)
            {
                ComparisonStatus    result{equalTo(other)};

                return (result.value() && result.isValid());
            }

            /*! @brief Return @c false if the two Values are equal.
             @param[in] other The Value to be compared with.
             @return @c false if the two Values are comparable and equal and @c true otherwise. */
            inline bool
            operator!=
                (const Value &  other)
            {
                ComparisonStatus    result{equalTo(other)};

                return ((! result.value()) && result.isValid());
            }

            /*! @brief Add a readable representation of the object to the buffer.
             @param[in,out] outBuffer The buffer to be appended to.
             @param[in] squished @c true if the output has no unnecessary characters and @c false if it
            is as readable as possible. */
            virtual void
            printToStringBuffer
                (StringBuffer & outBuffer,
                 const bool     squished = false)
                const;

            /*! @brief Add a JSON representation of the object to the buffer.
             @param[in,out] outBuffer The buffer to be appended to.
             @param[in] asKey The value is a key.
             @param[in] squished @c true if the output has no unnecessary characters and @c false if it
             is as readable as possible. */
            virtual void
            printToStringBufferAsJSON
                (StringBuffer & outBuffer,
                 const bool     asKey = false,
                 const bool     squished = false)
                const;

            /*! @brief Convert a readable representation of the object in a buffer into an object.
             @param[in] inBuffer The buffer to be scanned.
             @param[in,out] position Where in the buffer to start.
             @return A new object if there is a valid object in the buffer and @c nullptr otherwise. */
            static SpValue
            readFromStringBuffer
                (const StringBuffer &   inBuffer,
                 size_t &               position);

            /*! @brief Add a binary representation of the object to the Message.
             @param[in,out] outMessage The Message to be appended to. */
            virtual void
            writeToMessage
                (Message &  outMessage)
                const;

            friend std::ostream &
            operator<<
                (std::ostream & out,
                 const Value &  aValue);

        protected :
            // Protected methods.

            /*! @brief The constructor. */
            Value
                (void) = default;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            Value &
            operator=
                (Value && other)
                noexcept = default;

            /*! @brief Insert a readable version of the object into an output stream.
             @param[in,out] out The stream to be added to.
             @param[in] aValue The object to be printed.
             @return The modified stream. */
            virtual std::ostream &
            operator<<
                (std::ostream & out)
                const;

            /*! @brief Extracts an integer value from a Message.
             @param[in] theMessage The Message being processed.
             @param[in] leadByte The initial byte from the Message.
             @param[in,out] position The location of the next byte to be processed.
             @param[out] status Whether the extraction was successful.
             @return Zero if there is a problem with the extraction. */
            static int64_t
            extractInt64FromMessage
                (const Message &    theMessage,
                 const int          leadByte,
                 size_t &           position,
                 IntStatus &        status);

            /*! @brief Add a binary representation of an integer to the Message.
             @param[in,out] outMessage The Message to be appended to.
             @param[in] outValue The integer to be appended. */
            static void
            writeInt64ToMessage
                (Message &      outMessage,
                 const int64_t  outValue);

        private :
            // Private methods.

            /*! @brief Update the Reader map with the given values.
             @param[in] prefixes The initial characters for the reader.
             @param[in] reader The reader corresponding to the initial characters. */
            static void
            addToReaderMap
                (CPtr(char)     prefixes,
                 BufferReader   reader);

            /*! @brief Update the Extractor map with the given values.
             @param[in] aByte The basic value to be used as the index.
             @param[in] aMask The bits of interest in the value.
             @param[in] theExtractor The function to be recorded. */
            static void
            addToExtractionMap
                (const DataKind aByte,
                 const DataKind aMask,
                 Extractor      theExtractor);

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The table of Message extractors. */
            static ExtractorMap gExtractors;

            /*! @brief The table of StringBuffer readers. */
            static BufferReaderMap  gReaders;

            /*! @brief The legal terminating characters for a Value. */
            static std::string  gTerminators;

    }; // Value

    /*! @brief Insert a readable version of the object into an output stream.
     @param[in,out] out The stream to be added to.
     @param[in] aValue The Value to be printed.
     @return The modified stream. */
    std::ostream &
    operator<<
        (std::ostream & out,
         const Value &  aValue);

} // nImO

#endif // not defined(nImOvalue_H_)

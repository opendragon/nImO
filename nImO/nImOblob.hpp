//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOblob.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO 'blob' values.
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
//  Created:    2016-03-22
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOblob_HPP_))
# define nImOblob_HPP_ /* Header guard */

# include <nImO/nImOvalue.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO 'blob' values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide binary data with unknown structure. */
    class Blob : public Value
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        typedef Value inherited;

    public :
        // Public methods.

        /*! @brief The constructor. */
        Blob(void);

        /*! @brief The constructor.
         @param data The data to be placed in the object.
         @param size The number of bytes in the data. */
        Blob(const uint8_t * data,
             const size_t    size);

        /*! @brief The copy constructor.
         @param other The object to be copied. */
        Blob(const Blob & other);

        /*! @brief The destructor. */
        virtual
        ~Blob(void);

        /*! @brief Return non-@c NULL if the object is a Blob.
         @returns Non-@c NULL if the object is a Blob and @c NULL otherwise. */
        virtual inline const Blob *
        asBlob(void)
        const
        {
            return this;
        } // asBlob
        
        /*! @brief Return a copy of the object.
         @returns Returns a copy of the object. */
        virtual Value *
        clone(void)
        const;

        /*! @brief Return @c true if two Values are structurally identical.
         @param other The Value to be compared with.
         @returns @c true if the two Values are structurally identical. */
        virtual bool
        deeplyEqualTo(const Value & other)
        const;
        
        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        equalTo(const Value & other,
                bool &        validComparison)
        const;

        /*! @brief Get the extraction information for Blob objects.
         @param aByte The byte value that indicates the start of a Blob value.
         @param aMask The mask to apply to a lead byte.
         @param theExtractor The function to perform when the lead byte is seen. */
        static void
        getExtractionInfo(uint8_t &   aByte,
                          uint8_t &   aMask,
                          Extractor & theExtractor);

        /*! @brief Return the type tag for the Value for use with Messages.
         @returns The type tag for the Value for use with Messages. */
        virtual inline uint8_t
        getTypeTag(void)
        const
        {
            return kKindOtherMessageExpectedStringOrBlobValue;
        } // getTypeTag

        /*! @brief Return the value of the object.
         @returns The value of the object. */
        inline const uint8_t *
        getValue(size_t & length)
        const
        {
            length = _size;
            return _value;
        } // getValue

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
        Blob &
        operator =(const Blob & other);

        /*! @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to.
         @param squished @c true if the output has no unnecessary characters and @c false if it
         is as readable as possible. */
        virtual void
        printToStringBuffer(StringBuffer & outBuffer,
                            const bool     squished = false)
        const;

        /*! @brief Add a binary representation of the object to the message.
         @param outMessage The Message to be appended to. */
        virtual void
        writeToMessage(Message & outMessage)
        const;

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Extracts Value objects from a Message.
         Note that the parentValue argument is normally @c NULL, and is used for handling multiple
         floating-point numbers in a sequence; if a series of Double values are extracted, they are
         directly added to the Array and the last Value is returned as the result of the function;
         for all other Value objects, the (single) Value that is extracted is added to the Array to
         simplify the logic, as well as being returned.
         @param theMessage The Message being processed.
         @param leadByte The initial byte of the Value.
         @param position The location of the next byte to be processed.
         @param status Whether the extraction was successful.
         @param parentValue A pointer to the Value that will contain the new object.
         @returns @c NULL if there is a problem with the extraction and non-@c NULL if
         a Value was found and processed. */
        static Value *
        extractValue(const Message & theMessage,
                     const int       leadByte,
                     size_t &        position,
                     ReadStatus &    status,
                     Array *         parentValue);

        /*! @brief Remove all entries. */
        void
        removeAllEntries(void);

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The associated value. */
        uint8_t * _value;

        /*! @brief The size of the associated value. */
        size_t _size;

    }; // Blob

} // nImO

#endif // ! defined(nImOblob_HPP_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOboolean.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO boolean values.
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

#if (! defined(nImOboolean_HPP_))
# define nImOboolean_HPP_ /* Header guard */

# include <nImO/nImOatom.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO boolean values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide true / false values. */
    class Boolean : public Atom
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        typedef Atom inherited;

    public :
        // Public methods.

        /*! @brief The constructor. */
        Boolean(void);

        /*! @brief The constructor.
          @param initialValue The initial value for the object. */
        explicit Boolean(const bool initialValue);

        /*! @brief The copy constructor.
         @param other The object to be copied. */
        Boolean(const Boolean & other);

        /*! @brief The destructor. */
        virtual
        ~Boolean(void);

        /*! @brief Return a copy of the object.
         @returns Returns a copy of the object. */
        virtual Value *
        clone(void)
        const;

        /*! @brief Return the enumeraton type of an object.
         @returns The enumeration type of an object. */
        virtual inline Enumerable
        enumerationType(void)
        const
        {
            return kEnumerableBoolean;
        } // enumerationType

        /*! @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        equalTo(const Value & other,
                bool &        validComparison)
        const;

        /*! @brief Return the standard textual representation of a boolean value.
         @param aValue The value to be represented.
         @returns The standard textual representation of a boolean value. */
        static const std::string &
        getCanonicalRepresentation(const bool aValue);

        /*! @brief Get the extraction information for Boolean objects.
         @param aByte The byte value that indicates the start of a Boolean value.
         @param aMask The mask to apply to a lead byte.
         @param theExtractor The function to perform when the lead byte is seen. */
        static void
        getExtractionInfo(uint8_t &   aByte,
                          uint8_t &   aMask,
                          Extractor & theExtractor);

        /*! @brief Return the characters that can appear as the start of a Boolean.
         @returns The characters that can appear as the start of a Boolean. */
        static const char *
        getInitialCharacters(void);

        /*! @brief Return the type tag for the Value for use with Messages.
         @returns The type tag for the Value for use with Messages. */
        virtual inline uint8_t
        getTypeTag(void)
        const
        {
            return kKindOtherMessageExpectedOtherValue;
        } // getTypeTag

        /*! @brief Return the value of the object.
         @returns The value of the object. */
        inline bool getValue(void)
        const
        {
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

        /*! @brief Return @c true if the object is a Boolean.
         @returns @c true if the object is a Boolean and @c false otherwise. */
        virtual inline bool
        isBoolean(void)
        const
        {
            return true;
        } // isBoolean

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
        Boolean &
        operator =(const Boolean & other);

        /*! @brief The assignment operator.
         @param value The value to be assigned.
         @returns The updated object. */
        Boolean &
        operator =(const bool value);

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
                             size_t  &            position);

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
         @param position The location of the next byte to be processed.
         @param status Whether the extraction was successful.
         @param parentValue A pointer to the Value that will contain the new object.
         @returns @c NULL if there is a problem with the extraction and non-@c NULL if
         a Value was found and processed. */
        static Value *
        extractValue(Message &    theMessage,
                     size_t &           position,
                     ReadStatus & status,
                     Array *      parentValue);
        
    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The associated value of the object. */
        bool _value;

    }; // Boolean

} // nImO

#endif // ! defined(nImOboolean_HPP_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOlogical.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO logical values.
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

#if (! defined(nImOlogical_HPP_))
# define nImOlogical_HPP_ /* Header guard */

# include <nImOatom.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO logical values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide true / false values. */
    class Logical : public Atom
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

        /*! @brief The class that this class is derived from. */
        using inherited = Atom;

    public :
        // Public methods.

        /*! @brief The constructor. */
        Logical(void);

        /*! @brief The constructor.
          @param[in] initialValue The initial value for the object. */
        explicit Logical(const bool initialValue);

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        Logical(const Logical &other);

        /*! @brief The destructor. */
        virtual
        ~Logical(void);

        /*! @brief Return non-@c nullptr if the object is a Logical.
         @returns Non-@c nullptr if the object is a Logical and @c nullptr otherwise. */
        virtual const Logical *
        asLogical(void)
        const
        override;

        /*! @brief Return @c true if two Values are structurally identical.
         @param[in] other The Value to be compared with.
         @returns @c true if the two Values are structurally identical. */
        virtual bool
        deeplyEqualTo(const Value &other)
        const
        override;

        /*! @brief Return the enumeration type of an object.
         @returns The enumeration type of an object. */
        virtual Enumerable
        enumerationType(void)
        const
        override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        equalTo(const Value &other,
                bool        &validComparison)
        const
        override;

        /*! @brief Return the standard textual representation of a boolean value.
         @param[in] aValue The value to be represented.
         @returns The standard textual representation of a boolean value. */
        static const std::string &
        getCanonicalRepresentation(const bool aValue);

        /*! @brief Get the extraction information for Logical objects.
         @param[out] aByte The byte value that indicates the start of a Logical value.
         @param[out] aMask The mask to apply to a lead byte.
         @param[out] theExtractor The function to perform when the lead byte is seen. */
        static void
        getExtractionInfo(DataKind  &aByte,
                          DataKind  &aMask,
                          Extractor &theExtractor);

        /*! @brief Return the characters that can appear as the start of a Logical.
         @returns The characters that can appear as the start of a Logical. */
        static const char *
        getInitialCharacters(void);

        /*! @brief Return the type tag for the Value for use with Messages.
         @returns The type tag for the Value for use with Messages. */
        virtual DataKind
        getTypeTag(void)
        const
        override;

        /*! @brief Return the value of the object.
         @returns The value of the object. */
        inline bool
        getValue(void)
        const
        {
            return _value;
        } // getValue

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        greaterThan(const Value &other,
                    bool        &validComparison)
        const
        override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        greaterThanOrEqual(const Value &other,
                           bool        &validComparison)
        const
        override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        lessThan(const Value &other,
                 bool        &validComparison)
        const
        override;

        /*! @brief Return the relative ordering of two Values.
         @param[in] other The Value to be compared with.
         @param[out] validComparison @c true if the Values were comparable and @c false otherwise;
         if @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        virtual bool
        lessThanOrEqual(const Value &other,
                        bool        &validComparison)
        const
        override;

        /*! @brief The assignment operator.
         @param[in] other The object to be copied.
         @returns The updated object. */
        Logical &
        operator =(const Logical &other);

        /*! @brief The assignment operator.
         @param[in] value The value to be assigned.
         @returns The updated object. */
        Logical &
        operator =(const bool value);

        /*! @brief Add a readable representation of the object to the buffer.
         @param[out] outBuffer The buffer to be appended to.
         @param[in] squished @c true if the output has no unnecessary characters and @c false if it
         is as readable as possible. */
        virtual void
        printToStringBuffer(StringBuffer &outBuffer,
                            const bool   squished = false)
        const
        override;

        /*! @brief Convert a readable representation of the object in a buffer into an object.
         @param[in] inBuffer The buffer to be scanned.
         @param[out] position Where in the buffer to start.
         @returns A new object if there is a valid object in the buffer and @c nullptr otherwise. */
        static SpValue
        readFromStringBuffer(const StringBuffer &inBuffer,
                             size_t             &position);

        /*! @brief Add a binary representation of the object to the message.
         @param[out] outMessage The Message to be appended to. */
        virtual void
        writeToMessage(Message &outMessage)
        const
        override;

    protected :
        // Protected methods.

    private :
        // Private methods.

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
        extractValue(const Message &theMessage,
                     const int     leadByte,
                     size_t        &position,
                     SpArray       parentValue);

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The associated value of the object. */
        bool _value;

    }; // Logical

} // nImO

#endif // ! defined(nImOlogical_HPP_)
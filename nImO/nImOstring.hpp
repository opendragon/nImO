//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstring.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO string values.
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

#if (! defined(nImOstring_HPP_))
# define nImOstring_HPP_ /* Header guard */

# include <nImO/nImOatom.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO string values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide string values. */
    class String : public Atom
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
        String(void);

        /*! @brief The copy constructor.
         @param other The object to be copied. */
        String(const String & other);

        /*! @brief The destructor. */
        ~String(void);

        /*! @brief The constructor.
         @param initialValue The initial value for the object. */
        explicit String(const std::string & initialValue);

        /*! @brief The constructor.
         @param initialValue The initial value for the object. */
        explicit String(const char * initialValue);

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
            return kEnumerableString;
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

        /*! @brief Return the characters that can appear as the start of a String.
         @returns The characters that can appear as the start of a String. */
        static const char *
        getInitialCharacters(void);

        /*! @brief Return the value of the object.
         @returns The value of the object. */
        inline const std::string & getValue(void)
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

        /*! @brief Return @c true if the object is a String.
         @returns @c true if the object is a String and @c false otherwise. */
        virtual inline bool
        isString(void)
        const
        {
            return true;
        } // isString

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
        String &
        operator =(const String & other);

        /*! @brief The assignment operator.
         @param value The value to be assigned.
         @returns The updated object. */
        String &
        operator =(const std::string & value);

        /*! @brief The assignment operator.
         @param value The value to be assigned.
         @returns The updated object. */
        String &
        operator =(const char * value);

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
 
    protected :
        // Protected methods.

    private :
        // Private methods.

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The associated value. */
        std::string _value;

    }; // String

} // nImO

#endif // ! defined(nImOstring_HPP_)
//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOdateTime.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO Date and Time values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-05-14
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOdateTime_H_))
# define nImOdateTime_H_ /* Header guard */

# include <BasicTypes/nImOatom.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO Date and Time values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide Date and Time values. */
    class DateTime : public Atom
    {

        public :
            // Public type definitions.

            /*! @brief A convenience type. */
            using DateTimeBytes = uint8_t[4];

            /*! @brief A convenience type. */
            using DateTimeValue = uint32_t;

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = Atom;

        public :
            // Public methods.

            /*! @brief Return the characters that can appear as the start of a Date or a Time.
             @return The characters that can appear as the start of a Date or a Time. */
            static CPtr(char)
            getInitialCharacters
                (void);

            /*! @brief Return the type tag for the Value for use with Messages.
             @return The type tag for the Value for use with Messages. */
            DataKind
            getTypeTag
                (void)
                const
                override;

            /*! @brief Return the raw internal value.
             @return The raw internal value. */
            DateTimeValue
            getValue
                (void)
                const
            {
                return _dateTimeValue;
            }

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            inline DateTime &
            operator=
                (const DateTime &    other)
            {
                if (this != &other)
                {
                    _dateTimeValue = other._dateTimeValue;
                }
                return *this;
            }

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            DateTime &
            operator=
                (DateTime && other)
                noexcept;

            /*! @brief Convert a readable representation of the object in a buffer into an object.
             @param[in] inBuffer The buffer to be scanned.
             @param[out] position Where in the buffer to start.
             @return A new object if there is a valid object in the buffer and @c nullptr otherwise. */
            static SpValue
            readFromStringBuffer
                (const StringBuffer &   inBuffer,
                 size_t &               position);

        protected :
            // Protected methods.

            /*! @brief Convert a 32-bit unsigned value into a sequence of bytes in network order.
             @param[out] outValue The byte sequence.
             @param[in] inValue The input value. */
            static void
            convertToByteArray
                (DateTimeBytes &        outValue,
                 const DateTimeValue    inValue);

            /*! @brief The constructor. */
            DateTime
                (void);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object. */
            DateTime
                (const DateTimeValue    initialValue);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object. */
            DateTime
                (const DateTimeBytes &  initialValue);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            DateTime
                (const DateTime &    other);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            DateTime
                (DateTime && other)
                noexcept;

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

            /*! @brief The associated value. */
            DateTimeValue   _dateTimeValue{0};

        private :
            // Private fields.

    }; // DateTime

} // nImO

#endif // not defined(nImOdateTime_H_)

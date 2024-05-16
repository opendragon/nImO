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
    /*! @brief The largest allowed value for the year. */
    constexpr int   kMaxYear{9999};

    /*! @brief The largest allowed value for the month. */
    constexpr int   kMaxMonth{12};

    /*! @brief The largest allowed value for the day. */
    constexpr int   kMaxDay{31};

    /*! @brief The largest allowed value for the hour. */
    constexpr int   kMaxHours{23};

    /*! @brief The largest allowed value for the minutes. */
    constexpr int   kMaxMinutes{59};

    /*! @brief The largest allowed value for the seconds. */
    constexpr int   kMaxSeconds{59};

    /*! @brief The largest allowed value for the seconds. */
    constexpr int   kMaxMilliseconds{999};

    /*! @brief A class to provide Date and Time values. */
    class DateTime : public Atom
    {

        public :
            // Public type definitions.

            /*! @brief A convenience type. */
            using DateTimeBytes = uint8_t[4];

            /*! @brief Another convenience type. */
            using DateTimeInts = uint16_t[4];

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = Atom;

        public :
            // Public methods.

            /*! @brief Get the extraction information for Date and Time objects.
             @param[out] aByte The byte value that indicates the start of a Date or Time value.
             @param[out] aMask The mask to apply to a lead byte.
             @return The function to perform when the lead byte is seen. */
            static Extractor
            getExtractionInfo
                (DataKind & aByte,
                 DataKind & aMask);

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
                    _isDate = other._isDate;
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

            /*! @brief Add a binary representation of the object to the message.
             @param[in,out] outMessage The Message to be appended to. */
            void
            writeToMessage
                (Message &  outMessage)
                const
                override;

        protected :
            // Protected methods.

            /*! @brief The constructor.
             @param[in] isDate @c true if a Date value and @c false if a Time value*/
            DateTime
                (const bool isDate);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object.
             @param[in] isDate @c true if a Date value and @c false if a Time value*/
            DateTime
                (const uint32_t initialValue,
                 const bool     isDate);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object.
             @param[in] isDate @c true if a Date value and @c false if a Time value*/
            DateTime
                (const DateTimeBytes &  initialValue,
                 const bool             isDate);

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
             @return @c nullptr if the Value could not be extracted because the Message ended before
             the Value did, a Flaw if the Value could not be extracted because it was not correct and
             a non-Flaw Value if extraction was successful. */
            static SpValue
            extractValue
                (const Message &    theMessage,
                 const int          leadByte,
                 size_t &           position,
                 SpArray            parentValue);

        public :
            // Public fields.

        protected :
            // Protected fields.

            /*! @brief The associated value. */
            uint32_t    _dateTimeValue{0};

            /*! @brief @c true if the value is a Date and @c false if it is a Time. */
            bool    _isDate{false};

        private :
            // Private fields.

    }; // DateTime

    /*! @brief Generate a value that can be used to initialize a Date value.
     @param[in] theYear The year part of the value.
     @param[in] theMonth The month part of the value.
     @param[in] theDay The day part of the value.
     @return The year, month and day combined to make a suitable initialization value for a Date. */
    inline constexpr uint32_t
    MakeDateValue
        (const int  theYear = 0,
         const int  theMonth = 0,
         const int  theDay = 0)
    {
        return StaticCast(uint32_t, (theYear * (kMaxMonth + 1) * (kMaxDay + 1)) + (theMonth * (kMaxDay + 1)) + theDay);
    }

    /*! @brief Generate a value that can be used to initialize a Time value.
     @param[in] theHour The hour part of the value.
     @param[in] theMinute The minute part of the value.
     @param[in] theSecond The second part of the value.
     @param[in] theMillisecond The millisecond part of the value.
     @return The hour, minute, second and millisecond combined to make a suitable initialization value for a Time. */
    inline constexpr uint32_t
    MakeTimeValue
        (const int  theHour = 0,
         const int  theMinute = 0,
         const int  theSecond = 0,
         const int  theMillisecond = 0)
    {
        return StaticCast(uint32_t, (theHour * (kMaxMinutes + 1) * (kMaxSeconds + 1) * (kMaxMilliseconds + 1)) +
                                    (theMinute * (kMaxSeconds + 1) * (kMaxMilliseconds + 1)) +
                                    (theSecond * (kMaxMilliseconds + 1)) + theMillisecond);
    }

} // nImO

#endif // not defined(nImOdateTime_H_)

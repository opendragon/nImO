//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOtime.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO Time values.
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
//  Created:    2024-05-15
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOtime_H_))
# define nImOtime_H_ /* Header guard */

# include <BasicTypes/nImOdateTime.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO Time values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The largest allowed value for the hour. */
    constexpr int   kMaxHours{23};

    /*! @brief The largest allowed value for the minutes. */
    constexpr int   kMaxMinutes{59};

    /*! @brief The largest allowed value for the seconds. */
    constexpr int   kMaxSeconds{59};

    /*! @brief The largest allowed value for the seconds. */
    constexpr int   kMaxMilliseconds{999};

    /*! @brief A class to provide Time values. */
    class Time final : public DateTime
    {

        public :
            // Public type definitions.

            /*! @brief A convenience type. */
            using TimePieces = uint16_t[4];

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = DateTime;

        public :
            // Public methods.

            /*! @brief The constructor. */
            Time
                (void);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object. */
            Time
                (const uint32_t initialValue);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object. */
            Time
                (const DateTimeBytes &  initialValue);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            Time
                (const Time &   other);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Time
                (Time && other)
                noexcept;

            /*! @brief Return non-@c nullptr if the object is a Time.
             @return Non-@c nullptr if the object is a Time and @c nullptr otherwise. */
            CPtr(Time)
            asTime
                (void)
                const
                override;

            /*! @brief Return @c true if two Values are structurally identical.
             @param[in] other The Value to be compared with.
             @return @c true if the two Values are structurally identical. */
            bool
            deeplyEqualTo
                (const Value &  other)
                const
                override;

            /*! @brief Write a short description of the Value to a stream.
             @param[in/out] output The stream to write to.
             @return The modified stream. */
            std::ostream &
            describe
                (std::ostream & output)
                const
                override;

            /*! @brief Return the enumeration type of an object.
             @return The enumeration type of an object. */
            Enumerable
            enumerationType
                (void)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            equalTo
                (const Value &  other)
                const
                override;

            /*! @brief Get the extraction information for Date and Time objects.
             @param[out] aByte The byte value that indicates the start of a Date or Time value.
             @param[out] aMask The mask to apply to a lead byte.
             @return The function to perform when the lead byte is seen. */
            static Extractor
            getExtractionInfo
                (DataKind & aByte,
                 DataKind & aMask);

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            greaterThan
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            greaterThanOrEqual
                (const Value &  other)
                const
                override;

            /*! @brief Return the hour part of the Time.
             @return The hour part of the Time. */
            uint16_t
            hour
                (void)
                const;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            lessThan
                (const Value &  other)
                const
                override;

            /*! @brief Return the relative ordering of two Values.
             @param[in] other The Value to be compared with.
             @return The relative ordering of the two Values. */
            ComparisonStatus
            lessThanOrEqual
                (const Value &  other)
                const
                override;

            /*! @brief Return the millisecond part of the Time.
             @return The millisecond part of the Time. */
            uint16_t
            millisecond
                (void)
                const;

            /*! @brief Return the minute part of the Time.
             @return The minute part of the Time. */
            uint16_t
            minute
                (void)
                const;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            inline Time &
            operator=
                (const Time &    other)
            {
                if (this != &other)
                {
                    inherited::operator=(other);
                }
                return *this;
            }

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            inline Time &
            operator=
                (Time && other)
                noexcept
            {
                if (this != &other)
                {
                    inherited::operator=(std::move(other));
                }
                return *this;
            }

            /*! @brief Add a readable representation of the object to the buffer.
             @param[in,out] outBuffer The buffer to be appended to.
             @param[in] squished @c true if the output has no unnecessary characters and @c false if it
            is as readable as possible. */
            void
            printToStringBuffer
                (StringBuffer & outBuffer,
                 const bool     squished = false)
                const
                override;

            /*! @brief Add a JSON representation of the object to the buffer.
             @param[in,out] outBuffer The buffer to be appended to.
             @param[in] asKey The value is a key.
             @param[in] squished @c true if the output has no unnecessary characters and @c false if it
             is as readable as possible. */
            void
            printToStringBufferAsJSON
                (StringBuffer & outBuffer,
                 const bool     asKey = false,
                 const bool     squished = false)
                const
                override;

            /*! @brief Return the second part of the Time.
             @return The second part of the time. */
            uint16_t
            second
                (void)
                const;

            /*! @brief Add a binary representation of the object to the message.
             @param[in,out] outMessage The Message to be appended to. */
            void
            writeToMessage
                (Message &  outMessage)
                const
                override;

        protected :
            // Protected methods.

            /*! @brief Insert a readable version of the object into an output stream.
             @param[in,out] out The stream to be added to.
             @param[in] aValue The object to be printed.
             @return The modified stream. */
            std::ostream &
            operator<<
                (std::ostream & out)
                const
                override;

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

        private :
            // Private fields.

    }; // Time

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

    /*! @brief Generate a value that can be used to initialize a Time value.
     @param[in] thePieces The components of the value.
     @return The pieces combined to make a suitable initialization value for a Time. */
    inline constexpr uint32_t
    MakeTimeValue
        (const Time::TimePieces &   thePieces)
    {
        return StaticCast(uint32_t, (thePieces[0] * (kMaxMinutes + 1) * (kMaxSeconds + 1) * (kMaxMilliseconds + 1)) +
                                    (thePieces[1] * (kMaxSeconds + 1) * (kMaxMilliseconds + 1)) +
                                    (thePieces[2] * (kMaxMilliseconds + 1)) + thePieces[3]);
    }

    /*! @brief Extract the first byte of a Time value in network order.
     @param[in] theHour The hour part of the value.
     @param[in] theMinute The minute part of the value.
     @param[in] theSecond The second part of the value.
     @param[in] theMillisecond The millisecond part of the value.
     @return The first byte of a Time value in network order. */
    inline constexpr uint8_t
    FirstTimeByte
        (const int  theHour = 0,
         const int  theMinute = 0,
         const int  theSecond = 0,
         const int  theMillisecond = 0)
    {
        return ((MakeTimeValue(theHour, theMinute, theSecond, theMillisecond) >> 24) & 0x0FF);
    }

    /*! @brief Extract the first byte of a Time value in network order.
     @param[in] thePieces The components of the value.
     @return The first byte of a Time value in network order. */
    inline constexpr uint8_t
    FirstTimeByte
        (const Time::TimePieces &   thePieces)
    {
        return ((MakeTimeValue(thePieces) >> 24) & 0x0FF);
    }

    /*! @brief Extract the second byte of a Time value in network order.
     @param[in] theHour The hour part of the value.
     @param[in] theMinute The minute part of the value.
     @param[in] theSecond The second part of the value.
     @param[in] theMillisecond The millisecond part of the value.
     @return The second byte of a Time value in network order. */
    inline constexpr uint8_t
    SecondTimeByte
        (const int  theHour = 0,
         const int  theMinute = 0,
         const int  theSecond = 0,
         const int  theMillisecond = 0)
    {
        return ((MakeTimeValue(theHour, theMinute, theSecond, theMillisecond) >> 16) & 0x0FF);
    }

    /*! @brief Extract the second byte of a Time value in network order.
     @param[in] thePieces The components of the value.
     @return The second byte of a Time value in network order. */
    inline constexpr uint8_t
    SecondTimeByte
        (const Time::TimePieces &   thePieces)
    {
        return ((MakeTimeValue(thePieces) >> 16) & 0x0FF);
    }

    /*! @brief Extract the third byte of a Time value in network order.
     @param[in] theHour The hour part of the value.
     @param[in] theMinute The minute part of the value.
     @param[in] theSecond The second part of the value.
     @param[in] theMillisecond The millisecond part of the value.
     @return The third byte of a Time value in network order. */
    inline constexpr uint8_t
    ThirdTimeByte
        (const int  theHour = 0,
         const int  theMinute = 0,
         const int  theSecond = 0,
         const int  theMillisecond = 0)
    {
        return ((MakeTimeValue(theHour, theMinute, theSecond, theMillisecond) >> 8) & 0x0FF);
    }

    /*! @brief Extract the third byte of a Time value in network order.
     @param[in] thePieces The components of the value.
     @return The third byte of a Time value in network order. */
    inline constexpr uint8_t
    ThirdTimeByte
        (const Time::TimePieces &   thePieces)
    {
        return ((MakeTimeValue(thePieces) >> 8) & 0x0FF);
    }

    /*! @brief Extract the fourth byte of a Time value in network order.
     @param[in] theHour The hour part of the value.
     @param[in] theMinute The minute part of the value.
     @param[in] theSecond The second part of the value.
     @param[in] theMillisecond The millisecond part of the value.
     @return The fourth byte of a Time value in network order. */
    inline constexpr uint8_t
    FourthTimeByte
        (const int  theHour = 0,
         const int  theMinute = 0,
         const int  theSecond = 0,
         const int  theMillisecond = 0)
    {
        return (MakeTimeValue(theHour, theMinute, theSecond, theMillisecond) & 0x0FF);
    }

    /*! @brief Extract the fourth byte of a Time value in network order.
     @param[in] thePieces The components of the value.
     @return The fourth byte of a Time value in network order. */
    inline constexpr uint8_t
    FourthTimeByte
        (const Time::TimePieces &   thePieces)
    {
        return (MakeTimeValue(thePieces) & 0x0FF);
    }

} // nImO

#endif // not defined(nImOtime_H_)

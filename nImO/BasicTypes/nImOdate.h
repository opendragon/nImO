//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOdate.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO Date values.
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

#if (! defined(nImOdate_H_))
# define nImOdate_H_ /* Header guard */

# include <BasicTypes/nImOdateTime.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO Date values. */
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

    /*! @brief The smallest allowed value for the year. */
    constexpr int   kMinYear{0};

    /*! @brief The smallest allowed value for the month. */
    constexpr int   kMinMonth{1};

    /*! @brief The smallest allowed value for the day. */
    constexpr int   kMinDay{1};

    /*! @brief A class to provide Date values. */
    class Date final : public DateTime
    {

        public :
            // Public type definitions.

            /*! @brief A convenience type. */
            using DatePieces = uint16_t[3];

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = DateTime;

        public :
            // Public methods.

            /*! @brief The constructor. */
            Date
                (void);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object. */
            Date
                (const DateTimeValue    initialValue);

            /*! @brief The constructor.
             @param[in] initialValue The initial value for the object. */
            Date
                (const DateTimeBytes &  initialValue);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            Date
                (const Date &   other);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Date
                (Date && other)
                noexcept;

            /*! @brief Return non-@c nullptr if the object is a Date.
             @return Non-@c nullptr if the object is a Date and @c nullptr otherwise. */
            CPtr(Date)
            asDate
                (void)
                const
                override;

            /*! @brief Return the day part of the Date.
             @return The day part of the Date. */
            uint16_t
            day
                (void)
                const;

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

            /*! @brief Return the month part of the Date.
             @return The month part of the Date. */
            uint16_t
            month
                (void)
                const;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            inline Date &
            operator=
                (const Date &    other)
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
            inline Date &
            operator=
                (Date && other)
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

            /*! @brief Add a binary representation of the object to the message.
             @param[in,out] outMessage The Message to be appended to. */
            void
            writeToMessage
                (Message &  outMessage)
                const
                override;

            /*! @brief Return the year part of the Date.
             @return The year part of the Date. */
            uint16_t
            year
                (void)
                const;

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

    }; // Date

    /*! @brief Generate a string representation of a date.
     @param[in] value The date to be converted to a string.
     @return The date as a string. */
    std::string
    ConvertDateToString
        (const DateTimeValue    value);

    /*! @brief Extract the components of a date from a string.
     @param[out] asBytes The bytes for the address.
     @param[in] inString The character string to process.
     @param[out] processedLength The number of characters processed.
     @return @c true on success and @c false on failure. */
    bool
    GetDatePieces
        (Date::DatePieces &     pieces,
         const std::string &    inString,
         Ptr(size_t)            processedLength = nullptr);

    /*! @brief Generate a value that can be used to initialize a Date value.
     @param[in] theYear The year part of the value.
     @param[in] theMonth The month part of the value.
     @param[in] theDay The day part of the value.
     @return The year, month and day combined to make a suitable initialization value for a Date. */
    inline constexpr DateTime::DateTimeValue
    MakeDateValue
        (const int  theYear = kMinYear,
         const int  theMonth = kMinMonth,
         const int  theDay = kMinDay)
    {
        return StaticCast(DateTime::DateTimeValue, (theYear * (kMaxMonth + 1) * (kMaxDay + 1)) + (theMonth * (kMaxDay + 1)) + theDay);
    }

    /*! @brief Generate a value that can be used to initialize a Date value.
     @param[in] thePieces The components of the value.
     @return The pieces combined to make a suitable initialization value for a Date. */
    inline constexpr DateTime::DateTimeValue
    MakeDateValue
        (const Date::DatePieces &   thePieces)
    {
        return StaticCast(DateTime::DateTimeValue, (thePieces[0] * (kMaxMonth + 1) * (kMaxDay + 1)) + (thePieces[1] * (kMaxDay + 1)) + thePieces[2]);
    }

    /*! @brief Extract the first byte of a Date value in network order.
     @param[in] theYear The year part of the value.
     @param[in] theMonth The month part of the value.
     @param[in] theDay The day part of the value.
     @return The first byte of a Date value in network order. */
    inline constexpr uint8_t
    FirstDateByte
        (const int  theYear = 0,
         const int  theMonth = 0,
         const int  theDay = 0)
    {
        return ((MakeDateValue(theYear, theMonth, theDay) >> 24) & 0x0FF);
    }

    /*! @brief Extract the first byte of a Date value in network order.
     @param[in] thePieces The components of the value.
     @return The first byte of a Date value in network order. */
    inline constexpr uint8_t
    FirstDateByte
        (const Date::DatePieces &   thePieces)
    {
        return ((MakeDateValue(thePieces) >> 24) & 0x0FF);
    }

    /*! @brief Extract the second byte of a Date value in network order.
     @param[in] theYear The year part of the value.
     @param[in] theMonth The month part of the value.
     @param[in] theDay The day part of the value.
     @return The second byte of a Date value in network order. */
    inline constexpr uint8_t
    SecondDateByte
        (const int  theYear = 0,
         const int  theMonth = 0,
         const int  theDay = 0)
    {
        return ((MakeDateValue(theYear, theMonth, theDay) >> 16) & 0x0FF);
    }

    /*! @brief Extract the second byte of a Date value in network order.
     @param[in] thePieces The components of the value.
     @return The second byte of a Date value in network order. */
    inline constexpr uint8_t
    SecondDateByte
        (const Date::DatePieces &   thePieces)
    {
        return ((MakeDateValue(thePieces) >> 16) & 0x0FF);
    }

    /*! @brief Extract the third byte of a Date value in network order.
     @param[in] theYear The year part of the value.
     @param[in] theMonth The month part of the value.
     @param[in] theDay The day part of the value.
     @return The third byte of a Date value in network order. */
    inline constexpr uint8_t
    ThirdDateByte
        (const int  theYear = 0,
         const int  theMonth = 0,
         const int  theDay = 0)
    {
        return ((MakeDateValue(theYear, theMonth, theDay) >> 8) & 0x0FF);
    }

    /*! @brief Extract the third byte of a Date value in network order.
     @param[in] thePieces The components of the value.
     @return The third byte of a Date value in network order. */
    inline constexpr uint8_t
    ThirdDateByte
        (const Date::DatePieces &   thePieces)
    {
        return ((MakeDateValue(thePieces) >> 8) & 0x0FF);
    }

    /*! @brief Extract the fourth byte of a Date value in network order.
     @param[in] theYear The year part of the value.
     @param[in] theMonth The month part of the value.
     @param[in] theDay The day part of the value.
     @return The fourth byte of a Date value in network order. */
    inline constexpr uint8_t
    FourthDateByte
        (const int  theYear = 0,
         const int  theMonth = 0,
         const int  theDay = 0)
    {
        return (MakeDateValue(theYear, theMonth, theDay) & 0x0FF);
    }

    /*! @brief Extract the fourth byte of a Date value in network order.
     @param[in] thePieces The components of the value.
     @return The fourth byte of a Date value in network order. */
    inline constexpr uint8_t
    FourthDateByte
        (const Date::DatePieces &   thePieces)
    {
        return (MakeDateValue(thePieces) & 0x0FF);
    }

} // nImO

#endif // not defined(nImOdate_H_)

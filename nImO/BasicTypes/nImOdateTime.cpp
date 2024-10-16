//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOdateTime.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO Date and Time values.
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

#include <BasicTypes/nImOdateTime.h>

#include <BasicTypes/nImOdate.h>
#include <BasicTypes/nImOtime.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmessage.h>
#include <Containers/nImOstringBuffer.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO Date and Time values. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

void
nImO::DateTime::convertToByteArray
    (DateTimeBytes &        outValue,
     const DateTimeValue    inValue)
{
    outValue[0] = StaticCast(uint8_t, (inValue >> 24) & 0x0FF);
    outValue[1] = StaticCast(uint8_t, (inValue >> 16) & 0x0FF);
    outValue[2] = StaticCast(uint8_t, (inValue >> 8) & 0x0FF);
    outValue[3] = StaticCast(uint8_t, inValue & 0x0FF);
} // convertToByteArray

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::DateTime::DateTime
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (const DateTimeValue    initialValue) :
        inherited{}, _dateTimeValue{initialValue}
{
    ODL_ENTER(); //####
    ODL_X1(initialValue); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (const DateTimeBytes &  initialValue) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_P1(&initialValue); //####
    _dateTimeValue = ((initialValue[0] << 24) | (initialValue[1] << 16) | (initialValue[2] << 8) | initialValue[3]);
    ODL_X1(_dateTimeValue); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (const DateTime &    other) :
        inherited{}, _dateTimeValue{other._dateTimeValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

nImO::DateTime::DateTime
    (DateTime && other)
    noexcept :
        inherited{std::move(other)}, _dateTimeValue{other._dateTimeValue}
{
    ODL_ENTER(); //####
    ODL_P1(&other); //####
    other._dateTimeValue = 0;
    ODL_EXIT_P(this); //####
} // nImO::DateTime::DateTime

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

CPtr(char)
nImO::DateTime::getInitialCharacters
    (void)
{
    ODL_ENTER(); //####
    static CPtr(char)   initialChars{"^"};

    ODL_EXIT_S(initialChars); //####
    return initialChars;
} // nImO::DateTime::getInitialCharacters

nImO::DataKind
nImO::DateTime::getTypeTag
    (void)
    const
{
    ODL_OBJENTER(); //####
    DataKind    result{DataKind::OtherMessageExpectedOtherValue};

    ODL_OBJEXIT_I(StaticCast(int, result)); //####
    return result;
} // nImO::DateTime::getTypeTag

nImO::DateTime &
nImO::DateTime::operator=
    (DateTime && other)
    noexcept
{
    ODL_OBJENTER(); //####
    ODL_P1(&other); //####
    if (this != &other)
    {
        inherited::operator=(std::move(other));
        _dateTimeValue = other._dateTimeValue;
        other._dateTimeValue = 0;
    }
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::DateTime::operator=

nImO::SpValue
nImO::DateTime::readFromStringBuffer
    (const StringBuffer &   inBuffer,
     size_t &               position)
{
    ODL_ENTER(); //####
    ODL_P2(&inBuffer, &position); //####
    SpValue result;
    size_t  localIndex{position};
    bool    atEnd;
    int     aChar{inBuffer.getChar(localIndex++, atEnd)};

    if ((! atEnd) && (kStartDateTimeChar == aChar))
    {
        // Determine if it's a Date or a Time.
        aChar = inBuffer.getChar(localIndex++, atEnd);
        if ((! atEnd) && ((kSecondCharForDate == aChar) || (kSecondCharForTime == aChar) ||
                          (kAltSecondCharForDate == aChar) || (kAltSecondCharForTime == aChar)))
        {
            bool    isDate{(kSecondCharForDate == aChar) || (kAltSecondCharForDate == aChar)};
            size_t  processed{0};

            if (isDate)
            {
                Date::DatePieces    pieces;
                auto                toScan{inBuffer.getString(localIndex)};

                if (GetDatePieces(pieces, toScan, &processed))
                {
                    result = std::make_shared<Date>(MakeDateValue(pieces));
                    localIndex += processed;
                }
                else
                {
                    ODL_LOG("! (GetDatePieces(pieces, toScan, &processed))"); //####
                }
            }
            else
            {
                Time::TimePieces    pieces;
                auto                toScan{inBuffer.getString(localIndex)};

                if (GetTimePieces(pieces, toScan, &processed))
                {
                    result = std::make_shared<Time>(MakeTimeValue(pieces));
                    localIndex += processed;
                }
                else
                {
                    ODL_LOG("! (GetTimePieces(pieces, toScan, &processed))"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! ((! atEnd) && ((kSecondCharForDate == aChar) || (kSecondCharForTime == aChar) || " //####
                    "(kAltSecondCharForDate == aChar) || (kAltSecondCharForTime == aChar)))"); //####
        }
    }
    else
    {
        ODL_LOG("! ((! atEnd) && (kStartDateTimeChar == aChar))"); //####
    }
    if (result)
    {
        position = localIndex;
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::DateTime::readFromStringBuffer

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

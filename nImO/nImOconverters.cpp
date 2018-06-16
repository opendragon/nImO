//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOconverters.cpp
//
//  Project:    nImO
//
//  Contains:   The function definitions for the packet conversion functions.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2018 by OpenDragon.
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
//  Created:    2018-06-15
//
//--------------------------------------------------------------------------------------------------

#include "nImOconverters.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The definitions of utility conversion functions. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace nImO;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#define NIMO_PACKET_ORDER   BIG_ENDIAN

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/* IEEE Standard 754 Single Precision Storage Format (float):
 *
 *        31 30           23 22            0
 * +--------+---------------+---------------+
 * | s 1bit | e[30:23] 8bit | f[22:0] 23bit |
 * +--------+---------------+---------------+
 * B0------------------->B1------->B2-->B3-->
 *
 * IEEE Standard 754 Double Precision Storage Format (double):
 *
 *        63 62            52 51            32   31            0
 * +--------+----------------+----------------+ +---------------+
 * | s 1bit | e[62:52] 11bit | f[51:32] 20bit | | f[31:0] 32bit |
 * +--------+----------------+----------------+ +---------------+
 * B0--------------->B1---------->B2--->B3---->  B4->B5->B6->B7->
 */

/*
    Transfer format for 'float' values:

    +-------------------------------+
    | byte 0                        |
    .-------------------------------.
    | S | top 7 bits of mantissa    | S = negative bit, mantissa[22..16]
    +-------------------------------+
    +-------------------------------+
    | byte 1                        |
    .-------------------------------.
    | exponent (8 bits)             | exponent[7..0]
    +-------------------------------+
    +-------------------------------+
    | byte 2                        |
    .-------------------------------.
    | middle 8 bits of mantissa     | mantissa[15..8]
    +-------------------------------+
    +-------------------------------+
    | byte 3                        |
    .-------------------------------.
    | bottom 8 bits of mantissa     | mantissa[7..0]
    +-------------------------------+
*/

/*
    Transfer format for 'double' values:

    +-------------------------------+
    | byte 0                        |
    .-------------------------------.
    | S | top 7 bits of exponent    | S = negative bit, exponent[10..4]
    +-------------------------------+
    +-------------------------------+
    | byte 1                        |
    .-------------------------------.
    | bottom 4 exp | top 4 mantissa | exponent[3..0], mantissa[51..48]
    +-------------------------------+
    +-------------------------------+
    | byte 2                        |
    .-------------------------------.
    | high mid 8 bits of mantissa   | mantissa[47..40]
    +-------------------------------+
    +-------------------------------+
    | byte 3                        |
    .-------------------------------.
    | mid mid 8 bits of mantissa    | mantissa[39..32]
    +-------------------------------+
    +-------------------------------+
    | byte 4                        |
    .-------------------------------.
    | low mid 8 bits of mantissa    | mantissa[31..24]
    +-------------------------------+
    +-------------------------------+
    | byte 5                        |
    .-------------------------------.
    | high bot 8 bits of mantissa   | mantissa[23..16]
    +-------------------------------+
    +-------------------------------+
    | byte 6                        |
    .-------------------------------.
    | mid bot 8 bits of mantissa    | mantissa[15..8]
    +-------------------------------+
    +-------------------------------+
    | byte 7                        |
    .-------------------------------.
    | low bot 8 bits of mantissa    | mantissa[7..0]
    +-------------------------------+
*/

# if (BYTE_ORDER == LITTLE_ENDIAN)
    union FloatAsBits
    {
        float _float;
        struct
        {
            unsigned int _mantissa : 23;
            unsigned int _exponent : 8;
            unsigned int _sign : 1;
        } _bits;
    }; // FloatAsBits
    
    union DoubleAsBits
    {
        double _double;
        struct
        {
            unsigned int _mantissa_low : 32;
            unsigned int _mantissa_high : 20;
            unsigned int _exponent : 11;
            unsigned int _sign : 1;
        } _bits;
    }; // DoubleAsBits
# elif (BYTE_ORDER == BIG_ENDIAN)
    union FloatAsBits
    {
        float _float;
        struct
        {
            unsigned int _sign : 1;
            unsigned int _exponent : 8;
            unsigned int _mantissa : 23;
        } _bits;
    }; // FloatAsBits
    
    union DoubleAsBits
    {
        double _double;
        struct
        {
            unsigned int _sign : 1;
            unsigned int _exponent : 11;
            unsigned int _mantissa_high : 20;
            unsigned int _mantissa_low : 32;
        } _bits;
    }; // DoubleAsBits
# else /* (BYTE_ORDER != LITTLE_ENDIAN) && (BYTE_ORDER != BIG_ENDIAN) */
#  error unknown ENDIAN type
# endif /* (BYTE_ORDER != LITTLE_ENDIAN) && (BYTE_ORDER != BIG_ENDIAN) */

int
nImO::ConvertDoubleToPacketOrder(uint8_t         *start,
                                 const uint8_t *end,
                                 const double    value)
{
    return -1;
} /* nImO:ConvertDoubleToPacketOrder */

int
nImO::ConvertFloatToPacketOrder(uint8_t       *start,
                                const uint8_t *end,
                                const float   value)
{
    return -1;
} /* nImO:ConvertFloatToPacketOrder */
 
int
nImO::ConvertLongToPacketOrder(uint8_t       *start,
                               const uint8_t *end,
                               const int64_t value)
{
    return -1;
} /* nImO:ConvertLongToPacketOrder */
   
int
nImO::ConvertPacketOrderToDouble(const uint8_t *start,
                                 const uint8_t *end,
                                 const double  &value)
{
    return -1;
} /* nImO:ConvertPacketOrderToDouble */

int
nImO::ConvertPacketOrderToFloat(const uint8_t *start,
                                const uint8_t *end,
                                const float   &value)
{
    return -1;
} /* nImO:ConvertPacketOrderToFloat */

int
nImO::ConvertPacketOrderToLong(const uint8_t *start,
                               const uint8_t *end,
                               const size_t  numBytes,
                               const int64_t &value)
{
    return -1;
} /* nImO:ConvertPacketOrderToLong */

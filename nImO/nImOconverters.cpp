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

#include <nImOconverters.h>

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

#if ((BYTE_ORDER != BIG_ENDIAN) && (BYTE_ORDER != LITTLE_ENDIAN))
# error Unknown byte order.
#endif // (BYTE_ORDER != BIG_ENDIAN) && (BYTE_ORDER != LITTLE_ENDIAN)

/*! @brief Swap the contents of a uint8_t array.
 @param[in,out] buffer The array to be swapped.
 @param[in] bufferSize The number of elements in the array. */
static void
swapBytes
    (Ptr(uint8_t)   buffer,
     const size_t   bufferSize)
{
    for (size_t ii = 0; ii < (bufferSize / 2); ++ii)
    {
        std::swap(buffer[ii], buffer[bufferSize - (ii + 1)]);
    }
} // swapBytes

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

size_t
nImO::ConvertDoubleToPacketOrder
    (Ptr(uint8_t)   start,
     CPtr(uint8_t)  end,
     const double   value)
{
    size_t  result;

    if (nullptr == start)
    {
        result = sizeof(double);
    }
    else if (nullptr == end)
    {
        result = 0;
    }
    else if ((start + sizeof(double)) > end)
    {
        result = 0;
    }
    else
    {
#if (BYTE_ORDER != NIMO_PACKET_ORDER)
        uint8_t buffer[sizeof(double)];
#endif // BYTE_ORDER != NIMO_PACKET_ORDER

#if (BYTE_ORDER == NIMO_PACKET_ORDER)
        memcpy(start, &value, sizeof(double));
#else // BYTE_ORDER != NIMO_PACKET_ORDER
        memcpy(buffer, &value, sizeof(buffer));
        swapBytes(buffer, sizeof(buffer));
        memcpy(start, buffer, sizeof(buffer));
#endif // BYTE_ORDER != NIMO_PACKET_ORDER
        result = sizeof(double);
    }
    return result;
} /* nImO:ConvertDoubleToPacketOrder */

size_t
nImO::ConvertInt64ToPacketOrder
    (Ptr(uint8_t)   start,
     CPtr(uint8_t)  end,
     const int64_t  value)
{
    size_t  result;
    uint8_t buffer[sizeof(int64_t)];
    size_t  numBytes{1};
    int64_t valueCopy{value};

    if ((nullptr != start) && ((nullptr == end) || (start > end)))
    {
        result = 0;
    }
    else
    {
        // Store the bytes of the value, MSB first.
        for (size_t ii = sizeof(buffer); ii > 0; --ii)
        {
            buffer[ii - 1] = (valueCopy & 0x00FF);
            valueCopy >>= 8;
        }
        // Determine the number of significant bytes.
        if (0 <= value)
        {
            for (size_t ii = 0; ii < sizeof(buffer); ++ii)
            {
                if (0 != buffer[ii])
                {
                    numBytes = sizeof(buffer) - ii;
                    // Correct for the high bit being set.
                    if (0x80 == (buffer[ii] & 0x80))
                    {
                        ++numBytes;
                    }
                    break;

                }
            }
        }
        else
        {
            for (size_t ii = 0; ii < sizeof(buffer); ++ii)
            {
                if (0xFF != buffer[ii])
                {
                    numBytes = sizeof(buffer) - ii;
                    // Correct for the high bit not being set.
                    if (0x00 == (buffer[ii] & 0x80))
                    {
                        ++numBytes;
                    }
                    break;

                }
            }
        }
        if (nullptr == start)
        {
            result = numBytes;
        }
        else
        {
#if (NIMO_PACKET_ORDER == BIG_ENDIAN)
            memcpy(start, buffer + sizeof(buffer) - numBytes, numBytes);
#else // NIMO_PACKET_ORDER != BIG_ENDIAN
            swapBytes(buffer, sizeof(buffer));
            memcpy(start, buffer, numBytes);
#endif // NIMO_PACKET_ORDER != BIG_ENDIAN
            result = numBytes;
        }
    }
    return result;
} /* nImO:ConvertInt64ToPacketOrder */

size_t
nImO::ConvertPacketOrderToDouble
    (CPtr(uint8_t)  start,
     CPtr(uint8_t)  end,
     double &       value)
{
    size_t  result;

    if ((nullptr == start) || (nullptr == end) || (end < start) || (start < (end + 1 - sizeof(double))))
    {
        result = 0;
    }
    else
    {
#if (BYTE_ORDER != NIMO_PACKET_ORDER)
        uint8_t buffer[sizeof(double)];
#endif // BYTE_ORDER != NIMO_PACKET_ORDER

#if (BYTE_ORDER == NIMO_PACKET_ORDER)
        memcpy(&value, start, sizeof(value));
#else // BYTE_ORDER != NIMO_PACKET_ORDER
        memcpy(buffer, start, sizeof(buffer));
        swapBytes(buffer, sizeof(buffer));
        memcpy(&value, buffer, sizeof(value));
#endif // BYTE_ORDER != NIMO_PACKET_ORDER
        result = sizeof(double);
    }
    return result;
} /* nImO:ConvertPacketOrderToDouble */

size_t
nImO::ConvertPacketOrderToInt64
    (CPtr(uint8_t)  start,
     CPtr(uint8_t)  end,
     int64_t &      value)
{
    size_t  result;

    if ((nullptr == start) || (nullptr == end) || (end < start) || (start < (end + 1 - sizeof(int64_t))))
    {
        result = 0;
    }
    else
    {
        uint8_t buffer[sizeof(value)];
        size_t  numBytes = end + 1 - start;

        // Fill the buffer, in MSB order.
#if (NIMO_PACKET_ORDER == BIG_ENDIAN)
        memcpy(buffer + sizeof(buffer) - numBytes, start, numBytes);
#else // NIMO_PACKET_ORDER != BIG_ENDIAN
        memcpy(buffer, start, numBytes);
        swapBytes(buffer, sizeof(buffer));
#endif // NIMO_PACKET_ORDER != BIG_ENDIAN
        // Find the sign bit and perform a sign-extension.
        if (numBytes < sizeof(value))
        {
            uint8_t aByte = buffer[sizeof(buffer) - numBytes];

            if (0x80 == (aByte & 0x80))
            {
                for (size_t ii = 0; ii < (sizeof(buffer) - numBytes); ++ii)
                {
                    buffer[ii] = 0xFF;
                }
            }
            else
            {
                for (size_t ii = 0; ii < (sizeof(buffer) - numBytes); ++ii)
                {
                    buffer[ii] = 0x00;
                }
            }
        }
        // Reconstruct the value.
        value = 0;
        for (size_t ii = 0; ii < sizeof(buffer); ++ii)
        {
            value = ((value << 8) | buffer[ii]);
        }
        result = numBytes;
    }
    return result;
} /* nImO:ConvertPacketOrderToInt64 */


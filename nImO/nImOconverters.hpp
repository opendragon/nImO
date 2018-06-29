//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOconverters.hpp
//
//  Project:    nImO
//
//  Contains:   The function declarations for the packet conversion functions.
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

#if (! defined(nImOconverters_HPP_))
# define nImOconverters_HPP_ /* Header guard */

# include <nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The declarations of utility conversion functions. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief Convert a double value to a sequence of bytes.
     @param[in,out] start The address of the first byte that is available;
     if @c NULL, do not store any bytes.
     @param[in] end The address of the last byte that is available.
     @param[in] value The value to be stored.
     @returns @c -1 if there is insufficient room to store the value, or the number of bytes
     stored (if start is non-@c NULL) or the number of bytes that would have been stored, if
     start is @c NULL. */
    int
    ConvertDoubleToPacketOrder(uint8_t       *start,
                               const uint8_t *end,
                               const double  value);


    /*! @brief Convert an integer value to a sequence of bytes.
     @param[in,out] start The address of the first byte that is available;
     if @c NULL, do not store any bytes.
     @param[in] end The address of the last byte that is available.
     @param[in] value The value to be stored.
     @returns @c -1 if there is insufficient room to store the value, or the number of bytes
     stored (if start is non-@c NULL) or the number of bytes that would have been stored, if
     start is @c NULL. */
    int
    ConvertLongToPacketOrder(uint8_t       *start,
                             const uint8_t *end,
                             const int64_t value);
   
    /*! @brief Convert a sequence of bytes to a double value.
     @param[in] start The address of the first byte that contains the value.
     @param[in] end The address of the last byte that contains data.
     @param[out] value The location to store the value.
     @returns @c -1 if the sequence was too short to hold the value or a parameter was invalid,
     or the number of bytes read. */
    int
    ConvertPacketOrderToDouble(const uint8_t *start,
                               const uint8_t *end,
                               double        &value);
    
    /*! @brief Convert a sequence of bytes to an integer value.
     @param[in] start The address of the first byte that contains the value.
     @param[in] end The address of the last byte that contains data.
     @param[in] numBytes The number of bytes of the sequence to use.
     @param[out] value The location to store the value.
     @returns @c -1 if the sequence was too short to hold the value or a parameter was invalid,
     or the number of bytes read. */
    int
    ConvertPacketOrderToLong(const uint8_t *start,
                             const uint8_t *end,
                             const size_t  numBytes,
                             int64_t       &value);
    
} // nImO

#endif // ! defined(nImOconverters_HPP_)


//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOMIMESupport.h
//
//  Project:    nImO
//
//  Contains:   The function definitions for MIME conversions.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2022 by OpenDragon.
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
//  Created:    2022-12-10
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOMIMESupport_H_))
# define nImOMIMESupport_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The function definitions for MIME conversions. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief The string to follow a MIME message being sent via TCP/IP; UDP/IP MIME messages are
 contained within a single datagram so don't need this string. */
const std::string   kMiMeMessageTerminator{"$$$"s};

namespace nImO
{
    /*! @brief Return a copy of the bytes in the Message as well as the number of bytes to be
     transmitted.
     Start-of-message bytes (as well as escape bytes) are escaped if present in the Message,
     except for the initial start-of-message byte.
     Escaping a byte involves inverting the high bit of the byte and having an escape byte
     inserted before the byte.
     The Message bytes are followed by a checksum byte, which is escaped if it matches a
     start-of-message byte or an escape byte.
     @param[out] length Set to the number of bytes returned.
     @return A pointer to a copy of the bytes in the Message, ready to be transmitted. */

    /*! @brief Convert a MIME-encoded string into the corresponding bytes.
     @param[in] inValue The MIME-encoding of some bytes.
     @param[out] outBytes The bytes represented by the MIME encoding.
     @return @c true if the input string can be converted into a sequence of bytes and
     @c false otherwise. */
    bool
    DecodeMIMEToBytes
        (const StringVector &   inValue,
         ByteVector &           outBytes);

    /*! @brief Convert a MIME-encoded string into the corresponding bytes.
     @param[in] inValue The MIME-encoding of the bytes to be converted.
     @param[out] outBytes The bytes represented by the MIME encoding.
     @return @c true if the input string can be converted into a sequence of bytes and
     @c false otherwise. */
    bool
    DecodeMIMEToBytes
        (const std::string &    inValue,
         ByteVector &           outBytes);

    /*! @brief Convert a sequence of bytes into a sequence of MIME-encoded strings.
     @param[out] outValue The MIME encoding of the sequence of bytes.
     @param[in] inBytes The bytes to be encoded.
     @param[in] numBytes The number of bytes to be encoded. */
    void
    EncodeBytesAsMIME
        (StringVector & outValue,
         CPtr(void)     inBytes,
         const size_t   numBytes);

    /*! @brief Convert a string into a sequence of MIME-encoded strings.
     @param[out] outValue The MIME encoding of the sequence of bytes.
     @param[in] inString The characters to be encoded. */
    inline void
    EncodeBytesAsMIME
        (StringVector &         outValue,
         const std::string &    inString)
    {
        EncodeBytesAsMIME(outValue, inString.data(), inString.length());
    }

} // nImO

#endif // not defined(nImOzMIMESupport_H_)

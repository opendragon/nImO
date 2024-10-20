//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOMIMESupport.cpp
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

#include <nImOMIMESupport.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif // defined(__APPLE__)
#include <boost/algorithm/string.hpp>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The function definitions for MIME conversions. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The 'equals' character that is used to pad MIME data. */
constexpr char  kEqualsChar{'='};

/*! @brief The set of characters to be used with MIME data. */
static const char   kMIMECharSet[]{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

/*! @brief The 'plus' character that is used in MIME data.
 This is a convenience declaration to simply validity checks. */
constexpr char  kPlusChar{'+'};

/*! @brief The 'slash' character that is used in MIME data.
 This is a convenience declaration to simply validity checks. */
constexpr char  kSlashChar{'/'};

/*! @brief The maximum line length when converting to a MIME representation of data. */
constexpr size_t    kMaxMIMELine{72}; // Must be divisible by 4!

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Check if a character can be used for MIME data.
 @param[in] ch The character to be checked.
 @return @c true if the character is valid in MIME data. */
static bool
isValidMIMEChar
    (const char ch)
{
    BOOST_STATIC_ASSERT_MSG(0 == (kMaxMIMELine % 4), "MIME line length is not divisible by 4.");
    return (isalnum(ch) || (kPlusChar == ch) || (kSlashChar == ch));
} // isValidMIMEChar

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

bool
nImO::DecodeMIMEToBytes
    (const StdStringVector &    inValue,
     ByteVector &               outBytes)
{
    bool        okSoFar{true};
    uint8_t     group6[4];
    uint8_t     group8[3];
    size_t      count4s{0};
    size_t      numRows{inValue.size()};
    size_t      newSize{0};
    std::string line;

    outBytes.clear();
    // First, validate the row sizes.
    for (size_t ii = 0; okSoFar && (ii < numRows); ++ii)
    {
        line = inValue[ii];
        if (0 == (line.length() % 4))
        {
            newSize += ((line.length() / 4) * 3);
        }
        else
        {
            okSoFar = false;
            ODL_B1(okSoFar); //####
        }
    }
    if (okSoFar)
    {
        outBytes.reserve(newSize);
    }
    for (size_t ii = 0; okSoFar && (ii < numRows); ++ii)
    {
        line = inValue[ii];
        for (size_t jj = 0, nn = line.length(); jj < nn; ++jj)
        {
            char    ch{line[jj]};

            if (kEqualsChar == ch)
            {
                break;

            }
            if (isValidMIMEChar(ch))
            {
                group6[count4s] = ch;
                if (4 == ++count4s)
                {
                    for (size_t kk = 0; kk < 4; ++kk)
                    {
                        group6[kk] = strchr(kMIMECharSet, group6[kk]) - kMIMECharSet;
                    }
                    group8[0] = (group6[0] << 2) + ((group6[1] & 0x0030) >> 4);
                    group8[1] = ((group6[1] & 0x000f) << 4) + ((group6[2] & 0x003c) >> 2);
                    group8[2] = ((group6[2] & 0x0003) << 6) + group6[3];
                    for (size_t kk = 0; kk < 3; ++kk)
                    {
                        outBytes.push_back(group8[kk]);
                    }
                    count4s = 0;
                }
            }
            else
            {
                okSoFar = false;
                ODL_B1(okSoFar); //####
            }
        }
        if (okSoFar && (count4s > 0))
        {
            for (size_t jj = count4s; jj < 4; ++jj)
            {
                group6[jj] = kEndOfString;
            }
            for (size_t jj = 0; jj < 4; ++jj)
            {
                CPtr(char)  offset{strchr(kMIMECharSet, group6[jj])};

                if (nullptr == offset)
                {
                    group6[jj] = 0;
                }
                else
                {
                    group6[jj] = offset - kMIMECharSet;
                }
            }
            group8[0] = (group6[0] << 2) + ((group6[1] & 0x0030) >> 4);
            group8[1] = ((group6[1] & 0x000f) << 4) + ((group6[2] & 0x003c) >> 2);
            group8[2] = ((group6[2] & 0x0003) << 6) + group6[3];
            for (size_t jj = 0; jj < (count4s - 1); ++jj)
            {
                outBytes.push_back(group8[jj]);
            }
        }
    }
    return okSoFar;
} // nImO::DecodeMIMEToBytes

bool
nImO::DecodeMIMEToBytes
    (const std::string &    inValue,
     ByteVector &           outBytes)
{
    StdStringVector tempValues;

    boost::split(tempValues, inValue, boost::is_any_of("\n"));
    return DecodeMIMEToBytes(tempValues, outBytes);
} // nImO::DecodeMIMEToBytes

void
nImO::EncodeBytesAsMIME
    (StdStringVector &  outValue,
     CPtr(void)         inBytes,
     const size_t       numBytes)
{
    CPtr(uint8_t)   rawBytes{StaticCast(CPtr(uint8_t), inBytes)};
    uint8_t         group8[3];
    uint8_t         group6[4];
    size_t          count3s{0};
    std::string     line;

    outValue.clear();
    // Calculate the number of rows.
    size_t  numQuads{(numBytes + 2) / 3};
    size_t  numRows{((4 * numQuads) + kMaxMIMELine - 1) / kMaxMIMELine};

    outValue.reserve(numRows);
    for (size_t ii = 0; ii < numBytes; ++ii)
    {
        group8[count3s++] = rawBytes[ii];
        if (3 == count3s)
        {
            group6[0] = ((group8[0] & 0x00fc) >> 2);
            group6[1] = ((group8[0] & 0x0003) << 4) + ((group8[1] & 0x00f0) >> 4);
            group6[2] = ((group8[1] & 0x000f) << 2) + ((group8[2] & 0x00c0) >> 6);
            group6[3] = (group8[2] & 0x003f);
            for (size_t jj = 0; jj < 4; ++jj)
            {
                if (kMaxMIMELine <= line.length())
                {
                    outValue.push_back(line);
                    line = ""s;
                }
                line += kMIMECharSet[group6[jj]];
            }
            count3s = 0;
        }
    }
    if (0 < count3s)
    {
        for (size_t ii = count3s; ii < 3; ++ii)
        {
            group8[ii] = kEndOfString;
        }
        group6[0] = ((group8[0] & 0x00fc) >> 2);
        group6[1] = ((group8[0] & 0x0003) << 4) + ((group8[1] & 0x00f0) >> 4);
        group6[2] = ((group8[1] & 0x000f) << 2) + ((group8[2] & 0x00c0) >> 6);
        group6[3] = (group8[2] & 0x003f);
        for (size_t ii = 0; ii < (count3s + 1); ++ii)
        {
            if (kMaxMIMELine <= line.length())
            {
                outValue.push_back(line);
                line = ""s;
            }
            line += kMIMECharSet[group6[ii]];
        }
        for ( ; count3s++ < 3; )
        {
            if (kMaxMIMELine <= line.length())
            {
                outValue.push_back(line);
                line = ""s;
            }
            line += kEqualsChar;
        }
    }
    if (! line.empty())
    {
        outValue.push_back(line);
    }
} // nImO::EncodeBytesAsMIME

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

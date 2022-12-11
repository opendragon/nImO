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

#include "nImOMIMESupport.hpp"

//#include <odlEnable.h>
#include <odlInclude.h>

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

static const char   kEqualsChar = '=';
static const char   kMIMECharSet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char   kPlusChar = '+';
static const char   kSlashChar = '/';

static const size_t kMaxMIMELine = 78;

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

static bool
isValidMIMEChar
    (const char ch)
{
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
    (const StringVector &   inValue,
     ByteVector &           outBytes)
{
    bool        okSoFar = true;
    uint8_t     group6[4];
    uint8_t     group8[3];
    size_t      count4s = 0;
    std::string line;

    outBytes.clear();
    for (size_t ii = 0, mm = inValue.size(); okSoFar && (ii < mm); ii++)
    {
        line = inValue[ii];
        for (size_t jj = 0, nn = line.length(); jj < nn; jj++)
        {
            char    ch = line[jj];

            if (kEqualsChar == ch)
            {
                break;

            }
            if (isValidMIMEChar(ch))
            {
                group6[count4s++] = ch;
                if (4 == count4s)
                {
                    for (size_t kk = 0; kk < 4; kk++)
                    {
                        group6[kk] = strchr(kMIMECharSet, group6[kk]) - kMIMECharSet;
                    }
                    group8[0] = (group6[0] << 2) + ((group6[1] & 0x30) >> 4);
                    group8[1] = ((group6[1] & 0xf) << 4) + ((group6[2] & 0x3c) >> 2);
                    group8[2] = ((group6[2] & 0x3) << 6) + group6[3];
                    for (size_t kk = 0; kk < 3; kk++)
                    {
                        outBytes.push_back(group8[kk]);
                    }
                    count4s = 0;
                }
            }
            else
            {
                okSoFar = false;
            }
        }
        if (okSoFar && (count4s > 0))
        {
            for (size_t jj = count4s; jj < 4; jj++)
            {
                group6[jj] = '\0';
            }
            for (size_t jj = 0; jj < 4; jj++)
            {
                CPtr(char)  offset = strchr(kMIMECharSet, group6[jj]);

                if (nullptr == offset)
                {
                    group6[jj] = 0;
                }
                else
                {
                    group6[jj] = offset - kMIMECharSet;
                }
            }
            group8[0] = (group6[0] << 2) + ((group6[1] & 0x30) >> 4);
            group8[1] = ((group6[1] & 0xf) << 4) + ((group6[2] & 0x3c) >> 2);
            group8[2] = ((group6[2] & 0x3) << 6) + group6[3];
            for (size_t jj = 0; jj < (count4s - 1); jj++)
            {
                outBytes.push_back(group8[jj]);
            }
        }
    }
    return okSoFar;
} // nImO::DecodeMIMEToBytes

void
nImO::EncodeBytesAsMIME
    (StringVector & outValue,
     CPtr(void)     inBytes,
     const size_t   numBytes)
{
    CPtr(uint8_t)   rawBytes = StaticCast(CPtr(uint8_t), inBytes);
    uint8_t         group8[3];
    uint8_t         group6[4];
    size_t          count3s = 0;
    std::string     line;

    outValue.clear();
    for (size_t ii = 0; ii < numBytes; ii++)
    {
        group8[count3s++] = rawBytes[ii];
        if (3 == count3s)
        {
            group6[0] = ((group8[0] & 0xfc) >> 2);
            group6[1] = ((group8[0] & 0x03) << 4) + ((group8[1] & 0xf0) >> 4);
            group6[2] = ((group8[1] & 0x0f) << 2) + ((group8[2] & 0xc0) >> 6);
            group6[3] = (group8[2] & 0x3f);
            for (size_t jj = 0; jj < 4; jj++)
            {
                line += kMIMECharSet[group6[jj]];
            }
            count3s = 0;
            if (kMaxMIMELine <= line.length())
            {
                outValue.push_back(line);
                line = "";
            }
        }
    }
    if (0 < count3s)
    {
        for (size_t ii = count3s; ii < 3; ii++)
        {
            group8[ii] = '\0';
        }
        group6[0] = ((group8[0] & 0xfc) >> 2);
        group6[1] = ((group8[0] & 0x03) << 4) + ((group8[1] & 0xf0) >> 4);
        group6[2] = ((group8[1] & 0x0f) << 2) + ((group8[2] & 0xc0) >> 6);
        group6[3] = (group8[2] & 0x3f);
        for (size_t ii = 0; ii < (count3s + 1); ii++)
        {
            if (kMaxMIMELine <= line.length())
            {
                outValue.push_back(line);
                line = "";
            }
            line += kMIMECharSet[group6[ii]];
        }
        while (count3s++ < 3)
        {
            if (kMaxMIMELine <= line.length())
            {
                outValue.push_back(line);
                line = "";
            }
            line += kEqualsChar;
        }
    }
    if (0 < line.length())
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

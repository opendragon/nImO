//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcompareWithoutCase.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO comparing strings without regard to case.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
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
//  Created:    2023-12-25
//
//--------------------------------------------------------------------------------------------------

#include <nImOcompareWithoutCase.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO string comparison functional objects. */
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

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::CompareWithoutCase &
nImO::CompareWithoutCase::operator=
    (CompareWithoutCase &&    other)
    noexcept
{
    NIMO_UNUSED_VAR_(other);
    ODL_OBJENTER(); //####
    ODL_P1("other = ", &other); //####
    ODL_OBJEXIT_P(this); //####
    return *this;
} // nImO::CompareWithoutCase::operator=

bool
nImO::CompareWithoutCase::operator()
    (const std::string &    lhs,
     const std::string &    rhs)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("lhs = ", lhs, "rhs = ", rhs); //####
    // true if lhs < rhs, false otherwise.
    const size_t  lhs_max{lhs.size()};
    const size_t  rhs_max{rhs.size()};
    const size_t  max_i{std::min(lhs_max, rhs_max)};
    bool          result{true};
    bool          same{true};

    for (size_t ii = 0; ii < max_i; ++ii)
    {
        const char  left{static_cast<char>(tolower(lhs[ii]))};
        const char  right{static_cast<char>(tolower(rhs[ii]))};

        if (left > right)
        {
            result = same = false;
            break;

        }
        if (left < right)
        {
            same = false;
            break;

        }
    }
    if (result && same)
    {
        // All the characters matched, up to the smaller of the two strings.
        result = (lhs_max < rhs_max);
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::CompareWithoutCase::operator()

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

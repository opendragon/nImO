//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/BasicTypes/nImOinvalid.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO invalid values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2017 by OpenDragon.
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
//  Created:    2017-03-05
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOinvalid.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO invalid values. */
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

nImO::Invalid::Invalid
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::Invalid::Invalid

nImO::Invalid::Invalid
    (const std::string &    description) :
        inherited{}, _description{description}
{
    ODL_ENTER(); //####
    ODL_S1s("description = ", description); //####
    ODL_EXIT_P(this); //####
} // nImO::Invalid::Invalid

nImO::Invalid::Invalid
    (const std::string &    description,
     const int64_t          position) :
        inherited{}, _description{description}
{
    std::stringstream   restOfDescription;

    ODL_ENTER(); //####
    ODL_S1s("description = ", description); //####
    ODL_I1("position = ", position); //####
    restOfDescription << " @" << position << "d/0x" << std::hex << position;
    _description += restOfDescription.str();
    ODL_EXIT_P(this); //####
} // nImO::Invalid::Invalid

nImO::Invalid::Invalid
    (Invalid && other)
    noexcept :
        inherited{std::move(other)}, _description{other._description}
{
    ODL_ENTER(); //####
    ODL_P1("other = ", &other); //####
    other._description = "";
    ODL_EXIT_P(this); //####
} // nImO::Invalid::Invalid

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

std::string
nImO::Invalid::getDescription
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_s(_description); //####
    return _description;
} // nImO::Invalid::GetDescription

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

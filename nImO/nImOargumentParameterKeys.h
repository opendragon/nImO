//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOargumentParameterKeys.h
//
//  Project:    nImO
//
//  Contains:   The type declarations for keys for argument parameters for nImO services.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2025 by OpenDragon.
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
//  Created:    2025-11-15
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOargumentParameterKeys_H_))
# define nImOargumentParameterKeys_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The type declarations for commands sent to %nImO services. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief The key for the allowedValues parameter. */
    const std::string   kAllowedValuesParameterKey{"allowedValues"s};

    /*! @brief The key for the description parameter. */
    const std::string   kDefaultParameterKey{"default"s};

    /*! @brief The key for the description parameter. */
    const std::string   kDescriptionParameterKey{"description"s};

    /*! @brief The key for the forOutput parameter. */
    const std::string   kForOutputParameterKey{"forOutput"s};

    /*! @brief The key for the hasMaximum parameter. */
    const std::string   kHasMaximumParameterKey{"hasMaximum"s};

    /*! @brief The key for the hasMinimum parameter. */
    const std::string   kHasMinimumParameterKey{"hasMinimum"s};

    /*! @brief The key for the isSystemPort parameter. */
    const std::string   kIsSystemPortParameterKey{"isSystemPort"s};

    /*! @brief The key for the maximum parameter. */
    const std::string   kMaximumParameterKey{"maximum"s};

    /*! @brief The key for the minimum parameter. */
    const std::string   kMinimumParameterKey{"minimum"s};

    /*! @brief The key for the name parameter. */
    const std::string   kNameParameterKey{"name"s};

    /*! @brief The key for the mode parameter. */
    const std::string   kModeParameterKey{"mode"s};

    /*! @brief The key for the pathPrefix parameter. */
    const std::string   kPathPrefixParameterKey{"pathPrefix"s};

    /*! @brief The key for the pathSuffix parameter. */
    const std::string   kPathSuffixParameterKey{"pathSuffix"s};

    /*! @brief The key for the type parameter. */
    const std::string   kTypeParameterKey{"type"s};

    /*! @brief The key for the useRandomPath parameter. */
    const std::string   kUseRandomPathParameterKey{"useRandomPath"s};

} // nImO

#endif // not defined(nImOargumentParameterKeys_H_)

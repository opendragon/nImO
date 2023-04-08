//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryTypes.h
//
//  Project:    nImO
//
//  Contains:   The type declarations for nImO registries.
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
//  Created:    2023-03-12
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOregistryTypes_H_))
# define nImOregistryTypes_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The type declarations for %nImO registries. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief The kind of service being registered. */
    enum class ServiceType : uint8_t
    {
        /*! @brief A general servic with no special attributes.*/
        GenericService,

        /*! @brief A launcher service. */
        LauncherService,

        /*! @brief An I/O service that has both inputs and outputs. */
        FilterService,

        /*! @brief An I/O service that only has inputs. */
        InputService,

        /*! @brief An I/O service that only has outputs. */
        OutputService
    }; // ServiceType

    /*! @brief The data found in the Registry for a node. */
    struct NodeInfo
    {
        /*! @brief @c true if the _connection field is valid. */
        bool    _found;

        /*! @brief The command IP address and port that was found.*/
        Connection  _connection;

        /*! @brief The nature of the service associated with the node. */
        ServiceType _serviceType;

        inline NodeInfo
            (void) :
                _found(false), _serviceType(ServiceType::GenericService)
        {
        }

    }; // NodeInfo

    /*! @brief Contains @c true if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<bool, std::string>    RegSuccessOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<RegSuccessOrFailure, int64_t> RegIntOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<RegSuccessOrFailure, bool> RegBoolOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<RegSuccessOrFailure, NodeInfo> RegNodeInfoOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<RegSuccessOrFailure, StringSet>   RegStringSetOrFailure;

    /*! @brief Contains @c true and the result if there was no problem and @c false along with an error message if there was a problem. */
    typedef std::pair<RegSuccessOrFailure, SpValue>   RegValueOrFailure;

} // nImO

#endif // not defined(nImOregistryTypes_H_)

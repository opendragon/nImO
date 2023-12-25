//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOinputOutputCommands.h
//
//  Project:    nImO
//
//  Contains:   The type declarations for commands sent to nImO I/O services.
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
//  Created:    2023-08-07
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOinputOutputCommands_H_))
# define nImOinputOutputCommands_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The type declarations for commands sent to %nImO I/O services. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief The 'setUpReceiver' request. */
    const std::string   kSetUpReceiverRequest{"setUpReceiver."s};

    /*! @brief The 'setUpReceiver' response. */
    const std::string   kSetUpReceiverResponse{"setUpReceiver="s};

    /*! @brief The 'setUpSender' request. */
    const std::string   kSetUpSenderRequest{"setUpSender."s};

    /*! @brief The 'setUpSender' response. */
    const std::string   kSetUpSenderResponse{"setUpSender="s};

    /*! @brief The 'startReceiver' request. */
    const std::string   kStartReceiverRequest{"startReceiver."s};

    /*! @brief The 'startReceiver' response. */
    const std::string   kStartReceiverResponse{"startReceiver="s};

    /*! @brief The 'startSender' request. */
    const std::string   kStartSenderRequest{"startSender."s};

    /*! @brief The 'startSender' response. */
    const std::string   kStartSenderResponse{"startSender="s};

    /*! @brief The 'stopReceiver' request. */
    const std::string   kStopReceiverRequest{"stopReceiver."s};

    /*! @brief The 'stopReceiver' response. */
    const std::string   kStopReceiverResponse{"stopReceiver="s};

    /*! @brief The 'stopSender' request. */
    const std::string   kStopSenderRequest{"stopSender."s};

    /*! @brief The 'stopSender' response. */
    const std::string   kStopSenderResponse{"stopSender="s};

} // nImO

#endif // not defined(nImOinputOutputCommands_H_)

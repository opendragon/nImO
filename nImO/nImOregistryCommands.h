//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryCommands.h
//
//  Project:    nImO
//
//  Contains:   The type declarations for commands sent to the nImO Registry.
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
//  Created:    2023-03-20
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOregistryCommands_H_))
# define nImOregistryCommands_H_ /* Header guard */

# include <nImOcommandTypes.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The type declarations for commands sent to the %nImO Registry. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief The request to add a node to the Registry. */
    const std::string   kAddNodeCommand = "addNode";

    /*! @brief The request to get information on a node from the Registry. */
    const std::string   kGetNodeInformationCommand = "getNodeInformation";

    /*! @brief The request to get the set of nodes in the Registry. */
    const std::string   kGetNodesCommand = "getNodes";

    /*! @brief The request to check if a node is present in the Registry. */
    const std::string   kNodePresentCommand = "nodePresent";

    /*! @brief The request to get the number of nodes in the Registry. */
    const std::string   kNumNodesCommand = "numNodes";

    /*! @brief The request to remove a node from the Registry. */
    const std::string   kRemoveNodeCommand = "removeNode";

} // nImO

#endif // not defined(nImOregistryCommands_H_)
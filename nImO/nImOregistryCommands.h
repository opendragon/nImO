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

# include <nImOcommonCommands.h>

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

    // Status reports

    /*! @brief The prefix for a channel added status report. */
    const std::string   kChannelAddedStatus = "c+";

    /*! @brief The prefix for a channel connected status report. */
    const std::string   kChannelConnectedStatus = "c*";

    /*! @brief The prefix for a channel connected status report. */
    const std::string   kChannelDisconnectedStatus = "c/";

    /*! @brief The prefix for a channel removed status report. */
    const std::string   kChannelRemovedStatus = "c-";

    /*! @brief The prefix for a channels removed status report. */
    const std::string   kChannelsRemovedStatus = "c!";

    /*! @brief The prefix for a node added status report. */
    const std::string   kNodeAddedStatus = "n+";

    /*! @brief The prefix for a node removed status report. */
    const std::string   kNodeRemovedStatus = "n-";

    // Requests and responses

    /*! @brief The request to add a channel to the Registry. */
    const std::string   kAddChannelRequest = "addChannel!";

    /*! @brief The 'addChannel' response. */
    const std::string   kAddChannelResponse = "addChannel=";

    /*! @brief The request to add a node to the Registry. */
    const std::string   kAddNodeRequest = "addNode!";

    /*! @brief The 'addNode' response. */
    const std::string   kAddNodeResponse = "addNode=";

    /*! @brief The request to reset the connection status on a channel from the Registry. */
    const std::string   kClearChannelInUseRequest = "clearChannelInUse!";

    /*! @brief The 'clearChannelInUse' response. */
    const std::string   kClearChannelInUseResponse = "clearChannelInUse=";

    /*! @brief The request to connect two channels to the Registry. */
    const std::string   kConnectChannelsRequest = "connectChannels!";

    /*! @brief The 'connectChannels' response. */
    const std::string   kConnectChannelsResponse = "connectChannels=";

    /*! @brief The request to break the connection between two channels to the Registry. */
    const std::string   kDisconnectChannelsRequest = "disconnectChannels!";

    /*! @brief The 'disconnectChannels' response. */
    const std::string   kDisconnectChannelsResponse = "disconnectChannels=";

    /*! @brief The request to get information on a channel from the Registry. */
    const std::string   kGetChannelInformationRequest = "getChannelInformation?";

    /*! @brief The 'getChannelInformation' response. */
    const std::string   kGetChannelInformationResponse = "getChannelInformation=";

    /*! @brief The request to get connection status on a channel from the Registry. */
    const std::string   kGetChannelInUseRequest = "getChannelInUse?";

    /*! @brief The 'getChannelInUse' response. */
    const std::string   kGetChannelInUseResponse = "getChannelInUse=";

    /*! @brief The request to get information on all channels in the Registry. */
    const std::string   kGetInformationForAllChannelsRequest = "getInformationForAllChannels?";

    /*! @brief The 'getInformationForAllChannels' response. */
    const std::string   kGetInformationForAllChannelsResponse = "getInformationForAllChannels=";

    /*! @brief The request to get information on all channels on a machine in the Registry. */
    const std::string   kGetInformationForAllChannelsOnMachineRequest = "getInformationForAllChannelsOnMachine?";

    /*! @brief The 'getInformationForAllChannelsOnMachine' response. */
    const std::string   kGetInformationForAllChannelsOnMachineResponse = "getInformationForAllChannelsOnMachine=";

    /*! @brief The request to get information on all channels on a node in the Registry. */
    const std::string   kGetInformationForAllChannelsOnNodeRequest = "getInformationForAllChannelsOnNode?";

    /*! @brief The 'getInformationForAllChannelsOnNode' response. */
    const std::string   kGetInformationForAllChannelsOnNodeResponse = "getInformationForAllChannelsOnNode=";

    /*! @brief The request to get information on all machines in the Registry. */
    const std::string   kGetInformationForAllMachinesRequest = "getInformationForAllMachines?";

    /*! @brief The 'getInformationForAllMachines' response. */
    const std::string   kGetInformationForAllMachinesResponse = "getInformationForAllMachines=";

    /*! @brief The request to get information on all nodes in the Registry. */
    const std::string   kGetInformationForAllNodesRequest = "getInformationForAllNodes?";

    /*! @brief The 'getInformationForAllNodes' response. */
    const std::string   kGetInformationForAllNodesResponse = "getInformationForAllNodes=";

    /*! @brief The request to get information on all nodes on a machine in the Registry. */
    const std::string   kGetInformationForAllNodesOnMachineRequest = "getInformationForAllNodesOnMachine?";

    /*! @brief The 'getInformationForAllNodesOnMachine' response. */
    const std::string   kGetInformationForAllNodesOnMachineResponse = "getInformationForAllNodesOnMachine=";

    /*! @brief The request to get launch details in the Registry. */
    const std::string   kGetLaunchDetailsRequest = "getLaunchDetails?";

    /*! @brief The 'getLaunchDetails' response. */
    const std::string   kGetLaunchDetailsResponse = "getLaunchDetails=";

    /*! @brief The request to get information on a machine from the Registry. */
    const std::string   kGetMachineInformationRequest = "getMachineInformation?";

    /*! @brief The 'getMachineInformation' response. */
    const std::string   kGetMachineInformationResponse = "getMachineInformation=";

    /*! @brief The request to get the set of machines in the Registry. */
    const std::string   kGetNamesOfMachinesRequest = "getNamesOfMachines?";

    /*! @brief The 'getNamesOfMachines' response'. */
    const std::string   kGetNamesOfMachinesResponse = "getNamesOfMachines=";

    /*! @brief The request to get the set of nodes in the Registry. */
    const std::string   kGetNamesOfNodesRequest = "getNamesOfNodes?";

    /*! @brief The 'getNamesOfNodes' response'. */
    const std::string   kGetNamesOfNodesResponse = "getNamesOfNodes=";

    /*! @brief The request to get the set of nodes on a machine in the Registry. */
    const std::string   kGetNamesOfNodesOnMachineRequest = "getNamesOfNodesOnMachine?";

    /*! @brief The 'getNamesOfNodesOnMachine' response'. */
    const std::string   kGetNamesOfNodesOnMachineResponse = "getNamesOfNodesOnMachine=";

    /*! @brief The request to get information on a node from the Registry. */
    const std::string   kGetNodeInformationRequest = "getNodeInformation?";

    /*! @brief The 'getNodeInformation' response. */
    const std::string   kGetNodeInformationResponse = "getNodeInformation=";

    /*! @brief The request to get the number of channels on a node in the Registry. */
    const std::string   kGetNumberOfChannelsOnNodeRequest = "getNumberOfChannelsOnNode?";

    /*! @brief The 'getNumberOfChannelsOnNode' response. */
    const std::string   kGetNumberOfChannelsOnNodeResponse = "getNumberOfChannelsOnNode=";

    /*! @brief The request to get the number of channels in the Registry. */
    const std::string   kGetNumberOfChannelsRequest = "getNumberOfChannels?";

    /*! @brief The 'getNumberOfChannels' response. */
    const std::string   kGetNumberOfChannelsResponse = "getNumberOfChannels=";

    /*! @brief The request to get the number of machines in the Registry. */
    const std::string   kGetNumberOfMachinesRequest = "getNumberOfMachines?";

    /*! @brief The 'getNumberOfMachines' response. */
    const std::string   kGetNumberOfMachinesResponse = "getNumberOfMachines=";

    /*! @brief The request to get the number of nodes in the Registry. */
    const std::string   kGetNumberOfNodesRequest = "getNumberOfNodes?";

    /*! @brief The 'getNumberOfNodes' response. */
    const std::string   kGetNumberOfNodesResponse = "getNumberOfNodes=";

    /*! @brief The request to get the number of nodes on a machine in the Registry. */
    const std::string   kGetNumberOfNodesOnMachineRequest = "getNumberOfNodesOnMachine?";

    /*! @brief The 'getNumberOfNodesOnMachine' response. */
    const std::string   kGetNumberOfNodesOnMachineResponse = "getNumberOfNodesOnMachine=";

    /*! @brief The request to check if a channel is present in the Registry. */
    const std::string   kIsChannelPresentRequest = "isChannelPresent?";

    /*! @brief The 'isChannelPresent' response. */
    const std::string   kIsChannelPresentResponse = "isChannelPresent=";

    /*! @brief The request to check if a machine is present in the Registry. */
    const std::string   kIsMachinePresentRequest = "isMachinePresent?";

    /*! @brief The 'isMachinePresent' response. */
    const std::string   kIsMachinePresentResponse = "isMachinePresent=";

    /*! @brief The request to check if a node is present in the Registry. */
    const std::string   kIsNodePresentRequest = "isNodePresent?";

    /*! @brief The 'isNodePresent' response. */
    const std::string   kIsNodePresentResponse = "isNodePresent=";

    /*! @brief The request to remove a channel from the Registry. */
    const std::string   kRemoveChannelRequest = "removeChannel!";

    /*! @brief The 'removeChannel' response. */
    const std::string   kRemoveChannelResponse = "removeChannel=";

    /*! @brief The request to remove the channels for a node from the Registry. */
    const std::string   kRemoveChannelsForNodeRequest = "removeChannelsForNode!";

    /*! @brief The 'removeChannelsForNode' response. */
    const std::string   kRemoveChannelsForNodeResponse = "removeChannelsForNode=";

    /*! @brief The request to remove a node from the Registry. */
    const std::string   kRemoveNodeRequest = "removeNode!";

    /*! @brief The 'removeNode' response. */
    const std::string   kRemoveNodeResponse = "removeNode=";

    /*! @brief The request to set the connection status on a channel from the Registry. */
    const std::string   kSetChannelInUseRequest = "setChannelInUse!";

    /*! @brief The 'setChannelInUse' response. */
    const std::string   kSetChannelInUseResponse = "setChannelInUse=";

} // nImO

#endif // not defined(nImOregistryCommands_H_)

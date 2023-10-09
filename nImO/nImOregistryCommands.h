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
    const std::string   kChannelAddedStatus{"c+"s};

    /*! @brief The prefix for a channel removed status report. */
    const std::string   kChannelRemovedStatus{"c-"s};

    /*! @brief The prefix for a channels removed status report. */
    const std::string   kChannelsRemovedStatus{"c^"s};

    /*! @brief The prefix for a connection added status report. */
    const std::string   kConnectionAddedStatus{"c*"s};

    /*! @brief The prefix for a connection removed status report. */
    const std::string   kConnectionRemovedStatus{"c/"s};

    /*! @brief The prefix for a node added status report. */
    const std::string   kNodeAddedStatus{"n+"s};

    /*! @brief The prefix for a node removed status report. */
    const std::string   kNodeRemovedStatus{"n-"s};

    // Requests and responses

    /*! @brief The request to add a channel to the Registry. */
    const std::string   kAddChannelRequest{"addChannel!"s};

    /*! @brief The 'addChannel' response. */
    const std::string   kAddChannelResponse{"addChannel="s};

    /*! @brief The request to connect two channels to the Registry. */
    const std::string   kAddConnectionRequest{"addConnection!"s};

    /*! @brief The 'addConnection' response. */
    const std::string   kAddConnectionResponse{"addConnection="s};

    /*! @brief The request to add a node to the Registry. */
    const std::string   kAddNodeRequest{"addNode!"s};

    /*! @brief The 'addNode' response. */
    const std::string   kAddNodeResponse{"addNode="s};

    /*! @brief The request to reset the connection status on a channel from the Registry. */
    const std::string   kClearChannelInUseRequest{"clearChannelInUse!"s};

    /*! @brief The 'clearChannelInUse' response. */
    const std::string   kClearChannelInUseResponse{"clearChannelInUse="s};

    /*! @brief The request to break the connection between two channels to the Registry. */
    const std::string   kDisconnectChannelsRequest{"disconnectChannels!"s};

    /*! @brief The 'disconnectChannels' response. */
    const std::string   kDisconnectChannelsResponse{"disconnectChannels="s};

    /*! @brief The request to get information on a channel from the Registry. */
    const std::string   kGetChannelInformationRequest{"getChannelInformation?"s};

    /*! @brief The 'getChannelInformation' response. */
    const std::string   kGetChannelInformationResponse{"getChannelInformation="s};

    /*! @brief The request to get connection status on a channel from the Registry and set it. */
    const std::string   kGetChannelInUseAndSetRequest{"getChannelInUseAndSet#"s};

    /*! @brief The 'getChannelInUseAndSet' response. */
    const std::string   kGetChannelInUseAndSetResponse{"getChannelInUseAndSet="s};

    /*! @brief The request to get connection status on a channel from the Registry. */
    const std::string   kGetChannelInUseRequest{"getChannelInUse?"s};

    /*! @brief The 'getChannelInUse' response. */
    const std::string   kGetChannelInUseResponse{"getChannelInUse="s};

    /*! @brief The request to get connection status on a channel from the Registry. */
    const std::string   kGetConnectionInformationRequest{"getConnectionInformation?"s};

    /*! @brief The 'getChannelInUse' response. */
    const std::string   kGetConnectionInformationResponse{"getConnectionInformation="s};

    /*! @brief The request to get information on all channels in the Registry. */
    const std::string   kGetInformationForAllChannelsRequest{"getInformationForAllChannels?"s};

    /*! @brief The 'getInformationForAllChannels' response. */
    const std::string   kGetInformationForAllChannelsResponse{"getInformationForAllChannels="s};

    /*! @brief The request to get information on all channels on a machine in the Registry. */
    const std::string   kGetInformationForAllChannelsOnMachineRequest{"getInformationForAllChannelsOnMachine?"s};

    /*! @brief The 'getInformationForAllChannelsOnMachine' response. */
    const std::string   kGetInformationForAllChannelsOnMachineResponse{"getInformationForAllChannelsOnMachine="s};

    /*! @brief The request to get information on all channels on a node in the Registry. */
    const std::string   kGetInformationForAllChannelsOnNodeRequest{"getInformationForAllChannelsOnNode?"s};

    /*! @brief The 'getInformationForAllChannelsOnNode' response. */
    const std::string   kGetInformationForAllChannelsOnNodeResponse{"getInformationForAllChannelsOnNode="s};

    /*! @brief The request to get information on all connections in the Registry. */
    const std::string   kGetInformationForAllConnectionsRequest{"getInformationForAllConnections?"s};

    /*! @brief The 'getInformationForAllConnections' response. */
    const std::string   kGetInformationForAllConnectionsResponse{"getInformationForAllConnections="s};

    /*! @brief The request to get information on all connections on a machine in the Registry. */
    const std::string   kGetInformationForAllConnectionsOnMachineRequest{"getInformationForAllConnectionsOnMachine?"s};

    /*! @brief The 'getInformationForAllConnectionsOnMachine' response. */
    const std::string   kGetInformationForAllConnectionsOnMachineResponse{"getInformationForAllConnectionsOnMachine="s};

    /*! @brief The request to get information on all connections on a node in the Registry. */
    const std::string   kGetInformationForAllConnectionsOnNodeRequest{"getInformationForAllConnectionsOnNode?"s};

    /*! @brief The 'getInformationForAllConnectionsOnNode' response. */
    const std::string   kGetInformationForAllConnectionsOnNodeResponse{"getInformationForAllConnectionsOnNode="s};

    /*! @brief The request to get information on all machines in the Registry. */
    const std::string   kGetInformationForAllMachinesRequest{"getInformationForAllMachines?"s};

    /*! @brief The 'getInformationForAllMachines' response. */
    const std::string   kGetInformationForAllMachinesResponse{"getInformationForAllMachines="s};

    /*! @brief The request to get information on all nodes in the Registry. */
    const std::string   kGetInformationForAllNodesRequest{"getInformationForAllNodes?"s};

    /*! @brief The 'getInformationForAllNodes' response. */
    const std::string   kGetInformationForAllNodesResponse{"getInformationForAllNodes="s};

    /*! @brief The request to get information on all nodes on a machine in the Registry. */
    const std::string   kGetInformationForAllNodesOnMachineRequest{"getInformationForAllNodesOnMachine?"s};

    /*! @brief The 'getInformationForAllNodesOnMachine' response. */
    const std::string   kGetInformationForAllNodesOnMachineResponse{"getInformationForAllNodesOnMachine="s};

    /*! @brief The request to get launch details in the Registry. */
    const std::string   kGetLaunchDetailsRequest{"getLaunchDetails?"s};

    /*! @brief The 'getLaunchDetails' response. */
    const std::string   kGetLaunchDetailsResponse{"getLaunchDetails="s};

    /*! @brief The request to get information on a machine from the Registry. */
    const std::string   kGetMachineInformationRequest{"getMachineInformation?"s};

    /*! @brief The 'getMachineInformation' response. */
    const std::string   kGetMachineInformationResponse{"getMachineInformation="s};

    /*! @brief The request to get the set of machines in the Registry. */
    const std::string   kGetNamesOfMachinesRequest{"getNamesOfMachines?"s};

    /*! @brief The 'getNamesOfMachines' response'. */
    const std::string   kGetNamesOfMachinesResponse{"getNamesOfMachines="s};

    /*! @brief The request to get the set of nodes in the Registry. */
    const std::string   kGetNamesOfNodesRequest{"getNamesOfNodes?"s};

    /*! @brief The 'getNamesOfNodes' response'. */
    const std::string   kGetNamesOfNodesResponse{"getNamesOfNodes="s};

    /*! @brief The request to get the set of nodes on a machine in the Registry. */
    const std::string   kGetNamesOfNodesOnMachineRequest{"getNamesOfNodesOnMachine?"s};

    /*! @brief The 'getNamesOfNodesOnMachine' response'. */
    const std::string   kGetNamesOfNodesOnMachineResponse{"getNamesOfNodesOnMachine="s};

    /*! @brief The request to get information on a node from the Registry. */
    const std::string   kGetNodeInformationRequest{"getNodeInformation?"s};

    /*! @brief The 'getNodeInformation' response. */
    const std::string   kGetNodeInformationResponse{"getNodeInformation="s};

    /*! @brief The request to get the number of channels on a node in the Registry. */
    const std::string   kGetNumberOfChannelsOnNodeRequest{"getNumberOfChannelsOnNode?"s};

    /*! @brief The 'getNumberOfChannelsOnNode' response. */
    const std::string   kGetNumberOfChannelsOnNodeResponse{"getNumberOfChannelsOnNode="s};

    /*! @brief The request to get the number of channels in the Registry. */
    const std::string   kGetNumberOfChannelsRequest{"getNumberOfChannels?"s};

    /*! @brief The 'getNumberOfChannels' response. */
    const std::string   kGetNumberOfChannelsResponse{"getNumberOfChannels="s};

    /*! @brief The request to get the number of channels in the Registry. */
    const std::string   kGetNumberOfConnectionsRequest{"getNumberOfConnections?"s};

    /*! @brief The 'getNumberOfConnections' response. */
    const std::string   kGetNumberOfConnectionsResponse{"getNumberOfConnections="s};

    /*! @brief The request to get the number of machines in the Registry. */
    const std::string   kGetNumberOfMachinesRequest{"getNumberOfMachines?"s};

    /*! @brief The 'getNumberOfMachines' response. */
    const std::string   kGetNumberOfMachinesResponse{"getNumberOfMachines="s};

    /*! @brief The request to get the number of nodes in the Registry. */
    const std::string   kGetNumberOfNodesRequest{"getNumberOfNodes?"s};

    /*! @brief The 'getNumberOfNodes' response. */
    const std::string   kGetNumberOfNodesResponse{"getNumberOfNodes="s};

    /*! @brief The request to get the number of nodes on a machine in the Registry. */
    const std::string   kGetNumberOfNodesOnMachineRequest{"getNumberOfNodesOnMachine?"s};

    /*! @brief The 'getNumberOfNodesOnMachine' response. */
    const std::string   kGetNumberOfNodesOnMachineResponse{"getNumberOfNodesOnMachine="s};

    /*! @brief The request to check if a channel is present in the Registry. */
    const std::string   kIsChannelPresentRequest{"isChannelPresent?"s};

    /*! @brief The 'isChannelPresent' response. */
    const std::string   kIsChannelPresentResponse{"isChannelPresent="s};

    /*! @brief The request to check if a machine is present in the Registry. */
    const std::string   kIsMachinePresentRequest{"isMachinePresent?"s};

    /*! @brief The 'isMachinePresent' response. */
    const std::string   kIsMachinePresentResponse{"isMachinePresent="s};

    /*! @brief The request to check if a node is present in the Registry. */
    const std::string   kIsNodePresentRequest{"isNodePresent?"s};

    /*! @brief The 'isNodePresent' response. */
    const std::string   kIsNodePresentResponse{"isNodePresent="s};

    /*! @brief The request to remove a channel from the Registry. */
    const std::string   kRemoveChannelRequest{"removeChannel!"s};

    /*! @brief The 'removeChannel' response. */
    const std::string   kRemoveChannelResponse{"removeChannel="s};

    /*! @brief The request to remove the channels for a node from the Registry. */
    const std::string   kRemoveChannelsForNodeRequest{"removeChannelsForNode!"s};

    /*! @brief The 'removeChannelsForNode' response. */
    const std::string   kRemoveChannelsForNodeResponse{"removeChannelsForNode="s};

    /*! @brief The request to remove a connection from the Registry. */
    const std::string   kRemoveConnectionRequest{"removeConnection!"s};

    /*! @brief The 'removeConnection' response. */
    const std::string   kRemoveConnectionResponse{"removeConnection="s};

    /*! @brief The request to remove a node from the Registry. */
    const std::string   kRemoveNodeRequest{"removeNode!"s};

    /*! @brief The 'removeNode' response. */
    const std::string   kRemoveNodeResponse{"removeNode="s};

    /*! @brief The request to set the connection status on a channel from the Registry. */
    const std::string   kSetChannelInUseRequest{"setChannelInUse!"s};

    /*! @brief The 'setChannelInUse' response. */
    const std::string   kSetChannelInUseResponse{"setChannelInUse="s};

} // nImO

#endif // not defined(nImOregistryCommands_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryProxy.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the interface to nImO registries.
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
//  Created:    2023-01-26
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOregistryProxy_H_))
# define nImOregistryProxy_H_ /* Header guard */

# include <Contexts/nImOcontextWithNetworking.h>
# include <nImOregistryTypes.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO registries. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide access to the Registry. */
    class RegistryProxy final
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] context The application context to use.
             @param[in] connection The IP address and port of the Registry. */
            RegistryProxy
                (SpContextWithNetworking    context,
                 const Connection &         connection);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            RegistryProxy
                (const RegistryProxy &  other) = delete;

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            RegistryProxy
                (RegistryProxy &&  other)
                noexcept = delete;

            /*! @brief Add an application to the Registry.
             @param[in] nodeName The name of the Launcher managing the application.
             @param[in] applicationName The name to display for the application.
             @param[in] applicationDescription The description of the application.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            addAppToList
                (const std::string &    nodeName,
                 const std::string &    applicationName,
                 const std::string &    applicationDescription);

            /*! @brief Add a channel to the Registry.
             @param[in] nodeName The node for the channel to be added.
             @param[in] path The path for the channel.
             @param[in] isOutput @c true if the channel is an output.
             @param[in] dataType The format for the data to be transferred over the channel.
             @param[in] modes The allowed transport modes for the channel.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            addChannel
                (const std::string &    nodeName,
                 const std::string &    path,
                 const bool             isOutput = false,
                 const std::string &    dataType = ""s,
                 const TransportType    modes = TransportType::kAny);

            /*! @brief Add a connection to the Registry.
             @param[in] fromNodeName The input node for the connection to be added.
             @param[in] fromPath The input path for the connection.
             @param[in] toNodeName The output node for the connection to be added.
             @param[in] toPath The output path for the connection.
             @param[in] dataType The format for the data to be transferred over the connection.
             @param[in] mode The transport mode for the connection.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            addConnection
                (const std::string &    fromNodeName,
                 const std::string &    fromPath,
                 const std::string &    toNodeName,
                 const std::string &    toPath,
                 const std::string &    dataType = ""s,
                 const TransportType    mode = TransportType::kAny);
    
            /*! @brief Add a node to the Registry.
             @param[in] nodeName The name of the node to be added.
             @param[in] argc The number of arguments in 'argv'.
             @param[in] argv The arguments given to the application.
             @param[in] serviceType The nature of the service corresponding to the node.
             @param[in] nodeConnection The command address and port of the node.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            addNode
                (const std::string &    nodeName,
                 const int              argc,
                 Ptr(Ptr(char))         argv,
                 const ServiceType      serviceType = ServiceType::GenericService,
                 const Connection &     nodeConnection = Connection());

            /*! @brief Clear the applications recorded in the Registry for the specified Launcher.
             @param[in] nodeName The name of the Launcher node to be updated.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            clearAppListForLauncher
                (const std::string &    nodeName);

            /*! @brief Mark a channel is in the Registry as not in use.
             @param[in] nodeName The name of the node to be updated.
             @param[in] path The path of the channel to be updated.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            clearChannelInUse
                (const std::string &    nodeName,
                 const std::string &    path);

            /*! @brief Get information on the channel stored in the Registry.
             @param[in] nodeName The name of the node for the channel to be located in the Registry.
             @param[in] path The path of the channel.
             @return @c true and if the channel was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            ChannelInfoOrFailure
            getChannelInformation
                (const std::string &    nodeName,
                 const std::string &    path);
        
            /*! @brief Check if a channel is in the Registry and is in use.
             @param[in] nodeName The name of the node to be checked.
             @param[in] path The path of the channel to be checked.
             @return @c true and if the channel was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            getChannelInUse
                (const std::string &    nodeName,
                 const std::string &    path);

            /*! @brief Get the current value of the in-use state of a channel in the Registry and set it, returning the state prior to setting it.
             @param[in] nodeName The name of the node to be checked.
             @param[in] path The path of the channel to be checked.
             @return @c true and if the channel was found and the operation was successfully performed, if it was in use,  and @c false and an error string otherwise. */
            BoolOrFailure
            getChannelInUseAndSet
                (const std::string &    nodeName,
                 const std::string &    path);

            /*! @brief Get information for a connection in the Registry.
             @param[in] nodeName The name of the node for the connection to be removed.
             @param[in] path The path for the connection.
             @param[in] fromIsSpecified @c true if the node and path are for the input to the connection and @c false if the output for the connection is specified.
             @return @c true and the information for the connection if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoOrFailure
            getConnectionInformation
                (const std::string &    nodeName,
                 const std::string &    path,
                 const bool             fromIsSpecified);

            /*! @brief Get information on the available applications.
             @return @c true and the list of applications if the operation was successfully performed and @c false and an error string otherwise. */
            ApplicationInfoVectorOrFailure
            getInformationForAllApplications
                (void);

            /*! @brief Get information for all channels in the Registry.
             @return @c true and the information for each channel if the operation was successfully performed and @c false and an error string otherwise. */
            ChannelInfoVectorOrFailure
            getInformationForAllChannels
                (void);

            /*! @brief Get information for all channels on a machine in the Registry.
             @param[in] machineName The name of the node for the channels to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            ChannelInfoVectorOrFailure
            getInformationForAllChannelsOnMachine
                (const std::string &    machineName);

            /*! @brief Get information for all channels on a node in the Registry.
             @param[in] nodeName The name of the node for the channels to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            ChannelInfoVectorOrFailure
            getInformationForAllChannelsOnNode
                (const std::string &    nodeName);

            /*! @brief Get information for all connections in the Registry.
             @return @c true and the information for each channel if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoVectorOrFailure
            getInformationForAllConnections
                (void);

            /*! @brief Get information for all connections to a machine in the Registry.
             @param[in] machineName The name of the machine for the connections to be located in the Registry.
             @return @c true and the information for each machine if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoVectorOrFailure
            getInformationForAllConnectionsOnMachine
                (const std::string &    machineName);

            /*! @brief Get information for all connections to a node in the Registry.
             @param[in] nodeName The name of the node for the connections to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoVectorOrFailure
            getInformationForAllConnectionsOnNode
                (const std::string &    nodeName);

            /*! @brief Get information for all machines in the Registry.
             @return @c true and the information for each machine if the operation was successfully performed and @c false and an error string otherwise. */
            MachineInfoVectorOrFailure
            getInformationForAllMachines
                (void);

            /*! @brief Get information for all nodes in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            NodeInfoVectorOrFailure
            getInformationForAllNodes
                (void);

            /*! @brief Get information for all nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            NodeInfoVectorOrFailure
            getInformationForAllNodesOnMachine
                (const std::string &    machineName);

            /*! @brief Get information on how the node was launched.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and if the node was found and the operation was successfully performed, its data, and @c false and an error string otherwise. */
            LaunchDetailsOrFailure
            getLaunchDetails
                (const std::string &    nodeName);

            /*! @brief Get information on the machine stored in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and if the machine was found its data,  if the operation was successfully performed and @c false and an error string otherwise. */
            MachineInfoOrFailure
            getMachineInformation
                (const std::string &    machineName);

            /*! @brief Get the set of machines in the Registry.
             @return @c true and the set of machines if the operation was successfully performed and @c false and an error string otherwise. */
            StdStringSetOrFailure
            getNamesOfMachines
                (void);

            /*! @brief Get the set of nodes in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            StdStringSetOrFailure
            getNamesOfNodes
                (void);

            /*! @brief Get the set of nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            StdStringSetOrFailure
            getNamesOfNodesOnMachine
                (const std::string &    machineName);

            /*! @brief Get information on the node stored in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and if the node was found its data,  if the operation was successfully performed and @c false and an error string otherwise. */
            NodeInfoOrFailure
            getNodeInformation
                (const std::string &    nodeName);

            /*! @brief Return the number of channels in the Registry.
             @return @c true and the number of channels if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfChannels
                (void);

            /*! @brief Return the number of channels associated with a node in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and the number of channels if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfChannelsOnNode
                (const std::string &    nodeName);

            /*! @brief Return the number of connections in the Registry.
             @return @c true and the number of connections if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfConnections
                (void);

            /*! @brief Return the number of machines in the Registry.
             @return @c true and the number of machines if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfMachines
                (void);

            /*! @brief Return the number of nodes in the Registry.
             @return @c true and the number of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfNodes
                (void);

            /*! @brief Return the number of nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the number of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfNodesOnMachine
                (const std::string &    machineName);

            /*! @brief Check if a channel is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @param[in] path The path of the channel to be checked.
             @return @c true and if the channel was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            isChannelPresent
                (const std::string &    nodeName,
                 const std::string &    path);

            /*! @brief Check if a machine is in the Registry.
             @param[in] machineName The name of the machine to be checked.
             @return @c true and if the machine was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            isMachinePresent
                (const std::string &    machineName);

            /*! @brief Check if a node is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @return @c true and if the node was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            isNodePresent
                (const std::string &    nodeName);

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            RegistryProxy &
            operator=
                (const RegistryProxy &  other) = delete;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            RegistryProxy &
            operator=
                (RegistryProxy &&   other)
                noexcept = delete;

            /*! @brief Remove a channel from the Registry.
             @param[in] nodeName The name of the node for the channel to be removed.
             @param[in] path The path for the channel.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            removeChannel
                (const std::string &    nodeName,
                 const std::string &    path);

            /*! @brief Remove all channels for a node from the Registry.
             @param[in] nodeName The name of the node.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            removeChannelsForNode
                (const std::string &    nodeName);

            /*! @brief Remove a connection from the Registry.
             @param[in] nodeName The name of the node for the connection to be removed.
             @param[in] path The path for the connection.
             @param[in] fromIsSpecified @c true if the node and path are for the input to the connection and @c false if the output for the connection is specified.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            removeConnection
                (const std::string &    nodeName,
                 const std::string &    path,
                 const bool             fromIsSpecified);

            /*! @brief Remove a node from the Registry.
             @param[in] nodeName The name of the node to be removed.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            removeNode
                (const std::string &    nodeName);

            /*! @brief Mark a channel is in the Registry in use.
             @param[in] nodeName The name of the node to be updated.
             @param[in] path The path of the channel to be updated.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            setChannelInUse
                (const std::string &    nodeName,
                 const std::string &    path);

        protected :
            // Protected methods.

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The application context to use. */
            SpContextWithNetworking _context{};

            /*! @brief The IP address and port of the Registry. */
            Connection  _connection{};

    }; // RegistryProxy

} // nImO

#endif // not defined(nImOregistryProxy_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistry.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO registries.
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

#if (! defined(nImOregistry_H_))
# define nImOregistry_H_ /* Header guard */

# include <Containers/nImOset.h>
# include <Contexts/nImOcontextWithNetworking.h>
# include <nImOregistryTypes.h>
# include "sqlite3.h"

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

    /*! @brief A class to provide database services. */
    class Registry final
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
             @param[in] owner The Context to be used for logging.
             @param[in] logging @c true if database activity is to be reported. */
            Registry
                (SpContextWithNetworking    owner,
                 const bool                 logging = false);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            Registry
                (const Registry &   other) = delete;

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Registry
                (Registry &&	other) = delete;

            /*! @brief The destructor. */
            ~Registry
                (void);

            /*! @brief Add an application to the Registry.
             @param[in] nodeName The name of the Launcher managing the application.
             @param[in] applicationName The name to display for the application.
             @param[in] applicationDescription The description of the application.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            addAppToList
                (const std::string &    nodeName,
                 const std::string &    applicationName,
                 const std::string &    applicationDescription)
                const;

            /*! @brief Add a channel to the Registry.
             @param[in] nodeName The node for the channel to be added.
             @param[in] path The path for the channel.
             @param[in] isOutput @c true if the channel is an output.
             @param[in] dataType The format for the data to be transferred over the channel.
             @param[in] modes The allowed transport modes for the channel.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            addChannel
                (const std::string &    nodeName,
                 const std::string &    path,
                 const bool             isOutput = false,
                 const std::string &    dataType = ""s,
                 const TransportType    modes = TransportType::kAny)
                const;

            /*! @brief Add a connection to the Registry.
             @param[in] fromNodeName The input node for the connection to be added.
             @param[in] fromPath The input path for the connection.
             @param[in] toNodeName The output node for the connection to be added.
             @param[in] toPath The output path for the connection.
             @param[in] dataType The format for the data to be transferred over the connection.
             @param[in] mode The transport mode for the connection.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            addConnection
                (const std::string &    fromNodeName,
                 const std::string &    fromPath,
                 const std::string &    toNodeName,
                 const std::string &    toPath,
                 const std::string &    dataType = ""s,
                 const TransportType    mode = TransportType::kAny)
                const;

            /*! @brief Add a machine to the Registry.
             @param[in] machineName The name of the machine to be added.
             @param[in] address The IP address for the machine.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            addMachine
                (const std::string &    machineName,
                 const IPv4Address      address = 0)
                const;

            /*! @brief Add a node to the Registry.
             @param[in] nodeName The name of the node to be added.
             @param[in] execPath The path to the executable for the node.
             @param[in] launchDirectory The path to the current directory when the executable for the node is launched.
             @param[in] commandLine The command line arguments passed to the executable for the node.
             @param[in] serviceClass The nature of the service corresponding to the node.
             @param[in] nodeConnection The command address and port of the node.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            addNode
                (const std::string &    nodeName,
                 const std::string &    execPath,
                 const std::string &    launchDirectory,
                 const std::string &    commandLine,
                 const ServiceType      serviceClass = ServiceType::GenericService,
                 const Connection &     nodeConnection = Connection())
                const;

            /*! @brief Clear the applications recorded in the Registry for the specified Launcher.
             @param[in] nodeName The name of the Launcher node to be updated.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            clearAppListForLauncher
                (const std::string &    nodeName)
                const;

            /*! @brief Mark a channel is in the Registry as not in use.
             @param[in] nodeName The name of the node to be updated.
             @param[in] path The path of the channel to be updated.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            clearChannelInUse
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Get information on the channel stored in the Registry.
             @param[in] nodeName The name of the node for the channel to be located in the Registry.
             @param[in] path The path of the channel.
             @return @c true and if the channel was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            ChannelInfoOrFailure
            getChannelInformation
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Check if a channel is in the Registry and is in use.
             @param[in] nodeName The name of the node to be checked.
             @param[in] path The path of the channel to be checked.
             @return @c true and if the channel was found and the operation was successfully performed, if it is in use,  and @c false and an error string otherwise. */
            BoolOrFailure
            getChannelInUse
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Get the current value of the in-use state of a channel in the Registry and set it, returning the state prior to setting it.
             @param[in] nodeName The name of the node to be checked.
             @param[in] path The path of the channel to be checked.
             @return @c true and if the channel was found and the operation was successfully performed, if it was in use,  and @c false and an error string otherwise. */
            BoolOrFailure
            getChannelInUseAndSet
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Get information for a connection in the Registry.
             @param[in] nodeName The name of the node for the connection to be removed.
             @param[in] path The path for the connection.
             @param[in] fromIsSpecified @c true if the node and path are for the input to the connection and @c false if the output for the connection is specified.
             @return @c true and the information for the connection if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoOrFailure
            getConnectionInformation
                (const std::string &    nodeName,
                 const std::string &    path,
                 const bool             fromIsSpecified)
                const;

            /*! @brief Get information on the available applications in the Registry.
             @return @c true and the list of applications if the operation was successfully performed and @c false and an error string otherwise. */
            ApplicationInfoVectorOrFailure
            getInformationForAllApplications
                (void)
                const;

            /*! @brief Get information on the available applications on a node in the Registry.
             @param[in] nodeName The name of the node for the applications to be located in the Registry.
             @return @c true and the list of applications if the operation was successfully performed and @c false and an error string otherwise. */
            ApplicationInfoVectorOrFailure
            getInformationForAllApplicationsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Get information for all channels in the Registry.
             @return @c true and the information for each channel if the operation was successfully performed and @c false and an error string otherwise. */
            ChannelInfoVectorOrFailure
            getInformationForAllChannels
                (void)
                const;

            /*! @brief Get information for all channels on a machine in the Registry.
             @param[in] machineName The name of the node for the channels to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            ChannelInfoVectorOrFailure
            getInformationForAllChannelsOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Get information for all channels on a node in the Registry.
             @param[in] nodeName The name of the node for the channels to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            ChannelInfoVectorOrFailure
            getInformationForAllChannelsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Get information for all connections in the Registry.
             @return @c true and the information for each channel if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoVectorOrFailure
            getInformationForAllConnections
                (void)
                const;

            /*! @brief Get information for all connections to a machine in the Registry.
             @param[in] machineName The name of the machine for the connections to be located in the Registry.
             @return @c true and the information for each machine if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoVectorOrFailure
            getInformationForAllConnectionsOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Get information for all connections to a node in the Registry.
             @param[in] nodeName The name of the node for the connections to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            ConnectionInfoVectorOrFailure
            getInformationForAllConnectionsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Get information for all machines in the Registry.
             @return @c true and the information for each machine if the operation was successfully performed and @c false and an error string otherwise. */
            MachineInfoVectorOrFailure
            getInformationForAllMachines
                (void)
                const;

            /*! @brief Get information for all nodes in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            NodeInfoVectorOrFailure
            getInformationForAllNodes
                (void)
                const;

            /*! @brief Get information for all nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            NodeInfoVectorOrFailure
            getInformationForAllNodesOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Get information on how the node was launched.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and if the node was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            LaunchDetailsOrFailure
            getLaunchDetails
                (const std::string &    nodeName)
                const;

            /*! @brief Get information on the machine stored in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and if the machine was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            MachineInfoOrFailure
            getMachineInformation
                (const std::string &    machineName)
                const;

            /*! @brief Get the set of machines in the Registry.
             @return @c true and the set of machines if the operation was successfully performed and @c false and an error string otherwise. */
            StdStringSetOrFailure
            getNamesOfMachines
                (void)
                const;

            /*! @brief Get the set of nodes in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            StdStringSetOrFailure
            getNamesOfNodes
                (void)
                const;

            /*! @brief Get the set of nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            StdStringSetOrFailure
            getNamesOfNodesOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Get information on the node stored in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and if the node was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            NodeInfoOrFailure
            getNodeInformation
                (const std::string &    nodeName)
                const;

            /*! @brief Get the set of nodes containing an application in the Registry.
             @param[in] applicationName The name of the application to be located in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            StdStringSetOrFailure
            getNodesWithApplication
                (const std::string &    applicationName)
                const;

            /*! @brief Return the number of applications in the Registry.
             @return @c true and the number of applications if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfApplications
                (void)
                const;

            /*! @brief Return the number of applications associated with a node in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and the number of applications if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfApplicationsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Return the number of channels in the Registry.
             @return @c true and the number of channels if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfChannels
                (void)
                const;

            /*! @brief Return the number of channels associated with a node in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and the number of channels if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfChannelsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Return the number of connections in the Registry.
             @return @c true and the number of connections if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfConnections
                (void)
                const;

            /*! @brief Return the number of input channels associated with a node in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and the number of input channels if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfInputChannelsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Return the number of machines in the Registry.
             @return @c true and the number of machines if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfMachines
                (void)
                const;

            /*! @brief Return the number of nodes in the Registry.
             @return @c true and the number of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfNodes
                (void)
                const;

            /*! @brief Return the number of nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the number of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfNodesOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Return the number of output channels associated with a node in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and the number of output channels if the operation was successfully performed and @c false and an error string otherwise. */
            IntOrFailure
            getNumberOfOutputChannelsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Check if a channel is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @param[in] path The path of the channel to be checked.
             @return @c true and if the channel was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            isChannelPresent
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Check if a machine is in the Registry.
             @param[in] machineName The name of the machine to be checked.
             @return @c true and if the machine was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            isMachinePresent
                (const std::string &    machineName)
                const;

            /*! @brief Check if a node is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @return @c true and if the node was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            BoolOrFailure
            isNodePresent
                (const std::string &    nodeName)
                const;

            /*! @brief Remove a channel from the Registry.
             @param[in] nodeName The name of the node for the channel to be removed.
             @param[in] path The path for the channel.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            removeChannel
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Remove all channels for a node from the Registry.
             @param[in] nodeName The name of the node.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            removeChannelsForNode
                (const std::string &    nodeName)
                const;

            /*! @brief Remove a connection from the Registry.
             @param[in] nodeName The name of the node for the connection to be removed.
             @param[in] path The path for the connection.
             @param[in] fromIsSpecified @c true if the node and path are for the input to the connection and @c false if the output for the connection is specified.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            removeConnection
                (const std::string &    nodeName,
                 const std::string &    path,
                 const bool             fromIsSpecified)
                const;

            /*! @brief Remove a node from the Registry.
             @param[in] nodeName The name of the node to be removed.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            removeNode
                (const std::string &    nodeName)
                const;

            /*! @brief Mark a channel is in the Registry in use.
             @param[in] nodeName The name of the node to be updated.
             @param[in] path The path of the channel to be updated.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            SuccessOrFailure
            setChannelInUse
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

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

            /*! @brief A pointer to the database context. */
            Ptr(sqlite3)    _dbHandle{nullptr};

            /*! @brief The owning Context. */
            SpContextWithNetworking _owner{};

    }; // Registry

    /*! @brief A holder for a shared pointer to a Registry. */
    using SpRegistry = std::shared_ptr<Registry>;

} // nImO

#endif // not defined(nImOregistry_H_)

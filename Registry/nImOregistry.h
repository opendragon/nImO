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

# include <ContainerTypes/nImOset.h>
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
            virtual
            ~Registry
                (void);

            /*! @brief Add a channel to the Registry.
             @param[in] nodeName The node for the channel to be added.
             @param[in] path The path for the channel.
             @param[in] isOutput @c true if the channel is an output.
             @param[in] dataType The format for the data to be transferred over the channel.
             @param[in] modes The allowed transport modes for the channel.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            RegSuccessOrFailure
            addChannel
                (const std::string &    nodeName,
                 const std::string &    path,
                 const bool             isOutput = false,
                 const std::string &    dataType = "",
                 const TransportType    modes = TransportType::kAny)
                const;

            /*! @brief Add a machine to the Registry.
             @param[in] machineName The name of the machine to be added.
             @param[in] address The IP address for the machine.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            RegSuccessOrFailure
            addMachine
                (const std::string &    machineName,
                 const uint32_t         address = 0)
                const;

            /*! @brief Add a node to the Registry.
             @param[in] nodeName The name of the node to be added.
             @param[in] execPath The path to the executable for the node.
             @param[in] launchDirectory The path to the current directory when the executable for the node is launched.
             @param[in] commandLine The command line arguments passed to the executable for the node.
             @param[in] serviceClass The nature of the service corresponding to the node.
             @param[in] nodeConnection The command address and port of the node.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            RegSuccessOrFailure
            addNode
                (const std::string &    nodeName,
                 const std::string &    execPath,
                 const std::string &    launchDirectory,
                 const std::string &    commandLine,
                 const ServiceType      serviceClass = ServiceType::GenericService,
                 const Connection &     nodeConnection = Connection())
                const;

            /*! @brief Get information on the channel stored in the Registry.
             @param[in] nodeName The name of the node for the channel to be located in the Registry.
             @param[in] path The path of the channel.
             @return @c true and if the channel was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            RegChannelInfoOrFailure
            getChannelInformation
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Get information for all channels in the Registry.
             @return @c true and the information for each channel if the operation was successfully performed and @c false and an error string otherwise. */
            RegChannelInfoVectorOrFailure
            getInformationForAllChannels
                (void)
                const;

            /*! @brief Get information for all channels on a machine in the Registry.
             @param[in] machineName The name of the node for the channels to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            RegChannelInfoVectorOrFailure
            getInformationForAllChannelsOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Get information for all channels on a node in the Registry.
             @param[in] nodeName The name of the node for the channels to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            RegChannelInfoVectorOrFailure
            getInformationForAllChannelsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Get information for all machines in the Registry.
             @return @c true and the information for each machine if the operation was successfully performed and @c false and an error string otherwise. */
            RegMachineInfoVectorOrFailure
            getInformationForAllMachines
                (void)
                const;

            /*! @brief Get information for all nodes in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            RegNodeInfoVectorOrFailure
            getInformationForAllNodes
                (void)
                const;

            /*! @brief Get information for all nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            RegNodeInfoVectorOrFailure
            getInformationForAllNodesOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Get information on how the node was launched.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and if the node was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            RegLaunchDetailsOrFailure
            getLaunchDetails
                (const std::string &    nodeName)
                const;

            /*! @brief Get information on the machine stored in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and if the machine was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            RegMachineInfoOrFailure
            getMachineInformation
                (const std::string &    machineName)
                const;

            /*! @brief Get the set of machines in the Registry.
             @return @c true and the set of machines if the operation was successfully performed and @c false and an error string otherwise. */
            RegStringSetOrFailure
            getNamesOfMachines
                (void)
                const;

            /*! @brief Get the set of nodes in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            RegStringSetOrFailure
            getNamesOfNodes
                (void)
                const;

            /*! @brief Get the set of nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            RegStringSetOrFailure
            getNamesOfNodesOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Get information on the node stored in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and if the node was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            RegNodeInfoOrFailure
            getNodeInformation
                (const std::string &    nodeName)
                const;

            /*! @brief Return the number of channels in the Registry.
             @return @c true and the number of channels if the operation was successfully performed and @c false and an error string otherwise. */
            RegIntOrFailure
            getNumberOfChannels
                (void)
                const;

            /*! @brief Return the number of channels associated with a node in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and the number of channels if the operation was successfully performed and @c false and an error string otherwise. */
            RegIntOrFailure
            getNumberOfChannelsOnNode
                (const std::string &    nodeName)
                const;

            /*! @brief Return the number of machines in the Registry.
             @return @c true and the number of machines if the operation was successfully performed and @c false and an error string otherwise. */
            RegIntOrFailure
            getNumberOfMachines
                (void)
                const;

            /*! @brief Return the number of nodes in the Registry.
             @return @c true and the number of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            RegIntOrFailure
            getNumberOfNodes
                (void)
                const;

            /*! @brief Return the number of nodes on a machine in the Registry.
             @param[in] machineName The name of the machine to be located in the Registry.
             @return @c true and the number of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            RegIntOrFailure
            getNumberOfNodesOnMachine
                (const std::string &    machineName)
                const;

            /*! @brief Check if a channel is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @param[in] channelPath The path of the channel to be checked.
             @return @c true and if the channel was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            RegBoolOrFailure
            isChannelPresent
                (const std::string &    nodeName,
                 const std::string &    channelPath)
                const;

            /*! @brief Check if a machine is in the Registry.
             @param[in] machineName The name of the machine to be checked.
             @return @c true and if the machine was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            RegBoolOrFailure
            isMachinePresent
                (const std::string &    machineName)
                const;

            /*! @brief Check if a node is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @return @c true and if the node was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            RegBoolOrFailure
            isNodePresent
                (const std::string &    nodeName)
                const;

            /*! @brief Remove a channel from the Registry.
             @param[in] nodeName The name of the node for the channel to be removed.
             @param[in] path The path for the channel.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            RegSuccessOrFailure
            removeChannel
                (const std::string &    nodeName,
                 const std::string &    path)
                const;

            /*! @brief Remove all channels for a node from the Registry.
             @param[in] nodeName The name of the node.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            RegSuccessOrFailure
            removeChannelsForNode
                (const std::string &    nodeName)
                const;

            /*! @brief Remove a node from the Registry.
             @param[in] nodeName The name of the node to be removed.
             @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
            RegSuccessOrFailure
            removeNode
                (const std::string &    nodeName)
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
            Ptr(sqlite3)    _dbHandle;

            /*! @brief The owning Context. */
            SpContextWithNetworking _owner;

    }; // Registry

    /*! @brief A holder for a shared pointer to a Registry. */
    using SpRegistry = std::shared_ptr<Registry>;

} // nImO

#endif // not defined(nImOregistry_H_)

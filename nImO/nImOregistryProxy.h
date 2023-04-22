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

# include <nImOcontextWithNetworking.h>
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

            /*! @brief The destructor. */
            virtual
            ~RegistryProxy
                (void);

            /*! @brief Add a node to the Registry.
             @param[in] nodeName The name of the node to be added.
             @param[in] execPath The path to the executable for the node.
             @param[in] launchDirectory The path to the current directory when the executable for the node is launched.
             @param[in] commandLine The command line arguments passed to the executable for the node.
             @param[in] serviceType The nature of the service corresponding to the node.
             @param[in] nodeConnection The command address and port of the node.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            RegBoolOrFailure
            addNode
                (const std::string &    nodeName,
                 const std::string &    execPath,
                 const std::string &    launchDirectory,
                 const std::string &    commandLine,                
                 const ServiceType      serviceType = ServiceType::GenericService,
                 const Connection &     nodeConnection = Connection());

            /*! @brief Get information for all nodes in the Registry.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            RegNodeInfoVectorOrFailure
            getInformationForAllNodes
                (void);

            /*! @brief Get information on how the node was launched.
             @param[in] nodeName The name of the node to be located in the Registry.
             @return @c true and if the node was found and the operation was successfully performed, its data,  and @c false and an error string otherwise. */
            RegLaunchDetailsOrFailure
            getLaunchDetails
                (const std::string &    nodeName);

            /*! @brief Get the set of nodes in the Registry.
             @return @c true and the set of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            RegStringSetOrFailure
            getNamesOfNodes
                (void);

            /*! @brief Get information on the node stored in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @param[out] nodeAddress The IP address of the node.
             @param[out] nodePort The command port of the node.
             @return @c true and if the node was found its data,  if the operation was successfully performed and @c false and an error string otherwise. */
            RegNodeInfoOrFailure
            getNodeInformation
                (const std::string &    nodeName);

            /*! @brief Return the number of nodes in the Registry.
             @return @c true and the number of nodes if the operation was successfully performed and @c false and an error string otherwise. */
            RegIntOrFailure
            getNumberOfNodes
                (void);

            /*! @brief Check if a node is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @return @c true and if the node was found,  if the operation was successfully performed and @c false and an error string otherwise. */
            RegBoolOrFailure
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

            /*! @brief Remove a node from the Registry.
             @param[in] nodeName The name of the node to be removed.
             @return @c true and the information for each node if the operation was successfully performed and @c false and an error string otherwise. */
            RegBoolOrFailure
            removeNode
                (const std::string &    nodeName);

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
            SpContextWithNetworking _context;

            /*! @brief The IP address and port of the Registry. */
            Connection  _connection;

    }; // RegistryProxy

} // nImO

#endif // not defined(nImOregistryProxy_H_)

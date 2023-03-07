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

# include <nImOcontextWithNetworking.h>
# include <nImOset.h>
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
             @param[in] owner The context to be used for logging.
             @param[in] logging @c true if database activity is to be reported. */
            Registry
                (Ptr(ContextWithNetworking) owner = nullptr,
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

            /*! @brief Add a node to the Registry.
             @param[in] nodeName The name of the node to be added.
             @param[in] nodeAddress The IPv4 address of the node.
             @param[in] nodePort The command port for the node.
             @return @c true if the node was added and @c false if it was not added. */
            bool
            addNode
                (const std::string &    nodeName,
                 const uint32_t         nodeAddress = 0,
                 const uint16_t         nodePort = 0);

            /*! @brief Get information on the node stored in the Registry.
             @param[in] nodeName The name of the node to be located in the Registry.
             @param[out] nodeAddress The IP address of the node.
             @param[out] nodePort The command port of the node.
             @return @c true if the node was found in the Registry. */
            bool
            getNodeInformation
                (const std::string &    nodeName,
                 uint32_t &             nodeAddress,
                 uint16_t &             nodePort)
                const;

        /*! @brief Get the set of nodes in the Registry.
             @return The set of nodes in the Registry. */
            StringSet
            getNodes
                (void)
                const;

            /*! @brief Check if a node is in the Registry.
             @param[in] nodeName The name of the node to be checked.
             @return @c true if the node was found and @c false if it was not found. */
            bool
            nodePresent
                (const std::string &    nodeName);

            /*! @brief Return the number of nodes in the Registry.
             @return The number of nodes in the Registry. */
            int
            numNodes
                (void)
                const;

            /*! @brief Remove a node from the Registry.
             @param[in] nodeName The name of the node to be removed.
             @return @c true if the node was removed and @c false if it was not removed. */
            bool
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

            /*! @brief A pointer to the database context. */
            Ptr(sqlite3)    _dbHandle;

            /*! @brief The owning context. */
            Ptr(ContextWithNetworking) _owner;

    }; // Registry

} // nImO

#endif // not defined(nImOregistry_H_)

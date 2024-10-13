//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOaddOutputChannelCallbackHandler.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for a callback function for adding output channels.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-10-13
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOaddOutputChannelCallbackHandler_H_))
# define nImOaddOutputChannelCallbackHandler_H_ /* Header guard */

# include <Contexts/nImOfilterContext.h>
# include <nImOcallbackFunction.h>

# if MAC_OR_LINUX_OR_BSD_
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
# endif // MAC_OR_LINUX_OR_BSD_
# include <mdns.hpp>
# if MAC_OR_LINUX_OR_BSD_
#  pragma GCC diagnostic pop
# endif // MAC_OR_LINUX_OR_BSD_

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a callback function for adding output channels. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide values that are used for handling callbacks for the application. */
    class AddOutputChannelCallbackHandler final : public nImO::CallbackFunction
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = CallbackFunction;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] theContext The filter context that is active.
             @param[in] basePath The base part of the channel name. */
            inline AddOutputChannelCallbackHandler
                (Ptr(nImO::FilterContext)   theContext,
                 const std::string &        basePath) :
                    inherited(), _context(theContext), _basePath(basePath)
            {
            }

            /*! @brief Stop accepting requests. */
            inline void
            disable
                (void)
            {
                _requestsAllowed = false;
            }

            /*! @brief Indicate that the service is ready to accept these requests.
             @param[in] nodeName The name of this node.
             @param[in] proxy The RegistryProxy to use.
             @param[in] dataType The expected data format. */
            inline void
            enable
                (const std::string &    nodeName,
                 nImO::SpRegistryProxy  proxy,
                 const std::string &    dataType)
            {
                _dataType = dataType;
                _nodeName = nodeName;
                _proxy = proxy;
                _requestsAllowed = true;
            }

            /*! @brief Return @c true if the callback is processing a request.
             @return @c true if the callback is processing a request. */
            inline bool
            isActive
                (void)
            {
                return _active;
            }

            /*! @brief Return @c true is a channel was added and clear the flag
             used to track when a channel is added.
             @return @c true if a channel was added. */
            inline bool
            wasAdded
                (void)
            {
                return _added.exchange(false);
            }

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Process an add output channel request.
             @return @c true on success. */
            bool
            operator()
                (void)
                override;

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The filter context that is active. */
            Ptr(nImO::FilterContext)    _context{nullptr};

            /*! @brief A flag to control when requests can be honoured. */
            std::atomic_bool    _requestsAllowed{false};

            /*! @brief The base part of the channel name. */
            std::string _basePath{};

            /*! @brief The RegistryProxy to use. */
            nImO::SpRegistryProxy   _proxy{};

            /*! @brief The name of this node. */
            std::string _nodeName{};

            /*! @brief The expected data type. */
            std::string _dataType{};

            /*! @brief @c true while the callback is executing. */
            std::atomic_bool    _active{false};

            /*! @brief @c true when a channel has been added. */
            std::atomic_bool    _added{false};

    }; // AddOutputChannelCallbackHandler

} // nImO

#endif // not defined(nImOaddOutputChannelCallbackHandler_H_)

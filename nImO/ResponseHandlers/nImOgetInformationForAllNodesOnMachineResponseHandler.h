//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for a functor used with the nImO request/response mechanism.
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
//  Created:    2023-04-25
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOgetInformationForAllNodesOnMachineResponseHandler_H_))
# define nImOgetInformationForAllNodesOnMachineResponseHandler_H_ /* Header guard */

# include <ResponseHandlers/nImOresponseHandler.h>

# include <nImOregistryTypes.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for a functor used with the %nImO request/response mechanism. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide a functor used with the %nImO request/response mechanism. */
    class InformationForAllNodesOnMachineResponseHandler final : public ResponseHandler
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = nImO::ResponseHandler;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] responseKey The expected response key. */
            InformationForAllNodesOnMachineResponseHandler
                (void);

            /*! @brief The destructor. */
            virtual
            ~InformationForAllNodesOnMachineResponseHandler
                (void);

            /*! @brief Handle the response, returning @c true if successful.
             @param[in] stuff The data included in the response. */
            virtual void
            doIt
                (const nImO::Array &    stuff)
                override;

            /*! @brief Return the received value.
             @return The received value. */
            NodeInfoVector
            result
                (void)
                const
            {
                return _result;
            }

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

            /*! @brief The received value. */
            NodeInfoVector    _result;

    }; // InformationForAllNodesOnMachineResponseHandler

} // nImO

#endif // not defined(nImOgetInformationForAllNodesOnMachineResponseHandler_H_)
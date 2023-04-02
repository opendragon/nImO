//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOrequestResponse.h
//
//  Project:    nImO
//
//  Contains:   The function declarations for the nImO request/response mechanism.
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
//  Created:    2023-03-25
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOrequestResponse_H_))
# define nImOrequestResponse_H_ /* Header guard */

# include <nImOcontextWithNetworking.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The function declarations for the %nImO request/response mechanism. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    class ContextWithMDNS;

    /*! @brief A class to provide functors used to process responses. */
    class ResponseHandler
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The destructor. */
            virtual
            ~ResponseHandler
                (void);

            /*! @brief The copy constructor.
            @param[in] other The object to be copied. */
            ResponseHandler
                (const ResponseHandler &  other) = delete;

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            ResponseHandler
                (ResponseHandler &&    other) = delete;

            /*! @brief Handle the response, returning @c true if successful.
             @param[in] stuff The data included in the response. */
            virtual void
            doIt
                (const Array &  stuff)
                const = 0;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            ResponseHandler &
            operator=
                (const ResponseHandler &    other) = delete;

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            ResponseHandler &
            operator=
                (ResponseHandler && other) = delete;

        protected :
            // Protected methods.

            /*! @brief The constructor.
             @param[in] responseKey The expected response key. */
            inline ResponseHandler
                (const std::string  responseKey) :
                    _responseKey(responseKey)
            {
            }

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

            /*! @brief The expected key in the response. */
            std::string _responseKey;

        private :
            // Private fields.

    }; // ResponseHandler

    /*! @brief Send a simple request with no expected results.
     @param[in] context The context in which the request is being made.
     @param[in] connection The connection to be used.
     @param[in] requestKey The request to be sent.
     @param[in] responseKey The expected response, which will have no data. */
    void
    SendRequestWithEmptyResponse
        (SpContextWithNetworking    context,
         Connection &               connection,
         const std::string          requestKey,
         const std::string          responseKey);

} // nImO

#endif // not defined(nImOrequestResponse_H_)

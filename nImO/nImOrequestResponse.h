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

# include <Contexts/nImOcontextWithNetworking.h>
# include <ResponseHandlers/nImOresponseHandler.h>
# include <nImOregistryTypes.h>

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

    /*! @brief Send a simple request with expected results and arguments.
     @param[in] context The context in which the request is being made.
     @param[in] connection The connection to be used.
     @param[in] handler The function to process the response.
     @param[in] requestKey The request to be sent.
     @param[in] responseKey The expected response, which will have no data.
     @return Whether the request succeeded or failed. */
    SuccessOrFailure
    SendRequestWithArgumentsAndNonEmptyResponse
        (SpContextWithNetworking    context,
         Connection &               connection,
         Ptr(ResponseHandler)       handler,
         Ptr(Array)                 arguments,
         const std::string &        requestKey,
         const std::string &        responseKey);

    /*! @brief Send a simple request with arguments and no expected results.
     @param[in] context The context in which the request is being made.
     @param[in] connection The connection to be used.
     @param[in] handler The function to process the response.
     @param[in] requestKey The request to be sent.
     @param[in] responseKey The expected response, which will have no data.
     @return Whether the request succeeded or failed. */
    inline SuccessOrFailure
    SendRequestWithArgumentsAndEmptyResponse
        (SpContextWithNetworking    context,
         Connection &               connection,
         Ptr(Array)                 arguments,
         const std::string &        requestKey,
         const std::string &        responseKey)
    {
        return SendRequestWithArgumentsAndNonEmptyResponse(context, connection, nullptr, arguments, requestKey, responseKey);
    }

    /*! @brief Send a simple request with no expected results and no arguments.
     @param[in] context The context in which the request is being made.
     @param[in] connection The connection to be used.
     @param[in] requestKey The request to be sent.
     @param[in] responseKey The expected response, which will have no data.
     @return Whether the request succeeded or failed. */
    inline SuccessOrFailure
    SendRequestWithNoArgumentsAndEmptyResponse
        (SpContextWithNetworking    context,
         Connection &               connection,
         const std::string &        requestKey,
         const std::string &        responseKey)
    {
        return SendRequestWithArgumentsAndNonEmptyResponse(context, connection, nullptr, nullptr, requestKey, responseKey);
    }

    /*! @brief Send a simple request with expected results and no arguments.
     @param[in] context The context in which the request is being made.
     @param[in] connection The connection to be used.
     @param[in] handler The function to process the response.
     @param[in] requestKey The request to be sent.
     @param[in] responseKey The expected response, which will have no data.
     @return Whether the request succeeded or failed. */
    inline SuccessOrFailure
    SendRequestWithNoArgumentsAndNonEmptyResponse
        (SpContextWithNetworking    context,
         Connection &               connection,
         Ptr(ResponseHandler)       handler,
         const std::string &        requestKey,
         const std::string &        responseKey)
    {
        return SendRequestWithArgumentsAndNonEmptyResponse(context, connection, handler, nullptr, requestKey, responseKey);
    }

} // nImO

#endif // not defined(nImOrequestResponse_H_)

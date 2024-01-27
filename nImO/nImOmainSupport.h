//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOmainSupport.h
//
//  Project:    nImO
//
//  Contains:   The function and variable declarations for nImO applications.
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
//  Created:    2023-03-22
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOmainSupport_H_))
# define nImOmainSupport_H_ /* Header guard */

# include <Contexts/nImOutilityContext.h>
# include <nImOcallbackFunction.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The function and variable declarations for %nImO applications. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    class RegistryProxy;

    /*! @brief The signal handler to catch requests to stop the application.
     @param[in] signal The signal being handled. */
    void
    CatchSignal
        (const int  signal);

    /*! @brief Perform the operations involved with closing a Connection.
     @param[in] context The context used with the Connection.
     @param[in] nodeName The name of the node with the Connection.
     @param[in] proxy The Registry proxy to use.
     @param[in] path The path used with the Connection.
     @param[in] isFrom @c true if this is the source end of the Connection.
     @param[in/out] reported @c true if a failure has been reported.
     @return @c true if the Connection exists. */
    bool
    CloseConnection
        (SpContextWithNetworking    context,
         const std::string &        nodeName,
         RegistryProxy &            proxy,
         const std::string &        path,
         const bool                 isFrom,
         bool &                     reported);

    /* @brief Return the path to the executable.
     @return The path to the executable. */
    std::string
    GetPathToExecutable
        (void);

    /* @brief Generate a platform-specific representation of a command-line option.
     @param[in] shortForm The short form of the option, usually a single character.
     @param[in] longForm The longer form of the option.
     @return A platform-specific representation of the command-line option. */
    std::string
    MakeOption
        (const std::string &    shortForm,
         const std::string &    longForm = ""s);

    /*! @brief Set the function object to be invoked when a system break signal is received.
     @param[in] sigHObject The function object to be invoked. */
    void
    SetSpecialBreakObject
        (Ptr(CallbackFunction)    sigObject);

    /*! @brief Remove a connection between two channels.
     @param[in] ourContext A context to use for requests.
     @param[in] fromConnection The sender command channel.
     @param[in] fromNode The sender node name.
     @param[in] fromPath The sender channel path.
     @param[in] toConnection The receiver command channel.
     @param[in] toNode The receiver node name.
     @param[in] toPath The receiver channel path. */
    void
    StopConnection
        (SpContextWithNetworking    ourContext,
         Connection &               fromConnection,
         const std::string &        fromNode,
         const std::string &        fromPath,
         Connection &               toConnection,
         const std::string &        toNode,
         const std::string &        toPath);

    /*! @brief Set to @c false when a SIGINT occurs. */
    extern std::atomic_bool gKeepRunning;

    /*! @brief Set to @c true when there's a pending shutdown request. */
    extern std::atomic_bool gPendingStop;

} // nImO

#endif // not defined(nImOmainSupport_H_)

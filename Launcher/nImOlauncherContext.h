//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Launcher/nImOlauncherContext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the nImO Launcher execution context.
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
//  Created:    2024-01-15
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOlauncherContext_H_))
# define nImOlauncherContext_H_ /* Header guard */

# include <Contexts/nImOserviceContext.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the Launcher %nImO execution context. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    class LauncherContext; // needed due to circular references.

    /*! @brief A class to provide support for a Launcher application. */
    class LauncherContext final : public ServiceContext
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = ServiceContext;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] argc The number of arguments in 'argv'.
             @param[in] argv The command-line arguments provided to the application.
             @param[in] executable The name of the executing program.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            LauncherContext
                (const int              argc,
                 Ptr(Ptr(char))         argv,
                 const std::string &    executableName,
                 const std::string &    tagForLogging = ""s,
                 const bool             logging = false,
                 const std::string &    nodeName = ""s);

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

    }; // LauncherContext

    /*! @brief Add the standard command handlers for an LauncherContext.
     @param[in] context The Context to be updated.
     @param[in] shutdownCallback A callback to be used when a shutdown command is processed. */
    void
    AddLauncherHandlers
        (SpLauncherContext      context,
         Ptr(CallbackFunction)  shutdownCallback = nullptr);

} // nImO

#endif // not defined(nImOlauncherContext_H_)

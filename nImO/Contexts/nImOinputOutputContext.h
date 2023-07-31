//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOinputOutputContext.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the nImO 'inputOutput' execution context.
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
//  Created:    2023-04-12
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOinputOutputContext_H_))
# define nImOinputOutputContext_H_ /* Header guard */

# include <Contexts/nImOserviceContext.h>

# include <nImOinChannel.h>
# include <nImOoutChannel.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the 'inputOutput' %nImO execution context. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A holder for a shared pointer to an input channel. */
    using SpInChannel = std::shared_ptr<InChannel>;

    /*! @brief A holder for a shared pointer to an output channel. */
    using SpOutChannel = std::shared_ptr<OutChannel>;

    /*! @brief An array of input channels. */
    typedef std::vector<SpInChannel>    InChannelVector;

    /*! @brief An array of output channels. */
    typedef std::vector<SpOutChannel>   OutChannelVector;

    /*! @brief A class to provide support for an 'inputOutput' application. */
    class InputOutputContext : public ServiceContext
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

            /*! @brief The destructor. */
            virtual
            ~InputOutputContext
                (void)
                override;

        protected :
            // Protected methods.

            /*! @brief The constructor.
             @param[in] argc The number of arguments in 'argv'.
             @param[in] argv The command-line arguments provided to the application.
             @param[in] executable The name of the executing program.
             @param[in] tagForLogging The symbolic name for the current process.
             @param[in] logging @c true if the executing program is to be logged.
             @param[in] nodeName The @nImO-visible name of the executing program. */
            InputOutputContext
                (const int              argc,
                 Ptr(Ptr(char))         argv,
                 const std::string &    executableName,
                 const std::string &    tagForLogging = "",
                 const bool             logging = false,
                 const std::string &    nodeName = "");

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The input channels for the service. */
            InChannelVector _inputChannels{};

            /*! @brief The output channels for the service. */
            OutChannelVector    _outputChannels{};

    }; // InputOutputContext

} // nImO

#endif // not defined(nImOinputOutputContext_H_)

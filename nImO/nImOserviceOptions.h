//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOserviceOptions.h
//
//  Project:    nImO
//
//  Contains:   The function and class declarations for the service command-line options used with nImO.
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
//  Created:    2023-03-11
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOserviceOptions_H_))
# define nImOserviceOptions_H_ /* Header guard */

# include <nImOstandardOptions.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The function and class declarations for the service command-line options used with %nImO. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief Convenience structure for standard options. */
    struct ServiceOptions final : StandardOptions
    {
        /*! @brief The struct that this struct is derived from. */
        using inherited = StandardOptions;

        /*! @brief The base name for channels. */
        std::string _base{};

        /*! @brief The data type for input channels. */
        std::string _inType{};

        /*! @brief The node name set by a command-line option. */
        std::string _node{};

        /*! @brief The data type for output channels. */
        std::string _outType{};

        /*! @brief The tag modifier set by a command-line option. */
        std::string _tag{};

        /*! @brief @c true if the main service loop delays until the connection(s) are made. */
        bool    _waitForConnections{false};

        /*! @brief The constructor. */
        ServiceOptions
            (void) :
                inherited{}
        {
        }

    }; // ServiceOptions

    /*! @brief Process the standard options for service executables.
     The option '-a' / '--args' specifies the arguments to the executable.
     The option '-b' / '--base' specifies the base name of the channels for the service.
     The option '-c' / '--config' specifies an alternative configuration file to use.
     The option '-d' / '--describe' displays the type of the executable, the available options and the description of the executable and returns @c false.
     The option '-e' / '--expanded' increases the amount of detail presented.
     The option '-h' / '--help' displays the list of optional parameters and arguments and returns @c false.
     The option '-i' / '--intype' specifies the data type for input channels.
     The option '-l' / '--log' specifies that the executable is to be logged.
     The option '-o / '--outtype' specifies the data type for input channels.
     The option '-t' / '--tag' specifies the tag modifier, which is applied to the name of the service.
     The option '-v' / '--version' displays the version and copyright information and returns @c false.
     @param[in] argc The number of arguments in 'argv'.
     @param[in] argv The arguments to be used with the service.
     @param[in] argumentDescriptions Descriptions of the arguments to the service.
     @param[in] serviceDescription A description of the service.
     @param[in] serviceExample An example of invoking the service.
     @param[in] year The copyright year for the calling application.
     @param[in] copyrightHolder The name of the entity holding the copyright to the utility.
     @param[out] optionValues Values set by command-line options.
     @param[in] skipOptions The command-line options to be skipped.
     @param[in] multipleInputs @c true if multiple inputs are supported.
     @param[in] multipleOutputs @c true if multiple outputs are supported.
     @param[in] arguments If non-@c NULL, returns the arguments for the service.
     @return @c true if the service should continue and @c false if it should leave. */
    bool
    ProcessServiceOptions
        (const int              argc,
         Ptr(Ptr(char))         argv,
         DescriptorVector &     argumentDescriptions,
         const std::string &    serviceDescription,
         const std::string &    serviceExample,
         const int              year,
         const std::string &    copyrightHolder,
         ServiceOptions &       optionValues,
         const OptionsMask      skipOptions,
         const bool             multipleInputs = false,
         const bool             multipleOutputs = false,
         Ptr(StdStringVector)   arguments = nullptr);

} // nImO

#endif // not defined(nImOserviceOptions_H_)

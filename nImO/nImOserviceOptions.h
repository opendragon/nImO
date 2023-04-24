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
    struct ServiceOptions : StandardOptions
    {
        /*! @brief The struct that this struct is derived from. */
        using inherited = StandardOptions;

        /*! @brief The address tag set by a command-line option. */
        std::string _tag;

        /*! @brief The node name set by a command-line option. */
        std::string _node;

        /*! @brief The constructor. */
        ServiceOptions
            (void) :
                inherited()
        {
        }

    }; // ServiceOptions

    /*! @brief Process the standard options for service executables.
    The option '-c' / '--conf' specifies an alternative configuration file to use.
    The option '-d' / '--detail' increases the amount of detail presented.
    The option '-e' / '--endpoint' specifies the endpoint name to be used.
    The option '-h' / '--help' displays the list of optional parameters and arguments and
    returns @c false.
    The option '-i' / '--info' displays the type of the executable, the available options and
    the description of the executable and returns @c false.
    The option '-l' / '--log' specifies that the executable is to be logged.
    The option '-t' / '--tag' specifies the tag modifier, which is applied to the name of the
    channel, if the name was not specified. It is also applied to the service name as a suffix.
    The option '-v' / '--vers' displays the version and copyright information and returns
    @c false.
    @param[in] argc The number of arguments in 'argv'.
    @param[in] argv The arguments to be used with the service.
    @param[in] argumentDescriptions Descriptions of the arguments to the service.
    @param[in] serviceDescription A description of the service.
    @param[in] matchingCriteria The criteria used to locate the service that the service
    requires to be running.
    @param[in] year The copyright year for the calling application.
    @param[in] copyrightHolder The name of the entity holding the copyright to the utility.
    @param[out] optionValues Values set by command-line options.
    @param[in] skipOptions The command-line options to be skipped.
    @param[in] arguments If non-@c NULL, returns the arguments for the service.
    @return @c true if the service should continue and @c false if it should leave. */
    bool
    ProcessServiceOptions
        (const int              argc,
         Ptr(Ptr(char))         argv,
         DescriptorVector &     argumentDescriptions,
         const std::string &    serviceDescription,
         const std::string &    matchingCriteria,
         const int              year,
         CPtr(char)             copyrightHolder,
         ServiceOptions &       optionValues,
         const OptionsMask      skipOptions,
         Ptr(StringVector)      arguments = nullptr);

} // nImO

#endif // not defined(nImOserviceOptions_H_)

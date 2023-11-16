//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOstandardOptions.h
//
//  Project:    nImO
//
//  Contains:   The function and class declarations for the standard command-line options used with nImO.
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

#if (! defined(nImOstandardOptions_H_))
# define nImOstandardOptions_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The function and class declarations for the standard command-line options used with %nImO. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{

    /*! @brief The command-line options to skip.
     Note that the 'help' and 'version' options are always present. */
    enum OptionsMask
    {
        /*! @brief Skip no options. */
        kSkipNone               = 0x0000,

        /*! @brief Skip the 'args' option. */
        kSkipArgsOption         = 0x0001,

        /*! @brief Skip the 'base' option. */
        kSkipBaseOption         = 0x0002,

        /*! @brief Skip the 'configFile' option. */
        kSkipConfigFileOption   = 0x0004,

        /*! @brief Skip the 'describe' option. */
        kSkipDescribeOption     = 0x0008,

        /*! @brief Skip the 'expanded' option. */
        kSkipExpandedOption     = 0x0010,

        /*! @brief Skip the 'flavours' option. */
        kSkipFlavoursOption     = 0x0020,

        /*! @brief Skip the 'inType' option. */
        kSkipInTypeOption       = 0x0040,

        /*! @brief Skip the 'logging' option. */
        kSkipLoggingOption      = 0x0080,

        /*! @brief Skip the 'machine' option. */
        kSkipMachineOption      = 0x0100,

        /*! @brief Skip the 'node' option. */
        kSkipNodeOption         = 0x0200,

        /*! @brief Skip the 'outType' option. */
        kSkipOutTypeOption      = 0x0400,

        /*! @brief Skip the 'tag' option. */
        kSkipTagOption          = 0x0800,

        /*! @brief Skip all the options. */
        kSkipAllOptions         = 0xFFFF
    }; // OptionsMask

    /*! @brief The format for the output from command-line tools. */
    enum class OutputFlavour
    {
        /*! @brief Normal output with no special processing. */
        kFlavourNormal,

        /*! @brief Output in JSON format. Tabs and newlines are replaced with spaces. */
        kFlavourJSON,

        /*! @brief Output in tab-delimited format. Tabs and newlines are replaced with
         spaces. */
        kFlavourTabs,

        /*! @brief The output format is unknown. */
        kFlavourUnknown

    }; // OutputFlavour

    UnaryAndBinaryOperators(OptionsMask)

    /*! @brief Convenience structure for standard options. */
    struct StandardOptions
{
        /*! @brief The configuration file path set by a command-line option. */
        std::string _configFilePath{};

        /*! @brief @c true is a command-line option requested more details. */
        bool    _expanded{false};

        /*! @brief The flavour set by a command-line option. */
        OutputFlavour   _flavour{OutputFlavour::kFlavourNormal};

        /*! @brief @c true if a command-line option enabled logging. */
        bool    _logging{false};

        /*! @brief The machine name set by a command-line option. */
        std::string _machine{};

        /*! @brief The constructor.
         @param[in] loggingOnByDefault @c true if logging should be enabled. */
        StandardOptions
            (const bool loggingOnByDefault = false) :
                _logging{loggingOnByDefault}
        {
        }

    }; // StandardOptions

    /*! @brief Get a value associated with the provided key in the configuration data.
     @param[in] key The key took look up in the configuration data.
     @return The associated value if found, or 'empty'. */
    boost::optional<SpValue>
    GetConfiguredValue
        (const std::string &    key);

    /*! @brief Load configuration data into memory.
     @param[in] configFilePath The file system path to the configuration file. */
    void
    LoadConfiguration
        (const std::string &    configFilePath);

    /*! @brief Process the standard options for utility executables.
     The option '-c' / '--config' specifies an alternative configuration file to use.
     The option '-d' / '--describe' displays the type of the executable and the description of the executable and returns @c false.
     The option '-e' / '--expanded' increases the amount of detail presented.
     The option '-h' / '--help' displays the list of optional parameters and arguments and returns @c false.
     The option '-j' / '--json' specifies that output is to be in JSON format.
     The option '-l' / '--log' specifies that the executable is to be logged.
     The option '-m'/'--machine' specifies the machine to be referenced.
     The option '-t' / '--tabs' specifies that output is to be in tab-delimited format.
     The option '-v' / '--version' displays the version and copyright information and returns @c false.
     @param[in] argc The number of arguments in 'argv'.
     @param[in] argv The arguments to be used with the utility.
     @param[in,out] argumentDescriptions Descriptions of the arguments to the application.
     @param[in] utilityDescription A description of the utility.
     @param[in] utilityExample An example of invoking the utility.
     @param[in] year The copyright year for the calling application.
     @param[in] copyrightHolder The name of the entity holding the copyright to the utility.
     @param[out] optionValues Values set by command-line options.
     @param[in] helper A function to call when -h is requested, to provide more details.
     @param[in] optionsToIgnore which command-line options are to be ignored..
     @param[in] arguments If non-@c nullptr, returns the arguments for the utility.
     @return @c true if the program should continue and @c false if it should leave. */
    bool
    ProcessStandardOptions
        (const int              argc,
         Ptr(Ptr(char))         argv,
         DescriptorVector &     argumentDescriptions,
         const std::string &    utilityDescription,
         const std::string &    utilityExample,
         const int              year,
         const std::string &    copyrightHolder,
         StandardOptions &      optionValues,
         HelpFunction           helper = nullptr,
         const OptionsMask      optionsToIgnore = kSkipNone,
         Ptr(StringVector)      arguments = nullptr);

} // nImO

#endif // not defined(nImOstandardOptions_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImObaseArgumentDescriptor.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for the minimal functionality required to represent a
//              command-line argument.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2015 by H Plus Technologies Ltd. and Simon Fraser University.
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
//  Created:    2015-05-15
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImObaseArgumentDescriptor_HPP_))
# define nImObaseArgumentDescriptor_HPP_ /* Header guard */

# include <nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wnon-virtual-dtor"
# endif // defined(__APPLE__)
# if (! MAC_OR_LINUX_)
#  pragma warning(push)
#  pragma warning(disable: 4512)
# endif // ! MAC_OR_LINUX_
//# include <optionparser.hpp>
# include "optionparser.hpp"
# if (! MAC_OR_LINUX_)
#  pragma warning(pop)
# endif // ! MAC_OR_LINUX_
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the minimal functionality required to represent a command-line
 argument. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief The mode of an argument. */
    enum class ArgumentMode : uint8_t
    {
        /*! @brief The argument is required. */
        Required = 0x00,

        /*! @brief The argument is optional. */
        Optional = 0x01,

        /*! @brief The argument is modifiable. */
        Modifiable = 0x02,

        /*! @brief The argument is a password (not displayable). */
        Password = 0x04,

        /*! @brief The argument is both required and modifiable. */
        RequiredModifiable = (Required | Modifiable),

        /*! @brief The argument is both optional and modifiable. */
        OptionalModifiable = (Optional | Modifiable),

        /*! @brief The argument is both required and modifiable. */
        RequiredPassword = (Required | Password),

        /*! @brief The argument is both optional and modifiable. */
        OptionalPassword = (Optional | Password),

        /*! @brief A mask for the available flags. */
        Mask = (Optional | Modifiable | Password),

        /*! @brief The mode of the argument is undefined. */
        Unknown = 0x00FF

    }; // ArgumentMode

    /*! @brief A holder for a shared pointer to a BaseArgumentDescriptor. */
    using SpBaseArgumentDescriptor = std::shared_ptr<BaseArgumentDescriptor>;

    /*! @brief A holder for a non-shared pointer to a BaseArgumentDescriptor. */
    using UpBaseArgumentDescriptor = std::unique_ptr<BaseArgumentDescriptor>;

    /*! @brief A holder for a weak pointer to a BaseArgumentDescriptor. */
    using WpBaseArgumentDescriptor = std::weak_ptr<BaseArgumentDescriptor>;

    /*! @brief An argument description.

     The external representation of an argument description is:

     argFormat ::= argName sep argMode sep typeTagAndInfo sep default_value sep
                    text_description_for_label;

     sep ::= ':';

     argMode ::= numeric value of mode;

     default_value ::= delimiter text delimiter;
     # use matching pairs of |, <>, (), {}, [], whichever is not present in the text

     where typeTagAndInfo is described with each derived class.
     The following enumerates the standard type tags:

     'A' => address

     'B' => boolean

     'C' => channel

     'D' => double

     'E' => extra (a placeholder for zero or more trailing arguments)

     'F' => file path

     'I' => integer

     'L' => strings (a list of strings)
     
     'P' => port number

     'S' => string */
    class BaseArgumentDescriptor
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

    public :
        // Public methods.

        /*! @brief The constructor.
         @param[in] argName The name of the command-line argument.
         @param[in] argDescription A description of the command-line argument.
         @param[in] argMode The mode of the command-line argument. */
        BaseArgumentDescriptor
            (const std::string &    argName,
             const std::string &    argDescription,
             const ArgumentMode     argMode);

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        BaseArgumentDescriptor
            (const BaseArgumentDescriptor & other);

        /*! @brief The destructor. */
        virtual
        ~BaseArgumentDescriptor
            (void);

        /*! @brief Return the description of the command-line argument.
         @return The description of the command-line argument. */
        inline const std::string &
        argumentDescription
            (void)
            const
        {
            return _argDescription;
        } // argumentDescription

        /*! @brief Return the mode of the command-line argument.
         @return The mode of the command-line argument. */
        inline ArgumentMode
        argumentMode
            (void)
            const
        {
            return _argMode;
        } // argumentMode

        /*! @brief Return the name of the command-line argument.
         @return The name of the command-line argument. */
        inline const std::string &
        argumentName
            (void)
            const
        {
            return _argName;
        } // argumentName

        /*! @brief Return a copy of the descriptor, with only non-pointer types duplicated.
         @return A copy of the descriptor, with only non-pointer types duplicated. */
        virtual SpBaseArgumentDescriptor
        clone
            (void)
            const = 0;

        /*! @brief Return the default value.
         @return The default value. */
        virtual std::string
        getDefaultValue
            (void) = 0;

        /*! @brief Return the default value as a human-readable string.
         @return The default value as a human-readable string. */
        virtual std::string
        getPrintableDefaultValue
            (void) = 0;

        /*! @brief Return the processed value.
         @return The processed value. */
        virtual std::string
        getProcessedValue
            (void) = 0;

        /*! @brief Return @c true if the argument is a placeholder for zero or more trailing
         arguments.
         @return @c true if the argument is a placeholder for zero of more trailing arguments
         and @c false otherwise. */
        virtual bool
        isExtra
            (void)
            const;

        /*! @brief Return @c true if the argument is for file paths and @c false otherwise.
         @param[out] isForOutput Set to @c true if the argument is for output files and @c false
         otherwise.
         @return @c true if the argument is for file paths and @c false otherwise. */
        virtual bool
        isForFiles
            (bool & isForOutput)
            const;

        /*! @brief Return @c true if the argument is for Logical arguments.
         @return @c true if the argument is for Logical arguments and @c false otherwise. */
        virtual bool
        isLogical
            (void)
            const;

        /*! @brief Return @c true if the argument is modifiable and @c false otherwise.
         @return @c true if the argument is modifiable and @c false otherwise. */
        inline bool
        isModifiable
            (void)
            const
        {
            return ((ArgumentMode::Unknown != _argMode) && (0 != (toUType(_argMode) & toUType(ArgumentMode::Modifiable))));
        } // isModifiable

        /*! @brief Return @c true if the argument is optional and @c false otherwise.
         @return @c true if the argument is optional and @c false otherwise. */
        inline bool
        isOptional
            (void)
            const
        {
            return ((ArgumentMode::Unknown != _argMode) && (0 != (toUType(_argMode) & toUType(ArgumentMode::Optional))));
        } // isOptional

        /*! @brief Return @c true if the argument is a password and @c false otherwise.
         @return @c true if the argument is a password and @c false otherwise. */
        inline bool
        isPassword
            (void)
            const
        {
            return ((ArgumentMode::Unknown != _argMode) && (0 != (toUType(_argMode) & toUType(ArgumentMode::Password))));
        } // isPassword

        /*! @brief Return @c true if the argument is required and @c false otherwise.
         @return @c true if the argument is required and @c false otherwise. */
        inline bool
        isRequired
            (void)
            const
        {
            return ((ArgumentMode::Unknown != _argMode) && (0 == (toUType(_argMode) & toUType(ArgumentMode::Optional))));
        } // isRequired

        /*! @brief Return @c true if the argument is valid and @c false otherwise.
         @return @c true if the argument is valid and @c false otherwise. */
        inline bool
        isValid
            (void)
            const
        {
            return _valid;
        } // isValid

        /*! @brief The assignment operator.
         @tparam Type The type of value being assigned.
         @param[in] other The object to be copied.
         @return The updated object. */
        template
            <typename Type>
        Type &
        operator =
            (const Type &   other)
        {
            Type    temp(other);

            swap(temp);
            return *this;
        } // operator =
        
        /*! @brief Set the associated variable to the default value. */
        virtual void
        setToDefaultValue
            (void) = 0;

        /*! @brief Convert to a printable representation.
         @return A printable representation of the descriptor. */
        virtual std::string
        toString
            (void) = 0;

        /*! @brief Check an input value against the constraints of the descriptor.
         @param[in] value The value to be checked.
         @return @c true if the value is within the domain of the descriptor and @c false
         otherwise. */
        virtual bool
        validate
            (const std::string &    value) = 0;

    protected :
        // Protected methods.

        /*! @brief Find a character that is not present in the input, to use as a delimiter.
         @param[in] inString The string to be analyzed.
         @return @c A character not present in the string that can be used as a delimiter for
         the string. */
        static char
        identifyDelimiter
            (const std::string &    valueToCheck);

        /*! @brief Partition a string that is in 'arguments' format into a sequence of strings.
         @param[in] inString The string to be partitioned.
         @param[in] indexOfDefaultValue The position in the input string where the default value
         will appear. The default value uses a secondary delimiter.
         @param[out] result The partitioned string.
         @param[in] indexOfListValue The position in the input string where a list value will
         appear. A list value uses the field separator internally and a secondary delimiter.
         @return @c true if the correct number of fields appear within the input string and
         @c false otherwise. */
        static bool
        partitionString
            (const std::string &    inString,
             const size_t           indexOfDefaultValue,
             StringVector &         result,
             const size_t           indexOfListValue = 0);

        /*! @brief Returns a string that contains a printable representation of the standard
         prefix fields for a command-line argument.
         @param[in] tagForField The tag value to use for the field.
         @return A string that contains a printable representation of the standard prefix
         fields for a command-line argument. */
        std::string
        prefixFields
            (const std::string &    tagForField)
            const;

        /*! @brief Returns a string that contains a printable representation of the standard
         fields for a command-line argument.
         @param[in] defaultToUse The string to put in the printable representation for the default
         value.
         @return A string that contains a printable representation of the standard fields for
         a command-line argument. */
        std::string
        suffixFields
            (const std::string &    defaultToUse);

        /*! @brief Exchanges the contents of the object with those of other.
         @param[in,out] other The object to be swapped with. */
        void
        swap
            (BaseArgumentDescriptor &   other);
        
    private :
        // Private methods.

    public :
        // Public fields.

    protected :
        // Protected fields.

        /*! @brief The separator string to use when converting to a string. */
        static std::string _parameterSeparator;

        /*! @brief @c true if the argument was valid and @c false otherwise. */
        bool _valid;

    private :
        // Private fields.

        /*! @brief The description of the command-line argument for the adapter. */
        std::string _argDescription;

        /*! @brief The name of the command-line argument. */
        std::string _argName;

        /*! @brief The mode of the command-line argument. */
        ArgumentMode _argMode;

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
        /*! @brief Filler to pad to alignment boundary */
        char _filler[7];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

    }; // BaseArgumentDescriptor

    /*! @brief A sequence of argument descriptors. */
    using DescriptorVector = std::vector<BaseArgumentDescriptor *>;

    /*! @brief Generate the standard 'argument list' description from an argument sequence.
     @param[in] arguments The argument sequence.
     @return A string containing the standard 'argument list' representation of the argument
     sequence. */
    std::string
    ArgumentsToArgString
        (const DescriptorVector &   arguments);

    /*! @brief Generate the standard 'argument description' from an argument sequence.
     @param[in] arguments The argument sequence.
     @param[out] output The generated argument descriptions.
     @param[in] minSpace The number of characters between the argument names and their
     descriptions. */
    void
    ArgumentsToDescriptionArray
        (const DescriptorVector &   arguments,
         StringVector &             output,
         const size_t               minSpace = 1);

    /*! @brief Return the resulting argument values.
     @param[in] arguments The argument sequence.
     @param[in] sep The separator string between the argument values.
     @return The argument values, separated by 'sep'. */
    std::string
    CombineArguments
        (const DescriptorVector &   arguments,
         const std::string &        sep);

    /*! @brief Convert a string in '--args' format into an argument description.
     @param[in] inString The string to be analyzed.
     @return A newly allocated argument descriptor or @c nullptr if the string is not valid. */
    SpBaseArgumentDescriptor
    ConvertStringToArgument
        (const std::string &    inString);

    /*! @brief Return the mode corresponding to a string.
     @param[in] modeString The mode value as a string.
     @return The mode corresponding to a string. */
    ArgumentMode
    ModeFromString
        (const std::string &    modeString);

    /*! @brief Update the arguments data from the parsed argument list.
     @param[in] arguments The argument sequence.
     @param[out] parseResult The parsed argument list.
     @param[out] badArgs The list of invalid or missing arguments.
     @return @c true if the parsed argument list matches the argument sequence and @c false
     otherwise. */
    bool
    ProcessArguments
        (const DescriptorVector &   arguments,
         Option_::Parser &          parseResult,
         std::string &              badArgs);

    /*! @brief Prompt the user for the value of each of the arguments.
     @param[in] arguments The argument sequence.
     @return @c true if all arguments are valid and @c false otherwise. */
    bool
    PromptForValues
        (const DescriptorVector &   arguments);

} // nImO

#endif // ! defined(nImObaseArgumentDescriptor_HPP_)

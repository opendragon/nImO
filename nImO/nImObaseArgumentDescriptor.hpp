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

# include <nImO/nImOcommon.hpp>
# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wnon-virtual-dtor"
# endif // defined(__APPLE__)
# if (! MAC_OR_LINUX_)
#  pragma warning(push)
#  pragma warning(disable: 4512)
# endif // ! MAC_OR_LINUX_
# include <nImO/optionparser.hpp>
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

#if 0
/*! @brief Declare the addValueToBottle method, which takes a single argument, container, and adds
 the processed value to the container. */
# define DECLARE_ADDVALUETOBOTTLE_ \
    virtual void\
    addValueToBottle(yarp::os::Bottle & container)
#endif//0

/*! @brief Declare the clone method, which returns a copy of the descriptor, with only
 non-pointer fields duplicated. */
# define DECLARE_CLONE_ \
    virtual BaseArgumentDescriptor *\
    clone(void)

/*! @brief Declare the getDefaultValue method, which returns the default value of the descriptor. */
# define DECLARE_GETDEFAULTVALUE_ \
    virtual std::string\
    getDefaultValue(void)

/*! @brief Declare the getProcessedValue method, which returns the processed value for the
 descriptor. */
# define DECLARE_GETPROCESSEDVALUE_ \
    virtual std::string\
    getProcessedValue(void)

/*! @brief Declare the isBoolean method, which returns @c true if the descriptor is for Boolean
 arguments and @c false otherwise. */
# define DECLARE_ISBOOLEAN_ \
    virtual bool\
    isBoolean(void)\
    const

/*! @brief Declare the isExtra method, which returns @c true if the descriptor is a placeholder for
 zero or more trailing arguments and @c false otherwise. */
# define DECLARE_ISEXTRA_ \
    virtual bool\
    isExtra(void)\
    const

/*! @brief Declare the isForFiles method, which returns @c true if the descriptor is for file paths
 and @c false otherwise.
 The argument isForOutput is set to @c true is the descriptor is for output files and @c false
 otherwise. */
# define DECLARE_ISFORFILES_ \
    virtual bool\
    isForFiles(bool & isForOutput)\
    const

/*! @brief Declare the setToDefaultValue method, which sets the descriptor to its default value. */
# define DECLARE_SETTODEFAULTVALUE_ \
    virtual void\
    setToDefaultValue(void)

/*! @brief Declare the toString method, which returns a printable representation of the
 descriptor. */
# define DECLARE_TOSTRING_ \
    virtual std::string\
    toString(void)

/*! @brief Declare the validate method, which takes a single argument, value, and checks it against
 the constraints of the descriptor.
 The method returns @c true if the argument is within the domain of the descriptor and @c false
 otherwise. */
# define DECLARE_VALIDATE_ \
    virtual bool\
    validate(const std::string & value)

#if 0
/*! @brief Define the addValueToBottle method. */
# define DEFINE_ADDVALUETOBOTTLE_(class_) \
    void\
    class_::addValueToBottle(yarp::os::Bottle & container)
#endif//0

/*! @brief Define the clone method. */
# define DEFINE_CLONE_(class_) \
    BaseArgumentDescriptor *\
    class_::clone(void)

/*! @brief Define the getDefaultValue method. */
# define DEFINE_GETDEFAULTVALUE_(class_) \
    std::string\
    class_::getDefaultValue(void)

/*! @brief Define the getProcessedValue method. */
# define DEFINE_GETPROCESSEDVALUE_(class_) \
    std::string\
    class_::getProcessedValue(void)

/*! @brief Define the setToDefaultValue method. */
# define DEFINE_SETTODEFAULTVALUE_(class_) \
    void\
    class_::setToDefaultValue(void)

/*! @brief Define the toString method. */
# define DEFINE_TOSTRING_(class_) \
    std::string\
    class_::toString(void)

/*! @brief Define the validate method. */
# define DEFINE_VALIDATE_(class_) \
    bool\
    class_::validate(const std::string & value)

namespace nImO
{
    /*! @brief The mode of an argument. */
    enum ArgumentMode
    {
        /*! @brief The argument is required. */
        kArgModeRequired = 0x00,

        /*! @brief The argument is optional. */
        kArgModeOptional = 0x01,

        /*! @brief The argument is modifiable. */
        kArgModeModifiable = 0x02,

        /*! @brief The argument is a password (not displayable). */
        kArgModePassword = 0x04,

        /*! @brief The argument is both required and modifiable. */
        kArgModeRequiredModifiable = (kArgModeRequired | kArgModeModifiable),

        /*! @brief The argument is both optional and modifiable. */
        kArgModeOptionalModifiable = (kArgModeOptional | kArgModeModifiable),

        /*! @brief The argument is both required and modifiable. */
        kArgModeRequiredPassword = (kArgModeRequired | kArgModePassword),

        /*! @brief The argument is both optional and modifiable. */
        kArgModeOptionalPassword = (kArgModeOptional | kArgModePassword),

        /*! @brief A mask for the available flags. */
        kArgModeMask = (kArgModeOptional | kArgModeModifiable | kArgModePassword),

        /*! @brief The mode of the argument is undefined. */
        kArgModeUnknown = -1

    }; // ArgumentMode

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

     'P' => port number

     'S' => string */
    class BaseArgumentDescriptor
    {
    public :

    protected :

    private :

    public :

        /*! @brief The constructor.
         @param argName The name of the command-line argument.
         @param argDescription A description of the command-line argument.
         @param argMode The mode of the command-line argument. */
        BaseArgumentDescriptor(const std::string & argName,
                               const std::string & argDescription,
                               const ArgumentMode  argMode);

        /*! @brief The destructor. */
        virtual
        ~BaseArgumentDescriptor(void);

#if 0
        /*! @fn virtual void
                addValueToBottle(yarp::os::Bottle & container)
         @brief Add the processed value to a bottle.
         @param container The bottle to be modified. */
        DECLARE_ADDVALUETOBOTTLE_ = 0;
#endif//0

        /*! @brief Return the description of the command-line argument.
         @returns The description of the command-line argument. */
        inline const std::string &
        argumentDescription(void)
        const
        {
            return _argDescription;
        } // argumentDescription

        /*! @brief Return the mode of the command-line argument.
         @returns The mode of the command-line argument. */
        inline ArgumentMode
        argumentMode(void)
        const
        {
            return _argMode;
        } // argumentMode

        /*! @brief Return the name of the command-line argument.
         @returns The name of the command-line argument. */
        inline const std::string &
        argumentName(void)
        const
        {
            return _argName;
        } // argumentName

        /*! @fn virtual BaseArgumentDescriptor *
                clone(void)
         @brief Return a copy of the descriptor, with only non-pointer types duplicated.
         @returns A copy of the descriptor, with only non-pointer types duplicated. */
        DECLARE_CLONE_ = 0;

        /*! @fn virtual std::string
                getDefaultValue(void)
         @brief Return the default value.
         @returns The default value. */
        DECLARE_GETDEFAULTVALUE_ = 0;

        /*! @fn virtual std::string
                getProcessedValue(void)
         @brief Return the processed value.
         @returns The processed value. */
        DECLARE_GETPROCESSEDVALUE_ = 0;

        /*! @fn virtual bool
                isBoolean(void)
                const
         @brief Return @c true if the argument is for Boolean arguments.
         @returns @c true if the argument is for Boolean arguments and @c false otherwise. */
        DECLARE_ISBOOLEAN_
        {
            return false;
        } // isBoolean

        /*! @fn virtual bool
                isExtra(void)
                const
         @brief Return @c true if the argument is a placeholder for zero or more trailing
         arguments.
         @returns @c true if the argument is a placeholder for zero of more trailing arguments
         and @c false otherwise. */
        DECLARE_ISEXTRA_
        {
            return false;
        } // isExtra

        /*! @fn virtual bool
                isForFiles(bool & isForOutput)
                const
         @brief Return @c true if the argument is for file paths and @c false otherwise.
         @param isForOutput Set to @c true if the argument is for output files and @c false
         otherwise.
         @returns @c true if the argument is for file paths and @c false otherwise. */
        DECLARE_ISFORFILES_
        {
            isForOutput = false;
            return false;
        } // isForFiles

        /*! @brief Return @c true if the argument is modifiable and @c false otherwise.
         @returns @c true if the argument is modifiable and @c false otherwise. */
        inline bool
        isModifiable(void)
        const
        {
            return ((kArgModeUnknown != _argMode) && (0 != (_argMode & kArgModeModifiable)));
        } // isModifiable

        /*! @brief Return @c true if the argument is optional and @c false otherwise.
         @returns @c true if the argument is optional and @c false otherwise. */
        inline bool
        isOptional(void)
        const
        {
            return ((kArgModeUnknown != _argMode) && (0 != (_argMode & kArgModeOptional)));
        } // isOptional

        /*! @brief Return @c true if the argument is a password and @c false otherwise.
         @returns @c true if the argument is a password and @c false otherwise. */
        inline bool
        isPassword(void)
        const
        {
            return ((kArgModeUnknown != _argMode) && (0 != (_argMode & kArgModePassword)));
        } // isPassword

        /*! @brief Return @c true if the argument is required and @c false otherwise.
         @returns @c true if the argument is required and @c false otherwise. */
        inline bool
        isRequired(void)
        const
        {
            return ((kArgModeUnknown != _argMode) && (0 == (_argMode & kArgModeOptional)));
        } // isRequired

        /*! @brief Return @c true if the argument is valid and @c false otherwise.
         @returns @c true if the argument is valid and @c false otherwise. */
        inline bool
        isValid(void)
        const
        {
            return _valid;
        } // isValid

        /*! @fn virtual void
                setToDefaultValue(void)
         @brief Set the associated variable to the default value. */
        DECLARE_SETTODEFAULTVALUE_ = 0;

        /*! @fn virtual std::string
                toString(void)
         @brief Convert to a printable representation.
         @returns A printable representation of the descriptor. */
        DECLARE_TOSTRING_ = 0;

        /*! @fn virtual bool
                validate(const std::string & value)
         @brief Check an input value against the constraints of the descriptor.
         @param value The value to be checked.
         @returns @c true if the value is within the domain of the descriptor and @c false
         otherwise. */
        DECLARE_VALIDATE_ = 0;

    protected :

        /*! @brief Partition a string that is in 'arguments' format into a sequence of strings.
         @param inString The string to be partitioned.
         @param indexOfDefaultValue The position in the input string where the default value
         will appear.
         @param result The partitioned string.
         @returns @c true if the correct number of fields appear within the input string and
         @c false otherwise. */
        static bool
        partitionString(const std::string & inString,
                        const size_t        indexOfDefaultValue,
                        StringVector &      result);

        /*! @brief Returns a string that contains a printable representation of the standard
         prefix fields for a command-line argument.
         @param tagForField The tag value to use for the field.
         @returns A string that contains a printable representation of the standard prefix
         fields for a command-line argument. */
        std::string
        prefixFields(const std::string & tagForField)
        const;

        /*! @brief Returns a string that contains a printable representation of the standard
         fields for a command-line argument.
         @param defaultToUse The string to put in the printable representation for the default
         value.
         @returns A string that contains a printable representation of the standard fields for
         a command-line argument. */
        std::string
        suffixFields(const std::string & defaultToUse);

    private :

        COPY_AND_ASSIGNMENT_(BaseArgumentDescriptor);

    public :

    protected :

        /*! @brief The separator string to use when converting to a string. */
        static std::string _parameterSeparator;

        /*! @brief @c true if the argument was valid and @c false otherwise. */
        bool _valid;

    private :

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
    typedef std::vector<BaseArgumentDescriptor *> DescriptorVector;

    /*! @brief Generate the standard 'argument list' description from an argument sequence.
     @param arguments The argument sequence.
     @returns A string containing the standard 'argument list' representation of the argument
     sequence. */
    std::string
    ArgumentsToArgString(const DescriptorVector & arguments);

    /*! @brief Generate the standard 'argument description' from an argument sequence.
     @param arguments The argument sequence.
     @param output The generated argument descriptions.
     @param minSpace The number of characters between the argument names and their
     descriptions. */
    void
    ArgumentsToDescriptionArray(const DescriptorVector & arguments,
                                StringVector &           output,
                                const size_t             minSpace);

    /*! @brief Return the resulting argument values.
     @param arguments The argument sequence.
     @param sep The separator string between the argument values.
     @returns The argument values, separated by 'sep'. */
    std::string
    CombineArguments(const DescriptorVector & arguments,
                     const std::string &       sep);

    /*! @brief Convert a string in '--args' format into an argument description.
     @param inString The string to be analyzed.
     @returns A newly allocated argument descriptor or @c NULL if the string is not valid. */
    BaseArgumentDescriptor *
    ConvertStringToArgument(const std::string & inString);

#if 0
    /*! @brief Copy the argument values to a bottle.
     @param arguments The argument sequence.
     @param container The bottle to be modified. */
    void
    CopyArgumentsToBottle(const DescriptorVector & arguments,
                          yarp::os::Bottle &       container);
#endif//0

    /*! @brief Return the mode corresponding to a string.
     @param modeString The mode value as a string.
     @returns The mode corresponding to a string. */
    ArgumentMode
    ModeFromString(const std::string & modeString);

    /*! @brief Update the arguments data from the parsed argument list.
     @param arguments The argument sequence.
     @param parseResult The parsed argument list.
     @param badArgs The list of invalid or missing arguments.
     @returns @c true if the parsed argument list matches the argument sequence and @c false
     otherwise. */
    bool
    ProcessArguments(const DescriptorVector & arguments,
                     Option_::Parser &        parseResult,
                     std::string &            badArgs);

    /*! @brief Prompt the user for the value of each of the arguments.
     @param arguments The argument sequence.
     @returns @c true if all arguments are valid and @c false otherwise. */
    bool
    PromptForValues(const DescriptorVector & arguments);

} // nImO

#endif // ! defined(nImObaseArgumentDescriptor_HPP_)

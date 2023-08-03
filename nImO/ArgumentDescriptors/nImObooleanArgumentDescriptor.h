//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImObooleanArgumentDescriptor.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the minimal functionality required to represent a boolean
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
//  Created:    2015-08-25
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOboolArgumentDescriptor_H_))
# define nImOboolArgumentDescriptor_H_ /* Header guard */

# include <ArgumentDescriptors/nImObaseArgumentDescriptor.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the minimal functionality required to represent a boolean
 command-line argument. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A boolean argument description.

     The external representation of a boolean argument description is:

     booleanTagAndInfo ::= 'B'; */
    class BooleanArgumentDescriptor final : public BaseArgumentDescriptor
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = BaseArgumentDescriptor;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] argName The name of the command-line argument.
             @param[in] argDescription A description of the command-line argument.
             @param[in] argMode The mode of the command-line argument.
             @param[in] defaultValue The default value for the command-line argument. */
            BooleanArgumentDescriptor
                (const std::string &    argName,
                 const std::string &    argDescription,
                 const ArgumentMode     argMode,
                 const bool             defaultValue = false);

            /*! @brief The copy constructor.
             @param[in] other The object to be copied. */
            BooleanArgumentDescriptor
                (const BooleanArgumentDescriptor & other);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            BooleanArgumentDescriptor
                (BooleanArgumentDescriptor &&	other)
                noexcept;

            /*! @brief Return the current value.
             @return The current value. */
            inline bool
            getCurrentValue
                (void)
                const
            {
                return _currentValue;
            }

            /*! @brief Return @c true if the argument is for Logical arguments.
             @return @c true if the argument is for Logical arguments and @c false otherwise. */
            bool
            isLogical
                (void)
                const
                override;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            BooleanArgumentDescriptor &
            operator=
                (const BooleanArgumentDescriptor &  other);

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            BooleanArgumentDescriptor &
            operator=
                (BooleanArgumentDescriptor &&  other)
                noexcept;

            /*! @brief Construct a descriptor, if at all possible, from the input string.
             @param[in] inString The input string in 'arguments' format.
             @return A valid descriptor or @c nullptr if the input is not recognized. */
            static SpBaseArgumentDescriptor
            parseArgString
                (const std::string &    inString);

            /*! @brief Exchanges the contents of the object with those of other.
             @param[in,out] other The object to be swapped with. */
            void
            swap
                (BooleanArgumentDescriptor &   other);

        protected :
            // Protected methods.

            /*! @brief Return the default value.
             @return The default value. */
            std::string
            getDefaultValue
                (void)
                override;

            /*! @brief Return the default value as a human-readable string.
             @return The default value as a human-readable string. */
            std::string
            getPrintableDefaultValue
                (void)
                override;

        private :
            // Private methods.

            /*! @brief Return a copy of the descriptor, with only non-pointer types duplicated.
             @return A copy of the descriptor, with only non-pointer types duplicated. */
            SpBaseArgumentDescriptor
            clone
                (void)
                const
                override;

            /*! @brief Return the processed value.
             @return The processed value. */
            std::string
            getProcessedValue
                (void)
                override;

            /*! @brief Set the associated variable to the default value. */
            void
            setToDefaultValue
                (void)
                override;

            /*! @brief Convert to a printable representation.
             @return A printable representation of the descriptor. */
            std::string
            toString
                (void)
                override;

            /*! @brief Check an input value against the constraints of the descriptor.
             @param[in] value The value to be checked.
             @return @c true if the value is within the domain of the descriptor and @c false
             otherwise. */
            bool
            validate
                (const std::string &    value)
                override;

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The default value for the command-line argument. */
            bool    _defaultValue{false};

            /*! @brief The current value of the command-line argument. */
            bool    _currentValue{false};

# if MAC_OR_LINUX_
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // MAC_OR_LINUX_
            /*! @brief Filler to pad to alignment boundary */
            char    _filler[6];
# if MAC_OR_LINUX_
#  pragma clang diagnostic pop
# endif // MAC_OR_LINUX_

    }; // BooleanArgumentDescriptor

} // nImO

#endif // not defined(nImOboolArgumentDescriptor_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ArgumentDescriptors/nImOextraArgumentDescriptor.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the minimal functionality required to represent a
//              placeholder for trailing command-line arguments.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2015 by OpenDragon.
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
//  Created:    2015-06-08
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOextraArgumentDescriptor_H_))
# define nImOextraArgumentDescriptor_H_ /* Header guard */

# include <ArgumentDescriptors/nImObaseArgumentDescriptor.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the minimal functionality required to represent a placeholder for
 trailing command-line arguments. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A trailing arguments description.

     The external representation of a trailing arguments description is:

     extraTagAndInfo ::= 'E';

     Note that the concept of 'optional' versus 'mandatory' is not applicable to trailing
     arguments, as it's possible to have zero or more of them.
     Likewise, there is no 'default' value that makes sense or, for that matter, a single
     argument reference is of no practical use. */
    class ExtraArgumentDescriptor final : public BaseArgumentDescriptor
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
            @param[in] argDescription A description of the command-line argument. */
            ExtraArgumentDescriptor
                (const std::string &    argName,
                 const std::string &    argDescription);

            /*! @brief The copy constructor.
            @param[in] other The object to be copied. */
            ExtraArgumentDescriptor
                (const ExtraArgumentDescriptor &    other);

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            ExtraArgumentDescriptor
                (ExtraArgumentDescriptor &&	other)
                noexcept;

            /*! @brief Convert to a description of the expected values.
             @return A representation of the descriptor that describes the expected values. */
            std::string
            describe
                (void)
                override;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            ExtraArgumentDescriptor &
            operator=
                (const ExtraArgumentDescriptor &    other);

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            ExtraArgumentDescriptor &
            operator=
                (ExtraArgumentDescriptor &&  other)
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
                (ExtraArgumentDescriptor &  other);

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Return a copy of the descriptor, with only non-pointer types duplicated.
            @return A copy of the descriptor, with only non-pointer types duplicated. */
            UpBaseArgumentDescriptor
            clone
                (void)
                const
                override;

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

            /*! @brief Return the processed value.
            @return The processed value. */
            std::string
            getProcessedValue
                (void)
                override;

            /*! @brief Return @c true if the argument is a placeholder for zero or more trailing
            arguments.
            @return @c true if the argument is a placeholder for zero of more trailing arguments
            and @c false otherwise. */
            bool
            isExtra
                (void)
                const
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

    }; // ExtraArgumentDescriptor

} // nImO

#endif // not defined(nImOextraArgumentDescriptor_H_)

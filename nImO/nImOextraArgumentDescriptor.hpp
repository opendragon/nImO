//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOextraArgumentDescriptor.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for the minimal functionality required to represent a
//              placeholder for trailing command-line arguments.
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
//  Created:    2015-06-08
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOextraArgumentDescriptor_HPP_))
# define nImOextraArgumentDescriptor_HPP_ /* Header guard */

# include <nImObaseArgumentDescriptor.hpp>

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
    class ExtraArgumentDescriptor : public BaseArgumentDescriptor
    {
    public :

    protected :

    private :

        /*! @brief The class that this class is derived from. */
        using inherited = BaseArgumentDescriptor;

    public :

        /*! @brief The constructor.
         @param[in] argName The name of the command-line argument.
         @param[in] argDescription A description of the command-line argument. */
        ExtraArgumentDescriptor
            (const std::string& argName,
             const std::string& argDescription);

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        ExtraArgumentDescriptor
            (const ExtraArgumentDescriptor& other);

        /*! @brief The destructor. */
        virtual
        ~ExtraArgumentDescriptor
            (void);

        /*! @brief Construct a descriptor, if at all possible, from the input string.
         @param[in] inString The input string in 'arguments' format.
         @returns A valid descriptor or @c nullptr if the input is not recognized. */
        static SpBaseArgumentDescriptor
        parseArgString
            (const std::string& inString);

        /*! @brief Exchanges the contents of the object with those of other.
         @param[in,out] other The object to be swapped with. */
        void
        swap
            (ExtraArgumentDescriptor&   other);
        
    protected :

    private :

#if 0
        /*! @brief Add the processed value to a bottle.
         @param[in,out] container The bottle to be modified. */
        virtual void
        addValueToBottle
            (yarp::os::Bottle&  container)
            override;
#endif//0

        /*! @brief Return a copy of the descriptor, with only non-pointer types duplicated.
         @returns A copy of the descriptor, with only non-pointer types duplicated. */
        virtual SpBaseArgumentDescriptor
        clone
            (void)
            const
            override;

        /*! @brief Return the default value.
         @returns The default value. */
        virtual std::string
        getDefaultValue
            (void)
            override;

        /*! @brief Return the processed value.
         @returns The processed value. */
        virtual std::string
        getProcessedValue
            (void)
            override;

        /*! @brief Return @c true if the argument is a placeholder for zero or more trailing
         arguments.
         @returns @c true if the argument is a placeholder for zero of more trailing arguments
         and @c false otherwise. */
        virtual bool
        isExtra
            (void)
            const
            override;

        /*! @brief Set the associated variable to the default value. */
        virtual void
        setToDefaultValue
            (void)
            override;

        /*! @brief Convert to a printable representation.
         @returns A printable representation of the descriptor. */
        virtual std::string
        toString
            (void)
            override;

        /*! @brief Check an input value against the constraints of the descriptor.
         @param[in] value The value to be checked.
         @returns @c true if the value is within the domain of the descriptor and @c false
         otherwise. */
        virtual bool
        validate
            (const std::string& value)
            override;

    public :

    protected :

    private :

    }; // ExtraArgumentDescriptor

} // nImO

#endif // ! defined(nImOextraArgumentDescriptor_HPP_)

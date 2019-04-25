//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOaddressArgumentDescriptor.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for the minimal functionality required to represent an IP
//              address command-line argument.
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
//  Created:    2015-05-17
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOaddressArgumentDescriptor_HPP_))
# define nImOaddressArgumentDescriptor_HPP_ /* Header guard */

# include <nImOstringArgumentDescriptor.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the minimal functionality required to represent an IP address
 command-line argument. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief An address argument description.

    The external representation of an address argument description is:

     addressTagAndInfo ::= 'A'; */
    class AddressArgumentDescriptor : public StringArgumentDescriptor
    {
    public :

    protected :

    private :

        /*! @brief The class that this class is derived from. */
        using inherited = StringArgumentDescriptor;

    public :

        /*! @brief The constructor.
         @param[in] argName The name of the command-line argument.
         @param[in] argDescription A description of the command-line argument.
         @param[in] argMode The mode of the command-line argument.
         @param[in] defaultValue The default value for the command-line argument.
         @param[in,out] addrBuff If non-@c nullptr, the variable to be set with the actual
         address. */
        AddressArgumentDescriptor
            (const std::string& argName,
             const std::string& argDescription,
             const ArgumentMode argMode,
             const std::string& defaultValue,
             struct in_addr*    addrBuff = nullptr);

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        AddressArgumentDescriptor
            (const AddressArgumentDescriptor&   other);

        /*! @brief The destructor. */
        virtual
        ~AddressArgumentDescriptor
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
            (AddressArgumentDescriptor& other);

    protected :

    private :

        /*! @brief Return a copy of the descriptor, with only non-pointer types duplicated.
         @returns A copy of the descriptor, with only non-pointer types duplicated. */
        virtual SpBaseArgumentDescriptor
        clone
            (void)
            const
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

        /*! @brief The variable to be filled in with the actual address. */
        struct in_addr* _addrBuff;

    }; // AddressArgumentDescriptor

} // nImO

#endif // ! defined(nImOaddressArgumentDescriptor_HPP_)

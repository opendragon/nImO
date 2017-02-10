//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOportArgumentDescriptor.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for the minimal functionality required to represent a port
//              number command-line argument.
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
//  Created:    2015-05-21
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOportArgumentDescriptor_HPP_))
# define nImOportArgumentDescriptor_HPP_ /* Header guard */

# include <nImO/nImOintArgumentDescriptor.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for the minimal functionality required to represent a port number
 command-line argument. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A port number argument description.

     The external representation of a port number argument description is:

     portTagAndInfo ::= 'P' sep systemOrRegular;

     systemOrRegular ::= 's' | 'r'; */
    class PortArgumentDescriptor : public IntArgumentDescriptor
    {
    public :

    protected :

    private :

        /*! @brief The class that this class is derived from. */
        typedef IntArgumentDescriptor inherited;

    public :

        /*! @brief The constructor.
         @param[in] argName The name of the command-line argument.
         @param[in] argDescription A description of the command-line argument.
         @param[in] argMode The mode of the command-line argument.
         @param[in] defaultValue The default value for the command-line argument.
         @param[in] isSystemPort @c true if the value can be a system port and @c false
         otherwise. */
        PortArgumentDescriptor(const std::string  &argName,
                               const std::string  &argDescription,
                               const ArgumentMode argMode,
                               const int          defaultValue,
                               const bool         isSystemPort);

        /*! @brief The destructor. */
        virtual
        ~PortArgumentDescriptor(void);

        /*! @brief Construct a descriptor, if at all possible, from the input string.
         @param[in] inString The input string in 'arguments' format.
         @returns A valid descriptor or @c NULL if the input is not recognized. */
        static BaseArgumentDescriptor *
        parseArgString(const std::string &inString);

    protected :

    private :

        /*! @brief The copy constructor.
         @param[in] other The object to be copied. */
        PortArgumentDescriptor(const PortArgumentDescriptor &other);

        /*! @brief Return a copy of the descriptor, with only non-pointer types duplicated.
         @returns A copy of the descriptor, with only non-pointer types duplicated. */
        virtual BaseArgumentDescriptor *
        clone(void)
        override;

        /*! @brief The assignment operator.
         @param[in] other The object to be copied.
         @returns The updated object. */
        PortArgumentDescriptor &
        operator =(const PortArgumentDescriptor &other);

        /*! @brief Convert to a printable representation.
         @returns A printable representation of the descriptor. */
        virtual std::string
        toString(void)
        override;

    public :

    protected :

    private :

        /*! @brief @c true if the value can be a system port and @c false otherwise. */
        bool _isSystemPort;

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-private-field"
# endif // defined(__APPLE__)
        /*! @brief Filler to pad to alignment boundary */
        char _filler[7];
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

    }; // PortArgumentDescriptor

} // nImO

#endif // ! defined(nImOportArgumentDescriptor_HPP_)

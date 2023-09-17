//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOpackage.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO received or sent data.
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
//  Created:    2023-09-17
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOpackage_H_))
# define nImOpackage_H_ /* Header guard */

# include <ContainerTypes/nImOmessage.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO received or sent data. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide received or sent data. */
    class Package final
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor. */
            Package
                (const int  tag = 0,
                 SpMessage  value = nullptr);

            /*! @brief The move constructor.
             @param[in] other The object to be moved. */
            Package
                (Package &&    other)
                noexcept;

            /*! @brief The copy assignment operator.
             @param[in] other The object to be copied.
             @return The updated object. */
            Package &
            operator=
                (const Package &    other);

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            Package &
            operator=
                (Package && other)
                noexcept;

            /*! @brief Return the tag associated with the Message.
             @return The tag associated with the Message. */
            inline int
            tag
                (void)
                const
            {
                return _tag;
            }

            /*! @brief Return the contained Message.
             @return The contained Message. */
            inline SpMessage
            value
                (void)
                const
            {
                return _value;
            }
        
        protected :
            // Protected methods.

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.
        
            /*! @brief The tag for the associated Message. */
            int _tag;

            /*! @brief The Message being transferred. */
            SpMessage   _value;

    }; // Package

    /*! @brief A sequence of Messages encapsulated in Packages. */
    using PackageQueue = std::queue<Package>;

} // nImO

#endif // not defined(nImOpackage_H_)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Containers/nImOcontainer.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO containers.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-03-24
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOcontainer_H_))
# define nImOcontainer_H_ /* Header guard */

# include <BasicTypes/nImOvalue.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO containers. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide values that contain other values.

     Note that Containers 'own' their data and will perform a delete of the
     contained elements on deletion. */
    class Container : public Value
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = Value;

        public :
            // Public methods.

            /*! @brief The move constructor.
            @param[in] other The object to be moved. */
            Container
                (Container &&	other)
                noexcept;

            /*! @brief Return non-@c nullptr if the object is a Container.
            @return Non-@c nullptr if the object is a Container and @c nullptr otherwise. */
            virtual CPtr(Container)
            asContainer
                (void)
                const
                final;

            /*! @brief Remove all entries from the Container. */
            virtual void
            clear
                (void) = 0;

            /*! @brief Return @c true if the Container is empty. */
            virtual bool
            empty
                (void)
                const = 0;

            /*! @brief Returns the number of elements in the Container. */
            virtual size_t
            size
                (void)
                const = 0;

        protected :
            // Protected methods.

            /*! @brief The constructor. */
            Container
                (void);

            /*! @brief The move assignment operator.
             @param[in] other The object to be moved.
             @return The updated object. */
            Container &
            operator=
                (Container &&   other)
                noexcept;

        private :
            // Private methods.

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

    }; // Container

} // nImO

#endif // not defined(nImOcontainer_H_)

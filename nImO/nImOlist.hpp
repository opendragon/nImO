//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOlist.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO lists.
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
//  Created:    2016-03-21
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOlist_HPP_))
# define nImOlist_HPP_ /* Header guard */

# include <nImO/nImOcontainer.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO lists. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide collections with list-like behaviour. */
    class List : public Container,
                 public std::list<Value *>
    {
    public :
        // Public type definitions.
    
    protected :
        // Protected type definitions.
    
    private :
        // Private type definitions.
        
        /*! @brief The first class that this class is derived from. */
        typedef Container inherited1;
        
        /*! @brief The second class that this class is derived from. */
        typedef std::list<Value *> inherited2;
        
    public :
        // Public methods.
        
        /*! @brief The constructor. */
        List(void);

        /*! @brief The destructor. */
        ~List(void);
        
        /*! @fn virtual void
                addToStringBuffer(StringBuffer & outBuffer)
         @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to. */
        DECLARE_ADDTOSTRINGBUFFER_;
        
        /*! @fn bool
                lessThan(const Value & other,
                         bool &        validComparison)
                const
         @brief Return the relative ordering of two Lists.
         @param other The List to be compared with.
         @param validComparison @c true if the Lists were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Lists. */
        DECLARE_LESSTHAN_;

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
        
    }; // List

} // nImO

#endif // ! defined(nImOlist_HPP_)

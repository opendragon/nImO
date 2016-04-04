//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOnumber.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO numeric values.
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

#if (! defined(nImO$file$_HPP_))
# define nImO$file$_HPP_ /* Header guard */

# include <nImO/nImOatom.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO numeric values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide numeric values. */
    class Number : public Atom
    {
    public :
        // Public type definitions.
    
    protected :
        // Protected type definitions.
    
    private :
        // Private type definitions.
        
        /*! @brief The class that this class is derived from. */
        typedef Atom inherited;

        public :
        // Public methods.
        
        /*! @brief The constructor. */
        Number(void);

        /*! @brief The constructor.
          @param initialValue The initial value for the object. */
        explicit Number(const int64_t initialValue);

        /*! @brief The constructor.
          @param initialValue The initial value for the object. */
        explicit Number(const double initialValue);

        /*! @brief The destructor. */
        ~Number(void);
        
        /*! @fn virtual void
                addToStringBuffer(StringBuffer & outBuffer)
         @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to. */
        DECLARE_ADDTOSTRINGBUFFER_;
        
        /*! @fn int
                lessThan(const Value & other,
                          bool &        validComparison)
                const
         @brief Return the relative ordering of two Numbers.
         @param other The Number to be compared with.
         @param validComparison @c true if the Numbers were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Numbers. */
        DECLARE_LESSTHAN_;
        
        /*! @fn Enumerable
                enumerationType(void)
                const
         @brief Return the enumeraton type of an object.
         @returns The enumeration type of an object. */
        DECLARE_ENUMERATIONTYPE_
        {
            return (_valueIsFloat ? kEnumerableNotEnumerable : kEnumerableInteger);
        } // enumerationType
        
        /*! @brief Returns @c true if the associated value is a floating-point number and @c false
         otherwise.
         @returns @c true if the associated value is a floating-point number and @c false
         otherwise. */
        bool
        isFloat(void)
        const
        {
            return _valueIsFloat;
        } // isFloat

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
        
        /*! @brief The associated value, if it is floating point. */
        int64_t _intValue;
        
        /*! @brief The associated value, if it is an integer. */
        double _floatValue;
        
        /*! @brief @c true if the associated value is a floating-point number and @c false
         otherwise. */
        bool _valueIsFloat;
        
    }; // Number

} // nImO

#endif // ! defined(nImOnumber_HPP_)

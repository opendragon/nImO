//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOvalue.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO general values.
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

#if (! defined(nImOvalue_HPP_))
# define nImOvalue_HPP_ /* Header guard */

# include <nImO/nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO general values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief Declare the addToStringBuffer method, which appends a printable version the object to a
 string buffer. */
# define DECLARE_ADDTOSTRINGBUFFER_ \
    virtual void\
    addToStringBuffer(StringBuffer & outBuffer)\
    const

/*! @brief Declare the greaterThan method, which returns the relative ordering of two values. */
# define DECLARE_GREATERTHAN_ \
    virtual bool\
    greaterThan(const Value & other,\
                bool &        validComparison)\
    const

/*! @brief Declare the lessThan method, which returns the relative ordering of two values. */
# define DECLARE_LESSTHAN_ \
    virtual bool\
    lessThan(const Value & other,\
             bool &        validComparison)\
    const

/*! @brief Declare the enumerationType method, which returns the enumerability of an object. */
# define DECLARE_ENUMERATIONTYPE_ \
    virtual Enumerable\
    enumerationType(void)\
    const

/*! @brief Declare the isContainer method, which returns @c true if the object is a container and
 @c false otherwise. */
# define DECLARE_ISCONTAINER_ \
    virtual bool\
    isContainer(void)\
    const

/*! @brief Define the addToStringBuffer method, which appends a printable version the object to a
 string buffer. */
# define DEFINE_ADDTOSTRINGBUFFER_(class_) \
    void\
    class_::addToStringBuffer(StringBuffer & outBuffer)\
    const

/*! @brief Define the greaterThan method, which returns the relative ordering of two Values. */
# define DEFINE_GREATERTHAN_(class_) \
    bool\
    class_::greaterThan(const Value & other,\
                        bool &        validComparison)\
    const

/*! @brief Declare the isContainer method, which returns @c true if the object is a container and
 @c false otherwise. */
# define DEFINE_ISCONTAINER_(class_) \
    bool\
    class_::isContainer(void)\
    const

/*! @brief Define the lessThan method, which returns the relative ordering of two Values. */
# define DEFINE_LESSTHAN_(class_) \
    bool\
    class_::lessThan(const Value & other,\
                     bool &        validComparison)\
    const

namespace nImO
{
    class StringBuffer;

    /*! @brief A class to provide general value behaviours. */
    class Value
    {
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

    public :
        // Public methods.

        /*! @brief The destructor. */
        ~Value(void);

        /*! @fn virtual void
                addToStringBuffer(StringBuffer & outBuffer)
         @brief Add a readable representation of the object to the buffer.
         @param outBuffer The buffer to be appended to. */
        DECLARE_ADDTOSTRINGBUFFER_
        {
        } // addToStringBuffer

        /*! @fn Enumerable
                enumerationType(void)
                const
         @brief Return the enumeraton type of an object.
         @returns The enumeration type of an object. */
        DECLARE_ENUMERATIONTYPE_
        {
            return kEnumerableNotEnumerable;
        } // enumerationType

        /*! @fn bool
                greaterThan(const Value & other,
                            bool &        validComparison)
                const
         @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        DECLARE_GREATERTHAN_
        {
            validComparison = false;
            return false;
        } // greaterThan

        /*! @fn virtual bool
                isContainer(void)
                const
         @brief Return @c true if the object is a container.
         @returns @c true if the object is a container and @c false otherwise. */
        DECLARE_ISCONTAINER_
        {
            return false;
        } // isContainer

        /*! @fn bool
                lessThan(const Value & other,
                         bool &        validComparison)
                const
         @brief Return the relative ordering of two Values.
         @param other The Value to be compared with.
         @param validComparison @c true if the Values were comparable and @c false otherwise; if
         @c false, the returned value should be ignored.
         @returns The relative ordering of the two Values. */
        DECLARE_LESSTHAN_
        {
            validComparison = false;
            return false;
        } // lessThan

    protected :
        // Protected methods.

        /*! @brief The constructor. */
        Value(void);

    private :
        // Private methods.

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

    }; // Value

} // nImO

#endif // ! defined(nImOvalue_HPP_)

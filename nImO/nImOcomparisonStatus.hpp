//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcomparisonStatus.hpp
//
//  Project:    nImO
//
//  Contains:   The class declaration for nImO comparison values.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2020 by OpenDragon.
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
//  Created:    2020-02-23
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOcomparisonStatus_HPP_))
# define nImOcomparisonStatus_HPP_ /* Header guard */

# include <nImOcommon.hpp>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for %nImO comparison values. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    /*! @brief A class to provide comparison values. */
    class ComparisonStatus
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
        inline ComparisonStatus
            (const bool result = true,
             const bool valid = true) :
            _result(result), _valid(valid)
        {
        } // constructor

        /*! @brief Update the current status by merging in the other status.
         @param[in] other The status to be merged in.
         @return The modified status. */
        inline ComparisonStatus &
        operator &=
            (const ComparisonStatus &   other)
        {
            _result &= other._result;
            _valid &= other._valid;
            return *this;
        } // operator &=

        /*! @brief Copy a status.
         @param[in] other The status to be copied.
         @return The modified status. */
        inline ComparisonStatus &
        operator =
            (const ComparisonStatus &   other)
        {
            _result = other._result;
            _valid = other._valid;
            return *this;
        } // operator =

        /*! @brief Return the relative ordering of two statuses.
         @param[in] other The status to be compared with.
         @return The relative ordering of the two statuses. */
        inline bool
        operator ==
            (const ComparisonStatus &   other)
            const
        {
            return ((_result == other._result) && (_valid == other._valid));
        } // operator ==

        /*! @brief Return the relative ordering of two statuses.
         @param[in] other The status to be compared with.
         @return The relative ordering of the two statuses. */
        inline bool
        operator !=
            (const ComparisonStatus &   other)
            const
        {
            return ((_result != other._result) || (_valid != other._valid));
        } // operator !=

        /*! @brief Set a valid status.
         @param[in] value The status to be assigned.
         @return The modified status. */
        inline ComparisonStatus &
            operator =
            (const bool value)
        {
            _result = value;
            _valid = true;
            return *this;
        } // operator =

        /*! @brief Clear the status.
         @return The modified status. */
        inline ComparisonStatus &
            clear
            (void)
        {
            _result = _valid = false;
            return *this;
        } // clear

        /*! @brief Return the validity of the status.
         @return The validity of the comparison. */
        inline bool
        IsValid
            (void)
            const
        {
            return _valid;
        } // IsValid

        /*! @brief Return the result of the status.
         @return The result of the comparison. */
        inline bool
        Result
            (void)
            const
        {
            return _result;
        } // Result

        friend std::ostream &
        operator <<
            (std::ostream &             out,
             const ComparisonStatus &   aValue);

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

        /*! @brief The comparison result; @c true if successful. */
        bool    _result;

        /*! @brief The validity of the comparison; @c true if all comparisons were allowed. */
        bool    _valid;

    }; // ComparisonStatus

    /*! @brief Insert a readable version of the status into an output stream.
     @param[in,out] out The stream to be added to.
     @param[in] aValue The object to be printed.
     @return The modified stream. */
    std::ostream &
    operator <<
        (std::ostream &             out,
         const ComparisonStatus &   aValue);

} // nImO

#endif // ! defined(nImOcomparisonStatus_HPP_)

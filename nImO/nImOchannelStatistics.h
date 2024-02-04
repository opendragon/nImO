//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOchannelStatistics.h
//
//  Project:    nImO
//
//  Contains:   The class declaration for information about nImO connections.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-02-04
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOchannelStatistics_H_))
# define nImOchannelStatistics_H_ /* Header guard */

# include <nImOcommon.h>

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The class declaration for information about %nImO connections. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    class InputOutputContext;

    /*! @brief Information structure for channels. */
    class ChannelStatistics final
    {

        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] choice The choice value associated with the description.
             @param[in] description The text describing the choice. */
            ChannelStatistics
                (void)
            {
            }

            /*! @brief Reset the statistics. */
            void
            clear
                (void);

            /*! @brief Retrieve the current statistics.
             @param[out] numberOfBytes The number of bytes transferred.
             @param[out] numberOfMessage The number of messages transferred. */
            void
            get
                (int64_t &  numberOfBytes,
                 int64_t &  numberOfMessages);

            /*! @brief Update the statistics.
             @param[in] additionalBytes The number of bytes transferred. */
            void
            update
                (const int64_t  additionalBytes);

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

            /*! @brief The number of bytes transferred. */
            int64_t _numberOfBytes{0};

            /*! @brief The number of messages transferred. */
            int64_t _numberOfMessages{0};

            /*! @brief Mutual-exclusion protection. */
            mutable std::mutex  _lock;

    }; // ChannelStatistics

} // nImO

#endif // not defined(nImOchannelStatistics_H_)

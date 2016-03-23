//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommon.h
//
//  Project:    nImO
//
//  Contains:   The function and class declarations for common entities for nImO.
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

#if (! defined(nImOcommon_HPP_))
# define nImOcommon_HPP_ /* Header guard */

# include <nImO/nImOconfig.hpp>

# if (! defined(LINUX_))
/*! @brief @c TRUE if Linux, @c FALSE otherwise. */
#  define LINUX_ defined(__linux__)
# endif // ! defined(LINUX_)
# if (! defined(MAC_OR_LINUX_))
/*! @brief @c TRUE if non-Windows, @c FALSE if Windows. */
#  define MAC_OR_LINUX_ (defined(__APPLE__) || defined(__linux__))
# endif // ! defined(MAC_OR_LINUX_)

//# include <algorithm>
//# include <cctype>
//# include <csignal>
//# include <cstdlib>
//# include <cstring>
# include <iostream>
//# include <list>
//# include <map>
//# include <stdint.h>
//# include <sstream>
//# include <time.h>
//# include <vector>

# if (! defined(TRUE))
#  define TRUE 1
# endif // ! defined(TRUE)
# if (! defined(FALSE))
#  define FALSE 0
# endif // ! defined(FALSE)

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
 @brief The function and class declarations for common entities for nImO. */

/*! @dir /nImO
 @brief The set of files that implement the nImO framework. */

/*! @dir /CommonTests
 @brief The set of files that provide test cases for the nImO framework. */

/*! @namespace nImO
 @brief The classes that implement the nImO framework. */

/*! @namespace nImO::Base
 @brief The classes that support the basic functionality of the nImO framework. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

namespace nImO
{
    namespace Base
    {

    } // Base

} // nImO

#endif // ! defined(nImOcommon_HPP_)

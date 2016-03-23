//--------------------------------------------------------------------------------------------------
//
//  File:       Common/nImOConfig.h
//
//  Project:    nImO
//
//  Contains:   The common macro definitions for nImO applications.
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
//  Created:    2014-02-18
//
//--------------------------------------------------------------------------------------------------

#if (! defined(nImOConfig_H_))
# define nImOConfig_H_ /* Header guard */

# if defined(__APPLE__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-pragmas"
#  pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
# endif // defined(__APPLE__)
/*! @file
   @brief The common macro definitions for nImO clients and services. */
# if defined(__APPLE__)
#  pragma clang diagnostic pop
# endif // defined(__APPLE__)

/*! @brief The major part of the version number. */
# define nImO_VERSION_MAJOR_ 1

/*! @brief The minor part of the version number. */
# define nImO_VERSION_MINOR_ 0

/*! @brief The patch part of the version number. */
# define nImO_VERSION_PATCH_ 0

/*! @brief The version number as a string. */
# define nImO_VERSION_ "1.0.0"

/*! @brief The base of the channel name to use for an adapter. */
# define nImO_ADAPTER_BASE_NAME_        ""

/*! @brief The base of the channel name to use for a client. */
# define nImO_CLIENT_BASE_NAME_         ""

/*! @brief The base name of the channel name to use for an input. */
# define nImO_INPUT_BASE_NAME_          ""

/*! @brief The base name of the channel name to use for an output. */
# define nImO_OUTPUT_BASE_NAME_         ""

/*! @brief The name of the %Registry service executable. */
# define nImO_REGISTRY_EXECUTABLE_NAME_ ""

/*! @brief The base of the channel name to use for a service. */
# define nImO_SERVICE_BASE_NAME_        ""

/* #undef nImO_BuildDummyServices */

/* #undef nImO_ChattyStart */

/* #undef nImO_DoExplicitCheckForOK */

/* #undef nImO_DoExplicitClose */

/* #undef nImO_DoExplicitDisconnect */

/* #undef nImO_DontUseTimeouts */

/* #undef nImO_LogIncludesYarpTrace */

/* #undef nImO_MetricsInitiallyOn */

/* #undef nImO_ReportContactDetails */

/* #undef nImO_ReportOnConnections */

/* #undef nImO_ServicesLogToStandardError */

/* #undef nImO_StallOnSendProblem */

/* #undef nImO_UseCustomStringBuffer */

/* #undef nImO_UseDiskDatabase */

/* #undef nImO_UseTestDatabase */

/* #undef nImO_UseTimeoutsInRetryLoops */

#endif // ! defined(nImOConfig_H_)

#--------------------------------------------------------------------------------------------------
#
#  File:       iOS/CMakeLists.txt
#
#  Project:    nImO
#
#  Contains:   The common CMAKE definitions for the nImO project.
#
#  Written by: Norman Jaffe
#
#  Copyright:  (c) 2016 by OpenDragon.
#
#              All rights reserved. Redistribution and use in source and binary forms, with or
#              without modification, are permitted provided that the following conditions are met:
#                * Redistributions of source code must retain the above copyright notice, this list
#                  of conditions and the following disclaimer.
#                * Redistributions in binary form must reproduce the above copyright notice, this
#                  list of conditions and the following disclaimer in the documentation and / or
#                  other materials provided with the distribution.
#                * Neither the name of the copyright holders nor the names of its contributors may
#                  be used to endorse or promote products derived from this software without
#                  specific prior written permission.
#
#              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
#              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
#              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
#              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
#              DAMAGE.
#
#  Created:    2016-02-18
#
#--------------------------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(PROJECT_NAME "nImO")

include(iOS.cmake)

project(nImO
        HOMEPAGE_URL "https://github.com/opendragon/nImO")

include(../nImOcommonSettings.cmake NO_POLICY_SCOPE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Make some flags to control the build flags visibilities
mark_as_advanced(CLEAR BUILD_SHARED_LIBS)

set(CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 9.0)
set(CMAKE_C_FLAGS "-miphoneos-version-min=9.0" CACHE STRING "Make sure version is supportable" FORCE)

set(CMAKE_CXX_FLAGS "-Wall -Wextra" CACHE STRING "Fixes linking error for nImO" FORCE)
set(CMAKE_INSTALL_PREFIX "/opt/nImO" CACHE STRING "Fixes install path for nImO" FORCE)
# 'rpath' warning
cmake_policy(SET CMP0042 OLD)

option(nImO_ChattyStart "Report the version numbers when launching an executable")

option(nImO_DoExplicitCheckForOK "Check OK responses for validity")

#option(nImO_DoExplicitClose "Perform an explicit CloseChannel() prior to freeing a channel")
#mark_as_advanced(nImO_DoExplicitClose)

#option(nImO_DoExplicitDisconnect "Perform an explicit disconnect prior to closing a channel")
#mark_as_advanced(nImO_DoExplicitDisconnect)

#option(nImO_DontUseTimeouts "Allow operations to take arbitrary lengths of time")
#mark_as_advanced(nImO_DontUseTimeouts)

#option(nImO_LogIncludesYarpTrace "Include YARP trace when logging")

#option(nImO_MetricsInitiallyOn "Collect channel measurement data by default")

#option(nImO_ReportContactDetails
#        "Report details of the contacts during operations that might change them")
#mark_as_advanced(nImO_ReportContactDetails)

#option(nImO_ReportOnConnections "Report on connections")

#option(nImO_ServicesLogToStandardError "Services send logging output to stderr" ON)

#option(nImO_StallOnSendProblem "A send failure goes to a tight loop")
#mark_as_advanced(nImO_StallOnSendProblem)

#option(nImO_UseCustomStringBuffer "Use a custom string buffer for large string output" ON)
#mark_as_advanced(nImO_UseCustomStringBuffer)

#option(nImO_UseDiskDatabase "Use a disk-based database, rather than in-memory")
#mark_as_advanced(nImO_UseDiskDatabase)

#option(nImO_UseTestDatabase "Use a test database, in /tmp, rather than a random disk location")
#mark_as_advanced(nImO_UseTestDatabase)

#option(nImO_UseTimeoutsInRetryLoops "Use timeouts in retry loops")
#mark_as_advanced(nImO_UseTimeoutsInRetryLoops)

#option(nImO_DO_SWIG "Build the SWIG files" OFF)

# Add the nImO target path so that nImO can be found
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

set(BOOST_ROOT "/opt/boost")
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(Boost_USE_MULTITHREADED)
endif()

configure_file("${nImO_SOURCE_DIR}/nImO/nImOconfig.h.in" "${nImO_SOURCE_DIR}/nImO/nImOconfig.h")
configure_file(${nImO_CONFIG_DIR}/nImOConfigVersion.cmake.in
                ${CMAKE_CURRENT_BINARY_DIR}/nImOConfigVersion.cmake @ONLY)

include_directories("${nImO_SOURCE_DIR}/nImO")

set(BONJOUR_LIB "")

set(ODL_DIR "/opt/odl/lib")
find_package(ODL 1.0.0 REQUIRED)
if(ODL_FOUND)
    include_directories(${ODL_INCLUDE_DIRS})
endif()

set(IF_DIR "/opt/if/lib")
find_package(IF 1.0.0 REQUIRED)
if(IF_FOUND)
    include_directories(${IF_INCLUDE_DIRS})
endif()

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(OTHER_LIBS "")

set(nImO_LINK_LIBRARIES nImOcommon ${ODL_LIBRARY} ${Boost_LIBRARIES} ${BONJOUR_LIB} ${OTHER_LIBS}
    Threads::Threads)

function(fix_dynamic_libs target)
endfunction()

install(FILES
        ${nImO_CONFIG_DIR}/nImOConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/nImOConfigVersion.cmake
        DESTINATION ${LIB_DEST}
        COMPONENT scripts)

install(EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST})

add_subdirectory(nImO)
#add_subdirectory(CPack)

#enable_testing()

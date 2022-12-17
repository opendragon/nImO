#--------------------------------------------------------------------------------------------------
#
#  File:       non-iOS/CMakeLists.txt
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

if(WIN32)
    set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE INTERNAL "" FORCE)
endif()

if(APPLE)
    execute_process(COMMAND uname -m
                    OUTPUT_VARIABLE CPU_TYPE
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND sw_vers -productVersion
                    OUTPUT_VARIABLE SYS_VERSION
                    OUTPUT_STRIP_TRAILING_WHITESPACE)

    set(CMAKE_OSX_ARCHITECTURES ${CPU_TYPE} CACHE STRING "Build architectures for Mac OSX")
    set(CMAKE_OSX_DEPLOYMENT_TARGET ${SYS_VERSION} CACHE STRING "Deployment target for Mac OSX")
endif()

project(nImO
        HOMEPAGE_URL "https://github.com/opendragon/nImO")

include(../nImOcommonSettings.cmake NO_POLICY_SCOPE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Make some flags to control the build flags visibilities
mark_as_advanced(CLEAR BUILD_SHARED_LIBS)
mark_as_advanced(SET CMAKE_INSTALL_RPATH)
mark_as_advanced(SET CMAKE_BUILD_WITH_INSTALL_RPATH)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(LINUX ON)
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "unknown")
        set(UNKNOWN_CPU ON)
    else()
        set(UNKNOWN_CPU OFF)
    endif()
else()
    set(LINUX OFF)
    set(UNKNOWN_CPU OFF)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
    set(E_PATH "@executable_path")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra" CACHE STRING "Fixes linking error for nImO" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS "-headerpad_max_install_names" CACHE STRING "Increases link limit"
        FORCE)
    set(CMAKE_INSTALL_PREFIX "/opt/nImO" CACHE STRING "Fixes install path for nImO" FORCE)
    set(CMAKE_INSTALL_RPATH
"${E_PATH}/../lib;${E_PATH}/../nImO;${E_PATH}/../odl;${E_PATH}/../if;${E_PATH}/../../nImO;${E_PATH}/../../odl;${E_PATH}/../../if;${CMAKE_INSTALL_PREFIX}/lib;${CMAKE_INSTALL_PREFIX}/../odl/lib;${CMAKE_INSTALL_PREFIX}/../if/lib"
        CACHE STRING "Fixes rpath" FORCE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON CACHE BOOL "Make sure to use rpath")
# 'rpath' warning
    cmake_policy(SET CMP0042 OLD)
elseif(LINUX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra" CACHE STRING "Fixes linking error for nImO" FORCE)
    set(CMAKE_INSTALL_PREFIX "/opt/nImO" CACHE STRING "Fixes install path for nImO" FORCE)
    set(CMAKE_INSTALL_RPATH
"${E_PATH}/../lib;${E_PATH}/../nImO;${E_PATH}/../odl;${E_PATH}/../if;${E_PATH}/../../nImO;${E_PATH}/../../odl;${E_PATH}/../../if;${CMAKE_INSTALL_PREFIX}/lib;${CMAKE_INSTALL_PREFIX}/../odl/lib;${CMAKE_INSTALL_PREFIX}/../if/lib"
        CACHE STRING "Fixes rpath" FORCE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON CACHE BOOL "Make sure to use rpath")
else()
    if(NOT ("${CMAKE_EXE_LINKER_FLAGS}" MATCHES ".*NODEFAULTLIB:libcmt.*"))
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt" CACHE STRING
            "Flags used by the linker." FORCE)
    endif()
endif()

set(CMAKE_USE_RELATIVE_PATHS ON CACHE BOOL "Always set file paths as relative")

if(WIN32)
    option(WIN64 "Build 64-bit binaries" ON)
else()
    set(WIN64 OFF)
endif()

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

option(nImO_DO_SWIG "Build the SWIG files" OFF)

# Add the nImO target path so that nImO can be found
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

# Find SWIG
if(nImO_DO_SWIG)
    find_package(SWIG REQUIRED)
    include(${SWIG_USE_FILE})
    set(CMAKE_SWIG_FLAGS "")
endif()

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_DEBUG_LIBS OFF)
set(Boost_USE_RELEASE_LIBS ON)
#find_package(Boost 1.50 REQUIRED COMPONENTS thread system iostreams coroutine program_options timer context)
find_package(Boost 1.50 REQUIRED COMPONENTS exception thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

configure_file("${nImO_SOURCE_DIR}/nImO/nImOconfig.h.in" "${nImO_SOURCE_DIR}/nImO/nImOconfig.h")
configure_file(${nImO_CONFIG_DIR}/nImOConfigVersion.cmake.in
                ${CMAKE_CURRENT_BINARY_DIR}/nImOConfigVersion.cmake @ONLY)

include_directories("${nImO_SOURCE_DIR}/nImO")

if(WIN32)
    set(BONJOUR_DIR "C:/Program Files/Bonjour SDK")
    if(WIN64)
        set(BONJOUR_LIB "${BONJOUR_DIR}/Lib/x64/dnssd.lib")
    else()
        set(BONJOUR_LIB "${BONJOUR_DIR}/Lib/Win32/dnssd.lib")
    endif()
    include_directories("${BONJOUR_DIR}/Include")
else()
    set(BONJOUR_LIB "")
endif()

# The following is to help CMake find ODL...
if(WIN32)
    set(ODL_DIR "C:/Program Files/ODL/lib")
else()
    set(ODL_DIR "/opt/odl/lib")
endif()
find_package(ODL 1.0.0 REQUIRED)
if(ODL_FOUND)
    include_directories(${ODL_INCLUDE_DIRS})
endif()

# The following is to help CMake find IF...
if(WIN32)
    set(IF_DIR "C:/Program Files/IF/lib")
else()
    set(IF_DIR "/opt/if/lib")
endif()
find_package(IF 1.0.0 REQUIRED)
if(IF_FOUND)
    include_directories(${IF_INCLUDE_DIRS})
endif()

# The following is to help CMake find mdns_plusplus...
if(WIN32)
    set(mdns_plusplus_DIR "C:/Program Files/mdns_plusplus/lib")
else()
    set(mdns_plusplus_DIR "/opt/mdns_plusplus/lib")
endif()
find_package(mdns_plusplus 1.0.0 REQUIRED)
if(mdns_plusplus_FOUND)
    include_directories(${mdns_plusplus_INCLUDE_DIRS})
endif()

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

if(WIN32)
    set(OTHER_LIBS "ws2_32.lib")
else()
    set(OTHER_LIBS "")
endif()

#message(${IF_LIBRARY})
#message(${IF_LIBRARY_ROOT})
set(nImO_LINK_LIBRARIES nImOcommon ${ODL_LIBRARY} ${IF_LIBRARY} ${BONJOUR_LIB} ${Boost_LIBRARIES} ${OTHER_LIBS}
    Threads::Threads)

if(LINUX)
#    set(nImO_LINK_LIBRARIES ${nImO_LINK_LIBRARIES} dns_sd)
endif()

if(APPLE)
    function(fix_dynamic_libs target)
        add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                            libnImOcommon.dylib "@rpath/libnImOcommon.dylib" ${target})

        add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                            ${ODL_LIBRARY_ROOT} "@rpath/${ODL_LIBRARY_ROOT}" ${target})

        add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                            ${IF_LIBRARY_ROOT} "@rpath/${IF_LIBRARY_ROOT}" ${target})

    endfunction()
else()
# Do nothing
    function(fix_dynamic_libs target)
    endfunction()
endif()

install(FILES
        ${nImO_CONFIG_DIR}/nImOConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/nImOConfigVersion.cmake
        DESTINATION ${LIB_DEST}
        COMPONENT scripts)

install(PROGRAMS
        ${CMAKE_CURRENT_BINARY_DIR}/nimo.sh
        DESTINATION bin
        COMPONENT applications
        RENAME nimo)

install(EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST})

add_subdirectory(ApplicationSupport)
add_subdirectory(Bridge)
add_subdirectory(Connect)
add_subdirectory(CPack)
add_subdirectory(Disconnect)
add_subdirectory(Info)
add_subdirectory(Launch)
add_subdirectory(List)
add_subdirectory(Monitor)
add_subdirectory(nImO)
add_subdirectory(Post)
add_subdirectory(Read)
add_subdirectory(Registry)
add_subdirectory(Tests)
add_subdirectory(Version)
add_subdirectory(Write)
add_subdirectory(examples)

enable_testing()

#--------------------------------------------------------------------------------------------------
#
#  File:       iOS/nImO/CMakeLists.txt
#
#  Project:    nImO
#
#  Contains:   The CMAKE definitions for the nImO library.
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
#  Created:    2016-02-19
#
#--------------------------------------------------------------------------------------------------

include_directories("${nImO_SOURCE_DIR}")

set(THIS_TARGET nImOcommon)
set(THIS_SOURCE_DIR ${nImO_SOURCE_DIR}/nImO)

macro(ADD_FRAMEWORK fwname appname)
    find_library(FRAMEWORK_${fwname}
                NAMES ${fwname}
                PATHS ${CMAKE_OSX_SYSROOT}/System/Library
                PATH_SUFFIXES Frameworks
                NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        TARGET_LINK_LIBRARIES(${appname} ${FRAMEWORK_${fwname}})
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(ADD_FRAMEWORK)

set(TARGET_ONE nImOCi)

add_library(${TARGET_ONE}
            STATIC
            "${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOarray.cpp"
            "${THIS_SOURCE_DIR}/nImOatom.cpp"
            "${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOblob.cpp"
            "${THIS_SOURCE_DIR}/nImOboolArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImObufferChunk.cpp"
            "${THIS_SOURCE_DIR}/nImOchannel.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelName.cpp"
            "${THIS_SOURCE_DIR}/nImOchunkArray.cpp"
            "${THIS_SOURCE_DIR}/nImOcommon.cpp"
            "${THIS_SOURCE_DIR}/nImOcompareValues.cpp"
            "${THIS_SOURCE_DIR}/nImOcomparisonStatus.cpp"
            "${THIS_SOURCE_DIR}/nImOcontainer.cpp"
            "${THIS_SOURCE_DIR}/nImOconverters.cpp"
            "${THIS_SOURCE_DIR}/nImOdouble.cpp"
            "${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOflaw.cpp"
            "${THIS_SOURCE_DIR}/nImOintArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOinteger.cpp"
            "${THIS_SOURCE_DIR}/nImOinvalid.cpp"
            "${THIS_SOURCE_DIR}/nImOlogical.cpp"
            "${THIS_SOURCE_DIR}/nImOmap.cpp"
            "${THIS_SOURCE_DIR}/nImOmessage.cpp"
            "${THIS_SOURCE_DIR}/nImOnumber.cpp"
            "${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOset.cpp"
            "${THIS_SOURCE_DIR}/nImOstring.cpp"
            "${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOstringBuffer.cpp"
            "${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOvalue.cpp"
            "${THIS_SOURCE_DIR}/nImOzeroConfClient.cpp"
            "${THIS_SOURCE_DIR}/nImOzeroConfService.cpp"
            "${THIS_SOURCE_DIR}/optionparser.cpp")
#target_include_directories(${TARGET_ONE} PUBLIC
#                            $<BUILD_INTERFACE:${nImO_SOURCE_DIR}> # for headers when building
#                            $<INSTALL_INTERFACE:${INCLUDE_DEST}> # for client in install mode
#                            )

install(TARGETS
        ${TARGET_ONE}
        EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST}
        COMPONENT libraries)

set(TARGET_TWO nImOOCi)

add_library(${TARGET_TWO}
            STATIC
            "${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOarray.cpp"
            "${THIS_SOURCE_DIR}/nImOatom.cpp"
            "${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOblob.cpp"
            "${THIS_SOURCE_DIR}/nImOboolArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImObufferChunk.cpp"
            "${THIS_SOURCE_DIR}/nImOchannel.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelName.cpp"
            "${THIS_SOURCE_DIR}/nImOchunkArray.cpp"
            "${THIS_SOURCE_DIR}/nImOcommon.cpp"
            "${THIS_SOURCE_DIR}/nImOcompareValues.cpp"
            "${THIS_SOURCE_DIR}/nImOcomparisonStatus.cpp"
            "${THIS_SOURCE_DIR}/nImOcontainer.cpp"
            "${THIS_SOURCE_DIR}/nImOconverters.cpp"
            "${THIS_SOURCE_DIR}/nImOdouble.cpp"
            "${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOflaw.cpp"
            "${THIS_SOURCE_DIR}/nImOintArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOinteger.cpp"
            "${THIS_SOURCE_DIR}/nImOinvalid.cpp"
            "${THIS_SOURCE_DIR}/nImOlogical.cpp"
            "${THIS_SOURCE_DIR}/nImOmap.cpp"
            "${THIS_SOURCE_DIR}/nImOmessage.cpp"
            "${THIS_SOURCE_DIR}/nImOnumber.cpp"
            "${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOset.cpp"
            "${THIS_SOURCE_DIR}/nImOstring.cpp"
            "${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOstringBuffer.cpp"
            "${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOvalue.cpp"
            "${THIS_SOURCE_DIR}/nImOzeroConfClient.cpp"
            "${THIS_SOURCE_DIR}/nImOzeroConfService.cpp"
            "${THIS_SOURCE_DIR}/optionparser.cpp")
add_framework(Foundation ${TARGET_TWO})
#target_include_directories(${TARGET_TWO} PUBLIC
#                            $<BUILD_INTERFACE:${nImO_SOURCE_DIR}> # for headers when building
#                            $<INSTALL_INTERFACE:${INCLUDE_DEST}> # for client in install mode
#                            )
install(TARGETS
        ${TARGET_TWO}
        EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST}
        COMPONENT libraries)

install(FILES
        "${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOarray.h"
        "${THIS_SOURCE_DIR}/nImOatom.h"
        "${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOblob.h"
        "${THIS_SOURCE_DIR}/nImObooleanArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImObufferChunk.h"
        "${THIS_SOURCE_DIR}/nImOchannel.h"
        "${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOchannelName.h"
        "${THIS_SOURCE_DIR}/nImOchunkArray.h"
        "${THIS_SOURCE_DIR}/nImOcommon.h"
        "${THIS_SOURCE_DIR}/nImOcompareValues.h"
        "${THIS_SOURCE_DIR}/nImOcomparisonStatus.h"
        "${THIS_SOURCE_DIR}/nImOcontainer.h"
        "${THIS_SOURCE_DIR}/nImOconverters.h"
        "${THIS_SOURCE_DIR}/nImOdouble.h"
        "${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOflaw.h"
        "${THIS_SOURCE_DIR}/nImOintegerArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOinteger.h"
        "${THIS_SOURCE_DIR}/nImOinvalid.h"
        "${THIS_SOURCE_DIR}/nImOlogical.h"
        "${THIS_SOURCE_DIR}/nImOmap.h"
        "${THIS_SOURCE_DIR}/nImOmessage.h"
        "${THIS_SOURCE_DIR}/nImOnumber.h"
        "${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOset.h"
        "${THIS_SOURCE_DIR}/nImOstring.h"
        "${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOstringBuffer.h"
        "${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOvalue.h"
        "${THIS_SOURCE_DIR}/nImOzeroConfClient.h"
        "${THIS_SOURCE_DIR}/nImOzeroConfService.h"
        "${THIS_SOURCE_DIR}/optionparser.h"
        DESTINATION ${INCLUDE_DEST}
        COMPONENT headers)

install(EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST})

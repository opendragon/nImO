#
#  nImOConfig.cmake
#  ----------------------------------
#
#  Project 	nImO
#  Created by 	Norman Jaffe on 2017/04/14
#
#  Copyright:  (c) 2017 by OpenDragon.
#
#  All rights reserved. Redistribution and use in source and binary forms, with or
#  without modification, are permitted provided that the following conditions are met:
#  * Redistributions of source code must retain the above copyright notice, this list
#  of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright notice, this
#  list of conditions and the following disclaimer in the documentation and / or
#  other materials provided with the distribution.
#  * Neither the name of the copyright holders nor the names of its contributors may
#  be used to endorse or promote products derived from this software without
#  specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
#  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
#  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
#  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
#  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
#  DAMAGE.

get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/nImO.cmake)

get_filename_component(PARENT_DIR "${SELF_DIR}" PATH)
set(nImO_INCLUDE_DIRS "${PARENT_DIR}/include")
if(WIN32)
    set(nImO_LIBRARY "${SELF_DIR}/nImOcommon.lib")
elseif(APPLE)
    set(nImO_LIBRARY "${SELF_DIR}/libnImOcommon.dylib")
    set(nImO_LIBRARY_ROOT "libnImOcommon.dylib")
else()
    set(nImO_LIBRARY "${SELF_DIR}/libnImOcommon.a")
endif()

message(STATUS "nImO version: ${nImO_VERSION}")

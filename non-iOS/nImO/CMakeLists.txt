#--------------------------------------------------------------------------------------------------
#
#  File:       non-iOS/nImO/CMakeLists.txt
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
set(OTHER_TARGET_CSHARP nImOcommon_swig_csharp)
set(OTHER_TARGET_PYTHON nImOcommon_swig_python)

if(APPLE)
    set(DO_SHARED "SHARED")
    set(THIS_TARGET_LIB "lib${THIS_TARGET}.dylib")
elseif(LINUX)
    set(DO_SHARED "SHARED")
else()
    set(DO_SHARED "")
endif()

add_library(${THIS_TARGET}
            "${DO_SHARED}"
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

target_link_libraries(${THIS_TARGET}
                        ${ODL_LIBRARY}
                        ${BONJOUR_LIB})

if(LINUX)
    target_link_libraries(${THIS_TARGET}
                          pthread)
endif()

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        ${ODL_LIBRARY_ROOT} ${ODL_LIBRARY} ${THIS_TARGET_LIB})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -id
                        ${THIS_TARGET_LIB} ${THIS_TARGET_LIB})
endif()

install(TARGETS ${THIS_TARGET}
        EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST}
        COMPONENT libraries)

install(FILES
        "${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOarray.hpp"
        "${THIS_SOURCE_DIR}/nImOatom.hpp"
        "${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOblob.hpp"
        "${THIS_SOURCE_DIR}/nImOboolArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImObufferChunk.hpp"
        "${THIS_SOURCE_DIR}/nImOchannel.hpp"
        "${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOchannelName.hpp"
        "${THIS_SOURCE_DIR}/nImOchunkArray.hpp"
        "${THIS_SOURCE_DIR}/nImOcommon.hpp"
        "${THIS_SOURCE_DIR}/nImOcompareValues.hpp"
        "${THIS_SOURCE_DIR}/nImOcomparisonStatus.hpp"
        "${THIS_SOURCE_DIR}/nImOcontainer.hpp"
        "${THIS_SOURCE_DIR}/nImOconverters.hpp"
        "${THIS_SOURCE_DIR}/nImOdouble.hpp"
        "${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOflaw.hpp"
        "${THIS_SOURCE_DIR}/nImOintArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOinteger.hpp"
        "${THIS_SOURCE_DIR}/nImOinvalid.hpp"
        "${THIS_SOURCE_DIR}/nImOlogical.hpp"
        "${THIS_SOURCE_DIR}/nImOmap.hpp"
        "${THIS_SOURCE_DIR}/nImOmessage.hpp"
        "${THIS_SOURCE_DIR}/nImOnumber.hpp"
        "${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOset.hpp"
        "${THIS_SOURCE_DIR}/nImOstring.hpp"
        "${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOstringBuffer.hpp"
        "${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.hpp"
        "${THIS_SOURCE_DIR}/nImOvalue.hpp"
        "${THIS_SOURCE_DIR}/nImOzeroConfClient.hpp"
        "${THIS_SOURCE_DIR}/nImOzeroConfService.hpp"
        "${THIS_SOURCE_DIR}/optionparser.hpp"
        DESTINATION ${INCLUDE_DEST}
        COMPONENT headers)

if(nImO_DO_SWIG)
    set(nImO_SWIG_SOURCES ${THIS_SOURCE_DIR}/swig_nImO_in/nImOcommon.i
        ${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOarray.cpp ${THIS_SOURCE_DIR}/nImOarray.hpp
        ${THIS_SOURCE_DIR}/nImOatom.cpp ${THIS_SOURCE_DIR}/nImOatom.hpp
        ${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOblob.cpp ${THIS_SOURCE_DIR}/nImOblob.hpp
        ${THIS_SOURCE_DIR}/nImOboolArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOboolArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImObufferChunk.cpp ${THIS_SOURCE_DIR}/nImObufferChunk.hpp
        ${THIS_SOURCE_DIR}/nImOchannel.cpp ${THIS_SOURCE_DIR}/nImOchannel.hpp
        ${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOchannelName.cpp ${THIS_SOURCE_DIR}/nImOchannelName.hpp
        ${THIS_SOURCE_DIR}/nImOchunkArray.cpp ${THIS_SOURCE_DIR}/nImOchunkArray.hpp
        ${THIS_SOURCE_DIR}/nImOcommon.cpp ${THIS_SOURCE_DIR}/nImOcommon.hpp
        ${THIS_SOURCE_DIR}/nImOcompareValues.cpp ${THIS_SOURCE_DIR}/nImOcompareValues.hpp
        ${THIS_SOURCE_DIR}/nImOcomparisonStatus.cpp ${THIS_SOURCE_DIR}/nImOcomparisonStatus.hpp
        ${THIS_SOURCE_DIR}/nImOcontainer.cpp ${THIS_SOURCE_DIR}/nImOcontainer.hpp
        ${THIS_SOURCE_DIR}/nImOconverters.cpp ${THIS_SOURCE_DIR}/nImOconverters.hpp
        ${THIS_SOURCE_DIR}/nImOdouble.cpp ${THIS_SOURCE_DIR}/nImOdouble.hpp
        ${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOflaw.cpp ${THIS_SOURCE_DIR}/nImOflaw.hpp
        ${THIS_SOURCE_DIR}/nImOintArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOintArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOinteger.cpp ${THIS_SOURCE_DIR}/nImOinteger.hpp
        ${THIS_SOURCE_DIR}/nImOinvalid.cpp ${THIS_SOURCE_DIR}/nImOinvalid.hpp
        ${THIS_SOURCE_DIR}/nImOlogical.cpp ${THIS_SOURCE_DIR}/nImOlogical.hpp
        ${THIS_SOURCE_DIR}/nImOmap.cpp ${THIS_SOURCE_DIR}/nImOmap.hpp
        ${THIS_SOURCE_DIR}/nImOmessage.cpp ${THIS_SOURCE_DIR}/nImOmessage.hpp
        ${THIS_SOURCE_DIR}/nImOnumber.cpp ${THIS_SOURCE_DIR}/nImOnumber.hpp
        ${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOset.cpp ${THIS_SOURCE_DIR}/nImOset.hpp
        ${THIS_SOURCE_DIR}/nImOstring.cpp ${THIS_SOURCE_DIR}/nImOstring.hpp
        ${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOstringBuffer.cpp ${THIS_SOURCE_DIR}/nImOstringBuffer.hpp
        ${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.hpp
        ${THIS_SOURCE_DIR}/nImOvalue.cpp ${THIS_SOURCE_DIR}/nImOvalue.hpp
        ${THIS_SOURCE_DIR}/nImOzeroConfClient.cpp ${THIS_SOURCE_DIR}/nImOzeroConfClient.hpp
        ${THIS_SOURCE_DIR}/nImOzeroConfService.cpp ${THIS_SOURCE_DIR}/nImOzeroConfService.hpp)

    include_directories("${nImO_SOURCE_DIR}/nImO")
    set_source_files_properties(swig_nImO_in/nImOcommon.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(swig_nImO_in/nImOcommon.i PROPERTIES SWIG_FLAGS "-includeall")

    set(CMAKE_SWIG_OUTDIR "${THIS_SOURCE_DIR}/swig_nImO_out_csharp")

    swig_add_module(${OTHER_TARGET_CSHARP} csharp ${nImO_SWIG_SOURCES})

    swig_link_libraries(${OTHER_TARGET_CSHARP}
                        ${THIS_TARGET}
                        ${ODL_LIBRARY})

    install(TARGETS ${OTHER_TARGET_CSHARP}
            EXPORT ${PROJECT_NAME}
            DESTINATION ${LIB_DEST}
            COMPONENT libraries)

    install(FILES
            swig_nImO_out_csharp/nImO.cs
            swig_nImO_out_csharp/nImOPINVOKE.cs
            DESTINATION csharp/nImO
            COMPONENT headers)

    set(CMAKE_SWIG_OUTDIR "${THIS_SOURCE_DIR}/swig_nImO_out_python")

    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_PATH})

    swig_add_module(${OTHER_TARGET_PYTHON} python ${nImO_SWIG_SOURCES})

    swig_link_libraries(${OTHER_TARGET_PYTHON}
                        ${THIS_TARGET}
                        ${ODL_LIBRARY}
                        ${PYTHON_LIBRARIES})

# Note the modified target name!
    install(TARGETS _${OTHER_TARGET_PYTHON}
            EXPORT ${PROJECT_NAME}
            DESTINATION ${LIB_DEST}
            COMPONENT libraries)

    install(FILES
            swig_nImO_out_python/nImO.py
            swig_nImO_out_python/nImOcommonPYTHON_wrap.cxx
            DESTINATION python/nImO
            COMPONENT headers)

endif()

enable_testing()

#packing stuff

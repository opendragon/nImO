#--------------------------------------------------------------------------------------------------
#
#  File:       nImO/CMakeLists.txt
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
set(OTHER_TARGET_CSHARP nImOcommon_swig_csharp)
set(OTHER_TARGET_PYTHON nImOcommon_swig_python)

if(APPLE)
    set(DO_SHARED "SHARED")
    set(THIS_TARGET_LIB "lib${THIS_TARGET}.dylib")
else()
    set(DO_SHARED "")
endif()

add_library(${THIS_TARGET}
            "${DO_SHARED}"
            "${nImO_SOURCE_DIR}/nImO/nImOaddressArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOarray.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOatom.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImObaseArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOblob.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOboolArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImObufferChunk.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOchannelArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOchunkArray.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOcommon.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOcompareValues.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOconnector.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOcontainer.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOconverters.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOdouble.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOdoubleArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOextraArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOfilePathArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOflaw.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOintArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOinteger.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOinvalid.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOlogical.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOmap.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOmessage.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOnumber.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOportArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOset.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOstring.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOstringArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOstringBuffer.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOvalue.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOzeroConfClient.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOzeroConfService.cpp"
            "${nImO_SOURCE_DIR}/nImO/optionparser.cpp")

target_link_libraries(${THIS_TARGET}
                        ${ODL_LIBRARIES}
                        ${BONJOUR_LIB})

if(LINUX)
    target_link_libraries(${THIS_TARGET}
                          pthread)
endif()

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        ${ODL_LIBRARY_ROOT} ${ODL_LIBRARY} ${THIS_TARGET_LIB})
endif()

install(TARGETS ${THIS_TARGET}
        EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST}
        COMPONENT libraries)

install(FILES
        "${nImO_SOURCE_DIR}/nImO/nImOaddressArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOarray.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOatom.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImObaseArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOblob.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOboolArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImObufferChunk.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOchannelArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOchunkArray.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOcommon.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOcompareValues.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOconnector.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOcontainer.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOconverters.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOdouble.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOdoubleArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOextraArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOfilePathArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOflaw.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOintArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOinteger.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOinvalid.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOlogical.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOmap.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOmessage.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOnumber.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOportArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOset.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOstring.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOstringArgumentDescriptor.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOstringBuffer.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOvalue.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOzeroConfClient.hpp"
        "${nImO_SOURCE_DIR}/nImO/nImOzeroConfService.hpp"
        "${nImO_SOURCE_DIR}/nImO/optionparser.hpp"
        DESTINATION ${INCLUDE_DEST}
        COMPONENT headers)

if(nImO_DO_SWIG)
    set(nImO_SWIG_SOURCES swig_nImO_in/nImOcommon.i
        nImOaddressArgumentDescriptor.cpp nImOaddressArgumentDescriptor.hpp
        nImOarray.cpp nImOarray.hpp
        nImOatom.cpp nImOatom.hpp
        nImObaseArgumentDescriptor.cpp nImObaseArgumentDescriptor.hpp
        nImOblob.cpp nImOblob.hpp
        nImOboolArgumentDescriptor.cpp nImOboolArgumentDescriptor.hpp
        nImObufferChunk.cpp nImObufferChunk.hpp
        nImOchannelArgumentDescriptor.cpp nImOchannelArgumentDescriptor.hpp
        nImOchunkArray.cpp nImOchunkArray.hpp
        nImOcommon.cpp nImOcommon.hpp
        nImOcompareValues.cpp nImOcompareValues.hpp
        nImOconnector.cpp nImOconnector.hpp
        nImOcontainer.cpp nImOcontainer.hpp
        nImOconverters.cpp nImOconverters.hpp
        nImOdouble.cpp nImOdouble.hpp
        nImOdoubleArgumentDescriptor.cpp nImOdoubleArgumentDescriptor.hpp
        nImOextraArgumentDescriptor.cpp nImOextraArgumentDescriptor.hpp
        nImOfilePathArgumentDescriptor.cpp nImOfilePathArgumentDescriptor.hpp
        nImOflaw.cpp nImOflaw.hpp
        nImOintArgumentDescriptor.cpp nImOintArgumentDescriptor.hpp
        nImOinteger.cpp nImOinteger.hpp
        nImOinvalid.cpp nImOinvalid.hpp
        nImOlogical.cpp nImOlogical.hpp
        nImOmap.cpp nImOmap.hpp
        nImOmessage.cpp nImOmessage.hpp
        nImOnumber.cpp nImOnumber.hpp
        nImOportArgumentDescriptor.cpp nImOportArgumentDescriptor.hpp
        nImOset.cpp nImOset.hpp
        nImOstring.cpp nImOstring.hpp
        nImOstringArgumentDescriptor.cpp nImOstringArgumentDescriptor.hpp
        nImOstringBuffer.cpp nImOstringBuffer.hpp
        nImOvalue.cpp nImOvalue.hpp
        nImOzeroConfClient.cpp mImOzeroConfClient.hpp
        nImOzeroConfService.cpp mImOzeroConfService.hpp)

    include_directories("${nImO_SOURCE_DIR}/nImO")
    set_source_files_properties(swig_nImO_in/nImOcommon.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(swig_nImO_in/nImOcommon.i PROPERTIES SWIG_FLAGS "-includeall")

    set(CMAKE_SWIG_OUTDIR "${nImO_SOURCE_DIR}/nImO/swig_nImO_out_csharp")

    swig_add_module(${OTHER_TARGET_CSHARP} csharp ${nImO_SWIG_SOURCES})

    swig_link_libraries(${OTHER_TARGET_CSHARP}
                        ${THIS_TARGET}
                        ${ODL_LIBRARIES})

    install(TARGETS ${OTHER_TARGET_CSHARP}
            EXPORT ${PROJECT_NAME}
            DESTINATION ${LIB_DEST}
            COMPONENT libraries)

    install(FILES
            swig_nImO_out_csharp/nImO.cs
            swig_nImO_out_csharp/nImOPINVOKE.cs
            DESTINATION csharp/nImO
            COMPONENT headers)

    set(CMAKE_SWIG_OUTDIR "${nImO_SOURCE_DIR}/nImO/swig_nImO_out_python")

    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_PATH})

    swig_add_module(${OTHER_TARGET_PYTHON} python ${nImO_SWIG_SOURCES})

    swig_link_libraries(${OTHER_TARGET_PYTHON}
                        ${THIS_TARGET}
                        ${ODL_LIBRARIES}
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

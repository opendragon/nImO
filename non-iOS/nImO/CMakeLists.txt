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
    set(THIS_TARGET_LIB "lib${THIS_TARGET}.so")
elseif(UNIX)
    set(DO_SHARED "SHARED")
    set(THIS_TARGET_LIB "lib${THIS_TARGET}.so")
else()
    set(DO_SHARED "")
endif()

add_library(${THIS_TARGET}
            "${DO_SHARED}"
            "${THIS_SOURCE_DIR}/nImOaddNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOannounceServiceData.cpp"
            "${THIS_SOURCE_DIR}/nImOarray.cpp"
            "${THIS_SOURCE_DIR}/nImOatom.cpp"
            "${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImObaseChannel.cpp"
            "${THIS_SOURCE_DIR}/nImOblob.cpp"
            "${THIS_SOURCE_DIR}/nImObooleanArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImObufferChunk.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelName.cpp"
            "${THIS_SOURCE_DIR}/nImOchunkArray.cpp"
            "${THIS_SOURCE_DIR}/nImOcommandHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOcommandSession.cpp"
            "${THIS_SOURCE_DIR}/nImOcommon.cpp"
            "${THIS_SOURCE_DIR}/nImOcompareValues.cpp"
            "${THIS_SOURCE_DIR}/nImOcomparisonStatus.cpp"
            "${THIS_SOURCE_DIR}/nImOcontainer.cpp"
            "${THIS_SOURCE_DIR}/nImOcontext.cpp"
            "${THIS_SOURCE_DIR}/nImOcontextWithMDNS.cpp"
            "${THIS_SOURCE_DIR}/nImOcontextWithNetworking.cpp"
            "${THIS_SOURCE_DIR}/nImOconverters.cpp"
            "${THIS_SOURCE_DIR}/nImOdouble.cpp"
            "${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOfilterContext.cpp"
            "${THIS_SOURCE_DIR}/nImOflaw.cpp"
            "${THIS_SOURCE_DIR}/nImOgetInformationForAllMachinesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetLaunchDetailsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetMachineInformationResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetNamesOfMachinesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetNamesOfNodesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetNamesOfNodesOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetNodeInformationResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetNumberOfMachinesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetNumberOfNodesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOgetNumberOfNodesOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOinChannel.cpp"
            "${THIS_SOURCE_DIR}/nImOinputOutputContext.cpp"
            "${THIS_SOURCE_DIR}/nImOinteger.cpp"
            "${THIS_SOURCE_DIR}/nImOintegerArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOinvalid.cpp"
            "${THIS_SOURCE_DIR}/nImOisMachinePresentResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOisNodePresentResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOlogger.cpp"
            "${THIS_SOURCE_DIR}/nImOlogical.cpp"
            "${THIS_SOURCE_DIR}/nImOmainSupport.cpp"
            "${THIS_SOURCE_DIR}/nImOmap.cpp"
            "${THIS_SOURCE_DIR}/nImOmessage.cpp"
            "${THIS_SOURCE_DIR}/nImOMIMESupport.cpp"
            "${THIS_SOURCE_DIR}/nImOmiscellaneousContext.cpp"
            "${THIS_SOURCE_DIR}/nImOnumber.cpp"
            "${THIS_SOURCE_DIR}/nImOoutChannel.cpp"
            "${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOregistryProxy.cpp"
            "${THIS_SOURCE_DIR}/nImOremoveNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOrequestResponse.cpp"
            "${THIS_SOURCE_DIR}/nImOresponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOserviceContext.cpp"
            "${THIS_SOURCE_DIR}/nImOserviceOptions.cpp"
            "${THIS_SOURCE_DIR}/nImOset.cpp"
            "${THIS_SOURCE_DIR}/nImOshutdownCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOsinkContext.cpp"
            "${THIS_SOURCE_DIR}/nImOsourceContext.cpp"
            "${THIS_SOURCE_DIR}/nImOstandardOptions.cpp"
            "${THIS_SOURCE_DIR}/nImOstring.cpp"
            "${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOstringBuffer.cpp"
            "${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/nImOtestContext.cpp"
            "${THIS_SOURCE_DIR}/nImOutilityContext.cpp"
            "${THIS_SOURCE_DIR}/nImOvalue.cpp"
            "${THIS_SOURCE_DIR}/optionparser.cpp")

target_link_libraries(${THIS_TARGET} ${ODL_LIBRARY} ${IF_LIBRARY} ${BONJOUR_LIB} ${Boost_LIBRARIES})

if(LINUX)
    target_link_libraries(${THIS_TARGET}
                          pthread)
endif()

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        ${ODL_LIBRARY_ROOT} ${ODL_LIBRARY} ${THIS_TARGET_LIB})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        ${IF_LIBRARY_ROOT} ${IF_LIBRARY} ${THIS_TARGET_LIB})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -id
                        ${THIS_TARGET_LIB} ${THIS_TARGET_LIB})

endif()

install(TARGETS ${THIS_TARGET}
        EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST}
        COMPONENT libraries)

install(FILES
        "${THIS_SOURCE_DIR}/nImOaddNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOannounceServiceData.h"
        "${THIS_SOURCE_DIR}/nImOarray.h"
        "${THIS_SOURCE_DIR}/nImOatom.h"
        "${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImObaseChannel.h"
        "${THIS_SOURCE_DIR}/nImOblob.h"
        "${THIS_SOURCE_DIR}/nImObooleanArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImObufferChunk.h"
        "${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOchannelName.h"
        "${THIS_SOURCE_DIR}/nImOchunkArray.h"
        "${THIS_SOURCE_DIR}/nImOcommandHandler.h"
        "${THIS_SOURCE_DIR}/nImOcommandSession.h"
        "${THIS_SOURCE_DIR}/nImOcommon.h"
        "${THIS_SOURCE_DIR}/nImOcommonCommands.h"
        "${THIS_SOURCE_DIR}/nImOcompareValues.h"
        "${THIS_SOURCE_DIR}/nImOcomparisonStatus.h"
        "${THIS_SOURCE_DIR}/nImOconfig.h"
        "${THIS_SOURCE_DIR}/nImOcontainer.h"
        "${THIS_SOURCE_DIR}/nImOcontext.h"
        "${THIS_SOURCE_DIR}/nImOcontextWithMDNS.h"
        "${THIS_SOURCE_DIR}/nImOcontextWithNetworking.h"
        "${THIS_SOURCE_DIR}/nImOconverters.h"
        "${THIS_SOURCE_DIR}/nImOdouble.h"
        "${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOfilterContext.h"
        "${THIS_SOURCE_DIR}/nImOflaw.h"
        "${THIS_SOURCE_DIR}/nImOgetInformationForAllMachinesResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetLaunchDetailsResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetMachineInformationResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetNamesOfMachinesResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetNamesOfNodesResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetNamesOfNodesOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetNodeInformationResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetNumberOfMachinesResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetNumberOfNodesResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOgetNumberOfNodesOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOinChannel.h"
        "${THIS_SOURCE_DIR}/nImOinputOutputContext.h"
        "${THIS_SOURCE_DIR}/nImOinteger.h"
        "${THIS_SOURCE_DIR}/nImOintegerArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOinvalid.h"
        "${THIS_SOURCE_DIR}/nImOisMachinePresentResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOisNodePresentResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOlogger.h"
        "${THIS_SOURCE_DIR}/nImOlogical.h"
        "${THIS_SOURCE_DIR}/nImOmainSupport.h"
        "${THIS_SOURCE_DIR}/nImOmap.h"
        "${THIS_SOURCE_DIR}/nImOmessage.h"
        "${THIS_SOURCE_DIR}/nImOMIMESupport.h"
        "${THIS_SOURCE_DIR}/nImOmiscellaneousContext.h"
        "${THIS_SOURCE_DIR}/nImOnumber.h"
        "${THIS_SOURCE_DIR}/nImOoutChannel.h"
        "${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOregistryCommands.h"
        "${THIS_SOURCE_DIR}/nImOregistryProxy.h"
        "${THIS_SOURCE_DIR}/nImOregistryTypes.h"
        "${THIS_SOURCE_DIR}/nImOremoveNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOrequestResponse.h"
        "${THIS_SOURCE_DIR}/nImOresponseHandler.h"
        "${THIS_SOURCE_DIR}/nImOserviceContext.h"
        "${THIS_SOURCE_DIR}/nImOserviceOptions.h"
        "${THIS_SOURCE_DIR}/nImOset.h"
        "${THIS_SOURCE_DIR}/nImOshutdownCommandHandler.h"
        "${THIS_SOURCE_DIR}/nImOsinkContext.h"
        "${THIS_SOURCE_DIR}/nImOsourceContext.h"
        "${THIS_SOURCE_DIR}/nImOstandardOptions.h"
        "${THIS_SOURCE_DIR}/nImOstring.h"
        "${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOstringBuffer.h"
        "${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/nImOtestContext.h"
        "${THIS_SOURCE_DIR}/nImOutilityContext.h"
        "${THIS_SOURCE_DIR}/nImOvalue.h"
        "${THIS_SOURCE_DIR}/optionparser.hpp"
        DESTINATION ${INCLUDE_DEST}
        COMPONENT headers)

if(nImO_DO_SWIG)
    set(nImO_SWIG_SOURCES ${THIS_SOURCE_DIR}/swig_nImO_in/nImOcommon.i
        ${THIS_SOURCE_DIR}/nImOaddNodeResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOaddNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOaddressArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOannounceServiceData.cpp ${THIS_SOURCE_DIR}/nImOannounceServiceData.h
        ${THIS_SOURCE_DIR}/nImOarray.cpp ${THIS_SOURCE_DIR}/nImOarray.h
        ${THIS_SOURCE_DIR}/nImOatom.cpp ${THIS_SOURCE_DIR}/nImOatom.h
        ${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImObaseArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImObaseChannel.cpp ${THIS_SOURCE_DIR}/nImObaseChannel.h
        ${THIS_SOURCE_DIR}/nImOblob.cpp ${THIS_SOURCE_DIR}/nImOblob.h
        ${THIS_SOURCE_DIR}/nImObooleanArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImObooleanArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImObufferChunk.cpp ${THIS_SOURCE_DIR}/nImObufferChunk.h
        ${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOchannelArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOchannelName.cpp ${THIS_SOURCE_DIR}/nImOchannelName.h
        ${THIS_SOURCE_DIR}/nImOchunkArray.cpp ${THIS_SOURCE_DIR}/nImOchunkArray.h
        ${THIS_SOURCE_DIR}/nImOcommandHandler.cpp ${THIS_SOURCE_DIR}/nImOcommandHandler.h
        ${THIS_SOURCE_DIR}/nImOcommandSession.cpp ${THIS_SOURCE_DIR}/nImOcommandSession.h
        ${THIS_SOURCE_DIR}/nImOcommon.cpp ${THIS_SOURCE_DIR}/nImOcommon.h
        ${THIS_SOURCE_DIR}/nImOcommonCommands.h
        ${THIS_SOURCE_DIR}/nImOcompareValues.cpp ${THIS_SOURCE_DIR}/nImOcompareValues.h
        ${THIS_SOURCE_DIR}/nImOcomparisonStatus.cpp ${THIS_SOURCE_DIR}/nImOcomparisonStatus.h
        ${THIS_SOURCE_DIR}/nImOcontainer.cpp ${THIS_SOURCE_DIR}/nImOcontainer.h
        ${THIS_SOURCE_DIR}/nImOcontext.cpp ${THIS_SOURCE_DIR}/nImOcontext.h
        ${THIS_SOURCE_DIR}/nImOcontextWithMDNS.cpp ${THIS_SOURCE_DIR}/nImOcontextWithMDNS.h
        ${THIS_SOURCE_DIR}/nImOcontextWithNetworking.cpp ${THIS_SOURCE_DIR}/nImOcontextWithNetworking.h
        ${THIS_SOURCE_DIR}/nImOconverters.cpp ${THIS_SOURCE_DIR}/nImOconverters.h
        ${THIS_SOURCE_DIR}/nImOdouble.cpp ${THIS_SOURCE_DIR}/nImOdouble.h
        ${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOdoubleArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOextraArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOfilePathArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOfilterContext.cpp ${THIS_SOURCE_DIR}/nImOfilterContext.h
        ${THIS_SOURCE_DIR}/nImOflaw.cpp ${THIS_SOURCE_DIR}/nImOflaw.h
        ${THIS_SOURCE_DIR}/nImOgetInformationForAllMachinesResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetInformationForAllMachinesResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesOnMachineResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetInformationForAllNodesOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetLaunchDetailsResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetLaunchDetailsResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetMachineInformationResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetMachineInformationResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetNamesOfMachinesResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetNamesOfMachinesResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetNamesOfNodesResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetNamesOfNodesResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetNamesOfNodesOnMachineResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetNamesOfNodesOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetNodeInformationResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetNodeInformationResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetNumberOfMachinesResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetNumberOfMachinesResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetNumberOfNodesResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetNumberOfNodesResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOgetNumberOfNodesOnMachineResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOgetNumberOfNodesOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOinChannel.cpp ${THIS_SOURCE_DIR}/nImOinChannel.h
        ${THIS_SOURCE_DIR}/nImOinputOutputContext.cpp ${THIS_SOURCE_DIR}/nImOinputOutputContext.h
        ${THIS_SOURCE_DIR}/nImOinteger.cpp ${THIS_SOURCE_DIR}/nImOinteger.h
        ${THIS_SOURCE_DIR}/nImOintegerArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOintegerArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOinvalid.cpp ${THIS_SOURCE_DIR}/nImOinvalid.h
        ${THIS_SOURCE_DIR}/nImOisMachinePresentResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOisMachinePresentResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOisNodePresentResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOisNodePresentResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOlogger.cpp ${THIS_SOURCE_DIR}/nImOlogger.h
        ${THIS_SOURCE_DIR}/nImOlogical.cpp ${THIS_SOURCE_DIR}/nImOlogical.h
        ${THIS_SOURCE_DIR}/nImOmainSupport.cpp ${THIS_SOURCE_DIR}/nImOmainSupport.h
        ${THIS_SOURCE_DIR}/nImOmap.cpp ${THIS_SOURCE_DIR}/nImOmap.h
        ${THIS_SOURCE_DIR}/nImOmessage.cpp ${THIS_SOURCE_DIR}/nImOmessage.h
        ${THIS_SOURCE_DIR}/nImOMIMESupport.cpp ${THIS_SOURCE_DIR}/nImOMIMESupport.h
        ${THIS_SOURCE_DIR}/nImOmiscellaneousContext.cpp ${THIS_SOURCE_DIR}/nImOmiscellaneousContext.h
        ${THIS_SOURCE_DIR}/nImOnumber.cpp ${THIS_SOURCE_DIR}/nImOnumber.h
        ${THIS_SOURCE_DIR}/nImOoutChannel.cpp ${THIS_SOURCE_DIR}/nImOoutChannel.h
        ${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOportArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOregistryCommands.h
        ${THIS_SOURCE_DIR}/nImOregistryProxy.cpp ${THIS_SOURCE_DIR}/nImOregistryProxy.h
        ${THIS_SOURCE_DIR}/nImOregistryTypes.h
        ${THIS_SOURCE_DIR}/nImOremoveNodeResponseHandler.cpp ${THIS_SOURCE_DIR}/nImOremoveNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOrequestResponse.cpp ${THIS_SOURCE_DIR}/nImOrequestResponse.h
        ${THIS_SOURCE_DIR}/nImOresponseHandler.cpp ${THIS_SOURCE_DIR}/nImOresponseHandler.h
        ${THIS_SOURCE_DIR}/nImOserviceContext.cpp ${THIS_SOURCE_DIR}/nImOserviceContext.h
        ${THIS_SOURCE_DIR}/nImOserviceOptions.cpp ${THIS_SOURCE_DIR}/nImOserviceOptions.h
        ${THIS_SOURCE_DIR}/nImOset.cpp ${THIS_SOURCE_DIR}/nImOset.h
        ${THIS_SOURCE_DIR}/nImOsourceContext.cpp ${THIS_SOURCE_DIR}/nImOsourceContext.h
        ${THIS_SOURCE_DIR}/nImOshutdownCommandHandler.cpp ${THIS_SOURCE_DIR}/nImOshutdownCommandHandler.h
        ${THIS_SOURCE_DIR}/nImOsinkContext.cpp ${THIS_SOURCE_DIR}/nImOsinkContext.h
        ${THIS_SOURCE_DIR}/nImOstandardOptions.cpp ${THIS_SOURCE_DIR}/nImOstandardOptions.h
        ${THIS_SOURCE_DIR}/nImOstring.cpp ${THIS_SOURCE_DIR}/nImOstring.h
        ${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOstringArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOstringBuffer.cpp ${THIS_SOURCE_DIR}/nImOstringBuffer.h
        ${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.cpp ${THIS_SOURCE_DIR}/nImOstringsArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/nImOtestContext.cpp ${THIS_SOURCE_DIR}/nImOtestContext.h
        ${THIS_SOURCE_DIR}/nImOutilityContext.cpp ${THIS_SOURCE_DIR}/nImOutilityContext.h
        ${THIS_SOURCE_DIR}/nImOvalue.cpp ${THIS_SOURCE_DIR}/nImOvalue.h)

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

#--------------------------------------------------------------------------------------------------
#
#  File:       Common/CMakeLists.txt
#
#  Project:    nImO
#
#  Contains:   The CMAKE definitions for the nImO common libraries.
#
#  Written by: Norman Jaffe
#
#  Copyright:  (c) 2014 by H Plus Technologies Ltd. and Simon Fraser University.
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
#  Created:    2014-02-06
#
#--------------------------------------------------------------------------------------------------

include_directories("${nImO_SOURCE_DIR}")

set(THIS_TARGET nImOCommon)
set(OTHER_TARGET_CSHARP nImOCommon_swig_csharp)
set(OTHER_TARGET_PYTHON nImOCommon_swig_python)

if(APPLE)
    set(DO_SHARED "SHARED")
    set(THIS_TARGET_LIB "lib${THIS_TARGET}.dylib")
else(APPLE)
    set(DO_SHARED "")
endif(APPLE)

add_library(${THIS_TARGET}
            "${DO_SHARED}"
            "${nImO_SOURCE_DIR}/nImO/optionparser.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOAddressArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOArgumentDescriptionsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOArgumentsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBailOut.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBailOutThread.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseAdapterData.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseAdapterService.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseChannel.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseClient.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseContext.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseFilterService.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseInputHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseInputHandlerCreator.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseInputOutputService.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseInputService.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseMatcher.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseNameValidator.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseOutputService.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseService.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBaseThread.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOBoolArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOChannelArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOChannelsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOChannelStatusReporter.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOClientChannel.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOClientsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOCommon.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOConfigurationRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOConfigureRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImODetachRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImODoubleArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOEndpoint.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOException.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOExtraArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOExtraInfoRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOFilePathArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOGeneralChannel.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOInfoRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOIntArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOListRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMatchConstraint.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMatchExpression.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMatchFieldName.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMatchFieldWithValues.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMatchValue.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMatchValueList.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMetricsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOMetricsStateRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImONameRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOPingThread.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOPortArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImORequestMap.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImORestartStreamsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOSendReceiveCounters.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOServiceChannel.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOServiceInputHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOServiceInputHandlerCreator.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOServiceRequest.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOServiceResponse.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOSetMetricsStateRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOStartStreamsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOStopRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOStopStreamsRequestHandler.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOStringArgumentDescriptor.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOStringBuffer.cpp"
            "${nImO_SOURCE_DIR}/nImO/nImOUtilities.cpp")

target_link_libraries(${THIS_TARGET}
                        odLogging
                        ${YARP_LIBRARIES}
                        ${ACE_LIBRARIES}
                        ${BONJOUR_LIB})

if(LINUX)
    target_link_libraries(${THIS_TARGET}
                          pthread)
endif(LINUX)

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        libACE.dylib "@rpath/libACE.dylib" ${THIS_TARGET_LIB})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        libodLogging.dylib "@rpath/libodLogging.dylib" ${THIS_TARGET_LIB})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        libYARP_OS.1.dylib "@rpath/libYARP_OS.1.dylib" ${THIS_TARGET_LIB})
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        libYARP_sig.1.dylib "@rpath/libYARP_sig.1.dylib" ${THIS_TARGET_LIB})
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        libYARP_dev.1.dylib "@rpath/libYARP_dev.1.dylib" ${THIS_TARGET_LIB})
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        libYARP_name.1.dylib "@rpath/libYARP_name.1.dylib" ${THIS_TARGET_LIB})
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        libYARP_init.1.dylib "@rpath/libYARP_init.1.dylib" ${THIS_TARGET_LIB})
endif(APPLE)

install(TARGETS ${THIS_TARGET}
        DESTINATION lib
        COMPONENT libraries)

install(FILES
        "${nImO_SOURCE_DIR}/nImO/optionparser.h"
        "${nImO_SOURCE_DIR}/nImO/nImOAddressArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBailOut.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBailOutThread.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseAdapterData.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseAdapterService.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseChannel.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseClient.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseContext.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseFilterService.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseInputHandler.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseInputHandlerCreator.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseInputOutputService.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseInputService.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseMatcher.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseNameValidator.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseOutputService.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseRequestHandler.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseService.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBaseThread.h"
        "${nImO_SOURCE_DIR}/nImO/nImOBoolArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOChannelArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOChannelStatusReporter.h"
        "${nImO_SOURCE_DIR}/nImO/nImOClientChannel.h"
        "${nImO_SOURCE_DIR}/nImO/nImOCommon.h"
        "${nImO_SOURCE_DIR}/nImO/nImOConfig.h"
        "${nImO_SOURCE_DIR}/nImO/nImODoubleArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOEndpoint.h"
        "${nImO_SOURCE_DIR}/nImO/nImOException.h"
        "${nImO_SOURCE_DIR}/nImO/nImOExtraArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOFilePathArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOGeneralChannel.h"
        "${nImO_SOURCE_DIR}/nImO/nImOIntArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOMatchConstraint.h"
        "${nImO_SOURCE_DIR}/nImO/nImOMatchExpression.h"
        "${nImO_SOURCE_DIR}/nImO/nImOMatchFieldName.h"
        "${nImO_SOURCE_DIR}/nImO/nImOMatchFieldWithValues.h"
        "${nImO_SOURCE_DIR}/nImO/nImOMatchValue.h"
        "${nImO_SOURCE_DIR}/nImO/nImOMatchValueList.h"
        "${nImO_SOURCE_DIR}/nImO/nImOPortArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImORequestMap.h"
        "${nImO_SOURCE_DIR}/nImO/nImORequests.h"
        "${nImO_SOURCE_DIR}/nImO/nImOSendReceiveCounters.h"
        "${nImO_SOURCE_DIR}/nImO/nImOServiceChannel.h"
        "${nImO_SOURCE_DIR}/nImO/nImOServiceInputHandler.h"
        "${nImO_SOURCE_DIR}/nImO/nImOServiceInputHandlerCreator.h"
        "${nImO_SOURCE_DIR}/nImO/nImOServiceRequest.h"
        "${nImO_SOURCE_DIR}/nImO/nImOServiceResponse.h"
        "${nImO_SOURCE_DIR}/nImO/nImOStringArgumentDescriptor.h"
        "${nImO_SOURCE_DIR}/nImO/nImOStringBuffer.h"
        "${nImO_SOURCE_DIR}/nImO/nImOUtilities.h"
        DESTINATION include/nImO
		COMPONENT headers)

if(nImO_DO_SWIG)
    set(nImO_SWIG_SOURCES swig_nImO_in/nImOCommon.i
        nImOAddressArgumentDescriptor.h nImOAddressArgumentDescriptor.cpp
        nImOBaseArgumentDescriptor.h nImOBaseArgumentDescriptor.cpp
        nImOBailOut.h nImOBailOut.cpp
        nImOBailOutThread.h nImOBailOutThread.cpp
        nImOBaseAdapterData.h nImOBaseAdapterData.cpp
        nImOBaseAdapterService.h nImOBaseAdapterService.cpp
        nImOBaseChannel.h nImOBaseChannel.cpp
        nImOBaseClient.h nImOBaseClient.cpp
        nImOBaseContext.h nImOBaseContext.cpp
        nImOBaseFilterService.h nImOBaseFilterService.cpp
        nImOBaseInputHandler.h nImOBaseInputHandler.cpp
        nImOBaseInputHandlerCreator.h nImOBaseInputHandlerCreator.cpp
        nImOBaseInputOutputService.h nImOBaseInputOutputService.cpp
        nImOBaseInputService.h nImOBaseInputService.cpp
        nImOBaseMatcher.h nImOBaseMatcher.cpp
        nImOBaseNameValidator.h nImOBaseNameValidator.cpp
        nImOBaseOutputService.h nImOBaseOutputService.cpp
        nImOBaseRequestHandler.h nImOBaseRequestHandler.cpp
        nImOBaseService.h nImOBaseService.cpp
        nImOBaseThread.h nImOBaseThread.cpp
        nImOBoolArgumentDescriptor.h nImOBoolArgumentDescriptor.cpp
        nImOChannelArgumentDescriptor.h nImOChannelArgumentDescriptor.cpp
        nImOChannelStatusReporter.h nImOChannelStatusReporter.cpp
        nImOClientChannel.h nImOClientChannel.cpp
        nImOCommon.h nImOCommon.cpp
        nImODoubleArgumentDescriptor.h nImODoubleArgumentDescriptor.cpp
        nImOEndpoint.h nImOEndpoint.cpp
        nImOException.h nImOException.cpp
        nImOExtraArgumentDescriptor.h nImOExtraArgumentDescriptor.cpp
        nImOFilePathArgumentDescriptor.h nImOFilePathArgumentDescriptor.cpp
        nImOGeneralChannel.h nImOGeneralChannel.cpp
        nImOIntArgumentDescriptor.h nImOIntArgumentDescriptor.cpp
        nImOMatchConstraint.h nImOMatchConstraint.cpp
        nImOMatchExpression.h nImOMatchExpression.cpp
        nImOMatchFieldName.h nImOMatchFieldName.cpp
        nImOMatchFieldWithValues.h nImOMatchFieldWithValues.cpp
        nImOMatchValue.h nImOMatchValue.cpp
        nImOMatchValueList.h nImOMatchValueList.cpp
        nImOPortArgumentDescriptor.h nImOPortArgumentDescriptor.cpp
        nImORequestMap.h nImORequestMap.cpp
        nImOSendReceiveCounters.h nImOSendReceiveCounters.cpp
        nImOServiceChannel.h nImOServiceChannel.cpp
        nImOServiceInputHandler.h nImOServiceInputHandler.cpp
        nImOServiceInputHandlerCreator.h nImOServiceInputHandlerCreator.cpp
        nImOServiceRequest.h nImOServiceRequest.cpp
        nImOServiceResponse.h nImOServiceResponse.cpp
        nImOStringArgumentDescriptor.h nImOStringArgumentDescriptor.cpp
        nImOStringBuffer.h nImOStringBuffer.cpp
        nImOUtilities.h nImOUtilities.cpp)

    include_directories("${nImO_SOURCE_DIR}/nImO")
    set_source_files_properties(swig_nImO_in/nImOCommon.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(swig_nImO_in/nImOCommon.i PROPERTIES SWIG_FLAGS "-includeall")

    set(CMAKE_SWIG_OUTDIR "${nImO_SOURCE_DIR}/nImO/swig_nImO_out_csharp")

    swig_add_module(${OTHER_TARGET_CSHARP} csharp ${nImO_SWIG_SOURCES})

    swig_link_libraries(${OTHER_TARGET_CSHARP}
                        ${THIS_TARGET}
                        odLogging
                        ${YARP_LIBRARIES}
                        ${ACE_LIBRARIES})

    install(TARGETS ${OTHER_TARGET_CSHARP}
            DESTINATION lib
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
                        odLogging
                        ${YARP_LIBRARIES}
                        ${ACE_LIBRARIES}
                        ${PYTHON_LIBRARIES})

# Note the modified target name!
    install(TARGETS _${OTHER_TARGET_PYTHON}
            DESTINATION lib
            COMPONENT libraries)

    install(FILES
            swig_nImO_out_python/nImO.py
            swig_nImO_out_python/nImOCommonPYTHON_wrap.cxx
            DESTINATION python/nImO
            COMPONENT headers)

endif(nImO_DO_SWIG)

enable_testing()

#packing stuff

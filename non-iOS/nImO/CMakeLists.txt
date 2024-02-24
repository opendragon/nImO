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
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOaddressArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImObaseArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOchannelArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOdoubleArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOextraArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOfilePathArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOintegerArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOlogicalArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOportArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringsArgumentDescriptor.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOaddress.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOatom.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOblob.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOdouble.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOflaw.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOinteger.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOinvalid.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOlogical.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOnumber.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOstring.cpp"
            "${THIS_SOURCE_DIR}/BasicTypes/nImOvalue.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOgetChannelStatisticsCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOinputOutputCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpReceiverCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpSenderCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOshutdownCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOstartReceiverCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOstartSenderCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOstopReceiverCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/CommandHandlers/nImOstopSenderCommandHandler.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImOarray.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImObufferChunk.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImOchunkArray.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImOcontainer.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImOmap.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImOmessage.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImOset.cpp"
            "${THIS_SOURCE_DIR}/Containers/nImOstringBuffer.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOcontext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOcontextWithMDNS.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOcontextWithNetworking.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOfilterContext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOinputOutputContext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOmiscellaneousContext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOserviceContext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOsinkContext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOsourceContext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOtestContext.cpp"
            "${THIS_SOURCE_DIR}/Contexts/nImOutilityContext.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddAppToListResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddChannelResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddConnectionResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearAppListForLauncherResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearChannelInUseResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInformationResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseAndSetResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelStatisticsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetConnectionInformationResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsOnNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllMachinesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetLaunchDetailsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetMachineInformationResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfMachinesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodeInformationResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodesWithApplicationResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsOnNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsOnNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfConnectionsResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfInputChannelsOnNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfMachinesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesOnMachineResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfOutputChannelsOnNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunOptionsForAppResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunParamsForAppResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOisChannelPresentResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOisMachinePresentResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOisNodePresentResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOlaunchAppResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelsForNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveConnectionResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveNodeResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOresponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetChannelInUseResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpReceiverResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpSenderResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartReceiverResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartSenderResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopReceiverResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopSenderResponseHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOannounceServiceData.cpp"
            "${THIS_SOURCE_DIR}/nImObaseChannel.cpp"
            "${THIS_SOURCE_DIR}/nImOcallbackFunction.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelName.cpp"
            "${THIS_SOURCE_DIR}/nImOchannelStatistics.cpp"
            "${THIS_SOURCE_DIR}/nImOcommandHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOcommandSession.cpp"
            "${THIS_SOURCE_DIR}/nImOcommon.cpp"
            "${THIS_SOURCE_DIR}/nImOcompareValues.cpp"
            "${THIS_SOURCE_DIR}/nImOconverters.cpp"
            "${THIS_SOURCE_DIR}/nImOfilterBreakHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOinChannel.cpp"
            "${THIS_SOURCE_DIR}/nImOlogger.cpp"
            "${THIS_SOURCE_DIR}/nImOmainSupport.cpp"
            "${THIS_SOURCE_DIR}/nImOMIMESupport.cpp"
            "${THIS_SOURCE_DIR}/nImOoutChannel.cpp"
            "${THIS_SOURCE_DIR}/nImOreceivedData.cpp"
            "${THIS_SOURCE_DIR}/nImOreceiveQueue.cpp"
            "${THIS_SOURCE_DIR}/nImOregistryProxy.cpp"
            "${THIS_SOURCE_DIR}/nImOrequestResponse.cpp"
            "${THIS_SOURCE_DIR}/nImOserviceOptions.cpp"
            "${THIS_SOURCE_DIR}/nImOsinkBreakHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOsourceBreakHandler.cpp"
            "${THIS_SOURCE_DIR}/nImOstandardOptions.cpp"
            "${THIS_SOURCE_DIR}/optionparser.cpp"
            "${THIS_SOURCE_DIR}/whereami.c")

target_link_libraries(${THIS_TARGET} ${ODL_LIBRARY} ${BONJOUR_LIB} ${Boost_LIBRARIES})

if(LINUX)
    target_link_libraries(${THIS_TARGET} pthread)
endif()

if(APPLE)
    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -change
                        ${ODL_LIBRARY_ROOT} ${ODL_LIBRARY} ${THIS_TARGET_LIB})

    add_custom_command(TARGET ${THIS_TARGET} POST_BUILD COMMAND install_name_tool -id
                        ${THIS_TARGET_LIB} ${THIS_TARGET_LIB})

endif()

install(TARGETS
        ${THIS_TARGET}
        EXPORT ${PROJECT_NAME}
        DESTINATION ${LIB_DEST}
        COMPONENT libraries)

install(FILES
        "${THIS_SOURCE_DIR}/nImOannounceServiceData.h"
        "${THIS_SOURCE_DIR}/nImObaseChannel.h"
        "${THIS_SOURCE_DIR}/nImOcallbackFunction.h"
        "${THIS_SOURCE_DIR}/nImOchannelName.h"
        "${THIS_SOURCE_DIR}/nImOchannelStatistics.h"
        "${THIS_SOURCE_DIR}/nImOcommandHandler.h"
        "${THIS_SOURCE_DIR}/nImOcommandSession.h"
        "${THIS_SOURCE_DIR}/nImOcommon.h"
        "${THIS_SOURCE_DIR}/nImOcommonCommands.h"
        "${THIS_SOURCE_DIR}/nImOcompareValues.h"
        "${THIS_SOURCE_DIR}/nImOcomparisonStatus.h"
        "${THIS_SOURCE_DIR}/nImOconfig.h"
        "${THIS_SOURCE_DIR}/nImOconverters.h"
        "${THIS_SOURCE_DIR}/nImOfilterBreakHandler.h"
        "${THIS_SOURCE_DIR}/nImOinChannel.h"
        "${THIS_SOURCE_DIR}/nImOinputOutputCommands.h"
        "${THIS_SOURCE_DIR}/nImOlauncherCommands.h"
        "${THIS_SOURCE_DIR}/nImOlogger.h"
        "${THIS_SOURCE_DIR}/nImOmainSupport.h"
        "${THIS_SOURCE_DIR}/nImOMIMESupport.h"
        "${THIS_SOURCE_DIR}/nImOoutChannel.h"
        "${THIS_SOURCE_DIR}/nImOreceivedData.h"
        "${THIS_SOURCE_DIR}/nImOreceiveQueue.h"
        "${THIS_SOURCE_DIR}/nImOregistryCommands.h"
        "${THIS_SOURCE_DIR}/nImOregistryProxy.h"
        "${THIS_SOURCE_DIR}/nImOregistryTypes.h"
        "${THIS_SOURCE_DIR}/nImOrequestResponse.h"
        "${THIS_SOURCE_DIR}/nImOserviceOptions.h"
        "${THIS_SOURCE_DIR}/nImOsinkBreakHandler.h"
        "${THIS_SOURCE_DIR}/nImOsourceBreakHandler.h"
        "${THIS_SOURCE_DIR}/nImOstandardChannels.h"
        "${THIS_SOURCE_DIR}/nImOstandardOptions.h"
        "${THIS_SOURCE_DIR}/optionparser.hpp"
        "${THIS_SOURCE_DIR}/whereami.h"
        DESTINATION ${INCLUDE_DEST}
        COMPONENT headers)

install(FILES
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOaddressArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImObaseArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOchannelArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOdoubleArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOextraArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOfilePathArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOintegerArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOlogicalArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOportArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringArgumentDescriptor.h"
        "${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringsArgumentDescriptor.h"
        DESTINATION ${INCLUDE_DEST}/ArgumentDescriptors
        COMPONENT headers)

install(FILES
        "${THIS_SOURCE_DIR}/BasicTypes/nImOaddress.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOatom.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOblob.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOdouble.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOflaw.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOinteger.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOinvalid.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOlogical.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOnumber.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOstring.h"
        "${THIS_SOURCE_DIR}/BasicTypes/nImOvalue.h"
        DESTINATION ${INCLUDE_DEST}/BasicTypes
        COMPONENT headers)

install(FILES
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOgetChannelStatisticsCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOinputOutputCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpReceiverCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpSenderCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOshutdownCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOstartReceiverCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOstartSenderCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOstopReceiverCommandHandler.h"
        "${THIS_SOURCE_DIR}/CommandHandlers/nImOstopSenderCommandHandler.h"
        DESTINATION ${INCLUDE_DEST}/CommandHandlers
        COMPONENT headers)

install(FILES
        "${THIS_SOURCE_DIR}/Containers/nImOarray.h"
        "${THIS_SOURCE_DIR}/Containers/nImObufferChunk.h"
        "${THIS_SOURCE_DIR}/Containers/nImOchunkArray.h"
        "${THIS_SOURCE_DIR}/Containers/nImOcontainer.h"
        "${THIS_SOURCE_DIR}/Containers/nImOmap.h"
        "${THIS_SOURCE_DIR}/Containers/nImOmessage.h"
        "${THIS_SOURCE_DIR}/Containers/nImOset.h"
        "${THIS_SOURCE_DIR}/Containers/nImOstringBuffer.h"
        DESTINATION ${INCLUDE_DEST}/Containers
        COMPONENT headers)

install(FILES
        "${THIS_SOURCE_DIR}/Contexts/nImOcontext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOcontextWithMDNS.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOcontextWithNetworking.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOfilterContext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOinputOutputContext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOmiscellaneousContext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOserviceContext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOsinkContext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOsourceContext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOtestContext.h"
        "${THIS_SOURCE_DIR}/Contexts/nImOutilityContext.h"
        DESTINATION ${INCLUDE_DEST}/Contexts
        COMPONENT headers)

install(FILES
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddAppToListResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddChannelResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddConnectionResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearAppListForLauncherResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearChannelInUseResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInformationResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseAndSetResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelStatisticsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetConnectionInformationResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsOnNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllMachinesResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetLaunchDetailsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetMachineInformationResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfMachinesResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodeInformationResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodesWithApplicationResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsOnNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsOnNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfConnectionsResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfInputChannelsOnNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfMachinesResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesOnMachineResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfOutputChannelsOnNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunOptionsForAppResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunParamsForAppResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOisChannelPresentResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOisMachinePresentResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOisNodePresentResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOlaunchAppResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelsForNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveConnectionResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveNodeResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOresponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetChannelInUseResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpReceiverResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpSenderResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartReceiverResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartSenderResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopReceiverResponseHandler.h"
        "${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopSenderResponseHandler.h"
        DESTINATION ${INCLUDE_DEST}/ResponseHandlers
        COMPONENT headers)

if(nImO_DO_SWIG)
    set(nImO_SWIG_SOURCES ${THIS_SOURCE_DIR}/swig_nImO_in/nImOcommon.i
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOaddressArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOaddressArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImObaseArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImObaseArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOchannelArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOchannelArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOdoubleArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOdoubleArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOextraArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOextraArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOfilePathArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOfilePathArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOintegerArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOintegerArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOlogicalArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOlogicalArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOportArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOportArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringsArgumentDescriptor.cpp
        ${THIS_SOURCE_DIR}/ArgumentDescriptors/nImOstringsArgumentDescriptor.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOaddress.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOaddress.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOatom.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOatom.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOblob.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOblob.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOdouble.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOdouble.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOflaw.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOflaw.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOinteger.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOinteger.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOinvalid.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOinvalid.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOlogical.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOlogical.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOnumber.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOnumber.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOstring.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOstring.h
        ${THIS_SOURCE_DIR}/BasicTypes/nImOvalue.cpp ${THIS_SOURCE_DIR}/BasicTypes/nImOvalue.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetChannelStatisticsCommandHandler.cpp
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetChannelStatisticsCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOinputOutputCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOinputOutputCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpReceiverCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpReceiverCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpSenderCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOsetUpSenderCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOshutdownCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOshutdownCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOstartReceiverCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOstartReceiverCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOstartSenderCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOstartSenderCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOstopReceiverCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOstopReceiverCommandHandler.h
        ${THIS_SOURCE_DIR}/CommandHandlers/nImOstopSenderCommandHandler.cpp ${THIS_SOURCE_DIR}/CommandHandlers/nImOstopSenderCommandHandler.h
        ${THIS_SOURCE_DIR}/Containers/nImOarray.cpp ${THIS_SOURCE_DIR}/Containers/nImOarray.h
        ${THIS_SOURCE_DIR}/Containers/nImObufferChunk.cpp ${THIS_SOURCE_DIR}/Containers/nImObufferChunk.h
        ${THIS_SOURCE_DIR}/Containers/nImOchunkArray.cpp ${THIS_SOURCE_DIR}/Containers/nImOchunkArray.h
        ${THIS_SOURCE_DIR}/Containers/nImOcontainer.cpp ${THIS_SOURCE_DIR}/Containers/nImOcontainer.h
        ${THIS_SOURCE_DIR}/Containers/nImOmap.cpp ${THIS_SOURCE_DIR}/Containers/nImOmap.h
        ${THIS_SOURCE_DIR}/Containers/nImOmessage.cpp ${THIS_SOURCE_DIR}/Containers/nImOmessage.h
        ${THIS_SOURCE_DIR}/Containers/nImOset.cpp ${THIS_SOURCE_DIR}/Containers/nImOset.h
        ${THIS_SOURCE_DIR}/Containers/nImOstringBuffer.cpp ${THIS_SOURCE_DIR}/Containers/nImOstringBuffer.h
        ${THIS_SOURCE_DIR}/Contexts/nImOcontext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOcontext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOcontextWithMDNS.cpp ${THIS_SOURCE_DIR}/Contexts/nImOcontextWithMDNS.h
        ${THIS_SOURCE_DIR}/Contexts/nImOcontextWithNetworking.cpp ${THIS_SOURCE_DIR}/Contexts/nImOcontextWithNetworking.h
        ${THIS_SOURCE_DIR}/Contexts/nImOfilterContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOfilterContext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOinputOutputContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOinputOutputContext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOmiscellaneousContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOmiscellaneousContext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOserviceContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOserviceContext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOsinkContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOsinkContext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOsourceContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOsourceContext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOtestContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOtestContext.h
        ${THIS_SOURCE_DIR}/Contexts/nImOutilityContext.cpp ${THIS_SOURCE_DIR}/Contexts/nImOutilityContext.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddAppToListResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddAppToListResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddChannelResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddChannelResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddConnectionResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddConnectionResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOaddNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearAppListForLauncherResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearAppListForLauncherResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearChannelInUseResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOclearChannelInUseResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInformationResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInformationResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseAndSetResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseAndSetResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelInUseResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelStatisticsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetChannelStatisticsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetConnectionInformationResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetConnectionInformationResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsOnNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsOnNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllApplicationsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnMachineResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsOnNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllChannelsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnMachineResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsOnNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllConnectionsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllMachinesResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllMachinesResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetInformationForAllNodesResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetLaunchDetailsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetLaunchDetailsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetMachineInformationResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetMachineInformationResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfMachinesResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfMachinesResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesOnMachineResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNamesOfNodesResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodeInformationResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodeInformationResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodesWithApplicationResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNodesWithApplicationResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsOnNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsOnNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfApplicationsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsOnNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsOnNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfChannelsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfConnectionsResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfConnectionsResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfInputChannelsOnNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfInputChannelsOnNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfMachinesResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfMachinesResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesOnMachineResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesOnMachineResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfNodesResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfOutputChannelsOnNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetNumberOfOutputChannelsOnNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunOptionsForAppResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunOptionsForAppResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunParamsForAppResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOgetRunParamsForAppResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOisChannelPresentResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOisChannelPresentResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOisMachinePresentResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOisMachinePresentResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOisNodePresentResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOisNodePresentResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOlaunchAppResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOlaunchAppResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelsForNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveChannelsForNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveConnectionResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveConnectionResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveNodeResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOremoveNodeResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOresponseHandler.cpp ${THIS_SOURCE_DIR}/ResponseHandlers/nImOresponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetChannelInUseResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetChannelInUseResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpReceiverResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpReceiverResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpSenderResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOsetUpSenderResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartReceiverResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartReceiverResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartSenderResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstartSenderResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopReceiverResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopReceiverResponseHandler.h
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopSenderResponseHandler.cpp
        ${THIS_SOURCE_DIR}/ResponseHandlers/nImOstopSenderResponseHandler.h
        ${THIS_SOURCE_DIR}/nImOannounceServiceData.cpp ${THIS_SOURCE_DIR}/nImOannounceServiceData.h
        ${THIS_SOURCE_DIR}/nImObaseChannel.cpp ${THIS_SOURCE_DIR}/nImObaseChannel.h
        ${THIS_SOURCE_DIR}/nImOcallbackFunction.cpp ${THIS_SOURCE_DIR}/nImOcallbackFunction.h
        ${THIS_SOURCE_DIR}/nImOchannelName.cpp ${THIS_SOURCE_DIR}/nImOchannelName.h
        ${THIS_SOURCE_DIR}/nImOchannelStatistics.cpp ${THIS_SOURCE_DIR}/nImOchannelStatistics.h
        ${THIS_SOURCE_DIR}/nImOcommandHandler.cpp ${THIS_SOURCE_DIR}/nImOcommandHandler.h
        ${THIS_SOURCE_DIR}/nImOcommandSession.cpp ${THIS_SOURCE_DIR}/nImOcommandSession.h
        ${THIS_SOURCE_DIR}/nImOcommon.cpp ${THIS_SOURCE_DIR}/nImOcommon.h
        ${THIS_SOURCE_DIR}/nImOcommonCommands.h
        ${THIS_SOURCE_DIR}/nImOcompareValues.cpp ${THIS_SOURCE_DIR}/nImOcompareValues.h
        ${THIS_SOURCE_DIR}/nImOcomparisonStatus.cpp ${THIS_SOURCE_DIR}/nImOcomparisonStatus.h
        ${THIS_SOURCE_DIR}/nImOconverters.cpp ${THIS_SOURCE_DIR}/nImOconverters.h
        ${THIS_SOURCE_DIR}/nImOfilterBreakHandler.cpp ${THIS_SOURCE_DIR}/nImOfilterBreakHandler.h
        ${THIS_SOURCE_DIR}/nImOinChannel.cpp ${THIS_SOURCE_DIR}/nImOinChannel.h
        ${THIS_SOURCE_DIR}/nImOinputOutputCommands.h
        ${THIS_SOURCE_DIR}/nImOlauncherCommands.h
        ${THIS_SOURCE_DIR}/nImOlogger.cpp ${THIS_SOURCE_DIR}/nImOlogger.h
        ${THIS_SOURCE_DIR}/nImOmainSupport.cpp ${THIS_SOURCE_DIR}/nImOmainSupport.h
        ${THIS_SOURCE_DIR}/nImOMIMESupport.cpp ${THIS_SOURCE_DIR}/nImOMIMESupport.h
        ${THIS_SOURCE_DIR}/nImOoutChannel.cpp ${THIS_SOURCE_DIR}/nImOoutChannel.h
        ${THIS_SOURCE_DIR}/nImOreceivedData.cpp ${THIS_SOURCE_DIR}/nImOreceivedData.h
        ${THIS_SOURCE_DIR}/nImOreceiveQueue.cpp ${THIS_SOURCE_DIR}/nImOreceiveQueue.h
        ${THIS_SOURCE_DIR}/nImOregistryCommands.h
        ${THIS_SOURCE_DIR}/nImOregistryProxy.cpp ${THIS_SOURCE_DIR}/nImOregistryProxy.h
        ${THIS_SOURCE_DIR}/nImOregistryTypes.h
        ${THIS_SOURCE_DIR}/nImOrequestResponse.cpp ${THIS_SOURCE_DIR}/nImOrequestResponse.h
        ${THIS_SOURCE_DIR}/nImOserviceOptions.cpp ${THIS_SOURCE_DIR}/nImOserviceOptions.h
        ${THIS_SOURCE_DIR}/nImOsinkBreakHandler.cpp ${THIS_SOURCE_DIR}/nImOsinkBreakHandler.h
        ${THIS_SOURCE_DIR}/nImOsourceBreakHandler.cpp ${THIS_SOURCE_DIR}/nImOsourceBreakHandler.h
        ${THIS_SOURCE_DIR}/nImOstandardChannels.h
        ${THIS_SOURCE_DIR}/nImOstandardOptions.cpp ${THIS_SOURCE_DIR}/nImOstandardOptions.h)

    include_directories("${nImO_SOURCE_DIR}/nImO")
    set_source_files_properties(swig_nImO_in/nImOcommon.i PROPERTIES CPLUSPLUS ON)
    set_source_files_properties(swig_nImO_in/nImOcommon.i PROPERTIES SWIG_FLAGS "-includeall")

    set(CMAKE_SWIG_OUTDIR "${THIS_SOURCE_DIR}/swig_nImO_out_python")

    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_PATH})

    swig_add_library(${OTHER_TARGET_PYTHON} LANGUAGE python SOURCES ${nImO_SWIG_SOURCES})

    swig_link_libraries(${OTHER_TARGET_PYTHON}
                        ${THIS_TARGET}
                        ${ODL_LIBRARY}
                        ${PYTHON_LIBRARIES})

# Note the modified target name!
    install(TARGETS
            _${OTHER_TARGET_PYTHON}
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

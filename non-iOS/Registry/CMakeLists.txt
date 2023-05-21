#--------------------------------------------------------------------------------------------------
#
#  File:       non-iOS/Registry/CMakeLists.txt
#
#  Project:    nImO
#
#  Contains:   The CMAKE definitions for the Registry application.
#
#  Written by: Norman Jaffe
#
#  Copyright:  (c) 2022 by OpenDragon.
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
#  Created:    2022-07-24
#
#--------------------------------------------------------------------------------------------------

include_directories("${nImO_SOURCE_DIR}")
set(THIS_SOURCE_DIR ${nImO_SOURCE_DIR}/Registry)

set(THIS_TARGET nImOregistry)

if(WIN32)
    set(VERS_RESOURCE ${THIS_TARGET}.rc)
    configure_file(${THIS_SOURCE_DIR}/${THIS_TARGET}.rc.in ${THIS_TARGET}.rc)
else()
    set(VERS_RESOURCE "")
endif()

include_directories("${nImO_SQLITE_DIR}")

# Set up our program
add_executable(${THIS_TARGET}
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOaddChannelCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOaddNodeCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetInformationForAllMachinesCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetInformationForAllNodesCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetInformationForAllNodesOnMachineCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetLaunchDetailsCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetMachineInformationCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNamesOfMachinesCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNamesOfNodesCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNamesOfNodesOnMachineCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNodeInformationCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNumberOfChannelsCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNumberOfMachinesCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNumberOfNodesCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOgetNumberOfNodesOnMachineCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOisMachinePresentCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOisNodePresentCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOregistryCommandHandler.cpp
               ${THIS_SOURCE_DIR}/CommandHandlers/nImOremoveNodeCommandHandler.cpp
               ${THIS_SOURCE_DIR}/nImOregistry.cpp
               ${THIS_SOURCE_DIR}/nImOregistryContext.cpp
               ${THIS_SOURCE_DIR}/nImOregistryMain.cpp
               ${nImO_SQLITE_DIR}/sqlite3.c
               ${VERS_RESOURCE})

# Note that the order of inclusion of libraries is critical in Linux, as they appear to only be
# processed once.
target_link_libraries(${THIS_TARGET} ${nImO_LINK_LIBRARIES})

fix_dynamic_libs(${THIS_TARGET})

install(TARGETS ${THIS_TARGET}
        DESTINATION bin
        COMPONENT applications)

enable_testing()

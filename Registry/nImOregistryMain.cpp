//--------------------------------------------------------------------------------------------------
//
//  File:       nImOregistryMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to provide a central registry for nImO.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2022 by OpenDragon.
//
//              All rights reserved. Redistribution and use in source and binary forms, with or
//              without modification, are permitted provided that the following conditions are met:
//                * Redistributions of source code must retain the above copyright notice, this list
//                  of conditions and the following disclaimer.
//                * Redistributions in binary form must reproduce the above copyright notice, this
//                  list of conditions and the following disclaimer in the documentation and / or
//                  other materials provided with the distribution.
//                * Neither the name of the copyright holders nor the names of its contributors may
//                  be used to endorse or promote products derived from this software without
//                  specific prior written permission.
//
//              THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//              ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//              DAMAGE.
//
//  Created:    2022-07-24
//
//--------------------------------------------------------------------------------------------------

#include "CommandHandlers/nImOaddChannelCommandHandler.h"
#include "CommandHandlers/nImOaddConnectionCommandHandler.h"
#include "CommandHandlers/nImOaddNodeCommandHandler.h"
#include "CommandHandlers/nImOclearChannelInUseCommandHandler.h"
#include "CommandHandlers/nImOgetChannelInformationCommandHandler.h"
#include "CommandHandlers/nImOgetChannelInUseAndSetCommandHandler.h"
#include "CommandHandlers/nImOgetChannelInUseCommandHandler.h"
#include "CommandHandlers/nImOgetConnectionInformationCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllChannelsCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllChannelsOnMachineCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllChannelsOnNodeCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllConnectionsCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllConnectionsOnMachineCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllConnectionsOnNodeCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllMachinesCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllNodesCommandHandler.h"
#include "CommandHandlers/nImOgetInformationForAllNodesOnMachineCommandHandler.h"
#include "CommandHandlers/nImOgetLaunchDetailsCommandHandler.h"
#include "CommandHandlers/nImOgetMachineInformationCommandHandler.h"
#include "CommandHandlers/nImOgetNamesOfMachinesCommandHandler.h"
#include "CommandHandlers/nImOgetNamesOfNodesCommandHandler.h"
#include "CommandHandlers/nImOgetNamesOfNodesOnMachineCommandHandler.h"
#include "CommandHandlers/nImOgetNodeInformationCommandHandler.h"
#include "CommandHandlers/nImOgetNumberOfChannelsCommandHandler.h"
#include "CommandHandlers/nImOgetNumberOfChannelsOnNodeCommandHandler.h"
#include "CommandHandlers/nImOgetNumberOfConnectionsCommandHandler.h"
#include "CommandHandlers/nImOgetNumberOfMachinesCommandHandler.h"
#include "CommandHandlers/nImOgetNumberOfNodesCommandHandler.h"
#include "CommandHandlers/nImOgetNumberOfNodesOnMachineCommandHandler.h"
#include "CommandHandlers/nImOisChannelPresentCommandHandler.h"
#include "CommandHandlers/nImOisMachinePresentCommandHandler.h"
#include "CommandHandlers/nImOisNodePresentCommandHandler.h"
#include "CommandHandlers/nImOremoveChannelCommandHandler.h"
#include "CommandHandlers/nImOremoveChannelsForNodeCommandHandler.h"
#include "CommandHandlers/nImOremoveConnectionCommandHandler.h"
#include "CommandHandlers/nImOremoveNodeCommandHandler.h"
#include "CommandHandlers/nImOsetChannelInUseCommandHandler.h"
#include "nImOregistry.h"
#include "nImOregistryContext.h"

#include <Contexts/nImOserviceContext.h>
#include <nImOmainSupport.h>
#include <nImOregistryCommands.h>
#include <nImOserviceOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A service application to register #nImO entities. */

/*! @dir Registry
 @brief The set of files that implement the Register application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for the #nImO Registry.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    nImO::DescriptorVector  argumentList;
    nImO::ServiceOptions    optionValues;
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::ReportVersions();
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Registry", "", 2022, NIMO_COPYRIGHT_NAME_, optionValues,
                                    nImO::kSkipArgsOption | nImO::kSkipBaseOption | nImO::kSkipDescribeOption | nImO::kSkipExpandedOption |
                                    nImO::kSkipFlavoursOption | nImO::kSkipInTypeOption | nImO::kSkipNodeOption | nImO::kSkipOutTypeOption |
                                    nImO::kSkipTagOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::DisableWaitForRegistry(true);
            auto                ourContext{std::make_shared<nImO::RegistryContext>(argc, argv, progName, optionValues._logging, true)};
            nImO::Connection    statusConnection{ourContext->getStatusInfo()};

            nImO::ServiceContext::addStandardHandlers(ourContext);
            if (ourContext->asServiceContext()->findRegistry(true))
            {
                ourContext->report("Registry already running.");
                std::cerr << "Registry already running.\n";
            }
            else
            {
                auto    theRegistry{std::make_shared<nImO::Registry>(ourContext, optionValues._logging)};

                if (nullptr == theRegistry)
                {
                    ourContext->report("Could not create Registry.");
                }
                else
                {
                    auto    asRegistryContext{ReinterpretCast(Ptr(nImO::RegistryContext), ourContext.get())};

                    asRegistryContext->addHandler(nImO::kAddChannelRequest,
                                                  std::make_shared<nImO::AddChannelCommandHandler>(ourContext, theRegistry, statusConnection));
                    asRegistryContext->addHandler(nImO::kAddConnectionRequest,
                                                  std::make_shared<nImO::AddConnectionCommandHandler>(ourContext, theRegistry, statusConnection));
                    asRegistryContext->addHandler(nImO::kAddNodeRequest,
                                                  std::make_shared<nImO::AddNodeCommandHandler>(ourContext, theRegistry, statusConnection));
                    asRegistryContext->addHandler(nImO::kClearChannelInUseRequest,
                                                  std::make_shared<nImO::ClearChannelInUseCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetChannelInformationRequest,
                                                  std::make_shared<nImO::GetChannelInformationCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetChannelInUseAndSetRequest,
                                                  std::make_shared<nImO::GetChannelInUseAndSetCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetChannelInUseRequest,
                                                  std::make_shared<nImO::GetChannelInUseCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetConnectionInformationRequest,
                                                  std::make_shared<nImO::GetConnectionInformationCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllChannelsOnMachineRequest,
                                                  std::make_shared<nImO::GetInformationForAllChannelsOnMachineCommandHandler>(ourContext,
                                                                                                                              theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllChannelsOnNodeRequest,
                                                  std::make_shared<nImO::GetInformationForAllChannelsOnNodeCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllChannelsRequest,
                                                  std::make_shared<nImO::GetInformationForAllChannelsCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllConnectionsOnMachineRequest,
                                                  std::make_shared<nImO::GetInformationForAllConnectionsOnMachineCommandHandler>(ourContext,
                                                                                                                                 theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllConnectionsOnNodeRequest,
                                                  std::make_shared<nImO::GetInformationForAllConnectionsOnNodeCommandHandler>(ourContext,
                                                                                                                              theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllConnectionsRequest,
                                                  std::make_shared<nImO::GetInformationForAllConnectionsCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllMachinesRequest,
                                                  std::make_shared<nImO::GetInformationForAllMachinesCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllNodesOnMachineRequest,
                                                  std::make_shared<nImO::GetInformationForAllNodesOnMachineCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetInformationForAllNodesRequest,
                                                  std::make_shared<nImO::GetInformationForAllNodesCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetLaunchDetailsRequest,
                                                  std::make_shared<nImO::GetLaunchDetailsCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetMachineInformationRequest,
                                                  std::make_shared<nImO::GetMachineInformationCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNamesOfMachinesRequest,
                                                  std::make_shared<nImO::GetNamesOfMachinesCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNamesOfNodesOnMachineRequest,
                                                  std::make_shared<nImO::GetNamesOfNodesOnMachineCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNamesOfNodesRequest,
                                                  std::make_shared<nImO::GetNamesOfNodesCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNodeInformationRequest,
                                                  std::make_shared<nImO::GetNodeInformationCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNumberOfChannelsOnNodeRequest,
                                                  std::make_shared<nImO::GetNumberOfChannelsOnNodeCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNumberOfChannelsRequest,
                                                  std::make_shared<nImO::GetNumberOfChannelsCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNumberOfConnectionsRequest,
                                                  std::make_shared<nImO::GetNumberOfConnectionsCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNumberOfMachinesRequest,
                                                  std::make_shared<nImO::GetNumberOfMachinesCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNumberOfNodesOnMachineRequest,
                                                  std::make_shared<nImO::GetNumberOfNodesOnMachineCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kGetNumberOfNodesRequest,
                                                  std::make_shared<nImO::GetNumberOfNodesCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kIsChannelPresentRequest,
                                                  std::make_shared<nImO::IsChannelPresentCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kIsMachinePresentRequest,
                                                  std::make_shared<nImO::IsMachinePresentCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kIsNodePresentRequest,
                                                  std::make_shared<nImO::IsNodePresentCommandHandler>(ourContext, theRegistry));
                    asRegistryContext->addHandler(nImO::kRemoveChannelRequest,
                                                  std::make_shared<nImO::RemoveChannelCommandHandler>(ourContext, theRegistry, statusConnection));
                    asRegistryContext->addHandler(nImO::kRemoveChannelsForNodeRequest,
                                                  std::make_shared<nImO::RemoveChannelsForNodeCommandHandler>(ourContext, theRegistry,
                                                                                                              statusConnection));
                    asRegistryContext->addHandler(nImO::kRemoveConnectionRequest,
                                                  std::make_shared<nImO::RemoveConnectionCommandHandler>(ourContext, theRegistry, statusConnection));
                    asRegistryContext->addHandler(nImO::kRemoveNodeRequest,
                                                  std::make_shared<nImO::RemoveNodeCommandHandler>(ourContext, theRegistry, statusConnection));
                    asRegistryContext->addHandler(nImO::kSetChannelInUseRequest,
                                                  std::make_shared<nImO::SetChannelInUseCommandHandler>(ourContext, theRegistry));
                    if (asRegistryContext->makePortAnnouncement(asRegistryContext->getCommandPort(), NIMO_REGISTRY_SERVICE_NAME,
                                                                nImO::GetShortComputerName(), NIMO_REGISTRY_ADDRESS_KEY))
                    {
                        for ( ; nImO::gKeepRunning; )
                        {
                            this_thread::yield();
    //TBD
                        }
                        asRegistryContext->removeAnnouncement();
                    }
                }
            }
            nImO::EnableWaitForRegistry();
            ourContext->report("exiting.");
        }
        catch (...)
        {
            ODL_LOG("Exception caught"); //####
            exitCode = -1;
        }
    }
    ODL_EXIT_I(exitCode); //####
    return exitCode;
} // main

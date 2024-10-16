//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistryProxy.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for access to nImO registries.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
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
//  Created:    2023-01-26
//
//--------------------------------------------------------------------------------------------------

#include <nImOregistryProxy.h>

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <Contexts/nImOcontextWithMDNS.h>
#include <nImOmainSupport.h>
#include <ResponseHandlers/nImOaddAppToListResponseHandler.h>
#include <ResponseHandlers/nImOaddChannelResponseHandler.h>
#include <ResponseHandlers/nImOaddConnectionResponseHandler.h>
#include <ResponseHandlers/nImOaddNodeResponseHandler.h>
#include <ResponseHandlers/nImOclearAppListForLauncherResponseHandler.h>
#include <ResponseHandlers/nImOclearChannelInUseResponseHandler.h>
#include <ResponseHandlers/nImOgetChannelInformationResponseHandler.h>
#include <ResponseHandlers/nImOgetChannelInUseResponseHandler.h>
#include <ResponseHandlers/nImOgetChannelInUseAndSetResponseHandler.h>
#include <ResponseHandlers/nImOgetConnectionInformationResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllApplicationsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllApplicationsResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllChannelsOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllChannelsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllChannelsResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllConnectionsOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllConnectionsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllConnectionsResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllMachinesResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllNodesResponseHandler.h>
#include <ResponseHandlers/nImOgetLaunchDetailsResponseHandler.h>
#include <ResponseHandlers/nImOgetMachineInformationResponseHandler.h>
#include <ResponseHandlers/nImOgetNamesOfMachinesResponseHandler.h>
#include <ResponseHandlers/nImOgetNamesOfNodesOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetNamesOfNodesResponseHandler.h>
#include <ResponseHandlers/nImOgetNodeInformationResponseHandler.h>
#include <ResponseHandlers/nImOgetNodesWithApplicationResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfApplicationsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfApplicationsResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfChannelsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfChannelsResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfConnectionsResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfInputChannelsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfMachinesResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfNodesOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfNodesResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfOutputChannelsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOisChannelPresentResponseHandler.h>
#include <ResponseHandlers/nImOisMachinePresentResponseHandler.h>
#include <ResponseHandlers/nImOisNodePresentResponseHandler.h>
#include <ResponseHandlers/nImOremoveChannelResponseHandler.h>
#include <ResponseHandlers/nImOremoveChannelsForNodeResponseHandler.h>
#include <ResponseHandlers/nImOremoveConnectionResponseHandler.h>
#include <ResponseHandlers/nImOremoveNodeResponseHandler.h>
#include <ResponseHandlers/nImOsetChannelInUseResponseHandler.h>
#include <nImOregistryCommands.h>
#include <nImOrequestResponse.h>

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for access to %nImO registries. */
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
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::RegistryProxy::RegistryProxy
    (SpContextWithNetworking    context,
     const Connection &         connection) :
        _context{context}, _connection{connection}
{
    ODL_ENTER(); //####
    ODL_P2(&context, &connection); //####
    sockaddr_in sock_addr;

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(connection._address);
    auto    regAddrStr{nImO::Ipv4AddressToStdString(sock_addr, sizeof(sock_addr))};

    _context->report("registry found at "s + regAddrStr + ":"s + std::to_string(_connection._port) + "."s);
    ODL_EXIT_P(this); //####
} // nImO::RegistryProxy::RegistryProxy

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::BoolOrFailure
nImO::RegistryProxy::addAppToList
    (const std::string &    nodeName,
     const std::string &    applicationName,
     const std::string &    applicationDescription)
{
    ODL_OBJENTER(); //####
    ODL_S3s(nodeName, applicationName, applicationDescription); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<AddChannelResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(applicationName));
    argArray->addValue(std::make_shared<String>(applicationDescription));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kAddAppToListRequest,
                                                               kAddAppToListResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::addAppToList

nImO::BoolOrFailure
nImO::RegistryProxy::addChannel
    (const std::string &    nodeName,
     const std::string &    path,
     const bool             isOutput,
     const std::string &    dataType,
     const TransportType    modes)
{
    ODL_OBJENTER(); //####
    ODL_S3s(nodeName, path, dataType); //####
    ODL_B1(isOutput); //####
    ODL_I1(StaticCast(int, modes)); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<AddChannelResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    argArray->addValue(std::make_shared<Logical>(isOutput));
    argArray->addValue(std::make_shared<String>(dataType));
    argArray->addValue(std::make_shared<Integer>(StaticCast(int, modes)));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kAddChannelRequest,
                                                               kAddChannelResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::addChannel

nImO::BoolOrFailure
nImO::RegistryProxy::addConnection
    (const std::string &    fromNodeName,
     const std::string &    fromPath,
     const std::string &    toNodeName,
     const std::string &    toPath,
     const std::string &    dataType,
     const TransportType    mode)
{
    ODL_OBJENTER(); //####
    ODL_S4s(fromNodeName, fromPath, toNodeName, toPath); //####
    ODL_S1s(dataType); //####
    ODL_I1(StaticCast(int, mode)); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<AddConnectionResponseHandler>()};

    argArray->addValue(std::make_shared<String>(fromNodeName));
    argArray->addValue(std::make_shared<String>(fromPath));
    argArray->addValue(std::make_shared<String>(toNodeName));
    argArray->addValue(std::make_shared<String>(toPath));
    argArray->addValue(std::make_shared<String>(dataType));
    argArray->addValue(std::make_shared<Integer>(StaticCast(int, mode)));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kAddConnectionRequest,
                                                               kAddConnectionResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::addConnection

nImO::BoolOrFailure
nImO::RegistryProxy::addNode
    (const std::string &    nodeName,
     const int              argc,
     Ptr(Ptr(char))         argv,
     const ServiceType      serviceType,
     const Connection &     nodeConnection)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    ODL_I2(argc, StaticCast(int, serviceType)); //####
    ODL_P2(argv, &nodeConnection); //####
    auto    execPath{nImO::GetPathToExecutable()};
    auto    launchDirectory{boost::filesystem::current_path().string()};
    auto    commandLine{nImO::MakeStringFromCommandLine(argc - 1, argv + 1)};
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<AddNodeResponseHandler>()};
    auto    connArray{std::make_shared<Array>()};

    argArray->addValue(std::make_shared<String>(nImO::GetShortComputerName()));
    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(execPath));
    argArray->addValue(std::make_shared<String>(launchDirectory));
    argArray->addValue(std::make_shared<String>(commandLine));
    connArray->addValue(std::make_shared<Integer>(nodeConnection._address));
    connArray->addValue(std::make_shared<Integer>(nodeConnection._port));
    connArray->addValue(std::make_shared<Integer>(StaticCast(int64_t, nodeConnection._transport)));
    connArray->addValue(std::make_shared<Integer>(StaticCast(int64_t, serviceType)));
    argArray->addValue(connArray);
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kAddNodeRequest,
                                                               kAddNodeResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::addNode

nImO::BoolOrFailure
nImO::RegistryProxy::clearAppListForLauncher
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<ClearChannelInUseResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kClearAppListForLauncherRequest,
                                                               kClearAppListForLauncherResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::clearAppListForLauncher

nImO::BoolOrFailure
nImO::RegistryProxy::clearChannelInUse
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<ClearChannelInUseResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kClearChannelInUseRequest,
                                                               kClearChannelInUseResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::clearChannelInUse

nImO::ChannelInfoOrFailure
nImO::RegistryProxy::getChannelInformation
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetChannelInformationResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetChannelInformationRequest,
                                                               kGetChannelInformationResponse)};

    ODL_OBJEXIT(); //####
    return ChannelInfoOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getChannelInformation

nImO::BoolOrFailure
nImO::RegistryProxy::getChannelInUseAndSet
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetChannelInUseAndSetResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetChannelInUseAndSetRequest,
                                                               kGetChannelInUseAndSetResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getChannelInUseAndSet

nImO::ConnectionInfoOrFailure
nImO::RegistryProxy::getConnectionInformation
    (const std::string &    nodeName,
     const std::string &    path,
     const bool             fromIsSpecified)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    ODL_B1(fromIsSpecified); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetConnectionInformationResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    argArray->addValue(std::make_shared<Logical>(fromIsSpecified));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetConnectionInformationRequest,
                                                                 kGetConnectionInformationResponse)};

    ODL_OBJEXIT(); //####
    return ConnectionInfoOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getConnectionInformation

nImO::ApplicationInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllApplications
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetInformationForAllApplicationsResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetInformationForAllApplicationsRequest,
                                                                 kGetInformationForAllApplicationsResponse)};

    ODL_OBJEXIT(); //####
    return ApplicationInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllApplications

nImO::ApplicationInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllApplicationsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetInformationForAllApplicationsOnNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetInformationForAllApplicationsOnNodeRequest,
                                                               kGetInformationForAllApplicationsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return ApplicationInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllApplicationsOnNode

nImO::ChannelInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllChannels
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetInformationForAllChannelsResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetInformationForAllChannelsRequest,
                                                                 kGetInformationForAllChannelsResponse)};

    ODL_OBJEXIT(); //####
    return ChannelInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllChannels

nImO::ChannelInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllChannelsOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetInformationForAllChannelsOnMachineResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetInformationForAllChannelsOnMachineRequest,
                                                               kGetInformationForAllChannelsOnMachineResponse)};

    ODL_OBJEXIT(); //####
    return ChannelInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllChannelsOnMachine

nImO::ChannelInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllChannelsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetInformationForAllChannelsOnNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetInformationForAllChannelsOnNodeRequest,
                                                               kGetInformationForAllChannelsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return ChannelInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllChannelsOnNode

nImO::ConnectionInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllConnections
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetInformationForAllConnectionsResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetInformationForAllConnectionsRequest,
                                                                 kGetInformationForAllConnectionsResponse)};

    ODL_OBJEXIT(); //####
    return ConnectionInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllConnections

nImO::ConnectionInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllConnectionsOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetInformationForAllConnectionsOnMachineResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetInformationForAllConnectionsOnMachineRequest,
                                                               kGetInformationForAllConnectionsOnMachineResponse)};

    ODL_OBJEXIT(); //####
    return ConnectionInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllConnectionsOnMachine

nImO::ConnectionInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllConnectionsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetInformationForAllConnectionsOnNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetInformationForAllConnectionsOnNodeRequest,
                                                               kGetInformationForAllConnectionsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return ConnectionInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllConnectionsOnNode

nImO::MachineInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllMachines
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetInformationForAllMachinesResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetInformationForAllMachinesRequest,
                                                                 kGetInformationForAllMachinesResponse)};

    ODL_OBJEXIT(); //####
    return MachineInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllMachines

nImO::NodeInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllNodes
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetInformationForAllNodesResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetInformationForAllNodesRequest,
                                                                 kGetInformationForAllNodesResponse)};

    ODL_OBJEXIT(); //####
    return NodeInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllNodes

nImO::NodeInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllNodesOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetInformationForAllNodesOnMachineResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetInformationForAllNodesOnMachineRequest,
                                                               kGetInformationForAllNodesOnMachineResponse)};

    ODL_OBJEXIT(); //####
    return NodeInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllNodesOnMachine

nImO::LaunchDetailsOrFailure
nImO::RegistryProxy::getLaunchDetails
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetLaunchDetailsResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetLaunchDetailsRequest,
                                                               kGetLaunchDetailsResponse)};

    ODL_OBJEXIT(); //####
    return LaunchDetailsOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getLaunchDetails

nImO::MachineInfoOrFailure
nImO::RegistryProxy::getMachineInformation
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetMachineInformationResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetMachineInformationRequest,
                                                               kGetMachineInformationResponse)};

    ODL_OBJEXIT(); //####
    return MachineInfoOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getMachineInformation

nImO::StdStringSetOrFailure
nImO::RegistryProxy::getNamesOfMachines
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetNamesOfMachinesResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNamesOfMachinesRequest,
                                                                 kGetNamesOfMachinesResponse)};

    ODL_OBJEXIT(); //####
    return StdStringSetOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNamesOfMachines

nImO::StdStringSetOrFailure
nImO::RegistryProxy::getNamesOfNodes
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetNamesOfNodesResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNamesOfNodesRequest,
                                                                 kGetNamesOfNodesResponse)};

    ODL_OBJEXIT(); //####
    return StdStringSetOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNamesOfNodes

nImO::StdStringSetOrFailure
nImO::RegistryProxy::getNamesOfNodesOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNamesOfNodesOnMachineResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetNamesOfNodesOnMachineRequest,
                                                               kGetNamesOfNodesOnMachineResponse)};

    ODL_OBJEXIT(); //####
    return StdStringSetOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNamesOfNodesOnMachine

nImO::NodeInfoOrFailure
nImO::RegistryProxy::getNodeInformation
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNodeInformationResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetNodeInformationRequest,
                                                               kGetNodeInformationResponse)};

    ODL_OBJEXIT(); //####
    return NodeInfoOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNodeInformation

nImO::StdStringSetOrFailure
nImO::RegistryProxy::getNodesWithApplication
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNodesWithApplicationResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetNodesWithApplicationRequest,
                                                               kGetNodesWithApplicationResponse)};

    ODL_OBJEXIT(); //####
    return StdStringSetOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNodesWithApplication

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfApplications
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetNumberOfApplicationsResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNumberOfApplicationsRequest,
                                                                 kGetNumberOfApplicationsResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfApplications

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfApplicationsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNumberOfApplicationsOnNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetNumberOfApplicationsOnNodeRequest, kGetNumberOfApplicationsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfApplicationsOnNode

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfChannels
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetNumberOfChannelsResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNumberOfChannelsRequest,
                                                                 kGetNumberOfChannelsResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfChannels

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfChannelsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNumberOfChannelsOnNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetNumberOfChannelsOnNodeRequest, kGetNumberOfChannelsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfChannelsOnNode

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfConnections
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetNumberOfConnectionsResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNumberOfConnectionsRequest,
                                                                 kGetNumberOfConnectionsResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfConnections

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfInputChannelsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNumberOfInputChannelsOnNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetNumberOfInputChannelsOnNodeRequest, kGetNumberOfInputChannelsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfInputChannelsOnNode

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfMachines
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetNumberOfMachinesResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNumberOfMachinesRequest,
                                                                 kGetNumberOfMachinesResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfMachines

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfNodes
    (void)
{
    ODL_OBJENTER(); //####
    auto    handler{std::make_unique<GetNumberOfNodesResponseHandler>()};
    auto    status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNumberOfNodesRequest,
                                                                 kGetNumberOfNodesResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfNodes

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfNodesOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNumberOfNodesOnMachineResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetNumberOfNodesOnMachineRequest, kGetNumberOfNodesOnMachineResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfNodesOnMachine

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfOutputChannelsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<GetNumberOfOutputChannelsOnNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                               kGetNumberOfOutputChannelsOnNodeRequest, kGetNumberOfOutputChannelsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfOutputChannelsOnNode

nImO::BoolOrFailure
nImO::RegistryProxy::isChannelPresent
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<IsChannelPresentResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kIsChannelPresentRequest,
                                                               kIsChannelPresentResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::isChannelPresent

nImO::BoolOrFailure
nImO::RegistryProxy::isMachinePresent
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(machineName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<IsMachinePresentResponseHandler>()};

    argArray->addValue(std::make_shared<String>(machineName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kIsMachinePresentRequest,
                                                               kIsMachinePresentResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::isMachinePresent

nImO::BoolOrFailure
nImO::RegistryProxy::isNodePresent
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<IsNodePresentResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kIsNodePresentRequest,
                                                               kIsNodePresentResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::isNodePresent

nImO::BoolOrFailure
nImO::RegistryProxy::removeChannel
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<RemoveChannelResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kRemoveChannelRequest,
                                                               kRemoveChannelResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::removeChannel

nImO::BoolOrFailure
nImO::RegistryProxy::removeChannelsForNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<RemoveChannelsForNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kRemoveChannelsForNodeRequest,
                                                               kRemoveChannelsForNodeResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::removeChannelsForNode

nImO::BoolOrFailure
nImO::RegistryProxy::removeConnection
    (const std::string &    nodeName,
     const std::string &    path,
     const bool             fromIsSpecified)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    ODL_B1(fromIsSpecified); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<RemoveConnectionResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    argArray->addValue(std::make_shared<Logical>(fromIsSpecified));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kRemoveConnectionRequest,
                                                               kRemoveConnectionResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::removeConnection

nImO::BoolOrFailure
nImO::RegistryProxy::removeNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(nodeName); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<RemoveNodeResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kRemoveNodeRequest,
                                                               kRemoveNodeResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::removeNode

nImO::BoolOrFailure
nImO::RegistryProxy::setChannelInUse
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s(nodeName, path); //####
    auto    argArray{std::make_shared<Array>()};
    auto    handler{std::make_unique<SetChannelInUseResponseHandler>()};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    auto    status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kSetChannelInUseRequest,
                                                               kSetChannelInUseResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::setChannelInUse

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

nImO::SpMap
nImO::ConvertApplicationListToMap
    (const ApplicationInfoVector &  applications)
{
    ODL_ENTER(); //####
    ODL_P1(&applications); //####
    auto        result{std::make_shared<Map>()};
    auto        applicationSubMap{std::make_shared<Map>()};
    std::string nodeName{};

    for (auto & walker : applications)
    {
        if (walker._found)
        {
            if (walker._launcherName != nodeName)
            {
                if (! nodeName.empty())
                {
                    result->addValue(std::make_shared<String>(nodeName), applicationSubMap);
                    applicationSubMap->clear();
                }
                nodeName = walker._launcherName;
            }
            applicationSubMap->addValue(std::make_shared<String>(walker._appName),
                                        std::make_shared<String>(walker._appDescription));
        }
    }
    if (! applicationSubMap->empty())
    {
        result->addValue(std::make_shared<String>(nodeName), applicationSubMap);
    }
    ODL_EXIT_P(result.get()); //####
    return result;
} // nImO::ConvertApplicationListToMap

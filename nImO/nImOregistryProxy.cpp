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
#include <ContainerTypes/nImOarray.h>
#include <Contexts/nImOcontextWithMDNS.h>
#include <ResponseHandlers/nImOaddChannelResponseHandler.h>
#include <ResponseHandlers/nImOaddNodeResponseHandler.h>
#include <ResponseHandlers/nImOclearChannelInUseResponseHandler.h>
#include <ResponseHandlers/nImOgetChannelInformationResponseHandler.h>
#include <ResponseHandlers/nImOgetChannelInUseResponseHandler.h>
#include <ResponseHandlers/nImOgetChannelInUseAndSetResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllChannelsOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllChannelsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllChannelsResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllMachinesResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetInformationForAllNodesResponseHandler.h>
#include <ResponseHandlers/nImOgetLaunchDetailsResponseHandler.h>
#include <ResponseHandlers/nImOgetMachineInformationResponseHandler.h>
#include <ResponseHandlers/nImOgetNamesOfMachinesResponseHandler.h>
#include <ResponseHandlers/nImOgetNamesOfNodesOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetNamesOfNodesResponseHandler.h>
#include <ResponseHandlers/nImOgetNodeInformationResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfChannelsOnNodeResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfChannelsResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfMachinesResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfNodesOnMachineResponseHandler.h>
#include <ResponseHandlers/nImOgetNumberOfNodesResponseHandler.h>
#include <ResponseHandlers/nImOisChannelPresentResponseHandler.h>
#include <ResponseHandlers/nImOisMachinePresentResponseHandler.h>
#include <ResponseHandlers/nImOisNodePresentResponseHandler.h>
#include <ResponseHandlers/nImOremoveChannelResponseHandler.h>
#include <ResponseHandlers/nImOremoveChannelsForNodeResponseHandler.h>
#include <ResponseHandlers/nImOremoveNodeResponseHandler.h>
#include <ResponseHandlers/nImOsetChannelInUseResponseHandler.h>
#include <nImOregistryCommands.h>
#include <nImOrequestResponse.h>

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
        _context(context), _connection(connection)
{
    ODL_ENTER(); //####
    ODL_P2("context = ", &context, "connection = ", &connection); //####
    sockaddr_in sock_addr;

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(connection._address);
    std::string regAddrStr{nImO::Ipv4AddressToStdString(sock_addr, sizeof(sock_addr))};

    _context->report("Registry found at " + regAddrStr + ":" + std::to_string(_connection._port) + ".");
    ODL_EXIT_P(this); //####
} // nImO::RegistryProxy::RegistryProxy

nImO::RegistryProxy::~RegistryProxy
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::RegistryProxy::~~RegistryProxy

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

nImO::BoolOrFailure
nImO::RegistryProxy::addChannel
    (const std::string &    nodeName,
     const std::string &    path,
     const bool             isOutput,
     const std::string &    dataType,
     const TransportType    modes)
{
    ODL_OBJENTER(); //####
    ODL_S3s("nodeName = ", nodeName, "path = ", path, "dataType = ", dataType); //####
    ODL_B1("isOutput = ", isOutput); //####
    ODL_I1("modes = ", StaticCast(int, modes)); //####
    SpArray                                     argArray{new Array};
    std::unique_ptr<AddChannelResponseHandler>  handler{new AddChannelResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    argArray->addValue(std::make_shared<Logical>(isOutput));
    argArray->addValue(std::make_shared<String>(dataType));
    argArray->addValue(std::make_shared<Integer>(StaticCast(int, modes)));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kAddChannelRequest,
                                                                           kAddChannelResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::addChannel

nImO::BoolOrFailure
nImO::RegistryProxy::addNode
    (const std::string &    nodeName,
     const int              argc,
     Ptr(Ptr(char))         argv,
     const ServiceType      serviceType,
     const Connection &     nodeConnection)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    ODL_I2("argc = ", argc, "serviceType = ", StaticCast(int, serviceType)); //####
    ODL_P2("argv = ", argv, "nodeConnection = ", &nodeConnection); //####
    std::string                             execPath{boost::dll::program_location().string()};
    std::string                             launchDirectory{boost::filesystem::current_path().string()};
    std::string                             commandLine{nImO::MakeStringFromComandLine(argc - 1, argv + 1)};
    SpArray                                 argArray{new Array};
    std::unique_ptr<AddNodeResponseHandler> handler{new AddNodeResponseHandler};
    SpArray                                 connArray{new Array};

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
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kAddNodeRequest,
                                                                           kAddNodeResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::addNode

nImO::BoolOrFailure
nImO::RegistryProxy::clearChannelInUse
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SpArray                                             argArray{new Array};
    std::unique_ptr<ClearChannelInUseResponseHandler>   handler{new ClearChannelInUseResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kClearChannelInUseRequest, kClearChannelInUseResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::clearChannelInUse

nImO::ChannelInfoOrFailure
nImO::RegistryProxy::getChannelInformation
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SpArray                                                 argArray{new Array};
    std::unique_ptr<GetChannelInformationResponseHandler>   handler{new GetChannelInformationResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetChannelInformationRequest, kGetChannelInformationResponse)};

    ODL_OBJEXIT(); //####
    return ChannelInfoOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getChannelInformation

nImO::BoolOrFailure
nImO::RegistryProxy::getChannelInUseAndSet
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SpArray                                                 argArray{new Array};
    std::unique_ptr<GetChannelInUseAndSetResponseHandler>   handler{new GetChannelInUseAndSetResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetChannelInUseAndSetRequest, kGetChannelInUseAndSetResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getChannelInUseAndSet

nImO::ChannelInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllChannels
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetInformationForAllChannelsResponseHandler>    handler{new GetInformationForAllChannelsResponseHandler};
    SuccessOrFailure                                             status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection,
                                                                                                                         handler.get(),
                                                                                                             kGetInformationForAllChannelsRequest,
                                                                                                             kGetInformationForAllChannelsResponse)};

    ODL_OBJEXIT(); //####
    return ChannelInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllChannels

nImO::ChannelInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllChannelsOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    SpArray                                                                 argArray{new Array};
    std::unique_ptr<GetInformationForAllChannelsOnMachineResponseHandler>   handler{new GetInformationForAllChannelsOnMachineResponseHandler};

    argArray->addValue(std::make_shared<String>(machineName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
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
    SpArray                                                             argArray{new Array};
    std::unique_ptr<GetInformationForAllChannelsOnNodeResponseHandler>  handler{new GetInformationForAllChannelsOnNodeResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                             kGetInformationForAllChannelsOnNodeRequest,
                                                                             kGetInformationForAllChannelsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return ChannelInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllChannelsOnNode

nImO::MachineInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllMachines
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetInformationForAllMachinesResponseHandler>    handler{new GetInformationForAllMachinesResponseHandler};
    SuccessOrFailure                                             status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection,
                                                                                                                         handler.get(),
                                                                                                             kGetInformationForAllMachinesRequest,
                                                                                                             kGetInformationForAllMachinesResponse)};

    ODL_OBJEXIT(); //####
    return MachineInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllMachines

nImO::NodeInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllNodes
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetInformationForAllNodesResponseHandler>   handler{new GetInformationForAllNodesResponseHandler};
    SuccessOrFailure                                         status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection,
                                                                                                                     handler.get(),
                                                                                                                 kGetInformationForAllNodesRequest,
                                                                                                                 kGetInformationForAllNodesResponse)};

    ODL_OBJEXIT(); //####
    return NodeInfoVectorOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getInformationForAllNodes

nImO::NodeInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllNodesOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    SpArray                                                             argArray{new Array};
    std::unique_ptr<GetInformationForAllNodesOnMachineResponseHandler>  handler{new GetInformationForAllNodesOnMachineResponseHandler};

    argArray->addValue(std::make_shared<String>(machineName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
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
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                             argArray{new Array};
    std::unique_ptr<GetLaunchDetailsResponseHandler>    handler{new GetLaunchDetailsResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetLaunchDetailsRequest, kGetLaunchDetailsResponse)};

    ODL_OBJEXIT(); //####
    return LaunchDetailsOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getLaunchDetails

nImO::MachineInfoOrFailure
nImO::RegistryProxy::getMachineInformation
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    SpArray                                                 argArray{new Array};
    std::unique_ptr<GetMachineInformationResponseHandler>   handler{new GetMachineInformationResponseHandler};

    argArray->addValue(std::make_shared<String>(machineName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetMachineInformationRequest, kGetMachineInformationResponse)};

    ODL_OBJEXIT(); //####
    return MachineInfoOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getMachineInformation

nImO::StringSetOrFailure
nImO::RegistryProxy::getNamesOfMachines
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetNamesOfMachinesResponseHandler>  handler{new GetNamesOfMachinesResponseHandler};
    SuccessOrFailure                                 status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(),
                                                                                                             kGetNamesOfMachinesRequest,
                                                                                                             kGetNamesOfMachinesResponse)};

    ODL_OBJEXIT(); //####
    return StringSetOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNamesOfMachines

nImO::StringSetOrFailure
nImO::RegistryProxy::getNamesOfNodes
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetNamesOfNodesResponseHandler> handler{new GetNamesOfNodesResponseHandler};
    SuccessOrFailure                             status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(),
                                                                                                         kGetNamesOfNodesRequest,
                                                                                                         kGetNamesOfNodesResponse)};

    ODL_OBJEXIT(); //####
    return StringSetOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNamesOfNodes

nImO::StringSetOrFailure
nImO::RegistryProxy::getNamesOfNodesOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    SpArray                                                     argArray{new Array};
    std::unique_ptr<GetNamesOfNodesOnMachineResponseHandler>    handler{new GetNamesOfNodesOnMachineResponseHandler};

    argArray->addValue(std::make_shared<String>(machineName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetNamesOfNodesOnMachineRequest, kGetNamesOfNodesOnMachineResponse)};

    ODL_OBJEXIT(); //####
    return StringSetOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNamesOfNodesOnMachine

nImO::NodeInfoOrFailure
nImO::RegistryProxy::getNodeInformation
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                             argArray{new Array};
    std::unique_ptr<GetNodeInformationResponseHandler>  handler{new GetNodeInformationResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetNodeInformationRequest, kGetNodeInformationResponse)};

    ODL_OBJEXIT(); //####
    return NodeInfoOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNodeInformation

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfChannels
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetNumberOfChannelsResponseHandler> handler{new GetNumberOfChannelsResponseHandler};
    SuccessOrFailure                                 status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(),
                                                                                                             kGetNumberOfChannelsRequest,
                                                                                                             kGetNumberOfChannelsResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfChannels

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfChannelsOnNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                                     argArray{new Array};
    std::unique_ptr<GetNumberOfChannelsOnNodeResponseHandler>   handler{new GetNumberOfChannelsOnNodeResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetNumberOfChannelsOnNodeRequest, kGetNumberOfChannelsOnNodeResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfChannelsOnNode

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfMachines
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetNumberOfMachinesResponseHandler> handler{new GetNumberOfMachinesResponseHandler};
    SuccessOrFailure                                 status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(),
                                                                                                             kGetNumberOfMachinesRequest,
                                                                                                             kGetNumberOfMachinesResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfMachines

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfNodes
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<GetNumberOfNodesResponseHandler>    handler{new GetNumberOfNodesResponseHandler};
    SuccessOrFailure                                 status{SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(),
                                                                                                             kGetNumberOfNodesRequest,
                                                                                                             kGetNumberOfNodesResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfNodes

nImO::IntOrFailure
nImO::RegistryProxy::getNumberOfNodesOnMachine
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    SpArray                                                     argArray{new Array};
    std::unique_ptr<GetNumberOfNodesOnMachineResponseHandler>   handler{new GetNumberOfNodesOnMachineResponseHandler};

    argArray->addValue(std::make_shared<String>(machineName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kGetNumberOfNodesOnMachineRequest, kGetNumberOfNodesOnMachineResponse)};

    ODL_OBJEXIT(); //####
    return IntOrFailure{status, handler->result()};
} // nImO::RegistryProxy::getNumberOfNodesOnMachine

nImO::BoolOrFailure
nImO::RegistryProxy::isChannelPresent
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SpArray                                             argArray{new Array};
    std::unique_ptr<IsChannelPresentResponseHandler>    handler{new IsChannelPresentResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kIsChannelPresentRequest, kIsChannelPresentResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::isChannelPresent

nImO::BoolOrFailure
nImO::RegistryProxy::isMachinePresent
    (const std::string &    machineName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    SpArray                                             argArray{new Array};
    std::unique_ptr<IsMachinePresentResponseHandler>    handler{new IsMachinePresentResponseHandler};

    argArray->addValue(std::make_shared<String>(machineName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kIsMachinePresentRequest, kIsMachinePresentResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::isMachinePresent

nImO::BoolOrFailure
nImO::RegistryProxy::isNodePresent
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                         argArray{new Array};
    std::unique_ptr<IsNodePresentResponseHandler>   handler{new IsNodePresentResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kIsNodePresentRequest, kIsNodePresentResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::isNodePresent

nImO::BoolOrFailure
nImO::RegistryProxy::removeChannel
    (const std::string &    nodeName,
     const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SpArray                                         argArray{new Array};
    std::unique_ptr<RemoveChannelResponseHandler>   handler{new RemoveChannelResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kRemoveChannelRequest, kRemoveChannelResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::removeChannel

nImO::BoolOrFailure
nImO::RegistryProxy::removeChannelsForNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                                 argArray{new Array};
    std::unique_ptr<RemoveChannelsForNodeResponseHandler>   handler{new RemoveChannelsForNodeResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kRemoveChannelsForNodeRequest, kRemoveChannelsForNodeResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::removeChannelsForNode

nImO::BoolOrFailure
nImO::RegistryProxy::removeNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                     argArray{new Array};
    std::unique_ptr<RemoveNodeResponseHandler>  handler{new RemoveNodeResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kRemoveNodeRequest,
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
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SpArray                                         argArray{new Array};
    std::unique_ptr<SetChannelInUseResponseHandler> handler{new SetChannelInUseResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    argArray->addValue(std::make_shared<String>(path));
    SuccessOrFailure status{SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(),
                                                                           kSetChannelInUseRequest, kSetChannelInUseResponse)};

    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, handler->result()};
} // nImO::RegistryProxy::setChannelInUse

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

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

#include <nImOaddNodeResponseHandler.h>
#include <nImOarray.h>
#include <nImOcontextWithMDNS.h>
#include <nImOgetNamesOfNodesResponseHandler.h>
#include <nImOgetNodeInformationResponseHandler.h>
#include <nImOgetNumberOfNodesResponseHandler.h>
#include <nImOinteger.h>
#include <nImOlogical.h>
#include <nImOisNodePresentResponseHandler.h>
#include <nImOregistryCommands.h>
#include <nImOremoveNodeResponseHandler.h>
#include <nImOrequestResponse.h>
#include <nImOstring.h>

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
    sockaddr_in sock_addr;

    ODL_ENTER(); //####
    ODL_P2("context = ", &context, "connection = ", &connection); //####
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(connection._address);
    std::string regAddrStr = nImO::Ipv4AddressToStdString(sock_addr, sizeof(sock_addr));

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

nImO::RegSuccessOrFailure
nImO::RegistryProxy::addNode
    (const std::string &    nodeName,
     const ServiceType      serviceType,
     const Connection &     nodeConnection)
{
    NIMO_UNUSED_ARG_(nodeConnection);
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    ODL_I1("serviceClass = ", StasticCast(int, serviceClass)); //####
    ODL_P1("nodeConnection = ", &nodeConnection); //####
    SpArray                                 argArray{new Array};
    std::unique_ptr<AddNodeResponseHandler> handler{new AddNodeResponseHandler};
    SpArray                                 connArray{new Array};

    argArray->addValue(std::make_shared<String>(nodeName));
    connArray->addValue(std::make_shared<Integer>(nodeConnection._address));
    connArray->addValue(std::make_shared<Integer>(nodeConnection._port));
    connArray->addValue(std::make_shared<Integer>(StaticCast(int64_t, nodeConnection._transport)));
    connArray->addValue(std::make_shared<Integer>(StaticCast(int64_t, serviceType)));
    argArray->addValue(connArray);
    SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kAddNodeRequest, kAddNodeResponse);
    ODL_OBJEXIT(); //####
    return RegSuccessOrFailure{handler->result(), "already registered"};
} // nImO::RegistryProxy::addNode

nImO::RegNodeInfoVectorOrFailure
nImO::RegistryProxy::getInformationForAllNodes
    (void)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status{false, "not implemented"};
    NodeInfoVector      infoVector;

    //TBD
    ODL_OBJEXIT(); //####
    return RegNodeInfoVectorOrFailure{status, infoVector};
} // nImO::RegistryProxy::getInformationForAllNodes

nImO::RegStringSetOrFailure
nImO::RegistryProxy::getNamesOfNodes
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<NamesOfNodesResponseHandler>    handler{new NamesOfNodesResponseHandler};

    SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNamesOfNodesRequest, kGetNamesOfNodesResponse);
    ODL_OBJEXIT(); //####
    return RegStringSetOrFailure{RegSuccessOrFailure{true, ""}, handler->result()};
} // nImO::RegistryProxy::getNamesOfNodes

nImO::RegNodeInfoOrFailure
nImO::RegistryProxy::getNodeInformation
    (const std::string &    nodeName)
{
    NIMO_UNUSED_ARG_(nodeName);
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                         argArray{new Array};
    std::unique_ptr<NodeInformationResponseHandler> handler{new NodeInformationResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kGetNodeInformationRequest,
                                                kGetNodeInformationResponse);
    ODL_OBJEXIT(); //####
    return RegNodeInfoOrFailure{RegSuccessOrFailure{true, ""}, handler->result()};
} // nImO::RegistryProxy::getNodeInformation

nImO::RegIntOrFailure
nImO::RegistryProxy::getNumberOfNodes
    (void)
{
    ODL_OBJENTER(); //####
    std::unique_ptr<NumberOfNodesResponseHandler>   handler{new NumberOfNodesResponseHandler};

    SendRequestWithNoArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), kGetNumberOfNodesRequest, kGetNumberOfNodesResponse);
    ODL_OBJEXIT(); //####
    return RegIntOrFailure{RegSuccessOrFailure{true, ""}, handler->result()};
} // nImO::RegistryProxy::getNumberOfNodes

nImO::RegBoolOrFailure
nImO::RegistryProxy::isNodePresent
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                     argArray{new Array};
    std::unique_ptr<NodePresentResponseHandler> handler{new NodePresentResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kIsNodePresentRequest, kIsNodePresentResponse);
    ODL_OBJEXIT(); //####
    return RegBoolOrFailure{RegSuccessOrFailure{true, ""}, handler->result()};
} // nImO::RegistryProxy::isNodePresent

nImO::RegSuccessOrFailure
nImO::RegistryProxy::removeNode
    (const std::string &    nodeName)
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SpArray                                     argArray{new Array};
    std::unique_ptr<RemoveNodeResponseHandler> handler{new RemoveNodeResponseHandler};

    argArray->addValue(std::make_shared<String>(nodeName));
    SendRequestWithArgumentsAndNonEmptyResponse(_context, _connection, handler.get(), argArray.get(), kRemoveNodeRequest, kRemoveNodeResponse);
    ODL_OBJEXIT(); //####
    return RegSuccessOrFailure{handler->result(), "already removed"};
} // nImO::RegistryProxy::removeNode

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

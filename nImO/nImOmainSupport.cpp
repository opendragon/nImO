//--------------------------------------------------------------------------------------------------
//
//  File:       nImOmainSupport.cpp
//
//  Project:    nImO
//
//  Contains:   Support routines and variables for nImO applications.
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
//  Created:    2023-03-22
//
//--------------------------------------------------------------------------------------------------

#include <nImOmainSupport.h>

#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <nImOinputOutputCommands.h>
#include <nImOregistryProxy.h>
#include <nImOrequestResponse.h>
#include <ResponseHandlers/nImOstopReceiverResponseHandler.h>
#include <ResponseHandlers/nImOstopSenderResponseHandler.h>
#include "whereami.h"

#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief Support routines and variables for #nImO applications. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief A pointer to a function object to be invoked when a Control-C is handled. */
static Ptr(nImO::CallbackFunction)    lSpecialSignalObject{nullptr};

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

std::atomic_bool    nImO::gKeepRunning{true};

std::atomic_bool    nImO::gPendingStop;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::CatchSignal
    (const int  signal)
{
    ODL_ENTER(); //####
    ODL_I1("signal = ", signal); //####
#if defined(SIGINT)
    if (SIGINT == signal)
    {
        gKeepRunning = false;
        ODL_B1("gKeepRunning <- ", gKeepRunning); //####
        InterruptRegistryWait();
        if (nullptr != lSpecialSignalObject)
        {
            (*lSpecialSignalObject)();
        }
    }
    else
#endif // defined(SIGINT)
    {
        auto    message{"exiting due to signal "s + std::to_string(signal) + " = "s + nImO::NameOfSignal(signal)};

        NIMO_UNUSED_VAR_(message);
        ODL_EXIT_EXIT(1); //####
        exit(1);
    }
} // nImO::CatchSignal

bool
nImO::CloseConnection
    (SpContextWithNetworking    context,
     const std::string &        nodeName,
     RegistryProxy &            proxy,
     const std::string &        path,
     const bool                 isFrom,
     bool &                     reported)
{
    ODL_ENTER(); //####
    ODL_P2("context = ", context.get(), "proxy = ", &proxy); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    ODL_B2("isFrom = ", isFrom, "reported = ", reported); //####
    bool    result{false};
    auto    statusWithInfo{proxy.getConnectionInformation(nodeName, path, isFrom)};

    if (statusWithInfo.first.first)
    {
        nImO::ConnectionInfo &  theConnection{statusWithInfo.second};

        if (theConnection._found)
        {
            auto    fromNode{theConnection._fromNode};
            auto    fromPath{theConnection._fromPath};
            auto    toNode{theConnection._toNode};
            auto    toPath{theConnection._toPath};
            auto    statusWithNodeInfo{proxy.getNodeInformation(toNode)};

            if (statusWithNodeInfo.first.first)
            {
                if (statusWithNodeInfo.second._found)
                {
                    nImO::Connection    toConnection{statusWithNodeInfo.second._connection};

                    statusWithNodeInfo = proxy.getNodeInformation(fromNode);
                    if (statusWithNodeInfo.first.first)
                    {
                        if (statusWithNodeInfo.second._found)
                        {
                            nImO::Connection    fromConnection{statusWithNodeInfo.second._connection};

                            StopConnection(context, fromConnection, fromNode, fromPath, toConnection, toNode, toPath);
                            result = true;
                        }
                        else
                        {
                            context->report("Unknown node: '"s + toNode + "'"s);
                        }
                    }
                    else
                    {
                        if (! reported)
                        {
                            std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                            reported = true;
                        }
                    }
                }
                else
                {
                    context->report("Unknown node: '"s + toNode + "'"s);
                }
            }
            else
            {
                if (! reported)
                {
                    std::cerr << "Problem with 'getNodeInformation': " << statusWithNodeInfo.first.second << "\n";
                    reported = true;
                }
            }
            if (result)
            {
                auto    statusWithBool{proxy.removeConnection(nodeName, path, isFrom)};

                if (statusWithBool.first.first)
                {
                    if (! statusWithBool.second)
                    {
                        context->report("channel '"s + nodeName + " "s + path + "' could not be disconnected."s);
                        if (! reported)
                        {
                            std::cerr << "channel '" << nodeName << " " << path << "' could not be disconnected.\n";
                        }
                    }
                }
                else
                {
                    if (! reported)
                    {
                        std::cerr << "Problem with 'removeConnection': " << statusWithBool.first.second << "\n";
                        reported = true;
                    }
                }
                statusWithBool = proxy.clearChannelInUse(fromNode, fromPath);
                if (! statusWithBool.first.first)
                {
                    if (! reported)
                    {
                        std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                        reported = true;
                    }
                }
                statusWithBool = proxy.clearChannelInUse(toNode, toPath);
                if (! statusWithBool.first.first)
                {
                    if (! reported)
                    {
                        std::cerr << "Problem with 'clearChannelInUse': " << statusWithBool.first.second << "\n";
                        reported = true;
                    }
                }
            }
        }
    }
    else
    {
        if (! reported)
        {
            std::cerr << "Problem with 'getConnectionInformation': " << statusWithInfo.first.second << "\n";
            reported = true;
        }
    }
    ODL_EXIT_B(result); //####
    return result;
} // nImO::CloseConnection

std::string
nImO::GetPathToExecutable
    (void)
{
    ODL_ENTER(); //####
    std::string result{};
    int         dirNameLength{0};
    int         length{wai_getExecutablePath(nullptr, 0, &dirNameLength)};

    if (0 < length)
    {
        auto    path{boost::scoped_array<char>(new char[length + 1])};

        wai_getExecutablePath(path.get(), length, &dirNameLength);
        path[length] = nImO::kEndOfString;
        result = path.get();
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::GetPathToExecutable

void
nImO::SetSpecialBreakObject
    (Ptr(CallbackFunction)    sigObject)
{
    ODL_ENTER(); //####
    ODL_P1("sigObject = ", sigObject); //####
    lSpecialSignalObject = sigObject;
    ODL_EXIT(); //####
} // nImO::SetSpecialBreakObject

void
nImO::StopConnection
    (SpContextWithNetworking    ourContext,
     Connection &               fromConnection,
     const std::string &        fromNode,
     const std::string &        fromPath,
     Connection &               toConnection,
     const std::string &        toNode,
     const std::string &        toPath)
{
    auto    argArray1{std::make_shared<nImO::Array>()};
    auto    handler1{std::make_unique<nImO::StopSenderResponseHandler>()};

    argArray1->addValue(std::make_shared<nImO::String>(fromPath));
    auto    statusWithBool{SendRequestWithArgumentsAndNonEmptyResponse(ourContext, fromConnection, handler1.get(), argArray1.get(),
                                                                       kStopSenderRequest, kStopSenderResponse)};

    if (! statusWithBool.first)
    {
        ourContext->report("Problem stopping the channel '"s + fromNode + " "s + fromPath + "'"s);
    }
    auto    argArray2{std::make_shared<nImO::Array>()};
    auto    handler2{std::make_unique<nImO::StopReceiverResponseHandler>()};

    argArray2->addValue(std::make_shared<nImO::String>(toPath));
    statusWithBool = SendRequestWithArgumentsAndNonEmptyResponse(ourContext, toConnection, handler2.get(), argArray2.get(), kStopReceiverRequest,
                                                                 kStopReceiverResponse);
    if (! statusWithBool.first)
    {
        ourContext->report("Problem stopping the channel '"s + toNode + " "s + toPath + "'"s);
    }
} // nImO::StopConnection

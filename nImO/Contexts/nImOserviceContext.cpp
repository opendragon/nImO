//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOserviceContext.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO execution contexts that use a command port.
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
//  Created:    2022-07-05
//
//--------------------------------------------------------------------------------------------------

#include <Contexts/nImOserviceContext.h>

#include <BasicTypes/nImOstring.h>
#include <CommandHandlers/nImOstopCommandHandler.h>
#include <Containers/nImOarray.h>
#include <nImOcommandHandler.h>
#include <nImOcommandSession.h>
#include <nImOcommonCommands.h>
#include <nImOmainSupport.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO execution contexts that use a command port. */
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

nImO::ServiceContext::ServiceContext
    (const int              argc,
     Ptr(Ptr(char))         argv,
     const std::string &    tagForLogging,
     const bool             logging,
     const bool             startBrowser,
     const std::string &    nodeName) :
        inherited{tagForLogging, logging, startBrowser}, _acceptor{*getService()},
        _commandLine{std::make_shared<Array>()}, _keepGoing{true}, _nodeName{nodeName}
{
    ODL_ENTER(); //####
    ODL_S2s(tagForLogging, nodeName); //####
    ODL_B2(logging, startBrowser); //####
    for (int ii = 0; ii < argc; ++ii)
    {
        _commandLine->addValue(std::make_shared<String>(argv[ii]));
    }
    try
    {
        createCommandPort();
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
        
    }
    ODL_EXIT_P(this); //####
} // nImO::ServiceContext::ServiceContext

nImO::ServiceContext::~ServiceContext
    (void)
{
    ODL_OBJENTER(); //####
    removeHandlers();
    destroyCommandPort();
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::~ServiceContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::ServiceContext::addHandler
    (const std::string &    commandName,
     SpCommandHandler       theHandler)
{
    ODL_OBJENTER(); //####
    ODL_S1s(commandName); //####
    ODL_P1(theHandler.get()); //####
    bool    okSoFar{false};

    if (theHandler && (0 < commandName.size()))
    {
        const auto result = _commandHandlers.insert({commandName, theHandler});

        okSoFar = result.second;
        ODL_B1(okSoFar); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ServiceContext::addHandler

void
nImO::ServiceContext::addStandardHandlers
    (SpServiceContext       context,
     Ptr(CallbackFunction)  stopCallback)
{
    ODL_ENTER(); //####
    ODL_P2(context.get(), stopCallback); //####
    if (context)
    {
        auto    newHandler{std::make_shared<StopCommandHandler>(context, stopCallback)};

        ODL_P1(newHandler.get()); //####
        if (context->addHandler(kStopRequest, newHandler))
        {
            auto    newSession{std::make_shared<CommandSession>(context)};

            ODL_P1(newSession.get()); //####
            context->_acceptor.async_accept(*newSession->getSocket(),
                                               [context, newSession]
                                               (const BSErr ec)
                                               {
                                                    context->handleAccept(newSession, ec);
                                               });
            if (context->waitForRegistry())
            {
            }
        }
    }
    ODL_EXIT(); //####
} // nImO::ServiceContext::addStandardHandlers

Ptr(nImO::ServiceContext)
nImO::ServiceContext::asServiceContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::ServiceContext::asServiceContext

CPtr(nImO::ServiceContext)
nImO::ServiceContext::asServiceContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::ServiceContext::asServiceContext

void
nImO::ServiceContext::createCommandPort
    (void)
{
    ODL_OBJENTER(); //####
#if defined(nImO_ChattyTcpUdpLogging)
    report("creating a command port."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
    _acceptor.open(BTCP::v4());
    _acceptor.listen();
    _commandAddress = ntohl(gServiceAddressIpv4.sin_addr.s_addr);
    _commandPort = _acceptor.local_endpoint().port();
    setCommandPort(_commandPort);
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::createCommandPort

void
nImO::ServiceContext::destroyCommandPort
    (void)
{
    ODL_OBJENTER(); //####
#if defined(nImO_ChattyTcpUdpLogging)
    report("destroying a command port."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
    _keepGoing = false;
    ODL_B1(_keepGoing); //####
    _acceptor.close();
    for (auto & walker : _sessions)
    {
        auto    sessionSocket{walker->getSocket()};

#if defined(nImO_ChattyTcpUdpLogging)
        report("closing a session."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
        if (nullptr != sessionSocket)
        {
            sessionSocket->close();
        }
    }
    _sessions.clear();
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::destroyCommandPort

void
nImO::ServiceContext::forgetSession
    (SpCommandSession   aSession)
{
    ODL_OBJENTER(); //####
    ODL_P1(aSession.get()); //####
    // Drop the finished session.
    auto    found{_sessions.find(aSession)};

    if (_sessions.end() != found)
    {
        _sessions.erase(found);
    }
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::forgetSession

/*! @brief Returns a Connection that specifies the command port.
 @return A Connection with the command port details. */
nImO::Connection
nImO::ServiceContext::getCommandConnection
    (void)
    const
{
    ODL_OBJENTER(); //####
    Connection  serviceConnection{getCommandAddress(), getCommandPort()};

    ODL_OBJEXIT(); //####
    return serviceConnection;
} // nImO::ServiceContext::getCommandConnection

nImO::SpCommandHandler
nImO::ServiceContext::getHandler
    (const std::string &    commandName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s(commandName); //####
    SpCommandHandler    handler{};

    if (0 < commandName.size())
    {
        auto match{_commandHandlers.find(commandName)};

        if (_commandHandlers.end() != match)
        {
            handler = match->second;
        }
    }
    ODL_OBJEXIT_P(handler.get()); //####
    return handler;
} // nImO::ServiceContext::getHandler

void
nImO::ServiceContext::handleAccept
    (SpCommandSession   newSession,
     const BSErr &      error)
{
    ODL_OBJENTER(); //####
    ODL_P1(newSession.get()); //####
    ODL_I1(error.value()); //####
    bool    releaseSession;

    if (error)
    {
        if (BAErr::operation_aborted == error)
        {
#if defined(nImO_ChattyTcpUdpLogging)
            report("async_accept() operation cancelled."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
            ODL_LOG("(BAErr::operation_aborted == ec)"); //####
        }
        else
        {
            report("async_accept() failed -> "s + error.message() + "."s);
        }
        releaseSession = true;
    }
    else
    {
        if (_keepGoing)
        {
            releaseSession = false;
            _sessions.insert(newSession);
            newSession->start();
            if (gKeepRunning)
            {
                forgetSession(newSession);
#if defined(nImO_ChattyTcpUdpLogging)
                report("creating new session."s);
#endif /* defined(nImO_ChattyTcpUdpLogging) */
                newSession = std::make_shared<CommandSession>(newSession->getContext());
                ODL_P1(newSession.get()); //####
                _acceptor.async_accept(*newSession->getSocket(),
                                       [this, newSession]
                                       (const BSErr ec)
                                       {
                                            handleAccept(newSession, ec);
                                       });
            }
            else
            {
                releaseSession = true;
            }
        }
        else
        {
            releaseSession = true;
        }
    }
    if (releaseSession)
    {
        forgetSession(newSession);
    }
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::handleAccept

bool
nImO::ServiceContext::removeHandler
    (const std::string &    commandName)
{
    ODL_OBJENTER(); //####
    ODL_S1s(commandName); //####
    bool    okSoFar{false};

    if (0 < commandName.size())
    {
        auto match{_commandHandlers.find(commandName)};

        if (_commandHandlers.end() != match)
        {
            okSoFar = (1 == _commandHandlers.erase(commandName));
            ODL_B1(okSoFar); //####
        }
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ServiceContext::removeHandler

void
nImO::ServiceContext::removeHandlers
    (void)
{
    ODL_OBJENTER(); //####
    _commandHandlers.clear();
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::removeHandlers

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

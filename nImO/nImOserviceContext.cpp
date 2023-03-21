//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOserviceContext.cpp
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

#include <nImOserviceContext.h>
#include <nImOarray.h>
#include <nImOstring.h>

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
     const std::string &    executableName,
     const std::string &    tag,
     const bool             logging,
     const ThreadMode       whichThreads,
     const std::string &    nodeName) :
        inherited(executableName, tag, logging, whichThreads, nodeName), _acceptor(*getService()), _commandLine(new Array), _keepGoing(true)
{
    ODL_ENTER(); //####
    //ODL_S3s("progName = ", executableName, "tag = ", tag, "nodeName = ", nodeName); //####
    //ODL_B1("logging = ", logging); //####
    for (int ii = 0; ii < argc; ++ii)
    {
        _commandLine->addValue(std::make_shared<String>(argv[ii]));
    }
    try
    {
        createCommandPort();
        setCommandPort(_commandPort);
        if (waitForRegistry())
        {
            // TBD
        }
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
    destroyCommandPort();
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::~ServiceContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::ServiceContext::addHandler
    (const std::string &    commandName,
     Ptr(CommandHandler)    theHandler)
{
    bool    okSoFar = false;

    ODL_OBJENTER(); //####
    if ((nullptr != theHandler) && (0 < commandName.size()))
    {
        const auto result = _commandHandlers.insert({commandName, theHandler});

        okSoFar = result.second;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ServiceContext::addHandler

void
nImO::ServiceContext::createCommandPort
    (void)
{
    ODL_OBJENTER(); //####
    _acceptor.open(asio::ip::tcp::v4());
    _acceptor.listen();
    _commandPort = _acceptor.local_endpoint().port();
    Ptr(CommandSession) newSession = new CommandSession(*this);

    _acceptor.async_accept(newSession->getSocket(),
                           [this, newSession]
                           (const boost::system::error_code  ec)
                           {
                               handleAccept(newSession, ec);
                           });
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::createCommandPort

void
nImO::ServiceContext::destroyCommandPort
(void)
{
    ODL_OBJENTER(); //####
    _keepGoing = false;
    _acceptor.cancel();
    _acceptor.close();
    for (auto walker = _sessions.begin(); walker != _sessions.end(); ++walker)
    {
        Ptr(CommandSession) aSession = *walker;

        aSession->getSocket().cancel();
    }
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::destroyCommandPort

Ptr(nImO::CommandHandler)
nImO::ServiceContext::getHandler
    (const std::string &    commandName)
    const
{
    Ptr(CommandHandler) handler = nullptr;

    ODL_OBJENTER(); //####
    if (0 < commandName.size())
    {
        auto match = _commandHandlers.find(commandName);

        if (_commandHandlers.end() != match)
        {
            handler = match->second;
        }
    }
    ODL_OBJEXIT_P(handler); //####
    return handler;
} // nImO::ServiceContext::getHandler

void
nImO::ServiceContext::handleAccept
    (Ptr(CommandSession)        newSession,
     const system::error_code & error)
{
    bool    releaseSession;

    ODL_OBJENTER(); //####
    if (0 == error.value())
    {
        if (_keepGoing)
        {
            releaseSession = false;
            newSession->start();
            newSession = new CommandSession(*this);
            _sessions.insert(newSession);
            _acceptor.async_accept(newSession->getSocket(),
                                   [this, newSession]
                                   (const system::error_code  ec)
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
    if (releaseSession)
    {
        auto    found(_sessions.find(newSession));

        if (_sessions.end() != found)
        {
            _sessions.erase(found);
            delete newSession;
        }
    }
    ODL_OBJEXIT(); //####
} // nImO::ServiceContext::handleAccept

bool
nImO::ServiceContext::removeHandler
    (const std::string &    commandName)
{
    bool    okSoFar = false;

    ODL_OBJENTER(); //####
    if (0 < commandName.size())
    {
        okSoFar = (1 == _commandHandlers.erase(commandName));
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ServiceContext::removeHandler

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

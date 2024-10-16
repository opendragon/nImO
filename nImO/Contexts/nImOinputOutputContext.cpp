//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOinputOutputContext.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO 'inputOutput' execution context.
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
//  Created:    2023-04-12
//
//--------------------------------------------------------------------------------------------------

#include <Contexts/nImOinputOutputContext.h>

#include <CommandHandlers/nImOaddInputChannelCommandHandler.h>
#include <CommandHandlers/nImOaddOutputChannelCommandHandler.h>
#include <CommandHandlers/nImOgetChannelLimitsCommandHandler.h>
#include <CommandHandlers/nImOgetChannelStatisticsCommandHandler.h>
#include <CommandHandlers/nImOsetUpReceiverCommandHandler.h>
#include <CommandHandlers/nImOsetUpSenderCommandHandler.h>
#include <CommandHandlers/nImOstartReceiverCommandHandler.h>
#include <CommandHandlers/nImOstartSenderCommandHandler.h>
#include <CommandHandlers/nImOstopReceiverCommandHandler.h>
#include <CommandHandlers/nImOstopSenderCommandHandler.h>
#include <nImOinputOutputCommands.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the 'inputOutput' %nImO execution context. */
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

nImO::InputOutputContext::InputOutputContext
    (const int              argc,
     Ptr(Ptr(char))         argv,
     const std::string &    tagForLogging,
     const bool             logging,
     const std::string &    nodeName) :
        inherited{argc, argv, tagForLogging, logging, true, nodeName}
{
    ODL_ENTER(); //####
    ODL_S2s(tagForLogging, nodeName); //####
    ODL_B1(logging); //####
    try
    {
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
        
    }
    ODL_EXIT_P(this); //####
} // nImO::InputOutputContext::InputOutputContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::InputOutputContext::addInputChannel
    (const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S1s(path); //####
    auto        adjustedName{ConvertToLowerCase(path)};
    const auto  result = _inputChannelMap.insert({adjustedName, std::make_shared<InChannel>(_receiveQueue, *this, adjustedName,
                                                                                            _inputChannelMap.size())});

    ODL_OBJEXIT_B(result.second); //####
    return result.second;
} // nImO::InputOutputContext::addInputChannel

bool
nImO::InputOutputContext::addOutputChannel
    (const std::string &    path)
{
    ODL_OBJENTER(); //####
    ODL_S1s(path); //####
    auto        adjustedName{ConvertToLowerCase(path)};
    const auto  result = _outputChannelMap.insert({adjustedName, std::make_shared<OutChannel>(*this, adjustedName, _outputChannelMap.size())});

    ODL_OBJEXIT_B(result.second); //####
    return result.second;
} // nImO::InputOutputContext::addOutputChannel

Ptr(nImO::InputOutputContext)
nImO::InputOutputContext::asInputOutputContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::InputOutputContext::asInputOutputContext

CPtr(nImO::InputOutputContext)
nImO::InputOutputContext::asInputOutputContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(this); //####
    return this;
} // nImO::InputOutputContext::asInputOutputContext

bool
nImO::InputOutputContext::anInputChannelIsConnected
    (void)
    const
{
    ODL_OBJENTER(); //####
    bool    result{false};

    for (auto & walker : _inputChannelMap)
    {
        if (walker.second->isConnected())
        {
            result = true;
            break;

        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::InputOutputContext::anInputChannelIsConnected

bool
nImO::InputOutputContext::anOutputChannelIsConnected
    (void)
    const
{
    ODL_OBJENTER(); //####
    bool    result{false};

    for (auto & walker : _outputChannelMap)
    {
        if (walker.second->isConnected())
        {
            result = true;
            break;

        }
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::InputOutputContext::anOutputChannelIsConnected

void
nImO::InputOutputContext::collectOutputChannels
    (OutChannelVector & outChannels)
{
    ODL_OBJENTER(); //####
    ODL_P1(&outChannels); //####
    outChannels.clear();
    for (auto & walker : _outputChannelMap)
    {
        outChannels.push_back(walker.second);
    }
    ODL_OBJEXIT(); //####
} // nImO::InputOutputContext::collectOutputChannels

nImO::SpInChannel
nImO::InputOutputContext::getInputChannel
    (const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s(path); //####
    SpInChannel result;
    auto        match{_inputChannelMap.find(ConvertToLowerCase(path))};

    if (_inputChannelMap.end() != match)
    {
        result = match->second;
    }
    ODL_OBJEXIT_P(result.get()); //####
    return result;
} // nImO::InputOutputContext::getInputChannel

void
nImO::InputOutputContext::getInputChannelNames
    (nImO::StdStringVector &    names)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&names); //####
    names.clear();
    for (auto & walker : _inputChannelMap)
    {
        names.push_back(walker.second->getName());
    }
    ODL_OBJEXIT(); //####
} // nImO::InputOutputContext::getInputChannelNames

nImO::SpOutChannel
nImO::InputOutputContext::getOutputChannel
    (const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s(path); //####
    SpOutChannel    result;
    auto            match{_outputChannelMap.find(ConvertToLowerCase(path))};

    if (_outputChannelMap.end() != match)
    {
        result = match->second;
    }
    ODL_OBJEXIT_P(result.get()); //####
    return result;
} // nImO::InputOutputContext::getOutputChannel

void
nImO::InputOutputContext::getOutputChannelNames
    (nImO::StdStringVector &    names)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&names); //####
    names.clear();
    for (auto & walker : _outputChannelMap)
    {
        names.push_back(walker.second->getName());
    }
    ODL_OBJEXIT(); //####
} // nImO::InputOutputContext::getOutputChannelNames

void
nImO::InputOutputContext::stopInputQueue
    (void)
{
    ODL_OBJENTER(); //####
    _receiveQueue.stop();
    ODL_OBJEXIT(); //####
} // nImO::InputOutputContext::stopInputQueue

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

void
nImO::AddInputOutputHandlers
    (SpInputOutputContext   context,
     Ptr(CallbackFunction)  stopCallback,
     Ptr(CallbackFunction)  addInputChannelCallback,
     Ptr(CallbackFunction)  addOutputChannelCallback)
{
    ODL_ENTER(); //####
    ODL_P4(context.get(), stopCallback, addInputChannelCallback, addOutputChannelCallback); //####
    // Note that we have to add our handlers first, since adding the standard handlers initiates an acceptor.
    if (context)
    {
        bool    goAhead{true};
        auto    newHandler1{std::make_shared<StartReceiverCommandHandler>(context)};

        ODL_P1(newHandler1.get()); //####
        if (! context->addHandler(kStartReceiverRequest, newHandler1))
        {
            goAhead = false;
        }
        if (goAhead)
        {
            auto    newHandler2{std::make_shared<StartSenderCommandHandler>(context)};

            ODL_P1(newHandler2.get()); //####
            if (! context->addHandler(kStartSenderRequest, newHandler2))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler3{std::make_shared<StopReceiverCommandHandler>(context)};

            ODL_P1(newHandler3.get()); //####
            if (! context->addHandler(kStopReceiverRequest, newHandler3))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler4{std::make_shared<StopSenderCommandHandler>(context)};

            ODL_P1(newHandler4.get()); //####
            if (! context->addHandler(kStopSenderRequest, newHandler4))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler5{std::make_shared<SetUpReceiverCommandHandler>(context)};

            ODL_P1(newHandler5.get()); //####
            if (! context->addHandler(kSetUpReceiverRequest, newHandler5))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler6{std::make_shared<SetUpSenderCommandHandler>(context)};

            ODL_P1(newHandler6.get()); //####
            if (! context->addHandler(kSetUpSenderRequest, newHandler6))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler7{std::make_shared<GetChannelStatisticsCommandHandler>(context)};

            ODL_P1(newHandler7.get()); //####
            if (! context->addHandler(kGetChannelStatisticsRequest, newHandler7))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            auto    newHandler8{std::make_shared<GetChannelLimitsCommandHandler>(context)};

            ODL_P1(newHandler8.get()); //####
            if (! context->addHandler(kGetChannelLimitsRequest, newHandler8))
            {
                goAhead = false;
            }
        }
        if (goAhead && (nullptr != addInputChannelCallback))
        {
            auto    newHandler9{std::make_shared<AddInputChannelCommandHandler>(context, addInputChannelCallback)};

            ODL_P1(newHandler9.get()); //####
            if (! context->addHandler(kAddInputChannelRequest, newHandler9))
            {
                goAhead = false;
            }
        }
        if (goAhead && (nullptr != addOutputChannelCallback))
        {
            auto    newHandler10{std::make_shared<AddOutputChannelCommandHandler>(context, addOutputChannelCallback)};

            ODL_P1(newHandler10.get()); //####
            if (! context->addHandler(kAddOutputChannelRequest, newHandler10))
            {
                goAhead = false;
            }
        }
        if (goAhead)
        {
            ServiceContext::addStandardHandlers(context, stopCallback);
        }
    }
    ODL_EXIT(); //####
} // nImO::AddInputOutputHandlers

//--------------------------------------------------------------------------------------------------
//
//  File:       nImOjunctionMain.cpp
//
//  Project:    nImO
//
//  Contains:   A wiring application to demonstrate using the nImO library in a program.
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
//  Created:    2023-01-29
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <Contexts/nImOfilterContext.h>
#include <nImOchannelName.h>
#include <nImOfilterBreakHandler.h>
#include <nImOinputOutputCommands.h>
#include <nImOmainSupport.h>
#include <nImOregistryProxy.h>
#include <nImOserviceOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A wiring application to demonstrate using the nImO library in a program. */

/*! @dir Junction
 @brief The set of files that implement the Junction application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

namespace Junction_Private
{
    /*! @brief A class to provide values that are used for handling callbacks for the application. */
    class AddInputChannelCallbackHandler final : public nImO::CallbackFunction
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = CallbackFunction;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] theContext The filter context that is active. */
            inline AddInputChannelCallbackHandler
                (Ptr(nImO::FilterContext)   theContext) :
                    inherited(), _context(theContext)
            {
            }

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Process an add input channel request.
             @return @c true on success. */
            bool
            operator()
                (void)
                override;

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.

            /*! @brief The filter context that is active. */
            Ptr(nImO::FilterContext)    _context;

    }; // AddInputChannelCallbackHandler

    /*! @brief A class to provide values that are used for handling callbacks for the application. */
    class AddOutputChannelCallbackHandler final : public nImO::CallbackFunction
    {
        public :
            // Public type definitions.

        protected :
            // Protected type definitions.

        private :
            // Private type definitions.

            /*! @brief The class that this class is derived from. */
            using inherited = CallbackFunction;

        public :
            // Public methods.

            /*! @brief The constructor.
             @param[in] theContext The filter context that is active. */
            inline AddOutputChannelCallbackHandler
                (Ptr(nImO::FilterContext)   theContext) :
                    inherited(), _context(theContext)
            {
            }

        protected :
            // Protected methods.

        private :
            // Private methods.

            /*! @brief Process an add output channel request.
             @return @c true on success. */
            bool
            operator()
                (void)
                override;

        public :
            // Public fields.

        protected :
            // Protected fields.

        private :
            // Private fields.
        
            /*! @brief The filter context that is active. */
            Ptr(nImO::FilterContext)    _context;

    }; // AddOutputChannelCallbackHandler

}; // namespace Junction_Private

bool
Junction_Private::AddInputChannelCallbackHandler::operator()
    (void)
{
    ODL_OBJENTER(); //####
    _failureReason = "*** Unimplemented ***"s;
    ODL_OBJEXIT_B(false); //####
    return false;
} // Junction_Private::AddInputChannelCallbackHandler::operator()

bool
Junction_Private::AddOutputChannelCallbackHandler::operator()
    (void)
{
    ODL_OBJENTER(); //####
    _failureReason = "*** Unimplemented ***"s;
    ODL_OBJEXIT_B(false); //####
    return false;
} // Junction_Private::AddOutputChannelCallbackHandler::operator()

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for the wiring application.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::IntegerArgumentDescriptor>("numIn"s, "Number of input channels"s,
                                                                                       nImO::ArgumentMode::Optional, 1, true, 1, false, 0)};
    auto                    secondArg{std::make_shared<nImO::IntegerArgumentDescriptor>("numOut"s, "Number of output channels"s,
                                                                                        nImO::ArgumentMode::Optional, 1, true, 1, false, 0)};
    nImO::DescriptorVector  argumentList{};
    nImO::ServiceOptions    optionValues{};
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    argumentList.push_back(firstArg);
    argumentList.push_back(secondArg);
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Junction"s, 2023, nImO::kCopyrightName, optionValues,
                                    nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption, true, true))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, "junction"s, optionValues._tag)};
            auto                ourContext{std::make_shared<nImO::FilterContext>(argc, argv, progName, "Junction"s, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new nImO::FilterBreakHandler{ourContext.get()}};
            auto                addInputChannelCallback{new Junction_Private::AddInputChannelCallbackHandler{ourContext.get()}};
            auto                addOutputChannelCallback{new Junction_Private::AddOutputChannelCallbackHandler{ourContext.get()}};

            nImO::SetSpecialBreakObject(cleanup);
            ourContext->setChannelLimits(nImO::kUnlimitedChannels, nImO::kUnlimitedChannels);
            nImO::AddInputOutputHandlers(ourContext, cleanup, addInputChannelCallback, addOutputChannelCallback);
            if (ourContext->findRegistry(registryConnection))
            {
                nImO::RegistryProxy proxy{ourContext, registryConnection};
                auto                statusWithBool{proxy.isNodePresent(nodeName)};

                if (statusWithBool.first.first)
                {
                    if (statusWithBool.second)
                    {
                        ourContext->report(nodeName + " already running."s);
                        std::cerr << nodeName << " already running.\n";
                        exitCode = 1;
                    }
                    else
                    {
                        statusWithBool = proxy.addNode(nodeName, argc, argv, nImO::ServiceType::FilterService,
                                                       ourContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                auto    basePath{optionValues._base};

                                for (int ii = 1, mm = firstArg->getCurrentValue(); (ii <= mm) && (0 == exitCode); ++ii)
                                {
                                    std::string scratch;

                                    // Using one greater than the requested number of channels will ensure that all the
                                    // channel paths will have a number at the end.
                                    if (nImO::ChannelName::generatePath(basePath, false, mm + 1, ii, scratch))
                                    {
                                        statusWithBool = proxy.addChannel(nodeName, scratch, false, optionValues._inType,
                                                                          nImO::TransportType::kAny);
                                        if (statusWithBool.first.first)
                                        {
                                            if (statusWithBool.second)
                                            {
                                                ourContext->addInputChannel(scratch);
                                            }
                                            else
                                            {
                                                ourContext->report(scratch + " already registered."s);
                                                std::cerr << scratch << " already registered.\n";
                                                exitCode = 1;
                                            }
                                        }
                                        else
                                        {
                                            std::cerr << "Problem with 'addChannel': " << statusWithBool.first.second << ".\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Invalid channel path " << "'" << basePath << "'.\n";
                                        exitCode = 1;
                                    }
                                }
                                nImO::OutChannelVector  outChannels{};

                                for (int ii = 1, mm = secondArg->getCurrentValue(); (ii <= mm) && (0 == exitCode); ++ii)
                                {
                                    std::string scratch;

                                    // Using one greater than the requested number of channels will ensure that all the
                                    // channel paths will have a number at the end.
                                    if (nImO::ChannelName::generatePath(basePath, true, mm + 1, ii, scratch))
                                    {
                                        statusWithBool = proxy.addChannel(nodeName, scratch, true, optionValues._outType,
                                                                          nImO::TransportType::kAny);
                                        if (statusWithBool.first.first)
                                        {
                                            if (statusWithBool.second)
                                            {
                                                ourContext->addOutputChannel(scratch);
                                                auto    aChannel{ourContext->getOutputChannel(scratch)};

                                                if (aChannel)
                                                {
                                                    outChannels.push_back(aChannel);
                                                }
                                            }
                                            else
                                            {
                                                ourContext->report(scratch + " already registered."s);
                                                std::cerr << scratch << " already registered.\n";
                                                exitCode = 1;
                                            }
                                        }
                                        else
                                        {
                                            std::cerr << "Problem with 'addChannel': " << statusWithBool.first.second << ".\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Invalid channel path " << "'" << basePath << "'.\n";
                                        exitCode = 1;
                                    }
                                }
                                if (0 == exitCode)
                                {
                                    if (optionValues._waitForConnections)
                                    {
                                        bool    connected{false};

                                        ourContext->report("waiting for connection(s)."s);
                                        for ( ; nImO::gKeepRunning && (! connected); )
                                        {
                                            boost::this_thread::yield();
                                            connected = (ourContext->anOutputChannelIsConnected() && ourContext->anInputChannelIsConnected());
                                        }
                                    }
                                    if (nImO::gKeepRunning)
                                    {
                                        ourContext->report("waiting for messages."s);
                                        std::cerr << "ready.\n";
                                    }
                                    for ( ; nImO::gKeepRunning && (0 == exitCode); )
                                    {
                                        boost::this_thread::yield();
                                        auto    nextData{ourContext->getNextMessage()};

                                        if (nImO::gKeepRunning)
                                        {
                                            if (nextData)
                                            {
                                                auto    contents{nextData->_receivedMessage};

                                                if (contents)
                                                {
                                                    for (auto & walker : outChannels)
                                                    {
                                                        if (! walker->send(contents))
                                                        {
                                                            ourContext->report("problem sending to '"s + walker->getName() + "'."s);
                                                            std::cerr << "problem sending to " << walker->getName() << "\n";
                                                            exitCode = 1;
                                                            break;

                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if (! nImO::gPendingStop)
                                    {
                                        bool    alreadyReported{false};

                                        nImO::gKeepRunning = true; // So that the calls to 'CloseConnection' and 'getInputChannelNames' won't fail...
                                        for (auto & walker : outChannels)
                                        {
                                            nImO::CloseConnection(ourContext, nodeName, proxy, walker->getName(), true, alreadyReported);
                                        }
                                        nImO::StdStringVector   inChannelPaths;

                                        ourContext->getInputChannelNames(inChannelPaths);
                                        for (auto & walker : inChannelPaths)
                                        {
                                            nImO::CloseConnection(ourContext, nodeName, proxy, walker, false, alreadyReported);
                                        }
                                    }
                                    std::cerr << "done.\n";
                                }
                                nImO::StdStringVector   outChannelPaths;

                                nImO::gKeepRunning = true; // So that the call to 'getOutputChannelNames', 'removeChannel' and
                                                           // 'getInputChannelNames'won't fail...
                                ourContext->getOutputChannelNames(outChannelPaths);
                                for (auto & walker : outChannelPaths)
                                {
                                    statusWithBool = proxy.removeChannel(nodeName, walker);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(walker + " already unregistered."s);
                                            std::cerr << walker << " already unregistered.\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Problem with 'removeChannel': " << statusWithBool.first.second << ".\n";
                                        exitCode = 1;
                                    }
                                }
                                nImO::StdStringVector   inChannelPaths;

                                ourContext->getInputChannelNames(inChannelPaths);
                                for (auto & walker : inChannelPaths)
                                {
                                    statusWithBool = proxy.removeChannel(nodeName, walker);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(walker + " already unregistered."s);
                                            std::cerr << walker << " already unregistered.\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Problem with 'removeChannel': " << statusWithBool.first.second << ".\n";
                                        exitCode = 1;
                                    }
                                }
                                if (! nImO::gPendingStop)
                                {
                                    nImO::gKeepRunning = true; // So that the call to 'removeNode' won't fail...
                                    statusWithBool = proxy.removeNode(nodeName);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(nodeName + " already unregistered."s);
                                            std::cerr << nodeName << " already unregistered.\n";
                                            exitCode = 1;
                                        }
                                    }
                                    else
                                    {
                                        std::cerr << "Problem with 'removeNode': " << statusWithBool.first.second << ".\n";
                                        exitCode = 1;
                                    }
                                }
                            }
                            else
                            {
                                ourContext->report(nodeName + " already registered."s);
                                std::cerr << nodeName << " already registered.\n";
                                exitCode = 1;
                            }
                        }
                        else
                        {
                            std::cerr << "Problem with 'addNode': " << statusWithBool.first.second << ".\n";
                            exitCode = 1;
                        }
                    }
                }
                else
                {
                    std::cerr << "Problem with 'isNodePresent': " << statusWithBool.first.second << ".\n";
                    exitCode = 1;
                }
            }
            else
            {
                ourContext->report("Registry not found."s);
                exitCode = 2;
            }
            ourContext->report("exiting."s);
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

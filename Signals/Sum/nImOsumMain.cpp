//--------------------------------------------------------------------------------------------------
//
//  File:       nImOsumMain.cpp
//
//  Project:    nImO
//
//  Contains:   A signals application to demonstrate using the nImO library in a program.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2025 by OpenDragon.
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
//  Created:    2025-05-23
//
//--------------------------------------------------------------------------------------------------

#include <ArgumentDescriptors/nImOintegerArgumentDescriptor.h>
#include <BasicTypes/nImOdouble.h>
#include <Contexts/nImOfilterContext.h>
#include <nImOaddInputChannelCallbackHandler.h>
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
 @brief A signals application to demonstrate using the nImO library in a program. */

/*! @dir Sum
 @brief The set of files that implement the Sum application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief A class to accumulate received values. */
class ValueCollector final : public nImO::CallbackFunction
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

        /*! @brief The constructor. */
        inline ValueCollector
            (void) :
                inherited()
        {
        }

        /*! @brief Calculate the sum of the values.
         @return The sum of the values. */
        inline double
        calculate
            (void)
        {
            std::lock_guard<std::mutex>  lock{_valuesLock};
            double  result{0};

            for (auto aValue : _values)
            {
                result += aValue;
            }
            return result;
        }

        /*! @brief Increase the size of the collection of values. */
        inline void
        resize
            (void)
        {
            ODL_OBJENTER(); //####
            std::lock_guard<std::mutex>  lock{_valuesLock};

            _values.resize(_values.size() + 1);
            ODL_OBJEXIT(); //####
        }

        /*! @brief Set a value in the collection.
         @param[in] index The item in the collection to be updated.
         @param[in] newValue The value to be placed in the collection. */
        inline void
        setValue
            (const int      index,
             const double   newValue)
        {
            ODL_OBJENTER(); //####
            std::lock_guard<std::mutex>  lock{_valuesLock};

            _values[index] = newValue;
            ODL_OBJEXIT(); //####
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Process an add request.
         @return @c true on success. */
        bool
        operator()
            (void)
            override
        {
            ODL_OBJENTER(); //####
            resize();
            ODL_OBJEXIT_B(true); //####
            return true;
        }

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The collected values. */
        std::vector<double> _values{};

        /*! @brief Used to protect the collected values. */
        std::mutex  _valuesLock{};

}; // ValueCollector

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
    std::string             thisService{"Sum"s};
    std::string             progName{*argv};
    auto                    firstArg{std::make_shared<nImO::IntegerArgumentDescriptor>("numIn"s, "Number of input channels"s,
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
    if (nImO::ProcessServiceOptions(argc, argv, argumentList, "Send the sum of the messages to an output channel from the input SIGNAL channel"s, "nImOsum 2"s, 2025,
                                    nImO::kCopyrightName, optionValues, nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipInTypeOption |
                                    nImO::kSkipOutTypeOption | nImO::kSkipPortOption | nImO::kSkipRemoteOption, true))
    {
        try
        {
            nImO::CheckArgumentDescriptions(argumentList);
            nImO::LoadConfiguration(optionValues._configFilePath);
            nImO::SetSignalHandlers(nImO::CatchSignal);
            auto                nodeName{nImO::ConstructNodeName(optionValues._node, thisService, optionValues._tag)};
            auto                basePath{optionValues._base};
            auto                ourContext{std::make_shared<nImO::FilterContext>(argc, argv, thisService, optionValues._logging, nodeName)};
            nImO::Connection    registryConnection{};
            auto                cleanup{new nImO::FilterBreakHandler{ourContext.get()}};
            auto                valueCollection{std::make_shared<ValueCollector>()};
            auto                addInputChannelCallback{new nImO::AddInputChannelCallbackHandler{ourContext.get(), basePath, valueCollection.get()}};

            if (! basePath.empty())
            {
                if ('/' != basePath[0])
                {
                    basePath = "/"s + basePath;
                }
            }
            nImO::SetSpecialBreakObject(cleanup);
            ourContext->setChannelLimits(nImO::kUnlimitedChannels, 1);
            if (optionValues._autolaunch)
            {
                ourContext->findAndLaunchTheRegistry();
            }
            nImO::AddInputOutputHandlers(ourContext, cleanup, addInputChannelCallback);
            if (ourContext->findTheRegistry(registryConnection))
            {
                auto    proxy{nImO::RegistryProxy::create(ourContext, registryConnection)};
                auto    statusWithBool{proxy->isNodePresent(nodeName)};

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
                        statusWithBool = proxy->addNode(nodeName, argc, argv, nImO::ServiceType::FilterService,
                                                        ourContext->getCommandConnection());
                        if (statusWithBool.first.first)
                        {
                            if (statusWithBool.second)
                            {
                                for (int ii = 1, mm = firstArg->getCurrentValue(); (ii <= mm) && (0 == exitCode); ++ii)
                                {
                                    std::string scratch;

                                    // Using one greater than the requested number of channels will ensure that all the
                                    // channel paths will have a number at the end.
                                    if (nImO::ChannelName::generatePath(basePath, nImO::ChannelName::ChannelType::Input, mm + 1, ii, scratch))
                                    {
                                        statusWithBool = proxy->addChannel(nodeName, scratch, false, nImO::kSignalType,
                                                                           nImO::TransportType::kAny);
                                        if (statusWithBool.first.first)
                                        {
                                            if (statusWithBool.second)
                                            {
                                                ourContext->addInputChannel(scratch);
                                                valueCollection->resize();
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
                                        std::cerr << "Invalid channel path '" << basePath << "'.\n";
                                        exitCode = 1;
                                    }
                                }
                                bool        outValid{false};
                                std::string outChannelPath;

                                if (nImO::ChannelName::generatePath(basePath, nImO::ChannelName::ChannelType::Output, 1, 1, outChannelPath))
                                {
                                    statusWithBool = proxy->addChannel(nodeName, outChannelPath, true, nImO::kSignalType,
                                                                       nImO::TransportType::kAny);
                                    if (statusWithBool.first.first)
                                    {
                                        if (statusWithBool.second)
                                        {
                                            ourContext->addOutputChannel(outChannelPath);
                                            outValid = true;
                                        }
                                        else
                                        {
                                            ourContext->report(outChannelPath + " already registered."s);
                                            std::cerr << outChannelPath << " already registered.\n";
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
                                    std::cerr << "Invalid channel path '" << basePath << "'.\n";
                                    exitCode = 1;
                                }
                                if (0 == exitCode)
                                {
                                    addInputChannelCallback->enable(nodeName, proxy, optionValues._inType);
                                    auto    outChannel{ourContext->getOutputChannel(outChannelPath)};

                                    if (outChannel)
                                    {
                                        if (optionValues._waitForConnections)
                                        {
                                            bool    connected{false};

                                            std::cout << "waiting for connection(s).\n";
                                            ourContext->report("waiting for connection(s)."s);
                                            for ( ; nImO::gKeepRunning && (! connected); )
                                            {
                                                boost::this_thread::yield();
                                                connected = (outChannel->isConnected() && ourContext->anInputChannelIsConnected());
                                            }
                                        }
                                        if (nImO::gKeepRunning)
                                        {
                                            ourContext->report("waiting for messages."s);
                                            std::cout << progName << " ready.\n";
                                            std::cout.flush();
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
                                                        auto    asDouble{contents->asDouble()};

                                                        if (nullptr == asDouble)
                                                        {
                                                            std::string scratch;

                                                            nImO::ChannelName::generatePath(basePath, nImO::ChannelName::ChannelType::Input,
                                                                                            ourContext->getNumberOfInputChannels(), nextData->_tag + 1, scratch);
                                                            ourContext->report("incorrect data received from '"s + scratch + "'."s);
                                                            std::cerr << "incorrect data received from " << scratch << "\n";
                                                        }
                                                        else
                                                        {
                                                            valueCollection->setValue(nextData->_tag, asDouble->getDoubleValue());
                                                            nImO::SpValue   valueToSend{std::make_shared<nImO::Double>(valueCollection->calculate())};

                                                            if (! outChannel->send(valueToSend))
                                                            {
                                                                ourContext->report("problem sending to '"s + outChannelPath + "'."s);
                                                                std::cerr << "problem sending to " << outChannelPath << "\n";
                                                                exitCode = 1;
                                                                break;

                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        addInputChannelCallback->disable();
                                        // Wait for the callbacks to finish
                                        for ( ; addInputChannelCallback->isActive() && nImO::gKeepRunning; )
                                        {
                                            boost::this_thread::yield();
                                        }
                                        if (! nImO::gPendingStop)
                                        {
                                            bool    alreadyReported{false};

                                            nImO::gKeepRunning = true; // So that the calls to 'CloseConnection' and 'getInputChannelNames' won't fail...
                                            if (! nImO::gPendingStop)
                                            {
                                                nImO::gKeepRunning = true; // So that the call to 'removeConnection' won't fail...
                                                nImO::CloseConnection(ourContext, nodeName, proxy, outChannelPath, true, alreadyReported);
                                            }
                                            nImO::StdStringVector   inChannelPaths;

                                            ourContext->getInputChannelNames(inChannelPaths);
                                            for (auto & walker : inChannelPaths)
                                            {
                                                nImO::CloseConnection(ourContext, nodeName, proxy, walker, false, alreadyReported);
                                            }
                                        }
                                    }
                                    std::cout << progName << " done.\n";
                                    std::cout.flush();
                                }
                                if (outValid)
                                {
                                    nImO::gKeepRunning = true; // So that the call to 'removeChannel' won't fail...
                                    statusWithBool = proxy->removeChannel(nodeName, outChannelPath);
                                    if (statusWithBool.first.first)
                                    {
                                        if (! statusWithBool.second)
                                        {
                                            ourContext->report(outChannelPath + " already unregistered."s);
                                            std::cerr << outChannelPath << " already unregistered.\n";
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
                                    statusWithBool = proxy->removeChannel(nodeName, walker);
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
                                    statusWithBool = proxy->removeNode(nodeName);
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
        catch (const std::string &  fault)
        {
            std::cerr << "Exception: " << fault << "\n";
            exitCode = -1;
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

//--------------------------------------------------------------------------------------------------
//
//  File:       nImOwatchMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to display information about nImO.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2024 by OpenDragon.
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
//  Created:    2024-04-12
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <BasicTypes/nImOvalue.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <Contexts/nImOsearchContext.h>
#include <nImOcallbackFunction.h>
#include <nImOmainSupport.h>
#include <nImOreceivedData.h>
#include <nImOreceiveFromMulticastPort.h>
#include <nImOreceiveQueue.h>
#include <nImOstandardOptions.h>

#include <deque>
#include <signal.h>
#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief A utility application to display information about #nImO. */

/*! @dir Watch
 @brief The set of files that implement the Watch application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The sequence of received messages. */
static nImO::ReceiveQueue   lReceiveQueue;

/*! @brief A class to provide values that are used for handling callbacks for the application. */
class LogBreakHandler final : public nImO::CallbackFunction
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
        inline LogBreakHandler
            (void) :
                inherited()
        {
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Process a break signal.
         @return @c true on success. */
        bool
        operator()
            (void)
            override
        {
            ODL_OBJENTER(); //####
            lReceiveQueue.stop();
            ODL_OBJEXIT_B(true); //####
            return true;
        }

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

}; // LogBreakHandler

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

/*! @brief The entry point for reporting information on #nImO.

 Standard output will receive a list of the connections to the channel.
 @param[in] argc The number of arguments in 'argv'.
 @param[in] argv The arguments to be used with the application.
 @return @c 0. */
int
main
    (int            argc,
     Ptr(Ptr(char)) argv)
{
    std::string             progName{*argv};
    nImO::DescriptorVector  argumentList{};
    nImO::StandardOptions   optionValues{};
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::Initialize();
    nImO::ReportVersions();
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Watch nImO"s, "nImOwatch"s, 2024, nImO::kCopyrightName, optionValues, nullptr,
                                     nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipLoggingOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
std::cerr << "** Unimplemented **\n";
            // TBD

#if 0
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::SearchContext ourContext{"watch"s, optionValues._logging};
            auto                loggingConnection{ourContext.getLoggingInfo()};
            auto                registrySearchConnection{ourContext.gerRegistrySearchInfo()};
            auto                statusConnection{ourContext.getStatusInfo()};
            auto                logReceiver{std::make_shared<ReceiveFromMulticastPort>(ourContext.getService(), loggingConnection, lReceiveQueue)};
            auto                registrySearchReceiver{std::make_shared<ReceiveFromMulticastPort>(ourContext.getService(), registrySearchConnection, lReceiveQueue)};
            auto                statusReceiver{std::make_shared<ReceiveFromMulticastPort>(ourContext.getService(), statusConnection, lReceiveQueue)};

            nImO::SetSpecialBreakObject(new LogBreakHandler());
            // Wait for messages until exit requested via Ctrl-C.
            for ( ; nImO::gKeepRunning; )
            {
                auto    nextData{lReceiveQueue.getNextMessage()};

                if (nImO::gKeepRunning)
                {
                    time_t              rawTime;
                    std::string         nowAsString;
                    BAIP::address_v4    sender{nextData->_receivedAddress};
                    char                timeBuffer[80];
                    auto                addressString{"["s + sender.to_string() + "]"s};

                    time(&rawTime);
                    strftime(timeBuffer, sizeof(timeBuffer), "@%F/%T ", localtime(&rawTime));
                    if (auto asMap{nextData->_receivedMessage->asMap()}; nullptr == asMap)
                    {
                        // 'old' style or a status message
                        if (auto asArray{nextData->_receivedMessage->asArray()}; nullptr == asArray)
                        {
                            std::cout << addressString << timeBuffer;
                            if (auto asString{nextData->_receivedMessage->asString()}; nullptr == asString)
                            {
                                std::cout << *nextData->_receivedMessage;
                            }
                            else
                            {
                                std::cout << asString->getValue();
                            }
                            std::cout << "\n";
                        }
                        else
                        {
                            for (size_t ii{0}, numElements{asArray->size()}; ii < numElements; ++ii)
                            {
                                auto    element{asArray->at(ii)};

                                std::cout << addressString << timeBuffer;
                                if (auto asString{element->asString()}; nullptr == asString)
                                {
                                    std::cout << *element;
                                }
                                else
                                {
                                    std::cout << asString->getValue();
                                }
                                std::cout << "\n";
                            }
                        }
                    }
                    else
                    {
                        auto            commandPortKey{std::make_shared<nImO::String>(nImO::kCommandPortKey)};
                        auto            computerNameKey{std::make_shared<nImO::String>(nImO::kComputerNameKey)};
                        auto            tagKey{std::make_shared<nImO::String>(nImO::kTagKey)};
                        auto            messageKey{std::make_shared<nImO::String>(nImO::kMessageKey)};
                        // Get the computer name
                        nImO::SpValue   theComputerName;
                        nImO::SpValue   theCommandPort;
                        nImO::SpValue   theTag;

                        if (auto anIterator{asMap->find(computerNameKey)}; anIterator == asMap->end())
                        {
                            theComputerName = nullptr;
                        }
                        else
                        {
                            theComputerName = anIterator->second;
                        }
                        // Get the command port
                        if (auto anIterator{asMap->find(commandPortKey)}; anIterator == asMap->end())
                        {
                            theCommandPort = nullptr;
                        }
                        else
                        {
                            theCommandPort = anIterator->second;
                        }
                        // Get the tag
                        if (auto anIterator{asMap->find(tagKey)}; anIterator == asMap->end())
                        {
                            theTag = nullptr;
                        }
                        else
                        {
                            theTag = anIterator->second;
                        }
                        // Get the message
                        if (auto anIterator{asMap->find(messageKey)}; anIterator != asMap->end())
                        {
                            auto        theMessage{anIterator->second};
                            std::string tagText;
                            std::string computerNameText;
                            std::string commandPortText;

                            if (theTag)
                            {
                                if (auto asString{theTag->asString()}; nullptr != asString)
                                {
                                    tagText = "#"s + asString->getValue();
                                }
                            }
                            if (theComputerName)
                            {
                                if (auto asString{theComputerName->asString()}; nullptr != asString)
                                {
                                    computerNameText = asString->getValue();
                                }
                            }
                            if (theCommandPort)
                            {
                                if (auto asInteger{theCommandPort->asInteger()}; nullptr != asInteger)
                                {
                                    commandPortText = "-"s + std::to_string(asInteger->getIntegerValue());
                                }
                            }
                            auto    prefix{addressString + computerNameText + tagText + commandPortText + timeBuffer};

                            if (auto asArray{theMessage->asArray()}; nullptr == asArray)
                            {
                                std::cout << prefix;
                                if (auto asString{theMessage->asString()}; nullptr == asString)
                                {
                                    std::cout << *theMessage;
                                }
                                else
                                {
                                    std::cout << asString->getValue();
                                }
                                std::cout << "\n";
                            }
                            else
                            {
                                for (size_t ii{0}, numElements{asArray->size()}; ii < numElements; ++ii)
                                {
                                    auto    element{asArray->at(ii)};

                                    std::cout << prefix;
                                    if (auto asString{element->asString()}; nullptr == asString)
                                    {
                                        std::cout << *element;
                                    }
                                    else
                                    {
                                        std::cout << asString->getValue();
                                    }
                                    std::cout << "\n";
                                }
                            }
                        }
                    }
                    nextData.reset();
                }
            }
#endif//0
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

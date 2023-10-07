//--------------------------------------------------------------------------------------------------
//
//  File:       nImOmonitorMain.cpp
//
//  Project:    nImO
//
//  Contains:   A utility application to continuously report information on nImO.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2017 by OpenDragon.
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
//  Created:    2017-01-26
//
//--------------------------------------------------------------------------------------------------

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <BasicTypes/nImOvalue.h>
#include <ContainerTypes/nImOarray.h>
#include <ContainerTypes/nImOmap.h>
#include <Contexts/nImOcontextWithMDNS.h>
#include <nImOmainSupport.h>
#include <nImOMIMESupport.h>
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
 @brief A utility application to continuously report information on #nImO. */

/*! @dir Monitor
 @brief The set of files that implement the Monitor application. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace std::string_literals;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief A structure to hold a received message. */
struct ReceivedData final
{
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

    public :
        // Public methods.

        /*! @brief The constructor.
         @param[in] receivedMessage The message from the sender.
         @param[in] receivedAddress The send IP address. */
        inline ReceivedData
            (nImO::SpValue              receivedMessage,
             const nImO::IPv4Address    receivedAddress) :
                _receivedMessage(receivedMessage), _receivedAddress(receivedAddress)
        {
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

    public :
        // Public fields.

        /*! @brief The message from the sender. */
        nImO::SpValue   _receivedMessage{};

        /*! @brief The IP address of the sender. */
        nImO::IPv4Address   _receivedAddress{};

    protected :
        // Protected fields.

    private :
        // Private fields.

}; // ReceivedData

/*! @brief A holder for a shared pointer to ReceivedData. */
using SpReceivedData = std::shared_ptr<ReceivedData>;

/*! @brief The sequence of received messages. */
static std::deque<SpReceivedData>   lReceivedData;

/*! @brief Used to protect lReceivedValues. */
static std::mutex lReceivedLock;

/*! @brief Used to indicate that lReceivedValues is ready to use. */
static std::condition_variable    lReceivedCondition;

/*! @brief A class to handle receiving messages from the logging or status multicast group. */
class ReceiveOnMessagePort final
{
    public :
        // Public type definitions.

    protected :
        // Protected type definitions.

    private :
        // Private type definitions.

    public :
        // Public methods.

        /*! @brief The constructor.
         @param[in] service The I/O service to attach to.
         @param[in] runFlag A reference to the flag that is used to stop execution.
         @param[in] theConnection The connection to listen on. */
        inline ReceiveOnMessagePort
            (nImO::SPservice            service,
             const nImO::Connection &   theConnection) :
                _socket(*service)
        {
            BAIP::address_v4    listenAddress{0};
            BAIP::address_v4    multicastAddress{theConnection._address};
            BUDP::endpoint      listenEndpoint{listenAddress, theConnection._port};

            _socket.open(listenEndpoint.protocol());
            _socket.set_option(BUDP::socket::reuse_address(true));
            _socket.bind(listenEndpoint);
            // Join the multicast group.
            _socket.set_option(BAIP::multicast::join_group(multicastAddress));
            receiveMessages();
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Receive a message. */
        inline void
        receiveMessages
            (void)
        {
            if (nImO::gKeepRunning)
            {
                _socket.async_receive_from(boost::asio::buffer(_data), _senderEndpoint,
                                           [this]
                                           (const BSErr         ec,
                                            const std::size_t   length)
                                           {
                                               if (! ec)
                                               {
                                                   nImO::ByteVector inBytes;
                                                   std::string      receivedAsString{_data.data(), length};

                                                   // We need to convert the raw data to a string!
                                                   if (nImO::DecodeMIMEToBytes(receivedAsString, inBytes))
                                                   {
                                                       auto                 newMessage{std::make_shared<nImO::Message>()};
                                                       nImO::IPv4Address    senderAddress{_senderEndpoint.address().to_v4().to_uint()};

                                                       newMessage->open(false);
                                                       newMessage->appendBytes(inBytes.data(), inBytes.size());
                                                       SpReceivedData   newData{std::make_shared<ReceivedData>(newMessage->getValue(),
                                                                                                               senderAddress)};

                                                       {
                                                           std::lock_guard<std::mutex>  lock{lReceivedLock};

                                                           lReceivedData.push_back(newData);
                                                       }
                                                       newMessage->close();
                                                       lReceivedCondition.notify_one();
                                                   }
                                                   receiveMessages();
                                               }
                                           });
            }
        }

    public :
        // Public fields.

    protected :
        // Protected fields.

    private :
        // Private fields.

        /*! @brief The socket for a multicast reception. */
        BUDP::socket    _socket;

        /*! @brief The sender's endpoint. */
        BUDP::endpoint  _senderEndpoint{};

        /*! @brief A buffer for the raw message data. */
        std::array<char, 2048>  _data{};

}; // ReceiveOnMessagePort

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Simulate a received message so that the received-message-loop can exit. */
static void
doConditionNotify
    (void)
{
    ODL_ENTER(); //####
    lReceivedCondition.notify_one();
    ODL_EXIT(); //####
} // doConditionNotify

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
    nImO::DescriptorVector  argumentList;
    nImO::StandardOptions   optionValues;
    int                     exitCode{0};

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::ReportVersions();
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Report on nImO", "nImOmonitor", 2017, NIMO_COPYRIGHT_NAME_, optionValues, nullptr,
                                     nImO::kSkipExpandedOption | nImO::kSkipFlavoursOption | nImO::kSkipLoggingOption | nImO::kSkipMachineOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSpecialBreakFunction(doConditionNotify);
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::ContextWithNetworking             ourContext{progName, "monitor", optionValues._logging};
            nImO::Connection                        loggingConnection{ourContext.getLoggingInfo()};
            nImO::Connection                        statusConnection{ourContext.getStatusInfo()};
            auto                                    logReceiver{std::make_shared<ReceiveOnMessagePort>(ourContext.getService(), loggingConnection)};
            std::shared_ptr<ReceiveOnMessagePort>   statusReceiver;

            if (loggingConnection != statusConnection)
            {
                statusReceiver = std::make_shared<ReceiveOnMessagePort>(ourContext.getService(), statusConnection);
            }
            // Wait for messages until exit requested via Ctrl-C.
            for ( ; nImO::gKeepRunning; )
            {
                SpReceivedData  nextData;

                boost::this_thread::yield();
                {
                    // Check for messages.
                    std::unique_lock<std::mutex>    lock{lReceivedLock};

                    for ( ; nImO::gKeepRunning && (0 == lReceivedData.size()); )
                    {
                        boost::this_thread::yield();
                        lReceivedCondition.wait(lock);
                    }
                    if (nImO::gKeepRunning)
                    {
                        nextData = lReceivedData.front();
                        lReceivedData.pop_front();
                    }
                }
                if (nImO::gKeepRunning)
                {
                    time_t              rawTime;
                    std::string         nowAsString;
                    CPtr(nImO::Map)     asMap{nextData->_receivedMessage->asMap()};
                    BAIP::address_v4    sender{nextData->_receivedAddress};
                    char                timeBuffer[80];
                    std::string         addressString{"["s + sender.to_string() + "]"s};

                    time(&rawTime);
                    strftime(timeBuffer, sizeof(timeBuffer), "@%F/%T ", localtime(&rawTime));
                    if (nullptr == asMap)
                    {
                        CPtr(nImO::Array)   asArray{nextData->_receivedMessage->asArray()};

                        // 'old' style or a status message
                        if (nullptr == asArray)
                        {
                            CPtr(nImO::String)  asString{nextData->_receivedMessage->asString()};

                            std::cout << addressString << timeBuffer;
                            if (nullptr == asString)
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
                            for (size_t ii = 0, numElements = asArray->size(); ii < numElements; ++ii)
                            {
                                nImO::SpValue       element{asArray->at(ii)};
                                CPtr(nImO::String)  asString{element->asString()};

                                std::cout << addressString << timeBuffer;
                                if (nullptr == asString)
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
                        nImO::SpString  commandPortKey{std::make_shared<nImO::String>(nImO::kCommandPortKey)};
                        nImO::SpString  computerNameKey{std::make_shared<nImO::String>(nImO::kComputerNameKey)};
                        nImO::SpString  tagKey{std::make_shared<nImO::String>(nImO::kTagKey)};
                        nImO::SpString  messageKey{std::make_shared<nImO::String>(nImO::kMessageKey)};
                        // Get the computer name
                        auto            anIterator{asMap->find(computerNameKey)};
                        nImO::SpValue   theComputerName;
                        nImO::SpValue   theCommandPort;
                        nImO::SpValue   theTag;

                        if (anIterator == asMap->end())
                        {
                            theComputerName = nullptr;
                        }
                        else
                        {
                            theComputerName = anIterator->second;
                        }
                        // Get the command port
                        anIterator = asMap->find(commandPortKey);
                        if (anIterator == asMap->end())
                        {
                            theCommandPort = nullptr;
                        }
                        else
                        {
                            theCommandPort = anIterator->second;
                        }
                        // Get the tag
                        anIterator = asMap->find(tagKey);
                        if (anIterator == asMap->end())
                        {
                            theTag = nullptr;
                        }
                        else
                        {
                            theTag = anIterator->second;
                        }
                        // Get the message
                        anIterator = asMap->find(messageKey);
                        if (anIterator != asMap->end())
                        {
                            nImO::SpValue       theMessage{anIterator->second};
                            CPtr(nImO::Array)   asArray{theMessage->asArray()};
                            std::string         tagText;
                            std::string         computerNameText;
                            std::string         commandPortText;

                            if (nullptr != theTag)
                            {
                                CPtr(nImO::String)  asString{theTag->asString()};

                                if (nullptr != asString)
                                {
                                    tagText = "#"s + asString->getValue();
                                }
                            }
                            if (nullptr != theComputerName)
                            {
                                CPtr(nImO::String)  asString{theComputerName->asString()};

                                if (nullptr != asString)
                                {
                                    computerNameText = asString->getValue();
                                }
                            }
                            if (nullptr != theCommandPort)
                            {
                                CPtr(nImO::Integer) asInteger{theCommandPort->asInteger()};

                                if (nullptr != asInteger)
                                {
                                    commandPortText = "-"s + std::to_string(asInteger->getIntegerValue());
                                }
                            }
                            std::string prefix{addressString + computerNameText + tagText + commandPortText + timeBuffer};

                            if (nullptr == asArray)
                            {
                                CPtr(nImO::String)  asString{theMessage->asString()};

                                std::cout << prefix;
                                if (nullptr == asString)
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
                                for (size_t ii = 0, numElements = asArray->size(); ii < numElements; ++ii)
                                {
                                    nImO::SpValue       element{asArray->at(ii)};
                                    CPtr(nImO::String)  asString{element->asString()};

                                    std::cout << prefix;
                                    if (nullptr == asString)
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

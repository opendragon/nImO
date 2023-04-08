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

#include <nImOcontextWithMDNS.h>
#include <nImOarray.h>
#include <nImOinteger.h>
#include <nImOmainSupport.h>
#include <nImOmap.h>
#include <nImOMIMESupport.h>
#include <nImOstandardOptions.h>
#include <nImOstring.h>
#include <nImOvalue.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#include <deque>
#include <signal.h>

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
        ReceivedData
            (nImO::SpValue  receivedMessage,
             const uint32_t receivedAddress) :
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
        nImO::SpValue   _receivedMessage;

        /*! @brief The IP address of the sender. */
        uint32_t    _receivedAddress;

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

/*! @brief A class to handle receiving messages from the logging multicast group. */
class ReceiveOnLoggingPort final
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
         @param[in] loggingConnection The connection to listen on. */
        ReceiveOnLoggingPort
            (nImO::SPservice            service,
             const nImO::Connection &   loggingConnection) :
                _socket(*service)
        {
            asio::ip::address_v4    listenAddress{0};
            asio::ip::address_v4    multicastAddress{loggingConnection._address};
            asio::ip::udp::endpoint listenEndpoint{listenAddress, loggingConnection._port};

            _socket.open(listenEndpoint.protocol());
            _socket.set_option(asio::ip::udp::socket::reuse_address(true));
            _socket.bind(listenEndpoint);
            // Join the multicast group.
            _socket.set_option(asio::ip::multicast::join_group(multicastAddress));
            receiveMessages();
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Receive a message. */
        void
        receiveMessages
            (void)
        {
            if (nImO::gKeepRunning)
            {
                _socket.async_receive_from(asio::buffer(_data), _senderEndpoint,
                                           [this]
                                           (const system::error_code    ec,
                                            const std::size_t           length)
                                           {
                                               if (! ec)
                                               {
                                                   nImO::ByteVector inBytes;
                                                   std::string      receivedAsString(_data.data(), length);

                                                   // We need to convert the raw data to a string!
                                                   if (nImO::DecodeMIMEToBytes(receivedAsString, inBytes))
                                                   {
                                                       auto     newMessage{std::make_shared<nImO::Message>()};
                                                       uint32_t senderAddress = _senderEndpoint.address().to_v4().to_uint();

                                                       newMessage->open(false);
                                                       newMessage->appendBytes(inBytes.data(), inBytes.size());
                                                       SpReceivedData   newData{std::make_shared<ReceivedData>(newMessage->getValue(),
                                                                                                               senderAddress)};

                                                       {
                                                           std::lock_guard<std::mutex>  lock(lReceivedLock);

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
        asio::ip::udp::socket   _socket;

        /*! @brief The sender's endpoint. */
        asio::ip::udp::endpoint _senderEndpoint;

        /*! @brief A buffer for the raw message data. */
        std::array<char, 2048>  _data;

}; // ReceiveOnLoggingPort

/*! @brief A class to handle receiving messages from the status multicast group. */
class ReceiveOnStatusPort final
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
         @param[in] statusConnection The connection to listen on. */
        ReceiveOnStatusPort
            (nImO::SPservice            service,
             const nImO::Connection &   statusConnection) :
                _socket(*service)
        {
            asio::ip::address_v4    listenAddress{0};
            asio::ip::address_v4    multicastAddress{statusConnection._address};
            asio::ip::udp::endpoint listenEndpoint{listenAddress, statusConnection._port};

            _socket.open(listenEndpoint.protocol());
            _socket.set_option(asio::ip::udp::socket::reuse_address(true));
            _socket.bind(listenEndpoint);
            // Join the multicast group.
            _socket.set_option(asio::ip::multicast::join_group(multicastAddress));
            receiveMessages();
        }

    protected :
        // Protected methods.

    private :
        // Private methods.

        /*! @brief Receive a message. */
        void
        receiveMessages
            (void)
        {
            if (nImO::gKeepRunning)
            {
                _socket.async_receive_from(asio::buffer(_data), _senderEndpoint,
                                           [this]
                                           (const system::error_code    ec,
                                            const std::size_t           length)
                                           {
                                               if (! ec)
                                               {
                                                std::string     receivedAsString(_data.data(), length);

                                                // Note that the status message is a simple text string with particular data present.
                                                // It is not a Message, so we need to make one in order to process it with our main loop.
                                                auto        newMessage{std::make_shared<nImO::Message>()};
                                                uint32_t    senderAddress = _senderEndpoint.address().to_v4().to_uint();

                                                ODL_I1("at line ", __LINE__); //!!
                                                newMessage->open(true);
                                                ODL_I1("at line ", __LINE__); //!!
                                                newMessage->setValue(std::make_shared<nImO::String>("status='" + receivedAsString + "'"));
                                                ODL_I1("at line ", __LINE__); //!!
                                                newMessage->close();
                                                ODL_I1("at line ", __LINE__); //!!
                                                SpReceivedData   newData{std::make_shared<ReceivedData>(newMessage->getValue(true), senderAddress)};
                                                ODL_I1("at line ", __LINE__); //!!

                                                {
                                                    std::lock_guard<std::mutex>  lock(lReceivedLock);

                                                    lReceivedData.push_back(newData);
                                                }
                                                   ODL_I1("at line ", __LINE__); //!!
                                                lReceivedCondition.notify_one();
                                                   ODL_I1("at line ", __LINE__); //!!
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
        asio::ip::udp::socket   _socket;

        /*! @brief The sender's endpoint. */
        asio::ip::udp::endpoint _senderEndpoint;

        /*! @brief A buffer for the raw message data. */
        std::array<char, 2048>  _data;

}; // ReceiveOnStatusPort

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
    nImO::DescriptorVector  argumentList;
    nImO::StandardOptions   optionValues;
    int                     exitCode = 0;

    ODL_INIT(progName.c_str(), kODLoggingOptionIncludeProcessID | //####
             kODLoggingOptionIncludeThreadID | kODLoggingOptionEnableThreadSupport | //####
             kODLoggingOptionWriteToStderr); //####
    ODL_ENTER(); //####
    nImO::ReportVersions();
    if (nImO::ProcessStandardOptions(argc, argv, argumentList, "Report on nImO", "nImOmonitor", 2017, NIMO_COPYRIGHT_NAME_, optionValues, nullptr,
                                     nImO::kSkipFlavoursOption | nImO::kSkipLoggingOption))
    {
        nImO::LoadConfiguration(optionValues._configFilePath);
        try
        {
            nImO::SetSignalHandlers(nImO::CatchSignal);
            nImO::ContextWithNetworking ourContext{progName, "monitor", optionValues._logging};
            nImO::Connection            loggingConnection{ourContext.getLoggingInfo()};
            nImO::Connection            statusConnection{ourContext.getStatusInfo()};
            ReceiveOnLoggingPort        logReceiver{ourContext.getService(), loggingConnection};
            ReceiveOnStatusPort         statusReceiver{ourContext.getService(), statusConnection};

            // Wait for messages until exit requested via Ctrl-C.
            for ( ; nImO::gKeepRunning; )
            {
                SpReceivedData  nextData;

                this_thread::yield();
                {
                    // Check for messages.
                    std::unique_lock<std::mutex>    lock(lReceivedLock);

                    for ( ; nImO::gKeepRunning && (0 == lReceivedData.size()); )
                    {
                        this_thread::yield();
                        lReceivedCondition.wait(lock);
                    }
                    if (nImO::gKeepRunning)
                    {
                        ODL_I1("at line ", __LINE__); //!!
                        nextData = lReceivedData.front();
                        ODL_P1("nextData = ", nextData.get()); //!!
                        lReceivedData.pop_front();
                        ODL_I1("at line ", __LINE__); //!!
                    }
                }
                if (nImO::gKeepRunning)
                {
                    ODL_LOG("(nImO::gKeepRunning)"); //!!
                    time_t                  rawTime;
                    std::string             nowAsString;
                    CPtr(nImO::Map)         asMap{nextData->_receivedMessage->asMap()};
                    ODL_P1("asMap = ", asMap); //!!
                    asio::ip::address_v4    sender{nextData->_receivedAddress};
                    char                    timeBuffer[80];
                    std::string             addressString{"[" + sender.to_string() + "]"};

                    time(&rawTime);
                    strftime(timeBuffer, sizeof(timeBuffer), "@%F/%T ", localtime(&rawTime));
                    if (nullptr == asMap)
                    {
                        ODL_LOG("(nullptr == asMap)"); //!!
                        CPtr(nImO::Array)   asArray{nextData->_receivedMessage->asArray()};

                        // 'old' style
                        if (nullptr == asArray)
                        {
                            ODL_LOG("(nullptr == asArray)"); //!!
                            CPtr(nImO::String)  asString{nextData->_receivedMessage->asString()};

                            std::cout << addressString << timeBuffer;
                            if (nullptr == asString)
                            {
                                ODL_LOG("(nullptr == asString)"); //!!
                                std::cout << *nextData->_receivedMessage;
                            }
                            else
                            {
                                ODL_LOG("! (nullptr == asString)"); //!!
                                std::cout << asString->getValue();
                            }
                            std::cout << std::endl;
                        }
                        else
                        {
                            ODL_LOG("! (nullptr == asMap)"); //!!
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
                                std::cout << std::endl;
                            }
                        }
                    }
                    else
                    {
                        ODL_LOG("! (nullptr == asMap)"); //!!
                        nImO::SpString  commandPortKey{std::make_shared<nImO::String>(nImO::kCommandPortKey)};
                        nImO::SpString  computerNameKey{std::make_shared<nImO::String>(nImO::kComputerNameKey)};
                        nImO::SpString  tagKey{std::make_shared<nImO::String>(nImO::kTagKey)};
                        nImO::SpString  messageKey{std::make_shared<nImO::String>(nImO::kMessageKey)};
                        // Get the computer name
                        auto            anIterator = asMap->find(computerNameKey);
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
                                    tagText = "#" + asString->getValue();
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
                                    commandPortText = "-" + std::to_string(asInteger->getIntegerValue());
                                }
                            }
                            std::string prefix{addressString + computerNameText + tagText + commandPortText +
                                                timeBuffer};

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
                                std::cout << std::endl;
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
                                    std::cout << std::endl;
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

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOcontextWithNetworking.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO execution contexts that use networking.
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
//  Created:    2022-12-14
//
//--------------------------------------------------------------------------------------------------

#include <Contexts/nImOcontextWithNetworking.h>

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOinteger.h>
#include <nImOstandardOptions.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO execution contexts that use networking. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief The connection to be used for logging, if none is specified in the configuration file. */
static nImO::Connection kDefaultLogConnection{StaticCast(nImO::IPv4Address, BytesToIPv4Address(239, 17, 12, 1)), 1954};

/*! @brief The connection to be used for status reporting, if none is specified in the configuration file. */
static nImO::Connection kDefaultStatusConnection{StaticCast(nImO::IPv4Address, BytesToIPv4Address(239, 17, 12, 1)), 1955};

/*! @brief The registry search timeout value to be used if none is specified in the configuration file. */
constexpr int   kDefaultRegistryTimeout{5};

/*! @brief The key for the logger address in the configuration file. */
static const std::string    kLoggerAddressKey{"logger address"s};

/*! @brief The key for the logger port in the configuration file. */
static const std::string    kLoggerPortKey{"logger port"s};

/*! @brief The key for the maximum number of seconds to watch for a running Registry. */
static const std::string    kRegistryTimeoutKey{"registry search timeout"s};

/*! @brief The key for the status address in the configuration file. */
static const std::string    kStatusAddressKey{"status address"s};

/*! @brief The key for the status port in the configuration file. */
static const std::string    kStatusPortKey{"status port"s};

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

nImO::ContextWithNetworking::ContextWithNetworking
    (const std::string &    executableName,
     const std::string &    tagForLogging,
     const bool             logging,
     const int              numReservedThreads,
     const std::string &    nodeName) :
        inherited{executableName, nodeName}, _logConnection{kDefaultLogConnection},
        _statusConnection{kDefaultStatusConnection}, _loggingEnabled{logging}
{
    ODL_ENTER(); //####
    ODL_S3s("executableName = ", executableName, "tagForLogging = ", tagForLogging, "nodeName = ", nodeName); //####
    ODL_B1("logging = ", logging); //####
    ODL_I1("numReservedThreads = ", numReservedThreads); //####
#if (! MAC_OR_LINUX_)
    WORD    versionWanted{MAKEWORD(1, 1)};
#endif // not MAC_OR_LINUX_

#if (! MAC_OR_LINUX_)
    if (0 != WSAStartup(versionWanted, &_wsaData))
    {
        std::cerr << "Failed to initialize WinSock\n";
        throw "WinSock problem";

    }
#endif // not MAC_OR_LINUX_
    try
    {
        // The number of threads requested should be one less than the number possible, to account for the main thread
        // and the reserved threads.
        int numThreadsInPool{std::max(static_cast<int>(boost::thread::hardware_concurrency()), 1) - 1};

        if ((0 < numReservedThreads) && ((numReservedThreads + 1) < numThreadsInPool))
        {
            numThreadsInPool -= numReservedThreads;
        }
        _work = std::make_unique<boost::asio::io_service::work>(*getService());
        ODL_P1("_work <- ", _work.get()); //####
        for (int ii = 0; ii < numThreadsInPool; ++ii)
        {
            Ptr(boost::thread)  aThread{new boost::thread([this]
                                                          (void)
                                                          {
                getService()->run();
            })};

            ODL_P1("service thread = ", aThread); //####
            _pool.add_thread(aThread);
        }
        // Get the address and port to use for logging.
        auto    retValue{GetConfiguredValue(kLoggerAddressKey)};

        if (retValue)
        {
            SpValue         actualValue(*retValue);
            CPtr(Address)   asAddress{actualValue->asAddress()};

            if (nullptr != asAddress)
            {
                IPv4Address tempValue{asAddress->getAddressValue()};

                if (239 == (tempValue >> 24))
                {
                    _logConnection._address = tempValue;
                }
                else
                {
                    std::cerr << "Invalid address in configuration file; using default address.\n";
                }
            }
        }
        retValue = GetConfiguredValue(kLoggerPortKey);
        if (retValue)
        {
            SpValue         actualValue(*retValue);
            CPtr(Integer)   asInteger{actualValue->asInteger()};

            if (nullptr != asInteger)
            {
                int64_t tempValue{asInteger->getIntegerValue()};

                if ((0 < tempValue) && (tempValue <= 0x0FFFF))
                {
                    _logConnection._port = StaticCast(IPv4Port, tempValue);
                }
                else
                {
                    std::cerr << "Invalid port in configuration file; using default port.\n";
                }
            }
        }
        retValue = GetConfiguredValue(kStatusAddressKey);
        if (retValue)
        {
            SpValue         actualValue{*retValue};
            CPtr(Address)   asAddress{actualValue->asAddress()};

            if (nullptr != asAddress)
            {
                IPv4Address tempValue{asAddress->getAddressValue()};

                if (239 == (tempValue >> 24))
                {
                    _statusConnection._address = tempValue;
                }
                else
                {
                    std::cerr << "Invalid address in configuration file; using default address.\n";
                }
            }
        }
        retValue = GetConfiguredValue(kStatusPortKey);
        if (retValue)
        {
            SpValue         actualValue{*retValue};
            CPtr(Integer)   asInteger{actualValue->asInteger()};

            if (nullptr != asInteger)
            {
                int64_t tempValue{asInteger->getIntegerValue()};

                if ((0 < tempValue) && (tempValue <= 0x0FFFF))
                {
                    _statusConnection._port = StaticCast(IPv4Port, tempValue);
                }
                else
                {
                    std::cerr << "Invalid port in configuration file; using default port.\n";
                }
            }
        }
        if (_loggingEnabled)
        {
            std::lock_guard<std::mutex> loggerGuard(_loggerLock);

            _logger = std::make_shared<Logger>(getService(), tagForLogging, _logConnection);
            ODL_P1("_logger <- ", _logger.get()); //####
        }
        retValue = GetConfiguredValue(kRegistryTimeoutKey);
        if (retValue)
        {
            SpValue         actualValue(*retValue);
            CPtr(Integer)   asInteger{actualValue->asInteger()};

            if (nullptr == asInteger)
            {
                _registrySearchTimeout = kDefaultRegistryTimeout;
            }
            else
            {
                int tempValue{StaticCast(int, asInteger->getIntegerValue())};

                if (0 < tempValue)
                {
                    _registrySearchTimeout = tempValue;
                }
                else
                {
                    _registrySearchTimeout = kDefaultRegistryTimeout;
                }
            }
        }
        else
        {
            _registrySearchTimeout = kDefaultRegistryTimeout;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::ContextWithNetworking::ContextWithNetworking

nImO::ContextWithNetworking::~ContextWithNetworking
    (void)
{
    ODL_OBJENTER(); //####
    {
        std::lock_guard<std::mutex> loggerGuard{_loggerLock};

        _logger.reset();
    }
    _work.reset(nullptr);
    _pool.join_all();
#if (! MAC_OR_LINUX_)
    WSACleanup();
#endif // not MAC_OR_LINUX_
    ODL_OBJEXIT(); //####
} // nImO::ContextWithNetworking::~ContextWithNetworking

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

Ptr(nImO::InputOutputContext)
nImO::ContextWithNetworking::asInputOutputContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::ContextWithNetworking::asInputOutputContext

CPtr(nImO::InputOutputContext)
nImO::ContextWithNetworking::asInputOutputContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::ContextWithNetworking::asInputOutputContext

Ptr(nImO::ServiceContext)
nImO::ContextWithNetworking::asServiceContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::ContextWithNetworking::asServiceContext

CPtr(nImO::ServiceContext)
nImO::ContextWithNetworking::asServiceContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::ContextWithNetworking::asServiceContext

Ptr(nImO::UtilityContext)
nImO::ContextWithNetworking::asUtilityContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::ContextWithNetworking::asUtilityContext

CPtr(nImO::UtilityContext)
nImO::ContextWithNetworking::asUtilityContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::ContextWithNetworking::asUtilityContext

bool
nImO::ContextWithNetworking::report
    (CPtr(char) stringToSend)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1("stringToSend = ", stringToSend); //####
    bool    okSoFar;

    if (_loggingEnabled)
    {
        std::lock_guard<std::mutex> loggerGuard{_loggerLock};

        if (nullptr == _logger)
        {
            okSoFar = true;
        }
        else
        {
            okSoFar = _logger->report(stringToSend);
        }
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ContextWithNetworking::report

bool
nImO::ContextWithNetworking::report
    (const std::string &    stringToSend)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("stringToSend = ", stringToSend); //####
    bool    okSoFar;

    if (_loggingEnabled)
    {
        std::lock_guard<std::mutex> loggerGuard{_loggerLock};

        if (nullptr == _logger)
        {
            okSoFar = true;
        }
        else
        {
            okSoFar = _logger->report(stringToSend);
        }
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ContextWithNetworking::report

bool
nImO::ContextWithNetworking::report
    (const StringVector & stringsToSend)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1("stringsToSend = ", &stringsToSend); //####
    bool    okSoFar;

    if (_loggingEnabled)
    {
        std::lock_guard<std::mutex> loggerGuard{_loggerLock};

        if (nullptr == _logger)
        {
            okSoFar = true;
        }
        else
        {
            okSoFar = _logger->report(stringsToSend);
        }
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ContextWithNetworking::report

void
nImO::ContextWithNetworking::setCommandPort
    (const IPv4Port commandPort)
{
    ODL_OBJENTER(); //####
    ODL_I1("commandPort = ", commandPort); //####
    if (_loggingEnabled && (nullptr != _logger))
    {
        _logger->setCommandPort(commandPort);
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithNetworking::setCommandPort

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

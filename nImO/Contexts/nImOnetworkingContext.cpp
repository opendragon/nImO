//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Contexts/nImOnetworkingContext.cpp
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

#include <Contexts/nImOnetworkingContext.h>

#include <BasicTypes/nImOaddress.h>
#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <nImOstandardOptions.h>

#include <regex>
#include <string>

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

/*! @brief The multicast connection to be used for logging, if none is specified in the configuration file. */
static nImO::Connection kDefaultLogConnection{StaticCast(nImO::IPv4Address, nImO::BytesToIPv4Address(239, 17, 12, 1)), 1954};

/*! @brief The Registry launch options value to be used if none is specified in the configuration file. */
static const std::string    kDefaultRegistryLaunchOptions{""s};

/*! @brief The multicast connection to be used for status reporting, if none is specified in the configuration file. */
static nImO::Connection kDefaultStatusConnection{StaticCast(nImO::IPv4Address, nImO::BytesToIPv4Address(239, 17, 12, 1)), 1955};

/*! @brief The key for the logger multicast address in the configuration file. */
static const std::string    kLoggerAddressKey{"logger address"s};

/*! @brief The key for the logger multicast port in the configuration file. */
static const std::string    kLoggerPortKey{"logger port"s};

/*! @brief The key for the status multicast address in the configuration file. */
static const std::string    kStatusAddressKey{"status address"s};

/*! @brief The key for the status multicast port in the configuration file. */
static const std::string    kStatusPortKey{"status port"s};

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

bool nImO::NetworkingContext::gHasIpv4{false};

bool nImO::NetworkingContext::gHasIpv6{false};

struct sockaddr_in   nImO::NetworkingContext::gServiceAddressIpv4;

struct sockaddr_in6  nImO::NetworkingContext::gServiceAddressIpv6;

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::NetworkingContext::NetworkingContext
    (const std::string &    tagForLogging,
     const bool             logging,
     const int              numReservedThreads) :
        inherited{}, _logConnection{kDefaultLogConnection}, _loggingEnabled{logging}, _statusConnection{kDefaultStatusConnection}
{
    ODL_ENTER(); //####
    ODL_S1s(tagForLogging); //####
    ODL_B1(logging); //####
    ODL_I1(numReservedThreads); //####
#if (! MAC_OR_LINUX_OR_BSD_)
    WORD    versionWanted{MAKEWORD(1, 1)};
#endif // not MAC_OR_LINUX_OR_BSD_

#if (! MAC_OR_LINUX_OR_BSD_)
    if (0 != WSAStartup(versionWanted, &_wsaData))
    {
        std::cerr << "Failed to initialize WinSock\n";
        throw "WinSock problem"s;

    }
#endif // not MAC_OR_LINUX_OR_BSD_
    try
    {
        // The number of threads requested should be one less than the number possible, to account for the main thread
        // and the reserved threads.
        auto    numThreadsInPool{std::max(StaticCast(int, boost::thread::hardware_concurrency()), 1) - 1};

        if ((0 < numReservedThreads) && ((numReservedThreads + 1) < numThreadsInPool))
        {
            numThreadsInPool -= numReservedThreads;
        }
        _work = std::make_unique<BA::executor_work_guard<BA::io_context::executor_type>>(BA::make_work_guard(*getService()));
        ODL_P1(_work.get()); //####
        for (int ii{0}; ii < numThreadsInPool; ++ii)
        {
            auto    aThread{new boost::thread([this]
                                                (void)
                                                {
                                                    getService()->run();
                                                })};

            ODL_P1(aThread); //####
            _pool.add_thread(aThread);
        }
        // Get the address and port to use for logging.
        auto    retValue{GetConfiguredValue(kLoggerAddressKey)};

        if (retValue)
        {
            SpValue actualValue{*retValue};

            if (auto asAddress{actualValue->asAddress()}; nullptr == asAddress)
            {
                std::cerr << "Invalid address (" << kLoggerAddressKey << ") in configuration file; ignored.\n";
            }
            else
            {
                auto    tempValue{asAddress->getAddressValue()};

                if (239 == (tempValue >> 24))
                {
                    _logConnection._address = tempValue;
                }
                else
                {
                    std::cerr << "Invalid address (" << kLoggerAddressKey << ") in configuration file; using default address.\n";
                }
            }
        }
        retValue = GetConfiguredValue(kLoggerPortKey);
        if (retValue)
        {
            SpValue actualValue{*retValue};

            if (auto asInteger{actualValue->asInteger()}; nullptr == asInteger)
            {
                std::cerr << "Invalid port (" << kLoggerPortKey << ") in configuration file; ignored.\n";
            }
            else
            {
                int64_t tempValue{asInteger->getIntegerValue()};

                if ((0 < tempValue) && (tempValue <= 0x0FFFF))
                {
                    _logConnection._port = StaticCast(IPv4Port, tempValue);
                }
                else
                {
                    std::cerr << "Invalid port (" << kLoggerPortKey << ") in configuration file; using default port.\n";
                }
            }
        }
        retValue = GetConfiguredValue(kStatusAddressKey);
        if (retValue)
        {
            SpValue actualValue{*retValue};

            if (auto asAddress{actualValue->asAddress()}; nullptr == asAddress)
            {
                std::cerr << "Invalid address (" << kStatusAddressKey << ") in configuration file; ignored.\n";
            }
            else
            {
                IPv4Address tempValue{asAddress->getAddressValue()};

                if (239 == (tempValue >> 24))
                {
                    _statusConnection._address = tempValue;
                }
                else
                {
                    std::cerr << "Invalid address (" << kStatusAddressKey << ") in configuration file; using default address.\n";
                }
            }
        }
        retValue = GetConfiguredValue(kStatusPortKey);
        if (retValue)
        {
            SpValue actualValue{*retValue};

            if (auto asInteger{actualValue->asInteger()}; nullptr == asInteger)
            {
                std::cerr << "Invalid port (" << kStatusPortKey << ") in configuration file; ignored.\n";
            }
            else
            {
                int64_t tempValue{asInteger->getIntegerValue()};

                if ((0 < tempValue) && (tempValue <= 0x0FFFF))
                {
                    _statusConnection._port = StaticCast(IPv4Port, tempValue);
                }
                else
                {
                    std::cerr << "Invalid port (" << kStatusPortKey << ") in configuration file; using default port.\n";
                }
            }
        }
        if (_loggingEnabled)
        {
            std::lock_guard<std::mutex> loggerGuard{_loggerLock};

            _logger = std::make_shared<Logger>(getService(), tagForLogging, _logConnection);
            ODL_P1(_logger.get()); //####
        }
        if (_statusConnection == _logConnection)
        {
            throw "The status connection and the logging connection are the same."s;

        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
        
    }
    ODL_EXIT_P(this); //####
} // nImO::NetworkingContext::NetworkingContext

nImO::NetworkingContext::~NetworkingContext
    (void)
{
    ODL_OBJENTER(); //####
    {
        std::lock_guard<std::mutex> loggerGuard{_loggerLock};

        _logger.reset();
    }
    _work.reset(nullptr);
    _pool.join_all();
#if (! MAC_OR_LINUX_OR_BSD_)
    WSACleanup();
#endif // not MAC_OR_LINUX_OR_BSD_
    ODL_OBJEXIT(); //####
} // nImO::NetworkingContext::~NetworkingContext

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

Ptr(nImO::InputOutputContext)
nImO::NetworkingContext::asInputOutputContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::NetworkingContext::asInputOutputContext

CPtr(nImO::InputOutputContext)
nImO::NetworkingContext::asInputOutputContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::NetworkingContext::asInputOutputContext

Ptr(nImO::ServiceContext)
nImO::NetworkingContext::asServiceContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::NetworkingContext::asServiceContext

CPtr(nImO::ServiceContext)
nImO::NetworkingContext::asServiceContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::NetworkingContext::asServiceContext

Ptr(nImO::UtilityContext)
nImO::NetworkingContext::asUtilityContext
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::NetworkingContext::asUtilityContext

CPtr(nImO::UtilityContext)
nImO::NetworkingContext::asUtilityContext
    (void)
    const
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT_P(nullptr); //####
    return nullptr;
} // nImO::NetworkingContext::asUtilityContext

bool
nImO::NetworkingContext::report
    (CPtr(char) stringToSend)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1(stringToSend); //####
    bool    okSoFar{false};

    if (_loggingEnabled)
    {
        if (nullptr == _logger)
        {
            okSoFar = true;
            ODL_B1(okSoFar); //####
        }
        else
        {
            std::lock_guard<std::mutex> loggerGuard{_loggerLock};

            okSoFar = _logger->report(stringToSend);
            ODL_B1(okSoFar); //####
        }
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
        ODL_B1(okSoFar); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::NetworkingContext::report

bool
nImO::NetworkingContext::report
    (const std::string &    stringToSend)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s(stringToSend); //####
    bool    okSoFar{false};

    if (_loggingEnabled)
    {
        if (nullptr == _logger)
        {
            okSoFar = true;
            ODL_B1(okSoFar); //####
        }
        else
        {
            std::lock_guard<std::mutex> loggerGuard{_loggerLock};

            okSoFar = _logger->report(stringToSend);
            ODL_B1(okSoFar); //####
        }
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
        ODL_B1(okSoFar); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::NetworkingContext::report

bool
nImO::NetworkingContext::report
    (const StdStringVector &    stringsToSend)
    const
{
    ODL_OBJENTER(); //####
    ODL_P1(&stringsToSend); //####
    bool    okSoFar{false};

    if (_loggingEnabled)
    {
        if (nullptr == _logger)
        {
            okSoFar = true;
            ODL_B1(okSoFar); //####
        }
        else
        {
            std::lock_guard<std::mutex> loggerGuard{_loggerLock};

            okSoFar = _logger->report(stringsToSend);
            ODL_B1(okSoFar); //####
        }
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
        ODL_B1(okSoFar); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::NetworkingContext::report

void
nImO::NetworkingContext::setCommandPort
    (const IPv4Port commandPort)
{
    ODL_OBJENTER(); //####
    ODL_I1(commandPort); //####
    if (_loggingEnabled && (nullptr != _logger))
    {
        _logger->setCommandPort(commandPort);
    }
    ODL_OBJEXIT(); //####
} // nImO::NetworkingContext::setCommandPort

void
nImO::NetworkingContext::setTag
    (const std::string &    newTag)
{
    ODL_OBJENTER(); //####
    ODL_S1s(newTag); //####
    if (_loggingEnabled && (nullptr != _logger))
    {
        _logger->setTag(newTag);
    }
    ODL_OBJEXIT(); //####
} // nImO::NetworkingContext::setTag

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

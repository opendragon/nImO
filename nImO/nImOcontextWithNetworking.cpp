//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithNetworking.cpp
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

#include <nImOcontextWithNetworking.h>

#include <initFileAddress.h>
#include <initFileInteger.h>
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
static nImO::Connection kDefaultLogConnection{StaticCast(uint32_t, IPV4_ADDR(239, 17, 12, 1)), 1954};

/*! @brief The registry search timeout value to be used if none is specified in the configuration file. */
static int kDefaultRegistryTimeout = 5;

/*! @brief The key for the logger address in the configuration file. */
static std::string  kAddressKey = "logger address";

/*! @brief The key for the logger port in the configuration file. */
static std::string  kPortKey = "logger port";

/*! @brief The key for the maximum number of seconds to watch for a running Registry. */
static std::string  kRegistryTimeoutKey = "registry search timeout";

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
     const std::string &    tag,
     const bool             logging,
     const int              numReservedThreads,
     const std::string &    nodeName) :
        inherited(executableName, nodeName), _logConnection(kDefaultLogConnection), _loggingEnabled(logging), _logger(nullptr)
{
#if (! MAC_OR_LINUX_)
    WORD    versionWanted = MAKEWORD(1, 1);
#endif // not MAC_OR_LINUX_

#if (! MAC_OR_LINUX_)
    ODL_ENTER(); //####
    //ODL_S3s("progName = ", executableName, "tag = ", tag, "nodeName = ", nodeName); //####
    //ODL_B1("logging = ", logging); //####
    if (0 != WSAStartup(versionWanted, &_wsaData))
    {
        std::cerr << "Failed to initialize WinSock" << std::endl;
        throw "WinSock problem";

    }
#endif // not MAC_OR_LINUX_
    try
    {
        // The number of threads requested should be one less than the number possible, to account for the main thread
        // and the reserved threads.
        int numThreadsInPool = std::max(static_cast<int>(thread::hardware_concurrency()), 1) - 1;

        if ((0 < numReservedThreads) && ((numReservedThreads + 1) < numThreadsInPool))
        {
            numThreadsInPool -= numReservedThreads;
        }
        _work.reset(new asio::io_service::work(*getService()));
        for (int ii = 0; ii < numThreadsInPool; ++ii)
        {
            _pool.create_thread([this]
                                (void)
                                {
                                    getService()->run();
                                });
        }
        // Get the address and port to use for logging.
        boost::optional<InitFile::SpBaseValue>  retValue = GetConfiguredValue(kAddressKey);

        if (retValue)
        {
            InitFile::SpBaseValue       actualValue{*retValue};
            Ptr(InitFile::AddressValue) asAddress{actualValue->AsAddress()};

            if (nullptr != asAddress)
            {
                uint64_t    tempValue = asAddress->GetValue();

                if (239 == (tempValue >> 24))
                {
                    _logConnection._address = tempValue;
                }
                else
                {
                    std::cerr << "Invalid address in configuration file; using default address." << std::endl;
                }
            }
        }
        retValue = GetConfiguredValue(kPortKey);
        if (retValue)
        {
            InitFile::SpBaseValue       actualValue{*retValue};
            Ptr(InitFile::IntegerValue) asInteger{actualValue->AsInteger()};

            if (nullptr != asInteger)
            {
                int64_t tempValue = asInteger->GetValue();

                if ((0 < tempValue) && (tempValue <= 0x0FFFF))
                {
                    _logConnection._port = StaticCast(uint16_t, tempValue);
                }
                else
                {
                    std::cerr << "Invalid port in configuration file; using default port." << std::endl;
                }
            }
        }
        if (_loggingEnabled)
        {
            std::lock_guard<std::mutex> loggerGuard(_loggerLock);

            _logger = new Logger(getService(), tag, _logConnection);
        }
        retValue = GetConfiguredValue(kRegistryTimeoutKey);
        if (retValue)
        {
            InitFile::SpBaseValue       actualValue(*retValue);
            Ptr(InitFile::IntegerValue) asInteger{actualValue->AsInteger()};

            if (nullptr == asInteger)
            {
                _registrySearchTimeout = kDefaultRegistryTimeout;
            }
            else
            {
                int tempValue = asInteger->GetValue();

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
        std::lock_guard<std::mutex> loggerGuard(_loggerLock);

        if (nullptr != _logger)
        {
            delete _logger;
            _logger = nullptr;
        }
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

bool
nImO::ContextWithNetworking::report
    (CPtr(char) stringToSend)
    const
{
    bool    okSoFar;

    ODL_OBJENTER(); //####
    if (_loggingEnabled)
    {
        std::lock_guard<std::mutex> loggerGuard(_loggerLock);

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
    bool    okSoFar;

    ODL_OBJENTER(); //####
    if (_loggingEnabled)
    {
        std::lock_guard<std::mutex> loggerGuard(_loggerLock);

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
    bool    okSoFar;

    ODL_OBJENTER(); //####
    if (_loggingEnabled)
    {
        std::lock_guard<std::mutex> loggerGuard(_loggerLock);

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
    (const uint16_t commandPort)
{
    ODL_OBJENTER(); //####
    if (_loggingEnabled && (nullptr != _logger))
    {
        _logger->setCommandPort(commandPort);
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithNetworking::setCommandPort

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

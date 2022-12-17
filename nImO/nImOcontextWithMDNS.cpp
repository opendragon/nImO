//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcontextWithMDNS.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO execution contexts that use mDNS.
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
//  Created:    2022-07-18
//
//--------------------------------------------------------------------------------------------------

#include "nImOcontextWithMDNS.h"
#include "initFileAddress.h"
#include "initFileInteger.h"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO execution contexts that use mDNS. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief A macro to convert four integers into an IPv4 address. */
#define IPV4_ADDR(a_, b_, c_, d_) \
    (((a_ & 0xff) << 24) | ((b_ & 0xff) << 16) | ((c_ & 0xff) << 8) | (d_ & 0xff))

/*! @brief The address to be used for logging, if none is specified in the configuration file. */
static uint32_t  kDefaultLogAddress = IPV4_ADDR(239, 17, 12, 1);

/*! @brief The port to be used for logging, if none is specified in the configuration file. */
static uint16_t kDefaultLogPort = 1954;

/*! @brief The key for the logger address in the configuration file. */
static std::string  kAddressKey = "logger address";

/*! @brief The key for the logger port in the configuration file. */
static std::string  kPortKey = "logger port";

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

nImO::ContextWithMDNS::ContextWithMDNS
    (const std::string &    executableName,
     const bool             logging,
     const std::string &    nodeName) :
        inherited(executableName, nodeName), _loggingEnabled(logging), _logger(nullptr)
{
    ODL_ENTER(); //####
    //ODL_S2s("progName = ", executableName, "nodeName = ", nodeName); //####
    //ODL_B1("logging = ", logging); //####
    try
    {
        // Get the address and port to use for logging.
        boost::optional<InitFile::SpBaseValue>  retValue = GetConfiguredValue(kAddressKey);

        if (retValue)
        {
            InitFile::SpBaseValue       actualValue = *retValue;
            Ptr(InitFile::AddressValue) asAddress = actualValue->AsAddress();

            if (nullptr == asAddress)
            {
                _logAddress = kDefaultLogAddress;
            }
            else
            {
                _logAddress = asAddress->GetValue();
            }
        }
        else
        {
            _logAddress = kDefaultLogAddress;
        }
        retValue = GetConfiguredValue(kPortKey);
        if (retValue)
        {
            InitFile::SpBaseValue       actualValue = *retValue;
            Ptr(InitFile::IntegerValue) asInteger = actualValue->AsInteger();

            if (nullptr == asInteger)
            {
                _logPort = kDefaultLogPort;
            }
            else
            {
                int64_t tempValue = asInteger->GetValue();

                if ((0 < tempValue) && (tempValue <= 0x0FFFF))
                {
                    _logPort = StaticCast(uint16_t, tempValue);
                }
                else
                {
                    _logPort = kDefaultLogPort;
                }
            }
        }
        else
        {
            _logPort = kDefaultLogPort;
        }
        if (_loggingEnabled)
        {
            _logger = new Logger(_logAddress, _logPort);
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_P(this); //####
} // nImO::ContextWithMDNS::ContextWithMDNS

nImO::ContextWithMDNS::~ContextWithMDNS
    (void)
{
    ODL_OBJENTER(); //####
    if (nullptr != _logger)
    {
        delete _logger;
    }
    ODL_OBJEXIT(); //####
} // nImO::ContextWithMDNS::~ContextWithMDNS

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

//void
//nImO::ContextWithMDNS::addListeningPort
//    (void)
//{
//    ODL_OBJENTER(); //####
//    if (nullptr != _logger)
//    {
//        _logger->addListeningPort();
//    }
//    ODL_OBJEXIT(); //####
//} // nImO::ContextWithMDNS::addListeningPort

//void
//nImO::ContextWithMDNS::removeListeningPort
//    (void)
//{
//    ODL_OBJENTER(); //####
//    if (nullptr != _logger)
//    {
//        _logger->removeListeningPort();
//    }
//    ODL_OBJEXIT(); //####
//} // nImO::ContextWithMDNS::removeListeningPort

bool
nImO::ContextWithMDNS::report
    (const std::string &    stringToSend)
    const
{
    bool    okSoFar;

    ODL_OBJENTER(); //####
    if (_loggingEnabled && (nullptr != _logger))
    {
        okSoFar = _logger->report(stringToSend);
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ContextWithMDNS::report

bool
nImO::ContextWithMDNS::report
    (const nImO::StringVector & stringsToSend)
    const
{
    bool    okSoFar;

    ODL_OBJENTER(); //####
    if (_loggingEnabled && (nullptr != _logger))
    {
        okSoFar = _logger->report(stringsToSend);
    }
    else
    {
        okSoFar = true; // If we aren't set up for logging, ignore this call.
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ContextWithMDNS::report

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

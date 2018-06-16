//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOcommon.cpp
//
//  Project:    nImO
//
//  Contains:   The function and class definitions for common entities for nImO.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2016 by OpenDragon.
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
//  Created:    2016-03-21
//
//--------------------------------------------------------------------------------------------------

#include "nImOcommon.hpp"

#include <nImObaseArgumentDescriptor.hpp>
#include <nImOvalue.hpp>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(MAC_OR_LINUX_)
# include <unistd.h>
#else // ! defined(MAC_OR_LINUX_)
# include <Windows.h>
#endif // ! defined(MAC_OR_LINUX_)

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The function and variable definitions for common entities for nImO applications. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

using namespace nImO;
using std::cout;
using std::endl;

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief @c true once the random number generator is seeded. */
static bool lRandomSeeded = false;

#if 0
/*! @brief The maximum integer that we wish to use for generated random values. */
static const int kMaxRandom = 123456789;
#endif//0

#if 0
/*! @brief @c true if the executable is running or ready-to-run and @c false otherwise. */
static bool lKeepRunning = false;

#if defined(MAC_OR_LINUX_)
/*! @brief The logger to use for reporting problems. */
static yarp::os::impl::Logger * lLogger = nullptr;
#endif // defined(MAC_OR_LINUX_)
#endif//0

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

const char nImO::kBlobSeparator = '%';

const char nImO::kEndArrayChar = ')';

const char nImO::kEndMapChar = '}';

const char nImO::kEndSetChar = ']';

const char nImO::kKeyValueSeparator = '>';

const char nImO::kSingleQuote = '\'';

const char nImO::kStartArrayChar = '(';

const char nImO::kStartMapChar = '{';

const char nImO::kStartSetChar = '[';

const uint8_t nImO::kDoubleQuote = '"';

const uint8_t nImO::kEscapeChar = '\\';

// Note that this MUST be a single-character string!!!
#if defined(MAC_OR_LINUX_)
const std::string nImO::kDirectorySeparator = "/";
#else // ! defined(MAC_OR_LINUX_)
const std::string nImO::kDirectorySeparator = "\\";
#endif // ! defined(MAC_OR_LINUX_)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(MAC_OR_LINUX_)
/*! @brief The signal handler to catch requests to stop the service.
 @param[in] signal The signal being handled. */
[[noreturn]]
static void
localCatcher(UNUSED_ int signal)
{
    ODL_ENTER(); //####
    ODL_LL1("signal = ", signal); //####
#if 0
    if (lLogger)
    {
        std::string message("Exiting due to signal ");

        message += std::to_string(signal);
        message += " = ";
        message += NameOfSignal(signal);
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->error("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->error(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
    }
#endif//0
    ODL_EXIT_EXIT(1); //####
    exit(1);
} // localCatcher
#endif // defined(MAC_OR_LINUX_)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

double
nImO::B2D(const nImO::NumberAsBytes &inString)
{
    ODL_ENTER(); //####
    ODL_P1("inString = ", &inString); //####
    int64_t inValueCopy = B2I(inString, sizeof(inValueCopy));
    double  result = *reinterpret_cast<double *>(&inValueCopy);

    ODL_EXIT_D(result); //####
    return result;
} // nImO::B2D

int64_t
nImO::B2I(const nImO::NumberAsBytes &inString,
          const size_t              numBytes)
{
    ODL_ENTER(); //####
    ODL_P1("inString = ", &inString); //####
    ODL_LL1("numBytes = ", numBytes); //####
    bool          isNegative = (0 != (0x080 & inString[0]));
    const uint8_t *walker = inString;
    int64_t       result = (isNegative ? -1 : 0);

    for (size_t ii = 0; numBytes > ii; ++ii)
    {
        uint8_t aByte = *walker++;

        result = ((result << 8) | aByte);
    }
    ODL_EXIT_LL(result); //####
    return result;
} // nImO::B2I

size_t
nImO::CompareBytes(const void   *first,
                   const void   *second,
                   const size_t numBytes)
{
    ODL_ENTER(); //####
    ODL_P2("first = ", first, "second = ", second); //####
    ODL_LL1("numBytes = ", numBytes); //####
    size_t result = 0;

    if (memcmp(first, second, numBytes))
    {
        const uint8_t *firstWalker = static_cast<const uint8_t *>(first);
        const uint8_t *secondWalker = static_cast<const uint8_t *>(second);

        for (size_t ii = 0; numBytes > ii; ++ii)
        {
            uint8_t firstByte = *firstWalker++;
            uint8_t secondByte = *secondWalker++;

            if (firstByte != secondByte)
            {
                ODL_LL1("mismatch at index: ", ii); //####
                result = ii + 1;
                break;
            }

        }
    }
    ODL_EXIT_LL(result); //####
    return result;
} // nImO::CompareBytes

std::string
nImO::ConvertDoubleToString(const double value)
{
    ODL_ENTER(); //####
    ODL_D1("value = ", value); //####
    // Note that boost::lexical_cast<std::string>(double) generates strings with trailing digits.
    // That is, 1E-22 winds up as 9.9999999999999E-21, which is platform-sensitive.
    std::ostringstream holder;

    holder << std::defaultfloat << value;
    std::string result(holder.str());

    ODL_EXIT_s(result); //####
    return result;
} // nImO::ConvertDoubleToString

bool
nImO::ConvertToDouble(const char *startPtr,
                      double     &result)
{
    ODL_ENTER(); //####
    ODL_S1("startPtr = ", startPtr); //####
    ODL_P1("result = ", &result); //####
    bool   okSoFar;
    char   *endPtr;
    double value = strtod(startPtr, &endPtr);

    if ((startPtr != endPtr) && (! *endPtr))
    {
        result = value;
        ODL_D1("result <- ", result); //####
        okSoFar = true;
    }
    else
    {
        okSoFar = false;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ConvertToDouble

bool
nImO::ConvertToLong(const char *startPtr,
                    int64_t    &result)
{
    ODL_ENTER(); //####
    ODL_S1("startPtr = ", startPtr); //####
    ODL_P1("result = ", &result); //####
    bool okSoFar;
    char *endPtr;
    long value = strtol(startPtr, &endPtr, 10);

    if ((startPtr != endPtr) && (! *endPtr))
    {
        result = value;
        ODL_L1("result <- ", result); //####
        okSoFar = true;
    }
    else
    {
        okSoFar = false;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ConvertToLong

void
nImO::D2B(const double        inValue,
          nImO::NumberAsBytes &outString)
{
    ODL_ENTER(); //####
    ODL_D1("inValue = ", inValue); //####
    ODL_P1("outString = ", &outString); //####
    double  inValueCopy = inValue;
    int64_t inValueAsInt = *reinterpret_cast<int64_t *>(&inValueCopy);

    I2B(inValueAsInt, outString);
    ODL_EXIT(); //####
} // nImO::D2B

#if 0
void
nImO::DumpContactToLog(const char              *tag,
                       const yarp::os::Contact &aContact)
{
#if defined(MAC_OR_LINUX_)
    if (lLogger)
    {
        std::string message("tag = ");

        message += tag;
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->info("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->info(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
        message = "contact.carrier = ";
        message += aContact.getCarrier();
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->info("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->info(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
        message = "contact.host = ";
        message += aContact.getHost();
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->info("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->info(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
        message = "contact.isValid = ";
        message += (aContact.isValid() ? "true" : "false");
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->info("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->info(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
        message = "contact.name = ";
        message += aContact.getName();
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->info("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->info(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
        message = "contact.port = ";
        message += std::to_string(aContact.getPort());
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->info("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->info(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
        message = "contact.toString = ";
        message += aContact.toString();
# if USE_YARP_FATAL_NOT_FAIL_
        lLogger->info("%s", message.c_str());
# else // ! USE_YARP_FATAL_NOT_FAIL_
        lLogger->info(message.c_str());
# endif // ! USE_YARP_FATAL_NOT_FAIL_
    }
#endif // defined(MAC_OR_LINUX_)
} // nImO::DumpContactToLog

#if defined(MAC_OR_LINUX_)
yarp::os::impl::Logger &
nImO::GetLogger(void)
{
    ODL_ENTER(); //####
    ODL_EXIT_P(lLogger);
    return *lLogger;
} // nImO::GetLogger
#endif // defined(MAC_OR_LINUX_)
#endif //0

std::string
nImO::GetRandomChannelName(const char *channelRoot)
{
    ODL_ENTER(); //####
    ODL_S1("channelRoot = ", channelRoot); //####
    std::string result;

    try
    {
        bool              hasLeadingSlash = false;
        const char        *stringToUse;
#if 0
        int               randNumb = static_cast<int>(yarp::os::Random::uniform() * kMaxRandom);
#else//0
        int               randNumb = 17;
#endif//0
        std::stringstream buff;

        if (channelRoot)
        {
            stringToUse = channelRoot;
            if ('/' == *channelRoot)
            {
                hasLeadingSlash = true;
            }
        }
        else
        {
            stringToUse = "_";
        }
        if (! hasLeadingSlash)
        {
            buff << "/" ;
        }
        buff << stringToUse << std::hex << randNumb;
        result = buff.str();
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::GetRandomChannelName

std::string
nImO::GetRandomChannelName(const std::string &channelRoot)
{
    return GetRandomChannelName(channelRoot.c_str());
} // nImO::GetRandomChannelName

size_t
nImO::I2B(const int64_t       inValue,
          nImO::NumberAsBytes &outString)
{
    ODL_ENTER(); //####
    ODL_XL1("inValue = ", inValue); //####
    ODL_P1("outString = ", &outString); //####
    int64_t workValue = inValue;
    size_t  length = 0;

    for (size_t ii = sizeof(inValue); 0 < ii; --ii)
    {
        outString[ii - 1] = (0x0FF & workValue);
        workValue >>= 8;
    }
    if (0 <= inValue)
    {
        for (size_t ii = 0; (0 == length) && (sizeof(inValue) > ii); ++ii)
        {
            if (0x00 != outString[ii])
            {
                length = sizeof(inValue) - ii;
            }
        }
        // Correct for the MSB having the sign bit set
        if (0 < length)
        {
            uint8_t aByte = outString[sizeof(inValue) - length];

            if (0x00 != (0x080 & aByte))
            {
                ++length;
            }
        }
    }
    else
    {
        for (size_t ii = 0; (0 == length) && (sizeof(inValue) > ii); ++ii)
        {
            if (0xFF != outString[ii])
            {
                length = sizeof(inValue) - ii;
            }
        }
        // Correct for the MSB not having the sign bit set
        if (0 < length)
        {
            uint8_t aByte = outString[sizeof(inValue) - length];

            if (0x00 == (0x080 & aByte))
            {
                ++length;
            }
        }
    }
    ODL_EXIT_LL(length); //####
    return length;
} // nImO::I2B

#if (! defined(MAC_OR_LINUX_))
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! defined(MAC_OR_LINUX_)
void
nImO::Initialize(UNUSED_ const std::string &progName)
{
    ODL_ENTER(); //####
    ODL_S1s("progName = ", progName); //####
    try
    {
        Value::initialize();
#if 0
#if (defined(ODL_ENABLE_LOGGING_) && defined(MpM_LogIncludesYarpTrace))
        yarp::os::Network::setVerbosity(1);
#else // ! (defined(ODL_ENABLE_LOGGING_) && defined(MpM_LogIncludesYarpTrace))
        yarp::os::Network::setVerbosity(-1);
#endif // ! (defined(ODL_ENABLE_LOGGING_) && defined(MpM_LogIncludesYarpTrace))
        double intPart;
        double now = yarp::os::Time::now();
        double fraction = modf(now, &intPart);
        int    seed = static_cast<int>(ceil(fraction * kMaxRandom));

#if defined(MpM_ChattyStart)
# if defined(MAC_OR_LINUX_)
        if (lLogger)
        {
            std::string message("Program ");

            message += progName;
#  if USE_YARP_FATAL_NOT_FAIL_
            lLogger->info("%s", message.c_str());
#  else // ! USE_YARP_FATAL_NOT_FAIL_
            lLogger->info(message.c_str());
#  endif // ! USE_YARP_FATAL_NOT_FAIL_
            lLogger->info("Movement And Meaning Version: " MpM_VERSION_ ", YARP Version: "
                          YARP_VERSION_STRING ", ACE Version: " ACE_VERSION);
        }
# endif // defined(MAC_OR_LINUX_)
#endif // defined(MpM_ChattyStart)
        ODL_D2("time = ", now, "fraction = ", fraction); //####
        ODL_LL1("seed = ", seed); //####
        yarp::os::Random::seed(seed);
#endif//0
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT(); //####
} // nImO::Initialize
#if (! defined(MAC_OR_LINUX_))
# pragma warning(pop)
#endif // ! defined(MAC_OR_LINUX_)

void
nImO::SetSignalHandlers(nImO::SignalHandler theHandler)
{
    ODL_ENTER(); //####
#if defined(MAC_OR_LINUX_)
    sigset_t         blocking;
    struct sigaction act;
#endif // defined(MAC_OR_LINUX_)

#if defined(MAC_OR_LINUX_)
    act.sa_handler = theHandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
# if (defined(SIGABRT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_))
    sigaction(SIGABRT, &act, nullptr);
# endif // defined(SIGABRT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGHUP) && (SIGHUP != STANDARD_SIGNAL_TO_USE_))
    sigaction(SIGHUP, &act, nullptr);
# endif // defined(SIGHUP) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGINT) && (SIGINT != STANDARD_SIGNAL_TO_USE_))
    sigaction(SIGINT, &act, nullptr);
# endif // defined(SIGINT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGQUIT) && (SIGQUIT != STANDARD_SIGNAL_TO_USE_))
    sigaction(SIGQUIT, &act, nullptr);
# endif // defined(SIGQUIT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGUSR1) && (SIGUSR1 != STANDARD_SIGNAL_TO_USE_))
    sigaction(SIGUSR1, &act, nullptr);
# endif // defined(SIGUSR1) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGUSR2) && (SIGUSR2 != STANDARD_SIGNAL_TO_USE_))
    sigaction(SIGUSR2, &act, nullptr);
# endif // defined(SIGUSR2) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
    sigemptyset(&blocking);
    sigaddset(&blocking, STANDARD_SIGNAL_TO_USE_);
    pthread_sigmask(SIG_BLOCK, &blocking, nullptr);
#else // ! defined(MAC_OR_LINUX_)
# if (defined(SIGABRT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_))
    //yarp::os::signal(SIGABRT, theHandler);
    signal(SIGABRT, theHandler); //windows doesn't like the yarp signals for some reason
# endif // defined(SIGABRT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGHUP) && (SIGHUP != STANDARD_SIGNAL_TO_USE_))
    yarp::os::signal(SIGHUP, theHandler);
# endif // defined(SIGHUP) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGINT) && (SIGINT != STANDARD_SIGNAL_TO_USE_))
    //yarp::os::signal(SIGINT, theHandler);
    signal(SIGINT, theHandler); //windows doesn't like the yarp signals for some reason
# endif // defined(SIGINT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGQUIT) && (SIGQUIT != STANDARD_SIGNAL_TO_USE_))
    yarp::os::signal(SIGQUIT, theHandler);
# endif // defined(SIGQUIT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGUSR1) && (SIGUSR1 != STANDARD_SIGNAL_TO_USE_))
    yarp::os::signal(SIGUSR1, theHandler);
# endif // defined(SIGUSR1) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGUSR2) && (SIGUSR2 != STANDARD_SIGNAL_TO_USE_))
    yarp::os::signal(SIGUSR2, theHandler);
# endif // defined(SIGUSR2) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
#if 0
    yarp::os::signal(SIGTERM, theHandler);
#endif//0
#endif // ! defined(MAC_OR_LINUX_)
    ODL_EXIT(); //####
} // Common::SetSignalHandlers

void
nImO::SetUpCatcher(void)
{
    ODL_ENTER(); //####
#if defined(MAC_OR_LINUX_)
    sigset_t         unblocking;
    struct sigaction act;
#endif // defined(MAC_OR_LINUX_)

#if defined(MAC_OR_LINUX_)
    sigemptyset(&unblocking);
    sigaddset(&unblocking, STANDARD_SIGNAL_TO_USE_);
    pthread_sigmask(SIG_UNBLOCK, &unblocking, nullptr);
    act.sa_handler = localCatcher;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(STANDARD_SIGNAL_TO_USE_, &act, nullptr);
#else // ! defined(MAC_OR_LINUX_)
#endif // ! defined(MAC_OR_LINUX_)
    ODL_EXIT(); //####
} // nImO::SetUpCatcher

#if 0
#if defined(MAC_OR_LINUX_)
void
nImO::SetUpLogger(const std::string &progName)
{
    ODL_ENTER(); //####
    lLogger = new yarp::os::impl::Logger(progName.c_str());
    if (lLogger)
    {
        lLogger->setVerbosity(1);
    }
    ODL_EXIT(); //####
} // nImO::SetUpLogger
#endif // defined(MAC_OR_LINUX_)
#endif//0

void
nImO::ShutDownCatcher(void)
{
    ODL_ENTER(); //####
#if defined(MAC_OR_LINUX_)
    sigset_t         blocking;
    struct sigaction act;
#endif // defined(MAC_OR_LINUX_)

#if defined(MAC_OR_LINUX_)
    sigemptyset(&blocking);
    sigaddset(&blocking, STANDARD_SIGNAL_TO_USE_);
    pthread_sigmask(SIG_BLOCK, &blocking, nullptr);
    act.sa_handler = SIG_DFL;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(STANDARD_SIGNAL_TO_USE_, &act, nullptr);
#else // ! defined(MAC_OR_LINUX_)
#endif // ! defined(MAC_OR_LINUX_)
    ODL_EXIT(); //####
} // nImO::ShutDownCatcher

#if 0
void
nImO::Stall(void)
{
    for ( ; ; )
    {
        ConsumeSomeTime();
    }
} // nImO::Stall
#endif//0

bool
nImO::CanReadFromStandardInput(void)
{
    ODL_ENTER(); //####
#if defined(MAC_OR_LINUX_)
    pid_t fg = tcgetpgrp(STDIN_FILENO);
#else // ! defined(MAC_OR_LINUX_)
    HWND  wind = GetConsoleWindow();
#endif // ! defined(MAC_OR_LINUX_)
    bool  result = false;

#if defined(MAC_OR_LINUX_)
    if (-1 == fg)
    {
        // Piped
        result = true;
    }
    else if (getpgrp() == fg)
    {
        // Foreground
        result = true;
    }
    else
    {
        // Background
        result = false;
    }
#else // ! defined(MAC_OR_LINUX_)
    result = (nullptr != wind);
#endif // ! defined(MAC_OR_LINUX_)
    ODL_EXIT_B(result); //####
    return result;
} // nImO::CanReadFromStandardInput

#if 0
void
nImO::ConsumeSomeTime(const double factor)
{
    ODL_ENTER(); //####
    yarp::os::Time::delay(ONE_SECOND_DELAY_ / factor);
    yarp::os::Time::yield();
    ODL_EXIT(); //####
} // nImO::ConsumeSomeTime
#endif//0

std::string
nImO::GetRandomHexString(void)
{
    ODL_ENTER(); //####
    int               randNumb;
    std::string       result;
    std::stringstream buff;

    if (! lRandomSeeded)
    {
#if defined(__APPLE__)
        sranddev();
#else // ! defined(__APPLE__)
        srand(clock());
#endif // ! defined(__APPLE__)
        lRandomSeeded = true;
    }
    randNumb = (rand() % 10000);
    buff << std::hex << randNumb;
    result = buff.str();
    ODL_EXIT_s(result); //####
    return result;
} // nImO::GetRandomHexString

#if 0
void
nImO::IdleUntilNotRunning(void)
{
    ODL_ENTER(); //####
    for ( ; IsRunning(); )
    {
        ConsumeSomeTime();
    }
    ODL_EXIT(); //####
} // nImO::IdleUntilNotRunning

bool
nImO::IsRunning(void)
{
    ODL_ENTER(); //####
    ODL_EXIT_B(lKeepRunning); //####
    return lKeepRunning;
} // nImO::IsRunning
#endif//0

const char *
nImO::NameOfSignal(const int theSignal)
{
    const char *result;

#if defined(MAC_OR_LINUX_)
    switch (theSignal)
    {
        case SIGHUP :
            result = "SIGHUP[hangup]";
            break;

        case SIGINT :
            result = "SIGINT[interrupt]";
            break;

        case SIGQUIT :
            result = "SIGQUIT[quit]";
            break;

        case SIGILL :
            result = "SIGILL[illegal instruction]";
            break;

        case SIGTRAP :
            result = "SIGTRAP[trace trap]";
            break;

        case SIGABRT :
            result = "SIGABRT[abort()]";
            break;

# if (defined(_POSIX_C_SOURCE) && (! defined(_DARWIN_C_SOURCE)))
        case SIGPOLL :
            result = "SIGPOLL[pollable evebt]";
            break;
# else // (! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE)
        case SIGEMT :
            result = "SIGEMT[EMT instruction]";
            break;
# endif // (! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE)

        case SIGFPE :
            result = "SIGFPE[floating point exception]";
            break;

        case SIGKILL :
            result = "SIGKILL[kill]";
            break;

        case SIGBUS :
            result = "SIGBUS[bus error]";
            break;

        case SIGSEGV :
            result = "SIGSEGV[segmentation violation]";
            break;

        case SIGSYS :
            result = "SIGSYS[bad argument to system call]";
            break;

        case SIGPIPE :
            result = "SIGPIPE[write on a pipe with no one to read it]";
            break;

        case SIGALRM :
            result = "SIGALRM[alarm clock]";
            break;

        case SIGTERM :
            result = "SIGTERM[software termination signal from kill]";
            break;

        case SIGURG :
            result = "SIGURG[urgent condition on IO channel]";
            break;

        case SIGSTOP :
            result = "SIGSTOP[sendable stop signal not from tty]";
            break;

        case SIGTSTP :
            result = "SIGTSTP[stop signal from tty]";
            break;

        case SIGCONT :
            result = "SIGCONT[continue a stopped process]";
            break;

        case SIGCHLD :
            result = "SIGCHLD[to parent on child stop or exit]";
            break;

        case SIGTTIN :
            result = "SIGTTIN[to readers pgrp upon background tty read]";
            break;

        case SIGTTOU :
            result = "SIGTTOU[like TTIN for output if (tp->t_local&LTOSTOP)]";
            break;

# if ((! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE))
        case SIGIO :
            result = "SIGIO[input/output possible signal]";
            break;
# endif // (! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE)

        case SIGXCPU :
            result = "SIGXCPU[exceeded CPU time limit]";
            break;

        case SIGXFSZ :
            result = "SIGXFSZ[exceeded file size limit]";
            break;

        case SIGVTALRM :
            result = "SIGVTALRM[virtual time alarm]";
            break;

        case SIGPROF :
            result = "SIGPROF[profiling time alarm]";
            break;

# if ((! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE))
        case SIGWINCH :
            result = "SIGWINCH[window size changes]";
            break;
# endif // (! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE)

# if ((! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE))
        case SIGINFO :
            result = "SIGINFO[information request]";
            break;
# endif // (! defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE)

        case SIGUSR1 :
            result = "SIGUSR1[user defined signal 1]";
            break;

        case SIGUSR2 :
            result = "SIGUSR2[user defined signal 2]";
            break;

        default :
            result = "unknown";
            break;

    }
#else // ! defined(MAC_OR_LINUX_)
    switch (theSignal)
    {
        case SIGINT :
            result = "SIGINT[interrupt]";
            break;

        case SIGABRT :
            result = "SIGABRT[abort()]";
            break;

        default :
            result = "unknown";
            break;

    }
#endif // ! defined(MAC_OR_LINUX_)
    return result;
} // nImO::NameOfSignal

void
nImO::OutputDescription(std::ostream      &outStream,
                        const char        *heading,
                        const std::string &description)
{
    size_t      descriptionLength = description.length();
    size_t      indentSize = strlen(heading);
    size_t      pieceStart = 0;
    std::string blanks(indentSize, ' ');
    std::string indent(heading);

    for (size_t ii = 0; ii < descriptionLength; ++ii)
    {
        if ('\n' == description[ii])
        {
            std::string piece(description.substr(pieceStart, ii - pieceStart));

            outStream << indent << piece.c_str() << endl;
            pieceStart = ii + 1;
            indent = blanks;
        }
    }
    std::string piece(description.substr(pieceStart, descriptionLength - pieceStart));

    outStream << indent << piece.c_str() << endl;
} // nImO::OutputDescription

bool
nImO::ProcessStandardUtilitiesOptions(const int              argc,
                                      char                   **argv,
                                      nImO::DescriptorVector &argumentDescriptions,
                                      const std::string      &utilityDescription,
                                      const int              year,
                                      const char             *copyrightHolder,
                                      nImO::OutputFlavour    &flavour,
                                      const bool             ignoreFlavours,
                                      nImO::StringVector     *arguments)
{
    ODL_ENTER(); //####
    ODL_L2("argc = ", argc, "year = ", year); //####
    ODL_P4("argv = ", argv, "argumentDescriptions = ", &argumentDescriptions, //####
           "flavour = ", &flavour, "arguments = ", arguments); //####
    ODL_S1s("utilityDescription = ", utilityDescription); //####
    ODL_S1("copyrightHolder = ", copyrightHolder); //####
    ODL_B1("ignoreFlavours = ", ignoreFlavours); //####
    enum class OptionIndex
    {
        UNKNOWN,
        HELP,
        INFO,
        JSON,
        TABS,
        VERSION
    }; // OptionIndex

    bool                keepGoing = true;
    Option_::Descriptor firstDescriptor(static_cast<unsigned>(OptionIndex::UNKNOWN), 0, "", "",
                                        Option_::Arg::None, nullptr);
    Option_::Descriptor helpDescriptor(static_cast<unsigned>(OptionIndex::HELP), 0, "h", "help",
                                        Option_::Arg::None,
                                        T_("  --help, -h    Print usage and exit"));
    Option_::Descriptor infoDescriptor(static_cast<unsigned>(OptionIndex::INFO), 0, "i", "info",
                                       Option_::Arg::None,
                                       T_("  --info, -i    Print type and description and exit"));
    Option_::Descriptor jsonDescriptor(static_cast<unsigned>(OptionIndex::JSON), 0, "j", "json",
                                       Option_::Arg::None,
                                       T_("  --json, -j    Generate output in JSON format"));
    Option_::Descriptor tabsDescriptor(static_cast<unsigned>(OptionIndex::TABS), 0, "t", "tabs",
                                       Option_::Arg::None,
                                       T_("  --tabs, -t    Generate output in tab-delimited "
                                          "format"));
    Option_::Descriptor versionDescriptor(static_cast<unsigned>(OptionIndex::VERSION), 0, "v",
                                          "vers", Option_::Arg::None,
                                          T_("  --vers, -v    Print version information and "
                                             "exit"));
    Option_::Descriptor lastDescriptor(0, 0, nullptr, nullptr, nullptr, nullptr);
    Option_::Descriptor usage[7];
    Option_::Descriptor *usageWalker = usage;
    int                 argcWork = argc;
    char                **argvWork = argv;
    std::string         usageString("USAGE: ");
    std::string         argList(ArgumentsToArgString(argumentDescriptions));

    flavour = OutputFlavour::Normal;
    usageString += *argv;
    usageString += " [options]";
    if (0 < argList.length())
    {
        StringVector descriptions;

        ArgumentsToDescriptionArray(argumentDescriptions, descriptions, 2);
        usageString += " ";
        usageString += argList + "\n\n";
        for (size_t ii = 0, mm = descriptions.size(); mm > ii; ++ii)
        {
            if (0 < ii)
            {
                usageString += "\n";
            }
            usageString += "  ";
            usageString += descriptions[ii];
        }
    }
    usageString += "\n\nOptions:";
#if defined(MAC_OR_LINUX_)
    firstDescriptor.help = strdup(usageString.c_str());
#else // ! defined(MAC_OR_LINUX_)
    firstDescriptor.help = _strdup(usageString.c_str());
#endif // ! defined(MAC_OR_LINUX_)
    memcpy(usageWalker++, &firstDescriptor, sizeof(firstDescriptor));
    memcpy(usageWalker++, &helpDescriptor, sizeof(helpDescriptor));
    memcpy(usageWalker++, &infoDescriptor, sizeof(infoDescriptor));
    if (! ignoreFlavours)
    {
        memcpy(usageWalker++, &jsonDescriptor, sizeof(jsonDescriptor));
    }
    if (! ignoreFlavours)
    {
        memcpy(usageWalker++, &tabsDescriptor, sizeof(tabsDescriptor));
    }
    memcpy(usageWalker++, &versionDescriptor, sizeof(versionDescriptor));
    memcpy(usageWalker++, &lastDescriptor, sizeof(lastDescriptor));
    argcWork -= (argc > 0);
    argvWork += (argc > 0); // skip program name argv[0] if present
    Option_::Stats                     stats(usage, argcWork, argvWork);
    std::unique_ptr<Option_::Option[]> options(new Option_::Option[stats.options_max]);
    std::unique_ptr<Option_::Option[]> buffer(new Option_::Option[stats.buffer_max]);
    Option_::Parser                    parse(usage, argcWork, argvWork, options.get(),
                                             buffer.get(), 1);
    std::string                        badArgs;

    if (parse.error())
    {
        keepGoing = false;
    }
    else if (options[static_cast<size_t>(OptionIndex::HELP)] ||
             options[static_cast<size_t>(OptionIndex::UNKNOWN)])
    {
        Option_::printUsage(cout, usage, HELP_LINE_LENGTH_);
        keepGoing = false;
    }
    else if (options[static_cast<size_t>(OptionIndex::VERSION)])
    {
        std::string nImOversionString(SanitizeString(nImO_VERSION_, true));

        cout << "Version " << nImOversionString.c_str() << ": Copyright (c) " << year << " by " <<
        copyrightHolder << "." << endl;
        keepGoing = false;
    }
    else if (options[static_cast<size_t>(OptionIndex::INFO)])
    {
        cout << "Utility\t" << utilityDescription.c_str() << endl;
        keepGoing = false;
    }
    else if (ProcessArguments(argumentDescriptions, parse, badArgs))
    {
        if (options[static_cast<size_t>(OptionIndex::JSON)])
        {
            flavour = OutputFlavour::JSON;
        }
        else if (options[static_cast<size_t>(OptionIndex::TABS)])
        {
            flavour = OutputFlavour::Tabs;
        }
        if (arguments)
        {
            arguments->clear();
            for (int ii = 0; ii < parse.nonOptionsCount(); ++ii)
            {
                arguments->emplace_back(parse.nonOption(ii));
            }
        }
    }
    else
    {
        cout << "One or more invalid or missing arguments (" << badArgs.c_str() << ")." << endl;
        keepGoing = false;
    }
    ODL_EXIT_B(keepGoing); //####
    return keepGoing;
} // nImO::ProcessStandardUtilitiesOptions

std::string
nImO::SanitizeString(const std::string &inString,
                     const bool        allowDoubleQuotes)
{
    ODL_ENTER(); //####
    ODL_S1s("channelRoot = ", inString); //####
    ODL_B1("allowDoubleQuotes = ", allowDoubleQuotes); //####
    std::string outString;

    try
    {
        for (size_t ii = 0, mm = inString.length(); mm > ii; )
        {
            char cc = inString[ii++];

            switch (cc)
            {
                case '\t' :
                    outString += kEscapeChar;
                    cc = 't';
                    break;

                case '\n' :
                    outString += kEscapeChar;
                    cc = 'n';
                    break;

                case '\\' :
                    outString += kEscapeChar;
                    break;

                case '"' :
                    if (! allowDoubleQuotes)
                    {
                        outString += kEscapeChar;
                    }
                    break;

                default :
                    break;

            }
            outString += cc;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_s(outString); //####
    return outString;
} // nImO::SanitizeString

#if 0
void
nImO::StartRunning(void)
{
    ODL_ENTER(); //####
    lKeepRunning = true;
    ODL_EXIT(); //####
} // nImO::StartRunning

void
nImO::StopRunning(void)
{
    ODL_ENTER(); //####
    lKeepRunning = false;
    ODL_EXIT(); //####
} // nImO::StopRunning

#if (! defined(MAC_OR_LINUX_))
# pragma warning(push)
# pragma warning(disable: 4100)
#endif // ! defined(MAC_OR_LINUX_)
void
nImO::SignalRunningStop(UNUSED_ const int signal)
{
    ODL_ENTER(); //####
    ODL_LL1("signal = ", signal); //####
    StopRunning();
    ODL_EXIT(); //####
} // nImO::SignalRunningStop
#if (! defined(MAC_OR_LINUX_))
# pragma warning(pop)
#endif // ! defined(MAC_OR_LINUX_)
#endif//0

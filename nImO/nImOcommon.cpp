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

#include <nImOcommon.h>

#include <initFile.h>
#include <initFileObject.h>
#include <nImObaseArgumentDescriptor.h>
#include <nImOcontext.h>
#include <nImOvalue.h>
#include <fstream>

//#include <odlEnable.h>
#include <odlInclude.h>

#if MAC_OR_LINUX_
# include <unistd.h>
#else // ! MAC_OR_LINUX_
# include <Windows.h>
# include <io.h>
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif // defined(__APPLE__)
#include <boost/endian/buffers.hpp>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

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

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

/*! @brief @c true once the random number generator is seeded. */
static bool lRandomSeeded = false;

/*! @brief The maximum integer that we wish to use for generated random values. */
static const int    kMaxRandom = 123456789;

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

const char  nImO::kBlobSeparator = '%';

const char  nImO::kEndArrayChar = ')';

const char  nImO::kEndMapChar = '}';

const char  nImO::kEndOfString = '\0';

const char  nImO::kEndSetChar = ']';

const char  nImO::kKeyValueSeparator = '>';

const char  nImO::kSingleQuote = '\'';

const char  nImO::kStartArrayChar = '(';

const char  nImO::kStartMapChar = '{';

const char  nImO::kStartSetChar = '[';

const uint8_t   nImO::kDoubleQuote = '"';

const uint8_t   nImO::kEscapeChar = '\\';

// Note that this MUST be a single-character string!!!
#if MAC_OR_LINUX_
const std::string   nImO::kDirectorySeparator{"/"};
#else // ! MAC_OR_LINUX_
const std::string   nImO::kDirectorySeparator{"\\"};
#endif // ! MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if MAC_OR_LINUX_
/*! @brief The signal handler to catch requests to stop the service.
 @param[in] signal The signal being handled. */
[[noreturn]]
static void
localCatcher
    (int    signal)
{
    NIMO_UNUSED_ARG_(signal);
    ODL_ENTER(); //####
    //ODL_I1("signal = ", signal); //####
#if 0
    if (lLogger)
    {
        std::string message{"Exiting due to signal "};

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
#endif // MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

double
nImO::B2D
    (const NumberAsBytes &  inString)
{
    boost::endian::big_float64_buf_t    holder;
    double                              result;

    ODL_ENTER(); //####
    ODL_P1("inString = ", &inString); //####
    memcpy(holder.data(), inString, sizeof(result));
    result = holder.value();
    ODL_EXIT_D(result); //####
    return result;
} // nImO::B2D

int64_t
nImO::B2I
    (const NumberAsBytes &  inString,
     const size_t           numBytes)
{
    bool                            isNegative = (0 != (0x080 & inString[0]));
    boost::endian::big_int64_buf_t  holder;
    int64_t                         result;

    ODL_ENTER(); //####
    ODL_P1("inString = ", &inString); //####
    ODL_I1("numBytes = ", numBytes); //####
    if (isNegative)
    {
        holder = -1;
    }
    else
    {
        holder = 0;
    }
    for (size_t ii = (sizeof(result) - numBytes); ii < sizeof(result); ++ii)
    {
        holder.data()[ii] = inString[ii + numBytes - sizeof(result)];
    }
    result = holder.value();
    ODL_EXIT_I(result); //####
    return result;
} // nImO::B2I

bool
nImO::CanReadFromStandardInput
    (void)
{
#if MAC_OR_LINUX_
    pid_t   fg = tcgetpgrp(STDIN_FILENO);
#else // ! MAC_OR_LINUX_
    HWND    wind = GetConsoleWindow();
#endif // ! MAC_OR_LINUX_
    bool    result = false;

    ODL_ENTER(); //####
#if MAC_OR_LINUX_
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
#else // ! MAC_OR_LINUX_
    result = (nullptr != wind);
#endif // ! MAC_OR_LINUX_
    ODL_EXIT_B(result); //####
    return result;
} // nImO::CanReadFromStandardInput

size_t
nImO::CompareBytes
    (CPtr(void)     first,
     CPtr(void)     second,
     const size_t   numBytes)
{
    size_t  result = 0;

    ODL_ENTER(); //####
    ODL_P2("first = ", first, "second = ", second); //####
    ODL_I1("numBytes = ", numBytes); //####
    if (memcmp(first, second, numBytes))
    {
        CPtr(uint8_t)   firstWalker{StaticCast(CPtr(uint8_t), first)};
        CPtr(uint8_t)   secondWalker{StaticCast(CPtr(uint8_t), second)};

        for (size_t ii = 0; numBytes > ii; ++ii)
        {
            uint8_t firstByte{*firstWalker++};
            uint8_t secondByte{*secondWalker++};

            if (firstByte != secondByte)
            {
                ODL_I1("mismatch at index: ", ii); //####
                result = ii + 1;
                break;

            }
        }
    }
    ODL_EXIT_I(result); //####
    return result;
} // nImO::CompareBytes

void
nImO::ConsumeSomeTime
    (Ptr(Context)   context,
     const double   factor)
{
    ODL_ENTER(); //####
    ODL_D1("amount = ", amount); //####
    if (nullptr != context)
    {
        boost::asio::deadline_timer timer(*context->getService());

        timer.expires_from_now(boost::posix_time::milliseconds(StaticCast(int, 1000.0 / factor)));
        timer.wait();
    }
    thread::yield();
    ODL_EXIT(); //####
} // nImO::ConsumeSomeTime

std::string
nImO::ConvertDoubleToString
    (const double   value)
{
    // Note that boost::lexical_cast<std::string>(double) generates strings with trailing digits.
    // That is, 1E-22 winds up as 9.9999999999999E-21, which is platform-sensitive.
    std::ostringstream  holder;

    ODL_ENTER(); //####
    ODL_D1("value = ", value); //####
    holder << std::defaultfloat << value;
    std::string result{holder.str()};

    ODL_EXIT_s(result); //####
    return result;
} // nImO::ConvertDoubleToString

bool
nImO::ConvertToDouble
    (CPtr(char) startPtr,
     double &   result)
{
    bool        okSoFar;
    Ptr(char)   endPtr;
    double      value = strtod(startPtr, &endPtr);

    ODL_ENTER(); //####
    ODL_S1("startPtr = ", startPtr); //####
    ODL_P1("result = ", &result); //####
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
nImO::ConvertToDouble
    (const std::string &    aString,
     double &               result)
{
    bool    okSoFar = ConvertToDouble(aString.c_str(), result);

    ODL_ENTER(); //####
    ODL_S1s("aString = ", aString); //####
    ODL_P1("result = ", &result); //####
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ConvertToDouble

bool
nImO::ConvertToInt64
    (CPtr(char) startPtr,
     int64_t &  result)
{
    bool        okSoFar;
    Ptr(char)   endPtr;
    int64_t     value = strtoll(startPtr, &endPtr, 10);

    ODL_ENTER(); //####
    ODL_S1("startPtr = ", startPtr); //####
    ODL_P1("result = ", &result); //####
    if ((startPtr != endPtr) && (! *endPtr))
    {
        result = value;
        ODL_I1("result <- ", result); //####
        okSoFar = true;
    }
    else
    {
        okSoFar = false;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ConvertToInt64

bool
nImO::ConvertToInt64
    (const std::string &    aString,
     int64_t &              result)
{
    bool    okSoFar = ConvertToInt64(aString.c_str(), result);

    ODL_ENTER(); //####
    ODL_S1s("aString = ", aString); //####
    ODL_P1("result = ", &result); //####
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ConvertToInt64

void
nImO::D2B
    (const double       inValue,
     NumberAsBytes &    outString)
{
    boost::endian::big_float64_buf_t    holder{inValue};

    ODL_ENTER(); //####
    ODL_D1("inValue = ", inValue); //####
    ODL_P1("outString = ", &outString); //####
    memcpy(outString, holder.data(), sizeof(inValue));
    ODL_EXIT(); //####
} // nImO::D2B

void
nImO::DumpMemoryToStandardError
    (CPtr(void)     address,
     const size_t   numBytes)
{
    if ((nullptr != address) && (0 < numBytes))
    {
        const size_t    bytesPerRow = 16;
        size_t          offset = 0;
        size_t          bytesInNextRow = std::min(numBytes, bytesPerRow);

        std::cerr << "**** address: " << std::hex << ReinterpretCast(intptr_t, address) << ", size: " << std::dec <<
                    numBytes << " ****" << std::endl;
        std::cerr << "____ | 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F |" << std::endl;
        for ( ; offset < numBytes; offset += bytesPerRow)
        {
            std::cerr << std::hex << std::setw(4) << std::setfill('0') << offset << " : ";
            for (size_t ii = 0; ii < bytesInNextRow; ++ii)
            {
                CPtr(uint8_t)   ptrToByte = ReinterpretCast(CPtr(uint8_t), address) + offset + ii;
                uint            aByte = *ptrToByte;

                std::cerr << std::setw(2) << std::setfill('0') << aByte << " ";
                if (3 == (ii % 4))
                {
                    std::cerr << "| ";
                }
            }
            if (bytesPerRow > bytesInNextRow)
            {
                for (size_t ii = bytesInNextRow; ii < bytesPerRow; ++ii)
                {
                    std::cerr << "   ";
                    if (3 == (ii % 4))
                    {
                        std::cerr << "| ";
                    }
                }
            }
            for (size_t ii = 0; ii < bytesInNextRow; ++ii)
            {
                CPtr(char)  ptrToChar = ReinterpretCast(CPtr(char), address) + offset + ii;
                char        aChar = *ptrToChar;

                if (std::isprint(aChar))
                {
                    std::cerr << aChar;
                }
                else
                {
                    std::cerr << ".";
                }
                if (3 == (ii % 4))
                {
                    std::cerr << " ";
                }
            }
            std::cerr << std::endl;
            if ((offset + bytesPerRow) < numBytes)
            {
                bytesInNextRow = std::min(numBytes - (offset + bytesPerRow), bytesPerRow);
            }
        }
        std::cerr << std::dec;
    }
} // nImO::DumpMemoryToStandardError

std::string
nImO::GetRandomChannelName
    (CPtr(char) channelRoot)
{
    std::string result;

    ODL_ENTER(); //####
    ODL_S1("channelRoot = ", channelRoot); //####
    try
    {
        bool                hasLeadingSlash = false;
        CPtr(char)          stringToUse;
        int                 randNumb = (rand() % kMaxRandom);
        std::stringstream   buff;

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
nImO::GetRandomChannelName
    (const std::string &    channelRoot)
{
    return GetRandomChannelName(channelRoot.c_str());
} // nImO::GetRandomChannelName

std::string
nImO::GetRandomHexString
    (void)
{
    int                 randNumb;
    std::string         result;
    std::stringstream   buff;

    ODL_ENTER(); //####
    if (! lRandomSeeded)
    {
#if defined(__APPLE__)
        sranddev();
#else // not defined(__APPLE__)
        srand(StaticCast(unsigned int, time(nullptr)));
#endif // not defined(__APPLE__)
        lRandomSeeded = true;
    }
    randNumb = (rand() % 10000);
    buff << std::hex << randNumb;
    result = buff.str();
    ODL_EXIT_s(result); //####
    return result;
} // nImO::GetRandomHexString

std::string
nImO::GetShortComputerName
    (void)
{
    std::string result{asio::ip::host_name()};
    size_t      dotPos = result.find('.');

    ODL_ENTER(); //####
    if (std::string::npos != dotPos)
    {
        result.resize(dotPos);
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::GetShortComputerName

size_t
nImO::I2B
    (const int64_t      inValue,
     NumberAsBytes &    outString)
{
    boost::endian::big_int64_buf_t  holder{inValue};
    size_t                          length = 0;

    ODL_ENTER(); //####
    ODL_X1("inValue = ", inValue); //####
    ODL_P1("outString = ", &outString); //####
    memcpy(outString, holder.data(), sizeof(inValue));
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
            if (0x0FF != outString[ii])
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
    ODL_EXIT_I(length); //####
    return length;
} // nImO::I2B

CPtr(char)
nImO::NameOfSignal
    (const int  theSignal)
{
    CPtr(char)  result;

#if MAC_OR_LINUX_
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
            result = "SIGTTOU[like TTIN for output if (tp->t_local &LTOSTOP)]";
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
#else // ! MAC_OR_LINUX_
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
#endif // ! MAC_OR_LINUX_
    return result;
} // nImO::NameOfSignal

void
nImO::OutputDescription
    (std::ostream &         outStream,
     CPtr(char)             heading,
     const std::string &    description)
{
    size_t      descriptionLength = description.length();
    size_t      indentSize = strlen(heading);
    size_t      pieceStart = 0;
    std::string blanks(indentSize, ' ');
    std::string indent{heading};

    for (size_t ii = 0; ii < descriptionLength; ++ii)
    {
        if ('\n' == description[ii])
        {
            std::string piece{description.substr(pieceStart, ii - pieceStart)};

            outStream << indent << piece.c_str() << std::endl;
            pieceStart = ii + 1;
            indent = blanks;
        }
    }
    std::string piece{description.substr(pieceStart, descriptionLength - pieceStart)};

    outStream << indent << piece.c_str() << std::endl;
} // nImO::OutputDescription

nImO::Transport
nImO::ResolveTransport
    (const Transport    firstTransport,
     const Transport    secondTransport,
     const Transport    defaultTransport)
{
    Transport   result;

    switch (firstTransport)
    {
        case Transport::TCP :
            result = firstTransport;
            break;

        case Transport::UDP :
            if (Transport::TCP == secondTransport)
            {
                result = secondTransport;
            }
            else
            {
                result = firstTransport;
            }
            break;

        default:
            if (Transport::Unknown == secondTransport)
            {
                if (Transport::Unknown == defaultTransport)
                {
                    result = Transport::TCP;
                }
                else
                {
                    result = defaultTransport;
                }
            }
            else
            {
                result = secondTransport;
            }
            break;

    }
    return result;
} /* ResolveTransport */

nImO::Transport
nImO::ResolveTransport
    (const Transport    firstTransport,
     const Transport    defaultTransport)
{
    Transport   result;

    switch (firstTransport)
    {
        case Transport::TCP :
        case Transport::UDP :
            result = firstTransport;
            break;

        default:
            if (Transport::Unknown == defaultTransport)
            {
                result = Transport::TCP;
            }
            else
            {
                result = defaultTransport;
            }
            break;

    }
    return result;
} /* ResolveTransport */

std::string
nImO::SanitizeString
    (const std::string &    inString,
     const bool             allowDoubleQuotes)
{
    std::string outString;

    ODL_ENTER(); //####
    ODL_S1s("channelRoot = ", inString); //####
    ODL_B1("allowDoubleQuotes = ", allowDoubleQuotes); //####
    try
    {
        for (size_t ii = 0, mm = inString.length(); mm > ii; )
        {
            char    cc = inString[ii++];

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

void
nImO::SetSignalHandlers
    (SignalHandler  theHandler)
{
#if MAC_OR_LINUX_
    sigset_t            blocking;
    struct sigaction    act;
#endif // MAC_OR_LINUX_

    ODL_ENTER(); //####
#if MAC_OR_LINUX_
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
#else // ! MAC_OR_LINUX_
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
#endif // ! MAC_OR_LINUX_
    ODL_EXIT(); //####
} // nImO::SetSignalHandlers

void
nImO::SetUpCatcher
    (void)
{
#if MAC_OR_LINUX_
    sigset_t            unblocking;
    struct sigaction    act;
#endif // MAC_OR_LINUX_

    ODL_ENTER(); //####
#if MAC_OR_LINUX_
    sigemptyset(&unblocking);
    sigaddset(&unblocking, STANDARD_SIGNAL_TO_USE_);
    pthread_sigmask(SIG_UNBLOCK, &unblocking, nullptr);
    act.sa_handler = localCatcher;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(STANDARD_SIGNAL_TO_USE_, &act, nullptr);
#else // ! MAC_OR_LINUX_
#endif // ! MAC_OR_LINUX_
    ODL_EXIT(); //####
} // nImO::SetUpCatcher

void
nImO::ShutDownCatcher
    (void)
{
#if MAC_OR_LINUX_
    sigset_t            blocking;
    struct sigaction    act;
#endif // MAC_OR_LINUX_

    ODL_ENTER(); //####
#if MAC_OR_LINUX_
    sigemptyset(&blocking);
    sigaddset(&blocking, STANDARD_SIGNAL_TO_USE_);
    pthread_sigmask(SIG_BLOCK, &blocking, nullptr);
    act.sa_handler = SIG_DFL;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(STANDARD_SIGNAL_TO_USE_, &act, nullptr);
#else // ! MAC_OR_LINUX_
#endif // ! MAC_OR_LINUX_
    ODL_EXIT(); //####
} // nImO::ShutDownCatcher

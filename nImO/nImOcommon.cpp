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

#include <ArgumentDescriptors/nImObaseArgumentDescriptor.h>
#include <BasicTypes/nImOvalue.h>
#include <Contexts/nImOcontext.h>

#include <boost/version.hpp>
#include <random>
#include <regex>
#include <string>

//#include <odlEnable.h>
#include <odlInclude.h>

#if MAC_OR_LINUX_
# include <unistd.h>
#else // not MAC_OR_LINUX_
# include <Windows.h>
# include <io.h>
#endif // not MAC_OR_LINUX_

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif // defined(__APPLE__)
#include <boost/endian/buffers.hpp>
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if MAC_OR_LINUX_
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif // MAC_OR_LINUX_
#include <mdns.hpp>
#if MAC_OR_LINUX_
# pragma GCC diagnostic pop
#endif // MAC_OR_LINUX_

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

/*! @brief Seed for random number generator. */
static std::random_device   lRd;

/*! @brief Mersenne Twister random number engine. */
static std::mt19937 lMt{lRd()};

/*! @brief Flag to prevent more than one initialization. */
static bool lInitialized{false};

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

// Note that this MUST be a single-character string!!!
#if MAC_OR_LINUX_
const std::string   nImO::kDirectorySeparator{"/"s};
#else // not MAC_OR_LINUX_
const std::string   nImO::kDirectorySeparator{"\\"s};
#endif // not MAC_OR_LINUX_

const std::string   nImO::kStatusSeparator{"\t"s};

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

double
nImO::B2D
    (const NumberAsBytes &  inString)
{
    ODL_ENTER(); //####
    ODL_P1("inString = ", &inString); //####
    boost::endian::big_float64_buf_t    holder;
    double                              result;

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
    ODL_ENTER(); //####
    ODL_P1("inString = ", &inString); //####
    ODL_I1("numBytes = ", numBytes); //####
    bool                            isNegative{0 != (0x080 & inString[0])};
    boost::endian::big_int64_buf_t  holder;
    int64_t                         result;

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
    ODL_ENTER(); //####
#if MAC_OR_LINUX_
    pid_t   fg{tcgetpgrp(STDIN_FILENO)};
#else // not MAC_OR_LINUX_
    HWND    wind{GetConsoleWindow()};
#endif // not MAC_OR_LINUX_
    bool    result{false};

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
#else // not MAC_OR_LINUX_
    result = (nullptr != wind);
#endif // not MAC_OR_LINUX_
    ODL_EXIT_B(result); //####
    return result;
} // nImO::CanReadFromStandardInput

size_t
nImO::CompareBytes
    (CPtr(void)     first,
     CPtr(void)     second,
     const size_t   numBytes)
{
    ODL_ENTER(); //####
    ODL_P2("first = ", first, "second = ", second); //####
    ODL_I1("numBytes = ", numBytes); //####
    size_t  result{0};

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

std::string
nImO::ConstructNodeName
    (const std::string  nameFromOptions,
     const std::string  suffixIfNotFromOptions,
     const std::string  tag)
{
    ODL_ENTER(); //####
    ODL_S3s("nameFromOptions = ", nameFromOptions, "suffixIfNotFromOptions = ", suffixIfNotFromOptions, "tag =", tag); //####
    std::string nodeName;

    if (nameFromOptions.empty())
    {
        nodeName = nImO::GetShortComputerName() + "-"s + suffixIfNotFromOptions;
    }
    else
    {
        nodeName = nameFromOptions;
    }
    if (! tag.empty())
    {
        nodeName += "-"s + tag;
    }
    ODL_EXIT_s(nodeName); //####
    return nodeName;
} // nImO::ConstructNodeName

void
nImO::ConsumeSomeTime
    (Ptr(Context)   context,
     const double   factor)
{
    ODL_ENTER(); //####
    ODL_P1("context = ", context); //####
    ODL_D1("factor = ", factor); //####
    if (nullptr != context)
    {
        BAD_t   timer(*context->getService());

        timer.expires_from_now(boost::posix_time::milliseconds(StaticCast(int, 1000.0 / factor)));
        timer.wait();
    }
    boost::this_thread::yield();
    ODL_EXIT(); //####
} // nImO::ConsumeSomeTime

std::string
nImO::ConvertDoubleToString
    (const double   value)
{
    ODL_ENTER(); //####
    ODL_D1("value = ", value); //####
    // Note that boost::lexical_cast<std::string>(double) generates strings with trailing digits.
    // That is, 1E-22 winds up as 9.9999999999999E-21, which is platform-sensitive.
    std::ostringstream  holder;

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
    ODL_ENTER(); //####
    ODL_S1("startPtr = ", startPtr); //####
    ODL_P1("result = ", &result); //####
    bool        okSoFar;
    Ptr(char)   endPtr;
    double      value{strtod(startPtr, &endPtr)};

    if ((startPtr != endPtr) && (kEndOfString == *endPtr))
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
    ODL_ENTER(); //####
    ODL_S1s("aString = ", aString); //####
    ODL_P1("result = ", &result); //####
    bool    okSoFar{ConvertToDouble(aString.c_str(), result)};

    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ConvertToDouble

bool
nImO::ConvertToInt64
    (CPtr(char) startPtr,
     int64_t &  result)
{
    ODL_ENTER(); //####
    ODL_S1("startPtr = ", startPtr); //####
    ODL_P1("result = ", &result); //####
    bool        okSoFar;
    Ptr(char)   endPtr;
    int64_t     value{strtoll(startPtr, &endPtr, 10)};

    if ((startPtr != endPtr) && (kEndOfString == *endPtr))
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
    ODL_ENTER(); //####
    ODL_S1s("aString = ", aString); //####
    ODL_P1("result = ", &result); //####
    bool    okSoFar{ConvertToInt64(aString.c_str(), result)};

    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::ConvertToInt64

std::string
nImO::ConvertToLowerCase
    (const std::string &    aString)
{
    ODL_ENTER(); //####
    ODL_S1s("aString = ", aString); //####
    std::string result;

    for (auto walker : aString)
    {
        result.push_back(tolower(walker));
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::ConvertToLowerCase

void
nImO::D2B
    (const double       inValue,
     NumberAsBytes &    outString)
{
    ODL_ENTER(); //####
    ODL_D1("inValue = ", inValue); //####
    ODL_P1("outString = ", &outString); //####
    boost::endian::big_float64_buf_t    holder{inValue};

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
        const size_t    bytesPerRow{16};
        size_t          offset{0};
        size_t          bytesInNextRow{std::min(numBytes, bytesPerRow)};

        std::cerr << "**** address: " << std::hex << ReinterpretCast(intptr_t, address) << ", size: " << std::dec <<
                    numBytes << " ****\n";
        std::cerr << "____ | 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F |\n";
        for ( ; offset < numBytes; offset += bytesPerRow)
        {
            std::cerr << std::hex << std::setw(4) << std::setfill('0') << offset << " : ";
            for (size_t ii = 0; ii < bytesInNextRow; ++ii)
            {
                CPtr(uint8_t)   ptrToByte{ReinterpretCast(CPtr(uint8_t), address) + offset + ii};
                uint            aByte{*ptrToByte};

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
                CPtr(char)  ptrToChar{ReinterpretCast(CPtr(char), address) + offset + ii};
                char        aChar{*ptrToChar};

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
            std::cerr << "\n";
            if ((offset + bytesPerRow) < numBytes)
            {
                bytesInNextRow = std::min(numBytes - (offset + bytesPerRow), bytesPerRow);
            }
        }
        std::cerr << std::dec;
    }
} // nImO::DumpMemoryToStandardError

std::string
nImO::GetRandomHexString
    (void)
{
    ODL_ENTER(); //####
    std::string         result;
    std::stringstream   buff;

    buff << std::hex << (nImO::RandomUnsigned() % 10000);
    result = buff.str();
    ODL_EXIT_s(result); //####
    return result;
} // nImO::GetRandomHexString

std::string
nImO::GetShortComputerName
    (void)
{
    ODL_ENTER(); //####
    std::string result{BAIP::host_name()};
    size_t      dotPos{result.find('.')};

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
    ODL_ENTER(); //####
    ODL_X1("inValue = ", inValue); //####
    ODL_P1("outString = ", &outString); //####
    boost::endian::big_int64_buf_t  holder{inValue};
    size_t                          length{0};

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
            uint8_t aByte{outString[sizeof(inValue) - length]};

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
            uint8_t aByte{outString[sizeof(inValue) - length]};

            if (0x00 == (0x080 & aByte))
            {
                ++length;
            }
        }
    }
    ODL_EXIT_I(length); //####
    return length;
} // nImO::I2B

void
nImO::Initialize
    (void)
{
    ODL_ENTER(); //####
    if (! lInitialized)
    {
        Value::initialize();
        lInitialized = true;
    }
    ODL_EXIT(); //####
} // nImO::Initialize

std::string
nImO::MakeStringFromComandLine
    (const int      numArgs,
     Ptr(Ptr(char)) args)
{
    ODL_ENTER(); //####
    ODL_I1("numArgs = ", numArgs); //####
    ODL_P1("args = ", args); //####
    std::string result;

    if (0 < numArgs)
    {
        result = args[0];
        for (int ii = 1; ii < numArgs; ++ii)
        {
            result += "\t"s;
            result += args[ii];
        }
    }
    ODL_EXIT_s(result); //####
    return result;
} // nImO::MakeStringFromCommandLine

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
#else // not MAC_OR_LINUX_
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
#endif // not MAC_OR_LINUX_
    return result;
} // nImO::NameOfSignal

void
nImO::OutputDescription
    (std::ostream &         outStream,
     CPtr(char)             heading,
     const std::string &    description)
{
    size_t      descriptionLength{description.length()};
    size_t      indentSize{strlen(heading)};
    size_t      pieceStart{0};
    std::string blanks(indentSize, ' ');
    std::string indent{heading};

    for (size_t ii = 0; ii < descriptionLength; ++ii)
    {
        if (kEndOfLine == description[ii])
        {
            auto    piece{description.substr(pieceStart, ii - pieceStart)};

            outStream << indent << piece.c_str() << "\n";
            pieceStart = ii + 1;
            indent = blanks;
        }
    }
    auto    piece{description.substr(pieceStart, descriptionLength - pieceStart)};

    outStream << indent << piece.c_str() << "\n";
} // nImO::OutputDescription

uint32_t
nImO::RandomUnsigned
    (void)
{
    std::uniform_int_distribution<> dist(0, RAND_MAX);

    return dist(lMt);
} // nImO::RandomUnsigned

void
nImO::ReportVersions
    (void)
{
#if defined(nImO_ChattyStart)
    std::string source{BOOST_LIB_VERSION};
    std::regex  exp{"_"};

    std::cout << "nImO Version: " << nImO::SanitizeString(nImO_VERSION_, true) << ", ODL Version: " << nImO::SanitizeString(ODL_VERSION_, true) <<
                ", mdns_plusplus Version: " << nImO::SanitizeString(mdns_plusplus_VERSION_, true) << ", Boost Version: " <<
                std::regex_replace(source, exp, ".") << "\n";
#endif /* defined(nImO_ChattyStart) */
} // nImO::ReportVersions

nImO::TransportType
nImO::ResolveTransport
    (const TransportType    firstTransport,
     const TransportType    secondTransport,
     const TransportType    defaultTransport)
{
    TransportType   result = (firstTransport & secondTransport);

    if (TransportType::kUnknown == result)
    {
        result = defaultTransport;
    }
    return result;
} /* ResolveTransport */

std::string
nImO::SanitizeString
    (const std::string &    inString,
     const bool             allowDoubleQuotes)
{
    ODL_ENTER(); //####
    ODL_S1s("inString = ", inString); //####
    ODL_B1("allowDoubleQuotes = ", allowDoubleQuotes); //####
    std::string outString;

    try
    {
        for (size_t ii = 0, mm = inString.length(); mm > ii; )
        {
            char    cc{inString[ii++]};

            switch (cc)
            {
                case '\t' :
                    outString += kEscapeChar;
                    cc = 't';
                    break;

                case kEndOfLine :
                    outString += kEscapeChar;
                    cc = 'n';
                    break;

                case kEscapeChar :
                    outString += kEscapeChar;
                    break;

                case kDoubleQuote :
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
    ODL_ENTER(); //####
#if MAC_OR_LINUX_
    sigset_t            blocking;
    struct sigaction    act;
#endif // MAC_OR_LINUX_

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
#else // not MAC_OR_LINUX_
# if (defined(SIGABRT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_))
    signal(SIGABRT, theHandler);
# endif // defined(SIGABRT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGHUP) && (SIGHUP != STANDARD_SIGNAL_TO_USE_))
    signal(SIGHUP, theHandler);
# endif // defined(SIGHUP) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGINT) && (SIGINT != STANDARD_SIGNAL_TO_USE_))
    signal(SIGINT, theHandler);
# endif // defined(SIGINT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGQUIT) && (SIGQUIT != STANDARD_SIGNAL_TO_USE_))
    signal(SIGQUIT, theHandler);
# endif // defined(SIGQUIT) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGUSR1) && (SIGUSR1 != STANDARD_SIGNAL_TO_USE_))
    signal(SIGUSR1, theHandler);
# endif // defined(SIGUSR1) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
# if (defined(SIGUSR2) && (SIGUSR2 != STANDARD_SIGNAL_TO_USE_))
    signal(SIGUSR2, theHandler);
# endif // defined(SIGUSR2) && (SIGABRT != STANDARD_SIGNAL_TO_USE_)
#if 0
    signal(SIGTERM, theHandler);
#endif//0
#endif // not MAC_OR_LINUX_
    ODL_EXIT(); //####
} // nImO::SetSignalHandlers

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Launcher/CommandHandlers/nImOgetRunParamsForAppCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO get run params for app command handler.
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
//  Created:    2024-01-16
//
//--------------------------------------------------------------------------------------------------

#include <Launcher/CommandHandlers/nImOgetRunParamsForAppCommandHandler.h>

//#include <BasicTypes/nImOaddress.h>
//#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <nImOlauncherCommands.h>

#pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-parameter"
# include <boost/process.hpp>
#pragma clang diagnostic pop

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO get run params for app command handler. */
#if defined(__APPLE__)
# pragma clang diagnostic pop
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Namespace references
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Private structures, constants and variables
#endif // defined(__APPLE__)

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

nImO::GetRunParamsForAppCommandHandler::GetRunParamsForAppCommandHandler
    (SpLauncherContext  owner) :
        inherited{owner}
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::GetRunParamsForAppCommandHandler::GetRunParamsForAppCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::GetRunParamsForAppCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments)
    const
{
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    bool    okSoFar{false};
    auto    appList{*_ownerForLauncher->getAppList()->asMap()};

    _ownerForLauncher->report("get run params for app request received"s);
    if (0 < appList.size())
    {
        if (1 < arguments.size())
        {
            auto    appNameEntry{appList.find(arguments[1])};

            if (appList.end() != appNameEntry)
            {
                auto    appNameString{arguments[1]->asString()};

NIMO_UNUSED_VAR_(socket);
std::cerr << "run params requested for " << *appNameString << std::endl;//!!
            }
            else
            {
                ODL_LOG("! (appList.end() != appNameEntry)"); //####
            }
        }
        else
        {
            ODL_LOG("! (1 < arguments.size())"); //####
        }

    }
    else
    {
        ODL_LOG("! (0 < appList.size())"); //####
    }
#if 0
    if (3 < arguments.size())
    {
        auto    pathString{arguments[1]->asString()};
        auto    dataTypeString{arguments[2]->asString()};
        auto    modeValue{arguments[3]->asInteger()};

        if ((nullptr != pathString) && (nullptr != dataTypeString) && (nullptr != modeValue))
        {
            auto    theChannel{_ownerForLauncher->getInputChannel(pathString->getValue())};

            if (nullptr == theChannel)
            {
                ODL_LOG("(nullptr == theChannel)"); //####
            }
            else
            {
                if (theChannel->setUp(StaticCast(TransportType, modeValue->getIntegerValue())))
                {
                    auto    theConnection{theChannel->getConnection()};
                    auto    infoArray{std::make_shared<Array>()};

                    infoArray->addValue(std::make_shared<Address>(theConnection._address));
                    infoArray->addValue(std::make_shared<Integer>(theConnection._port));
                    okSoFar = sendComplexResponse(socket, kGetRunParamsForAppResponse, "set up receiver"s, infoArray);
                }
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != pathString) && (nullptr != dataTypeString) && (nullptr != modeValue))"); //####
        }
    }
    else
    {
        ODL_LOG("! (3 < arguments.size())"); //####
    }
#endif//0
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetRunParamsForAppCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

#if 0
Here's a simple example of how to start a program with Boost.Process:

#include <boost/process.hpp>

#include <string>
#include <iostream>

using namespace boost::process;

int main()
{
    ipstream pipe_stream;
    child c("gcc --version", std_out > pipe_stream);

    std::string line;

    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        std::cerr << line << std::endl;

    c.wait();
}
#endif//0

#if 0
bool
ManagerApplication::getArgumentsForApplication(ApplicationInfo & theInfo)
{
    ODL_OBJENTER(); //####
    ODL_P1("theInfo = ", &theInfo); //####
    bool         okSoFar = false;
    ChildProcess runApplication;
    StringArray  nameAndArgs(theInfo._applicationPath);

    nameAndArgs.add("--args");
    if (runApplication.start(nameAndArgs))
    {
        const String childOutput(runApplication.readAllProcessOutput());

        LazyLaunchProcess(runApplication, kThreadKillTime);
        ODL_S1s("childOutput = ", childOutput.toStdString()); //####
        if (0 < childOutput.length())
        {
            StringArray aRecord(StringArray::fromTokens(childOutput, ARGUMENT_SEPARATOR_, ""));

            // The input lines should be composed of argument descriptions separated by the
            // ARGUMENT_SEPARATOR_ string.
            for (int ii = 0, mm = aRecord.size(); mm > ii; ++ii)
            {
                String                              trimmedRecord(aRecord[ii].trim());
                YarpString                          argString(trimmedRecord.toStdString());
                Utilities::BaseArgumentDescriptor * argDesc =
                                                    Utilities::ConvertStringToArgument(argString);

                if (argDesc)
                {
                    theInfo._argDescriptions.push_back(argDesc);
                }
            }
            okSoFar = true;
        }
    }
    else
    {
        ODL_LOG("! (runApplication.start(nameAndArgs))"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // ManagerApplication::getArgumentsForApplication
bool
ManagerApplication::getParametersForApplication(const String &    execName,
                                                ApplicationInfo & theInfo)
{
    ODL_OBJENTER(); //####
    ODL_S1s("execName = ", execName.toStdString()); //####
    ODL_P1("theInfo = ", &theInfo); //####
    bool   okSoFar = false;
    String execPath(findPathToExecutable(execName));

    if (0 < execPath.length())
    {
        ChildProcess runApplication;
        StringArray  nameAndArgs(execPath);

        nameAndArgs.add("--info");
        if (runApplication.start(nameAndArgs))
        {
            const String childOutput(runApplication.readAllProcessOutput());

            LazyLaunchProcess(runApplication, kThreadKillTime);
            ODL_S1s("childOutput = ", childOutput.toStdString()); //####
            if (0 < childOutput.length())
            {
                StringArray aRecord(StringArray::fromTokens(childOutput, "\t", ""));

                // The input lines should be composed of three tab-separated items:
                // 0) Type ('Service' or 'Adapter')
                // 1) Allowed options
                // 2) Matching criteria
                // 3) Description
                if (4 <= aRecord.size())
                {
                    String execKind(aRecord[0]);

                    if (execKind == "Adapter")
                    {
                        theInfo._kind = kApplicationAdapter;
                        okSoFar = (4 <= aRecord.size());
                    }
                    else if (execKind == "Service")
                    {
                        theInfo._kind = kApplicationService;
                        okSoFar = true;
                    }
                    if (okSoFar)
                    {
                        theInfo._applicationPath = nameAndArgs[0];
                        theInfo._options = aRecord[1];
                        theInfo._criteria = aRecord[2];
                        theInfo._description = aRecord[3].trim();
                        theInfo._shortName = execName;
                    }
                }
            }
        }
        else
        {
            ODL_LOG("! (runApplication.start(nameAndArgs))"); //####
        }
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // ManagerApplication::getParametersForApplication

#endif//0

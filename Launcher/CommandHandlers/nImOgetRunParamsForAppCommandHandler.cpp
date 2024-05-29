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

#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <nImOlauncherCommands.h>
#include <nImOmainSupport.h>

#pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
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

namespace BP = boost::process;

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
     const Array &  arguments,
     std::string &  reason)
    const
{
    ODL_OBJENTER(); //####
    ODL_P3("socket = ", &socket, "arguments = ", &arguments, "reason = ", &reason); //####
    bool    okSoFar{false};
    auto    appList{*_ownerForLauncher->getAppList()->asMap()};

    _ownerForLauncher->report("get run params for app request received."s);
    if (0 < appList.size())
    {
        if (1 < arguments.size())
        {
            auto    appListIterator{appList.find(arguments[1])};

            if (appList.end() == appListIterator)
            {
                ODL_LOG("(appList.end() == appListIterator)"); //####
                reason = "Application name is unknown"s;
            }
            else
            {
                auto    appInfoMap{appListIterator->second->asMap()};

                if (nullptr == appInfoMap)
                {
                    ODL_LOG("(nullptr == appInfoMap)"); //####
                    reason = "Internal structure invalid - not a map"s;
                }
                else
                {
                    auto    appPathIterator{appInfoMap->find(std::make_shared<nImO::String>(nImO::kPathKey))};

                    if (appInfoMap->end() == appPathIterator)
                    {
                        ODL_LOG("(appInfoMap->end() == appPathIterator)"); //####
                        reason = "Internal structure invalid - key missing"s;
                    }
                    else
                    {
                        auto            appPath{appPathIterator->second->asString()->getValue()};
                        BP::ipstream    pipeStream{};
                        BP::child       cc{StdStringVector{appPath, MakeOption("a"s)}, BP::std_out > pipeStream};
                        std::string     line{};
                        auto            params{std::make_shared<Array>()};

                        for ( ; getline(pipeStream, line); )
                        {
                            params->addValue(std::make_shared<String>(line));
                        }
                        okSoFar = sendComplexResponse(socket, kGetRunParamsForAppResponse, "get run params for app"s, params, reason);
                        ODL_B1("okSoFar <- ", okSoFar); //####
                        cc.wait();
                    }
                }
            }
        }
        else
        {
            ODL_LOG("! (1 < arguments.size())"); //####
            reason = "Missing argument(s)"s;
        }
    }
    else
    {
        ODL_LOG("! (0 < appList.size())"); //####
        reason = "Empty applications list"s;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetRunParamsForAppCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

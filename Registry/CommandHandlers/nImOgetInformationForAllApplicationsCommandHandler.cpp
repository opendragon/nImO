//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/Registry/CommandHandlers/nImOgetInformationForAllApplicationsCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO get list of apps command handler.
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

#include <Registry/CommandHandlers/nImOgetInformationForAllApplicationsCommandHandler.h>

#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>
#include <Containers/nImOarray.h>
#include <Containers/nImOmap.h>
#include <nImOregistryCommands.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO get list of apps command handler. */
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

nImO::GetInformationForAllApplicationsCommandHandler::GetInformationForAllApplicationsCommandHandler
    (SpServiceContext   owner,
     SpRegistry         theRegistry) :
        inherited{owner, theRegistry}
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "theRegistry = ", theRegistry.get()); //####
    ODL_EXIT_P(this); //####
} // nImO::GetInformationForAllApplicationsCommandHandler::GetInformationForAllApplicationsCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::GetInformationForAllApplicationsCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments)
    const
{
    NIMO_UNUSED_VAR_(arguments);
    ODL_OBJENTER(); //####
    ODL_P2("socket = ", &socket, "arguments = ", &arguments); //####
    bool    okSoFar{false};

    _owner->report("get information for all applications request received"s);
    if (0 < arguments.size())
    {
        auto    statusWithInfoVector{_registry->getInformationForAllApplications()};

        if (statusWithInfoVector.first.first)
        {
            auto                    applicationArray{std::make_shared<Array>()};
            ApplicationInfoVector & theApplications{statusWithInfoVector.second};

            for (auto walker = theApplications.begin(); walker != theApplications.end(); ++walker)
            {
                ApplicationInfo &   theInfo(*walker);
                auto                infoArray{std::make_shared<Array>()};

                infoArray->addValue(std::make_shared<Logical>(theInfo._found));
                infoArray->addValue(std::make_shared<String>(theInfo._launcherName));
                infoArray->addValue(std::make_shared<String>(theInfo._appName));
                infoArray->addValue(std::make_shared<String>(theInfo._appDescription));
                applicationArray->addValue(infoArray);
            }
            okSoFar = sendComplexResponse(socket, kGetInformationForAllApplicationsResponse, "get information for all applications"s,
                                          applicationArray);
        }
        else
        {
            ODL_LOG("! (statusWithInfoVector.first.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (0 < arguments.size())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetInformationForAllApplicationsCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)
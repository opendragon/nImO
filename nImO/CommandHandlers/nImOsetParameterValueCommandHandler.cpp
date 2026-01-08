//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/CommandHandlers/nImOsetParameterValueCommandHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for the nImO set parameter value command handler.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2025 by OpenDragon.
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
//  Created:    2025-11-12
//
//--------------------------------------------------------------------------------------------------

#include <CommandHandlers/nImOsetParameterValueCommandHandler.h>

#include <ArgumentDescriptors/nImObaseArgumentDescriptor.h>
#include <BasicTypes/nImOstring.h>
#include <nImOinputOutputCommands.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for the %nImO set parameter value command handler. */
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

nImO::SetParameterValueCommandHandler::SetParameterValueCommandHandler
    (SpInputOutputContext   owner,
     DescriptorVector &     argumentList) :
        inherited{owner}, _argumentList(argumentList)
{
    ODL_ENTER(); //####
    ODL_P2(owner.get(), &argumentList); //####
    ODL_EXIT_P(this); //####
} // nImO::SetParameterValueCommandHandler::SetParameterValueCommandHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::SetParameterValueCommandHandler::doIt
    (BTCP::socket & socket,
     const Array &  arguments,
     std::string &  reason)
    const
{
    ODL_OBJENTER(); //####
    ODL_P3(&socket, &arguments, &reason); //####
    bool    okSoFar{false};

    _ownerForInputOutput->report("Set parameter value request received."s);
    if (2 < arguments.size())
    {
        auto    asString1{arguments[1]->asString()};
        auto    asString2{arguments[2]->asString()};

        if ((nullptr == asString1) || (nullptr == asString2))
        {
            ODL_LOG("((nullptr == asString1) || (nullptr == asString2))"); //####
            reason = "Invalid argument(s)"s;
        }
        else
        {
            std::string paramName{asString1->getValue()};
            std::string paramValue{asString2->getValue()};
            bool        found{false};

            for (SpBaseArgumentDescriptor anArg : _argumentList)
            {
                if (nullptr != anArg)
                {
                    std::string argName{anArg->argumentName()};

                    if (paramName == argName)
                    {
                        found = true;
                        if (anArg->isMutable())
                        {
                            auto    oldValue{anArg->getProcessedValue()};

                            if (ProcessAnArgument(anArg, paramValue))
                            {
                                auto    infoArray{std::make_shared<Array>()};

                                // Remember the previous value.
                                infoArray->addValue(std::make_shared<String>(oldValue));
                                okSoFar = sendComplexResponse(socket, nImO::kSetParameterValueResponse, "set parameter value"s, infoArray, reason);
                                ODL_B1(okSoFar); //####
                            }
                            else
                            {
                                reason = "New value is invalid"s;
                            }
                        }
                        else
                        {
                            reason = "Parameter is not mutable"s;
                        }
                        break;

                    }
                }
            }
            if (! found)
            {
                ODL_LOG("! found"); //####
                reason = "Unknown parameter name"s;
            }
        }
    }
    else
    {
        ODL_LOG("! (2 < arguments.size())"); //####
        reason = "Missing argument(s)"s;
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::SetParameterValueCommandHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

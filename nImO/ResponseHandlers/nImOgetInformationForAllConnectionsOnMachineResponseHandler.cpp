//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ResponseHandlers/nImOgetInformationForAllConnectionsOnMachineResponseHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a functor used with the nImO request/response mechanism.
//
//  Written by: Norman Jaffe
//
//  Copyright:  (c) 2023 by OpenDragon.
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
//  Created:    2023-07-23
//
//--------------------------------------------------------------------------------------------------

#include <ResponseHandlers/nImOgetInformationForAllConnectionsOnMachineResponseHandler.h>

#include <BasicTypes/nImOinteger.h>
#include <BasicTypes/nImOlogical.h>
#include <BasicTypes/nImOstring.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a functor used with the %nImO request/response mechanism. */
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

nImO::GetInformationForAllConnectionsOnMachineResponseHandler::GetInformationForAllConnectionsOnMachineResponseHandler
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::GetInformationForAllConnectionsOnMachineResponseHandler::GetInformationForAllConnectionsOnMachineResponseHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::GetInformationForAllConnectionsOnMachineResponseHandler::doIt
    (const Array &  stuff)
{
    ODL_OBJENTER(); //####
    bool    okSoFar{false};

    _result.clear();
    if (1 < stuff.size())
    {
        auto    infoVector{stuff[1]->asArray()};

        if (nullptr == infoVector)
        {
            ODL_LOG("(nullptr == infoVector)"); //####
        }
        else
        {
            okSoFar = true;
            for (auto & walker : *infoVector)
            {
                auto    infoArray{walker->asArray()};

                if (nullptr == infoArray)
                {
                    ODL_LOG("(nullptr == infoArray)"); //####
                    okSoFar = false;
                }
                else
                {
                    ConnectionInfo  thisConnection;

                    thisConnection._found = false;
                    if (5 < infoArray->size())
                    {
                        auto    foundPtr{(*infoArray)[0]->asLogical()};
                        auto    fromNodePtr{(*infoArray)[1]->asString()};
                        auto    fromPathPtr{(*infoArray)[2]->asString()};
                        auto    toNodePtr{(*infoArray)[3]->asString()};
                        auto    toPathPtr{(*infoArray)[4]->asString()};
                        auto    dataTypePtr{(*infoArray)[5]->asString()};
                        auto    modePtr{(*infoArray)[6]->asInteger()};

                        if ((nullptr != foundPtr) && (nullptr != fromNodePtr) && (nullptr != fromPathPtr) && (nullptr != toNodePtr) &&
                            (nullptr != toPathPtr) && (nullptr != dataTypePtr) && (nullptr != modePtr))
                        {
                            thisConnection._found = foundPtr->getValue();
                            thisConnection._fromNode = fromNodePtr->getValue();
                            thisConnection._fromPath = fromPathPtr->getValue();
                            thisConnection._toNode = toNodePtr->getValue();
                            thisConnection._toPath = toPathPtr->getValue();
                            thisConnection._dataType = dataTypePtr->getValue();
                            thisConnection._mode = StaticCast(TransportType, modePtr->getIntegerValue());
                            if (thisConnection._found)
                            {
                                _result.push_back(thisConnection);
                            }
                        }
                        else
                        {
                            ODL_LOG("! ((nullptr != foundPtr) && (nullptr != fromNodePtr) && (nullptr != fromPathPtr) && " //####
                                    "(nullptr != toNodePtr) && (nullptr != toPathPtr) && (nullptr != dataTypePtr) && (nullptr != modePtr))"); //####
                            okSoFar = false;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (5 < infoArray->size())"); //####
                        okSoFar = false;
                    }
                }
            }
        }
    }
    else
    {
        ODL_LOG("! (1 < stuff.size())"); //####
    }
    ODL_OBJEXIT_B(okSoFar); //####
    return okSoFar;
} // nImO::GetInformationForAllConnectionsOnMachineResponseHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.cpp
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
//  Created:    2023-04-25
//
//--------------------------------------------------------------------------------------------------

#include <ResponseHandlers/nImOgetInformationForAllNodesOnMachineResponseHandler.h>

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

nImO::GetInformationForAllNodesOnMachineResponseHandler::GetInformationForAllNodesOnMachineResponseHandler
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::GetInformationForAllNodesOnMachineResponseHandler::GetInformationForAllNodesOnMachineResponseHandler

nImO::GetInformationForAllNodesOnMachineResponseHandler::~GetInformationForAllNodesOnMachineResponseHandler
    (void)
{
    ODL_OBJENTER(); //####
    ODL_OBJEXIT(); //####
} // nImO::GetInformationForAllNodesOnMachineResponseHandler::~GetInformationForAllNodesOnMachineResponseHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::GetInformationForAllNodesOnMachineResponseHandler::doIt
    (const Array &  stuff)
{
    ODL_OBJENTER(); //####
    _result.clear();
    if (1 < stuff.size())
    {
        SpValue     element{stuff[1]};
        CPtr(Array) infoVector{element->asArray()};

        if (nullptr == infoVector)
        {
            ODL_LOG("(nullptr == infoVector)"); //####
        }
        else
        {
            for (auto walker = infoVector->begin(); walker != infoVector->end(); ++walker)
            {
                CPtr(Array) infoArray{(*walker)->asArray()};

                if (nullptr == infoArray)
                {
                    ODL_LOG("(nullptr == infoArray)"); //####
                }
                else
                {
                    NodeInfo    thisNode;

                    thisNode._found = false;
                    if (5 < infoArray->size())
                    {
                        CPtr(Logical)   foundPtr{(*infoArray)[0]->asLogical()};
                        CPtr(String)    namePtr{(*infoArray)[1]->asString()};
                        CPtr(Integer)   serviceTypePtr{(*infoArray)[2]->asInteger()};
                        CPtr(Integer)   addressPtr{(*infoArray)[3]->asInteger()};
                        CPtr(Integer)   portPtr{(*infoArray)[4]->asInteger()};
                        CPtr(Integer)   transportPtr{(*infoArray)[5]->asInteger()};

                        if ((nullptr != foundPtr) && (nullptr != namePtr) && (nullptr != serviceTypePtr) && (nullptr != addressPtr) &&
                            (nullptr != portPtr) && (nullptr != transportPtr))
                        {
                            thisNode._found = foundPtr->getValue();
                            thisNode._name = namePtr->getValue();
                            thisNode._serviceType = StaticCast(ServiceType, serviceTypePtr->getIntegerValue());
                            thisNode._connection._address = addressPtr->getIntegerValue();
                            thisNode._connection._port = portPtr->getIntegerValue();
                            thisNode._connection._transport = StaticCast(TransportType, transportPtr->getIntegerValue());
                        }
                        else
                        {
                            ODL_LOG("! ((nullptr != foundPtr) && (nullptr != namePtr) && (nullptr != serviceTypePtr) && " //####
                                    "(nullptr != addressPtr) && (nullptr != portPtr) && (nullptr != transportPtr))"); //####
                        }
                    }
                    if (thisNode._found)
                    {
                        _result.push_back(thisNode);
                    }
                }
            }
        }
    }
    else
    {
        ODL_LOG("! (1 < stuff.size())"); //####
    }
    ODL_OBJEXIT(); //####
} // nImO::GetInformationForAllNodesOnMachineResponseHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/ResponseHandlers/nImOgetChannelInformationResponseHandler.cpp
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
//  Created:    2023-05-21
//
//--------------------------------------------------------------------------------------------------

#include <ResponseHandlers/nImOgetChannelInformationResponseHandler.h>

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

nImO::GetChannelInformationResponseHandler::GetChannelInformationResponseHandler
    (void) :
        inherited{}
{
    ODL_ENTER(); //####
    ODL_EXIT_P(this); //####
} // nImO::GetChannelInformationResponseHandler::GetChannelInformationResponseHandler

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

void
nImO::GetChannelInformationResponseHandler::doIt
    (const Array &  stuff)
{
    ODL_OBJENTER(); //####
    _result._found = false;
    if (1 < stuff.size())
    {
        SpValue     element{stuff[1]};
        CPtr(Array) infoArray{element->asArray()};

        if (nullptr == infoArray)
        {
            ODL_LOG("(nullptr == infoArray)"); //####
        }
        else
        {
            if (5 < infoArray->size())
            {
                CPtr(Logical)   foundPtr{(*infoArray)[0]->asLogical()};
                CPtr(String)    nodePtr{(*infoArray)[1]->asString()};
                CPtr(String)    pathPtr{(*infoArray)[2]->asString()};
                CPtr(Logical)   isOutputPtr{(*infoArray)[3]->asLogical()};
                CPtr(String)    dataTypePtr{(*infoArray)[4]->asString()};
                CPtr(Integer)   modesPtr{(*infoArray)[5]->asInteger()};

                if ((nullptr != foundPtr) && (nullptr != nodePtr) && (nullptr != pathPtr) && (nullptr != isOutputPtr) &&
                    (nullptr != dataTypePtr) && (nullptr != modesPtr))
                {
                    _result._found = foundPtr->getValue();
                    _result._node = nodePtr->getValue();
                    _result._path = pathPtr->getValue();
                    _result._isOutput = isOutputPtr->getValue();
                    _result._dataType = dataTypePtr->getValue();
                    _result._modes = StaticCast(TransportType, modesPtr->getIntegerValue());
                }
                else
                {
                    ODL_LOG("! ((nullptr != foundPtr) && (nullptr != nodePtr) && (nullptr != pathPtr) && (nullptr != isOutputPtr) && " //####
                            "(nullptr != dataTypePtr) && (nullptr != modesPtr))"); //####
                }
            }
            else
            {
                ODL_LOG("! (5 < infoArray->size())"); //####
            }
        }
    }
    else
    {
        ODL_LOG("! (1 < stuff.size())"); //####
    }
    ODL_OBJEXIT(); //####
} // nImO::GetChannelInformationResponseHandler::doIt

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

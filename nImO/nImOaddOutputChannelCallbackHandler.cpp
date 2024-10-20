//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOaddOutputChannelCallbackHandler.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for a callback function for adding output channels.
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
//  Created:    2024-10-13
//
//--------------------------------------------------------------------------------------------------

#include <nImOaddOutputChannelCallbackHandler.h>

#include <nImOchannelName.h>
#include <nImOregistryProxy.h>

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for a callback function for adding output channels. */
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

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::AddOutputChannelCallbackHandler::operator()
    (void)
{
    ODL_OBJENTER(); //####
    bool    result{false};

    if (_requestsAllowed)
    {
        try
        {
            _active = true;
            std::string scratch;
            int64_t     currentNumChannels = _context->getNumberOfOutputChannels();
            int64_t     nextChannelNumber = currentNumChannels + 1;

            // Using one greater than the requested number of channels will ensure that all the
            // channel paths will have a number at the end.
            if (nImO::ChannelName::generatePath(_basePath, true, nextChannelNumber + 1, nextChannelNumber, scratch))
            {
                auto    statusWithBool{_proxy->addChannel(_nodeName, scratch, true, _dataType, nImO::TransportType::kAny)};

                if (statusWithBool.first.first)
                {
                    if (statusWithBool.second)
                    {
                        _context->addOutputChannel(scratch);
                        _added = result = true;
                    }
                    else
                    {
                        _failureReason = "'"s + scratch + "' already registered"s;
                    }
                }
                else
                {
                    _failureReason = "Problem with 'addChannel': "s + statusWithBool.first.second;
                }
            }
            else
            {
                _failureReason = "Invalid channel path '"s + _basePath + "'"s;
            }
            _active = false;
        }
        catch (...)
        {
            _active = false;
            throw;

        }
    }
    else
    {
        _failureReason = "Service not finished setup or exiting"s;
    }
    ODL_OBJEXIT_B(result); //####
    return result;
} // nImO::AddOutputChannelCallbackHandler::operator()

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

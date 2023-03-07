//--------------------------------------------------------------------------------------------------
//
//  File:       nImO/nImOregistry.cpp
//
//  Project:    nImO
//
//  Contains:   The class definition for nImO registries.
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
//  Created:    2023-01-26
//
//--------------------------------------------------------------------------------------------------

#include "nImOregistry.h"

//#include <odlEnable.h>
#include <odlInclude.h>

#if defined(__APPLE__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunknown-pragmas"
# pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif // defined(__APPLE__)
/*! @file
 @brief The class definition for %nImO registries. */
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

/*! @brief Create the tables needed in the database.
 @parm[in,out] dbHandle The database handle to use.
 @return The status of the first failing operation or SQLITE 'OK' if all operations succeeded. */
static int
createTables
    (Ptr(sqlite3)   dbHandle)
{
    int result = SQLITE_OK;
    
    ODL_ENTER();
    if (nullptr != dbHandle)
    {
        
    }
    ODL_EXIT_I(result);
    return result;
} // createTables

/*! @brief A logging function specific for SQL events.
 @param[in] data The object to be used for reporting.
 @param[in] code The status code to be reported.
 @param[in] message The description of the event. */
static void
sqlLogger
    (Ptr(void)  data,
     const int  code,
     CPtr(char) message)
{
    NIMO_UNUSED_ARG_(code);
    Ptr(nImO::ContextWithNetworking)    owner = StaticCast(Ptr(nImO::ContextWithNetworking), data);

    if (nullptr != owner)
    {
        owner->report(message);
    }
} // sqlLogger

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Registry::Registry
    (Ptr(ContextWithNetworking) owner,
     const bool                 logging) :
        _dbHandle(nullptr), _owner(owner)
{
    ODL_ENTER(); //####
    if (logging && (nullptr != _owner))
    {
        sqlite3_config(SQLITE_CONFIG_LOG, sqlLogger, _owner);
    }
    int result = sqlite3_open_v2("nImO_registry", &_dbHandle,
                                 SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY | SQLITE_OPEN_PRIVATECACHE, nullptr);

    if (SQLITE_OK == result)
    {
        createTables(_dbHandle);
    }
    else
    {
        std::string errorMessage(sqlite3_errstr(result));

        throw "Unable to open database: " + errorMessage;
    }
    ODL_EXIT_P(this); //####
} // nImO::Registry::Registry

nImO::Registry::~Registry
    (void)
{
    ODL_OBJENTER(); //####
    sqlite3_close_v2(_dbHandle);
    ODL_OBJEXIT(); //####
} // nImO::Registry::~Registry

#if defined(__APPLE__)
# pragma mark Actions and Accessors
#endif // defined(__APPLE__)

bool
nImO::Registry::addNode
    (const std::string &    nodeName)
{
    bool    added = false;

    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(added); //####
    return added;
} // nImO::Registry::addNode

nImO::StringSet
nImO::Registry::getNodes
    (void)
    const
{
    StringSet   result;

    ODL_OBJENTER();
    ODL_OBJEXIT();
    return result;
} // nImO::Registry::getNodes

bool
nImO::Registry::nodePresent
    (const std::string &    nodeName)
{
    bool    found = false;

    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(found); //####
    return found;
} // nImO::Registry::nodePresent

int
nImO::Registry::numNodes
    (void)
    const
{
    int count = -1;

    ODL_OBJENTER(); //####
    ODL_OBJEXIT_I(count); //####
    return count;
} // nImO::Registry::numNodes

bool
nImO::Registry::removeNode
    (const std::string &    nodeName)
{
    bool    removed = false;

    ODL_OBJENTER(); //####
    ODL_OBJEXIT_B(removed); //####
    return removed;
} // nImO::Registry::removeNode

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

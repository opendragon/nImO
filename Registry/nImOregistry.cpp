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

#include <nImOchannelName.h>

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

/*! @brief A shortcut for the case-sensitive form of a 'Text' column. */
#define BINARY_ "COLLATE BINARY"

/*! @brief A shortcut for the case-insensitive form of a 'Text' column. */
#define NOCASE_ "COLLATE NOCASE"

/*! @brief A shortcut for the standard format for a 'Text' column. */
#define TEXTNOTNULL_    "TEXT NOT NULL DEFAULT _"

/*! @brief The name of the 'Machines' table. */
#define MACHINES_T_ "Machines"

/*! @brief The named parameter for the 'name' column of the 'Machines' table. */
#define MACHINE_NAME_C_ "name"

/*! @brief The named parameter for the 'address' column of the 'Machines' table. */
#define MACHINE_ADDRESS_C_  "address"

/*! @brief The name of the index for the 'name' column of the 'Machines' table. */
#define MACHINES_NAME_I_    "Machines_name_idx"

/*! @brief The name of the index for the 'address' column of the 'Machines' table. */
#define MACHINES_ADDRESS_I_ "Machines_address_idx"

/*! @brief The name of the 'Nodes' table. */
#define NODES_T_    "Nodes"

/*! @brief The named parameter for the 'name' column of the 'Nodes' table. */
#define NODE_NAME_C_    "name"

/*! @brief The named parameter for the 'address' column of the 'Nodes' table. */
#define NODE_ADDRESS_C_ "address"

/*! @brief The named parameter for the 'port' column of the 'Nodes' table. */
#define NODE_PORT_C_    "port"

/*! @brief The named parameter for the 'serviceType' column of the 'Nodes' table. */
#define NODE_SERVICE_TYPE_C_    "serviceType"

/*! @brief The named parameter for the 'execPath' column of the 'Nodes' table. */
#define NODE_EXEC_PATH_C_   "execPath"

/*! @brief The named parameter for the 'launchDirectory' column of the 'Nodes' table. */
#define NODE_LAUNCH_DIRECTORY_C_    "launchDirectory"

/*! @brief The named parameter for the 'commandLine' column of the 'Nodes' table. */
#define NODE_COMMAND_LINE_C_    "commandLine"

/*! @brief The name of the index for the 'name' column of the 'Nodes' table. */
#define NODES_NAME_I_   "Nodes_name_idx"

/*! @brief The name of the 'Channels' table. */
#define CHANNELS_T_ "Channels"

/*! @brief The named parameter for the 'node' column of the 'Channels' table. */
#define CHANNEL_NODE_C_    "node"

/*! @brief The named parameter for the 'path' column of the 'Channels' table. */
#define CHANNEL_PATH_C_    "path"

/*! @brief The named parameter for the 'isOutput' column of the 'Channels' table. */
#define CHANNEL_IS_OUTPUT_C_   "isOutput"

/*! @brief The named parameter for the 'dataType' column of the 'Channels' table. */
#define CHANNEL_DATA_TYPE_C_   "dataType"

/*! @brief The named parameter for the 'modes' column of the 'Channels' table. */
#define CHANNEL_MODES_C_    "modes"

/*! @brief The name of the index for the 'node' and 'path' columns of the 'Channels' table. */
#define CHANNELS_I_ "Channels_idx"

/*! @brief A function that provides bindings for parameters in an SQL statement.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
typedef int (*BindFunction)
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff);

/*! @brief The data used to update the Channels table. */
struct ChannelInsertData
{
    /*! @brief The node for this channel. */
    std::string _node;

    /*! @brief The path for this channel. */
    std::string _path;

    /*! @brief @c true if this channel is to be used for output. */
    bool    _isOutput;

    /*! @brief The format of the data to be transferred over this channel. */
    std::string _dataType;

    /*! @brief The allowed transport types for the channel. */
    nImO::TransportType   _modes;

    /*! @brief The constructor.
     @param[in] node The name of the node for the channel.
     @param[in] path The path for the channel.
     @param[in] isOutput @c true if the channel is an output.
     @param[in] dataType The format for the data to be transferred over the channel.
     @param[in] modes The allowed transport types for the channel. */
    inline ChannelInsertData
        (const std::string &        node,
         const std::string &        path,
         const bool                 isOutput,
         const std::string &        dataType,
         const nImO::TransportType  modes) :
            _node(node), _path(path), _isOutput(isOutput), _dataType(dataType), _modes(modes)
    {
    }

}; // ChannelInsertData

/*! @brief The data used to search the Channels table. */
struct ChannelSearchData
{
    /*! @brief The node for this channel. */
    std::string _node;

    /*! @brief The path for this channel. */
    std::string _path;

    /*! @brief The constructor.
     @param[in] node The name of the node for the channel.
     @param[in] path The path for the channel. */
    inline ChannelSearchData
        (const std::string &    node,
         const std::string &    path) :
            _node(node), _path(path)
    {
    }

}; // ChannelSearchData

/*! @brief The data used to update the Machines table. */
struct MachineInsertData
{
    /*! @brief The name of this machine. */
    std::string _name;

    /*! @brief The IP address for this machine.*/
    uint32_t    _address;

    /*! @brief The constructor.
     @param[in] name The name of this node.
     @param[in] connection The command IP address and port for this node.
     @param[in] serviceType The type of service provided by this node. */
    inline MachineInsertData
        (const std::string &    name,
         const uint32_t         address) :
            _name(name), _address(address)
    {
    }

}; // MachineInsertData

/*! @brief The data used to update the Nodes table. */
struct NodeInsertData
{
    /*! @brief The name of this node. */
    std::string _name;

    /*! @brief The command IP address and port for this node.*/
    nImO::Connection    _connection;

    /*! @brief The type of this node. */
    nImO::ServiceType   _serviceType;

    /*! @brief The path to the executable for this node. */
    std::string _execPath;

    /*! @brief The directory where this node was launched. */
    std::string _launchDirectory;

    /*! @brief The command line that was used to launch this node. */
    std::string _commandLine;

    /*! @brief The constructor.
     @param[in] name The name of this node.
     @param[in] connection The command IP address and port for this node.
     @param[in] serviceType The type of service provided by this node. */
    inline NodeInsertData
        (const std::string &        name,
         const nImO::Connection &   connection,
         const nImO::ServiceType    serviceType,
         const std::string &        execPath,
         const std::string &        launchDirectory,
         const std::string &        commandLine) :
            _name(name), _connection(connection), _serviceType(serviceType), _execPath(execPath), _launchDirectory(launchDirectory),
            _commandLine(commandLine)
    {
    }

}; // NodeInsertData

#if defined(__APPLE__)
# pragma mark Global constants and variables
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Local functions
#endif // defined(__APPLE__)

/*! @brief Perform an operation that can return multiple rows of results.
 @param[in] database The database to be modified.
 @param[in,out] resultList The list to be filled in with the values from the column of interest.
 @param[in] sqlStatement The operation to be performed.
 @param[in] doBinds A function that will fill in any parameters in the statement.
 @param[in] data The custom information used with the binding function.
 @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
static nImO::RegSuccessOrFailure
performSQLstatementWithMultipleColumnResults
    (nImO::SpContextWithNetworking      owner,
     Ptr(sqlite3)                       dbHandle,
     std::vector<nImO::StringVector> &  results,
     CPtr(char)                         sqlStatement,
     BindFunction                       doBinds = nullptr,
     CPtr(void)                         data = nullptr)
{
    ODL_ENTER(); //####
    ODL_P4("owner = ", owner.get(), "dbHandle = ", dbHandle, "results = ", &results, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    ODL_B1("(nullptr != doBinds) = ", nullptr != doBinds); //####
    nImO::RegSuccessOrFailure   status{true, ""};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared{nullptr};
            int                 sqlRes{sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr)};

            ODL_I1("sqlRes <- ", sqlRes); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                if (nullptr != doBinds)
                {
                    sqlRes = doBinds(prepared, data);
                    ODL_I1("sqlRes <- ", sqlRes); //####
                    if (SQLITE_OK != sqlRes)
                    {
                        status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                if (status.first)
                {
                    for (sqlRes = SQLITE_ROW; SQLITE_ROW == sqlRes; )
                    {
                        do
                        {
                            sqlRes = sqlite3_step(prepared);
                            ODL_I1("sqlRes <- ", sqlRes); //####
                            if (SQLITE_BUSY == sqlRes)
                            {
                                nImO::ConsumeSomeTime(owner.get(), 10.0);
                            }
                        }
                        while (SQLITE_BUSY == sqlRes);
                        if (SQLITE_ROW == sqlRes)
                        {
                            // Gather the column data...
                            int colCount{sqlite3_column_count(prepared)};

                            ODL_I1("colCount <- ", colCount); //####
                            if (0 < colCount)
                            {
                                nImO::StringVector  thisRow;

                                for (int ii = 0; ii < colCount; ++ii)
                                {
                                    CPtr(char)  value{ReinterpretCast(CPtr(char), sqlite3_column_text(prepared, ii))};

                                    ODL_S1("value <- ", value); //####
                                    if (nullptr == value)
                                    {
                                        thisRow.push_back("");
                                    }
                                    else
                                    {
                                        thisRow.push_back(value);
                                    }
                                }
                                results.push_back(thisRow);
                            }
                        }
                    }
                    if (SQLITE_DONE != sqlRes)
                    {
                        ODL_LOG("(SQLITE_DONE != sqlRes)"); //####
                        status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT(); //####
    return status;
} // performSQLstatementWithMultipleColumnResults

/*! @brief Perform a simple operation on the database.
 @param[in] dbHandle The database to be modified.
 @param[in] sqlStatement The operation to be performed.
 @param[in] doBinds A function that will fill in any parameters in the statement.
 @param[in] data The custom information used with the binding function.
 @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
static nImO::RegSuccessOrFailure
performSQLstatementWithNoResults
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     CPtr(char)                     sqlStatement,
     BindFunction                   doBinds = nullptr,
     CPtr(void)                     data = nullptr)
{
    ODL_ENTER(); //####
    ODL_P3("owner = ", owner.get(), "dbHandle = ", dbHandle, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    ODL_B1("(nullptr != doBinds) = ", nullptr != doBinds); //####
    nImO::RegSuccessOrFailure   status{true, ""};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared{nullptr};
            int                 sqlRes{sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr)};

            ODL_I1("sqlRes <- ", sqlRes); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                if (nullptr != doBinds)
                {
                    sqlRes = doBinds(prepared, data);
                    ODL_I1("sqlRes <- ", sqlRes); //####
                    if (SQLITE_OK != sqlRes)
                    {
                        status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                if (status.first)
                {
                    do
                    {
                        sqlRes = sqlite3_step(prepared);
                        ODL_I1("sqlRes <- ", sqlRes); //####
                        if (SQLITE_BUSY == sqlRes)
                        {
                            nImO::ConsumeSomeTime(owner.get(), 10.0);
                        }
                    }
                    while (SQLITE_BUSY == sqlRes);
                    if (SQLITE_DONE != sqlRes)
                    {
                        ODL_LOG("(SQLITE_DONE != sqlRes)"); //####
                        status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && prepared)"); //####
                status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT(); //####
    return status;
} // performSQLstatementWithNoResults

/*! @brief Perform a simple operation on the database.
 @param[in] owner The object to be used for reporting.
 @param[in] dbHandle The database to be modified.
 @param[in] sqlStatement The operation to be performed.
 @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
static nImO::RegSuccessOrFailure
performSQLstatementWithNoResultsNoArgs
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     CPtr(char)                     sqlStatement)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    nImO::RegSuccessOrFailure   status{true, ""};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared{nullptr};
            int                 sqlRes{sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr)};

            ODL_I1("sqlRes <- ", sqlRes); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                do
                {
                    sqlRes = sqlite3_step(prepared);
                    ODL_I1("sqlRes <- ", sqlRes); //####
                    if (SQLITE_BUSY == sqlRes)
                    {
                        nImO::ConsumeSomeTime(owner.get(), 10.0);
                    }
                }
                while (SQLITE_BUSY == sqlRes);
                if (SQLITE_DONE != sqlRes)
                {
                    ODL_LOG("(SQLITE_DONE != sqlRes)"); //####
                    status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT(); //####
    return status;
} // performSQLstatementWithNoResultsNoArgs

/*! @brief Perform an operation that can return multiple rows of results.
 @param[in] database The database to be modified.
 @param[in,out] resultList The list to be filled in with the values from the column of interest.
 @param[in] sqlStatement The operation to be performed.
 @param[in] doBinds A function that will fill in any parameters in the statement.
 @param[in] data The custom information used with the binding function.
 @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
static nImO::RegSuccessOrFailure
performSQLstatementWithSingleColumnResults
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     nImO::StringVector &           resultList,
     CPtr(char)                     sqlStatement,
     BindFunction                   doBinds = nullptr,
     CPtr(void)                     data = nullptr)
{
    ODL_ENTER(); //####
    ODL_P4("owner = ", owner.get(), "dbHandle = ", dbHandle, "resultList = ", &resultList, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    ODL_B1("(nullptr != doBinds) = ", nullptr != doBinds); //####
    nImO::RegSuccessOrFailure   status{true, ""};

    resultList.clear();
    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared{nullptr};
            int                 sqlRes{sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr)};

            ODL_I1("sqlRes <- ", sqlRes); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                if (nullptr != doBinds)
                {
                    sqlRes = doBinds(prepared, data);
                    ODL_I1("sqlRes <- ", sqlRes); //####
                    if (SQLITE_OK != sqlRes)
                    {
                        status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                if (status.first)
                {
                    for (sqlRes = SQLITE_ROW; SQLITE_ROW == sqlRes; )
                    {
                        do
                        {
                            sqlRes = sqlite3_step(prepared);
                            ODL_I1("sqlRes <- ", sqlRes); //####
                            if (SQLITE_BUSY == sqlRes)
                            {
                                nImO::ConsumeSomeTime(owner.get(), 10.0);
                            }
                        }
                        while (SQLITE_BUSY == sqlRes);
                        if (SQLITE_ROW == sqlRes)
                        {
                            // Gather the column data...
                            int colCount{sqlite3_column_count(prepared)};

                            ODL_I1("colCount <- ", colCount); //####
                            if (0 < colCount)
                            {
                                CPtr(char)  value{ReinterpretCast(CPtr(char), sqlite3_column_text(prepared, 0))};

                                ODL_S1("value <- ", value); //####
                                if (nullptr != value)
                                {
                                    resultList.push_back(value);
                                }
                            }
                        }
                    }
                    if (SQLITE_DONE != sqlRes)
                    {
                        ODL_LOG("(SQLITE_DONE != sqlRes)"); //####
                        status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                status = nImO::RegSuccessOrFailure{false, sqlite3_errstr(sqlRes)};
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT(); //####
    return status;
} // performSQLstatementWithSingleColumnResults

/*! @brief Start a transaction.
 @param[in] owner The object to be used for reporting.
 @param[in] dbHandle The database to be modified.
 @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
static nImO::RegSuccessOrFailure
doBeginTransaction
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    nImO::RegSuccessOrFailure   status{true, ""};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            static CPtr(char)   beginTransaction{"BEGIN TRANSACTION"};

            status = performSQLstatementWithNoResultsNoArgs(owner, dbHandle, beginTransaction);
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT(); //####
    return status;
} // doBeginTransaction

/*! @brief End a transaction.
 @param[in] owner The object to be used for reporting.
 @param[in] database The database to be modified.
 @param[in] wasOK @c true if the transaction was successful and @c false otherwise.
 @return @c true and an empty error message if the operation was successfully performed and @c false and an error string otherwise. */
static nImO::RegSuccessOrFailure
doEndTransaction
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     const bool                     wasOK)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_B1("wasOK = ", wasOK); //####
    nImO::RegSuccessOrFailure   status{true, ""};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            static CPtr(char)   abortTransaction{"ROLLBACK TRANSACTION"};
            static CPtr(char)   commitTransaction{"END TRANSACTION"};

            status = performSQLstatementWithNoResultsNoArgs(owner, dbHandle, wasOK ? commitTransaction : abortTransaction);
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT(); //####
    return status;
} // doEndTransaction

/*! @brief Create the tables needed in the database.
 @param[in] owner The object to be used for reporting.
 @param[in] logging @c true if operations are to be logged.
 @parm[in,out] dbHandle The database handle to use.
 @return @c true if all the tables were successfully created. */
static nImO::RegSuccessOrFailure
createTables
    (nImO::SpContextWithNetworking  owner,
     const bool                     logging,
     Ptr(sqlite3)                   dbHandle)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_B1("logging = ", logging); //####
    nImO::RegSuccessOrFailure   status{true, ""};

    if (nullptr == dbHandle)
    {
        ODL_LOG("(nullptr == dbHandle)"); //####
        status = nImO::RegSuccessOrFailure{false, "No open database"};
    }
    else
    {
        if ((nullptr != owner) && logging)
        {
            owner->report("creating tables.");
        }
        status = doBeginTransaction(owner, dbHandle);
        if (status.first)
        {
            static CPtr(char)   tableSQL[]
            {
                "CREATE TABLE IF NOT EXISTS " MACHINES_T_ "(" MACHINE_NAME_C_ " " TEXTNOTNULL_ " " NOCASE_ "," MACHINE_ADDRESS_C_
                        " INTEGER UNIQUE ON CONFLICT ABORT, PRIMARY KEY (" MACHINE_NAME_C_ ") ON CONFLICT IGNORE)",
                "CREATE INDEX IF NOT EXISTS " MACHINES_NAME_I_ " ON " MACHINES_T_ "(" MACHINE_NAME_C_ ")",
                "CREATE INDEX IF NOT EXISTS " MACHINES_ADDRESS_I_ " ON " MACHINES_T_ "(" MACHINE_ADDRESS_C_ ")",
                "CREATE TABLE IF NOT EXISTS " NODES_T_ "(" NODE_NAME_C_ " " TEXTNOTNULL_ " " NOCASE_ "," NODE_ADDRESS_C_ " INTEGER, " NODE_PORT_C_
                        " INTEGER, " NODE_SERVICE_TYPE_C_ " INTEGER," NODE_EXEC_PATH_C_ " " TEXTNOTNULL_ " " BINARY_ ", " NODE_LAUNCH_DIRECTORY_C_
                        " " TEXTNOTNULL_ " " BINARY_ ", " NODE_COMMAND_LINE_C_ " " TEXTNOTNULL_ " " BINARY_ ", PRIMARY KEY (" NODE_NAME_C_
                        ") ON CONFLICT ABORT, FOREIGN KEY (" MACHINE_ADDRESS_C_ ") REFERENCES " MACHINES_T_ " (" MACHINE_ADDRESS_C_ "))",
                "CREATE INDEX IF NOT EXISTS " NODES_NAME_I_ " ON " NODES_T_ "(" NODE_NAME_C_ ")",
                "CREATE TABLE IF NOT EXISTS " CHANNELS_T_ " (" CHANNEL_NODE_C_ " TEXT NOT NULL DEFAULT _ COLLATE NOCASE, " CHANNEL_PATH_C_
                        " TEXT NOT NULL DEFAULT _ COLLATE BINARY, " CHANNEL_IS_OUTPUT_C_ " INTEGER, " CHANNEL_DATA_TYPE_C_
                        " TEXT DEFAULT _ COLLATE BINARY, " CHANNEL_MODES_C_ " INTEGER, FOREIGN KEY (" CHANNEL_NODE_C_ ") REFERENCES "
                        NODES_T_ " (" NODE_NAME_C_ "), PRIMARY KEY (" CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ ") ON CONFLICT ABORT)",
                "CREATE INDEX IF NOT EXISTS " CHANNELS_I_ " ON " CHANNELS_T_ " (" CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ ")"
            };
            static const size_t numTables{A_SIZE(tableSQL)};

            for (size_t ii = 0; status.first && (ii < numTables); ++ii)
            {
                status = performSQLstatementWithNoResultsNoArgs(owner, dbHandle, tableSQL[ii]);
            }
            doEndTransaction(owner, dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    ODL_EXIT(); //####
    return status;
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
    NIMO_UNUSED_VAR_(code);
    Ptr(nImO::ContextWithNetworking)    owner{StaticCast(Ptr(nImO::ContextWithNetworking), data)};

    if (nullptr != owner)
    {
        owner->report(message);
    }
} // sqlLogger

/*! @brief Bind the value that is to be searched for in the Machines table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupCountChannels
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int nodeNameIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_NODE_C_)};

        if (0 < nodeNameIndex)
        {
            std::string name{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, nodeNameIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < nodeNameIndex)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupCountChannels

/*! @brief Bind the values that are to be inserted into the Channels table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupInsertIntoChannels
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int nodeNameIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_NODE_C_)};
        int pathIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_PATH_C_)};
        int isOutputIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_IS_OUTPUT_C_)};
        int dataTypeIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_DATA_TYPE_C_)};
        int modesIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_MODES_C_)};

        if ((0 < nodeNameIndex) && (0 < pathIndex) && (0 < isOutputIndex) && (0 < dataTypeIndex) && (0 < modesIndex))
        {
            auto                channelData{StaticCast(CPtr(ChannelInsertData), stuff)};
            std::string         node{channelData->_node};
            std::string         path{channelData->_path};
            bool                isOutput{channelData->_isOutput};
            std::string         dataType{channelData->_dataType};
            nImO::TransportType modes{channelData->_modes};

            result = sqlite3_bind_text(statement, nodeNameIndex, node.c_str(), StaticCast(int, node.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, pathIndex, path.c_str(), StaticCast(int, path.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, isOutputIndex, isOutput ? 1 : 0);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, dataTypeIndex, dataType.c_str(), StaticCast(int, dataType.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, modesIndex, StaticCast(int, modes));
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < nodeNameIndex) && (0 < pathIndex) && (0 < isOutputIndex) && (0 < dataTypeIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupInsertIntoChannels

/*! @brief Bind the values that are to be inserted into the Machines table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupInsertIntoMachines
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int machineNameIndex{sqlite3_bind_parameter_index(statement, "@" MACHINE_NAME_C_)};
        int machineAddressIndex{sqlite3_bind_parameter_index(statement, "@" MACHINE_ADDRESS_C_)};

        if ((0 < machineNameIndex) && (0 < machineAddressIndex))
        {
            auto        machineData{StaticCast(CPtr(MachineInsertData), stuff)};
            std::string name{machineData->_name};
            uint32_t    address{machineData->_address};

            result = sqlite3_bind_text(statement, machineNameIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, machineAddressIndex, address);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < machineNameIndex) && (0 < machineAddressIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupInsertIntoMachines

/*! @brief Bind the values that are to be inserted into the Nodes table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupInsertIntoNodes
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int nodeNameIndex{sqlite3_bind_parameter_index(statement, "@" NODE_NAME_C_)};
        int nodeAddressIndex{sqlite3_bind_parameter_index(statement, "@" NODE_ADDRESS_C_)};
        int nodePortIndex{sqlite3_bind_parameter_index(statement, "@" NODE_PORT_C_)};
        int nodeServiceTypeIndex{sqlite3_bind_parameter_index(statement, "@" NODE_SERVICE_TYPE_C_)};
        int nodeExecPathIndex{sqlite3_bind_parameter_index(statement, "@" NODE_EXEC_PATH_C_)};
        int nodeLaunchDirectoryIndex{sqlite3_bind_parameter_index(statement, "@" NODE_LAUNCH_DIRECTORY_C_)};
        int nodeCommandLineIndex{sqlite3_bind_parameter_index(statement, "@" NODE_COMMAND_LINE_C_)};

        if ((0 < nodeNameIndex) && (0 < nodeAddressIndex) && (0 < nodePortIndex) && (0 < nodeServiceTypeIndex) && (0 < nodeExecPathIndex) &&
            (0 < nodeLaunchDirectoryIndex) && (0 < nodeCommandLineIndex))
        {
            auto        nodeData{StaticCast(CPtr(NodeInsertData), stuff)};
            std::string name{nodeData->_name};
            std::string execPath{nodeData->_execPath};
            std::string launchDirectory{nodeData->_launchDirectory};
            std::string commandLine{nodeData->_commandLine};

            result = sqlite3_bind_text(statement, nodeNameIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, nodeAddressIndex, nodeData->_connection._address);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, nodePortIndex, nodeData->_connection._port);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, nodeServiceTypeIndex, StaticCast(int, nodeData->_serviceType));
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, nodeExecPathIndex, execPath.c_str(), StaticCast(int, execPath.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, nodeLaunchDirectoryIndex, launchDirectory.c_str(), StaticCast(int, launchDirectory.length()),
                                           SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, nodeCommandLineIndex, commandLine.c_str(), StaticCast(int, commandLine.length()),
                                           SQLITE_TRANSIENT);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < nodeNameIndex) && (0 < nodeAddressIndex) && (0 < nodePortIndex) && (0 < nodeServiceTypeIndex) && " //####
                    "(0 < nodeExecPathIndex) && (0 < nodeLaunchDirectoryIndex) && (0 < nodeCommandLineIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupInsertIntoNodes

/*! @brief Bind the values that are to be searched for in the Channels table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchChannels
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int channelNodeIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_NODE_C_)};
        int channelPathIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_PATH_C_)};

        if ((0 < channelNodeIndex) && (0 < channelPathIndex))
        {
            auto        channelSearch{StaticCast(CPtr(ChannelSearchData), stuff)};
            std::string node{channelSearch->_node};
            std::string path{channelSearch->_path};

            result = sqlite3_bind_text(statement, channelNodeIndex, node.c_str(), StaticCast(int, node.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, channelPathIndex, path.c_str(), StaticCast(int, path.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < machineNameIndex) && (0 < channelPathIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchChannels

/*! @brief Bind the value that is to be searched for in the Channels table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchChannelsMachineOnly
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int machineNameIndex{sqlite3_bind_parameter_index(statement, "@" MACHINE_NAME_C_)};

        if (0 < machineNameIndex)
        {
            std::string machine{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, machineNameIndex, machine.c_str(), StaticCast(int, machine.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < machineNameIndex)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchChannelsMachineOnly

/*! @brief Bind the value that is to be searched for in the Channels table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchChannelsNodeOnly
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int channelNodeIndex{sqlite3_bind_parameter_index(statement, "@" CHANNEL_NODE_C_)};

        if (0 < channelNodeIndex)
        {
            std::string node{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, channelNodeIndex, node.c_str(), StaticCast(int, node.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < channelNodeIndex)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchChannelsNodeOnly

/*! @brief Bind the value that is to be searched for in the Machines table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchMachines
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int machineNameIndex{sqlite3_bind_parameter_index(statement, "@" MACHINE_NAME_C_)};

        if (0 < machineNameIndex)
        {
            std::string name{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, machineNameIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < nodeNameIndex)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchMachines

/*! @brief Bind the value that is to be searched for in the Nodes table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchNodes
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int nodeNameIndex{sqlite3_bind_parameter_index(statement, "@" NODE_NAME_C_)};

        if (0 < nodeNameIndex)
        {
            std::string name{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, nodeNameIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! (0 < nodeNameIndex)"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchNodes

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Registry::Registry
    (SpContextWithNetworking    owner,
     const bool                 logging) :
        _dbHandle(nullptr), _owner(owner)
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_B1("logging = ", logging); //####
    if (logging && (nullptr != _owner))
    {
        sqlite3_config(SQLITE_CONFIG_LOG, sqlLogger, _owner.get());
    }
    int result{sqlite3_open_v2("nImO_registry", &_dbHandle,
                               SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY | SQLITE_OPEN_PRIVATECACHE, nullptr)};

    if (SQLITE_OK == result)
    {
        nImO::RegSuccessOrFailure   status{createTables(_owner, logging, _dbHandle)};

        if (! status.first)
        {
            std::string prefix{"Problem creating tables in database: "};

            if ((nullptr != _owner) && logging)
            {
                _owner->report(prefix + status.second);
            }
            throw prefix + status.second;
        }
    }
    else
    {
        std::string errorMessage(sqlite3_errstr(result));
        std::string prefix{"Unable to open database: "};

        if ((nullptr != _owner) && logging)
        {
            _owner->report(prefix + errorMessage);
        }
        throw prefix + errorMessage;
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

nImO::RegSuccessOrFailure
nImO::Registry::addChannel
    (const std::string &    nodeName,
     const std::string &    path,
     const bool             isOutput,
     const std::string &    dataType,
     const TransportType    modes)
    const
{
    ODL_OBJENTER(); //####
    ODL_S3s("nodeName = ", nodeName, "path = ", path, "dataType = ", dataType); //####
    ODL_B1("isOutput = ", isOutput); //####
    ODL_I1("modes = ", StaticCast(int, modes)); //####
    RegSuccessOrFailure status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        RegBoolOrFailure    statusWithBool{isNodePresent(nodeName)};

        if (statusWithBool.first.first)
        {
            if (statusWithBool.second)
            {
                status = doBeginTransaction(_owner, _dbHandle);
                if (status.first)
                {
                    ChannelInsertData   data{nodeName, path, isOutput, dataType, modes};
                    static CPtr(char)   insertIntoChannels{"INSERT INTO " CHANNELS_T_ " (" CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ ", "
                                                            CHANNEL_IS_OUTPUT_C_ ", " CHANNEL_DATA_TYPE_C_ ", " CHANNEL_MODES_C_
                                                            ") VALUES (@" CHANNEL_NODE_C_ ", @" CHANNEL_PATH_C_ ", @" CHANNEL_IS_OUTPUT_C_
                                                            ", @" CHANNEL_DATA_TYPE_C_ ", @" CHANNEL_MODES_C_ ")"};

                    status = performSQLstatementWithNoResults(_owner, _dbHandle, insertIntoChannels, setupInsertIntoChannels, &data);
                    doEndTransaction(_owner, _dbHandle, status.first);
                }
                else
                {
                    ODL_LOG("! (status.first)"); //####
                }
            }
            else
            {
                ODL_LOG("! (statusWithBool.second)"); //####
                status = RegSuccessOrFailure(false, "Unknown node name");
            }
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name or path");
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addChannel

nImO::RegSuccessOrFailure
nImO::Registry::addMachine
    (const std::string &    machineName,
     const uint32_t         address)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    ODL_I1("address = ", address); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        MachineInsertData   data{machineName, address};
        static CPtr(char)   insertIntoMachines{"INSERT INTO " MACHINES_T_ " (" MACHINE_NAME_C_ ", " MACHINE_ADDRESS_C_ ") VALUES (@" MACHINE_NAME_C_
                                                ", @" MACHINE_ADDRESS_C_ ")"};

        status = performSQLstatementWithNoResults(_owner, _dbHandle, insertIntoMachines, setupInsertIntoMachines, &data);
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addMachine

nImO::RegSuccessOrFailure
nImO::Registry::addNode
    (const std::string &    nodeName,
     const std::string &    execPath,
     const std::string &    launchDirectory,
     const std::string &    commandLine,
     const ServiceType      serviceClass,
     const Connection &     nodeConnection)
    const
{
    ODL_OBJENTER(); //####
    ODL_S4s("nodeName = ", nodeName, "execPath = ", execPath, "launchDirectory = ", launchDirectory, "commandLine = ", commandLine); //####
    ODL_I1("serviceClass = ", StaticCast(int, serviceClass)); //####
    ODL_P1("nodeConnection = ", &nodeConnection); //####
    RegSuccessOrFailure status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            NodeInsertData      data{nodeName, nodeConnection, serviceClass, execPath, launchDirectory, commandLine};
            static CPtr(char)   insertIntoNodes{"INSERT INTO " NODES_T_ " (" NODE_NAME_C_ ", " NODE_ADDRESS_C_ ", " NODE_PORT_C_ ", "
                                                NODE_SERVICE_TYPE_C_ ", " NODE_EXEC_PATH_C_ ", " NODE_LAUNCH_DIRECTORY_C_ ", " NODE_COMMAND_LINE_C_
                                                ") VALUES (@" NODE_NAME_C_ ", @" NODE_ADDRESS_C_ ", @" NODE_PORT_C_ ", @" NODE_SERVICE_TYPE_C_
                                                ", @" NODE_EXEC_PATH_C_ ", @" NODE_LAUNCH_DIRECTORY_C_ ", @" NODE_COMMAND_LINE_C_ ")"};

            status = performSQLstatementWithNoResults(_owner, _dbHandle, insertIntoNodes, setupInsertIntoNodes, &data);
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addNode

nImO::RegChannelInfoOrFailure
nImO::Registry::getChannelInformation
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status;
    ChannelInfo         info;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            std::vector<StringVector>   results;
            ChannelSearchData           data{nodeName, path};
            static CPtr(char)           searchChannels{"SELECT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ "," CHANNEL_DATA_TYPE_C_
                                                        "," CHANNEL_MODES_C_ "  FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_
                                                        " AND " CHANNEL_PATH_C_ " = @" CHANNEL_PATH_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannels, &data);
            if (status.first)
            {
                if (0 < results.size())
                {
                    StringVector    values{results[0]};

                    if (4 < values.size())
                    {
                        size_t      pos;
                        uint32_t    scratch;

                        info._found = true;
                        info._node = values[0];
                        info._path = values[1];
                        scratch = StaticCast(uint32_t, stoul(values[2], &pos));
                        if (0 == pos)
                        {
                            info._found = false;
                        }
                        else
                        {
                            info._isOutput = (0 != scratch);
                        }
                        info._dataType = values[3];
                        scratch = StaticCast(uint32_t, stoul(values[4], &pos));
                        if (0 == pos)
                        {
                            info._found = false;
                        }
                        else
                        {
                            info._modes = StaticCast(nImO::TransportType, scratch);
                        }
                    }
                    else
                    {
                        ODL_LOG("! (4 < values.size())"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (0 < results.size())"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (Connection::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return RegChannelInfoOrFailure{status, info};
} // nImO::Registry::getChannelInformation

nImO::RegChannelInfoVectorOrFailure
nImO::Registry::getInformationForAllChannels
    (void)
    const
{
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    ChannelInfoVector   channelData;

    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchChannels{"SELECT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ "," CHANNEL_DATA_TYPE_C_
                                                   "," CHANNEL_MODES_C_ " FROM " CHANNELS_T_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                StringVector    values{results[ii]};

                if (4 < values.size())
                {
                    ChannelInfo info;
                    size_t      pos;
                    uint32_t    scratch;

                    info._found = true;
                    info._node = values[0];
                    info._path = values[1];
                    scratch = StaticCast(uint32_t, stoul(values[2], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    else
                    {
                        info._isOutput = (0 != scratch);
                    }
                    info._dataType = values[3];
                    scratch = StaticCast(uint32_t, stoul(values[4], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    else
                    {
                        info._modes = StaticCast(nImO::TransportType, scratch);
                    }
                    if (info._found)
                    {
                        channelData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (4 < values.size())"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return RegChannelInfoVectorOrFailure{status, channelData};
} // nImO::Registry::getInformationForAllChannels

nImO::RegChannelInfoVectorOrFailure
nImO::Registry::getInformationForAllChannelsOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    ChannelInfoVector   channelData;

    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchChannels{"SELECT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ "," CHANNEL_DATA_TYPE_C_
                                                    "," CHANNEL_MODES_C_ " FROM " CHANNELS_T_ "," NODES_T_ "," MACHINES_T_ " WHERE " NODES_T_ "."
                                                    NODE_NAME_C_ " = " CHANNELS_T_ "." CHANNEL_NODE_C_ " AND " MACHINES_T_ "." MACHINE_ADDRESS_C_
                                                    " = " NODES_T_ "." NODE_ADDRESS_C_ " AND " MACHINES_T_ "." MACHINE_NAME_C_ " = @" MACHINE_NAME_C_ };

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannelsMachineOnly,
                                                              &machineName);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                StringVector    values{results[ii]};

                if (4 < values.size())
                {
                    ChannelInfo info;
                    size_t      pos;
                    uint32_t    scratch;

                    info._found = true;
                    info._node = values[0];
                    info._path = values[1];
                    scratch = StaticCast(uint32_t, stoul(values[2], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    else
                    {
                        info._isOutput = (0 != scratch);
                    }
                    info._dataType = values[3];
                    scratch = StaticCast(uint32_t, stoul(values[4], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    else
                    {
                        info._modes = StaticCast(nImO::TransportType, scratch);
                    }
                    if (info._found)
                    {
                        channelData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (4 < values.size())"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
    ODL_OBJEXIT(); //####
    return RegChannelInfoVectorOrFailure{status, channelData};
} // nImO::Registry::getInformationForAllChannelsOnMachine

nImO::RegChannelInfoVectorOrFailure
nImO::Registry::getInformationForAllChannelsOnNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    ChannelInfoVector   channelData;

    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchChannels{"SELECT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ "," CHANNEL_DATA_TYPE_C_
                                                   "," CHANNEL_MODES_C_ " FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_ };

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannelsNodeOnly, &nodeName);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                StringVector    values{results[ii]};

                if (4 < values.size())
                {
                    ChannelInfo info;
                    size_t      pos;
                    uint32_t    scratch;

                    info._found = true;
                    info._node = values[0];
                    info._path = values[1];
                    scratch = StaticCast(uint32_t, stoul(values[2], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    else
                    {
                        info._isOutput = (0 != scratch);
                    }
                    info._dataType = values[3];
                    scratch = StaticCast(uint32_t, stoul(values[4], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    else
                    {
                        info._modes = StaticCast(nImO::TransportType, scratch);
                    }
                    if (info._found)
                    {
                        channelData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (4 < values.size())"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
    ODL_OBJEXIT(); //####
    return RegChannelInfoVectorOrFailure{status, channelData};
} // nImO::Registry::getInformationForAllChannelsOnNode

nImO::RegMachineInfoVectorOrFailure
nImO::Registry::getInformationForAllMachines
    (void)
    const
{
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    MachineInfoVector   machineData;

    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchMachines{"SELECT " MACHINE_NAME_C_ "," MACHINE_ADDRESS_C_ " FROM " MACHINES_T_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchMachines);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                StringVector    values{results[ii]};

                if (1 < values.size())
                {
                    MachineInfo info;
                    size_t      pos;

                    info._found = true;
                    info._name = values[0];
                    info._address = StaticCast(uint32_t, stoul(values[1], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    if (info._found)
                    {
                        machineData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (1 < values.size())"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return RegMachineInfoVectorOrFailure{status, machineData};
} // nImO::Registry::getInformationForAllMachines

nImO::RegNodeInfoVectorOrFailure
nImO::Registry::getInformationForAllNodes
    (void)
    const
{
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    NodeInfoVector      nodeData;

    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchNodes{"SELECT " NODE_NAME_C_ "," NODE_ADDRESS_C_ "," NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_ " FROM "
                                                NODES_T_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodes);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                StringVector    values{results[ii]};

                if (3 < values.size())
                {
                    NodeInfo    info;
                    size_t      pos;

                    info._found = true;
                    info._name = values[0];
                    info._connection._address = StaticCast(uint32_t, stoul(values[1], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    info._connection._port = StaticCast(uint16_t, stoul(values[2], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    info._serviceType = StaticCast(ServiceType, stoul(values[3], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    if (info._found)
                    {
                        nodeData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (3 < values.size())"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return RegNodeInfoVectorOrFailure{status, nodeData};
} // nImO::Registry::getInformationForAllNodes

nImO::RegNodeInfoVectorOrFailure
nImO::Registry::getInformationForAllNodesOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    NodeInfoVector      nodeData;

    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchNodesAndMachines{"SELECT " NODES_T_ "." NODE_NAME_C_ "," NODES_T_ "." NODE_ADDRESS_C_ "," NODE_PORT_C_ ","
                                                            NODE_SERVICE_TYPE_C_ " FROM " NODES_T_ ", " MACHINES_T_ " WHERE " MACHINES_T_ "."
                                                            MACHINE_NAME_C_ " = @" MACHINE_NAME_C_ " AND " MACHINES_T_ "." MACHINE_ADDRESS_C_
                                                            " = " NODES_T_ "." NODE_ADDRESS_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodesAndMachines, setupSearchMachines, &machineName);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                StringVector    values{results[ii]};

                if (3 < values.size())
                {
                    NodeInfo    info;
                    size_t      pos;

                    info._found = true;
                    info._name = values[0];
                    info._connection._address = StaticCast(uint32_t, stoul(values[1], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    info._connection._port = StaticCast(uint16_t, stoul(values[2], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    info._serviceType = StaticCast(ServiceType, stoul(values[3], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    if (info._found)
                    {
                        nodeData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (3 < values.size())"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return RegNodeInfoVectorOrFailure{status, nodeData};
} // nImO::Registry::getInformationForAllNodesOnMachine

nImO::RegLaunchDetailsOrFailure
nImO::Registry::getLaunchDetails
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status;
    LaunchDetails       details;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            std::vector<StringVector>   results;
            static CPtr(char)           searchNodes{"SELECT " NODE_EXEC_PATH_C_ "," NODE_LAUNCH_DIRECTORY_C_ "," NODE_COMMAND_LINE_C_ " FROM "
                                                    NODES_T_ " WHERE " NODE_NAME_C_ " = @" NODE_NAME_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodes, setupSearchNodes, &nodeName);
            if (status.first)
            {
                if (0 < results.size())
                {
                    StringVector    values{results[0]};

                    if (2 < values.size())
                    {
                        details._found = true;
                        details._execPath = values[0];
                        details._launchDirectory = values[1];
                        details._commandLine = values[2];
                    }
                    else
                    {
                        ODL_LOG("! (2 < values.size())"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (0 < results.size())"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return RegLaunchDetailsOrFailure{status, details};
} // nImO::Registry::getLaunchDetails

nImO::RegMachineInfoOrFailure
nImO::Registry::getMachineInformation
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status;
    MachineInfo         info;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            std::vector<StringVector>   results;
            static CPtr(char)           searchMachines{"SELECT " MACHINE_ADDRESS_C_ " FROM " MACHINES_T_ " WHERE " MACHINE_NAME_C_ " = @"
                                                        MACHINE_NAME_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchMachines, setupSearchMachines, &nodeName);
            if (status.first)
            {
                if (0 < results.size())
                {
                    StringVector    values{results[0]};

                    info._name = nodeName;
                    if (0 < values.size())
                    {
                        size_t  pos;

                        info._found = true;
                        info._address = StaticCast(uint32_t, stoul(values[0], &pos));
                        if (0 == pos)
                        {
                            info._found = false;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (0 < values.size())"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (0 < results.size())"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (Connection::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return RegMachineInfoOrFailure{status, info};
} // nImO::Registry::getMachineInformation

nImO::RegStringSetOrFailure
nImO::Registry::getNamesOfMachines
    (void)
    const
{
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    StringSet           strings;

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   searchMachines{"SELECT " MACHINE_NAME_C_ " FROM " MACHINES_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchMachines);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                strings.insert(results[ii]);
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return RegStringSetOrFailure{status, strings};
} // nImO::Registry::getNamesOfMachines

nImO::RegStringSetOrFailure
nImO::Registry::getNamesOfNodes
    (void)
    const
{
    ODL_OBJENTER(); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    StringSet           strings;

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   searchNodes{"SELECT " NODE_NAME_C_ " FROM " NODES_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchNodes);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                strings.insert(results[ii]);
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return RegStringSetOrFailure{status, strings};
} // nImO::Registry::getNamesOfNodes

nImO::RegStringSetOrFailure
nImO::Registry::getNamesOfNodesOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};
    StringSet           strings;

    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchNodesAndMachines{"SELECT " NODES_T_ "." NODE_NAME_C_ " FROM " NODES_T_ ", " MACHINES_T_ " WHERE "
                                                            MACHINES_T_ "." MACHINE_NAME_C_ " = @" MACHINE_NAME_C_ " AND " MACHINES_T_ "."
                                                            MACHINE_ADDRESS_C_ " = " NODES_T_ "." NODE_ADDRESS_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodesAndMachines, setupSearchMachines, &machineName);
        if (status.first)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                StringVector    values{results[ii]};

                if (0 < values.size())
                {
                    strings.insert(values[0]);
                }
                else
                {
                    ODL_LOG("! (0 < values.size())"); //####
                }
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return RegStringSetOrFailure{status, strings};
} // nImO::Registry::getNamesOfNodesOnMachine

nImO::RegNodeInfoOrFailure
nImO::Registry::getNodeInformation
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status;
    NodeInfo            info;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            std::vector<StringVector>   results;
            static CPtr(char)           searchNodes{"SELECT " NODE_ADDRESS_C_ "," NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_ " FROM " NODES_T_ " WHERE "
                                                    NODE_NAME_C_ " = @" NODE_NAME_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodes, setupSearchNodes, &nodeName);
            if (status.first)
            {
                if (0 < results.size())
                {
                    StringVector    values{results[0]};

                    info._name = nodeName;
                    if (2 < values.size())
                    {
                        size_t  pos;

                        info._found = true;
                        info._connection._address = StaticCast(uint32_t, stoul(values[0], &pos));
                        if (0 == pos)
                        {
                            info._found = false;
                        }
                        info._connection._port = StaticCast(uint16_t, stoul(values[1], &pos));
                        if (0 == pos)
                        {
                            info._found = false;
                        }
                        info._serviceType = StaticCast(ServiceType, stoul(values[2], &pos));
                        if (0 == pos)
                        {
                            info._found = false;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (2 < values.size())"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (0 < results.size())"); //####
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (Connection::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return RegNodeInfoOrFailure{status, info};
} // nImO::Registry::getNodeInformation

nImO::RegIntOrFailure
nImO::Registry::getNumberOfChannels
    (void)
    const
{
    ODL_OBJENTER(); //####
    int                 count{-1};
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   countMachines{"SELECT COUNT(*) FROM " CHANNELS_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, countMachines);
        if (status.first)
        {
            size_t  pos;

            count = stoi(results[0], &pos);
            if (0 == pos)
            {
                count = -1;
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
   ODL_OBJEXIT(); //####
    return RegIntOrFailure{status, count};
} // nImO::Registry::getNumberOfChannels

nImO::RegIntOrFailure
nImO::Registry::getNumberOfChannelsOnNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    int                 count{-1};
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   countChannels{"SELECT COUNT(*) FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, countChannels, setupCountChannels, &nodeName);
        if (status.first)
        {
            size_t  pos;

            count = stoi(results[0], &pos);
            if (0 == pos)
            {
                count = -1;
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
   ODL_OBJEXIT(); //####
    return RegIntOrFailure{status, count};
} // nImO::Registry::getNumberOfChannelsOnNode

nImO::RegIntOrFailure
nImO::Registry::getNumberOfMachines
    (void)
    const
{
    ODL_OBJENTER(); //####
    int                 count{-1};
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   countMachines{"SELECT COUNT(*) FROM " MACHINES_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, countMachines);
        if (status.first)
        {
            size_t  pos;

            count = stoi(results[0], &pos);
            if (0 == pos)
            {
                count = -1;
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
   ODL_OBJEXIT(); //####
    return RegIntOrFailure{status, count};
} // nImO::Registry::getNumberOfMachines

nImO::RegIntOrFailure
nImO::Registry::getNumberOfNodes
    (void)
    const
{
    ODL_OBJENTER(); //####
    int                 count{-1};
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   countNodes{"SELECT COUNT(*) FROM " NODES_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, countNodes);
        if (status.first)
        {
            size_t  pos;

            count = stoi(results[0], &pos);
            if (0 == pos)
            {
                count = -1;
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
   ODL_OBJEXIT(); //####
    return RegIntOrFailure{status, count};
} // nImO::Registry::getNumberOfNodes

nImO::RegIntOrFailure
nImO::Registry::getNumberOfNodesOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    int                 count{-1};
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   searchMachines{"SELECT COUNT(*) FROM " NODES_T_ ", " MACHINES_T_ " WHERE " MACHINES_T_ "." MACHINE_NAME_C_ " = @"
                                            MACHINE_NAME_C_ " AND " MACHINES_T_ "." MACHINE_ADDRESS_C_ " = " NODES_T_ "." NODE_ADDRESS_C_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchMachines, setupSearchMachines, &machineName);
        if (status.first)
        {
            size_t  pos;

            count = stoi(results[0], &pos);
            if (0 == pos)
            {
                count = -1;
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
   ODL_OBJEXIT(); //####
    return RegIntOrFailure{status, count};
} // nImO::Registry::getNumberOfNodesOnMachine

nImO::RegBoolOrFailure
nImO::Registry::isChannelPresent
    (const std::string &    nodeName,
     const std::string &    channelPath)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "channelPath = ", channelPath); //####
    bool                found{false};
    RegSuccessOrFailure status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StringVector        results;
            ChannelSearchData   data{nodeName, channelPath};
            static CPtr(char)   searchChannels{"SELECT COUNT(*) FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_ " AND "
                                                CHANNEL_PATH_C_ " = @" CHANNEL_PATH_C_};

            status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannels, &data);
            if (status.first)
            {
                size_t  pos;
                int     count = stoi(results[0], &pos);

                if (0 == pos)
                {
                    found = false;
                }
                else
                {
                    found = (1 == count);
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (Connection::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return RegBoolOrFailure{status, found};
} // nImO::Registry::isChannelPresent

nImO::RegBoolOrFailure
nImO::Registry::isMachinePresent
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    bool                found{false};
    RegSuccessOrFailure status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   searchMachines{"SELECT COUNT(*) FROM " MACHINES_T_ " WHERE " MACHINE_NAME_C_ " = @" MACHINE_NAME_C_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchMachines, setupSearchMachines, &machineName);
        if (status.first)
        {
            size_t  pos;
            int     count = stoi(results[0], &pos);

            if (0 == pos)
            {
                found = false;
            }
            else
            {
                found = (1 == count);
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
    ODL_OBJEXIT(); //####
    return RegBoolOrFailure{status, found};
} // nImO::Registry::isMachinePresent

nImO::RegBoolOrFailure
nImO::Registry::isNodePresent
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    bool                found{false};
    RegSuccessOrFailure status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StringVector        results;
            static CPtr(char)   searchNodes{"SELECT COUNT(*) FROM " NODES_T_ " WHERE " NODE_NAME_C_ " = @" NODE_NAME_C_};

            status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchNodes, setupSearchNodes, &nodeName);
            if (status.first)
            {
                size_t  pos;
                int     count = stoi(results[0], &pos);

                if (0 == pos)
                {
                    found = false;
                }
                else
                {
                    found = (1 == count);
                }
            }
            else
            {
                ODL_LOG("! (status.first)"); //####
            }
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return RegBoolOrFailure{status, found};
} // nImO::Registry::isNodePresent

nImO::RegSuccessOrFailure
nImO::Registry::removeChannel
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            ChannelSearchData   data{nodeName, path};
            static CPtr(char)   searchChannels{"DELETE FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_ " AND " CHANNEL_PATH_C_
                                                " = @" CHANNEL_PATH_C_};

            status = performSQLstatementWithNoResults(_owner, _dbHandle, searchChannels, setupSearchChannels, &data);
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeChannel

nImO::RegSuccessOrFailure
nImO::Registry::removeChannelsForNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            static CPtr(char)   searchChannels{"DELETE FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_};

            status = performSQLstatementWithNoResults(_owner, _dbHandle, searchChannels, setupSearchChannelsNodeOnly, &nodeName);
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeChannelsForNode

nImO::RegSuccessOrFailure
nImO::Registry::removeNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    RegSuccessOrFailure status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            static CPtr(char)   searchNodes{"DELETE FROM " NODES_T_ " WHERE " NODE_NAME_C_ " = @" NODE_NAME_C_};

            status = performSQLstatementWithNoResults(_owner, _dbHandle, searchNodes, setupSearchNodes, &nodeName);
            doEndTransaction(_owner, _dbHandle, status.first);
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName))"); //####
        status = RegSuccessOrFailure(false, "Invalid node name");
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeNode

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

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

/*! @brief The name of the 'Applications' table. */
#define APPLICATIONS_T_ "Applications"

/*! @brief The named parameter for the 'launcherName' column of the 'Applications' table. */
#define APPLICATIONS_LAUNCHER_NAME_C_ "launcherName"

/*! @brief The named parameter for the 'appName' column of the 'Applications' table. */
#define APPLICATIONS_APP_NAME_C_ "appName"

/*! @brief The named parameter for the 'appDescription' column of the 'Applications' table. */
#define APPLICATIONS_APP_DESCR_C_ "appDescription"

/*! @brief The name of the index for the 'launcherName' and 'appName' columns of the 'Applications' table. */
#define APPLICATIONS_I_ "Applications_idx"

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
#define CHANNEL_NODE_C_ "node"

/*! @brief The named parameter for the 'path' column of the 'Channels' table. */
#define CHANNEL_PATH_C_ "path"

/*! @brief The named parameter for the 'isOutput' column of the 'Channels' table. */
#define CHANNEL_IS_OUTPUT_C_    "isOutput"

/*! @brief The named parameter for the 'dataType' column of the 'Channels' table. */
#define CHANNEL_DATA_TYPE_C_    "dataType"

/*! @brief The named parameter for the 'modes' column of the 'Channels' table. */
#define CHANNEL_MODES_C_    "modes"

/*! @brief The named parameter for the 'inUse' column of the 'Channels' table. */
#define CHANNEL_IN_USE_C_   "inUse"

/*! @brief The name of the index for the 'node' and 'path' columns of the 'Channels' table. */
#define CHANNELS_I_ "Channels_idx"

/*! @brief The name of the 'Connections' table. */
#define CONNECTIONS_T_  "Connections"

/*! @brief The named parameter for the 'fromNode' column of the 'Connecions' table. */
#define CONNECTION_FROM_NODE_C_ "fromNode"

/*! @brief The named parameter for the 'fromPath' column of the 'Connections' table. */
#define CONNECTION_FROM_PATH_C_ "fromPath"

/*! @brief The named parameter for the 'toNode' column of the 'Connecions' table. */
#define CONNECTION_TO_NODE_C_   "toNode"

/*! @brief The named parameter for the 'toPath' column of the 'Connections' table. */
#define CONNECTION_TO_PATH_C_   "toPath"

/*! @brief The named parameter for the 'dataType' column of the 'Connections' table. */
#define CONNECTION_DATA_TYPE_C_ "dataType"

/*! @brief The named parameter for the 'mode' column of the 'Connections' table. */
#define CONNECTION_MODE_C_  "mode"

/*! @brief The name of the index for the 'fromNode', 'fromPath', 'toNode' and 'toPath' columns of the 'Connections' table. */
#define CONNECTIONS_I_ "Connections_idx"

/*! @brief A function that provides bindings for parameters in an SQL statement.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
using BindFunction = int (*)
   (Ptr(sqlite3_stmt)  statement,
    CPtr(void)         stuff);

/*! @brief The data used to update the Applications table. */
struct ApplicationInsertData
{
    /*! @brief The Launcher node for this application. */
    std::string _launcherName;

    /*! @brief The name for this application. */
    std::string _appName;

    /*! @brief The description for this application. */
    std::string _appDescription;

    /*! @brief The constructor.
     @param[in] launcherName The name of the Launcher node for the application.
     @param[in] appName The application name.
     @param[in] appDescription The application description. */
    inline ApplicationInsertData
        (const std::string &    launcherName,
         const std::string &    appName,
         const std::string &    appDescription) :
            _launcherName(launcherName), _appName(appName), _appDescription(appDescription)
    {
    }

}; // ApplicationInsertData

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

/*! @brief The data used to update the Connections table. */
struct ConnectionInsertData
{
    /*! @brief The input node for this connection. */
    std::string _fromNode;

    /*! @brief The input path for this connection. */
    std::string _fromPath;

    /*! @brief The output node for this connection. */
    std::string _toNode;

    /*! @brief The output path for this connection. */
    std::string _toPath;

    /*! @brief The format of the data to be transferred over this connection. */
    std::string _dataType;

    /*! @brief The transport types for the connection. */
    nImO::TransportType   _mode;

    /*! @brief The constructor.
     @param[in] fromNode The name of the input node for the connection.
     @param[in] fromPath The input path for the connection.
     @param[in] toNode The name of the output node for the connection.
     @param[in] toPath The output path for the connection.
     @param[in] dataType The format for the data to be transferred over the connection.
     @param[in] mode The transport type for the connection. */
    inline ConnectionInsertData
        (const std::string &        fromNode,
         const std::string &        fromPath,
         const std::string &        toNode,
         const std::string &        toPath,
         const std::string &        dataType,
         const nImO::TransportType  mode) :
            _fromNode(fromNode), _fromPath(fromPath), _toNode(toNode), _toPath(toPath), _dataType(dataType), _mode(mode)
    {
    }

}; // ConnectionInsertData

/*! @brief The data used to search the Connections table. */
struct ConnectionSearchData
{
    /*! @brief The input node for this connection. */
    std::string _node;

    /*! @brief The input path for this connection. */
    std::string _path;

    /*! @brief The constructor.
     @param[in] node The name of the input or output node for the connection.
     @param[in] path The input or output path for the connection. */
    inline ConnectionSearchData
        (const std::string &    node,
         const std::string &    path) :
            _node(node), _path(path)
    {
    }

}; // ConnectionSearchData

/*! @brief The data used to update the Machines table. */
struct MachineInsertData
{
    /*! @brief The name of this machine. */
    std::string _name;

    /*! @brief The IP address for this machine.*/
    nImO::IPv4Address   _address;

    /*! @brief The constructor.
     @param[in] name The name of this node.
     @param[in] connection The command IP address and port for this node.
     @param[in] serviceType The type of service provided by this node. */
    inline MachineInsertData
        (const std::string &        name,
         const nImO::IPv4Address    address) :
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
static nImO::SuccessOrFailure
performSQLstatementWithMultipleColumnResults
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     nImO::StdStringVectorVector &  results,
     CPtr(char)                     sqlStatement,
     BindFunction                   doBinds = nullptr,
     CPtr(void)                     data = nullptr)
{
    ODL_ENTER(); //####
    ODL_P4("owner = ", owner.get(), "dbHandle = ", dbHandle, "results = ", &results, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    ODL_B1("(nullptr != doBinds) = ", nullptr != doBinds); //####
    nImO::SuccessOrFailure  status{true, ""s};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::SuccessOrFailure{false, "No open database"s};
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
                        status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
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
                                nImO::StdStringVector   thisRow;

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
                        status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
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
static nImO::SuccessOrFailure
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
    nImO::SuccessOrFailure  status{true, ""s};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::SuccessOrFailure{false, "No open database"s};
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
                        status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
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
                        status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && prepared)"); //####
                status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
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
static nImO::SuccessOrFailure
performSQLstatementWithNoResultsNoArgs
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     CPtr(char)                     sqlStatement)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    nImO::SuccessOrFailure  status{true, ""s};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::SuccessOrFailure{false, "No open database"s};
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
                    status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
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
static nImO::SuccessOrFailure
performSQLstatementWithSingleColumnResults
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     nImO::StdStringVector &        resultList,
     CPtr(char)                     sqlStatement,
     BindFunction                   doBinds = nullptr,
     CPtr(void)                     data = nullptr)
{
    ODL_ENTER(); //####
    ODL_P4("owner = ", owner.get(), "dbHandle = ", dbHandle, "resultList = ", &resultList, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    ODL_B1("(nullptr != doBinds) = ", nullptr != doBinds); //####
    nImO::SuccessOrFailure  status{true, ""s};

    resultList.clear();
    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::SuccessOrFailure{false, "No open database"s};
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
                        status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
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
                        status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                status = nImO::SuccessOrFailure{false, sqlite3_errstr(sqlRes)};
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
static nImO::SuccessOrFailure
doBeginTransaction
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    nImO::SuccessOrFailure  status{true, ""s};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::SuccessOrFailure{false, "No open database"s};
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
static nImO::SuccessOrFailure
doEndTransaction
    (nImO::SpContextWithNetworking  owner,
     Ptr(sqlite3)                   dbHandle,
     const bool                     wasOK)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_B1("wasOK = ", wasOK); //####
    nImO::SuccessOrFailure  status{true, ""s};

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::SuccessOrFailure{false, "No open database"s};
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
static nImO::SuccessOrFailure
createTables
    (nImO::SpContextWithNetworking  owner,
     const bool                     logging,
     Ptr(sqlite3)                   dbHandle)
{
    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_B1("logging = ", logging); //####
    nImO::SuccessOrFailure  status{true, ""s};

    if (nullptr == dbHandle)
    {
        ODL_LOG("(nullptr == dbHandle)"); //####
        status = nImO::SuccessOrFailure{false, "No open database"s};
    }
    else
    {
        if ((nullptr != owner) && logging)
        {
            owner->report("creating tables."s);
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
                "CREATE TABLE IF NOT EXISTS " CHANNELS_T_ " (" CHANNEL_NODE_C_ " " TEXTNOTNULL_ " " NOCASE_ ", " CHANNEL_PATH_C_ " " TEXTNOTNULL_
                        " " BINARY_ ", " CHANNEL_IS_OUTPUT_C_ " INTEGER, " CHANNEL_DATA_TYPE_C_ " TEXT DEFAULT _ " BINARY_ ", " CHANNEL_MODES_C_
                        " INTEGER, " CHANNEL_IN_USE_C_ " INTEGER DEFAULT 0, FOREIGN KEY (" CHANNEL_NODE_C_ ") REFERENCES " NODES_T_ " ("
                        NODE_NAME_C_ "), PRIMARY KEY (" CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ ") ON CONFLICT ABORT)",
                "CREATE INDEX IF NOT EXISTS " CHANNELS_I_ " ON " CHANNELS_T_ " (" CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ ")",
                "CREATE TABLE IF NOT EXISTS " CONNECTIONS_T_ " (" CONNECTION_FROM_NODE_C_ " " TEXTNOTNULL_ " " NOCASE_ ", " CONNECTION_FROM_PATH_C_
                        " " TEXTNOTNULL_ " " BINARY_ ", " CONNECTION_TO_NODE_C_ " " TEXTNOTNULL_ " " NOCASE_ ", " CONNECTION_TO_PATH_C_ " "
                        TEXTNOTNULL_ " " BINARY_ ", " CONNECTION_DATA_TYPE_C_ " TEXT DEFAULT _ " BINARY_ ", " CONNECTION_MODE_C_
                        " INTEGER, FOREIGN KEY (" CONNECTION_FROM_NODE_C_ ", " CONNECTION_FROM_PATH_C_ ") REFERENCES " CHANNELS_T_ " ("
                        CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ "), FOREIGN KEY (" CONNECTION_TO_NODE_C_ ", " CONNECTION_TO_PATH_C_ ") REFERENCES "
                        CHANNELS_T_ " (" CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ "), PRIMARY KEY (" CONNECTION_FROM_NODE_C_ ", "
                        CONNECTION_FROM_PATH_C_ ", " CONNECTION_TO_NODE_C_ ", " CONNECTION_TO_PATH_C_ ") ON CONFLICT ABORT)",
                "CREATE INDEX IF NOT EXISTS " CONNECTIONS_I_ " ON " CONNECTIONS_T_ " (" CONNECTION_FROM_NODE_C_ ", " CONNECTION_FROM_PATH_C_ ", "
                            CONNECTION_TO_NODE_C_ ", " CONNECTION_TO_PATH_C_ ")",
                "CREATE TABLE IF NOT EXISTS " APPLICATIONS_T_ " (" APPLICATIONS_LAUNCHER_NAME_C_ " " TEXTNOTNULL_ " " NOCASE_ ", " APPLICATIONS_APP_NAME_C_ " " TEXTNOTNULL_ " " NOCASE_ ", " APPLICATIONS_APP_DESCR_C_ " " TEXTNOTNULL_ " " BINARY_
                    ", FOREIGN KEY (" APPLICATIONS_LAUNCHER_NAME_C_ ") REFERENCES " NODES_T_ " (" NODE_NAME_C_ "), PRIMARY KEY ("
                    APPLICATIONS_LAUNCHER_NAME_C_ ", " APPLICATIONS_APP_NAME_C_ ") ON CONFLICT ABORT)",
                "CREATE INDEX IF NOT EXISTS " APPLICATIONS_I_ " ON " APPLICATIONS_T_ " (" APPLICATIONS_LAUNCHER_NAME_C_ ", "
                    APPLICATIONS_APP_NAME_C_ ")"
            };
            constexpr size_t    numTables{numElementsInArray(tableSQL)};

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

/*! @brief Bind the value that is to be searched for in the Applications table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupCountApplications
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int nodeNameIndex{sqlite3_bind_parameter_index(statement, "@" APPLICATIONS_LAUNCHER_NAME_C_)};

        if (0 < nodeNameIndex)
        {
            auto    name{*StaticCast(CPtr(std::string), stuff)};

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
} // setupCountApplications

/*! @brief Bind the value that is to be searched for in the Channels table.
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
            auto    name{*StaticCast(CPtr(std::string), stuff)};

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
setupInsertIntoApplications
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int launcherNameIndex{sqlite3_bind_parameter_index(statement, "@" APPLICATIONS_LAUNCHER_NAME_C_)};
        int appNameIndex{sqlite3_bind_parameter_index(statement, "@" APPLICATIONS_APP_NAME_C_)};
        int appDescrIndex{sqlite3_bind_parameter_index(statement, "@" APPLICATIONS_APP_DESCR_C_)};

        if ((0 < launcherNameIndex) && (0 < appNameIndex) && (0 < appDescrIndex))
        {
            auto    appData{StaticCast(CPtr(ApplicationInsertData), stuff)};
            auto    launcherName{appData->_launcherName};
            auto    appName{appData->_appName};
            auto    appDescr{appData->_appDescription};

            result = sqlite3_bind_text(statement, launcherNameIndex, launcherName.c_str(), StaticCast(int, launcherName.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, appNameIndex, appName.c_str(), StaticCast(int, appName.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, appDescrIndex, appDescr.c_str(), StaticCast(int, appDescr.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < launcherNameIndex) && (0 < appNameIndex) && (0 < appDescrIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupInsertIntoApplications

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
            auto    channelData{StaticCast(CPtr(ChannelInsertData), stuff)};
            auto    node{channelData->_node};
            auto    path{channelData->_path};
            bool    isOutput{channelData->_isOutput};
            auto    dataType{channelData->_dataType};
            auto    modes{channelData->_modes};

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
            ODL_LOG("! ((0 < nodeNameIndex) && (0 < pathIndex) && (0 < isOutputIndex) && (0 < dataTypeIndex) && (0 < modesIndex))"); //####
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

/*! @brief Bind the values that are to be inserted into the Connections table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupInsertIntoConnections
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int fromNodeNameIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_FROM_NODE_C_)};
        int fromPathIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_FROM_PATH_C_)};
        int toNodeNameIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_TO_NODE_C_)};
        int toPathIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_TO_PATH_C_)};
        int dataTypeIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_DATA_TYPE_C_)};
        int modeIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_MODE_C_)};

        if ((0 < fromNodeNameIndex) && (0 < fromPathIndex) && (0 < toNodeNameIndex) && (0 < toPathIndex) && (0 < dataTypeIndex) && (0 < modeIndex))
        {
            auto    connectionData{StaticCast(CPtr(ConnectionInsertData), stuff)};
            auto    fromNode{connectionData->_fromNode};
            auto    fromPath{connectionData->_fromPath};
            auto    toNode{connectionData->_toNode};
            auto    toPath{connectionData->_toPath};
            auto    dataType{connectionData->_dataType};
            auto    mode{connectionData->_mode};

            result = sqlite3_bind_text(statement, fromNodeNameIndex, fromNode.c_str(), StaticCast(int, fromNode.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, fromPathIndex, fromPath.c_str(), StaticCast(int, fromPath.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, toNodeNameIndex, toNode.c_str(), StaticCast(int, toNode.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, toPathIndex, toPath.c_str(), StaticCast(int, toPath.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, dataTypeIndex, dataType.c_str(), StaticCast(int, dataType.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, modeIndex, StaticCast(int, mode));
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < fromNodeNameIndex) && (0 < fromPathIndex) && (0 < toNodeNameIndex) && (0 < toPathIndex) && " //####
                    "(0 < dataTypeIndex) && (0 < modeIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupInsertIntoConnections

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
            auto    machineData{StaticCast(CPtr(MachineInsertData), stuff)};
            auto    name{machineData->_name};
            auto    address{machineData->_address};

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
            auto    nodeData{StaticCast(CPtr(NodeInsertData), stuff)};
            auto    name{nodeData->_name};
            auto    execPath{nodeData->_execPath};
            auto    launchDirectory{nodeData->_launchDirectory};
            auto    commandLine{nodeData->_commandLine};

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

/*! @brief Bind the value that is to be searched for in the Applications table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchApplicationsNodeOnly
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int nodeNameIndex{sqlite3_bind_parameter_index(statement, "@" APPLICATIONS_LAUNCHER_NAME_C_)};

        if (0 < nodeNameIndex)
        {
            auto    node{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, nodeNameIndex, node.c_str(), StaticCast(int, node.length()), SQLITE_TRANSIENT);
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
} // setupSearchApplicationsNodeOnly

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
            auto    channelSearch{StaticCast(CPtr(ChannelSearchData), stuff)};
            auto    node{channelSearch->_node};
            auto    path{channelSearch->_path};

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
            ODL_LOG("! ((0 < channelNodeIndex) && (0 < channelPathIndex))"); //####
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
            auto    machine{*StaticCast(CPtr(std::string), stuff)};

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
            auto    node{*StaticCast(CPtr(std::string), stuff)};

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

/*! @brief Bind the values that are to be searched for in the Connections table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchConnectionsViaFrom
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int fromNodeIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_FROM_NODE_C_)};
        int fromPathIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_FROM_PATH_C_)};

        if ((0 < fromNodeIndex) && (0 < fromPathIndex))
        {
            auto    connectionSearch{StaticCast(CPtr(ConnectionSearchData), stuff)};
            auto    node{connectionSearch->_node};
            auto    path{connectionSearch->_path};

            result = sqlite3_bind_text(statement, fromNodeIndex, node.c_str(), StaticCast(int, node.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, fromPathIndex, path.c_str(), StaticCast(int, path.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < fromNodeIndex) && (0 < fromPathIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchConnectionsViaFrom

/*! @brief Bind the values that are to be searched for in the Connections table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchConnectionsViaTo
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int toNodeIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_TO_NODE_C_)};
        int toPathIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_TO_PATH_C_)};

        if ((0 < toNodeIndex) && (0 < toPathIndex))
        {
            auto    connectionSearch{StaticCast(CPtr(ConnectionSearchData), stuff)};
            auto    node{connectionSearch->_node};
            auto    path{connectionSearch->_path};

            result = sqlite3_bind_text(statement, toNodeIndex, node.c_str(), StaticCast(int, node.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, toPathIndex, path.c_str(), StaticCast(int, path.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < toNodeIndex) && (0 < fromPathIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchConnectionsViaTo

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
            auto    name{*StaticCast(CPtr(std::string), stuff)};

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
setupSearchNodeConnections
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int fromNodeIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_FROM_NODE_C_)};
        int toNodeIndex{sqlite3_bind_parameter_index(statement, "@" CONNECTION_TO_NODE_C_)};

        if ((0 < fromNodeIndex) && (0 < toNodeIndex))
        {
            auto    name{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, fromNodeIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_text(statement, toNodeIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < fromNodeIndex) && (0 < toNodeIndex))"); //####
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_I(result);
    return result;
} // setupSearchNodeConnections

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
            auto    name{*StaticCast(CPtr(std::string), stuff)};

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

/*! @brief Bind the value that is to be searched for in the Applications table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchNodesForApplication
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result{SQLITE_MISUSE};

    try
    {
        int appNameIndex{sqlite3_bind_parameter_index(statement, "@" APPLICATIONS_APP_NAME_C_)};

        if (0 < appNameIndex)
        {
            auto    appName{*StaticCast(CPtr(std::string), stuff)};

            result = sqlite3_bind_text(statement, appNameIndex, appName.c_str(), StaticCast(int, appName.length()), SQLITE_TRANSIENT);
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
} // setupSearchNodesForApplication

/*! @brief Extract the fields for the application information from the strings retrieved from the table.
 @param[out] info The data corresponding to the retrieved strings.
 @param[in] values The retrieved strings. */
static void
extractApplicationInfoFromVector
    (nImO::ApplicationInfo &        info,
     const nImO::StdStringVector &  values)
{
    ODL_ENTER(); //####
    ODL_P1("info = ", &info); //####
    if (2 < values.size())
    {
        info._found = true;
        info._launcherName = values[0];
        info._appName = values[1];
        info._appDescription = values[2];
    }
    else
    {
        info._found = false;
        ODL_LOG("! (2 < values.size())"); //####
    }
    ODL_EXIT(); //####
} // extractApplicationInfoFromVector

/*! @brief Extract the fields for the channel information from the strings retrieved from the table.
 @param[out] info The data corresponding to the retrieved strings.
 @param[in] values The retrieved strings. */
static void
extractChannelInfoFromVector
    (nImO::ChannelInfo &            info,
     const nImO::StdStringVector &  values)
{
    ODL_ENTER(); //####
    ODL_P1("info = ", &info); //####
    if (5 < values.size())
    {
        size_t  pos;
        int     scratch;

        info._found = true;
        info._node = values[0];
        info._path = values[1];
        scratch = StaticCast(int, stoul(values[2], &pos));
        if (0 == pos)
        {
            info._found = false;
        }
        else
        {
            info._isOutput = (0 != scratch);
        }
        info._dataType = values[3];
        scratch = StaticCast(int, stoul(values[4], &pos));
        if (0 == pos)
        {
            info._found = false;
        }
        else
        {
            info._modes = StaticCast(nImO::TransportType, scratch);
        }
        scratch = StaticCast(int, stoul(values[5], &pos));
        if (0 == pos)
        {
            info._found = false;
        }
        else
        {
            info._inUse = (0 != scratch);
        }
    }
    else
    {
        info._found = false;
        ODL_LOG("! (5 < values.size())"); //####
    }
    ODL_EXIT(); //####
} // extractChannelInfoFromVector

/*! @brief Extract the fields for the node information from the strings retrieved from the table.
 @param[out] info The data corresponding to the retrieved strings.
 @param[in] values The retrieved strings. */
static void
extractNodeInfoFromVector
    (nImO::NodeInfo &               info,
     const nImO::StdStringVector &  values)
{
    ODL_ENTER(); //####
    ODL_P1("info = ", &info); //####
    if (3 < values.size())
    {
        size_t  pos;

        info._found = true;
        info._name = values[0];
        info._connection._address = StaticCast(nImO::IPv4Address, stoul(values[1], &pos));
        if (0 == pos)
        {
            info._found = false;
        }
        info._connection._port = StaticCast(nImO::IPv4Port, stoul(values[2], &pos));
        if (0 == pos)
        {
            info._found = false;
        }
        info._serviceType = StaticCast(nImO::ServiceType, stoul(values[3], &pos));
        if (0 == pos)
        {
            info._found = false;
        }
    }
    else
    {
        ODL_LOG("! (3 < values.size())"); //####
    }
    ODL_EXIT(); //####
} // extractNodeInfoFromVector

#if defined(__APPLE__)
# pragma mark Class methods
#endif // defined(__APPLE__)

#if defined(__APPLE__)
# pragma mark Constructors and Destructors
#endif // defined(__APPLE__)

nImO::Registry::Registry
    (SpContextWithNetworking    owner,
     const bool                 logging) :
        _owner{owner}
{
    ODL_ENTER(); //####
    ODL_P1("owner = ", owner.get()); //####
    ODL_B1("logging = ", logging); //####
    if (logging && (nullptr != _owner))
    {
        sqlite3_config(SQLITE_CONFIG_LOG, sqlLogger, _owner.get());
    }
    int result{sqlite3_open_v2("nImO_registry", &_dbHandle,
                            SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY | SQLITE_OPEN_PRIVATECACHE,
                               nullptr)};

    if (SQLITE_OK == result)
    {
        auto    status{createTables(_owner, logging, _dbHandle)};

        if (! status.first)
        {
            auto    prefix{"Problem creating tables in database: "s};

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
        auto        prefix{"Unable to open database: "s};

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

nImO::SuccessOrFailure
nImO::Registry::addAppToList
    (const std::string &    nodeName,
     const std::string &    applicationName,
     const std::string &    applicationDescription)
    const
{
    ODL_OBJENTER(); //####
    ODL_S3s("nodeName = ", nodeName, "applicationName = ", applicationName, "applicationDescription = ", applicationDescription); //####
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && (! applicationName.empty()) && (! applicationDescription.empty()))
    {
        auto    statusWithNodeInfo{getNodeInformation(nodeName)};

        if (statusWithNodeInfo.first.first)
        {
            if (statusWithNodeInfo.second._found)
            {
                if (ServiceType::LauncherService == statusWithNodeInfo.second._serviceType)
                {
                    status = doBeginTransaction(_owner, _dbHandle);
                    if (status.first)
                    {
                        ApplicationInsertData   data{nodeName, applicationName, applicationDescription};
                        static CPtr(char)       insertIntoApplications{"INSERT INTO " APPLICATIONS_T_ " (" APPLICATIONS_LAUNCHER_NAME_C_ ", "
                                                                        APPLICATIONS_APP_NAME_C_ ", " APPLICATIONS_APP_DESCR_C_ ") VALUES (@"
                                                                        APPLICATIONS_LAUNCHER_NAME_C_ ", @" APPLICATIONS_APP_NAME_C_ ", @"
                                                                        APPLICATIONS_APP_DESCR_C_ ")"};

                        status = performSQLstatementWithNoResults(_owner, _dbHandle, insertIntoApplications, setupInsertIntoApplications, &data);
                        doEndTransaction(_owner, _dbHandle, status.first);
                    }
                    else
                    {
                        ODL_LOG("! (status.first)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (ServiceType::LauncherService == statusWithNodeInfo.second._serviceType)"); //####
                    status = SuccessOrFailure(false, "Only Launcher services can add applications"s);
                }
            }
            else
            {
                ODL_LOG("! (statusWithNodeInfo.second._found)"); //####
                status = SuccessOrFailure(false, "Unknown node name"s);
            }
        }
        else
        {
            ODL_LOG("! (statusWithNodeInfo.first.first)"); //####
            status = SuccessOrFailure(false, "Problem with 'getNodeInformation': "s + statusWithNodeInfo.first.second);
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validName(nodeName) && (! applicationName.empty()) && (! applicationDescription.empty()))"); //####
        status = SuccessOrFailure(false, "Invalid node name or empty application name or description"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addAppToList

nImO::SuccessOrFailure
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
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        auto    statusWithBool{isNodePresent(nodeName)};

        if (statusWithBool.first.first)
        {
            if (statusWithBool.second)
            {
                status = doBeginTransaction(_owner, _dbHandle);
                if (status.first)
                {
                    ChannelInsertData   data{nodeName, path, isOutput, dataType, modes};
                    static CPtr(char)   insertIntoChannels{"INSERT INTO " CHANNELS_T_ " (" CHANNEL_NODE_C_ ", " CHANNEL_PATH_C_ ", "
                                                            CHANNEL_IS_OUTPUT_C_ ", " CHANNEL_DATA_TYPE_C_ ", " CHANNEL_MODES_C_ ") VALUES (@"
                                                            CHANNEL_NODE_C_ ", @" CHANNEL_PATH_C_ ", @"
                                                            CHANNEL_IS_OUTPUT_C_ ", @" CHANNEL_DATA_TYPE_C_ ", @" CHANNEL_MODES_C_ ")"};

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
                status = SuccessOrFailure(false, "Unknown node name"s);
            }
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addChannel

nImO::SuccessOrFailure
nImO::Registry::addConnection
    (const std::string &    fromNodeName,
     const std::string &    fromPath,
     const std::string &    toNodeName,
     const std::string &    toPath,
     const std::string &    dataType,
     const TransportType    mode)
    const
{
    ODL_OBJENTER(); //####
    ODL_S4s("fromNodeName = ", fromNodeName, "fromPath = ", fromPath, "toNodeName = ", toNodeName, "toPath = ", toPath); //####
    ODL_S1s("dataType = ", dataType); //####
    ODL_I1("mode = ", StaticCast(int, mode)); //####
    SuccessOrFailure    status;

    if (ChannelName::validNode(fromNodeName) && ChannelName::validPath(fromPath) && ChannelName::validNode(toNodeName) &&
        ChannelName::validPath(toPath))
    {
        auto    statusWithBool{isChannelPresent(fromNodeName, fromPath)};

        if (statusWithBool.first.first)
        {
            if (statusWithBool.second)
            {
                statusWithBool = isChannelPresent(toNodeName, toPath);
                if (statusWithBool.first.first)
                {
                    if (statusWithBool.second)
                    {
                        status = doBeginTransaction(_owner, _dbHandle);
                        if (status.first)
                        {
                            ConnectionInsertData    data{fromNodeName, fromPath, toNodeName, toPath, dataType, mode};
                            static CPtr(char)       insertIntoConnections{"INSERT INTO " CONNECTIONS_T_ " (" CONNECTION_FROM_NODE_C_ ", "
                                                                            CONNECTION_FROM_PATH_C_ ", " CONNECTION_TO_NODE_C_ ", "
                                                                            CONNECTION_TO_PATH_C_ ", " CONNECTION_DATA_TYPE_C_ ", "
                                                                            CONNECTION_MODE_C_ ") VALUES (@" CONNECTION_FROM_NODE_C_ ", @"
                                                                            CONNECTION_FROM_PATH_C_ ", @" CONNECTION_TO_NODE_C_ ", @"
                                                                            CONNECTION_TO_PATH_C_ ", @" CONNECTION_DATA_TYPE_C_ ", @"
                                                                            CONNECTION_MODE_C_ ")"};

                            status = performSQLstatementWithNoResults(_owner, _dbHandle, insertIntoConnections, setupInsertIntoConnections, &data);
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
                        status = SuccessOrFailure(false, "Unknown 'to' channel"s);
                    }
                }
            }
            else
            {
                ODL_LOG("! (statusWithBool.second)"); //####
                status = SuccessOrFailure(false, "Unknown 'from' channel"s);
            }
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(fromNodeName) && ChannelName::validPath(fromPath) && " //####
                "ChannelName::validNode(toNodeName) && ChannelName::validPath(toPath))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addConnection

nImO::SuccessOrFailure
nImO::Registry::addMachine
    (const std::string &    machineName,
     const IPv4Address      address)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    ODL_I1("address = ", address); //####
    auto    status{doBeginTransaction(_owner, _dbHandle)};

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

nImO::SuccessOrFailure
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
    SuccessOrFailure    status;

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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addNode

nImO::SuccessOrFailure
nImO::Registry::clearAppListForLauncher
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            static CPtr(char)   searchNodes{"DELETE FROM " APPLICATIONS_T_ " WHERE " APPLICATIONS_LAUNCHER_NAME_C_ " = @" NODE_NAME_C_};

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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::clearAppListForLauncher

nImO::SuccessOrFailure
nImO::Registry::clearChannelInUse
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVector     results;
            ChannelSearchData   data{nodeName, path};
            static CPtr(char)   updateChannel{"UPDATE " CHANNELS_T_ " SET " CHANNEL_IN_USE_C_ " = 0 WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_
                                                " AND " CHANNEL_PATH_C_ " = @" CHANNEL_PATH_C_ " RETURNING " CHANNEL_IN_USE_C_};

            status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, updateChannel, setupSearchChannels, &data);
            if (0 == results.size())
            {
                ODL_LOG("(0 == results.size())"); //####
                status = SuccessOrFailure(false, "No such node or path"s);
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
        ODL_LOG("! (ChannelName::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::clearChannelInUse

nImO::ChannelInfoOrFailure
nImO::Registry::getChannelInformation
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SuccessOrFailure    status;
    ChannelInfo         info;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVectorVector   results;
            ChannelSearchData       data{nodeName, path};
            static CPtr(char)       searchChannels{"SELECT DISTINCT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ ","
                                                    CHANNEL_DATA_TYPE_C_ "," CHANNEL_MODES_C_ "," CHANNEL_IN_USE_C_ " FROM " CHANNELS_T_
                                                    " WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_ " AND " CHANNEL_PATH_C_ " = @"
                                                    CHANNEL_PATH_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannels, &data);
            if (status.first)
            {
                if (0 < results.size())
                {
                    extractChannelInfoFromVector(info, results[0]);
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
        ODL_LOG("! (Connection::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return ChannelInfoOrFailure{status, info};
} // nImO::Registry::getChannelInformation

nImO::BoolOrFailure
nImO::Registry::getChannelInUseAndSet
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    bool                inUse{false};
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVector     results;
            ChannelSearchData   data{nodeName, path};
            static CPtr(char)   searchChannels{"SELECT DISTINCT " CHANNEL_IN_USE_C_ " FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @"
                                                CHANNEL_NODE_C_ " AND " CHANNEL_PATH_C_ " = @" CHANNEL_PATH_C_};

            status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannels, &data);
            if (status.first)
            {
                if (0 < results.size())
                {
                    size_t  pos;
                    int     fieldValue = stoi(results[0], &pos);

                    if (0 == pos)
                    {
                        inUse = false;
                    }
                    else
                    {
                        inUse = (1 == fieldValue);
                        static CPtr(char)   updateChannel{"UPDATE " CHANNELS_T_ " SET " CHANNEL_IN_USE_C_ " = 1 WHERE " CHANNEL_NODE_C_ " = @"
                                                            CHANNEL_NODE_C_ " AND " CHANNEL_PATH_C_ " = @" CHANNEL_PATH_C_ " RETURNING "
                                                            CHANNEL_IN_USE_C_};

                        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, updateChannel, setupSearchChannels, &data);
                        if (0 == results.size())
                        {
                            ODL_LOG("(0 == results.size())"); //####
                            status = SuccessOrFailure(false, "No such node or path"s);
                        }
                    }
                }
                else
                {
                    ODL_LOG("! (0 < results.size())"); //####
                    status = SuccessOrFailure(false, "No such node or path"s);
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
        ODL_LOG("! (Connection::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, inUse};
} // nImO::Registry::getChannelInUseAndSet

nImO::BoolOrFailure
nImO::Registry::getChannelInUse
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    bool                inUse{false};
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVector     results;
            ChannelSearchData   data{nodeName, path};
            static CPtr(char)   searchChannels{"SELECT DISTINCT " CHANNEL_IN_USE_C_ " FROM " CHANNELS_T_ " WHERE " CHANNEL_NODE_C_ " = @"
                                                CHANNEL_NODE_C_ " AND " CHANNEL_PATH_C_ " = @" CHANNEL_PATH_C_};

            status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannels, &data);
            if (status.first)
            {
                if (0 < results.size())
                {
                    size_t  pos;
                    int     fieldValue = stoi(results[0], &pos);

                    if (0 == pos)
                    {
                        inUse = false;
                    }
                    else
                    {
                        inUse = (1 == fieldValue);
                    }
                }
                else
                {
                    ODL_LOG("! (0 < results.size())"); //####
                    status = SuccessOrFailure(false, "No such node or path"s);
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
        ODL_LOG("! (Connection::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, inUse};
} // nImO::Registry::getChannelInUse

nImO::ConnectionInfoOrFailure
nImO::Registry::getConnectionInformation
    (const std::string &    nodeName,
     const std::string &    path,
     const bool             fromIsSpecified)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    ODL_B1("fromIsSpecified = ", fromIsSpecified); //####
    SuccessOrFailure    status;
    ConnectionInfo      connectionData;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        ConnectionSearchData    searchData{nodeName, path};

        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVectorVector   results;

            if (fromIsSpecified)
            {
                static CPtr(char)   searchConnections{"SELECT DISTINCT " CONNECTION_FROM_NODE_C_ "," CONNECTION_FROM_PATH_C_ ","
                                                        CONNECTION_TO_NODE_C_ "," CONNECTION_TO_PATH_C_ "," CONNECTION_DATA_TYPE_C_ ","
                                                        CONNECTION_MODE_C_ " FROM " CONNECTIONS_T_ " WHERE " CONNECTION_FROM_NODE_C_ " = @"
                                                        CONNECTION_FROM_NODE_C_ " AND " CONNECTION_FROM_PATH_C_ " = @" CONNECTION_FROM_PATH_C_};

                status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchConnections, setupSearchConnectionsViaFrom,
                                                                      &searchData);
            }
            else
            {
                static CPtr(char)   searchConnections{"SELECT DISTINCT " CONNECTION_FROM_NODE_C_ "," CONNECTION_FROM_PATH_C_ ","
                                                        CONNECTION_TO_NODE_C_ "," CONNECTION_TO_PATH_C_ "," CONNECTION_DATA_TYPE_C_ ","
                                                        CONNECTION_MODE_C_ " FROM " CONNECTIONS_T_ " WHERE " CONNECTION_TO_NODE_C_ " = @"
                                                        CONNECTION_TO_NODE_C_ " AND " CONNECTION_TO_PATH_C_ " = @" CONNECTION_TO_PATH_C_};

                status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchConnections, setupSearchConnectionsViaTo,
                                                                      &searchData);
            }
            if (status.first)
            {
                if (0 < results.size())
                {
                    StdStringVector &   values{results[0]};

                    if (5 < values.size())
                    {
                        ConnectionInfo  info;
                        size_t          pos;

                        connectionData._found = true;
                        connectionData._fromNode = values[0];
                        connectionData._fromPath = values[1];
                        connectionData._toNode = values[2];
                        connectionData._toPath = values[3];
                        connectionData._dataType = values[4];
                        connectionData._mode = StaticCast(TransportType, stoul(values[5], &pos));
                        if (0 == pos)
                        {
                            connectionData._found = false;
                        }
                    }
                    else
                    {
                        ODL_LOG("! (5 < values.size())"); //####
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
        ODL_LOG("! (ChannelName::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return ConnectionInfoOrFailure{status, connectionData};
} // nImO::Registry::getConnectionInformation

nImO::ApplicationInfoVectorOrFailure
nImO::Registry::getInformationForAllApplications
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto                    status{doBeginTransaction(_owner, _dbHandle)};
    ApplicationInfoVector   applicationData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchApplications{"SELECT DISTINCT " APPLICATIONS_LAUNCHER_NAME_C_ "," APPLICATIONS_APP_NAME_C_ ","
                                                    APPLICATIONS_APP_DESCR_C_ " FROM " APPLICATIONS_T_ " ORDER BY " APPLICATIONS_LAUNCHER_NAME_C_ ","
                                                    APPLICATIONS_APP_NAME_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchApplications);
        if (status.first)
        {
            ApplicationInfo info;

            for (auto & walker : results)
            {
                extractApplicationInfoFromVector(info, walker);
                if (info._found)
                {
                    applicationData.push_back(info);
                }
                else
                {
                    ODL_LOG("! (info._found)"); //####
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
    return ApplicationInfoVectorOrFailure{status, applicationData};
} // nImO::Registry::getInformationForAllApplications

nImO::ApplicationInfoVectorOrFailure
nImO::Registry::getInformationForAllApplicationsOnNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    auto                    status{doBeginTransaction(_owner, _dbHandle)};
    ApplicationInfoVector   applicationData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchApplications{"SELECT DISTINCT " APPLICATIONS_LAUNCHER_NAME_C_ "," APPLICATIONS_APP_NAME_C_ ","
                                                    APPLICATIONS_APP_DESCR_C_ " FROM " APPLICATIONS_T_ " WHERE " APPLICATIONS_LAUNCHER_NAME_C_
                                                    " = @" APPLICATIONS_LAUNCHER_NAME_C_" ORDER BY " APPLICATIONS_APP_NAME_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchApplications, setupSearchApplicationsNodeOnly,
                                                              &nodeName);
        if (status.first)
        {
            ApplicationInfo info;

            for (auto & walker : results)
            {
                extractApplicationInfoFromVector(info, walker);
                if (info._found)
                {
                    applicationData.push_back(info);
                }
                else
                {
                    ODL_LOG("! (info._found)"); //####
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
    return ApplicationInfoVectorOrFailure{status, applicationData};
} // nImO::Registry::getInformationForAllApplicationsOnNode

nImO::ChannelInfoVectorOrFailure
nImO::Registry::getInformationForAllChannels
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto                status{doBeginTransaction(_owner, _dbHandle)};
    ChannelInfoVector   channelData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchChannels{"SELECT DISTINCT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ ","
                                                CHANNEL_DATA_TYPE_C_ "," CHANNEL_MODES_C_ "," CHANNEL_IN_USE_C_" FROM " CHANNELS_T_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels);
        if (status.first)
        {
            ChannelInfo info;

            for (auto & walker : results)
            {
                extractChannelInfoFromVector(info, walker);
                if (info._found)
                {
                    channelData.push_back(info);
                }
                else
                {
                    ODL_LOG("! (info._found)"); //####
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
    return ChannelInfoVectorOrFailure{status, channelData};
} // nImO::Registry::getInformationForAllChannels

nImO::ChannelInfoVectorOrFailure
nImO::Registry::getInformationForAllChannelsOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    auto                status{doBeginTransaction(_owner, _dbHandle)};
    ChannelInfoVector   channelData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchChannels{"SELECT DISTINCT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ ","
                                                CHANNEL_DATA_TYPE_C_ "," CHANNEL_MODES_C_ "," CHANNEL_IN_USE_C_ " FROM " CHANNELS_T_ "," NODES_T_
                                                "," MACHINES_T_ " WHERE " NODES_T_ "." NODE_NAME_C_ " = " CHANNELS_T_ "." CHANNEL_NODE_C_
                                                " AND " MACHINES_T_ "." MACHINE_ADDRESS_C_ " = " NODES_T_ "." NODE_ADDRESS_C_ " AND " MACHINES_T_
                                                "." MACHINE_NAME_C_ " = @" MACHINE_NAME_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannelsMachineOnly,
                                                              &machineName);
        if (status.first)
        {
            ChannelInfo info;

            for (auto & walker : results)
            {
                extractChannelInfoFromVector(info, walker);
                if (info._found)
                {
                    channelData.push_back(info);
                }
                else
                {
                    ODL_LOG("! (info._found)"); //####
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
    return ChannelInfoVectorOrFailure{status, channelData};
} // nImO::Registry::getInformationForAllChannelsOnMachine

nImO::ChannelInfoVectorOrFailure
nImO::Registry::getInformationForAllChannelsOnNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    auto                status{doBeginTransaction(_owner, _dbHandle)};
    ChannelInfoVector   channelData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchChannels{"SELECT DISTINCT " CHANNEL_NODE_C_ "," CHANNEL_PATH_C_ "," CHANNEL_IS_OUTPUT_C_ ","
                                                CHANNEL_DATA_TYPE_C_ "," CHANNEL_MODES_C_ "," CHANNEL_IN_USE_C_ " FROM " CHANNELS_T_ " WHERE "
                                                CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchChannels, setupSearchChannelsNodeOnly, &nodeName);
        if (status.first)
        {
            ChannelInfo info;

            for (auto & walker : results)
            {
                extractChannelInfoFromVector(info, walker);
                if (info._found)
                {
                    channelData.push_back(info);
                }
                else
                {
                    ODL_LOG("! (info._found)"); //####
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
    return ChannelInfoVectorOrFailure{status, channelData};
} // nImO::Registry::getInformationForAllChannelsOnNode

nImO::ConnectionInfoVectorOrFailure
nImO::Registry::getInformationForAllConnections
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto                    status{doBeginTransaction(_owner, _dbHandle)};
    ConnectionInfoVector    connectionData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchConnections{"SELECT DISTINCT " CONNECTION_FROM_NODE_C_ ", " CONNECTION_FROM_PATH_C_ ", "
                                                    CONNECTION_TO_NODE_C_ ", " CONNECTION_TO_PATH_C_ ", " CONNECTION_DATA_TYPE_C_ ", "
                                                    CONNECTION_MODE_C_ " FROM " CONNECTIONS_T_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchConnections);
        if (status.first)
        {
            for (auto & walker : results)
            {
                if (5 < walker.size())
                {
                    ConnectionInfo  info;
                    size_t          pos;

                    info._found = true;
                    info._fromNode = walker[0];
                    info._fromPath = walker[1];
                    info._toNode = walker[2];
                    info._toPath = walker[3];
                    info._dataType = walker[4];
                    info._mode = StaticCast(TransportType, stoul(walker[5], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    if (info._found)
                    {
                        connectionData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (5 < walker.size())"); //####
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
    return ConnectionInfoVectorOrFailure{status, connectionData};
} // nImO::Registry::getInformationForAllConnections

nImO::ConnectionInfoVectorOrFailure
nImO::Registry::getInformationForAllConnectionsOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    auto                    status{doBeginTransaction(_owner, _dbHandle)};
    ConnectionInfoVector    connectionData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchConnections{"SELECT DISTINCT " CONNECTION_FROM_NODE_C_ ", " CONNECTION_FROM_PATH_C_ ", "
                                                    CONNECTION_TO_NODE_C_ ", " CONNECTION_TO_PATH_C_ ", " CONNECTION_DATA_TYPE_C_ ", "
                                                    CONNECTION_MODE_C_ " FROM " CONNECTIONS_T_ ", " NODES_T_ ", " MACHINES_T_ " WHERE ("
                                                    CONNECTION_FROM_NODE_C_ " = " NODES_T_ "." NODE_NAME_C_ " OR " CONNECTION_TO_NODE_C_ " = "
                                                    NODES_T_ "." NODE_NAME_C_ ") AND " MACHINES_T_ "." MACHINE_NAME_C_ " = @" MACHINE_NAME_C_
                                                    " AND " MACHINES_T_ "." MACHINE_ADDRESS_C_ " = " NODES_T_ "." NODE_ADDRESS_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchConnections, setupSearchMachines, &machineName);
        if (status.first)
        {
            for (auto & walker : results)
            {
                if (5 < walker.size())
                {
                    ConnectionInfo  info;
                    size_t          pos;

                    info._found = true;
                    info._fromNode = walker[0];
                    info._fromPath = walker[1];
                    info._toNode = walker[2];
                    info._toPath = walker[3];
                    info._dataType = walker[4];
                    info._mode = StaticCast(TransportType, stoul(walker[5], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    if (info._found)
                    {
                        connectionData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (5 < walker.size())"); //####
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
    return ConnectionInfoVectorOrFailure{status, connectionData};
} // nImO::Registry::getInformationForAllConnectionsOnNode

nImO::ConnectionInfoVectorOrFailure
nImO::Registry::getInformationForAllConnectionsOnNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    auto                    status{doBeginTransaction(_owner, _dbHandle)};
    ConnectionInfoVector    connectionData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchConnections{"SELECT DISTINCT " CONNECTION_FROM_NODE_C_ ", " CONNECTION_FROM_PATH_C_ ", "
                                                    CONNECTION_TO_NODE_C_ ", " CONNECTION_TO_PATH_C_ ", " CONNECTION_DATA_TYPE_C_ ", "
                                                    CONNECTION_MODE_C_ " FROM " CONNECTIONS_T_ " WHERE " CONNECTION_FROM_NODE_C_ " = @"
                                                    CONNECTION_FROM_NODE_C_ " OR " CONNECTION_TO_NODE_C_ " = @" CONNECTION_TO_NODE_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchConnections, setupSearchNodeConnections, &nodeName);
        if (status.first)
        {
            for (auto & walker : results)
            {
                if (5 < walker.size())
                {
                    ConnectionInfo  info;
                    size_t          pos;

                    info._found = true;
                    info._fromNode = walker[0];
                    info._fromPath = walker[1];
                    info._toNode = walker[2];
                    info._toPath = walker[3];
                    info._dataType = walker[4];
                    info._mode = StaticCast(TransportType, stoul(walker[5], &pos));
                    if (0 == pos)
                    {
                        info._found = false;
                    }
                    if (info._found)
                    {
                        connectionData.push_back(info);
                    }
                    else
                    {
                        ODL_LOG("! (info._found)"); //####
                    }
                }
                else
                {
                    ODL_LOG("! (5 < walker.size())"); //####
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
    return ConnectionInfoVectorOrFailure{status, connectionData};
} // nImO::Registry::getInformationForAllConnectionsOnNode

nImO::MachineInfoVectorOrFailure
nImO::Registry::getInformationForAllMachines
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto                status{doBeginTransaction(_owner, _dbHandle)};
    MachineInfoVector   machineData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchMachines{"SELECT DISTINCT " MACHINE_NAME_C_ "," MACHINE_ADDRESS_C_ " FROM " MACHINES_T_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchMachines);
        if (status.first)
        {
            for (auto & walker : results)
            {
                if (1 < walker.size())
                {
                    MachineInfo info;
                    size_t      pos;

                    info._found = true;
                    info._name = walker[0];
                    info._address = StaticCast(IPv4Address, stoul(walker[1], &pos));
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
                    ODL_LOG("! (1 < walker.size())"); //####
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
    return MachineInfoVectorOrFailure{status, machineData};
} // nImO::Registry::getInformationForAllMachines

nImO::NodeInfoVectorOrFailure
nImO::Registry::getInformationForAllNodes
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto            status{doBeginTransaction(_owner, _dbHandle)};
    NodeInfoVector  nodeData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchNodes{"SELECT DISTINCT " NODE_NAME_C_ "," NODE_ADDRESS_C_ "," NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_
                                            " FROM " NODES_T_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodes);
        if (status.first)
        {
            NodeInfo    info;

            for (auto & walker : results)
            {
                extractNodeInfoFromVector(info, walker);
                if (info._found)
                {
                    nodeData.push_back(info);
                }
                else
                {
                    ODL_LOG("! (info._found)"); //####
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
    return NodeInfoVectorOrFailure{status, nodeData};
} // nImO::Registry::getInformationForAllNodes

nImO::NodeInfoVectorOrFailure
nImO::Registry::getInformationForAllNodesOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    auto            status{doBeginTransaction(_owner, _dbHandle)};
    NodeInfoVector  nodeData;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchNodesAndMachines{"SELECT DISTINCT " NODES_T_ "." NODE_NAME_C_ "," NODES_T_ "." NODE_ADDRESS_C_ ","
                                                        NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_ " FROM " NODES_T_ ", " MACHINES_T_ " WHERE "
                                                        MACHINES_T_ "." MACHINE_NAME_C_ " = @" MACHINE_NAME_C_ " AND " MACHINES_T_ "."
                                                        MACHINE_ADDRESS_C_ " = " NODES_T_ "." NODE_ADDRESS_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodesAndMachines, setupSearchMachines, &machineName);
        if (status.first)
        {
            NodeInfo    info;

            for (auto & walker : results)
            {
                extractNodeInfoFromVector(info, walker);
                if (info._found)
                {
                    nodeData.push_back(info);
                }
                else
                {
                    ODL_LOG("! (info._found)"); //####
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
    return NodeInfoVectorOrFailure{status, nodeData};
} // nImO::Registry::getInformationForAllNodesOnMachine

nImO::LaunchDetailsOrFailure
nImO::Registry::getLaunchDetails
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SuccessOrFailure    status;
    LaunchDetails       details;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVectorVector   results;
            static CPtr(char)       searchNodes{"SELECT DISTINCT " NODE_EXEC_PATH_C_ "," NODE_LAUNCH_DIRECTORY_C_ "," NODE_COMMAND_LINE_C_
                                                " FROM " NODES_T_ " WHERE " NODE_NAME_C_ " = @" NODE_NAME_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodes, setupSearchNodes, &nodeName);
            if (status.first)
            {
                if (0 < results.size())
                {
                    auto    values{results[0]};

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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return LaunchDetailsOrFailure{status, details};
} // nImO::Registry::getLaunchDetails

nImO::MachineInfoOrFailure
nImO::Registry::getMachineInformation
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SuccessOrFailure    status;
    MachineInfo         info;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVectorVector   results;
            static CPtr(char)       searchMachines{"SELECT DISTINCT " MACHINE_ADDRESS_C_ " FROM " MACHINES_T_ " WHERE " MACHINE_NAME_C_ " = @"
                                                    MACHINE_NAME_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchMachines, setupSearchMachines, &nodeName);
            if (status.first)
            {
                if (0 < results.size())
                {
                    auto    values{results[0]};

                    info._name = nodeName;
                    if (0 < values.size())
                    {
                        size_t  pos;

                        info._found = true;
                        info._address = StaticCast(IPv4Address, stoul(values[0], &pos));
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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return MachineInfoOrFailure{status, info};
} // nImO::Registry::getMachineInformation

nImO::StdStringSetOrFailure
nImO::Registry::getNamesOfMachines
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto            status{doBeginTransaction(_owner, _dbHandle)};
    StdStringSet    strings;

    if (status.first)
    {
        StdStringVector     results;
        static CPtr(char)   searchMachines{"SELECT DISTINCT " MACHINE_NAME_C_ " FROM " MACHINES_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchMachines);
        if (status.first)
        {
            for (auto & walker : results)
            {
                strings.insert(walker);
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return StdStringSetOrFailure{status, strings};
} // nImO::Registry::getNamesOfMachines

nImO::StdStringSetOrFailure
nImO::Registry::getNamesOfNodes
    (void)
    const
{
    ODL_OBJENTER(); //####
    auto            status{doBeginTransaction(_owner, _dbHandle)};
    StdStringSet    strings;

    if (status.first)
    {
        StdStringVector     results;
        static CPtr(char)   searchNodes{"SELECT DISTINCT " NODE_NAME_C_ " FROM " NODES_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchNodes);
        if (status.first)
        {
            for (auto & walker : results)
            {
                strings.insert(walker);
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return StdStringSetOrFailure{status, strings};
} // nImO::Registry::getNamesOfNodes

nImO::StdStringSetOrFailure
nImO::Registry::getNamesOfNodesOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    auto            status{doBeginTransaction(_owner, _dbHandle)};
    StdStringSet    strings;

    if (status.first)
    {
        StdStringVectorVector   results;
        static CPtr(char)       searchNodesAndMachines{"SELECT DISTINCT " NODES_T_ "." NODE_NAME_C_ " FROM " NODES_T_ ", " MACHINES_T_ " WHERE "
                                                        MACHINES_T_ "." MACHINE_NAME_C_ " = @" MACHINE_NAME_C_ " AND " MACHINES_T_ "."
                                                        MACHINE_ADDRESS_C_ " = " NODES_T_ "." NODE_ADDRESS_C_};

        status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodesAndMachines, setupSearchMachines, &machineName);
        if (status.first)
        {
            for (auto & walker : results)
            {
                if (0 < walker.size())
                {
                    strings.insert(walker[0]);
                }
                else
                {
                    ODL_LOG("! (0 < walker.size())"); //####
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
    return StdStringSetOrFailure{status, strings};
} // nImO::Registry::getNamesOfNodesOnMachine

nImO::NodeInfoOrFailure
nImO::Registry::getNodeInformation
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SuccessOrFailure    status;
    NodeInfo            info;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVectorVector   results;
            static CPtr(char)       searchNodes{"SELECT DISTINCT " NODE_ADDRESS_C_ "," NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_ " FROM " NODES_T_
                                                " WHERE " NODE_NAME_C_ " = @" NODE_NAME_C_};

            status = performSQLstatementWithMultipleColumnResults(_owner, _dbHandle, results, searchNodes, setupSearchNodes, &nodeName);
            if (status.first)
            {
                if (0 < results.size())
                {
                    StdStringVector &   values{results[0]};

                    info._name = nodeName;
                    if (2 < values.size())
                    {
                        size_t  pos;

                        info._found = true;
                        info._connection._address = StaticCast(IPv4Address, stoul(values[0], &pos));
                        if (0 == pos)
                        {
                            info._found = false;
                        }
                        info._connection._port = StaticCast(IPv4Port, stoul(values[1], &pos));
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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return NodeInfoOrFailure{status, info};
} // nImO::Registry::getNodeInformation

nImO::StdStringSetOrFailure
nImO::Registry::getNodesWithApplication
    (const std::string &    applicationName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("applicationName = ", applicationName); //####
    auto            status{doBeginTransaction(_owner, _dbHandle)};
    StdStringSet    strings;

    if (status.first)
    {
        StdStringVector     results;
        static CPtr(char)   searchNodesForApplication{"SELECT DISTINCT " APPLICATIONS_LAUNCHER_NAME_C_ " FROM " APPLICATIONS_T_ " WHERE "
                                                            APPLICATIONS_APP_NAME_C_ " = @" APPLICATIONS_APP_NAME_C_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchNodesForApplication, setupSearchNodesForApplication,
                                                            &applicationName);
        if (status.first)
        {
            for (auto & walker : results)
            {
                strings.insert(walker);
            }
        }
        else
        {
            ODL_LOG("! (status.first)"); //####
        }
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    ODL_OBJEXIT(); //####
    return StdStringSetOrFailure{status, strings};
} // nImO::Registry::getNodesWithApplication

nImO::IntOrFailure
nImO::Registry::getNumberOfApplications
    (void)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
        static CPtr(char)   countApplications{"SELECT COUNT(*) FROM " APPLICATIONS_T_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, countApplications);
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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfApplications

nImO::IntOrFailure
nImO::Registry::getNumberOfApplicationsOnNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
        static CPtr(char)   countApplications{"SELECT COUNT(*) FROM " APPLICATIONS_T_ " WHERE " APPLICATIONS_LAUNCHER_NAME_C_ " = @"
                                                APPLICATIONS_LAUNCHER_NAME_C_};

        status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, countApplications, setupCountApplications, &nodeName);
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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfApplicationsOnNode

nImO::IntOrFailure
nImO::Registry::getNumberOfChannels
    (void)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfChannels

nImO::IntOrFailure
nImO::Registry::getNumberOfChannelsOnNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfChannelsOnNode

nImO::IntOrFailure
nImO::Registry::getNumberOfConnections
    (void)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
        static CPtr(char)   countMachines{"SELECT COUNT(*) FROM " CONNECTIONS_T_};

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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfConnections

nImO::IntOrFailure
nImO::Registry::getNumberOfMachines
    (void)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfMachines

nImO::IntOrFailure
nImO::Registry::getNumberOfNodes
    (void)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfNodes

nImO::IntOrFailure
nImO::Registry::getNumberOfNodesOnMachine
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    int     count{-1};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
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
    return IntOrFailure{status, count};
} // nImO::Registry::getNumberOfNodesOnMachine

nImO::BoolOrFailure
nImO::Registry::isChannelPresent
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    bool                found{false};
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVector     results;
            ChannelSearchData   data{nodeName, path};
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
        ODL_LOG("! (Connection::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, found};
} // nImO::Registry::isChannelPresent

nImO::BoolOrFailure
nImO::Registry::isMachinePresent
    (const std::string &    machineName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("machineName = ", machineName); //####
    bool    found{false};
    auto    status{doBeginTransaction(_owner, _dbHandle)};

    if (status.first)
    {
        StdStringVector     results;
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
    return BoolOrFailure{status, found};
} // nImO::Registry::isMachinePresent

nImO::BoolOrFailure
nImO::Registry::isNodePresent
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    bool                found{false};
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVector     results;
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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return BoolOrFailure{status, found};
} // nImO::Registry::isNodePresent

nImO::SuccessOrFailure
nImO::Registry::removeChannel
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
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
        ODL_LOG("! (ChannelName::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeChannel

nImO::SuccessOrFailure
nImO::Registry::removeChannelsForNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SuccessOrFailure    status;

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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeChannelsForNode

nImO::SuccessOrFailure
nImO::Registry::removeConnection
    (const std::string &    nodeName,
     const std::string &    path,
     const bool             fromIsSpecified)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    ODL_B1("fromIsSpecified = ", fromIsSpecified); //####
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        auto    statusWithBool{isChannelPresent(nodeName, path)};

        if (statusWithBool.first.first)
        {
            if (statusWithBool.second)
            {
                ConnectionSearchData    searchData{nodeName, path};

                status = doBeginTransaction(_owner, _dbHandle);
                if (status.first)
                {
                    if (fromIsSpecified)
                    {
                        static CPtr(char)   searchConnections{"DELETE FROM " CONNECTIONS_T_ " WHERE " CONNECTION_FROM_NODE_C_ " = @"
                                                                CONNECTION_FROM_NODE_C_ " AND " CONNECTION_FROM_PATH_C_ " = @"
                                                                CONNECTION_FROM_PATH_C_};

                        status = performSQLstatementWithNoResults(_owner, _dbHandle, searchConnections, setupSearchConnectionsViaFrom, &searchData);
                    }
                    else
                    {
                        static CPtr(char)   searchConnections{"DELETE FROM " CONNECTIONS_T_ " WHERE " CONNECTION_TO_NODE_C_ " = @"
                                                                CONNECTION_TO_NODE_C_ " AND " CONNECTION_TO_PATH_C_ " = @" CONNECTION_TO_PATH_C_};

                        status = performSQLstatementWithNoResults(_owner, _dbHandle, searchConnections, setupSearchConnectionsViaTo, &searchData);
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
                ODL_LOG("! (statusWithBool.second)"); //####
                status = SuccessOrFailure(false, "Unknown 'from' channel"s);
            }
        }
    }
    else
    {
        ODL_LOG("! (ChannelName::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeConnection

nImO::SuccessOrFailure
nImO::Registry::removeNode
    (const std::string &    nodeName)
    const
{
    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    SuccessOrFailure    status;

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
        status = SuccessOrFailure(false, "Invalid node name"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeNode

nImO::SuccessOrFailure
nImO::Registry::setChannelInUse
    (const std::string &    nodeName,
     const std::string &    path)
    const
{
    ODL_OBJENTER(); //####
    ODL_S2s("nodeName = ", nodeName, "path = ", path); //####
    SuccessOrFailure    status;

    if (ChannelName::validNode(nodeName) && ChannelName::validPath(path))
    {
        status = doBeginTransaction(_owner, _dbHandle);
        if (status.first)
        {
            StdStringVector     results;
            ChannelSearchData   data{nodeName, path};
            static CPtr(char)   updateChannel{"UPDATE " CHANNELS_T_ " SET " CHANNEL_IN_USE_C_ " = 1 WHERE " CHANNEL_NODE_C_ " = @" CHANNEL_NODE_C_
                                                " AND " CHANNEL_PATH_C_ " = @" CHANNEL_PATH_C_ " RETURNING " CHANNEL_IN_USE_C_};

            status = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, updateChannel, setupSearchChannels, &data);
            if (0 == results.size())
            {
                ODL_LOG("(0 == results.size())"); //####
                status = SuccessOrFailure(false, "No such node or path"s);
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
        ODL_LOG("! (ChannelName::validNode(nodeName) && ChannelName::validPath(path))"); //####
        status = SuccessOrFailure(false, "Invalid node name or path"s);
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::setChannelInUse

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

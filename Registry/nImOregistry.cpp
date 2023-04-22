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

/*! @brief A shortcut for the case-sensitive form of a 'Text' column. */
#define BINARY_ "COLLATE BINARY"

/*! @brief A shortcut for the case-insensitive form of a 'Text' column. */
#define NOCASE_ "COLLATE NOCASE"

/*! @brief A shortcut for the standard format for a 'Text' column. */
#define TEXTNOTNULL_    "Text NOT NULL DEFAULT _"

/*! @brief The name of the 'Nodes' table. */
# define NODES_T_   "Nodes"

/*! @brief The named parameter for the 'name' column. */
# define NODE_NAME_C_   "name"

/*! @brief The named parameter for the 'address' column. */
# define NODE_ADDRESS_C_    "address"

/*! @brief The named parameter for the 'port' column. */
# define NODE_PORT_C_   "port"

/*! @brief The named parameter for the 'serviceType' column. */
# define NODE_SERVICE_TYPE_C_   "serviceType"

/*! @brief The named parameter for the 'execPath' column. */
# define NODE_EXEC_PATH_C_  "execPath"

/*! @brief The named parameter for the 'launchDirectory' column. */
# define NODE_LAUNCH_DIRECTORY_C_   "launchDirectory"

/*! @brief The named parameter for the 'commandLine' column. */
# define NODE_COMMAND_LINE_C_   "commandLine"

/*! @brief The name of the index for the 'name' column of the 'Nodes' table. */
#define NODES_NAME_I_   "Nodes_name_idx"

/*! @brief A function that provides bindings for parameters in an SQL statement.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
typedef int (*BindFunction)
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff);

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
    nImO::RegSuccessOrFailure   status{true, ""};

    ODL_ENTER(); //####
    ODL_P4("owner = ", owner.get(), "dbHandle = ", dbHandle, "results = ", &results, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared = NULL;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr);

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
                            int colCount = sqlite3_column_count(prepared);

                            ODL_I1("colCount <- ", colCount); //####
                            if (0 < colCount)
                            {
                                nImO::StringVector  thisRow;

                                for (int ii = 0; ii < colCount; ++ii)
                                {
                                    CPtr(char)  value = ReinterpretCast(CPtr(char), sqlite3_column_text(prepared, ii));

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
    nImO::RegSuccessOrFailure   status{true, ""};

    ODL_ENTER(); //####
    ODL_P3("owner = ", owner.get(), "dbHandle = ", dbHandle, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared = nullptr;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr);

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
    nImO::RegSuccessOrFailure   status{true, ""};

    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared = nullptr;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr);

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
    nImO::RegSuccessOrFailure   status{true, ""};

    ODL_ENTER(); //####
    ODL_P4("owner = ", owner.get(), "dbHandle = ", dbHandle, "resultList = ", &resultList, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
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
            Ptr(sqlite3_stmt)   prepared = nullptr;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement, static_cast<int>(strlen(sqlStatement)), &prepared, nullptr);

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
                            int colCount = sqlite3_column_count(prepared);

                            ODL_I1("colCount <- ", colCount); //####
                            if (0 < colCount)
                            {
                                CPtr(char)  value = ReinterpretCast(CPtr(char), sqlite3_column_text(prepared, 0));

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
    nImO::RegSuccessOrFailure   status{true, ""};

    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            static CPtr(char)   beginTransaction = "BEGIN TRANSACTION";

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
    nImO::RegSuccessOrFailure   status{true, ""};

    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_B1("wasOK = ", wasOK); //####
    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            status = nImO::RegSuccessOrFailure{false, "No open database"};
        }
        else
        {
            static CPtr(char)   abortTransaction = "ROLLBACK TRANSACTION";
            static CPtr(char)   commitTransaction = "END TRANSACTION";

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
    nImO::RegSuccessOrFailure   status{true, ""};

    ODL_ENTER(); //####
    ODL_P2("owner = ", owner.get(), "dbHandle = ", dbHandle); //####
    ODL_B1("logging = ", logging); //####
    if (nullptr == dbHandle)
    {
        ODL_LOG("(nullptr == dbHandle)"); //####
        status = nImO::RegSuccessOrFailure{false, "No open database"};
    }
    else
    {
        if (owner && logging)
        {
            owner->report("creating tables.");
        }
        status = doBeginTransaction(owner, dbHandle);
        if (status.first)
        {
            static CPtr(char)   tableSQL[] =
            {
                "CREATE TABLE IF NOT EXISTS " NODES_T_ "(" NODE_NAME_C_ " " TEXTNOTNULL_ " " NOCASE_ " PRIMARY KEY ON CONFLICT ABORT,"
                                                            NODE_ADDRESS_C_ " INTEGER, " NODE_PORT_C_ " INTEGER, " NODE_SERVICE_TYPE_C_ " INTEGER,"
                                                            NODE_EXEC_PATH_C_ " " TEXTNOTNULL_ " " BINARY_ ", " NODE_LAUNCH_DIRECTORY_C_ " "
                                                            TEXTNOTNULL_ " " BINARY_ ", " NODE_COMMAND_LINE_C_ " " TEXTNOTNULL_ " " BINARY_ ")",
                "CREATE INDEX IF NOT EXISTS " NODES_NAME_I_ " ON " NODES_T_ "(" NODE_NAME_C_ ")"
            };
            static const size_t numTables = A_SIZE(tableSQL);

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
    NIMO_UNUSED_ARG_(code);
    Ptr(nImO::ContextWithNetworking)    owner = StaticCast(Ptr(nImO::ContextWithNetworking), data);

    if (nullptr != owner)
    {
        owner->report(message);
    }
} // sqlLogger

/*! @brief Bind the values that are to be inserted into the Nodes table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupInsertIntoNodes
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    int result = SQLITE_MISUSE;

    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    try
    {
        int nodeNameIndex = sqlite3_bind_parameter_index(statement, "@" NODE_NAME_C_);
        int nodeAddressIndex = sqlite3_bind_parameter_index(statement, "@" NODE_ADDRESS_C_);
        int nodePortIndex = sqlite3_bind_parameter_index(statement, "@" NODE_PORT_C_);
        int nodeServiceTypeIndex = sqlite3_bind_parameter_index(statement, "@" NODE_SERVICE_TYPE_C_);
        int nodeExecPathIndex = sqlite3_bind_parameter_index(statement, "@" NODE_EXEC_PATH_C_);
        int nodeLaunchDirectoryIndex = sqlite3_bind_parameter_index(statement, "@" NODE_LAUNCH_DIRECTORY_C_);
        int nodeCommandLineIndex = sqlite3_bind_parameter_index(statement, "@" NODE_COMMAND_LINE_C_);

        if ((0 < nodeNameIndex) && (0 < nodeAddressIndex) && (0 < nodePortIndex) && (0 < nodeServiceTypeIndex) && (0 < nodeExecPathIndex) &&
            (0 < nodeLaunchDirectoryIndex) && (0 < nodeCommandLineIndex))
        {
            CPtr(NodeInsertData)    nodeData = StaticCast(CPtr(NodeInsertData), stuff);
            std::string             name = nodeData->_name;
            std::string             execPath = nodeData->_execPath;
            std::string             launchDirectory = nodeData->_launchDirectory;
            std::string             commandLine = nodeData->_commandLine;

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
} // setupInsertIntoRequests

/*! @brief Bind the value that is to be searched for in the Nodes table.
 @param[in] statement The prepared statement that is to be updated.
 @param[in] stuff The source of data that is to be bound.
 @return The SQLite error from the bind operation. */
static int
setupSearchNodes
    (Ptr(sqlite3_stmt)  statement,
     CPtr(void)         stuff)
{
    int result = SQLITE_MISUSE;

    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    try
    {
        int nodeNameIndex = sqlite3_bind_parameter_index(statement, "@" NODE_NAME_C_);

        if (0 < nodeNameIndex)
        {
            std::string name = *StaticCast(CPtr(std::string), stuff);

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
    if (logging && _owner)
    {
        sqlite3_config(SQLITE_CONFIG_LOG, sqlLogger, _owner.get());
    }
    int result = sqlite3_open_v2("nImO_registry", &_dbHandle,
                                 SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY | SQLITE_OPEN_PRIVATECACHE, nullptr);

    if (SQLITE_OK == result)
    {
        nImO::RegSuccessOrFailure   status = createTables(_owner, logging, _dbHandle);

        if (! status.first)
        {
            std::string prefix{"Problem creating tables in database: "};

            if (_owner && logging)
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

        if (_owner && logging)
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
nImO::Registry::addNode
    (const std::string &    nodeName,
     const std::string &    execPath,
     const std::string &    launchDirectory,
     const std::string &    commandLine,
     const ServiceType      serviceClass,
     const Connection &     nodeConnection)
{
    RegSuccessOrFailure status = doBeginTransaction(_owner, _dbHandle);

    ODL_OBJENTER(); //####
    ODL_S4s("nodeName = ", nodeName, "execPath = ", execPath, "launchDirectory = ", launchDirectory, "commandLine = ", commandLine); //####
    ODL_I1("serviceClass = ", StaticCast(int, serviceClass)); //####
    ODL_P1("nodeConnection = ", &nodeConnection); //####
    if (status.first)
    {
        NodeInsertData      data{nodeName, nodeConnection, serviceClass, execPath, launchDirectory, commandLine};
        static CPtr(char)   insertIntoNodes = "INSERT INTO " NODES_T_ "(" NODE_NAME_C_ "," NODE_ADDRESS_C_ "," NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_
                                                "," NODE_EXEC_PATH_C_ "," NODE_LAUNCH_DIRECTORY_C_ "," NODE_COMMAND_LINE_C_ ") VALUES(@" NODE_NAME_C_
                                                ",@" NODE_ADDRESS_C_ ",@" NODE_PORT_C_ ",@" NODE_SERVICE_TYPE_C_ ",@" NODE_EXEC_PATH_C_ ",@"
                                                NODE_LAUNCH_DIRECTORY_C_ ",@" NODE_COMMAND_LINE_C_ ")";

        status = performSQLstatementWithNoResults(_owner, _dbHandle, insertIntoNodes, setupInsertIntoNodes, &data);
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::addNode

nImO::RegNodeInfoVectorOrFailure
nImO::Registry::getInformationForAllNodes
    (void)
    const
{
    RegSuccessOrFailure status = doBeginTransaction(_owner, _dbHandle);
    NodeInfoVector      nodeData;

    ODL_OBJENTER(); //####
    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchNodes = "SELECT " NODE_NAME_C_ "," NODE_ADDRESS_C_ "," NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_ " FROM "
                                                    NODES_T_;

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

nImO::RegLaunchDetailsOrFailure
nImO::Registry::getLaunchDetails
    (const std::string &    nodeName)
    const
{
    RegSuccessOrFailure status = doBeginTransaction(_owner, _dbHandle);
    LaunchDetails       details;

    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchNodes = "SELECT " NODE_EXEC_PATH_C_ "," NODE_LAUNCH_DIRECTORY_C_ "," NODE_COMMAND_LINE_C_ " FROM " NODES_T_
                                                    " WHERE " NODE_NAME_C_ "=@" NODE_NAME_C_;

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
    ODL_OBJEXIT(); //####
    return RegLaunchDetailsOrFailure{status, details};
} // nImO::Registry::getLaunchDetails

nImO::RegStringSetOrFailure
nImO::Registry::getNamesOfNodes
    (void)
    const
{
    RegSuccessOrFailure status = doBeginTransaction(_owner, _dbHandle);
    StringSet           strings;

    ODL_OBJENTER(); //####
    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   searchNodes = "SELECT " NODE_NAME_C_ " FROM " NODES_T_;

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

nImO::RegNodeInfoOrFailure
nImO::Registry::getNodeInformation
    (const std::string &    nodeName)
    const
{
    RegSuccessOrFailure status = doBeginTransaction(_owner, _dbHandle);
    NodeInfo            info;

    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    if (status.first)
    {
        std::vector<StringVector>   results;
        static CPtr(char)           searchNodes = "SELECT " NODE_ADDRESS_C_ "," NODE_PORT_C_ "," NODE_SERVICE_TYPE_C_ " FROM " NODES_T_ " WHERE "
                                                    NODE_NAME_C_ "=@" NODE_NAME_C_;

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
    ODL_OBJEXIT(); //####
    return RegNodeInfoOrFailure{status, info};
} // nImO::Registry::getNodeInformation

nImO::RegIntOrFailure
nImO::Registry::getNumberOfNodes
    (void)
    const
{
    int                 count = -1;
    RegSuccessOrFailure status = doBeginTransaction(_owner, _dbHandle);

    ODL_OBJENTER(); //####
    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   countNodes = "SELECT COUNT(*) FROM " NODES_T_;

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

nImO::RegBoolOrFailure
nImO::Registry::isNodePresent
    (const std::string &    nodeName)
{
    bool                found = false;
    RegSuccessOrFailure status = doBeginTransaction(_owner, _dbHandle);

    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    if (status.first)
    {
        StringVector        results;
        static CPtr(char)   searchNodes = "SELECT COUNT(*) FROM " NODES_T_ " WHERE " NODE_NAME_C_ "=@" NODE_NAME_C_;

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
    ODL_OBJEXIT(); //####
    return RegBoolOrFailure{status, found};
} // nImO::Registry::isNodePresent

nImO::RegSuccessOrFailure
nImO::Registry::removeNode
    (const std::string &    nodeName)
{
    RegSuccessOrFailure   status = doBeginTransaction(_owner, _dbHandle);

    ODL_OBJENTER(); //####
    ODL_S1s("nodeName = ", nodeName); //####
    if (status.first)
    {
        static CPtr(char)   searchNodes = "DELETE FROM " NODES_T_ " WHERE " NODE_NAME_C_ "=@" NODE_NAME_C_;

        status = performSQLstatementWithNoResults(_owner, _dbHandle, searchNodes, setupSearchNodes, &nodeName);
        doEndTransaction(_owner, _dbHandle, status.first);
    }
    else
    {
        ODL_LOG("! (status.first)"); //####
    }
    ODL_OBJEXIT(); //####
    return status;
} // nImO::Registry::removeNode

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

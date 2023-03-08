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

/*! @brief A shortcut for the standard format for a 'Text' column. */
#define TEXTNOTNULL_    "Text NOT NULL DEFAULT _"

/*! @brief The name of the 'Nodes' table. */
# define NODES_T_   "Nodes"

/*! @brief The named parameter for the 'name' column. */
# define NODENAME_C_    "name"

/*! @brief The named parameter for the 'address' column. */
# define NODEADDRESS_C_ "address"

/*! @brief The named parameter for the 'port' column. */
# define NODEPORT_C_    "port"

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

    /*! @brief The IP address of this node. */
    uint32_t    _address;

    /*@ @brief The command port for this node.*/
    uint16_t    _port;
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
 @param[in] columnOfInterest1 The column containing the first value of interest.
 @param[in] columnOfInterest2 The column containing the second value of interest.
 @param[in] doBinds A function that will fill in any parameters in the statement.
 @param[in] data The custom information used with the binding function.
 @return @c true if the operation was successfully performed and @c false otherwise. */
static bool
performSQLstatementWithDoubleColumnResults
    (Ptr(nImO::ContextWithNetworking)   owner,
     Ptr(sqlite3)                       dbHandle,
     nImO::StringVector &               resultColumn1,
     nImO::StringVector &               resultColumn2,
     CPtr(char)                         sqlStatement,
     const int                          columnOfInterest1,
     const int                          columnOfInterest2,
     BindFunction                       doBinds,
     CPtr(void)                         data)
{
    ODL_ENTER(); //####
    ODL_P2("dbHandle = ", dbHandle, "data = ", data); //####
    ODL_I2("columnOfInterest1 = ", columnOfInterest1, "columnOfInterest2 = ", //####
            columnOfInterest2); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    bool okSoFar = true;

    try
    {
        if ((nullptr != dbHandle) && (0 <= columnOfInterest1) && (0 <= columnOfInterest2))
        {
            Ptr(sqlite3_stmt)   prepared = NULL;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement,
                                                           static_cast<int>(strlen(sqlStatement)),
                                                           &prepared, nullptr);

            ODL_I1("sqlRes <- ", sqlRes); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                if (nullptr != doBinds)
                {
                    sqlRes = doBinds(prepared, data);
                    ODL_I1("sqlRes <- ", sqlRes); //####
                    okSoFar = (SQLITE_OK == sqlRes);
                }
                if (okSoFar)
                {
                    for (sqlRes = SQLITE_ROW; SQLITE_ROW == sqlRes; )
                    {
                        do
                        {
                            sqlRes = sqlite3_step(prepared);
                            ODL_I1("sqlRes <- ", sqlRes); //####
                            ODL_S1("sqlRes <- ", mapStatusToStringForSQL(sqlRes)); //####
                            if (SQLITE_BUSY == sqlRes)
                            {
                                nImO::ConsumeSomeTime(owner, 10.0);
                            }
                        }
                        while (SQLITE_BUSY == sqlRes);
                        if (SQLITE_ROW == sqlRes)
                        {
                            // Gather the column data...
                            int colCount = sqlite3_column_count(prepared);

                            ODL_I1("colCount <- ", colCount); //####
                            if ((0 < colCount) && (columnOfInterest1 < colCount) && (columnOfInterest2 < colCount))
                            {
                                CPtr(char)  value = ReinterpretCast(CPtr(char), sqlite3_column_text(prepared, columnOfInterest1));

                                ODL_S1("value <- ", value); //####
                                if (nullptr == value)
                                {
                                    resultColumn1.push_back("");
                                }
                                else
                                {
                                    resultColumn1.push_back(value);
                                }
                                value = ReinterpretCast(CPtr(char), sqlite3_column_text(prepared, columnOfInterest2));
                                ODL_S1("value <- ", value); //####
                                if (nullptr == value)
                                {
                                    resultColumn2.push_back("");
                                }
                                else
                                {
                                    resultColumn2.push_back(value);
                                }
                            }
                        }
                    }
                    if (SQLITE_DONE != sqlRes)
                    {
                        ODL_LOG("(SQLITE_DONE != sqlRes)"); //####
                        okSoFar = false;
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                okSoFar = false;
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != dbHandle) && (0 <= columnOfInterest1) && (0 <= columnOfInterest2))"); //####
            okSoFar = false;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // performSQLstatementWithDoubleColumnResults

/*! @brief Perform a simple operation on the database.
 @param[in] dbHandle The database to be modified.
 @param[in] sqlStatement The operation to be performed.
 @param[in] doBinds A function that will fill in any parameters in the statement.
 @param[in] data The custom information used with the binding function.
 @return @c true if the operation was successfully performed and @c false otherwise. */
static bool
performSQLstatementWithNoResults
    (Ptr(nImO::ContextWithNetworking)   owner,
     Ptr(sqlite3)                       dbHandle,
     CPtr(char)                         sqlStatement,
     BindFunction                       doBinds,
     CPtr(void)                         data)
{
    ODL_ENTER(); //####
    ODL_P2("dbHandle = ", dbHandle, "data = ", data); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    bool okSoFar = true;

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            okSoFar = false;
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared = nullptr;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement,
                                                           static_cast<int>(strlen(sqlStatement)),
                                                           &prepared, nullptr);

            ODL_I1("sqlRes <- ", sqlRes); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                if (nullptr != doBinds)
                {
                    sqlRes = doBinds(prepared, data);
                    ODL_I1("sqlRes <- ", sqlRes); //####
                    okSoFar = (SQLITE_OK == sqlRes);
                }
                if (okSoFar)
                {
                    do
                    {
                        sqlRes = sqlite3_step(prepared);
                        ODL_I1("sqlRes <- ", sqlRes); //####
                        if (SQLITE_BUSY == sqlRes)
                        {
                            nImO::ConsumeSomeTime(owner, 10.0);
                        }
                    }
                    while (SQLITE_BUSY == sqlRes);
                    if (SQLITE_DONE != sqlRes)
                    {
                        ODL_LOG("(SQLITE_DONE != sqlRes)"); //####
                        okSoFar = false;
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && prepared)"); //####
                okSoFar = false;
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // performSQLstatementWithNoResults

/*! @brief Perform a simple operation on the database.
 @param[in] owner The object to be used for reporting.
 @param[in] dbHandle The database to be modified.
 @param[in] sqlStatement The operation to be performed.
 @return @c true if the operation was successfully performed and @c false otherwise. */
static bool
performSQLstatementWithNoResultsNoArgs
    (Ptr(nImO::ContextWithNetworking)   owner,
     Ptr(sqlite3)                       dbHandle,
     CPtr(char)                         sqlStatement)
{
    ODL_ENTER(); //####
    ODL_P1("dbHandle = ", dbHandle); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    bool    okSoFar = true;

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            okSoFar = false;
        }
        else
        {
            Ptr(sqlite3_stmt)   prepared = nullptr;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement,
                                                           static_cast<int>(strlen(sqlStatement)),
                                                           &prepared, nullptr);

            ODL_I1("sqlRes <- ", sqlRes); //####
            ODL_S1("sqlRes <- ", mapStatusToStringForSQL(sqlRes)); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                if (okSoFar)
                {
                    do
                    {
                        sqlRes = sqlite3_step(prepared);
                        ODL_I1("sqlRes <- ", sqlRes); //####
                        ODL_S1("sqlRes <- ", mapStatusToStringForSQL(sqlRes)); //####
                        if (SQLITE_BUSY == sqlRes)
                        {
                            nImO::ConsumeSomeTime(owner, 10.0);
                        }
                    }
                    while (SQLITE_BUSY == sqlRes);
                    if (SQLITE_DONE != sqlRes)
                    {
                        ODL_LOG("(SQLITE_DONE != sqlRes)"); //####
                        okSoFar = false;
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                okSoFar = false;
            }
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // performSQLstatementWithNoResultsNoArgs

/*! @brief Perform an operation that can return multiple rows of results.
 @param[in] database The database to be modified.
 @param[in,out] resultList The list to be filled in with the values from the column of interest.
 @param[in] sqlStatement The operation to be performed.
 @param[in] columnOfInterest The column containing the value of interest.
 @param[in] doBinds A function that will fill in any parameters in the statement.
 @param[in] data The custom information used with the binding function.
 @return @c true if the operation was successfully performed and @c false otherwise. */
static bool
performSQLstatementWithSingleColumnResults
    (Ptr(nImO::ContextWithNetworking)   owner,
     Ptr(sqlite3)                       dbHandle,
     nImO::StringVector &               resultList,
     CPtr(char)                         sqlStatement,
     const int                          columnOfInterest = 0,
     BindFunction                       doBinds = nullptr,
     CPtr(void)                         data = nullptr)
{
    ODL_ENTER(); //####
    ODL_P3("dbHandle = ", dbHandle, "resultList = ", &resultList, "data = ", data); //####
    ODL_I1("columnOfInterest = ", columnOfInterest); //####
    ODL_S1("sqlStatement = ", sqlStatement); //####
    bool    okSoFar = true;

    resultList.clear();
    try
    {
        if ((nullptr != dbHandle) && (0 <= columnOfInterest))
        {
            Ptr(sqlite3_stmt)   prepared = nullptr;
            int                 sqlRes = sqlite3_prepare_v2(dbHandle, sqlStatement,
                                                           static_cast<int>(strlen(sqlStatement)),
                                                           &prepared, nullptr);

            ODL_I1("sqlRes <- ", sqlRes); //####
            if ((SQLITE_OK == sqlRes) && (nullptr != prepared))
            {
                if (nullptr != doBinds)
                {
                    sqlRes = doBinds(prepared, data);
                    ODL_I1("sqlRes <- ", sqlRes); //####
                    okSoFar = (SQLITE_OK == sqlRes);
                }
                if (okSoFar)
                {
                    for (sqlRes = SQLITE_ROW; SQLITE_ROW == sqlRes; )
                    {
                        do
                        {
                            sqlRes = sqlite3_step(prepared);
                            ODL_I1("sqlRes <- ", sqlRes); //####
                            if (SQLITE_BUSY == sqlRes)
                            {
                                nImO::ConsumeSomeTime(owner, 10.0);
                            }
                        }
                        while (SQLITE_BUSY == sqlRes);
                        if (SQLITE_ROW == sqlRes)
                        {
                            // Gather the column data...
                            int colCount = sqlite3_column_count(prepared);

                            ODL_I1("colCount <- ", colCount); //####
                            if ((0 < colCount) && (columnOfInterest < colCount))
                            {
                                CPtr(char)  value = ReinterpretCast(CPtr(char), sqlite3_column_text(prepared, columnOfInterest));

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
                        okSoFar = false;
                    }
                }
                sqlite3_finalize(prepared);
            }
            else
            {
                ODL_LOG("! ((SQLITE_OK == sqlRes) && (nullptr != prepared))"); //####
                okSoFar = false;
            }
        }
        else
        {
            ODL_LOG("! ((nullptr != dbHandle) && (0 <= columnOfInterest))"); //####
            okSoFar = false;
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }

    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // performSQLstatementWithSingleColumnResults

/*! @brief Start a transaction.
 @param[in] owner The object to be used for reporting.
 @param[in] dbHandle The database to be modified.
 @return @c true if the transaction was initiated and @c false otherwise. */
static bool
doBeginTransaction
    (Ptr(nImO::ContextWithNetworking)   owner,
     Ptr(sqlite3)                       dbHandle)
{
    ODL_ENTER(); //####
    ODL_P1("dbHandle = ", dbHandle); //####
    bool okSoFar = true;

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            okSoFar = false;
        }
        else
        {
            static CPtr(char)   beginTransaction = "BEGIN TRANSACTION";

            okSoFar = performSQLstatementWithNoResultsNoArgs(owner, dbHandle, beginTransaction);
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // doBeginTransaction

/*! @brief End a transaction.
 @param[in] owner The object to be used for reporting.
 @param[in] database The database to be modified.
 @param[in] wasOK @c true if the transaction was successful and @c false otherwise.
 @return @c true if the transaction was closed successfully and @c false otherwise. */
static bool
doEndTransaction
    (Ptr(nImO::ContextWithNetworking)   owner,
     Ptr(sqlite3)                       dbHandle,
     const bool                         wasOK)
{
    ODL_ENTER(); //####
    ODL_P1("dbHandle = ", dbHandle); //####
    ODL_B1("wasOK = ", wasOK); //####
    bool    okSoFar = true;

    try
    {
        if (nullptr == dbHandle)
        {
            ODL_LOG("(nullptr == dbHandle)"); //####
            okSoFar = false;
        }
        else
        {
            static CPtr(char)   abortTransaction = "ROLLBACK TRANSACTION";
            static CPtr(char)   commitTransaction = "END TRANSACTION";

            okSoFar = performSQLstatementWithNoResultsNoArgs(owner, dbHandle, wasOK ? commitTransaction :
                                                             abortTransaction);
        }
    }
    catch (...)
    {
        ODL_LOG("Exception caught"); //####
        throw;
    }
    ODL_EXIT_B(okSoFar); //####
    return okSoFar;
} // doEndTransaction

/*! @brief Create the tables needed in the database.
 @param[in] owner The object to be used for reporting.
 @param[in] logging @c true if operations are to be logged.
 @parm[in,out] dbHandle The database handle to use.
 @return @c true if all the tables were successfully created. */
static bool
createTables
    (Ptr(nImO::ContextWithNetworking)   owner,
     const bool                         logging,
     Ptr(sqlite3)                       dbHandle)
{
    bool    okSoFar = true;
    
    ODL_ENTER();
    if (nullptr != dbHandle)
    {
        if ((nullptr != owner) && logging)
        {
            owner->report("creating tables.");
        }
        if (doBeginTransaction(owner, dbHandle))
        {
            static CPtr(char)   tableSQL[] =
            {
                "CREATE TABLE IF NOT EXISTS " NODES_T_ "(" NODENAME_C_ " " TEXTNOTNULL_ " " BINARY_ " PRIMARY KEY ON CONFLICT ABORT,"
                                                            NODEADDRESS_C_ " INTEGER, " NODEPORT_C_ " INTEGER)",
                "CREATE INDEX IF NOT EXISTS " NODES_NAME_I_ " ON " NODES_T_ "(" NODENAME_C_ ")"
            };
            static const size_t numTables = A_SIZE(tableSQL);

            for (size_t ii = 0; okSoFar && (ii < numTables); ++ii)
            {
                okSoFar = performSQLstatementWithNoResultsNoArgs(owner, dbHandle, tableSQL[ii]);
            }
            doEndTransaction(owner, dbHandle, okSoFar);
        }
    }
    ODL_EXIT_B(okSoFar);
    return okSoFar;
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
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result = SQLITE_MISUSE;

    try
    {
        int nodeNameIndex = sqlite3_bind_parameter_index(statement, "@" NODENAME_C_);
        int nodeAddressIndex = sqlite3_bind_parameter_index(statement, "@" NODEADDRESS_C_);
        int nodePortIndex = sqlite3_bind_parameter_index(statement, "@" NODEPORT_C_);

        if ((0 < nodeNameIndex) && (0 < nodeAddressIndex) && (0 < nodePortIndex))
        {
            CPtr(NodeInsertData)    nodeData = StaticCast(CPtr(NodeInsertData), stuff);
            std::string             name = nodeData->_name;
            uint32_t                address = nodeData->_address;
            uint16_t                port = nodeData->_port;

            result = sqlite3_bind_text(statement, nodeNameIndex, name.c_str(), StaticCast(int, name.length()), SQLITE_TRANSIENT);
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, nodeAddressIndex, address);
            }
            if (SQLITE_OK == result)
            {
                result = sqlite3_bind_int(statement, nodePortIndex, port);
            }
            if (SQLITE_OK != result)
            {
                ODL_S1("error description: ", sqlite3_errstr(result)); //####
            }
        }
        else
        {
            ODL_LOG("! ((0 < nodeNameIndex) && (0 < nodeAddressIndex) && (0 < nodePortIndex))"); //####
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
    ODL_ENTER(); //####
    ODL_P2("statement = ", statement, "stuff = ", stuff); //####
    int result = SQLITE_MISUSE;

    try
    {
        int nodeNameIndex = sqlite3_bind_parameter_index(statement, "@" NODENAME_C_);

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
        createTables(_owner, logging, _dbHandle);
    }
    else
    {
        std::string errorMessage(sqlite3_errstr(result));
        std::string prefix("Unable to open database: ");

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

bool
nImO::Registry::addNode
    (const std::string &    nodeName,
     const uint32_t         nodeAddress,
     const uint16_t         nodePort)
{
    bool    added = false;

    ODL_OBJENTER(); //####
    if (doBeginTransaction(_owner, _dbHandle))
    {
        NodeInsertData      data{nodeName, nodeAddress, nodePort};
        static CPtr(char)   insertIntoNodes = "INSERT INTO " NODES_T_ "(" NODENAME_C_ "," NODEADDRESS_C_ "," NODEPORT_C_ ") VALUES(@" NODENAME_C_
                                                ",@" NODEADDRESS_C_ ",@" NODEPORT_C_ ")";

        added = performSQLstatementWithNoResults(_owner, _dbHandle, insertIntoNodes, setupInsertIntoNodes, &data);
        doEndTransaction(_owner, _dbHandle, added);
    }
    ODL_OBJEXIT_B(added); //####
    return added;
} // nImO::Registry::addNode

bool
nImO::Registry::getNodeInformation
    (const std::string &    nodeName,
     uint32_t &             nodeAddress,
     uint16_t &             nodePort)
    const
{
    bool    found = false;

    ODL_OBJENTER(); //####
    if (doBeginTransaction(_owner, _dbHandle))
    {
        bool                okSoFar = true;
        StringVector        results1;
        StringVector        results2;
        static CPtr(char)   searchNodes = "SELECT " NODEADDRESS_C_ "," NODEPORT_C_ " FROM " NODES_T_ " WHERE " NODENAME_C_ "=@" NODENAME_C_;

        okSoFar = performSQLstatementWithDoubleColumnResults(_owner, _dbHandle, results1, results2, searchNodes, 0, 1, setupSearchNodes, &nodeName);
        if (okSoFar)
        {
            size_t  pos;

            found = true;
            nodeAddress = StaticCast(uint32_t, stoul(results1[0], &pos));
            if (0 == pos)
            {
                found = false;
            }
            nodePort = StaticCast(uint16_t, stoul(results2[0], &pos));
            if (0 == pos)
            {
                found = false;
            }
        }
        doEndTransaction(_owner, _dbHandle, okSoFar);
    }
    ODL_OBJEXIT_B(found); //####
    return found;
} // nImO::Registry::getNodeInformation

nImO::StringSet
nImO::Registry::getNodes
    (void)
    const
{
    StringSet   result;

    ODL_OBJENTER();
    if (doBeginTransaction(_owner, _dbHandle))
    {
        bool                okSoFar = true;
        StringVector        results;
        static CPtr(char)   searchNodes = "SELECT " NODENAME_C_ " FROM " NODES_T_;

        okSoFar = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchNodes);
        if (okSoFar)
        {
            for (size_t ii = 0; ii < results.size(); ++ii)
            {
                result.insert(results[ii]);
            }
        }
        doEndTransaction(_owner, _dbHandle, okSoFar);
    }
    ODL_OBJEXIT();
    return result;
} // nImO::Registry::getNodes

bool
nImO::Registry::nodePresent
    (const std::string &    nodeName)
{
    bool    found = false;

    ODL_OBJENTER(); //####
    if (doBeginTransaction(_owner, _dbHandle))
    {
        bool                okSoFar = true;
        StringVector        results;
        static CPtr(char)   searchNodes = "SELECT COUNT(*) FROM " NODES_T_ " WHERE " NODENAME_C_ "=@" NODENAME_C_;

        okSoFar = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, searchNodes, 0, setupSearchNodes, &nodeName);
        if (okSoFar)
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
        doEndTransaction(_owner, _dbHandle, okSoFar);
    }
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
    if (doBeginTransaction(_owner, _dbHandle))
    {
        bool                okSoFar = true;
        StringVector        results;
        static CPtr(char)   countNodes = "SELECT COUNT(*) FROM " NODES_T_;

        okSoFar = performSQLstatementWithSingleColumnResults(_owner, _dbHandle, results, countNodes);
        if (okSoFar)
        {
            size_t  pos;

            count = stoi(results[0], &pos);
            if (0 == pos)
            {
                count = -1;
            }
        }
        doEndTransaction(_owner, _dbHandle, okSoFar);
    }
    ODL_OBJEXIT_I(count); //####
    return count;
} // nImO::Registry::numNodes

bool
nImO::Registry::removeNode
    (const std::string &    nodeName)
{
    bool    removed = false;

    ODL_OBJENTER(); //####

    if (doBeginTransaction(_owner, _dbHandle))
    {
        static CPtr(char)   searchNodes = "DELETE FROM " NODES_T_ " WHERE " NODENAME_C_ "=@" NODENAME_C_;

        removed = performSQLstatementWithNoResults(_owner, _dbHandle, searchNodes, setupSearchNodes, &nodeName);
        doEndTransaction(_owner, _dbHandle, removed);
    }
    ODL_OBJEXIT_B(removed); //####
    return removed;
} // nImO::Registry::removeNode

#if defined(__APPLE__)
# pragma mark Global functions
#endif // defined(__APPLE__)

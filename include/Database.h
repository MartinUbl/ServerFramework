#ifndef __DATABASE_H_
#define __DATABASE_H_

#include <global.h>
#include "Singleton.h"

#ifdef _WIN32
 #include <windows.h>
 #include <mysql.h>
#else
 #include <mysql/mysql.h>
 #include <stdlib.h>
#endif

struct DBResult: public MYSQL_RES
{
    DBResult() {};
    ~DBResult() {};

    // obsolete
    DBResult operator=(MYSQL_RES* res)
    {
        return *this;
    };

    bool FetchRow()
    {
        row = mysql_fetch_row(this);
        if(row != NULL)
            return true;
        else
            return false;
    }

    int GetInt(int column = 0)
    {
        if(row)
            return atoi(row[column]);
        else
            return 0;
    }

    std::string GetString(int column = 0)
    {
        if(row)
            return row[column];
        else
            return "";
    }

    MYSQL_ROW row;
};

class DB_Connector
{
    public:
        DB_Connector() {};
        ~DB_Connector() {};

    protected:
        const char* server;
        const char* username;
        const char* password;
        const char* database;
};

class MySQL_DB_Connector: public DB_Connector
{
    public:
        MySQL_DB_Connector(): DB_Connector() {};
        ~MySQL_DB_Connector() {};

        void Start(const char* cserver, const char* cusername, const char* cpassword, const char* cdatabase);
        bool Connected()
        {
            if(connection)
                return true;
            else 
                return false;
        }
        const char* DBError()
        {
            return mysql_error(connection);
        }

        DBResult* ExecuteQuery(const char* query);

    protected:
        MYSQL *connection, mysql;
};

class MainDB_Connector: public MySQL_DB_Connector
{
    public:
        void Start(const char* cserver, const char* cusername, const char* cpassword, const char* cdatabase);
        bool Test();

    protected:
        //
};

static MainDB_Connector* sMainDB = Singleton<MainDB_Connector>::Instance();

#endif

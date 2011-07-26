#include <global.h>
#include "Database.h"

void MainDB_Connector::Start(const char* cserver, const char* cusername, const char* cpassword, const char* cdatabase)
{
    MySQL_DB_Connector::Start(cserver,cusername,cpassword,cdatabase);
}

bool MainDB_Connector::Test()
{
    DBResult* pRes = ExecuteQuery("SELECT 1 FROM server_info");
    if (pRes)
        return true;

    return false;
}

void MySQL_DB_Connector::Start(const char* cserver, const char* cusername, const char* cpassword, const char* cdatabase)
{
    server = cserver;
    username = cusername;
    password = cpassword;
    database = cdatabase;

    mysql_init(&mysql);
    connection = mysql_real_connect(&mysql,server,username,password,database,0,0,0);
}

DBResult* MySQL_DB_Connector::ExecuteQuery(const char *query)
{
    int result = mysql_query(&mysql,query);
    MYSQL_RES* ret = new MYSQL_RES;

    if(result == 0) //query ok
    {
        ret = mysql_store_result(connection);
        return static_cast<DBResult*>(ret);
    }
    else            //query failed
        return NULL;
}

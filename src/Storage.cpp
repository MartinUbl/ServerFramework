/*                                         *
*            Server Framework              *
*                                          *
*    Developed by: Cmaranec (Kennny)       *
*                                          *
*    Copyright (c) 2011                    *
*                                          */

#include <global.h>
#include "Storage.h"
#include "Database.h"

void GlobalStorage::LoadServerInfo()
{
    DBResult* pRes = sMainDB->ExecuteQuery("SELECT * FROM server_info;");
    if (!pRes || !pRes->FetchRow())
    {
        m_id = 0;
        m_serverName = "NULL";
        m_ip = "127.0.0.1";
        m_lock = 0;
        return;
    }

    m_id = pRes->GetInt(0);
    m_serverName = pRes->GetString(1);
    m_ip = pRes->GetString(2);
    m_lock = pRes->GetInt(3);
}

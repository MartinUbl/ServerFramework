/*                                         *
*            Server Framework              *
*                                          *
*    Developed by: Cmaranec (Kennny)       *
*                                          *
*    Copyright (c) 2011                    *
*                                          */

#include <global.h>
#include "NetworkHandlers.h"
#include "Log.h"

void Session::BroadcastPacket(SmartPacket* data)
{
    if (clientList.empty())
        return;

    for (std::list<Client*>::const_iterator itr = clientList.begin(); itr != clientList.end(); ++itr)
        SendPacket((*itr)->m_socket, data);
}

void Session::SendPacket(Client* pClient, SmartPacket* data)
{
    if (!pClient)
    {
        sLog->ErrorOut("Invalid (NULL) Client pointer as argument in Session::SendPacket");
        return;
    }

    SendPacket(pClient->m_socket, data);
}

void Session::SendPacket(SOCK socket, SmartPacket *data)
{
    //Total storage size + 4 bytes for opcode + 4 bytes for size
    size_t psize = data->GetSize() + 4 + 4;

    char* buff = new char[psize];
    unsigned int opcode = data->GetOpcode();
    memcpy(&buff[0],&opcode,sizeof(unsigned int));

    unsigned int size = (unsigned int)data->GetSize();
    memcpy(&buff[4],&size,sizeof(unsigned int));

    for(size_t i = 0; i < size; i++)
    {
        *data >> buff[8+i];
    }

    send(socket, buff, psize, 0);
}

SmartPacket* Session::BuildPacket(const char *buffer, uint32 size)
{
    if (size < 8)
    {
        sLog->ErrorOut("Received packet without smart header. Data: %s", buffer);
        return NULL;
    }

    unsigned int opcode, psize;

    //at first, parse opcode ID
    memcpy(&opcode,&buffer[0],sizeof(unsigned int));

    SmartPacket* packet = new SmartPacket(opcode);

    //next parse size
    memcpy(&psize,&buffer[4],sizeof(unsigned int));

    //and parse the body of packet
    for(size_t i = 0; i < psize; i++)
        *packet << (unsigned char)buffer[8+i];

    return packet;
}

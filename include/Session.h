#ifndef __SESSION_H_
#define __SESSION_H_

#include "Singleton.h"
#include "Packets/SmartPacket.h"

#include <list>

#ifdef _WIN32
 #include <windows.h>
 #include <winsock.h>

 #define SOCK SOCKET
 #define ADDRLEN int
#else
 #include <unistd.h>
 #include <netdb.h>
 #include <netinet/in.h>
 #include <sys/types.h>
 #include <sys/socket.h>

 #define SOCK int
 #define ADDRLEN socklen_t
#endif

// Network buffer length = 1 kB
// If necessary, you can change it
#define BUFFER_LEN 1*1024

class Client
{
    public:
        SOCK m_socket;
        hostent* m_host;
        sockaddr_in m_sockInfo;
        ADDRLEN m_addrLen;
};

class Session
{
    public:
        Session() {};
        ~Session() {};

        bool Startup();

        void Worker();
        void Acceptor();

        SmartPacket* BuildPacket(const char* buffer, uint32 size);
        void BroadcastPacket(SmartPacket* data);
        void SendPacket(Client* pClient, SmartPacket* data);
        void SendPacket(SOCK socket, SmartPacket* data);

        void ProcessPacket(SmartPacket* packet, Client* pSource);

    protected:
        std::list<Client*> clientList;

        SOCK m_socket;
        int m_port;
        sockaddr_in m_sockName;
};

static Session* sSession = Singleton<Session>::Instance();

extern void runSessionWorker();
extern void runSessionAcceptor();

#endif

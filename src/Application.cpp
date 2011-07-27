/*                                         *
*            Server Framework              *
*                                          *
*    Developed by: Cmaranec (Kennny)       *
*                                          *
*    Copyright (c) 2011                    *
*                                          */

#include <global.h>
#include "Application.h"
#include "Singleton.h"
#include "Log.h"
#include "Config.h"
#include "Database.h"
#include "Storage.h"
#include "Timer.h"
#include "Session.h"

#include <ctime>
#include <boost/thread.hpp>

void Application::init()
{
    sLog->init();
    sLog->StaticOut("---------------------------------");
    sLog->StaticOut("-    Simple Server Framework    -");
    sLog->StaticOut("-                               -");
    sLog->StaticOut("- Created by Cmaranec (Kennny)  -");
    sLog->StaticOut("- Copyright (c) 2011            -");
    sLog->StaticOut("- Feel free to modify           -");
    sLog->StaticOut("---------------------------------");
    sLog->StaticOut("");

    sLog->StaticOut(">> Loading config...");
    if (!sConfig->LoadConfig("main.conf"))
        abort("Loading config main.conf failed");
    sLog->StaticOut("Config loaded");

    sLog->StaticOut("");

    sLog->StaticOut(">> Connecting to database...");
    sMainDB->Start( sConfig->GetStringValue(CONFIG_DB_HOST),
                    sConfig->GetStringValue(CONFIG_DB_USER),
                    sConfig->GetStringValue(CONFIG_DB_PASSWORD),
                    sConfig->GetStringValue(CONFIG_DB_MAIN_DB));
    if (!sMainDB->Connected())
        abort("Cannot connect to main database");
    sLog->StaticOut("Connection estabilished");
    if (!sMainDB->Test())
        abort("Failed to communicate with database server");
    sLog->StaticOut("Data transfer OK");

    sLog->StaticOut("");

    sLog->StaticOut(">> Loading server info...");
    sGlobalStorage->LoadServerInfo();
    sLog->StaticOut("Server info loaded");

    sLog->StaticOut("");

    sLog->StaticOut(">> Starting network services...");
    sSession->Startup();
    sLog->StaticOut("Network services started");

    sLog->StaticOut("");
}

void Application::run()
{
    sLog->StaticOut("Successfully loaded!");
    sLog->StringOut("Running ID %u: %s",sGlobalStorage->GetId(),sGlobalStorage->GetServerName());
    sLog->StaticOut("");

    sLog->StaticOut(">> Starting threads..");
    sLog->StaticOut("Starting timer thread...");
    sLog->StaticOut("Starting network worker thread...");
    sLog->StaticOut("Starting network acceptor thread...");
    boost::thread timerWorker(runTimerWorker);
    boost::thread networkWorker(runSessionWorker);
    boost::thread networkAcceptor(runSessionAcceptor);

    uint64 sw = clock() / CLOCK_MOD;
    bool ready = false;
    for (uint64 wait = sw; wait <= sw+5000; wait = clock() / CLOCK_MOD)
    {
        ready = ThreadStatus.timer
            && ThreadStatus.sessionworker
            && ThreadStatus.sessionacceptor;

        if (ready)
            break;
    }
    if (!ready)
        abort("Failed to start all threads in 5 seconds time limit");

    sLog->StaticOut("");
    sLog->StaticOut("All threads running");

    std::string input; // Used for storing user input

    while(1)
    {
        input.clear();
        std::getline(std::cin,input);

        if (!HandleConsoleCommand(input.c_str()))
            sLog->StringOut("No such command.");
    }
}

void Application::abort(const char* reason)
{
    sLog->ErrorOut("An exception has occured while running application: %s",reason);
    sLog->StaticOut("Press any key to terminate application...");
    std::cin.get();
    exit(-1);
}

void Application::abort()
{
    exit(-1);
}

bool Application::HandleConsoleCommand(const char *input)
{
    int cmpres;   // Used for storing string compare result

    if ((cmpres = mstrcmp("broadcast",input)) == 1)
    {
        char* arg = new char[1024];
        strcpy(arg,&(input[10]));
        SmartPacket data(SMSG_SERVER_BROADCAST);
        data << arg;
        sSession->BroadcastPacket(&data);
        sLog->StringOut("Broadcasting of message '%s' was successful!",arg);
        return true;
    }
    else if (cmpres == 0)
    {
        sLog->StringOut("Usage: broadcast $message\n$message - message to be broadcast");
        return true;
    }
    else if ((cmpres = mstrcmp("exit",input)) == 0)
    {
        sLog->StringOut("Exit requested from console command. Exiting...");
        exit(0);
        return true;
    }
    else if (cmpres == 1)
    {
        sLog->StringOut("Usage: exit\nNo arguments");
        return true;
    }
    return false;
}

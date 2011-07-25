#include <global.h>
#include "Log.h"

#ifdef _WIN32
 #include <windows.h>
#endif

#include <iostream>
#include <cstdarg>
using namespace std;

void Log::StaticOut(const char* c)
{
    cout << c << endl;
}

void Log::StringOut(const char *str, ...)
{
    va_list argList;
    va_start(argList,str);
    char buf[2048];
    vsnprintf(buf,2048,str,argList);
    va_end(argList);
    cout << buf << endl;
}

void Log::ErrorOut(const char *str, ...)
{
    va_list argList;
    va_start(argList,str);
    char buf[2048];
    vsnprintf(buf,2048,str,argList);
    va_end(argList);
    SetConsoleColor(1);
    cout << "! Error: ";
    SetConsoleColor(0);
    cout << buf << endl;
}

void Log::NetworkOut(Client* pClient, const char *str, ...)
{
    if (!pClient)
    {
        ErrorOut("Invalid (NULL) Client pointer as argument in Log::NetworkOut");
        return;
    }

    va_list argList;
    va_start(argList,str);
    char buf[2048];
    vsnprintf(buf,2048,str,argList);
    va_end(argList);
    cout << "Network: ";
    SetConsoleColor(2);
    cout << pClient->m_socket;
    SetConsoleColor(0);
    cout << ": " << buf << endl;
}

void Log::init()
{
// Clear screen implemented only for Windows
#ifdef _WIN32
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '),
                             dwConSize,
                             coordScreen,
                             &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole,
                             csbi.wAttributes,
                             dwConSize,
                             coordScreen,
                             &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
#endif

    SetConsoleColor(0);
}

void Log::SetConsoleColor(int32 color)
{
//Implementation only for Windows..
#ifdef _WIN32
    switch (color)
    {
    case 0:    // White on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                        FOREGROUND_INTENSITY | FOREGROUND_RED |
                        FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case 1:    // Red on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                         FOREGROUND_INTENSITY | FOREGROUND_RED);
        break;
    case 2:    // Green on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                      FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        break;
    case 3:    // Yellow on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                      FOREGROUND_INTENSITY | FOREGROUND_RED |
                      FOREGROUND_GREEN);
        break;
    case 4:    // Blue on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                      FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        break;
    case 5:    // Magenta on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                     FOREGROUND_INTENSITY | FOREGROUND_RED |
                     FOREGROUND_BLUE);
        break;
    case 6:    // Cyan on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    FOREGROUND_INTENSITY | FOREGROUND_GREEN |
                    FOREGROUND_BLUE);
        break;
    case 7:    // Black on Gray
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                  BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
        break;
    case 8:    // Black on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                  BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                  BACKGROUND_RED | BACKGROUND_GREEN |
                  BACKGROUND_BLUE);
        break;
    case 9:    // Red on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                  BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                  BACKGROUND_RED | BACKGROUND_GREEN |
                  BACKGROUND_BLUE | FOREGROUND_RED);
        break;
    case 10:    // Green on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                 BACKGROUND_RED | BACKGROUND_GREEN |
                 BACKGROUND_BLUE | FOREGROUND_GREEN);
        break;
    case 11:    // Yellow on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                 BACKGROUND_RED | BACKGROUND_GREEN |
                 BACKGROUND_BLUE | FOREGROUND_RED |
                 FOREGROUND_GREEN);
        break;
    case 12:    // Blue on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                 BACKGROUND_RED | BACKGROUND_GREEN |
                 BACKGROUND_BLUE | FOREGROUND_BLUE);
        break;
    case 13:    // Magenta on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                 BACKGROUND_RED | BACKGROUND_GREEN |
                 BACKGROUND_BLUE | FOREGROUND_RED |
                 FOREGROUND_BLUE);
        break;
    case 14:    // Cyan on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                 BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                 BACKGROUND_RED | BACKGROUND_GREEN |
                 BACKGROUND_BLUE | FOREGROUND_GREEN |
                 FOREGROUND_BLUE);
        break;
    case 15:    // White on White
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
                BACKGROUND_RED | BACKGROUND_GREEN |
                BACKGROUND_BLUE | FOREGROUND_RED |
                FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    default:    // White on Black
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_INTENSITY | FOREGROUND_RED |
                FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
#endif
}

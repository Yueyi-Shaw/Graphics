#ifndef __DEBUG_CONSOLE__
#define __DEBUG_CONSOLE__

#ifdef _WIN32
#include <iostream>
#include <windows.h>

class DebugConsole
{
private:
    /* data */
public:
    DebugConsole(/* args */);
    ~DebugConsole();
};

DebugConsole::DebugConsole(/* args */)
{
    // allocate a new console
    AllocConsole();
    HWND consoleHandle = GetConsoleWindow();
    ShowWindow(consoleHandle, SW_SHOW);
    // test log
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    std::cout << "Hello, World!" << std::endl;
    std::cerr << "Error message" << std::endl;
}

DebugConsole::~DebugConsole()
{
}
#endif

#endif
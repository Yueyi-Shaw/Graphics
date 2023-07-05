#include "debug_toolkits.h"

OPGToolkits::OPGToolkits()
{
    // Allocate a new console
    AllocConsole();
    HWND consoleHandle = GetConsoleWindow();
    ShowWindow(consoleHandle, SW_SHOW);
    // redirect
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
    // Get the console screen buffer handle
    hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole_, FOREGROUND_WHITE);
}

OPGToolkits::~OPGToolkits()
{
    // wait key for exit
    std::cout << "Press any key to exit...";
    getchar();

    // Release the console
    FreeConsole();
}

void OPGToolkits::SetTextColor(WORD bit)
{
    HANDLE hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole_, bit);
}
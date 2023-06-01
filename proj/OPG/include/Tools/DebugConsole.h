#ifndef __DEBUG_CONSOLE__
#define __DEBUG_CONSOLE__

#ifdef _WIN32

#include <iostream>
#include <windows.h>

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_WHITE  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

class DebugConsole
{
private:
    HANDLE hConsole_;

public:
    DebugConsole()
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

        // Set the initial text color
        SetConsoleTextAttribute(hConsole_, FOREGROUND_GREEN);
        std::cout << "Debug Message" << std::endl;

        SetConsoleTextAttribute(hConsole_, FOREGROUND_RED);
        std::cerr << "Error Message" << std::endl;

        SetConsoleTextAttribute(hConsole_, FOREGROUND_YELLOW);
        std::cout << "Warning Message" << std::endl;

        SetConsoleTextAttribute(hConsole_, FOREGROUND_BLUE);
        std::cout << "Fileloading Message" << std::endl;

        SetConsoleTextAttribute(hConsole_, FOREGROUND_GREEN);
    }

    ~DebugConsole()
    {
        // Release the console
        FreeConsole();
    }
};

void LogError(const char *content)
{
    HANDLE hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole_, FOREGROUND_RED);
    std::cerr << content << std::endl;
    SetConsoleTextAttribute(hConsole_, FOREGROUND_GREEN);
}

void LogWarning(const char *content)
{
    HANDLE hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole_, FOREGROUND_YELLOW);
    std::cout << content << std::endl;
    SetConsoleTextAttribute(hConsole_, FOREGROUND_GREEN);
}

void LogFilePath(const char *content)
{
    HANDLE hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole_, FOREGROUND_BLUE);
    std::cout << content << std::endl;
    SetConsoleTextAttribute(hConsole_, FOREGROUND_GREEN);
}

void LogMessage(const char *content)
{
    HANDLE hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole_, FOREGROUND_GREEN);
    std::cout << content << std::endl;
}

#endif

#endif
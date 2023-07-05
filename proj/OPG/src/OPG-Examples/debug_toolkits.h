#ifndef DEBUG_TOOLKITS_H
#define DEBUG_TOOLKITS_H

#ifdef _WIN32
#include <iostream>
#include <windows.h>

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_PURPLE FOREGROUND_RED | FOREGROUND_BLUE
#define FOREGROUND_CYAN   FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_WHITE  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
class OPGToolkits
{
private:
    HANDLE hConsole_;

public:
    OPGToolkits();
    ~OPGToolkits();
    static void SetTextColor(WORD bit);
};

#endif

#endif // DEBUG_TOOLKITS_H
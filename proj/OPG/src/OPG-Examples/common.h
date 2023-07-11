#ifndef COMMON_H
#define COMMON_H

#define DEBUG // Define DEBUG before you include debug_toolkits.h

#ifdef _DEBUG
#include "debug_toolkits.h"
#endif /* _DEBUG */

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

#ifdef DEBUG
#else
#define DEBUG_PRINTF(...)
#define ERR_PRINT(...)
#endif

#endif // COMMON_H
#ifndef OPG_H
#define OPG_H

#ifdef _DEBUG
#include "debug_toolkits.h"
#endif /* _DEBUG */

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#define ERR_PRINT(...)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        OPGToolkits::SetTextColor(FOREGROUND_RED);                                                                     \
        printf(__VA_ARGS__);                                                                                           \
        OPGToolkits::SetTextColor(FOREGROUND_WHITE);                                                                   \
    }                                                                                                                  \
    while (0);
#else
#define DEBUG_PRINTF(...)
#define ERR_PRINT(...)
#endif

class OPGExample
{
protected:
    GLFWwindow *mWindow;
    bool mInitSuccess;

private:
    void init();
    void loop();
    void cleanup();

public:
    OPGExample(/* args */);
    ~OPGExample();
    void Checkout();
    void Start();
    void Stop();
    void LogCurrentSceneInfo();
};

#endif // OPG_H
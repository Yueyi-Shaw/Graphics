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
#else
#define DEBUG_PRINTF(...)
#endif

class OPGExample
{
private:
    void init();
    void loop();

public:
    OPGExample(/* args */);
    ~OPGExample();
    void CheckoutScene();
    void StartRenderring();
    void StopRenderring();
    void LogCurrentSceneInfo();
};

#endif // OPG_H
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

#include <memory>
#include "scene_manager.h"
#include "test_scene.h"

#ifdef DEBUG

#else
#define DEBUG_PRINTF(...)
#define ERR_PRINT(...)
#endif

class OPGExample
{
protected:
    SceneManager mSceneManager;
    std::shared_ptr<Scene> mScene;
    GLFWwindow *mWindow;
    bool mInitSuccess;

private:
    void init();
    void loop();
    void cleanup();
    void sceneui();

public:
    OPGExample(/* args */);
    ~OPGExample();
    void Checkout();
    void Start();
    void Stop();
    void LogCurrentSceneInfo();
};

#endif // OPG_H
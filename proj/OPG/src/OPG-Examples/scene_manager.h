#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "debug_toolkits.h"

#ifdef DEBUG

#else
#define DEBUG_PRINTF(...)
#define ERR_PRINT(...)
#endif

class Scene
{
protected:
    std::string mName;

private:
    /* data */
public:
    Scene(std::string name);
    ~Scene();
    virtual void GLRendering();
    virtual void ImguiRendering();
};

class SceneManager
{
protected:
    std::shared_ptr<Scene> mCurrentScene;
    std::vector<std::shared_ptr<Scene>> mSceneList;

private:
public:
    SceneManager();
    ~SceneManager();
    void RegisterScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> GetCurrentScene();
    void SwitchScene(uint16_t index);
};

#endif // SCENE_MANAGER_H
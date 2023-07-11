#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class Scene
{
protected:
    std::string mName;

private:
public:
    Scene(std::string name);
    ~Scene();
    std::string GetName();
    unsigned int GetTime()
    {
        return (unsigned int)(glfwGetTime() * 1000.0);
    }
    virtual void Init(){};
    virtual void Clean(){};
    virtual void GLRendering()    = 0;
    virtual void ImguiRendering() = 0;
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
    std::vector<std::shared_ptr<Scene>> GetSceneList();
    void SwitchScene(uint16_t index);
};

#endif // SCENE_MANAGER_H
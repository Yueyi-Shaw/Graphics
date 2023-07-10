#include "scene_manager.h"

Scene::Scene(std::string name = "untitled") : mName(name)
{
}

Scene::~Scene()
{
}

std::string Scene::GetName()
{
    return mName;
}

void Scene::GLRendering()
{
    glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Scene::ImguiRendering()
{
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::RegisterScene(std::shared_ptr<Scene> scene)
{
    mSceneList.push_back(scene);
    if (!mCurrentScene)
        mCurrentScene = scene;
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}

std::vector<std::shared_ptr<Scene>> SceneManager::GetSceneList()
{
    return mSceneList;
}

void SceneManager::SwitchScene(uint16_t index)
{
    if (index < 0 || index >= mSceneList.size())
    {
        ERR_PRINT("scene index error.");
        return;
    }
    mCurrentScene = mSceneList[index];
}
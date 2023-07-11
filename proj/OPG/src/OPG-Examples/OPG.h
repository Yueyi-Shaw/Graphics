#ifndef OPG_H
#define OPG_H

#include "scene_manager.h"
#include "scenes.h"

class OPGExample
{
protected:
    GLFWwindow *mWindow;

    // scenes
    SceneManager mSceneManager;
    std::shared_ptr<Scene> mScene;
    std::vector<const char *> mSceneNameList;
    int mCurrentIndex = 0;
    // flag
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
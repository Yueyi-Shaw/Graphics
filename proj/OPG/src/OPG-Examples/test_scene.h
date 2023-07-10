#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "scene_manager.h"

class TestScene : public Scene
{
private:
public:
    TestScene(std::string name);
    ~TestScene();
    void GLRendering() override;
    void ImguiRendering() override;
};

#endif // TEST_SCENE_H
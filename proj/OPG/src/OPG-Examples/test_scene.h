#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "scene_manager.h"

class TestScene : public Scene
{
private:
public:
    TestScene();
    ~TestScene();
    void GLRendering() override;
    void ImguiRendering() override;
};

#endif // TEST_SCENE_H
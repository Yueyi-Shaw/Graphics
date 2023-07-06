#include "test_scene.h"

TestScene::TestScene() : Scene("TEST_SCENE")
{
}

TestScene::~TestScene()
{
}

void TestScene::GLRendering()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void TestScene::ImguiRendering()
{
}

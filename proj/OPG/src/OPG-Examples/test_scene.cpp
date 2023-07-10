#include "test_scene.h"

TestScene::TestScene(std::string name = "TEST_SCENE") : Scene(name)
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
    ImGui::ShowDemoWindow();
}

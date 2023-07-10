#ifndef SCENES_H
#define SCENES_H

#include "scene_manager.h"

class Scene1 : public Scene
{
private:
public:
    Scene1(std::string name = "Scene1") : Scene(name){};
    ~Scene1(){};
    void GLRendering() override;
    void ImguiRendering() override;
};

class Scene2 : public Scene
{
private:
public:
    Scene2(std::string name = "Scene2") : Scene(name){};
    ~Scene2(){};
    void GLRendering() override;
    void ImguiRendering() override;
};

#endif // SCENE_H
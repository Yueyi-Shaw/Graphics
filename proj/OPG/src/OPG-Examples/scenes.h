#ifndef SCENES_H
#define SCENES_H

#include "scene_manager.h"
#include "model.h"

class Scene1 : public Scene
{
private:
    float aspect;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];

    GLint render_model_matrix_loc;
    GLint render_projection_matrix_loc;
    Shader *mShader;

public:
    Scene1(std::string name = "Scene1") : Scene(name)
    {
        Init();
    };
    ~Scene1()
    {
        Clean();
    };
    void Init() override;
    void Clean() override;
    void GLRendering() override;
    void ImguiRendering() override;
};

class Scene2 : public Scene
{
private:
public:
    Scene2(std::string name = "Scene2") : Scene(name)
    {
        Init();
    };
    ~Scene2()
    {
        Clean();
    };
    void Init() override;
    void Clean() override;
    void GLRendering() override;
    void ImguiRendering() override;
};

#endif // SCENE_H
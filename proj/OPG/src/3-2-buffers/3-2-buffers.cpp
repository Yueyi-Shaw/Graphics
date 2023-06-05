#include "Tools/AppTemplate.h"
#include "YueyiLibs/shader.h"
#include "YueyiLibs/model.h"
#include "YueyiLibs/camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

class BuffersExample : public ApplicationTemplate
{
private:
    // Member variables
    Shader *mShader;
    GLuint VAOs[1];
    GLuint VBOs[1];
    Model *mModel;

    enum Attrib_IDs
    {
        vPosition = 0
    };

public:
    BuffersExample(/* args */)
    {
    }
    ~BuffersExample()
    {
    }
    void Initialize(const char *title) override
    {
        ApplicationTemplate::Initialize(title);
        std::cout << "init start" << std::endl;
        static const GLfloat vertices[52][2] = {// Points
                                                {-0.8, -0.8},
                                                {0.8, 0.8},
                                                {0.8, -0.8},
                                                {-0.8, 0.8},
                                                // triangle
                                                {0., 0.},
                                                {0.05, 0.2},
                                                {0.1, 0.},
                                                {0.15, 0.2},
                                                {0.2, 0.},
                                                {0.25, 0.2},
                                                {0.3, 0.},
                                                {0.35, 0.2},
                                                {0.4, 0.},
                                                {0.45, 0.2},
                                                {0.5, 0.},
                                                {0.55, 0.2},
                                                // triangle strip
                                                {0., 0.3},
                                                {0.05, 0.5},
                                                {0.1, 0.3},
                                                {0.15, 0.5},
                                                {0.2, 0.3},
                                                {0.25, 0.5},
                                                {0.3, 0.3},
                                                {0.35, 0.5},
                                                {0.4, 0.3},
                                                {0.45, 0.5},
                                                {0.5, 0.3},
                                                {0.55, 0.5},
                                                // triangle fan
                                                {0., 0.6},
                                                {0.05, 0.8},
                                                {0.1, 0.6},
                                                {0.15, 0.8},
                                                {0.2, 0.6},
                                                {0.25, 0.8},
                                                {0.3, 0.6},
                                                {0.35, 0.8},
                                                {0.4, 0.6},
                                                {0.45, 0.8},
                                                {0.5, 0.6},
                                                {0.55, 0.8},
                                                // triangle fan
                                                {0., -0.6},
                                                {0.05, -0.8},
                                                {0.1, -0.6},
                                                {0.15, -0.8},
                                                {0.2, -0.6},
                                                {0.25, -0.8},
                                                {0.3, -0.6},
                                                {0.35, -0.8},
                                                {0.4, -0.6},
                                                {0.45, -0.8},
                                                {0.5, -0.6},
                                                {0.55, -0.8}};

        glCreateVertexArrays(1, VAOs);
        glCreateBuffers(1, VBOs);
        glNamedBufferStorage(VBOs[0], sizeof(vertices), vertices, 0);

        std::string vpath("../../../src/3-2-buffers/shader.vert");
        std::string fpath("../../../src/3-2-buffers/shader.frag");
        ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};

        mShader = new Shader(shaders);

        // load model
        const char *pFile = "../../../models\\DragonAttenuation\\glTF-Binary\\DragonAttenuation.glb";
        mModel            = new Model(pFile);

        // VBO
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(vPosition);
        std::cout << "init end" << std::endl;
    }
    void Display(bool auto_redraw) override
    {
        static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
        glClearBufferfv(GL_COLOR, 0, black);

        mShader->use();
        // mShader->setFloat("u_time", (GLfloat)glfwGetTime());
        // float resolution[2] = {800, 600};
        // mShader->setVec2("u_resolution", (GLfloat)resolution[0], (GLfloat)resolution[1]);

        // view/projection transformations
        glm::mat4 projection =
            glm::perspective(glm::radians(45.0f), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        mShader->setMat4("projection", projection);
        mShader->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model =
            glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // it's a bit too big for our scene, so scale it down
        mShader->setMat4("model", model);

        mModel->Draw(*mShader);
        ApplicationTemplate::Display();
    }

    void Finalize(void) override
    {
        delete mShader;
        glUseProgram(0);
        glDeleteVertexArrays(1, VAOs);
        glDeleteBuffers(1, VBOs);
    }

    void Resize(int width, int height) override
    {
        glViewport(0, 0, width, height);
    }
};

//--------------------------------------------------------------------
//
// main
//
int main(int argc, char **argv)
{
    BuffersExample app;
    app.AppStart();
}
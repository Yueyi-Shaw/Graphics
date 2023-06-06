#include "Tools/AppTemplate.h"
#include "YueyiLibs/shader.h"
#include "YueyiLibs/model.h"
#include "YueyiLibs/camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX     = WindowWidth / 2.0f;
float lastY     = WindowHeight / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

class BuffersExample : public ApplicationTemplate
{
private:
    // Member variables
    Shader *mShader;
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

        std::string vpath("../../../src/3-2-buffers/shader.vert");
        std::string fpath("../../../src/3-2-buffers/shader.frag");
        ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};

        mShader = new Shader(shaders);

        // load model
        const char *pFile = "../../../models/DragonAttenuation/glTF/DragonAttenuation.gltf";
        mModel            = new Model(pFile);

        stbi_set_flip_vertically_on_load(true);
        glEnable(GL_DEPTH_TEST);

        std::cout << "init end" << std::endl;
    }
    void Display(bool auto_redraw) override
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime          = currentFrame - lastFrame;
        lastFrame          = currentFrame;

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mShader->use();
        // view/projection transformations
        glm::mat4 projection =
            glm::perspective(glm::radians(camera.Zoom), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
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
    }

    void Resize(int width, int height) override
    {
        glViewport(0, 0, width, height);
    }

    void OnKey(int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_W:
            {
                camera.ProcessKeyboard(FORWARD, deltaTime);
                break;
            }
            case GLFW_KEY_S:
            {
                camera.ProcessKeyboard(BACKWARD, deltaTime);
                break;
            }
            case GLFW_KEY_A:
            {
                camera.ProcessKeyboard(LEFT, deltaTime);
                break;
            }
            case GLFW_KEY_D:
            {
                camera.ProcessKeyboard(RIGHT, deltaTime);
                break;
            }
            }
        }

        ApplicationTemplate::OnKey(key, scancode, action, mods);
    }

    void OnScoll(double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }

    void OnMouseMove(double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX      = xpos;
            lastY      = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
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
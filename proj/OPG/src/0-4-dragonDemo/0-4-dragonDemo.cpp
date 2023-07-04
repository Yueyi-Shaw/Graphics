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
bool mouseDown  = false;
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

        stbi_set_flip_vertically_on_load(true); // make sure you set this flag before load any models
        glEnable(GL_DEPTH_TEST);

        std::string vpath("../../../src/0-4-dragonDemo/shader.vert");
        std::string fpath("../../../src/0-4-dragonDemo/shader.frag");
        ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};

        mShader = new Shader(shaders);

        // load model
        const char *pFile = "../../../models/DragonAttenuation/glTF/DragonAttenuation.gltf";
        mModel            = new Model(pFile);

        // draw in wireframe
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
        model           = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model           = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model           = glm::scale(model, glm::vec3(0.2f));
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
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            // LogMessage("GLFW EVENT:" + key);
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
            case GLFW_MOUSE_BUTTON_1:
            {
                mouseDown = true;
                break;
            }
            }
        }
        else if (action == GLFW_RELEASE)
        {
            // LogMessage("GLFW_RELEASE");
            switch (key)
            {
            case GLFW_MOUSE_BUTTON_1:
            {
                mouseDown = false;
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

        if (!mouseDown)
        {
            lastX = xpos;
            lastY = ypos;
            return;
        }

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

    void OnMouseButton(int button, int action, int mods)
    {
        std::string content = "GLFW EVENT: " + to_string(action) + " KEY: " + to_string(button);
        // LogMessage(content.c_str());
        if (action == GLFW_PRESS)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_1:
            {
                mouseDown = true;
                break;
            }
            }
        }
        else if (action == GLFW_RELEASE)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_1:
            {
                mouseDown = false;
                break;
            }
            }
        }
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
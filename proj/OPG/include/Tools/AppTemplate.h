#ifndef __APP_TEMPLATE_H__
#define __APP_TEMPLATE_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifdef _DEBUG
// console
#include "Tools/DebugConsole.h"
#endif /* _DEBUG */
#define BUFFER_OFFSET(a) ((void *)(a))

const int WindowWidth  = 800;
const int WindowHeight = 600;

class ApplicationTemplate
{
protected:
    inline ApplicationTemplate(void)
    {
    }
    virtual ~ApplicationTemplate(void)
    {
    }
    static ApplicationTemplate *app_instance;
    GLFWwindow *m_pWindow;
    DebugConsole m_console;

    static void window_size_callback(GLFWwindow *window, int width, int height)
    {
        ApplicationTemplate *pThis = (ApplicationTemplate *)glfwGetWindowUserPointer(window);

        pThis->Resize(width, height);
    }
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        ApplicationTemplate *pThis = (ApplicationTemplate *)glfwGetWindowUserPointer(window);

        pThis->OnKey(key, scancode, action, mods);
    }
    static void char_callback(GLFWwindow *window, unsigned int codepoint)
    {
        ApplicationTemplate *pThis = (ApplicationTemplate *)glfwGetWindowUserPointer(window);

        pThis->OnChar(codepoint);
    }
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        ApplicationTemplate *pThis = (ApplicationTemplate *)glfwGetWindowUserPointer(window);

        pThis->OnScoll(xoffset, yoffset);
    }
    static void cursor_callback(GLFWwindow *window, double xposIn, double yposIn)
    {
        ApplicationTemplate *pThis = (ApplicationTemplate *)glfwGetWindowUserPointer(window);

        pThis->OnMouseMove(xposIn, yposIn);
    }
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        ApplicationTemplate *pThis = (ApplicationTemplate *)glfwGetWindowUserPointer(window);

        pThis->OnMouseButton(button, action, mods);
    }
    unsigned int app_time()
    {
        return (unsigned int)(glfwGetTime() * 1000.0);
    }

#ifdef _DEBUG
    static void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                             const GLchar *message, const GLvoid *userParam)
    {
        OutputDebugStringA(message);
        OutputDebugStringA("\n");
    }
#endif
public:
    void AppStart(const char *title = 0)
    {
        Initialize(title);
        MainLoop();
        Finalize();
    }

    void MainLoop(void)
    {
        do
        {
            Display();
            glfwPollEvents();
        }
        while (!glfwWindowShouldClose(m_pWindow));
    }

    virtual void Initialize(const char *title = 0)
    {
        glfwInit();

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
        m_pWindow = glfwCreateWindow(WindowWidth, WindowHeight, title ? title : "OpenGL Application", nullptr, nullptr);
        glfwSetWindowUserPointer(m_pWindow, this);
        glfwSetWindowSizeCallback(m_pWindow, window_size_callback);
        glfwSetKeyCallback(m_pWindow, key_callback);
        glfwSetCharCallback(m_pWindow, char_callback);
        glfwSetScrollCallback(m_pWindow, scroll_callback);
        glfwSetCursorPosCallback(m_pWindow, cursor_callback);
        glfwSetMouseButtonCallback(m_pWindow, mouse_button_callback);

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return;
        }
        // glad populates global constants after loading to indicate,
        // if a certain extension/version is available.
        printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

        Resize(WindowWidth, WindowHeight);

#ifdef _DEBUG
        if (glDebugMessageCallbackARB != nullptr)
            glDebugMessageCallbackARB(DebugOutputCallback, this);
#endif
    }

    virtual void Display(bool auto_redraw = true)
    {
        glfwSwapBuffers(m_pWindow);
    }

    virtual void Finalize(void)
    {
    }

    virtual void Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    virtual void OnKey(int key, int scancode, int action, int mods)
    { /* NOTHING */
    }

    virtual void OnChar(unsigned int codepoint)
    { /* NOTHING */
    }

    virtual void OnScoll(double xoffset, double yoffset)
    { /* NOTHING */
    }

    virtual void OnMouseMove(double xoffset, double yoffset)
    { /* NOTHING */
    }

    virtual void OnMouseButton(int button, int action, int mods)
    { /* NOTHING */
    }
};

#endif
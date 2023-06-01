#ifndef __APP_TEMPLATE_H__
#define __APP_TEMPLATE_H__

#include "Tools/GLlib.h"

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
    unsigned int app_time()
    {
        return (unsigned int)(glfwGetTime() * 1000.0);
    }

#ifdef _DEBUG
    static void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                             const GLchar *message, GLvoid *userParam)
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

        glfwMakeContextCurrent(m_pWindow);

        gl3wInit();

        Resize(WindowWidth, WindowHeight);

#ifdef _DEBUG
        if (glDebugMessageCallbackARB != NULL)
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
};

#endif
//////////////////////////////////////////////////////////////////////
//
//  triangles.cpp
//
//////////////////////////////////////////////////////////////////////

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "YueyiLibs/shader.h"
#include "Tools/DebugConsole.h"

enum VAO_IDs
{
    Triangles,
    NumVAOs
};
enum Buffer_IDs
{
    ArrayBuffer,
    NumBuffers
};
enum Attrib_IDs
{
    vPosition = 0
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

//--------------------------------------------------------------------
//
// init
//

void init(void)
{
    std::cout << "init start" << std::endl;
    static const GLfloat vertices[NumVertices][2] = {{-0.90, -0.90},                               // Triangle 1
                                                     {0.85, -0.90},  {-0.90, 0.85}, {0.90, -0.85}, // Triangle 2
                                                     {0.90, 0.90},   {-0.85, 0.90}};

    glCreateVertexArrays(NumVAOs, VAOs);

    glCreateBuffers(NumBuffers, Buffers);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

    std::string vpath("./media/shaders/triangles/triangles.vert");
    std::string fpath("./media/shaders/triangles/triangles.frag");
    ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};
    Shader mShader        = (shaders);

    mShader.use();

    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(vPosition);
    std::cout << "init end" << std::endl;
}

//--------------------------------------------------------------------
//
// display
//

void display(void)
{
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

//--------------------------------------------------------------------
//
// main
//

int main(int argc, char **argv)
{
    DebugConsole console;
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(640, 480, "Triangles", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    init();

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
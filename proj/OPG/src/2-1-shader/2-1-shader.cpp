//////////////////////////////////////////////////////////////////////
//
//  triangles.cpp
//
//////////////////////////////////////////////////////////////////////

#include "vgl.h"
#include "LoadShaders.h"
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
const int WindowWidth = 640;
const int WindowHeight = 480;
GLuint u_timeLoc;
GLuint u_resolutionLoc;

//--------------------------------------------------------------------
//
// init
//

void init(void)
{
    std::cout << "init start" << std::endl;
    static const GLfloat vertices[NumVertices][2] =
        {
            {-1.0, -1.0}, // Triangle 1
            {1.0, -1.0},
            {-1.0, 1.0},
            {1.0, -1.0}, // Triangle 2
            {1.0, 1.0},
            {-1.0, 1.0}};

    glCreateVertexArrays(NumVAOs, VAOs);

    glCreateBuffers(NumBuffers, Buffers);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices),
                         vertices, 0);

    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER, "../../../src\\2-1-shader\\shader.vert"},
        {GL_FRAGMENT_SHADER, "../../../src\\2-1-shader\\shader.frag"},
        {GL_NONE, NULL}};

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    u_timeLoc = glGetUniformLocation(program, "u_time");
    u_resolutionLoc = glGetUniformLocation(program, "u_resolution");

    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                          GL_FALSE, 0, BUFFER_OFFSET(0));
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

    if (u_timeLoc != -1)
    {
        glUniform1f(u_timeLoc, (float)glfwGetTime());
    }
    if (u_resolutionLoc != -1)
    {
        float resolution[2] = {WindowWidth, WindowHeight};
        glUniform2fv(u_resolutionLoc, 1, resolution);
    }

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

    GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight, "Shader", NULL, NULL);

    glfwMakeContextCurrent(window);
    gl3wInit();

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
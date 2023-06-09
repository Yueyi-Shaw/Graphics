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
const int WindowWidth    = 640;
const int WindowHeight   = 480;

Shader *mShader1;
Shader *mShader2;

GLuint programs[3];
GLuint pipelines[2];
GLuint p1_time_loc;
GLuint p1_resolution_loc;
GLuint p2_time_loc;
GLuint p2_resolution_loc;
// read func
extern "C"
{
    static const GLchar *ReadShader(const char *filename)
    {
#ifdef WIN32
        FILE *infile;
        fopen_s(&infile, filename, "rb");
#else
        FILE *infile = fopen(filename, "rb");
#endif // WIN32

        if (!infile)
        {
#ifdef _DEBUG
            std::cerr << "Unable to open file '" << filename << "'" << std::endl;
#endif /* DEBUG */
            return NULL;
        }

        fseek(infile, 0, SEEK_END);
        int len = ftell(infile);
        fseek(infile, 0, SEEK_SET);

        GLchar *source = new GLchar[len + 1];

        fread(source, 1, len, infile);
        fclose(infile);

        source[len] = 0;

        return const_cast<const GLchar *>(source);
    }
}
//--------------------------------------------------------------------
//
// init
//

void init(void)
{
    std::cout << "init start" << std::endl;
    static const GLfloat vertices[NumVertices][2] = {{-1.0, -1.0},                           // Triangle 1
                                                     {1.0, -1.0},  {-1.0, 1.0}, {1.0, -1.0}, // Triangle 2
                                                     {1.0, 1.0},   {-1.0, 1.0}};

    glCreateVertexArrays(NumVAOs, VAOs);

    glCreateBuffers(NumBuffers, Buffers);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

    // use multiple shader program
    // shader program1
    std::string vpath("../../../src/2-1-shader/shader.vert");
    std::string fpath("../../../src/2-1-shader/shader.frag");
    ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};

    mShader1 = new Shader(shaders);
    // shader program2
    std::string vpath2("../../../src/2-2-advanced/advanced_shader.vert");
    std::string fpath2("../../../src/2-2-advanced/advanced_shader.frag");
    ShaderInfo shaders2[3] = {{GL_VERTEX_SHADER, vpath2, 0}, {GL_FRAGMENT_SHADER, fpath2, 0}, {GL_NONE, "", 0}};

    mShader2 = new Shader(shaders2);
    // use program pipeline
    const GLchar *vertex_source = ReadShader(shaders[0].filename.c_str());
    programs[0]                 = glCreateShaderProgramv(shaders[0].type, 1, &vertex_source);
    delete[] vertex_source;

    const GLchar *frag_source1 = ReadShader(shaders[1].filename.c_str());
    programs[1]                = glCreateShaderProgramv(shaders[1].type, 1, &frag_source1);
    delete[] frag_source1;

    const GLchar *frag_source2 = ReadShader(shaders2[1].filename.c_str());
    programs[2]                = glCreateShaderProgramv(shaders2[1].type, 1, &frag_source2);
    delete[] frag_source2;

    p1_time_loc       = glGetUniformLocation(programs[1], "u_time");
    p1_resolution_loc = glGetUniformLocation(programs[1], "u_resolution");
    p2_time_loc       = glGetUniformLocation(programs[2], "u_time");
    p2_resolution_loc = glGetUniformLocation(programs[2], "u_resolution");

    glCreateProgramPipelines(GLsizei(2), pipelines);
    glUseProgramStages(pipelines[0], GL_VERTEX_SHADER_BIT, programs[0]);
    glUseProgramStages(pipelines[0], GL_FRAGMENT_SHADER_BIT, programs[1]);
    glUseProgramStages(pipelines[1], GL_VERTEX_SHADER_BIT, programs[0]);
    glUseProgramStages(pipelines[1], GL_FRAGMENT_SHADER_BIT, programs[2]);
    // VBO
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void *)(0));
    glEnableVertexAttribArray(vPosition);
    std::cout << "init end" << std::endl;
}

//--------------------------------------------------------------------
//
// display_traditional
//
void display_traditional(void)
{
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);

    // traditional way
    mShader1->use();
    mShader1->setFloat("u_time", (GLfloat)glfwGetTime());
    mShader1->setVec2("u_resolution", 800.0f, 600.0f);
    mShader2->use();
    mShader2->setFloat("u_time", (GLfloat)glfwGetTime());
    mShader2->setVec2("u_resolution", 800.0f, 600.0f);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 3, NumVertices / 2);
}

//--------------------------------------------------------------------
//
// display_traditional
//
void display_new(void)
{
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);

    // traditional way
    glBindProgramPipeline(pipelines[0]);
    if (p1_time_loc != -1)
    {
        glProgramUniform1f(programs[1], p1_time_loc, (float)glfwGetTime()); // use glProgramUniform instead of glUniform
    }
    if (p1_resolution_loc != -1)
    {
        float resolution[2] = {WindowWidth, WindowHeight};
        glProgramUniform2fv(programs[1], p1_resolution_loc, 1, resolution);
    }
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices / 2);

    glBindProgramPipeline(pipelines[1]);
    if (p2_time_loc != -1)
    {
        glProgramUniform1f(programs[2], p2_time_loc, (float)glfwGetTime());
    }
    if (p2_resolution_loc != -1)
    {
        float resolution[2] = {WindowWidth, WindowHeight};
        glProgramUniform2fv(programs[2], p2_resolution_loc, 1, resolution);
    }
    // glUseProgram(program2); // this line will replace pipeline binding
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 3, NumVertices / 2);
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
        // display_traditional();
        display_new();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete mShader1;
    delete mShader2;

    glfwDestroyWindow(window);

    glfwTerminate();
}
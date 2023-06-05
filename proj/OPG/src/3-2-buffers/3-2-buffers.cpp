#include "Tools/AppTemplate.h"
#include "YueyiLibs/shader.h"
class BuffersExample : public ApplicationTemplate
{
private:
    // Member variables
    Shader *mShader;
    GLuint VAOs[1];
    GLuint VBOs[1];
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

        std::string vpath("../../../src/3-1-primitives/shader.vert");
        std::string fpath("../../../src/3-1-primitives/shader.frag");
        ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};

        mShader = new Shader(shaders);

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
        mShader->setFloat("u_time", (GLfloat)glfwGetTime());
        float resolution[2] = {800, 600};
        mShader->setVec2("u_resolution", (GLfloat)resolution[0], (GLfloat)resolution[1]);

        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_FILL);

        glFrontFace(GL_CW);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // draw points
        // glEnable(GL_POINT_SPRITE); // use gl_PointCoord to see effects
        // glEnable(GL_PROGRAM_POINT_SIZE);
        // glPointSize(64.0f);
        // glBindVertexArray(VAOs[0]);
        // glDrawArrays(GL_POINTS, 0, 4);

        // draw lines
        // glLineWidth(64.0f);
        // glDrawArrays(GL_LINES, 0, 4);
        // glDrawArrays(GL_LINE_LOOP, 0, 4);
        // glDrawArrays(GL_LINE_STRIP, 0, 4);

        // draw triangle
        glDrawArrays(GL_TRIANGLES, 4, 12);
        glDrawArrays(GL_TRIANGLE_STRIP, 16, 12);
        glDrawArrays(GL_TRIANGLE_FAN, 28, 12);
        glDrawArrays(GL_TRIANGLE_FAN, 40, 12);
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
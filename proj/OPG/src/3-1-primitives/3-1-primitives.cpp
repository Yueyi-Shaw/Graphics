#include "Tools/AppTemplate.h"

class PrimitivesExample : public ApplicationTemplate
{
private:
    // Member variables
    GLuint render_prog;
    GLuint VAOs[1];
    GLuint VBOs[1];
    GLuint u_timeLoc1;
    GLuint u_resolutionLoc1;
    enum Attrib_IDs
    {
        vPosition = 0
    };

public:
    PrimitivesExample(/* args */) {}
    ~PrimitivesExample() {}
    void Initialize(const char *title) override
    {
        ApplicationTemplate::Initialize(title);
        std::cout << "init start" << std::endl;
        static const GLfloat vertices[40][2] =
            {
                // Points
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
                {0.55, 0.8}};

        glCreateVertexArrays(1, VAOs);
        glCreateBuffers(1, VBOs);
        glNamedBufferStorage(VBOs[0], sizeof(vertices),
                             vertices, 0);

        ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "../../../src\\3-1-primitives\\shader.vert"},
            {GL_FRAGMENT_SHADER, "../../../src\\3-1-primitives\\shader.frag"},
            {GL_NONE, NULL}};

        render_prog = LoadShaders(shaders);

        u_timeLoc1 = glGetUniformLocation(render_prog, "u_time");
        u_resolutionLoc1 = glGetUniformLocation(render_prog, "u_resolution");

        // VBO
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                              GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(vPosition);
        std::cout << "init end" << std::endl;
    }
    void Display(bool auto_redraw) override
    {
        static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
        glClearBufferfv(GL_COLOR, 0, black);

        glUseProgram(render_prog);
        if (u_timeLoc1 != -1)
        {
            glUniform1f(u_timeLoc1, (GLfloat)glfwGetTime());
        }
        if (u_resolutionLoc1 != -1)
        {
            float resolution[2] = {800, 600};
            glUniform2f(u_resolutionLoc1, (GLfloat)resolution[0], (GLfloat)resolution[1]);
        }

        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_FILL);

        glFrontFace(GL_CW);
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
        ApplicationTemplate::Display();
    }

    void Finalize(void) override
    {
        glUseProgram(0);
        glDeleteProgram(render_prog);
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
    PrimitivesExample app;
    app.AppStart();
}
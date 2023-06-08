#include "Tools/AppTemplate.h"
#include "YueyiLibs/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Define USE_PRIMITIVE_RESTART to 0 to use two separate draw commands
#define USE_PRIMITIVE_RESTART 0

class BuffersExample : public ApplicationTemplate
{
private:
    // Member variables
    float aspect;
    GLuint vao[1];
    GLuint vbo[1];
    GLuint ebo[1];

    GLint render_model_matrix_loc;
    GLint render_projection_matrix_loc;
    Shader *mShader;

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
        mShader               = new Shader(shaders);

        mShader->use();

        // init data
        // 8 corners of a cube, side length 2, centered on the origin
        static const GLfloat cube_positions[] = {
            -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
            1.0f,  -1.0f, -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f, 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f};

        // Color for each vertex
        static const GLfloat cube_colors[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                              1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                              0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f};

        // Indices for the triangle strips
        static const GLushort cube_indices[] = {
            0,      1, 2, 3, 6, 7, 4, 5, // First strip
            0xFFFF,                      // <<-- This is the restart index
            2,      6, 0, 4, 1, 5, 3, 7  // Second strip
        };

        // Set up the element array buffer
        glGenBuffers(1, ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

        // Set up the vertex attributes
        glGenVertexArrays(1, vao);
        glBindVertexArray(vao[0]);

        glGenBuffers(1, vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(cube_positions));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // gl global settings
        glEnable(GL_DEPTH_TEST);

        std::cout << "init end" << std::endl;
    }
    void Display(bool auto_redraw) override
    {
        float t        = float(app_time() & 0x1FFF) / float(0x1FFF);
        static float q = 0.0f;
        static const glm::vec3 X(1.0f, 0.0f, 0.0f);
        static const glm::vec3 Y(0.0f, 1.0f, 0.0f);
        static const glm::vec3 Z(0.0f, 0.0f, 1.0f);

        // Setup
        glEnable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate simple shading program
        mShader->use();

        // Set up the model and projection matrix
        glm::mat4 model_matrix = glm::mat4(1.0f);
        model_matrix           = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, -5.0f)) *
                       glm::rotate(model_matrix, glm::radians(t * 360.0f), Y) *
                       glm::rotate(model_matrix, glm::radians(t * 720.0f), Z);
        glm::mat4 projection_matrix(glm::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));

        mShader->setMat4("model_matrix", model_matrix);
        mShader->setMat4("projection_matrix", projection_matrix);

        // Set up for a glDrawElements call
        glBindVertexArray(vao[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

#if USE_PRIMITIVE_RESTART
        // When primitive restart is on, we can call one draw command
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xFFFF);
        glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
#else
        // Without primitive restart, we need to call two draw commands
        glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
        glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, (const GLvoid *)(9 * sizeof(GLushort)));
#endif
        ApplicationTemplate::Display();
    }

    void Finalize(void) override
    {
        delete mShader;
        glUseProgram(0);
        glDeleteVertexArrays(1, vao);
        glDeleteBuffers(1, vbo);
    }

    void Resize(int width, int height) override
    {
        glViewport(0, 0, width, height);
        aspect = float(height) / float(width);
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
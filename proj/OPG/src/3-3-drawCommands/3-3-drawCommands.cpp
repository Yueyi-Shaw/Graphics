#include "Tools/AppTemplate.h"
#include "YueyiLibs/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static inline float random_float()
{
    float res;
    unsigned int tmp;
    static unsigned int seed = 0x13371337;

    seed *= 16807;

    tmp = seed ^ (seed >> 4) ^ (seed << 15);

    *((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}

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

        std::string vpath("../../../src/3-3-drawCommands/shader.vert");
        std::string fpath("../../../src/3-3-drawCommands/shader.frag");
        ShaderInfo shaders[3] = {{GL_VERTEX_SHADER, vpath, 0}, {GL_FRAGMENT_SHADER, fpath, 0}, {GL_NONE, "", 0}};
        mShader               = new Shader(shaders);

        mShader->use();

        // A single triangle
        static const GLfloat vertex_positions[] = {
            -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
        };

        // Color for each vertex
        static const GLfloat vertex_colors[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                                                1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f};

        // Indices for the triangle strips
        static const GLushort vertex_indices[] = {0, 1, 2};

        // Set up the element array buffer
        glGenBuffers(1, ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

        // Set up the vertex attributes
        glGenVertexArrays(1, vao);
        glBindVertexArray(vao[0]);

        glGenBuffers(1, vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // gl global settings
        glEnable(GL_CULL_FACE);
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate simple shading program
        mShader->use();

        // Set up the model and projection matrix
        glm::mat4 projection_matrix(glm::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
        mShader->setMat4("projection_matrix", projection_matrix);

        // Set up for a glDrawElements call
        glBindVertexArray(vao[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

        glm::mat4 model_matrix = glm::mat4(1.0f);

        // Draw Arrays...
        model_matrix = glm::translate(model_matrix, glm::vec3(-3.0f, 0.0f, -5.0f));
        mShader->setMat4("model_matrix", model_matrix);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // DrawElements
        model_matrix = glm::translate(model_matrix, glm::vec3(-1.0f, 0.0f, -5.0f));
        mShader->setMat4("model_matrix", model_matrix);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

        // DrawElementsBaseVertex
        model_matrix = glm::translate(model_matrix, glm::vec3(1.0f, 0.0f, -5.0f));
        mShader->setMat4("model_matrix", model_matrix);
        glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

        // DrawArraysInstanced
        model_matrix = glm::translate(model_matrix, glm::vec3(3.0f, 0.0f, -5.0f));
        mShader->setMat4("model_matrix", model_matrix);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
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
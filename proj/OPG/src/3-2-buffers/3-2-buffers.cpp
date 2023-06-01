#include "Tools/AppTemplate.h"
#include "Tools/shader.h"
class BuffersExample : public ApplicationTemplate
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
    BuffersExample(/* args */)
    {
    }
    ~BuffersExample()
    {
    }
    void Initialize(const char *title) override
    {
        ApplicationTemplate::Initialize(title);
    }
    void Display(bool auto_redraw) override
    {
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
    BuffersExample app;
    app.AppStart();
}
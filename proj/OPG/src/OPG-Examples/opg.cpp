#include "opg.h"

OPGExample::OPGExample()
{
    init();
}

OPGExample::~OPGExample()
{
    cleanup();
}

void OPGExample::sceneui()
{
    if (ImGui::Begin("Scene Switcher"))
    {
        int currentScene    = 0;
        const char *items[] = {"Scene 1", "Scene 2", "Scene 3"};
        if (ImGui::Combo("Scenes", (int *)&currentScene, items, IM_ARRAYSIZE(items)))
        {
        }
    }
    ImGui::End();
}

void OPGExample::init()
{
    DEBUG_PRINTF("enter OPGExample::init()\n");
    // init GLFW
    DEBUG_PRINTF("OPGExample::init() load glfw\n");
    if (!glfwInit())
        DEBUG_PRINTF("OPGExample::init() glfwInit() failed\n");
    // Create a GLFW window
    mWindow = glfwCreateWindow(1280, 720, "OPG Example", NULL, NULL);
    if (!mWindow)
    {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(mWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DEBUG_PRINTF("Failed to initialize OpenGL context\n");
        return;
    }
    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    DEBUG_PRINTF("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // Initialize ImGui
    DEBUG_PRINTF("OPGExample::init() load imgui\n");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // Load Scene
    std::shared_ptr<TestScene> scene = std::make_shared<TestScene>();
    mSceneManager.RegisterScene(scene);

    mInitSuccess = true;
    DEBUG_PRINTF("OPGExample::init() %i \n", mInitSuccess);
}

void OPGExample::loop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // IMGUI part
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // TODO: draw imgui stuff here
        sceneui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mWindow);
    }
}

void OPGExample::cleanup()
{
    DEBUG_PRINTF("enter OPGExample::cleanup()\n");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void OPGExample::Start()
{
    if (!mInitSuccess)
    {
        ERR_PRINT("OPGExample::Start() : opg render is uninitlized.")
        return;
    }
    loop();
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    // init debug toolkits
    OPGToolkits toolkits;
#endif

    OPGExample opg;
    opg.Start();
    return 0;
}
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
    static int last_scen_index = mCurrentIndex;
    if (ImGui::Begin("Scene Switcher"))
    {
        if (ImGui::Combo("ScenesList", &mCurrentIndex, mSceneNameList.data(), mSceneNameList.size()))
        {
            if (mCurrentIndex != last_scen_index)
            {
                mSceneManager.SwitchScene(mCurrentIndex);
                mScene = mSceneManager.GetCurrentScene();
                last_scen_index = mCurrentIndex;
            }
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
    std::shared_ptr<TestScene> scene1 = std::make_shared<TestScene>("TEST1");
    std::shared_ptr<Scene> scene2     = std::make_shared<Scene>("TEST2");
    mSceneManager.RegisterScene(scene1);
    mSceneManager.RegisterScene(scene2);
    mScene        = mSceneManager.GetCurrentScene();
    int scene_num = mSceneManager.GetSceneList().size();
    for (auto item : mSceneManager.GetSceneList())
    {
        const char *tmp = new char[item->GetName().length() + 1];
        std::strcpy(const_cast<char *>(tmp), item->GetName().c_str());
        mSceneNameList.push_back(tmp);
    }

    mInitSuccess = true;
    DEBUG_PRINTF("OPGExample::init() %i \n", mInitSuccess);
}

void OPGExample::loop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        // GL part
        mScene->GLRendering();

        // IMGUI part
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // TODO: draw imgui stuff here
        sceneui();
        mScene->ImguiRendering();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mWindow);
    }
}

void OPGExample::cleanup()
{
    DEBUG_PRINTF("enter OPGExample::cleanup()\n");

    for (const char *item : mSceneNameList)
    {
        delete[] item;
    }

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
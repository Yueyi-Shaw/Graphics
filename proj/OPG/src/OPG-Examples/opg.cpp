#include "opg.h"

OPGExample::OPGExample()
{
    init();
}

OPGExample::~OPGExample()
{
    cleanup();
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

    mInitSuccess = true;
    DEBUG_PRINTF("OPGExample::init() %i \n", mInitSuccess);
}

void OPGExample::loop()
{
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    bool show_demo_window    = true;
    bool show_another_window = false;
    ImVec4 clear_color       = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code
        // to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f     = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button(
                    "Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window",
                         &show_another_window); // Pass a pointer to our bool variable (the window will have a closing
                                                // button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(mWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
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
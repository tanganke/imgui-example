#include <cstdio>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// #define IGL_VIEWER_VIEWER_QUIET
#include <igl/opengl/glfw/Viewer.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.cpp>
#include <imgui_impl_opengl3.h>

GLFWwindow *window;

igl::opengl::glfw::Viewer init_window()
{
    igl::opengl::glfw::Viewer viewer;
    viewer.launch_init(true, false, "imgui-example");
    return viewer;
}

int main()
{
    auto viewer = init_window();
    window = viewer.window;

    auto setup_imgui = []() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    };
    setup_imgui();

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        viewer.draw();

        // Start the Dear ImGui frame
        static auto imgui_newframe = []() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        };
        imgui_newframe();

        static auto imgui_render = []() {
            {
                ImGui::ShowDemoWindow();
            }
            ImGui::Render();
        };
        imgui_render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    auto imgui_cleanup = []() {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    };
    imgui_cleanup();

    viewer.launch_shut();
    return 0;
}
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// #define IGL_VIEWER_VIEWER_QUIET
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.cpp>
#include <imgui_impl_opengl3.h>

#include <implot/implot.h>

#include "gl_draw.h"
#include "imgui_draw.h"

igl::opengl::glfw::Viewer viewer;
GLFWwindow *window;
double prev_frame_time, current_frame_time;

int main()
{
    igl::opengl::glfw::imgui::ImGuiMenu imgui_plugin;
    viewer.plugins.push_back(&imgui_plugin);
    viewer.launch_init(true, false, "imgui-example");
    window = viewer.window;
    ImPlot::CreateContext();

    // Add content to the default menu window
    imgui_plugin.callback_draw_viewer_window = [&]() {
        // Draw parent menu content
        // imgui_plugin.draw_viewer_menu();
    };

    imgui_plugin.callback_draw_custom_window = []() {
        imgui_draw();
    };
    
    imgui_init();
    gl_init();
    
    current_frame_time = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        prev_frame_time = current_frame_time;
        current_frame_time = glfwGetTime();

        viewer.draw();

        // draw other stuff here
        gl_draw();

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

    ImPlot::DestroyContext();
    viewer.launch_shut();
    return 0;
}

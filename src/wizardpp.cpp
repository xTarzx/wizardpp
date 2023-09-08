#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "wizard.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main(int argc, char const *argv[])
{
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "WiZard", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigDockingWithShift = true;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    WiZard wiz;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground;
        // ImGui::Begin("W_docking", 0, flags);
        // ImGui::SetWindowPos({0, 0});
        // int w_width, w_height;
        // glfwGetWindowSize(window, &w_width, &w_height);
        // ImVec2 size(w_width, w_height);
        // ImGui::SetWindowSize(size);
        // ImGui::End(); // W_docking

        ImGui::Begin("bulbs", 0, ImGuiWindowFlags_NoCollapse);
        if (ImGui::Button("scan"))
        {
            wiz.scan();
        }
        ImGui::Text("device ip:");
        ImGui::SameLine();

        switch (wiz.get_scan_state())
        {
        case WIZ_SCAN_STATE::NOT_FOUND:
            ImGui::Text("no device");
            break;
        case WIZ_SCAN_STATE::FOUND:
            ImGui::Text(wiz.get_device_ip().c_str());
            break;

        case WIZ_SCAN_STATE::SCANNING:
            ImGui::Text("scanning...");
            break;

        default:
            ImGui::Text("click scan dumbass");
            break;
        }

        ImGui::End(); // bulbs

        ImGui::ShowDemoWindow();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

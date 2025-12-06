#include "GUI/Window/WindowHandler.h"
#include "GUI/Window/HomeworkWindow.h"
#include "GUI/Test/TestWindow.h"
#include "GUI/GUIIncludes.h"

#include <format>
#include <iostream>

inline void glfw_error_callback(const int error, const char* description)
{
    std::cerr << std::format("GLFW Error {}: ", error) << description << std::endl;
}

int main()
{
    // HomeworkHelper::HomeworkWindow window;
    // window.GenerateImguiContent();
    //
    // HomeworkHelper::WindowHandler::Initialize();
    // int windowID = HomeworkHelper::WindowHandler::CreateWindow(
    //     800,
    //     1200,
    //     "Test",
    //     std::bind(&HomeworkHelper::HomeworkWindow::UpdateImguiContent, &window)
    // );
    //
    // if (windowID == -1) {
    //     HomeworkHelper::WindowHandler::Shutdown();
    //     return -1;
    // }
    //
    // window.SetWindowData(HomeworkHelper::WindowHandler::GetWindowData(windowID));

    // Main loop
    // while (HomeworkHelper::WindowHandler::IsAnyWindowOpen()) {
    //     HomeworkHelper::WindowHandler::RenderWindows();
    // }

    // HomeworkHelper::WindowHandler::Shutdown();

    // TODO: Remove
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!glfwVulkanSupported()) {
        std::cerr << "Vulkan is not supported" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    VulkanData vulkanData = {};
    auto big = new HomeworkHelper::TestWindow(&vulkanData, "Big Window", 800, 1600);
    auto small = new HomeworkHelper::TestWindow(&vulkanData, "Small Window", 400, 800);

    while (small->IsOpen() || big->IsOpen()) {
        if (big->IsOpen())
            big->RenderWindow();
        if (small->IsOpen())
            small->RenderWindow();
    }
    delete big;
    delete small;

    glfwTerminate();
    return 0;
}

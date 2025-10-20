#ifndef HOMEWORKHELPER_WINDOW_H
#define HOMEWORKHELPER_WINDOW_H
#include <functional>

struct ImGui_ImplVulkanH_Window;
struct ImDrawData;
struct GLFWwindow;

namespace HomeworkHelper {
    typedef std::function<void()> ImguiStaticContentCallback;
    typedef std::function<void()> ImguiDynamicContentCallback;
    // Struct for holding Window specific variables.
    // All functionality lies in WindowHandler to keep implementation specific headers from flowing over to other files.
    struct Window {
        bool rebuildSwapChain = false;
        unsigned minImageCount = 2;
        GLFWwindow* windowHandle = nullptr;
        ImGui_ImplVulkanH_Window* windowData = nullptr;
        ImDrawData* drawData = nullptr;
        ImguiStaticContentCallback imguiStaticCallback;  // This callback should contain all code to generate the static content for the window, such as menus and anchor points
        ImguiDynamicContentCallback imguiDynamicCallback;  // This callback should contain all code to generate the dynamic content for the window, such as buttons and text fields
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_WINDOW_H
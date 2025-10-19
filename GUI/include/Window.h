#ifndef HOMEWORKHELPER_WINDOW_H
#define HOMEWORKHELPER_WINDOW_H

struct ImGui_ImplVulkanH_Window;
struct ImDrawData;
struct GLFWwindow;

namespace HomeworkHelper {
    // Struct for holding Window specific variables.
    // All functionality lies in WindowHandler to keep implementation specific headers from flowing over to other files.
    struct Window {
        //TODO: remove
        bool show_demo_window = true;
        bool show_another_window = false ;
        float clear_color[4] = {0.45f, 0.55f, 0.60f, 1.00f};

        bool rebuildSwapChain = false;
        unsigned minImageCount = 2;
        GLFWwindow* windowHandle = nullptr;
        ImGui_ImplVulkanH_Window* windowData = nullptr;
        ImDrawData* drawData = nullptr;

    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_WINDOW_H
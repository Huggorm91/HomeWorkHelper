#ifndef HOMEWORKHELPER_WINDOW_H
#define HOMEWORKHELPER_WINDOW_H
#include <imgui.h>

struct ImGui_ImplVulkanH_Window;
struct GLFWwindow;

namespace HomeworkHelper {
    class Window {
        public:
        Window();
        Window(int aWidth, int aHeight);
        ~Window();

        bool ShouldClose() const;
        bool IsMinimized() const;

        void RenderWindow();

        private:
        static int ourWindowCount;

        // TODO: Remove
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // Window handles
        GLFWwindow* myWindow;
        ImGui_ImplVulkanH_Window* myWindowData;
        ImDrawData* myDrawData;
        ImGuiIO* myIO;

        void Update();
        void Render();
        void Present();

        void CreateWindow(int aWidth, int aHeight);

        static void InitGLFW();
        static void DestroyGLFW();

        static void InitVulkan();
        static void DestroyVulkan();

        void InitImgui();
        static void DestroyImgui();
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_WINDOW_H
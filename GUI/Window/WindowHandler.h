#ifndef HOMEWORKHELPER_WINDOWHANDLER_H
#define HOMEWORKHELPER_WINDOWHANDLER_H
#include <unordered_map>
#include <string>
#include "Window.h"

namespace HomeworkHelper
{
    class WindowHandler
    {
    public:
        static void Initialize();
        static void Shutdown();

        static int CreateWindow(int aHeight, int aWidth, const std::string& aTitle, const ImguiDynamicContentCallback& anImguiCallback);

        static void RenderWindows();

        static bool DestroyWindow(int anID);

        static bool IsAnyWindowOpen();

        static void SetImguiCallback(int anID, const ImguiDynamicContentCallback& anImguiCallback);

        static ImGui_ImplVulkanH_Window* GetWindowData(int anID);

    private:
        int myWindowCounter;
        std::unordered_map<int, Window> myWindows;

        WindowHandler();
        ~WindowHandler() = default;

        static WindowHandler& GetInstance();

        static void InitGLFW();
        static void DestroyGLFW();

        static void InitVulkan();
        static void DestroyVulkan();

        static void InitImgui();
        static void DestroyImgui();

        static void CreateWindow(Window& outWindow, int aWidth, int aHeight, const std::string& aTitle);
        static void DestroyWindow(Window& outWindow);

        static bool ShouldCloseWindow(const Window& aWindow);
        static bool IsMinimizedWindow(const Window& aWindow);

        static void UpdateWindow(Window& outWindow);
        static void RenderWindow(Window& outWindow);
        static void PresentWindow(Window& outWindow);
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_WINDOWHANDLER_H

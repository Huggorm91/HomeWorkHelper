#include "WindowHandler.h"
#include "GUI/GUIIncludes.h"
#include "GUI/Rendering/OpenGLRender.h"
#include "GUI/Rendering/VulkanRender.h"
#include <format>
#include <vector>
#include <cassert>
#include <ranges>
#include <iostream>

static void glfw_error_callback(const int error, const char* description)
{
    std::cerr << std::format("GLFW Error {}: ", error) << description << std::endl;
}

namespace HomeworkHelper
{
    static WindowHandler* localInstance = nullptr;

    WindowHandler::WindowHandler() : myWindowCounter(0)
    {
    }

    WindowHandler& WindowHandler::GetInstance()
    {
        assert(localInstance && "WindowHandler is not initialized!");
        return *localInstance;
    }

    void WindowHandler::Initialize()
    {
        assert(localInstance == nullptr);
        localInstance = new WindowHandler();

        InitGLFW();

        if (glfwVulkanSupported()) {
            localInstance->myRenderer = std::make_unique<Rendering::VulkanRender>();
        }
        else {
            // Use OpenGL 2 as fallback
            localInstance->myRenderer = std::make_unique<Rendering::OpenGLRender>();
        }
        localInstance->myRenderer->Init();

        InitImgui();
    }

    void WindowHandler::Shutdown()
    {
        assert(localInstance);

        auto& instance = GetInstance();
        for (auto window: instance.myWindows | std::views::values) {
            DestroyWindow(window);
        }
        instance.myWindows.clear();

        instance.myRenderer->Shutdown();
        DestroyImgui();
        DestroyGLFW();

        delete localInstance;
        localInstance = nullptr;
    }

    int WindowHandler::CreateWindow(
        const int aHeight,
        const int aWidth,
        const std::string& aTitle,
        const ImguiDynamicContentCallback& anImguiCallback
    )
    {
        auto& instance = GetInstance();
        auto [entry, success] = instance.myWindows.emplace(instance.myWindowCounter++, Window());
        if (success) {
            CreateWindow(entry->second, aWidth, aHeight, aTitle);
            entry->second.imguiDynamicCallback = anImguiCallback;
            return entry->first;
        }

        return -1;
    }

    void WindowHandler::RenderWindows()
    {
        auto& instance = GetInstance();
        auto& renderer = *instance.myRenderer;
        std::vector<int> windowsToRemove;
        for (auto& [id, window]: instance.myWindows) {
            if (ShouldCloseWindow(window)) {
                windowsToRemove.emplace_back(id);
                continue;
            }

            UpdateWindow(window);
            if (!IsMinimizedWindow(window)) {
                renderer.Render(window);
                renderer.Present(window);
            }
        }

        for (auto id: windowsToRemove) {
            auto iter = instance.myWindows.find(id);
            DestroyWindow(iter->second);
            instance.myWindows.erase(iter);
        }

        // Update and Render additional Platform Windows
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    bool WindowHandler::DestroyWindow(const int anID)
    {
        auto& instance = GetInstance();
        if (auto iter = instance.myWindows.find(anID); iter != instance.myWindows.end()) {
            DestroyWindow(iter->second);
            instance.myWindows.erase(iter);
            return true;
        }
        return false;
    }

    bool WindowHandler::IsAnyWindowOpen()
    {
        auto& instance = GetInstance();
        bool anyWindowOpen = false;
        for (auto& window: instance.myWindows | std::views::values) {
            if (!ShouldCloseWindow(window)) {
                anyWindowOpen = true;
            }
        }
        return anyWindowOpen;
    }

    void WindowHandler::SetImguiCallback(int anID, const ImguiDynamicContentCallback& anImguiCallback)
    {
        auto& instance = GetInstance();
        if (auto iter = instance.myWindows.find(anID); iter != instance.myWindows.end()) {
            iter->second.imguiDynamicCallback = anImguiCallback;
        }
    }

    ImGui_ImplVulkanH_Window* WindowHandler::GetWindowData(int anID)
    {
        auto& instance = GetInstance();
        if (auto iter = instance.myWindows.find(anID); iter != instance.myWindows.end()) {
            return iter->second.windowData;
        }
        return nullptr;
    }

    void WindowHandler::InitGLFW()
    {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    void WindowHandler::DestroyGLFW()
    {
        glfwTerminate();
    }

    void WindowHandler::InitImgui()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        const float mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
        // Valid on GLFW 3.3+ only

        // Setup scaling
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(mainScale);
        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
        style.FontScaleDpi = mainScale;
        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
        io.ConfigDpiScaleFonts = true;
        // [Experimental] Automatically overwrite style.FontScaleDpi in Begin() when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
        io.ConfigDpiScaleViewports = true;
        // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
    }

    void WindowHandler::DestroyImgui()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void WindowHandler::CreateWindow(Window& outWindow, const int aWidth, const int aHeight, const std::string& aTitle)
    {
        auto& renderer = *GetInstance().myRenderer;
        CreateGlfwWindow(outWindow, aWidth, aHeight, aTitle, renderer.GetGlfwWindowHint(), renderer.GetGlfwWindowHintValue());
        renderer.CreateWindow(outWindow);
    }

    void WindowHandler::CreateGlfwWindow(
        Window& outWindow,
        int aWidth,
        int aHeight,
        const std::string& aTitle,
        int aHint,
        int aHintValue
    )
    {
        // Create window with Vulkan context
        glfwWindowHint(aHint, aHintValue);
        const float mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
        outWindow.height = static_cast<int>(aHeight * mainScale);
        outWindow.width = static_cast<int>(aWidth * mainScale);
        // Valid on GLFW 3.3+ only
        outWindow.windowHandle = glfwCreateWindow(
            outWindow.width,
            outWindow.height,
            aTitle.c_str(),
            nullptr,
            nullptr
        );
    }

    void WindowHandler::DestroyWindow(Window& outWindow)
    {
        GetInstance().myRenderer->DestroyWindow(outWindow);
        glfwDestroyWindow(outWindow.windowHandle);
        delete outWindow.windowData;
        outWindow.windowData = nullptr;
    }

    bool WindowHandler::ShouldCloseWindow(const Window& aWindow)
    {
        return glfwWindowShouldClose(aWindow.windowHandle);
    }

    bool WindowHandler::IsMinimizedWindow(const Window& aWindow)
    {
        if (aWindow.drawData == nullptr) {
            return true;
        }
        return aWindow.drawData->DisplaySize.x <= 0.0f || aWindow.drawData->DisplaySize.y <= 0.0f;
    }

    void WindowHandler::UpdateWindow(Window& outWindow)
    {
        auto& renderer = *GetInstance().myRenderer;
        outWindow.drawData = nullptr;
        glfwPollEvents();

        int bufferWidth, bufferHeight;
        glfwGetFramebufferSize(outWindow.windowHandle, &bufferWidth, &bufferHeight);

        renderer.HandleResize(outWindow, bufferWidth, bufferHeight);

        if (glfwGetWindowAttrib(outWindow.windowHandle, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            return;
        }

        renderer.Update();

        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        outWindow.imguiDynamicCallback();

        // Rendering
        ImGui::Render();

        outWindow.drawData = ImGui::GetDrawData();
    }
} // HomeworkHelper

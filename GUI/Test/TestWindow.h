#ifndef TEST_WINDOW_H
#define TEST_WINDOW_H
#include "TestVulkanData.h"
#include <string>

struct GLFWwindow;
struct VkSurfaceKHR_T;
struct VkSwapchainKHR_T;
struct VkPipelineCache_T;

namespace HomeworkHelper
{
    // Quickly thrown together in Notepad++ while having nothing to do at work
    class TestWindow
    {
    public:
        TestWindow() = default;

        TestWindow(
            const VulkanData* someData,
            const std::string& aTitle,
            int aHeight,
            int aWidth,
            bool isFullscreen = false
        );

        ~TestWindow();

        void CreateWindow(
            const VulkanData* someData,
            const std::string& aTitle,
            int aHeight,
            int aWidth,
            bool isFullscreen = false
        );

        void DestroyWindow();

        void RenderWindow();

        bool IsOpen() const;

    private:
        GLFWwindow* windowHandle = nullptr;
        VkSurfaceKHR_T* surface = nullptr;
        VkPipelineCache_T* pipelineCache = nullptr;
        VkSwapchainKHR_T* swapChain = nullptr;
        const VulkanData* vulkanData = nullptr;

        void CreateSwapChain();
    };
} // HomeworkHelper

#endif //TEST_WINDOW_H

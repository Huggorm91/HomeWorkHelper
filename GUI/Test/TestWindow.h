#ifndef TEST_WINDOW_H
#define TEST_WINDOW_H
#include "TestVulkanData.h"
#include <string>
#include <vector>

struct GLFWwindow;

namespace HomeworkHelper
{
    // Quickly thrown together in Notepad++ while having nothing to do at work
    class TestWindow
    {
    public:
        TestWindow() = default;

        TestWindow(
            const VulkanStaticData* someData,
            const std::string& aTitle,
            int aHeight,
            int aWidth,
            bool isFullscreen = false
        );

        ~TestWindow();

        void CreateWindow(
            const VulkanStaticData* someData,
            const std::string& aTitle,
            int aHeight,
            int aWidth,
            bool isFullscreen = false
        );

        void DestroyWindow();

        void RenderWindow();

        bool IsOpen() const;

    private:
        bool useDynamicRendering;
        bool clearEnable;
        int width;
        int height;
        unsigned frameIndex; // Current frame being rendered to (0 <= FrameIndex < FrameInFlightCount)
        unsigned imageCount; // Number of simultaneous in-flight frames (returned by vkGetSwapchainImagesKHR, usually derived from min_image_count)
        unsigned semaphoreCount; // Number of simultaneous in-flight frames + 1, to be able to use it in vkAcquireNextImageKHR
        unsigned semaphoreIndex; // Current set of swapchain wait semaphores we're using (needs to be distinct from per frame data)
        const VulkanStaticData* vulkanData = nullptr;
        GLFWwindow* windowHandle = nullptr;
        VkPipelineCache pipelineCache = nullptr;
        VkSwapchainKHR swapchain = nullptr;
        VkSurfaceKHR surface = nullptr;
        VkSurfaceFormatKHR surfaceFormat;
        VkRenderPass renderPass;
        VkClearValue clearValue;
        std::vector<VulkanFrameData> frames;
        std::vector<VulkanFrameSemaphores> frameSemaphores;

        void CreateSwapChain();

        void CreatePipeline();

        void CreateFrameBuffer();

        void CreateWindowCommandBuffer();
        void SubmitWindowCommandBuffer();

        void DestroyFrame(VulkanFrameData& outFrame);
        void DestroyFrameSemaphore(VulkanFrameSemaphores& outFrameSemaphore);
    };
} // HomeworkHelper

#endif //TEST_WINDOW_H

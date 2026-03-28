#ifndef HOMEWORKHELPER_VULKANRENDER_H
#define HOMEWORKHELPER_VULKANRENDER_H
#include "RenderBase.h"
#include <vulkan/vulkan_core.h>

namespace HomeworkHelper::Rendering
{
    class VulkanRender : public RenderBase
    {
    public:
        VulkanRender() = default;
        ~VulkanRender() override = default;

        void Init() override;
        void Shutdown() override;

        void Update() override;
        void Render(Window& outWindow) override;
        void Present(Window& outWindow) override;

        void HandleResize(Window& outWindow, int aNewWidth, int aNewHeight) override;

        void CreateWindow(Window& outWindow) override;
        void DestroyWindow(Window& outWindow) override;

        [[nodiscard]] constexpr int GetGlfwWindowHint() const override;
        [[nodiscard]] constexpr int GetGlfwWindowHintValue() const override;

    private:
        VkAllocationCallbacks* myAllocator = nullptr;
        VkInstance myInstance = VK_NULL_HANDLE;
        VkPhysicalDevice myPhysicalDevice = VK_NULL_HANDLE;
        VkDevice myDevice = VK_NULL_HANDLE;
        uint32_t myQueueFamily = static_cast<uint32_t>(-1);
        VkQueue myQueue = VK_NULL_HANDLE;
        VkPipelineCache myPipelineCache = VK_NULL_HANDLE;
        VkDescriptorPool myDescriptorPool = VK_NULL_HANDLE;
#ifdef APP_USE_VULKAN_DEBUG_REPORT
        VkDebugReportCallbackEXT myDebugReport = VK_NULL_HANDLE;
#endif // APP_USE_VULKAN_DEBUG_REPORT
    };
} // HomeworkHelper::Rendering

#endif //HOMEWORKHELPER_VULKANRENDER_H

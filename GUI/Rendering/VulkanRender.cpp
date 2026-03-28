#ifdef _DEBUG
#define APP_USE_VULKAN_DEBUG_REPORT
#endif

#include "VulkanRender.h"
#include "GUI/GUIIncludes.h"
#include <format>

namespace HomeworkHelper::Rendering
{
#ifdef APP_USE_VULKAN_DEBUG_REPORT
    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objectType,
        uint64_t object,
        size_t location,
        int32_t messageCode,
        const char* pLayerPrefix,
        const char* pMessage,
        void* pUserData
    )
    {
        (void) flags;
        (void) object;
        (void) location;
        (void) messageCode;
        (void) pUserData;
        (void) pLayerPrefix; // Unused arguments
        fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n", objectType, pMessage);
        return VK_FALSE;
    }
#endif // APP_USE_VULKAN_DEBUG_REPORT

    static bool IsExtensionAvailable(const ImVector<VkExtensionProperties>& properties, const char* extension)
    {
        for (const VkExtensionProperties& property: properties) {
            if (strcmp(property.extensionName, extension) == 0) {
                return true;
            }
        }
        return false;
    }

    static void check_vk_result(const VkResult err)
    {
        if (err == VK_SUCCESS) {
            return;
        }
        if (err < 0) {
            throw std::runtime_error(std::format("[vulkan] Error: VkResult = {}", static_cast<long>(err)));
        }
    }

    void VulkanRender::Init()
    {
        ImVector<const char*> instance_extensions;
        uint32_t extensions_count = 0;
        const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
        for (uint32_t i = 0; i < extensions_count; i++) {
            instance_extensions.push_back(glfw_extensions[i]);
        }

        VkResult err;
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
        volkInitialize();
#endif

        // Create Vulkan Instance
        {
            VkInstanceCreateInfo create_info = {};
            create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

            // Enumerate available extensions
            uint32_t properties_count;
            ImVector<VkExtensionProperties> properties;
            vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, nullptr);
            properties.resize(properties_count);
            err = vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, properties.Data);
            check_vk_result(err);

            // Enable required extensions
            if (IsExtensionAvailable(properties, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME)) {
                instance_extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
            }
#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
            if (IsExtensionAvailable(properties, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)) {
                instance_extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
                create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
            }
#endif

            // Enabling validation layers
#ifdef APP_USE_VULKAN_DEBUG_REPORT
            const char* layers[] = {"VK_LAYER_KHRONOS_validation"};
            create_info.enabledLayerCount = 1;
            create_info.ppEnabledLayerNames = layers;
            instance_extensions.push_back("VK_EXT_debug_report");
#endif

            // Create Vulkan Instance
            create_info.enabledExtensionCount = static_cast<uint32_t>(instance_extensions.Size);
            create_info.ppEnabledExtensionNames = instance_extensions.Data;
            err = vkCreateInstance(&create_info, myAllocator, &myInstance);
            check_vk_result(err);
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
            volkLoadInstance(g_Instance);
#endif

            // Setup the debug report callback
#ifdef APP_USE_VULKAN_DEBUG_REPORT
            auto f_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(
                myInstance,
                "vkCreateDebugReportCallbackEXT"
            );
            IM_ASSERT(f_vkCreateDebugReportCallbackEXT != nullptr);
            VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
            debug_report_ci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
            debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT |
                                    VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
            debug_report_ci.pfnCallback = debug_report;
            debug_report_ci.pUserData = nullptr;
            err = f_vkCreateDebugReportCallbackEXT(
                myInstance,
                &debug_report_ci,
                myAllocator,
                &myDebugReport
            );
            check_vk_result(err);
#endif
        }

        // Select Physical Device (GPU)
        myPhysicalDevice = ImGui_ImplVulkanH_SelectPhysicalDevice(myInstance);
        IM_ASSERT(myPhysicalDevice != VK_NULL_HANDLE);

        // Select graphics queue family
        myQueueFamily = ImGui_ImplVulkanH_SelectQueueFamilyIndex(myPhysicalDevice);
        IM_ASSERT(myQueueFamily != static_cast<uint32_t>(-1));

        // Create Logical Device (with 1 queue)
        {
            ImVector<const char*> device_extensions;
            device_extensions.push_back("VK_KHR_swapchain");

            // Enumerate physical device extension
            uint32_t properties_count;
            ImVector<VkExtensionProperties> properties;
            vkEnumerateDeviceExtensionProperties(myPhysicalDevice, nullptr, &properties_count, nullptr);
            properties.resize(properties_count);
            vkEnumerateDeviceExtensionProperties(
                myPhysicalDevice,
                nullptr,
                &properties_count,
                properties.Data
            );
#ifdef VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME
            if (IsExtensionAvailable(properties, VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME))
                device_extensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
#endif

            constexpr float queue_priority[] = {1.0f};
            VkDeviceQueueCreateInfo queue_info[1] = {};
            queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_info[0].queueFamilyIndex = myQueueFamily;
            queue_info[0].queueCount = 1;
            queue_info[0].pQueuePriorities = queue_priority;
            VkDeviceCreateInfo create_info = {};
            create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            create_info.queueCreateInfoCount = std::size(queue_info);
            create_info.pQueueCreateInfos = queue_info;
            create_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.Size);
            create_info.ppEnabledExtensionNames = device_extensions.Data;
            err = vkCreateDevice(
                myPhysicalDevice,
                &create_info,
                myAllocator,
                &myDevice
            );
            check_vk_result(err);
            vkGetDeviceQueue(myDevice, myQueueFamily, 0, &myQueue);
        }

        // Create Descriptor Pool
        // If you wish to load e.g. additional textures you may need to alter pools sizes and maxSets.
        {
            VkDescriptorPoolSize pool_sizes[] =
                    {
                        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, IMGUI_IMPL_VULKAN_MINIMUM_IMAGE_SAMPLER_POOL_SIZE},
                    };
            VkDescriptorPoolCreateInfo pool_info = {};
            pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
            pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
            pool_info.maxSets = 0;
            for (VkDescriptorPoolSize& pool_size: pool_sizes) {
                pool_info.maxSets += pool_size.descriptorCount;
            }
            pool_info.poolSizeCount = static_cast<uint32_t>(IM_ARRAYSIZE(pool_sizes));
            pool_info.pPoolSizes = pool_sizes;
            err = vkCreateDescriptorPool(
                myDevice,
                &pool_info,
                myAllocator,
                &myDescriptorPool
            );
            check_vk_result(err);
        }
    }

    void VulkanRender::Shutdown()
    {
        const VkResult err = vkDeviceWaitIdle(myDevice);
        check_vk_result(err);
        ImGui_ImplVulkan_Shutdown();

        vkDestroyDescriptorPool(myDevice, myDescriptorPool, myAllocator);

#ifdef APP_USE_VULKAN_DEBUG_REPORT
        // Remove the debug report callback
        auto f_vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(
            myInstance,
            "vkDestroyDebugReportCallbackEXT"
        );
        f_vkDestroyDebugReportCallbackEXT(myInstance, myDebugReport, myAllocator);
#endif // APP_USE_VULKAN_DEBUG_REPORT

        vkDestroyDevice(myDevice, myAllocator);
        vkDestroyInstance(myInstance, myAllocator);

        //Reset variables
        myInstance = VK_NULL_HANDLE;
    }

    void VulkanRender::Update()
    {
        ImGui_ImplVulkan_NewFrame();
    }

    void VulkanRender::Render(Window& outWindow)
    {
        VkSemaphore image_acquired_semaphore = outWindow.windowData->FrameSemaphores[outWindow.windowData->
                    SemaphoreIndex].
                ImageAcquiredSemaphore;
        VkSemaphore render_complete_semaphore = outWindow.windowData->FrameSemaphores[outWindow.windowData->
                    SemaphoreIndex].
                RenderCompleteSemaphore;
        VkResult err = vkAcquireNextImageKHR(
            myDevice,
            outWindow.windowData->Swapchain,
            UINT64_MAX,
            image_acquired_semaphore,
            VK_NULL_HANDLE,
            &outWindow.windowData->FrameIndex
        );
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
            outWindow.rebuildSwapChain = true;
        }
        if (err == VK_ERROR_OUT_OF_DATE_KHR) {
            return;
        }
        if (err != VK_SUBOPTIMAL_KHR) {
            check_vk_result(err);
        }

        const ImGui_ImplVulkanH_Frame* fd = &outWindow.windowData->Frames[outWindow.windowData->FrameIndex];
        {
            err = vkWaitForFences(myDevice, 1, &fd->Fence, VK_TRUE, UINT64_MAX);
            // wait indefinitely instead of periodically checking
            check_vk_result(err);

            err = vkResetFences(myDevice, 1, &fd->Fence);
            check_vk_result(err);
        }
        {
            err = vkResetCommandPool(myDevice, fd->CommandPool, 0);
            check_vk_result(err);
            VkCommandBufferBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
            err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
            check_vk_result(err);
        }
        {
            VkRenderPassBeginInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            info.renderPass = outWindow.windowData->RenderPass;
            info.framebuffer = fd->Framebuffer;
            info.renderArea.extent.width = outWindow.windowData->Width;
            info.renderArea.extent.height = outWindow.windowData->Height;
            info.clearValueCount = 1;
            info.pClearValues = &outWindow.windowData->ClearValue;
            vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
        }

        // Record dear imgui primitives into command buffer
        ImGui_ImplVulkan_RenderDrawData(outWindow.drawData, fd->CommandBuffer);

        // Submit command buffer
        vkCmdEndRenderPass(fd->CommandBuffer);
        {
            VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            VkSubmitInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            info.waitSemaphoreCount = 1;
            info.pWaitSemaphores = &image_acquired_semaphore;
            info.pWaitDstStageMask = &wait_stage;
            info.commandBufferCount = 1;
            info.pCommandBuffers = &fd->CommandBuffer;
            info.signalSemaphoreCount = 1;
            info.pSignalSemaphores = &render_complete_semaphore;

            err = vkEndCommandBuffer(fd->CommandBuffer);
            check_vk_result(err);
            err = vkQueueSubmit(myQueue, 1, &info, fd->Fence);
            check_vk_result(err);
        }
    }

    void VulkanRender::Present(Window& outWindow)
    {
        if (outWindow.rebuildSwapChain) {
            return;
        }
        VkSemaphore render_complete_semaphore = outWindow.windowData->FrameSemaphores[outWindow.windowData->
                    SemaphoreIndex].
                RenderCompleteSemaphore;
        VkPresentInfoKHR info = {};
        info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &render_complete_semaphore;
        info.swapchainCount = 1;
        info.pSwapchains = &outWindow.windowData->Swapchain;
        info.pImageIndices = &outWindow.windowData->FrameIndex;
        const VkResult err = vkQueuePresentKHR(myQueue, &info);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
            outWindow.rebuildSwapChain = true;
        }
        if (err == VK_ERROR_OUT_OF_DATE_KHR) {
            return;
        }
        if (err != VK_SUBOPTIMAL_KHR) {
            check_vk_result(err);
        }
        outWindow.windowData->SemaphoreIndex =
                (outWindow.windowData->SemaphoreIndex + 1) % outWindow.windowData->SemaphoreCount;
    }

    void VulkanRender::HandleResize(Window& outWindow, const int aNewWidth, const int aNewHeight)
    {
        // Resize swap chain?
        if (aNewWidth > 0 && aNewHeight > 0 && (outWindow.rebuildSwapChain ||
                                                outWindow.windowData->Width != aNewWidth ||
                                                outWindow.windowData->Height != aNewHeight)) {
            ImGui_ImplVulkan_SetMinImageCount(outWindow.minImageCount);
            ImGui_ImplVulkanH_CreateOrResizeWindow(
                myInstance,
                myPhysicalDevice,
                myDevice,
                outWindow.windowData,
                myQueueFamily,
                myAllocator,
                aNewWidth,
                aNewHeight,
                outWindow.minImageCount,
                0
            );
            outWindow.windowData->FrameIndex = 0;
            outWindow.rebuildSwapChain = false;
            outWindow.width = aNewWidth;
            outWindow.height = aNewHeight;
        }
    }

    void VulkanRender::CreateWindow(Window& outWindow)
    {
        outWindow.windowData = new ImGui_ImplVulkanH_Window();

        VkSurfaceKHR surface;
        const VkResult err = glfwCreateWindowSurface(
            myInstance,
            outWindow.windowHandle,
            myAllocator,
            &surface
        );
        check_vk_result(err);

        glfwGetFramebufferSize(outWindow.windowHandle, &outWindow.width, &outWindow.height);
        outWindow.windowData->Surface = surface;

        // Check for WSI support
        VkBool32 res;
        vkGetPhysicalDeviceSurfaceSupportKHR(
            myPhysicalDevice,
            myQueueFamily,
            outWindow.windowData->Surface,
            &res
        );
        if (res != VK_TRUE) {
            fprintf(stderr, "Error no WSI support on physical device 0\n");
            exit(-1);
        }

        // Select Surface Format
        constexpr VkFormat requestSurfaceImageFormat[] = {
                    VK_FORMAT_B8G8R8A8_UNORM,
                    VK_FORMAT_R8G8B8A8_UNORM,
                    VK_FORMAT_B8G8R8_UNORM,
                    VK_FORMAT_R8G8B8_UNORM
                };
        constexpr VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        outWindow.windowData->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(
            myPhysicalDevice,
            outWindow.windowData->Surface,
            requestSurfaceImageFormat,
            (size_t) IM_ARRAYSIZE(requestSurfaceImageFormat),
            requestSurfaceColorSpace
        );

        // Select Present Mode
#ifdef APP_USE_UNLIMITED_FRAME_RATE
        VkPresentModeKHR present_modes[] = {
                    VK_PRESENT_MODE_MAILBOX_KHR,
                    VK_PRESENT_MODE_IMMEDIATE_KHR,
                    VK_PRESENT_MODE_FIFO_KHR
                };
#else
        constexpr VkPresentModeKHR present_modes[] = {VK_PRESENT_MODE_FIFO_KHR};
#endif
        outWindow.windowData->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(
            myPhysicalDevice,
            outWindow.windowData->Surface,
            &present_modes[0],
            IM_ARRAYSIZE(present_modes)
        );
        //printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

        // Create SwapChain, RenderPass, Framebuffer, etc.
        IM_ASSERT(outWindow.minImageCount >= 2);
        ImGui_ImplVulkanH_CreateOrResizeWindow(
            myInstance,
            myPhysicalDevice,
            myDevice,
            outWindow.windowData,
            myQueueFamily,
            myAllocator,
            outWindow.width,
            outWindow.height,
            outWindow.minImageCount,
            0
        );

        //TODO: figure out how to be able to open more than one window
        // Probably have to write my own logic for initialization

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForVulkan(outWindow.windowHandle, true);
        ImGui_ImplVulkan_InitInfo init_info = {};
        //init_info.ApiVersion = VK_API_VERSION_1_3;              // Pass in your value of VkApplicationInfo::apiVersion, otherwise will default to header version.
        init_info.Instance = myInstance;
        init_info.PhysicalDevice = myPhysicalDevice;
        init_info.Device = myDevice;
        init_info.QueueFamily = myQueueFamily;
        init_info.Queue = myQueue;
        init_info.PipelineCache = myPipelineCache;
        init_info.DescriptorPool = myDescriptorPool;
        init_info.MinImageCount = outWindow.minImageCount;
        init_info.ImageCount = outWindow.windowData->ImageCount;
        init_info.Allocator = myAllocator;
        init_info.PipelineInfoMain.RenderPass = outWindow.windowData->RenderPass;
        init_info.PipelineInfoMain.Subpass = 0;
        init_info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.CheckVkResultFn = check_vk_result;
        ImGui_ImplVulkan_Init(&init_info);
    }

    void VulkanRender::DestroyWindow(Window& outWindow)
    {
        ImGui_ImplVulkanH_DestroyWindow(
            myInstance,
            myDevice,
            outWindow.windowData,
            myAllocator
        );
    }

    constexpr int VulkanRender::GetGlfwWindowHint() const
    {
        return GLFW_CLIENT_API;
    }

    constexpr int VulkanRender::GetGlfwWindowHintValue() const
    {
        return GLFW_NO_API;
    }
} // HomeworkHelper::Rendering

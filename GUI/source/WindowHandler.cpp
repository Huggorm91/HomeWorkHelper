#include "WindowHandler.h"
#include "GUIIncludes.h"
#include <format>
#include <vector>
#include <cassert>
#include <ranges>
#include <iostream>

static void glfw_error_callback(const int error, const char* description)
{
    std::cerr << std::format("GLFW Error {}: ", error) << description << std::endl;
}

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

namespace HomeworkHelper
{
    static WindowHandler* localInstance = nullptr;

    namespace Vulkan
    {
        static inline VkAllocationCallbacks* localAllocator = nullptr;
        static inline VkInstance localInstance = VK_NULL_HANDLE;
        static inline VkPhysicalDevice localPhysicalDevice = VK_NULL_HANDLE;
        static inline VkDevice localDevice = VK_NULL_HANDLE;
        static inline uint32_t localQueueFamily = static_cast<uint32_t>(-1);
        static inline VkQueue localQueue = VK_NULL_HANDLE;
        static inline VkPipelineCache localPipelineCache = VK_NULL_HANDLE;
        static inline VkDescriptorPool localDescriptorPool = VK_NULL_HANDLE;
    }

    WindowHandler::WindowHandler() : myWindowCounter(0)
    {
    }

    WindowHandler& WindowHandler::GetInstance()
    {
        assert(localInstance);
        return *localInstance;
    }

    void WindowHandler::Initialize()
    {
        assert(localInstance == nullptr);
        localInstance = new WindowHandler();

        InitGLFW();

        // TODO: Add OpenGL as backup
        if (glfwVulkanSupported()) {
            InitVulkan();
        }
        else {
            throw std::runtime_error("GLFW: Vulkan Not Supported");
        }

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

        DestroyImgui();
        DestroyVulkan();
        DestroyGLFW();

        delete localInstance;
        localInstance = nullptr;
    }

    int WindowHandler::CreateWindow(
        const int aHeight,
        const int aWidth,
        const std::string& aTitle,
        const ImguiUpdateCallback& anImguiCallback
    )
    {
        auto& instance = GetInstance();
        auto [entry, success] = instance.myWindows.emplace(instance.myWindowCounter++, Window());
        if (success) {
            CreateWindow(entry->second, aWidth, aHeight, aTitle);
            entry->second.imguiUpdateCallback = anImguiCallback;
            return entry->first;
        }

        return -1;
    }

    void WindowHandler::RenderWindows()
    {
        auto& instance = GetInstance();
        std::vector<int> windowsToRemove;
        for (auto& [id, window]: instance.myWindows) {
            if (ShouldCloseWindow(window)) {
                windowsToRemove.emplace_back(id);
                continue;
            }

            UpdateWindow(window);
            if (!IsMinimizedWindow(window)) {
                RenderWindow(window);
                PresentWindow(window);
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

    void WindowHandler::SetImguiCallback(int anID, const ImguiUpdateCallback& anImguiCallback)
    {
        auto& instance = GetInstance();
        if (auto iter = instance.myWindows.find(anID); iter != instance.myWindows.end()) {
            iter->second.imguiUpdateCallback = anImguiCallback;
        }
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

    void WindowHandler::InitVulkan()
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
            err = vkCreateInstance(&create_info, Vulkan::localAllocator, &Vulkan::localInstance);
            check_vk_result(err);
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
            volkLoadInstance(g_Instance);
#endif

            // Setup the debug report callback
#ifdef APP_USE_VULKAN_DEBUG_REPORT
            auto f_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(
                Vulkan::localInstance,
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
                Vulkan::localInstance,
                &debug_report_ci,
                Vulkan::localAllocator,
                &g_DebugReport
            );
            check_vk_result(err);
#endif
        }

        // Select Physical Device (GPU)
        Vulkan::localPhysicalDevice = ImGui_ImplVulkanH_SelectPhysicalDevice(Vulkan::localInstance);
        IM_ASSERT(Vulkan::localPhysicalDevice != VK_NULL_HANDLE);

        // Select graphics queue family
        Vulkan::localQueueFamily = ImGui_ImplVulkanH_SelectQueueFamilyIndex(Vulkan::localPhysicalDevice);
        IM_ASSERT(Vulkan::localQueueFamily != static_cast<uint32_t>(-1));

        // Create Logical Device (with 1 queue)
        {
            ImVector<const char*> device_extensions;
            device_extensions.push_back("VK_KHR_swapchain");

            // Enumerate physical device extension
            uint32_t properties_count;
            ImVector<VkExtensionProperties> properties;
            vkEnumerateDeviceExtensionProperties(Vulkan::localPhysicalDevice, nullptr, &properties_count, nullptr);
            properties.resize(properties_count);
            vkEnumerateDeviceExtensionProperties(
                Vulkan::localPhysicalDevice,
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
            queue_info[0].queueFamilyIndex = Vulkan::localQueueFamily;
            queue_info[0].queueCount = 1;
            queue_info[0].pQueuePriorities = queue_priority;
            VkDeviceCreateInfo create_info = {};
            create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            create_info.queueCreateInfoCount = std::size(queue_info);
            create_info.pQueueCreateInfos = queue_info;
            create_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.Size);
            create_info.ppEnabledExtensionNames = device_extensions.Data;
            err = vkCreateDevice(
                Vulkan::localPhysicalDevice,
                &create_info,
                Vulkan::localAllocator,
                &Vulkan::localDevice
            );
            check_vk_result(err);
            vkGetDeviceQueue(Vulkan::localDevice, Vulkan::localQueueFamily, 0, &Vulkan::localQueue);
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
                Vulkan::localDevice,
                &pool_info,
                Vulkan::localAllocator,
                &Vulkan::localDescriptorPool
            );
            check_vk_result(err);
        }
    }

    void WindowHandler::DestroyVulkan()
    {
        vkDestroyDescriptorPool(Vulkan::localDevice, Vulkan::localDescriptorPool, Vulkan::localAllocator);

#ifdef APP_USE_VULKAN_DEBUG_REPORT
        // Remove the debug report callback
        auto f_vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(
            g_Instance,
            "vkDestroyDebugReportCallbackEXT"
        );
        f_vkDestroyDebugReportCallbackEXT(g_Instance, g_DebugReport, Vulkan::localAllocator);
#endif // APP_USE_VULKAN_DEBUG_REPORT

        vkDestroyDevice(Vulkan::localDevice, Vulkan::localAllocator);
        vkDestroyInstance(Vulkan::localInstance, Vulkan::localAllocator);

        //Reset variables
        Vulkan::localInstance = VK_NULL_HANDLE;
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
        const VkResult err = vkDeviceWaitIdle(Vulkan::localDevice);
        check_vk_result(err);
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void WindowHandler::CreateWindow(Window& outWindow, int aWidth, int aHeight, const std::string& aTitle)
    {
        outWindow.windowData = new ImGui_ImplVulkanH_Window();

        // Create window with Vulkan context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        const float mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
        // Valid on GLFW 3.3+ only
        outWindow.windowHandle = glfwCreateWindow(
            static_cast<int>(aWidth * mainScale),
            static_cast<int>(aHeight * mainScale),
            aTitle.c_str(),
            nullptr,
            nullptr
        );

        VkSurfaceKHR surface;
        const VkResult err = glfwCreateWindowSurface(
            Vulkan::localInstance,
            outWindow.windowHandle,
            Vulkan::localAllocator,
            &surface
        );
        check_vk_result(err);

        glfwGetFramebufferSize(outWindow.windowHandle, &aWidth, &aHeight);
        outWindow.windowData = outWindow.windowData;
        outWindow.windowData->Surface = surface;

        // Check for WSI support
        VkBool32 res;
        vkGetPhysicalDeviceSurfaceSupportKHR(
            Vulkan::localPhysicalDevice,
            Vulkan::localQueueFamily,
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
            Vulkan::localPhysicalDevice,
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
            Vulkan::localPhysicalDevice,
            outWindow.windowData->Surface,
            &present_modes[0],
            IM_ARRAYSIZE(present_modes)
        );
        //printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

        // Create SwapChain, RenderPass, Framebuffer, etc.
        IM_ASSERT(outWindow.minImageCount >= 2);
        ImGui_ImplVulkanH_CreateOrResizeWindow(
            Vulkan::localInstance,
            Vulkan::localPhysicalDevice,
            Vulkan::localDevice,
            outWindow.windowData,
            Vulkan::localQueueFamily,
            Vulkan::localAllocator,
            aWidth,
            aHeight,
            outWindow.minImageCount,
            0
        );

        //TODO: figure out how to be able to open more than one window
        // Probably have to write my own logic for initialization

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForVulkan(outWindow.windowHandle, true);
        ImGui_ImplVulkan_InitInfo init_info = {};
        //init_info.ApiVersion = VK_API_VERSION_1_3;              // Pass in your value of VkApplicationInfo::apiVersion, otherwise will default to header version.
        init_info.Instance = Vulkan::localInstance;
        init_info.PhysicalDevice = Vulkan::localPhysicalDevice;
        init_info.Device = Vulkan::localDevice;
        init_info.QueueFamily = Vulkan::localQueueFamily;
        init_info.Queue = Vulkan::localQueue;
        init_info.PipelineCache = Vulkan::localPipelineCache;
        init_info.DescriptorPool = Vulkan::localDescriptorPool;
        init_info.MinImageCount = outWindow.minImageCount;
        init_info.ImageCount = outWindow.windowData->ImageCount;
        init_info.Allocator = Vulkan::localAllocator;
        init_info.PipelineInfoMain.RenderPass = outWindow.windowData->RenderPass;
        init_info.PipelineInfoMain.Subpass = 0;
        init_info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.CheckVkResultFn = check_vk_result;
        ImGui_ImplVulkan_Init(&init_info);
    }

    void WindowHandler::DestroyWindow(Window& outWindow)
    {
        ImGui_ImplVulkanH_DestroyWindow(
            Vulkan::localInstance,
            Vulkan::localDevice,
            outWindow.windowData,
            Vulkan::localAllocator
        );
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
        outWindow.drawData = nullptr;
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Resize swap chain?
        int fb_width, fb_height;
        glfwGetFramebufferSize(outWindow.windowHandle, &fb_width, &fb_height);
        if (fb_width > 0 && fb_height > 0 && (outWindow.rebuildSwapChain ||
                                              outWindow.windowData->Width != fb_width ||
                                              outWindow.windowData->Height != fb_height)) {
            ImGui_ImplVulkan_SetMinImageCount(outWindow.minImageCount);
            ImGui_ImplVulkanH_CreateOrResizeWindow(
                Vulkan::localInstance,
                Vulkan::localPhysicalDevice,
                Vulkan::localDevice,
                outWindow.windowData,
                Vulkan::localQueueFamily,
                Vulkan::localAllocator,
                fb_width,
                fb_height,
                outWindow.minImageCount,
                0
            );
            outWindow.windowData->FrameIndex = 0;
            outWindow.rebuildSwapChain = false;
        }
        if (glfwGetWindowAttrib(outWindow.windowHandle, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            return;
        }

        // Start the Dear ImGui frame
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        outWindow.imguiUpdateCallback(outWindow.windowData);

        // Rendering
        ImGui::Render();

        outWindow.drawData = ImGui::GetDrawData();
    }

    void WindowHandler::RenderWindow(Window& outWindow)
    {
        VkSemaphore image_acquired_semaphore = outWindow.windowData->FrameSemaphores[outWindow.windowData->
                    SemaphoreIndex].
                ImageAcquiredSemaphore;
        VkSemaphore render_complete_semaphore = outWindow.windowData->FrameSemaphores[outWindow.windowData->
                    SemaphoreIndex].
                RenderCompleteSemaphore;
        VkResult err = vkAcquireNextImageKHR(
            Vulkan::localDevice,
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
            err = vkWaitForFences(Vulkan::localDevice, 1, &fd->Fence, VK_TRUE, UINT64_MAX);
            // wait indefinitely instead of periodically checking
            check_vk_result(err);

            err = vkResetFences(Vulkan::localDevice, 1, &fd->Fence);
            check_vk_result(err);
        }
        {
            err = vkResetCommandPool(Vulkan::localDevice, fd->CommandPool, 0);
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
            err = vkQueueSubmit(Vulkan::localQueue, 1, &info, fd->Fence);
            check_vk_result(err);
        }
    }

    void WindowHandler::PresentWindow(Window& outWindow)
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
        const VkResult err = vkQueuePresentKHR(Vulkan::localQueue, &info);
        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
            outWindow.rebuildSwapChain = true;
        }
        if (err == VK_ERROR_OUT_OF_DATE_KHR) {
            return;
        }
        if (err != VK_SUBOPTIMAL_KHR) {
            check_vk_result(err);
        }
        outWindow.windowData->SemaphoreIndex = (outWindow.windowData->SemaphoreIndex + 1) % outWindow.windowData->
                                               SemaphoreCount;
    }
} // HomeworkHelper

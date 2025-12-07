#include "TestWindow.h"
#include "GUI/GUIIncludes.h"
#include "TestFunctions.h"

#include <iostream>

namespace HomeworkHelper
{
    TestWindow::TestWindow(
        const VulkanStaticData* someData,
        const std::string& aTitle,
        int aHeight,
        int aWidth,
        bool isFullscreen
    )
    {
        CreateWindow(someData, aTitle, aHeight, aWidth, isFullscreen);
    }

    TestWindow::~TestWindow()
    {
        DestroyWindow();
    }

    void TestWindow::CreateWindow(
        const VulkanStaticData* someData,
        const std::string& aTitle,
        int aHeight,
        int aWidth,
        bool isFullscreen
    )
    {
        DestroyWindow();
        vulkanData = someData;
        width = aWidth;
        height = aHeight;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        if (isFullscreen) {
            windowHandle = glfwCreateWindow(width, height, aTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
        }
        else {
            windowHandle = glfwCreateWindow(width, height, aTitle.c_str(), nullptr, nullptr);
        }

        if (glfwCreateWindowSurface(
                vulkanData->Instance(),
                windowHandle,
                vulkanData->Allocator(),
                &surface
            ) != VK_SUCCESS) {
            std::cerr << "Failed to create surface" << std::endl;
            return;
        }

        CreateSwapChain();
        CreatePipeline();
        CreateFrameBuffer();
        CreateWindowCommandBuffer();
        SubmitWindowCommandBuffer();
    }

    void TestWindow::DestroyWindow()
    {
        if (vulkanData && surface) {
            vkDestroySurfaceKHR(vulkanData->Instance(), surface, vulkanData->Allocator());
            surface = nullptr;
        }
        if (windowHandle) {
            glfwDestroyWindow(windowHandle);
            windowHandle = nullptr;
        }
    }

    void TestWindow::RenderWindow()
    {
        //glfwMakeContextCurrent(windowHandle);
        //glfwSwapBuffers(windowHandle);
    }

    bool TestWindow::IsOpen() const
    {
        return !glfwWindowShouldClose(windowHandle);
    }

    void TestWindow::CreateSwapChain()
    {
        // TODO: Research how queue and queueFamily works
        const auto& device = vulkanData->Device();
        const auto& allocator = vulkanData->Allocator();

        // Adapted IMGUI version
        VkSwapchainKHR oldSwapchain = swapchain;
        swapchain = VK_NULL_HANDLE;
        VkResult err = vkDeviceWaitIdle(device);
        CheckVkResult(err);

        // Destroy old Framebuffer
        for (auto frame: frames) {
            DestroyFrame(frame);
        }
        for (auto semaphores: frameSemaphores) {
            DestroyFrameSemaphore(semaphores);
        }
        frames.clear();
        frameSemaphores.clear();
        imageCount = 0;
        if (renderPass)
            vkDestroyRenderPass(device, renderPass, allocator);

        // Create Swapchain
        {
            VkSurfaceCapabilitiesKHR cap;
            err = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkanData->PhysicalDevice(), surface, &cap);
            CheckVkResult(err);

            VkSwapchainCreateInfoKHR info = {};
            info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            info.surface = surface;
            info.minImageCount = 2; // Since we are using FIFO
            info.imageFormat = surfaceFormat.format;
            info.imageColorSpace = surfaceFormat.colorSpace;
            info.imageArrayLayers = 1;
            info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
            info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // Assume that graphics family == present family
            info.preTransform = (cap.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) ?
                                    VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR :
                                    cap.currentTransform;
            info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            info.presentMode = VK_PRESENT_MODE_FIFO_KHR;
            info.clipped = VK_TRUE;
            info.oldSwapchain = oldSwapchain;
            if (info.minImageCount < cap.minImageCount)
                info.minImageCount = cap.minImageCount;
            else if (cap.maxImageCount != 0 && info.minImageCount > cap.maxImageCount)
                info.minImageCount = cap.maxImageCount;
            if (cap.currentExtent.width == 0xffffffff) {
                info.imageExtent.width = width;
                info.imageExtent.height = height;
            }
            else {
                info.imageExtent.width = width = cap.currentExtent.width;
                info.imageExtent.height = height = cap.currentExtent.height;
            }
            err = vkCreateSwapchainKHR(device, &info, allocator, &swapchain);
            CheckVkResult(err);
            err = vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
            CheckVkResult(err);
            VkImage backbuffers[16] = {};
            IM_ASSERT(imageCount >= 2);
            IM_ASSERT(imageCount < IM_ARRAYSIZE(backbuffers));
            err = vkGetSwapchainImagesKHR(device, swapchain, &imageCount, backbuffers);
            CheckVkResult(err);

            semaphoreCount = imageCount + 1;
            frames.resize(imageCount);
            frameSemaphores.resize(semaphoreCount);
            memset(frames.data(), 0, frames.size() * sizeof(VulkanFrameData));
            memset(frameSemaphores.data(), 0, frameSemaphores.size() * sizeof(VulkanFrameSemaphores));
            for (uint32_t i = 0; i < imageCount; i++)
                frames[i].backbuffer = backbuffers[i];
        }
        if (oldSwapchain)
            vkDestroySwapchainKHR(device, oldSwapchain, allocator);

        // Create the Render Pass
        if (useDynamicRendering == false) {
            VkAttachmentDescription attachment = {};
            attachment.format = surfaceFormat.format;
            attachment.samples = VK_SAMPLE_COUNT_1_BIT;
            attachment.loadOp = clearEnable ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
            attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            VkAttachmentReference color_attachment = {};
            color_attachment.attachment = 0;
            color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            VkSubpassDescription subpass = {};
            subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            subpass.colorAttachmentCount = 1;
            subpass.pColorAttachments = &color_attachment;
            VkSubpassDependency dependency = {};
            dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
            dependency.dstSubpass = 0;
            dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependency.srcAccessMask = 0;
            dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            VkRenderPassCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            info.attachmentCount = 1;
            info.pAttachments = &attachment;
            info.subpassCount = 1;
            info.pSubpasses = &subpass;
            info.dependencyCount = 1;
            info.pDependencies = &dependency;
            err = vkCreateRenderPass(device, &info, allocator, &renderPass);
            CheckVkResult(err);
        }
    }

    struct ImGui_ImplVulkan_PipelineInfo
    {
        // For Main viewport only
        VkRenderPass                    RenderPass;                     // Ignored if using dynamic rendering

        // For Main and Secondary viewports
        uint32_t                        Subpass;                        //
        VkSampleCountFlagBits           MSAASamples = {};               // 0 defaults to VK_SAMPLE_COUNT_1_BIT
#ifdef IMGUI_IMPL_VULKAN_HAS_DYNAMIC_RENDERING
        VkPipelineRenderingCreateInfoKHR PipelineRenderingCreateInfo;   // Optional, valid if .sType == VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR
#endif

        // For Secondary viewports only (created/managed by backend)
        VkImageUsageFlags               SwapChainImageUsage;            // Extra flags for vkCreateSwapchainKHR() calls for secondary viewports. We automatically add VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT. You can add e.g. VK_IMAGE_USAGE_TRANSFER_SRC_BIT if you need to capture from viewports.
    } info;

    void TestWindow::CreatePipeline()
    {
        // Adapted IMGUI version
//         ImGui_ImplVulkan_Data* bd = ImGui_ImplVulkan_GetBackendData();
//         ImGui_ImplVulkan_CreateShaderModules(device, allocator);
//
//         VkPipelineShaderStageCreateInfo stage[2] = {};
//         stage[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//         stage[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
//         stage[0].module = bd->ShaderModuleVert;
//         stage[0].pName = "main";
//         stage[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//         stage[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
//         stage[1].module = bd->ShaderModuleFrag;
//         stage[1].pName = "main";
//
//         VkVertexInputBindingDescription binding_desc[1] = {};
//         binding_desc[0].stride = sizeof(ImDrawVert);
//         binding_desc[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
//
//         VkVertexInputAttributeDescription attribute_desc[3] = {};
//         attribute_desc[0].location = 0;
//         attribute_desc[0].binding = binding_desc[0].binding;
//         attribute_desc[0].format = VK_FORMAT_R32G32_SFLOAT;
//         attribute_desc[0].offset = offsetof(ImDrawVert, pos);
//         attribute_desc[1].location = 1;
//         attribute_desc[1].binding = binding_desc[0].binding;
//         attribute_desc[1].format = VK_FORMAT_R32G32_SFLOAT;
//         attribute_desc[1].offset = offsetof(ImDrawVert, uv);
//         attribute_desc[2].location = 2;
//         attribute_desc[2].binding = binding_desc[0].binding;
//         attribute_desc[2].format = VK_FORMAT_R8G8B8A8_UNORM;
//         attribute_desc[2].offset = offsetof(ImDrawVert, col);
//
//         VkPipelineVertexInputStateCreateInfo vertex_info = {};
//         vertex_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
//         vertex_info.vertexBindingDescriptionCount = 1;
//         vertex_info.pVertexBindingDescriptions = binding_desc;
//         vertex_info.vertexAttributeDescriptionCount = 3;
//         vertex_info.pVertexAttributeDescriptions = attribute_desc;
//
//         VkPipelineInputAssemblyStateCreateInfo ia_info = {};
//         ia_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
//         ia_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
//
//         VkPipelineViewportStateCreateInfo viewport_info = {};
//         viewport_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
//         viewport_info.viewportCount = 1;
//         viewport_info.scissorCount = 1;
//
//         VkPipelineRasterizationStateCreateInfo raster_info = {};
//         raster_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
//         raster_info.polygonMode = VK_POLYGON_MODE_FILL;
//         raster_info.cullMode = VK_CULL_MODE_NONE;
//         raster_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
//         raster_info.lineWidth = 1.0f;
//
//         VkPipelineMultisampleStateCreateInfo ms_info = {};
//         ms_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
//         ms_info.rasterizationSamples = (info->MSAASamples != 0) ? info->MSAASamples : VK_SAMPLE_COUNT_1_BIT;
//
//         VkPipelineColorBlendAttachmentState color_attachment[1] = {};
//         color_attachment[0].blendEnable = VK_TRUE;
//         color_attachment[0].srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
//         color_attachment[0].dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
//         color_attachment[0].colorBlendOp = VK_BLEND_OP_ADD;
//         color_attachment[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
//         color_attachment[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
//         color_attachment[0].alphaBlendOp = VK_BLEND_OP_ADD;
//         color_attachment[0].colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
//                                              VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
//
//         VkPipelineDepthStencilStateCreateInfo depth_info = {};
//         depth_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
//
//         VkPipelineColorBlendStateCreateInfo blend_info = {};
//         blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
//         blend_info.attachmentCount = 1;
//         blend_info.pAttachments = color_attachment;
//
//         VkDynamicState dynamic_states[2] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
//         VkPipelineDynamicStateCreateInfo dynamic_state = {};
//         dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
//         dynamic_state.dynamicStateCount = (uint32_t) IM_ARRAYSIZE(dynamic_states);
//         dynamic_state.pDynamicStates = dynamic_states;
//
//         VkGraphicsPipelineCreateInfo create_info = {};
//         create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
//         create_info.flags = bd->PipelineCreateFlags;
//         create_info.stageCount = 2;
//         create_info.pStages = stage;
//         create_info.pVertexInputState = &vertex_info;
//         create_info.pInputAssemblyState = &ia_info;
//         create_info.pViewportState = &viewport_info;
//         create_info.pRasterizationState = &raster_info;
//         create_info.pMultisampleState = &ms_info;
//         create_info.pDepthStencilState = &depth_info;
//         create_info.pColorBlendState = &blend_info;
//         create_info.pDynamicState = &dynamic_state;
//         create_info.layout = bd->PipelineLayout;
//         create_info.renderPass = info->RenderPass;
//         create_info.subpass = info->Subpass;
//
// #ifdef IMGUI_IMPL_VULKAN_HAS_DYNAMIC_RENDERING
//         if (bd->VulkanInitInfo.UseDynamicRendering) {
//             IM_ASSERT(
//                 info->PipelineRenderingCreateInfo.sType == VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR &&
//                 "PipelineRenderingCreateInfo::sType must be VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR"
//             );
//             IM_ASSERT(
//                 info->PipelineRenderingCreateInfo.pNext == nullptr &&
//                 "PipelineRenderingCreateInfo::pNext must be nullptr"
//             );
//             create_info.pNext = &info->PipelineRenderingCreateInfo;
//             create_info.renderPass = VK_NULL_HANDLE; // Just make sure it's actually nullptr.
//         }
// #endif
//         VkPipeline pipeline;
//         VkResult err = vkCreateGraphicsPipelines(
//             vulkanData->Device(),
//             pipelineCache,
//             1,
//             &create_info,
//             vulkanData->Allocator(),
//             &pipeline
//         );
//         CheckVkResult(err);
    }

    void TestWindow::CreateFrameBuffer()
    {
        // Adapted IMGUI version
        const auto& device = vulkanData->Device();
        const auto& allocator = vulkanData->Allocator();
        VkResult err;
        // Create The Image Views
        {
            VkImageViewCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            info.viewType = VK_IMAGE_VIEW_TYPE_2D;
            info.format = surfaceFormat.format;
            info.components.r = VK_COMPONENT_SWIZZLE_R;
            info.components.g = VK_COMPONENT_SWIZZLE_G;
            info.components.b = VK_COMPONENT_SWIZZLE_B;
            info.components.a = VK_COMPONENT_SWIZZLE_A;
            VkImageSubresourceRange image_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
            info.subresourceRange = image_range;
            for (auto frame: frames) {
                info.image = frame.backbuffer;
                err = vkCreateImageView(device, &info, allocator, &frame.backbufferView);
                CheckVkResult(err);
            }
        }

        // Create Framebuffer
        if (useDynamicRendering == false) {
            VkImageView attachment[1];
            VkFramebufferCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            info.renderPass = renderPass;
            info.attachmentCount = 1;
            info.pAttachments = attachment;
            info.width = width;
            info.height = height;
            info.layers = 1;
            for (auto frame: frames) {
                attachment[0] = frame.backbufferView;
                err = vkCreateFramebuffer(device, &info, allocator, &frame.framebuffer);
                CheckVkResult(err);
            }
        }
    }

    void TestWindow::CreateWindowCommandBuffer()
    {
        const auto& device = vulkanData->Device();
        const auto& allocator = vulkanData->Allocator();
        VkResult err;
        // Create Command Buffers
        for (auto frame: frames) {
            {
                VkCommandPoolCreateInfo info = {};
                info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                info.flags = 0;
                info.queueFamilyIndex = vulkanData->QueueFamily();
                err = vkCreateCommandPool(device, &info, allocator, &frame.commandPool);
                CheckVkResult(err);
            }
            {
                VkCommandBufferAllocateInfo info = {};
                info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                info.commandPool = frame.commandPool;
                info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                info.commandBufferCount = 1;
                err = vkAllocateCommandBuffers(device, &info, &frame.commandBuffer);
                CheckVkResult(err);
            }
            {
                VkFenceCreateInfo info = {};
                info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
                info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
                err = vkCreateFence(device, &info, allocator, &frame.fence);
                CheckVkResult(err);
            }
        }

        for (auto semaphores: frameSemaphores) {
            {
                VkSemaphoreCreateInfo info = {};
                info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
                err = vkCreateSemaphore(device, &info, allocator, &semaphores.imageAcquiredSemaphore);
                CheckVkResult(err);
                err = vkCreateSemaphore(device, &info, allocator, &semaphores.renderCompleteSemaphore);
                CheckVkResult(err);
            }
        }
    }

    void TestWindow::SubmitWindowCommandBuffer()
    {
        const auto& device = vulkanData->Device();
        const auto& allocator = vulkanData->Allocator();

        // FIXME: to submit the command buffer, we need a queue. In the examples folder, the ImGui_ImplVulkanH_CreateOrResizeWindow function is called
        // before the ImGui_ImplVulkan_Init function, so we don't have access to the queue yet. Here we have the queue_family that we can use to grab
        // a queue from the device and submit the command buffer. It would be better to have access to the queue as suggested in the FIXME below.
        VkCommandPool command_pool;
        VkCommandPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_info.queueFamilyIndex = vulkanData->QueueFamily();
        pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        VkResult err = vkCreateCommandPool(device, &pool_info, allocator, &command_pool);
        CheckVkResult(err);

        VkFenceCreateInfo fence_info = {};
        fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        VkFence fence;
        err = vkCreateFence(device, &fence_info, allocator, &fence);
        CheckVkResult(err);

        VkCommandBufferAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.commandPool = command_pool;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandBufferCount = 1;
        VkCommandBuffer command_buffer;
        err = vkAllocateCommandBuffers(device, &alloc_info, &command_buffer);
        CheckVkResult(err);

        VkCommandBufferBeginInfo begin_info = {};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(command_buffer, &begin_info);
        CheckVkResult(err);

        // Transition the images to the correct layout for rendering
        for (auto frame: frames) {
            VkImageMemoryBarrier barrier = {};
            barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            barrier.image = frame.backbuffer;
            barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            barrier.subresourceRange.levelCount = 1;
            barrier.subresourceRange.layerCount = 1;
            vkCmdPipelineBarrier(
                command_buffer,
                VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                0,
                0,
                nullptr,
                0,
                nullptr,
                1,
                &barrier
            );
        }

        err = vkEndCommandBuffer(command_buffer);
        CheckVkResult(err);
        VkSubmitInfo submit_info = {};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &command_buffer;

        VkQueue queue;
        vkGetDeviceQueue(device, vulkanData->QueueFamily(), 0, &queue);
        err = vkQueueSubmit(queue, 1, &submit_info, fence);
        CheckVkResult(err);
        err = vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
        CheckVkResult(err);
        err = vkResetFences(device, 1, &fence);
        CheckVkResult(err);

        err = vkResetCommandPool(device, command_pool, 0);
        CheckVkResult(err);

        // Destroy command buffer and fence and command pool
        vkFreeCommandBuffers(device, command_pool, 1, &command_buffer);
        vkDestroyCommandPool(device, command_pool, allocator);
        vkDestroyFence(device, fence, allocator);
        command_pool = VK_NULL_HANDLE;
        command_buffer = VK_NULL_HANDLE;
        fence = VK_NULL_HANDLE;
        queue = VK_NULL_HANDLE;
    }

    void TestWindow::DestroyFrame(VulkanFrameData& outFrame)
    {
        const auto& device = vulkanData->Device();
        const auto& allocator = vulkanData->Allocator();

        vkDestroyFence(device, outFrame.fence, allocator);
        vkFreeCommandBuffers(device, outFrame.commandPool, 1, &outFrame.commandBuffer);
        vkDestroyCommandPool(device, outFrame.commandPool, allocator);
        outFrame.fence = VK_NULL_HANDLE;
        outFrame.commandBuffer = VK_NULL_HANDLE;
        outFrame.commandPool = VK_NULL_HANDLE;

        vkDestroyImageView(device, outFrame.backbufferView, allocator);
        vkDestroyFramebuffer(device, outFrame.framebuffer, allocator);
    }

    void TestWindow::DestroyFrameSemaphore(VulkanFrameSemaphores& outFrameSemaphore)
    {
        const auto& device = vulkanData->Device();
        const auto& allocator = vulkanData->Allocator();

        vkDestroySemaphore(device, outFrameSemaphore.imageAcquiredSemaphore, allocator);
        vkDestroySemaphore(device, outFrameSemaphore.renderCompleteSemaphore, allocator);
        outFrameSemaphore.imageAcquiredSemaphore = VK_NULL_HANDLE;
        outFrameSemaphore.renderCompleteSemaphore = VK_NULL_HANDLE;
    }
} // HomeworkHelper

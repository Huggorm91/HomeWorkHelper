#include "TestWindow.h"
#include "GUI/GUIIncludes.h"

#include <iostream>

namespace HomeworkHelper
{
    TestWindow::TestWindow(const VulkanData* someData, const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen)
    {
        CreateWindow(someData, aTitle, aHeight, aWidth, isFullscreen);
    }

    TestWindow::~TestWindow()
    {
        DestroyWindow();
    }

    void TestWindow::CreateWindow(const VulkanData* someData, const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen)
    {
        DestroyWindow();
        vulkanData = someData;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        if (isFullscreen) {
            windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
        }
        else {
            windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), nullptr, nullptr);
        }

        if (glfwCreateWindowSurface(vulkanData->Instance(), windowHandle, vulkanData->Allocator(), &surface) != VK_SUCCESS) {
            std::cerr << "Failed to create surface" << std::endl;
            return;
        }

        CreateSwapChain();
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

        VkSwapchainCreateInfoKHR swapchainInfo = {};
        VkResult err = vkCreateSwapchainKHR(vulkanData->Device(), &swapchainInfo, vulkanData->Allocator(), &swapChain);
        if (err != VK_SUCCESS) {
            std::cerr << "Vulkan failed to create SwapChain. Error: " << static_cast<long>(err) << std::endl;
            return;
        }
    }
} // HomeworkHelper

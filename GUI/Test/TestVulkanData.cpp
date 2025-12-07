#include "TestVulkanData.h"
#include "TestFunctions.h"

#include <iostream>

VulkanStaticData::VulkanStaticData()
{
    allocator = nullptr;
    instance = VK_NULL_HANDLE;
    CreateInstance(&instance, allocator);

    // Select Physical Device (GPU)
    physicalDevice = ImGui_ImplVulkanH_SelectPhysicalDevice(instance);
    if (physicalDevice == VK_NULL_HANDLE) {
        std::cerr << "Failed to create physical device" << std::endl;
        vkDestroyInstance(instance, allocator);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Select graphics queue family
    queueFamily = ImGui_ImplVulkanH_SelectQueueFamilyIndex(physicalDevice);
    if (queueFamily == static_cast<uint32_t>(-1)) {
        std::cerr << "Failed to create physical device" << std::endl;
        vkDestroyInstance(instance, allocator);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    device = VK_NULL_HANDLE;
    CreateDevice(physicalDevice, allocator, &device, queueFamily);

    queue = VK_NULL_HANDLE;
    vkGetDeviceQueue(device, queueFamily, 0, &queue);

    descriptorPool = VK_NULL_HANDLE;
    CreateDescriptorPool(device, allocator, &descriptorPool);
}

VulkanStaticData::~VulkanStaticData()
{
    if (*this)
        Destroy();
}

VulkanStaticData::operator bool() const
{
    return device && instance && physicalDevice;
}

void VulkanStaticData::Destroy()
{
    vkDestroyDescriptorPool(device, descriptorPool, allocator);
    descriptorPool = nullptr;

    vkDestroyDevice(device, allocator);
    device = nullptr;

    vkDestroyInstance(instance, allocator);
    instance = nullptr;

    allocator = nullptr;
    physicalDevice = nullptr;
}

unsigned VulkanStaticData::QueueFamily() const
{
    return queueFamily;
}

VkDevice_T* VulkanStaticData::Device() const
{
    return device;
}

VkInstance_T* VulkanStaticData::Instance() const
{
    return instance;
}

VkDescriptorPool_T* VulkanStaticData::DescriptorPool() const
{
    return descriptorPool;
}

VkPhysicalDevice_T* VulkanStaticData::PhysicalDevice() const
{
    return physicalDevice;
}

VkAllocationCallbacks* VulkanStaticData::Allocator() const
{
    return allocator;
}

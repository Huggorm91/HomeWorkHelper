#ifndef HOMEWORKHELPER_TESTFUNCTIONS_H
#define HOMEWORKHELPER_TESTFUNCTIONS_H
#include "GUI/GUIIncludes.h"
#include <vector>
#include <format>

inline bool IsExtensionAvailable(const std::vector<VkExtensionProperties>& properties, const char* extension)
{
    for (const VkExtensionProperties& property: properties) {
        if (strcmp(property.extensionName, extension) == 0) {
            return true;
        }
    }
    return false;
}

inline void CheckVkResult(const VkResult err)
{
    if (err < VK_SUCCESS) {
        throw std::runtime_error(std::format("[vulkan] Error: VkResult = {}", static_cast<long>(err)));
    }
}

inline void CreateInstance(VkInstance* outInstance, VkAllocationCallbacks*& outAllocator)
{
    VkInstanceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    std::vector<const char*> instanceExtensions;
    uint32_t extensions_count = 0;
    const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
    for (uint32_t i = 0; i < extensions_count; i++) {
        instanceExtensions.push_back(glfw_extensions[i]);
    }

    // Enumerate available extensions
    uint32_t properties_count;
    std::vector<VkExtensionProperties> properties;
    vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, nullptr);
    properties.resize(properties_count);

    VkResult err = vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, properties.data());
    CheckVkResult(err);

    // Enable required extensions
    if (IsExtensionAvailable(properties, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME)) {
        instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    }
#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
    if (IsExtensionAvailable(properties, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)) {
        instanceExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }
#endif

    info.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    info.ppEnabledExtensionNames = instanceExtensions.data();
    err = vkCreateInstance(&info, outAllocator, outInstance);
    CheckVkResult(err);
}


inline void CreateDevice(
    VkPhysicalDevice aPhysicalDevice,
    VkAllocationCallbacks* anAllocator,
    VkDevice* outDevice,
    uint32_t queueFamily
)
{
    // Create Logical Device (with 1 queue)
    ImVector<const char*> device_extensions;
    device_extensions.push_back("VK_KHR_swapchain");

    // Enumerate physical device extension
    uint32_t properties_count;
    ImVector<VkExtensionProperties> properties;
    vkEnumerateDeviceExtensionProperties(aPhysicalDevice, nullptr, &properties_count, nullptr);
    properties.resize(static_cast<int>(properties_count));
    vkEnumerateDeviceExtensionProperties(
        aPhysicalDevice,
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
    queue_info[0].queueFamilyIndex = queueFamily;
    queue_info[0].queueCount = 1;
    queue_info[0].pQueuePriorities = queue_priority;
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.queueCreateInfoCount = std::size(queue_info);
    create_info.pQueueCreateInfos = queue_info;
    create_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.Size);
    create_info.ppEnabledExtensionNames = device_extensions.Data;
    const VkResult err = vkCreateDevice(
        aPhysicalDevice,
        &create_info,
        anAllocator,
        outDevice
    );
    CheckVkResult(err);
}


inline void CreateDescriptorPool(
    VkDevice aDevice,
    VkAllocationCallbacks* anAllocator,
    VkDescriptorPool* outDescriptorPool
)
{
    // Create Descriptor Pool
    // If you wish to load e.g. additional textures you may need to alter pools sizes and maxSets.
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
    const VkResult err = vkCreateDescriptorPool(
        aDevice,
        &pool_info,
        anAllocator,
        outDescriptorPool
    );
    CheckVkResult(err);
}

#endif //HOMEWORKHELPER_TESTFUNCTIONS_H

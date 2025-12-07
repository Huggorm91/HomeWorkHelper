#ifndef HOMEWORKHELPER_TESTVULKANDATA_H
#define HOMEWORKHELPER_TESTVULKANDATA_H
#include "vulkan/vulkan.h"

class VulkanStaticData
{
    unsigned queueFamily;
    VkQueue queue;
    VkDevice device = nullptr;
    VkInstance instance = nullptr;
    VkDescriptorPool descriptorPool = nullptr;
    VkPhysicalDevice physicalDevice = nullptr;
    VkAllocationCallbacks* allocator = nullptr;

public:
    VulkanStaticData();

    ~VulkanStaticData();

    explicit operator bool() const;

    void Destroy();

    unsigned QueueFamily() const;

    VkDevice Device() const;

    VkInstance Instance() const;

    VkDescriptorPool DescriptorPool() const;

    VkPhysicalDevice PhysicalDevice() const;

    VkAllocationCallbacks* Allocator() const;
};

struct VulkanFrameData
{
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkFence fence;
    VkImage backbuffer;
    VkImageView backbufferView;
    VkFramebuffer framebuffer;
};

struct VulkanFrameSemaphores
{
    VkSemaphore imageAcquiredSemaphore;
    VkSemaphore renderCompleteSemaphore;
};

#endif //HOMEWORKHELPER_TESTVULKANDATA_H

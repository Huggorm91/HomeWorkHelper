#ifndef HOMEWORKHELPER_TESTVULKANDATA_H
#define HOMEWORKHELPER_TESTVULKANDATA_H
#include "TestVulkanData.h"

struct VkQueue_T;
struct VkDevice_T;
struct VkInstance_T;
struct VkDescriptorPool_T;
struct VkPhysicalDevice_T;
struct VkAllocationCallbacks;

class VulkanData
{
    unsigned queueFamily;
    VkQueue_T* queue;
    VkDevice_T* device = nullptr;
    VkInstance_T* instance = nullptr;
    VkDescriptorPool_T* descriptorPool = nullptr;
    VkPhysicalDevice_T* physicalDevice = nullptr;
    VkAllocationCallbacks* allocator = nullptr;

public:
    VulkanData();
    ~VulkanData();

    explicit operator bool() const;

    void Destroy();

    unsigned QueueFamily() const;

    VkDevice_T* Device() const;

    VkInstance_T* Instance() const;

    VkDescriptorPool_T* DescriptorPool() const;

    VkPhysicalDevice_T* PhysicalDevice() const;

    VkAllocationCallbacks* Allocator() const;
};


#endif //HOMEWORKHELPER_TESTVULKANDATA_H
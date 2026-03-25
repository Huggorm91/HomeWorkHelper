#ifndef HOMEWORKHELPER_VULKANRENDER_H
#define HOMEWORKHELPER_VULKANRENDER_H
#include "RenderBase.h"

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
        void Render(Component::Window& outWindow) override;
        void Present(Component::Window& outWindow) override;

        void HandleResize(Component::Window& outWindow, int aNewWidth, int aNewHeight) override;

        void CreateWindow(Component::Window& outWindow) override;
        void DestroyWindow(Component::Window& outWindow) override;

        [[nodiscard]] constexpr int GetGlfwWindowHint() const override;
        [[nodiscard]] constexpr int GetGlfwWindowHintValue() const override;
    };
} // HomeworkHelper::Rendering

#endif //HOMEWORKHELPER_VULKANRENDER_H

#ifndef HOMEWORKHELPER_RENDERBASE_H
#define HOMEWORKHELPER_RENDERBASE_H
#include "GUI/ImguiComponents/Window.h"

namespace HomeworkHelper::Rendering
{
    class RenderBase
    {
    public:
        RenderBase() = default;
        virtual ~RenderBase() = default;

        virtual void Init() = 0;
        virtual void Shutdown() = 0;

        virtual void Update() = 0;
        virtual void Render(Component::Window& outWindow) = 0;
        virtual void Present(Component::Window& outWindow) = 0;

        virtual void HandleResize(Component::Window& outWindow, int aNewWidth, int aNewHeight) = 0;

        virtual void CreateWindow(Component::Window& outWindow) = 0;
        virtual void DestroyWindow(Component::Window& outWindow) = 0;

        [[nodiscard]] virtual constexpr int GetGlfwWindowHint() const = 0;
        [[nodiscard]] virtual constexpr int GetGlfwWindowHintValue() const = 0;
    };
} // HomeworkHelper::Rendering

#endif //HOMEWORKHELPER_RENDERBASE_H

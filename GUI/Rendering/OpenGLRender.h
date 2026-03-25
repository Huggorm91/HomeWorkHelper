#ifndef HOMEWORKHELPER_OPENGLRENDER_H
#define HOMEWORKHELPER_OPENGLRENDER_H
#include "RenderBase.h"

namespace HomeworkHelper::Rendering
{
    class OpenGLRender : public RenderBase
    {
    public:
        OpenGLRender() = default;
        ~OpenGLRender() override = default;

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

#endif //HOMEWORKHELPER_OPENGLRENDER_H

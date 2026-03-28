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
        void Render(Window& outWindow) override;
        void Present(Window& outWindow) override;

        void HandleResize(Window& outWindow, int aNewWidth, int aNewHeight) override;

        void CreateWindow(Window& outWindow) override;
        void DestroyWindow(Window& outWindow) override;

        [[nodiscard]] constexpr int GetGlfwWindowHint() const override;
        [[nodiscard]] constexpr int GetGlfwWindowHintValue() const override;
    };
} // HomeworkHelper::Rendering

#endif //HOMEWORKHELPER_OPENGLRENDER_H

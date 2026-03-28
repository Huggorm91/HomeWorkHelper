#include "OpenGLRender.h"
#include "GUI/GUIIncludes.h"

namespace HomeworkHelper::Rendering
{
    void OpenGLRender::Init()
    {
    }

    void OpenGLRender::Shutdown()
    {
        ImGui_ImplOpenGL2_Shutdown();
    }

    void OpenGLRender::Update()
    {
        ImGui_ImplOpenGL2_NewFrame();
    }

    void OpenGLRender::Render(Window& outWindow)
    {
        glViewport(0, 0, outWindow.width, outWindow.height);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // If you are using this code with non-legacy OpenGL header/contexts (which you should not, prefer using imgui_impl_opengl3.cpp!!),
        // you may need to backup/reset/restore other state, e.g. for current shader using the commented lines below.
        //GLint last_program;
        //glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        //glUseProgram(0);
        ImGui_ImplOpenGL2_RenderDrawData(outWindow.drawData);
        //glUseProgram(last_program);
    }

    void OpenGLRender::Present(Window& outWindow)
    {
        glfwMakeContextCurrent(outWindow.windowHandle);
        glfwSwapBuffers(outWindow.windowHandle);
    }

    void OpenGLRender::HandleResize(Window& outWindow, const int aNewWidth, const int aNewHeight)
    {
        outWindow.width = aNewWidth;
        outWindow.height = aNewHeight;
    }

    void OpenGLRender::CreateWindow(Window& outWindow)
    {
        glfwMakeContextCurrent(outWindow.windowHandle);
        glfwSwapInterval(1); // Enable vsync

        //TODO: figure out how to be able to open more than one window
        // Probably have to write my own logic for initialization
        ImGui_ImplGlfw_InitForOpenGL(outWindow.windowHandle, true);
        ImGui_ImplOpenGL2_Init();
    }

    void OpenGLRender::DestroyWindow(Window& outWindow)
    {
        // TODO: Destroy OpenGL related objects (If any)
    }

    constexpr int OpenGLRender::GetGlfwWindowHint() const
    {
        return GLFW_CLIENT_API;
    }

    constexpr int OpenGLRender::GetGlfwWindowHintValue() const
    {
        return GLFW_OPENGL_API;
    }
} // HomeworkHelper::Rendering

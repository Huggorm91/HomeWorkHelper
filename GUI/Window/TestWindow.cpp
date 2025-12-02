#include "TestWindow.h"
#include "GUI/GUIIncludes.h"

namespace HomeworkHelper
{
    TestWindow::TestWindow(const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen)
    {
        CreateWindow(aTitle, aHeight, aWidth, isFullscreen);
    }

    TestWindow::~TestWindow()
    {
        DestroyWindow();
    }

    void TestWindow::CreateWindow(const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen)
    {
        DestroyWindow();

        if (isFullscreen) {
            windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
        }
        else {
            windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), nullptr, nullptr);
        }
    }

    void TestWindow::DestroyWindow()
    {
        if (windowHandle) {
            glfwDestroyWindow(windowHandle);
            windowHandle = nullptr;
        }
    }

    void TestWindow::RenderWindow()
    {
        glfwMakeContextCurrent(windowHandle);
        glfwSwapBuffers(windowHandle);
    }

    bool TestWindow::IsOpen() const
    {
        return !glfwWindowShouldClose(windowHandle);
    }
} // HomeworkHelper

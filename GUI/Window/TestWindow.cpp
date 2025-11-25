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
        ClearWindow();
    }

    void TestWindow::CreateWindow(const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen)
    {
        ClearWindow();

        if (isFullscreen) {
            windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
        }
        else {
            windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), nullptr, nullptr);
        }
    }

    void TestWindow::ClearWindow()
    {
        if (windowHandle) {
            glfwDestroyWindow(windowHandle);
            windowHandle = nullptr;
        }
    }
} // HomeworkHelper

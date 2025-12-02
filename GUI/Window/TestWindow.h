#ifndef TEST_WINDOW_H
#define TEST_WINDOW_H
#include <string>

struct GLFWwindow;

namespace HomeworkHelper
{
    // Quickly thrown together in Notepad++ while having nothing to do at work
    class TestWindow
    {
    public:
        TestWindow() = default;
        TestWindow(const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen = false);

        ~TestWindow();

        void CreateWindow(const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen = false);
        void DestroyWindow();

        void RenderWindow();

        bool IsOpen() const;

    private:
        GLFWwindow* windowHandle = nullptr;
    };
} // HomeworkHelper

#endif //TEST_WINDOW_H

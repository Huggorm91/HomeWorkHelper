#ifndef HOMEWORKHELPER_WINDOW_H
#define HOMEWORKHELPER_WINDOW_H
#include <string>

struct ImDrawData;
struct GLFWwindow;

namespace HomeworkHelper {
	// Quickly thrown together in Notepad++ while having nothing to do at work
    class TestWindow {
        bool rebuildSwapChain = false;
        unsigned minImageCount = 2;
        GLFWwindow* windowHandle = nullptr;
        ImDrawData* drawData = nullptr;
		
		void ClearWindow();
		
	public:
		TestWindow() = default;
		~TestWindow();
		
		CreateWindow(const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen);
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_WINDOW_H
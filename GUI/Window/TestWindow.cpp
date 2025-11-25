#include "TestWindow.h"
#include "GUI/GUIIncludes.h"

namespace HomeworkHelper
{
	TestWindow::ClearWindow(){
		if(windowHandle){
			glfwDestroyWindow(windowHandle);
			windowHandle = nullptr;
		}
	}
	
	TestWindow::~TestWindow(){
		ClearWindow();
		
		if(drawData){
			delete drawData
			drawData = nullptr;
		}
	}
	
	TestWindow::CreateWindow(const std::string& aTitle, int aHeight, int aWidth, bool isFullscreen){
		ClearWindow();
		
		if(isFullscreen){
			windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle, glfwGetPrimaryMonitor(), nullptr);
		}
		else{
			windowHandle = glfwCreateWindow(aWidth, aHeight, aTitle, nullptr, nullptr);
		}
	}
} // HomeworkHelper

#include "GUI/Window/WindowHandler.h"
#include "GUI/Window/HomeworkWindow.h"
#include "GUI/Window/TestWindow.h"

int main()
{
    // HomeworkHelper::HomeworkWindow window;
    // window.GenerateImguiContent();

    HomeworkHelper::WindowHandler::Initialize();
    // int windowID = HomeworkHelper::WindowHandler::CreateWindow(
    //     800,
    //     1200,
    //     "Test",
    //     std::bind(&HomeworkHelper::HomeworkWindow::UpdateImguiContent, &window)
    // );

    // if (windowID == -1) {
    //     HomeworkHelper::WindowHandler::Shutdown();
    //     return -1;
    // }

    // window.SetWindowData(HomeworkHelper::WindowHandler::GetWindowData(windowID));


    HomeworkHelper::TestWindow small("Small Window", 400, 800);

    while (true) {

    }

    // Main loop
    while (HomeworkHelper::WindowHandler::IsAnyWindowOpen()) {
        HomeworkHelper::WindowHandler::RenderWindows();
    }

    HomeworkHelper::WindowHandler::Shutdown();
    return 0;
}

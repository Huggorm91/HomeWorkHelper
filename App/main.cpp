#include "GUI/Window/WindowHandler.h"
#include "GUI/Window/HomeworkWindow.h"

int main()
{
    HomeworkHelper::HomeworkWindow window;
    HomeworkHelper::WindowHandler::Initialize();
    int windowID = HomeworkHelper::WindowHandler::CreateWindow(
        800,
        1200,
        "Test",
        std::bind(&HomeworkHelper::HomeworkWindow::CreateImguiContent, &window)
    );

    if (windowID == -1) {
        HomeworkHelper::WindowHandler::Shutdown();
        return -1;
    }

    window.SetWindowData(HomeworkHelper::WindowHandler::GetWindowData(windowID));

    // Main loop
    while (HomeworkHelper::WindowHandler::IsAnyWindowOpen()) {
        HomeworkHelper::WindowHandler::RenderWindows();
    }

    HomeworkHelper::WindowHandler::Shutdown();
    return 0;
}

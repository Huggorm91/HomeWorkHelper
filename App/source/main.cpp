#include "WindowHandler.h"
#include "HomeworkWindow.h"

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

    // Main loop
    while (HomeworkHelper::WindowHandler::IsAnyWindowOpen()) {
        HomeworkHelper::WindowHandler::RenderWindows();
    }

    HomeworkHelper::WindowHandler::Shutdown();
    return 0;
}

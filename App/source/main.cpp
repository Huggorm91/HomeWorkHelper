#include "WindowHandler.h"
#include "HomeworkWindow.h"

int main(int, char **)
{
    HomeworkHelper::HomeworkWindow window;
    HomeworkHelper::WindowHandler::Initialize();
    HomeworkHelper::WindowHandler::CreateWindow(
        800,
        1200,
        "Test",
        std::bind(&HomeworkHelper::HomeworkWindow::CreateImguiContent, window, std::placeholders::_1));

    // Main loop
    while (HomeworkHelper::WindowHandler::IsAnyWindowOpen()) {
        HomeworkHelper::WindowHandler::RenderWindows();
    }

    HomeworkHelper::WindowHandler::Shutdown();
    return 0;
}

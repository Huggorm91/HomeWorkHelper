#include "WindowHandler.h"

int main(int, char **)
{
    HomeworkHelper::WindowHandler::Initialize();
    HomeworkHelper::WindowHandler::CreateWindow(800, 1200, "Test");

    // Main loop
    while (HomeworkHelper::WindowHandler::IsAnyWindowOpen()) {
        HomeworkHelper::WindowHandler::RenderWindows();
    }

    HomeworkHelper::WindowHandler::Shutdown();
    return 0;
}

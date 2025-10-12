#include "Window.h"

int main(int, char **)
{
    HomeworkHelper::Window window(1200, 800);

    // Main loop
    while (!window.ShouldClose()) {
        window.RenderWindow();
    }

    return 0;
}

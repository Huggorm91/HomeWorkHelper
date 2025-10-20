#ifndef HOMEWORKHELPER_HOMEWORKWINDOW_H
#define HOMEWORKHELPER_HOMEWORKWINDOW_H
#include <GLFW/glfw3.h>

struct ImGui_ImplVulkanH_Window;

namespace HomeworkHelper
{
    class HomeworkWindow
    {
        public:
        HomeworkWindow() = default;
        ~HomeworkWindow() = default;

        void CreateImguiContent();

        void SetWindowData(ImGui_ImplVulkanH_Window* someWindowData);

        private:
        bool show_another_window = false;
        ImGui_ImplVulkanH_Window* myWindowData = nullptr;
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_HOMEWORKWINDOW_H
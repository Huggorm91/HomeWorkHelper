#ifndef HOMEWORKHELPER_HOMEWORKWINDOW_H
#define HOMEWORKHELPER_HOMEWORKWINDOW_H
#include "Window.h"

namespace HomeworkHelper
{
    class HomeworkWindow
    {
        public:
        HomeworkWindow() = default;
        ~HomeworkWindow() = default;

        void CreateImguiContent(ImGui_ImplVulkanH_Window* someWindowData);

        private:
        bool show_demo_window = true;
        bool show_another_window = false ;
        float clear_color[4] = {0.45f, 0.55f, 0.60f, 1.00f};
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_HOMEWORKWINDOW_H
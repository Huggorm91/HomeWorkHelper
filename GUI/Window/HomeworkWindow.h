#ifndef HOMEWORKHELPER_HOMEWORKWINDOW_H
#define HOMEWORKHELPER_HOMEWORKWINDOW_H
#include <memory>
#include <vector>

#include "GUI/ImguiComponents/ImguiComponent.h"

struct ImGui_ImplVulkanH_Window;

namespace HomeworkHelper
{
    class HomeworkWindow
    {
        public:
        HomeworkWindow() = default;
        ~HomeworkWindow() = default;

        void GenerateImguiContent();

        void UpdateImguiContent();

        void SetWindowData(ImGui_ImplVulkanH_Window* someWindowData);

        private:
        bool show_another_window = false;
        ImGui_ImplVulkanH_Window* myWindowData = nullptr;
        std::vector<std::unique_ptr<Component::ImguiComponent>> myComponents;
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_HOMEWORKWINDOW_H
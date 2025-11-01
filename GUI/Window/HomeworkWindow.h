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
        //TODO: Remove these test variables
        bool show_another_window = false;
        int slider = 0;
        int counter = 0;

        ImGui_ImplVulkanH_Window* myWindowData = nullptr;
        std::vector<std::unique_ptr<Component::ImguiComponent>> myComponents;
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_HOMEWORKWINDOW_H
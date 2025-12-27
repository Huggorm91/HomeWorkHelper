#ifndef HOMEWORKHELPER_HOMEWORKWINDOW_H
#define HOMEWORKHELPER_HOMEWORKWINDOW_H
#include <array>
#include <memory>
#include <vector>

#include "Common/Math/MathGenerator.h"
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
        bool myHasAnswered = false;
        bool myIsUsingFloats = false;
        bool myShouldShowAnswer = false;
        int myMin = 0;
        int myMax = 10;

        union
        {
            int i;
            float f;
        } myAnswer = {};

        constexpr static char mySymbolList[]{
                    '+',
                    '-',
                    '*',
                    '/'
                };
        std::array<bool, sizeof(mySymbolList)> mySelectedSymbols = {false};
        ImGui_ImplVulkanH_Window* myWindowData = nullptr;
        std::vector<std::unique_ptr<Component::ImguiComponent>> myComponents;
        Math::MathGenerator myGenerator;

        void NewQuestion();
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_HOMEWORKWINDOW_H

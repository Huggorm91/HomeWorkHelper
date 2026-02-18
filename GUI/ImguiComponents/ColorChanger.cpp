#include "ColorChanger.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    ColorChanger::ColorChanger(int anImGuiColValue, int aColor) : myImGuiColValue(anImGuiColValue), myColor(aColor)
    {
    }

    void ColorChanger::UpdateContent()
    {
        assert(myChild && "Child is not set!");
        ImGui::PushStyleColor(myImGuiColValue, myColor);
        myChild->UpdateContent();
        ImGui::PopStyleColor();
    }

    void ColorChanger::SetChild(std::unique_ptr<ImguiComponent> aChild)
    {
        myChild = std::move(aChild);
    }
} // HomeworkHelper::Component
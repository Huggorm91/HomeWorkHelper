#include "ColorChanger.h"
#include "ImguiConversions.h"
#include <cassert>


namespace HomeworkHelper::Component
{
    ColorChanger::ColorChanger(const int anImGuiColValue, const Common::Vec4& aColor): myImGuiColValue(anImGuiColValue), myColor(aColor)
    {
    }

    void ColorChanger::UpdateContent()
    {
        assert(myChild && "Child is not set!");
        ImGui::PushStyleColor(myImGuiColValue, VecToImVec(myColor));
        myChild->UpdateContent();
        ImGui::PopStyleColor();
    }

    void ColorChanger::SetImGuiColValue(const int anImGuiColValue)
    {
        myImGuiColValue = anImGuiColValue;
    }

    void ColorChanger::SetColor(const Common::Vec4& aColor)
    {
        myColor = aColor;
    }

    void ColorChanger::SetChild(std::unique_ptr<ImguiComponent> aChild)
    {
        myChild = std::move(aChild);
    }
} // HomeworkHelper::Component
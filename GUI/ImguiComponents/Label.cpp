#include "Label.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    Label::Label(const std::string& aLabel) : myLabel(aLabel)
    {
    }

    void Label::UpdateContent()
    {
        ImGui::Text("%s", myLabel.c_str());
    }

    void Label::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    DynamicLabel::DynamicLabel(const std::function<std::string()>& aLabelCallback) : myCallback(aLabelCallback)
    {
    }

    void DynamicLabel::UpdateContent()
    {
        ImGui::Text("%s", myCallback().c_str());
    }

    void DynamicLabel::SetLabelCallback(const std::function<std::string()>& aLabelCallback)
    {
        myCallback = aLabelCallback;
    }
} // HomeworkHelper::Component

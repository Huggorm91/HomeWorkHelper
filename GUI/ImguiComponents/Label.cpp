#include "Label.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    Label::Label(const std::string& aLabel): myLabel(aLabel)
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
} // HomeworkHelper::Component
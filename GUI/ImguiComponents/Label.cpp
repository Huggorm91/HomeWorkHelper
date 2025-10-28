#include "Label.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    void Label::UpdateContent()
    {
        ImGui::Text("%s", myLabel.c_str());
    }
} // HomeworkHelper::Component
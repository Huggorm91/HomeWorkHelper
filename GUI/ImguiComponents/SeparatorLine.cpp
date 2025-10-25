#include "SeparatorLine.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    void SeparatorLine::UpdateContent()
    {
        ImGui::Separator();
    }
} // HomeworkHelper::Component
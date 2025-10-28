#include "SameLine.h"

#include "imgui.h"

namespace HomeworkHelper::Component
{
    SameLine::SameLine(): myOffsetFromStart(0.f), mySpacing(-1.f)
    {
    }

    void SameLine::UpdateContent()
    {
        ImGui::SameLine(myOffsetFromStart, mySpacing);
    }
} // HomeworkHelper::Component
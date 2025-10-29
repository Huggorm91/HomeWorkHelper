#include "SameLine.h"

#include "imgui.h"

namespace HomeworkHelper::Component
{
    SameLine::SameLine(): myOffsetFromStart(0.f), mySpacing(-1.f)
    {
    }

    SameLine::SameLine(float aOffsetFromStart, float aSpacing): myOffsetFromStart(aOffsetFromStart), mySpacing(aSpacing)
    {
    }

    void SameLine::UpdateContent()
    {
        ImGui::SameLine(myOffsetFromStart, mySpacing);
    }

    void SameLine::SetOffsetFromStart(float aOffsetFromStart)
    {
        myOffsetFromStart = aOffsetFromStart;
    }

    void SameLine::SetSpacing(float aSpacing)
    {
        mySpacing = aSpacing;
    }
} // HomeworkHelper::Component
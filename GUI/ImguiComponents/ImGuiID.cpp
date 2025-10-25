#include "ImGuiID.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    void ImGuiID::UpdateContent()
    {
        assert(myChild && "Child is not set!");
        ImGui::PushID(myID.c_str());
        myChild->UpdateContent();
        ImGui::PopID();
    }

    void ImGuiID::AddChild(std::unique_ptr<ImguiComponent>& aChild)
    {
        myChild = std::move(aChild);
    }
} // HomeworkHelper::Component

#include "CollapsableHeader.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    CollapsableHeader::CollapsableHeader() : myIsDefaultOpen(false)
    {
    }

    void CollapsableHeader::UpdateContent()
    {
        if (ImGui::CollapsingHeader(myLabel.c_str(), myIsDefaultOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None)) {
            for (auto& item: myItems) {
                item->UpdateContent();
            }
        }
    }

    void CollapsableHeader::AddChildNode(std::unique_ptr<ImguiComponent>& aChild)
    {
        myItems.emplace_back(std::move(aChild));
    }

    void CollapsableHeader::ClearChildren()
    {
        myItems.clear();
    }
} // HomeworkHelper::Component
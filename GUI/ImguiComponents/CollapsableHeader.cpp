#include "CollapsableHeader.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    CollapsableHeader::CollapsableHeader() : myIsDefaultOpen(false)
    {
    }

    CollapsableHeader::CollapsableHeader(const std::string& aLabel, bool aIsDefaultOpen) :
        myIsDefaultOpen(aIsDefaultOpen),
        myLabel(aLabel)
    {
    }

    void CollapsableHeader::UpdateContent()
    {
        if (ImGui::CollapsingHeader(
            myLabel.c_str(),
            myIsDefaultOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None
        )) {
            for (auto& item: myItems) {
                item->UpdateContent();
            }
        }
    }

    void CollapsableHeader::AddChildNode(std::unique_ptr<ImguiComponent> aChild)
    {
        myItems.emplace_back(std::move(aChild));
    }

    void CollapsableHeader::ClearChildren()
    {
        myItems.clear();
    }

    void CollapsableHeader::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }
} // HomeworkHelper::Component

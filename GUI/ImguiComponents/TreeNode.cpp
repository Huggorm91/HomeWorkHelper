#include "TreeNode.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    TreeNode::TreeNode(const std::string& aLabel) : myLabel(aLabel)
    {
    }

    void TreeNode::UpdateContent()
    {
        if (ImGui::TreeNode(myLabel.c_str())) {
            for (auto& item: myItems) {
                item->UpdateContent();
            }
            ImGui::TreePop();
        }
    }

    void TreeNode::AddChildNode(std::unique_ptr<ImguiComponent> aChild)
    {
        myItems.emplace_back(std::move(aChild));
    }

    void TreeNode::ClearChildren()
    {
        myItems.clear();
    }

    void TreeNode::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }
} // HomeworkHelper::Component

#include "MenuTab.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    MenuTab::MenuTab(const std::string& aLabel): myLabel(aLabel)
    {
    }

    void MenuTab::UpdateContent()
    {
        if (ImGui::BeginMenu(myLabel.c_str())) {
            for (auto& item: myItems) {
                item->UpdateContent();
            }
            ImGui::EndMenu();
        }
    }

    void MenuTab::AddChildNode(std::unique_ptr<ImguiComponent>& aChild)
    {
        myItems.emplace_back(std::move(aChild));
    }

    void MenuTab::ClearChildren()
    {
        myItems.clear();
    }

    void MenuTab::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }
} // HomeworkHelper::Component
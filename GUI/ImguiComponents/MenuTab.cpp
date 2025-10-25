#include "MenuTab.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    void MenuTab::UpdateContent()
    {
        if (ImGui::BeginMenu(myName.c_str())) {
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
} // HomeworkHelper::Component
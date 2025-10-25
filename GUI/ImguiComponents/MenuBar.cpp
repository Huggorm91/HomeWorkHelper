#include "MenuBar.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    void MenuBar::UpdateContent()
    {
        if (ImGui::BeginMenuBar()) {
            for (auto& item: myItems) {
                item->UpdateContent();
            }
            ImGui::EndMenuBar();
        }
    }

    void MenuBar::AddChildNode(std::unique_ptr<MenuTab>& aChild)
    {
        myItems.emplace_back(std::move(aChild));
    }
} // HomeworkHelper::Component

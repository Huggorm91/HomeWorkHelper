#include "ComboBox.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    ComboBox::ComboBox() : myPreviewString(nullptr)
    {
    }

    void ComboBox::UpdateContent()
    {
        if (ImGui::BeginCombo(myLabel.c_str(), myPreviewString ? myPreviewString->c_str() : ""))
        {
            for (auto& item : myItems)
            {
                item->UpdateContent();
            }
            ImGui::EndCombo();
        }
    }

    void ComboBox::AddChildNode(std::unique_ptr<ImguiComponent>& aChild)
    {
        myItems.emplace_back(std::move(aChild));
    }

    void ComboBox::ClearChildren()
    {
        myItems.clear();
    }
} // HomeworkHelper::Component
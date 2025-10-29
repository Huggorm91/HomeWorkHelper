#include "ComboBox.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    ComboBox::ComboBox() : myPreviewString(nullptr)
    {
    }

    ComboBox::ComboBox(const std::string& aLabel, std::string* aPreviewString) : myPreviewString(aPreviewString), myLabel(aLabel)
    {
    }

    void ComboBox::UpdateContent()
    {
        if (ImGui::BeginCombo(myLabel.c_str(), myPreviewString ? myPreviewString->c_str() : "")) {
            for (auto& item: myItems) {
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

    void ComboBox::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void ComboBox::SetPreviewString(std::string* aPreviewString)
    {
        myPreviewString = aPreviewString;
    }
} // HomeworkHelper::Component

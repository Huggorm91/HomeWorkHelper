#include "ComboItem.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    void ComboItem::UpdateContent()
    {
        const bool isSelected = myIsSelectedFunction(myLabel);

        if (ImGui::Selectable(myLabel.c_str(), isSelected)
            && myOnSelectedCallback) {
            myOnSelectedCallback();
        }

        if (isSelected) {
            ImGui::SetItemDefaultFocus();
        }
    }
} // HomeworkHelper::Component

#include "ComboItem.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    ComboItem::ComboItem(
        const std::string& aLabel,
        const std::function<bool(const std::string&)>& aIsSelectedFunction,
        const std::function<void(const std::string&)>& aOnSelectedCallback
    ) : myLabel(aLabel),
        myIsSelectedFunction(aIsSelectedFunction),
        myOnSelectedCallback(aOnSelectedCallback)
    {
    }

    void ComboItem::UpdateContent()
    {
        const bool isSelected = myIsSelectedFunction(myLabel);

        if (ImGui::Selectable(myLabel.c_str(), isSelected)
            && myOnSelectedCallback) {
            myOnSelectedCallback(myLabel);
        }

        if (isSelected) {
            ImGui::SetItemDefaultFocus();
        }
    }

    void ComboItem::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void ComboItem::SetIsSelectedFunction(const std::function<bool(const std::string&)>& aIsSelectedFunction)
    {
        myIsSelectedFunction = aIsSelectedFunction;
    }

    void ComboItem::SetOnSelectedCallback(const std::function<void(const std::string&)>& aOnSelectedCallback)
    {
        myOnSelectedCallback = aOnSelectedCallback;
    }
} // HomeworkHelper::Component

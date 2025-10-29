#ifndef HOMEWORKHELPER_COMBOITEM_H
#define HOMEWORKHELPER_COMBOITEM_H
#include <string>
#include <functional>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class ComboItem : public ImguiComponent
    {
    public:
        ComboItem() = default;
        ///
        /// @param aLabel The displayed name of the selectable item
        /// @param aIsSelectedFunction This function is used to determine if the item it selected or not, provides the label as a parameter
        /// @param aOnSelectedCallback This function is called when the item is selected, provides the label as a parameter
        explicit ComboItem(const std::string& aLabel, const std::function<bool(const std::string&)>& aIsSelectedFunction = nullptr, const std::function<void(const std::string&)>& aOnSelectedCallback = nullptr);
        ~ComboItem() override = default;

        void UpdateContent() override;

        void SetLabel(const std::string& aLabel);
        void SetIsSelectedFunction(const std::function<bool(const std::string&)>& aIsSelectedFunction);
        void SetOnSelectedCallback(const std::function<void(const std::string&)>& aOnSelectedCallback);

    private:
        std::string myLabel;
        std::function<bool(const std::string&)> myIsSelectedFunction;
        std::function<void(const std::string&)> myOnSelectedCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COMBOITEM_H
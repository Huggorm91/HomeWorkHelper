#ifndef HOMEWORKHELPER_COMBOBOX_H
#define HOMEWORKHELPER_COMBOBOX_H
#include <vector>
#include <memory>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class ComboBox : public ImguiComponent
    {
    public:
        ComboBox();
        ///
        /// @param aLabel The displayed label
        /// @param aPreviewString The string shown when the ComboBox is closed, displays an empty string if nullptr
        explicit ComboBox(const std::string& aLabel, std::string* aPreviewString = nullptr);
        ~ComboBox() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent>& aChild);
        void ClearChildren();

        void SetLabel(const std::string& aLabel);
        void SetPreviewString(std::string* aPreviewString);

    private:
        std::string* myPreviewString;
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COMBOBOX_H
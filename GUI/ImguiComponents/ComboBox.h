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
        ~ComboBox() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent>& aChild);
        void ClearChildren();

    private:
        std::string* myPreviewString;
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COMBOBOX_H
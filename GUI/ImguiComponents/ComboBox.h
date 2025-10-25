#ifndef HOMEWORKHELPER_COMBOBOX_H
#define HOMEWORKHELPER_COMBOBOX_H
#include <vector>
#include <memory>

#include "ComboItem.h"

namespace HomeworkHelper::Component
{
    class ComboBox : public ImguiComponent
    {
    public:
        ComboBox() = default;
        ~ComboBox() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ComboItem>& aChild);

    private:
        std::vector<std::unique_ptr<ComboItem>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COMBOBOX_H
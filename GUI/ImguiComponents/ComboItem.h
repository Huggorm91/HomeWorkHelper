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
        ~ComboItem() override = default;

        void UpdateContent() override;

    private:
        std::string myLabel;
        std::function<void()> myOnSelectedCallback;
        std::function<bool(std::string&)> myIsSelectedFunction;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COMBOITEM_H
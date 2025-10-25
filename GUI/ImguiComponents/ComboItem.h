#ifndef HOMEWORKHELPER_COMBOOPTION_H
#define HOMEWORKHELPER_COMBOOPTION_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class ComboItem : public ImguiComponent
    {
    public:
        ComboItem() = default;
        ~ComboItem() override = default;

        void UpdateContent() override;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COMBOOPTION_H
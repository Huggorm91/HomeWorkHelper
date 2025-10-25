#ifndef HOMEWORKHELPER_RADIOBUTTON_H
#define HOMEWORKHELPER_RADIOBUTTON_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class RadioButton : public ImguiComponent
    {
    public:
        RadioButton() = default;
        ~RadioButton() override = default;

        void UpdateContent() override;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_RADIOBUTTON_H
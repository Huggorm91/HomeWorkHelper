#ifndef HOMEWORKHELPER_RADIOBUTTON_H
#define HOMEWORKHELPER_RADIOBUTTON_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class RadioButton : public ImguiComponent
    {
    public:
        RadioButton();
        ~RadioButton() override = default;

        void UpdateContent() override;

    private:
        int myValue;
        int* myOutput;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_RADIOBUTTON_H
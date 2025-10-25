#ifndef HOMEWORKHELPER_CHECKBOX_H
#define HOMEWORKHELPER_CHECKBOX_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class Checkbox : public ImguiComponent
    {
    public:
        Checkbox();
        ~Checkbox() override = default;

        void UpdateContent() override;

    private:
        bool* myBool;
        std::string myName;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_CHECKBOX_H
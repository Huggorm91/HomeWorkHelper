#ifndef HOMEWORKHELPER_BUTTON_H
#define HOMEWORKHELPER_BUTTON_H
#include <functional>
#include <string>

#include "Common/Math/Vec2.h"
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class Button : public ImguiComponent
    {
    public:
        Button() = default;
        ~Button() override = default;

        void UpdateContent() override;

    private:
        Common::Vec2 mySize;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_BUTTON_H
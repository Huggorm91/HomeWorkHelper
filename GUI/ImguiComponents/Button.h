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
        ///
        /// @param aLabel The displayed label
        /// @param aSize The buttons size
        /// @param aCallback The function called when the button is clicked
        Button(const std::string& aLabel, const Common::Vec2& aSize, const std::function<void()>& aCallback);
        ~Button() override = default;

        void UpdateContent() override;

        void SetSize(const Common::Vec2& aSize);
        void SetLabel(const std::string& aLabel);
        void SetCallback(const std::function<void()>& aCallback);

    private:
        Common::Vec2 mySize;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_BUTTON_H
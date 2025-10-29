#ifndef HOMEWORKHELPER_MENUITEM_H
#define HOMEWORKHELPER_MENUITEM_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class MenuItem : public ImguiComponent
    {
    public:
        MenuItem() = default;
        ///
        /// @param aLabel The displayed name of the menu option
        /// @param aCallback The function called when the option is clicked
        MenuItem(const std::string& aLabel, const std::function<void()>& aCallback);
        ~MenuItem() override = default;

        void UpdateContent() override;

        void SetLabel(const std::string& aLabel);
        void SetCallback(const std::function<void()>& aCallback);

    private:
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_MENUITEM_H
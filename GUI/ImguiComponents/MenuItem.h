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
        ~MenuItem() override = default;

        void UpdateContent() override;

    private:
        std::string myName;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_MENUITEM_H
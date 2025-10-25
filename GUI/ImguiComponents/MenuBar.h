#ifndef HOMEWORKHELPER_MENU_H
#define HOMEWORKHELPER_MENU_H
#include "MenuTab.h"

namespace HomeworkHelper::Component
{
    class MenuBar : public ImguiComponent
    {
    public:
        MenuBar() = default;
        ~MenuBar() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<MenuTab>& aChild);

    private:
        std::vector<std::unique_ptr<MenuTab>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_MENU_H

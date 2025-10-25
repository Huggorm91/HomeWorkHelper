#ifndef HOMEWORKHELPER_MENUITEM_H
#define HOMEWORKHELPER_MENUITEM_H
#include <vector>
#include <memory>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class MenuTab : public ImguiComponent
    {
    public:
        MenuTab() = default;
        ~MenuTab() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent>& aChild);

    private:
        std::string myName;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_MENUITEM_H
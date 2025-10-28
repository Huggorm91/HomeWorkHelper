#ifndef HOMEWORKHELPER_MENUBAR_H
#define HOMEWORKHELPER_MENUBAR_H
#include <vector>
#include <memory>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class MenuBar : public ImguiComponent
    {
    public:
        MenuBar() = default;
        ~MenuBar() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent>& aChild);
        void ClearChildren();

    private:
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_MENUBAR_H

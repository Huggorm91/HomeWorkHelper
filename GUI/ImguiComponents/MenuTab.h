#ifndef HOMEWORKHELPER_MENUTAB_H
#define HOMEWORKHELPER_MENUTAB_H
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
        void ClearChildren();

    private:
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_MENUTAB_H
#ifndef HOMEWORKHELPER_COLLAPSABLEHEADER_H
#define HOMEWORKHELPER_COLLAPSABLEHEADER_H
#include <vector>
#include <memory>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class CollapsableHeader : public ImguiComponent
    {
    public:
        CollapsableHeader();
        ~CollapsableHeader() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent>& aChild);
        void ClearChildren();

    private:
        bool myIsDefaultOpen;
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COLLAPSABLEHEADER_H
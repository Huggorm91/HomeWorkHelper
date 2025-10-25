#ifndef HOMEWORKHELPER_COLLAPSABLEHEADER_H
#define HOMEWORKHELPER_COLLAPSABLEHEADER_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class CollapsableHeader : public ImguiComponent
    {
    public:
        CollapsableHeader();
        ~CollapsableHeader() override = default;

        void UpdateContent() override;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COLLAPSABLEHEADER_H
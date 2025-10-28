#ifndef HOMEWORKHELPER_SEPARATORLINE_H
#define HOMEWORKHELPER_SEPARATORLINE_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class SeparatorLine : public ImguiComponent
    {
    public:
        SeparatorLine() = default;
        ~SeparatorLine() override = default;

        void UpdateContent() override;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_SEPARATORLINE_H
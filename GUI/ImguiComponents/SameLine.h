#ifndef HOMEWORKHELPER_SAMELINE_H
#define HOMEWORKHELPER_SAMELINE_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class SameLine : public ImguiComponent
    {
    public:
        SameLine();
        ~SameLine() override = default;

        void UpdateContent() override;

    private:
        float myOffsetFromStart;
        float mySpacing;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_SAMELINE_H
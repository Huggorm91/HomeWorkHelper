#ifndef HOMEWORKHELPER_SAMELINE_H
#define HOMEWORKHELPER_SAMELINE_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class SameLine : public ImguiComponent
    {
    public:
        SameLine();
        ///
        /// @param aOffsetFromStart Sets absolute value from start of row, this is ignored if set to 0.f
        /// @param aSpacing The spacing from offset position
        explicit SameLine(float aOffsetFromStart, float aSpacing = -1.f);
        ~SameLine() override = default;

        void UpdateContent() override;

        void SetOffsetFromStart(float aOffsetFromStart);
        void SetSpacing(float aSpacing);

    private:
        float myOffsetFromStart;
        float mySpacing;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_SAMELINE_H
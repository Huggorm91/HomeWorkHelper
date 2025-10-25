#ifndef HOMEWORKHELPER_NUMBERFIELD_H
#define HOMEWORKHELPER_NUMBERFIELD_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class NumberField : public ImguiComponent
    {
    public:
        NumberField() = default;
        ~NumberField() override = default;

        void UpdateContent() override;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_NUMBERFIELD_H
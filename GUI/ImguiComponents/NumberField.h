#ifndef HOMEWORKHELPER_NUMBERFIELD_H
#define HOMEWORKHELPER_NUMBERFIELD_H
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class NumberField : public ImguiComponent
    {
    public:
        NumberField();
        ~NumberField() override = default;

        void UpdateContent() override;

    private:
        int* myOutput;
        std::string myLabel;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_NUMBERFIELD_H
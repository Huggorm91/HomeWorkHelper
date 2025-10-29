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
        ///
        /// @param aLabel The displayed label
        /// @param aOutput The output of the field
        NumberField(const std::string& aLabel, int* aOutput);
        ~NumberField() override = default;

        void UpdateContent() override;

        void SetOutput(int* aOutput);
        void SetLabel(const std::string& aLabel);

    private:
        int* myOutput;
        std::string myLabel;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_NUMBERFIELD_H
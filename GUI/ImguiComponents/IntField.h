#ifndef HOMEWORKHELPER_INTFIELD_H
#define HOMEWORKHELPER_INTFIELD_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class IntField : public ImguiComponent
    {
    public:
        IntField();
        ///
        /// @param aLabel The displayed label
        /// @param aOutput The output of the field
        /// @param aCallback This function is called when the value is changed
        IntField(std::string aLabel, int* aOutput, const std::function<void()>& aCallback = nullptr);
        ~IntField() override = default;

        void UpdateContent() override;

        void SetOutput(int* aOutput);
        void SetLabel(const std::string& aLabel);
        void SetCallback(const std::function<void()>& aCallback);

    private:
        int* myOutput;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_INTFIELD_H
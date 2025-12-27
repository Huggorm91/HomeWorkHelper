#ifndef HOMEWORKHELPER_FLOATFIELD_H
#define HOMEWORKHELPER_FLOATFIELD_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class FloatField : public ImguiComponent
    {
    public:
        FloatField();
        ///
        /// @param aLabel The displayed label
        /// @param aOutput The output of the field
        /// @param aCallback This function is called when the value is changed
        FloatField(std::string aLabel, float* aOutput, const std::function<void()>& aCallback = nullptr);
        ~FloatField() override = default;

        void UpdateContent() override;

        void SetOutput(float* aOutput);
        void SetLabel(const std::string& aLabel);
        void SetCallback(const std::function<void()>& aCallback);

    private:
        float* myOutput;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_FLOATFIELD_H

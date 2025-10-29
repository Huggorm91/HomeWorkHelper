#ifndef HOMEWORKHELPER_CHECKBOX_H
#define HOMEWORKHELPER_CHECKBOX_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class Checkbox : public ImguiComponent
    {
    public:
        Checkbox();
        ///
        /// @param aLabel The displayed label
        /// @param aOutput The output used by the checkbox, true if checked
        /// @param aCallback This function is called when the box is set as checked
        Checkbox(const std::string& aLabel, bool* aOutput, const std::function<void()>& aCallback = nullptr);
        ~Checkbox() override = default;

        void UpdateContent() override;

        void SetOutput(bool* aOutput);
        void SetLabel(const std::string& aLabel);
        void SetCallback(const std::function<void()>& aCallback);

    private:
        bool* myOutput;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_CHECKBOX_H
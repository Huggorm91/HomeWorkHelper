#ifndef HOMEWORKHELPER_RADIOBUTTON_H
#define HOMEWORKHELPER_RADIOBUTTON_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class RadioButton : public ImguiComponent
    {
    public:
        RadioButton();
        ///
        /// @param aLabel The displayed label
        /// @param aValue The value output will be set to if this button is selected
        /// @param aOutput The output of the radiobutton, this should be a shared resource for all buttons within the same group
        /// @param aCallback This function will be called when the button is set as selected
        RadioButton(const std::string& aLabel, int aValue, int* aOutput, const std::function<void()>& aCallback = nullptr);
        ~RadioButton() override = default;

        void UpdateContent() override;

        void SetValue(int aValue);
        void SetOutput(int* aOutput);
        void SetLabel(const std::string& aLabel);
        void SetCallback(const std::function<void()>& aCallback);

    private:
        int myValue;
        int* myOutput;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_RADIOBUTTON_H

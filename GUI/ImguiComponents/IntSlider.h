#ifndef HOMEWORKHELPER_INTSLIDER_H
#define HOMEWORKHELPER_INTSLIDER_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class IntSlider : public ImguiComponent
    {
    public:
        IntSlider();
        ///
        /// @param aLabel The displayed label
        /// @param aOutput The output used by the slider
        /// @param aMin The minimum value the slider can go to
        /// @param aMax The maximum value the slider can go to
        /// @param aCallback This function is called when the value is changed
        IntSlider(std::string aLabel, int* aOutput, int aMin, int aMax, const std::function<void()>& aCallback = nullptr);
        ~IntSlider() override = default;

        void UpdateContent() override;

        void SetMin(int aMin);
        void SetMax(int aMax);
        void SetOutput(int* aOutput);
        void SetLabel(const std::string& aLabel);
        void SetCallback(const std::function<void()>& aCallback);

    private:
        int myMin;
        int myMax;
        int* myOutput;
        std::string myLabel;
        std::function<void()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_INTSLIDER_H
#ifndef HOMEWORKHELPER_INTSLIDER_H
#define HOMEWORKHELPER_INTSLIDER_H
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
        IntSlider(const std::string& aLabel, int* aOutput, int aMin, int aMax);
        ~IntSlider() override = default;

        void UpdateContent() override;

        void SetMin(int aMin);
        void SetMax(int aMax);
        void SetOutput(int* aOutput);
        void SetLabel(const std::string& aLabel);

    private:
        int myMin;
        int myMax;
        int* myOutput;
        std::string myLabel;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_INTSLIDER_H
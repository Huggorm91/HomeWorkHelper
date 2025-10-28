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
        ~IntSlider() override = default;

        void UpdateContent() override;

    private:
        int myMin;
        int myMax;
        int* myOutput;
        std::string myLabel;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_INTSLIDER_H
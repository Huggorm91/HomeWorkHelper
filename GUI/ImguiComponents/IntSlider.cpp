#include "IntSlider.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    IntSlider::IntSlider() : myMin(0),
                             myMax(0),
                             myOutput(nullptr)
    {
    }

    void IntSlider::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        ImGui::SliderInt(myLabel.c_str(), myOutput, myMin, myMax);
    }
} // HomeworkHelper::Component
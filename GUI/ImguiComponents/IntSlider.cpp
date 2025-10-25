#include "IntSlider.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    IntSlider::IntSlider() : myMin(0),
                             myMax(0),
                             myInt(nullptr)
    {
    }

    void IntSlider::UpdateContent()
    {
        assert(myInt && "Output is not set!");
        ImGui::SliderInt(myName.c_str(), myInt, myMin, myMax);
    }
} // HomeworkHelper::Component
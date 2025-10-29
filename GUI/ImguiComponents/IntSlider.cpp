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

    IntSlider::IntSlider(const std::string& aLabel, int* aOutput, int aMin, int aMax) :
        myMin(aMin),
        myMax(aMax),
        myOutput(aOutput),
        myLabel(aLabel)
    {
    }

    void IntSlider::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        ImGui::SliderInt(myLabel.c_str(), myOutput, myMin, myMax);
    }

    void IntSlider::SetMin(int aMin)
    {
        myMin = aMin;
    }

    void IntSlider::SetMax(int aMax)
    {
        myMax = aMax;
    }

    void IntSlider::SetOutput(int* aOutput)
    {
        myOutput = aOutput;
    }

    void IntSlider::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }
} // HomeworkHelper::Component

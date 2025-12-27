#include "IntSlider.h"
#include "imgui.h"
#include <cassert>
#include <utility>

namespace HomeworkHelper::Component
{
    IntSlider::IntSlider() : myMin(0),
                             myMax(0),
                             myOutput(nullptr)
    {
    }

    IntSlider::IntSlider(std::string aLabel, int* aOutput, int aMin, int aMax, const std::function<void()>& aCallback) :
        myMin(aMin),
        myMax(aMax),
        myOutput(aOutput),
        myLabel(std::move(aLabel)),
        myCallback(aCallback)
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

    void IntSlider::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component

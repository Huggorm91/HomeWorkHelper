#include "FloatField.h"

#include <utility>
#include "imgui.h"

namespace HomeworkHelper::Component
{
    FloatField::FloatField() : myOutput(nullptr)
    {
    }

    FloatField::FloatField(std::string aLabel, float* aOutput, const std::function<void()>& aCallback) :
        myOutput(aOutput),
        myLabel(std::move(aLabel)),
        myCallback(aCallback)
    {
    }

    void FloatField::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        if (ImGui::InputFloat(myLabel.c_str(), myOutput)) {
            myCallback();
        }
    }

    void FloatField::SetOutput(float* aOutput)
    {
        myOutput = aOutput;
    }

    void FloatField::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void FloatField::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component

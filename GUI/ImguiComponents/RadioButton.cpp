#include "RadioButton.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    RadioButton::RadioButton() : myValue(0),
                                 myOutput(nullptr)
    {
    }

    RadioButton::RadioButton(
        const std::string& aLabel,
        int aValue,
        int* aOutput,
        const std::function<void()>& aCallback
    ) : myValue(aValue),
        myOutput(aOutput),
        myLabel(aLabel),
        myCallback(aCallback)
    {
    }

    void RadioButton::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        if (ImGui::RadioButton(myLabel.c_str(), myOutput, myValue)
            && myCallback) {
            myCallback();
        }
    }

    void RadioButton::SetValue(int aValue)
    {
        myValue = aValue;
    }

    void RadioButton::SetOutput(int* aOutput)
    {
        myOutput = aOutput;
    }

    void RadioButton::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void RadioButton::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component

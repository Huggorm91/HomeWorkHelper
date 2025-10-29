#include "Checkbox.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    Checkbox::Checkbox() : myOutput(nullptr)
    {
    }

    Checkbox::Checkbox(const std::string& aLabel, bool* aOutput, const std::function<void()>& aCallback) :
        myOutput(aOutput),
        myLabel(aLabel),
        myCallback(aCallback)
    {
    }

    void Checkbox::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        if (ImGui::Checkbox(myLabel.c_str(), myOutput)
            && myCallback) {
            myCallback();
        }
    }

    void Checkbox::SetOutput(bool* aOutput)
    {
        myOutput = aOutput;
    }

    void Checkbox::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void Checkbox::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component

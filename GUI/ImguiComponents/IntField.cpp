#include "IntField.h"

#include <utility>
#include "imgui.h"

namespace HomeworkHelper::Component
{
    IntField::IntField() : myOutput(nullptr)
    {
    }

    IntField::IntField(std::string aLabel, int* aOutput, const std::function<void()>& aCallback) :
        myOutput(aOutput),
        myLabel(std::move(aLabel)),
        myCallback(aCallback)
    {
    }

    void IntField::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        if (ImGui::InputInt(myLabel.c_str(), myOutput)) {
            myCallback();
        }
    }

    void IntField::SetOutput(int* aOutput)
    {
        myOutput = aOutput;
    }

    void IntField::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void IntField::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component

#include "NumberField.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    NumberField::NumberField() : myOutput(nullptr)
    {
    }

    NumberField::NumberField(const std::string& aLabel, int* aOutput) :
        myOutput(aOutput),
        myLabel(aLabel)
    {
    }

    void NumberField::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        ImGui::InputInt(myLabel.c_str(), myOutput);
    }

    void NumberField::SetOutput(int* aOutput)
    {
        myOutput = aOutput;
    }

    void NumberField::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }
} // HomeworkHelper::Component

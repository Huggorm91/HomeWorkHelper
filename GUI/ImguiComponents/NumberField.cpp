#include "NumberField.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    NumberField::NumberField() : myOutput(nullptr)
    {
    }

    void NumberField::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        ImGui::InputInt(myLabel.c_str(), myOutput);
    }
} // HomeworkHelper::Component
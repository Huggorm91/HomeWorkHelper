#include "Textfield.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    Textfield::Textfield(): myOutput(nullptr)
    {
    }

    Textfield::Textfield(const std::string& aLabel, std::string* aOutput): myOutput(aOutput), myLabel(aLabel)
    {
    }

    void Textfield::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        ImGui::InputText(myLabel.c_str(), myOutput, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
    }

    void Textfield::SetOutput(std::string* aOutput)
    {
        myOutput = aOutput;
    }

    void Textfield::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }
} // HomeworkHelper::Component
#include "Textfield.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    Textfield::Textfield(): myOutput(nullptr)
    {
    }

    void Textfield::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        ImGui::InputText(myLabel.c_str(), myOutput, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
    }
} // HomeworkHelper::Component
#include "Textfield.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    Textfield::Textfield(): myText(nullptr)
    {
    }

    void Textfield::UpdateContent()
    {
        assert(myText && "Output is not set!");
        ImGui::InputText(myName.c_str(), myText, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
    }
} // HomeworkHelper::Component
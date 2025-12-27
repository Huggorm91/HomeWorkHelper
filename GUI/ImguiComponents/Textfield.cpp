#include "Textfield.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include <cassert>
#include <utility>

namespace HomeworkHelper::Component
{
    Textfield::Textfield() : myOutput(nullptr)
    {
    }

    Textfield::Textfield(std::string aLabel, std::string* aOutput, const std::function<void()>& aCallback) :
        myOutput(aOutput),
        myLabel(std::move(aLabel)),
        myCallback(aCallback)
    {
    }

    void Textfield::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        if (ImGui::InputText(
            myLabel.c_str(),
            myOutput,
            ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue
        )) {
            myCallback();
        }
    }

    void Textfield::SetOutput(std::string* aOutput)
    {
        myOutput = aOutput;
    }

    void Textfield::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void Textfield::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component

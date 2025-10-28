#include "Checkbox.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    Checkbox::Checkbox() : myOutput(nullptr)
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
} // HomeworkHelper::Component

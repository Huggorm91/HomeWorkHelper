#include "Checkbox.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    Checkbox::Checkbox() : myBool(nullptr)
    {
    }

    void Checkbox::UpdateContent()
    {
        assert(myBool && "Output is not set!");
        if (ImGui::Checkbox(myName.c_str(), myBool)
            && myCallback) {
            myCallback();
        }
    }
} // HomeworkHelper::Component

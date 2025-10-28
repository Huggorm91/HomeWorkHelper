#include "Button.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    void Button::UpdateContent()
    {
        if (ImGui::Button(myLabel.c_str(), ImVec2(mySize.x, mySize.y))) {
            assert(myCallback && "Callback is not set!");
            myCallback();
        }
    }
} // HomeworkHelper::Component
#include "RadioButton.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    RadioButton::RadioButton() : myValue(0),
                                 myOutput(nullptr)
    {
    }

    void RadioButton::UpdateContent()
    {
        assert(myOutput && "Output is not set!");
        if (ImGui::RadioButton(myLabel.c_str(), myOutput, myValue)
            && myCallback) {
            myCallback();
            }
    }
} // HomeworkHelper::Component
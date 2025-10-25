#include "MenuItem.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    void MenuItem::UpdateContent()
    {
        if (ImGui::MenuItem(myName.c_str()))
        {
            assert(myCallback && "Callback is not set!");
            myCallback();
        }
    }
} // HomeworkHelper::Component
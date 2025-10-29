#include "MenuItem.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    MenuItem::MenuItem(const std::string& aLabel, const std::function<void()>& aCallback): myLabel(aLabel), myCallback(aCallback)
    {
    }

    void MenuItem::UpdateContent()
    {
        if (ImGui::MenuItem(myLabel.c_str()))
        {
            assert(myCallback && "Callback is not set!");
            myCallback();
        }
    }

    void MenuItem::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void MenuItem::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component
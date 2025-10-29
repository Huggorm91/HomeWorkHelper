#include "Button.h"
#include "imgui.h"
#include <cassert>

namespace HomeworkHelper::Component
{
    Button::Button(
        const std::string& aLabel,
        const Common::Vec2& aSize,
        const std::function<void()>& aCallback
    ) : mySize(aSize),
        myLabel(aLabel),
        myCallback(aCallback)
    {
    }

    void Button::UpdateContent()
    {
        if (ImGui::Button(myLabel.c_str(), ImVec2(mySize.x, mySize.y))) {
            assert(myCallback && "Callback is not set!");
            myCallback();
        }
    }

    void Button::SetSize(const Common::Vec2& aSize)
    {
        mySize = aSize;
    }

    void Button::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }

    void Button::SetCallback(const std::function<void()>& aCallback)
    {
        myCallback = aCallback;
    }
} // HomeworkHelper::Component

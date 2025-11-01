#include "Window.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    Window::Window(const std::string& aLabel, bool* aIsOpen): myIsOpen(aIsOpen), myLabel(aLabel)
    {
    }

    void Window::UpdateContent()
    {
        ImGui::Begin(myLabel.c_str(), myIsOpen);
        for (auto& item: myItems) {
            item->UpdateContent();
        }
        ImGui::End();
    }

    void Window::AddChildNode(std::unique_ptr<ImguiComponent>& aChild)
    {
        myItems.emplace_back(std::move(aChild));
    }

    void Window::ClearChildren()
    {
        myItems.clear();
    }

    void Window::SetIsOpen(bool* aIsOpen)
    {
        myIsOpen = aIsOpen;
    }

    void Window::SetLabel(const std::string& aLabel)
    {
        myLabel = aLabel;
    }
} // HomeworkHelper::Component
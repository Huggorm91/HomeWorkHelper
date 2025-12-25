#include "Window.h"
#include "imgui.h"

namespace HomeworkHelper::Component
{
    Window::Window(const std::string& aLabel, bool* aIsOpen, Common::Vec2 aSize, Common::Vec2 aPosition) :
        myIsOpen(aIsOpen),
        mySize(aSize),
        myPosition(aPosition),
        myLabel(aLabel)
    {
    }

    void Window::UpdateContent()
    {
        ImGui::SetNextWindowPos(ImVec2(myPosition.x, myPosition.y));
        ImVec2 size = {mySize.x, mySize.y};
        if (mySize.x == 0.f || mySize.y == 0.f) {
            ImVec2 fullSize;
#ifdef IMGUI_HAS_VIEWPORT
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowViewport(viewport->ID);
            fullSize = viewport->WorkSize;
#else
            fullSize = ImGui::GetIO().DisplaySize;
#endif
            if (mySize.x == 0.f) {
                size.x = fullSize.x;
            }
            if (mySize.y == 0.f) {
                size.y = fullSize.y;
            }
        }
        ImGui::SetNextWindowSize(size);

        // Only render window if myIsOpen is nullptr or true
        if (myIsOpen == nullptr || *myIsOpen) {
            ImGui::Begin(myLabel.c_str(), myIsOpen);
            for (auto& item: myItems) {
                item->UpdateContent();
            }
            ImGui::End();
        }
    }

    void Window::AddChildNode(std::unique_ptr<ImguiComponent> aChild)
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

    void Window::SetSize(Common::Vec2 aSize)
    {
        mySize = aSize;
    }

    void Window::SetPosition(Common::Vec2 aPosition)
    {
        myPosition = aPosition;
    }
} // HomeworkHelper::Component

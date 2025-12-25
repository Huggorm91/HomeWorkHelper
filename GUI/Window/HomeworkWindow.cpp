#include "HomeworkWindow.h"

#include <format>

#include "GUI/GUIIncludes.h"

#include "GUI/ImguiComponents/Window.h"
#include "GUI/ImguiComponents/Label.h"
#include "GUI/ImguiComponents/Checkbox.h"
#include "GUI/ImguiComponents/IntSlider.h"
#include "GUI/ImguiComponents/Button.h"
#include "GUI/ImguiComponents/SameLine.h"

namespace HomeworkHelper
{
    void HomeworkWindow::GenerateImguiContent()
    {
        // Temporary content to test the system
        auto& baseWindow = myComponents.emplace_back(std::make_unique<Component::Window>("Hello, world!"));
        auto& window = dynamic_cast<Component::Window&>(*baseWindow);

        window.AddChildNode(std::make_unique<Component::Label>("This is some useful text."));

        window.AddChildNode(std::make_unique<Component::Checkbox>("Another Window", &show_another_window));

        window.AddChildNode(std::make_unique<Component::IntSlider>("integer", &slider, 0, 100));

        window.AddChildNode(std::make_unique<Component::Button>("Button", Common::Vec2(), [this]{counter++;}));
        window.AddChildNode(std::make_unique<Component::SameLine>());
        window.AddChildNode(std::make_unique<Component::DynamicLabel>([this]{return std::format("counter = {}", counter);}));

        window.AddChildNode(std::make_unique<Component::DynamicLabel>([]{return std::format("Application average {} ms/frame ({} FPS)",
            1000.0f / ImGui::GetIO().Framerate,
            ImGui::GetIO().Framerate);}));

        auto& baseAnotherWindow = myComponents.emplace_back(std::make_unique<Component::Window>("Another Window", &show_another_window, Common::Vec2{250.f, 100.f}));
        auto& anotherWindow = dynamic_cast<Component::Window&>(*baseAnotherWindow);
        anotherWindow.AddChildNode(std::make_unique<Component::Label>("Hello from another window!"));
        anotherWindow.AddChildNode(std::make_unique<Component::Button>("Close Me", Common::Vec2(), [this]{show_another_window = false;}));
    }

    void HomeworkWindow::UpdateImguiContent()
    {
        for (const auto& component: myComponents) {
            component->UpdateContent();
        }
    }

    void HomeworkWindow::SetWindowData(ImGui_ImplVulkanH_Window* someWindowData)
    {
        myWindowData = someWindowData;
    }
} // HomeworkHelper

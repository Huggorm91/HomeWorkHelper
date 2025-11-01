#ifndef HOMEWORKHELPER_WINDOW_H
#define HOMEWORKHELPER_WINDOW_H
#include <vector>
#include <memory>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class Window : public ImguiComponent
    {
    public:
        Window() = default;
        ///
        /// @param aLabel The titlebar of the window
        /// @param aIsOpen Minimized if false, always open if nullptr
        explicit Window(const std::string& aLabel, bool* aIsOpen = nullptr);
        ~Window() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent>& aChild);
        void ClearChildren();

        void SetIsOpen(bool* aIsOpen);
        void SetLabel(const std::string& aLabel);

    private:
        bool* myIsOpen;
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_WINDOW_H
#ifndef HOMEWORKHELPER_WINDOW_H
#define HOMEWORKHELPER_WINDOW_H
#include <vector>
#include <memory>

#include "ImguiComponent.h"
#include "Common/Math/Vec2.h"

namespace HomeworkHelper::Component
{
    class Window : public ImguiComponent
    {
    public:
        Window() = default;
        ///
        /// @param aLabel The titlebar of the window
        /// @param aIsOpen Not rendered if false, always shown if nullptr
        /// @param aSize The size of the window, a zero value will fill the workspace in that dimension
        /// @param aPosition The position of the top-left corner of the window, 0, 0 is the top left of the workspace
        explicit Window(const std::string& aLabel, bool* aIsOpen = nullptr, Common::Vec2 aSize = { 0,0 }, Common::Vec2 aPosition = { 0,0 } );
        ~Window() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent> aChild);
        void ClearChildren();

        void SetIsOpen(bool* aIsOpen);
        void SetLabel(const std::string& aLabel);
        void SetSize(Common::Vec2 aSize);
        void SetPosition(Common::Vec2 aPosition);

    private:
        bool* myIsOpen;
        Common::Vec2 mySize;
        Common::Vec2 myPosition;
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_WINDOW_H
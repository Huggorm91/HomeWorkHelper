#ifndef HOMEWORKHELPER_COMPONENTWINDOW_H
#define HOMEWORKHELPER_COMPONENTWINDOW_H
#include <bitset>
#include <vector>
#include <memory>

#include "ImguiComponent.h"
#include "Common/Math/Vec2.h"

namespace HomeworkHelper::Component
{
    struct WindowFlags
    {
        enum
        {
            None = 0,
            SetPositionFirstTime = 1 << 1,
            SetPositionEveryStart = 1 << 2,
            SetSizeFirstTime = 1 << 3,
            SetSizeEveryStart = 1 << 4,
            RemoveTopBar = 1 << 5,
            DisableResize = 1 << 6
        };
    };

    class Window : public ImguiComponent
    {
    public:
        Window();
        ///
        /// @param aLabel The titlebar of the window
        /// @param aIsOpen Not rendered if false, always shown if nullptr
        /// @param aSize The size of the window, a zero value will fill the workspace in that dimension
        /// @param aPosition The position of the top-left corner of the window, 0, 0 is the top left of the workspace
        /// @param someFlags Flags that define the behaviour and look of the window
        explicit Window(std::string aLabel, bool* aIsOpen = nullptr, Common::Vec2 aSize = { 0,0 }, Common::Vec2 aPosition = { 0,0 } , int someFlags = WindowFlags::None);
        ~Window() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent> aChild);
        void ClearChildren();

        void SetIsOpen(bool* aIsOpen);
        void SetLabel(const std::string& aLabel);
        void SetSize(Common::Vec2 aSize);
        void SetPosition(Common::Vec2 aPosition);

    private:
        int myFlags;
        bool* myIsOpen;
        Common::Vec2 mySize;
        Common::Vec2 myPosition;
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COMPONENTWINDOW_H
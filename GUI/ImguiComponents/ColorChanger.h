#ifndef HOMEWORKHELPER_COLORCHANGER_H
#define HOMEWORKHELPER_COLORCHANGER_H
#include <memory>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class ColorChanger : public ImguiComponent
    {
    public:
        ColorChanger() = default;
        ///
        /// @param aId The ID that is going to wrap the child
        explicit ColorChanger(int anImGuiColValue, int aColor);
        ~ImGuiID() override = default;

        void UpdateContent() override;

		void SetImGuiColValue(int anImGuiColValue);
        void SetColor(int aColor);
        void SetChild(std::unique_ptr<ImguiComponent> aChild);

    private:
        int myImGuiColValue;  // TODO: Change to the correct format
		int myColor; // TODO: Change to the correct format
        std::unique_ptr<ImguiComponent> myChild;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COLORCHANGER_H
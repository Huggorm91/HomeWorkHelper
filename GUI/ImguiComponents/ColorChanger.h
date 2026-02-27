#ifndef HOMEWORKHELPER_COLORCHANGER_H
#define HOMEWORKHELPER_COLORCHANGER_H
#include <memory>
#include "Common/Math/Vec4.h"

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class ColorChanger : public ImguiComponent
    {
    public:
        ColorChanger() = default;
        ///
        /// @param anImGuiColValue The Imgui Color index that should be changed
        /// @param aColor The color that will be applied
        ColorChanger(int anImGuiColValue, const Common::Vec4& aColor);
        ~ColorChanger() override = default;

        void UpdateContent() override;

		void SetImGuiColValue(int anImGuiColValue);
        void SetColor(const Common::Vec4& aColor);
        void SetChild(std::unique_ptr<ImguiComponent> aChild);

    private:
        int myImGuiColValue = -1;
		Common::Vec4 myColor;
        std::unique_ptr<ImguiComponent> myChild;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COLORCHANGER_H
#ifndef HOMEWORKHELPER_LABEL_H
#define HOMEWORKHELPER_LABEL_H
#include <functional>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class Label : public ImguiComponent
    {
    public:
        Label() = default;
        explicit Label(const std::string& aLabel);
        ~Label() override = default;

        void UpdateContent() override;

        void SetLabel(const std::string& aLabel);

    private:
        std::string myLabel;
    };

    class DynamicLabel : public ImguiComponent
    {
    public:
        DynamicLabel() = default;
        ///
        /// @param aLabelCallback This will be called every frame to generate the shown label
        explicit DynamicLabel(const std::function<std::string()>& aLabelCallback);
        ~DynamicLabel() override = default;

        void UpdateContent() override;

        void SetLabelCallback(const std::function<std::string()>& aLabelCallback);

    private:
        std::function<std::string()> myCallback;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_LABEL_H

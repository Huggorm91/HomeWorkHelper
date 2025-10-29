#ifndef HOMEWORKHELPER_LABEL_H
#define HOMEWORKHELPER_LABEL_H
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
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_LABEL_H

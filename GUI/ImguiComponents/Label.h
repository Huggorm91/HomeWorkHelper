#ifndef HOMEWORKHELPER_LABEL_H
#define HOMEWORKHELPER_LABEL_H
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class Label: public ImguiComponent
    {
    public:
        Label() = default;
        ~Label() override = default;

        void UpdateContent() override;

    private:
        std::string myLabel;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_LABEL_H
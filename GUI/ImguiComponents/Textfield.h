#ifndef HOMEWORKHELPER_TEXTFIELD_H
#define HOMEWORKHELPER_TEXTFIELD_H
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class Textfield : public ImguiComponent
    {
    public:
        Textfield();
        ~Textfield() override = default;

        void UpdateContent() override;

    private:
        std::string* myText;
        std::string myName;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_TEXTFIELD_H
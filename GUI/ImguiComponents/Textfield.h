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
        ///
        /// @param aLabel The displayed label
        /// @param aOutput The output of the field
        Textfield(const std::string& aLabel, std::string* aOutput);
        ~Textfield() override = default;

        void UpdateContent() override;

        void SetOutput(std::string* aOutput);
        void SetLabel(const std::string& aLabel);

    private:
        std::string* myOutput;
        std::string myLabel;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_TEXTFIELD_H

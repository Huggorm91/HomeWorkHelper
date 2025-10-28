#ifndef HOMEWORKHELPER_IMGUIID_H
#define HOMEWORKHELPER_IMGUIID_H
#include <memory>
#include <string>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class ImGuiID : public ImguiComponent
    {
    public:
        ImGuiID() = default;
        ~ImGuiID() override = default;

        void UpdateContent() override;

        void AddChild(std::unique_ptr<ImguiComponent>& aChild);
    private:
        std::string myID;
        std::unique_ptr<ImguiComponent> myChild;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_IMGUIID_H
#ifndef HOMEWORKHELPER_IMGUICOMPONENT_H
#define HOMEWORKHELPER_IMGUICOMPONENT_H
#include <memory>

namespace HomeworkHelper
{
    // Base class for building an application window using Imgui
    class ImguiComponent
    {
    public:
        ImguiComponent() = default;
        virtual ~ImguiComponent() = default;

        // This should include the necessary imgui code and call any potential child UpdateContent
        virtual void UpdateContent() = 0;

        virtual void AddChildNode(const std::shared_ptr<ImguiComponent>& aChild) = 0;

    protected:
        // No variable dedicated to potential children, these have to be stored in the derived class
    };
}

#endif //HOMEWORKHELPER_IMGUICOMPONENT_H
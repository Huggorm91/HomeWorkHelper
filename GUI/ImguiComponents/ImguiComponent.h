#ifndef HOMEWORKHELPER_IMGUICOMPONENT_H
#define HOMEWORKHELPER_IMGUICOMPONENT_H

namespace HomeworkHelper::Component
{
    // Base class for building an application window using Imgui
    class ImguiComponent
    {
    public:
        ImguiComponent() = default;
        virtual ~ImguiComponent() = default;

        // This should include the necessary imgui code and call any potential child UpdateContent
        virtual void UpdateContent() = 0;
    };
}

#endif //HOMEWORKHELPER_IMGUICOMPONENT_H

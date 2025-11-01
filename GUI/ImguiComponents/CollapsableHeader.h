#ifndef HOMEWORKHELPER_COLLAPSABLEHEADER_H
#define HOMEWORKHELPER_COLLAPSABLEHEADER_H
#include <vector>
#include <memory>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class CollapsableHeader : public ImguiComponent
    {
    public:
        CollapsableHeader();
        ///
        /// @param aLabel The displayed name of the header
        /// @param aIsDefaultOpen Will determine if the header is expanded or not when loaded
        explicit CollapsableHeader(const std::string& aLabel, bool aIsDefaultOpen = false);
        ~CollapsableHeader() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent> aChild);
        void ClearChildren();

        void SetLabel(const std::string& aLabel);

    private:
        bool myIsDefaultOpen;
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_COLLAPSABLEHEADER_H
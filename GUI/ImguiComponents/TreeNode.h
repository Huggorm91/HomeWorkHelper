#ifndef HOMEWORKHELPER_TREENODE_H
#define HOMEWORKHELPER_TREENODE_H
#include <memory>
#include <string>
#include <vector>

#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class TreeNode : public ImguiComponent
    {
    public:
        TreeNode() = default;
        ///
        /// @param aLabel The displayed name of the node
        explicit TreeNode(const std::string& aLabel);
        ~TreeNode() override = default;

        void UpdateContent() override;

        void AddChildNode(std::unique_ptr<ImguiComponent> aChild);
        void ClearChildren();

        void SetLabel(const std::string& aLabel);

    private:
        std::string myLabel;
        std::vector<std::unique_ptr<ImguiComponent>> myItems;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_TREENODE_H
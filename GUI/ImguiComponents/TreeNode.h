#ifndef HOMEWORKHELPER_TREENODE_H
#define HOMEWORKHELPER_TREENODE_H
#include "ImguiComponent.h"

namespace HomeworkHelper::Component
{
    class TreeNode : public ImguiComponent
    {
    public:
        TreeNode();
        ~TreeNode() override = default;

        void UpdateContent() override;
    };
} // HomeworkHelper::Component

#endif //HOMEWORKHELPER_TREENODE_H
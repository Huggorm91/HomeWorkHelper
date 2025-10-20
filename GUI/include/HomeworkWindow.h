#ifndef HOMEWORKHELPER_HOMEWORKWINDOW_H
#define HOMEWORKHELPER_HOMEWORKWINDOW_H

namespace HomeworkHelper
{
    class HomeworkWindow
    {
        public:
        HomeworkWindow() = default;
        ~HomeworkWindow() = default;

        void CreateImguiContent();

        private:
        bool show_another_window = false;
    };
} // HomeworkHelper

#endif //HOMEWORKHELPER_HOMEWORKWINDOW_H
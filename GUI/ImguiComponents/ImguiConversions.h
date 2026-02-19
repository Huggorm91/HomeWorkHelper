#ifndef HOMEWORKHELPER_IMGUICONVERSIONS_H
#define HOMEWORKHELPER_IMGUICONVERSIONS_H
#include "imgui.h"
#include "Common/Math/Vec2.h"
#include "Common/Math/Vec4.h"

namespace HomeworkHelper
{
    inline ImVec2 VecToImVec(const Common::Vec2& aVec)
    {
        return {aVec.x, aVec.y};
    }

    inline ImVec4 VecToImVec(const Common::Vec4& aVec)
    {
        return {aVec.x, aVec.y, aVec.z, aVec.w};
    }
} // HomeworkHelper
#endif //HOMEWORKHELPER_IMGUICONVERSIONS_H
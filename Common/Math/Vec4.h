#ifndef HOMEWORKHELPER_VEC4_H
#define HOMEWORKHELPER_VEC4_H

namespace Common
{
    class Vec4
    {
    public:
        float x = 0.f, y = 0.f, z = 0.f, w = 0.f;

        Vec4() = default;
        Vec4(float aX, float aY, float aZ, float aW);
        ~Vec4() = default;
    };
} // Common

#endif //HOMEWORKHELPER_VEC4_H
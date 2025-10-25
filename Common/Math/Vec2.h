#ifndef HOMEWORKHELPER_VEC2_H
#define HOMEWORKHELPER_VEC2_H

namespace Common
{
    class Vec2
    {
        public:
        float x = 0.f, y = 0.f;

        Vec2() = default;
        Vec2(float aX, float aY);
        ~Vec2() = default;
    };
} // Common

#endif //HOMEWORKHELPER_VEC2_H
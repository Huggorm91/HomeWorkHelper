#ifndef HOMEWORKHELPER_VEC2_H
#define HOMEWORKHELPER_VEC2_H

namespace Common
{
    class Vec2
    {
        public:
        int x, y;

        Vec2() = default;
        Vec2(int aX, int aY);
        ~Vec2() = default;
    };
} // Common

#endif //HOMEWORKHELPER_VEC2_H
#ifndef HOMEWORKHELPER_SUBTRACT_H
#define HOMEWORKHELPER_SUBTRACT_H
#include "SolverBase.h"

namespace Math
{
    class Subtract : public SolverBase
    {
    public:
        Subtract() = default;
        Subtract(int aFirst, int aSecond);
        Subtract(float aFirst, float aSecond);
        ~Subtract() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;
    };
} // Math

#endif //HOMEWORKHELPER_SUBTRACT_H
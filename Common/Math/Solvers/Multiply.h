#ifndef HOMEWORKHELPER_MULTIPLY_H
#define HOMEWORKHELPER_MULTIPLY_H
#include "SolverBase.h"

namespace Math
{
    class Multiply : public SolverBase
    {
    public:
        Multiply() = default;
        Multiply(int aFirst, int aSecond);
        Multiply(float aFirst, float aSecond);
        ~Multiply() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;
    };
} // Math

#endif //HOMEWORKHELPER_MULTIPLY_H
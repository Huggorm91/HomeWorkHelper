#ifndef HOMEWORKHELPER_MULTIPLY_H
#define HOMEWORKHELPER_MULTIPLY_H
#include "SolverBase.h"

namespace Math
{
    class Multiply : public SolverBase
    {
    public:
        Multiply(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats);
        ~Multiply() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;

        char GetSymbol() const override;
    };
} // Math

#endif //HOMEWORKHELPER_MULTIPLY_H
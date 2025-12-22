#ifndef HOMEWORKHELPER_SUBTRACT_H
#define HOMEWORKHELPER_SUBTRACT_H
#include "SolverBase.h"

namespace Math
{
    class Subtract : public SolverBase
    {
    public:
        Subtract(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats);
        ~Subtract() override = default;

        int GetAnswerInt() const override;
        float GetAnswerFloat() const override;

        char GetSymbol() const override;
    };
} // Math

#endif //HOMEWORKHELPER_SUBTRACT_H
#include "Multiply.h"
#include <cmath>

namespace Math
{
    Multiply::Multiply(int aFirst, int aSecond): SolverBase(aFirst, aSecond)
    {
    }

    Multiply::Multiply(float aFirst, float aSecond): SolverBase(aFirst, aSecond)
    {
    }

    int Multiply::GetAnswerInt() const
    {
        if (isUsingFloats) {
            return static_cast<int>(std::round(firstNumber.f * secondNumber.f));
        }

        return firstNumber.i * secondNumber.i;
    }

    float Multiply::GetAnswerFloat() const
    {
        if (isUsingFloats) {
            return firstNumber.f * secondNumber.f;
        }

        return static_cast<float>(firstNumber.i * secondNumber.i);
    }
} // Math
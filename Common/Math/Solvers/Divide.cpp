#include "Divide.h"
#include <cmath>

namespace Math
{
    Divide::Divide(int aFirst, int aSecond): SolverBase(aFirst, aSecond)
    {
    }

    Divide::Divide(float aFirst, float aSecond): SolverBase(aFirst, aSecond)
    {
    }

    int Divide::GetAnswerInt() const
    {
        if (isUsingFloats) {
            return static_cast<int>(std::round(firstNumber.f / secondNumber.f));
        }

        return firstNumber.i / secondNumber.i;
    }

    float Divide::GetAnswerFloat() const
    {
        if (isUsingFloats) {
            return firstNumber.f / secondNumber.f;
        }

        return static_cast<float>(firstNumber.i / secondNumber.i);
    }
} // Math
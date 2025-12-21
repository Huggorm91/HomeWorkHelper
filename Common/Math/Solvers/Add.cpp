#include "Add.h"
#include <cmath>

namespace Math
{
    Add::Add(int aFirst, int aSecond): SolverBase(aFirst, aSecond)
    {
    }

    Add::Add(float aFirst, float aSecond): SolverBase(aFirst, aSecond)
    {
    }

    int Add::GetAnswerInt() const
    {
        if (isUsingFloats) {
            return static_cast<int>(std::round(firstNumber.f + secondNumber.f));
        }

        return firstNumber.i + secondNumber.i;
    }

    float Add::GetAnswerFloat() const
    {
        if (isUsingFloats) {
            return firstNumber.f + secondNumber.f;
        }

        return static_cast<float>(firstNumber.i + secondNumber.i);
    }
} // Math

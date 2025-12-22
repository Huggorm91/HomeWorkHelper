#include "Add.h"
#include <cmath>

namespace Math
{
    Add::Add(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats): SolverBase(anEngine, aMin, aMax, aIsUsingFloats)
    {
    }

    int Add::GetAnswerInt() const
    {
        if (isUsingFloats) {
            return static_cast<int>(std::round(myFirstNumber.f + mySecondNumber.f));
        }

        return myFirstNumber.i + mySecondNumber.i;
    }

    float Add::GetAnswerFloat() const
    {
        if (isUsingFloats) {
            return myFirstNumber.f + mySecondNumber.f;
        }

        return static_cast<float>(myFirstNumber.i + mySecondNumber.i);
    }

    char Add::GetSymbol() const
    {
        return '+';
    }
} // Math

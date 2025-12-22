#include "Subtract.h"
#include <cmath>

namespace Math
{
    Subtract::Subtract(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats): SolverBase(anEngine, aMin, aMax, aIsUsingFloats)
    {
    }

    int Subtract::GetAnswerInt() const
    {
        if (isUsingFloats) {
            return static_cast<int>(std::round(myFirstNumber.f - mySecondNumber.f));
        }

        return myFirstNumber.i - mySecondNumber.i;
    }

    float Subtract::GetAnswerFloat() const
    {
        if (isUsingFloats) {
            return myFirstNumber.f - mySecondNumber.f;
        }

        return static_cast<float>(myFirstNumber.i - mySecondNumber.i);
    }

    char Subtract::GetSymbol() const
    {
        return '-';
    }
} // Math
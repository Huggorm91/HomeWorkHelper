#include "Multiply.h"
#include <cmath>

namespace Math
{
    Multiply::Multiply(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats): SolverBase(anEngine, aMin, aMax, aIsUsingFloats)
    {
    }

    int Multiply::GetAnswerInt() const
    {
        if (isUsingFloats) {
            return static_cast<int>(std::round(myFirstNumber.f * mySecondNumber.f));
        }

        return myFirstNumber.i * mySecondNumber.i;
    }

    float Multiply::GetAnswerFloat() const
    {
        if (isUsingFloats) {
            return myFirstNumber.f * mySecondNumber.f;
        }

        return static_cast<float>(myFirstNumber.i * mySecondNumber.i);
    }

    char Multiply::GetSymbol() const
    {
        return '*';
    }
} // Math
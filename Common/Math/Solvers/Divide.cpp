#include "Divide.h"
#include <cmath>

namespace Math
{
    Divide::Divide(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats): SolverBase(anEngine, aMin, aMax, aIsUsingFloats)
    {
    }

    int Divide::GetAnswerInt() const
    {
        if (isUsingFloats) {
            return static_cast<int>(std::round(myFirstNumber.f / mySecondNumber.f));
        }

        return myFirstNumber.i / mySecondNumber.i;
    }

    float Divide::GetAnswerFloat() const
    {
        if (isUsingFloats) {
            return myFirstNumber.f / mySecondNumber.f;
        }

        return static_cast<float>(myFirstNumber.i / mySecondNumber.i);
    }

    char Divide::GetSymbol() const
    {
        return '/';
    }

    void Divide::GenerateNumbers()
    {
        SolverBase::GenerateNumbers();
        if (isUsingFloats) {
            if (mySecondNumber.f == 0.f) {
                mySecondNumber.f = 2.f;
            }
        }
        else {
            if (mySecondNumber.i == 0) {
                mySecondNumber.i = 2;
            }
        }
    }
} // Math
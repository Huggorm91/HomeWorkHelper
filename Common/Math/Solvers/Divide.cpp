#include "Divide.h"
#include <cmath>

namespace Math
{
    Divide::Divide(std::mt19937& anEngine, int aMin, int aMax, bool aIsUsingFloats): SolverBase(anEngine, aMin, aMax, aIsUsingFloats)
    {
    }

    int Divide::GetAnswerInt() const
    {
        if (myIsUsingFloats) {
            return static_cast<int>(std::round(myFirstNumber.f / mySecondNumber.f));
        }

        return myFirstNumber.i / mySecondNumber.i;
    }

    float Divide::GetAnswerFloat() const
    {
        if (myIsUsingFloats) {
            return myFirstNumber.f / mySecondNumber.f;
        }

        return static_cast<float>(myFirstNumber.i) / static_cast<float>(mySecondNumber.i);
    }

    char Divide::GetSymbol() const
    {
        return '/';
    }

    void Divide::GenerateNumbers()
    {
        SolverBase::GenerateNumbers();
        if (myIsUsingFloats) {
            int counter = 0;
            while(mySecondNumber.f == 0.f) {
                mySecondNumber.f = myNumberGenerator.f(myEngine);
                ++counter;
                if (counter == 10) {
                    mySecondNumber.f = 1.f;
                }
            }
        }
        else {
            int counter = 0;
            while(mySecondNumber.i == 0) {
                mySecondNumber.i = myNumberGenerator.i(myEngine);
                ++counter;
                if (counter == 10) {
                    mySecondNumber.i = 1;
                }
            }
        }
    }
} // Math
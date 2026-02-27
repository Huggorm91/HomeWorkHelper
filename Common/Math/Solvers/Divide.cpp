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
        constexpr int maxAttempts = 5;
        SolverBase::GenerateNumbers();
        if (myIsUsingFloats) {
            int counter = 0;
            while(mySecondNumber.f == 0.f) {
                mySecondNumber.f = RoundTo2Decimals(myNumberGenerator.f(myEngine));
                ++counter;
                if (counter == maxAttempts) {
                    mySecondNumber.f = 1.f;
                }
            }
        }
        else {
            int counter = 0;
            while(mySecondNumber.i == 0) {
                mySecondNumber.i = myNumberGenerator.i(myEngine);
                ++counter;
                if (counter == maxAttempts) {
                    mySecondNumber.i = 1;
                }
            }
        }
    }
} // Math
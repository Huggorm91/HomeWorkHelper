#include "SolverBase.h"

namespace Math
{
    SolverBase::SolverBase(std::mt19937& anEngine, int aMin, int aMax, bool anIsUsingFloats) :
        myIsUsingFloats(anIsUsingFloats),
        myFirstNumber{},
        mySecondNumber{},
        myNumberGenerator{},
        myEngine(anEngine)
    {
        SetExtremes(aMin, aMax);
    }
	
	void SolverBase::SetExtremes(int aMin, int aMax)
    {
        if (aMin > aMax) {
            std::swap(aMin, aMax);
        }
        if (myIsUsingFloats) {
            myNumberGenerator.f = std::uniform_real_distribution<float>(static_cast<float>(aMin), static_cast<float>(aMax));
        }
        else {
            myNumberGenerator.i = std::uniform_int_distribution<int>(aMin, aMax);
        }
    }

    bool SolverBase::Solve(int anAnswer) const
    {
        return anAnswer == GetAnswerInt();
    }

    bool SolverBase::Solve(float anAnswer) const
    {
        return anAnswer == GetAnswerFloat();
    }

    std::string SolverBase::GenerateEquation()
    {
        GenerateNumbers();
        if (myIsUsingFloats) {
            return std::to_string(myFirstNumber.f) + " " + GetSymbol() + " " + std::to_string(mySecondNumber.f);
        }
        return std::to_string(myFirstNumber.i) + " " + GetSymbol() + " " + std::to_string(mySecondNumber.i);
    }

    void SolverBase::GenerateNumbers()
    {
        if (myIsUsingFloats) {
            myFirstNumber.f = myNumberGenerator.f(myEngine);
            mySecondNumber.f = myNumberGenerator.f(myEngine);
        }
        else {
            myFirstNumber.i = myNumberGenerator.i(myEngine);
            mySecondNumber.i = myNumberGenerator.i(myEngine);
        }
    }
}

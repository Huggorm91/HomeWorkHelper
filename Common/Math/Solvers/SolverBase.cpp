#include "SolverBase.h"

#include <format>

namespace Math
{
    std::string FloatToString(float aFloat)
    {
        return std::format("{:.2f}",aFloat);
    }

    SolverBase::SolverBase(std::mt19937& anEngine, const int aMin, const int aMax, const bool anIsUsingFloats) :
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

    bool SolverBase::Solve(const int anAnswer) const
    {
        return anAnswer == GetAnswerInt();
    }

    bool SolverBase::Solve(const float anAnswer) const
    {
        return anAnswer == GetAnswerFloat();
    }

    std::string SolverBase::GenerateEquation()
    {
        GenerateNumbers();
        if (myIsUsingFloats) {
            return FloatToString(myFirstNumber.f) + " " + GetSymbol() + " " + FloatToString(mySecondNumber.f);
        }
        return std::to_string(myFirstNumber.i) + " " + GetSymbol() + " " + std::to_string(mySecondNumber.i);
    }

    void SolverBase::GenerateNumbers()
    {
        if (myIsUsingFloats) {
            myFirstNumber.f = RoundTo2Decimals(myNumberGenerator.f(myEngine));
            mySecondNumber.f = RoundTo2Decimals(myNumberGenerator.f(myEngine));
        }
        else {
            myFirstNumber.i = myNumberGenerator.i(myEngine);
            mySecondNumber.i = myNumberGenerator.i(myEngine);
        }
    }

    float SolverBase::RoundTo2Decimals(const float aNumber) const
    {
        return roundf(aNumber * 100.0f) / 100.0f;
    }
}

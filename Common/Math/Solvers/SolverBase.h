#ifndef HOMEWORKHELPER_SOLVERBASE_H
#define HOMEWORKHELPER_SOLVERBASE_H
#include <random>

namespace Math
{
	std::string FloatToString(float aFloat);

    class SolverBase
    {
    public:
        SolverBase(std::mt19937& anEngine, int aMin, int aMax, bool anIsUsingFloats);

        virtual ~SolverBase() = default;
		
		void SetExtremes(int aMin, int aMax);

        bool Solve(int anAnswer) const;

        bool Solve(float anAnswer) const;
		
		virtual std::string GenerateEquation();

        virtual int GetAnswerInt() const = 0;

        virtual float GetAnswerFloat() const = 0;
		
		virtual char GetSymbol() const = 0;
		
	protected:
        bool myIsUsingFloats;
        union
        {
            int i;
            float f;
        } myFirstNumber, mySecondNumber;
		
		union
        {
            std::uniform_int_distribution<int> i;
            std::uniform_real_distribution<float> f;
        } myNumberGenerator;
		
		std::mt19937& myEngine;
		
		virtual void GenerateNumbers();
    	float RoundTo2Decimals(float aNumber) const;
    };
} // Math

#endif //HOMEWORKHELPER_SOLVERBASE_H

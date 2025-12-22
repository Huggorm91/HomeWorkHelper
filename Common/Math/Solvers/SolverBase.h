#ifndef HOMEWORKHELPER_SOLVERBASE_H
#define HOMEWORKHELPER_SOLVERBASE_H
#include <random>

namespace Math
{
    class SolverBase
    {
    public:
        SolverBase(std::mt19937& anEngine, int aMin, int aMax) : 
						isUsingFloats(false),
						myNumberGenerator(aMin, aMax),
						myEngine(anEngine)
        {
			myFirstNumber.i = myNumberGenerator(myEngine);
			mySecondNumber.i = myNumberGenerator.i(myEngine);
        }

        SolverBase(std::mt19937& anEngine, float aMin, float aMax) : 
						isUsingFloats(true),
						myNumberGenerator{.f(aMin, aMax)},
						myEngine(anEngine)
        {
			myFirstNumber.f = myNumberGenerator.f(myEngine);
			mySecondNumber.f = myNumberGenerator.f(myEngine);
        }

        virtual ~SolverBase() = default;

        bool Solve(int anAnswer) const
        {
            return anAnswer == GetAnswerInt();
        }

        bool Solve(float anAnswer) const
        {
            return anAnswer == GetAnswerFloat();
        }
		
		virtual std::string_view GenerateEquation(){
			return myFirstNumber + " " + GetSymbol() + " " + mySecondNumber;
		}

        virtual int GetAnswerInt() const = 0;

        virtual float GetAnswerFloat() const = 0;
		
		virtual char GetSymbol() const = 0;
		
	protected:
        bool isUsingFloats;
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
		
		std::mt19937& myEngine
		
		virtual void GenerateNumbers(){
			if (isUsingFloats) {
				myFirstNumber.f = myNumberGenerator.f(myEngine);
				mySecondNumber.f = myNumberGenerator.f(myEngine);
			}
			else {
				myFirstNumber.i = myNumberGenerator.i(myEngine);
				mySecondNumber.i = myNumberGenerator.i(myEngine);
			}
		}
    };
} // Math

#endif //HOMEWORKHELPER_SOLVERBASE_H

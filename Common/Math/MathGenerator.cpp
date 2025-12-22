#include "MathGenerator.h"

#include "Solvers/Add.h"
#include "Solvers/Subtract.h"
#include "Solvers/Multiply.h"
#include "Solvers/Divide.h"

namespace Math
{
    MathGenerator::MathGenerator() : isUsingFloats(false),
                                     myMin(0),
                                     myMax(0),
                                     myNumberGenerator(),
                                     myEngine(std::random_device{}())
    {
    }

    MathGenerator::MathGenerator(const std::string_view& aSymbolList, int aMin, int aMax, bool useFloats) :
        isUsingFloats(useFloats),
        myMin(aMin),
        myMax(aMax),
        myNumberGenerator(),
        myEngine(std::random_device{}())
    {
		AddGenerators(aSymbolList);
    }

    void MathGenerator::AddGenerator(char aSymbol)
    {
        union
        {
            int i;
            float f;
        } firstNumber, secondNumber;

        if (isUsingFloats) {
            firstNumber.f = myNumberGenerator.f(myEngine);
            secondNumber.f = myNumberGenerator.f(myEngine);
        }
        else {
            firstNumber.i = myNumberGenerator.i(myEngine);
            secondNumber.i = myNumberGenerator.i(myEngine);
        }
		
		myNumberGenerator = std::uniform_int_distribution<int>(0, mySolvers.count());

        switch (aSymbol) {
            case '+': {
                if (isUsingFloats) {
                    mySolvers.emplace_back(std::make_unique<Add>(firstNumber.f, secondNumber.f));
                }
                else {
                    mySolvers.emplace_back(std::make_unique<Add>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            case '-': {
                if (isUsingFloats) {
                    mySolvers.emplace_back(std::make_unique<Subtract>(firstNumber.f, secondNumber.f));
                }
                else {
                    mySolvers.emplace_back(std::make_unique<Subtract>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            case '*': {
                if (isUsingFloats) {
                    mySolvers.emplace_back(std::make_unique<Multiply>(firstNumber.f, secondNumber.f));
                }
                else {
                    mySolvers.emplace_back(std::make_unique<Multiply>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            case '/': {
                if (isUsingFloats) {
                    while (secondNumber.f == 0.f) {
                        secondNumber.f = myNumberGenerator.f(myEngine);
                    }
                    mySolvers.emplace_back(std::make_unique<Divide>(firstNumber.f, secondNumber.f));
                }
                else {
                    while (secondNumber.i == 0) {
                        secondNumber.i = myNumberGenerator.i(myEngine);
                    }
                    mySolvers.emplace_back(std::make_unique<Divide>(firstNumber.i, secondNumber.i));
                }
                break;
            }
            default:
                break;
        }
    }

    void MathGenerator::AddGenerators(const std::string_view& aSymbolList)
    {
		// Loop through string and add each symbol using AddGenerator()
    }

    void MathGenerator::ClearGenerators()
    {
		mySolvers.clear();
		myNumberGenerator. // Reset
    }

    void MathGenerator::SetExtremes(int aMin, int aMax)
    {
        myMin = aMin;
        myMax = aMax;
        if (myMin > myMax) {
            std::swap(myMin, myMax);
        }
        if (isUsingFloats) {
            myNumberGenerator.f = std::uniform_real_distribution<float>(
                static_cast<float>(myMin),
                static_cast<float>(myMax)
            );
        }
        else {
            myNumberGenerator.i = std::uniform_int_distribution<int>(myMin, myMax);
        }
    }

    void MathGenerator::GenerateQuestion()
    {
		myCurrentSolverIndex = myNumberGenerator(myEngine);
		myQuestion = mySolvers[myCurrentSolverIndex].GenerateEquation();
    }

    std::string_view MathGenerator::GetQuestion() const
    {
		return myQuestion;
    }

    bool MathGenerator::CheckAnswer(int anAnswer)
    {
		return mySolvers[myCurrentSolverIndex].Solve(anAnswer);
    }

    bool MathGenerator::CheckAnswer(float anAnswer)
    {
		return mySolvers[myCurrentSolverIndex].Solve(anAnswer);
    }
} // Math
